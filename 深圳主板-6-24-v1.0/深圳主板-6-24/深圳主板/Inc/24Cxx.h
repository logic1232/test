#ifndef __24Cxx_H
#define __24Cxx_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"
 

#define AT24C01		127
#define AT24C02		255
#define AT24C04		511
#define AT24C08		1023
#define AT24C16		2047
#define AT24C32		4095
#define AT24C64	    8191
#define AT24C128	16383
#define AT24C256	32767  
//Mini STM32开发板使用的是24c02，所以定义EE_TYPE为AT24C02
#define EE_TYPE AT24C256
	 
u8 AT24CXX_ReadOneByte(u16 ReadAddr,u8 ChooseAddr);							//指定地址读取一个字节
u8 AT24CXX_ReadLongByte(u16 ReadAddr, u8 length, u8 *ps,u8 ChooseAddr);
void AT24CXX_WriteOneByte(u16 WriteAddr,u8 DataToWrite,u8 ChooseAddr);		//指定地址写入一个字节
void AT24CXX_WriteLenByte(u16 WriteAddr,u32 DataToWrite,u8 Len);//指定地址开始写入指定长度的数据
u32 AT24CXX_ReadLenByte(u16 ReadAddr,u8 Len);					//指定地址开始读取指定长度数据
void AT24CXX_Write(u16 WriteAddr,u8 *pBuffer,u16 NumToWrite);	//从指定地址开始写入指定长度的数据
void AT24CXX_Read(u16 ReadAddr,u8 *pBuffer,u16 NumToRead);   	//从指定地址开始读出指定长度的数据
void MODIFY_EEP_W(unsigned int WriteAddr,unsigned char *a,unsigned char Len,unsigned char SelectAddr);
void EEPROM_R(unsigned int WriteAddr,unsigned char *a,unsigned char Len,unsigned char SelectAddr);
void EEPROM_C(unsigned int AT24C64_address,unsigned int count,unsigned char SelectAddr);
	
u8 AT24CXX_Check(void);  //检查器件
void AT24CXX_Init(void); //初始化IIC

#ifdef __cplusplus
}
#endif
#endif /*__ pinoutConfig_H */
