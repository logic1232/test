#ifndef __lcd_H
#define __lcd_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"
//#include "sys.h"
#include <stdint.h>
#include "stm32f0xx_hal.h"
volatile extern unsigned int Func_Index;  
   
#define uchar unsigned char
#define uint unsigned int
#define ulong unsigned long
typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t u8;
//#define RS_HIGH    HAL_GPIO_WritePin(LCD_RS_GPIO_Port, LCD_RS_Pin, GPIO_PIN_SET)
//#define RS_LOW     HAL_GPIO_WritePin(LCD_RS_GPIO_Port, LCD_RS_Pin, GPIO_PIN_RESET)
//#define RESET_HIGH    HAL_GPIO_WritePin(LCD_RESET_GPIO_Port, LCD_RESET_Pin, GPIO_PIN_SET)
//#define RESET_LOW     HAL_GPIO_WritePin(LCD_RESET_GPIO_Port, LCD_RESET_Pin, GPIO_PIN_RESET)
//#define RD_HIGH    HAL_GPIO_WritePin(LCD_RD_GPIO_Port, LCD_RD_Pin, GPIO_PIN_SET)
//#define RD_LOW     HAL_GPIO_WritePin(LCD_RD_GPIO_Port, LCD_RD_Pin, GPIO_PIN_RESET)
//#define WR_HIGH    HAL_GPIO_WritePin(LCD_WR_GPIO_Port, LCD_WR_Pin, GPIO_PIN_SET)
//#define WR_LOW     HAL_GPIO_WritePin(LCD_WR_GPIO_Port, LCD_WR_Pin, GPIO_PIN_RESET)
	  
#define CS_LOW   HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_RESET)
#define CS_HIGH   HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_SET)
#define AO_LOW   HAL_GPIO_WritePin(GPIOB,GPIO_PIN_2,GPIO_PIN_RESET)
#define AO_HIGH   HAL_GPIO_WritePin(GPIOB,GPIO_PIN_2,GPIO_PIN_SET)
#define SCLK_LOW   HAL_GPIO_WritePin(GPIOB,GPIO_PIN_10,GPIO_PIN_RESET)
#define SCLK_HIGH   HAL_GPIO_WritePin(GPIOB,GPIO_PIN_10,GPIO_PIN_SET)
#define SDA_LOW   HAL_GPIO_WritePin(GPIOB,GPIO_PIN_11,GPIO_PIN_RESET)
#define SDA_HIGH   HAL_GPIO_WritePin(GPIOB,GPIO_PIN_11,GPIO_PIN_SET)
#define RESET_LOW   HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,GPIO_PIN_RESET)
#define RESET_HIGH   HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,GPIO_PIN_SET)




#define LEDA_OFF  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,RESET)
#define LEDA_ON    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,SET)

void transfer_command(u8 tmp);
void transfer_command1(void);
void transfer_data(unsigned char data1);
void display_graphic_32x32(uchar page,uchar column,uchar *dp);
void initial_lcd(void);
void lcd_address(u8 page,u8 column);
void clear_screen(void);

void clear_define_screen(unsigned char x0,unsigned char x1,unsigned char y0,u8 y1);
void disp_grap(char *dp) ;
void font1(void);
void font4(void);
unsigned char read_data_from_lcd(unsigned char page, unsigned char column);
void draw_point(unsigned char x, unsigned char y, unsigned char state);
void LCD_Fill(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2);
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

