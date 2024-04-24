#include <reg52.h>

sbit Key1 = P3^1;
sbit Key2 = P3^0;
sbit Key3 = P3^2;
sbit Key4 = P3^3;

unsigned char Key_KeyNum;

/**
  * @brief  独立按键检测
  * @param  无
  * @retval 返回按下的独立按键键码，下降沿检测
  */
unsigned char Key()
{
	unsigned char temp=0;
	temp = Key_KeyNum;
	Key_KeyNum = 0;
	return temp;
}

/**
  * @brief  检测独立按键状态
  * @param  无
  * @retval 返回独立按键此时状态
  */
unsigned char Key_GetState()
{
	unsigned char KeyState=0;
	if(Key1==0) {KeyState=1;}
	if(Key2==0) {KeyState=2;}
	if(Key3==0) {KeyState=3;}
	if(Key4==0) {KeyState=4;}
	return KeyState;
}

/**
  * @brief  计时器扫描按键状态循环，使用时放入计时器中断函数，参考时间20ms
  * @param  无
  * @retval 无
  */
void Key_Loop()
{
	static unsigned char NowState,LastState;
	LastState = NowState;
	NowState = Key_GetState();
	if(LastState == 1 && NowState == 0)
	{
		Key_KeyNum = 1;
	}
	if(LastState == 2 && NowState == 0)
	{
		Key_KeyNum = 2;
	}
	if(LastState == 3 && NowState == 0)
	{
		Key_KeyNum = 3;
	}
	if(LastState == 4 && NowState == 0)
	{
		Key_KeyNum = 4;
	}
}