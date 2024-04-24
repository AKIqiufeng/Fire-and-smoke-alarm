
#ifndef __I2C_H__
#define __I2C_H__

#include <reg52.h>
#include <intrins.h>

#ifndef uint
#define uint unsigned int
#endif
#ifndef uchar
#define uchar unsigned char
#endif

/******************************************/
sbit I2C_SCL = P2^1; //I2C时钟线p02
sbit I2C_SDA = P2^0; //I2C数据线p01
/******************************************/

void Delay_5us();
void I2C_Start();
void I2C_Stop();
uint I2C_Wait_Ack();
void I2C_Ack();
void I2C_NoAck();
void I2C_Write_Byte(uchar WData);
uchar I2C_Read_Byte();

#endif
