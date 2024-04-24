#ifndef __DHT11_H
#define __DHT11_H

#include <reg52.h>
#include  "delay.h"

sbit dht_io = P0^0; 

u8 receive(char* temperature_h, char* humidity_h);
	
#endif