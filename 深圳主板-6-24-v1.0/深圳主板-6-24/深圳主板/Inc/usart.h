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

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

extern UART_HandleTypeDef huart4;

extern UART_HandleTypeDef huart1;

extern UART_HandleTypeDef huart3;

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

void MX_UART4_Init(void);
void MX_USART1_UART_Init(void);
void MX_USART3_UART_Init(void);

/* USER CODE BEGIN Prototypes */

void clear_uart_sta(void);
void UART_process(void);

unsigned char  frame_check(void);	


//void RS485_hongwai_Init(u32 bound);
void RS485_Init(u32 bound);
//void ////RS485_Send_Data(u8 *buf,u8 len);
void RS485_Receive_Data(u8 *buf);
extern volatile unsigned char T_value[13];

extern uint8_t Receive_Temp;        //接收数据
extern uint8_t Receive_Flag;      //接收标志 1：正在接收数据
extern uint8_t Receive_index ;   //接收数据位置索引
extern uint8_t send_array_temp[12];    //用于存放发送的BCD数据 
extern uint8_t Receive_CRC;         //接收校验位
extern uint8_t ID_array[4];  //用于存放数据识别码
extern uint8_t LCD_Receive[100];  //接收数据数组
extern uint8_t LCD_Receive_last[400]; //保存数据数组
extern uint8_t Send[400];  //发送数据数组
extern unsigned char  data_array[70];
extern unsigned char  Lcd_data_array[400];
/************************工作状态字***************************/
extern uint8_t Work_State;

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __USART_H__ */

