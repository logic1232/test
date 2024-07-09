#include "state.h"
#include "display_ziku.h"
#include "LCD.h"
#include "delay.h"
#include "disp.h"
#include "rtc.h" 	

//#include "ziku.h"
#define Lenth_dev_addr	6
#define Addr_I_2d		      	10011	//1字节，二段保护功能
#define Addr_dev_addr 			10029	//6字节，设备通信地址
#define Addr_crtl_word1      	10018	//1字节，控制字1
#define Addr_crtl_word2      	10019	//1字节，控制字2
#define Addr_crtl_word3      	10020	//1字节，控制字3
#define Addr_crtl_word4      	10021	//1字节，控制字4
#define Addr_crtl_word5      	10022	//1字节，控制字5
#define Addr_Type_Cur 			10023	//1字节，电流壳架等级
#define Addr_ctrlword 			10018	//4字节，控制字1-5
#define Addr_L_TB             	10013	//1字节，突变保护功能
#define Addr_shangdian				10261
#define Addr_loudian				10264
#define Addr_dianya				1002  //1字节
#define Addr_dianliu			1001	//1字节
#define Addr_Vol_g 				10024	//1字节，过压档位
#define Addr_Vol_q				10025	//1字节，欠压档位
#define Addr_D_Cur				10027	//1字节，电流档位
#define Addr_baud				10028	//1字节，波特率
//#define Addr_dev_addr 			10029	//6字节，设备通信地址
#define Addr_D2_Cur				10251
#define Addr_D3_Cur				10252
#define Addr_D2_Time				10253
#define Addr_CurLong_Time				10254
#define Addr_GY_yanshi				10257
#define Addr_QY_yanshi				10258
#define Addr_SY_yanshi    10291
#define Addr_jiaozhun       10300
#define Addr_SY_F    10288
#define Addr_I_3d		      	10250
#define Addr_duandian				10263

#define Addr_mima_set 10824//4
#define Addr_L_specialwave 10828  //1

/*****漏电延时档位***********/
#define Addr_TH_LCur 12000  //1

/*****电机合闸延时档位***********/
#define Addr_hezha_delay 13000  //1

extern volatile unsigned char TH_hezha_delay;
extern unsigned char hezha_delay_show[6][4];
extern volatile unsigned char hezha_delay_arry[6];
extern volatile unsigned char hezha_delay;

extern unsigned char  dian[16];
extern unsigned char  qirigang[16];
extern unsigned char  xiaogang[16];
extern unsigned char  xiaomaohao[16];
unsigned char F_queren=1;
extern volatile unsigned char  F_Leak_Delay;

extern unsigned char F_init_chenggong;
unsigned char Type_cur_Temp=0;
extern unsigned char self_addr_code_temp[6];
extern unsigned char  gang[2];
extern unsigned char  num_table_8x16[10][16];
unsigned char nian_qian[3]={0};
unsigned char F_year_gengxin=0;
volatile unsigned char tim_m3,tim_d3,tim_h3,tim_f3,tim_s3;
volatile unsigned int  tim_y3;
extern unsigned char shangdian,duandian,jiaozhun,LD_hezha,DY_hezha,DL_hezha;	
extern volatile unsigned char D2_Cur,TH_DL,D3_Cur; 
extern unsigned char F_initial_lcd;
extern unsigned char F_initial_lcd_hezha;
extern volatile unsigned char  TH_Long_Cur,F_ip_3;
extern volatile unsigned int Func_Index;      
extern void (*Func_Ptr)();				
extern	void I_VAL_handle(void);
//extern void Delay10us();		//@20.000MHz
extern	 unsigned char  frame1[32];
extern	  unsigned char  frame2[32];
extern unsigned char  temp_frame[32];
extern  unsigned int key_state;
unsigned int NUM_test=0,NUM_test1=0;
extern unsigned char key_value_tmp;
extern unsigned char ctrlword[5];
extern void putchar(unsigned char dat);
extern volatile unsigned char F_key,F_Disp,F_ent;
extern volatile unsigned char 	  F_trip_ld,F_trip_qy,F_trip_gy ,F_dataalarm_xq,F_data_clear,F_trip_xq ,F_trip_gl ,	F_trip_xl,F_jiance,F_trip_sy,F_Corr,F_auto_ld;
extern volatile unsigned	char  F_trip_QX,F_trip_QL,F_trip_sy,F_trip_sy;
extern unsigned char D_LCur,D_A_LCur,LC_N;//漏电电流档位指针 
extern unsigned char TH_LCur;//漏电时间档位指针
extern unsigned char F_leak_maxmin,F_Conter_Updata,F_TB_trip,F_C_IP,F_Special_wave;
extern unsigned char Vol_g,Vol_q,F_TIME,T_W,V_point,Vol_s_T,Vol_up,Vol_down;//失过欠压保护时间档位指针
extern   unsigned char Type_Cur,D_M_Cur,D_Cur,D_I2,D_S;        //过流保护规格,档位长度,档位指针
extern unsigned char F_Cur,iii,F_ip,F_cd_set,F_ia,N_anolog_trip,F_I_STA,F_I_Lock;
extern  unsigned char lishijilu_1[5],lishijilu_2[5],lishijilu_3[5],guzhang_wei; 
extern	 unsigned char nian[3],yue[3],ri[3],shi[3],fen[3],miao[3];
extern	unsigned char add_1_1[2],add_2_1[2],add_3_1[2],add_4_1[2],add_5_1[2],add_6_1[2];
extern	unsigned char add_1_2[2],add_2_2[2],add_3_2[2],add_4_2[2],add_5_2[2],add_6_2[2];
extern u8 ds1302_read_time_uart(void); ; 
extern unsigned char tim_disp[7];
extern volatile signed  int I_I_Array_xianshi[20],CurA_cal_tmp[5],CurB_cal_tmp[5],CurC_cal_tmp[5],Leak1_temp,Vol1_A_temp,Vol1_B_temp,Vol1_C_temp;

extern volatile signed long CurA400_cal_tmp[5],CurB400_cal_tmp[5],CurC400_cal_tmp[5];
extern volatile signed long CurA630_cal_tmp[5],CurB630_cal_tmp[5],CurC630_cal_tmp[5];
extern volatile signed long CurA800_cal_tmp[5],CurB800_cal_tmp[5],CurC800_cal_tmp[5];
extern unsigned char F_shishi,F_sssj,F_gz_disp;
extern unsigned char  F_dianya_chonghe;
extern unsigned char baud;
extern void Sj_function_process();
extern  unsigned char wuxing[32];
extern unsigned int SET_I_VAL;
extern unsigned char disp_status1,disp_gz,SET_D_Cur ;
extern  unsigned char zifu_dian[4];
extern void xianshishuju(unsigned int dat);
extern 	void xianshishuju_dianliu(unsigned int dat);
unsigned char kaiguan_process(unsigned char a);
unsigned char dianliu_dang;
extern unsigned char N_GY_yanshi,N_QY_yanshi,D_GY_yanshi,D_QY_yanshi,D_SY_yanshi;
//extern void EEPROM_R(unsigned char *mcu_address, EEPROM_address,unsigned int count,unsigned int paga);
extern void EEPROM_R(unsigned int WriteAddr,unsigned char *a,unsigned char Len,unsigned char SelectAddr);
extern void generate_chuan(unsigned char p[5],unsigned char a,unsigned char b,unsigned char c,unsigned char d);
unsigned int Get_index(unsigned int factor1);
extern volatile unsigned int Leak_Cur_disp_temp;
unsigned char Type_Cur_temp,Type_Cur_change;
// unsigned char disbit1[]={"功能设置"};
//  unsigned char disbit2[]={" 2 记录查询"};
//	 unsigned char disbit3[]={"3 时间设置"};
//	  unsigned char disbit4[]={" 4 系统维护"};
// unsigned char kaiguan[4][6]=
//{
//    "关闭","打开"
//};

extern void Get_Selftest_Record(unsigned int N_tmp);
 unsigned char kaiguan[2][3]=
{
    "关","开"
};
 unsigned char guzhang_yuanyin[13][5]=
{
"欠压","过压","漏电","过流","停电","手动","按键","远程","其他","缺相","缺零","短延","短瞬"
};

 unsigned char shifou[2][3]=
{
    "否","是"
};
 unsigned char dianliu[9][6]=
{
 "0.03A","0.05A","0.1A","0.2A","0.3A","0.5A","0.8A","1A","Auto" 
};
 unsigned char shijian[5][6]=
{
    "0.2s","0.3s","0.5s","1s","0.1s"
};
 unsigned char cishu[4][4]=
{
    "0c","1c","3c","WX"
};
 unsigned char DIANYA[6][6]=
{
    "250V","260V","270V","280V" ,"290V", "300V"
};


 unsigned char DIANYA_1[6][6]=
{
    "140V","150V","160V","170V","180V","190V"  
};
 unsigned char DIANYA_down[7][6]=
{
    "140V","150V","160V","170V","180V","190V","200V"  
};
 unsigned char DIANYA_up[6][6]=
{
    "240V","250V","260V","270V","280V" ,"290V" 
};

 unsigned char botelv[4][6]=
{
"1200","2400","4800","9600"

};
 unsigned char GUOLIU_T[8][6]=
{
  //"15s","30s","60s","120s","240s"
	"3s","4s","6s","8s","10s","12s","16s","18s"

};
unsigned char D2_DW[6][5]=
{
  "2r","4r","6r","8r","10r","12r"

};
unsigned char D3_DW[6][5]=
{
  "4r","6r","8r","10r","12r","14r"

};
unsigned char D2_T[7][6]=
{
  //"0.1s","0.2s","0.3s","0.4s","27S"
	"0.1s","0.2s","0.3s","0.4s","0.6S","0.8S","1S"

};
unsigned char SY_yanshi[10][6]=
{
"1s","2s","3s","4s","5s","6s","7s","8s","9s","10s"
};
unsigned char GY_yanshi[10][4]=
{
  "1s","2s","3s","4s","5s","6s","7s","8s","9s","10s"

};
unsigned char QY_yanshi[10][4]=
{
  "1s","2s","3s","4s","5s","6s","7s","8s","9s","10s"

};
extern unsigned char  maohao[16];

extern unsigned char dispbit[8],array_temps[30];

extern  unsigned char   mima_set[4];//用户设定的密码，用于与输入的密码比对

extern void xianshishuju1(unsigned int dat);

		unsigned char ci[5];

void Disp_date(void)
{
      Lcd12864_Write16CnCHAR(0,0,4,"15日期\r");
		  display_graphic_8x16(5,55,maohao);
//	  display_xianfangkuai(3,5,0,0);
	

	    HAL_RTC_GetTime(&hrtc, &stimestructure, RTC_FORMAT_BCD);
      HAL_RTC_GetDate(&hrtc, &sdatestructure, RTC_FORMAT_BCD);
	    tim_y3 = sdatestructure.Year;  //tim_y为十进制，要转换二进制
			tim_m3 = sdatestructure.Month;
			tim_d3 = sdatestructure.Date;
			tim_h3 = stimestructure.Hours;
			tim_f3 = stimestructure.Minutes;
			tim_s3 = stimestructure.Seconds; 
			
				nian[0]=(tim_y3>>4)+0x30;	
				nian[1]=(tim_y3&0x0F)+0x30;
				nian[2]='\0';
	
				yue[0]=(tim_m3>>4)+0x30;
				yue[1]=(tim_m3&0x0F)+0x30;
				yue[2]='\0';

				ri[0]=(tim_d3>>4)+0x30;
				ri[1]=(tim_d3&0x0F)+0x30;
				ri[2]='\0';

				shi[0]=(tim_h3>>4)+0x30;
				shi[1]=(tim_h3&0x0F)+0x30;
				shi[2]='\0';

				fen[0]=(tim_f3>>4)+0x30;
				fen[1]=(tim_f3&0x0F)+0x30;
				fen[2]='\0';
				
				miao[0]=(tim_s3>>4)+0x30;
				miao[1]=(tim_s3&0x0F)+0x30;
				miao[2]='\0';
				
				nian_qian[0]=0x02+0x30;
				nian_qian[1]=0x00+0x30;
				nian_qian[2]='\0';
				display_ASCIIstring_8x16(5,55,nian_qian);
				display_ASCIIstring_8x16(5,71,nian);
				display_graphic_8x16(5,87,qirigang);	
				display_ASCIIstring_8x16(5,92,yue);
				display_graphic_8x16(5,108,qirigang);	
				display_ASCIIstring_8x16(5,113,ri);
}


void Disp_time(void)
{
    Lcd12864_Write16CnCHAR(0,0,6,"16时间\r");
		display_graphic_8x16(7,56,maohao);
//	  display_xianfangkuai(3,5,0,0);
	

	    HAL_RTC_GetTime(&hrtc, &stimestructure, RTC_FORMAT_BCD);
      HAL_RTC_GetDate(&hrtc, &sdatestructure, RTC_FORMAT_BCD);
	    tim_y3 = sdatestructure.Year;  //tim_y为十进制，要转换二进制
			tim_m3 = sdatestructure.Month;
			tim_d3 = sdatestructure.Date;
			tim_h3 = stimestructure.Hours;
			tim_f3 = stimestructure.Minutes;
			tim_s3 = stimestructure.Seconds; 
			
				nian[0]=(tim_y3>>4)+0x30;	
				nian[1]=(tim_y3&0x0F)+0x30;
				nian[2]='\0';
	
				yue[0]=(tim_m3>>4)+0x30;
				yue[1]=(tim_m3&0x0F)+0x30;
				yue[2]='\0';

				ri[0]=(tim_d3>>4)+0x30;
				ri[1]=(tim_d3&0x0F)+0x30;
				ri[2]='\0';

				shi[0]=(tim_h3>>4)+0x30;
				shi[1]=(tim_h3&0x0F)+0x30;
				shi[2]='\0';

				fen[0]=(tim_f3>>4)+0x30;
				fen[1]=(tim_f3&0x0F)+0x30;
				fen[2]='\0';
				
				miao[0]=(tim_s3>>4)+0x30;
				miao[1]=(tim_s3&0x0F)+0x30;
				miao[2]='\0';
				
				nian_qian[0]=0x02+0x30;
				nian_qian[1]=0x00+0x30;
				nian_qian[2]='\0';
				display_ASCIIstring_8x16(7,71,shi);
				display_graphic_8x16(7,87,xiaomaohao);	
				display_ASCIIstring_8x16(7,92,fen);
				display_graphic_8x16(7,108,xiaomaohao);	
				display_ASCIIstring_8x16(7,113,miao);
}
void RTC_Readtime(void)
{
//	  Lcd12864_Write16CnCHAR(0,32,0,"时间设置\r");
//	   Lcd12864_Write16CnCHAR(0,32,3,"年  月  日\r");
//	   Lcd12864_Write16CnCHAR(0,32,6,"时  分  秒\r");
//	  display_xianfangkuai(3,5,0,0);
	
	    HAL_RTC_GetTime(&hrtc, &stimestructure, RTC_FORMAT_BCD);
      HAL_RTC_GetDate(&hrtc, &sdatestructure, RTC_FORMAT_BCD);
	    tim_y3 = sdatestructure.Year;  //tim_y为十进制，要转换二进制
			tim_m3 = sdatestructure.Month;
			tim_d3 = sdatestructure.Date;
			tim_h3 = stimestructure.Hours;
			tim_f3 = stimestructure.Minutes;
			tim_s3 = stimestructure.Seconds; 
}
void Disp_Write_time(void)
{
	sdatestructure.Year=tim_y3;
	sdatestructure.Month=tim_m3;
	sdatestructure.Date=tim_d3;
	stimestructure.Hours=tim_h3;
	stimestructure.Minutes=tim_f3;
	stimestructure.Seconds=tim_s3;
				nian[0]=(tim_y3>>4)+0x30;	
				nian[1]=(tim_y3&0x0F)+0x30;
				nian[2]='\0';
	
				yue[0]=(tim_m3>>4)+0x30;
				yue[1]=(tim_m3&0x0F)+0x30;
				yue[2]='\0';

				ri[0]=(tim_d3>>4)+0x30;
				ri[1]=(tim_d3&0x0F)+0x30;
				ri[2]='\0';

				shi[0]=(tim_h3>>4)+0x30;
				shi[1]=(tim_h3&0x0F)+0x30;
				shi[2]='\0';

				fen[0]=(tim_f3>>4)+0x30;
				fen[1]=(tim_f3&0x0F)+0x30;
				fen[2]='\0';
				
				miao[0]=(tim_s3>>4)+0x30;
				miao[1]=(tim_s3&0x0F)+0x30;
				miao[2]='\0';
					nian_qian[0]=0x02+0x30;
				nian_qian[1]=0x00+0x30;
				nian_qian[2]='\0';
				display_ASCIIstring_8x16(5,55,nian_qian);
				display_ASCIIstring_8x16(5,71,nian);
				display_graphic_8x16(5,87,qirigang);	
				display_ASCIIstring_8x16(5,92,yue);
				display_graphic_8x16(5,108,qirigang);	
				display_ASCIIstring_8x16(5,113,ri);
				
				display_ASCIIstring_8x16(7,71,shi);
				display_graphic_8x16(7,87,xiaomaohao);	
				display_ASCIIstring_8x16(7,92,fen);
				display_graphic_8x16(7,108,xiaomaohao);	
				display_ASCIIstring_8x16(7,113,miao);
}
unsigned char queding(unsigned char dat)
{
		if(F_ent==1)
		{
		display_xianfangkuai(dat,5,0,1);
		F_ent=0;

		return 1;
		}
		else
		{
		display_xianfangkuai(dat,5,1,0);
		return 0;
		}

}



void Fun_Root()                                 //根目录    
{ 
		clear_screen();                             //清屏
		Lcd12864_Write16CnCHAR(0,16,0,"1漏电设置\r  2电压设置\r  3电流设置\r  4记录查询");
//    display_sanjiao(1,116,0,1);
		display_shouzhi(1,95);
//		if(F_initial_lcd==1)
//	{
//		F_initial_lcd=0;
//	}
//		display_xianfangkuai(1,116,0,1);

}

void Fun_GJ()                                   //漏电告警
{ 
 unsigned char array_tmp[3];
 clear_screen();
 Lcd12864_Write16CnCHAR(0,0,0,"1漏电告警\r2自动定档\r3突变保护\r4特波保护");
 display_graphic_8x16(1,77,maohao);
 display_graphic_8x16(3,77,maohao);
 display_graphic_8x16(5,77,maohao);
 display_graphic_8x16(7,77,maohao);

//   display_sanjiao(1,119,0,1);
   display_kaiguan_frame(1,83,F_trip_ld);
   display_kaiguan(3,83,F_auto_ld);
   display_kaiguan(5,83,F_TB_trip);
	  display_kaiguan(7,83,F_Special_wave);
 
 if(key_value_tmp==0x10)
  {
   F_trip_ld=1;
  }
  if(key_value_tmp==0x40)
  {
   F_trip_ld=0;
  }
  if(F_trip_ld==0)ctrlword[3]&=0xFC ;//控制字分析
  if(F_trip_ld==1)
    {
     ctrlword[3]&=0xFC ;
     ctrlword[3]+=0x02 ;
    }
  array_tmp[0]=ctrlword[3];

  MODIFY_EEP_W(Addr_crtl_word4,array_tmp,1,0xA0);//存储
  ctrlword4_analyze();
  clear_define_screen(0,2,82,99);
  display_kaiguan_frame(1,83,F_trip_ld);  
}


void Fun_auto_LD()
{
	 unsigned char array_tmp[3];
 clear_screen();
 Lcd12864_Write16CnCHAR(0,0,0,"1漏电告警\r2自动定档\r3突变保护\r4特波保护");
 display_graphic_8x16(1,77,maohao);
 display_graphic_8x16(3,77,maohao);
 display_graphic_8x16(5,77,maohao);
 display_graphic_8x16(7,77,maohao);

//   display_sanjiao(1,119,0,1);
   display_kaiguan(1,83,F_trip_ld);
   display_kaiguan_frame(3,83,F_auto_ld);
   display_kaiguan(5,83,F_TB_trip);
	  display_kaiguan(7,83,F_Special_wave);
 
 if(key_value_tmp==0x10)
  {
   F_auto_ld=1;
	 D_LCur=8;
  }
  if(key_value_tmp==0x40)
  {
   F_auto_ld=0;
	 D_LCur=7;
  }
   ctrlword[3]&=0x0F ;
   ctrlword[3]+=(D_LCur<<4);
   array_tmp[0]=ctrlword[3];
   MODIFY_EEP_W(Addr_crtl_word4,array_tmp,1,0xA0);
  ctrlword4_analyze();
	if(D_LCur==8)  F_auto_ld=1;
	else F_auto_ld=0;
  clear_define_screen(2,4,82,99);
  display_kaiguan_frame(3,83,F_auto_ld); 
}
void Fun_FZ()                                  //漏电阀值
{  	
  unsigned char array_tmp[3];	
	clear_screen();
	Lcd12864_Write16CnCHAR(0,0,0,"1漏电阀值\r2漏电延时\r3过压档位\r4欠压档位");
  display_graphic_8x16(1,77,maohao);
	display_graphic_8x16(3,77,maohao);
	display_graphic_8x16(5,77,maohao);
	display_graphic_8x16(7,77,maohao);

	display_ASCIIstring_8x16_frame(1,83,dianliu[D_LCur]);
  display_ASCIIstring_8x16(3,83,shijian[TH_LCur]);	
	display_ASCIIstring_8x16(5,83,DIANYA[Vol_g]);
	display_ASCIIstring_8x16(7,83,DIANYA_1[Vol_q]);
	if(F_queren==1)
	{
	key_state=key_state|D_LCur;
	}
	if((key_value_tmp==0x20)&&(F_queren<3))
	{
		F_queren++;
	}
	
	clear_define_screen(0,2,82,128);
	display_ASCIIstring_8x16_fanxian(1,83,dianliu[(key_state&0xFF)]);	
	if((key_value_tmp==0x20)&&(F_queren==3))
	{
		D_LCur=((key_state)&0x0F);
    ctrlword[3]&=0x0F ;
    ctrlword[3]+=(D_LCur<<4);
    array_tmp[0]=ctrlword[3];
    MODIFY_EEP_W(Addr_crtl_word4,array_tmp,1,0xA0);
		ctrlword4_analyze();
		clear_define_screen(0,2,82,128);
	  display_ASCIIstring_8x16(1,83,dianliu[D_LCur]);
    key_state=0x22100;		
		F_queren=1;
	}
}

void Fun_FZ_Set()                              //漏电阀值设置
{	
		if(key_value_tmp==0x20)
	{
	  key_state=key_state|D_LCur;
	}
	clear_define_screen(2,4,82,128);
	display_ASCIIstring_8x16_fanxian(3,83,dianliu[(key_state&0xFF)]);	
}	
 
void Fun_YS()                                  //漏电延时
{		
	unsigned char array_tmp[3];	
	clear_screen();
	Lcd12864_Write16CnCHAR(0,0,0,"1漏电阀值\r2漏电延时\r3过压档位\r4欠压档位");
  display_graphic_8x16(1,77,maohao);
	display_graphic_8x16(3,77,maohao);
	display_graphic_8x16(5,77,maohao);
	display_graphic_8x16(7,77,maohao);

	display_ASCIIstring_8x16(1,83,dianliu[D_LCur]);
  display_ASCIIstring_8x16_frame(3,83,shijian[TH_LCur]);	
	display_ASCIIstring_8x16(5,83,DIANYA[Vol_g]);
	display_ASCIIstring_8x16(7,83,DIANYA_1[Vol_q]);
	if(F_queren==1)
	{
	key_state=key_state|TH_LCur;
	}
	if((key_value_tmp==0x20)&&(F_queren<3))
	{
		F_queren++;
	}
	
	clear_define_screen(2,4,82,128);
	display_ASCIIstring_8x16_fanxian(3,83,shijian[(key_state&0xFF)]);	
	if((key_value_tmp==0x20)&&(F_queren==3))
	{
		TH_LCur=((key_state)&0x07);
		array_tmp[0]=TH_LCur;
		MODIFY_EEP_W(Addr_TH_LCur ,array_tmp,1,0xA0);
//    ctrlword[3]&=0xF3 ;
//    ctrlword[3]+=(TH_LCur<<2);
//    array_tmp[0]=ctrlword[3];
//    MODIFY_EEP_W(Addr_crtl_word4,array_tmp,1,0xA0);
//		ctrlword4_analyze();
		clear_define_screen(2,4,82,128);
	  display_ASCIIstring_8x16(3,83,shijian[TH_LCur]);
    key_state=0x23100;		
		F_queren=1;
	}
}

void Fun_YS_Set()                               //漏电延时设置
{
	if(key_value_tmp==0x20)
	{
	   key_state=key_state|TH_LCur;
	
	}
		clear_define_screen(4,6,82,128);
		display_ASCIIstring_8x16_fanxian(5,83,shijian[(key_state&0xFF)]);
	
}

void Fun_CH_Num()                                //漏电重合闸
{ 
clear_screen();
	Lcd12864_Write16CnCHAR(0,0,0,"1漏电告警\r2漏电阀值\r3漏电延时\r4漏电重合");
      display_graphic_8x16(1,77,maohao);
	display_graphic_8x16(3,77,maohao);
	display_graphic_8x16(5,77,maohao);
	display_graphic_8x16(7,77,maohao);
//  display_sanjiao(1,119,0,1);
	  display_kaiguan(1,83,F_trip_ld);
//	  Lcd12864_Write16CnCHAR(0,78,0,kaiguan[F_trip_ld]);
	  display_ASCIIstring_8x16(3,83,dianliu[D_LCur]);	
	  display_ASCIIstring_8x16(5,83,shijian[TH_LCur]);
//		Lcd12864_Write16CnCHAR(0,78,6,kaiguan[F_TB_trip]);
		  display_ASCIIstring_8x16_frame(7,83,cishu[LC_N]);
//	 display_kaiguan(7,83,F_TB_trip);
}

void Fun_CH_Num_Set()                            //漏电重合次数
{
if(key_value_tmp==0x20)
{
key_state=key_state|LC_N;	
}
 clear_define_screen(6,8,82,128);
display_ASCIIstring_8x16_fanxian(7,83,cishu[(key_state&0xFF)]); 
}

void Fun_SC()                                    //突变保护  
{
	unsigned char array_tmp[3];
	  clear_screen();
	Lcd12864_Write16CnCHAR(0,0,0,"1漏电告警\r2自动定档\r3突变保护\r4特波保护");
	display_graphic_8x16(1,77,maohao);
	display_graphic_8x16(3,77,maohao);
	display_graphic_8x16(5,77,maohao);
	display_graphic_8x16(7,77,maohao);

//	  display_sanjiao(1,119,0,1);
	  display_kaiguan(1,83,F_trip_ld);
   display_kaiguan(3,83,F_auto_ld);
	  display_kaiguan(5,83,F_TB_trip);
	  display_kaiguan(7,83,F_Special_wave);
	
	if(key_value_tmp==0x10)
		{
			F_TB_trip=1;
		}
		if(key_value_tmp==0x40)
		{
			F_TB_trip=0;
		}
		if(F_TB_trip==1)	{array_tmp[0] = 0x01 ;F_Leak_Delay = 0;}
     else if(F_TB_trip==0)	array_tmp[0] = 0x00;
        else array_tmp[0] = 0x00;
				MODIFY_EEP_W(Addr_L_TB,array_tmp,1,0xA0);
	  clear_define_screen(4,6,82,128);
		display_kaiguan_frame(5,83,F_TB_trip);
}


void Fun_SW()                                    //特波保护  
{
	unsigned char array_tmp[3];
	  clear_screen();
	Lcd12864_Write16CnCHAR(0,0,0,"1漏电告警\r2自动定档\r3突变保护\r4特波保护");
	display_graphic_8x16(1,77,maohao);
	display_graphic_8x16(3,77,maohao);
	display_graphic_8x16(5,77,maohao);
	display_graphic_8x16(7,77,maohao);

//	  display_sanjiao(1,119,0,1);
	  display_kaiguan(1,83,F_trip_ld);
   display_kaiguan(3,83,F_auto_ld);	
	  display_kaiguan(5,83,F_TB_trip);
	  display_kaiguan(7,83,F_Special_wave);
	
	if(key_value_tmp==0x10)
		{
			F_Special_wave=1;
		}
		if(key_value_tmp==0x40)
		{
			F_Special_wave=0;
		}
		if(F_Special_wave==1)	
   {
	 array_tmp[0] = 0x01 ;
	 F_Leak_Delay = 0;
	 }
    else if(F_Special_wave==0)	array_tmp[0] = 0x00;
    else array_tmp[0] = 0x00;
		MODIFY_EEP_W(Addr_L_specialwave,array_tmp,1,0xA0);
	  clear_define_screen(6,8,82,128);
		display_kaiguan_frame(7,83,F_Special_wave);
}


void Fun_JC()                                    //漏电检测
{
clear_screen();
	Lcd12864_Write16CnCHAR(0,0,0,"5突变保护\r6漏电监测");
      display_graphic_8x16(1,77,maohao);
	display_graphic_8x16(3,77,maohao);
//  display_sanjiao(1,119,1,1);
	  display_kaiguan(1,83,F_TB_trip);
		  display_kaiguan_frame(3,83,F_jiance);
}

void Fun_JC_Set()                                //漏电检测设置
{
if(key_value_tmp==0x20)
{
key_state=key_state|F_jiance;
}
clear_define_screen(2,4,82,99);
display_kaiguan_fanxian(3,83,(key_state&0xFF)); 

}

void Fun_DY()
{
		if(key_value_tmp==0x40)//退出键
		{
			clear_screen();
		  Lcd12864_Write16CnCHAR(0,16,0,"1漏电设置\r  2电压设置\r  3电流设置\r  4记录查询");
		}
		else
		{
			clear_define_screen(0,16,91,116);
		}
//		if(F_initial_lcd==1)
//	{
//		F_initial_lcd=0;
//	}	
//		 display_sanjiao(1,116,0,1);
		 	display_shouzhi(3,95);


}

void Fun_SY()                                  //失压保护
{
	unsigned char array_tmp[3];
	  clear_screen();
	Lcd12864_Write16CnCHAR(0,0,0,"9失压保护\r10过流保护\r11短延保护\r12瞬时保护");
	display_graphic_8x16(1,94,maohao);
	display_graphic_8x16(3,94,maohao);
	display_graphic_8x16(5,94,maohao);
	display_graphic_8x16(7,94,maohao);

//	  display_sanjiao(1,119,0,1);
	  display_kaiguan(1,100,F_trip_sy);
   display_kaiguan(3,100,F_trip_gl);	
	  display_kaiguan(5,100,F_ip);
	  display_kaiguan(7,100,F_ip_3);
	
	if(key_value_tmp==0x10)
		{
			F_trip_sy=1;
		}
		if(key_value_tmp==0x40)
		{
			F_trip_sy=0;
		}
		if(F_trip_sy==1)	
   {
	 array_tmp[0] = 0x01 ;
	 }
    else if(F_trip_sy==0)	array_tmp[0] = 0x00;
  	array_tmp[0]=F_trip_sy;
		MODIFY_EEP_W(Addr_SY_F,array_tmp,1,0xA0);
	  clear_define_screen(0,2,100,128);
		display_kaiguan_frame(1,100,F_trip_sy);
}
void Fun_SY_Set()                             //失压保护设置
{
if(key_value_tmp==0x20)
{
key_state=key_state|F_trip_sy;	
}
clear_define_screen(0,2,82,99);
display_kaiguan_fanxian(1,83,(key_state&0xFF)); 
}

void Fun_QX()                                 //缺相保护
{
unsigned char array_tmp[3];
	  clear_screen();

	Lcd12864_Write16CnCHAR(0,0,0,"5断零保护\r6过电压保护\r7欠电压保护\r8断相保护");
	display_graphic_8x16(1,94,maohao);
	display_graphic_8x16(3,94,maohao);
	display_graphic_8x16(5,94,maohao);
	display_graphic_8x16(7,94,maohao);

//	  display_sanjiao(1,119,0,1);
	  display_kaiguan(1,100,F_trip_QL);
	  display_kaiguan(3,100,F_trip_gy);	
	  display_kaiguan(5,100,F_trip_qy);
	  display_kaiguan_frame(7,100,F_trip_QX);
	
	if(key_value_tmp==0x10)
		{
			F_trip_QX=1;
		}
		if(key_value_tmp==0x40)
		{
			F_trip_QX=0;
		}
		 if(F_trip_QX==1)	ctrlword[1]|=0x04 ; 
        if(F_trip_QX==0)	ctrlword[1]&=(~0x04);
			array_tmp[0]=ctrlword[1];
			MODIFY_EEP_W(Addr_crtl_word2,array_tmp,1,0xA0);
    clear_define_screen(6,8,100,128);
    display_kaiguan_frame(7,100,F_trip_QX); 
}

void Fun_GY()                                 //过压保护
{
unsigned char array_tmp[3];
	  clear_screen();

	Lcd12864_Write16CnCHAR(0,0,0,"5断零保护\r6过电压保护\r7欠电压保护\r8断相保护");
	display_graphic_8x16(1,94,maohao);
	display_graphic_8x16(3,94,maohao);
	display_graphic_8x16(5,94,maohao);
	display_graphic_8x16(7,94,maohao);

//	  display_sanjiao(1,119,0,1);
	  display_kaiguan(1,100,F_trip_QL);
	  display_kaiguan_frame(3,100,F_trip_gy);	
	  display_kaiguan(5,100,F_trip_qy);
	  display_kaiguan(7,100,F_trip_QX);
	
	if(key_value_tmp==0x10)
		{
			F_trip_gy=1;
		}
		if(key_value_tmp==0x40)
		{
			F_trip_gy=0;
		}
		if(F_trip_gy==1)ctrlword[1]|=0x10 ;
        if(F_trip_gy==0)ctrlword[1]&=(~0x10);
        array_tmp[0]=ctrlword[1];
        MODIFY_EEP_W(Addr_crtl_word2,array_tmp,1,0xA0);
	  clear_define_screen(2,4,100,128);
	  display_kaiguan_frame(3,100,F_trip_gy);
}

void Fun_QY()                                  //欠压保护
{
	unsigned char array_tmp[3];
  clear_screen();

	Lcd12864_Write16CnCHAR(0,0,0,"5断零保护\r6过电压保护\r7欠电压保护\r8断相保护");
	display_graphic_8x16(1,94,maohao);
	display_graphic_8x16(3,94,maohao);
	display_graphic_8x16(5,94,maohao);
	display_graphic_8x16(7,94,maohao);
	
//	  display_sanjiao(1,119,0,1);
	  display_kaiguan(1,100,F_trip_QL);
	  display_kaiguan(3,100,F_trip_gy);	
	  display_kaiguan_frame(5,100,F_trip_qy);
	  display_kaiguan(7,100,F_trip_QX);
	
	if(key_value_tmp==0x10)
		{
			F_trip_qy=1;
		}
		if(key_value_tmp==0x40)
		{
			F_trip_qy=0;
		}
		if(F_trip_qy==1)ctrlword[1]|=0x40 ;
    if(F_trip_qy==0)ctrlword[1]&=(~0x40);
        array_tmp[0]=ctrlword[1];
        MODIFY_EEP_W(Addr_crtl_word2,array_tmp,1,0xA0);
	  clear_define_screen(4,6,100,128);
		display_kaiguan_frame(5,100,F_trip_qy);
}
void Fun_GY_Val()                               //过压档位
{
	unsigned char array_tmp[3];	
	clear_screen();
	Lcd12864_Write16CnCHAR(0,0,0,"1漏电阀值\r2漏电延时\r3过压档位\r4欠压档位");
  display_graphic_8x16(1,77,maohao);
	display_graphic_8x16(3,77,maohao);
	display_graphic_8x16(5,77,maohao);
	display_graphic_8x16(7,77,maohao);

	display_ASCIIstring_8x16(1,83,dianliu[D_LCur]);
  display_ASCIIstring_8x16(3,83,shijian[TH_LCur]);	
	display_ASCIIstring_8x16_frame(5,83,DIANYA[Vol_g]);
	display_ASCIIstring_8x16(7,83,DIANYA_1[Vol_q]);
	if(F_queren==1)
	{
	key_state=key_state|Vol_g;
	}
	if((key_value_tmp==0x20)&&(F_queren<3))
	{
		F_queren++;
	}
	
	clear_define_screen(4,6,82,128);
	display_ASCIIstring_8x16_fanxian(5,83,DIANYA[(key_state&0xFF)]);	
	if((key_value_tmp==0x20)&&(F_queren==3))
	{
		Vol_g=((key_state)&0x07);
		array_tmp[0]=Vol_g ;
		MODIFY_EEP_W(Addr_Vol_g,array_tmp,1,0xA0);
		EEPROM_R(Addr_Vol_g,array_tmp,1,0xA0);
		clear_define_screen(4,6,82,128);
	  display_ASCIIstring_8x16(5,83,shijian[Vol_g]);
    key_state=0x24100;		
		F_queren=1;
	}
}
void GY_Val_Set()                              //过压档位设置
{
 if(key_value_tmp==0x20)
		{
		key_state=key_state|Vol_g;
		
		}
      clear_define_screen(0,2,87,120);
	display_ASCIIstring_8x16_fanxian(1,83,DIANYA[(key_state&0xFF)]);
}

void Fun_QY_Val()                              //欠压档位
{
 unsigned char array_tmp[3]; 
 clear_screen();
 Lcd12864_Write16CnCHAR(0,0,0,"1漏电阀值\r2漏电延时\r3过压档位\r4欠压档位");
  display_graphic_8x16(1,77,maohao);
 display_graphic_8x16(3,77,maohao);
 display_graphic_8x16(5,77,maohao);
 display_graphic_8x16(7,77,maohao);

 display_ASCIIstring_8x16(1,83,dianliu[D_LCur]);
  display_ASCIIstring_8x16(3,83,shijian[TH_LCur]); 
 display_ASCIIstring_8x16(5,83,DIANYA[Vol_g]);
 display_ASCIIstring_8x16_frame(7,83,DIANYA_1[Vol_q]);
 if(F_queren==1)
 {
 key_state=key_state|Vol_q;
 }
 if((key_value_tmp==0x20)&&(F_queren<3))
 {
  F_queren++;
 }
 
 clear_define_screen(6,8,82,128);
 display_ASCIIstring_8x16_fanxian(7,83,DIANYA_1[(key_state&0xFF)]); 
 if((key_value_tmp==0x20)&&(F_queren==3))
 {
  Vol_q=((key_state)&0x07);
    array_tmp[0]=Vol_q ;
    MODIFY_EEP_W(Addr_Vol_q,array_tmp,1,0xA0);
  EEPROM_R(Addr_Vol_q,array_tmp,1,0xA0);
  clear_define_screen(6,8,82,128);
   display_ASCIIstring_8x16(7,83,DIANYA_1[Vol_q]);
    key_state=0x3D100;  
  F_queren=1;
 }
}


void QY_Val_Set()                                //欠压档位设置
{
		  if(key_value_tmp==0x20)
		{
		  key_state=key_state|Vol_q;
		
		}
      clear_define_screen(2,4,87,110);
//	    display_ASCIIstring_8x16_fanxian(1,91,DIANYA_1[(key_state&0xFF)]);
		display_ASCIIstring_8x16_fanxian(3,83,DIANYA_1[(key_state&0xFF)]);

}

void Fun_ST()                                    //失压延时
{
  clear_screen();
  unsigned char array_tmp[3];	
	Lcd12864_Write16CnCHAR(0,0,0,"5失压延时\r6过压延时\r7欠压延时\r8瞬时档位");
	display_graphic_8x16(1,77,maohao);
	display_graphic_8x16(3,77,maohao);
	display_graphic_8x16(5,77,maohao);
	display_graphic_8x16(7,77,maohao);

//	  display_sanjiao(1,119,0,1);
  display_ASCIIstring_8x16_frame(1,83,SY_yanshi[D_SY_yanshi]);
	display_ASCIIstring_8x16(3,83,GY_yanshi[D_GY_yanshi]);	
	display_ASCIIstring_8x16(5,83,QY_yanshi[D_QY_yanshi]);
  display_ASCIIstring_8x16(7,83,D3_DW[D3_Cur]);
	
	  if(F_queren==1)
	   {
	     key_state=key_state|D_SY_yanshi;
	   }
		 if((key_value_tmp==0x20)&&(F_queren<3))
	   {
		   F_queren++;
	   }
	  clear_define_screen(0,2,82,128);
	  display_ASCIIstring_8x16_fanxian(1,83,SY_yanshi[(key_state&0xFF)]);
		 
		 	  if((key_value_tmp==0x20)&&(F_queren==3))
	    {
		    D_SY_yanshi=((key_state)&0x0F);
		    array_tmp[0]=D_SY_yanshi ;
		    MODIFY_EEP_W(Addr_SY_yanshi,array_tmp,1,0xA0);
		    clear_define_screen(0,2,82,128);
	      display_ASCIIstring_8x16_frame(1,83,SY_yanshi[D_SY_yanshi]);
        key_state=0x3E100;  
        F_queren=1;
			}
}

void Fun_ST_Set()                                 //失压延时设置
{
if(key_value_tmp==0x20)
{
 key_state=key_state|D_SY_yanshi;
}
clear_define_screen(4,6,87,120);
//	    display_ASCIIstring_8x16_fanxian(1,91,DIANYA_1[(key_state&0xFF)]);
		display_ASCIIstring_8x16_fanxian(5,83,SY_yanshi[(key_state&0xFF)]);
}

void Fun_GT()                                     //过压延时
{
  clear_screen();
  unsigned char array_tmp[3];	
	Lcd12864_Write16CnCHAR(0,0,0,"5失压延时\r6过压延时\r7欠压延时\r8瞬时档位");
	display_graphic_8x16(1,77,maohao);
	display_graphic_8x16(3,77,maohao);
	display_graphic_8x16(5,77,maohao);
	display_graphic_8x16(7,77,maohao);

  display_ASCIIstring_8x16(1,83,SY_yanshi[D_SY_yanshi]);
	display_ASCIIstring_8x16_frame(3,83,GY_yanshi[D_GY_yanshi]);	
	display_ASCIIstring_8x16(5,83,QY_yanshi[D_QY_yanshi]);
  display_ASCIIstring_8x16(7,83,D3_DW[D3_Cur]);
	  if(F_queren==1)
	   {
	     key_state=key_state|D_GY_yanshi;
	   }
		 if((key_value_tmp==0x20)&&(F_queren<3))
	   {
		   F_queren++;
	   }
	  clear_define_screen(2,4,82,128);
	  display_ASCIIstring_8x16_fanxian(3,83,GY_yanshi[(key_state&0xFF)]);
		 
		 	  if((key_value_tmp==0x20)&&(F_queren==3))
	    {
		    D_GY_yanshi=((key_state)&0x0F);
		    array_tmp[0]=D_GY_yanshi ;
		    MODIFY_EEP_W(Addr_GY_yanshi,array_tmp,1,0xA0);
		    clear_define_screen(2,4,82,128);
	      display_ASCIIstring_8x16_frame(3,83,GY_yanshi[D_SY_yanshi]);
		    key_state=0x3F100;  
        F_queren=1;
			}	
}

void Fun_GT_Set()                                  //过压延时设置
{
if(key_value_tmp==0x20)
		{
		  key_state=key_state|D_GY_yanshi;
		
		}
      clear_define_screen(6,8,87,110);
//	    display_ASCIIstring_8x16_fanxian(1,91,DIANYA_1[(key_state&0xFF)]);
		display_ASCIIstring_8x16_fanxian(7,83,GY_yanshi[(key_state&0xFF)]);
}

void Fun_QT()                                     //欠压时间
{
  clear_screen();
  unsigned char array_tmp[3];
	Lcd12864_Write16CnCHAR(0,0,0,"5失压延时\r6过压延时\r7欠压延时\r8瞬时档位");
	display_graphic_8x16(1,77,maohao);
	display_graphic_8x16(3,77,maohao);
	display_graphic_8x16(5,77,maohao);
	display_graphic_8x16(7,77,maohao);

//	  display_sanjiao(1,119,0,1);
  display_ASCIIstring_8x16(1,83,SY_yanshi[D_SY_yanshi]);
	display_ASCIIstring_8x16(3,83,GY_yanshi[D_GY_yanshi]);	
	display_ASCIIstring_8x16_frame(5,83,QY_yanshi[D_QY_yanshi]);
  display_ASCIIstring_8x16(7,83,D3_DW[D3_Cur]);
	
	  if(F_queren==1)
	   {
	     key_state=key_state|D_QY_yanshi;
	   }
		 if((key_value_tmp==0x20)&&(F_queren<3))
	   {
		   F_queren++;
	   }
	  clear_define_screen(4,6,82,128);
	  display_ASCIIstring_8x16_fanxian(5,83,QY_yanshi[(key_state&0xFF)]);
		 
		 	  if((key_value_tmp==0x20)&&(F_queren==3))
	    {
        D_QY_yanshi=((key_state)&0x0F);//0000 01111
        array_tmp[0]=D_QY_yanshi ;
        MODIFY_EEP_W(Addr_QY_yanshi,array_tmp,1,0xA0);
		    clear_define_screen(4,6,82,128);
	      display_ASCIIstring_8x16_frame(3,83,QY_yanshi[D_QY_yanshi]);
		    key_state=0x40100;  
        F_queren=1;
			}	
}

void Fun_QT_Set()                                   //欠压时间设置    
{
		if(key_value_tmp==0x20)
		{
		key_state=key_state|D_QY_yanshi;
		
		}
      clear_define_screen(0,2,87,120);
		
//	   display_ASCIIstring_8x16_fanxian(3,91,DIANYA[(key_state&0xFF)]);	
		 display_ASCIIstring_8x16_fanxian(1,91,QY_yanshi[(key_state&0xFF)]); 
}
void Fun_DZ()                                       //断零保护
{
    clear_screen();
	  unsigned char array_tmp[3];
	Lcd12864_Write16CnCHAR(0,0,0,"5断零保护\r6过电压保护\r7欠电压保护\r8断相保护");
	display_graphic_8x16(1,94,maohao);
	display_graphic_8x16(3,94,maohao);
	display_graphic_8x16(5,94,maohao);
	display_graphic_8x16(7,94,maohao);
	
//	  display_sanjiao(1,119,0,1);
	  display_kaiguan_frame(1,100,F_trip_QL);
	  display_kaiguan(3,100,F_trip_gy);	
	  display_kaiguan(5,100,F_trip_qy);
	  display_kaiguan(7,100,F_trip_QX);
	  if(key_value_tmp==0x10)
		{
			F_trip_QL=1;
		}
		if(key_value_tmp==0x40)
		{
			F_trip_QL=0;
		}
    if(F_trip_QL==1)	ctrlword[2]|=0x01 ;
    if(F_trip_QL==0)	ctrlword[2]&=(~0x01);
	  array_tmp[0]=ctrlword[2];
    MODIFY_EEP_W(Addr_crtl_word3,array_tmp,1,0xA0);
	  clear_define_screen(0,2,100,128);
		display_kaiguan_frame(1,100,F_trip_QL);
}
void Fun_LD_hezha() 
{
	 	unsigned char Array_SD[2],Array_LD[2],Array_DY[2];
	clear_screen();
	EEPROM_R(Addr_shangdian,Array_SD,1,0xA0);
	EEPROM_R(Addr_loudian,Array_LD,1,0xA0);
	EEPROM_R(Addr_dianya,Array_DY,1,0xA0);
	shangdian=Array_SD[0];
	LD_hezha=Array_LD[0];
	DY_hezha=Array_DY[0];	
	  Lcd12864_Write16CnCHAR(0,0,0,"13校准档位\r14上电合闸\r15漏电合闸\r16电压合闸");
		display_graphic_8x16(1,94,maohao);
		display_graphic_8x16(3,94,maohao);
	  display_graphic_8x16(5,94,maohao);
	  display_graphic_8x16(7,94,maohao);
	
		display_jiaozhun(1,100,jiaozhun);
	  display_kaiguan(3,100,shangdian);
	  display_kaiguan_frame(5,100,LD_hezha);
	  display_kaiguan(7,100,DY_hezha);
		
	
	  if(key_value_tmp==0x10)
		{
			LD_hezha=1;
		}
		if(key_value_tmp==0x40)
		{
			LD_hezha=0;
		}
		 if(LD_hezha==1)	Array_LD[0] = 0x01;
     if(LD_hezha==0)	Array_LD[0] = 0x00;
        MODIFY_EEP_W(Addr_loudian,Array_LD,1,0xA0);
		clear_define_screen(5,6,100,128);
		display_kaiguan_frame(5,100,LD_hezha);
}
void Fun_DY_hezha()
{
 	unsigned char Array_SD[2],Array_LD[2],Array_DY[2];
	clear_screen();
	EEPROM_R(Addr_shangdian,Array_SD,1,0xA0);
	EEPROM_R(Addr_loudian,Array_LD,1,0xA0);
	EEPROM_R(Addr_dianya,Array_DY,1,0xA0);
	shangdian=Array_SD[0];
	LD_hezha=Array_LD[0];
	DY_hezha=Array_DY[0];	
	
	  Lcd12864_Write16CnCHAR(0,0,0,"13校准档位\r14上电合闸\r15漏电合闸\r16电压合闸");
		display_graphic_8x16(1,94,maohao);
		display_graphic_8x16(3,94,maohao);
	  display_graphic_8x16(5,94,maohao);
	  display_graphic_8x16(7,94,maohao);
	
		display_jiaozhun(1,100,jiaozhun);
	  display_kaiguan(3,100,shangdian);
	  display_kaiguan(5,100,LD_hezha);
	  display_kaiguan_frame(7,100,DY_hezha);
		
	
	  if(key_value_tmp==0x10)
		{
			DY_hezha=1;
		}
		if(key_value_tmp==0x40)
		{
			DY_hezha=0;
		}
		if(DY_hezha==1)	Array_DY[0] = 0x01;
    if(DY_hezha==0)	Array_DY[0] = 0x00;
    MODIFY_EEP_W(Addr_dianya,Array_DY,1,0xA0);
		
		clear_define_screen(7,8,100,128);
		display_kaiguan_frame(7,100,DY_hezha);
}
void Fun_DL_hezha()
{
	  clear_screen();
	  unsigned char array_tmp[2];
		EEPROM_R(Addr_dianliu,array_tmp,1,0xA0);
	  DL_hezha=array_tmp[0];
	  Lcd12864_Write16CnCHAR(0,0,0,"17电流合闸");
		display_graphic_8x16(1,94,maohao);
	
	
		display_jiaozhun(1,100,DL_hezha);
	
		
	
	  if(key_value_tmp==0x10)
		{
			DL_hezha=1;
		}
		if(key_value_tmp==0x40)
		{
			DL_hezha=0;
		}
		 if(DL_hezha==1)	array_tmp[0] = 0x01;
     if(DL_hezha==0)	array_tmp[0] = 0x00;
        MODIFY_EEP_W(Addr_dianliu,array_tmp,1,0xA0);
		clear_define_screen(0,2,100,128);
		display_kaiguan_frame(1,100,DL_hezha);
}
void Fun_DZ_Set()                                   //断零保护设置
{
	   if(key_value_tmp==0x20)
		{
			key_state=key_state|F_trip_QL;
		}
	  clear_define_screen(2,4,87,120);
		display_kaiguan_fanxian(3,91,(key_state&0xFF));
}
void Fun_Vol_CH()                                   //电压重合 
{
clear_screen();
	Lcd12864_Write16CnCHAR(0,0,0,"9 欠压延时\r10断零保护\r11电压重合\r12缺零档位");
	display_graphic_8x16(1,85,maohao);
	display_graphic_8x16(3,85,maohao);
	display_graphic_8x16(5,85,maohao);
	display_graphic_8x16(7,85,maohao);

//	  display_sanjiao(1,119,0,1);
   display_ASCIIstring_8x16(1,91,QY_yanshi[D_QY_yanshi]);
	display_kaiguan(3,91,F_trip_QL);
	 display_kaiguan_frame(5,91,F_dianya_chonghe);
	display_ASCIIstring_8x16(7,91,DIANYA_up[Vol_up]);
}
void Vol_CH_Set()                                    //电压重合设置 
{
			 if(key_value_tmp==0x20)
		{
			key_state=key_state|F_dianya_chonghe;
		}
	  clear_define_screen(4,6,90,120);
		display_kaiguan_fanxian(5,91,(key_state&0xFF));
}
void Fun_QL_up()
{
   clear_screen();
   Lcd12864_Write16CnCHAR(0,0,0,"9 欠压延时\r10断零保护\r11电压重合\r12缺零档位");
	 display_graphic_8x16(1,85,maohao);
	 display_graphic_8x16(3,85,maohao);
	display_graphic_8x16(5,85,maohao);
	display_graphic_8x16(7,85,maohao);

//	  display_sanjiao(1,119,0,1);
   display_ASCIIstring_8x16(1,91,QY_yanshi[D_QY_yanshi]);
	display_kaiguan(3,91,F_trip_QL);
	 display_kaiguan(5,91,F_dianya_chonghe);
	display_ASCIIstring_8x16_frame(7,91,DIANYA_up[Vol_up]);
}
void QL_up_Set()
{
		if(key_value_tmp==0x20)
		{
			key_state=key_state|Vol_up;
		}
	  clear_define_screen(6,8,90,120);
		display_ASCIIstring_8x16_fanxian(7,91,DIANYA_up[(key_state&0xFF)]); 
}
void Fun_QL_down()
{
   clear_screen();
 	 Lcd12864_Write16CnCHAR(0,0,0,"13缺零档位");
	 display_graphic_8x16(1,85,maohao);
	 display_ASCIIstring_8x16_frame(1,91,DIANYA_down[Vol_down]);
}
void QL_down_Set()
{
		if(key_value_tmp==0x20)
		{
			key_state=key_state|Vol_down;
		}
	  clear_define_screen(0,2,90,120);
		display_ASCIIstring_8x16_fanxian(1,91,DIANYA_down[(key_state&0xFF)]); 
}
void Fun_DL()                                       //电流设置
{
if((key_value_tmp==0x40)||(key_value_tmp==0x01))//退出键或者向上键
{
clear_screen();
	Lcd12864_Write16CnCHAR(0,16,0,"1漏电设置\r  2电压设置\r  3电流设置\r  4记录查询");
}
else
		{
		 clear_define_screen(0,16,91,116);
		}
//			display_sanjiao(1,116,0,1);
			display_shouzhi(5,95);
//	if(F_initial_lcd==1)
//	{
//		F_initial_lcd=0;
//	}
}
void Fun_OP()                                       //过流保护
{
	unsigned char array_tmp[3];
	  clear_screen();
	Lcd12864_Write16CnCHAR(0,0,0,"9失压保护\r10过流保护\r11短延保护\r12瞬时保护");
	display_graphic_8x16(1,94,maohao);
	display_graphic_8x16(3,94,maohao);
	display_graphic_8x16(5,94,maohao);
	display_graphic_8x16(7,94,maohao);

//	  display_sanjiao(1,119,0,1);
	  display_kaiguan(1,100,F_trip_sy);
   display_kaiguan(3,100,F_trip_gl);	
	  display_kaiguan(5,100,F_ip);
	  display_kaiguan(7,100,F_ip_3);
	
	
	
	
	
	if(key_value_tmp==0x10)
		{
			F_trip_gl=1;
		}
		if(key_value_tmp==0x40)
		{
			F_trip_gl=0;
		}
    if(F_trip_gl==1)ctrlword[1]|=0x01 ;
    if(F_trip_gl==0)ctrlword[1]&=(~0x01);
    array_tmp[0]=ctrlword[1];
    MODIFY_EEP_W(Addr_crtl_word2,array_tmp,1,0xA0);		
	  clear_define_screen(2,4,100,128);
		display_kaiguan_frame(3,100,F_trip_gl);
}
void Fun_OP_Set()                                      //过流保护设置
{
if(key_value_tmp==0x20)
		{
			key_state=key_state|F_trip_gl;
		}
	  clear_define_screen(0,2,83,106);
		display_kaiguan_fanxian(1,83,(key_state&0xFF));
}

void Fun_OP_Val()                                      //过流档位 
{
	  unsigned char array_tmp[3];
	  clear_screen();
		Lcd12864_Write16CnCHAR(0,0,0,"9过流档位\r10过流时间\r11短延档位\r12短延时间");
		display_graphic_8x16(1,84,maohao);
		display_graphic_8x16(3,84,maohao);
		display_graphic_8x16(5,84,maohao);
		display_graphic_8x16(7,84,maohao);
//    display_sanjiao(1,119,1,1);
	  I_VAL_handle();
  	xianshishuju_dianliu(SET_I_VAL);
		display_ASCIIstring_8x16_frame(1,93,zifu_dian);    
	  display_ASCIIstring_8x16(3,93,GUOLIU_T[TH_Long_Cur]);
    display_ASCIIstring_8x16(5,93,D2_DW[D2_Cur]);
	  display_ASCIIstring_8x16(7,93,D2_T[TH_DL]);
	  if(F_queren==1)
	   {
		   dianliu_dang=D_Cur;
	     key_state=key_state|D_Cur;
	   }
	  if((key_value_tmp==0x20)&&(F_queren<3))
     {
		  F_queren++;
	   }	
		 D_Cur=key_state&0xFF;
		 clear_define_screen(0,2,93,128);	
		 I_VAL_handle();
		 delay_us(10);
	   xianshishuju_dianliu(SET_I_VAL);	
	   display_ASCIIstring_8x16_fanxian(1,93,zifu_dian);
		 if((key_value_tmp==0x20)&&(F_queren==3))
	   {
		   D_Cur=key_state-0x25100 ;
       array_tmp[0]=D_Cur ;
       MODIFY_EEP_W(Addr_D_Cur,array_tmp,1,0xA0);
			 Cur_Switch(Type_Cur);
			 EEPROM_R(Addr_D_Cur,array_tmp,1,0xA0);
		   clear_define_screen(0,2,93,128);	
		   I_VAL_handle();
		   delay_us(10);
	     xianshishuju_dianliu(SET_I_VAL);	
	     display_ASCIIstring_8x16_fanxian(1,93,zifu_dian);
       key_state=0x26100;		
		   F_queren=1;
	   }
}



void OP_Val_Set()                                     //过流档位设置
{
if(key_value_tmp==0x20)
	{
		dianliu_dang=D_Cur;
	  key_state=key_state|D_Cur;
	
	}
		
		D_Cur=key_state&0xFF;
		clear_define_screen(2,4,82,128);	
		I_VAL_handle();
		delay_us(10);

	  xianshishuju_dianliu(SET_I_VAL);
	
	 display_ASCIIstring_8x16_fanxian(3,83,zifu_dian);    
}
void Fun_OP_T()                                       //过流时间
{
		unsigned char array_tmp[3];
	  clear_screen();
		Lcd12864_Write16CnCHAR(0,0,0,"9过流档位\r10过流时间\r11短延档位\r12短延时间");
		display_graphic_8x16(1,84,maohao);
		display_graphic_8x16(3,84,maohao);
		display_graphic_8x16(5,84,maohao);
		display_graphic_8x16(7,84,maohao);

	  I_VAL_handle();
  	xianshishuju_dianliu(SET_I_VAL);
		display_ASCIIstring_8x16(1,93,zifu_dian);    
	  display_ASCIIstring_8x16_frame(3,93,GUOLIU_T[TH_Long_Cur]);
    display_ASCIIstring_8x16(5,93,D2_DW[D2_Cur]);
	  display_ASCIIstring_8x16(7,93,D2_T[TH_DL]);
	  
	  if(F_queren==1)
	   {
	     key_state=key_state|TH_Long_Cur;
	   }
		 if((key_value_tmp==0x20)&&(F_queren<3))
	   {
		   F_queren++;
	   }
	  clear_define_screen(2,4,93,128);
	  display_ASCIIstring_8x16_fanxian(3,93,GUOLIU_T[(key_state&0xFF)]);	
	  if((key_value_tmp==0x20)&&(F_queren==3))
	    {
		    TH_Long_Cur=key_state-0x26100 ;
				array_tmp[0]=TH_Long_Cur ;
				MODIFY_EEP_W(Addr_CurLong_Time,array_tmp,1,0xA0);
				Cur_Switch(Type_Cur);
				EEPROM_R(Addr_CurLong_Time,array_tmp,1,0xA0);
		    clear_define_screen(2,4,93,128);
	      display_ASCIIstring_8x16_frame(3,93,GUOLIU_T[TH_Long_Cur]);
        key_state=0x27100;		
		    F_queren=1;
	}
	  
}


void OP_T_Set()                                       //过流时间设置
{
	if(key_value_tmp==0x20)
	{
	   key_state=key_state|TH_Long_Cur;
	
	}
		clear_define_screen(4,6,82,128);
	   display_ASCIIstring_8x16_fanxian(5,83,GUOLIU_T[(key_state&0xFF)]);
}
void Fun_S_Delay()                                    //短延保护
{
	unsigned char array_tmp[3];
	clear_screen();
	Lcd12864_Write16CnCHAR(0,0,0,"9失压保护\r10过流保护\r11短延保护\r12瞬时保护");
	display_graphic_8x16(1,94,maohao);
	display_graphic_8x16(3,94,maohao);
	display_graphic_8x16(5,94,maohao);
	display_graphic_8x16(7,94,maohao);

//	  display_sanjiao(1,119,0,1);
	  display_kaiguan(1,100,F_trip_sy);
   display_kaiguan(3,100,F_trip_gl);	
	  display_kaiguan(5,100,F_ip);
	  display_kaiguan(7,100,F_ip_3);
	
	
	if(key_value_tmp==0x10)
		{
			F_ip=1;
		}
		if(key_value_tmp==0x40)
		{
			F_ip=0;
		}
    if(F_ip==1)	array_tmp[0] = 0x01 ;
    if(F_ip==0)	array_tmp[0] = 0x00;
    MODIFY_EEP_W(Addr_I_2d,array_tmp,1,0xA0);	
	  clear_define_screen(4,6,100,128);
		display_kaiguan_frame(5,100,F_ip);
}
void S_Delay_Set()                                   //短延保护设置
{
if(key_value_tmp==0x20)
		{
			key_state=key_state|F_ip;
		}
	  clear_define_screen(6,8,83,99);
		display_kaiguan_fanxian(7,83,(key_state&0xFF));
}
void Fun_Delay_Val()                                 //短延档位
{
    unsigned char array_tmp[3];
	  clear_screen();
		Lcd12864_Write16CnCHAR(0,0,0,"9过流档位\r10过流时间\r11短延档位\r12短延时间");
		display_graphic_8x16(1,84,maohao);
		display_graphic_8x16(3,84,maohao);
		display_graphic_8x16(5,84,maohao);
		display_graphic_8x16(7,84,maohao);

	  I_VAL_handle();
  	xianshishuju_dianliu(SET_I_VAL);
		display_ASCIIstring_8x16(1,93,zifu_dian);    
	  display_ASCIIstring_8x16(3,93,GUOLIU_T[TH_Long_Cur]);
    display_ASCIIstring_8x16_frame(5,93,D2_DW[D2_Cur]);
	  display_ASCIIstring_8x16(7,93,D2_T[TH_DL]);
	  
	   if(F_queren==1)
	   {
	     key_state=key_state|D2_Cur;
	   }
		 if((key_value_tmp==0x20)&&(F_queren<3))
	   {
		   F_queren++;
	   }
	  clear_define_screen(4,6,93,128);
	  display_ASCIIstring_8x16_fanxian(5,93,D2_DW[(key_state&0xFF)]);
		 
		 	  if((key_value_tmp==0x20)&&(F_queren==3))
	    {
		    D2_Cur=key_state-0x27100 ;
				array_tmp[0]=D2_Cur ;
				MODIFY_EEP_W(Addr_D2_Cur,array_tmp,1,0xA0);
				Cur_Switch(Type_Cur);
				F_ent=1 ;
				EEPROM_R(Addr_D2_Cur,array_tmp,1,0xA0);
		    clear_define_screen(4,6,93,128);
	      display_ASCIIstring_8x16_frame(5,93,D2_DW[D2_Cur]);
        key_state=0x28100;		
		    F_queren=1;
	    }
		 
}


void Delay_Val_Set()                                   //短延档位设置
{
 if(key_value_tmp==0x20)
		{
			key_state=key_state|D2_Cur;
		}
		 clear_define_screen(0,2,82,120);
      display_ASCIIstring_8x16_fanxian(1,83,D2_DW[key_state&0xFF]);
}
void Fun_Delay_T()                                     //短延时间
{
    unsigned char array_tmp[3];
	  clear_screen();
		Lcd12864_Write16CnCHAR(0,0,0,"9过流档位\r10过流时间\r11短延档位\r12短延时间");
		display_graphic_8x16(1,84,maohao);
		display_graphic_8x16(3,84,maohao);
		display_graphic_8x16(5,84,maohao);
		display_graphic_8x16(7,84,maohao);

	  I_VAL_handle();
  	xianshishuju_dianliu(SET_I_VAL);
		display_ASCIIstring_8x16(1,93,zifu_dian);    
	  display_ASCIIstring_8x16(3,93,GUOLIU_T[TH_Long_Cur]);
    display_ASCIIstring_8x16(5,93,D2_DW[D2_Cur]);
	  display_ASCIIstring_8x16_frame(7,93,D2_T[TH_DL]);
	  
	  if(F_queren==1)
	   {
	     key_state=key_state|TH_DL;
	   }
		 if((key_value_tmp==0x20)&&(F_queren<3))
	   {
		   F_queren++;
	   }
	  clear_define_screen(6,8,93,128);
	  display_ASCIIstring_8x16_fanxian(7,93,D2_T[(key_state&0xFF)]);
		 
		 	  if((key_value_tmp==0x20)&&(F_queren==3))
	    {
		    TH_DL=key_state-0x28100 ;
				array_tmp[0]=TH_DL ;
				MODIFY_EEP_W(Addr_D2_Time,array_tmp,1,0xA0);
				Cur_Switch(Type_Cur);
				F_ent=1 ;
				EEPROM_R(Addr_D2_Time,array_tmp,1,0xA0);
		    clear_define_screen(4,6,93,128);
	      display_ASCIIstring_8x16_frame(5,93,D2_T[TH_DL]);
        key_state=0x29100;		
		    F_queren=1;
	    }
}



void Delay_T_Set()                                     //短延时间设置
{
if(key_value_tmp==0x20)
		{
			key_state=key_state|TH_DL;
		}
		 clear_define_screen(2,4,82,120);

		
 	display_ASCIIstring_8x16_fanxian(3,83,D2_T[key_state&0xFF]);

}
void Fun_Instant()                                     //瞬时保护 
{
	unsigned char array_tmp[3];
	clear_screen();
	Lcd12864_Write16CnCHAR(0,0,0,"9失压保护\r10过流保护\r11短延保护\r12瞬时保护");
	display_graphic_8x16(1,94,maohao);
	display_graphic_8x16(3,94,maohao);
	display_graphic_8x16(5,94,maohao);
	display_graphic_8x16(7,94,maohao);

//	  display_sanjiao(1,119,0,1);
	  display_kaiguan(1,100,F_trip_sy);
   display_kaiguan(3,100,F_trip_gl);	
	  display_kaiguan(5,100,F_ip);
	  display_kaiguan(7,100,F_ip_3);
	
	
	if(key_value_tmp==0x10)
		{
			F_ip_3=1;
		}
		if(key_value_tmp==0x40)
		{
			F_ip_3=0;
		}
    if(F_ip_3==1)	array_tmp[0] = 0x01 ;
    if(F_ip_3==0)	array_tmp[0] = 0x00;
    MODIFY_EEP_W(Addr_I_3d,array_tmp,1,0xA0);
	  clear_define_screen(6,8,100,128);
		display_kaiguan_frame(7,100,F_ip_3);
}
void Fun_Instant_Val()                                 //瞬时档位
{
  clear_screen();
	unsigned char array_tmp[3];	
	Lcd12864_Write16CnCHAR(0,0,0,"5失压延时\r6过压延时\r7欠压延时\r8瞬时档位");
	display_graphic_8x16(1,77,maohao);
	display_graphic_8x16(3,77,maohao);
	display_graphic_8x16(5,77,maohao);
	display_graphic_8x16(7,77,maohao);

//	  display_sanjiao(1,119,0,1);
  display_ASCIIstring_8x16(1,83,SY_yanshi[D_SY_yanshi]);
	display_ASCIIstring_8x16(3,83,GY_yanshi[D_GY_yanshi]);	
	display_ASCIIstring_8x16(5,83,QY_yanshi[D_QY_yanshi]);
  display_ASCIIstring_8x16_frame(7,83,D3_DW[D3_Cur]);
	  if(F_queren==1)
	   {
	     key_state=key_state|D3_Cur;
	   }
		 if((key_value_tmp==0x20)&&(F_queren<3))
	   {
		   F_queren++;
	   }
	  clear_define_screen(6,8,82,128);
	  display_ASCIIstring_8x16_fanxian(7,83,D3_DW[(key_state&0xFF)]);
		 
		 	  if((key_value_tmp==0x20)&&(F_queren==3))
	    {
				D3_Cur=key_state-0x40100 ;
				array_tmp[0]=D3_Cur ;
				MODIFY_EEP_W(Addr_D3_Cur,array_tmp,1,0xA0);
				Cur_Switch(Type_Cur);
		    clear_define_screen(6,8,82,128);
	      display_ASCIIstring_8x16_frame(7,83,D3_DW[D3_Cur]);
        key_state=0x25100;		
		    F_queren=1;
	    }
}
void Instant_Val_Set()                                 //瞬时档位设置
{
	   if(key_value_tmp==0x20)
		{
			key_state=key_state|D3_Cur;
		}
		 clear_define_screen(6,8,82,120);
      display_ASCIIstring_8x16_fanxian(7,83,D3_DW[key_state&0xFF]);
}
void Fun_Cur_CH()                                      //电流重合     
{
		 clear_screen();
	 Lcd12864_Write16CnCHAR(0,0,0,"9电流重合");
		display_graphic_8x16(1,77,maohao);
		
//	 display_sanjiao(1,119,1,0);
	display_kaiguan_frame(1,83,F_ia);	
}
void Cur_CH_Set()                                      //电流重合设置
{
     if(key_value_tmp==0x20)
		{
			key_state=key_state|F_ia;
		}
	  clear_define_screen(0,2,87,120);
		display_kaiguan_fanxian(1,83,(key_state&0xFF));
}
void Fun_LS()                                          //记录查询
{
if((key_value_tmp==0x40)||(key_value_tmp==0x01))//退出键或者向上键
{
clear_screen();
	Lcd12864_Write16CnCHAR(0,16,0,"1漏电设置\r  2电压设置\r  3电流设置\r  4记录查询");
}
else
		{
		 clear_define_screen(0,16,91,116);
		}
//			display_sanjiao(1,116,0,1);
			display_shouzhi(7,95);
//	if(F_initial_lcd==1)
//	{
//		F_initial_lcd=0;
//	}
}
void Fun_Record()                                       //记录查询
{
     clear_screen();                             //清屏
		Lcd12864_Write16CnCHAR(0,16,0,"1历史记录\r  2跳闸次数\r");
//    display_sanjiao(1,116,0,0);
		display_shouzhi(1,95);
}
void Fun_Record_CX()                                     //记录查询内容  
{

			clear_screen();

			if((guzhang_wei==0)||(guzhang_wei==1)||(guzhang_wei==9))        //欠压/过压/缺相
		{
				display_ASCIIstring_8x16(5,110," V");	
			
		
		}
		else if(guzhang_wei==2)  //漏电
		{

				display_ASCIIstring_8x16(5,110,"mA");
		
		}
		else if(guzhang_wei==3)  //过流“GL”
		{

				display_ASCIIstring_8x16(5,110," A");
		}
		else
		{
			clear_define_screen(4,7,68,130);

		}
	
	if((key_value_tmp==0x80)||(key_value_tmp==0x01))  //向下键或者向上键
	{
		
		display_ASCIIstring_8x16(1,25,&lishijilu_1[2]);

		    Lcd12864_Write16CnCHAR(0,0,2,"类型:");
		    Lcd12864_Write16CnCHAR(0,40,2,guzhang_yuanyin[guzhang_wei]);
				Lcd12864_Write16CnCHAR(0,72,2,"分闸");
		
		  Lcd12864_Write16CnCHAR(0,0,4,"故障值:");
			display_ASCIIstring_8x16(5,77,lishijilu_2);	

		
		
		
						display_ASCIIstring_8x16(7,8,nian);
				display_graphic_8x16(7,24,qirigang);	
				display_ASCIIstring_8x16(7,29,yue);
				display_graphic_8x16(7,45,qirigang);	
				display_ASCIIstring_8x16(7,50,ri);
				
				display_graphic_8x16(7,65,xiaogang);	
				display_ASCIIstring_8x16(7,71,shi);
				display_graphic_8x16(7,87,xiaomaohao);	
				display_ASCIIstring_8x16(7,92,fen);
				display_graphic_8x16(7,108,xiaomaohao);	
				display_ASCIIstring_8x16(7,113,miao);
		
		
		
		
	}

		Lcd12864_Write16CnCHAR(0,0,0,"近   次跳闸信息\r");
		display_ASCIIstring_8x16(1,25,&lishijilu_1[2]);
	
       	Lcd12864_Write16CnCHAR(0,0,2,"类型:");
		    Lcd12864_Write16CnCHAR(0,40,2,guzhang_yuanyin[guzhang_wei]);
				Lcd12864_Write16CnCHAR(0,72,2,"分闸");
	
		Lcd12864_Write16CnCHAR(0,0,4,"故障值:");
		display_ASCIIstring_8x16(5,77,lishijilu_2);	
		

	
						display_ASCIIstring_8x16(7,8,nian);
				display_graphic_8x16(7,24,qirigang);	
				display_ASCIIstring_8x16(7,29,yue);
				display_graphic_8x16(7,45,qirigang);	
				display_ASCIIstring_8x16(7,50,ri);
				
				display_graphic_8x16(7,65,xiaogang);	
				display_ASCIIstring_8x16(7,71,shi);
				display_graphic_8x16(7,87,xiaomaohao);	
				display_ASCIIstring_8x16(7,92,fen);
				display_graphic_8x16(7,108,xiaomaohao);	
				display_ASCIIstring_8x16(7,113,miao);


}

void Fun_Shiyan_CX()                                     //记录查询内容  
{

	clear_screen();
	if((key_value_tmp==0x80)||(key_value_tmp==0x01))  //向下键或者向上键
	{ 

		
		
		Lcd12864_Write16CnCHAR(0,0,0,"近   次试验信息\r");

		
		Lcd12864_Write16CnCHAR(0,0,2,"类型: ");
		
		


		Lcd12864_Write16CnCHAR(0,0,4,"结果:");

	  	unsigned int  N_Selftest;
		
			N_Selftest = key_state - 0x43100;  //421
			N_Selftest=N_Selftest+1;
			Get_Selftest_Record(N_Selftest);   //
		
		if(array_temps[7]==0x0E)
		{
		Lcd12864_Write16CnCHAR(0,40,2,"按键试跳");
		}
		else if(array_temps[7]==0x0D)
		{
		Lcd12864_Write16CnCHAR(0,40,2,"远程试跳");
		}
		

		 generate_chuan(ci,0,0,(N_Selftest)/10,(N_Selftest)%10);
		
		  display_ASCIIstring_8x16(1,25,&ci[2]);
		
			if(array_temps[0]==0x11)
			{
				Lcd12864_Write16CnCHAR(0,40,4,"成功");
			}
			else
			{
				Lcd12864_Write16CnCHAR(0,40,4,"失败");
			}
			
//					dispbit[0]=table[array_temps[5]>>4];
//			dispbit[1]=table[array_temps[5]&0x0F]+0x80;
			

				nian[0]=(array_temps[6]>>4)+0x30;				
				nian[1]=(array_temps[6]&0x0F)+0x30;	
				nian[2]='\0';			
			  display_ASCIIstring_8x16(7,8,nian);
				display_graphic_8x16(7,24,qirigang);	
			
				yue[0]=(array_temps[5]>>4)+0x30;				
				yue[1]=(array_temps[5]&0x0F)+0x30;	
				yue[2]='\0';
				display_ASCIIstring_8x16(7,29,yue);
				display_graphic_8x16(7,45,qirigang);

				ri[0]=(array_temps[4]>>4)+0x30;				
				ri[1]=(array_temps[4]&0x0F)+0x30;	
				ri[2]='\0';
				display_ASCIIstring_8x16(7,50,ri);
				display_graphic_8x16(7,65,xiaogang);


				shi[0]=(array_temps[3]>>4)+0x30;				
				shi[1]=(array_temps[3]&0x0F)+0x30;	
				shi[2]='\0';
				display_ASCIIstring_8x16(7,71,shi);
				display_graphic_8x16(7,87,xiaomaohao);

			
				fen[0]=(array_temps[2]>>4)+0x30;				
				fen[1]=(array_temps[2]&0x0F)+0x30;	
				fen[2]='\0';
				display_ASCIIstring_8x16(7,92,fen);
				display_graphic_8x16(7,108,xiaomaohao);

				miao[0]=(array_temps[1]>>4)+0x30;				
				miao[1]=(array_temps[1]&0x0F)+0x30;	
				miao[2]='\0';
				display_ASCIIstring_8x16(7,113,miao);
		
		
	}
//	
//	if(NUM_test!=0)
//	{
//		Lcd12864_Write16CnCHAR(0,0,0,"近   次试验信息\r");
//		display_ASCIIstring_8x16(1,25,&lishijilu_1[2]);
//		
//		
//		Lcd12864_Write16CnCHAR(0,0,2,"类型: ");
//		Lcd12864_Write16CnCHAR(0,40,2,"按键试跳");
//		
//		Lcd12864_Write16CnCHAR(0,0,4,"结果:");

//		
//		
//		
//		
//				display_ASCIIstring_8x16(7,8,nian);
//				display_graphic_8x16(7,24,qirigang);	
//				display_ASCIIstring_8x16(7,29,yue);
//				display_graphic_8x16(7,45,qirigang);	
//				display_ASCIIstring_8x16(7,50,ri);
//				
//				display_graphic_8x16(7,65,xiaogang);	
//				display_ASCIIstring_8x16(7,71,shi);
//				display_graphic_8x16(7,87,xiaomaohao);	
//				display_ASCIIstring_8x16(7,92,fen);
//				display_graphic_8x16(7,108,xiaomaohao);	
//				display_ASCIIstring_8x16(7,113,miao);
//	}
//	if(NUM_test==0)
//	{
//		clear_screen();
//		Lcd12864_Write16CnCHAR(0,0,2,"无按键试跳记录");
//	}


}
void Fun_Trip_Num()                                      //跳闸次数
{
	   if(key_value_tmp==0x40)
		{
			clear_screen();
		 	Lcd12864_Write16CnCHAR(0,16,0,"1历史记录\r  2跳闸次数\r");
		}
		else
		{
			clear_define_screen(0,16,91,116);
		}
	
//		display_xianfangkuai(3,100,0,0);
//    display_xianfangkuai(1,116,0,1);
		
//		 display_sanjiao(1,116,0,0);
		 	display_shouzhi(3,95);
}
void Trip_Num_LOCK()                                    //漏电跳闸次数
{
			clear_screen();
	Lcd12864_Write16CnCHAR(0,0,0,"1 总跳闸次数\r         次");
		Lcd12864_Write16CnCHAR(0,0,4,"2 数据清零次数\r         次");
		display_ASCIIstring_8x16(3,39,lishijilu_1);
	display_ASCIIstring_8x16(7,39,lishijilu_2);
}
void Trip_Num_LD()                                    //电压/电流跳闸次数
{
		clear_screen();
	Lcd12864_Write16CnCHAR(0,0,0,"3 闭锁跳闸次数\r         次");
		Lcd12864_Write16CnCHAR(0,0,4,"4 漏电跳闸次数\r         次");
		display_ASCIIstring_8x16(3,39,lishijilu_1);
	display_ASCIIstring_8x16(7,39,lishijilu_2);
}
void Trip_Num_DY()                                     //上电/缺零跳闸次数  
{
	clear_screen();
	Lcd12864_Write16CnCHAR(0,0,0,"5 电流跳闸次数\r         次");
		Lcd12864_Write16CnCHAR(0,0,4,"6 过压跳闸次数\r         次");
		display_ASCIIstring_8x16(3,39,lishijilu_1);
	display_ASCIIstring_8x16(7,39,lishijilu_2);
}
void Trip_Num_TEST()                                      //失压跳闸次数
{
clear_screen();
Lcd12864_Write16CnCHAR(0,0,0,"7 手动闭锁跳闸次数\r         次");
		Lcd12864_Write16CnCHAR(0,0,4,"8 按键跳闸次数\r         次");////2022.2.22发现此处应该由试验跳闸改为按键跳闸
		display_ASCIIstring_8x16(3,39,lishijilu_1);
	display_ASCIIstring_8x16(7,39,lishijilu_2);
}

void Trip_Num_Instant()                                      //失压跳闸次数
{
clear_screen();
     Lcd12864_Write16CnCHAR(0,0,0,"9 短延跳闸次数\r         次");
		Lcd12864_Write16CnCHAR(0,0,4,"10短瞬跳闸次数\r         次");
		display_ASCIIstring_8x16(3,39,lishijilu_1);
	display_ASCIIstring_8x16(7,39,lishijilu_2);
}
void Trip_Num_Check()                                      //失压跳闸次数
{
clear_screen();
Lcd12864_Write16CnCHAR(0,0,0,"11欠压跳闸次数\r         次");
		Lcd12864_Write16CnCHAR(0,0,4,"12缺相跳闸次数\r         次");
		display_ASCIIstring_8x16(3,39,lishijilu_1);
	display_ASCIIstring_8x16(7,39,lishijilu_2);
}
void Fun_Time()                                         //时间设置
{
				clear_screen();
//		if((key_value_tmp==0x40)||(key_value_tmp==0x01))//退出键或者向上键
//		{
//			clear_screen();
	Lcd12864_Write16CnCHAR(0,16,0,"5时间设置\r  6系统设置\r  7校准设置");
//		}
//		else
//		{
//		 clear_define_screen(0,16,91,116);
//		}
		
//	display_sanjiao(1,116,1,0);
			display_shouzhi(1,95);
//	if(F_initial_lcd==1)
//	{
//		F_initial_lcd=0;
//	}
}
void Fun_Time_Y()                                     //时间设置-年
{
	  u8 year_tmp,key_tmp;	
    if((key_value_tmp==0x20)&&(F_year_gengxin==1))
		  {
				Sf_function_process();
			  F_year_gengxin=0;
		  }
		clear_screen();
	  Lcd12864_Write16CnCHAR(0,0,0,"13通信速率\r14壳架设置");
		display_graphic_8x16(1,85,maohao);
		display_graphic_8x16(3,85,maohao);
    display_ASCIIstring_8x16(1,92,botelv[baud]);
		Disp_date();
		Disp_time();
	   if(Type_cur_Temp==0)
			{
				display_ASCIIstring_8x16(3,92,"125A");

			}
			if(Type_cur_Temp==1)
			{
				display_ASCIIstring_8x16(3,92,"250A");

			}
			else if(Type_cur_Temp==2)
			{
				display_ASCIIstring_8x16(3,92,"400A");

			}
			else if(Type_cur_Temp==3)
			{
				display_ASCIIstring_8x16(3,92,"630A");
				
			}
	    else if(Type_cur_Temp==4)
			{
				display_ASCIIstring_8x16(3,92,"800A");

			}
	  display_ASCIIstring_8x16_frame(5,71,nian);
		RTC_Readtime();
		if(F_queren==1)
	 {
	   year_tmp = ((tim_y3>>4)*10)+(tim_y3&0x0F);	
		 key_state = key_state+year_tmp;		
	 }
	  if((key_value_tmp==0x40)||(key_value_tmp==0x10)||(key_value_tmp==0x20)&&(F_queren<3))
	 {
		F_queren++;
	 }
	 key_tmp =  key_state&0xFF;
	 if(key_tmp>99) key_tmp = 0;
	 tim_y3=((key_tmp/10)<<4)+(key_tmp%10);
	 Disp_Write_time();
	 display_ASCIIstring_8x16_fanxian(5,71,nian);			
	 F_year_gengxin=1;
   if((key_value_tmp==0x20)&&(F_queren==3))
	 {
		 RTC_Set_Time(tim_h3,tim_f3,tim_s3);
	   RTC_Set_Date(tim_y3,tim_m3,tim_d3);
     key_state=0x2C100;		
		 F_queren=1;
	 }	
	 if((key_value_tmp==0x10)&&(F_queren==3)) 
   {					
		 key_state=0x2D101;
		 F_queren=1;
	 }
	 if((key_value_tmp==0x40)&&(F_queren==3)) 
   {					
		 key_state=0x2C100;
		 F_queren=1;
	 }	 
	
}
void Time_Y_Set()                                    //年设置
{
	u8 year_tmp,key_tmp;
    clear_screen();
	RTC_Readtime();
	if(key_value_tmp==0x20)
	{
 		year_tmp = ((tim_y3>>4)*10)+(tim_y3&0x0F);	
		key_state = key_state+year_tmp;			
	}
	key_tmp =  key_state&0xFF;
	if(key_tmp>99) key_tmp = 0;
	tim_y3=((key_tmp/10)<<4)+(key_tmp%10);
	Disp_Write_time();
	display_ASCIIstring_8x16_fanxian(4,21,nian);			
	F_year_gengxin=1;	
}

void Fun_Time_M()                                           //月
{
	u8 month_tmp,key_tmp;
	if(key_value_tmp==0x20)
	{
		Sf_function_process();
	}	
   clear_screen();
	  Lcd12864_Write16CnCHAR(0,0,0,"13通信速率\r14壳架设置");
		display_graphic_8x16(1,85,maohao);
		display_graphic_8x16(3,85,maohao);
    display_ASCIIstring_8x16(1,92,botelv[baud]);
		Disp_date();
		Disp_time();
	   if(Type_cur_Temp==0)
			{
				display_ASCIIstring_8x16(3,92,"125A");

			}
			if(Type_cur_Temp==1)
			{
				display_ASCIIstring_8x16(3,92,"250A");

			}
			else if(Type_cur_Temp==2)
			{
				display_ASCIIstring_8x16(3,92,"400A");

			}
			else if(Type_cur_Temp==3)
			{
				display_ASCIIstring_8x16(3,92,"630A");
				
			}
	    else if(Type_cur_Temp==4)
			{
				display_ASCIIstring_8x16(3,92,"800A");

			}
	 display_ASCIIstring_8x16_frame(5,92,yue);
	 RTC_Readtime();
		if(F_queren==1)
	 {
 		month_tmp = ((tim_m3>>4)*10)+(tim_m3&0x0F);	
		key_state = key_state+month_tmp;			
	 }
	  if((key_value_tmp==0x40)||(key_value_tmp==0x10)||(key_value_tmp==0x20)&&(F_queren<3))
	 {
		F_queren++;
	 }
	 key_tmp =  key_state&0xFF;
	 if(key_tmp>13) key_tmp = 0;
	 tim_m3=((key_tmp/10)<<4)+(key_tmp%10);
 	 Disp_Write_time();
	 display_ASCIIstring_8x16_fanxian(5,92,yue);
	 if((key_value_tmp==0x20)&&(F_queren==3))
	 {
		 RTC_Set_Time(tim_h3,tim_f3,tim_s3);
	   RTC_Set_Date(tim_y3,tim_m3,tim_d3);
     key_state=0x2D101;		
		 F_queren=1;
	 }
	 	 if((key_value_tmp==0x10)&&(F_queren==3)) 
   {					
		 key_state=0x2B100;
		 F_queren=1;
	 }
	 if((key_value_tmp==0x40)&&(F_queren==3)) 
   {					
		 key_state=0x2D101;
		 F_queren=1;
	 }
}
void Time_M_Set()                                         //月设置
{
	u8 month_tmp,key_tmp;
	RTC_Readtime();
	
	if(key_value_tmp==0x20)
	{
 		month_tmp = ((tim_m3>>4)*10)+(tim_m3&0x0F);	
		key_state = key_state+month_tmp;			
	}
	key_tmp =  key_state&0xFF;
	if(key_tmp>13) key_tmp = 0;
	tim_m3=((key_tmp/10)<<4)+(key_tmp%10);
	Disp_Write_time();
	display_ASCIIstring_8x16_fanxian(4,53,yue);
}
void Fun_Time_D()                                         //日
{
	u8 day_tmp,key_tmp;
  if(key_value_tmp==0x20)
		{
		  Sf_function_process();
		}
   clear_screen();
	  Lcd12864_Write16CnCHAR(0,0,0,"13通信速率\r14壳架设置");
		display_graphic_8x16(1,85,maohao);
		display_graphic_8x16(3,85,maohao);
    display_ASCIIstring_8x16(1,92,botelv[baud]);
		Disp_date();
		Disp_time();
	   if(Type_cur_Temp==0)
			{
				display_ASCIIstring_8x16(3,92,"125A");

			}
			if(Type_cur_Temp==1)
			{
				display_ASCIIstring_8x16(3,92,"250A");

			}
			else if(Type_cur_Temp==2)
			{
				display_ASCIIstring_8x16(3,92,"400A");

			}
			else if(Type_cur_Temp==3)
			{
				display_ASCIIstring_8x16(3,92,"630A");
				
			}
	    else if(Type_cur_Temp==4)
			{
				display_ASCIIstring_8x16(3,92,"800A");

			}
		display_ASCIIstring_8x16_frame(5,113,ri);
   	RTC_Readtime();
		if(F_queren==1)
	 {
 		day_tmp = ((tim_d3>>4)*10)+(tim_d3&0x0F);	
		key_state = key_state+day_tmp-1;//1-31日，日期设置键值0x2D101			
	 }
	  if((key_value_tmp==0x40)||(key_value_tmp==0x10)||(key_value_tmp==0x20)&&(F_queren<3))
	 {
		F_queren++;
	 }
	  key_tmp =  key_state&0xFF;
	  if(key_tmp>31) key_tmp = 0;
	  tim_d3=((key_tmp/10)<<4)+(key_tmp%10);						
	  Disp_Write_time();
	  display_ASCIIstring_8x16_fanxian(5,113,ri);
	 	 if((key_value_tmp==0x20)&&(F_queren==3))
	 {
		 RTC_Set_Time(tim_h3,tim_f3,tim_s3);
	   RTC_Set_Date(tim_y3,tim_m3,tim_d3);
     key_state=0x2E100;		
		 F_queren=1;
	 }
	 	 if((key_value_tmp==0x10)&&(F_queren==3)) 
   {					
		 key_state=0x2C100;
		 F_queren=1;
	 }
	 if((key_value_tmp==0x40)&&(F_queren==3)) 
   {					
		 key_state=0x2B100;
		 F_queren=1;
	 }
}
void Time_D_Set()                                         //日设置
{
	u8 day_tmp,key_tmp;
	clear_screen();
	RTC_Readtime();
	if(key_value_tmp==0x20)
	{
 		day_tmp = ((tim_d3>>4)*10)+(tim_d3&0x0F);	
		key_state = key_state+day_tmp;			
	}
	key_tmp =  key_state&0xFF;
	if(key_tmp>31) key_tmp = 0;
	tim_d3=((key_tmp/10)<<4)+(key_tmp%10);						
	Disp_Write_time();
	display_ASCIIstring_8x16_fanxian(4,86,ri);
}
void Fun_Time_H()                                    //时
{
	 u8 hour_tmp,key_tmp;
   if(key_value_tmp==0x20)
		{
			Sf_function_process();
		}
   clear_screen();
	  Lcd12864_Write16CnCHAR(0,0,0,"13通信速率\r14壳架设置");
		display_graphic_8x16(1,85,maohao);
		display_graphic_8x16(3,85,maohao);
    display_ASCIIstring_8x16(1,92,botelv[baud]);
		Disp_date();
		Disp_time();
	   if(Type_cur_Temp==0)
			{
				display_ASCIIstring_8x16(3,92,"125A");

			}
			if(Type_cur_Temp==1)
			{
				display_ASCIIstring_8x16(3,92,"250A");

			}
			else if(Type_cur_Temp==2)
			{
				display_ASCIIstring_8x16(3,92,"400A");

			}
			else if(Type_cur_Temp==3)
			{
				display_ASCIIstring_8x16(3,92,"630A");
				
			}
	    else if(Type_cur_Temp==4)
			{
				display_ASCIIstring_8x16(3,92,"800A");

			}
	display_ASCIIstring_8x16_frame(7,71,shi);
	RTC_Readtime();	
		if(F_queren==1)
	 {
 		hour_tmp = ((tim_h3>>4)*10)+(tim_h3&0x0F);	
		key_state = key_state+hour_tmp;			
	 }
	  if((key_value_tmp==0x40)||(key_value_tmp==0x10)||(key_value_tmp==0x20)&&(F_queren<3))
	 {
		F_queren++;
	 }
	key_tmp =  key_state&0xFF;
	if(key_tmp>24) key_tmp = 0;
	tim_h3=((key_tmp/10)<<4)+(key_tmp%10);
	Disp_Write_time();			
	display_ASCIIstring_8x16_fanxian(7,71,shi);
	 	 if((key_value_tmp==0x20)&&(F_queren==3))
	 {
		 RTC_Set_Time(tim_h3,tim_f3,tim_s3);
	   RTC_Set_Date(tim_y3,tim_m3,tim_d3);
     key_state=0x2F100;		
		 F_queren=1;
	 }
	 	 if((key_value_tmp==0x10)&&(F_queren==3)) 
   {					
		 key_state=0x30100;
		 F_queren=1;
	 }
	 if((key_value_tmp==0x40)&&(F_queren==3)) 
   {					
		 key_state=0x2F100;
		 F_queren=1;
	 }
}
void Time_H_Set()                                       //时设置
{
	u8 hour_tmp,key_tmp;
	clear_screen();
	RTC_Readtime();	
	if(key_value_tmp==0x20)
	{
 		hour_tmp = ((tim_h3>>4)*10)+(tim_h3&0x0F);	
		key_state = key_state+hour_tmp;			
	}
	key_tmp =  key_state&0xFF;
	if(key_tmp>24) key_tmp = 0;
	tim_h3=((key_tmp/10)<<4)+(key_tmp%10);
	Disp_Write_time();			
	display_ASCIIstring_8x16_fanxian(7,21,shi);
}
void Fun_Time_F()                                         //分
{
	u8 min_tmp,key_tmp;
	if(key_value_tmp==0x20)
	{
		Sf_function_process();
	}
   clear_screen();
	  Lcd12864_Write16CnCHAR(0,0,0,"13通信速率\r14壳架设置");
		display_graphic_8x16(1,85,maohao);
		display_graphic_8x16(3,85,maohao);
    display_ASCIIstring_8x16(1,92,botelv[baud]);
		Disp_date();
		Disp_time();
	   if(Type_cur_Temp==0)
			{
				display_ASCIIstring_8x16(3,92,"125A");

			}
			if(Type_cur_Temp==1)
			{
				display_ASCIIstring_8x16(3,92,"250A");

			}
			else if(Type_cur_Temp==2)
			{
				display_ASCIIstring_8x16(3,92,"400A");

			}
			else if(Type_cur_Temp==3)
			{
				display_ASCIIstring_8x16(3,92,"630A");
				
			}
	    else if(Type_cur_Temp==4)
			{
				display_ASCIIstring_8x16(3,92,"800A");

			}	
	display_ASCIIstring_8x16_frame(7,92,fen);
		RTC_Readtime();
		if(F_queren==1)
	 {
 		min_tmp = ((tim_f3>>4)*10)+(tim_f3&0x0F);	
		key_state = key_state+min_tmp;	
	 }
	  if((key_value_tmp==0x40)||(key_value_tmp==0x10)||(key_value_tmp==0x20)&&(F_queren<3))
	 {
		F_queren++;
	 }
	key_tmp =  key_state&0xFF;
	if(key_tmp>60) key_tmp = 0;
	tim_f3=((key_tmp/10)<<4)+(key_tmp%10);		 
	Disp_Write_time();		
	display_ASCIIstring_8x16_fanxian(7,92,fen);
//	display_ASCIIstring_8x16(7,86,miao);
	if((key_value_tmp==0x20)&&(F_queren==3))
	 {
		 RTC_Set_Time(tim_h3,tim_f3,tim_s3);
	   RTC_Set_Date(tim_y3,tim_m3,tim_d3);
     key_state=0x30100;		
		 F_queren=1;
	 }
	 	 if((key_value_tmp==0x10)&&(F_queren==3)) 
   {					
		 key_state=0x2E100;
		 F_queren=1;
	 }
	 if((key_value_tmp==0x40)&&(F_queren==3)) 
   {					
		 key_state=0x30100;
		 F_queren=1;
	 }
}
void Time_F_Set()                                           //分设置
{
	u8 min_tmp,key_tmp;
	clear_screen();
	RTC_Readtime();
	if(key_value_tmp==0x20)
	{
 		min_tmp = ((tim_f3>>4)*10)+(tim_f3&0x0F);	
		key_state = key_state+min_tmp;			
	}
	key_tmp =  key_state&0xFF;
	if(key_tmp>60) key_tmp = 0;
	tim_f3=((key_tmp/10)<<4)+(key_tmp%10);		 
	Disp_Write_time();		
	display_ASCIIstring_8x16_fanxian(7,53,fen);
	display_ASCIIstring_8x16(7,86,miao);
}
void Fun_Time_S()                                           //秒
{
	u8 sec_tmp,key_tmp;
	if(key_value_tmp==0x20)
	{
		Sf_function_process();
	}
   clear_screen();
	  Lcd12864_Write16CnCHAR(0,0,0,"13通信速率\r14壳架设置");
		display_graphic_8x16(1,85,maohao);
		display_graphic_8x16(3,85,maohao);
    display_ASCIIstring_8x16(1,92,botelv[baud]);
		Disp_date();
		Disp_time();
	   if(Type_cur_Temp==0)
			{
				display_ASCIIstring_8x16(3,92,"125A");

			}
			if(Type_cur_Temp==1)
			{
				display_ASCIIstring_8x16(3,92,"250A");

			}
			else if(Type_cur_Temp==2)
			{
				display_ASCIIstring_8x16(3,92,"400A");

			}
			else if(Type_cur_Temp==3)
			{
				display_ASCIIstring_8x16(3,92,"630A");
				
			}
	    else if(Type_cur_Temp==4)
			{
				display_ASCIIstring_8x16(3,92,"800A");

			}
	display_ASCIIstring_8x16_frame(7,113,miao);
	RTC_Readtime();
		if(F_queren==1)
	 {
 		sec_tmp = ((tim_s3>>4)*10)+(tim_s3&0x0F);	
		key_state = key_state+sec_tmp;
	 }
	  if((key_value_tmp==0x40)||(key_value_tmp==0x10)||(key_value_tmp==0x20)&&(F_queren<3))
	 {
		F_queren++;
	 }
	key_tmp =  key_state&0xFF;
	if(key_tmp>60) key_tmp = 0;
	tim_s3=((key_tmp/10)<<4)+(key_tmp%10);			
	Disp_Write_time();
	display_ASCIIstring_8x16_fanxian(7,113,miao);
	if((key_value_tmp==0x20)&&(F_queren==3))
	 {
		 RTC_Set_Time(tim_h3,tim_f3,tim_s3);
	   RTC_Set_Date(tim_y3,tim_m3,tim_d3);
     key_state=0x50100;	
		 F_queren=1;
	 }
	 	 if((key_value_tmp==0x10)&&(F_queren==3)) 
   {					
		 key_state=0x2F100;
		 F_queren=1;
	 }
	 if((key_value_tmp==0x40)&&(F_queren==3)) 
   {					
		 key_state=0x2E100;
		 F_queren=1;
	 }
}
void Time_S_Set()                                     //秒设置
{
	u8 sec_tmp,key_tmp;
	clear_screen();
	RTC_Readtime();
	if(key_value_tmp==0x20)
	{
 		sec_tmp = ((tim_s3>>4)*10)+(tim_s3&0x0F);	
		key_state = key_state+sec_tmp;			
	}
	key_tmp =  key_state&0xFF;
	if(key_tmp>60) key_tmp = 0;
	tim_s3=((key_tmp/10)<<4)+(key_tmp%10);			
	Disp_Write_time();
	display_ASCIIstring_8x16_fanxian(7,86,miao);
}
void Fun_Sys_Set()                               //系统设置
{
		if((key_value_tmp==0x40)||(key_value_tmp==0x01))//退出键或者向上键
		{
			clear_screen();
	Lcd12864_Write16CnCHAR(0,16,0,"5时间设置\r  6系统设置\r  7校准设置");
		}
		else
		{
		 clear_define_screen(0,16,91,116);
		}
		
//	display_sanjiao(1,116,1,0);
			display_shouzhi(3,95);
//	if(F_initial_lcd==1)
//	{
//		F_initial_lcd=0;
//	}
}
void Fun_SD_hezha()                              //上电合闸
{
	
	unsigned char Array_SD[2],Array_LD[2],Array_DY[2];
	clear_screen();
	EEPROM_R(Addr_shangdian,Array_SD,1,0xA0);
	EEPROM_R(Addr_loudian,Array_LD,1,0xA0);
	EEPROM_R(Addr_dianya,Array_DY,1,0xA0);
	shangdian=Array_SD[0];
	LD_hezha=Array_LD[0];
	DY_hezha=Array_DY[0];
	 Lcd12864_Write16CnCHAR(0,0,0,"13校准档位\r14上电合闸\r15漏电合闸\r16电压合闸");
		display_graphic_8x16(1,94,maohao);
		display_graphic_8x16(3,94,maohao);
	  display_graphic_8x16(5,94,maohao);
	  display_graphic_8x16(7,94,maohao);
	
		display_jiaozhun(1,100,jiaozhun);
	  display_kaiguan_frame(3,100,shangdian);
	  display_kaiguan(5,100,LD_hezha);
	  display_kaiguan(7,100,DY_hezha);
	
	if(key_value_tmp==0x10)
		{
			shangdian=1;
		}
		if(key_value_tmp==0x40)
		{
			shangdian=0;
		}
		 if(shangdian==1)	Array_SD[0] = 0x01;
     if(shangdian==0)	Array_SD[0] = 0x00;
        MODIFY_EEP_W(Addr_shangdian,Array_SD,1,0xA0);
	  clear_define_screen(3,4,100,120);
		display_kaiguan_frame(3,100,shangdian);
}
void Fun_TD_fenzha()                                 //停电分闸
{
//    clear_screen();
//	   unsigned char array_tmp[3];
//	  Lcd12864_Write16CnCHAR(0,0,0,"13校准档位\r14断零保护");
//		display_graphic_8x16(1,94,maohao);
//		display_graphic_8x16(3,94,maohao);
//		display_graphic_8x16(5,94,maohao);
//	
//		display_jiaozhun(1,100,jiaozhun);
//	  display_kaiguan_frame(3,100,duandian);
//		display_kaiguan(5,100,F_trip_QL);		
//	  EEPROM_R(Addr_jiaozhun,array_tmp,1,0xA0);
//	  F_Corr=jiaozhun=array_tmp[0];
//	  if(key_value_tmp==0x10)
//		{
//			duandian=1;
//		}
//		if(key_value_tmp==0x40)
//		{
//			duandian=0;
//		}
//     if(duandian==1)	array_tmp[0] = 0x01 ;
//     if(duandian==0)	array_tmp[0] = 0x00;
//     MODIFY_EEP_W(Addr_duandian,array_tmp,1,0xA0);
//     clear_define_screen(2,4,100,128);
//		 display_kaiguan_frame(3,100,duandian);
}
void TD_fenzha_Set()                                   //停电分闸设置
{
		 if(key_value_tmp==0x20)
		{
			key_state=key_state|duandian;
		}
	  clear_define_screen(2,4,82,120);
		display_kaiguan_fanxian(3,83,(key_state&0xFF));
}
void Fun_Com_S()                                      //通信速率
{
	  unsigned char array_tmp[3];
    clear_screen();
	  Lcd12864_Write16CnCHAR(0,0,0,"13通信速率\r14壳架设置");
		display_graphic_8x16(1,85,maohao);
		display_graphic_8x16(3,85,maohao);
		Disp_date();
		Disp_time();
    display_ASCIIstring_8x16_frame(1,92,botelv[baud]);
		 if(Type_Cur==0)
			{
				display_ASCIIstring_8x16(3,92,"125A");

			}
			if(Type_Cur==1)
			{
				display_ASCIIstring_8x16(3,92,"250A");

			}
			else if(Type_Cur==2)
			{
				display_ASCIIstring_8x16(3,92,"400A");

			}
			else if(Type_Cur==3)
			{
				display_ASCIIstring_8x16(3,92,"630A");
			}
			else if(Type_Cur==4)
			{
				display_ASCIIstring_8x16(3,92,"800A");
			}
			 if(F_queren==1)
	   {
	     key_state=key_state|baud;
	   }
		 if((key_value_tmp==0x20)&&(F_queren<3))
	   {
		   F_queren++;
	   }
	  clear_define_screen(0,2,91,128);
	  display_ASCIIstring_8x16_fanxian(1,92,botelv[(key_state&0xFF)]);
		 
		 	  if((key_value_tmp==0x20)&&(F_queren==3))
	    {
		    baud=key_state&0xFF;
				array_tmp[0]=baud ;
				MODIFY_EEP_W(Addr_baud,array_tmp,1,0xA0); 
				if(baud==3)
				{
					RS485_Init(9600);	
				}
				else if(baud==2)
				{
					RS485_Init(4800);	
				}
				else if(baud==1)
				{
					RS485_Init(2400);	
				}
				else if(baud==0)
				{
					RS485_Init(1200);	
				}
				EEPROM_R(Addr_baud,array_tmp,1,0xA0);
		    clear_define_screen(0,2,91,128);
	      display_ASCIIstring_8x16_frame(1,92,botelv[baud]);
        key_state=0x2A100;		
		    F_queren=1;
	    }
}


void Com_S_Set()                                    //通信速率设置
{
if(key_value_tmp==0x20)
		{
			key_state=key_state|baud;

		}	
		clear_define_screen(4,6,82,120);
		display_ASCIIstring_8x16_fanxian(5,83,botelv[(key_state&0xFF)]);
}
void Fun_Type_Cur()                                 //壳架等级
{
    unsigned char array_tmp[3];
    clear_screen();
	  Type_Cur_temp=Type_Cur;
	  Lcd12864_Write16CnCHAR(0,0,0,"13通信速率\r14壳架设置");
		display_graphic_8x16(1,85,maohao);
		display_graphic_8x16(3,85,maohao);
    display_ASCIIstring_8x16(1,92,botelv[baud]);
		Disp_date();
		Disp_time();
//		 if(Type_Cur==0)
//			{
//				display_ASCIIstring_8x16_frame(3,92,"800A");

//			}
//			if(Type_Cur==1)
//			{
//				display_ASCIIstring_8x16_frame(3,92,"250A");

//			}
//			else if(Type_Cur==2)
//			{
//				display_ASCIIstring_8x16_frame(3,92,"400A");

//			}
//			else if(Type_Cur==3)
//			{
//				display_ASCIIstring_8x16_frame(3,92,"630A");
//			}
			 if(F_queren==1)
	   {
	     key_state=key_state|Type_Cur;
	   }
		 if((key_value_tmp==0x20)&&(F_queren<3))
	   {
		   F_queren++;
	   }
		 Type_cur_Temp=key_state&0x0F;
	   clear_define_screen(2,4,91,128);
	   if(Type_cur_Temp==0)
			{
				display_ASCIIstring_8x16_fanxian(3,92,"125A");

			}
			if(Type_cur_Temp==1)
			{
				display_ASCIIstring_8x16_fanxian(3,92,"250A");

			}
			else if(Type_cur_Temp==2)
			{
				display_ASCIIstring_8x16_fanxian(3,92,"400A");

			}
			else if(Type_cur_Temp==3)
			{
				display_ASCIIstring_8x16_fanxian(3,92,"630A");
			}
	    else if(Type_cur_Temp==4)
			{
				display_ASCIIstring_8x16_fanxian(3,92,"800A");

			}
		 
		 	  if((key_value_tmp==0x20)&&(F_queren==3))
	    {
		    array_tmp[0]=Type_cur_Temp;				
				MODIFY_EEP_W(Addr_Type_Cur,array_tmp,1,0xA0);
				EEPROM_R(Addr_Type_Cur,array_tmp,1,0xA0);
		     Type_Cur=	array_tmp[0];
			if(Type_Cur_temp!=Type_Cur)
			{
				Type_Cur_change=1;
      if(Type_Cur==0)
			{
				{
					D_Cur=8;
					array_tmp[0]=D_Cur ;
					MODIFY_EEP_W(Addr_D_Cur,array_tmp,1,0xA0);
				}
			}
			else if(Type_Cur==1)
			{
				{				
					D_Cur=19;
					array_tmp[0]=D_Cur ;
					MODIFY_EEP_W(Addr_D_Cur,array_tmp,1,0xA0);
				}
			}
			else if(Type_Cur==2)
			{
				{
					D_Cur=12;
					array_tmp[0]=D_Cur ;
					MODIFY_EEP_W(Addr_D_Cur,array_tmp,1,0xA0);
				} 
			}
			else if(Type_Cur==3)
			{
				{				
					D_Cur=14;
					array_tmp[0]=D_Cur;
					MODIFY_EEP_W(Addr_D_Cur,array_tmp,1,0xA0);
				} 
			}
			else if(Type_Cur==4)
			{
				{				
					D_Cur=6;
					array_tmp[0]=D_Cur;
					MODIFY_EEP_W(Addr_D_Cur,array_tmp,1,0xA0);
				} 
			}
			else Type_Cur_change=0;
			}

			Read_Cur_calibrae_data();
			Cur_Switch(Type_Cur);
        key_state=0x2B100;		
		    F_queren=1;
	    }
}

void Type_Cur_Set()                               //壳架等级设置
{
 if(key_value_tmp==0x20)
		{
			key_state=key_state|Type_Cur;		 
		}
		Type_cur_Temp=key_state&0x0F;
	     if(Type_cur_Temp==0)
			{
				display_ASCIIstring_8x16_fanxian(7,83,"125A");
			}
			else if(Type_cur_Temp==1)
			{
				display_ASCIIstring_8x16_fanxian(7,83,"250A");
			}
			else if(Type_cur_Temp==2)
			{
				display_ASCIIstring_8x16_fanxian(7,83,"400A");
			}
			else if(Type_cur_Temp==3)
			{
				display_ASCIIstring_8x16_fanxian(7,83,"630A");
			}
			else if(Type_cur_Temp==4)
			{
				display_ASCIIstring_8x16_fanxian(7,83,"800A");
			}
//		Cur_Switch(Type_Cur);	
}
void Fun_Com_D_1()                               //通信地址第1位
{
     clear_screen();       
	
		unsigned char mima0[2],mima1[2],mima2[2],mima3[2];
	  EEPROM_R(Addr_mima_set,mima_set,4,0xA0);
    Lcd12864_Write16CnCHAR(0,0,0,"17修改密码\r");
		display_graphic_8x16(1,86,maohao);
		mima0[0]=mima_set[0]+0x30;
		mima0[1]='\0';
	  mima1[0]=mima_set[1]+0x30;
		mima1[1]='\0';
		mima2[0]=mima_set[2]+0x30;
		mima2[1]='\0';
	 	mima3[0]=mima_set[3]+0x30;
		mima3[1]='\0';

     display_ASCIIstring_8x16(1,96,mima0);
    display_ASCIIstring_8x16(1,104,mima1);
    display_ASCIIstring_8x16(1,112,mima2);
     display_ASCIIstring_8x16(1,120,mima3);
				
	
     Lcd12864_Write16CnCHAR(0,0,3,"18通信地址\r");
		 display_graphic_8x16(1,86,maohao);
		 add_1_2[0]=(self_addr_code[0]&0x0F)+0x30;
				add_1_2[1]='\0';
	
	      add_1_1[0]=(self_addr_code[0]>>4)+0x30;
				add_1_1[1]='\0';
	
	      add_2_2[0]=(self_addr_code[1]&0x0F)+0x30;
				add_2_2[1]='\0';
	
	      add_2_1[0]=(self_addr_code[1]>>4)+0x30;
				add_2_1[1]='\0';

	      add_3_2[0]=(self_addr_code[2]&0x0F)+0x30;
 				add_3_2[1]='\0';
	
	      add_3_1[0]=(self_addr_code[2]>>4)+0x30;
				add_3_1[1]='\0';
				
				
	      add_4_2[0]=(self_addr_code[3]&0x0F)+0x30;
 				add_4_2[1]='\0';
	
	      add_4_1[0]=(self_addr_code[3]>>4)+0x30;
				add_4_1[1]='\0';
			

	      add_5_2[0]=(self_addr_code[4]&0x0F)+0x30;
 				add_5_2[1]='\0';
	
	      add_5_1[0]=(self_addr_code[4]>>4)+0x30;
				add_5_1[1]='\0';
			

	      add_6_2[0]=(self_addr_code[5]&0x0F)+0x30;
 				add_6_2[1]='\0';
	
	      add_6_1[0]=(self_addr_code[5]>>4)+0x30;
				add_6_1[1]='\0';
		    if(F_queren==1)
	      {
		      key_state=key_state|((self_addr_code[5])>>4);	
	      }
	      if((key_value_tmp==0x40)||(key_value_tmp==0x10)||(key_value_tmp==0x20)&&(F_queren<3))
	      {
		      F_queren++;
	      }
	 			self_addr_code_temp[5]=((key_state&0x0F)<<4)|((self_addr_code[5])&0x0F);				
	      add_6_2[0]=(self_addr_code_temp[5]&0x0F)+0x30;
 				add_6_2[1]='\0';
	      add_6_1[0]=(self_addr_code_temp[5]>>4)+0x30;
				add_6_1[1]='\0';
				display_ASCIIstring_8x16_fanxian(6,8,add_6_1);
				display_ASCIIstring_8x16(6,18,add_6_2);			
				display_ASCIIstring_8x16(6,28,add_5_1);
				display_ASCIIstring_8x16(6,38,add_5_2);			
				display_ASCIIstring_8x16(6,48,add_4_1);
				display_ASCIIstring_8x16(6,58,add_4_2);							
				display_ASCIIstring_8x16(6,68,add_3_1);
				display_ASCIIstring_8x16(6,78,add_3_2);	
				display_ASCIIstring_8x16(6,88,add_2_1);
				display_ASCIIstring_8x16(6,98,add_2_2);		
				display_ASCIIstring_8x16(6,108,add_1_1);				
				display_ASCIIstring_8x16(6,118,add_1_2);
				
			  if((key_value_tmp==0x20)&&(F_queren==3))
	      {
				  self_addr_code[0]=self_addr_code[0];
				  self_addr_code[1]=self_addr_code[1] ;
				  self_addr_code[2]=self_addr_code[2];
				  self_addr_code[3]=self_addr_code[3] ;
				  self_addr_code[4]=self_addr_code[4];
				  self_addr_code[5]=self_addr_code_temp[5] ;											//lpb,设备断电自动回复初始地址
				  MODIFY_EEP_W(Addr_dev_addr,self_addr_code,Lenth_dev_addr,0xA0);
          key_state=0x32100;		
		      F_queren=1;
	      }
				if((key_value_tmp==0x10)&&(F_queren==3)) 
        {					
					key_state=0x3C100;
					F_queren=1;
				}
				if((key_value_tmp==0x40)&&(F_queren==3)) 
        {					
					key_state=0x32100;
					F_queren=1;
				}
				
				

				
				
				
	 
}
void Com_D_1()
{
clear_screen();       
Lcd12864_Write16CnCHAR(0,0,0,"5通信地址\r");
			display_graphic_8x16(1,77,maohao);
		 Lcd12864_Write16CnCHAR(0,80,0,"A5-A0\r");
//		  display_sanjiao(1,119,0,1);
			add_1_2[0]=(self_addr_code[0]&0x0F)+0x30;
				add_1_2[1]='\0';
	
	      add_1_1[0]=(self_addr_code[0]>>4)+0x30;
				add_1_1[1]='\0';
	
	      add_2_2[0]=(self_addr_code[1]&0x0F)+0x30;
				add_2_2[1]='\0';
	
	      add_2_1[0]=(self_addr_code[1]>>4)+0x30;
				add_2_1[1]='\0';

	      add_3_2[0]=(self_addr_code[2]&0x0F)+0x30;
 				add_3_2[1]='\0';
	
	      add_3_1[0]=(self_addr_code[2]>>4)+0x30;
				add_3_1[1]='\0';
				
				
	      add_4_2[0]=(self_addr_code[3]&0x0F)+0x30;
 				add_4_2[1]='\0';
	
	      add_4_1[0]=(self_addr_code[3]>>4)+0x30;
				add_4_1[1]='\0';
			

	      add_5_2[0]=(self_addr_code[4]&0x0F)+0x30;
 				add_5_2[1]='\0';
	
	      add_5_1[0]=(self_addr_code[4]>>4)+0x30;
				add_5_1[1]='\0';
			
	        if(key_value_tmp==0x20)
				{
					key_state=key_state|((self_addr_code[5])>>4);		
				}
			  self_addr_code_temp[5]=((key_state&0x0F)<<4)|((self_addr_code[5])&0x0F);
	     
				
	      add_6_2[0]=(self_addr_code_temp[5]&0x0F)+0x30;
 				add_6_2[1]='\0';
	      add_6_1[0]=(self_addr_code_temp[5]>>4)+0x30;
				add_6_1[1]='\0';
				display_ASCIIstring_8x16_fanxian(6,8,add_6_1);
				display_ASCIIstring_8x16(6,18,add_6_2);			
					display_ASCIIstring_8x16(6,28,add_5_1);
				display_ASCIIstring_8x16(6,38,add_5_2);			
					display_ASCIIstring_8x16(6,48,add_4_1);
				display_ASCIIstring_8x16(6,58,add_4_2);							
					display_ASCIIstring_8x16(6,68,add_3_1);
				display_ASCIIstring_8x16(6,78,add_3_2);	
					display_ASCIIstring_8x16(6,88,add_2_1);
				display_ASCIIstring_8x16(6,98,add_2_2);		
					display_ASCIIstring_8x16(6,108,add_1_1);				
				display_ASCIIstring_8x16(6,118,add_1_2);
				
}
void Fun_Com_D_2()
{
        clear_screen();     

	unsigned char mima0[2],mima1[2],mima2[2],mima3[2];
	  EEPROM_R(Addr_mima_set,mima_set,4,0xA0);
    Lcd12864_Write16CnCHAR(0,0,0,"17修改密码\r");
		display_graphic_8x16(1,86,maohao);
		mima0[0]=mima_set[0]+0x30;
		mima0[1]='\0';
	  mima1[0]=mima_set[1]+0x30;
		mima1[1]='\0';
		mima2[0]=mima_set[2]+0x30;
		mima2[1]='\0';
	 	mima3[0]=mima_set[3]+0x30;
		mima3[1]='\0';

     display_ASCIIstring_8x16(1,96,mima0);
    display_ASCIIstring_8x16(1,104,mima1);
    display_ASCIIstring_8x16(1,112,mima2);
     display_ASCIIstring_8x16(1,120,mima3);
				
  
        Lcd12864_Write16CnCHAR(0,0,3,"18通信地址\r");
			  display_graphic_8x16(1,86,maohao);
//		  display_sanjiao(1,119,0,1);
		    add_1_2[0]=(self_addr_code[0]&0x0F)+0x30;
				add_1_2[1]='\0';
	
	      add_1_1[0]=(self_addr_code[0]>>4)+0x30;
				add_1_1[1]='\0';
	
	      add_2_2[0]=(self_addr_code[1]&0x0F)+0x30;
				add_2_2[1]='\0';
	
	      add_2_1[0]=(self_addr_code[1]>>4)+0x30;
				add_2_1[1]='\0';

	      add_3_2[0]=(self_addr_code[2]&0x0F)+0x30;
 				add_3_2[1]='\0';
	
	      add_3_1[0]=(self_addr_code[2]>>4)+0x30;
				add_3_1[1]='\0';
				
				
	      add_4_2[0]=(self_addr_code[3]&0x0F)+0x30;
 				add_4_2[1]='\0';
	
	      add_4_1[0]=(self_addr_code[3]>>4)+0x30;
				add_4_1[1]='\0';
			

	      add_5_2[0]=(self_addr_code[4]&0x0F)+0x30;
 				add_5_2[1]='\0';
	
	      add_5_1[0]=(self_addr_code[4]>>4)+0x30;
				add_5_1[1]='\0';
			

	      add_6_2[0]=(self_addr_code[5]&0x0F)+0x30;
 				add_6_2[1]='\0';
	
	      add_6_1[0]=(self_addr_code[5]>>4)+0x30;
				add_6_1[1]='\0';
		    if(F_queren==1)
	      {
		      key_state=key_state|((self_addr_code[5])&0x0F);	
	      }
	      if((key_value_tmp==0x40)||(key_value_tmp==0x10)||(key_value_tmp==0x20)&&(F_queren<3))
	      {
		      F_queren++;
	      }
			  self_addr_code_temp[5]=((key_state&0x0F))|((self_addr_code[5])&0xF0);				
	      add_6_2[0]=(self_addr_code_temp[5]&0x0F)+0x30;
 				add_6_2[1]='\0';
	      add_6_1[0]=(self_addr_code_temp[5]>>4)+0x30;
				add_6_1[1]='\0';
				display_ASCIIstring_8x16(6,8,add_6_1);
				display_ASCIIstring_8x16_fanxian(6,18,add_6_2);			
				display_ASCIIstring_8x16(6,28,add_5_1);
				display_ASCIIstring_8x16(6,38,add_5_2);			
				display_ASCIIstring_8x16(6,48,add_4_1);
				display_ASCIIstring_8x16(6,58,add_4_2);							
				display_ASCIIstring_8x16(6,68,add_3_1);
				display_ASCIIstring_8x16(6,78,add_3_2);	
				display_ASCIIstring_8x16(6,88,add_2_1);
				display_ASCIIstring_8x16(6,98,add_2_2);		
				display_ASCIIstring_8x16(6,108,add_1_1);				
				display_ASCIIstring_8x16(6,118,add_1_2);
				
			  if((key_value_tmp==0x20)&&(F_queren==3))
	      {
				  self_addr_code[0]=self_addr_code[0];
				  self_addr_code[1]=self_addr_code[1] ;
				  self_addr_code[2]=self_addr_code[2];
				  self_addr_code[3]=self_addr_code[3] ;
				  self_addr_code[4]=self_addr_code[4];
				  self_addr_code[5]=self_addr_code_temp[5] ;											//lpb,设备断电自动回复初始地址
				  MODIFY_EEP_W(Addr_dev_addr,self_addr_code,Lenth_dev_addr,0xA0);
          key_state=0x33100;		
		      F_queren=1;
	      }
				if((key_value_tmp==0x10)&&(F_queren==3)) 
        {					
					key_state=0x31100;
					F_queren=1;
				}
				if((key_value_tmp==0x40)&&(F_queren==3)) 
        {					
					key_state=0x33100;
					F_queren=1;
				}
}
void Com_D_2()
{
clear_screen();       
Lcd12864_Write16CnCHAR(0,0,0,"5通信地址\r");
			display_graphic_8x16(1,77,maohao);
		 Lcd12864_Write16CnCHAR(0,80,0,"A5-A0\r");
//		  display_sanjiao(1,119,0,1);
	add_1_2[0]=(self_addr_code[0]&0x0F)+0x30;
				add_1_2[1]='\0';
	
	      add_1_1[0]=(self_addr_code[0]>>4)+0x30;
				add_1_1[1]='\0';
	
	      add_2_2[0]=(self_addr_code[1]&0x0F)+0x30;
				add_2_2[1]='\0';
	
	      add_2_1[0]=(self_addr_code[1]>>4)+0x30;
				add_2_1[1]='\0';

	      add_3_2[0]=(self_addr_code[2]&0x0F)+0x30;
 				add_3_2[1]='\0';
	
	      add_3_1[0]=(self_addr_code[2]>>4)+0x30;
				add_3_1[1]='\0';
				
				
	      add_4_2[0]=(self_addr_code[3]&0x0F)+0x30;
 				add_4_2[1]='\0';
	
	      add_4_1[0]=(self_addr_code[3]>>4)+0x30;
				add_4_1[1]='\0';
			

	      add_5_2[0]=(self_addr_code[4]&0x0F)+0x30;
 				add_5_2[1]='\0';
	
	      add_5_1[0]=(self_addr_code[4]>>4)+0x30;
				add_5_1[1]='\0';
			
            if(key_value_tmp==0x20)
				{
					key_state=key_state|((self_addr_code[5])&0x0F);		
				}
			  self_addr_code_temp[5]=((key_state&0x0F))|((self_addr_code[5])&0xF0);
	     
				
	      add_6_2[0]=(self_addr_code_temp[5]&0x0F)+0x30;
 				add_6_2[1]='\0';
	
	      add_6_1[0]=(self_addr_code_temp[5]>>4)+0x30;
				add_6_1[1]='\0';

		
				
				display_ASCIIstring_8x16(6,8,add_6_1);
				display_ASCIIstring_8x16_fanxian(6,18,add_6_2);
				
					display_ASCIIstring_8x16(6,28,add_5_1);
				display_ASCIIstring_8x16(6,38,add_5_2);
//				
					display_ASCIIstring_8x16(6,48,add_4_1);
				display_ASCIIstring_8x16(6,58,add_4_2);
					
				
					display_ASCIIstring_8x16(6,68,add_3_1);
				display_ASCIIstring_8x16(6,78,add_3_2);
				
					display_ASCIIstring_8x16(6,88,add_2_1);
				display_ASCIIstring_8x16(6,98,add_2_2);
				
				
					display_ASCIIstring_8x16(6,108,add_1_1);
					
				display_ASCIIstring_8x16(6,118,add_1_2);
}
void Fun_Com_D_3()
{
clear_screen();     
	unsigned char mima0[2],mima1[2],mima2[2],mima3[2];
	  EEPROM_R(Addr_mima_set,mima_set,4,0xA0);
    Lcd12864_Write16CnCHAR(0,0,0,"17修改密码\r");
		display_graphic_8x16(1,86,maohao);
		mima0[0]=mima_set[0]+0x30;
		mima0[1]='\0';
	  mima1[0]=mima_set[1]+0x30;
		mima1[1]='\0';
		mima2[0]=mima_set[2]+0x30;
		mima2[1]='\0';
	 	mima3[0]=mima_set[3]+0x30;
		mima3[1]='\0';

     display_ASCIIstring_8x16(1,96,mima0);
    display_ASCIIstring_8x16(1,104,mima1);
    display_ASCIIstring_8x16(1,112,mima2);
     display_ASCIIstring_8x16(1,120,mima3);
				
  
Lcd12864_Write16CnCHAR(0,0,3,"18通信地址\r");
			display_graphic_8x16(1,86,maohao);
//		  display_sanjiao(1,119,0,1);
		add_1_2[0]=(self_addr_code[0]&0x0F)+0x30;
				add_1_2[1]='\0';
	
	      add_1_1[0]=(self_addr_code[0]>>4)+0x30;
				add_1_1[1]='\0';
	
	      add_2_2[0]=(self_addr_code[1]&0x0F)+0x30;
				add_2_2[1]='\0';
	
	      add_2_1[0]=(self_addr_code[1]>>4)+0x30;
				add_2_1[1]='\0';

	      add_3_2[0]=(self_addr_code[2]&0x0F)+0x30;
 				add_3_2[1]='\0';
	
	      add_3_1[0]=(self_addr_code[2]>>4)+0x30;
				add_3_1[1]='\0';
				
				
	      add_4_2[0]=(self_addr_code[3]&0x0F)+0x30;
 				add_4_2[1]='\0';
	
	      add_4_1[0]=(self_addr_code[3]>>4)+0x30;
				add_4_1[1]='\0';
			

	      add_5_2[0]=(self_addr_code[4]&0x0F)+0x30;
 				add_5_2[1]='\0';
	
	      add_5_1[0]=(self_addr_code[4]>>4)+0x30;
				add_5_1[1]='\0';
			

	      add_6_2[0]=(self_addr_code[5]&0x0F)+0x30;
 				add_6_2[1]='\0';
	
	      add_6_1[0]=(self_addr_code[5]>>4)+0x30;
				add_6_1[1]='\0';
		    if(F_queren==1)
	      {
					key_state=key_state|((self_addr_code[4])>>4);
	      }
	      if((key_value_tmp==0x40)||(key_value_tmp==0x10)||(key_value_tmp==0x20)&&(F_queren<3))
	      {
		      F_queren++;
	      }
			  self_addr_code_temp[4]=((key_state&0x0F)<<4)|((self_addr_code[4])&0x0F);			
	      add_5_2[0]=(self_addr_code_temp[4]&0x0F)+0x30;
 				add_5_2[1]='\0';
	
	      add_5_1[0]=(self_addr_code_temp[4]>>4)+0x30;
				add_5_1[1]='\0';
				display_ASCIIstring_8x16(6,8,add_6_1);
				display_ASCIIstring_8x16(6,18,add_6_2);			
				display_ASCIIstring_8x16_fanxian(6,28,add_5_1);
				display_ASCIIstring_8x16(6,38,add_5_2);			
				display_ASCIIstring_8x16(6,48,add_4_1);
				display_ASCIIstring_8x16(6,58,add_4_2);							
				display_ASCIIstring_8x16(6,68,add_3_1);
				display_ASCIIstring_8x16(6,78,add_3_2);	
				display_ASCIIstring_8x16(6,88,add_2_1);
				display_ASCIIstring_8x16(6,98,add_2_2);		
				display_ASCIIstring_8x16(6,108,add_1_1);				
				display_ASCIIstring_8x16(6,118,add_1_2);
				
			  if((key_value_tmp==0x20)&&(F_queren==3))
	      {
				  self_addr_code[0]=self_addr_code[0];
				  self_addr_code[1]=self_addr_code[1] ;
				  self_addr_code[2]=self_addr_code[2];
				  self_addr_code[3]=self_addr_code[3] ;
				  self_addr_code[4]=self_addr_code_temp[4];
				  self_addr_code[5]=self_addr_code[5] ;											//lpb,设备断电自动回复初始地址
				  MODIFY_EEP_W(Addr_dev_addr,self_addr_code,Lenth_dev_addr,0xA0);
          key_state=0x34100;		
		      F_queren=1;
	      }
				if((key_value_tmp==0x10)&&(F_queren==3)) 
        {					
					key_state=0x32100;
					F_queren=1;
				}
				if((key_value_tmp==0x40)&&(F_queren==3)) 
        {					
					key_state=0x34100;
					F_queren=1;
				}
}
void Com_D_3()
{
clear_screen();       
Lcd12864_Write16CnCHAR(0,0,0,"5通信地址\r");
			display_graphic_8x16(1,77,maohao);
		 Lcd12864_Write16CnCHAR(0,80,0,"A5-A0\r");
//		  display_sanjiao(1,119,0,1);
		add_1_2[0]=(self_addr_code[0]&0x0F)+0x30;
				add_1_2[1]='\0';
	
	      add_1_1[0]=(self_addr_code[0]>>4)+0x30;
				add_1_1[1]='\0';
	
	      add_2_2[0]=(self_addr_code[1]&0x0F)+0x30;
				add_2_2[1]='\0';
	
	      add_2_1[0]=(self_addr_code[1]>>4)+0x30;
				add_2_1[1]='\0';

	      add_3_2[0]=(self_addr_code[2]&0x0F)+0x30;
 				add_3_2[1]='\0';
	
	      add_3_1[0]=(self_addr_code[2]>>4)+0x30;
				add_3_1[1]='\0';
				
				
	      add_4_2[0]=(self_addr_code[3]&0x0F)+0x30;
 				add_4_2[1]='\0';
	
	      add_4_1[0]=(self_addr_code[3]>>4)+0x30;
				add_4_1[1]='\0';
			
       if(key_value_tmp==0x20)
				{
					key_state=key_state|((self_addr_code[4])>>4);		
				}
			  self_addr_code_temp[4]=((key_state&0x0F)<<4)|((self_addr_code[4])&0x0F);
				
	      add_5_2[0]=(self_addr_code_temp[4]&0x0F)+0x30;
 				add_5_2[1]='\0';
	
	      add_5_1[0]=(self_addr_code_temp[4]>>4)+0x30;
				add_5_1[1]='\0';

	      add_6_2[0]=(self_addr_code[5]&0x0F)+0x30;
 				add_6_2[1]='\0';
	      add_6_1[0]=(self_addr_code[5]>>4)+0x30;
				add_6_1[1]='\0';
				display_ASCIIstring_8x16(6,8,add_6_1);
				display_ASCIIstring_8x16(6,18,add_6_2);			
					display_ASCIIstring_8x16_fanxian(6,28,add_5_1);
				display_ASCIIstring_8x16(6,38,add_5_2);			
					display_ASCIIstring_8x16(6,48,add_4_1);
				display_ASCIIstring_8x16(6,58,add_4_2);							
					display_ASCIIstring_8x16(6,68,add_3_1);
				display_ASCIIstring_8x16(6,78,add_3_2);	
					display_ASCIIstring_8x16(6,88,add_2_1);
				display_ASCIIstring_8x16(6,98,add_2_2);		
					display_ASCIIstring_8x16(6,108,add_1_1);				
				display_ASCIIstring_8x16(6,118,add_1_2);
}
void Fun_Com_D_4()
{
clear_screen();       
	unsigned char mima0[2],mima1[2],mima2[2],mima3[2];
	  EEPROM_R(Addr_mima_set,mima_set,4,0xA0);
    Lcd12864_Write16CnCHAR(0,0,0,"17修改密码\r");
		display_graphic_8x16(1,86,maohao);
		mima0[0]=mima_set[0]+0x30;
		mima0[1]='\0';
	  mima1[0]=mima_set[1]+0x30;
		mima1[1]='\0';
		mima2[0]=mima_set[2]+0x30;
		mima2[1]='\0';
	 	mima3[0]=mima_set[3]+0x30;
		mima3[1]='\0';

     display_ASCIIstring_8x16(1,96,mima0);
    display_ASCIIstring_8x16(1,104,mima1);
    display_ASCIIstring_8x16(1,112,mima2);
     display_ASCIIstring_8x16(1,120,mima3);
				
  
Lcd12864_Write16CnCHAR(0,0,3,"18通信地址\r");
			display_graphic_8x16(1,86,maohao);
//		  display_sanjiao(1,119,0,1);
		add_1_2[0]=(self_addr_code[0]&0x0F)+0x30;
				add_1_2[1]='\0';
	
	      add_1_1[0]=(self_addr_code[0]>>4)+0x30;
				add_1_1[1]='\0';
	
	      add_2_2[0]=(self_addr_code[1]&0x0F)+0x30;
				add_2_2[1]='\0';
	
	      add_2_1[0]=(self_addr_code[1]>>4)+0x30;
				add_2_1[1]='\0';

	      add_3_2[0]=(self_addr_code[2]&0x0F)+0x30;
 				add_3_2[1]='\0';
	
	      add_3_1[0]=(self_addr_code[2]>>4)+0x30;
				add_3_1[1]='\0';
				
				
	      add_4_2[0]=(self_addr_code[3]&0x0F)+0x30;
 				add_4_2[1]='\0';
	
	      add_4_1[0]=(self_addr_code[3]>>4)+0x30;
				add_4_1[1]='\0';
			

	      add_5_2[0]=(self_addr_code[4]&0x0F)+0x30;
 				add_5_2[1]='\0';
	
	      add_5_1[0]=(self_addr_code[4]>>4)+0x30;
				add_5_1[1]='\0';
			

	      add_6_2[0]=(self_addr_code[5]&0x0F)+0x30;
 				add_6_2[1]='\0';
	
	      add_6_1[0]=(self_addr_code[5]>>4)+0x30;
				add_6_1[1]='\0';
		    if(F_queren==1)
	      {
					key_state=key_state|((self_addr_code[4])&0x0F);	
	      }
	      if((key_value_tmp==0x40)||(key_value_tmp==0x10)||(key_value_tmp==0x20)&&(F_queren<3))
	      {
		      F_queren++;
	      }
			  self_addr_code_temp[4]=((key_state&0x0F))|((self_addr_code[4])&0xF0);			
	      add_5_2[0]=(self_addr_code_temp[4]&0x0F)+0x30;
 				add_5_2[1]='\0';
	
	      add_5_1[0]=(self_addr_code_temp[4]>>4)+0x30;
				add_5_1[1]='\0';
				display_ASCIIstring_8x16(6,8,add_6_1);
				display_ASCIIstring_8x16(6,18,add_6_2);			
				display_ASCIIstring_8x16(6,28,add_5_1);
				display_ASCIIstring_8x16_fanxian(6,38,add_5_2);			
				display_ASCIIstring_8x16(6,48,add_4_1);
				display_ASCIIstring_8x16(6,58,add_4_2);							
				display_ASCIIstring_8x16(6,68,add_3_1);
				display_ASCIIstring_8x16(6,78,add_3_2);	
				display_ASCIIstring_8x16(6,88,add_2_1);
				display_ASCIIstring_8x16(6,98,add_2_2);		
				display_ASCIIstring_8x16(6,108,add_1_1);				
				display_ASCIIstring_8x16(6,118,add_1_2);
				
			  if((key_value_tmp==0x20)&&(F_queren==3))
	      {
				  self_addr_code[0]=self_addr_code[0];
				  self_addr_code[1]=self_addr_code[1] ;
				  self_addr_code[2]=self_addr_code[2];
				  self_addr_code[3]=self_addr_code[3] ;
				  self_addr_code[4]=self_addr_code_temp[4];
				  self_addr_code[5]=self_addr_code[5] ;											//lpb,设备断电自动回复初始地址
				  MODIFY_EEP_W(Addr_dev_addr,self_addr_code,Lenth_dev_addr,0xA0);
          key_state=0x35100;		
		      F_queren=1;
	      }
				if((key_value_tmp==0x10)&&(F_queren==3)) 
        {					
					key_state=0x33100;
					F_queren=1;
				}
				if((key_value_tmp==0x40)&&(F_queren==3)) 
        {					
					key_state=0x35100;
					F_queren=1;
				}
}
void Com_D_4()
{
clear_screen();       
Lcd12864_Write16CnCHAR(0,0,0,"5通信地址\r");
			display_graphic_8x16(1,77,maohao);
		 Lcd12864_Write16CnCHAR(0,80,0,"A5-A0\r");
//		  display_sanjiao(1,119,0,1);
	add_1_2[0]=(self_addr_code[0]&0x0F)+0x30;
				add_1_2[1]='\0';
	
	      add_1_1[0]=(self_addr_code[0]>>4)+0x30;
				add_1_1[1]='\0';
	
	      add_2_2[0]=(self_addr_code[1]&0x0F)+0x30;
				add_2_2[1]='\0';
	
	      add_2_1[0]=(self_addr_code[1]>>4)+0x30;
				add_2_1[1]='\0';

	      add_3_2[0]=(self_addr_code[2]&0x0F)+0x30;
 				add_3_2[1]='\0';
	
	      add_3_1[0]=(self_addr_code[2]>>4)+0x30;
				add_3_1[1]='\0';
				
				
	      add_4_2[0]=(self_addr_code[3]&0x0F)+0x30;
 				add_4_2[1]='\0';
	
	      add_4_1[0]=(self_addr_code[3]>>4)+0x30;
				add_4_1[1]='\0';
			
         if(key_value_tmp==0x20)
				{
					key_state=key_state|((self_addr_code[4])&0x0F);		
				}
			  self_addr_code_temp[4]=((key_state&0x0F))|((self_addr_code[4])&0xF0);
	     
				
	      add_5_2[0]=(self_addr_code_temp[4]&0x0F)+0x30;
 				add_5_2[1]='\0';
	
	      add_5_1[0]=(self_addr_code_temp[4]>>4)+0x30;
				add_5_1[1]='\0';
			
         
	      add_6_2[0]=(self_addr_code[5]&0x0F)+0x30;
 				add_6_2[1]='\0';
	
	      add_6_1[0]=(self_addr_code[5]>>4)+0x30;
				add_6_1[1]='\0';

		
				
				display_ASCIIstring_8x16(6,8,add_6_1);
				display_ASCIIstring_8x16(6,18,add_6_2);
				
					display_ASCIIstring_8x16(6,28,add_5_1);
				display_ASCIIstring_8x16_fanxian(6,38,add_5_2);
//				
					display_ASCIIstring_8x16(6,48,add_4_1);
				display_ASCIIstring_8x16(6,58,add_4_2);
					
				
					display_ASCIIstring_8x16(6,68,add_3_1);
				display_ASCIIstring_8x16(6,78,add_3_2);
				
					display_ASCIIstring_8x16(6,88,add_2_1);
				display_ASCIIstring_8x16(6,98,add_2_2);
				
				
					display_ASCIIstring_8x16(6,108,add_1_1);
					
				display_ASCIIstring_8x16(6,118,add_1_2);
}
void Fun_Com_D_5()
{
        clear_screen();       
      	unsigned char mima0[2],mima1[2],mima2[2],mima3[2];
	  EEPROM_R(Addr_mima_set,mima_set,4,0xA0);
    Lcd12864_Write16CnCHAR(0,0,0,"17修改密码\r");
		display_graphic_8x16(1,86,maohao);
		mima0[0]=mima_set[0]+0x30;
		mima0[1]='\0';
	  mima1[0]=mima_set[1]+0x30;
		mima1[1]='\0';
		mima2[0]=mima_set[2]+0x30;
		mima2[1]='\0';
	 	mima3[0]=mima_set[3]+0x30;
		mima3[1]='\0';

     display_ASCIIstring_8x16(1,96,mima0);
    display_ASCIIstring_8x16(1,104,mima1);
    display_ASCIIstring_8x16(1,112,mima2);
     display_ASCIIstring_8x16(1,120,mima3);
				
  
Lcd12864_Write16CnCHAR(0,0,3,"18通信地址\r");
		    display_graphic_8x16(1,86,maohao);
//		  display_sanjiao(1,119,0,1);
		    add_1_2[0]=(self_addr_code[0]&0x0F)+0x30;
				add_1_2[1]='\0';
	
	      add_1_1[0]=(self_addr_code[0]>>4)+0x30;
				add_1_1[1]='\0';
	
	      add_2_2[0]=(self_addr_code[1]&0x0F)+0x30;
				add_2_2[1]='\0';
	
	      add_2_1[0]=(self_addr_code[1]>>4)+0x30;
				add_2_1[1]='\0';

	      add_3_2[0]=(self_addr_code[2]&0x0F)+0x30;
 				add_3_2[1]='\0';
	
	      add_3_1[0]=(self_addr_code[2]>>4)+0x30;
				add_3_1[1]='\0';
				
				
	      add_4_2[0]=(self_addr_code[3]&0x0F)+0x30;
 				add_4_2[1]='\0';
	
	      add_4_1[0]=(self_addr_code[3]>>4)+0x30;
				add_4_1[1]='\0';
			

	      add_5_2[0]=(self_addr_code[4]&0x0F)+0x30;
 				add_5_2[1]='\0';
	
	      add_5_1[0]=(self_addr_code[4]>>4)+0x30;
				add_5_1[1]='\0';
			

	      add_6_2[0]=(self_addr_code[5]&0x0F)+0x30;
 				add_6_2[1]='\0';
	
	      add_6_1[0]=(self_addr_code[5]>>4)+0x30;
				add_6_1[1]='\0';
		    if(F_queren==1)
	      {
					key_state=key_state|((self_addr_code[3])>>4);
	      }
	      if((key_value_tmp==0x40)||(key_value_tmp==0x10)||(key_value_tmp==0x20)&&(F_queren<3))
	      {
		      F_queren++;
	      }
			  self_addr_code_temp[3]=((key_state&0x0F)<<4)|((self_addr_code[3])&0x0F);			
	      add_4_2[0]=(self_addr_code_temp[3]&0x0F)+0x30;
 				add_4_2[1]='\0';
	
	      add_4_1[0]=(self_addr_code_temp[3]>>4)+0x30;
				add_4_1[1]='\0';
				display_ASCIIstring_8x16(6,8,add_6_1);
				display_ASCIIstring_8x16(6,18,add_6_2);			
				display_ASCIIstring_8x16(6,28,add_5_1);
				display_ASCIIstring_8x16(6,38,add_5_2);			
				display_ASCIIstring_8x16_fanxian(6,48,add_4_1);
				display_ASCIIstring_8x16(6,58,add_4_2);							
				display_ASCIIstring_8x16(6,68,add_3_1);
				display_ASCIIstring_8x16(6,78,add_3_2);	
				display_ASCIIstring_8x16(6,88,add_2_1);
				display_ASCIIstring_8x16(6,98,add_2_2);		
				display_ASCIIstring_8x16(6,108,add_1_1);				
				display_ASCIIstring_8x16(6,118,add_1_2);
				
			  if((key_value_tmp==0x20)&&(F_queren==3))
	      {
				  self_addr_code[0]=self_addr_code[0];
				  self_addr_code[1]=self_addr_code[1] ;
				  self_addr_code[2]=self_addr_code[2];
				  self_addr_code[3]=self_addr_code_temp[3] ;
				  self_addr_code[4]=self_addr_code[4];
				  self_addr_code[5]=self_addr_code[5] ;											//lpb,设备断电自动回复初始地址
				  MODIFY_EEP_W(Addr_dev_addr,self_addr_code,Lenth_dev_addr,0xA0);
          key_state=0x36100;		
		      F_queren=1;
	      }
				if((key_value_tmp==0x10)&&(F_queren==3)) 
        {					
					key_state=0x34100;
					F_queren=1;
				}
				if((key_value_tmp==0x40)&&(F_queren==3)) 
        {					
					key_state=0x36100;
					F_queren=1;
				}
				
				
}
void Com_D_5()
{
clear_screen();       
Lcd12864_Write16CnCHAR(0,0,0,"5通信地址\r");
			display_graphic_8x16(1,77,maohao);
		 Lcd12864_Write16CnCHAR(0,80,0,"A5-A0\r");
//		  display_sanjiao(1,119,0,1);
		add_1_2[0]=(self_addr_code[0]&0x0F)+0x30;
				add_1_2[1]='\0';
	
	      add_1_1[0]=(self_addr_code[0]>>4)+0x30;
				add_1_1[1]='\0';
	
	      add_2_2[0]=(self_addr_code[1]&0x0F)+0x30;
				add_2_2[1]='\0';
	
	      add_2_1[0]=(self_addr_code[1]>>4)+0x30;
				add_2_1[1]='\0';

	      add_3_2[0]=(self_addr_code[2]&0x0F)+0x30;
 				add_3_2[1]='\0';
	
	      add_3_1[0]=(self_addr_code[2]>>4)+0x30;
				add_3_1[1]='\0';
				
				
       if(key_value_tmp==0x20)
				{
					key_state=key_state|((self_addr_code[3])>>4);		
				}
			  self_addr_code_temp[3]=((key_state&0x0F)<<4)|((self_addr_code[3])&0x0F);
				
	      add_4_2[0]=(self_addr_code_temp[3]&0x0F)+0x30;
 				add_4_2[1]='\0';
	
	      add_4_1[0]=(self_addr_code_temp[3]>>4)+0x30;
				add_4_1[1]='\0';
			
	      add_5_2[0]=(self_addr_code[4]&0x0F)+0x30;
 				add_5_2[1]='\0';
	
	      add_5_1[0]=(self_addr_code[4]>>4)+0x30;
				add_5_1[1]='\0';

	      add_6_2[0]=(self_addr_code[5]&0x0F)+0x30;
 				add_6_2[1]='\0';
	      add_6_1[0]=(self_addr_code[5]>>4)+0x30;
				add_6_1[1]='\0';
				display_ASCIIstring_8x16(6,8,add_6_1);
				display_ASCIIstring_8x16(6,18,add_6_2);			
					display_ASCIIstring_8x16(6,28,add_5_1);
				display_ASCIIstring_8x16(6,38,add_5_2);			
					display_ASCIIstring_8x16_fanxian(6,48,add_4_1);
				display_ASCIIstring_8x16(6,58,add_4_2);							
					display_ASCIIstring_8x16(6,68,add_3_1);
				display_ASCIIstring_8x16(6,78,add_3_2);	
					display_ASCIIstring_8x16(6,88,add_2_1);
				display_ASCIIstring_8x16(6,98,add_2_2);		
					display_ASCIIstring_8x16(6,108,add_1_1);				
				display_ASCIIstring_8x16(6,118,add_1_2);
}
void Fun_Com_D_6()
{
        clear_screen();       
       	unsigned char mima0[2],mima1[2],mima2[2],mima3[2];
	  EEPROM_R(Addr_mima_set,mima_set,4,0xA0);
    Lcd12864_Write16CnCHAR(0,0,0,"17修改密码\r");
		display_graphic_8x16(1,86,maohao);
		mima0[0]=mima_set[0]+0x30;
		mima0[1]='\0';
	  mima1[0]=mima_set[1]+0x30;
		mima1[1]='\0';
		mima2[0]=mima_set[2]+0x30;
		mima2[1]='\0';
	 	mima3[0]=mima_set[3]+0x30;
		mima3[1]='\0';

     display_ASCIIstring_8x16(1,96,mima0);
    display_ASCIIstring_8x16(1,104,mima1);
    display_ASCIIstring_8x16(1,112,mima2);
     display_ASCIIstring_8x16(1,120,mima3);
				
  
Lcd12864_Write16CnCHAR(0,0,3,"18通信地址\r");
			  display_graphic_8x16(1,86,maohao);
//		  display_sanjiao(1,119,0,1);
		    add_1_2[0]=(self_addr_code[0]&0x0F)+0x30;
				add_1_2[1]='\0';
	
	      add_1_1[0]=(self_addr_code[0]>>4)+0x30;
				add_1_1[1]='\0';
	
	      add_2_2[0]=(self_addr_code[1]&0x0F)+0x30;
				add_2_2[1]='\0';
	
	      add_2_1[0]=(self_addr_code[1]>>4)+0x30;
				add_2_1[1]='\0';

	      add_3_2[0]=(self_addr_code[2]&0x0F)+0x30;
 				add_3_2[1]='\0';
	
	      add_3_1[0]=(self_addr_code[2]>>4)+0x30;
				add_3_1[1]='\0';
				
				
	      add_4_2[0]=(self_addr_code[3]&0x0F)+0x30;
 				add_4_2[1]='\0';
	
	      add_4_1[0]=(self_addr_code[3]>>4)+0x30;
				add_4_1[1]='\0';
			

	      add_5_2[0]=(self_addr_code[4]&0x0F)+0x30;
 				add_5_2[1]='\0';
	
	      add_5_1[0]=(self_addr_code[4]>>4)+0x30;
				add_5_1[1]='\0';
			

	      add_6_2[0]=(self_addr_code[5]&0x0F)+0x30;
 				add_6_2[1]='\0';
	
	      add_6_1[0]=(self_addr_code[5]>>4)+0x30;
				add_6_1[1]='\0';
		    if(F_queren==1)
	      {
					key_state=key_state|((self_addr_code[3])&0x0F);	
	      }
	      if((key_value_tmp==0x40)||(key_value_tmp==0x10)||(key_value_tmp==0x20)&&(F_queren<3))
	      {
		      F_queren++;
	      }
			  self_addr_code_temp[3]=((key_state&0x0F))|((self_addr_code[3])&0xF0);			
	      add_4_2[0]=(self_addr_code_temp[3]&0x0F)+0x30;
 				add_4_2[1]='\0';	
	      add_4_1[0]=(self_addr_code_temp[3]>>4)+0x30;
				add_4_1[1]='\0';      	     				
				display_ASCIIstring_8x16(6,8,add_6_1);
				display_ASCIIstring_8x16(6,18,add_6_2);			
				display_ASCIIstring_8x16(6,28,add_5_1);
				display_ASCIIstring_8x16(6,38,add_5_2);			
				display_ASCIIstring_8x16(6,48,add_4_1);
				display_ASCIIstring_8x16_fanxian(6,58,add_4_2);							
				display_ASCIIstring_8x16(6,68,add_3_1);
				display_ASCIIstring_8x16(6,78,add_3_2);	
				display_ASCIIstring_8x16(6,88,add_2_1);
				display_ASCIIstring_8x16(6,98,add_2_2);		
				display_ASCIIstring_8x16(6,108,add_1_1);				
				display_ASCIIstring_8x16(6,118,add_1_2);
				
			  if((key_value_tmp==0x20)&&(F_queren==3))
	      {
				  self_addr_code[0]=self_addr_code[0];
				  self_addr_code[1]=self_addr_code[1] ;
				  self_addr_code[2]=self_addr_code[2];
				  self_addr_code[3]=self_addr_code_temp[3] ;
				  self_addr_code[4]=self_addr_code[4];
				  self_addr_code[5]=self_addr_code[5] ;											//lpb,设备断电自动回复初始地址
				  MODIFY_EEP_W(Addr_dev_addr,self_addr_code,Lenth_dev_addr,0xA0);
          key_state=0x37100;		
		      F_queren=1;
	      }
				if((key_value_tmp==0x10)&&(F_queren==3)) 
        {					
					key_state=0x35100;
					F_queren=1;
				}
				if((key_value_tmp==0x40)&&(F_queren==3)) 
        {					
					key_state=0x37100;
					F_queren=1;
				}
}
void Com_D_6()
{
clear_screen();       
Lcd12864_Write16CnCHAR(0,0,0,"5通信地址\r");
			display_graphic_8x16(1,77,maohao);
		 Lcd12864_Write16CnCHAR(0,80,0,"A5-A0\r");
//		  display_sanjiao(1,119,0,1);
	add_1_2[0]=(self_addr_code[0]&0x0F)+0x30;
				add_1_2[1]='\0';
	
	      add_1_1[0]=(self_addr_code[0]>>4)+0x30;
				add_1_1[1]='\0';
	
	      add_2_2[0]=(self_addr_code[1]&0x0F)+0x30;
				add_2_2[1]='\0';
	
	      add_2_1[0]=(self_addr_code[1]>>4)+0x30;
				add_2_1[1]='\0';

	      add_3_2[0]=(self_addr_code[2]&0x0F)+0x30;
 				add_3_2[1]='\0';
	
	      add_3_1[0]=(self_addr_code[2]>>4)+0x30;
				add_3_1[1]='\0';
				
				   if(key_value_tmp==0x20)
				{
					key_state=key_state|((self_addr_code[3])&0x0F);		
				}
			  self_addr_code_temp[3]=((key_state&0x0F))|((self_addr_code[3])&0xF0);
				
	      add_4_2[0]=(self_addr_code_temp[3]&0x0F)+0x30;
 				add_4_2[1]='\0';
	
	      add_4_1[0]=(self_addr_code_temp[3]>>4)+0x30;
				add_4_1[1]='\0';
			
      
	     
				
	      add_5_2[0]=(self_addr_code[4]&0x0F)+0x30;
 				add_5_2[1]='\0';
	
	      add_5_1[0]=(self_addr_code[4]>>4)+0x30;
				add_5_1[1]='\0';
			
         
	      add_6_2[0]=(self_addr_code[5]&0x0F)+0x30;
 				add_6_2[1]='\0';
	
	      add_6_1[0]=(self_addr_code[5]>>4)+0x30;
				add_6_1[1]='\0';

		
				
				display_ASCIIstring_8x16(6,8,add_6_1);
				display_ASCIIstring_8x16(6,18,add_6_2);
				
					display_ASCIIstring_8x16(6,28,add_5_1);
				display_ASCIIstring_8x16(6,38,add_5_2);
//				
					display_ASCIIstring_8x16(6,48,add_4_1);
				display_ASCIIstring_8x16_fanxian(6,58,add_4_2);
					
				
					display_ASCIIstring_8x16(6,68,add_3_1);
				display_ASCIIstring_8x16(6,78,add_3_2);
				
					display_ASCIIstring_8x16(6,88,add_2_1);
				display_ASCIIstring_8x16(6,98,add_2_2);
				
				
					display_ASCIIstring_8x16(6,108,add_1_1);
					
				display_ASCIIstring_8x16(6,118,add_1_2);
	
}
void Fun_Com_D_7()
{
        clear_screen();       
        	unsigned char mima0[2],mima1[2],mima2[2],mima3[2];
	  EEPROM_R(Addr_mima_set,mima_set,4,0xA0);
    Lcd12864_Write16CnCHAR(0,0,0,"17修改密码\r");
		display_graphic_8x16(1,86,maohao);
		mima0[0]=mima_set[0]+0x30;
		mima0[1]='\0';
	  mima1[0]=mima_set[1]+0x30;
		mima1[1]='\0'; 
		mima2[0]=mima_set[2]+0x30;
		mima2[1]='\0';
	 	mima3[0]=mima_set[3]+0x30;
		mima3[1]='\0';

     display_ASCIIstring_8x16(1,96,mima0);
    display_ASCIIstring_8x16(1,104,mima1);
    display_ASCIIstring_8x16(1,112,mima2);
     display_ASCIIstring_8x16(1,120,mima3);
				
  
Lcd12864_Write16CnCHAR(0,0,3,"18通信地址\r");
		    display_graphic_8x16(1,86,maohao);
//		  display_sanjiao(1,119,0,1);
		    add_1_2[0]=(self_addr_code[0]&0x0F)+0x30;
				add_1_2[1]='\0';
	
	      add_1_1[0]=(self_addr_code[0]>>4)+0x30;
				add_1_1[1]='\0';
	
	      add_2_2[0]=(self_addr_code[1]&0x0F)+0x30;
				add_2_2[1]='\0';
	
	      add_2_1[0]=(self_addr_code[1]>>4)+0x30;
				add_2_1[1]='\0';

	      add_3_2[0]=(self_addr_code[2]&0x0F)+0x30;
 				add_3_2[1]='\0';
	
	      add_3_1[0]=(self_addr_code[2]>>4)+0x30;
				add_3_1[1]='\0';
				
				
	      add_4_2[0]=(self_addr_code[3]&0x0F)+0x30;
 				add_4_2[1]='\0';
	
	      add_4_1[0]=(self_addr_code[3]>>4)+0x30;
				add_4_1[1]='\0';
			

	      add_5_2[0]=(self_addr_code[4]&0x0F)+0x30;
 				add_5_2[1]='\0';
	
	      add_5_1[0]=(self_addr_code[4]>>4)+0x30;
				add_5_1[1]='\0';
			

	      add_6_2[0]=(self_addr_code[5]&0x0F)+0x30;
 				add_6_2[1]='\0';
	
	      add_6_1[0]=(self_addr_code[5]>>4)+0x30;
				add_6_1[1]='\0';
		    if(F_queren==1)
	      {
					key_state=key_state|((self_addr_code[2])>>4);
	      }
	      if((key_value_tmp==0x40)||(key_value_tmp==0x10)||(key_value_tmp==0x20)&&(F_queren<3))
	      {
		      F_queren++;
	      }
			  self_addr_code_temp[2]=((key_state&0x0F)<<4)|((self_addr_code[2])&0x0F);
	      add_3_2[0]=(self_addr_code_temp[2]&0x0F)+0x30;
 				add_3_2[1]='\0';
	
	      add_3_1[0]=(self_addr_code_temp[2]>>4)+0x30;
				add_3_1[1]='\0';
				display_ASCIIstring_8x16(6,8,add_6_1);
				display_ASCIIstring_8x16(6,18,add_6_2);			
				display_ASCIIstring_8x16(6,28,add_5_1);
				display_ASCIIstring_8x16(6,38,add_5_2);			
				display_ASCIIstring_8x16(6,48,add_4_1);
				display_ASCIIstring_8x16(6,58,add_4_2);							
				display_ASCIIstring_8x16_fanxian(6,68,add_3_1);
				display_ASCIIstring_8x16(6,78,add_3_2);	
				display_ASCIIstring_8x16(6,88,add_2_1);
				display_ASCIIstring_8x16(6,98,add_2_2);		
				display_ASCIIstring_8x16(6,108,add_1_1);				
				display_ASCIIstring_8x16(6,118,add_1_2);
				
			  if((key_value_tmp==0x20)&&(F_queren==3))
	      {
				  self_addr_code[0]=self_addr_code[0];
				  self_addr_code[1]=self_addr_code[1] ;
				  self_addr_code[2]=self_addr_code_temp[2];
				  self_addr_code[3]=self_addr_code[3] ;
				  self_addr_code[4]=self_addr_code[4];
				  self_addr_code[5]=self_addr_code[5] ;											//lpb,设备断电自动回复初始地址
				  MODIFY_EEP_W(Addr_dev_addr,self_addr_code,Lenth_dev_addr,0xA0);
          key_state=0x38100;		
		      F_queren=1;
	      }
				if((key_value_tmp==0x10)&&(F_queren==3)) 
        {					
					key_state=0x36100;
					F_queren=1;
				}
				if((key_value_tmp==0x40)&&(F_queren==3)) 
        {					
					key_state=0x38100;
					F_queren=1;
				}
}
void Com_D_7()
{
	clear_screen();       
Lcd12864_Write16CnCHAR(0,0,0,"5通信地址\r");
			display_graphic_8x16(1,77,maohao);
		 Lcd12864_Write16CnCHAR(0,80,0,"A5-A0\r");
//		  display_sanjiao(1,119,0,1);
add_1_2[0]=(self_addr_code[0]&0x0F)+0x30;
				add_1_2[1]='\0';
	
	      add_1_1[0]=(self_addr_code[0]>>4)+0x30;
				add_1_1[1]='\0';
	
	      add_2_2[0]=(self_addr_code[1]&0x0F)+0x30;
				add_2_2[1]='\0';
	
	      add_2_1[0]=(self_addr_code[1]>>4)+0x30;
				add_2_1[1]='\0';

          if(key_value_tmp==0x20)
				{
					key_state=key_state|((self_addr_code[2])>>4);		
				}
			  self_addr_code_temp[2]=((key_state&0x0F)<<4)|((self_addr_code[2])&0x0F);
				
	      add_3_2[0]=(self_addr_code_temp[2]&0x0F)+0x30;
 				add_3_2[1]='\0';
	
	      add_3_1[0]=(self_addr_code_temp[2]>>4)+0x30;
				add_3_1[1]='\0';
				
				
      
				
	      add_4_2[0]=(self_addr_code[3]&0x0F)+0x30;
 				add_4_2[1]='\0';
	
	      add_4_1[0]=(self_addr_code[3]>>4)+0x30;
				add_4_1[1]='\0';
			
	      add_5_2[0]=(self_addr_code[4]&0x0F)+0x30;
 				add_5_2[1]='\0';
	
	      add_5_1[0]=(self_addr_code[4]>>4)+0x30;
				add_5_1[1]='\0';

	      add_6_2[0]=(self_addr_code[5]&0x0F)+0x30;
 				add_6_2[1]='\0';
	      add_6_1[0]=(self_addr_code[5]>>4)+0x30;
				add_6_1[1]='\0';
				display_ASCIIstring_8x16(6,8,add_6_1);
				display_ASCIIstring_8x16(6,18,add_6_2);			
					display_ASCIIstring_8x16(6,28,add_5_1);
				display_ASCIIstring_8x16(6,38,add_5_2);			
					display_ASCIIstring_8x16(6,48,add_4_1);
				display_ASCIIstring_8x16(6,58,add_4_2);							
					display_ASCIIstring_8x16_fanxian(6,68,add_3_1);
				display_ASCIIstring_8x16(6,78,add_3_2);	
					display_ASCIIstring_8x16(6,88,add_2_1);
				display_ASCIIstring_8x16(6,98,add_2_2);		
					display_ASCIIstring_8x16(6,108,add_1_1);				
				display_ASCIIstring_8x16(6,118,add_1_2);
}
void Fun_Com_D_8()
{
        clear_screen();       
        	unsigned char mima0[2],mima1[2],mima2[2],mima3[2];
	  EEPROM_R(Addr_mima_set,mima_set,4,0xA0);
    Lcd12864_Write16CnCHAR(0,0,0,"17修改密码\r");
		display_graphic_8x16(1,86,maohao);
		mima0[0]=mima_set[0]+0x30;
		mima0[1]='\0';
	  mima1[0]=mima_set[1]+0x30;
		mima1[1]='\0';
		mima2[0]=mima_set[2]+0x30;
		mima2[1]='\0';
	 	mima3[0]=mima_set[3]+0x30;
		mima3[1]='\0';

     display_ASCIIstring_8x16(1,96,mima0);
    display_ASCIIstring_8x16(1,104,mima1);
    display_ASCIIstring_8x16(1,112,mima2);
     display_ASCIIstring_8x16(1,120,mima3);
				
  
Lcd12864_Write16CnCHAR(0,0,3,"18通信地址\r");
			  display_graphic_8x16(1,86,maohao);
//		  display_sanjiao(1,119,0,1);
		    add_1_2[0]=(self_addr_code[0]&0x0F)+0x30;
				add_1_2[1]='\0';
	
	      add_1_1[0]=(self_addr_code[0]>>4)+0x30;
				add_1_1[1]='\0';
	
	      add_2_2[0]=(self_addr_code[1]&0x0F)+0x30;
				add_2_2[1]='\0';
	
	      add_2_1[0]=(self_addr_code[1]>>4)+0x30;
				add_2_1[1]='\0';

	      add_3_2[0]=(self_addr_code[2]&0x0F)+0x30;
 				add_3_2[1]='\0';
	
	      add_3_1[0]=(self_addr_code[2]>>4)+0x30;
				add_3_1[1]='\0';
				
				
	      add_4_2[0]=(self_addr_code[3]&0x0F)+0x30;
 				add_4_2[1]='\0';
	
	      add_4_1[0]=(self_addr_code[3]>>4)+0x30;
				add_4_1[1]='\0';
			

	      add_5_2[0]=(self_addr_code[4]&0x0F)+0x30;
 				add_5_2[1]='\0';
	
	      add_5_1[0]=(self_addr_code[4]>>4)+0x30;
				add_5_1[1]='\0';
			

	      add_6_2[0]=(self_addr_code[5]&0x0F)+0x30;
 				add_6_2[1]='\0';
	
	      add_6_1[0]=(self_addr_code[5]>>4)+0x30;
				add_6_1[1]='\0';
		    if(F_queren==1)
	      {
				  key_state=key_state|((self_addr_code[2])&0x0F);	
	      }
	      if((key_value_tmp==0x40)||(key_value_tmp==0x10)||(key_value_tmp==0x20)&&(F_queren<3))
	      {
		      F_queren++;
	      }
			  self_addr_code_temp[2]=((key_state&0x0F))|((self_addr_code[2])&0xF0);
	      add_3_2[0]=(self_addr_code_temp[2]&0x0F)+0x30;
 				add_3_2[1]='\0';	
	      add_3_1[0]=(self_addr_code_temp[2]>>4)+0x30;
				add_3_1[1]='\0';				
				display_ASCIIstring_8x16(6,8,add_6_1);
				display_ASCIIstring_8x16(6,18,add_6_2);			
				display_ASCIIstring_8x16(6,28,add_5_1);
				display_ASCIIstring_8x16(6,38,add_5_2);			
				display_ASCIIstring_8x16(6,48,add_4_1);
				display_ASCIIstring_8x16(6,58,add_4_2);							
				display_ASCIIstring_8x16(6,68,add_3_1);
				display_ASCIIstring_8x16_fanxian(6,78,add_3_2);	
				display_ASCIIstring_8x16(6,88,add_2_1);
				display_ASCIIstring_8x16(6,98,add_2_2);		
				display_ASCIIstring_8x16(6,108,add_1_1);				
				display_ASCIIstring_8x16(6,118,add_1_2);
				
			  if((key_value_tmp==0x20)&&(F_queren==3))
	      {
				  self_addr_code[0]=self_addr_code[0];
				  self_addr_code[1]=self_addr_code[1] ;
				  self_addr_code[2]=self_addr_code_temp[2];
				  self_addr_code[3]=self_addr_code[3] ;
				  self_addr_code[4]=self_addr_code[4];
				  self_addr_code[5]=self_addr_code[5] ;											//lpb,设备断电自动回复初始地址
				  MODIFY_EEP_W(Addr_dev_addr,self_addr_code,Lenth_dev_addr,0xA0);
          key_state=0x39100;		
		      F_queren=1;
	      }
				if((key_value_tmp==0x10)&&(F_queren==3)) 
        {					
					key_state=0x37100;
					F_queren=1;
				}
				if((key_value_tmp==0x40)&&(F_queren==3)) 
        {					
					key_state=0x39100;
					F_queren=1;
				}
}
void Com_D_8()
{
clear_screen();       
Lcd12864_Write16CnCHAR(0,0,0,"5通信地址\r");
			display_graphic_8x16(1,77,maohao);
		 Lcd12864_Write16CnCHAR(0,80,0,"A5-A0\r");
//		  display_sanjiao(1,119,0,1);
	add_1_2[0]=(self_addr_code[0]&0x0F)+0x30;
				add_1_2[1]='\0';
	
	      add_1_1[0]=(self_addr_code[0]>>4)+0x30;
				add_1_1[1]='\0';
	
	      add_2_2[0]=(self_addr_code[1]&0x0F)+0x30;
				add_2_2[1]='\0';
	
	      add_2_1[0]=(self_addr_code[1]>>4)+0x30;
				add_2_1[1]='\0';
           if(key_value_tmp==0x20)
				{
					key_state=key_state|((self_addr_code[2])&0x0F);		
				}
			  self_addr_code_temp[2]=((key_state&0x0F))|((self_addr_code[2])&0xF0);
				
	      add_3_2[0]=(self_addr_code_temp[2]&0x0F)+0x30;
 				add_3_2[1]='\0';
	
	      add_3_1[0]=(self_addr_code_temp[2]>>4)+0x30;
				add_3_1[1]='\0';
				
				   
				
	      add_4_2[0]=(self_addr_code[3]&0x0F)+0x30;
 				add_4_2[1]='\0';
	
	      add_4_1[0]=(self_addr_code[3]>>4)+0x30;
				add_4_1[1]='\0';
			
      
	     
				
	      add_5_2[0]=(self_addr_code[4]&0x0F)+0x30;
 				add_5_2[1]='\0';
	
	      add_5_1[0]=(self_addr_code[4]>>4)+0x30;
				add_5_1[1]='\0';
			
         
	      add_6_2[0]=(self_addr_code[5]&0x0F)+0x30;
 				add_6_2[1]='\0';
	
	      add_6_1[0]=(self_addr_code[5]>>4)+0x30;
				add_6_1[1]='\0';

		
				
				display_ASCIIstring_8x16(6,8,add_6_1);
				display_ASCIIstring_8x16(6,18,add_6_2);
				
					display_ASCIIstring_8x16(6,28,add_5_1);
				display_ASCIIstring_8x16(6,38,add_5_2);
//				
					display_ASCIIstring_8x16(6,48,add_4_1);
				display_ASCIIstring_8x16(6,58,add_4_2);
					
				
					display_ASCIIstring_8x16(6,68,add_3_1);
				display_ASCIIstring_8x16_fanxian(6,78,add_3_2);
				
					display_ASCIIstring_8x16(6,88,add_2_1);
				display_ASCIIstring_8x16(6,98,add_2_2);
				
				
					display_ASCIIstring_8x16(6,108,add_1_1);
					
				display_ASCIIstring_8x16(6,118,add_1_2);
}
void Fun_Com_D_9()
{
        clear_screen();       
        	unsigned char mima0[2],mima1[2],mima2[2],mima3[2];
	  EEPROM_R(Addr_mima_set,mima_set,4,0xA0);
    Lcd12864_Write16CnCHAR(0,0,0,"17修改密码\r");
		display_graphic_8x16(1,86,maohao);
		mima0[0]=mima_set[0]+0x30;
		mima0[1]='\0';
	  mima1[0]=mima_set[1]+0x30;
		mima1[1]='\0';
		mima2[0]=mima_set[2]+0x30;
		mima2[1]='\0';
	 	mima3[0]=mima_set[3]+0x30;
		mima3[1]='\0';

     display_ASCIIstring_8x16(1,96,mima0);
    display_ASCIIstring_8x16(1,104,mima1);
    display_ASCIIstring_8x16(1,112,mima2);
     display_ASCIIstring_8x16(1,120,mima3);
				
  
Lcd12864_Write16CnCHAR(0,0,3,"18通信地址\r");
		    display_graphic_8x16(1,86,maohao);
//		  display_sanjiao(1,119,0,1);
		    add_1_2[0]=(self_addr_code[0]&0x0F)+0x30;
				add_1_2[1]='\0';
	
	      add_1_1[0]=(self_addr_code[0]>>4)+0x30;
				add_1_1[1]='\0';
	
	      add_2_2[0]=(self_addr_code[1]&0x0F)+0x30;
				add_2_2[1]='\0';
	
	      add_2_1[0]=(self_addr_code[1]>>4)+0x30;
				add_2_1[1]='\0';

	      add_3_2[0]=(self_addr_code[2]&0x0F)+0x30;
 				add_3_2[1]='\0';
	
	      add_3_1[0]=(self_addr_code[2]>>4)+0x30;
				add_3_1[1]='\0';
				
				
	      add_4_2[0]=(self_addr_code[3]&0x0F)+0x30;
 				add_4_2[1]='\0';
	
	      add_4_1[0]=(self_addr_code[3]>>4)+0x30;
				add_4_1[1]='\0';
			

	      add_5_2[0]=(self_addr_code[4]&0x0F)+0x30;
 				add_5_2[1]='\0';
	
	      add_5_1[0]=(self_addr_code[4]>>4)+0x30;
				add_5_1[1]='\0';
			

	      add_6_2[0]=(self_addr_code[5]&0x0F)+0x30;
 				add_6_2[1]='\0';
	
	      add_6_1[0]=(self_addr_code[5]>>4)+0x30;
				add_6_1[1]='\0';
		    if(F_queren==1)
	      {
					key_state=key_state|((self_addr_code[1])>>4);
	      }
	      if((key_value_tmp==0x40)||(key_value_tmp==0x10)||(key_value_tmp==0x20)&&(F_queren<3))
	      {
		      F_queren++;
	      }
			  self_addr_code_temp[1]=((key_state&0x0F)<<4)|((self_addr_code[1])&0x0F);
				add_2_2[0]=(self_addr_code_temp[1]&0x0F)+0x30;
				add_2_2[1]='\0';
	
	      add_2_1[0]=(self_addr_code_temp[1]>>4)+0x30;
				add_2_1[1]='\0';
				display_ASCIIstring_8x16(6,8,add_6_1);
				display_ASCIIstring_8x16(6,18,add_6_2);			
				display_ASCIIstring_8x16(6,28,add_5_1);
				display_ASCIIstring_8x16(6,38,add_5_2);			
				display_ASCIIstring_8x16(6,48,add_4_1);
				display_ASCIIstring_8x16(6,58,add_4_2);							
				display_ASCIIstring_8x16(6,68,add_3_1);
				display_ASCIIstring_8x16(6,78,add_3_2);	
				display_ASCIIstring_8x16_fanxian(6,88,add_2_1);
				display_ASCIIstring_8x16(6,98,add_2_2);		
				display_ASCIIstring_8x16(6,108,add_1_1);				
				display_ASCIIstring_8x16(6,118,add_1_2);
				
			  if((key_value_tmp==0x20)&&(F_queren==3))
	      {
				  self_addr_code[0]=self_addr_code[0];
				  self_addr_code[1]=self_addr_code_temp[1] ;
				  self_addr_code[2]=self_addr_code[2];
				  self_addr_code[3]=self_addr_code[3] ;
				  self_addr_code[4]=self_addr_code[4];
				  self_addr_code[5]=self_addr_code[5] ;											//lpb,设备断电自动回复初始地址
				  MODIFY_EEP_W(Addr_dev_addr,self_addr_code,Lenth_dev_addr,0xA0);
          key_state=0x3A100;		
		      F_queren=1;
	      }
				if((key_value_tmp==0x10)&&(F_queren==3)) 
        {					
					key_state=0x38100;
					F_queren=1;
				}
				if((key_value_tmp==0x40)&&(F_queren==3)) 
        {					
					key_state=0x3A100;
					F_queren=1;
				}
}
void Com_D_9()
{
clear_screen();       
Lcd12864_Write16CnCHAR(0,0,0,"5通信地址\r");
			display_graphic_8x16(1,77,maohao);
		 Lcd12864_Write16CnCHAR(0,80,0,"A5-A0\r");
//		  display_sanjiao(1,119,0,1);
	add_1_2[0]=(self_addr_code[0]&0x0F)+0x30;
				add_1_2[1]='\0';
	
	      add_1_1[0]=(self_addr_code[0]>>4)+0x30;
				add_1_1[1]='\0';
	     if(key_value_tmp==0x20)
				{
					key_state=key_state|((self_addr_code[1])>>4);		
				}
			  self_addr_code_temp[1]=((key_state&0x0F)<<4)|((self_addr_code[1])&0x0F);
	      add_2_2[0]=(self_addr_code_temp[1]&0x0F)+0x30;
				add_2_2[1]='\0';
	
	      add_2_1[0]=(self_addr_code_temp[1]>>4)+0x30;
				add_2_1[1]='\0';

				
	      add_3_2[0]=(self_addr_code[2]&0x0F)+0x30;
 				add_3_2[1]='\0';
	
	      add_3_1[0]=(self_addr_code[2]>>4)+0x30;
				add_3_1[1]='\0';
				
				
      
				
	      add_4_2[0]=(self_addr_code[3]&0x0F)+0x30;
 				add_4_2[1]='\0';
	
	      add_4_1[0]=(self_addr_code[3]>>4)+0x30;
				add_4_1[1]='\0';
			
	      add_5_2[0]=(self_addr_code[4]&0x0F)+0x30;
 				add_5_2[1]='\0';
	
	      add_5_1[0]=(self_addr_code[4]>>4)+0x30;
				add_5_1[1]='\0';

	      add_6_2[0]=(self_addr_code[5]&0x0F)+0x30;
 				add_6_2[1]='\0';
	      add_6_1[0]=(self_addr_code[5]>>4)+0x30;
				add_6_1[1]='\0';
				display_ASCIIstring_8x16(6,8,add_6_1);
				display_ASCIIstring_8x16(6,18,add_6_2);			
					display_ASCIIstring_8x16(6,28,add_5_1);
				display_ASCIIstring_8x16(6,38,add_5_2);			
					display_ASCIIstring_8x16(6,48,add_4_1);
				display_ASCIIstring_8x16(6,58,add_4_2);							
					display_ASCIIstring_8x16(6,68,add_3_1);
				display_ASCIIstring_8x16(6,78,add_3_2);	
					display_ASCIIstring_8x16_fanxian(6,88,add_2_1);
				display_ASCIIstring_8x16(6,98,add_2_2);		
					display_ASCIIstring_8x16(6,108,add_1_1);				
				display_ASCIIstring_8x16(6,118,add_1_2);
}
void Fun_Com_D_10()
{
        clear_screen();       
        	unsigned char mima0[2],mima1[2],mima2[2],mima3[2];
	  EEPROM_R(Addr_mima_set,mima_set,4,0xA0);
    Lcd12864_Write16CnCHAR(0,0,0,"17修改密码\r");
		display_graphic_8x16(1,86,maohao);
		mima0[0]=mima_set[0]+0x30;
		mima0[1]='\0';
	  mima1[0]=mima_set[1]+0x30;
		mima1[1]='\0';
		mima2[0]=mima_set[2]+0x30;
		mima2[1]='\0';
	 	mima3[0]=mima_set[3]+0x30;
		mima3[1]='\0';

     display_ASCIIstring_8x16(1,96,mima0);
    display_ASCIIstring_8x16(1,104,mima1);
    display_ASCIIstring_8x16(1,112,mima2);
     display_ASCIIstring_8x16(1,120,mima3);
				
  
Lcd12864_Write16CnCHAR(0,0,3,"18通信地址\r");
			  display_graphic_8x16(1,86,maohao);
//		  display_sanjiao(1,119,0,1);
		    add_1_2[0]=(self_addr_code[0]&0x0F)+0x30;
				add_1_2[1]='\0';
	
	      add_1_1[0]=(self_addr_code[0]>>4)+0x30;
				add_1_1[1]='\0';
	
	      add_2_2[0]=(self_addr_code[1]&0x0F)+0x30;
				add_2_2[1]='\0';
	
	      add_2_1[0]=(self_addr_code[1]>>4)+0x30;
				add_2_1[1]='\0';

	      add_3_2[0]=(self_addr_code[2]&0x0F)+0x30;
 				add_3_2[1]='\0';
	
	      add_3_1[0]=(self_addr_code[2]>>4)+0x30;
				add_3_1[1]='\0';
				
				
	      add_4_2[0]=(self_addr_code[3]&0x0F)+0x30;
 				add_4_2[1]='\0';
	
	      add_4_1[0]=(self_addr_code[3]>>4)+0x30;
				add_4_1[1]='\0';
			

	      add_5_2[0]=(self_addr_code[4]&0x0F)+0x30;
 				add_5_2[1]='\0';
	
	      add_5_1[0]=(self_addr_code[4]>>4)+0x30;
				add_5_1[1]='\0';
			

	      add_6_2[0]=(self_addr_code[5]&0x0F)+0x30;
 				add_6_2[1]='\0';
	
	      add_6_1[0]=(self_addr_code[5]>>4)+0x30;
				add_6_1[1]='\0';
		    if(F_queren==1)
	      {
					key_state=key_state|((self_addr_code[1])&0x0F);	
	      }
	      if((key_value_tmp==0x40)||(key_value_tmp==0x10)||(key_value_tmp==0x20)&&(F_queren<3))
	      {
		      F_queren++;
	      }
			  self_addr_code_temp[1]=((key_state&0x0F))|((self_addr_code[1])&0xF0);
	      add_2_2[0]=(self_addr_code_temp[1]&0x0F)+0x30;
				add_2_2[1]='\0';
	
	      add_2_1[0]=(self_addr_code_temp[1]>>4)+0x30;
				add_2_1[1]='\0';				
				display_ASCIIstring_8x16(6,8,add_6_1);
				display_ASCIIstring_8x16(6,18,add_6_2);			
				display_ASCIIstring_8x16(6,28,add_5_1);
				display_ASCIIstring_8x16(6,38,add_5_2);			
				display_ASCIIstring_8x16(6,48,add_4_1);
				display_ASCIIstring_8x16(6,58,add_4_2);							
				display_ASCIIstring_8x16(6,68,add_3_1);
				display_ASCIIstring_8x16(6,78,add_3_2);	
				display_ASCIIstring_8x16(6,88,add_2_1);
				display_ASCIIstring_8x16_fanxian(6,98,add_2_2);		
				display_ASCIIstring_8x16(6,108,add_1_1);				
				display_ASCIIstring_8x16(6,118,add_1_2);
				
			  if((key_value_tmp==0x20)&&(F_queren==3))
	      {
				  self_addr_code[0]=self_addr_code[0];
				  self_addr_code[1]=self_addr_code_temp[1] ;
				  self_addr_code[2]=self_addr_code[2];
				  self_addr_code[3]=self_addr_code[3] ;
				  self_addr_code[4]=self_addr_code[4];
				  self_addr_code[5]=self_addr_code[5] ;											//lpb,设备断电自动回复初始地址
				  MODIFY_EEP_W(Addr_dev_addr,self_addr_code,Lenth_dev_addr,0xA0);
          key_state=0x3B100;		
		      F_queren=1;
	      }
				if((key_value_tmp==0x10)&&(F_queren==3)) 
        {					
					key_state=0x39100;
					F_queren=1;
				}
				if((key_value_tmp==0x40)&&(F_queren==3)) 
        {					
					key_state=0x3B100;
					F_queren=1;
				}
}
void Com_D_10()
{
clear_screen();       
Lcd12864_Write16CnCHAR(0,0,0,"5通信地址\r");
			display_graphic_8x16(1,77,maohao);
		 Lcd12864_Write16CnCHAR(0,80,0,"A5-A0\r");
//		  display_sanjiao(1,119,0,1);
add_1_2[0]=(self_addr_code[0]&0x0F)+0x30;
				add_1_2[1]='\0';
	
	      add_1_1[0]=(self_addr_code[0]>>4)+0x30;
				add_1_1[1]='\0';
	
	       if(key_value_tmp==0x20)
				{
					key_state=key_state|((self_addr_code[1])&0x0F);		
				}
			  self_addr_code_temp[1]=((key_state&0x0F))|((self_addr_code[1])&0xF0);
				
	      add_2_2[0]=(self_addr_code_temp[1]&0x0F)+0x30;
				add_2_2[1]='\0';
	
	      add_2_1[0]=(self_addr_code_temp[1]>>4)+0x30;
				add_2_1[1]='\0';
       
				
	      add_3_2[0]=(self_addr_code[2]&0x0F)+0x30;
 				add_3_2[1]='\0';
	
	      add_3_1[0]=(self_addr_code[2]>>4)+0x30;
				add_3_1[1]='\0';
				
				   
				
	      add_4_2[0]=(self_addr_code[3]&0x0F)+0x30;
 				add_4_2[1]='\0';
	
	      add_4_1[0]=(self_addr_code[3]>>4)+0x30;
				add_4_1[1]='\0';
			
      
	     
				
	      add_5_2[0]=(self_addr_code[4]&0x0F)+0x30;
 				add_5_2[1]='\0';
	
	      add_5_1[0]=(self_addr_code[4]>>4)+0x30;
				add_5_1[1]='\0';
			
         
	      add_6_2[0]=(self_addr_code[5]&0x0F)+0x30;
 				add_6_2[1]='\0';
	
	      add_6_1[0]=(self_addr_code[5]>>4)+0x30;
				add_6_1[1]='\0';

		
				
				display_ASCIIstring_8x16(6,8,add_6_1);
				display_ASCIIstring_8x16(6,18,add_6_2);
				
					display_ASCIIstring_8x16(6,28,add_5_1);
				display_ASCIIstring_8x16(6,38,add_5_2);
//				
					display_ASCIIstring_8x16(6,48,add_4_1);
				display_ASCIIstring_8x16(6,58,add_4_2);
					
				
					display_ASCIIstring_8x16(6,68,add_3_1);
				display_ASCIIstring_8x16(6,78,add_3_2);
				
					display_ASCIIstring_8x16(6,88,add_2_1);
				display_ASCIIstring_8x16_fanxian(6,98,add_2_2);
				
				
					display_ASCIIstring_8x16(6,108,add_1_1);
					
				display_ASCIIstring_8x16(6,118,add_1_2);
		
}
void Fun_Com_D_11()
{
        clear_screen();       
        	unsigned char mima0[2],mima1[2],mima2[2],mima3[2];
	  EEPROM_R(Addr_mima_set,mima_set,4,0xA0);
    Lcd12864_Write16CnCHAR(0,0,0,"17修改密码\r");
		display_graphic_8x16(1,86,maohao);
		mima0[0]=mima_set[0]+0x30;
		mima0[1]='\0';
	  mima1[0]=mima_set[1]+0x30;
		mima1[1]='\0';
		mima2[0]=mima_set[2]+0x30;
		mima2[1]='\0';
	 	mima3[0]=mima_set[3]+0x30;
		mima3[1]='\0';

     display_ASCIIstring_8x16(1,96,mima0);
    display_ASCIIstring_8x16(1,104,mima1);
    display_ASCIIstring_8x16(1,112,mima2);
     display_ASCIIstring_8x16(1,120,mima3);
				
  
Lcd12864_Write16CnCHAR(0,0,3,"18通信地址\r");
		    display_graphic_8x16(1,86,maohao);
//		  display_sanjiao(1,119,0,1);
		    add_1_2[0]=(self_addr_code[0]&0x0F)+0x30;
				add_1_2[1]='\0';
	
	      add_1_1[0]=(self_addr_code[0]>>4)+0x30;
				add_1_1[1]='\0';
	
	      add_2_2[0]=(self_addr_code[1]&0x0F)+0x30;
				add_2_2[1]='\0';
	
	      add_2_1[0]=(self_addr_code[1]>>4)+0x30;
				add_2_1[1]='\0';

	      add_3_2[0]=(self_addr_code[2]&0x0F)+0x30;
 				add_3_2[1]='\0';
	
	      add_3_1[0]=(self_addr_code[2]>>4)+0x30;
				add_3_1[1]='\0';
				
				
	      add_4_2[0]=(self_addr_code[3]&0x0F)+0x30;
 				add_4_2[1]='\0';
	
	      add_4_1[0]=(self_addr_code[3]>>4)+0x30;
				add_4_1[1]='\0';
			

	      add_5_2[0]=(self_addr_code[4]&0x0F)+0x30;
 				add_5_2[1]='\0';
	
	      add_5_1[0]=(self_addr_code[4]>>4)+0x30;
				add_5_1[1]='\0';
			

	      add_6_2[0]=(self_addr_code[5]&0x0F)+0x30;
 				add_6_2[1]='\0';
	
	      add_6_1[0]=(self_addr_code[5]>>4)+0x30;
				add_6_1[1]='\0';
		    if(F_queren==1)
	      {
					key_state=key_state|((self_addr_code[0])>>4);
	      }
	      if((key_value_tmp==0x40)||(key_value_tmp==0x10)||(key_value_tmp==0x20)&&(F_queren<3))
	      {
		      F_queren++;
	      }
			  self_addr_code_temp[0]=((key_state&0x0F)<<4)|((self_addr_code[0])&0x0F);
				add_1_2[0]=(self_addr_code_temp[0]&0x0F)+0x30;
				add_1_2[1]='\0';
	
	      add_1_1[0]=(self_addr_code_temp[0]>>4)+0x30;
				add_1_1[1]='\0';
				display_ASCIIstring_8x16(6,8,add_6_1);
				display_ASCIIstring_8x16(6,18,add_6_2);			
				display_ASCIIstring_8x16(6,28,add_5_1);
				display_ASCIIstring_8x16(6,38,add_5_2);			
				display_ASCIIstring_8x16(6,48,add_4_1);
				display_ASCIIstring_8x16(6,58,add_4_2);							
				display_ASCIIstring_8x16(6,68,add_3_1);
				display_ASCIIstring_8x16(6,78,add_3_2);	
				display_ASCIIstring_8x16(6,88,add_2_1);
				display_ASCIIstring_8x16(6,98,add_2_2);		
				display_ASCIIstring_8x16_fanxian(6,108,add_1_1);				
				display_ASCIIstring_8x16(6,118,add_1_2);
				
			  if((key_value_tmp==0x20)&&(F_queren==3))
	      {
				  self_addr_code[0]=self_addr_code_temp[0];
				  self_addr_code[1]=self_addr_code[1] ;
				  self_addr_code[2]=self_addr_code[2];
				  self_addr_code[3]=self_addr_code[3] ;
				  self_addr_code[4]=self_addr_code[4];
				  self_addr_code[5]=self_addr_code[5] ;											//lpb,设备断电自动回复初始地址
				  MODIFY_EEP_W(Addr_dev_addr,self_addr_code,Lenth_dev_addr,0xA0);
          key_state=0x3C100;		
		      F_queren=1;
	      }
				if((key_value_tmp==0x10)&&(F_queren==3)) 
        {					
					key_state=0x50100;
					F_queren=1;
				}
				if((key_value_tmp==0x40)&&(F_queren==3)) 
        {					
					key_state=0x3C100;
					F_queren=1;
				}
}
void Com_D_11()
{
clear_screen();       
Lcd12864_Write16CnCHAR(0,0,0,"5通信地址\r");
			display_graphic_8x16(1,77,maohao);
		 Lcd12864_Write16CnCHAR(0,80,0,"A5-A0\r");
//		  display_sanjiao(1,119,0,1);
	if(key_value_tmp==0x20)
				{
					key_state=key_state|((self_addr_code[0])>>4);		
				}
			  self_addr_code_temp[0]=((key_state&0x0F)<<4)|((self_addr_code[0])&0x0F);				
				add_1_2[0]=(self_addr_code_temp[0]&0x0F)+0x30;
				add_1_2[1]='\0';
	
	      add_1_1[0]=(self_addr_code_temp[0]>>4)+0x30;
				add_1_1[1]='\0';
	     
	      add_2_2[0]=(self_addr_code[1]&0x0F)+0x30;
				add_2_2[1]='\0';
	
	      add_2_1[0]=(self_addr_code[1]>>4)+0x30;
				add_2_1[1]='\0';

				
	      add_3_2[0]=(self_addr_code[2]&0x0F)+0x30;
 				add_3_2[1]='\0';
	
	      add_3_1[0]=(self_addr_code[2]>>4)+0x30;
				add_3_1[1]='\0';
				
				
      
				
	      add_4_2[0]=(self_addr_code[3]&0x0F)+0x30;
 				add_4_2[1]='\0';
	
	      add_4_1[0]=(self_addr_code[3]>>4)+0x30;
				add_4_1[1]='\0';
			
	      add_5_2[0]=(self_addr_code[4]&0x0F)+0x30;
 				add_5_2[1]='\0';
	
	      add_5_1[0]=(self_addr_code[4]>>4)+0x30;
				add_5_1[1]='\0';

	      add_6_2[0]=(self_addr_code[5]&0x0F)+0x30;
 				add_6_2[1]='\0';
	      add_6_1[0]=(self_addr_code[5]>>4)+0x30;
				add_6_1[1]='\0';
				display_ASCIIstring_8x16(6,8,add_6_1);
				display_ASCIIstring_8x16(6,18,add_6_2);			
					display_ASCIIstring_8x16(6,28,add_5_1);
				display_ASCIIstring_8x16(6,38,add_5_2);			
					display_ASCIIstring_8x16(6,48,add_4_1);
				display_ASCIIstring_8x16(6,58,add_4_2);							
					display_ASCIIstring_8x16(6,68,add_3_1);
				display_ASCIIstring_8x16(6,78,add_3_2);	
					display_ASCIIstring_8x16(6,88,add_2_1);
				display_ASCIIstring_8x16(6,98,add_2_2);		
					display_ASCIIstring_8x16_fanxian(6,108,add_1_1);				
				display_ASCIIstring_8x16(6,118,add_1_2);
	
}
void Fun_Com_D_12()
{
        clear_screen();       
       	unsigned char mima0[2],mima1[2],mima2[2],mima3[2];
	  EEPROM_R(Addr_mima_set,mima_set,4,0xA0);
    Lcd12864_Write16CnCHAR(0,0,0,"17修改密码\r");
		display_graphic_8x16(1,86,maohao);
		mima0[0]=mima_set[0]+0x30;
		mima0[1]='\0';
	  mima1[0]=mima_set[1]+0x30;
		mima1[1]='\0';
		mima2[0]=mima_set[2]+0x30;
		mima2[1]='\0';
	 	mima3[0]=mima_set[3]+0x30;
		mima3[1]='\0';

     display_ASCIIstring_8x16(1,96,mima0);
    display_ASCIIstring_8x16(1,104,mima1);
    display_ASCIIstring_8x16(1,112,mima2);
     display_ASCIIstring_8x16(1,120,mima3);
				
  
Lcd12864_Write16CnCHAR(0,0,3,"18通信地址\r");
			  display_graphic_8x16(1,86,maohao);
//		  display_sanjiao(1,119,0,1);
		    add_1_2[0]=(self_addr_code[0]&0x0F)+0x30;
				add_1_2[1]='\0';
	
	      add_1_1[0]=(self_addr_code[0]>>4)+0x30;
				add_1_1[1]='\0';
	
	      add_2_2[0]=(self_addr_code[1]&0x0F)+0x30;
				add_2_2[1]='\0';
	
	      add_2_1[0]=(self_addr_code[1]>>4)+0x30;
				add_2_1[1]='\0';

	      add_3_2[0]=(self_addr_code[2]&0x0F)+0x30;
 				add_3_2[1]='\0';
	
	      add_3_1[0]=(self_addr_code[2]>>4)+0x30;
				add_3_1[1]='\0';
				
				
	      add_4_2[0]=(self_addr_code[3]&0x0F)+0x30;
 				add_4_2[1]='\0';
	
	      add_4_1[0]=(self_addr_code[3]>>4)+0x30;
				add_4_1[1]='\0';
			

	      add_5_2[0]=(self_addr_code[4]&0x0F)+0x30;
 				add_5_2[1]='\0';
	
	      add_5_1[0]=(self_addr_code[4]>>4)+0x30;
				add_5_1[1]='\0';
			

	      add_6_2[0]=(self_addr_code[5]&0x0F)+0x30;
 				add_6_2[1]='\0';
	
	      add_6_1[0]=(self_addr_code[5]>>4)+0x30;
				add_6_1[1]='\0';
		    if(F_queren==1)
	      {
					key_state=key_state|((self_addr_code[0])&0x0F);	
	      }
	      if((key_value_tmp==0x40)||(key_value_tmp==0x10)||(key_value_tmp==0x20)&&(F_queren<3))
	      {
		      F_queren++;
	      }
			  self_addr_code_temp[0]=((key_state&0x0F))|((self_addr_code[0])&0xF0);
				add_1_2[0]=(self_addr_code_temp[0]&0x0F)+0x30;
				add_1_2[1]='\0';
	
	      add_1_1[0]=(self_addr_code_temp[0]>>4)+0x30;
				add_1_1[1]='\0';			
				display_ASCIIstring_8x16(6,8,add_6_1);
				display_ASCIIstring_8x16(6,18,add_6_2);			
				display_ASCIIstring_8x16(6,28,add_5_1);
				display_ASCIIstring_8x16(6,38,add_5_2);			
				display_ASCIIstring_8x16(6,48,add_4_1);
				display_ASCIIstring_8x16(6,58,add_4_2);							
				display_ASCIIstring_8x16(6,68,add_3_1);
				display_ASCIIstring_8x16(6,78,add_3_2);	
				display_ASCIIstring_8x16(6,88,add_2_1);
				display_ASCIIstring_8x16(6,98,add_2_2);		
				display_ASCIIstring_8x16(6,108,add_1_1);				
				display_ASCIIstring_8x16_fanxian(6,118,add_1_2);
				
			  if((key_value_tmp==0x20)&&(F_queren==3))
	      {
				  self_addr_code[0]=self_addr_code_temp[0];
				  self_addr_code[1]=self_addr_code[1] ;
				  self_addr_code[2]=self_addr_code[2];
				  self_addr_code[3]=self_addr_code[3] ;
				  self_addr_code[4]=self_addr_code[4];
				  self_addr_code[5]=self_addr_code[5] ;											//lpb,设备断电自动回复初始地址
				  MODIFY_EEP_W(Addr_dev_addr,self_addr_code,Lenth_dev_addr,0xA0);
          key_state=0x21100;		
		      F_queren=1;
	      }
				if((key_value_tmp==0x10)&&(F_queren==3)) 
        {					
					key_state=0x3B100;
					F_queren=1;
				}
				if((key_value_tmp==0x40)&&(F_queren==3)) 
        {					
					key_state=0x30100;
					F_queren=1;
				}
}
void Com_D_12()
{
	int i;
clear_screen(); 
Lcd12864_Write16CnCHAR(0,0,0,"5通信地址\r");
			display_graphic_8x16(1,77,maohao);
		 Lcd12864_Write16CnCHAR(0,80,0,"A5-A0\r");
//		  display_sanjiao(1,119,0,1);
	 if(key_value_tmp==0x20)
				{
					key_state=key_state|((self_addr_code[0])&0x0F);		
				}
			  self_addr_code_temp[0]=((key_state&0x0F))|((self_addr_code[0])&0xF0);
				
				add_1_2[0]=(self_addr_code_temp[0]&0x0F)+0x30;
				add_1_2[1]='\0';
	
	      add_1_1[0]=(self_addr_code_temp[0]>>4)+0x30;
				add_1_1[1]='\0';

				
	      add_2_2[0]=(self_addr_code[1]&0x0F)+0x30;
				add_2_2[1]='\0';
	
	      add_2_1[0]=(self_addr_code[1]>>4)+0x30;
				add_2_1[1]='\0';
       
				
	      add_3_2[0]=(self_addr_code[2]&0x0F)+0x30;
 				add_3_2[1]='\0';
	
	      add_3_1[0]=(self_addr_code[2]>>4)+0x30;
				add_3_1[1]='\0';
				
				   
				
	      add_4_2[0]=(self_addr_code[3]&0x0F)+0x30;
 				add_4_2[1]='\0';
	
	      add_4_1[0]=(self_addr_code[3]>>4)+0x30;
				add_4_1[1]='\0';
			
      
	     
				
	      add_5_2[0]=(self_addr_code[4]&0x0F)+0x30;
 				add_5_2[1]='\0';
	
	      add_5_1[0]=(self_addr_code[4]>>4)+0x30;
				add_5_1[1]='\0';
			
         
	      add_6_2[0]=(self_addr_code[5]&0x0F)+0x30;
 				add_6_2[1]='\0';
	
	      add_6_1[0]=(self_addr_code[5]>>4)+0x30;
				add_6_1[1]='\0';

		
				
				display_ASCIIstring_8x16(6,8,add_6_1);
				display_ASCIIstring_8x16(6,18,add_6_2);
				
					display_ASCIIstring_8x16(6,28,add_5_1);
				display_ASCIIstring_8x16(6,38,add_5_2);
//				
					display_ASCIIstring_8x16(6,48,add_4_1);
				display_ASCIIstring_8x16(6,58,add_4_2);
					
				
					display_ASCIIstring_8x16(6,68,add_3_1);
				display_ASCIIstring_8x16(6,78,add_3_2);
				
					display_ASCIIstring_8x16(6,88,add_2_1);
				display_ASCIIstring_8x16(6,98,add_2_2);
				
				
					display_ASCIIstring_8x16(6,108,add_1_1);
					
				display_ASCIIstring_8x16_fanxian(6,118,add_1_2);
}

void Time_Hezha_delay()
{
		clear_screen();       
		unsigned char ARR[2],array_tmp[2];
		EEPROM_R(Addr_hezha_delay,ARR,1,0xA0);
		TH_hezha_delay=ARR[0];
		Lcd12864_Write16CnCHAR(0,0,0,"17合闸延时");
		display_ASCIIstring_8x16(1,96,hezha_delay_show[TH_hezha_delay]);
		display_graphic_8x16(1,88,maohao);
	
	  if(F_queren==1)
		{
			key_state=key_state|TH_hezha_delay;
		}
		if((key_value_tmp==0x20)&&(F_queren<3))
		{
			F_queren++;
		}
	  clear_define_screen(0,2,96,128);
	  display_ASCIIstring_8x16_fanxian(1,96,hezha_delay_show[(key_state&0xFF)]);
		 
		if((key_value_tmp==0x20)&&(F_queren==3))
		{
			TH_hezha_delay=((key_state)&0x0F);
			hezha_delay=hezha_delay_arry[TH_hezha_delay];
			array_tmp[0]=TH_hezha_delay ;
			MODIFY_EEP_W(Addr_hezha_delay,array_tmp,1,0xA0);
			clear_define_screen(0,2,96,128);
			display_ASCIIstring_8x16_frame(1,96,hezha_delay_show[TH_hezha_delay]);
			key_state=0x20000000;  
			F_queren=1;
		}
		
				
}

void Fun_Correct_Set()                               //校准设置
{
		if((key_value_tmp==0x40)||(key_value_tmp==0x01))//退出键或者向上键
		{
			clear_screen();
	Lcd12864_Write16CnCHAR(0,16,0,"5时间设置\r  6系统设置\r  7校准设置");
		}
		else
		{
		 clear_define_screen(0,16,91,116);
		}
		
//	display_sanjiao(1,116,1,0);
			display_shouzhi(5,95);
//	if(F_initial_lcd==1)
//	{
//		F_initial_lcd=0;
//	}
}
void Fun_Corr_Slec()
{
    clear_screen();
		unsigned char Array_SD[2],array_tmp[3],Array_LD[2],Array_DY[2];

	EEPROM_R(Addr_shangdian,Array_SD,1,0xA0);
	EEPROM_R(Addr_loudian,Array_LD,1,0xA0);
	EEPROM_R(Addr_dianya,Array_DY,1,0xA0);
	shangdian=Array_SD[0];
	LD_hezha=Array_LD[0];
	DY_hezha=Array_DY[0];
	  Lcd12864_Write16CnCHAR(0,0,0,"13校准档位\r14上电合闸\r15漏电合闸\r16电压合闸");
		display_graphic_8x16(1,94,maohao);
		display_graphic_8x16(3,94,maohao);
	  display_graphic_8x16(5,94,maohao);
	  display_graphic_8x16(7,94,maohao);
	
		display_jiaozhun_frame(1,100,jiaozhun);
	  display_kaiguan(3,100,shangdian);
	  display_kaiguan(5,100,LD_hezha);
	  display_kaiguan(7,100,DY_hezha);
	
	  EEPROM_R(Addr_jiaozhun,array_tmp,1,0xA0);
	  F_Corr=jiaozhun=array_tmp[0];
	  if(key_value_tmp==0x10)
		{
			jiaozhun=1;
		}
		if(key_value_tmp==0x40)
		{
			jiaozhun=0;
		}
        if(jiaozhun==1)	
				{
					array_tmp[0] = 0x01;//T
        clear_define_screen(0,2,100,128);
		    display_jiaozhun_frame(1,100,1);
					F_Corr=1;
				}
        else if(jiaozhun==0)
				{
					array_tmp[0] = 0x00;//K
        clear_define_screen(0,2,100,128);
		    display_jiaozhun_frame(1,100,0);
					F_Corr=0;
				}
        MODIFY_EEP_W(Addr_jiaozhun,array_tmp,1,0xA0);
}

void Fun_Corr_Slec_Set()
{
		 if(key_value_tmp==0x20)
		{
			key_state=key_state|jiaozhun;
		}
	  clear_define_screen(0,2,82,99);
		display_jiaozhun_fanxian(1,83,(key_state&0xFF));
}
//void Fun_Data_Clear(void)
//{
//			clear_screen();
//			Lcd12864_Write16_1CnCHAR(0,0,0,"6数据清零");
//			display_graphic_8x16(1,77,maohao);
//			display_kaiguan_frame(1,83,0);
//}
//void Data_Clear_Set(void)
//{
//		if(key_value_tmp==0x20)
//		{
//		key_state=key_state|F_data_clear;	
//		}
//			clear_define_screen(0,2,82,99);
//			display_kaiguan_fanxian(1,83,(key_state&0xFF));
////if(F_data_clear==1)	
////  {
////	data_clear();
////	}
//}


unsigned int Get_index(unsigned int factor1)
{
	unsigned int menu_index;
	if(factor1==0x1000) menu_index=0;
  if(factor1==0x1010) menu_index=1;
	if(factor1==0x1011) menu_index=2;
	if(factor1==0x1020) menu_index=3;
	if(factor1==0x1021) menu_index=4;
	if(factor1==0x1030) menu_index=5;
	if(factor1==0x1031) menu_index=6;
	if(factor1==0x1040) menu_index=7;
	if(factor1==0x1041) menu_index=8;
	if(factor1==0x1050) menu_index=9;
	if(factor1==0x1051) menu_index=10;
	if(factor1==0x1060) menu_index=11;
	if(factor1==0x1061) menu_index=12;
	if(factor1==0x2000) menu_index=13;
	if(factor1==0x2010) menu_index=14;
	if(factor1==0x2011) menu_index=15;
	if(factor1==0x2020) menu_index=16;
	if(factor1==0x2021) menu_index=17;
	if(factor1==0x2030) menu_index=18;
	if(factor1==0x2031) menu_index=19;
	if(factor1==0x2040) menu_index=20;
	if(factor1==0x2041) menu_index=21;
	if(factor1==0x2050) menu_index=22;
	if(factor1==0x2051) menu_index=23;
	if(factor1==0x2060) menu_index=24;
	if(factor1==0x2061) menu_index=25;
	if(factor1==0x2070) menu_index=26;
	if(factor1==0x2071) menu_index=27;
	if(factor1==0x2080) menu_index=28;
	if(factor1==0x2081) menu_index=29;
	if(factor1==0x2090) menu_index=30;
	if(factor1==0x2091) menu_index=31;
	if(factor1==0x20a0) menu_index=32;
	if(factor1==0x20a1) menu_index=33;
	if(factor1==0x20b0) menu_index=34;
	if(factor1==0x20b1) menu_index=35;
	if(factor1==0x20c0) menu_index=36;
	if(factor1==0x20c1) menu_index=37;
	if(factor1==0x20d0) menu_index=38;
	if(factor1==0x20d1) menu_index=39;
	if(factor1==0x3000) menu_index=40;
	if(factor1==0x3010) menu_index=41;
	if(factor1==0x3011) menu_index=42;
	if(factor1==0x3020) menu_index=43;
	if(factor1==0x3021) menu_index=44;
	if(factor1==0x3030) menu_index=45;
	if(factor1==0x3031) menu_index=46;
	if(factor1==0x3040) menu_index=47;
	if(factor1==0x3041) menu_index=48;
	if(factor1==0x3050) menu_index=49;
	if(factor1==0x3051) menu_index=50;
	if(factor1==0x3060) menu_index=51;
	if(factor1==0x3061) menu_index=52;
	if(factor1==0x3070) menu_index=53;
	if(factor1==0x3071) menu_index=54;
	if(factor1==0x3080) menu_index=55;
	if(factor1==0x3081) menu_index=56;
	if(factor1==0x3090) menu_index=57;
	if(factor1==0x3091) menu_index=58;
	if(factor1==0x4000) menu_index=59;
	if(factor1==0x4010) menu_index=60;
	if(factor1==0x4011) menu_index=61;
	if(factor1==0x4020) menu_index=62;
	if(factor1==0x4021) menu_index=63;
	if(factor1==0x4022) menu_index=64;
	if(factor1==0x4023) menu_index=65;
	if(factor1==0x4024) menu_index=66;
	if(factor1==0x4025) menu_index=67;
	if(factor1==0x4026) menu_index=68;
	if(factor1==0x5000) menu_index=69;
	if(factor1==0x5010) menu_index=70;
	if(factor1==0x5011) menu_index=71;
	if(factor1==0x5020) menu_index=72;
	if(factor1==0x5021) menu_index=73;
	if(factor1==0x5030) menu_index=74;
	if(factor1==0x5031) menu_index=75;
	if(factor1==0x5040) menu_index=76;
	if(factor1==0x5041) menu_index=77;
	if(factor1==0x5050) menu_index=78;
	if(factor1==0x5051) menu_index=79;
	if(factor1==0x5060) menu_index=80;
	if(factor1==0x5061) menu_index=81;
	if(factor1==0x6000) menu_index=82;
	if(factor1==0x6010) menu_index=83;
	if(factor1==0x6011) menu_index=84;	
	if(factor1==0x6020) menu_index=85;
	if(factor1==0x6021) menu_index=86;
	if(factor1==0x6030) menu_index=87;
	if(factor1==0x6031) menu_index=88;
	if(factor1==0x6040) menu_index=89;
	if(factor1==0x6041) menu_index=90;
	if(factor1==0x6050) menu_index=91;
	if(factor1==0x6051) menu_index=92;
	if(factor1==0x6060) menu_index=93;
	if(factor1==0x6061) menu_index=94;
	if(factor1==0x6070) menu_index=95;
	if(factor1==0x6071) menu_index=96;
	if(factor1==0x6080) menu_index=97;
	if(factor1==0x6081) menu_index=98;
	if(factor1==0x6090) menu_index=99;
	if(factor1==0x6091) menu_index=100;
	if(factor1==0x60a0) menu_index=101;
	if(factor1==0x60a1) menu_index=102;
  if(factor1==0x60b0) menu_index=103;
  if(factor1==0x60b1) menu_index=104;
	if(factor1==0x60c0) menu_index=105;
	if(factor1==0x60c1) menu_index=106;
	if(factor1==0x60d0) menu_index=107;
	if(factor1==0x60d1) menu_index=108;
	if(factor1==0x60e0) menu_index=109;
	if(factor1==0x60e1) menu_index=110;
	if(factor1==0x60f0) menu_index=111;
	if(factor1==0x60f1) menu_index=112;
	if(factor1==0x6100) menu_index=113;
	if(factor1==0x6101) menu_index=114;
//	if(factor1==0x6110) menu_index=115;						
//	if(factor1==0x6111) menu_index=116;	
	if(factor1==0x7000) menu_index=115;
  if(factor1==0x7010)	menu_index=116;
	if(factor1==0x7011) menu_index=117;
	return menu_index ;
}
		
void MenuOperate(uchar key)
{	 
	unsigned int B_Num;
     switch(key)
	 {
			 case	0x10:
			{	   
           B_Num= Menu_Tab[Func_Index].Left;
				  Func_Index = Get_index(B_Num);
//				  Func_Index=Menu_Tab[Func_Index].Left;
				
				  break;
			}
			 case  0x01:
			{	  
	
				  B_Num=Menu_Tab[Func_Index].Up;
				 Func_Index = Get_index(B_Num);
				  break;
			}
			case  0x80:
			{	  	
				  B_Num=Menu_Tab[Func_Index].Down;
				Func_Index = Get_index(B_Num);
				  break;
			}
				case 0x40:
			{	  
				  B_Num=Menu_Tab[Func_Index].Right;
					Func_Index = Get_index(B_Num);
				  break;
			}
		  	case 0x20:
			{
				  B_Num=Menu_Tab[Func_Index].Center;
				Func_Index = Get_index(B_Num);
				  break;
			}
	 }

	 Func_Ptr=Menu_Tab[Func_Index].Operate; 
	 (*Func_Ptr)();
	 Func_Ptr=0;
										
}

unsigned char kaiguan_process(unsigned char a)
{
	if(a==0)
	{
		return (*guan);
	}
	else if(a==1)
	{
		return (*kai);
	}
}

//void I_VAL_handle(void)
//{
// 
////	D_Cur=IapReadByte(Addr_D_Cur);                   
//    SET_D_Cur=D_Cur ;
//    //电流框架等级为20~100A
//    //电流框架等级为60~250A
//    
//		if(Type_Cur==0)	
//    {
//        if(SET_D_Cur==9)
//        SET_D_Cur=0 ;
//        SET_I_VAL=SET_D_Cur*10+20 ;
//    }
//		if(Type_Cur==1)
//    {
//        //if(SET_D_Cur==20)
//        //SET_D_Cur=0 ;
//        SET_I_VAL=SET_D_Cur*10+60 ;
//    }
//    //电流框架等级为200~400A
//    if(Type_Cur==2)
//    {
//        if(SET_D_Cur==11)
//        SET_D_Cur=0 ;
//        SET_I_VAL=SET_D_Cur*20+200 ;
//    }
//    //电流框架等级为200~750A 
//    if(Type_Cur==3)
//    {
//        if(SET_D_Cur==16)
//        {
//            SET_D_Cur=0 ;
//        }
//        SET_I_VAL=SET_D_Cur*30+210 ;
//    }

//}

