/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#define TRIP_LED_Pin GPIO_PIN_3
#define TRIP_LED_GPIO_Port GPIOC
#define LEAK_Pin GPIO_PIN_0
#define LEAK_GPIO_Port GPIOA
#define IA_ADC_Pin GPIO_PIN_1
#define IA_ADC_GPIO_Port GPIOA
#define IB_ADC_Pin GPIO_PIN_2
#define IB_ADC_GPIO_Port GPIOA
#define IC_ADC_Pin GPIO_PIN_3
#define IC_ADC_GPIO_Port GPIOA
#define VA_ADC_Pin GPIO_PIN_4
#define VA_ADC_GPIO_Port GPIOA
#define VB_ADC_Pin GPIO_PIN_5
#define VB_ADC_GPIO_Port GPIOA
#define VC_ADC_Pin GPIO_PIN_6
#define VC_ADC_GPIO_Port GPIOA
#define Vol_Check_ADC_Pin GPIO_PIN_7//14V控制板断电检查
#define Vol_Check_ADC_GPIO_Port GPIOA
#define CP_CHECK_Pin GPIO_PIN_4
#define CP_CHECK_GPIO_Port GPIOC
#define UP__BUTTON_Pin GPIO_PIN_5
#define UP__BUTTON_GPIO_Port GPIOC
#define CLOSE__BUTTON_Pin GPIO_PIN_0
#define CLOSE__BUTTON_GPIO_Port GPIOB
#define OPEN__BUTTON_Pin GPIO_PIN_1
#define OPEN__BUTTON_GPIO_Port GPIOB
#define SET__BUTTON_Pin GPIO_PIN_8//S5
#define SET__BUTTON_GPIO_Port GPIOA
#define CENTER__BUTTON_Pin GPIO_PIN_15//S6
#define CENTER__BUTTON_GPIO_Port GPIOB
#define DOWN__BUTTON_Pin GPIO_PIN_13//S8
#define DOWN__BUTTON_GPIO_Port GPIOB
#define BACK__BUTTON_Pin GPIO_PIN_14//S7
#define BACK__BUTTON_GPIO_Port GPIOB
//#define ATT7022_IRQ_Pin GPIO_PIN_13
//#define ATT7022_IRQ_GPIO_Port GPIOB
//#define ATT7022_RESET_Pin GPIO_PIN_14
//#define ATT7022_RESET_GPIO_Port GPIOB
//#define ATT7022_REVP_Pin GPIO_PIN_15
//#define ATT7022_REVP_GPIO_Port GPIOB
//#define SPI_DOUT_Pin GPIO_PIN_8
//#define SPI_DOUT_GPIO_Port GPIOA
#define SPI_DIN_Pin GPIO_PIN_9
#define SPI_DIN_GPIO_Port GPIOA
#define SPI_SCLK_Pin GPIO_PIN_6
#define SPI_SCLK_GPIO_Port GPIOC
#define SPI_CS_Pin GPIO_PIN_7
#define SPI_CS_GPIO_Port GPIOC
#define RS485_RX_Pin GPIO_PIN_8
#define RS485_RX_GPIO_Port GPIOD
#define RS485_TX_Pin GPIO_PIN_9
#define RS485_TX_GPIO_Port GPIOD
#define OUT_OPEN_Pin GPIO_PIN_11
#define OUT_OPEN_GPIO_Port GPIOA
#define OUT_CLOSE_Pin GPIO_PIN_12
#define OUT_CLOSE_GPIO_Port GPIOA
#define LCD_BACKLIGHT_Pin GPIO_PIN_15
#define LCD_BACKLIGHT_GPIO_Port GPIOA
#define MOTOR_Pin GPIO_PIN_8
#define MOTOR_GPIO_Port GPIOC
#define TRIP_Pin GPIO_PIN_9
#define TRIP_GPIO_Port GPIOC
#define LCD_D7_Pin GPIO_PIN_0
#define LCD_D7_GPIO_Port GPIOD
#define LCD_D6_Pin GPIO_PIN_1
#define LCD_D6_GPIO_Port GPIOD
#define LCD_D5_Pin GPIO_PIN_2
#define LCD_D5_GPIO_Port GPIOD
#define LCD_D4_Pin GPIO_PIN_3
#define LCD_D4_GPIO_Port GPIOD
#define LCD_D3_Pin GPIO_PIN_4
#define LCD_D3_GPIO_Port GPIOD
#define LCD_D2_Pin GPIO_PIN_5
#define LCD_D2_GPIO_Port GPIOD
#define LCD_D1_Pin GPIO_PIN_6
#define LCD_D1_GPIO_Port GPIOD
#define LCD_D0_Pin GPIO_PIN_3
#define LCD_D0_GPIO_Port GPIOB
#define LCD_RD_Pin GPIO_PIN_4
#define LCD_RD_GPIO_Port GPIOB
#define LCD_WR_Pin GPIO_PIN_5
#define LCD_WR_GPIO_Port GPIOB
#define LCD_RS_Pin GPIO_PIN_6
#define LCD_RS_GPIO_Port GPIOB
#define LCD_RESET_Pin GPIO_PIN_7
#define LCD_RESET_GPIO_Port GPIOB
#define AT24C512_I2C_SCL_Pin GPIO_PIN_8
#define AT24C512_I2C_SCL_GPIO_Port GPIOB
#define AT24C512_I2C_SDA_Pin GPIO_PIN_9
#define AT24C512_I2C_SDA_GPIO_Port GPIOB


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



#define RS485_TX_EN_Pin GPIO_PIN_10     //通讯使能
#define RS485_TX_EN_GPIO_Port GPIOA
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
