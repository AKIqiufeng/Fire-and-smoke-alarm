#include  "dht11.h"

u8 data_byte;		
u8 DHT_RH,DHT_RL,DHT_TH,DHT_TL;	


static void delay1()		//@11.0592MHz
{
	unsigned char i;

	i = 2;
	while (--i);
}

static void delay(int xms)		//@11.0592MHz
{
	unsigned char i, j;

	while(xms--)
	{
		_nop_();
		i = 2;
		j = 199;
		do
		{
			while (--j);
		} while (--i);
	}
}

//Եʼۯςʪ׈
void start()
{
	dht_io = 1;
	delay1();
	dht_io = 0;
	delay(25);
	dht_io = 1;
	delay1();
	delay1();
	delay1();
}

u8 receive_byte()
{
	u8 i,temp=0;
	
	for(i=0;i<8;i++)
	{
		while(!dht_io);
		delay1();
		delay1();
		delay1();
		//temp = 0;
		if(dht_io == 1)
		{
			temp |= 1<<(7-i);
			while(dht_io);
		}
	}
	return temp;
}

u8 receive(u16* temperature_h, u16* humidity_h)
{
	unsigned int T_H,T_L,R_H,R_L,check,num_check,i=0;
	
	start();	
	dht_io = 1;
	
	if(!dht_io)
	{
		while(!dht_io);
		while(dht_io);
		R_H=receive_byte();
		R_L=receive_byte();
		T_H=receive_byte();
		T_L=receive_byte();
		check=receive_byte();
		dht_io = 0;
		for(i=0;i<7;i++)
			delay1();
		dht_io = 1;
		num_check=R_H+R_L+T_H+T_L;
		if((num_check & 0xFF) == check)
		{
			DHT_RH=R_H;
			DHT_RL=R_L;
			DHT_TH=T_H;
			DHT_TL=T_L;
			*temperature_h = DHT_TH;
			*humidity_h = DHT_RH;
			check=num_check;
			return 0;
		}
		else{
			return 1;
		}
	}
}
