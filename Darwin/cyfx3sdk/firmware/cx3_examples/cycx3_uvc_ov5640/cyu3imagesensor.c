/*
## Cypress Image Sensor Routines for XXXX sensor (cyu3imagesensor.c)
## ===========================
##
##  Copyright Cypress Semiconductor Corporation, 2013,
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

#include <cyu3error.h>
#include <cyu3i2c.h>
#include "cyu3imagesensor.h"
#include <cyu3utils.h>
#include "cycx3_imagesensor.h"

/*Uncomment below line to enable UART debug messages during Sensor configuration*/
/*#define SENSOR_DEBUG*/

/* Misc Macros; Fill the correct I2C addresses below */
#define SENSOR_I2C_READ_ADDRESS         (0x79) 
#define SENSOR_I2C_WRITE_ADDRESS        (0x78)

/* Register Addresses */


/* Structure to store the Address/Value pair for each
 * register to be updated.
 */
 
typedef struct CySensorReg8
{
    uint16_t regAddr;
    uint8_t regValue;
} CySensorReg8_t;

typedef struct CySensorReg16
{
    uint16_t regAddr;
    uint16_t regValue;
} CySensorReg16_t;

typedef struct CySensorReg32
{
    uint16_t regAddr;
    uint32_t regValue;
} CySensorReg32_t;

/* Configuration Settings for Sensor Initialization.
 * These values are specific to the image sensor being used.
 */
CySensorReg8_t SENSOR_BaseConfigurationSettings [] =
{
	/* These are dummy Configuration Settings for Sensor. Replace with actual settings*/
	/*
    	{0xF000, 0x01},
    	{0xF008, 0x02},
    	{0xF008, 0x02},
    	{0xF103, 0x03},
	*/

};

					
/* Image sensor Configuration settings for Format : YUY2 Resolution : Resolution1  2592 x 1944 video stream  */
CySensorReg8_t OV5640_YUY2_Resolution1ConfigurationSettings [] =
{
	/* These are dummy Configuration Settings for Sensor. Replace with actual settings*/    
	/*
    	{0xF000, 0x01},
    	{0xF008, 0x02},
    	{0xF008, 0x02},
    	{0xF103, 0x03},
	*/
};
/* Image sensor Configuration settings for Format : YUY2 Resolution : Resolution2  1920 x 1080 video stream  */
CySensorReg8_t OV5640_YUY2_Resolution2ConfigurationSettings [] =
{
	/* These are dummy Configuration Settings for Sensor. Replace with actual settings*/    
	/*
    	{0xF000, 0x01},
    	{0xF008, 0x02},
    	{0xF008, 0x02},
    	{0xF103, 0x03},
	*/
};
/* Image sensor Configuration settings for Format : YUY2 Resolution : Resolution3  1280 x 720 video stream  */
CySensorReg8_t OV5640_YUY2_Resolution3ConfigurationSettings [] =
{
	/* These are dummy Configuration Settings for Sensor. Replace with actual settings*/    
	/*
    	{0xF000, 0x01},
    	{0xF008, 0x02},
    	{0xF008, 0x02},
    	{0xF103, 0x03},
	*/
};
/* Image sensor Configuration settings for Format : YUY2 Resolution : Resolution4  640 x 480 video stream  */
CySensorReg8_t OV5640_YUY2_Resolution4ConfigurationSettings [] =
{
	/* These are dummy Configuration Settings for Sensor. Replace with actual settings*/    
	/*
    	{0xF000, 0x01},
    	{0xF008, 0x02},
    	{0xF008, 0x02},
    	{0xF103, 0x03},
	*/
};

/*
 * Function to read one or more 8-bit registers from the Image Sensor.
 */
CyU3PReturnStatus_t 
I2C_SensorRead(
		uint16_t regAddr, 
		uint8_t count, 
		uint8_t *buf)
{
    CyU3PReturnStatus_t status = CY_U3P_SUCCESS;
    CyU3PI2cPreamble_t preamble;
    uint8_t cnt=0;

    for(cnt=0; cnt<3 ; cnt++)
    {
        preamble.buffer[1] = CY_U3P_GET_MSB (regAddr);
        preamble.buffer[2] = CY_U3P_GET_LSB (regAddr);
        preamble.buffer[3] = SENSOR_I2C_READ_ADDRESS; /* Slave address: Read operation */
        preamble.buffer[0] = SENSOR_I2C_WRITE_ADDRESS; /* Slave address: write operation */
        preamble.length = 4;
        preamble.ctrlMask = 0x0004;

        status = CyU3PI2cReceiveBytes (&preamble, buf, count,0);
        CyU3PThreadSleep(1);
        if (status == CY_U3P_SUCCESS)
        {
            break;
        }
#ifdef SENSOR_DEBUG
        else
            CyU3PDebugPrint(4,"\r\nImageSensorSensorRead Failed addr=0x%x",regAddr);
#endif
    }
    return status;
}
/*
 * Function to write one or more 8-bit registers on the Image Sensor.
 */
CyU3PReturnStatus_t
I2C_SensorWrite(
		uint16_t regAddr,
		uint16_t count, 
		uint8_t *buf)
{
    CyU3PReturnStatus_t status = CY_U3P_SUCCESS;
    CyU3PI2cPreamble_t preamble;
    uint8_t cnt=0;

    for(cnt=0; cnt<3 ; cnt++)
    {
        preamble.buffer[1] = CY_U3P_GET_MSB (regAddr);
        preamble.buffer[2] = CY_U3P_GET_LSB (regAddr);
        preamble.buffer[0] = SENSOR_I2C_WRITE_ADDRESS; /* Slave address: write operation */
        preamble.length = 3;
        preamble.ctrlMask = 0x0000;

        status = CyU3PI2cTransmitBytes (&preamble, buf, count,0);
        CyU3PThreadSleep(1);
        if (status == CY_U3P_SUCCESS)
        {
            break;
        }
#ifdef SENSOR_DEBUG
        else
            CyU3PDebugPrint(4,"\r\nImageSensorSensorWrite Failed addr=0x%x",regAddr);
#endif
    }
    return status;
}

/*
 *Function to clear or set the field bits in a 8-bit register based on the fieldValue parameter.
 */
CyU3PReturnStatus_t 
SensorWriteRegisterField (
		uint16_t RegAddr, 
		uint8_t Field,
		CyBool_t FieldValue)
{
    uint8_t WRBuff;
    uint8_t RDBuff;
    uint8_t CamRegVal;

	CyU3PReturnStatus_t status = CY_U3P_SUCCESS;

    status = I2C_SensorRead(RegAddr, 1, &RDBuff);
    CamRegVal = RDBuff;

    CamRegVal = ((CamRegVal & (~(Field)))| FieldValue);

    WRBuff= CamRegVal;
#ifdef SENSOR_DEBUG
    CyU3PDebugPrint(4,"\r\n0x%x = 0x%x\r\n",RegAddr,WRBuff);
#endif

    status = I2C_SensorWrite(RegAddr, 1, &WRBuff);
    
    return status;
}

/*
 * Function to initialize all 8-bit sensor registers associated with a specific configuration.
 */
CyU3PReturnStatus_t
Sensor_WriteConfigurationSettings_Reg8 (
        CySensorReg8_t *configSettings,
        uint16_t        configSettingsSize)
{
    CyU3PReturnStatus_t status = CY_U3P_SUCCESS;
    uint16_t regCounter = 0;
    uint8_t  rwBuffer[2];

#ifdef SENSOR_DEBUG
    CyU3PDebugPrint (4, "\r\nWriting Configuration Settings:");
#endif

    for (regCounter = 0; ((regCounter < configSettingsSize) && (status == CY_U3P_SUCCESS)); regCounter++)
    {
#ifdef SENSOR_DEBUG
        CyU3PDebugPrint (4, "\r\nRegister = 0x%x: Value = 0x%x",
                configSettings[regCounter].regAddr,
                configSettings[regCounter].regValue);
#endif

        rwBuffer[0] = configSettings[regCounter].regValue;
        status = I2C_SensorWrite (configSettings[regCounter].regAddr, 1, rwBuffer);
    }

    return status;
}

/*
 * Function to initialize all 16-bit sensor registers associated with a specific configuration.
 */
CyU3PReturnStatus_t
Sensor_WriteConfigurationSettings_Reg16 (
        CySensorReg16_t *configSettings,
        uint16_t         configSettingsSize)
{
    CyU3PReturnStatus_t status = CY_U3P_SUCCESS;
    uint16_t regCounter = 0;
    uint8_t  rwBuffer[2];

#ifdef SENSOR_DEBUG
    CyU3PDebugPrint (4, "\r\nWriting Configuration Settings:");
#endif

    for (regCounter = 0; ((regCounter < configSettingsSize) && (status == CY_U3P_SUCCESS)); regCounter++)
    {
#ifdef SENSOR_DEBUG
        CyU3PDebugPrint (4, "\r\nRegister = 0x%x: Value = 0x%x",
                configSettings[regCounter].regAddr,
                configSettings[regCounter].regValue);
#endif

        rwBuffer[0] = CY_U3P_GET_MSB (configSettings[regCounter].regValue);
        rwBuffer[1] = CY_U3P_GET_LSB (configSettings[regCounter].regValue);
        status = I2C_SensorWrite (configSettings[regCounter].regAddr, 2, rwBuffer);
    }

    return status;
}

/*
 * Function to initialize all 32-bit sensor registers associated with a specific configuration.
 */
CyU3PReturnStatus_t
Sensor_WriteConfigurationSettings_Reg32 (
        CySensorReg32_t *configSettings,
        uint16_t         configSettingsSize)
{
    CyU3PReturnStatus_t status = CY_U3P_SUCCESS;
    uint16_t regCounter = 0;
    uint8_t  rwBuffer[4];

#ifdef SENSOR_DEBUG
    CyU3PDebugPrint (4, "\r\nWriting Configuration Settings:");
#endif

    for (regCounter = 0; ((regCounter < configSettingsSize) && (status == CY_U3P_SUCCESS)); regCounter++)
    {
#ifdef SENSOR_DEBUG
        CyU3PDebugPrint (4, "\r\nRegister = 0x%x: Value = 0x%x",
                configSettings[regCounter].regAddr,
                configSettings[regCounter].regValue);
#endif

        rwBuffer[0] = CY_U3P_DWORD_GET_BYTE3 (configSettings[regCounter].regValue);
        rwBuffer[1] = CY_U3P_DWORD_GET_BYTE2 (configSettings[regCounter].regValue);
        rwBuffer[2] = CY_U3P_DWORD_GET_BYTE1 (configSettings[regCounter].regValue);
        rwBuffer[3] = CY_U3P_DWORD_GET_BYTE0 (configSettings[regCounter].regValue);
        status = I2C_SensorWrite (configSettings[regCounter].regAddr, 4, rwBuffer);
    }

    return status;
}

					
	
/* 
 *Configure the image Sensor to generate YUY2 Format video stream with Resolution : Resolution1 2592 x 1944
 */
CyU3PReturnStatus_t 
CyCx3_Set_OV5640_YUY2_Resolution1(
		void)
{
    uint16_t configSize;
    CyU3PReturnStatus_t status = CY_U3P_SUCCESS;

    configSize = (sizeof(OV5640_YUY2_Resolution1ConfigurationSettings))/(sizeof(CySensorReg8_t));
    status =  Sensor_WriteConfigurationSettings_Reg8(OV5640_YUY2_Resolution1ConfigurationSettings, configSize);
    
    return status;
}

	
/* 
 *Configure the image Sensor to generate YUY2 Format video stream with Resolution : Resolution2 1920 x 1080
 */
CyU3PReturnStatus_t 
CyCx3_Set_OV5640_YUY2_Resolution2(
		void)
{
    uint16_t configSize;
    CyU3PReturnStatus_t status = CY_U3P_SUCCESS;

    configSize = (sizeof(OV5640_YUY2_Resolution2ConfigurationSettings))/(sizeof(CySensorReg8_t));
    status =  Sensor_WriteConfigurationSettings_Reg8(OV5640_YUY2_Resolution2ConfigurationSettings, configSize);
    
    return status;
}

	
/* 
 *Configure the image Sensor to generate YUY2 Format video stream with Resolution : Resolution3 1280 x 720
 */
CyU3PReturnStatus_t 
CyCx3_Set_OV5640_YUY2_Resolution3(
		void)
{
    uint16_t configSize;
    CyU3PReturnStatus_t status = CY_U3P_SUCCESS;

    configSize = (sizeof(OV5640_YUY2_Resolution3ConfigurationSettings))/(sizeof(CySensorReg8_t));
    status =  Sensor_WriteConfigurationSettings_Reg8(OV5640_YUY2_Resolution3ConfigurationSettings, configSize);
    
    return status;
}

	
/* 
 *Configure the image Sensor to generate YUY2 Format video stream with Resolution : Resolution4 640 x 480
 */
CyU3PReturnStatus_t 
CyCx3_Set_OV5640_YUY2_Resolution4(
		void)
{
    uint16_t configSize;
    CyU3PReturnStatus_t status = CY_U3P_SUCCESS;

    configSize = (sizeof(OV5640_YUY2_Resolution4ConfigurationSettings))/(sizeof(CySensorReg8_t));
    status =  Sensor_WriteConfigurationSettings_Reg8(OV5640_YUY2_Resolution4ConfigurationSettings, configSize);
    
    return status;
}



/*
 * Function to initialize the image sensor. This is called at start-up.
 */
CyU3PReturnStatus_t 
CyCx3ImageSensorInit(
		void)
{
	uint16_t configSize;

#ifdef SENSOR_DEBUG
    CyU3PDebugPrint(4,"\r\n Sensor Initialization");
#endif

    CyU3PReturnStatus_t status = CY_U3P_SUCCESS;

	configSize = (sizeof(SENSOR_BaseConfigurationSettings))/(sizeof(CySensorReg8_t));
    status = Sensor_WriteConfigurationSettings_Reg8(SENSOR_BaseConfigurationSettings, configSize);
	
	/*Include any other I2C write required during Sensor Init here*/

    return status;
}

/*
 * Function to put Image Sensor to Sleep for power saving.
 */
CyU3PReturnStatus_t 
CyCx3ImageSensorSleep(
		void)
{
    CyU3PReturnStatus_t status = CY_U3P_SUCCESS;

    return status;
}

/*
 * Function to wakeup Image Sensor from sleep.
 */
CyU3PReturnStatus_t 
CyCx3ImageSensorWakeup(
		void)
{
    CyU3PReturnStatus_t status = CY_U3P_SUCCESS;
    return status;
}

/*
 * Function to trigger auto-focus setting on the image sensor.
 */
CyU3PReturnStatus_t 
CyCx3ImageSensorTriggerAutofocus (
		void)
{
    CyU3PReturnStatus_t status = CY_U3P_SUCCESS;
    return status;
}


/* End of file */
