/*
 ## Cypress CX3 Video Streaming Control Source File (cycx3_videostreaming.c)
 ## ===========================
 ##
 ##  Copyright Cypress Semiconductor Corporation, 2018-2019,
 ##  All Rights Reserved
 ##  UNPUBLISHED, LICENSED SOFTWARE.
 ##
 ##  CONFIDENTIAL AND PROPRIETARY INFORMATION
 ##  WHICH IS THE PROPERTY OF CYPRESS.
 ##
 ##  Use of this file is governed
 ##  by the license agreement included in the file
 ##
 ##     <install>/license/license.txt
 ##
 ##  where <install> is the Cypress software
 ##  installation root directory path.
 ##
 ## ===========================
*/

#include "cyu3system.h"
#include "cyu3os.h"
#include "cyu3dma.h"
#include "cyu3error.h"
#include "cyu3usb.h"
#include "cyu3utils.h"
#include "cyu3socket.h"
#include "sock_regs.h"
#include "cycx3_videostreaming.h"
#include "cycx3_uvc.h"
#include "cyu3mipicsi.h"
#include "cyu3imagesensor.h"
#include "cycx3_imagesensor.h"

/***********************************************************************************************
 ***************************** MIPI Configuration Parameters (HS and SS) ***********************
 **********************************************************************************************/

/* MIPI Configuration parameters to interface with OV5640_YUY2_Resolution1 :  (2592 x 1944 @ 15.0 fps) */
CyU3PMipicsiCfg_t mipiConfig_OV5640_YUY2_Resolution1 =  
{
    CY_U3P_MIPIOUT_DW_16,       /* MIPI out parallel width packing */
    2,                          /* Number of CSI data lanes. */
    1,                          /* PLL clock input divider. */
    64,                         /* PLL clock feedback divider. */
    CY_U3P_CSI_PLL_FRS_500_1000M, /* PLL clock range. */  
    CY_U3P_CSI_PLL_CLK_DIV_8,     /* Divider for clock used to detect CSI LP<->HS transition. */
    CY_U3P_CSI_PLL_CLK_DIV_8,	/* Divider for clock used on the parallel GPIF interface. */
    0x00,		                /* Reserved */
    0x00,                       /* Reserved */
    0x00,                       /* Reserved */
    1                        /* Delay on the parallel output buffer of CSI interface. */
};

/* MIPI Configuration parameters to interface with OV5640_YUY2_Resolution2 :  (1920 x 1080 @ 30.0 fps) */
CyU3PMipicsiCfg_t mipiConfig_OV5640_YUY2_Resolution2 =  
{
    CY_U3P_MIPIOUT_DW_16,       /* MIPI out parallel width packing */
    2,                          /* Number of CSI data lanes. */
    1,                          /* PLL clock input divider. */
    62,                         /* PLL clock feedback divider. */
    CY_U3P_CSI_PLL_FRS_500_1000M, /* PLL clock range. */  
    CY_U3P_CSI_PLL_CLK_DIV_8,     /* Divider for clock used to detect CSI LP<->HS transition. */
    CY_U3P_CSI_PLL_CLK_DIV_8,	/* Divider for clock used on the parallel GPIF interface. */
    0x00,		                /* Reserved */
    0x00,                       /* Reserved */
    0x00,                       /* Reserved */
    50                        /* Delay on the parallel output buffer of CSI interface. */
};

/* MIPI Configuration parameters to interface with OV5640_YUY2_Resolution3 :  (1280 x 720 @ 30.0 fps) */
CyU3PMipicsiCfg_t mipiConfig_OV5640_YUY2_Resolution3 =  
{
    CY_U3P_MIPIOUT_DW_16,       /* MIPI out parallel width packing */
    2,                          /* Number of CSI data lanes. */
    1,                          /* PLL clock input divider. */
    62,                         /* PLL clock feedback divider. */
    CY_U3P_CSI_PLL_FRS_500_1000M, /* PLL clock range. */  
    CY_U3P_CSI_PLL_CLK_DIV_8,     /* Divider for clock used to detect CSI LP<->HS transition. */
    CY_U3P_CSI_PLL_CLK_DIV_8,	/* Divider for clock used on the parallel GPIF interface. */
    0x00,		                /* Reserved */
    0x00,                       /* Reserved */
    0x00,                       /* Reserved */
    50                        /* Delay on the parallel output buffer of CSI interface. */
};

/* MIPI Configuration parameters to interface with OV5640_YUY2_Resolution4 :  (640 x 480 @ 30.0 fps) */
CyU3PMipicsiCfg_t mipiConfig_OV5640_YUY2_Resolution4 =  
{
    CY_U3P_MIPIOUT_DW_16,       /* MIPI out parallel width packing */
    1,                          /* Number of CSI data lanes. */
    1,                          /* PLL clock input divider. */
    90,                         /* PLL clock feedback divider. */
    CY_U3P_CSI_PLL_FRS_125_250M, /* PLL clock range. */   
    CY_U3P_CSI_PLL_CLK_DIV_2,     /* Divider for clock used to detect CSI LP<->HS transition. */
    CY_U3P_CSI_PLL_CLK_DIV_8,	/* Divider for clock used on the parallel GPIF interface. */
    0x00,		                /* Reserved */
    0x00,                       /* Reserved */
    0x00,                       /* Reserved */
    1                        /* Delay on the parallel output buffer of CSI interface. */
};

/* [ ] */

#ifdef STILL_CAPTURE_ENABLE

/*	Set the still image resolutions through this function. This function lists all the
 *  supported resolutions in SuperSpeed and HighSpeed. The frame index of resolutions
 *  supported in Still Capture can be different from the frame index of resolutions supported
 *  in Video streaming.
 */
void
CyCx3UvcAppImageSensorSetStillResolution(
		uint8_t format_index,
        uint8_t resolution_index        
        )
{
	CyU3PReturnStatus_t status = CY_U3P_SUCCESS;
	switch (CyU3PUsbGetSpeed ())
	{
	case CY_U3P_SUPER_SPEED:
		switch (format_index)
		{
		default:
			break;
		}
		break;
			
	case CY_U3P_HIGH_SPEED:
		switch (format_index)
		{
		default:
			break;
		}
		break;
	default:
	   	break;		
	}
}		

#endif

/*	Set the video resolution through this function. This function lists all the
 *  supported resolutions in SuperSpeed and HighSpeed. The frame index of resolutions
 *  supported in Still Capture can be different from the frame index of resolutions supported
 *  in Video streaming.
 */
void
CyCx3UvcAppImageSensorSetVideoResolution(
		uint8_t         formatIndex,
        uint8_t 		resolutionIndex
        )
{
	CyU3PReturnStatus_t status = CY_U3P_SUCCESS;
	switch (CyU3PUsbGetSpeed ())
	{
	case CY_U3P_SUPER_SPEED:
		switch (formatIndex)
		{
		case SS_YUY2_INDEX:
			switch(resolutionIndex)
			{
			case 0x01:
				/* Write Resolution1Settings */
				#ifndef FX3_STREAMING
				status = CyU3PMipicsiSetIntfParams (&mipiConfig_OV5640_YUY2_Resolution1, CyFalse);
				if (status != CY_U3P_SUCCESS)
				{
					CyU3PDebugPrint (4, "\n\rUSBStpCB:SetIntfParams SS1 Err = 0x%x", status);
				}
				
				/*Set MIPI PHY Time Delay (or THS_Settle) value for CX3's MIPI Decoder depending on THS-Prepare and THS-Zero parameters*/	
				
				/* CyU3PMipicsiSetPhyTimeDelay(1,9); */
				
				/* Set the GPIF bus width */ 
				CyCx3SwitchGpifBusWidth(16);
				#endif

				/*Set image sensor configuration for 2592 x 1944 @ 15.0 fps*/
#if USE_SENSOR_LIB
				CyCx3_ImageSensor_Set_5M();
#else
				CyCx3_Set_OV5640_YUY2_Resolution1();
#endif
				break; 
			case 0x02:
				/* Write Resolution2Settings */
				#ifndef FX3_STREAMING
				status = CyU3PMipicsiSetIntfParams (&mipiConfig_OV5640_YUY2_Resolution2, CyFalse);
				if (status != CY_U3P_SUCCESS)
				{
					CyU3PDebugPrint (4, "\n\rUSBStpCB:SetIntfParams SS1 Err = 0x%x", status);
				}
				
				/*Set MIPI PHY Time Delay (or THS_Settle) value for CX3's MIPI Decoder depending on THS-Prepare and THS-Zero parameters*/	
				
				/* CyU3PMipicsiSetPhyTimeDelay(1,8); */
				
				/* Set the GPIF bus width */ 
				CyCx3SwitchGpifBusWidth(16);
				#endif

				/*Set image sensor configuration for 1920 x 1080 @ 30.0 fps*/
#if USE_SENSOR_LIB
				CyCx3_ImageSensor_Set_1080p();
#else
				CyCx3_Set_OV5640_YUY2_Resolution2();
#endif
				break;
			case 0x03:
				/* Write Resolution3Settings */
				#ifndef FX3_STREAMING
				status = CyU3PMipicsiSetIntfParams (&mipiConfig_OV5640_YUY2_Resolution3, CyFalse);
				if (status != CY_U3P_SUCCESS)
				{
					CyU3PDebugPrint (4, "\n\rUSBStpCB:SetIntfParams SS1 Err = 0x%x", status);
				}
				
				/*Set MIPI PHY Time Delay (or THS_Settle) value for CX3's MIPI Decoder depending on THS-Prepare and THS-Zero parameters*/	
				
				/* CyU3PMipicsiSetPhyTimeDelay(1,8); */
				
				/* Set the GPIF bus width */ 
				CyCx3SwitchGpifBusWidth(16);
				#endif

				/*Set image sensor configuration for 1280 x 720 @ 30.0 fps*/
#if USE_SENSOR_LIB
				CyCx3_ImageSensor_Set_720p();
#else
				CyCx3_Set_OV5640_YUY2_Resolution3();
#endif
				break;

			case 0x04:
				/* Write Resolution4Settings */
				#ifndef FX3_STREAMING
				status = CyU3PMipicsiSetIntfParams (&mipiConfig_OV5640_YUY2_Resolution4, CyFalse);
				if (status != CY_U3P_SUCCESS)
				{
					CyU3PDebugPrint (4, "\n\rUSBStpCB:SetIntfParams SS1 Err = 0x%x", status);
				}
				
				/*Set MIPI PHY Time Delay (or THS_Settle) value for CX3's MIPI Decoder depending on THS-Prepare and THS-Zero parameters*/	
				
				/* CyU3PMipicsiSetPhyTimeDelay(1,13); */
				
				/* Set the GPIF bus width */ 
				CyCx3SwitchGpifBusWidth(16);
				#endif

				/*Set image sensor configuration for 640 x 480 @ 30.0 fps*/
#if USE_SENSOR_LIB
				CyCx3_ImageSensor_Set_Vga();
#else
				CyCx3_Set_OV5640_YUY2_Resolution4();
#endif
				break; 
			
			default:
				break;
			}
			break;
		
		default:
			break;
		}
		break;
			
	case CY_U3P_HIGH_SPEED:
		switch (formatIndex)
		{
		case HS_YUY2_INDEX:
			switch(resolutionIndex)
			{
			case 0x01:
				/* Write Resolution4Settings */
				#ifndef FX3_STREAMING
				status = CyU3PMipicsiSetIntfParams (&mipiConfig_OV5640_YUY2_Resolution4, CyFalse);
				if (status != CY_U3P_SUCCESS)
				{
					CyU3PDebugPrint (4, "\n\rUSBStpCB:SetIntfParams SS1 Err = 0x%x", status);
				}
				
				
				/* CyU3PMipicsiSetPhyTimeDelay(1,13); */
				
				/*Set the GPIF bus width*/ 
				CyCx3SwitchGpifBusWidth(16);
				#endif

				/*Set image sensor configuration for 640 x 480 @ 30.0 fps*/
#if USE_SENSOR_LIB
				CyCx3_ImageSensor_Set_Vga();
#else
				CyCx3_Set_OV5640_YUY2_Resolution4();
#endif
				break;
			default:
    			break;
			}
			break;
				
		default:
			break;
		}
		break;
	default:
		break;
	}
}

/*Returns the pointer to the Probe Control structure for the corresponding frame index.*/
uint8_t * 
CyCx3UvcAppGetProbeControlData (
        CyU3PUSBSpeed_t usbConType,
        uint8_t         formatIndex,
        uint8_t 		frameIndex
        )

{
	switch(usbConType) 
	{
	case CY_U3P_SUPER_SPEED:
		switch (formatIndex)
		{
		case SS_YUY2_INDEX:	
			switch(frameIndex)
			{	
			case 0x01:
				/* Send probe control structure corresponding to 2592 x 1944 @15.0 fps */
       			return ((uint8_t *) glYUY2_YUY2Resolution1ProbeCtrl);
			case 0x02:
				/* Send probe control structure corresponding to 1920 x 1080 @30.0 fps */
       			return ((uint8_t *) glYUY2_YUY2Resolution2ProbeCtrl);
			case 0x03:
				/* Send probe control structure corresponding to 1280 x 720 @30.0 fps */
       			return ((uint8_t *) glYUY2_YUY2Resolution3ProbeCtrl);
			case 0x04:
				/* Send probe control structure corresponding to 640 x 480 @30.0 fps */
       			return ((uint8_t *) glYUY2_YUY2Resolution4ProbeCtrl);	        				
       		default:
       			break;	
			}
			break;
		default:
			break;
        }
		break;
	case CY_U3P_HIGH_SPEED:
       	switch (formatIndex)
		{
		case HS_YUY2_INDEX:	
			switch(frameIndex)
			{    
			case 0x01:
				/*Send probe control structure corresponding to 640 x 480 @30.0 fps */
            	return ((uint8_t *) glYUY2_YUY2Resolution4ProbeCtrl_HS);	
   			}
			break;
       		
		default:
			break;
       	}
		break;
	default:
		break;
	}

    return NULL;
}

/*END OF FILE*/
