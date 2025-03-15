#include "stm32f10x.h"                  // Device header
#include "MyUSART.h"
#include "esp.h"
#include <string.h>

char RECS[250];
unsigned char i;

void MyUSART_Init(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 ,ENABLE);//1.开启时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO ,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA ,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;                 //初始化GIPIO
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	USART_InitTypeDef USART_InitStructure;              //初始化串口
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_HardwareFlowControl =USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStructure.USART_Parity =USART_Parity_No ;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_Init (USART1,&USART_InitStructure);
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel =USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&NVIC_InitStructure);
	
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	USART_Cmd(USART1,ENABLE);
	
}
char* MyUSART_GetString(void)
{
	return RECS;
}
void MyUSART_SendString(char* str)
{
	uint8_t stri=0;
	while(str[stri] != '\0')
		USART_SendData (USART1,str[stri++]);
}
void USART1_IRQHandler()
{
	if(USART_GetITStatus(USART1,USART_IT_RXNE))
	{
		RECS[i++]=USART_ReceiveData(USART1);
		if((RECS[i-2]=='\r')|(RECS[i-1]=='\n'))  
		{
			RECS[i-2]='\0';
			i = 0;
			CommandAnalyse();
		}
	}
}
