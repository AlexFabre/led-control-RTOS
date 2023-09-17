/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.h
 * @brief          : Header for main.c file.
 *                   This file contains the common defines of the application.
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 STMicroelectronics.
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

/*****************************************************************************/
/* Those pragma enable below listed warning for all files that include main.h
 * This way we make sure the SOUPs are not concerned by the severity of those flags */

/* Warnings to enable */
#pragma GCC diagnostic warning "-Wextra"
#pragma GCC diagnostic warning "-Wmissing-include-dirs"
#pragma GCC diagnostic warning "-Wswitch-default"
#pragma GCC diagnostic warning "-Wswitch-enum"
#pragma GCC diagnostic warning "-Wconversion"
#pragma GCC diagnostic warning "-Wsign-conversion"
#pragma GCC diagnostic warning "-Wwrite-strings"
#pragma GCC diagnostic warning "-Wduplicated-cond"
#pragma GCC diagnostic warning "-Wduplicated-branches"
#pragma GCC diagnostic warning "-Wlogical-op"
#pragma GCC diagnostic warning "-Wnull-dereference"
#pragma GCC diagnostic warning "-Wjump-misses-init"
#pragma GCC diagnostic warning "-Wshadow"
#pragma GCC diagnostic warning "-Wformat=2"
#pragma GCC diagnostic warning "-Wfloat-equal"

/* Warnings to ignore */
// #pragma GCC diagnostic ignored "-Wunused-parameter"
/*****************************************************************************/

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
#define BTN_Pin            GPIO_PIN_13
#define BTN_GPIO_Port      GPIOC
#define BTN_EXTI_IRQn      EXTI4_15_IRQn
#define USART_TX_Pin       GPIO_PIN_2
#define USART_TX_GPIO_Port GPIOA
#define USART_RX_Pin       GPIO_PIN_3
#define USART_RX_GPIO_Port GPIOA
#define LED_Pin            GPIO_PIN_5
#define LED_GPIO_Port      GPIOA
#define SWDIO_Pin          GPIO_PIN_13
#define SWDIO_GPIO_Port    GPIOA
#define SWCLK_Pin          GPIO_PIN_14
#define SWCLK_GPIO_Port    GPIOA

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
