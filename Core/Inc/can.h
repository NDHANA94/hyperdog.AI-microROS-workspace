/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    can.h
  * @brief   This file contains all the function prototypes for
  *          the can.c file
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
#ifndef __CAN_H__
#define __CAN_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

extern CAN_HandleTypeDef hcan1;

/* USER CODE BEGIN Private defines */
extern HAL_StatusTypeDef HAL_status;
/* USER CODE END Private defines */

void MX_CAN1_Init(void);

/* USER CODE BEGIN Prototypes */


typedef struct{
  uint8_t data[8];
  CAN_TxHeaderTypeDef header;
  uint32_t TxMailBox;
}CANTxMessage;

typedef struct{
  uint8_t data[7];
  CAN_RxHeaderTypeDef header;
  CAN_FilterTypeDef filter;
}CANRxMessage;


extern CANRxMessage can_rxMsg;
extern CANTxMessage can_txMsg;
HAL_StatusTypeDef can_rx_init();
void can_tx_init();
void send_can_test();
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __CAN_H__ */

