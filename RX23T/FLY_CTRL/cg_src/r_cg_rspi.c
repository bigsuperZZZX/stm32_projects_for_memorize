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
* File Name    : r_cg_rspi.c
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
uint32_t * gp_rspi0_tx_address;         /* RSPI0 transmit buffer address */
uint16_t   g_rspi0_tx_count;            /* RSPI0 transmit data number */
uint32_t * gp_rspi0_rx_address;         /* RSPI0 receive buffer address */
uint16_t   g_rspi0_rx_count;            /* RSPI0 receive data number */
uint16_t   g_rspi0_rx_length;           /* RSPI0 receive data length */
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_RSPI0_Create
* Description  : This function initializes the RSPI0 module.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_RSPI0_Create(void)
{
    /* Disable RSPI interrupts */
    IEN(RSPI0,SPTI0) = 0U;
    IEN(RSPI0,SPRI0) = 0U;
    IEN(RSPI0,SPEI0) = 0U;
    IEN(RSPI0,SPII0) = 0U;

    /* Cancel RSPI module stop state */
    MSTP(RSPI0) = 0;

    /* Disable RSPI function */
    RSPI0.SPCR.BIT.SPE = 0U;

    /* Set control registers */
    RSPI0.SPPCR.BYTE = _00_RSPI_MOSI_FIXING_PREV_TRANSFER | _00_RSPI_LOOPBACK_DISABLED | _00_RSPI_LOOPBACK2_DISABLED;
    RSPI0.SPBR = _13_RSPI0_DIVISOR;
    RSPI0.SPDCR.BYTE = _00_RSPI_ACCESS_WORD | _00_RSPI_FRAMES_1;
    RSPI0.SPSCR.BYTE = _00_RSPI_SEQUENCE_LENGTH_1;
    RSPI0.SSLP.BYTE = _00_RSPI_SSL0_POLARITY_LOW | _00_RSPI_SSL1_POLARITY_LOW | _00_RSPI_SSL2_POLARITY_LOW | 
                      _00_RSPI_SSL3_POLARITY_LOW;
    RSPI0.SPCKD.BYTE = _00_RSPI_RSPCK_DELAY_1;
    RSPI0.SSLND.BYTE = _00_RSPI_SSL_NEGATION_DELAY_1;
    RSPI0.SPND.BYTE = _00_RSPI_NEXT_ACCESS_DELAY_1;
    RSPI0.SPCR2.BYTE = _00_RSPI_PARITY_DISABLE;
    RSPI0.SPCMD0.WORD = _0001_RSPI_RSPCK_SAMPLING_EVEN | _0000_RSPI_RSPCK_POLARITY_LOW | _000C_RSPI_BASE_BITRATE_8 | 
                        _0000_RSPI_SIGNAL_ASSERT_SSL0 | _0000_RSPI_SSL_KEEP_DISABLE | _0400_RSPI_DATA_LENGTH_BITS_8 | 
                        _0000_RSPI_MSB_FIRST | _0000_RSPI_NEXT_ACCESS_DELAY_DISABLE | 
                        _0000_RSPI_NEGATION_DELAY_DISABLE | _0000_RSPI_RSPCK_DELAY_DISABLE;

    /* Set SPEI0, SPRI0, SPTI0 and SPII0 priority level */
    IPR(RSPI0,SPTI0) = _0F_RSPI_PRIORITY_LEVEL15;

    /* Set RSPCKA pin */
    MPC.P24PFS.BYTE = 0x0DU;
    PORT2.PMR.BYTE |= 0x10U;

    /* Set MOSIA pin */
    MPC.P23PFS.BYTE = 0x0DU;
    PORT2.PMR.BYTE |= 0x08U;

    /* Set MISOA pin */
    MPC.P22PFS.BYTE = 0x0DU;
    PORT2.PMR.BYTE |= 0x04U;

    /* Set SSLA0 pin */
    MPC.P30PFS.BYTE = 0x0DU;
    PORT3.PMR.BYTE |= 0x01U;

    /* Set SSLA1 pin */
    MPC.P31PFS.BYTE = 0x0DU;
    PORT3.PMR.BYTE |= 0x02U;

    /* Set SSLA2 pin */
    MPC.P32PFS.BYTE = 0x0DU;
    PORT3.PMR.BYTE |= 0x04U;

    /* Set SSLA3 pin */
    MPC.P33PFS.BYTE = 0x0DU;
    PORT3.PMR.BYTE |= 0x08U;

    RSPI0.SPCR.BYTE = _00_RSPI_MODE_SPI | _00_RSPI_FULL_DUPLEX_SYNCHRONOUS | _08_RSPI_MASTER_MODE;
}

/***********************************************************************************************************************
* Function Name: R_RSPI0_Start
* Description  : This function starts the RSPI0 module operation.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_RSPI0_Start(void)
{
    volatile uint8_t dummy;

    /* Enable RSPI interrupts */
    IEN(RSPI0,SPTI0) = 1U;
    IEN(RSPI0,SPRI0) = 1U;
    IEN(RSPI0,SPEI0) = 1U;
    IEN(RSPI0,SPII0) = 1U;

    /* Clear error sources */
    dummy = RSPI0.SPSR.BYTE;
    RSPI0.SPSR.BYTE = 0xA0U;

    /* Disable idle interrupt */
    RSPI0.SPCR2.BIT.SPIIE = 0U;
}

/***********************************************************************************************************************
* Function Name: R_RSPI0_Stop
* Description  : This function stops the RSPI0 module operation.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_RSPI0_Stop(void)
{
    /* Disable RSPI interrupts */
    IEN(RSPI0,SPTI0) = 0U;
    IEN(RSPI0,SPRI0) = 0U;
    IEN(RSPI0,SPEI0) = 0U;
    IEN(RSPI0,SPII0) = 0U;

    /* Disable RSPI function */
    RSPI0.SPCR.BIT.SPE = 0U;
}
/***********************************************************************************************************************
* Function Name: R_RSPI0_Send_Receive
* Description  : This function sends and receives RSPI0 data.
* Arguments    : tx_buf -
*                    transfer buffer pointer (not used when data is handled by DTC)
*                tx_num -
*                    buffer size
*                rx_buf -
*                    receive buffer pointer (not used when data is handled by DTC)
* Return Value : status -
*                    MD_OK or MD_ARGERROR
***********************************************************************************************************************/
MD_STATUS R_RSPI0_Send_Receive(uint32_t * const tx_buf, uint16_t tx_num, uint32_t * const rx_buf)
{
    MD_STATUS status = MD_OK;

    if (tx_num < 1U)
    {
        status = MD_ARGERROR;
    }
    else
    {
        /* Initialize the global counters */
        gp_rspi0_tx_address = tx_buf;
        g_rspi0_tx_count = tx_num;
        gp_rspi0_rx_address = rx_buf;
        g_rspi0_rx_length = tx_num;
        g_rspi0_rx_count = 0U;

        /* Enable transmit interrupt */
        RSPI0.SPCR.BIT.SPTIE = 1U;

        /* Enable receive interrupt */
        RSPI0.SPCR.BIT.SPRIE = 1U;

        /* Enable error interrupt */
        RSPI0.SPCR.BIT.SPEIE = 1U;

        /* Enable RSPI function */
        RSPI0.SPCR.BIT.SPE = 1U;
    }

    return (status);
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
