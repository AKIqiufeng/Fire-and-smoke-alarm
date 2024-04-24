#ifndef __DELAY_H
#define __DELAY_H

#include <reg52.h>
#include <intrins.h>


typedef unsigned char  u8;       /* defined for unsigned 8-bits integer variable 	  无符号8位整型变量  */
typedef signed   char  s8;       /* defined for signed 8-bits integer variable		  有符号8位整型变量  */
typedef unsigned int   u16;      /* defined for unsigned 16-bits integer variable 	  无符号16位整型变量 */
typedef signed   int   s16;      /* defined for signed 16-bits integer variable 	  有符号16位整型变量 */
typedef unsigned long  u32;      /* defined for unsigned 32-bits integer variable 	  无符号32位整型变量 */
typedef signed   long  s32;      /* defined for signed 32-bits integer variable 	  有符号32位整型变量 */
typedef float          f32;      /* single precision floating point variable (32bits) 单精度浮点数（32位长度） */
typedef double         f64;      /* double precision floating point variable (64bits) 双精度浮点数（64位长度） */


void delayms(u16 xms);
	
#endif