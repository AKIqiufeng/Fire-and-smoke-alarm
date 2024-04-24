#include <reg52.h>
#include <stdio.h>
#include "OLED.h"
#include "delay.h"
#include "dht11.h"
#include "Key.h"
#include "Beep.h"
#include "Timer0.h"
#include "XPT2046.h"
#include "AT24C02.h"

sbit HY = P0^3;
sbit YW = P0^4;

u8 hyFlag,ywFlag;

void Oled_ShowMsg()
{
	OLED_DisplayStr(0, 1, "Rebuild by", TextSize8x16);
	OLED_DisplayStr(48, 4, "AKIqiufeng", TextSize8x16);
	delayms(1000);
	OLED_DisplayStr(0, 1, "          ", TextSize8x16);
	OLED_DisplayStr(48, 4, "          ", TextSize8x16);
}

void main()
{
	u16 temperature_h,humidity_h,Set_temp = 50,YW_AD;
	u8 show_str[16];
	u8 keyNum,mode = 4,flag = 0;
	Timer0_Init();
	OLED_Init();
	Set_temp = AT24C02_ReadByte(1);
	delayms(100);
	Oled_ShowMsg();
  while (1)
  {
		keyNum = Key();
		
		if(keyNum)
		{
				if(mode == 1)
				{
					if(keyNum == 2) {Set_temp--;AT24C02_WriteByte(1,Set_temp);}
					if(keyNum == 3) {Set_temp++;AT24C02_WriteByte(1,Set_temp);}
					if(keyNum == 4) {mode = 4;OLED_Fill(0x00);}
				}
				else
				{
					if(keyNum == 1) {mode = 1;OLED_Fill(0x00);}
					if(keyNum == 2) {mode = 2;OLED_Fill(0x00);}
					if(keyNum == 3) {mode = 3;OLED_Fill(0x00);}
					if(keyNum == 4) {mode = 4;OLED_Fill(0x00);}
				}

		}
		
		if(mode == 1)
		{
			TR0 = 0;
			flag = receive(&temperature_h, &humidity_h);
			TR0 = 1;
			OLED_DisplayCN(40, 0, 0);
		  OLED_DisplayCN(56, 0, 1);
		  OLED_DisplayCN(72, 0, 2);
			sprintf(show_str, "SET:%d", Set_temp);
			OLED_DisplayStr(72, 4,show_str, TextSize8x16);
			OLED_DisplayStr(86, 7,"Menu:K4", TextSize6x8);
			if(flag == 0)
			{
				sprintf(show_str, "tem:%d", temperature_h);
				OLED_DisplayStr(0, 3, show_str, TextSize8x16);
				sprintf(show_str, "hum:%d\%", humidity_h);
				OLED_DisplayStr(0, 5, show_str, TextSize8x16);
				if(temperature_h > Set_temp)//温度报警阈值
				{
					BeepOn();
				}
				else
				{
					BeepOff();
				}
			}
			else{
				OLED_DisplayStr(0, 3, "error!", TextSize8x16);
			}
		}
		if(mode == 2)
		{  
			OLED_DisplayCN(24, 0, 11);
		  OLED_DisplayCN(40, 0, 12);
		  OLED_DisplayCN(56, 0, 15);
			OLED_DisplayCN(72, 0, 16);
			OLED_DisplayCN(88, 0, 17);
			OLED_DisplayStr(86, 7,"Menu:K4", TextSize6x8);
			if(hyFlag == 0)	 
			{
				BeepOn();
				OLED_DisplayCN(40, 3, 9);
				OLED_DisplayCN(80, 3, 11);
				delayms(100);
			}
			else
			{	
				BeepOff();
				OLED_DisplayCN(40, 3, 10);
				OLED_DisplayCN(80, 3, 11);
				delayms(100);
			}
		}
		if(mode == 3)
		{ 
			OLED_DisplayCN(24, 0, 13);
		  OLED_DisplayCN(40, 0, 14);
		  OLED_DisplayCN(56, 0, 15);
			OLED_DisplayCN(72, 0, 16);
			OLED_DisplayCN(88, 0, 17);
			OLED_DisplayStr(86, 7,"Menu:K4", TextSize6x8);

			YW_AD = XPT2046_ReadAD(XPT2046_AUX_12);
			sprintf(show_str, "AD value:%d", YW_AD);
			OLED_DisplayStr(16, 5, show_str, TextSize8x16);
			if(ywFlag == 0)	 
			{
				BeepOn();		  
			  OLED_DisplayCN(40, 3, 9);
        OLED_DisplayCN(80, 3, 13);
				delayms(100);
			}
			else
			{
				BeepOff();		 
				OLED_DisplayCN(40, 3, 10);
				OLED_DisplayCN(80, 3, 13);
				delayms(100);
			}
		}
		if(mode == 4)
		{
			BeepOff();
			OLED_DisplayStr(48, 0, "MENU", TextSize8x16);
			OLED_DisplayStr(0, 2, "----------------", TextSize8x16);
			OLED_DisplayCN(0, 4, 0);
			OLED_DisplayCN(16, 4, 1);
			OLED_DisplayCN(32, 4, 2);
			OLED_DisplayCN(56, 4, 11);
			OLED_DisplayCN(72, 4, 12);
			OLED_DisplayCN(96, 4, 13);
			OLED_DisplayCN(112, 4, 14);
			OLED_DisplayStr(0, 6, "  K1    K2   K3 ", TextSize8x16);
		}
   }
}

void Timer0_Routine() interrupt 1
{
	static unsigned int T0Count;
	TL0 = 0x33;				//设置定时初始值
	TH0 = 0xFE;				//设置定时初始值
	T0Count++;
	Beep_Loop();
	if(T0Count >= 40)
	{
		T0Count = 0;
		Key_Loop();
		hyFlag = HY;
		ywFlag = YW;
	}
}