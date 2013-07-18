/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
;                                                                     
;                     Software License Agreement                      
;                                                                     
; The software supplied herewith by Microchip Technology Incorporated 
; (the "Company") for its PICmicro® Microcontroller is intended and   
; supplied to you, the Company’s customer, for use solely and         
; exclusively on Microchip PICmicro Microcontroller products.         
;                                                                     
; The software is owned by the Company and/or its supplier, and is     
; protected under applicable copyright laws. All rights are reserved.  
; Any use in violation of the foregoing restrictions may subject the  
; user to criminal sanctions under applicable laws, as well as to     
; civil liability for the breach of the terms and conditions of this  
; license.                                                             
;                                                                      
; THIS SOFTWARE IS PROVIDED IN AN "AS IS" CONDITION. NO WARRANTIES,   
; WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED   
; TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A         
; PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,   
; IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR          
; CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.                    
;                                                                     
;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
;	Filename:			    AN991.c            
;	Date:				      September 28, 2006          
;	File Version:		  1.2                              
;	Assembled using:	MPLAB IDE 7.00.00.0               
;                                  
;	Author:				    Martin Kvasnicka              
;	Company:			    Microchip Technology, Inc.
;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#include <p18f452.h>
#include "AN991.h"
#include <i2c.h>

//config words
#pragma romdata CONFIG
rom const unsigned char CONFIG1L = 0xFF;	//Dummy byte
rom const unsigned char CONFIG1H = 0xF2;	//HS + 4x PLL mode, OSC switch enabled
rom const unsigned char CONFIG2L = 0xFC;	//BOR disabled, PWRTE enabled
rom const unsigned char CONFIG2H = 0x00;	//WDT disabled
rom const unsigned char CONFIG3L = 0xFF;	//Dummy byte
rom const unsigned char CONFIG3H = 0xFF;	//CCP is on RC1
rom const unsigned char CONFIG4L = 0xFB;	//Debug off, LVP off, stack reset
rom const unsigned char CONFIG4H = 0xFF;	//Dummy byte
rom const unsigned char CONFIG5L = 0xFF;	//Code protection off
rom const unsigned char CONFIG5H = 0xFF;	//EE unprotect, Boot unprotect
rom const unsigned char CONFIG6L = 0xFF;	//Write protection off
rom const unsigned char CONFIG6H = 0xFF;	//EE unprotect, Boot unprotect, Config unprotect
rom const unsigned char CONFIG7L = 0xFF;	//Reads unprotected
rom const unsigned char CONFIG7H = 0xFF;	//Boot read unprotected
#pragma romdata
//********************************************************************
// Global Variable declarations
//********************************************************************
unsigned char ControlByte;                //Control Byte
unsigned char HighAdd;                    //High Order Address Byte
unsigned char LowAdd;                     //Low Order Address Byte
unsigned char Data;                       //Data Byte
unsigned char Length;                     //Length of bytes to read
unsigned int  PageSize;                   //Page size in bytes
unsigned char PageString[64];             // Holds the device page data to/from EEPROM

void main(void)
{
  unsigned int n;
  ControlByte = 0xA0;                     //Control is always A0 for reads (& with 0x01 for writes)
  HighAdd = 0x5A;                         //HighAdd is first byte transmitted for High Density devices
  LowAdd = 0x00;                          //LowAdd is only Address byte for Low Density, second byte to HD
  Data = 0xAA;                            //Data can be whatever user would like
  Length = 0x01;                          //Length param set to 1 for single byte read
  PageSize = 0x10;                        //PageSize is Physical page boundry from Datasheet. (0x10 = 16, 0x20 = 32)
  for(n = 0; n < PageSize; n++)
  {
    PageString[n] = Data;
  }

  InitPIC();
  
  LDByteWriteI2C(ControlByte, LowAdd, Data );                                  //Low Density Byte Write
//  LDByteReadI2C(ControlByte, LowAdd, &Data, Length );                          //Low Density Byte Read
//  LDPageWriteI2C(ControlByte, LowAdd, PageString );                           //Low Density Page Write
//  LDSequentialReadI2C(ControlByte, LowAdd, PageString, PageSize );            //Low Density Page Read

//  HDByteWriteI2C(ControlByte, HighAdd, LowAdd, Data );                        //High Density Byte Write
//  HDByteReadI2C(ControlByte, HighAdd, LowAdd , &Data, Length) ;               //High Density Byte Read
//  HDPageWriteI2C(ControlByte, HighAdd, LowAdd, PageString );                  //High Density Page Write
//  HDSequentialReadI2C(ControlByte, HighAdd, LowAdd, PageString, PageSize );   //High Density Page Read  

  while(1){};                             // Loop here forever
}

void InitPIC(void)
{

  //here is the I2C setup from the Seeval32 code.
  DDRCbits.RC3 = 1; //Configure SCL
                    //as Input
	DDRCbits.RC4 = 1; //Configure SDA
                    //as Input
  SSPSTAT = 0x80;   //Disable SMBus &
                    //Slew Rate Control
  SSPCON1 = 0x28;   //Enable MSSP Master
  SSPADD = 0x18;    //Should be 0x18
                    //for 100kHz
  SSPCON2 = 0x00;   //Clear MSSP Conrol Bits
}
