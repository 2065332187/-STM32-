#include "stm32f10x_tim.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_adc.h"
#include "mq.h"
#include "Delay.h"
#include "sys.h"

 
void ADC_Pin_Init(void)        //???PA0???ADC???,?????ADC??1
{
	GPIO_InitTypeDef GPIO_InitStruct;
	ADC_InitTypeDef ADC_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_ADC1,ENABLE);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	ADC_InitStruct.ADC_ContinuousConvMode = ENABLE;  //??????
	ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStruct.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStruct.ADC_NbrOfChannel = 1;
	ADC_InitStruct.ADC_ScanConvMode = DISABLE;
	ADC_Init(ADC1,&ADC_InitStruct);
	
	ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_239Cycles5);
	
	ADC_ITConfig(ADC1,ADC_IT_EOC,ENABLE);
	
	ADC_Cmd(ADC1,ENABLE);
}
 
u16 ADC_Trans(void)       //????,????????
{
	u16 adc_value = 0;
	u8 i = 0;
	
	for(i = 0; i < 50; i++)
	{ 
		ADC_SoftwareStartConvCmd(ADC1,ENABLE);	
		adc_value = adc_value + ADC_GetConversionValue(ADC1);
	}
	
	return adc_value / 50;
}


