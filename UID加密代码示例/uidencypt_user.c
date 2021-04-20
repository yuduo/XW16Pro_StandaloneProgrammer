/************************************
STM32 GD32 UID算法加密代码DEMO。
www.xwopen.com
xuanweikeji.taobao.com
版权所有。
*************************************/


#include "uidencypt_user.h"

/*****************下面的不要修改！！！***********************/

#define ZI_JIE_SHU                      (4)             //STM32/GD32保持为4，不要修改
#define CUN_CHU_CHANG_DU				(4)

static uint32_t Fml_Constant; // 常数
static uint8_t *C;
static uint16_t Fml_CRC16;
static uint8_t D[12];
static uint8_t Result[CUN_CHU_CHANG_DU]={0};
static int32_t const resultLength=CUN_CHU_CHANG_DU;

static uint16_t Formula_CRC16(uint8_t *p,uint8_t len);
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength);

bool isDaoBan(void)
{
        uint8_t* pRightData;
        uint8_t* pUid;
        uint8_t i;
        
        //对常数赋值
        Fml_Constant=CHANG_SHU;
        //C指针指向常数首地址
        C=(uint8_t*)&Fml_Constant;
        
        //指向编程器写入UID算法处理后数据的首地址，用来取编程器的结果
        pRightData=(uint8_t*)CUN_FANG_QI_SHI_DI_ZHI;
        //指向芯片的UID区首地址，用来取芯片的UID值
        pUid=(uint8_t*)CHIP_UID_ADDRESS;
        
        //对D数组按配置赋值
        D[0]=pUid[D0_ID_INDEX];
        D[1]=pUid[D1_ID_INDEX];
        D[2]=pUid[D2_ID_INDEX];
        D[3]=pUid[D3_ID_INDEX];
        D[4]=pUid[D4_ID_INDEX];
        D[5]=pUid[D5_ID_INDEX];
        D[6]=pUid[D6_ID_INDEX];
        D[7]=pUid[D7_ID_INDEX];
        D[8]=pUid[D8_ID_INDEX];
        D[9]=pUid[D9_ID_INDEX];
        D[10]=pUid[D10_ID_INDEX];
        D[11]=pUid[D11_ID_INDEX];
        
        //计算结果
        formula(D,Result,&resultLength);
        //比较结果
        for(i=0;i<ZI_JIE_SHU;i++)
        {
                if(Result[i]!=pRightData[i])
                {
                        //有不一样的结果。返回假
                        return true;
                }
        }
        //
        return false;
}

static uint16_t Formula_CRC16(uint8_t *p,uint8_t len) //
{
        uint8_t i;
		Fml_CRC16 = 0;
        while(len--)
        {
                for(i=0x80; i!=0; i>>=1)
                {
                        if((Fml_CRC16 & 0x8000) != 0)
                        {
                                Fml_CRC16 <<= 1;
                                Fml_CRC16 ^= 0x1021;
                        }
                        else
                        {
                                Fml_CRC16 <<= 1;
                        }
                        if((*p&i)!=0)
                        {
                                Fml_CRC16 ^= 0x1021;
                        }
                }
                p++;
        }
        return Fml_CRC16;
}

#if GONG_SHI_HAO==0
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        Result[0] = C[0];
        Result[1] = C[1];
        Result[2] = C[2];
        Result[3] = C[3];
}
#endif //GONG_SHI_HAO==0

#if GONG_SHI_HAO==1
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        Result[0] = C[0] + D[0];
        Result[1] = C[1] + D[1];
        Result[2] = C[2] + D[2];
        Result[3] = C[3] + D[3];
}
#endif //GONG_SHI_HAO==1

#if GONG_SHI_HAO==2
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        Result[0] = C[0] | D[0];
        Result[1] = C[1] | D[1];
        Result[2] = C[2] | D[2];
        Result[3] = C[3] | D[3];
}
#endif //GONG_SHI_HAO==2

#if GONG_SHI_HAO==3
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        Result[0] = C[0] ^ D[0];
        Result[1] = C[1] ^ D[1];
        Result[2] = C[2] ^ D[2];
        Result[3] = C[3] ^ D[3];
}
#endif //GONG_SHI_HAO==3

#if GONG_SHI_HAO==4
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        Result[0] = C[0] & D[0];
        Result[1] = C[1] & D[1];
        Result[2] = C[2] & D[2];
        Result[3] = C[3] & D[3];
}
#endif //GONG_SHI_HAO==4

#if GONG_SHI_HAO==5
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        Result[0] = C[0] - D[0];
        Result[1] = C[1] - D[1];
        Result[2] = C[2] - D[2];
        Result[3] = C[3] - D[3];
}
#endif //GONG_SHI_HAO==5

#if GONG_SHI_HAO==6
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        Result[0] = C[0] + D[0];
        Result[1] = C[1] - D[1];
        Result[2] = C[2] * D[2];
        Result[3] = C[3] / D[3];
}
#endif //GONG_SHI_HAO==6

#if GONG_SHI_HAO==7
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        Result[0] = C[0] ^ D[0];
        Result[1] = C[1] & D[1];
        Result[2] = C[2] | D[2];
        Result[3] = C[3] % D[3];
}
#endif //GONG_SHI_HAO==7

#if GONG_SHI_HAO==8
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        Result[0] = C[0] + D[0];
        Result[1] = C[1] & D[1];
        Result[2] = C[2] | D[2];
        Result[3] = C[3] - D[3];
}
#endif //GONG_SHI_HAO==8

#if GONG_SHI_HAO==9
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        Result[0] = C[0] + D[0] + D[4];
        Result[1] = C[1] & D[1] + D[5];
        Result[2] = C[2] | D[2] + D[6];
        Result[3] = C[3] - D[3] + D[7];
}
#endif //GONG_SHI_HAO==9

#if GONG_SHI_HAO==10
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        Result[0] = C[0] + D[0] + D[4];
        Result[1] = C[1] & D[1] ^ D[5];
        Result[2] = C[2] | D[2] ^ D[6];
        Result[3] = C[3] - D[3] + D[7];
}
#endif //GONG_SHI_HAO==10

#if GONG_SHI_HAO==11
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        Result[0] = C[0] + D[0] + D[4] + D[8];
        Result[1] = C[1] & D[1] ^ D[5] + D[9];
        Result[2] = C[2] | D[2] ^ D[6] + D[10];
        Result[3] = C[3] - D[3] + D[7] + D[11];
}
#endif //GONG_SHI_HAO==11

#if GONG_SHI_HAO==12
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        Result[0] = C[0] + D[0] - D[4] + D[8];
        Result[1] = C[1] & D[1] ^ D[5] | D[9];
        Result[2] = C[2] | D[2] ^ D[6] ^ D[10];
        Result[3] = C[3] - D[3] + D[7] & D[11];
}
#endif //GONG_SHI_HAO==12

#if GONG_SHI_HAO==13
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        Result[0] = D[0] - D[4] + D[8];
        Result[1] = D[1] ^ D[5] | D[9];
        Result[2] = D[2] ^ D[6] ^ D[10];
        Result[3] = D[3] + D[7] & D[11];
}
#endif //GONG_SHI_HAO==13

#if GONG_SHI_HAO==14
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        Result[0] = D[0] - D[2] + D[3];
        Result[1] = D[4] ^ D[5] | D[6];
        Result[2] = D[7] ^ D[8] ^ D[9];
        Result[3] = D[10] + D[11] ;
}
#endif //GONG_SHI_HAO==14

#if GONG_SHI_HAO==15
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        Result[0] = D[0] - D[2] + D[3] - D[0] + D[2] + D[3];
        Result[1] = C[1];
        Result[2] = C[2];
        Result[3] = C[3];
}
#endif //GONG_SHI_HAO==15

#if GONG_SHI_HAO==16
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        Result[0] = D[0] - D[1] - D[2] + D[3] - D[4] + D[5] + D[6];
        Result[1] = C[1];
        Result[2] = C[2];
        Result[3] = C[3];
}
#endif //GONG_SHI_HAO==16

#if GONG_SHI_HAO==17
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        Result[0] = D[0] - D[1] - D[2] + D[3] - D[4] + D[5] + D[6] + D[7] - D[8] + D[9] - D[10] + D[11] ;
        Result[1] = C[1];
        Result[2] = C[2];
        Result[3] = C[3];
}
#endif //GONG_SHI_HAO==17

#if GONG_SHI_HAO==18
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        Result[0] = D[0] ^ D[1] ^ D[2] ^ D[3] ^ D[4] ^ D[5] ^ D[6] ^ D[7] ^ D[8] ^ D[9] ^ D[10] ^ D[11] ;
        Result[1] = C[1];
        Result[2] = C[2];
        Result[3] = C[3];
}
#endif //GONG_SHI_HAO==18

#if GONG_SHI_HAO==19
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        Result[0] = D[0] | D[1] ^ D[2] & D[3] ^ D[4] ^ D[5] | D[6] ^ D[7] ^ D[8] ^ D[9] ^ D[10] ^ D[11] ;
        Result[1] = C[1];
        Result[2] = C[2];
        Result[3] = C[3];
}
#endif //GONG_SHI_HAO==19

#if GONG_SHI_HAO==20
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        Result[0] = D[0] | D[1] ^ D[2] & D[3] ^ D[4] ^ D[5] | D[6] ^ D[7] ^ D[8] ^ D[9] ^ D[10] ^ D[11] ;
        Result[1] = D[0] - D[1] - D[2] + D[3] - D[4] + D[5] + D[6] + D[7] - D[8] + D[9] - D[10] + D[11] ;
        Result[2] = D[0] | D[1] ^ D[2] & D[3] ^ D[4] ^ D[5] | D[6] ^ D[7] ^ D[8] ^ D[9] ^ D[10] ^ D[11] ;
        Result[3] = D[0] | D[1] ^ D[2] ^ D[3] ^ D[4] ^ D[5] | D[6] ^ D[7] ^ D[8] ^ D[9] ^ D[10] ^ D[11] ;
}
#endif //GONG_SHI_HAO==20

#if GONG_SHI_HAO==21
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        Result[0] = C[0] | D[0] | D[1] ^ D[2] & D[3] ^ D[4] ^ D[5] | D[6] ^ D[7] ^ D[8] ^ D[9] ^ D[10] ^ D[11] ;
        Result[1] = C[0] | D[0] - D[1] - D[2] + D[3] - D[4] + D[5] + D[6] + D[7] - D[8] + D[9] - D[10] + D[11] ;
        Result[2] = C[0] | D[0] | D[1] ^ D[2] & D[3] ^ D[4] ^ D[5] | D[6] ^ D[7] ^ D[8] ^ D[9] ^ D[10] ^ D[11] ;
        Result[3] = C[0] | D[0] | D[1] ^ D[2] ^ D[3] ^ D[4] ^ D[5] | D[6] ^ D[7] ^ D[8] ^ D[9] ^ D[10] ^ D[11] ;
}
#endif //GONG_SHI_HAO==21

#if GONG_SHI_HAO==22
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        Result[0] = C[0] | D[0] | D[1] ^ D[2] & D[3] ^ D[4] ^ D[5] | D[6] ^ D[7] ^ D[8] ^ D[9] ^ D[10] ^ D[11] ;
        Result[1] = C[1] | D[0] - D[1] - D[2] + D[3] - D[4] + D[5] + D[6] + D[7] - D[8] + D[9] - D[10] + D[11] ;
        Result[2] = C[2] | D[0] | D[1] ^ D[2] & D[3] ^ D[4] ^ D[5] | D[6] ^ D[7] ^ D[8] ^ D[9] ^ D[10] ^ D[11] ;
        Result[3] = C[3] | D[0] | D[1] ^ D[2] ^ D[3] ^ D[4] ^ D[5] | D[6] ^ D[7] ^ D[8] ^ D[9] ^ D[10] & D[11] ;
}
#endif //GONG_SHI_HAO==22

#if GONG_SHI_HAO==23
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        Result[0] = C[0] ^ D[0] | D[1] ^ D[2] & D[3] ^ D[4] ^ D[5] | D[6] ^ D[7] ^ D[8] ^ D[9] ^ D[10] ^ D[11] ;
        Result[1] = C[1] ^ D[0] - D[1] - D[2] + D[3] - D[4] + D[5] + D[6] + D[7] - D[8] + D[9] - D[10] + D[11] ;
        Result[2] = C[2] ^ D[0] | D[1] ^ D[2] & D[3] ^ D[4] ^ D[5] | D[6] & D[7] ^ D[8] ^ D[9] ^ D[10] ^ D[11] ;
        Result[3] = C[3] ^ D[0] | D[1] ^ D[2] ^ D[3] ^ D[4] ^ D[5] | D[6] ^ D[7] ^ D[8] ^ D[9] ^ D[10] ^ D[11] ;
}
#endif //GONG_SHI_HAO==23

#if GONG_SHI_HAO==24
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        Result[0] = C[0] & D[0] | D[1] ^ D[2] & D[3] ^ D[4] ^ D[5] | D[6] ^ D[7] ^ D[8] ^ D[9] ^ D[10] ^ D[11] ;
        Result[1] = C[1] & D[0] - D[1] - D[2] + D[3] - D[4] + D[5] + D[6] + D[7] - D[8] + D[9] - D[10] + D[11] ;
        Result[2] = C[2] & D[0] | D[1] ^ D[2] & D[3] ^ D[4] ^ D[5] | D[6] ^ D[7] & D[8] ^ D[9] ^ D[10] ^ D[11] ;
        Result[3] = C[3] & D[0] | D[1] ^ D[2] ^ D[3] ^ D[4] ^ D[5] | D[6] ^ D[7] ^ D[8] ^ D[9] ^ D[10] ^ D[11] ;
}
#endif //GONG_SHI_HAO==24

#if GONG_SHI_HAO==25
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        Result[0] = C[0] & D[0] | D[1] ^ D[2] & D[3] ^ D[4] ^ D[5] | D[6] ^ D[7] ^ D[8] & D[9] ^ D[10] ^ D[11] ;
        Result[1] = C[1];
        Result[2] = C[2];
        Result[3] = C[3];
}
#endif //GONG_SHI_HAO==25

#if GONG_SHI_HAO==26
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        Result[0] = C[0] & D[0] | D[1] ^ D[2] & D[3] ^ D[4] ^ D[5] | D[6] | D[7] ^ D[8] | D[9] ^ D[10] ^ D[11] ;
        Result[1] = C[1] & D[0] ;
        Result[2] = C[2] & D[2] ;
        Result[3] = C[3] & D[3] ;
}
#endif //GONG_SHI_HAO==26

#if GONG_SHI_HAO==27
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        Result[0] = C[0] & D[0] | D[1] ^ D[2] & D[3] ^ D[4] ^ D[5] | D[6] | D[7] ^ D[8] | D[9] ^ D[10] ^ D[11] ;
        Result[1] = C[1];
        Result[2] = C[2];
        Result[3] = C[3];
}
#endif //GONG_SHI_HAO==27

#if GONG_SHI_HAO==28
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        Result[0] = C[0] & D[0] | D[1] ^ D[2] & D[3] ^ D[4] ^ D[5] | D[6] | D[7] ^ D[8] | D[9] ^ D[10] ^ D[11] ;
        Result[1] = C[1] + D[3] ^ D[4] ^ D[5] | D[6] | D[7];
        Result[2] = C[2];
        Result[3] = C[3];
}
#endif //GONG_SHI_HAO==28

#if GONG_SHI_HAO==29
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        Result[0] = C[0] + D[0] + D[1] + D[2] + D[3] + D[4] + D[5] + D[6] + D[7] + D[8] + D[9] + D[10] + D[11] ;
        Result[1] = C[1];
        Result[2] = C[2];
        Result[3] = C[3];
}
#endif //GONG_SHI_HAO==29

#if GONG_SHI_HAO==30
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        Result[0] = C[0] ^ D[0] ^ D[1] ^ D[2] ^ D[3] ^ D[4] ^ D[5] ^ D[6] ^ D[7] ^ D[8] ^ D[9] ^ D[10] ^ D[11] ;
        Result[1] = C[1];
        Result[2] = C[2];
        Result[3] = C[3];
}
#endif //GONG_SHI_HAO==30

#if GONG_SHI_HAO==31
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        Result[0] = C[0] ^ D[0] | D[1] ^ D[2] & D[3] ^ D[4] | D[5] ^ D[6] & D[7] ^ D[8] ^ D[9] ^ D[10] ^ D[11] ;
        Result[1] = C[1];
        Result[2] = C[2];
        Result[3] = C[3];
}
#endif //GONG_SHI_HAO==31

#if GONG_SHI_HAO==32
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        Result[0] = C[0] ^ D[0] | D[1] ^ D[2] & D[3] ^ D[4] | D[5] ^ D[6] & D[7] ^ D[8] ^ D[9] ^ D[10] ^ D[11] ;
        Result[1] = C[1] ^ D[0] ^ D[1] ^ D[2] ^ D[3] ^ D[4] ^ D[5] ^ D[6] ^ D[7] ^ D[8] ^ D[9] ^ D[10] ^ D[11] ;
        Result[2] = C[2];
        Result[3] = C[3];
}
#endif //GONG_SHI_HAO==32

#if GONG_SHI_HAO==33
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        Result[0] = C[0] ^ D[0] | D[1];
        Result[1] = C[1] ^ D[0] ^ D[1];
        Result[2] = C[2];
        Result[3] = C[3];
}
#endif //GONG_SHI_HAO==33

#if GONG_SHI_HAO==34
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        Result[0] = C[0] ^ D[0] | D[1] ^ D[2];
        Result[1] = C[1] ^ D[0] ^ D[1] ^ D[2];
        Result[2] = C[2];
        Result[3] = C[3];
}
#endif //GONG_SHI_HAO==34

#if GONG_SHI_HAO==35
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        Result[0] = C[0] ^ D[0] | D[1] ^ D[2] & D[3] ;
        Result[1] = C[1] ^ D[0] ^ D[1] ^ D[2] ^ D[3] ;
        Result[2] = C[2];
        Result[3] = C[3];
}
#endif //GONG_SHI_HAO==35

#if GONG_SHI_HAO==36
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        Result[0] = C[0] ^ D[0] | D[1] ^ D[2] & D[3] ^ D[4] | D[5] ;
        Result[1] = C[1] ^ D[0] ^ D[1] ^ D[2] ^ D[3] ^ D[4] ^ D[5] ;
        Result[2] = C[2];
        Result[3] = C[3];
}
#endif //GONG_SHI_HAO==36

#if GONG_SHI_HAO==37
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        Result[0] = C[0] ^ D[0] | D[1] ^ D[2] & D[3] ^ D[4] | D[5] ;
        Result[1] = C[1] ^ D[6] ^ D[7] ^ D[8] ^ D[9] ^ D[10] ^ D[11] ;
        Result[2] = C[2];
        Result[3] = C[3];
}
#endif //GONG_SHI_HAO==37

#if GONG_SHI_HAO==38
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        Result[0] = C[0] ^ D[0] | D[1] ^ D[2] & D[3] ^ D[4] | D[5] ;
        Result[1] = C[1] ^ D[6] ^ D[7] ^ D[8] ^ D[9] ^ D[10] ^ D[11] ;
        Result[2] = C[2] ^ D[6] | D[1] ^ D[7] & D[3] ^ D[9] | D[5] ;
        Result[3] = C[3];
}
#endif //GONG_SHI_HAO==38

#if GONG_SHI_HAO==39
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        Result[0] = C[0] ^ D[0] | D[1] ^ D[2] & D[3] ^ D[4] | D[5] ;
        Result[1] = C[1] ^ D[6] ^ D[7] ^ D[8] ^ D[9] ^ D[10] ^ D[11] ;
        Result[2] = C[2] ^ D[6] | D[1] ^ D[7] & D[3] ^ D[9] | D[5] ;
        Result[3] = C[3] ^ D[8] ^ D[7] ^ D[8] ^ D[2] ^ D[10] ^ D[1] ;
}
#endif //GONG_SHI_HAO==39

#if GONG_SHI_HAO==40
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        Result[0] = C[0] + D[0] - D[1];
        Result[1] = C[1] - D[0] + D[1];
        Result[2] = C[2];
        Result[3] = C[3];
}
#endif //GONG_SHI_HAO==40

#if GONG_SHI_HAO==41
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        Result[0] = C[0] + D[0] + D[1] + D[2];
        Result[1] = C[1] + D[5] + D[6] + D[7];
        Result[2] = C[2];
        Result[3] = C[3];
}
#endif //GONG_SHI_HAO==41

#if GONG_SHI_HAO==42
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        Result[0] = C[0] + D[0] + D[1] + D[2] + D[8] + D[9];
        Result[1] = C[1] + D[5] + D[6] + D[7] + D[10] + D[11];
        Result[2] = C[2];
        Result[3] = C[3];
}
#endif //GONG_SHI_HAO==42

#if GONG_SHI_HAO==43
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        Result[0] = C[0] + D[0] - D[1] + D[2] - D[8] + D[9];
        Result[1] = C[1] + D[5] - D[6] + D[7] - D[10] + D[11];
        Result[2] = C[2];
        Result[3] = C[3];
}
#endif //GONG_SHI_HAO==43

#if GONG_SHI_HAO==44
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        Result[0] = C[0] + D[0] - D[1] | D[2] - D[8] + D[9];
        Result[1] = C[1] + D[5] - D[6] | D[7] - D[10] + D[11];
        Result[2] = C[2];
        Result[3] = C[3];
}
#endif //GONG_SHI_HAO==44

#if GONG_SHI_HAO==45
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        Result[0] = C[0] + D[0] - D[1] | D[2] ^ D[8] & D[9];
        Result[1] = C[1] + D[5] - D[6] | D[7] ^ D[10] & D[11];
        Result[2] = C[2];
        Result[3] = C[3];
}
#endif //GONG_SHI_HAO==45

#if GONG_SHI_HAO==46
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        Result[0] = D[0] + D[0] + D[1] + D[2];
        Result[1] = D[1] + D[5] + D[6] + D[7];
        Result[2] = D[2];
        Result[3] = D[3];
}
#endif //GONG_SHI_HAO==46

#if GONG_SHI_HAO==47
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        Result[0] = D[0] + D[0] + D[1] + D[2] + D[8] + D[9];
        Result[1] = D[1] + D[5] + D[6] + D[7] + D[10] + D[11];
        Result[2] = D[2];
        Result[3] = D[3];
}
#endif //GONG_SHI_HAO==47

#if GONG_SHI_HAO==48
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        Result[0] = D[0] + D[0] - D[1] + D[2] - D[8] + D[9];
        Result[1] = D[1] + D[5] - D[6] + D[7] - D[10] + D[11];
        Result[2] = D[2];
        Result[3] = D[3];
}
#endif //GONG_SHI_HAO==48

#if GONG_SHI_HAO==49
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        Result[0] = D[0] + D[0] - D[1] | D[2] - D[8] + D[9];
        Result[1] = D[1] + D[5] - D[6] | D[7] - D[10] + D[11];
        Result[2] = D[2];
        Result[3] = D[3];
}
#endif //GONG_SHI_HAO==49

#if GONG_SHI_HAO==50
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        Result[0] = D[0] + D[0] - D[1] | D[2] ^ D[8] & D[9];
        Result[1] = D[1] + D[5] - D[6] | D[7] ^ D[10] & D[11];
        Result[2] = D[2];
        Result[3] = D[3];
}
#endif //GONG_SHI_HAO==50

#if GONG_SHI_HAO==51
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        uint32_t *d,a;
        d=(uint32_t*)D;
        a = d[0] ^ d[1] ^ d[2];
        d = (uint32_t*)Result;
        *d = a;
}
#endif //GONG_SHI_HAO==51

#if GONG_SHI_HAO==52
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        uint32_t *d,a;
        d=(uint32_t*)D;
        a = d[0] ^ d[1] | d[2];
        d = (uint32_t*)Result;
        *d = a;
}
#endif //GONG_SHI_HAO==52

#if GONG_SHI_HAO==53
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        uint32_t *d,a;
        d=(uint32_t*)D;
        a = d[0] & d[1] | d[2];
        d = (uint32_t*)Result;
        *d = a;
}
#endif //GONG_SHI_HAO==53

#if GONG_SHI_HAO==54
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        uint32_t *d,a;
        d=(uint32_t*)D;
        a = Fml_Constant + d[0] & d[1] | d[2];
        d = (uint32_t*)Result;
        *d = a;
}
#endif //GONG_SHI_HAO==54

#if GONG_SHI_HAO==55
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        uint32_t *d,a;
        d=(uint32_t*)D;
        a = Fml_Constant ^ d[0] ^ d[1] ^ d[2];
        d = (uint32_t*)Result;
        *d = a;
}
#endif //GONG_SHI_HAO==55

#if GONG_SHI_HAO==56
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        uint32_t *d,a;
        d=(uint32_t*)D;
        a = Fml_Constant ^ d[0] | d[1] ^ d[2];
        d = (uint32_t*)Result;
        *d = a;
}
#endif //GONG_SHI_HAO==56

#if GONG_SHI_HAO==57
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        uint32_t *d,a;
        d=(uint32_t*)D;
        a = Fml_Constant ^ d[0] | d[1] ^ d[2] + Fml_Constant;
        d = (uint32_t*)Result;
        *d = a;
}
#endif //GONG_SHI_HAO==57

#if GONG_SHI_HAO==58
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        uint32_t *d,a;
        d=(uint32_t*)D;
        a = Fml_Constant - d[0] - d[1] - d[2] + Fml_Constant;
        d = (uint32_t*)Result;
        *d = a;
}
#endif //GONG_SHI_HAO==58

#if GONG_SHI_HAO==59
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        uint32_t *d,a;
        d=(uint32_t*)D;
        a = Fml_Constant + d[0] + d[1] + d[2] + Fml_Constant;
        d = (uint32_t*)Result;
        *d = a;
}
#endif //GONG_SHI_HAO==59

#if GONG_SHI_HAO==60
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        Result[0] = C[0] + D[0] - D[4] + D[8] + D[2];
        Result[1] = C[1] & D[1] ^ D[5] | D[9];
        Result[2] = C[2] | D[2] ^ D[6] ^ D[10];
        Result[3] = C[3] - D[3] + D[7];
}
#endif //GONG_SHI_HAO==60

#if GONG_SHI_HAO==61
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        Result[0] = C[0]+ D[8];
        Result[1] = C[1] & D[1] ^ D[5] | D[9];
        Result[2] = C[2] | D[2] ^ D[6] ^ D[10];
        Result[3] = C[3] & D[11];
}
#endif //GONG_SHI_HAO==61

#if GONG_SHI_HAO==62
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        Result[0] = C[0] + D[0] - D[4] + D[8];
        Result[1] = C[1] & D[1] ^ D[5] | D[9];
        Result[2] = C[2] | D[2] ^ D[6] ^ D[10] ^ D[5] ;
        Result[3] = C[3] - D[3] + D[7] & D[11] ^ D[5] ;
}
#endif //GONG_SHI_HAO==62

#if GONG_SHI_HAO==63
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        Result[0] = C[0] + D[0] - D[4] + D[8]^ D[6];
        Result[1] = C[1] & D[1] ^ D[5] | D[9]^ D[6];
        Result[2] = C[2] | D[2] ^ D[6] ^ D[10] ^ D[5] ;
        Result[3] = C[3] - D[3] + D[7] & D[11] ^ D[5] ;
}
#endif //GONG_SHI_HAO==63

#if GONG_SHI_HAO==64
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        Result[0] = C[0] + D[0] - D[4] + D[8]^ D[6];
        Result[1] = C[1] & D[1] ^ D[5] | D[9]^ D[6];
        Result[2] = C[2] | D[2] ^ D[6] ^ D[10] ^ D[5] ^ C[1];
        Result[3] = C[3] - D[3] + D[7] & D[11] ;
}
#endif //GONG_SHI_HAO==64

#if GONG_SHI_HAO==65
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        Result[0] = C[0] ^ D[0] | D[1] ^ D[2] & D[3] ^ D[4] ^ D[5] | D[6] ^ D[7] ^ D[8] ^ D[9] ^ D[10] ^ D[11] ;
        Result[1] = C[1] ^ D[0] - D[1] - D[2] | D[6] + D[7] - D[8] + D[9] - D[10] + D[11] ;
        Result[2] = C[2] ^ D[0] | D[1] ^ D[2] & D[3] ^ D[4] ^ D[5] | D[6] ^ D[7] ^ D[8] ^ D[9] ^ D[10] ^ D[11] ;
        Result[3] = C[3] ^ D[0] | D[1] ^ D[2] ^ D[3] ^ D[4] ^ D[5];
}
#endif //GONG_SHI_HAO==65

#if GONG_SHI_HAO==66
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        Result[0] = C[0] ^ D[7] ^ D[8] ^ D[9] ^ D[10] ^ D[11] ;
        Result[1] = C[1] ^ D[0] - D[1] - D[2] + D[3] - D[4] + D[5] + D[6] ;
        Result[2] = C[2] ^ D[0] | D[1] ^ D[2] & D[3] ^ D[4] ^ D[5] | D[6] ^ D[7] ^ D[8] ^ D[9] ^ D[10] ^ D[11] ;
        Result[3] = C[3] ^ D[0] | D[4] ^ D[5] | D[6] ^ D[7] ^ D[8] ^ D[9] ^ D[10] ^ D[11] ;
}
#endif //GONG_SHI_HAO==66

#if GONG_SHI_HAO==67
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        Result[0] = C[0] ^ D[0] | D[1] ^ D[2] & D[3] ^ D[4] ^ D[5] | D[6] ^ D[7] ^ D[8] ^ D[9] ^ D[10] ^ D[11] ;
        Result[1] = C[1] ^ D[0];
        Result[2] = C[2] ^ D[0] | D[1] ^ D[2] & D[3] ^ D[4] ^ D[5] | D[6] ^ D[7] ^ D[8] ^ D[9] ^ D[10] ^ D[11] ;
        Result[3] = C[3] ^ D[11] ;
}
#endif //GONG_SHI_HAO==67

#if GONG_SHI_HAO==68
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        Result[0] = C[0] ^ D[0] ;
        Result[1] = C[1] ^ D[0] - D[1] - D[2] + D[3] - D[4] + D[5] + D[6] + D[7] - D[8] + D[9] - D[10] + D[11] ;
        Result[2] = C[2] ^ D[0] | D[1] ^ D[2] & D[3] ^ D[9] ^ D[10] ^ D[11] ;
        Result[3] = C[3] ^ D[0] | D[1] & D[11] ;
}
#endif //GONG_SHI_HAO==68

#if GONG_SHI_HAO==69
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        Result[0] = C[0] ^ D[0] | D[1] ^ D[2] & D[3] ^ D[4] ^ D[5] | D[6] ^ D[7] ^ D[8] ^ D[9] ^ D[10] ^ D[11] ;
        Result[1] = C[1] + D[11] ;
        Result[2] = C[2] ^ D[0] | D[1] ^ D[4] ^ D[5] | D[6] ^ D[7] ^ D[8] ^ D[9] ^ D[10] ^ D[11] ;
        Result[3] = C[3] ^ D[3] ^ D[4] ^ D[5] | D[6] ^ D[7] ^ D[8] ^ D[9] ^ D[10] ^ D[11] ;
}
#endif //GONG_SHI_HAO==69

#if GONG_SHI_HAO==70
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        Result[0] = D[0] | D[1] ^ D[2] & D[3] ^ D[4] ^ D[5] | D[6] ^ D[7] ^ D[8] ^ D[9] ^ D[10] ^ D[11] ;
        Result[1] = D[0] - D[1] ;
        Result[2] = D[0] | D[1] ;
        Result[3] = D[0] | D[1] ^ D[2];
}
#endif //GONG_SHI_HAO==70

#if GONG_SHI_HAO==71
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        Result[0] = D[0] | D[10] ^ D[11] ;
        Result[1] = D[0] - D[7] - D[8] + D[9] - D[10] + D[11] ;
        Result[2] = D[0] | D[1] ^ D[2] & D[3] ^ D[4] ^ D[5] | D[6] ^ D[7] ^ D[8] ^ D[9] ^ D[10] ^ D[11] ;
        Result[3] = D[0] | D[1] ^ D[2] ^ D[7] ^ D[8] ^ D[9] ^ D[10] ^ D[11] ;
}
#endif //GONG_SHI_HAO==71

#if GONG_SHI_HAO==72
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        Result[0] = D[0] | D[1] ^ D[2] ^ D[4] ^ D[5] | D[6] ^ D[7] ^ D[8] ^ D[9] ^ D[10] ^ D[11] ;
        Result[1] = D[0] - D[1] - D[2] + D[3] - D[4] + D[5] + D[6] + D[7] - D[8] + D[9] - D[10] + D[11] ;
        Result[2] = D[0] | D[1] ^ D[2] & D[3] ^ D[4] ^ D[10] ^ D[11] ;
        Result[3] = D[0] | D[1] ^ D[2] ^ D[3] ^ D[4] ^ D[5] | D[6] ^ D[7] ^ D[8] ^ D[9] ^ D[10] ^ D[11] ;
}
#endif //GONG_SHI_HAO==72

#if GONG_SHI_HAO==73
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        Result[0] = D[0] | D[1] ^ D[2] & D[3] ^ D[4] ^ D[5] | D[6] ^ D[7] ^ D[8] ^ D[9] ^ D[10] ^ D[11] ;
        Result[1] = D[0] - D[1] - D[2] + D[3] - D[4] + D[5] + D[6] + D[7] - D[8] + D[9] - D[10] + D[11] ;
        Result[2] = D[0] ^ D[11] ;
        Result[3] = D[0] | D[9] ;
}
#endif //GONG_SHI_HAO==73

#if GONG_SHI_HAO==74
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        Result[0] = D[0] | D[1] ;
        Result[1] = D[0] + D[6] + D[7] - D[8] + D[9] - D[10] + D[11] ;
        Result[2] = D[0] | D[1] ^ D[2] & D[3] ^ D[4];
        Result[3] = D[0] | D[1] ^ D[2] ^ D[3] ^ D[4] ^ D[5] | D[6] ^ D[7] ^ D[8] ^ D[9] ^ D[10] ^ D[11] ;
}
#endif //GONG_SHI_HAO==74

#if GONG_SHI_HAO==75
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        Result[0] = D[0] | D[1] ^ D[2] & D[3] ^ D[4] ^ D[5] | D[6] ^ D[7] ^ D[8] ^ D[9] ^ D[10] ^ D[11] ;
        Result[1] = D[0] - D[1] - 3;
        Result[2] = D[0] | D[1] ^ D[2] & D[3] ^ D[4] ^ D[5] ^ D[9] ^ D[10] ^ D[11] ;
        Result[3] = D[0] | D[1] ^ D[2];
}
#endif //GONG_SHI_HAO==75

#if GONG_SHI_HAO==76
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        Result[0] = C[0] ^ D[0] | D[1] ^ D[2] & D[3] ^ D[4] | D[5] ^ D[10] ;
        Result[1] = C[1] ^ D[6] ^ D[7] ^ D[8] ^ D[9] ^ D[10] ^ D[11] ^ D[10];
        Result[2] = C[2] ^ D[6] | D[1] ^ D[7] & D[3] ^ D[9] | D[5] ^ D[10] ;
        Result[3] = C[3] ^ D[8] ^ D[7] ^ D[8] ^ D[2] ^ D[10] ^ D[1] ^ D[10] ;
}
#endif //GONG_SHI_HAO==76

#if GONG_SHI_HAO==77
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        Result[0] = C[0] ^ D[0] | D[1] ^ D[2] & D[3] ^ D[4] | D[5] ^ D[10] ;
        Result[1] = C[1] ^ D[10];
        Result[2] = C[2] ^ D[6] | D[1] ^ D[7] & D[3] ^ D[9] | D[5] ^ D[10] ;
        Result[3] = C[3] ^ D[8] ^ D[7] ^ D[8] ^ D[2] ^ D[10] ^ D[1] ^ D[10] ;
}
#endif //GONG_SHI_HAO==77

#if GONG_SHI_HAO==78
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        Result[0] = C[0] ^ D[0] | D[1] & D[2] & D[3] ^ D[4] | D[5] ^ D[10] ;
        Result[1] = C[1] ^ D[6] ^ D[7] ^ D[8] ^ D[9] ^ D[10] ^ D[11] ^ D[10];
        Result[2] = C[2] ^ D[10] ;
        Result[3] = C[3] ^ D[8] ^ D[7] ^ D[8] ^ D[2] ^ D[10] ^ D[1] ^ D[10] ;
}
#endif //GONG_SHI_HAO==78

#if GONG_SHI_HAO==79
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        Result[0] = C[0] ^ D[0] | D[1] ^ D[2] & D[3] ^ D[4] | D[5] ^ D[10] ;
        Result[1] = C[1] ^ D[6] ^ D[7] ^ D[8] ^ D[9] ^ D[10] ^ D[11] ^ D[10];
        Result[2] = C[2] ^ D[10] ;
        Result[3] = C[3] ^ D[8] | D[10] ;
}
#endif //GONG_SHI_HAO==79

#if GONG_SHI_HAO==80
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        Result[0] = C[0] ^ D[0] | D[1] ^ D[2] & D[3] ^ D[4] | D[5] ^ D[10] ;
        Result[1] = C[1] ^ D[10] ^ D[11] ^ D[10];
        Result[2] = C[2] ^ D[6] | D[1] ^ D[7] & D[3] ^ D[2] | D[5] ^ D[10] ;
        Result[3] = C[3] ^ D[8] ^ D[0] ^ D[8] ^ D[2] ^ D[6] ^ D[1] ^ D[10] ;
}
#endif //GONG_SHI_HAO==80

#if GONG_SHI_HAO==81
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        Result[0] = C[0] ^ D[0] | D[1] ^ D[2] & D[3] ^ D[4] | D[5] ^ D[7] ;
        Result[1] = C[1] ^ D[2];
        Result[2] = C[2] ^ D[6] | D[1] ^ D[7] & D[3] ^ D[2] | D[5] ^ D[10] ;
        Result[3] = C[3] ^ D[8] ^ D[11] ^ D[8] ^ D[2] ^ D[6] ^ D[1] ^ D[10] ;
}
#endif //GONG_SHI_HAO==81

#if GONG_SHI_HAO==82
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        Result[0] = D[0] + D[0] - D[1] + D[2] - D[8] + D[9] + D[8] + D[6] ;
        Result[1] = D[1] + D[5] - D[6] + D[7] - D[10];
        Result[2] = D[2];
        Result[3] = D[3];
}
#endif //GONG_SHI_HAO==82

#if GONG_SHI_HAO==83
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        Result[0] = C[0] + D[0] - D[1] | D[2] ^ D[8] & D[9];
        Result[1] = C[1] + D[5] - D[6] | D[7] ^ D[10] & D[11];
        Result[2] = C[2] + D[4];
        Result[3] = C[3] + D[3];
}
#endif //GONG_SHI_HAO==83

#if GONG_SHI_HAO==84
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        Result[0] = C[0] + D[0] - D[1] | D[2] ^ D[8] & D[9] ^ D[8];
        Result[1] = C[1] + D[5] - D[6] | D[7] ^ D[10] & D[11];
        Result[2] = C[2] + D[4] ^ D[8];
        Result[3] = C[3] + D[3];
}
#endif //GONG_SHI_HAO==84

#if GONG_SHI_HAO==85
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        Result[0] = C[0] + D[0] | D[2] ^ D[8] & D[9] ^ D[8];
        Result[1] = C[1] + D[5] - D[6] | D[7] ^ D[10] & D[11];
        Result[2] = C[2] + D[4];
        Result[3] = C[3] + D[3]- D[1] ^ D[8] ;
}
#endif //GONG_SHI_HAO==85

#if GONG_SHI_HAO==86
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        Result[0] = D[0] ;
        Result[1] = D[1] ^ D[5] | D[9] - D[4];
        Result[2] = D[2] ^ D[6] ^ D[10];
        Result[3] = D[3] + D[8] + D[7] & D[11];
}
#endif //GONG_SHI_HAO==86

#if GONG_SHI_HAO==87
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        Result[0] = D[0] - D[4] + D[8] ^ D[10] & D[11];
        Result[1] = D[1] ^ D[5] | D[9];
        Result[2] = D[2] ^ D[6];
        Result[3] = D[3] + D[7];
}
#endif //GONG_SHI_HAO==87

#if GONG_SHI_HAO==88
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        Result[0] = D[0] ^ D[6] - D[4] + D[8];
        Result[1] = D[1] | D[9];
        Result[2] = D[2] ^ D[10];
        Result[3] = D[3] + D[7] & D[11]^ D[5];
}
#endif //GONG_SHI_HAO==88

#if GONG_SHI_HAO==89
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        Result[0] = C[0] + D[4] + D[8];
        Result[1] = C[1] ^ D[5] + D[9];
        Result[2] = C[2] | D[2] ^ D[6] + D[10];
        Result[3] = C[3] - D[3] + D[7] + D[11] + D[0] & D[1] ;
}
#endif //GONG_SHI_HAO==89

#if GONG_SHI_HAO==90
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        Result[0] = C[0] + D[0] + D[4] + D[8] - D[3];
        Result[1] = C[1] & D[1] ^ D[5] ;
        Result[2] = C[2] | D[2] ^ D[6] + D[10];
        Result[3] = C[3] + D[7] + D[11] + D[9];
}
#endif //GONG_SHI_HAO==90

#if GONG_SHI_HAO==91
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        Result[0] = C[0] + D[0] + D[4] + D[8];
        Result[1] = C[1] + D[9];
        Result[2] = C[2] ^ D[6] + D[10];
        Result[3] = C[3] - D[3] + D[7] + D[11]| D[2] ^ D[5] & D[1];
}
#endif //GONG_SHI_HAO==91

#if GONG_SHI_HAO==92
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        Result[0] = C[0] + D[0] + D[4] + D[8] - D[3] + D[7];
        Result[1] = C[1] & D[1] ^ D[5];
        Result[2] = C[2] | D[2] ^ D[6];
        Result[3] = C[3] + D[11] + D[9] + D[10];
}
#endif //GONG_SHI_HAO==92

#if GONG_SHI_HAO==93
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        Result[0] = C[0] + D[0] + D[4] + D[8];
        Result[1] = D[1] ^ D[5] + D[9];
        Result[2] = C[2] | D[2] ^ D[6] + D[10];
        Result[3] = C[3] - D[3] + D[7] + D[11] & C[1];
}
#endif //GONG_SHI_HAO==93

#if GONG_SHI_HAO==94
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        Result[0] = D[0] + D[4] + D[8];
        Result[1] = C[1] & D[1] ^ D[5] + D[9];
        Result[2] = C[2] | D[2] ^ D[6] + D[10] + C[0];
        Result[3] = C[3] - D[3] + D[7] + D[11];
}
#endif //GONG_SHI_HAO==94

#if GONG_SHI_HAO==95
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        Result[0] = C[0] + D[0] + D[4] + D[8] ^ C[1] & D[1] ;
        Result[1] = D[5] + D[9];
        Result[2] = C[2] | D[2] ^ D[6] + D[10];
        Result[3] = C[3] - D[3] + D[7] + D[11];
}
#endif //GONG_SHI_HAO==95

#if GONG_SHI_HAO==96
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        Result[0] = C[0] + D[0] + D[4] + D[8] ^ C[3];
        Result[1] = C[1] & D[1] ^ D[5] + D[9] ^ C[3];
        Result[2] = C[2] | D[2] ^ D[6] + D[10];
        Result[3] = C[3] - D[3] + D[7] + D[11];
}
#endif //GONG_SHI_HAO==96

#if GONG_SHI_HAO==97
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        Result[0] = C[0] + D[0] + D[4] + D[8] ^ C[3];
        Result[1] = C[1] & D[1] ^ D[5] + D[9] ^ C[3];
        Result[2] = C[2] | D[2] ^ D[6] + D[10];
        Result[3] = C[3] - D[3] + D[7] + D[11] ^ D[6];
}
#endif //GONG_SHI_HAO==97

#if GONG_SHI_HAO==98
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        Result[0] = C[0] + D[0] + D[4] + D[8] ^ C[3] & D[1] | D[2] ;
        Result[1] = C[1] & D[1] ^ D[5] + D[9] ^ C[3];
        Result[2] = C[2]^ D[6] + D[10];
        Result[3] = C[3] - D[3] + D[7] + D[11] ^ D[6];
}
#endif //GONG_SHI_HAO==98

#if GONG_SHI_HAO==99
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        Result[0] = C[0] ^ D[0] | D[1] ^ D[2] & D[3] ^ D[4] | D[5] ;
        Result[1] = C[1] ^ D[6] - D[9] ^ D[10] ^ D[11] ;
        Result[2] = C[2] ^ D[6] | D[1] ^ D[7] & D[3] ^ D[9] | D[5] ;
        Result[3] = C[3] ^ D[7] ^ D[8] ^ 9;
}
#endif //GONG_SHI_HAO==99

#if GONG_SHI_HAO==100
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        Result[0] = C[0] ^ D[0];
        Result[1] = C[1] ^ D[6] ^ D[7] ^ D[8] ^ D[9] ^ D[10] ^ D[11] ;
        Result[2] = C[2] ^ D[4] ;
        Result[3] = C[3] ^ D[2] ^ D[1];
}
#endif //GONG_SHI_HAO==100

#if GONG_SHI_HAO==101
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        uint8_t *crc;
        uint16_t dat;
        crc = (uint8_t*)&dat;
        Fml_CRC16 = 0;
        dat = Formula_CRC16(D,12);
        Result[0] = crc[0];
        Result[1] = crc[1];
        Result[2] = C[2];
        Result[3] = C[3];
}
#endif //GONG_SHI_HAO==101

#if GONG_SHI_HAO==102
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        uint8_t *crc;
        uint16_t dat;
        crc = (uint8_t*)&dat;
        Fml_CRC16 = 0;
        dat = Formula_CRC16(D,12);
        Result[0] = C[0] ^ crc[0];
        Result[1] = C[1] ^ crc[1];
        Result[2] = C[2] ^ crc[1];
        Result[3] = C[3] ^ crc[0];
}
#endif //GONG_SHI_HAO==102

#if GONG_SHI_HAO==103
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        uint8_t *crc;
        uint16_t dat;
        crc = (uint8_t*)&dat;
        Fml_CRC16 = 0;
        dat = Formula_CRC16(D,12);
        Result[0] = C[0] ^ crc[0];
        Result[1] = C[1] ^ crc[1];
        Result[2] = C[2];
        Result[3] = C[3];
}
#endif //GONG_SHI_HAO==103

#if GONG_SHI_HAO==104
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        uint8_t *crc;
        uint16_t dat;
        crc = (uint8_t*)&dat;
        Fml_CRC16 = 0;
        dat = Formula_CRC16(D,12);
        Result[0] = C[0] ^ C[3] ^ crc[0];
        Result[1] = C[1] ^ C[2] ^ crc[1];
        Result[2] = C[2];
        Result[3] = C[3];
}
#endif //GONG_SHI_HAO==104

#if GONG_SHI_HAO==105
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        uint8_t *crc;
        uint16_t dat;
        crc = (uint8_t*)&dat;
        Fml_CRC16 = 0;
        dat = Formula_CRC16(D,10);
        Result[0] = C[0] ^ C[3] ^ crc[0];
        Result[1] = C[1] ^ C[2] ^ crc[1];
        Result[2] = C[2] ^ D[10] ;
        Result[3] = C[3] ^ D[11] ;
}
#endif //GONG_SHI_HAO==105

#if GONG_SHI_HAO==106
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        uint8_t *crc;
        uint16_t dat;
        crc = (uint8_t*)&dat;
        Fml_CRC16 = 0;
        dat = Formula_CRC16(D,6);
        Result[0] = C[0] ^ D[6] ^ crc[0];
        Result[1] = C[1] ^ D[7] ^ crc[1];
        Result[2] = C[2] ^ D[8] ^ D[10] ^ Result[0];
        Result[3] = C[3] ^ D[9] ^ D[11] ^ Result[1];
}
#endif //GONG_SHI_HAO==106

#if GONG_SHI_HAO==107
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        uint8_t *crc;
        uint16_t dat;
        crc = (uint8_t*)&dat;
        Fml_CRC16 = 0;
        dat = Formula_CRC16(D,12);
        Result[0] = C[0] ^ crc[0] ^ crc[1];
        Result[1] = C[1];
        Result[2] = C[2];
        Result[3] = C[3];
}
#endif //GONG_SHI_HAO==107

#if GONG_SHI_HAO==108
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        uint8_t *crc;
        uint16_t dat;
        crc = (uint8_t*)&dat;
        Fml_CRC16 = 0;
        dat = Formula_CRC16(D,12);
        Result[0] = crc[0] ^ crc[1];
        Result[1] = C[1];
        Result[2] = C[2];
        Result[3] = C[3];
}
#endif //GONG_SHI_HAO==108

#if GONG_SHI_HAO==109
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        uint8_t *crc;
        uint16_t dat;
        crc = (uint8_t*)&dat;
        Fml_CRC16 = 0;
        dat = Formula_CRC16(D,6);
        Result[0] = crc[0];
        Result[1] = crc[1];
        Result[2] = C[2] ^ D[8] ^ D[10] ^ D[7]^ D[6] ;
        Result[3] = C[3] ^ D[9] ^ D[11] ;
}
#endif //GONG_SHI_HAO==109

#if GONG_SHI_HAO==110
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        uint8_t *crc;
        uint16_t dat;
        crc = (uint8_t*)&dat;
        Fml_CRC16 = 0;
        dat = Formula_CRC16(D,10);
        Result[0] = crc[0] + C[3];
        Result[1] = crc[1] + C[2] ;
        Result[2] = C[2] ^ D[8] ^ D[10] ^ D[7] ^ D[6] ;
        Result[3] = C[3] ^ D[9] ^ D[11] ;
}
#endif //GONG_SHI_HAO==110

#if GONG_SHI_HAO==111
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        uint8_t *crc;
        uint16_t dat;
        crc = (uint8_t*)&dat;
        Fml_CRC16 = 0;
        dat = Formula_CRC16(D,10);
        Result[0] = crc[0];
        Result[1] = crc[1];
        Result[2] = crc[1] | C[2] ^ D[8] ^ D[10] ^ D[7] ^ D[6] ;
        Result[3] = crc[0] ^ D[9] ^ D[11] ;
}
#endif //GONG_SHI_HAO==111

#if GONG_SHI_HAO==112
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        uint8_t *crc;
        uint16_t dat;
        crc = (uint8_t*)&dat;
        Fml_CRC16 = 0;
        dat = Formula_CRC16(D,12);
        Result[0] = crc[0];
        Result[1] = crc[1];
        Result[2] = 0;
        Result[3] = 0;
}
#endif //GONG_SHI_HAO==112

#if GONG_SHI_HAO==113
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        uint8_t *crc;
        uint16_t dat;
        crc = (uint8_t*)&dat;
        Fml_CRC16 = 0;
        dat = Formula_CRC16(D,12);
        Result[0] = crc[0];
        Result[1] = crc[1];
        Result[2] = C[2] ^ D[2] ^ D[1];
        Result[3] = C[3] ^ D[3] ^ D[0];
}
#endif //GONG_SHI_HAO==113

#if GONG_SHI_HAO==114
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        uint8_t *crc;
        uint16_t dat;
        crc = (uint8_t*)&dat;
        Fml_CRC16 = 0;
        dat = Formula_CRC16(C,4);
        Result[0] = crc[0] | D[0] | D[1] ^ D[2] & D[3] ^ D[4] ^ D[5] | D[6] ^ D[7] ^ D[8] ^ D[9] ^ D[10] ^ D[11] ;;
        Result[1] = crc[1] ^ D[1];
        Result[2] = C[2] ^ D[2] ^ D[1];
        Result[3] = C[3] ^ D[3] ^ D[0];
}
#endif //GONG_SHI_HAO==114

#if GONG_SHI_HAO==115
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        uint8_t *crc;
        uint16_t dat;
        crc = (uint8_t*)&dat;
        Fml_CRC16 = 0;
        dat = Formula_CRC16(D,6);
        Result[0] = C[0] ^ D[6] ^ crc[0];
        Result[1] = C[1] ^ D[7] ^ crc[1];
        Result[2] = C[2] ^ D[8] ^ D[10] ;
        Result[3] = C[3] ^ D[9] ^ D[11] ;
}
#endif //GONG_SHI_HAO==115

#if GONG_SHI_HAO==116
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        uint8_t *crc;
        uint16_t dat;
        crc = (uint8_t*)&dat;
        Fml_CRC16 = 0;
        dat = Formula_CRC16(D,12);
        Result[0] = C[0] ^ crc[0];
        Result[1] = C[1] ^ crc[1];
        Result[2] = C[2] ^ crc[0] ^ D[10] ;
        Result[3] = C[3] ^ crc[1] ^ D[11] ;
}
#endif //GONG_SHI_HAO==116

#if GONG_SHI_HAO==117
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        uint8_t *crc;
        uint16_t dat;
        crc = (uint8_t*)&dat;
        Result[0] = C[0] + D[0] - D[1] | D[2] ^ D[8] & D[9];
        Result[1] = C[1] + D[5] - D[6] | D[7] ^ D[10] & D[11];
        Result[2] = C[2];
        Result[3] = C[3];
        Fml_CRC16 = 0;
        dat = Formula_CRC16(Result,4);
        Result[0] = crc[0];
        Result[1] = crc[1];
        Result[2] = C[2];
        Result[3] = C[3];
}
#endif //GONG_SHI_HAO==117

#if GONG_SHI_HAO==118
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        uint8_t *crc;
        uint16_t dat;
        crc = (uint8_t*)&dat;
        Result[0] = C[0] + D[0] - D[1] | D[2] ^ D[3] & D[4];
        Result[1] = C[1] + D[5] - D[6] | D[7] ^ D[10] & D[11];
        Result[2] = C[2] ^ D[8];
        Result[3] = C[3] ^ D[8];;
        Fml_CRC16 = 0;
        dat = Formula_CRC16(Result,4);
        Result[0] = crc[0];
        Result[1] = crc[1];
        Result[2] = C[2] ^ crc[0];
        Result[3] = C[3] ^ crc[1];
}
#endif //GONG_SHI_HAO==118

#if GONG_SHI_HAO==119
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        uint8_t *crc;
        uint16_t dat;
        crc = (uint8_t*)&dat;
        Fml_CRC16 = 0;
        dat = Formula_CRC16(D+2,6);
        Result[0] = crc[0];
        Result[1] = crc[1];
        Result[2] = C[2] ^ D[0] ^ D[1] ^ D[9]^ D[10] ;
        Result[3] = C[3] ^ D[11] ^ D[5] ;
}
#endif //GONG_SHI_HAO==119

#if GONG_SHI_HAO==120
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        uint8_t *crc;
        uint16_t dat;
        crc = (uint8_t*)&dat;
        Fml_CRC16 = 0;
        dat = Formula_CRC16(D+6,6);
        Result[0] = crc[0];
        Result[1] = crc[1];
        Result[2] = C[2] ^ D[0] ^ D[1] ^ D[2]^ D[3] ;
        Result[3] = C[3] ^ D[4] ^ D[5] ;
}
#endif //GONG_SHI_HAO==120

#if GONG_SHI_HAO==121
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{
        for(int32_t i=0;i<*resultLength;i++)
        {
                Result[i]=D[i];
        }
}
#endif //GONG_SHI_HAO==121

#if GONG_SHI_HAO==122
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{

}
#endif //GONG_SHI_HAO==122

#if GONG_SHI_HAO==123
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{

}
#endif //GONG_SHI_HAO==123

#if GONG_SHI_HAO==124
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{

}
#endif //GONG_SHI_HAO==124

#if GONG_SHI_HAO==125
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{

}
#endif //GONG_SHI_HAO==125

#if GONG_SHI_HAO==126
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{

}
#endif //GONG_SHI_HAO==126

#if GONG_SHI_HAO==127
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{

}
#endif //GONG_SHI_HAO==127

#if GONG_SHI_HAO==128
static void formula(uint8_t *D,uint8_t *Result,int32_t* resultLength)
{

}
#endif //GONG_SHI_HAO==128

