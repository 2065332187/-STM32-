#include "stm32f10x.h"                  // Device header
#include <stdio.h>
#include "Delay.h"
#include "MyUSART.H"
#include "esp.h"
#include "DHT11.H"
#include "Timer.H"
#include "pwm.h"
#include "LightSensor.h"
#include "BEEP.h"
#include "led.h"
#include "mq.h"
int Temperature;
int Shidu;
uint8_t Switch1;
uint8_t Switch2;
extern char RECS[200];
extern char Data[5];
_Bool PWM_FLAG_1; 
uint16_t cnt;
int mqvalue;//气体浓度百分比
int lightvalue;//光照强度

void Init(void)
{
	uint8_t Judge=0;
	LightSensor_Init();
	Beep_Init();
	LED_Init();	
	ADC_Pin_Init();
	MyUSART_Init(); //初始化串口
	//Timer_Init();
    PWM_Init();
	do
	{
		Judge = esp_Init();
	
	}while(Judge);  //连接阿里云直到成功
	
}

int main(void)
{
	Init();
	while(1)
	{
		Shidu=Data[0];
		Temperature=Data[2];
		if(Switch1=='1'){
			GPIO_ResetBits(GPIOA,GPIO_Pin_3);
		}
		else if(Switch1=='0'){
			GPIO_SetBits(GPIOA,GPIO_Pin_3);
		}
		if(Switch2=='1'){
			GPIO_ResetBits(GPIOA,GPIO_Pin_2);
		}
		else if(Switch2=='0'){
			GPIO_SetBits(GPIOA,GPIO_Pin_2);
		}
		
		cnt++;
		if(cnt%150==0){
			DHT11_GetData(); //约每1s执行一次温湿度采集
		    mqvalue = (int)ADC_Trans()*99/4096.0;
		}
		if(cnt==600) //约每6s执行一次数据上报
		{
			if(Esp_PUB() == 1)
			{
				Delay_ms(500);
			}
			cnt=0;
		}
		
		
		
		//
		lightvalue=!(LightSensor_Get());
		if(LightSensor_Get()==1){
			LIGHT_ON;	
		}
		else{
			LIGHT_OFF;
		}
		//
		if(Temperature>28){
			    BEEP_ON;
		    }
		else{
			    BEEP_OFF;
		    }
	}
	
}






