#ifndef __PCA9685_H
#define __PCA9685_H

#include "main.h"

#include "stdio.h"

#define u8 uint8_t
#define u16 uint16_t
#define u32 uint32_t

   
#define PCA_Addr 0x80
#define PCA_Model 0x00
#define LED0_ON_L 0x06
#define LED0_ON_H 0x07
#define LED0_OFF_L 0x08
#define LED0_OFF_H 0x09
#define PCA_Pre 0xFE


void PCA9685_Init(float hz,u16 angle);
 
void PCA9685_Write(u8 addr,u8 data);
 
u8 PCA9685_Read(u8 addr);
 
void PCA9685_setPWM(u8 num,u32 on,u32 off);
 
void PCA9685_setFreq(float freq);
 
void setAngle(u8 num,u16 angle);
#endif
