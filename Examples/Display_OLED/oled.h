#ifndef __OLED_H
#define __OLED_H			  	 
//#include "sys.h"
#include "gpio.h"

//#define OLED_RST_Clr() PBout(3)=0   //RES (Reset)
//#define OLED_RST_Set() PBout(3)=1   //RES (Reset)

//#define OLED_RS_Clr() PAout(15)=0    //DC (Address)
//#define OLED_RS_Set() PAout(15)=1    //DC (Address)

//#define OLED_SCLK_Clr()  PBout(5)=0  //SCL (I2C)
//#define OLED_SCLK_Set()  PBout(5)=1   //SCL (I2C)

//#define OLED_SDIN_Clr()  PBout(4)=0   //SDA (I2C)
//#define OLED_SDIN_Set()  PBout(4)=1   //SDA (I2C)

#define OLED_CMD  0
#define OLED_DATA 1

void OLED_WR_Byte(uint8_t dat,uint8_t cmd);
void OLED_Display_On(void);
void OLED_Display_Off(void);
void OLED_Refresh_Gram(void);
void OLED_Init(void);
void OLED_Clear(void);
void OLED_DrawPoint(uint8_t x,uint8_t y,uint8_t t);
void OLED_ShowChar(uint8_t x,uint8_t y,uint8_t chr,uint8_t size,uint8_t mode);
void OLED_ShowNumber(uint8_t x,uint8_t y,int32_t num,uint8_t len,uint8_t size);
void OLED_ShowString(uint8_t x,uint8_t y,const uint8_t *p);

#endif     
	 
