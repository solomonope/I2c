#include <p18f2525.h>
#include <i2c.h>
#include "myi2c.h"

unsigned char  I2C_Init(){

OpenI2C(MASTER, SLEW_OFF); // Activate I2C as master, 100 kHz max
SSPADD = 39; // set the I2C baud rate to 50k
return 0;
}

unsigned char I2C_WriteByte( unsigned char Device, unsigned char Register, unsigned char Data ){
  IdleI2C();                          // ensure module is idle
  StartI2C();                         // initiate START condition
  while ( SSPCON2bits.SEN );          // wait until start condition is over 
  WriteI2C( Device );            	  // write 1 byte - R/W bit should be 0
  IdleI2C();                          // ensure module is idle
  WriteI2C( Register );                 // write address byte to EEPROM
  IdleI2C();                          // ensure module is idle
  WriteI2C ( Data );                  // Write data byte to EEPROM
  IdleI2C();                          // ensure module is idle
  StopI2C();                          // send STOP condition
  while ( SSPCON2bits.PEN );          // wait until stop condition is over 
  while (EEAckPolling(Device));  //Wait for write cycle to complete
  return ( 0 );                       // return with no error
}


unsigned char I2C_ReadByte( unsigned char Device, unsigned char Register, unsigned char *Data, unsigned char Length ){

  IdleI2C();                      // ensure module is idle
  StartI2C();                     // initiate START condition
  while ( SSPCON2bits.SEN );      // wait until start condition is over 
  WriteI2C( Device );        // write 1 byte 
  IdleI2C();                      // ensure module is idle
  WriteI2C( Register );            // WRITE word address to EEPROM
  IdleI2C();                      // ensure module is idle
  RestartI2C();                   // generate I2C bus restart condition
  while ( SSPCON2bits.RSEN );     // wait until re-start condition is over 
  WriteI2C( Device | 0x01 ); // WRITE 1 byte - R/W bit should be 1 for read
  IdleI2C();                      // ensure module is idle
  getsI2C( Data, Length );       // read in multiple bytes
  NotAckI2C();                    // send not ACK condition
  while ( SSPCON2bits.ACKEN );    // wait until ACK sequence is over 
  StopI2C();                      // send STOP condition
  while ( SSPCON2bits.PEN );      // wait until stop condition is over 
  return ( 0 );    

}