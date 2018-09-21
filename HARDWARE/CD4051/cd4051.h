#ifndef __CD4051_H
#define __CD4051_H

#include "sys.h"



#define CD4051_BIT0 PBout(3)
#define CD4051_BIT1 PBout(4)
#define CD4051_BIT2 PBout(5)
#define CD4051_BIT3 PBout(6)
#define CD4051_BIT4 PBout(7)
#define CD4051_BIT5 PBout(8)



void CD4051_Init(void);
void CD4051SetChannel(u8 ch);







































#endif
