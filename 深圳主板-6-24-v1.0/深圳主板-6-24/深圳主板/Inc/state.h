#ifndef __STATE_1_H_
#define __STATE_1_H_
//#include"ziku.h"
typedef struct
{
    unsigned int  Index;               //????????	  ????????
//	 unsigned int  F_Index;
	unsigned int  Left;                  //????????
	unsigned int  Up;               //????????
	unsigned int  Down;                //????????
	 unsigned int Right;
	 unsigned int Center;
	void   (*Operate)();	    //??????????
}   StateTab;

//extern ARRAY_STRUCT Test_fn(unsigned char a);
extern unsigned char  kai[32],t_jz[32];
extern unsigned char  guan[32],key_jz[32];

unsigned char queding(unsigned char dat);

void Fun_Root(void);
void Fun_GJ(void);
void Fun_GJ_Set(void);
void Fun_auto_LD(void);
void Fun_FZ(void);
void Fun_FZ_Set(void);
void Fun_YS(void);
void Fun_YS_Set(void);
void Fun_CH_Num(void);
void Fun_CH_Num_Set(void);
void Fun_SC(void);
void Fun_SC_Set(void);
void Fun_SW(void);
void Fun_JC(void);
void Fun_JC_Set(void);
void Fun_DY(void);
void Fun_SY(void);
void Fun_SY_Set(void);
void Fun_QX(void);
void Fun_QX_Set(void);
void Fun_GY(void);
void Fun_GY_Set(void);
void Fun_QY(void);
void Fun_QY_Set(void);
void Fun_GY_Val(void);
void GY_Val_Set(void);
void Fun_QY_Val(void);
void QY_Val_Set(void);
void Fun_ST(void);
void Fun_ST_Set(void);
void Fun_GT(void);
void Fun_GT_Set(void);
void Fun_QT(void);
void Fun_QT_Set(void);
void Fun_DZ(void);
void Fun_DZ_Set(void);
void Fun_LD_hezha();
void Fun_DY_hezha();
void Fun_DL_hezha();
void Fun_Vol_CH(void);
void Vol_CH_Set(void);
void Fun_QL_up(void);
void QL_up_Set(void);
void Fun_QL_down(void);
void QL_down_Set(void);
void Fun_DL(void);
void Fun_OP(void);
void Fun_OP_Set(void);
void Fun_OP_Val(void);
void OP_Val_Set(void);
void Fun_OP_T(void);
void OP_T_Set(void);
void Fun_S_Delay(void);
void S_Delay_Set(void);
void Fun_Delay_Val(void);
void Delay_Val_Set(void);
void Fun_Delay_T(void);
void Delay_T_Set(void);
void Fun_Instant(void);
void Fun_Instant_Set(void);
void Fun_Instant_Val(void);
void Instant_Val_Set(void);
void Fun_Cur_CH(void);
void Cur_CH_Set(void);
void Fun_LS(void);
void Fun_Record(void);
void Fun_Record_CX(void);
void Fun_Shiyan_CX(void);
void Fun_Trip_Num(void);
void Trip_Num_LOCK(void);
void Trip_Num_TEST(void);
void Trip_Num_Instant(void);
void Trip_Num_Check(void);
void Trip_Num_Protect(void);
void Trip_Num_LD(void);
void Trip_Num_DY(void);
void Trip_Num_QL(void);
void Trip_Num_SY(void);
void Fun_Time(void);
void Fun_Time_Y(void);
void Time_Y_Set(void);
void Fun_Time_M(void);
void Time_M_Set(void);
void Fun_Time_D(void);
void Time_D_Set(void);
void Fun_Time_H(void);
void Time_H_Set(void);
void Fun_Time_F(void);
void Time_F_Set(void);
void Fun_Time_S(void);
void Time_S_Set(void);
void Fun_Sys_Set(void);
void Fun_SD_hezha(void);
void SD_hezha_Set(void);
void Fun_TD_fenzha(void);
void TD_fenzha_Set(void);
void Fun_Com_S(void);
void Com_S_Set(void);
void Fun_Type_Cur(void);
void Type_Cur_Set(void);
void Fun_Com_D_1(void);
void Com_D_1(void);
void Fun_Com_D_2(void);
void Com_D_2(void);
void Fun_Com_D_3(void);
void Com_D_3(void);
void Fun_Com_D_4(void);
void Com_D_4(void);
void Fun_Com_D_5(void);
void Com_D_5(void);
void Fun_Com_D_6(void);
void Com_D_6(void);
void Fun_Com_D_7(void);
void Com_D_7(void);
void Fun_Com_D_8(void);
void Com_D_8(void);
void Fun_Com_D_9(void);
void Com_D_9(void);
void Fun_Com_D_10(void);
void Com_D_10(void);
void Fun_Com_D_11(void);
void Com_D_11(void);
void Fun_Com_D_12(void);
void Com_D_12(void);	
void Fun_Correct_Set(void);  
void Fun_Corr_Slec(void);
void Fun_Corr_Slec_Set(void);
void Fun_Data_Clear(void);
void Data_Clear_Set(void);
void Fun_TX_switch(void);
extern StateTab  Menu_Tab[120];
//extern unsigned char F_weizhi;



extern void MenuOperate(unsigned char key);
#endif
