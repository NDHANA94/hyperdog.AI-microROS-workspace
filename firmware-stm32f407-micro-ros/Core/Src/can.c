/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    can.c
  * @brief   This file provides code for the configuration
  *          of the CAN instances.
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
#include "can.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

CAN_HandleTypeDef hcan1;


// CANRxMessage can_rxMsg; /*!< for CAN test purpose */ 
// CANTxMessage can_txMsg; /*!< for CAN test purpose */

/* CAN1 init function */
void MX_CAN1_Init(void)
{

  /* USER CODE BEGIN CAN1_Init 0 */

  /* USER CODE END CAN1_Init 0 */

  /* USER CODE BEGIN CAN1_Init 1 */

  /* USER CODE END CAN1_Init 1 */
  hcan1.Instance = CAN1;
  hcan1.Init.Prescaler = 3;
  hcan1.Init.Mode = CAN_MODE_NORMAL;
  hcan1.Init.SyncJumpWidth = CAN_SJW_1TQ;
  hcan1.Init.TimeSeg1 = CAN_BS1_6TQ;
  hcan1.Init.TimeSeg2 = CAN_BS2_7TQ;
  hcan1.Init.TimeTriggeredMode = DISABLE;
  hcan1.Init.AutoBusOff = DISABLE;
  hcan1.Init.AutoWakeUp = DISABLE;
  hcan1.Init.AutoRetransmission = DISABLE;
  hcan1.Init.ReceiveFifoLocked = DISABLE;
  hcan1.Init.TransmitFifoPriority = DISABLE;
  if (HAL_CAN_Init(&hcan1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CAN1_Init 2 */

  /* USER CODE END CAN1_Init 2 */

}

void HAL_CAN_MspInit(CAN_HandleTypeDef* canHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(canHandle->Instance==CAN1)
  {
  /* USER CODE BEGIN CAN1_MspInit 0 */

  /* USER CODE END CAN1_MspInit 0 */
    /* CAN1 clock enable */
    __HAL_RCC_CAN1_CLK_ENABLE();

    __HAL_RCC_GPIOD_CLK_ENABLE();
    /**CAN1 GPIO Configuration
    PD0     ------> CAN1_RX
    PD1     ------> CAN1_TX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF9_CAN1;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

    /* CAN1 interrupt Init */ // Stopped CAN rx and tx interupts
    // HAL_NVIC_SetPriority(CAN1_TX_IRQn, 5, 0);
    // HAL_NVIC_EnableIRQ(CAN1_TX_IRQn);
    // HAL_NVIC_SetPriority(CAN1_RX0_IRQn, 10, 0);
    // HAL_NVIC_EnableIRQ(CAN1_RX0_IRQn);
  /* USER CODE BEGIN CAN1_MspInit 1 */

  /* USER CODE END CAN1_MspInit 1 */
  }
}

void HAL_CAN_MspDeInit(CAN_HandleTypeDef* canHandle)
{

  if(canHandle->Instance==CAN1)
  {
  /* USER CODE BEGIN CAN1_MspDeInit 0 */

  /* USER CODE END CAN1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_CAN1_CLK_DISABLE();

    /**CAN1 GPIO Configuration
    PD0     ------> CAN1_RX
    PD1     ------> CAN1_TX
    */
    HAL_GPIO_DeInit(GPIOD, GPIO_PIN_0|GPIO_PIN_1);

    /* CAN1 interrupt Deinit */ // Stopped CAN rx and tx interupts
    // HAL_NVIC_DisableIRQ(CAN1_TX_IRQn);
    // HAL_NVIC_DisableIRQ(CAN1_RX0_IRQn);
  /* USER CODE BEGIN CAN1_MspDeInit 1 */

  /* USER CODE END CAN1_MspDeInit 1 */
  }
}



/* USER CODE BEGIN 1 */

/* For CAN test purpose 

HAL_StatusTypeDef can_rx_init(){
  can_rxMsg.filter.FilterBank = 0;
  can_rxMsg.filter.FilterMode = CAN_FILTERMODE_IDMASK;
  can_rxMsg.filter.FilterScale = CAN_FILTERSCALE_32BIT;
  can_rxMsg.filter.FilterIdHigh = 1 << 5;
  can_rxMsg.filter.FilterIdLow = 0;
  can_rxMsg.filter.FilterMaskIdHigh = 0;
  can_rxMsg.filter.FilterMaskIdLow = 0;
  can_rxMsg.filter.FilterFIFOAssignment = CAN_FilterFIFO0;
  can_rxMsg.filter.FilterActivation = ENABLE;
  return HAL_CAN_ConfigFilter(&hcan1, &can_rxMsg.filter);
}

void can_tx_init(){
  can_txMsg.header.DLC = 8;
  can_txMsg.header.IDE = CAN_ID_STD;
  can_txMsg.header.RTR = CAN_RTR_DATA;
}

void send_can_test(){
  can_txMsg.header.StdId = 1;
  can_txMsg.data[0] = 12;
  can_txMsg.data[1] = 12;
  can_txMsg.data[2] = 12;
  can_txMsg.data[3] = 12;
  can_txMsg.data[4] = 12;
  can_txMsg.data[5] = 12;
  can_txMsg.data[6] = 12;
  can_txMsg.data[7] = 12;
  HAL_CAN_AddTxMessage(&hcan1, &can_txMsg.header, can_txMsg.data, &can_txMsg.TxMailBox);
 
}

*/

/* USER CODE END 1 */
