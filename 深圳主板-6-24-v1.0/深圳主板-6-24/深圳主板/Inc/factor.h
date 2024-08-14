#ifndef __factors_h
#define __factors_h




#define  H_H_V D_HV_Array[Vol_g]
#define  H_L_V D_LV_Array[Vol_q]
#define  V_UP  D_UP_Array[Vol_up]
#define  V_DOWN D_DOWN_Array[Vol_down]
#define F_ZTrip  F_ITrip+F_Trip+F_VTrip+F_UTrip+F_STrip

//5,6	漏电因子	L_factor
//7,8	电压因子	V_factor
//9,10	电流因字	I_factor
/*************************************
          内部存储第0页
		  包括：校准值；档位，控制字；
		        累计记录；事件记录
				部分参数变量
**************************************/
#define Addr_FACTORINIT_value	10000	//2字节，初始化标志
#define Addr_point_event_trip   10003   //2字节，内部记录跳闸记录
#define Addr_L_factor      		10005	//2字节，漏电校准值
#define Addr_V_factor      		10007	//2字节，电压校准值
#define Addr_I_factor      		10009	//2字节，电流校准值
#define Addr_I_2d		      	10011	//1字节，二段保护功能
#define Addr_I_ia             	10012	//1字节，电流重合闸保护功能
#define Addr_L_TB             	10013	//1字节，突变保护功能
#define Addr_C_IP             	10014	//1字节，短路短延时功能
#define Addr_L_JC							10015
#define Addr_F_gc							10146
#define Addr_crtl_word1      	10018	//1字节，控制字1
#define Addr_crtl_word2      	10019	//1字节，控制字2
#define Addr_crtl_word3      	10020	//1字节，控制字3
#define Addr_crtl_word4      	10021	//1字节，控制字4
#define Addr_crtl_word5      	10022	//1字节，控制字5
#define Addr_ctrlword 			10018	//4字节，控制字1-5
#define Addr_Type_Cur 			10023	//1字节，电流壳架等级
#define Addr_Vol_g 				10024	//1字节，过压档位
#define Addr_Vol_q				10025	//1字节，欠压档位
#define Addr_D_A_Lcur 			10026	//1字节，漏电自动档位
#define Addr_D_Cur				10027	//1字节，电流档位
#define Addr_baud				10028	//1字节，波特率
#define Addr_dev_addr 			10029	//6字节，设备通信地址
#define Addr_clear_num			10035	//3字节，清零次数
#define Addr_trip_num			10038	//2字节，总跳闸次数
#define Addr_close_num			10040	//2字节，闭锁跳闸次数
#define Addr_leak_num			10042	//2字节，漏电跳闸次数
#define Addr_current_num		10044	//2字节，电流跳闸次数
#define Addr_vol_num			10046	//2字节，电压跳闸次数
#define Addr_hand_num			10048	//2字节，手动跳闸次数
#define Addr_zero_num			10050	//2字节，缺零跳闸次数
#define Addr_test_num			10052	//2字节，测试跳闸次数
#define Addr_leakquit_num		10054	//2字节，漏电退运次数
#define Addr_2D_num  10410             //2字节，短路延时跳闸次数  
#define Addr_3D_num  10412             //2字节，短路瞬时跳闸次数
#define Addr_leakover_num      10414   //1字节，剩余电流超限次数
//#define Addr_tripkey_num       10416   //1字节，自检次数
#define Addr_leakprotect_num   10416   //1字节，剩余电流保护退出报警次数
//#define Addr_leakchange_num    10417   //1字节，剩余电流保护变化次数

#define Addr_protect_time	 	10056	//4字节，运行总时间
#define Addr_dev_id           	10060	//6字节，设备号
#define Addr_dev_code			10066	//32字节，资产代码
#define Addr_equi_type			10098	//10字节，设备类型
#define Addr_factory_code		10108	//24字节，厂家代码
#define Addr_0_password			10132	//4字节，密码0
#define Addr_1_password			10136	//4字节，密码1
#define Addr_2_password			10140	//4字节，密码2
#define Addr_Vol_ch				10147	//过欠压重合闸

#define Addr_I_3d		      	10250
#define Addr_D2_Cur				10251	
#define Addr_D3_Cur				10252
#define Addr_D2_Time				10253
#define Addr_CurLong_Time				10254
#define Addr_DD_LL				10256
#define Addr_SY_yanshi    10291
#define Addr_GY_yanshi				10257
#define Addr_QY_yanshi				10258
#define Addr_QX_BAOHU				10259
#define Addr_QL_BAOHU				10260
#define Addr_shangdian				10261
#define Addr_loudian				10264
#define Addr_dianya				1002  //1字节
#define Addr_dianliu			1001	//1字节
#define Addr_TX           1003
#define Addr_jiaozhun       10300
#define Addr_wendu       10301
#define Addr_DIANYA_chonghe				10262
#define Addr_duandian				10263
#define Addr_tingdian    10283//已用
#define Addr_SY_F    10288
//#define Addr_SY_T    10291	//2字节，电流校准值
#define Addr_data_clear 10316

#define Addr_AV_factor      		10265	//2字节，电压校准值
#define Addr_BV_factor      		10267	//2字节，电流校准值
#define Addr_CV_factor      		10269	//2字节，电压校准值
#define Addr_AI_factor      		10271	//2字节，电流校准值
#define Addr_BI_factor      		10273	//2字节，电压校准值
#define Addr_CI_factor      		10275	//2字节，电流校准值

#define Addr_L_F    10276	//2字节，电压校准值
#define Addr_AV_F    10277	//2字节，电压校准值
#define Addr_BV_F    10278	//2字节，电流校准值
#define Addr_CV_F    10279	//2字节，电压校准值
#define Addr_AI_F    10280	//2字节，电流校准值
#define Addr_BI_F    10281	//2字节，电压校准值
#define Addr_CI_F    10282	//2字节，电流校准值

#define Addr_L1_slope 10304
#define Addr_V1_A_slope 10306
#define Addr_V1_B_slope 10308
#define Addr_V1_C_slope 10310

#define Addr_I1_A_slope 10312//250壳架
#define Addr_I1_B_slope 10314
#define Addr_I1_C_slope 10316

#define Addr_I1_A_slope1 10318
#define Addr_I1_B_slope1 10320
#define Addr_I1_C_slope1 10322

#define Addr_CurA_cal_tmp 10324
#define Addr_CurB_cal_tmp 10326
#define Addr_CurC_cal_tmp 10328

#define Addr_CurA_cal_tmp1 10330
#define Addr_CurB_cal_tmp1 10332
#define Addr_CurC_cal_tmp1 10334

#define Addr_Leak1_temp    10336

#define Addr_Vol1_A_temp   10338
#define Addr_Vol1_B_temp   10340
#define Addr_Vol1_C_temp   10342

#define Addr400_I1_A_slope 10344   //400壳架
#define Addr400_I1_B_slope 10346
#define Addr400_I1_C_slope 10348

#define Addr400_I1_A_slope1 10350
#define Addr400_I1_B_slope1 10352
#define Addr400_I1_C_slope1 10354

#define Addr400_CurA_cal_tmp 10356
#define Addr400_CurB_cal_tmp 10358
#define Addr400_CurC_cal_tmp 10360

#define Addr400_CurA_cal_tmp1 10362
#define Addr400_CurB_cal_tmp1 10364
#define Addr400_CurC_cal_tmp1 10366

#define Addr630_I1_A_slope 10368   //630壳架
#define Addr630_I1_B_slope 10370
#define Addr630_I1_C_slope 10372

#define Addr630_I1_A_slope1 10374
#define Addr630_I1_B_slope1 10376
#define Addr630_I1_C_slope1 10378

#define Addr630_CurA_cal_tmp 10380
#define Addr630_CurB_cal_tmp 10382
#define Addr630_CurC_cal_tmp 10384

#define Addr630_CurA_cal_tmp1 10386
#define Addr630_CurB_cal_tmp1 10388
#define Addr630_CurC_cal_tmp1 10390

#define Addr800_I1_A_slope 10392   //800壳架
#define Addr800_I1_B_slope 10394
#define Addr800_I1_C_slope 10396

#define Addr800_I1_A_slope1 10398
#define Addr800_I1_B_slope1 10400
#define Addr800_I1_C_slope1 10402

#define Addr800_CurA_cal_tmp 10404
#define Addr800_CurB_cal_tmp 10406
#define Addr800_CurC_cal_tmp 10408

#define Addr800_CurA_cal_tmp1 10410
#define Addr800_CurB_cal_tmp1 10412
#define Addr800_CurC_cal_tmp1 10414

#define Addr100_I1_A_slope 10416   //100壳架
#define Addr100_I1_B_slope 10418
#define Addr100_I1_C_slope 10420

#define Addr100_I1_A_slope1 10422
#define Addr100_I1_B_slope1 10424
#define Addr100_I1_C_slope1 10426

#define Addr100_CurA_cal_tmp 10428
#define Addr100_CurB_cal_tmp 10430
#define Addr100_CurC_cal_tmp 10432

#define Addr100_CurA_cal_tmp1 10434
#define Addr100_CurB_cal_tmp1 10436
#define Addr100_CurC_cal_tmp1 10438

#define Addr100_L1_slope 10440
#define Addr400_L1_slope 10442
#define Addr630_L1_slope 10444
#define Addr800_L1_slope 10446

#define Addr100_Leak1_temp    10448
#define Addr400_Leak1_temp    10450
#define Addr630_Leak1_temp    10452
#define Addr800_Leak1_temp    10454


/***************************瞬动校准*********************************/
#define Addr_DLS_Cur_IV_AD_value   10900       //45			5*3 ad值 五点*3字节
#define Addr_DLS_Cur_IV_slope      10915         //45			5*3  斜率
#define Addr_DLS_Cur_IV_Value      10930        //45			5*3 瞬动电流值

#define Addr_DLS_Cur_I_AD_value   10945       //45			5*3  ad值 五点*3字节
#define Addr_DLS_Cur_I_slope      10960         //45			5*3  斜率
#define Addr_DLS_Cur_I_Value      10975        //45			5*3 瞬动电流值

#define Addr_DLS_Cur_II_AD_value   10990      //45			5*3  ad值 五点*3字节
#define Addr_DLS_Cur_II_slope      11005         //45			5*3  斜率
#define Addr_DLS_Cur_II_Value      11020        //45			5*3 瞬动电流值

#define Addr_DLS_Cur_III_AD_value   11035       //45			5*3  ad值 五点*3字节
#define Addr_DLS_Cur_III_slope      11050         //45			5*3  斜率
#define Addr_DLS_Cur_III_Value      11065        //45			5*3 瞬动电流值
/*************************************/



/*************************************
          外部存储
		  包括：
**************************************/



#define Addr_alarm_value		12	//2字节，漏电超限告警整定值
#define Addr_record_value		14	//2字节，漏电记录差值整定值
#define Addr_record_time		16	//2字节，漏电记录定时整定值
#define Addr_timed_trip			18	//3字节，定时试跳设定时间
#define Addr_over_vol			21	//2字节，过压整定值
#define Addr_under_vol			23	//2字节，欠压整定值
#define Addr_break_phase		25	//2字节，缺相整定值
#define Addr_rated_current		27	//3字节，额定电流整定值	
#define Addr_over_current		30	//1字节，电流超限报警整定值
#define Addr_remote_trip		31	//2字节，远程跳闸时间
#define Addr_remote_close		33	//2字节，远程合闸时间
#define Addr_analog_trip		35	//2字节，远程模拟试跳时间

#define Addr_leak_valve			188
#define Addr_leak_time			208
#define Addr_break_time			218


#define Addr_energy_active_he 12044  //合相有功电能存储，留20字节
#define Addr_energy_active_A  12048  //A相有功电能存储，留4字节,32位
#define Addr_energy_active_C  12052  //B相有功电能存储，留4字节,32位
#define Addr_energy_reactive_he  12056 //合相无功功电能存储，留4字节,32位
#define Addr_Ugain_A 12060   //A相电压增益
#define Addr_Ugain_B 12062   //B相电压增益
#define Addr_Ugain_C 12064

#define Addr_Pgain_A 12066   //A相功率增益
#define Addr_Pgain_B 12068   //B相功率增益
#define Addr_Pgain_C 12070

#define Addr_Uoffset_A 12072
#define Addr_Uoffset_B 12074
#define Addr_Uoffset_C 12076

#define Addr_Ioffset_A 12078
#define Addr_Ioffset_B 12080
#define Addr_Ioffset_C 12082
#define Addr_Ioffset_ABC 12090

#define Addr_Igain_A 12084   //A相电压增益
#define Addr_Igain_B 12086   //B相电压增益
#define Addr_Igain_C 12088

#define Addr_max_leak			346	//漏电最大值
#define Addr_max_Avol			634	//A相电压最大值
#define Addr_max_Bvol			922	//B相电压最大值
#define Addr_max_Cvol			1210//C相电压最大值 
#define Addr_max_Acur			1498//A相电流最大值 
#define Addr_max_Bcur			1786//B相电流最大值
#define Addr_max_Ccur			2074//C相电流最大值
#define Addr_min_leak			2362//漏电最小值  
#define Addr_min_Avol			2650//A相电压最小值 
#define Addr_min_Bvol			2938//B相电压最小值
#define Addr_min_Cvol			3226//C相电压最小值
#define Addr_min_Acur			3514//A相电流最小值
#define Addr_min_Bcur			3802//B相电流最小值
#define Addr_min_Ccur			4090//C相电流最小值


#define Addr_event_leak			4378//漏电事件
#define Addr_event_self			4528//自检事件
#define Addr_event_trip			4788//跳闸事件
#define Addr_event_alarm		5038//告警事件
#define Addr_record_leak1		5158//漏电记录1
#define Addr_record_leak2		7462//漏电记录2

#define Addr_point_leak_max		9766
#define Addr_point_Avol_max		9767
#define Addr_point_Bvol_max		9768
#define Addr_point_Cvol_max		9769
#define Addr_point_Acur_max		9770
#define Addr_point_Bcur_max		9771
#define Addr_point_Ccur_max		9772
#define Addr_point_leak_min		9773
#define Addr_point_Avol_min		9774
#define Addr_point_Bvol_min		9775
#define Addr_point_Cvol_min		9776
#define Addr_point_Acur_min		9777
#define Addr_point_Bcur_min		9778
#define Addr_point_Ccur_min		9779
#define Addr_point_leakrecord	9780
#define Addr_point_event_trip_24C256	9782
#define Addr_point_event_self	9783
#define Addr_F_GJ_FUNC          9800
#define Addr_point_event_leak	9801

//宏定义    普通校准      地址        长度       含义       段
#define   Addr_Vol_ad          9802         //18   3*2*3  3相*两点*一个点长度3（实际占用2字节）
#define   Addr_Vol_slope       9820         //18
#define		Addr_Vol_Disp        9838         //18	

#define   Addr_Leak_ad           9856         //6               三点校准*一个点长度2
#define   Addr_Leak_slope        9862        //6
#define   Addr_Leak_Disp         9868        //6

#define		Addr_Cur_250         9874        //30 			5*2*3  ad值 五点*2字节*三相
#define	  Addr_Cur_slope_250       9904        //30 	5*2*3  斜率
#define   Addr_Cur_Disp_250	   9934         //30 			5*2*3  实际接收到的校准点的值（例如10、50、300等）
//最值记录  段
#define Addr_min_Avol_TD 10800//4
#define Addr_min_Bvol_TD 10804//4
#define Addr_min_Cvol_TD 10808//4
#define Addr_max_Avol_TD 10812//4
#define Addr_max_Bvol_TD 10816//4
#define Addr_max_Cvol_TD 10820//4


/****四位密码1*4=4字节（2022.2.21温州杨济恺加）*****/
#define Addr_mima_set 10824//4
#define Addr_L_specialwave 10828  //1

/*****漏电延时档位***********/
#define Addr_TH_LCur 12000  //1

/*****温度上下限档位***********/
#define Addr_temperature_UP 13000  //1

#define Addr_temperature_DOWN 13001  //1

#define Addr_Delta_Cur 13002









#define Lenth_dev_id	6
#define Lenth_dev_addr	6
#define Lenth_dev_code	32
#define Lenth_rated_V	6
#define Lenth_rated_I	6
#define Lenth_frame_current	6
#define Lenth_equi_type	10
#define Lenth_production_date	10
#define Lenth_protocol_ver	16
#define Lenth_factory_code	24
#define Lenth_soft_ver	32
#define Lenth_hard_ver	32
#define Lenth_leak_valve	20
#define Lenth_leak_time	10
#define Lenth_break_time	10
#define Lenth_auto_closing	24
#define Lenth_leak_type	24
#define Lenth_install_phase	10
#define Lenth_0_password	4
#define Lenth_1_password	4
#define Lenth_2_password	4
#define Lenth_alarm_value	2
#define Lenth_record_value	1
#define Lenth_record_time	1
#define Lenth_timed_trip	3
#define Lenth_over_vol	2
#define Lenth_under_vol	2
#define Lenth_break_phase	2
#define Lenth_rated_current	3
#define Lenth_over_current	1
#define Lenth_remote_trip	2
#define Lenth_remote_close	2
#define Lenth_analog_trip	2
#define Lenth_clear_num		3
#define Lenth_trip_num		2
#define Lenth_close_num		2
#define Lenth_leak_num		2
#define Lenth_current_num	2
#define Lenth_vol_num		2
#define Lenth_hand_num		2
#define Lenth_zero_num		2
#define Lenth_test_num		2
#define Lenth_2D_num	2
#define Lenth_3D_num	2
#define Lenth_LD_up_num	2
#define Lenth_AJ_sy_num	2
#define Lenth_leakquit_num	2
#define Lenth_protect_time	4
#define Lenth_max_leak		9
#define Lenth_max_Avol		8
#define Lenth_max_Bvol		8
#define Lenth_max_Cvol		8
#define Lenth_max_Acur		9
#define Lenth_max_Bcur		9
#define Lenth_max_Ccur		9
#define Lenth_min_leak		9
#define Lenth_min_Avol		8
#define Lenth_min_Bvol		8
#define Lenth_min_Cvol		8
#define Lenth_min_Acur		9
#define Lenth_min_Bcur		9
#define Lenth_min_Ccur		9
#define Lenth_event_leak	15
#define Lenth_event_self	26
#define Lenth_event_trip	25
#define Lenth_event_alarm	12
#define Lenth_record_leak1	9
#define Lenth_record_leak2	9
#define Lenth_F_GJ_FUNC     1  




#define ERR_BAD_DATA (0x01+0x33)
#define ERR_NO_REQUEST (0x02+0x33)
#define ERR_BAD_PASSWORD (0x04+0x33)
#define ERR_BAD_BAUD (0x08+0x33)
#define ERR_NO_REMOTE (0x10+0x33)



//不隔离
#define TX_E   E485 = 1
#define RX_E   E485 = 0
//隔离
//#define TX_E   E485 = 0
//#define RX_E   E485 = 1

#define  T_H_V T_HV_Array[D_GY_yanshi]
#define  T_L_V T_LV_Array[D_QY_yanshi]
#define  T_S_V T_SV_Array[D_SY_yanshi]
int num=1;
//const unsigned int T_HV_Array[]={9,19,37,55,73,91,109,127,145,163,181}; //过压比较门限数组  140 150 160 170 180 
//const unsigned int T_LV_Array[]={9,19,37,55,73,91,109,127,145,163,181}; //140 150 160 170 180
const unsigned int T_HV_Array[]={5,20,40,60,80,100,120,140,160,180,200}; //过压比较门限数组  140 150 160 170 180 
const unsigned int T_LV_Array[]={5,20,40,60,80,100,120,140,160,180,200}; //140 150 160 170 180

const unsigned int T_SV_Array[]={1,20,40,60,80,100,120,140,160,180,200};
volatile unsigned char Vol_g_T=0,Vol_q_T=0,Vol_s_T=0,F_TIME=0,V_point=0,Vol_ch=0;//过欠压保护时间档位指针
unsigned char F_L_err=0,F_AVcal_err=0,F_BVcal_err=0,F_CVcal_err=0;
volatile unsigned int Leak_Cur_disp_cal = 0;
unsigned char F_AIcal_err=0,F_BIcal_err=0,F_CIcal_err=0,F_aIcal_err=0,F_bIcal_err=0,F_cIcal_err=0;
unsigned char F_cal_finish=0;
union adres
{
 int y1;
 unsigned  char adre[2];
}adresult;
signed char F_cal_L=0,F_cal_V_A=0,F_cal_V_B=0,F_cal_V_C=0,F_cal_I_A=0,F_cal_I_B=0,F_cal_I_C=0;
volatile unsigned char F_Dataval1;
 volatile signed int I_A_factor=0,V_A_factor=0,I_B_factor=0,V_B_factor=0,I_C_factor=0,V_C_factor=0,V1_slope[3]={0};
volatile unsigned short int I1_A_slope[2]={0},I1_B_slope[2]={0},I1_C_slope[2]={0};	
volatile unsigned short int I1_400A_slope[2]={0},I1_400B_slope[2]={0},I1_400C_slope[2]={0};
volatile unsigned short int I1_630A_slope[2]={0},I1_630B_slope[2]={0},I1_630C_slope[2]={0};
volatile unsigned short int I1_800A_slope[2]={0},I1_800B_slope[2]={0},I1_800C_slope[2]={0};
volatile unsigned char F_hezha_state,F_fenzha_state,F_hezha_delay;
	volatile unsigned long Delta_Cur,DLD_Cur,DLS_Cur;
volatile unsigned int N_fenzha_time=0,N_hezha_time=0,N_display_time=0;
/*******************************************************************************
 ******************************标志位区*****************************************
********************************************************************************/
volatile unsigned char	F_nokey,F_clear_al,F_QY_hezha,F_SY_hezha,F_syTrip,F_GY_hezha,F_QX_hezha,F_qyTrip,F_gyTrip,F_qyTrip,F_qxTrip,F_lzTrip,F_QL_hezha;
volatile unsigned char F_anti_islanding_hezha;
volatile unsigned char F_anti_islanding_trip;
volatile unsigned char  F_dianya_chonghe=0,F_tim_gz,F_analog_trip,F_dataalarm_all,F_lightalarm,F_voicealarm,F_timealarm,F_classreturn,F_chonghezha;
volatile unsigned char F_anti_islanding_chonghe;
volatile unsigned	char  F_trip_ld,F_trip_qy,F_trip_gy ,F_dataalarm_xq,F_trip_xq=1 ,F_trip_gl ,F_data_clear,	F_trip_xl,F_trip_sy,F_Corr,F_auto_ld;
volatile unsigned	char F_ld;
volatile unsigned	char  F_trip_QX=0,F_trip_QL=0,F_VLH=0;
unsigned	char F_DD_L[1];
volatile unsigned	char  F_shangdian_hezha;
volatile unsigned char	F_50hz_nomal,F_fz,F_hz,F_FR,F_I_Trip,F_IQ_Trip,F_ITrip,F_VTrip,F_L_Lock,F_STrip,F_TTrip,F_UP_hezha,F_V_Nomal,F_VL,F_VH,F_powerup_re,F_disp_tr;
volatile unsigned char F_anti_islanding_normal;
unsigned char shangdian=0,duandian=0,jiaozhun;	
volatile  unsigned char	F_disp_h,F_yc_hezha,F_yc_fenzha,F_an_fenzha;
volatile  unsigned char 	F_MODE,F_TB_start;
volatile  unsigned char	F_hezha_js,F_fenzha_js,F_an_js;
volatile  unsigned char 	F_day_updata,F_time_trip,F_timer_triped;
volatile  unsigned char  F_int0,F_key,F_TB_gz=0;
volatile unsigned char 	F_L_Delay,F_debug,F_leak_record,F_Uart,F_Frequncy,F_Record,F_Sync,F_Buttom,F_Vol,F_Disp,F_guocheng,F_Delay,F_Leak_Delay,F_Vol_Re,LEDA_FLAG;

volatile unsigned char F_lcd_transmit_D,F_lcd_realtime;
volatile unsigned char F_lcd_firsttime=0;

volatile unsigned char F_lcd_cnt=0;

volatile unsigned char F_bill;
volatile unsigned char F_anti_islanding=0;
volatile unsigned char F_anti_islanding_switch;
volatile unsigned long int  A_C_Sum_3=0,B_C_Sum_3=0,C_C_Sum_3=0,A_C_Sum_MAX;
volatile  unsigned char 	F_gl,F_tb,F_zd,F_hb,F_hb_old,F_qa,F_ga,F_la,F_la1,F_db,F_ni,F_la2,F_yc,F_cd,F_QUIT,F_tingdian_V,F_ks;
volatile  unsigned char F_dataalarm_gl,F_dataalarm_gy,F_dataalarm_qy,F_dataalarm_xl,F_al;
volatile unsigned char  F_N_shangdian=0;
unsigned char F_shangdian_2=0;
unsigned char F_initial_lcd=0;
unsigned char F_initial_lcd_hezha=0,F_hezha_set=0;
volatile signed int       N_shangdian_hezha=0;
volatile unsigned char F_gz,F_tingdian_fenzha=0,kaiguan_state_old,kaiguan_state_new;
volatile unsigned char  F_disp_jg;
volatile unsigned char  F_disp_jg;
volatile unsigned char F_Cur=0,iii=0,F_ip,F_ip_3,F_cd_set,F_ia,N_anolog_trip,F_I_STA = 0,F_I_Lock,F_jianyan=0;

volatile unsigned char F_DataClear=0;

 unsigned char BCD_temp[2] = {0},N_DLS=0;
volatile unsigned short int L_factor=0,I_factor=0,V_factor=0,L_factor_tmp=0,I_factor_tmp=0,V_factor_tmp=0,L1_slope=0;
unsigned char self_addr_code[6],EEPROM_array_tmp[150],F_gz_disp=0,F_ch=0;
unsigned char self_addr_code_temp[6]={0x00,0x00,0x00,0x00,0x00,0x00};
volatile signed int      N_qx_hezha=0,N_qy_hezha=0,N_sy_hezha=0,N_gy_hezha=0,N_aqy_trip=0,N_bqy_trip=0,N_cqy_trip=0,N_agy_trip=0,N_bgy_trip=0,N_cgy_trip=0,N_asy_trip=0,N_bsy_trip=0,N_csy_trip=0,N_lz_hezha=0;
volatile signed int N_anti_islanding_hezha;
volatile signed int N_anti_islanding_over_A,N_anti_islanding_over_B,N_anti_islanding_over_C;
volatile signed int N_anti_islanding_under_A,N_anti_islanding_under_B,N_anti_islanding_under_C;
volatile signed int  N_tem_trip=0;
volatile signed int      N_a_bqx_trip=0,N_a_cqx_trip=0,N_b_aqx_trip=0,N_b_cqx_trip=0,N_c_aqx_trip=0,N_c_bqx_trip=0;	
volatile unsigned char   hezha_num=0,F_al1=0;
volatile unsigned int    ci_shu=0;
//定义转换结果变量
//漏电流、A相电压、B相电压、C相电压、A相电流、B相电流、C相电流、零相电流、
volatile unsigned int Leak_Cur_disp_temp=0,Leak_xianshi_disp=0;
volatile unsigned int  L_Cur=0,A_Vol=0,B_Vol=0,C_Vol=0,I_VAL=0,V_Array[3]={0},V_Array_record[3]={0},V_sample[3]={0},V_Array_disp[3]={0};
volatile unsigned int A_Cur=0,B_Cur=0,C_Cur=0,Z_Cur=0,Power_A_Value=0,Power_B_Value=0,Power_C_Value=0;
volatile unsigned long I2=0,I3=0,I3_1=0;
volatile unsigned int H_DLD_Cur = 0;	
volatile unsigned char pre_sta=0,F_sssj=0;
volatile unsigned int N_key=0,N_disp=0;

volatile unsigned char  F_gc = 1;
volatile unsigned char F_wait_DY_Normal=0;
volatile unsigned long T_64_xs=0;

volatile unsigned int T_Timer2=0,Value_Timer1=0,Num_leakquit=0;
volatile unsigned int H_D_V;
volatile signed int N_T_TH,N_I2[4]={0},N_Tingdian=0;
 signed int N_I22[4]={0};
volatile signed int N_TH_DL[]={1,6,16,26,36,56,76};//{6,16,26,36,46,66,86}

//volatile unsigned char pw1,pw2,pw3,pw4;
volatile unsigned char F_pw1,F_pw2,F_pw3,F_pw4;
 signed int V_temp[3],V_temp_tmp[3];

volatile signed long  I2_Array_Sum[4]={0},I_I_Array_xianshi[20]={0},CurA_cal_tmp[5]={0},CurB_cal_tmp[5]={0},CurC_cal_tmp[5]={0},Leak1_temp=0,Vol1_A_temp=0,Vol1_B_temp=0,Vol1_C_temp=0;
volatile signed long CurA400_cal_tmp[5]={0},CurB400_cal_tmp[5]={0},CurC400_cal_tmp[5]={0};
volatile signed long CurA630_cal_tmp[5]={0},CurB630_cal_tmp[5]={0},CurC630_cal_tmp[5]={0};
volatile signed long CurA800_cal_tmp[5]={0},CurB800_cal_tmp[5]={0},CurC800_cal_tmp[5]={0};
volatile unsigned  int I_Array[20]={0},I_Array_xianshi[20]={0},I_Array_action[3]={0};
volatile unsigned int U_Array_xianshi[3]={0};
//unsigned short int Cur_cal_tmp[2]={100,500};
unsigned long Cur_cal_tmp[2]={100,250};//500
volatile unsigned long I2_Array[4]={0};
volatile unsigned char F_I2_Array[4]={0},F_I_Array[4]={0};

volatile unsigned long Time_procetect=0,Sum_run_time=0,Leak_xianshi_sum=0;

//串口
volatile unsigned char UART_T_Buf[60]={0},UART_S_Buf[60]={0},R_point={0},T_point=0,F_Dataval=0,F_Dataval_wendu=0,F_Dataval_lcd=0,Uart_od=0,TTT[3]={0};
volatile unsigned char	tmp_uart_rx[100];
volatile unsigned char	tmp_uart_rx_1[100];
extern volatile unsigned char	Lcd_uart_rx[50];
volatile unsigned long T_yc_hezha=0,T_yc_fenzha=0,T_yc_fenzha_js=0,T_yc_hezha_js=0,T_an_fenzha=0,T_an_fenzha_js=0;


volatile unsigned int E2_addr=0;
volatile unsigned int gz_disp=0;
volatile unsigned int key_state=0;

extern volatile unsigned char tim_m3,tim_d3,tim_h3,tim_f3,tim_s3;
extern volatile unsigned int  tim_y3;
volatile unsigned char button_status=0,F_hezha_sta=0,T_AD=0,TT_AD=0;
volatile unsigned char TT_1=0;


signed char N_key_temp=0;
unsigned char disp_status=0,long_key_temp=0,F_cal=0;
//定义各种定时器

volatile unsigned char F_AD =1,T_64_3=0,T_64_4=0,T_64_25=0,T_64_2=0,T_64_1=0,T_64_6=0,T_V=0,T_L=0,T_64_4_Re=0,T_Wendu_3s;             //各种计数器
volatile unsigned int T_64_2min=0,T_1min;
volatile unsigned int T_64_hezha_delay=0,T_sssj_N = 0,T_I = 0,T_64_1min=0,T_64_15m=0,T_64_20m=0,T_64_2m=0,T_64_10s=0,T_64_6s=0,T_64_11s=0,T_64_31s=0,T_64_40s=0,T_64_500ms=0,T_64_200ms=0,T_64_100ms=0,T_T=0,F_T=0;
volatile unsigned int T_30s;
//定义各种标志位
volatile unsigned char F_Trip=0;
volatile  unsigned char  F_GTrip=0,F_QTrip=0,F_fenzha_C=0,F_Rise=0,F_50Hz=0,F_Powerup=0,F_Firstrise=0,F_Updata=0,F_Compare=0,F_Vsam_begin=0,F_display=0;        //各种标志位
volatile unsigned char F_Alarm=0,F_A_Trip=0,F_hezha=0,F_Vtest=0,F_UTrip=0,F_HTrip=0,F_L_hezha,F_I_hezha=0,F_V_hezha=0,F_ZW=0;
//unsigned char F_fenzha_G_Array[3],F_fenzha_Q_Array[3];
volatile unsigned char F_asy_sta=0,F_bsy_sta=0,F_csy_sta=0;
//过流保护电流档位
volatile unsigned char D_M_Cur=0,D_I2=0,D_S=0;        //过流保护规格,档位长度,档位指针
volatile unsigned char D_Cur=0,Type_Cur=0,D2_Cur,D3_Cur=0;        //过流保护规格,档位长度,档位指针

volatile unsigned long H_Cur=0,H5_Cur=0;
//过欠压保护时间档位
volatile unsigned char Vol_g=0,Vol_q=0;//过欠压保护时间档位指针
volatile unsigned char Vol_up=0,Vol_down=0;
/*
signed char NAG_Vol_Array[3];//过欠压保护时间计数器
 signed char NAQ_Vol_Array[3];//过欠压保护时间计数器
 signed char NAN_Vol_Array[3];//过欠压保护时间计数器
 
 signed char NBG_Vol;//过欠压保护时间计数器
 signed char NBQ_Vol;//过欠压保护时间计数器
 signed char NBN_Vol;//过欠压保护时间计数器
 
 signed char NCG_Vol;//过欠压保护时间计数器
 signed char NCQ_Vol;//过欠压保护时间计数器
 signed char NCN_Vol;//过欠压保护时间计数器
*/ 
 volatile signed char TH_V=0;//时间比较门限
 
volatile  signed int N_K=0,N_A3D=0,N_B3D=0,N_C3D=0,N_A2D=0,N_B2D=0,N_C2D=0,N_BASE=0;
unsigned char N_GY_yanshi=0,N_QY_yanshi=0,D_GY_yanshi=0,D_QY_yanshi=0,D_SY_yanshi=0;

//漏电保护电流档位
volatile unsigned char D_LCur=0,D_A_LCur=0,LC_N=0;//漏电电流档位指针 
volatile unsigned char TH_LCur=0,TH_DL=0,TH_Long_Cur=0;//漏电时间档位指针 
volatile signed int N_T1=0,N_T2=0,N_T3=0,N_T=0;//漏电时间计数器
volatile unsigned int  Id1=0,Id2=0,Id3=0,Id4=0,Id1_A=0,Id1_H=0,Id1_L=0,Id1_delta=0,Id2_delta=0;
volatile signed int N_TH1=0,N_TH2=0,N_TH3=0,N_TH=0,N_A_T=0,N_A_L=0,N_A_H=0,N_delta=0,N_TB_T=0;
volatile unsigned int  Id45=0;

volatile unsigned char F_anolog_trip=0;
volatile unsigned char F_hezha_undo=0;
extern unsigned char dispbit[8];
volatile unsigned char baud=0x01,baud_uart=0x08;
volatile unsigned int IA_uart_temp=0,IB_uart_temp=0,IC_uart_temp=0;
volatile unsigned int VA_uart_temp=0,VB_uart_temp=0,VC_uart_temp=0;
volatile unsigned int IA_action_temp=0,IB_action_temp=0,IC_action_temp=0;
volatile unsigned char T_A=0,F_FI=0,GZ_ph=0,GZ_ph_disp=0;
 
                                    



volatile int N_Trip=0;


//unsigned long T_yc_hezha=0,T_yc_fenzha=0,T_yc_fenzha_js=0,T_yc_hezha_js=0,T_an_fenzha=0,T_an_fenzha_js=0;

//新修改增加变量
volatile signed int AD_tmp=0 ,N_A_phase,I_A_Array[3];
volatile unsigned long int Leak_Cur_Sum = 0, TEMP1[2],TEMP2[2];
volatile unsigned long int A_C_Sum=0,B_C_Sum=0,C_C_Sum=0,A_C_Sum_disp=0,B_C_Sum_disp=0,C_C_Sum_disp=0;
volatile unsigned int  Cur_A_temp[7]={0},Cur_B_temp[7]={0},Cur_C_temp[7]={0},Leak_temp[3]={0};
unsigned int Vol_A_temp[3],Vol_B_temp[3],Vol_C_temp[3];
unsigned short int V_A_slope[3],V_B_slope[3],V_C_slope[3],L_slope[3],I_A_slope[5],I_B_slope[5],I_C_slope[5],Vol_C_disp[3],Vol_B_disp[3],Vol_A_disp[3],Cur_A_disp[5],Cur_B_disp[5],Cur_C_disp[5],Leak_disp[3];
signed int I_C_vaule,I_A_vaule,I_B_vaule,AD_A_value,AD_B_value,AD_C_value;
volatile unsigned int Leak_Cur = 0,Leak_Cur1 = 0,Lea_Cur_old = 0;
volatile int Delta_Leak_Cur;
volatile unsigned int T_updata=0,Leak_Cur_disp = 0,Leak_Cur_disp_record = 0;
volatile unsigned char T =0 ,T_PH =0,TT=0 ;
unsigned char F_qingling=0;
volatile unsigned char F_gz_clear,F_time_compare,T_50hz_tmp,F_sys_pulse,F_Leak_Alarm,F_qxATrip,F_qxBTrip,F_qxCTrip,F_qxallTrip=0;
volatile unsigned char N_Leak_TH=0,gz_reason=0x00;
volatile unsigned  long Num_clearall = 0,Vol_A_Sum = 0;
volatile  unsigned int Num_tripall,Num_triplock,Num_tripleak,Num_tripcur,Num_tripvol,Vol_A_aver,Num_leakover;
volatile  unsigned int Num_triphand,Num_tripzero,Num_triptest,Num_tripkey,Num_leakprotect;
volatile  unsigned int Num_quitleak,Num_tripdelay,Num_tripinstant;
 
volatile unsigned char point_event_trip=0,point_event_trip_24C256=0,max_phase=0,F_run_time=0,point_event_leak=0;
volatile unsigned char password_0class[4],password_1class[4],password_2class[4];
unsigned char ctrlword[5],stateword[5];
volatile unsigned int  Leak_Alarm_Value=0,T_run_time=0;
volatile unsigned char Leak_record_value=0,Leak_record_time=0,Timer_trip[3];
//unsigned char overvoltage_setting[2],undervoltage_setting[2],phasevoltage_setting[2];
volatile unsigned char cur_setting[3],overcur_setting;
unsigned char remote_trip_time[2]={0xff,0xff},remote_close_time[2]={0xff,0xff},analog_trip_time[2]={0xff,0xff};
volatile unsigned int  point_Leak_record=0;



volatile unsigned char point_trip=0,F_set_state=0,N_fenzha=0,N_hezha=0;
volatile unsigned int T_set_state=0,T_time_trip=0;
volatile unsigned char F_leak_maxmin=0,F_Conter_Updata=0,F_TB_trip=0,F_C_IP=0,F_Special_wave=0;

volatile unsigned char F_jiance=0;										
volatile unsigned char point_leak_max=0,F_GJ_FUNC=0 ;

 unsigned char dev_id_code[Lenth_dev_id+1]={0x08,0x08,0x08,0x08,0x08,0x08};
 volatile unsigned char dev_addr_code[Lenth_dev_addr+1]={0x06,0x05,0x04,0x03,0x02,0x01};
 
 volatile unsigned int T_delay=0;
 
      unsigned char dev_code_code[32]= {"3330025000102030405069          "};
      unsigned char dev_code_code_head[12]= {"333002500"};
 
   volatile   unsigned char rated_V_code[Lenth_rated_V]="400   ";
   volatile   unsigned char rated_I_code[Lenth_rated_I]="100   ";
   volatile   unsigned char frame_current_code[Lenth_frame_current]="250   ";
    unsigned char equi_type_code[Lenth_equi_type+1]="123456    ";

 
      unsigned char production_date_code[Lenth_production_date]="20170914  ";
      unsigned char protocol_ver_code[Lenth_protocol_ver] = "DLT-2007        ";
      unsigned char factory_code_code[Lenth_factory_code] = "A065468               ";


   
  
   unsigned char auto_closing_code[Lenth_auto_closing] = "20-60                   ";  
   unsigned char leak_valve_code[Lenth_leak_valve] = {0x50,0x00,0x00,0x01,0x00,0x03,0x00,0x05,0x00,0x08,0x00,0x10,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
   unsigned char leak_time_code[Lenth_leak_time] ={0x60,0x00,0x00,0x01,0x50,0x01,0x00,0x03,0xFF,0xFF};
   unsigned char break_time_code[Lenth_break_time] = {0x00,0x02,0x00,0x03,0x00,0x05,0x00,0x10,0xFF,0xFF};
 
   unsigned char leak_type_code[Lenth_leak_type] = "AC                      ";
   unsigned char install_phase_type_code[Lenth_install_phase] = "IS  ";	 
   unsigned char alarm_value_code[Lenth_alarm_value]={0x00,0x05};
   unsigned char record_value_code[Lenth_record_value+1]={0x10,0xFF};
   unsigned char record_time_code[Lenth_record_time+1] ={0x10,0xFF};
      unsigned char timed_trip_code[Lenth_timed_trip] = {0x00,0x00,0x00};
      unsigned char over_vol_code[Lenth_over_vol] = {0x00,0x28};
      unsigned char under_vol_code[Lenth_under_vol] = {0x00,0x16};
      unsigned char break_phase_code[Lenth_break_phase] = {0x00,0x12};
      unsigned char rated_current_code[Lenth_rated_current] = {0x00,0x06,0x00};
      unsigned char over_current_code[Lenth_over_current+1] = {0x06,0x00};
 




//过流保护门限值数组
                                  //100// 20 30 40 50 60 70 80 90 100
								  //250   60 70 80 90 100 110 120 130 140 150 160 170 180 190 200 210 220 230 240 250
								  //400   200 230 260 230 240 250 260 270 

	
volatile unsigned int DLS_Cur_IV_AD_value[5]={0},DLS_Cur_IV_slope[5]={0},DLS_Cur_IV_Value[5]={0};
volatile unsigned int DLS_Cur_I_AD_value[5]={0},DLS_Cur_I_slope[5]={0},DLS_Cur_I_Value[5]={0};
volatile unsigned int DLS_Cur_II_AD_value[5]={0},DLS_Cur_II_slope[5]={0},DLS_Cur_II_Value[5]={0};
volatile unsigned int DLS_Cur_III_AD_value[5]={0},DLS_Cur_III_slope[5]={0},DLS_Cur_III_Value[5]={0};


								  
const unsigned long D_C1_Array[]={838,2991,6818,10820,15742,22219,29809,39358,49276};//20~100各档位1.15倍电流值
const unsigned long D_C15_Array[]={45000000,100663894,180000000,280272589,405000000,549881285,720000000,909489981,1125000000};//20~100各档位1.5倍电流值
const unsigned long D_C19_Array[]={800,1200,1600,2000,2400,2800,3200,3600,3800};
const unsigned int  D_C1H_Array[]={800,1200,1600,2000,2400,2800,3200,3600,3800}; 
const unsigned long  D_C15_15Array[]={446968,1594738,3635218,5768893,8393068,11846188,15892813,20984203,26271793};
const unsigned long  D_C1_2d_2Array[]={20,30,40,50,60,70,80,90,100};

const unsigned long  D_C1_3d_6Array[]={800,1200,1600,2000,2400,2800,3200,3600,3800};
const unsigned long  D_C1_3d_8Array[]={800,1200,1600,2000,2400,2800,3200,3600,3800};
const unsigned long  D_C1_3d_10Array[]={800,1200,1600,2000,2400,2800,3200,3600,3800};
const unsigned long  D_C1_3d_12Array[]={800,1200,1600,2000,2400,2800,3200,3600,3800};
	
const unsigned long D_C2_Array[]={1177,1660,2126,2761,3353,4140,5009,5797,6818,7922,8905,9946,11271,12438,13915,15474,16837,18548,20342,22219};//60~250各档位1.15倍电流值
const unsigned long D_C25_15Array[]={627840,885352,1133668,1472113,1787872,2207250,2670772,3090763,3635218,4223818,4748040,5302918,6009238,6631560,7418812,8250210,8976763,9889093,10845568,11846188};//60~250各档位1.5倍电流值//1.5平方*120 ,,
                                   //  60  70  80  90 100 110 120 130 140 150 160 170 180 190 200 210 220 230 240 250
const unsigned long D_C2H_Array[]={300,490,720,980,1160,1380,1590,1840,2060,2260,2380,2460,2600,2700,2820,2940,3140,3220,3360,3480};   //已经改过了  用来短路短延时的
                                     //  60  70  80  90 100 110 120 130 140 150 160 170 180 190 200 210 220 230 240 250
const unsigned long  D_C2_2d_2Array[]={60,70,80,90,100,110,120,130,140,150,160,170,180,190,200,210,220,230,240,250};
const unsigned long  D_C2_3d_6Array[]={300,339,370,449,500,550,600,650,700,750,800,850,890,950,970,995,1020,1039,1052,1071};
const unsigned long  D_C2_3d_8Array[]={400,448,488,592,664,728,800,864,928,1000,1064,1128,1184,1264,1288,1320,1360,1384,1400,1424,};
	const unsigned long  D_C2_3d_10Array[]={500,560,610,740,830,910,1000,1080,1160,1250,1330,1410,1480,1580,1610,1650,1700,1730,1750,1780};
const unsigned long  D_C2_3d_12Array[]={600,672,732,888,996,1092,1200,1296,1392,1500,1596,1692,1776,1896,1932,1980,2040,2076,2100,2136};
	


const unsigned long D_C3_Array[]={14169,17116,20342,23846,27628,31689,36028,41515,46461,51199,56676};//200~400各档位1.15倍电流值
const unsigned long D_C35_15Array[]={7554313,9125752,10845568,12713760,14730328,16895272,19208593,22133812,24770863,27296938,30217252};//60~250各档位1.5倍电流值//1.5平方*120 ,,
                                     //  60  70  80  90 100 110 120 130 140 150 160 170 180 190 200 210 220 230 240 250
const unsigned long D_C3H_Array[]={300,490,720,980,1160,1380,1590,1840,2060,2260,2380,2460,2600,2700,2820,2940,3140,3220,3360,3480};   //已经改过了  用来短路短延时的
                                     //  60  70  80  90 100 110 120 130 140 150 160 170 180 190 200 210 220 230 240 250
const unsigned long  D_C3_2d_2Array[]={200,220,240,260,280,300,320,340,360,380,400};

const unsigned long  D_C3_3d_6Array[]={0};
const unsigned long  D_C3_3d_8Array[]={0};
const unsigned long  D_C3_3d_10Array[]={0};
const unsigned long  D_C3_3d_12Array[]={0};


const unsigned long D_C4_Array[]={5009,6642,8505,10598,13166,16012,19137,22219,25875,29073,33235,37260,42393,46924,52174};//200~400各档位1.15倍电流值
//const unsigned long D_C4_Array[]={20036,26568,34020,42392,52664,64048,76548,88876,103500,29073,116292,149040,169572,187696,208696};
const unsigned long D_C45_15Array[]={2670772,3541410,4534672,5650560,7019668,8537152,10203013,11846188,13795312,15500413,17719312,19865250,22602240,25017952,27816868};//60~250各档位1.5倍电流值//1.5平方*120 ,,
//const unsigned long D_C45_15Array[]={10683088,14165640,18138688,5650560,22602240,34148608,40812052,47384752,55181248,62001652,70877248,79461000,90408960,100071808,111267472};
//    
//const unsigned long D_C45_15Array[]={88181938,115176409,145770142,179963139,217755398,259146920,304137705,319934469,352727753,404917063,460705636,520093472,583080571,649666932,719852557};
//  60  70  80  90 100 110 120 130 140 150 160 170 180 190 200 210 220 230 240 250
const unsigned long D_C4H_Array[]={300,490,720,980,1160,1380,1590,1840,2060,2260,2380,2460,2600,2700,2820,2940,3140,3220,3360,3480};   //已经改过了  用来短路短延时的
                                     //  60  70  80  90 100 110 120 130 140 150 160 170 180 190 200 210 220 230 240 250
const unsigned long  D_C4_2d_2Array[]={210,240,270,300,330,360,390,420,450,480,510,540,570,600,630};

const unsigned long  D_C4_3d_6Array[]={0};
const unsigned long  D_C4_3d_8Array[]={0};
const unsigned long  D_C4_3d_10Array[]={0};
const unsigned long  D_C4_3d_12Array[]={0};

float Power_factor[3]={0},Active_Pow[3]={0},Total_power[3]={0};		
	
const unsigned char D_V_Array[]={1,14,27,39,52,64};//{4,9,14,19,24,29};//过欠压时间档位数组 500ms 1000ms  1500ms  2000ms   2500ms 3000ms

const unsigned int D_HV_Array[]={250,260,270,280,290,300}; //过压比较门限数组  140 150 160 170 180 
const unsigned int D_LV_Array[]={140,150,160,170,180,190}; //140 150 160 170 180
//欠压比较门限数组
const unsigned int D_UP_Array[]={240,250,260,270,280,290};
const unsigned int D_DOWN_Array[]={140,150,160,170,180,190,200};  

const unsigned char D_I2_Array[]={4,11,17,23,30};
//漏电动作值                         30 50 100 300 500 800 1000 
//const unsigned long D_LCur1_Array[]={28,42,80,240,400,640,800};//0.8倍数组                               0  1   2  3   4   5    6
//const unsigned long D_LCur1_Array[]={24,40,80,160,240,400,640,800};//0.8倍数组 
const unsigned long D_LCur1_Array[]={30,50,100,200,290,480,750,950};//1倍数组    0  1   2  3   4   5    6
//const unsigned long D_LCur2_Array[]={40,55,110,220,330,550,880,1100};//1.1倍数组
const unsigned long D_LCur2_Array[]={40,65,130,260,390,650,1040,1300};//1.3倍数组

const unsigned long D_LCur45_Array[]={90,150,300,600,900,1500,2400,3000};//4.5倍数组  2022.9.29

const unsigned int D_LCur3_Array[]={2300,2300,2300,2300,3200,3200,3200,3200};//10倍数组上限
const unsigned int D_LCur4_Array[]={1700,1800,1800,1800,1220,1220,1220,1220};//10倍数组下限
const unsigned int D_LCur_delta_Array[]={0,0,0,0,40,80,0,0};//突变数组





const unsigned long H_A_L[12] = {1,20,80,140,200,260,320,380,440,500,560,620};  
const unsigned long H_A_H[12] = {40,100,160,220,280,340,400,460,520,580,640,700};
const unsigned long D_ACur_Array[12] = {60,120,180,240,300,360,420,480,540,600,660,720};




//                                          200  300 500 1000
//																					
//const unsigned char TD_LCur1_Array[]={24,48,80,160};

//                                         200  300 500 1000  100
//																					
const unsigned char TD_LCur1_Array[]={40,72,120,144,24};



const unsigned char TD_LCur2_Array[]={7,11,19,39,3};
const unsigned char TD_LCur3_Array[]={3,5,9,19,1};

//      unsigned int Leak_time_class[]={200,300,500,1000};
volatile       unsigned int Leak_limit_time_class[]={200,300,500,1000};

 

//code const  unsigned int N_Trip_Array[]={1000,30000,90000};//20s,10m,30m//{1000,2000,3000};//
const  unsigned int N_Trip_Array[]={1000,3000,9000};//20s,10m,30m//{1000,2000,3000};//

//extern unsigned char ICON_DOT1,ICON_DOT2,ICON_DOT3,ICON_DOT4,ICON_T8,ICON_T9,ICON_T10,ICON_T11,ICON_T7,ICON_T3,ICON_T2,ICON_T1,ICON_T16,
 //                    ICON_T15,ICON_T14,ICON_T13,ICON_T4,ICON_T5,ICON_T6,ICON_T12,ICON_H4,ICON_H3,ICON_H2,ICON_H1,ICON_S8,ICON_S7,
 //                    ICON_S6,ICON_S5,ICON_S1,ICON_S2,ICON_S3,ICON_S4;
//extern unsigned int disbuff[5];

	
volatile unsigned long Num_leak_record,T_leak_record,T_day_updata;	
volatile unsigned int  V_MAX[3],V_MAX_tmp[3];
volatile unsigned int V_MIN_tmp[3]={60000,60000,60000},V_MIN[3]={60000,60000,60000};//old code 3000
unsigned char T_run_time_array[5]={0},tim_array[8],now_year,old_year,now_month,old_month,now_day,old_day;
volatile unsigned int I_Array_record[4],I_MIN[4]={60000,60000,60000,60000},I_MAX[4],I_MIN_tmp[4]={60000,60000,60000,60000},I_MAX_tmp[4];
volatile unsigned int Leak_MIN_tmp,Leak_MAX_tmp,Leak_MIN,Leak_MAX;
unsigned char Num_Sync,Leak_Over_array[20],FN_Vol,F_Cur_m;

volatile unsigned char point_leak_max,point_leak_min;
volatile unsigned char  point_Avol_max,point_Bvol_max,point_Cvol_max;
volatile unsigned char  point_Acur_max,point_Bcur_max,point_Ccur_max;
volatile unsigned char  point_Avol_min,point_Bvol_min,point_Cvol_min;
volatile unsigned char  point_Acur_min,point_Bcur_min,point_Ccur_min;
volatile unsigned char point_event_leak,point_event_alarm;
volatile unsigned  int point_Leak_record;
volatile unsigned char point_event_trip,point_event_trip_24C256,point_event_leak,F_hezha_sta,point_event_self;
unsigned char V_sample_tem=0,C_sample_tem=0;
extern unsigned int temp_AD,temp_AD1;
volatile signed int AD_result=0,AD_TEMP=0,C_AD_result[3],AD_result1=0,AD_JIAOZHUN=0,N_JIAOZHUN=0,F_JIAOZHUN=0;
                               //最基本的AD采样值
volatile unsigned char F_V_AD=0,F_C_AD=0,F_L_AD=0;
volatile unsigned char V_B_point=0,Leak_piont=0,I_point=0,Num_Cur_protect=0;
unsigned int  ADC_ConvertedValue[8],ADC_ConvertedValue1[3];
volatile unsigned long A_V_Sum1=0,B_V_Sum1=0,C_V_Sum1=0,A_V_Sum_disp=0,B_V_Sum_disp=0,C_V_Sum_disp=0;
volatile unsigned char T_64_1000ms=0,F_quick_protect=0,F_Bottom_queding=0;
unsigned char A_QL=0,B_QL=0,C_QL=0;
signed int N_QL=0;
signed int N_TD_A=0,N_TD_B=0,N_TD_C=0,N_QL_A=0,N_QL_B=0,N_QL_C=0;
unsigned char F_QLA_TRIP=0,F_QLB_TRIP=0,F_QLC_TRIP=0,F_QL_TRIP=0;
unsigned char F_qlchonghe=1,F_shiya_hezha=0;
 unsigned char N_delay_3D=0;
 signed int N_delay_DL=0;
 volatile signed int      N_a_bql_trip=0,N_a_cql_trip=0,N_b_aql_trip=0,N_b_cql_trip=0,N_c_aql_trip=0,N_c_bql_trip=0;
 unsigned char LouD_GaoJing=0;
 volatile signed int Leak_Cur_uart;
 unsigned short int AQL_Judge_tmp=0,BQL_Judge_tmp=0,CQL_Judge_tmp=0;
 volatile signed int AD_tmp_V=0,AD_tmp_VA_Max=0,AD_tmp_VB_Max=0,AD_tmp_VC_Max=0;
//volatile signed int AD_tmp_V=0;
  unsigned char R_SD[16]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
	unsigned char F_HT7038_Read=0,F_Wendu=0,Low_vol_begin=0;///ht7038zzz
unsigned char fuhao[12] = {0};

signed int HT7038_buf[100] = {0};
signed int ATT[2048] = {0};
signed int ATT_UA[256] = {0};  //谐波UA
signed int ATT_UB[256] = {0};
signed int ATT_UC[256] = {0};
signed int ATT_IA[256] = {0};
signed int ATT_IB[256] = {0};
signed int ATT_IC[256] = {0};

	int P1_Reactive,P2_Reactive=0;
	int P1_Apparent,P2_Apparent=0;
	int P1,P2=0;
	float Unbal_Vol,Unbal_Cur=0;


volatile unsigned int Samp_start_end_flag=0,Re_point_VA=0,T_LED_1s=0,Re_UA_j=0,Re_UB_j=0,Re_UC_j=0,Re_IA_j=0,Re_IB_j=0,Re_IC_j=0,Re_dot_U[3]={0},Re_dot_I[3]={0};		
volatile signed int Re_Zhou_bo_UA[64]={0},Re_Zhou_bo_UB[64]={0},Re_Zhou_bo_UC[64]={0};
volatile signed int Re_Zhou_bo_IA[64]={0},Re_Zhou_bo_IB[64]={0},Re_Zhou_bo_IC[64]={0};
volatile signed int Zhou_bo_UA[70]={0},Zhou_bo_UB[70]={0},Zhou_bo_UC[70]={0},Zhou_bo_IA[70]={0},Zhou_bo_IB[70]={0},Zhou_bo_IC[70]={0};
volatile signed int Zhou_bo_Ins_UA[64]={0},Zhou_bo_Ins_UB[64]={0},Zhou_bo_Ins_UC[64]={0},Zhou_bo_De_IA[64]={0},Zhou_bo_De_IB[64]={0},Zhou_bo_De_IC[64]={0};
volatile signed int N_T_TH,Phase_Differ[3]={0},Cross_Zero[3]={0},Phase_Differ1[3]={0},Phase_Differ_A[16]={0},Phase_Differ_B[16]={0},Phase_Differ_C[16]={0};
volatile signed int Zhou_bo_De_UA[64]={0},Zhou_bo_De_UB[64]={0},Zhou_bo_De_UC[64]={0},Zhou_bo_Ins_IA[64]={0},Zhou_bo_Ins_IB[64]={0},Zhou_bo_Ins_IC[64]={0};	
float Zhou_bojilu[600]={0},UI_AD_multi[3]={0},Phase_Differ_buffer[3]={0},Power_factor_test[3]={0},Power_factor_test_Ave[3]={0};
float Power_factor_testA[4]={0},Power_factor_testB[4]={0},Power_factor_testC[4]={0},Phase_Differ_A_Two=0,Phase_Differ_B_Two=0,Phase_Differ_C_Two=0;

volatile signed int AD_tmp_pow,AD_tmp_Power[3]={0} ;
volatile signed int AD_tmp_A_V_min=4095,AD_tmp_B_V_min,AD_tmp_C_V_min,Min_A_V_128,AD_tmp_A_V_max;
volatile unsigned long int I_A_Sum=0,I_B_Sum=0,I_C_Sum=0;
volatile unsigned long int U_A_Sum=0,U_B_Sum=0,U_C_Sum=0;
volatile unsigned char Fun_Power=0,Fun_Power_Flag=0,Fun_Power1=0,Fun_Power_Flag1=0,Fun_Power_test=0,YiChang_A_Flag=0,YiChang_B_Flag=0,YiChang_C_Flag=0;
volatile signed int Zhou_bojilu_V[640]={0},Zhou_bojilu_A[640]={0},Phase_Differ_average[3]={0},QPhase_Differ_average[3]={0},Phase_Differ_buffer1[3]={0};
volatile signed int Phase_Differ_A_one[16]={0},Phase_Differ_B_one[16]={0},Phase_Differ_C_one[16]={0};
volatile signed int Phase_Differ_A_Two_Av=0,Phase_Differ_B_Two_Av=0,Phase_Differ_C_Two_Av=0;
float Urms_A,Urms_B,Urms_C,Error_A,Error_B,Error_C,Irms_A,Irms_B,Irms_C;
volatile unsigned int Power_pool[161]={
1000,1000,1000,1000,999,999,998,998,997,996,
	995,994,993,992,991,989,988,986,984,983,
	981,979,977,975,972,970,968,965,962,960,
	957,954,951,948,945,942,938,935,931,928,
	924,920,916,912,908,904,900,895,891,887,
	882,877,872,868,863,858,853,847,842,837,
	831,826,820,815,809,803,797,791,785,779,
	773,767,760,754,748,741,734,728,721,714,
	707,700,693,686,679,672,664,657,649,642,
	634,627,619,611,604,596,588,580,572,564,
	556,547,539,531,522,514,506,497,489,480,
	471,463,454,445,436,428,419,410,401,392,
	383,374,364,355,346,337,328,318,309,300,
	290,281,271,262,252,243,233,224,214,205,
	195,185,176,166,156,147,137,127,118,108,
	98,88,78,69,59,49,39,29,20,10,0

};
volatile signed int AD_tmp_V_Power[3]={0},AD_tmp_I_Power[3]={0},AD_tmp_V_Power_Zero[3]={0},AD_tmp_I_Power_Zero[3]={0};
volatile signed int AD_tmp_I_PowerA[2]={0},AD_tmp_I_PowerB[2]={0},AD_tmp_I_PowerC[2]={0};

volatile unsigned char F_temTrip,F_tem_hezha;
volatile signed int  N_tem_hezha;

volatile unsigned char F_tem=0,Num_tem_protect;//200ms一次温度分闸处理



volatile unsigned char TH_TEM_UP,TH_TEM_DOWN;
volatile unsigned char TEM_UP,TEM_DOWN;
volatile unsigned char TEM_UP_arry[6]={50,60,70,80,90,100},TEM_DOWN_arry[5]={10,20,30,40,50};//

unsigned char TEM_UP_show[6][4]=
{
"50","60","70","80","90","100"
};


unsigned char TEM_DOWN_show[5][4]=
{
"10","20","30","40","50"
};
volatile unsigned int T_average_power=0,sum_active_power=0,sum_reactive_power=0,average_active_power=0,average_reactive_power=0;  //用于计算1分钟平均功率
volatile unsigned char T_60times=0;//用于计算1分钟平均功率
 signed int Accumulate_energy_dangqian_active_he=0 ; //计算电能合相有功
 signed int Accumulate_energy_shangci_active_he=0;
 signed int Accumulate_energy_dangqian_active_A=0; //计算电能A相有功
 signed int Accumulate_energy_shangci_active_A=0;
 signed int Accumulate_energy_dangqian_active_C=0; //计算电能C相有功
 signed int Accumulate_energy_shangci_active_C=0;
 signed int Accumulate_energy_dangqian_reactive_he=0 ; //计算电能合相无功
 signed int Accumulate_energy_shangci_reactive_he=0;

unsigned char jiaozhun,LD_hezha=0,DY_hezha=0,DL_hezha=0,wendu=0,F_TX=0;	

unsigned char LCD_Close,LCD_Open;

unsigned int undervol_slope=0;

unsigned char F_Harmonic_Content;

//电费
float Charge_sum=0;
float Energy_shangci=0;
int mins=0;//全局——初始值为零
int E[16]={0};
int E_Reactive[16]={0};
int E_Apparent[16]={0};
int is_First=1;//全局变量，初始1

unsigned char quadrant=0; //四象限指示


#endif




