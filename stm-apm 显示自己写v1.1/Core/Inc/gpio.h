/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.h
  * @brief   This file contains all the function prototypes for
  *          the gpio.c file
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
#ifndef __GPIO_H__
#define __GPIO_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* USER CODE BEGIN Private defines */
#define KEY_UP       HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_13)   
#define KEY_DOWN          HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_9) 
#define KEY_LEFT         HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8)
#define KEY_RIGHT         HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_14) 
#define KEY_AFFIRM        HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_15)
#define KEY_GOBACK        HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_11)
#define KEY_LEAKCUR         HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_12)
#define KEY_OPEN    HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_10)
#define KEY_OPEN_hardware    HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_0)
#define KEY_CLOSE_hardware    HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_1)

//#define KEY_OPEN       HAL_GPIO_ReadPin(WKUP_GPIO_PORT, WKUP_GPIO_PIN)     
#define KEY_UP_PRES    1              /* KEY0按下 */     //上
#define KEY_DOWN_PRES    2              /* KEY1按下 */   //下  
#define KEY_GOBACK_PRES    3              /* KEY_UP按下(即WK_UP) */   //返回//合闸
#define KEY_OPEN_PRES    4                    //分闸
#define KEY_AFFIRM_PRES    5              /* KEY1按下 */      //确定
#define KEY_LEFT_PRES    6              /* KEY_UP按下(即WK_UP) */   // 左
#define KEY_RIGHRT_PRES    7              /* KEY0按下 *////右
#define KEY_LEAK_PRES    8              /* KEY1按下 */
#define KEY_OPEN_hardware_PRES   9              /* KEY_UP按下(即WK_UP) */
#define KEY_CLOSE_hardware_PRES  10

/* USER CODE END Private defines */

void MX_GPIO_Init(void);

/* USER CODE BEGIN Prototypes */
int scanKeys(void);
uint8_t key_scan(uint8_t mode);
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ GPIO_H__ */

