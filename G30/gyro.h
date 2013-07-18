#ifndef _GYRO_H
#define  _GYRO_H

/* Register Macros  */



/*Config Macros   */

#define Gyro_Device_Write_Address  0xAA

#define  Gyro_Device_Read_Address   0xAA

#define  Gyro_Power_Register       0xAA

typedef struct Gyro_Point {
unsigned int X;
unsigned int Y;
unsigned int Z;
}Point;

unsigned char Gyro_Init();

unsigned char Gyro_GetLocation(Point * PresentPoint);
#endif 