#include <reg52.h>
#include "I2C.h"

#define AT24C02_ADDRESS		0xA0

/**
  * @brief  AT24C02写入一字节数据
  * @param  WordAddress 要写入字节的地址
	* @param  Data 要写入的数据
  * @retval 无
  */
void AT24C02_WriteByte(unsigned char WordAddress,Data)
{
	I2C_Start();
	I2C_Write_Byte(AT24C02_ADDRESS);
	I2C_Wait_Ack();
	I2C_Write_Byte(WordAddress);
	I2C_Wait_Ack();
	I2C_Write_Byte(Data);
	I2C_Wait_Ack();
	I2C_Stop();
}

/**
  * @brief  AT24C02读取一字节数据
  * @param  WordAddress 要读取的字节的地址
  * @retval Data 读取的一字节数据
  */
unsigned char AT24C02_ReadByte(unsigned char WordAddress)
{
	unsigned char Data;
	I2C_Start();
	I2C_Write_Byte(AT24C02_ADDRESS);
	I2C_Wait_Ack();
	I2C_Write_Byte(WordAddress);
	I2C_Wait_Ack();
	I2C_Start();
	I2C_Write_Byte(AT24C02_ADDRESS|0x01);
	I2C_Wait_Ack();
	Data = I2C_Read_Byte();
	I2C_NoAck();
	I2C_Stop();
	return Data;
}