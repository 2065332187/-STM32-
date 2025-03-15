#include "stm32f10x.h"                  // Device header
#include "MyUSART.h"
#include <stdio.h>
#include <string.h>
#include "Delay.h"
extern int Temperature;
extern int Shidu;
extern int mqvalue;
extern int lightvalue;
extern uint8_t Switch1;
extern uint8_t Switch2;
extern char RECS[250];
const char* WIFI ="OnePlus";
const char* WIFIASSWORD="123456321";
const char* ClintID="k10fpvqhgUG.wen-shi-du|securemode=2\\,signmethod=hmacsha256\\,timestamp=1720574333844|";
const char* username="wen-shi-du&k10fpvqhgUG";
const char* passwd="45641d417e171422959c0a5d5b75871910f880587e21089dd93c95322b659daf";
const char* Url="iot-06z00bmizfm8wx2.mqtt.iothub.aliyuncs.com";
const char* pubtopic="/sys/k10fpvqhgUG/wen-shi-du/thing/event/property/post";
const char* subtopic="/sys/k10fpvqhgUG/wen-shi-du/thing/event/property/post_reply";
const char* func1="CurrentTemperature";
const char* func2="CurrentHumidity";
const char* func3="USBSwitch_1";
const char* func4="USBSwitch_2";
const char* func5="Gas";
const char* func6="deng";
int fputc(int ch,FILE *f )   //printf重定向  
{
	USART_SendData(USART1,(uint8_t)ch);
	while(USART_GetFlagStatus (USART1,USART_FLAG_TC) == RESET);
	return ch;
}
char esp_Init(void)
{
	memset(RECS,0,sizeof(RECS));
	printf("AT+RST\r\n");  //重启
	Delay_ms(2000);
	
	memset(RECS,0,sizeof(RECS));
	printf("ATE0\r\n");    //关闭回显
	Delay_ms(10);
	if(strcmp(RECS,"OK"))
		return 1;
	
	printf("AT+CWMODE=1\r\n"); //Station模式
	Delay_ms(1000);
	if(strcmp(RECS,"OK"))
		return 2;
	
	memset(RECS,0,sizeof(RECS));
	printf("AT+CWJAP=\"%s\",\"%s\"\r\n",WIFI,WIFIASSWORD); //连接热点
	Delay_ms(2000);
	if(strcmp(RECS,"OK"))
		return 3;
	
	memset(RECS,0,sizeof(RECS));
	printf("AT+MQTTUSERCFG=0,1,\"%s\",\"%s\",\"%s\",0,0,\"\"\r\n",ClintID,username,passwd);//用户信息配置
	Delay_ms(10);
	if(strcmp(RECS,"OK"))
		return 4;
	
	memset(RECS,0,sizeof(RECS));
	printf("AT+MQTTCONN=0,\"%s\",1883,1\r\n",Url); //连接服务器
	Delay_ms(1000);
	if(strcmp(RECS,"OK"))
		return 5;
	
	printf("AT+MQTTSUB=0,\"%s\",1\r\n",subtopic); //订阅消息
	Delay_ms(500);
	if(strcmp(RECS,"OK"))
		return 5;
	memset(RECS,0,sizeof(RECS));
	return 0;
}
//功能：esp发送消息
//参数：无
//返回值：0：发送成功；1：发送失败
char Esp_PUB(void)
{
	memset(RECS,0,sizeof(RECS));
	/*printf("AT+MQTTPUB=0,\"%s\",\"{\\\"method\\\":\\\"thing.event.property.post\\\"\\,"
       "\\\"params\\\":{\\\"%s\\\":%d\\,\\\"%s\\\":%d\\,\\\"%s\\\":%d\\,"
       "\\\"%s\\\":%d}}\", 0, 0\r\n",
       pubtopic, func1, Temperature, func2, Shidu, func3, Switch1, func4, Switch2);*/
	printf("AT+MQTTPUB=0,\"%s\",\"{\\\"method\\\":\\\"thing.event.property.post\\\"\\,\\\"params\\\":{\\\"%s\\\":%d\\,\\\"%s\\\":%d\\,\\\"%s\\\":%d\\,\\\"%s\\\":%d\\,\\\"%s\\\":%d\\,\\\"%s\\\":%d}}\",0,0\r\n",pubtopic,func1,Temperature,func2,Shidu,func3,Switch1,func4,Switch2,func5,mqvalue,func6,lightvalue);
	//while(RECS[0]);//等待ESP返回数据
	Delay_ms(2000);//延时等待数据接收完成
	if(strcmp(RECS,"ERROR")==0)
		return 1;
	return 0;
}
void CommandAnalyse(void)
{
	//Switch1='0';
	//Switch2='0';
	if(strncmp(RECS,"+MQTTSUBRECV:",13)==0)
	{
		uint8_t i=0;
		while(RECS[i++] != '\0')             
		{
			if(strncmp((RECS+i),func3,11)==0)//标识符3的字节数为13
			{
				while(RECS[i++] != ':');       
				Switch1=RECS[i];
			}
			if(strncmp((RECS+i),func4,11)==0)
			{
				while(RECS[i++] != ':');
				Switch2=RECS[i];
			}
		}
	}
}









