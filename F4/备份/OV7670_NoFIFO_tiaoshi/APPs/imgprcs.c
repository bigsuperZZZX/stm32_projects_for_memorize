#include "sys.h"
#include "delay.h"
#include "OV7670.h"
#include "sccb.h"
#include "usart.h"
#include "dcmi.h" 
#include "imgprcs.h"

u8 rows_get;    //存储到哪一行
u8 color_get_flag=0; //颜色寻找完成
u8 balloon_remain=0x1f;   //还在的气球（按位存储，0x00,0x01-0x10） ,串口中断中接收信息
u8 row[640];
u8 R[120][120];
u8 G[120][120];
u8 B[120][120];
u8 Gray[120][120];
extern u8 color_absent2;  //找气球时哪种颜色缺失

u8 K_origR,K_origG,K_origB,R_origR,R_origG,R_origB,  //每次颜色标准值的初始值
	 G_origR,G_origG,G_origB,B_origR,B_origG,B_origB,
	 Y_origR,Y_origG,Y_origB;

StdColor_TypeDef std_color[5];     //五个颜色的标准色
ColorPosi_TypeDef color_posi[5];

struct 
{
	u8 x;
	u8 y;
}grow_stack[1000];   //区域生长法的栈

struct 
{
	u8 x;
	u8 y;
}class_posi[2000];   

/*定位每个气球的位置和大小，包括中间黑圆*/
/*颜色全有返回0x00，否则返回对应消失的颜色(按位表示，黑到黄分别从第0位起置1*/
u8 get_balloon(void)
{ 
	u16 i,j,k;   //这边的k和找标准色函数中的k含义不同，这个代表颜色，另一个函数中代表多个区域
	u8 error_sbl=0x00;
	
	/*以下繁琐的代换可将处理时间缩短30%*/
	u8 *pR = &R[0][0], *pG = &G[0][0], *pB = &B[0][0]; //指针数组寻址快一点，keil很奇怪不能直接将数组名赋值给指针
	u16 K_cpntR,K_cpntG,K_cpntB,R_cpntR,R_cpntG,R_cpntB,G_cpntR,G_cpntG,G_cpntB,
			B_cpntR,B_cpntG,B_cpntB,Y_cpntR,Y_cpntG,Y_cpntB;  //减少寻址花费时间，将结构体转变为单变量
	char K_deviR,K_deviG,K_deviB,R_deviR,R_deviG,R_deviB,G_deviR,G_deviG,G_deviB,
			 B_deviR,B_deviG,B_deviB,Y_deviR,Y_deviG,Y_deviB;  //减少寻址花费时间，将结构体转变为单变量
	u16 K_area_curr,R_area_curr,G_area_curr,B_area_curr,Y_area_curr;
	u32 K_sum_x,K_sum_y,R_sum_x,R_sum_y,G_sum_x,G_sum_y,B_sum_x,B_sum_y,Y_sum_x,Y_sum_y;
	K_area_curr=R_area_curr=G_area_curr=B_area_curr=Y_area_curr=0;  //全部初始化为零
	K_sum_x=K_sum_y=R_sum_x=R_sum_y=G_sum_x=G_sum_y=B_sum_x=B_sum_y=Y_sum_x=Y_sum_y=0;
	K_cpntR = std_color[0].StdR; K_cpntG = std_color[0].StdG; K_cpntB = std_color[0].StdB;
	R_cpntR = std_color[1].StdR; R_cpntG = std_color[1].StdG; R_cpntB = std_color[1].StdB;
	G_cpntR = std_color[2].StdR; G_cpntG = std_color[2].StdG; G_cpntB = std_color[2].StdB;
	B_cpntR = std_color[3].StdR; B_cpntG = std_color[3].StdG; B_cpntB = std_color[3].StdB;
	Y_cpntR = std_color[4].StdR; Y_cpntG = std_color[4].StdG; Y_cpntB = std_color[4].StdB;
	K_deviR = std_color[0].R_devi; K_deviG = std_color[0].G_devi; K_deviB = std_color[0].B_devi;
	R_deviR = std_color[1].R_devi; R_deviG = std_color[1].G_devi; R_deviB = std_color[1].B_devi;
	G_deviR = std_color[2].R_devi; G_deviG = std_color[2].G_devi; G_deviB = std_color[2].B_devi;
	B_deviR = std_color[3].R_devi; B_deviG = std_color[3].G_devi; B_deviB = std_color[3].B_devi;
	Y_deviR = std_color[4].R_devi; Y_deviG = std_color[4].G_devi; Y_deviB = std_color[4].B_devi;
	
	for(i=0;i<120;i++)
		for(j=0;j<120;j++)
		{
			if(abs(*(pR+i*120+j)-K_cpntR) <= K_deviR &&
				 abs(*(pG+i*120+j)-K_cpntG) <= K_deviG &&
				 abs(*(pB+i*120+j)-K_cpntB) <= K_deviB   )
			{
				K_area_curr++;
				K_sum_x += j;
				K_sum_y += i;
				continue;
			}
			if(abs(*(pR+i*120+j)-R_cpntR) <= R_deviR &&
				 abs(*(pG+i*120+j)-R_cpntG) <= R_deviG &&
				 abs(*(pB+i*120+j)-R_cpntB) <= R_deviB   )
			{
				R_area_curr++;
				R_sum_x += j;
				R_sum_y += i;
				continue;
			}
			if(abs(*(pR+i*120+j)-G_cpntR) <= G_deviR &&
				 abs(*(pG+i*120+j)-G_cpntG) <= G_deviG &&
				 abs(*(pB+i*120+j)-G_cpntB) <= G_deviB   )
			{
				G_area_curr++;
				G_sum_x += j;
				G_sum_y += i;
				continue;
			}
			if(abs(*(pR+i*120+j)-B_cpntR) <= B_deviR &&
				 abs(*(pG+i*120+j)-B_cpntG) <= B_deviG &&
				 abs(*(pB+i*120+j)-B_cpntB) <= B_deviB   )
			{
				B_area_curr++;
				B_sum_x += j;
				B_sum_y += i;
				continue;
			}
			if(abs(*(pR+i*120+j)-Y_cpntR) <= Y_deviR &&
				 abs(*(pG+i*120+j)-Y_cpntG) <= Y_deviG &&
				 abs(*(pB+i*120+j)-Y_cpntB) <= Y_deviB   )
			{
				Y_area_curr++;
				Y_sum_x += j;
				Y_sum_y += i;
				continue;
			}
		}
		
	color_posi[0].area_curr = K_area_curr;
	color_posi[1].area_curr = R_area_curr;
	color_posi[2].area_curr = G_area_curr;	
	color_posi[3].area_curr = B_area_curr;	
	color_posi[4].area_curr = Y_area_curr;
	color_posi[0].x = K_sum_x /= K_area_curr;
	color_posi[1].x = R_sum_x /= R_area_curr;
	color_posi[2].x = G_sum_x /= G_area_curr;
	color_posi[3].x = B_sum_x /= B_area_curr;
	color_posi[4].x = Y_sum_x /= Y_area_curr;
	color_posi[0].y = K_sum_y /= K_area_curr;
	color_posi[1].y = R_sum_y /= R_area_curr;
	color_posi[2].y = G_sum_y /= G_area_curr;
	color_posi[3].y = B_sum_y /= B_area_curr;
	color_posi[4].y = Y_sum_y /= Y_area_curr;  //由此sum已经不是sum了
		
	u8 color[5],stdcolor_temp=0; //中心点上下左右中心的颜色
	color[0] = R[K_sum_y][K_sum_x];                  //为节省运算时间，尽量避免使用结构体
	color[1] = R[K_sum_y-8][K_sum_x];
	color[2] = R[K_sum_y+8][K_sum_x];
	color[3] = R[K_sum_y][K_sum_x-8];
	color[4] = R[K_sum_y][K_sum_x+8];
	stdcolor_temp = (std_color[0].StdR *7 + get_middle(color) *3 + 5) /10;  //颜色更新
	if(abs(stdcolor_temp - K_origR) > 2)
		error_sbl |= 0x01;
	else
		std_color[0].StdR = stdcolor_temp;
	color[0] = G[K_sum_y][K_sum_x];                  
	color[1] = G[K_sum_y-3][K_sum_x];
	color[2] = G[K_sum_y+3][K_sum_x];
	color[3] = G[K_sum_y][K_sum_x-3];
	color[4] = G[K_sum_y][K_sum_x+3];
	stdcolor_temp = (std_color[0].StdG *7 + get_middle(color) *3 + 5) /10;
	if(abs(stdcolor_temp - K_origG) > 2)
		error_sbl |= 0x01;
	else
		std_color[0].StdG = stdcolor_temp;
	color[0] = B[K_sum_y][K_sum_x];                  
	color[1] = B[K_sum_y-3][K_sum_x];
	color[2] = B[K_sum_y+3][K_sum_x];
	color[3] = B[K_sum_y][K_sum_x-3];
	color[4] = B[K_sum_y][K_sum_x+3];
	stdcolor_temp = (std_color[0].StdB *7 + get_middle(color) *3 + 5) /10;
	if(abs(stdcolor_temp - K_origB) > 2)
		error_sbl |= 0x01;
	else
		std_color[0].StdB = stdcolor_temp;
	
	color[0] = R[R_sum_y][R_sum_x];                  //为节省运算时间，尽量避免使用结构体和循环
	color[1] = R[R_sum_y-3][R_sum_x];
	color[2] = R[R_sum_y+3][R_sum_x];
	color[3] = R[R_sum_y][R_sum_x-3];
	color[4] = R[R_sum_y][R_sum_x+3];
	stdcolor_temp = (std_color[1].StdR *7 + get_middle(color) *3 + 5) /10;   //2个数字、3个R\G\B , 一个KRBGY ，一个阈值, 1个return
	if(abs(stdcolor_temp - R_origR) > 5)
		error_sbl |= 0x02;
	else
		std_color[1].StdR = stdcolor_temp;
	color[0] = G[R_sum_y][R_sum_x];                  
	color[1] = G[R_sum_y-3][R_sum_x];
	color[2] = G[R_sum_y+3][R_sum_x];
	color[3] = G[R_sum_y][R_sum_x-3];
	color[4] = G[R_sum_y][R_sum_x+3];
	stdcolor_temp = (std_color[1].StdG *7 + get_middle(color) *3 + 5) /10;   //2个数字、3个R\G\B , 一个KRBGY ，一个阈值, 1个return
	if(abs(stdcolor_temp - R_origG) > 2)
		error_sbl |= 0x02;
	else
		std_color[1].StdG = stdcolor_temp;
	color[0] = B[R_sum_y][R_sum_x];                  
	color[1] = B[R_sum_y-3][R_sum_x];
	color[2] = B[R_sum_y+3][R_sum_x];
	color[3] = B[R_sum_y][R_sum_x-3];
	color[4] = B[R_sum_y][R_sum_x+3];
	stdcolor_temp = (std_color[1].StdB *7 + get_middle(color) *3 + 5) /10;   //2个数字、3个R\G\B , 一个KRGBY ，一个阈值, 1个return
	if(abs(stdcolor_temp - R_origB) > 2)
		error_sbl |= 0x02;
	else
		std_color[1].StdB = stdcolor_temp;
	
	color[0] = R[G_sum_y][G_sum_x];                  //为节省运算时间，尽量避免使用结构体和循环
	color[1] = R[G_sum_y-3][G_sum_x];
	color[2] = R[G_sum_y+3][G_sum_x];
	color[3] = R[G_sum_y][G_sum_x-3];
	color[4] = R[G_sum_y][G_sum_x+3];
	stdcolor_temp = (std_color[2].StdR *7 + get_middle(color) *3 + 5) /10;   //2个数字、3个R\G\B , 一个KRGBY ，一个阈值, 1个return
	if(abs(stdcolor_temp - G_origR) > 2)
		error_sbl |= 0x04;
	else
		std_color[2].StdR = stdcolor_temp;
	color[0] = G[G_sum_y][G_sum_x];                  
	color[1] = G[G_sum_y-3][G_sum_x];
	color[2] = G[G_sum_y+3][G_sum_x];
	color[3] = G[G_sum_y][G_sum_x-3];
	color[4] = G[G_sum_y][G_sum_x+3];
	stdcolor_temp = (std_color[2].StdG *7 + get_middle(color) *3 + 5) /10;   //2个数字、3个R\G\B , 一个KRGBY ，一个阈值, 1个return
	if(abs(stdcolor_temp - G_origG) > 5)
		error_sbl |= 0x04;
	else
		std_color[2].StdG = stdcolor_temp;
	color[0] = B[G_sum_y][G_sum_x];                  
	color[1] = B[G_sum_y-3][G_sum_x];
	color[2] = B[G_sum_y+3][G_sum_x];
	color[3] = B[G_sum_y][G_sum_x-3];
	color[4] = B[G_sum_y][G_sum_x+3];
	stdcolor_temp = (std_color[2].StdB *7 + get_middle(color) *3 + 5) /10;   //2个数字、3个R\G\B , 一个KRGBY ，一个阈值, 1个return
	if(abs(stdcolor_temp - G_origB) > 2)
		error_sbl |= 0x04;
	else
		std_color[2].StdB = stdcolor_temp;
	
	color[0] = R[B_sum_y][B_sum_x];                  //为节省运算时间，尽量避免使用结构体和循环
	color[1] = R[B_sum_y-3][B_sum_x];
	color[2] = R[B_sum_y+3][B_sum_x];
	color[3] = R[B_sum_y][B_sum_x-3];
	color[4] = R[B_sum_y][B_sum_x+3];
	stdcolor_temp = (std_color[3].StdR *7 + get_middle(color) *3 + 5) /10;   //2个数字、3个R\G\B , 一个KRGBY ，一个阈值, 1个return
	if(abs(stdcolor_temp - B_origR) > 2)
		error_sbl |= 0x08;
	else
		std_color[3].StdR = stdcolor_temp;
	color[0] = G[B_sum_y][B_sum_x];                  
	color[1] = G[B_sum_y-3][B_sum_x];
	color[2] = G[B_sum_y+3][B_sum_x];
	color[3] = G[B_sum_y][B_sum_x-3];
	color[4] = G[B_sum_y][B_sum_x+3];
	stdcolor_temp = (std_color[3].StdG *7 + get_middle(color) *3 + 5) /10;   //2个数字、3个R\G\B , 一个KRGBY ，一个阈值, 1个return
	if(abs(stdcolor_temp - B_origG) > 2)
		error_sbl |= 0x08;
	else
		std_color[3].StdG = stdcolor_temp;
	color[0] = B[B_sum_y][B_sum_x];                  
	color[1] = B[B_sum_y-3][B_sum_x];
	color[2] = B[B_sum_y+3][B_sum_x];
	color[3] = B[B_sum_y][B_sum_x-3];
	color[4] = B[B_sum_y][B_sum_x+3];
	stdcolor_temp = (std_color[3].StdB *7 + get_middle(color) *3 + 5) /10;   //2个数字、3个R\G\B , 一个KRGBY ，一个阈值, 1个return
	if(abs(stdcolor_temp - B_origB) > 5)
		error_sbl |= 0x08;
	else
		std_color[3].StdB = stdcolor_temp;
	
	color[0] = R[Y_sum_y][Y_sum_x];                  //为节省运算时间，尽量避免使用结构体和循环
	color[1] = R[Y_sum_y-3][Y_sum_x];
	color[2] = R[Y_sum_y+3][Y_sum_x];
	color[3] = R[Y_sum_y][Y_sum_x-3];
	color[4] = R[Y_sum_y][Y_sum_x+3];
	stdcolor_temp = (std_color[4].StdR *7 + get_middle(color) *3 + 5) /10;   //2个数字、3个R\G\B , 一个KRGBY ，一个阈值, 1个return
	if(abs(stdcolor_temp - Y_origR) > 4)
		error_sbl |= 0x10;
	else
		std_color[4].StdR = stdcolor_temp;
	color[0] = G[Y_sum_y][Y_sum_x];                  
	color[1] = G[Y_sum_y-3][Y_sum_x];
	color[2] = G[Y_sum_y+3][Y_sum_x];
	color[3] = G[Y_sum_y][Y_sum_x-3];
	color[4] = G[Y_sum_y][Y_sum_x+3];
	stdcolor_temp = (std_color[4].StdG *7 + get_middle(color) *3 + 5) /10;   //2个数字、3个R\G\B , 一个KRGBY ，一个阈值, 1个return
	if(abs(stdcolor_temp - Y_origG) > 4)
		error_sbl |= 0x10;
	else
		std_color[4].StdG = stdcolor_temp;
	color[0] = B[Y_sum_y][Y_sum_x];                  
	color[1] = B[Y_sum_y-3][Y_sum_x];
	color[2] = B[Y_sum_y+3][Y_sum_x];
	color[3] = B[Y_sum_y][Y_sum_x-3];
	color[4] = B[Y_sum_y][Y_sum_x+3];
	stdcolor_temp = (std_color[4].StdB *7 + get_middle(color) *3 + 5) /10;   //2个数字、3个R\G\B , 一个KRGBY ，一个阈值, 1个return
	if(abs(stdcolor_temp - Y_origB) > 2)
		error_sbl |= 0x10;
	else
		std_color[4].StdB = stdcolor_temp;
	
	for(k=0;k<5;k++)
	{
		color_posi[k].area_last = color_posi[k].area_curr;
		color_transfer(1,1<<k,color_posi[k].x,color_posi[k].y,color_posi[k].area_curr);
//		printf("%d (%d,%d)\r\n",color_posi[k].area_curr,color_posi[k].x,color_posi[k].y);
	}
//	printf("\r\n");
	for(k=0;k<5;k++)
	{
		color_posi[k].area_curr = 0;
		color_posi[k].x = 0;
		color_posi[k].y = 0;
	}
	
	return error_sbl & balloon_remain ;
}


/*错误返回0，正确返回1*/
/*开始时为每种颜色寻找最优三颜色分量*/
/*并在起开始时候的识别和中心黑圆的坐标输出*/
u8 get_stdcolor(void)   //寻找几种颜色的标准值和输出位置信息
{
	u16 i,j,k;             	 //i:行号，j：列号，k区域号(从1开始)
	u8 area_num2;          	 //区域数量  
	
	ImgPrcs_TypeDef area_info[20];  //定义各区域信息结构体变量
	
	for(k=0;k<20;k++)
	{
		area_info[k].color=0;
		area_info[k].acre=0;
	}
	
	roberts(Gray,120,120);   //进行一次边缘检测
	
	area_num2=area_grow();   //图像分块并存入Gray , 存入格式：0x80+area_num，0x80代表有效边缘，area_num为分区编号
	
	if(area_num2==0 || area_num2>19) 
		return 0;
	
//	img_display(Gray);
	
	
	/*统计各区域面积，计算各区域中心坐标*/
	for(i=0;i<area_num2;i++)  
	{
		area_info[i].acre=0;
		area_info[i].area_x=0;
		area_info[i].area_y=0;
	}
	for(i=0;i<120;i++)       //统计各区域数量，计算x、y总和
		for(j=0;j<120;j++)
		{
			if(Gray[i][j] >0x80 ) 
			{
				u8 temp = Gray[i][j]&0x7f;
				area_info[temp].acre++;
				area_info[temp].area_x += j;
				area_info[temp].area_y += i;
			}
		}
	for(i=0;i<area_num2;i++)  //得各区域x，y坐标
	{
		area_info[i].area_x = area_info[i].area_x/area_info[i].acre;
		area_info[i].area_y = area_info[i].area_y/area_info[i].acre;
	}
	
	/*找小圆和中心圆 */
	u8 temp_y,temp_max,temp_x;				//找最大半径时用    
	u8 max_num=0;             //找出的最大半径区域号
	for(k=1;k<area_num2;k++)     //修改：最后一列全置为0，k从1开始
	{
		area_info[k].Y_N=1;   //假定是圆
		
		for(i=area_info[k].area_y ;i>1;i--)           //向上穿线
			if(Gray[i][area_info[k].area_x] == 0x80+k)
			{
				area_info[k].get=area_info[k].area_y-i;
				break;
			}
		if(i<=1) {area_info[k].Y_N=0;goto END;}
		for( ;i>1;i--)
			if(Gray[i][area_info[k].area_x] != 0x80+k)
			{
				area_info[k].leave=area_info[k].area_y-i;
				break;
			}
		
		for(i=area_info[k].area_y ,j=area_info[k].area_x ; i>1&&j<117 ; i--,j++)           //右上穿线
			if(Gray[i][j] == 0x80+k)
			{
				temp_y=area_info[k].area_y-i;
				if( temp_y>area_info[k].get || 2*temp_y<area_info[k].get)
				{
					area_info[k].Y_N=0;
					goto END;                 //完全跳出
				}
				area_info[k].get=temp_y;
				break;
			}
		if(i<=1) {area_info[k].Y_N=0;goto END;}
		for( ; i>1&&j<117 ; i--,j++)
			if(Gray[i][j] != 0x80+k)
			{
				temp_y=area_info[k].area_y-i;
				if( temp_y>area_info[k].leave || 2*temp_y<area_info[k].leave)
				{
					area_info[k].Y_N=0;
					goto END;                 //完全跳出
				}
				area_info[k].leave=temp_y;
				break;
			}
			
		for(j=area_info[k].area_x ;j<118;j++)           //向右穿线
			if(Gray[area_info[k].area_y][j] == 0x80+k)
			{
				temp_x=j-area_info[k].area_x;
				if( temp_x<area_info[k].get || temp_x>area_info[k].get*2)
				{
					area_info[k].Y_N=0;
					goto END;                 //完全跳出
				}
				area_info[k].get=temp_x;
				break;
			}
		if(j>=118) {area_info[k].Y_N=0;goto END;}
		for( ;j<118;j++)
			if(Gray[area_info[k].area_y][j] != 0x80+k)
			{
				temp_x=j-area_info[k].area_x;
				if( temp_x<area_info[k].leave || temp_x>area_info[k].leave*2)
				{
					area_info[k].Y_N=0;
					goto END;                 //完全跳出
				}
				area_info[k].leave=temp_x;
				break;
			}
		
		for(i=area_info[k].area_y ,j=area_info[k].area_x ; i<117&&j<117 ; i++,j++)           //右下穿线
			if(Gray[i][j] == 0x80+k)
			{
				temp_y=i-area_info[k].area_y;
				if( temp_y>area_info[k].get || 2*temp_y<area_info[k].get)
				{
					area_info[k].Y_N=0;
					goto END;                 //完全跳出
				}
				area_info[k].get=temp_y;
				break;
			}
		if(i>=117) {area_info[k].Y_N=0;goto END;}
		for( ; i<117&&j<117 ; i++,j++)
			if(Gray[i][j] != 0x80+k)
			{
				temp_y=i-area_info[k].area_y;
				if( temp_y>area_info[k].leave || 2*temp_y<area_info[k].leave)
				{
					area_info[k].Y_N=0;
					goto END;                 //完全跳出
				}
				area_info[k].leave=temp_y;
				break;
			}
			
			
		for(i=area_info[k].area_y ;i<118;i++)           //向xia穿线
			if(Gray[i][area_info[k].area_x] == 0x80+k)
			{
				temp_y=i-area_info[k].area_y;
				if( temp_y<area_info[k].get || temp_y>area_info[k].get*2)
				{
					area_info[k].Y_N=0;
					goto END;                 //完全跳出
				}
				area_info[k].get=temp_y;
				break;
			}
		if(i>=118) {area_info[k].Y_N=0;goto END;}
		for( ;i<118;i++)
			if(Gray[i][area_info[k].area_x] != 0x80+k)
			{
				temp_y=i-area_info[k].area_y;
				if( temp_y<area_info[k].leave || temp_y>area_info[k].leave*2)
				{
					area_info[k].Y_N=0;
					goto END;                 //完全跳出
				}
				area_info[k].leave=temp_y;
				break;
			}
			
		for(i=area_info[k].area_y,j=area_info[k].area_x ; i<118&&j>1 ;i++,j--)           //左下穿线
			if(Gray[i][j] == 0x80+k)
			{
				temp_y=i-area_info[k].area_y;
				if( temp_y>area_info[k].get || 2*temp_y<area_info[k].get)
				{
					area_info[k].Y_N=0;
					goto END;                 //完全跳出
				}
				area_info[k].get=temp_y;
				break;
			}
		if(i>=118) {area_info[k].Y_N=0;goto END;}
		for( ; i<118&&j>1 ; i++,j--)
			if(Gray[i][j] != 0x80+k)
			{
				temp_y=i-area_info[k].area_y;
				if( temp_y>area_info[k].leave || 2*temp_y<area_info[k].leave)
				{
					area_info[k].Y_N=0;
					goto END;                 //完全跳出
				}
				area_info[k].leave=temp_y;
				break;
			}
			
		for(j=area_info[k].area_x ;j>0;j--)           //向左穿线
			if(Gray[area_info[k].area_y][j] == 0x80+k)
			{
				temp_x=area_info[k].area_x-j;
				if( temp_x<area_info[k].get || temp_x>area_info[k].get*2)
				{
					area_info[k].Y_N=0;
					goto END;                 //完全跳出
				}
				area_info[k].get=temp_x;
				break;
			}
		if(j<=0) {area_info[k].Y_N=0;goto END;}
		for( ;j>0;j--)
			if(Gray[area_info[k].area_y][j] != 0x80+k)
			{
				temp_x=area_info[k].area_x-j;
				if( temp_x<area_info[k].leave || temp_x>area_info[k].leave*2)
				{
					area_info[k].Y_N=0;
					goto END;                 //完全跳出
				}
				area_info[k].leave=temp_x;
				break;
			}
			
			for(i=area_info[k].area_y,j=area_info[k].area_x ; i>1&&j>1 ;i--,j--)           //左上穿线
			if(Gray[i][j] == 0x80+k)
			{
				temp_y=area_info[k].area_y-i;
				if( temp_y>area_info[k].get || 2*temp_y<area_info[k].get)
				{
					area_info[k].Y_N=0;
					goto END;                 //完全跳出
				}
				area_info[k].get=temp_y;
				break;
			}
		if(i<=1) {area_info[k].Y_N=0;goto END;}
		for( ; i>1&&j>1 ; i--,j--)
			if(Gray[i][j] != 0x80+k)
			{
				temp_y=area_info[k].area_y-i;
				if( temp_y>area_info[k].leave || 2*temp_y<area_info[k].leave)
				{
					area_info[k].Y_N=0;
					goto END;                 //完全跳出
				}
				area_info[k].leave=temp_y;
				break;
			}
			
		END:;                    //当前区域不是圆，提前跳出循环
	}

	
		for(k=1;k<area_num2;k++)    //输出各区域信息
		{
			if(area_info[k].Y_N != 0 )
			{
				color_transfer(0,area_info[k].color>>1,(u8)area_info[k].area_x,(u8)area_info[k].area_y,area_info[k].acre);
			}
		}
	
		
//		data_output(k,area_num2,area_info,data_valid);  //串口输出至电脑显示
//	img_display(Gray);
	
	return 1;
}


void getline(void)
{
	int i,j;
	u32 sum_x = 0,count = 0;
	for(i=0;i<120;i++)
		for(j=0;j<120;j++)
		{
			if( Gray[i][j] < 20 )
			{
				sum_x += j;
			}
		}
	sum_x /= count;
	printf("%d",sum_x);
}


void get_point(u8 posi[2])
{
	u8 i,j;
	u32 sum_x=0,sum_y=0,count=0;
	roberts(Gray,120,120);
	for(i=0;i<120;i++)
		for(j=0;j<120;j++)
			if(Gray[i][j]>9)
			{
				sum_x += j;
				sum_y += i;
				count++;
			}
	posi[0] = sum_x/count;
	posi[1] = sum_y/count;
	printf("%4d %4d\r\n",posi[0],posi[1]);
}


/***出错返回0，正确返回区域数量+1（因为k是从1开始的）*/
u8 area_grow(void)     //区域生长函数    
{ 
	u8 i,j,i_last,j_last;
	u16 n;
	int top=0;             //栈顶
	u8 area_num=1;         //各白色区域区域号 编号1开始
	u16 area_acre=0;       //单色区域面积
	for(i=4;i<120;i+=10)
		for(j=1;j<117;j++)
			if(Gray[i][j] > 9 && Gray[i-1][j] < 0x80)    //具体大于多少阈值还需计算
			{
				i_last=i; j_last=j;
				top=0;
				Gray[i][j] = 0;    //种子点
	//			data_process1();
				while(top!=-1)
				{
					/*遍历四周8个元素*/
					if(Gray[i-1][j] > 9 && Gray[i-1][j] < 0x80)
					{
						Gray[i-1][j] = 0;
						class_posi[area_acre].x = grow_stack[top].x = j;
						class_posi[area_acre].y = grow_stack[top].y=i-1;
						top++;
						area_acre++;
					}
					if(Gray[i-1][j+1] > 9 && Gray[i-1][j+1] < 0x80)
					{
						Gray[i-1][j+1] = 0;
						class_posi[area_acre].x = grow_stack[top].x=j+1;
						class_posi[area_acre].y = grow_stack[top].y=i-1;
						top++;
						area_acre++;
					}
					if(Gray[i][j+1] > 9 && Gray[i][j+1] < 0x80)
					{
						Gray[i][j+1] = 0;
						class_posi[area_acre].x = grow_stack[top].x=j+1;
						class_posi[area_acre].y = grow_stack[top].y=i;
						top++;
						area_acre++;
					}
					if(Gray[i+1][j+1] > 9 && Gray[i+1][j+1] < 0x80)
					{
						Gray[i+1][j+1] = 0;
						class_posi[area_acre].x = grow_stack[top].x=j+1;
						class_posi[area_acre].y = grow_stack[top].y=i+1;
						top++;
						area_acre++;
					}
					if(Gray[i+1][j] > 9 && Gray[i+1][j] < 0x80)
					{
						Gray[i+1][j] = 0;
						class_posi[area_acre].x = grow_stack[top].x=j;
						class_posi[area_acre].y = grow_stack[top].y=i+1;
						top++;
						area_acre++;
					}
					if(Gray[i+1][j-1] > 9 && Gray[i+1][j-1] < 0x80)
					{
						Gray[i+1][j-1] = 0;
						class_posi[area_acre].x = grow_stack[top].x=j-1;
						class_posi[area_acre].y = grow_stack[top].y=i+1;
						top++;
						area_acre++;
					}
					if(Gray[i][j-1] > 9 && Gray[i][j-1] < 0x80)
					{
						Gray[i][j-1] = 0;
						class_posi[area_acre].x = grow_stack[top].x=j-1;
						class_posi[area_acre].y = grow_stack[top].y=i;
						top++;
						area_acre++;
					}
					if(Gray[i-1][j-1] > 9 && Gray[i-1][j-1] < 0x80)
					{
						Gray[i-1][j-1] = 0;
						class_posi[area_acre].x = grow_stack[top].x=j-1;
						class_posi[area_acre].y = grow_stack[top].y=i-1;
						top++;
						area_acre++;
					}
					/*四周8个元素遍历完*/
					if(area_acre>1996 || top>998){    //太大了，丢弃
						return 0;}
					/*取出栈顶元素*/
					if(top>0)
					{
						i=grow_stack[top-1].y;
						j=grow_stack[top-1].x;
					}
					top--;
				}
				if(area_acre>20)             //区域面积足够大，有效
				{
					for(n=0;n<area_acre;n++)
					{
						Gray[ class_posi[n].y ][ class_posi[n].x ] = area_num+0x80;
					}
					area_num++;
				}
				i=i_last; j=j_last;
				area_acre=0;
			}
//	printf("%d ",area_num);
			
	return (area_num);
}
 
/*roberts算子边缘检测*/
void roberts(u8 in[120][120],int rows,int cols)   //边缘检测函数
{
	int h,q,v,i,j;
	for(i=0;i<rows-2;i++)
	{
		for(j=0;j<cols-2;j++)
		{
			h=in[i][j]-in[i+2][j+2];
			v=in[i][j+2]-in[i+2][j];
			q=abs(h)+abs(v);
			if(q<=2) q=0;
			if(q>127) q=127;
			in[i][j]=q;
		}
		in[i][118]=in[i][119]=0;
	}
	for(j=0;j<120;j++)
		in[118][j]=in[119][j]=0;
}

int abs(int i)
{
	if(i<0) i=-i;
	return i;
}

u8 get_middle(u8 color[5])
{
	char i,j;
	unsigned char temp;
	for(i=0;i<3;i++)
		for(j=4;j>i;j--)
			if(color[j-1]<color[j])
			{
				temp=color[j-1];
				color[j-1]=color[j];
				color[j]=temp;
			}
	return color[2];
}

/*各颜色各分量比较偏差初始化*/
void devition_init(void)
{
	std_color[0].R_devi=1;
	std_color[0].G_devi=1;
	std_color[0].B_devi=1;
	std_color[1].R_devi=3;
	std_color[1].G_devi=1;
	std_color[1].B_devi=1;
	std_color[2].R_devi=1;
	std_color[2].G_devi=3;
	std_color[2].B_devi=1;
	std_color[3].R_devi=1;
	std_color[3].G_devi=1;
	std_color[3].B_devi=3;
	std_color[4].R_devi=3;
	std_color[4].G_devi=3;
	std_color[4].B_devi=1;
}

void color_transfer(u8 which_f, u8 color, u8 x, u8 y, u16 area)  //第一个参数，0代表找标准色函数，1代表另一个函数
{
//	printf("%d 0X%X x%d y%d S%d\r\n",which_f,color,x,y,area);
	
	printf("%d %d\r\n",x,y);
	
	/*if(which_f == 0)
		USART_SendData(USART1,0xc0);
	if(which_f == 1)
		USART_SendData(USART1,0xc1);
	USART_SendData(USART1,color);
	USART_SendData(USART1,x);
	USART_SendData(USART1,y);
	USART_SendData(USART1,(area&0xff00)>>8);
	USART_SendData(USART1,area&0x00ff);
	if(which_f == 0)
		USART_SendData(USART1,0xc0);
	if(which_f == 1)
		USART_SendData(USART1,0xc1);*/
}

void img_display(u8 img[120][120])  //串口输出图像
{
	int i,j;
	DCMI_Stop();
	USART_SendData(USART1,0);
	delay_us(40);
	USART_SendData(USART1,255);
	delay_us(40);
	USART_SendData(USART1,1);
	delay_us(40);
	USART_SendData(USART1,0);
	delay_us(40);
	for(i=0;i<120;i++)
	{
		 for(j=0;j<120;j++)
		 {
			 delay_us(40);
			 USART_SendData(USART1, img[i][j]);
		 }
  }
	DCMI_Start();
}

void data_output(u16 k , u8 area_num2 , ImgPrcs_TypeDef area_info[20] , u8 data_valid)   //串口输出至电脑显示
{
	if(data_valid!=0)
	{
		for(k=1;k<area_num2;k++)    //输出各区域信息
		{
			if(area_info[k].acre != 0 && area_info[k].color != 0 )
			{
				if(area_info[k].color == 0x02)
					printf("黑     :%3d 坐标X:%3d Y%3d\r\n",area_info[k].acre,area_info[k].area_x,area_info[k].area_y);
			}
		}
		for(k=1;k<area_num2;k++)    //输出各区域信息
		{
			if(area_info[k].acre != 0 && area_info[k].color != 0 )
			{
				if(area_info[k].color == 0x04)
					printf("红     :%3d 坐标X:%3d Y%3d\r\n",area_info[k].acre,area_info[k].area_x,area_info[k].area_y);
			}
		}
		for(k=1;k<area_num2;k++)    //输出各区域信息
		{
			if(area_info[k].acre != 0 && area_info[k].color != 0 )
			{
				if(area_info[k].color == 0x08)
					printf("绿 面积:%3d 坐标X:%3d Y%3d\r\n",area_info[k].acre,area_info[k].area_x,area_info[k].area_y);
			}
		}
		for(k=1;k<area_num2;k++)    //输出各区域信息
		{
			if(area_info[k].acre != 0 && area_info[k].color != 0 )
			{
				if(area_info[k].color == 0x10)
					printf("蓝     :%3d 坐标X:%3d Y%3d\r\n",area_info[k].acre,area_info[k].area_x,area_info[k].area_y);
			}
		}
		for(k=1;k<area_num2;k++)    //输出各区域信息
		{
			if(area_info[k].acre != 0 && area_info[k].color != 0 )
			{
				if(area_info[k].color == 0x20)
					printf("黄     :%3d 坐标X:%3d Y%3d\r\n",area_info[k].acre,area_info[k].area_x,area_info[k].area_y);
			}
		}
		//printf("\r\n");	
	}
	else
			printf("无效\r\n\r\n");
}


