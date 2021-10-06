/**
  ******************************************************************************
  * @file    comm.h
  * @brief   This file contains all the function prototypes for
  *          the comm.c file
  ******************************************************************************
  * @attention
  *
  * Written by Thomas Jung
  * Date: 2021. 6. 25
  *
  * Modified by Geongsu Park
  * Date: 2021. 9. 27
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __COMM_H__
#define __COMM_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "usart.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

void debugPrint(UART_HandleTypeDef *huart, char _out[]);

void debugPrintln(UART_HandleTypeDef *huart, char _out[]);

void Float2Byte(float *target,uint8_t *buf,uint8_t beg);

void DataScope_Get_Channel_Data(float Data,uint8_t Channel);

uint8_t DataScope_Data_Generate(uint8_t Channel_Number);

void DataScope(UART_HandleTypeDef *huart);

float timer_counter_to_angle(uint16_t timer_counter);

/* USER CODE BEGIN Prototypes */

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ COMM_H__ */

/*****END OF FILE****/
