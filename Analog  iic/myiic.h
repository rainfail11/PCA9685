#ifndef __MYIIC_H
#define __MYIIC_H

#include "main.h"


static GPIO_InitTypeDef GPIO_InitStruct;

#define SCL_Type     GPIOB
#define SDA_Type     GPIOB
 
#define SCL_GPIO    GPIO_PIN_6
#define SDA_GPIO    GPIO_PIN_7

#define SDA_OUT(X)   if(X) \
					 HAL_GPIO_WritePin(SDA_Type, SDA_GPIO, GPIO_PIN_SET); \
				     else  \
					 HAL_GPIO_WritePin(SDA_Type, SDA_GPIO, GPIO_PIN_RESET);
 
#define SCL_OUT(X)   if(X) \
					 HAL_GPIO_WritePin(SCL_Type, SCL_GPIO, GPIO_PIN_SET); \
				     else  \
					 HAL_GPIO_WritePin(SCL_Type, SCL_GPIO, GPIO_PIN_RESET);    
                                     
#define SDA_IN		 HAL_GPIO_ReadPin(SDA_Type,SDA_GPIO)


void IIC_Start(void);
void IIC_Stop(void);
void IIC_Send_Byte(uint8_t d);
uint8_t IIC_Wait_Ack(void);
uint8_t  IIC_Read_Byte(unsigned char ack);
void IIC_Ack(uint8_t ack);
void IIC_NAck(void);
					 
#endif	
