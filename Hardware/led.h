#ifndef __LED_H
#define __LED_H	 
#include "sys.h"   
#define LIGHT_ON PAout(7)=1;	
#define LIGHT_OFF PAout(7)=0;	
#define LIGHT1_ON PAout(8)=1;	
#define LIGHT1_OFF PAout(8)=0;	
void LED_Init(void);//≥ı ºªØ	 
void LED1_Init(void);
#endif
