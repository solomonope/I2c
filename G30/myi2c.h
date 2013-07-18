#ifndef  _My_I2C


#define _My_I2C

unsigned char I2C_Init();
unsigned char I2C_WriteByte( unsigned char Device, unsigned char Register, unsigned char Data );
unsigned char I2C_ReadByte( unsigned char Device, unsigned char Register, unsigned char *Data, unsigned char Length );

#endif 