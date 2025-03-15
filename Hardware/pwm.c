#include "pwm.h"
#include "led.h"
#include "delay.h"
#include "stm32f10x.h"

extern _Bool PWM_FLAG_1;//µç»ú
void PWM_Init(void){
    GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;				 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
	GPIO_Init(GPIOB, &GPIO_InitStructure);	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;				 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
	GPIO_Init(GPIOB, &GPIO_InitStructure);	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;				 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
	GPIO_Init(GPIOB, &GPIO_InitStructure);	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;				 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
	GPIO_Init(GPIOB, &GPIO_InitStructure);	

}
	
void PWM_control(void){
	if(PWM_FLAG_1==1){
		 GPIO_SetBits(GPIOB,GPIO_Pin_0);
		 GPIO_ResetBits(GPIOB,GPIO_Pin_1);
		 GPIO_SetBits(GPIOB,GPIO_Pin_2);
		 GPIO_ResetBits(GPIOB,GPIO_Pin_3);
		 GPIO_SetBits(GPIOB,GPIO_Pin_4);
		 GPIO_ResetBits(GPIOB,GPIO_Pin_5);
		 GPIO_SetBits(GPIOB,GPIO_Pin_6);
		 GPIO_ResetBits(GPIOB,GPIO_Pin_7);
	}
	else if(PWM_FLAG_1==0){
		 GPIO_SetBits(GPIOB,GPIO_Pin_1);
		 GPIO_ResetBits(GPIOB,GPIO_Pin_0);
		 GPIO_SetBits(GPIOB,GPIO_Pin_3);
		 GPIO_ResetBits(GPIOB,GPIO_Pin_2);
		 GPIO_SetBits(GPIOB,GPIO_Pin_5);
		 GPIO_ResetBits(GPIOB,GPIO_Pin_4);
		 GPIO_SetBits(GPIOB,GPIO_Pin_7);
		 GPIO_ResetBits(GPIOB,GPIO_Pin_6);
	}
}




