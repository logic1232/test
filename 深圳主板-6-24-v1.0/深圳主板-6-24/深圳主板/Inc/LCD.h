#ifndef __lcd_H
#define __lcd_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"
//#include "sys.h"

volatile extern unsigned int Func_Index;  
   
#define uchar unsigned char
#define uint unsigned int
#define ulong unsigned long

//#define RS_HIGH    HAL_GPIO_WritePin(LCD_RS_GPIO_Port, LCD_RS_Pin, GPIO_PIN_SET)
//#define RS_LOW     HAL_GPIO_WritePin(LCD_RS_GPIO_Port, LCD_RS_Pin, GPIO_PIN_RESET)
//#define RESET_HIGH    HAL_GPIO_WritePin(LCD_RESET_GPIO_Port, LCD_RESET_Pin, GPIO_PIN_SET)
//#define RESET_LOW     HAL_GPIO_WritePin(LCD_RESET_GPIO_Port, LCD_RESET_Pin, GPIO_PIN_RESET)
//#define RD_HIGH    HAL_GPIO_WritePin(LCD_RD_GPIO_Port, LCD_RD_Pin, GPIO_PIN_SET)
//#define RD_LOW     HAL_GPIO_WritePin(LCD_RD_GPIO_Port, LCD_RD_Pin, GPIO_PIN_RESET)
//#define WR_HIGH    HAL_GPIO_WritePin(LCD_WR_GPIO_Port, LCD_WR_Pin, GPIO_PIN_SET)
//#define WR_LOW     HAL_GPIO_WritePin(LCD_WR_GPIO_Port, LCD_WR_Pin, GPIO_PIN_RESET)
	  
#define CS_HIGH    HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_SET)
#define CS_LOW     HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_RESET)

#define RESET_HIGH    HAL_GPIO_WritePin(LCD_RESET_GPIO_Port, LCD_RESET_Pin, GPIO_PIN_SET)
#define RESET_LOW     HAL_GPIO_WritePin(LCD_RESET_GPIO_Port, LCD_RESET_Pin, GPIO_PIN_RESET)

#define AO_HIGH    HAL_GPIO_WritePin(LCD_A0_GPIO_Port, LCD_AO_Pin, GPIO_PIN_SET)
#define AO_LOW     HAL_GPIO_WritePin(LCD_A0_GPIO_Port, LCD_AO_Pin, GPIO_PIN_RESET)

#define SCLK_HIGH    HAL_GPIO_WritePin(LCD_SCLK_GPIO_Port, LCD_SCLK_Pin, GPIO_PIN_SET)
#define SCLK_LOW     HAL_GPIO_WritePin(LCD_SCLK_GPIO_Port, LCD_SCLK_Pin, GPIO_PIN_RESET)

#define SDA_HIGH    HAL_GPIO_WritePin(LCD_SDA_GPIO_Port, LCD_SDA_Pin, GPIO_PIN_SET)
#define SDA_LOW     HAL_GPIO_WritePin(LCD_SDA_GPIO_Port, LCD_SDA_Pin, GPIO_PIN_RESET)



#define LEDA_OFF     HAL_GPIO_WritePin(LCD_BACKLIGHT_GPIO_Port, LCD_BACKLIGHT_Pin, GPIO_PIN_RESET);//SDA	
#define LEDA_ON     HAL_GPIO_WritePin(LCD_BACKLIGHT_GPIO_Port, LCD_BACKLIGHT_Pin, GPIO_PIN_SET);//SDA	

void transfer_command(u8 tmp);
void transfer_command1(void);
void transfer_data(unsigned char data1);

void initial_lcd(void);
void lcd_address(u8 page,u8 column);
void clear_screen(void);

void clear_define_screen(unsigned char x0,unsigned char x1,unsigned char y0,u8 y1);
void disp_grap(char *dp) ;
void font1(void);
void font4(void);

#ifdef __cplusplus
}
#endif
#endif /*__ pinoutConfig_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

