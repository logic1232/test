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
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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
#define CP_CHECK_Pin GPIO_PIN_1
#define CP_CHECK_GPIO_Port GPIOD
#define VA_ADC_Pin GPIO_PIN_0
#define VA_ADC_GPIO_Port GPIOC
#define VB_ADC_Pin GPIO_PIN_1
#define VB_ADC_GPIO_Port GPIOC
#define VC_ADC_Pin GPIO_PIN_2
#define VC_ADC_GPIO_Port GPIOC
#define TRIP_Pin GPIO_PIN_5
#define TRIP_GPIO_Port GPIOA
#define Vol_Check_ADC_Pin GPIO_PIN_6
#define Vol_Check_ADC_GPIO_Port GPIOA
#define IC_ADC_Pin GPIO_PIN_4
#define IC_ADC_GPIO_Port GPIOC
#define LEAK_Pin GPIO_PIN_5
#define LEAK_GPIO_Port GPIOC
#define IB_ADC_Pin GPIO_PIN_0
#define IB_ADC_GPIO_Port GPIOB
#define IA_ADC_Pin GPIO_PIN_1
#define IA_ADC_GPIO_Port GPIOB
#define Leak_Test_Pin GPIO_PIN_2
#define Leak_Test_GPIO_Port GPIOB
#define PLC_TX_Pin GPIO_PIN_10
#define PLC_TX_GPIO_Port GPIOB
#define PLC_RX_Pin GPIO_PIN_11
#define PLC_RX_GPIO_Port GPIOB
#define LED_Pin GPIO_PIN_12
#define LED_GPIO_Port GPIOB
#define MOTOR_Pin GPIO_PIN_7
#define MOTOR_GPIO_Port GPIOC
#define OUT_OPEN_Pin GPIO_PIN_8
#define OUT_OPEN_GPIO_Port GPIOC
#define OUT_CLOSE_Pin GPIO_PIN_9
#define OUT_CLOSE_GPIO_Port GPIOC
#define LCD_TX_Pin GPIO_PIN_9
#define LCD_TX_GPIO_Port GPIOA
#define LCD_RX_Pin GPIO_PIN_10
#define LCD_RX_GPIO_Port GPIOA
#define RS485_TX_Pin GPIO_PIN_10
#define RS485_TX_GPIO_Port GPIOC
#define RS485_RX_Pin GPIO_PIN_11
#define RS485_RX_GPIO_Port GPIOC
#define SPI_RESET_Pin GPIO_PIN_2
#define SPI_RESET_GPIO_Port GPIOD
#define SPI_MISO_Pin GPIO_PIN_3
#define SPI_MISO_GPIO_Port GPIOB
#define SPI_MOSI_Pin GPIO_PIN_4
#define SPI_MOSI_GPIO_Port GPIOB
#define SPI_SCK_Pin GPIO_PIN_5
#define SPI_SCK_GPIO_Port GPIOB
#define AT24C512_I2C_SCL_Pin GPIO_PIN_6
#define AT24C512_I2C_SCL_GPIO_Port GPIOB
#define AT24C512_I2C_SDA_Pin GPIO_PIN_7
#define AT24C512_I2C_SDA_GPIO_Port GPIOB
#define EEPROM_WP_Pin GPIO_PIN_8
#define EEPROM_WP_GPIO_Port GPIOB
#define SPI_NSS_Pin GPIO_PIN_9
#define SPI_NSS_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */
#define Leak_Test_HIGH HAL_GPIO_WritePin(Leak_Test_GPIO_Port,Leak_Test_Pin,GPIO_PIN_SET)
#define Leak_Test_LOW HAL_GPIO_WritePin(Leak_Test_GPIO_Port,Leak_Test_Pin,GPIO_PIN_RESET)

extern	int P1,P2;
extern	float Unbal_Vol,Unbal_Cur;
extern	int P1_Reactive,P2_Reactive;
extern	int P1_Apparent,P2_Apparent;
extern int E_Reactive[16];
extern int E_Apparent[16];
extern unsigned char quadrant; //四象限指示
extern float Charge_sum;


/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
