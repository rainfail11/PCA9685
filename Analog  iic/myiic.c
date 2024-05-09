#include "myiic.h"
#include "Delay.h"


void IIC_SDA_Mode_OUT(void)
{
    GPIO_InitStruct.Pin = SDA_GPIO;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(SDA_Type, &GPIO_InitStruct);
}

void IIC_SDA_Mode_IN(void)
{
    GPIO_InitStruct.Pin = SDA_GPIO;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(SDA_Type, &GPIO_InitStruct);
}


void IIC_Start(void)
{
	
	IIC_SDA_Mode_OUT();
	
	
	SDA_OUT(1);
	SCL_OUT(1) ;
	Delay_us(5);
	
	
	SDA_OUT(0);
	Delay_us(5);
	
	
	SCL_OUT(0) ;
	Delay_us(5);
}



void IIC_Stop(void)
{
	
	IIC_SDA_Mode_OUT();
 
	
	SDA_OUT(0);
	SCL_OUT(0);
	Delay_us(5);
	
	
	SCL_OUT(1);
	Delay_us(5);
	
	
	SDA_OUT(1);
	Delay_us(5);
}


void IIC_Send_Byte(uint8_t d)
{
    uint8_t i = 0;
    
	IIC_SDA_Mode_OUT();
	
	SDA_OUT(0);
	SCL_OUT(0);
	Delay_us(5);
	for(i=0;i<8;i++)
	{
		if(d & (0x1<<(7-i)))
			SDA_OUT(1)
		else
			SDA_OUT(0);
		
		Delay_us(5);
		SCL_OUT(1);
		
		Delay_us(5);
		SCL_OUT(0);
	}
 
}

uint8_t IIC_Wait_Ack(void)
{
	uint8_t ack = 0;
	
	IIC_SDA_Mode_IN();
	
	
	SCL_OUT(1);
	Delay_us(5);
	
	if( SDA_IN  == 1)
		ack = 1;
	else
		ack = 0;
	
	SCL_OUT(0);
    
	Delay_us(5);
	return ack;
}

uint8_t  IIC_Read_Byte(unsigned char ack)
{
	uint8_t i =0;
	uint8_t data = 0;
	
	IIC_SDA_Mode_IN();
	
	SCL_OUT(0);
	Delay_us(5);
	
	for(i=0;i<8;i++)
	{
		SCL_OUT(1);
		Delay_us(5);
		if(SDA_IN == 1)
			data |= (0x1<<(7-i));
		else
			data &= ~(0x1<<(7-i));
		
		SCL_OUT (0);
		Delay_us(5);
	}
	    if (!ack)
        IIC_NAck();
    else
        IIC_Ack(0);   
	return data;
}

void IIC_Ack(uint8_t ack)
{
	
	IIC_SDA_Mode_OUT();
	
	SDA_OUT(0);
	SCL_OUT(0);
	Delay_us(5);
	
	SDA_OUT(ack);
	Delay_us(5);
	
	SCL_OUT(1);
	Delay_us(5);
	
	SCL_OUT (0);
	Delay_us(5);
}

void IIC_NAck(void)	  
{
	
	IIC_SDA_Mode_OUT();
	SDA_OUT(1);
	Delay_us(2);
	SCL_OUT(1);
	Delay_us(2);
	SCL_OUT(0);
}
