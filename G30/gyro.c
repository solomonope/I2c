#include <p18f2525.h>
#include <i2c.h>
#include "myi2c.h"
#include "gyro.h"

unsigned char Gyro_Init(){
I2C_Init();

I2C_WriteByte( Gyro_Device_Write_Address, Gyro_Power_Register ,0x0A );

return 0;

}

unsigned char Gyro_GetLocation(Point * PresentPoint){

return 0;
}
