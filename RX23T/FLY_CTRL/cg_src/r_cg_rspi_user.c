/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products.
* No other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
* applicable laws, including copyright laws. 
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIESREGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED
* OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY
* LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE FOR ANY DIRECT,
* INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR
* ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability 
* of this software. By using this software, you agree to the additional terms and conditions found by accessing the 
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2015, 2016 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name    : r_cg_rspi_user.c
* Version      : Code Generator for RX23T V1.00.04.02 [29 Nov 2016]
* Device(s)    : R5F523T5AxFM
* Tool-Chain   : CCRX
* Description  : This file implements device driver for RSPI module.
* Creation Date: 2017/6/25
***********************************************************************************************************************/

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_rspi.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
extern uint32_t * gp_rspi0_tx_address;         /* RSPI0 transmit buffer address */
extern uint16_t   g_rspi0_tx_count;            /* RSPI0 transmit data number */
extern uint32_t * gp_rspi0_rx_address;         /* RSPI0 receive buffer address */
extern uint16_t   g_rspi0_rx_count;            /* RSPI0 receive data number */
extern uint16_t   g_rspi0_rx_length;           /* RSPI0 receive data length */
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: r_rspi0_transmit_interrupt
* Description  : None
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
#if FAST_INTERRUPT_VECTOR == VECT_RSPI0_SPTI0
#pragma interrupt r_rspi0_transmit_interrupt(vect=VECT(RSPI0,SPTI0),fint)
#else
#pragma interrupt r_rspi0_transmit_interrupt(vect=VECT(RSPI0,SPTI0))
#endif
static void r_rspi0_transmit_interrupt(void)
{
    uint16_t frame_cnt;
        
    for (frame_cnt = 0U; frame_cnt < (_00_RSPI_FRAMES_1 + 1U); frame_cnt++)
    {
        if (g_rspi0_tx_count > 0U)
        {
            /* Write data for transmission */
            RSPI0.SPDR.WORD.H = (*(uint16_t*)gp_rspi0_tx_address);
            gp_rspi0_tx_address++;
            g_rspi0_tx_count--;
        }
        else
        {
            /* Disable transmit interrupt */
            RSPI0.SPCR.BIT.SPTIE = 0U;

            /* Enable idle interrupt */
            RSPI0.SPCR2.BIT.SPIIE = 1U;
            break;
        }
    }
}
/***********************************************************************************************************************
* Function Name: r_rspi0_receive_interrupt
* Description  : None
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
#if FAST_INTERRUPT_VECTOR == VECT_RSPI0_SPRI0
#pragma interrupt r_rspi0_receive_interrupt(vect=VECT(RSPI0,SPRI0),fint)
#else
#pragma interrupt r_rspi0_receive_interrupt(vect=VECT(RSPI0,SPRI0))
#endif
static void r_rspi0_receive_interrupt(void)
{
    uint16_t frame_cnt;
    
    for (frame_cnt = 0U; frame_cnt < (_00_RSPI_FRAMES_1 + 1U); frame_cnt++)
    {
        if (g_rspi0_rx_length > g_rspi0_rx_count)
        {
            *(uint16_t *)gp_rspi0_rx_address = RSPI0.SPDR.WORD.H;
            gp_rspi0_rx_address++;
            g_rspi0_rx_count++;

            if (g_rspi0_rx_length == g_rspi0_rx_count)
            {
                /* Disable receive interrupt */
                RSPI0.SPCR.BIT.SPRIE = 0U;
                r_rspi0_callback_receiveend();
                break;
            }
        }
    }
}
/***********************************************************************************************************************
* Function Name: r_rspi0_error_interrupt
* Description  : None
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
#if FAST_INTERRUPT_VECTOR == VECT_RSPI0_SPEI0
#pragma interrupt r_rspi0_error_interrupt(vect=VECT(RSPI0,SPEI0),fint)
#else
#pragma interrupt r_rspi0_error_interrupt(vect=VECT(RSPI0,SPEI0))
#endif
static void r_rspi0_error_interrupt(void)
{
    uint8_t err_type;

    if (1U == RSPI0.SPSR.BIT.MODF)
    {
        /* Confirm that SSL0 pin is at inactive level */
    }

    /* Disable RSPI function */
    RSPI0.SPCR.BIT.SPE = 0U;

    /* Disable transmit interrupt */
    RSPI0.SPCR.BIT.SPTIE = 0U;

    /* Disable receive interrupt */
    RSPI0.SPCR.BIT.SPRIE = 0U;

    /* Disable error interrupt */
    RSPI0.SPCR.BIT.SPEIE = 0U;

    /* Disable idle interrupt */
    RSPI0.SPCR2.BIT.SPIIE = 0U;

    /* Clear error sources */
    err_type = RSPI0.SPSR.BYTE;
    RSPI0.SPSR.BYTE = 0xA0U;

    if (0U != err_type)
    {
        r_rspi0_callback_error(err_type);
    }
}
/***********************************************************************************************************************
* Function Name: r_rspi0_idle_interrupt
* Description  : None
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
#if FAST_INTERRUPT_VECTOR == VECT_RSPI0_SPII0
#pragma interrupt r_rspi0_idle_interrupt(vect=VECT(RSPI0,SPII0),fint)
#else
#pragma interrupt r_rspi0_idle_interrupt(vect=VECT(RSPI0,SPII0))
#endif
static void r_rspi0_idle_interrupt(void)
{
    /* Disable RSPI function */
    RSPI0.SPCR.BIT.SPE = 0U;

    /* Disable idle interrupt */
    RSPI0.SPCR2.BIT.SPIIE = 0U;

    r_rspi0_callback_transmitend();
}
/***********************************************************************************************************************
* Function Name: r_rspi0_callback_transmitend
* Description  : This function is a callback function when RSPI0 finishes transmission.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
static void r_rspi0_callback_transmitend(void)
{
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: r_rspi0_callback_receiveend
* Description  : This function is a callback function when RSPI0 finishes reception.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
static void r_rspi0_callback_receiveend(void)
{
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: r_rspi0_callback_error
* Description  : This function is a callback function when RSPI0 error occurs.
* Arguments    : err_type -
*                    error type value
* Return Value : None
***********************************************************************************************************************/
static void r_rspi0_callback_error(uint8_t err_type)
{
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
