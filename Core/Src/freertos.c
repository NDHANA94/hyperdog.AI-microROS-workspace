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
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

#include "uros_tasks.h"
#include "error_indicator.h"
#include "can.h"
#include "minicheetah_motor.h"




/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
typedef StaticTask_t osStaticThreadDef_t;
/* USER CODE BEGIN PTD */
HAL_StatusTypeDef can_status;
// Motor_TypeDef motor[NUM_OF_MOTORS];
// uint16_t motor_error_code;
// uint8_t motor_status;
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
osThreadId_t defaultTaskHandle;
uint32_t defaultTaskBuffer[ 3000 ];
osStaticThreadDef_t defaultTaskControlBlock;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .cb_mem = &defaultTaskControlBlock,
  .cb_size = sizeof(defaultTaskControlBlock),
  .stack_mem = &defaultTaskBuffer[0],
  .stack_size = sizeof(defaultTaskBuffer),
  .priority = (osPriority_t) osPriorityHigh2,
};


/* Definitions for errorIndicatorTask */
osThreadId_t errorIndicatorTaskHandle;
const osThreadAttr_t errorIndicatorTask_attributes = {
  .name = "errorIndicatorTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};


/* Definitions for CAN */
osThreadId_t CANTaskHandle;
const osThreadAttr_t CANTask_attributes = {
  .name = "canTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityHigh1,
};

/* Private function prototypes -----------------------------------------------*/

/* USER CODE BEGIN FunctionPrototypes */
void StartErrorIndicatorTask(void *argument);
void StartCANTask(void* argument);
/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);


void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
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

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);
  errorIndicatorTaskHandle = osThreadNew(StartErrorIndicatorTask, NULL, &errorIndicatorTask_attributes);
  CANTaskHandle = osThreadNew(StartCANTask, NULL, &CANTask_attributes);
  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}


/* USER CODE END Header_StartDefaultTask */
/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN 5 */

  // micro-ROS configuration

  init_uros_node();  
  spin_uros_node(2);
  
  /* USER CODE END 5 */
}

void StartErrorIndicatorTask(void *argument)
{
  /* USER CODE BEGIN 5 */

  // micro-ROS configuration

  error_indicator();
  
  /* USER CODE END 5 */
}

void StartCANTask(void* argument)
{

  MOTOR_initId(FR_HIP, 1);
  MOTOR_initParams(FR_HIP, 12.5, 60, 500, 5, 18, 40);
  MOTOR_initCtrlLimits(FR_HIP, 1.2, -1.0, 3.0, 15);
  MOTOR_initCANConfig(FR_HIP, &hcan1, 0);
  

  // can_rx_init();
  // can_tx_init();
  
  while(1){
      // send_can_test();
      MOTOR_sendHeatbeat(FR_HIP);
      osDelay(10);
      MOTOR_setZero(FR_HIP);
  }
  

}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */


