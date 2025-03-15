#ifndef __BEEP_H
#define __BEEP_H	
#include "sys.h"


#define BEEP_ON PBout(12)=0;	// PB12
#define BEEP_OFF PBout(12)=1;	// PB12
#define GET_BEEP_STATE GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12)
void Beep_Init(void);
 
#endif 
