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
#include "usart.h"
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

static const char big_msg[] = "a191f8d6ea9cadff3ff58a915d6f0318f6caf45e1762fa381\
61c7266ad4ab1b5ddd530a72f3ef17c592805e3ea60aa69ae103a079fa6a9e471d06d5b441bf0f2b\
62f40fd7c6c58e5548e18e0690376b317a143d3795a479c4c2f680a792be26eaa9c7745c52d8ded6\
b3c7a9f0335c7a9e1039b176a15c1805f09fcefcbd94890b985f7ecdbe33b11d564c38cfa35a9f9a\
65cbb1bbc1d1a85a60a035ceb5d7d1c409854692ea30796615d516ee9a9f7c7418b8809d01ae9763\
e992b57884335143e2b65de13e77013479b12d7e150135f7500f86891e31df4e351a5fd60c5a1229\
bae58fa81a82421c54dceaf9cd77297bc76edc6ca4df462e6c26b02b18e4341f96e8cd68df581306\
62c4836c5f6c150ca7c42a539558e080d6efdaf015710d347eb5e14b69c07052f388d398f9bfe02c\
e01075b180d86ac9a5ad47a67f353c40849b88fc842d72508b1eadec6fb40fe184d6af61822d9a4f\
53224c9d99f1b5978b0f502273d0811a0f0468d6ad4c8423cf14218d0b5f3edef6fb48d2b1e86456\
6a728d03d0615a6b86327e6d86ca695c168f932aaf4d925d915a42229a717ca9a372e3e2b45947dd\
402fe7a74a8dda1a7843096f9ea8224cfc0c833238b083abc172379ca508ae8bf759e87e3a487dc3\
61c7266ad4ab1b5ddd530a72f3ef17c592805e3ea60aa69ae103a079fa6a9e471d06d5b441bf0f2b\
62f40fd7c6c58e5548e18e0690376b317a143d3795a479c4c2f680a792be26eaa9c7745c52d8ded6\
b3c7a9f0335c7a9e1039b176a15c1805f09fcefcbd94890b985f7ecdbe33b11d564c38cfa35a9f9a\
65cbb1bbc1d1a85a60a035ceb5d7d1c409854692ea30796615d516ee9a9f7c7418b8809d01ae9763\
bae58fa81a82421c54dceaf9cd77297bc76edc6ca4df462e6c26b02b18e4341f96e8cd68df581306\
62f40fd7c6c58e5548e18e0690376b317a143d3795a479c4c2f680a792be26eaa9c7745c52d8ded6\
b3c7a9f0335c7a9e1039b176a15c1805f09fcefcbd94890b985f7ecdbe33b11d564c38cfa35a9f9a\
65cbb1bbc1d1a85a60a035ceb5d7d1c409854692ea30796615d516ee9a9f7c7418b8809d01ae9763\
e992b57884335143e2b65de13e77013479b12d7e150135f7500f86891e31df4e351a5fd60c5a1229\
bae58fa81a82421c54dceaf9cd77297bc76edc6ca4df462e6c26b02b18e4341f96e8cd68df581306\
62c4836c5f6c150ca7c42a539558e080d6efdaf015710d347eb5e14b69c07052f388d398f9bfe02c\
e01075b180d86ac9a5ad47a67f353c40849b88fc842d72508b1eadec6fb40fe184d6af61822d9a4f\
53224c9d99f1b5978b0f502273d0811a0f0468d6ad4c8423cf14218d0b5f3edef6fb48d2b1e86456\
6a728d03d0615a6b86327e6d86ca695c168f932aaf4d925d915a42229a717ca9a372e3e2b45947dd\
402fe7a74a8dda1a7843096f9ea8224cfc0c833238b083abc172379ca508ae8bf759e87e3a487dc3\
e992b57884335143e2b65de13e77013479b12d7e150135f7500f86891e31df4e351a5fd60c5a1229\
bae58fa81a82421c54dceaf9cd77297bc76edc6ca4df462e6c26b02b18e4341f96e8cd68df581306\
62c4836c5f6c150ca7c42a539558e080d6efdaf015710d347eb5e14b69c07052f388d398f9bfe02c\
e01075b180d86ac9a5ad47a67f353c40849b88fc842d72508b1eadec6fb40fe184d6af61822d9a4f\
53224c9d99f1b5978b0f502273d0811a0f0468d6ad4c8423cf14218d0b5f3edef6fb48d2b1e86456\
6a728d03d0615a6b86327e6d86ca695c168f932aaf4d925d915a42229a717ca9a372e3e2b45947dd\
402fe7a74a8dda1a7843096f9ea8224cfc0c833238b083abc172379ca508ae8bf759e87e3a487dc3\
61c7266ad4ab1b5ddd530a72f3ef17c592805e3ea60aa69ae103a079fa6a9e471d06d5b441bf0f2b\
62f40fd7c6c58e5548e18e0690376b317a143d3795a479c4c2f680a792be26eaa9c7745c52d8ded6\
b3c7a9f0335c7a9e1039b176a15c1805f09fcefcbd94890b985f7ecdbe33b11d564c38cfa35a9f9a\
65cbb1bbc1d1a85a60a035ceb5d7d1c409854692ea30796615d516ee9a9f7c7418b8809d01ae9763\
e992b57884335143e2b65de13e77013479b12d7e150135f7500f86891e31df4e351a5fd60c5a1229\
65cbb1bbc1d1a85a60a035ceb5d7d1c409854692ea30796615d516ee9a9f7c7418b8809d01ae9763\
e992b57884335143e2b65de13e77013479b12d7e150135f7500f86891e31df4e351a5fd60c5a1229\
bae58fa81a82421c54dceaf9cd77297bc76edc6ca4df462e6c26b02b18e4341f96e8cd68df581306\
62c4836c5f6c150ca7c42a539558e080d6efdaf015710d347eb5e14b69c07052f388d398f9bfe02c\
e01075b180d86ac9a5ad47a67f353c40849b88fc842d72508b1eadec6fb40fe184d6af61822d9a4f\
bae58fa81a82421c54dceaf9cd77297bc76edc6ca4df462e6c26b02b18e4341f96e8cd68df581306\
62c4836c5f6c150ca7c42a539558e080d6efdaf015710d347eb5e14b69c07052f388d398f9bfe02c\
e01075b180d86ac9a5ad47a67f353c40849b88fc842d72508b1eadec6fb40fe184d6af61822d9a4f\
53224c9d99f1b5978b0f502273d0811a0f0468d6ad4c8423cf14218d0b5f3edef6fb48d2b1e86456\
6a728d03d0615a6b86327e6d86ca695c168f932aaf4d925d915a42229a717ca9a372e3e2b45947dd\
402fe7a74a8dda1a7843096f9ea8224cfc0c833238b083abc172379ca508ae8bf759e87e3a487dc3\
a915a66fd4e2da9484811bb0c8dcc644bd9acd8a8081d90240aa700a97240033dd0d4f2gz37h6dr4\
rf5r54dceaf9cd77297bc76ed24cfc08fc842d7c83v6gh";

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

    button_event_t btn_state;

    /* Infinite loop */
    for (;;) {
        /* Read the btn event */
        btn_state = get_button_state();

        if (btn_state == BTN_CLICK) {
            user_click_event();
        }

        if (btn_state == BTN_DOUBLE_CLICK) {
            /* Send the big frame over UART */
            uart2_print(big_msg, sizeof(big_msg));
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

    while (1) {
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
        osDelay(100);
    }
}

/* USER CODE END Application */
