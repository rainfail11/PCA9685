#include "PAC9685.h"
#include "myiic.h"
#include "Delay.h"


char buf[20];

void PCA9685_Init(float hz,u16 angle)
{
	u32 off = 0;
	
	PCA9685_Write(PCA_Model,0x00);
	
	PCA9685_setFreq(hz);
	
    off = (u32)(103+angle*2.28);  //180度舵机，每转动一度=2.28   0度起始位置：103
	
	PCA9685_setPWM(0,0,off);
	PCA9685_setPWM(1,0,off);
	PCA9685_setPWM(2,0,off);
	PCA9685_setPWM(3,0,off);
	PCA9685_setPWM(4,0,off);
	PCA9685_setPWM(5,0,off);
	PCA9685_setPWM(6,0,off);
	PCA9685_setPWM(7,0,off);
	PCA9685_setPWM(8,0,off);
	PCA9685_setPWM(9,0,off);
	PCA9685_setPWM(10,0,off);
	PCA9685_setPWM(11,0,off);
	PCA9685_setPWM(12,0,off);
	PCA9685_setPWM(13,0,off);
	PCA9685_setPWM(14,0,off);
	PCA9685_setPWM(15,0,off);
	
	Delay_ms(100);
	
}
 
void PCA9685_Write(u8 addr,u8 data)
{
	IIC_Start();
	
	IIC_Send_Byte(PCA_Addr);
	IIC_NAck();
	
	IIC_Send_Byte(addr);
	IIC_NAck();
	
	IIC_Send_Byte(data);
	IIC_NAck();
	
	IIC_Stop();
	
	
}
 
u8 PCA9685_Read(u8 addr)
{
	u8 data;
	
	IIC_Start();
	
	IIC_Send_Byte(PCA_Addr);
	IIC_NAck();
	
	IIC_Send_Byte(addr);
	IIC_NAck();
	
	IIC_Stop();
	
	Delay_us(10);
 
	
	IIC_Start();
 
	IIC_Send_Byte(PCA_Addr|0x01);
	IIC_NAck();
	
	data = IIC_Read_Byte(0);
	
	IIC_Stop();
	
	return data;
	
}
 
void PCA9685_setPWM(u8 num,u32 on,u32 off)
{
	
	
	PCA9685_Write(LED0_ON_L + 4 * num,on);
	PCA9685_Write(LED0_ON_H + 4 * num,on >> 8);
	
	PCA9685_Write(LED0_OFF_L + 4 * num,off);
	PCA9685_Write(LED0_OFF_H + 4 * num,off >> 8);
	
	
	
}
 
void PCA9685_setFreq(float freq)
{
	u8 prescale,oldmode,newmode;
	
	double prescaleval;
	
	freq *= 0.98;
	prescaleval = (25000000 /4096/freq) - 1;

	prescale = prescaleval;
	sprintf(buf,"value:%f",prescaleval);
	oldmode = PCA9685_Read(PCA_Model);
	
	newmode = (oldmode&0x7F)|0x10;
	PCA9685_Write(PCA_Model,newmode);
	PCA9685_Write(PCA_Pre,prescaleval);
	PCA9685_Write(PCA_Model,oldmode);
	Delay_ms(5);
	PCA9685_Write(PCA_Model,oldmode|0xa1);
   
	
}

void setAngle(u8 num,u16 angle)
{
	u32 off = 0;                
	off = (u32)(103+angle*2.28);  //360度舵机，每转动一度=2.28   0度起始位置：103
	PCA9685_setPWM(num,0,off);
}
 
  