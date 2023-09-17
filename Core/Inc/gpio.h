/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file    gpio.h
 * @brief   This file contains all the function prototypes for
 *          the gpio.c file
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
#ifndef __GPIO_H__
#define __GPIO_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */
#include <stdbool.h>

/* USER CODE END Includes */

/* USER CODE BEGIN Private defines */

/* Toggle Green LED */
#define toggle_LED() (HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin))

/* Set LED on (1) or off (0) */
#define set_LED(state) HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, (state == true) ? GPIO_PIN_SET : GPIO_PIN_RESET);

/* Read Green LED state
 * 1: LED is ON
 * 0: LED is OFF */
#define is_LED_ON() ((bool)HAL_GPIO_ReadPin(LED_GPIO_Port, LED_Pin))

/* USER CODE END Private defines */

void MX_GPIO_Init(void);

/* USER CODE BEGIN Prototypes */

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ GPIO_H__ */
