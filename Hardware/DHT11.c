#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include <string.h>
unsigned char Data[5];

uint16_t dhti;
char DHT11_GetData(void)
{
	memset(Data,0,5);
	RCC_APB2PeriphClockCmd (RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init (GPIOB,&GPIO_InitStructure);             //初始化GPIO为推挽输出模式
	
	GPIO_ResetBits(GPIOB,GPIO_Pin_12);
	Delay_ms(20); 
	GPIO_SetBits(GPIOB,GPIO_Pin_12);
	Delay_us(25);                           //发送开始信号

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init (GPIOB,&GPIO_InitStructure);              //切换到输入模式
	
	dhti=0;
	while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12)==0)
	{dhti++;if(dhti>10000) {break;}}
	dhti=0;
	while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12)==1)
		{dhti++;if(dhti>10000) {break;}} //DHT11响应信号
	
	for(char j=0;j<5;j++)
	{
		for(char i=0;i<8;i++)
		{
			dhti=0;
			while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12)==0)
				{dhti++;if(dhti>10000) {break;}}
			Delay_us(30);
			Data[j] <<=1;
			Data[j] |= (unsigned char)GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12);
			dhti=0;
			while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12)==1)
				{dhti++;if(dhti>10000) {break;}};//消除为1时的余时
		}
	}
	if(Data[4]==(char)(Data[0]+Data[1]+Data[2]+Data[3]))
		return 1;
	else
		return 0;
}

