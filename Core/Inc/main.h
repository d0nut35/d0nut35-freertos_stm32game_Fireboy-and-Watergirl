/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#include "stm32f4xx_hal.h"

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
#define R_S1_Pin GPIO_PIN_4
#define R_S1_GPIO_Port GPIOA
#define R_S1_EXTI_IRQn EXTI4_IRQn
#define R_S2_Pin GPIO_PIN_5
#define R_S2_GPIO_Port GPIOA
#define R_KEY_Pin GPIO_PIN_6
#define R_KEY_GPIO_Port GPIOA
#define MPU6050_IINT_Pin GPIO_PIN_15
#define MPU6050_IINT_GPIO_Port GPIOE
#define MPU6050_IINT_EXTI_IRQn EXTI15_10_IRQn
#define LCD_CS_Pin GPIO_PIN_13
#define LCD_CS_GPIO_Port GPIOB
#define LCD_LED_Pin GPIO_PIN_14
#define LCD_LED_GPIO_Port GPIOB
#define D_KEY_Pin GPIO_PIN_14
#define D_KEY_GPIO_Port GPIOD
#define C_KEY_Pin GPIO_PIN_15
#define C_KEY_GPIO_Port GPIOD
#define FLASH_CS_Pin GPIO_PIN_9
#define FLASH_CS_GPIO_Port GPIOC
#define LCD_RST_Pin GPIO_PIN_15
#define LCD_RST_GPIO_Port GPIOA
#define key_enter_Pin GPIO_PIN_1
#define key_enter_GPIO_Port GPIOD
#define A_KEY_Pin GPIO_PIN_4
#define A_KEY_GPIO_Port GPIOD
#define B_KEY_Pin GPIO_PIN_5
#define B_KEY_GPIO_Port GPIOD
#define LCD_DC_Pin GPIO_PIN_4
#define LCD_DC_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
