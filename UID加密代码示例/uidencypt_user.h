/************************************
STM32 GD32 UID算法加密代码DEMO。
www.xwopen.com
xuanweikeji.taobao.com
版权所有。
*************************************/

#ifndef uidencypt_user_h
#define uidencypt_user_h

#include "stdint.h"
#include "stdbool.h"

#define GONG_SHI_HAO                    (110)           //修改为你要使用的公式号，此值要与软件配置的一致
#define CHANG_SHU                       (0X6AB85F)      //修改为你要使用的常数值，此值要与软件配置的一致
#define CUN_FANG_QI_SHI_DI_ZHI          (0X8006000)     //修改为你配置的结果值的存放地址。此值要与软件配置的一致,必须是4的倍数。注意这个地址要与你程序配合好，不要乱写。

#define CHIP_UID_ADDRESS                (0x1FFFF7E8)    //修改为你目标芯片的UID所在的地址。注意不同芯片型号不一样。这个要查手册确定

//据配置的顺序修改这个UID顺序列表
#define D0_ID_INDEX     0X4  
#define D1_ID_INDEX     0X8
#define D2_ID_INDEX     0X1
#define D3_ID_INDEX     0X3
#define D4_ID_INDEX     0X0
#define D5_ID_INDEX     0X5
#define D6_ID_INDEX     0XA
#define D7_ID_INDEX     0X7
#define D8_ID_INDEX     0X9
#define D9_ID_INDEX     0X2
#define D10_ID_INDEX    0XB
#define D11_ID_INDEX    0X6

//外部调用这个函数，返回值为true时。说明为盗版，返回值为false时，说明为正版。
extern bool isDaoBan(void);

#endif//uidencypt_user_h                
