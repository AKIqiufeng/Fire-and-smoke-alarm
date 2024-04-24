#ifndef __BEEP_H
#define __BEEP_H

#include <reg52.h>
#include  "delay.h"


sbit BEEP = P0^7; 

void  BeepOn();
void  BeepOff();

#endif