/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    usart.h
  * @brief   This file contains all the function prototypes for
  *          the usart.c file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USART_H__
#define __USART_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"
//#include "stm32f0xx_hal_uart.h"
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

extern UART_HandleTypeDef huart1;

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

void MX_USART1_UART_Init(void);

/* USER CODE BEGIN Prototypes */
void clear_uart_sta(void);
void UART_process(void);
unsigned char  frame_check(void);	
void Write_or_Readresponse(uint8_t tmp,unsigned char len,unsigned char *array_temp);
//void RS485_hongwai_Init(u32 bound);
void RS485_Init(u32 bound);
//void ////RS485_Send_Data(u8 *buf,u8 len);
void RS485_Receive_Data(u8 *buf);
u16 crc16(unsigned char *ptr,unsigned short len);   //CRCºÏ—È
extern unsigned char  data_array[70];
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __USART_H__ */

