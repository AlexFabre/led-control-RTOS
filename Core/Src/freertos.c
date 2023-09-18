/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * File Name          : freertos.c
 * Description        : Code for freertos applications
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

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "cmsis_os.h"
#include "main.h"
#include "task.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "button.h"
#include "gpio.h"
#include "rtc.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
typedef StaticTask_t  osStaticThreadDef_t;
typedef StaticQueue_t osStaticMessageQDef_t;
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t         defaultTaskHandle;
uint32_t             defaultTaskBuffer[128];
osStaticThreadDef_t  defaultTaskControlBlock;
const osThreadAttr_t defaultTask_attributes = {
    .name       = "defaultTask",
    .cb_mem     = &defaultTaskControlBlock,
    .cb_size    = sizeof(defaultTaskControlBlock),
    .stack_mem  = &defaultTaskBuffer[0],
    .stack_size = sizeof(defaultTaskBuffer),
    .priority   = (osPriority_t)osPriorityNormal,
};
/* Definitions for ledTask */
osThreadId_t         ledTaskHandle;
uint32_t             ledTaskBuffer[128];
osStaticThreadDef_t  ledTaskControlBlock;
const osThreadAttr_t ledTask_attributes = {
    .name       = "ledTask",
    .cb_mem     = &ledTaskControlBlock,
    .cb_size    = sizeof(ledTaskControlBlock),
    .stack_mem  = &ledTaskBuffer[0],
    .stack_size = sizeof(ledTaskBuffer),
    .priority   = (osPriority_t)osPriorityNormal,
};
/* Definitions for uartTask */
osThreadId_t         uartTaskHandle;
uint32_t             uartTaskBuffer[128];
osStaticThreadDef_t  uartTaskControlBlock;
const osThreadAttr_t uartTask_attributes = {
    .name       = "uartTask",
    .cb_mem     = &uartTaskControlBlock,
    .cb_size    = sizeof(uartTaskControlBlock),
    .stack_mem  = &uartTaskBuffer[0],
    .stack_size = sizeof(uartTaskBuffer),
    .priority   = (osPriority_t)osPriorityNormal,
};
/* Definitions for uartQueue */
osMessageQueueId_t         uartQueueHandle;
uint8_t                    uartQueueBuffer[10 * sizeof(char *)];
osStaticMessageQDef_t      uartQueueControlBlock;
const osMessageQueueAttr_t uartQueue_attributes = {
    .name    = "uartQueue",
    .cb_mem  = &uartQueueControlBlock,
    .cb_size = sizeof(uartQueueControlBlock),
    .mq_mem  = &uartQueueBuffer,
    .mq_size = sizeof(uartQueueBuffer)
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void        StartDefaultTask(void *argument);
extern void led_task(void *argument);
extern void uart_task(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
 * @brief  FreeRTOS initialization
 * @param  None
 * @retval None
 */
void MX_FREERTOS_Init(void)
{
    /* USER CODE BEGIN Init */

    /* USER CODE END Init */

    /* USER CODE BEGIN RTOS_MUTEX */
    /* add mutexes, ... */
    /* USER CODE END RTOS_MUTEX */

    /* USER CODE BEGIN RTOS_SEMAPHORES */
    /* add semaphores, ... */
    /* USER CODE END RTOS_SEMAPHORES */

    /* USER CODE BEGIN RTOS_TIMERS */
    /* start timers, add new ones, ... */
    /* USER CODE END RTOS_TIMERS */

    /* Create the queue(s) */
    /* creation of uartQueue */
    uartQueueHandle = osMessageQueueNew(10, sizeof(char *), &uartQueue_attributes);

    /* USER CODE BEGIN RTOS_QUEUES */
    /* add queues, ... */
    /* USER CODE END RTOS_QUEUES */

    /* Create the thread(s) */
    /* creation of defaultTask */
    defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

    /* creation of ledTask */
    ledTaskHandle = osThreadNew(led_task, NULL, &ledTask_attributes);

    /* creation of uartTask */
    uartTaskHandle = osThreadNew(uart_task, NULL, &uartTask_attributes);

    /* USER CODE BEGIN RTOS_THREADS */
    /* add threads, ... */
    /* USER CODE END RTOS_THREADS */

    /* USER CODE BEGIN RTOS_EVENTS */
    /* add events, ... */
    /* USER CODE END RTOS_EVENTS */
}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
 * @brief  Function implementing the defaultTask thread.
 * @param  argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
    /* USER CODE BEGIN StartDefaultTask */
    (void)argument;

    /* Infinite loop */
    for (;;) {
        if (get_button_state() == BTN_CLICK) {
            user_click_event();
        }
        osDelay(1);
    }
    /* USER CODE END StartDefaultTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* Possible states of the device */
typedef enum {
    APP_SHUTDOWN,
    APP_RUNNING,
    APP_STANDBY
} app_state_t;

/* Current state of the device */
static app_state_t _app_state = APP_SHUTDOWN;

/* Process device state change consecutive to button press */
void user_click_event(void)
{
    infoPrintln("User click");

    switch (_app_state) {
    case APP_SHUTDOWN:
        _app_state = APP_RUNNING;
        enter_sequence_running();
        break;
    case APP_RUNNING:
    case APP_STANDBY:
        _app_state = APP_SHUTDOWN;
        stop_sequence();
        break;
    default:
        break;
    }
}

/* Process device state change consecutive to RTC IRQ */
void RTC_wakeup_IRQ(void)
{
    stop_RTC_periodic_wkup();

    switch (_app_state) {
    case APP_RUNNING:
        _app_state = APP_STANDBY;
        enter_sequence_stanby();
        break;
    case APP_STANDBY:
        _app_state = APP_RUNNING;
        enter_sequence_running();
        break;
    case APP_SHUTDOWN:
        /* Should never happen */
        stop_sequence();
        break;
    default:
        break;
    }
}

/* The device starts running for 20s */
void enter_sequence_running(void)
{
    /* TODO: Currently the led toggles every 300ms. (300ms ON - 300ms OFF)
     * We would rather prefer the led to make a short blink every 3s (150ms ON - 2.850s OFF)
     *
     * Send on UART2 the message "Enter running !" */

    infoPrintln("Enter running !");

    start_RTC_periodic_wkup(20);
}

/* The device enters standby for 40s */
void enter_sequence_stanby(void)
{
    /* TODO: Currently the led toggles every 600ms. (600ms ON - 600ms OFF)
     * We would rather prefer the led to make a short blink every 10s (150ms ON - 9.850s OFF)
     *
     * Send on UART2 the message "Enter standby !" */

    infoPrintln("Enter standby !");

    start_RTC_periodic_wkup(40);
}

/* The device cycle stops */
void stop_sequence(void)
{
    /* TODO: We would like a 4 blink scheme as soon as the cycle stops, to inform the user
     * that the app effectively stopped running: (150ms ON - 150ms OFF) x4
     *
     * Send on UART2 the message "Enter shutdown !" */

    infoPrintln("Enter shutdown !");

    stop_RTC_periodic_wkup();
}

void led_task(void *argument)
{
    (void)argument;

    static app_state_t _prev_app_state;

    _prev_app_state = _app_state;

    while (1) {

        if (_prev_app_state == _app_state) {
            osDelay(10);
            continue;
        }

        switch (_app_state) {
        case APP_RUNNING:
            set_LED(1);
            osDelay(300);
            set_LED(0);
            osDelay(300);
            break;
        case APP_STANDBY:
            set_LED(1);
            osDelay(600);
            set_LED(0);
            osDelay(600);
            break;
        case APP_SHUTDOWN:
            set_LED(0);
            break;
        default:
            errorPrintln("unknown app state %d", _app_state);
            break;
        }
        osDelay(10);
    }
}

void uart_task(void *argument)
{
    (void)argument;

    while (1) {
        osDelay(500);
    }
}

/* USER CODE END Application */
