#include <reg52.h>
#include <intrins.h>

sbit beep = P2^5;//普中51开发板A2新款蜂鸣器端口为P25
unsigned char BeepFlag=0;


/**
  * @brief  蜂鸣器专用延时函数，延时500us
  * @param  无
  * @retval 无
  */
	/*
void Beep_Delay500us(void)	//@11.0592MHz
{
	unsigned char data i;

	_nop_();
	i = 227;
	while (--i);
}
*/
/**
  * @brief  蜂鸣器播放提示音(1000hz)
  * @param  播放时长
  * @retval 无
  */
/*
void Beep_Time(unsigned int ms)
{
	unsigned int i;
	for(i=0;i<ms*2;i++)
			{
				beep = !beep;
				Beep_Delay500us();
			}
}
*/
void BeepOff()
{
	BeepFlag = 0;
}

void BeepOn()
{
	BeepFlag = 1;
}

void Beep_Loop()
{
	if(BeepFlag == 1)
	{
		beep = !beep;
	}
}
