/*
 ## Cypress FX3 Core Library Header (cycx3_imagesensor.h)
 ## ===========================
 ##
 ##  Copyright Cypress Semiconductor Corporation, 2010-2014,
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
#ifndef _INCLUDED_CY_CX3_IMAGESENSOR_H_
#define _INCLUDED_CY_CX3_IMAGESENSOR_H_

#include <cyu3types.h>

					
	
/* Set OV5640 Sensor to generate video data of Format : YUY2, Resolution : Resolution1  2592 x 1944 */
extern CyU3PReturnStatus_t CyCx3_Set_OV5640_YUY2_Resolution1();
	
/* Set OV5640 Sensor to generate video data of Format : YUY2, Resolution : Resolution2  1920 x 1080 */
extern CyU3PReturnStatus_t CyCx3_Set_OV5640_YUY2_Resolution2();
	
/* Set OV5640 Sensor to generate video data of Format : YUY2, Resolution : Resolution3  1280 x 720 */
extern CyU3PReturnStatus_t CyCx3_Set_OV5640_YUY2_Resolution3();
	
/* Set OV5640 Sensor to generate video data of Format : YUY2, Resolution : Resolution4  640 x 480 */
extern CyU3PReturnStatus_t CyCx3_Set_OV5640_YUY2_Resolution4();

/* Initialize Image Sensor. */
extern CyU3PReturnStatus_t
CyCx3ImageSensorInit (
        void);

/* Put Image Sensor to Sleep/Low Power Mode. */
extern CyU3PReturnStatus_t
CyCx3ImageSensorSleep (
        void);

/* Wake Image Sensor from Sleep/Low Power Mode to Active Mode. */
extern CyU3PReturnStatus_t
CyCx3ImageSensorWakeup (
        void);


/* Trigger Autofocus for the Sensor. */
extern CyU3PReturnStatus_t
CyCx3ImageSensorTriggerAutofocus (
        void);


#endif /* _INCLUDED_CY_CX3_IMAGESENSOR_H_ */

/*[]*/