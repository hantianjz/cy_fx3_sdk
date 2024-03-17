/*
 ## Cypress FX3 Core Library Header (cycx3_videostreaming.h)
 ## ===========================
 ##
 ##  Copyright Cypress Semiconductor Corporation, 2010-2023,
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
 
/* CX3 Header file for APIs implementing Image Sensor specific functions
 */
#ifndef _INCLUDED_CY_CX3_VIDEOSTREAMING_H_
#define _INCLUDED_CY_CX3_VIDEOSTREAMING_H_

#include <cyu3types.h>
#include "cyu3usb.h"
#include "cycx3_uvc.h"




/** \brief MIPI-CSI Data Formats

    **Description**\n
    This enumerated type lists the MIPI CSI data formats supported by the MIPI-CSI block
    on the CX3. The MIPI-CSI block on the CX3 supports the listed data formats in 8, 16 and
    24 bit modes. Some data formats (RAW8, RGB888) support only a fixed data width,
    while some formats support more than one data widths with different padding mechanisms
    and byte orders on the received data.

    **Note**\n
    The user needs to set the Fixed Function GPIF interface on the CX3 to an
    appropriate width based on the Data Format being selected. Selection of an incorrect GPIF bus
    width can lead to loss of data or introduction of garbage data into the data stream.

    **\see
    *\see CyU3PMipicsiCfg_t
    *\see CyU3PMipicsiSetIntfParams
    *\see CyU3PMipicsiQueryIntfParams
*/
typedef enum CyU3PMipicsiParallelWidth_t
{
	CY_U3P_MIPIOUT_DW_8 = 0x00,          /**< RAW8 Data Type. CSI-2 Data Type 0x2A \n
                                             8 Bit Output = RAW[7:0]      */

	CY_U3P_MIPIOUT_DW_10 = 0x01,         /**< RAW10 Data Type. CSI-2 Data Type 0x2B  \n
                                             16 Bit Output = 6'b0,RAW[9:0]        */

	CY_U3P_MIPIOUT_DW_12 = 0x02,         /**< RAW12 Data Type. CSI-2 Data Type 0x2C \n
                                             16 Bit Output = 4'b0,RAW[11:0]       */

	CY_U3P_MIPIOUT_DW_14 = 0x08,         /**< RAW14 Data Type. CSI-2 Data Type 0x2D \n
                                             16 Bit Output = 2'b0,RAW[13:0]       */

    CY_U3P_MIPIOUT_DW_24 =0x03,         /**< RGB888 Data type. CSI-2 Data Type 0x24. \n
                                             24 Bit Output = R[7:0],G[7:0],B[7:0]*/

    CY_U3P_MIPIOUT_RGB666_0_DW_24 = 0x04,      /**< RGB666 Data type. CSI-2 Data Type 0x23. \n
                                             24 Bit Output = 2'b0,R[5:0],2'b0,G[5:0], 2'b0,B[5:0]*/

    CY_U3P_MIPIOUT_RGB666_1_DW_24 = 0x14,      /**< RGB666 Data type. CSI-2 Data Type 0x23. \n
                                             24 Bit Output = 6'b0,R[5:0],G[5:0], B[5:0]*/

    CY_U3P_MIPIOUT_RGB565_0_DW_24 = 0x05,      /**< RGB565 Data type. CSI-2 Data Type 0x22. \n
                                             24 Bit Output = 2'b0,R[4:0],3'b0,G[5:0], 2'b0,B[4:0],1'b0*/

    CY_U3P_MIPIOUT_RGB565_1_DW_24 = 0x15,      /**< RGB565 Data type. CSI-2 Data Type 0x22. \n
                                             24 Bit Output = 3'b0,R[4:0],2'b0,G[5:0], 3'b0,B[4:0]*/

    CY_U3P_MIPIOUT_RGB565_2_DW_16 = 0x25,      /**< RGB565 Data type. CSI-2 Data Type 0x22. \n
                                             24 Bit Output = 8'b0,R[4:0],G[5:0], B[4:0] \n
                                             16 Bit Output = R[4:0],G[5:0], B[4:0]*/

//    CY_U3P_CSI_DF_YUV422_8_0 = 0x06,    /**< YUV422 8-Bit Data type. CSI-2 Type 0x1E. \n
//                                             24 Bit Output = 16'b0,P[7:0] \n
//                                             16 Bit Output = 8'b0, P[7:0] \n
//                                             8 Bit Output = P[7:0]        \n
//                                             Data Order: U1,Y1,V1,Y2,U3,Y3,V3,Y4....  */

    CY_U3P_MIPIOUT_DW_16_SWAP = 0x16,    /**< YUV422 8-Bit Data type. CSI-2 Type 0x1E. \n
                                             24 Bit Output = 8'b0,P[15:0] \n
                                             16 Bit Output = P[15:0] \n
                                             Data Order: {U1,Y1},{V1,Y2},{U3,Y3},{V3,Y4}....  */

    CY_U3P_MIPIOUT_DW_16 = 0x26,    /**< YUV422 8-Bit Data type. CSI-2 Type 0x1E. \n
                                             24 Bit Output = 8'b0,P[15:0] \n
                                             16 Bit Output = P[15:0] \n
                                             Data Order: {Y1,U1},{Y2,V1},{Y3,U3},{Y4,V3}....  */

    CY_U3P_MIPIOUT_DW_YUV422_10 = 0x07      /**< YUV422 10-Bit Data type. CSI-2 Type 0x1F. \n
                                             24 Bit Output = 14'b0,P[9:0] \n
                                             16 Bit Output = 6'b0,P[9:0] \n
                                             Data Order: U1,Y1,V1,Y2,U3,Y3,V3,Y4....  */
} CyU3PMipicsiParallelWidth_t;



/* Video Format index used in Configuration descriptor */
typedef enum CyU3PUvcSSVideoFormat
{
    
	SS_YUY2_INDEX = 1,    /* YUY2 Format*/
}CyU3PUvcSSVideoFormat_t;

/* Video Format index used in Configuration descriptor */
typedef enum CyU3PUvcHSVideoFormat
{
    	
	HS_YUY2_INDEX = 1,    /* YUY2 Format*/	
}CyU3PUvcHSVideoFormat_t;
/*********************************************************************************************/
/***************** SS Configuration Descriptor Length Calculation ****************************/
/*********************************************************************************************/

#define SS_NO_OF_VIDEO_FORMATS_SUPPORTED		1   // To be generated

#define SS_YUY2_TOTAL_NO_OF_RES		4


#define COLOR_MATCHING_DESCRIPTOR_SIZE			0x06

#ifdef CX3_UVC_1_0_SUPPORT
#define SS_TOTAL_SIZE_VC_CLASS_DSCR				0x50
#else
#define SS_TOTAL_SIZE_VC_CLASS_DSCR				0x51
#endif

/* Total descriptor calculation
 * Total size of Class specific VS descr for camera interface =
 *                                 Class specific video streaming input header +
 *                                 Class specific uncompressed VS descr + total number of frame descriptor + Still Capture uncompressed +
 *                                 Class specific compressed VS descr + total number of frame descriptor +  Still Capture compressed +
 *                                 Color matching descriptor x 3(for each format)  */

#define SS_TOTAL_SIZE_VS_CLASS_DSCR        	(0x0D + SS_NO_OF_VIDEO_FORMATS_SUPPORTED + \
0x1B + (SS_YUY2_TOTAL_NO_OF_RES	* 0x1E) + 0x00 + \
											 COLOR_MATCHING_DESCRIPTOR_SIZE * SS_NO_OF_VIDEO_FORMATS_SUPPORTED\
                                             )


/* Low byte - Total size of Class specific VS descr for front camera*/
#define SS_TOTAL_SIZE_VS_CLASS_DSCR_L      CY_U3P_GET_LSB(SS_TOTAL_SIZE_VS_CLASS_DSCR)

/* High byte - Total size of Class specific VS descr for front camera*/
#define SS_TOTAL_SIZE_VS_CLASS_DSCR_H      CY_U3P_GET_MSB(SS_TOTAL_SIZE_VS_CLASS_DSCR)


#define SS_TOTAL_SIZE_CONFIG_DSCR		(0x09 + 0x08 + 0x09 + SS_TOTAL_SIZE_VC_CLASS_DSCR + 0x07 + 0x06 + 0x05+\
										 0x09 + SS_TOTAL_SIZE_VS_CLASS_DSCR +0x7 + 0x6)

/* Low byte - Total size of the device descriptor */
#define SS_TOTAL_SIZE_CONFIG_DSCR_L          CY_U3P_GET_LSB(SS_TOTAL_SIZE_CONFIG_DSCR)

/* High byte - Total size of the device descriptor */
#define SS_TOTAL_SIZE_CONFIG_DSCR_H          CY_U3P_GET_MSB(SS_TOTAL_SIZE_CONFIG_DSCR)


/*********************************************************************************************/
/***************** HS Configuration Descriptor Length Calculation ****************************/
/*********************************************************************************************/

#define HS_NO_OF_VIDEO_FORMATS_SUPPORTED		1 

#define HS_YUY2_TOTAL_NO_OF_RES		1

/* Total descriptor calculation
 * Total size of Class specific VS descr for camera interface =
 *                                 Class specific video streaming input header +
 *                                 Class specific uncompressed VS descr + total number of frame descriptor + Still Capture uncompressed +
 *                                 Class specific compressed VS descr + total number of frame descriptor +  Still Capture compressed +
 *                                 Color matching descriptor x number of formats supported  */
#define HS_TOTAL_SIZE_VS_CLASS_DSCR        	(0x0D + HS_NO_OF_VIDEO_FORMATS_SUPPORTED + \
											0x1B + (HS_YUY2_TOTAL_NO_OF_RES	* 0x1E) + 0x00 + \
											 COLOR_MATCHING_DESCRIPTOR_SIZE * HS_NO_OF_VIDEO_FORMATS_SUPPORTED\
                                             )


/* Low byte - Total size of Class specific VS descr for front camera*/
#define HS_TOTAL_SIZE_VS_CLASS_DSCR_L      CY_U3P_GET_LSB(HS_TOTAL_SIZE_VS_CLASS_DSCR)
/* High byte - Total size of Class specific VS descr for front camera*/
#define HS_TOTAL_SIZE_VS_CLASS_DSCR_H      CY_U3P_GET_MSB(HS_TOTAL_SIZE_VS_CLASS_DSCR)

/*This macro is generated only if the still image support is enabled in Image sensor configuration tab*/
#undef STILL_CAPTURE_ENABLE


#ifdef CX3_UVC_1_0_SUPPORT
#define HS_TOTAL_SIZE_VC_CLASS_DSCR				0x50
#else
#define HS_TOTAL_SIZE_VC_CLASS_DSCR				0x51
#endif

#define HS_TOTAL_SIZE_CONFIG_DSCR		(0x09 + 0x08 + 0x09 + HS_TOTAL_SIZE_VC_CLASS_DSCR + 0x07 + 0x05+\
		 	 	 	 	 	 	 	 	 0x09 + HS_TOTAL_SIZE_VS_CLASS_DSCR +0x7)

/* Low byte - Total size of the device descriptor */
#define HS_TOTAL_SIZE_CONFIG_DSCR_L          CY_U3P_GET_LSB(HS_TOTAL_SIZE_CONFIG_DSCR)

/* High byte - Total size of the device descriptor */
#define HS_TOTAL_SIZE_CONFIG_DSCR_H          CY_U3P_GET_MSB(HS_TOTAL_SIZE_CONFIG_DSCR)


#ifdef CX3_UVC_1_0_SUPPORT
#define CX3_UVC_MAX_PROBE_SETTING               (26)            /* UVC 1.0 Maximum number of bytes in Probe Control */
#define CX3_UVC_MAX_PROBE_SETTING_ALIGNED       (32)            /* Maximum number of bytes in Probe Control aligned to 32 byte */
#else
#define CX3_UVC_MAX_PROBE_SETTING               (34)            /* UVC 1.1 Maximum number of bytes in Probe Control */
#define CX3_UVC_MAX_PROBE_SETTING_ALIGNED       (64)            /* Maximum number of bytes in Probe Control aligned to 32 byte */
#endif

#ifdef STILL_CAPTURE_ENABLE
#define CX3_UVC_MAX_STILL_PROBE_SETTING 		(11)	           /* Maximum number of bytes in Still Probe Control */
#define CX3_UVC_HEADER_STI			            (uint8_t)(1 << 5)  /* Still Image Indication in the UVC Header*/
#define CX3_STILL_IMAGE_EVENT 	   	            (1 << 7)			/*Event used to Still Image Capture*/

uint8_t glStillProbeCtrl[CX3_UVC_MAX_STILL_PROBE_SETTING];
#endif

/* Extern definitions of the Video frame data based on the format assigned in UVC descriptors*/

/*********************************/
/* UVC Probe Control Setting - SS*/
/*********************************/
extern         uint8_t glProbeCtrl[CX3_UVC_MAX_PROBE_SETTING];                        /* Scratch buffer. */
extern const uint8_t glYUY2_YUY2Resolution1ProbeCtrl[CX3_UVC_MAX_PROBE_SETTING];        /* 2592 x 1944 @15.0 fps settings. */
extern const uint8_t glYUY2_YUY2Resolution2ProbeCtrl[CX3_UVC_MAX_PROBE_SETTING];        /* 1920 x 1080 @30.0 fps settings. */
extern const uint8_t glYUY2_YUY2Resolution3ProbeCtrl[CX3_UVC_MAX_PROBE_SETTING];        /* 1280 x 720 @30.0 fps settings. */
extern const uint8_t glYUY2_YUY2Resolution4ProbeCtrl[CX3_UVC_MAX_PROBE_SETTING];        /* 640 x 480 @30.0 fps settings. */

/*********************************/
/* UVC Probe Control Setting - HS*/
/*********************************/
extern const uint8_t glYUY2_YUY2Resolution4ProbeCtrl_HS[CX3_UVC_MAX_PROBE_SETTING];        /* 640 x 480 @30.0 fps settings. */

/*Extern definitions of MIPI configuration parameters corresponding to each format and resolution*/

/*********************************/
/* MIPI Configuration parameters */
/*********************************/

extern CyU3PMipicsiCfg_t OV5640_YUY2_Resolution1;
extern CyU3PMipicsiCfg_t OV5640_YUY2_Resolution2;
extern CyU3PMipicsiCfg_t OV5640_YUY2_Resolution3;
extern CyU3PMipicsiCfg_t OV5640_YUY2_Resolution4;


/*Function that returns the pointer to the Probe Control structure for the corresponding frame index.*/
uint8_t * CyCx3UvcAppGetProbeControlData ( CyU3PUSBSpeed_t usbConType, uint8_t formatIndex, uint8_t frameIndex);

/*Function to set the mipi configuration parameters and image sensor configuration for a still capture resolution*/
void CyCx3UvcAppImageSensorSetStillResolution(uint8_t formatIndex, uint8_t resolution_index);

/*Function to set the mipi configuration parameters and image sensor configuration for a streaming resolution*/
void CyCx3UvcAppImageSensorSetVideoResolution(uint8_t formatIndex, uint8_t resolution_index);

/* Function to switch the GPIf Bus Width*/
extern CyU3PReturnStatus_t CyCx3SwitchGpifBusWidth(uint8_t busWidthrequired); /*busWidthrequired = 16 or 24*/
/* Initialize Image Sensor*/
extern CyU3PReturnStatus_t CyCx3_ImageSensor_Init();

/* Set Sensor to output Resolution0 Stream */
extern CyU3PReturnStatus_t CyCx3_ImageSensor_Set_Resolution0 ();

/* Put Image Sensor to Sleep/Low Power Mode */
extern CyU3PReturnStatus_t CyCx3_ImageSensor_Sleep();

/* Wake Image Sensor from Sleep/Low Power Mode to Active Mode */
extern CyU3PReturnStatus_t CyCx3_ImageSensor_Wakeup();

/* Trigger Autofocus for the Sensor*/
extern CyU3PReturnStatus_t CyCx3_ImageSensor_Trigger_Autofocus();

#endif /* _INCLUDED_CYCX3_UVC_H_ */

