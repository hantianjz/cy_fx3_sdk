                        CYPRESS SEMICONDUCTOR CORPORATION
                                    FX3 SDK

Command line for downloading Firmware
---------------------------------------

  This utility is a console application for downloading of the firmware images to 
  SYSMEM, I2C EEPROM and SPI Flash.
  
  The application assumes the following 
  1. FX3 device need to be in reset state i.e. boot loader should be running 
  2. Board setting must be set for the corresponding media to be programmed. 
  3. Size of EEPROM and Flash should be greater than or equal to the size of the image.
  
  Usage:
  ------
    The utility is a console application that needs to be invoked with the
    following options.

    cyfwprog.exe -fw <firmware image filename> [-dest <programming location>] [-v] [-h]
	
    where
    <programming location> Firmware programming location[SYSTEM | I2C_EEPROM | SPI_FLASH]
    <firmware image filename> is the input firmware image file name with path. 
	Tool expect the image in *.img file format. Refer elf2img for conversion

    -v is used for verbose logs during the conversion process
    -h is used to print this help information    

[]

