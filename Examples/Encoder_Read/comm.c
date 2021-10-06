/*
 * comm.c
 *
 *  Created on: 2021. 6. 25.
 *      Author: Á¤µ¿¿ø
 *
 *
 *  Modified by GEONGSU PARK
 *  Date: 2021. 9. 27.
 */

#include "comm.h"
#include "usart.h"
#include "string.h"
#include "main.h"

uint8_t DataScope_OutPut_Buffer[42] = {0};

void debugPrint(UART_HandleTypeDef *huart, char _out[])
{
	HAL_UART_Transmit(huart, (uint8_t *)_out, strlen(_out), 10);
}

void debugPrintln(UART_HandleTypeDef *huart, char _out[])
{
	HAL_UART_Transmit(huart, (uint8_t *) _out, strlen(_out), 10);
	char newline[2] = "\r\n";
	HAL_UART_Transmit(huart, (uint8_t *) newline, 2, 10);
}
/* USER CODE END 4 */

void Float2Byte(float *target,uint8_t *buf,uint8_t beg)
{
    unsigned char *point;
    point = (unsigned char*)target;
    buf[beg]   = point[0];
    buf[beg+1] = point[1];
    buf[beg+2] = point[2];
    buf[beg+3] = point[3];
}

void DataScope_Get_Channel_Data(float Data,uint8_t Channel)
{
	if ( (Channel > 10) || (Channel == 0) ) return;
	else
	{
		switch (Channel)
		{
			case 1:  Float2Byte(&Data,DataScope_OutPut_Buffer,1); break;
			case 2:  Float2Byte(&Data,DataScope_OutPut_Buffer,5); break;
			case 3:  Float2Byte(&Data,DataScope_OutPut_Buffer,9); break;
			case 4:  Float2Byte(&Data,DataScope_OutPut_Buffer,13); break;
			case 5:  Float2Byte(&Data,DataScope_OutPut_Buffer,17); break;
			case 6:  Float2Byte(&Data,DataScope_OutPut_Buffer,21); break;
			case 7:  Float2Byte(&Data,DataScope_OutPut_Buffer,25); break;
			case 8:  Float2Byte(&Data,DataScope_OutPut_Buffer,29); break;
			case 9:  Float2Byte(&Data,DataScope_OutPut_Buffer,33); break;
			case 10: Float2Byte(&Data,DataScope_OutPut_Buffer,37); break;
		}
	}
}

unsigned char DataScope_Data_Generate(uint8_t Channel_Number)
{
	if ( (Channel_Number > 10) || (Channel_Number == 0) ) { return 0; }
	else
	{
		DataScope_OutPut_Buffer[0] = '$';

		switch(Channel_Number)
		{
			case 1:   DataScope_OutPut_Buffer[5]  =  5; return  6;
			case 2:   DataScope_OutPut_Buffer[9]  =  9; return 10;
			case 3:   DataScope_OutPut_Buffer[13] = 13; return 14;
			case 4:   DataScope_OutPut_Buffer[17] = 17; return 18;
			case 5:   DataScope_OutPut_Buffer[21] = 21; return 22;
			case 6:   DataScope_OutPut_Buffer[25] = 25; return 26;
			case 7:   DataScope_OutPut_Buffer[29] = 29; return 30;
			case 8:   DataScope_OutPut_Buffer[33] = 33; return 34;
			case 9:   DataScope_OutPut_Buffer[37] = 37; return 38;
			case 10:  DataScope_OutPut_Buffer[41] = 41; return 42;
		}
	}
	return 0;
}

void DataScope(UART_HandleTypeDef *huart)
{
	uint8_t Send_Count;

	// Time value
	DataScope_Get_Channel_Data( timeval, 1 );

	// Position value
	DataScope_Get_Channel_Data( Target_Position, 2 );

	// Velocity value
	DataScope_Get_Channel_Data( Target_Velocity, 3 );

	// Control output
	DataScope_Get_Channel_Data( Target_Control, 4 );

	// Finalize the packet
	Send_Count = DataScope_Data_Generate(4);

	// Send-out the packet
	HAL_UART_Transmit(&huart1, (uint8_t *)DataScope_OutPut_Buffer, Send_Count, 10);

}


/*
 *  Convert timer counter [uint16_t] to angle [deg]
 *
 *  Modified by GEONGSU PARK
 *  Date: 2021. 9. 27.
 */

int timer_counter_pre;
int overflow_flag = 0;
const float clocks_per_revolution = 11700/11;

float timer_counter_to_angle(uint16_t timer_counter)
{
	float degree = 0;
	// int revolution = 0;

	if((timer_counter_pre > 49152) && (timer_counter < 16384))
	{ // overflow
		overflow_flag++;
	}

	if((timer_counter_pre < 16384) && (timer_counter > 49152))
	{ // underflow
		overflow_flag--;
	}

	// revolution = (int)((float)(timer_counter + (65535 * overflow_flag)) / clocks_per_revolution);
	degree = (float)(timer_counter + (65535 * overflow_flag)) / clocks_per_revolution * 360;

	timer_counter_pre = timer_counter;

	return degree;
}
