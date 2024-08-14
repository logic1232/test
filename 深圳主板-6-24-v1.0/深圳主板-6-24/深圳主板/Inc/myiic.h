#ifndef __myiic_H
#define __myiic_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"
 
//IO方向设置

 
//#define SDA_IN()  {GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=(u32)8<<28;}
//#define SDA_OUT() {GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=(u32)3<<28;}
///IO操作函数	

#define IIC_SCL_HIGH    HAL_GPIO_WritePin(AT24C512_I2C_SCL_GPIO_Port,AT24C512_I2C_SCL_Pin, GPIO_PIN_SET)
#define IIC_SCL_LOW     HAL_GPIO_WritePin(AT24C512_I2C_SCL_GPIO_Port,AT24C512_I2C_SCL_Pin, GPIO_PIN_RESET)
#define IIC_SDA_HIGH    HAL_GPIO_WritePin(AT24C512_I2C_SDA_GPIO_Port,AT24C512_I2C_SDA_Pin, GPIO_PIN_SET)
#define IIC_SDA_LOW     HAL_GPIO_WritePin(AT24C512_I2C_SDA_GPIO_Port,AT24C512_I2C_SDA_Pin, GPIO_PIN_RESET)
#define READ_SDA        HAL_GPIO_ReadPin(AT24C512_I2C_SDA_GPIO_Port,AT24C512_I2C_SDA_Pin)
#define EEPROM_WP_H     HAL_GPIO_WritePin(GPIOB,EEPROM_WP_Pin, GPIO_PIN_SET)
#define EEPROM_WP_L     HAL_GPIO_WritePin(GPIOB,EEPROM_WP_Pin, GPIO_PIN_RESET)



//IIC所有操作函数
void SDA_IN(void);
void SDA_OUT(void);
void IIC_Init(void);                //初始化IIC的IO口				 
void IIC_Start(void);				//发送IIC开始信号
void IIC_Stop(void);	  			//发送IIC停止信号
void IIC_Send_Byte(u8 txd);			//IIC发送一个字节
u8 IIC_Read_Byte(unsigned char ack);//IIC读取一个字节
u8 IIC_Wait_Ack(void); 				//IIC等待ACK信号
void IIC_Ack(void);					//IIC发送ACK信号
void IIC_NAck(void);				//IIC不发送ACK信号

void IIC_Write_One_Byte(u8 daddr,u8 addr,u8 data);
u8 IIC_Read_One_Byte(u8 daddr,u8 addr);	  

#ifdef __cplusplus
}
#endif
#endif /*__ pinoutConfig_H */

