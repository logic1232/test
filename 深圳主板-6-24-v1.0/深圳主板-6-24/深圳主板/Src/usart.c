/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    usart.c
  * @brief   This file provides code for the configuration
  *          of the USART instances.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "usart.h"

/* USER CODE BEGIN 0 */

//#include "uart.h"	 
#include "delay.h"
#include "rtc.h"
#include "tool.h"
#include "disp.h"
#include "24cxx.h"
#include "ht7038.h"

#define F_vison 0                     //������������
/*************************************
          �ڲ��洢��0ҳ
		  ������У׼ֵ����λ�������֣�
		        �ۼƼ�¼���¼���¼
				���ֲ�������
**************************************/
#define Addr_FACTORINIT_value	10000	//2�ֽڣ���ʼ����־
#define Addr_point_event_trip   10003   //2�ֽڣ��ڲ���¼��բ��¼
#define Addr_L_factor      		10005	//2�ֽڣ�©��У׼ֵ
#define Addr_V_factor      		10007	//2�ֽڣ���ѹУ׼ֵ
#define Addr_I_factor      		10009	//2�ֽڣ�����У׼ֵ
#define Addr_I_2d		      	10011	//1�ֽڣ����α�������
#define Addr_I_ia             	10012	//1�ֽڣ������غ�բ��������
#define Addr_L_TB             	10013	//1�ֽڣ�ͻ�䱣������
#define Addr_C_IP             	10014	//1�ֽڣ���·����ʱ����
#define Addr_L_JC				10015
#define Addr_F_gc				10146
#define Addr_crtl_word1      	10018	//1�ֽڣ�������1
#define Addr_crtl_word2      	10019	//1�ֽڣ�������2
#define Addr_crtl_word3      	10020	//1�ֽڣ�������3
#define Addr_crtl_word4      	10021	//1�ֽڣ�������4
#define Addr_crtl_word5      	10022	//1�ֽڣ�������5
#define Addr_ctrlword 			10018	//4�ֽڣ�������1-5
#define Addr_Type_Cur 			10023	//1�ֽڣ������Ǽܵȼ�
#define Addr_Vol_g 				10024	//1�ֽڣ���ѹ��λ
#define Addr_Vol_q				10025	//1�ֽڣ�Ƿѹ��λ
#define Addr_D_A_Lcur 			10026	//1�ֽڣ�©���Զ���λ
#define Addr_D_Cur				10027	//1�ֽڣ�������λ
#define Addr_baud				10028	//1�ֽڣ�������
#define Addr_dev_addr 			10029	//6�ֽڣ��豸ͨ�ŵ�ַ
#define Addr_clear_num			10035	//3�ֽڣ��������
#define Addr_trip_num			10038	//2�ֽڣ�����բ����
#define Addr_close_num			10040	//2�ֽڣ�������բ����
#define Addr_leak_num			10042	//2�ֽڣ�©����բ����
#define Addr_current_num		10044	//2�ֽڣ�������բ����
#define Addr_vol_num			10046	//2�ֽڣ���ѹ��բ����
#define Addr_hand_num			10048	//2�ֽڣ��ֶ���բ����
#define Addr_zero_num			10050	//2�ֽڣ�ȱ����բ����
#define Addr_test_num			10052	//2�ֽڣ�������բ����
#define Addr_leakquit_num		10054	//2�ֽڣ�©�����˴���
#define Addr_2D_num  10410             //2�ֽڣ���·��ʱ��բ����  
#define Addr_3D_num  10412             //2�ֽڣ���·˲ʱ��բ����
#define Addr_leakover_num      10414   //1�ֽڣ�ʣ��������޴���
//#define Addr_tripkey_num       10416   //1�ֽڣ��Լ����
#define Addr_leakprotect_num   10416   //1�ֽڣ�ʣ����������˳���������
//#define Addr_leakchange_num    10417   //1�ֽڣ�ʣ����������仯����

#define Addr_protect_time	 	10056	//4�ֽڣ�������ʱ��
#define Addr_dev_id           	10060	//6�ֽڣ��豸��
#define Addr_dev_code			10066	//32�ֽڣ��ʲ�����
#define Addr_equi_type			10098	//10�ֽڣ��豸����
#define Addr_factory_code		10108	//24�ֽڣ����Ҵ���
#define Addr_0_password			10132	//4�ֽڣ�����0
#define Addr_1_password			10136	//4�ֽڣ�����1
#define Addr_2_password			10140	//4�ֽڣ�����2
#define Addr_Vol_ch				10147	//��Ƿѹ�غ�բ

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
#define Addr_jiaozhun       10300
#define Addr_DIANYA_chonghe				10262
#define Addr_duandian				10263
#define Addr_tingdian    10283//����
#define Addr_SY_F    10288
//#define Addr_SY_T    10291	//2�ֽڣ�����У׼ֵ
#define Addr_data_clear 10316

#define Addr_AV_factor      		10265	//2�ֽڣ���ѹУ׼ֵ
#define Addr_BV_factor      		10267	//2�ֽڣ�����У׼ֵ
#define Addr_CV_factor      		10269	//2�ֽڣ���ѹУ׼ֵ
#define Addr_AI_factor      		10271	//2�ֽڣ�����У׼ֵ
#define Addr_BI_factor      		10273	//2�ֽڣ���ѹУ׼ֵ
#define Addr_CI_factor      		10275	//2�ֽڣ�����У׼ֵ

#define Addr_L_F    10276	//2�ֽڣ���ѹУ׼ֵ
#define Addr_AV_F    10277	//2�ֽڣ���ѹУ׼ֵ
#define Addr_BV_F    10278	//2�ֽڣ�����У׼ֵ
#define Addr_CV_F    10279	//2�ֽڣ���ѹУ׼ֵ
#define Addr_AI_F    10280	//2�ֽڣ�����У׼ֵ
#define Addr_BI_F    10281	//2�ֽڣ���ѹУ׼ֵ
#define Addr_CI_F    10282	//2�ֽڣ�����У׼ֵ

#define Addr_L1_slope 10304
#define Addr_V1_A_slope 10306
#define Addr_V1_B_slope 10308
#define Addr_V1_C_slope 10310

#define Addr_I1_A_slope 10312//250�Ǽ�
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

#define Addr400_I1_A_slope 10344   //400�Ǽ�
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

#define Addr630_I1_A_slope 10368   //630�Ǽ�
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

#define Addr800_I1_A_slope 10392   //800�Ǽ�
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

#define Addr100_I1_A_slope 10416   //100�Ǽ�
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

#define Addr_alarm_value		12	//2�ֽڣ�©�糬�޸澯����ֵ
#define Addr_record_value		14	//2�ֽڣ�©���¼��ֵ����ֵ
#define Addr_record_time		16	//2�ֽڣ�©���¼��ʱ����ֵ
#define Addr_timed_trip			18	//3�ֽڣ���ʱ�����趨ʱ��
#define Addr_over_vol			21	//2�ֽڣ���ѹ����ֵ
#define Addr_under_vol			23	//2�ֽڣ�Ƿѹ����ֵ
#define Addr_break_phase		25	//2�ֽڣ�ȱ������ֵ
#define Addr_rated_current		27	//3�ֽڣ����������ֵ	
#define Addr_over_current		30	//1�ֽڣ��������ޱ�������ֵ
#define Addr_remote_trip		31	//2�ֽڣ�Զ����բʱ��
#define Addr_remote_close		33	//2�ֽڣ�Զ�̺�բʱ��
#define Addr_analog_trip		35	//2�ֽڣ�Զ��ģ������ʱ��

#define Addr_leak_valve			188
#define Addr_leak_time			208
#define Addr_break_time			218
#define Addr_energy_active_he 12044  //�����й����ܴ洢����4�ֽ�,32λ

#define Addr_energy_active_A  12048  //A���й����ܴ洢����4�ֽ�,32λ
#define Addr_energy_active_C  12052  //B���й����ܴ洢����4�ֽ�,32λ
#define Addr_energy_reactive_he  12056 //�����޹������ܴ洢����4�ֽ�,32λ
#define Addr_Ugain_A 12060   //A���ѹ����
#define Addr_Ugain_B 12062   //B���ѹ����
#define Addr_Ugain_C 12064

#define Addr_Pgain_A 12066   //A�๦������
#define Addr_Pgain_B 12068   //B�๦������
#define Addr_Pgain_C 12070

#define Addr_Uoffset_A 12072
#define Addr_Uoffset_B 12074
#define Addr_Uoffset_C 12076

#define Addr_Ioffset_A 12078
#define Addr_Ioffset_B 12080
#define Addr_Ioffset_C 12082
#define Addr_Ioffset_ABC 12090
#define Addr_Igain_A 12084   //A���ѹ����
#define Addr_Igain_B 12086   //B���ѹ����
#define Addr_Igain_C 12088

#define Addr_max_leak			346	//©�����ֵ
#define Addr_max_Avol			634	//A���ѹ���ֵ
#define Addr_max_Bvol			922	//B���ѹ���ֵ
#define Addr_max_Cvol			1210//C���ѹ���ֵ 
#define Addr_max_Acur			1498//A��������ֵ 
#define Addr_max_Bcur			1786//B��������ֵ
#define Addr_max_Ccur			2074//C��������ֵ
#define Addr_min_leak			2362//©����Сֵ  
#define Addr_min_Avol			2650//A���ѹ��Сֵ 
#define Addr_min_Bvol			2938//B���ѹ��Сֵ
#define Addr_min_Cvol			3226//C���ѹ��Сֵ
#define Addr_min_Acur			3514//A�������Сֵ
#define Addr_min_Bcur			3802//B�������Сֵ
#define Addr_min_Ccur			4090//C�������Сֵ

#define Addr_event_leak			4378//©���¼�
#define Addr_event_self			4528//�Լ��¼�
#define Addr_event_trip			4788//��բ�¼�
#define Addr_event_alarm		5038//�澯�¼�
#define Addr_record_leak1		5158//©���¼1
#define Addr_record_leak2		7462//©���¼2

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
//�궨��    ��ͨУ׼      ��ַ        ����       ����       ��
#define   Addr_Vol_ad          9802         //18   3*2*3  3��*����*һ���㳤��3��ʵ��ռ��2�ֽڣ�
#define   Addr_Vol_slope       9820         //18
#define		Addr_Vol_Disp        9838         //18	

#define   Addr_Leak_ad           9856         //6               ����У׼*һ���㳤��2
#define   Addr_Leak_slope        9862        //6
#define   Addr_Leak_Disp         9868        //6

#define		Addr_Cur_250         9874        //30 			5*2*3  adֵ ���*2�ֽ�*����
#define	  Addr_Cur_slope_250       9904        //30 	5*2*3  б��
#define   Addr_Cur_Disp_250	   9934         //30 			5*2*3  ʵ�ʽ��յ���У׼���ֵ������10��50��300�ȣ�
//��ֵ��¼  ��
#define Addr_min_Avol_TD 10800//4
#define Addr_min_Bvol_TD 10804//4
#define Addr_min_Cvol_TD 10808//4
#define Addr_max_Avol_TD 10812//4
#define Addr_max_Bvol_TD 10816//4
#define Addr_max_Cvol_TD 10820//4


/****��λ����1*4=4�ֽڣ�2022.2.21����������ӣ�*****/
#define Addr_mima_set 10824//4
#define Addr_L_specialwave 10828  //1

/*****©����ʱ��λ***********/
#define Addr_TH_LCur 12000  //1


/***************************˲��У׼*********************************/
#define Addr_DLS_Cur_IV_AD_value   10900       //45			5*3 adֵ ���*3�ֽ�
#define Addr_DLS_Cur_IV_slope      10915         //45			5*3  б��
#define Addr_DLS_Cur_IV_Value      10930        //45			5*3 ˲������ֵ

#define Addr_DLS_Cur_I_AD_value   10945       //45			5*3  adֵ ���*3�ֽ�
#define Addr_DLS_Cur_I_slope      10960         //45			5*3  б��
#define Addr_DLS_Cur_I_Value      10975        //45			5*3 ˲������ֵ

#define Addr_DLS_Cur_II_AD_value   10990      //45			5*3  adֵ ���*3�ֽ�
#define Addr_DLS_Cur_II_slope      11005         //45			5*3  б��
#define Addr_DLS_Cur_II_Value      11020        //45			5*3 ˲������ֵ

#define Addr_DLS_Cur_III_AD_value   11035       //45			5*3  adֵ ���*3�ֽ�
#define Addr_DLS_Cur_III_slope      11050         //45			5*3  б��
#define Addr_DLS_Cur_III_Value      11065        //45			5*3 ˲������ֵ
/*************************************/


/*****�¶������޵�λ***********/
#define Addr_temperature_UP 13000  //1

#define Addr_temperature_DOWN 13001  //1



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

//#define set_bit(val, bitn)    (val |=(1<<(bitn)))
#define clr_bit(val, bitn)    (val&=~(1<<(bitn)))
//#define get_bit(val, bitn)    (val &(1<<(bitn)) )
//#define neg_bit(val, bitn)    (val^=(1<<(bitn)))
#define A_QX 0x10
#define B_QX 0x11
#define C_QX 0x12
#define A_sy 0x14
#define B_sy 0x15
#define C_sy 0x16
#define A_qy 0  
//A��Ƿѹ����		
#define B_qy 2  
//B��Ƿѹ����  
#define C_qy 4  
//C��Ƿѹ����
#define A_gy 1  
//A���ѹ����
#define B_gy 3  
//B���ѹ����
#define C_gy 5  
//C���ѹ����
#define L_hb 6 
//©�����
#define A_gl 7  
//A���������
#define B_gl 8  
//B���������
#define C_gl 9  
//C���������
#define N_gl 0x0A 
//D���������
#define Gz_TD 0x0B 
//ͣ�����
//#define FZ_SD 0x0C //�ֶ���բ��δ֪��
#define FZ_UK 0x0c 
//δ֪��բ
#define FZ_AJ 0x0d 
//������բ
#define FZ_YC 0x0e 
//Զ�̷�բ
#define Gz_QL 0x13
//���ϵƵĶ���
#define GV_LED_ON dispbit[4] = 0x01;
#define GL_LED_ON dispbit[4] = 0x02;
#define GC_LED_ON dispbit[4] = 0x04;
#define GJ_LED_ON dispbit[4] = 0x08;

#define trip_reason_normal 0 
#define trip_reason_leak 2 
#define trip_reason_zero 4 
#define trip_reason_cur 5 
#define trip_reason_short 6 
#define trip_reason_phase 7 
#define trip_reason_undervoltage 8 
#define trip_reason_overvoltage 9 
#define trip_reason_ground 0x0A 
#define trip_reason_powerdown 0x0B 
#define trip_reason_timer 0x0C 
#define trip_reason_remote 0x0D 
#define trip_reason_key 0x0E 
#define trip_reason_lock 0x0F 
#define trip_reason_sensor 0x10 
#define trip_reason_close 0x11 
#define trip_reason_hand 0x12 
#define trip_reason_change 0x13 
#define trip_reason_quit 0x1F
#define trip_reason_3D_cur 0x16
#define trip_reason_lowvoltage 0x17

//#define  T_H_V T_HV_Array[Vol_g_T]
//#define  T_L_V T_LV_Array[Vol_q_T]


extern	u8 at[3];
//LCD
//uint8_t Receive_Temp;        //��������
//uint8_t Receive_Flag=0;      //���ձ�־ 1�����ڽ�������
//uint8_t Receive_index = 0;   //��������λ������
//uint8_t Receive_CRC;         //����У��λ

//uint8_t LCD_Receive[30];  //������������
//uint8_t LCD_Receive_last[30]; //������������
//uint8_t Send[30];  //������������
void Write_or_Readresponse(uint8_t tmp,unsigned short len,unsigned char *array_temp);
void Read_Data_process(void); 
//void WorRrespond_process(void);
void Write_response(uint8_t tmp);
void Warn_process();
void Protect_process();
//
extern void Cur_Switch(unsigned char tmp);
extern void ctrlword1_analyze(void);
extern void ctrlword2_analyze(void);
extern void ctrlword3_analyze(void);
extern void ctrlword4_analyze(void);
extern void ctrlword5_analyze(void);
void Read_fenzha_tim(unsigned char fact_tmp);

extern volatile unsigned char tim_disp[7],tim_m,tim_d,tim_h,tim_f,tim_s,sssj_N;
extern volatile unsigned char tim_m1,tim_d1,tim_h1,tim_f1,tim_s1;
extern volatile unsigned int  tim_y;
extern volatile unsigned int  tim_y1;


extern volatile unsigned char tim_m2,tim_d2,tim_h2,tim_f2,tim_s2;
extern volatile unsigned int  tim_y2;


extern volatile unsigned int DLS_Cur_IV_AD_value[5],DLS_Cur_IV_slope[5],DLS_Cur_IV_Value[5];
extern volatile unsigned int DLS_Cur_I_AD_value[5],DLS_Cur_I_slope[5],DLS_Cur_I_Value[5];
extern volatile unsigned int DLS_Cur_II_AD_value[5],DLS_Cur_II_slope[5],DLS_Cur_II_Value[5];
extern volatile unsigned int DLS_Cur_III_AD_value[5],DLS_Cur_III_slope[5],DLS_Cur_III_Value[5];


void hongwai_SendData(unsigned char Data);
unsigned char hard_ver_code[Lenth_hard_ver] = "hard ver1.0 2013-11-28          ";
unsigned char soft_ver_code[Lenth_soft_ver] = "soft ver1.0 2013-11-28          ";

//�Ͼ����Ƶ���"1LJM4L    "
//����һ����  "1GRM1L    "
unsigned int UART_N1=0,UART_N2=0;
extern void Cur_Switch_F(unsigned char tmp);
extern void copy_array(unsigned char *obj_tmp,unsigned char *sours_tmp,unsigned char lenth_tmp);
extern unsigned char dev_id_code[];
extern      unsigned char dev_code_code[];
extern      unsigned char frame_current_code[];
extern      unsigned char rated_V_code[];
extern      unsigned char equi_type_code[];
extern      unsigned char production_date_code[];
extern      unsigned char protocol_ver_code[];
extern      unsigned char factory_code_code[];
//extern      unsigned char soft_ver_code[];
//extern      unsigned char hard_ver_code[];
extern      unsigned char leak_valve_code[];
extern      unsigned char leak_time_code[];
extern      unsigned char break_time_code[];
extern      unsigned char auto_closing_code[];
extern      unsigned char leak_type_code[],install_phase_type_code[];
extern   volatile    unsigned int Leak_limit_time_class[];
extern  unsigned int Leak_Class[];
extern volatile  unsigned long T_yc_hezha ,T_yc_fenzha,T_yc_fenzha_js,T_yc_hezha_js,T_an_fenzha,T_an_fenzha_js;
extern volatile unsigned int  Leak_Cur_disp;

extern unsigned char alarm_value_code[];
extern unsigned char record_value_code[];
extern unsigned char record_time_code[];
extern unsigned char timed_trip_code[];
extern unsigned char over_vol_code[];
extern unsigned char under_vol_code[];
extern unsigned char break_phase_code[];
extern unsigned char rated_current_code[];
extern unsigned char over_current_code[],F_GJ_FUNC ;
extern  const unsigned int D_HV_Array[],D_LV_Array[];
extern  const unsigned long D_C1_Array[];//20~100����λ1.15������ֵ
extern  const unsigned long D_C15_Array[];//00,100663894,180000000,280272589,405000000,549881285,720000000,909489981,1125000000};//20~100����λ1.5������ֵ
extern  const unsigned long D_C19_Array[];//={200,300,400,500,600,700,800,900,950};
extern  const unsigned int  D_C1H_Array[];//
extern volatile unsigned long H_Cur,H5_Cur,I2,I3;
extern volatile unsigned  long Num_clearall;

extern volatile unsigned long Num_leak_record;
//void hongwai_Send_Data(u8 *buf,u8 len);
extern volatile int Num_leakquit,H_D_V;
extern volatile unsigned int  Leak_Alarm_Value;
extern volatile unsigned int Leak_Cur_disp_temp;
extern  unsigned char ctrlword[5],stateword[5];
extern volatile unsigned char F_Trip;
extern  unsigned char password_0class[4],password_1class[4],password_2class[4];
extern volatile unsigned char point_trip,F_set_state;
extern volatile unsigned char 	F_trip_dl, F_analog_trip, F_trip_ld,F_trip_sy,F_trip_qy,F_trip_gy ,F_dataalarm_xq,F_trip_xq ,F_trip_gl ,	F_trip_xl,F_data_clear,F_Corr,F_auto_ld;
extern volatile unsigned char  	F_hezha_js,F_fenzha_js,F_an_js;

volatile unsigned char F_re_sta,F_re_sta1,Addr_len,Addr_len1,F_guangbo,F_benji,F_addr,TH_tem;
volatile unsigned char DI0,DI1,DI2,DI3;
volatile unsigned char ctrl_code,cs_data1,ctrl_code1,data_len_temp,cs_data,guozhitao,Addr_array[6],Addr_array1[6],T_value[13],Addr_len,data_len,data_len1,data_len_temp1,TH_tem;
extern unsigned char UART_T_Buf[60],UART_S_Buf[60],F_Dataval1,self_addr_code[6],F_Dataval,F_Dataval_lcd,F_Dataval_wendu;
extern volatile signed int I_Array[4],I_Array_xianshi[20],I1_cal_tmp[3],I2_cal_tmp[3];
extern volatile unsigned char tmp_uart_rx[50];
unsigned char  data_array[70];
unsigned char  Lcd_data_array[400];
unsigned char  data_array1[70];


extern unsigned short int V_A_slope[3],V_B_slope[3],V_C_slope[3],L_slope[3],I_A_slope[5],I_B_slope[5],I_C_slope[5],Vol_C_disp[3],Vol_B_disp[3],Vol_A_disp[3],Cur_A_disp[5],Cur_B_disp[5],Cur_C_disp[5],Leak_disp[3];
extern unsigned int Vol_A_temp[3],Vol_B_temp[3],Vol_C_temp[3];
extern volatile unsigned int  Cur_A_temp[7],Cur_B_temp[7],Cur_C_temp[7],Leak_temp[3];


volatile unsigned int Vol_uart_q,Vol_uart_g,UART_Cur_Value;

extern unsigned char F_day_updata,F_yc_hezha,F_yc_fenzha,F_yc;
extern unsigned char  	F_disp_h,F_yc_hezha,F_yc_fenzha,F_an_fenzha;
extern volatile unsigned int  L_Cur,A_Vol,B_Vol,C_Vol,A_Cur,B_Cur,C_Cur,Z_Cur,I_VAL,V_Array[3],V_Array_record[3],V_sample[3];
extern volatile unsigned char max_phase;
extern  volatile unsigned char F_disp_jg;
extern volatile unsigned int Leak_Cur;
extern unsigned int vol_handle(unsigned int value);
extern unsigned int vol_handle_A(unsigned int value);
extern unsigned int vol_handle_B(unsigned int value);
extern unsigned int vol_handle_C(unsigned int value);

extern  unsigned int cur_handle(unsigned int x);
extern unsigned int cur_handle_A(unsigned int x);
extern unsigned int cur_handle_B(unsigned int x);
extern unsigned int cur_handle_C(unsigned int x);
extern  unsigned int cur_cal_handle(unsigned int x);
extern volatile unsigned char D_LCur,TH_LCur,T_run_time_array[5],F_gz,D2_Cur,TH_DL;
extern volatile unsigned char D_Cur,Type_Cur;
extern unsigned int leak_handle(unsigned int x);
extern volatile unsigned char point_leak_max,point_leak_min;
extern volatile unsigned char  point_Avol_max,point_Bvol_max,point_Cvol_max;
extern volatile unsigned char  point_Acur_max,point_Bcur_max,point_Ccur_max;
extern volatile unsigned char  point_Avol_min,point_Bvol_min,point_Cvol_min;
extern volatile unsigned char  point_Acur_min,point_Bcur_min,point_Ccur_min;
extern volatile unsigned char point_event_leak,point_event_alarm;
extern volatile unsigned  int point_Leak_record;
extern volatile unsigned char point_event_trip,point_event_trip_24C256,point_event_leak,F_hezha_sta,point_event_self;
extern  unsigned char baud,baud_uart;
extern  unsigned char timed_trip_code[3];
extern  unsigned char Vol_g_T,Vol_q_T,Vol_s_T,over_vol_code[2],Vol_g,Vol_q;
extern  unsigned char under_vol_code[2];
extern  unsigned char break_phase_code[2];
extern unsigned char remote_trip_time[2],remote_close_time[2],analog_trip_time[2];
extern  unsigned char rated_current_code[3] ;
extern  unsigned char over_current_code[2];
extern volatile unsigned char Leak_record_value,Leak_record_time;
extern volatile signed int Leak_Cur_uart;
extern volatile signed long I_I_Array_xianshi[20],CurA_cal_tmp[5],CurB_cal_tmp[5],CurC_cal_tmp[5],Leak1_temp,Vol1_A_temp,Vol1_B_temp,Vol1_C_temp;

extern volatile signed long CurA400_cal_tmp[5],CurB400_cal_tmp[5],CurC400_cal_tmp[5];
extern volatile signed long CurA630_cal_tmp[5],CurB630_cal_tmp[5],CurC630_cal_tmp[5];
extern volatile signed long CurA800_cal_tmp[5],CurB800_cal_tmp[5],CurC800_cal_tmp[5];
volatile unsigned int rated_cur;
void vol_uart_cal_handle(unsigned char tmp,unsigned char temp,unsigned int value);
void cur_uart_cal_handle(unsigned char tmp,unsigned char temp,unsigned int value);
void leak_uart_cal_handle(void);
void SD_uart_cal_handle(unsigned char tmp,unsigned char temp,unsigned int value);

extern float Power_factor[3],Active_Pow[3],Total_power[3];

extern void xianshishuju1(unsigned int dat);


 unsigned char TXJZ_start=0;//ͨѶУ׼��ʼ��־λ0������1��ʼ
unsigned char TXJZ_SJ=0;//ͨѶʱ��
//unsigned char TXJZ_DY=0;//ͨѶ��ѹ
unsigned char TXJZ_LD=0;//ͨѶ©��

unsigned char TXJZ_DL_A=0;//ͨѶ����A
unsigned char TXJZ_DL_B=0;//ͨѶ����B
unsigned char TXJZ_DL_C=0;//ͨѶ����C

unsigned char TXJZ_DY_A=0;//ͨѶ��ѹA
unsigned char TXJZ_DY_B=0;//ͨѶ��ѹB
unsigned char TXJZ_DY_C=0;//ͨѶ��ѹC

extern volatile unsigned char F_initial_lcd,F_ld_change_stateword,LEDA_FLAG,Fun_Power_Flag,Fun_Power_Flag1;
extern  signed int HT7038_buf[100];
extern  signed int Accumulate_energy_dangqian_active_he ; //������ܺ����й�
extern  signed int Accumulate_energy_shangci_active_he;
extern  signed int Accumulate_energy_dangqian_active_A ; //�������A���й�
extern  signed int Accumulate_energy_shangci_active_A;
extern  signed int Accumulate_energy_dangqian_active_C ; //�������C���й�
extern  signed int Accumulate_energy_shangci_active_C;
extern  signed int Accumulate_energy_dangqian_reactive_he ; //������ܺ����޹�
extern  signed int Accumulate_energy_shangci_reactive_he;
extern volatile unsigned char duandian,TH_Long_Cur,F_TB_trip,N_anolog_trip,F_ia,F_ip_3,F_sssj,F_ip,F_anolog_trip,LC_N,F_al1,D_LCur,TH_LCur,Vol_ch ,F_trip_QL;
extern float Urms_A,Urms_B,Urms_C,Ugain_A,Ugain_B,Ugain_C,Igain_A,Igain_B,Igain_C,Error_A,Error_B,Error_C,Pgain_A,Pgain_B,Pgain_C,Pgain_AA,Pgain_BB,Pgain_CC,Irms_A,Irms_B,Irms_C;
extern unsigned int Uoffset_B,Uoffset_C,Ioffset_A,Ioffset_B,Ioffset_C,Ioffset_ABC;


extern volatile unsigned char F_sssj;
extern void factor_first_init(unsigned char tmp);
extern void factors_init(void);
extern volatile unsigned short int I1_A_slope[2],I1_B_slope[2],I1_C_slope[2];	
extern volatile unsigned int Leak_Cur_disp_temp,V_Array_disp[3];
extern volatile signed int I_A_factor,V_A_factor,I_B_factor,V_B_factor,I_C_factor,V_C_factor,V1_slope[3],Power_Add[3],Power_Add_flag[3];
extern volatile unsigned char F_sssj,F_shishichaxun;

extern unsigned char shangdian;
extern volatile unsigned	char F_trip_QX;
extern volatile unsigned short int L1_slope;
unsigned char crc_temp=0;
extern volatile unsigned long Delta_Cur,DLD_Cur,DLS_Cur;

extern volatile unsigned char	tmp_uart_rx_1[100];

#define ERR_BAD_DATA (0x01+0x33)
#define ERR_NO_REQUEST (0x02+0x33)
#define ERR_BAD_PASSWORD (0x04+0x33)
#define ERR_BAD_BAUD (0x08+0x33)
#define ERR_NO_REMOTE (0x10+0x33)


#define RS485_RX_EN   HAL_GPIO_WritePin(RS485_TX_EN_GPIO_Port, RS485_TX_EN_Pin, GPIO_PIN_SET)//����Ϊ����ģʽ  
#define RS485_TX_EN   HAL_GPIO_WritePin(RS485_TX_EN_GPIO_Port, RS485_TX_EN_Pin, GPIO_PIN_RESET)//����Ϊ����ģʽ

  
//#ifdef EN_USART3_RX   	//���ʹ���˽���
	

//���ջ����� 	
u8 RS485_RX_BUF[64];  	//���ջ���,���64���ֽ�.
//���յ������ݳ���
u8 RS485_RX_CNT=0;   		


/* USER CODE END 0 */

UART_HandleTypeDef huart4;
UART_HandleTypeDef huart1;
UART_HandleTypeDef huart3;

/* UART4 init function */
void MX_UART4_Init(void)
{

  /* USER CODE BEGIN UART4_Init 0 */

  /* USER CODE END UART4_Init 0 */

  /* USER CODE BEGIN UART4_Init 1 */

  /* USER CODE END UART4_Init 1 */
  huart4.Instance = UART4;
  huart4.Init.BaudRate = 115200;
  huart4.Init.WordLength = UART_WORDLENGTH_8B;
  huart4.Init.StopBits = UART_STOPBITS_1;
  huart4.Init.Parity = UART_PARITY_NONE;
  huart4.Init.Mode = UART_MODE_TX_RX;
  huart4.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart4.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart4) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN UART4_Init 2 */
HAL_UART_Receive_IT(&huart4,(uint8_t*)tmp_uart_rx,1);
  /* USER CODE END UART4_Init 2 */

}
/* USART1 init function */

void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 38400;
  huart1.Init.WordLength = UART_WORDLENGTH_9B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_EVEN;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */
	HAL_UART_Receive_IT(&huart1, (uint8_t *)tmp_uart_rx, 1);
//HAL_UART_Receive_IT(&huart1,(uint8_t*)tmp_uart_rx,1);
  /* USER CODE END USART1_Init 2 */

}
/* USART3 init function */

void MX_USART3_UART_Init(void)
{

  /* USER CODE BEGIN USART3_Init 0 */

  /* USER CODE END USART3_Init 0 */

  /* USER CODE BEGIN USART3_Init 1 */

  /* USER CODE END USART3_Init 1 */
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 9600;
  huart3.Init.WordLength = UART_WORDLENGTH_9B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_EVEN;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART3_Init 2 */
HAL_UART_Receive_IT(&huart3,(uint8_t*)tmp_uart_rx,1);
  /* USER CODE END USART3_Init 2 */

}

void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(uartHandle->Instance==UART4)
  {
  /* USER CODE BEGIN UART4_MspInit 0 */

  /* USER CODE END UART4_MspInit 0 */
    /* UART4 clock enable */
    __HAL_RCC_UART4_CLK_ENABLE();

    __HAL_RCC_GPIOC_CLK_ENABLE();
    /**UART4 GPIO Configuration
    PC10     ------> UART4_TX
    PC11     ------> UART4_RX
    */
    GPIO_InitStruct.Pin = RS485_TX_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(RS485_TX_GPIO_Port, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = RS485_RX_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(RS485_RX_GPIO_Port, &GPIO_InitStruct);

    /* UART4 interrupt Init */
    HAL_NVIC_SetPriority(UART4_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(UART4_IRQn);
  /* USER CODE BEGIN UART4_MspInit 1 */

  /* USER CODE END UART4_MspInit 1 */
  }
  else if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspInit 0 */

  /* USER CODE END USART1_MspInit 0 */
    /* USART1 clock enable */
    __HAL_RCC_USART1_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**USART1 GPIO Configuration
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX
    */
    GPIO_InitStruct.Pin = LCD_TX_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(LCD_TX_GPIO_Port, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = LCD_RX_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(LCD_RX_GPIO_Port, &GPIO_InitStruct);

    /* USART1 interrupt Init */
    HAL_NVIC_SetPriority(USART1_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART1_IRQn);
  /* USER CODE BEGIN USART1_MspInit 1 */

  /* USER CODE END USART1_MspInit 1 */
  }
  else if(uartHandle->Instance==USART3)
  {
  /* USER CODE BEGIN USART3_MspInit 0 */

  /* USER CODE END USART3_MspInit 0 */
    /* USART3 clock enable */
    __HAL_RCC_USART3_CLK_ENABLE();

    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**USART3 GPIO Configuration
    PB10     ------> USART3_TX
    PB11     ------> USART3_RX
    */
    GPIO_InitStruct.Pin = PLC_TX_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(PLC_TX_GPIO_Port, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = PLC_RX_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(PLC_RX_GPIO_Port, &GPIO_InitStruct);

    /* USART3 interrupt Init */
    HAL_NVIC_SetPriority(USART3_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART3_IRQn);
  /* USER CODE BEGIN USART3_MspInit 1 */

  /* USER CODE END USART3_MspInit 1 */
  }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{

  if(uartHandle->Instance==UART4)
  {
  /* USER CODE BEGIN UART4_MspDeInit 0 */

  /* USER CODE END UART4_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_UART4_CLK_DISABLE();

    /**UART4 GPIO Configuration
    PC10     ------> UART4_TX
    PC11     ------> UART4_RX
    */
    HAL_GPIO_DeInit(GPIOC, RS485_TX_Pin|RS485_RX_Pin);

    /* UART4 interrupt Deinit */
    HAL_NVIC_DisableIRQ(UART4_IRQn);
  /* USER CODE BEGIN UART4_MspDeInit 1 */

  /* USER CODE END UART4_MspDeInit 1 */
  }
  else if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspDeInit 0 */

  /* USER CODE END USART1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART1_CLK_DISABLE();

    /**USART1 GPIO Configuration
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX
    */
    HAL_GPIO_DeInit(GPIOA, LCD_TX_Pin|LCD_RX_Pin);

    /* USART1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USART1_IRQn);
  /* USER CODE BEGIN USART1_MspDeInit 1 */

  /* USER CODE END USART1_MspDeInit 1 */
  }
  else if(uartHandle->Instance==USART3)
  {
  /* USER CODE BEGIN USART3_MspDeInit 0 */

  /* USER CODE END USART3_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART3_CLK_DISABLE();

    /**USART3 GPIO Configuration
    PB10     ------> USART3_TX
    PB11     ------> USART3_RX
    */
    HAL_GPIO_DeInit(GPIOB, PLC_TX_Pin|PLC_RX_Pin);

    /* USART3 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USART3_IRQn);
  /* USER CODE BEGIN USART3_MspDeInit 1 */

  /* USER CODE END USART3_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
 if(huart==&huart1)// ��ʾ��ͨ��
 {
//HAL_UART_Receive_IT(&huart1,(uint8_t*)tmp_uart_rx_1,55);
	 u8 tmp = tmp_uart_rx[0];			
		if(F_re_sta==0)  // �޿�ʼ��־���ȴ�֡ͷ
		{
			if(tmp!=0x68) 
			{
				HAL_UART_Receive_IT(&huart1,(uint8_t*)tmp_uart_rx,1);  
				return;//����֡ͷ��δ�ý��ձ�־�򲻽��� 
			}
			if(tmp==0x68)		  //֡ͷ���޿�ʼ��־����ʼ���ղ��ñ�־
			{
				data_len_temp = 0;
				F_re_sta = 2;
				HAL_UART_Receive_IT(&huart1,(uint8_t*)tmp_uart_rx,1);  
				return;
			}
		}
		else if(F_re_sta==2) //��ʼ���յ�ַ����
		{
			
			if(Addr_len==1)
			{
				if(tmp==0x68)
				{
					Addr_len = 0;
					F_re_sta=3;
					HAL_UART_Receive_IT(&huart1,(uint8_t*)tmp_uart_rx,1);  
					return;
				}
				else
				{
					F_re_sta =0;
					Addr_len =0 ;
					HAL_UART_Receive_IT(&huart1,(uint8_t*)tmp_uart_rx,1);  
					return;
				}
			}
			else
			{
				Addr_array[Addr_len] = tmp;
				Addr_len++;
				HAL_UART_Receive_IT(&huart1,(uint8_t*)tmp_uart_rx,1);  
				return;
			}
		}
		else if(F_re_sta==3) //���տ�����
		{
			ctrl_code = tmp;
			if(ctrl_code<=0x80)  //��վ����������֡  80 Ϊ����
			{
				F_re_sta=4;
				HAL_UART_Receive_IT(&huart1,(uint8_t*)tmp_uart_rx,1);  
				return;
			}
			else
			{
				F_re_sta = 0;
				//ctrl_code = 0;
				HAL_UART_Receive_IT(&huart1,(uint8_t*)tmp_uart_rx,1);  
				return;
			}
		}
    else if(F_re_sta==4)//�������ݳ���
		{
			data_len = 	tmp;
			if(data_len<=208)
			{
				if(data_len==0)
				{
					F_re_sta = 6;
					HAL_UART_Receive_IT(&huart1,(uint8_t*)tmp_uart_rx,1);  
					return;
				}
				else
				{
					F_re_sta = 5;
					HAL_UART_Receive_IT(&huart1,(uint8_t*)tmp_uart_rx,1);  
					return;
				}
			}
			else
			{
				F_re_sta = 0;
				HAL_UART_Receive_IT(&huart1,(uint8_t*)tmp_uart_rx,1);  
				return;
			}	
		}
		else if(F_re_sta==5)	  //��ʼ��������
		{
			if(data_len>0)
			{
				Lcd_data_array[data_len_temp] = tmp;
				data_len_temp++;
				HAL_UART_Receive_IT(&huart1,(uint8_t*)tmp_uart_rx,1);  
				if(data_len_temp==data_len)
				{
					F_re_sta = 6;
				}
				if(data_len_temp>data_len)  //ʲô��˼��
				{
					//clear_uart_sta();
					F_re_sta = 0;
					HAL_UART_Receive_IT(&huart1,(uint8_t*)tmp_uart_rx,1);  
					return;					
				}
//				if(data_len_temp>50)
//				{
//					clear_uart_sta();
//					HAL_UART_Receive_IT(&huart3,(uint8_t*)tmp_uart_rx,1);  
//					return;					
//				}
				HAL_UART_Receive_IT(&huart1,(uint8_t*)tmp_uart_rx,1);  
				return;
			}
		}
    else if(F_re_sta==6)//����У����
		{
			cs_data = tmp;
			F_re_sta = 7;
			HAL_UART_Receive_IT(&huart1,(uint8_t*)tmp_uart_rx,1);  
			return;
		}
		else if(F_re_sta ==7)//����֡β
		{
			if(tmp == 0x16)
			{
				//F_re_sta = 8;
				F_re_sta = 0;
				F_Dataval_lcd = 1;
				HAL_UART_Receive_IT(&huart1,(uint8_t*)tmp_uart_rx,1);  
				return;
			}
			else
			{
				F_re_sta = 0;
				HAL_UART_Receive_IT(&huart1,(uint8_t*)tmp_uart_rx,1); 
				return ;
			}
		}
  											 
	}
//		
 if(huart==&huart3)//�ز�
 {
	 
	  u8 tmp = tmp_uart_rx[0];			
		if(F_re_sta==0)  // �޿�ʼ��־���ȴ�֡ͷ
		{
			if(tmp!=0x68) 
			{
				HAL_UART_Receive_IT(&huart3,(uint8_t*)tmp_uart_rx,1);  
				return;//����֡ͷ��δ�ý��ձ�־�򲻽��� 
			}
			if(tmp==0x68)		  //֡ͷ���޿�ʼ��־����ʼ���ղ��ñ�־
			{
				data_len_temp = 0;
				F_re_sta = 2;
				HAL_UART_Receive_IT(&huart3,(uint8_t*)tmp_uart_rx,1);  
				return;
			}
		}
		else if(F_re_sta==2) //��ʼ���յ�ַ����
		{
			
			if(Addr_len==6)
			{
				if(tmp==0x68)
				{
					Addr_len = 0;
					F_re_sta=3;
					HAL_UART_Receive_IT(&huart3,(uint8_t*)tmp_uart_rx,1);  
					return;
				}
				else
				{
					F_re_sta =0;
					Addr_len =0 ;
					HAL_UART_Receive_IT(&huart3,(uint8_t*)tmp_uart_rx,1);  
					return;
				}
			}
			else
			{
				Addr_array[Addr_len] = tmp;
				Addr_len++;
				HAL_UART_Receive_IT(&huart3,(uint8_t*)tmp_uart_rx,1);  
				return;
			}
		}
		else if(F_re_sta==3) //���տ�����
		{
			ctrl_code = tmp;
			if(ctrl_code<=0x80)  //��վ����������֡  80 Ϊ����
			{
				F_re_sta=4;
				HAL_UART_Receive_IT(&huart3,(uint8_t*)tmp_uart_rx,1);  
				return;
			}
			else
			{
				F_re_sta = 0;
				//ctrl_code = 0;
				HAL_UART_Receive_IT(&huart3,(uint8_t*)tmp_uart_rx,1);  
				return;
			}
		}
    else if(F_re_sta==4)//�������ݳ���
		{
			data_len = 	tmp;
			if(data_len<=208)
			{
				if(data_len==0)
				{
					F_re_sta = 6;
					HAL_UART_Receive_IT(&huart3,(uint8_t*)tmp_uart_rx,1);  
					return;
				}
				else
				{
					F_re_sta = 5;
					HAL_UART_Receive_IT(&huart3,(uint8_t*)tmp_uart_rx,1);  
					return;
				}
			}
			else
			{
				F_re_sta = 0;
				HAL_UART_Receive_IT(&huart3,(uint8_t*)tmp_uart_rx,1);  
				return;
			}	
		}
		else if(F_re_sta==5)	  //��ʼ��������
		{
			if(data_len>0)
			{
				data_array[data_len_temp] = tmp;
				data_len_temp++;
				
				if(data_len_temp==data_len)
				{
					F_re_sta = 6;
				}
				if(data_len_temp>data_len)  //ʲô��˼��
				{
					//clear_uart_sta();
					F_re_sta = 0;
					HAL_UART_Receive_IT(&huart3,(uint8_t*)tmp_uart_rx,1);  
					return;					
				}
//				if(data_len_temp>50)
//				{
//					clear_uart_sta();
//					HAL_UART_Receive_IT(&huart3,(uint8_t*)tmp_uart_rx,1);  
//					return;					
//				}
				HAL_UART_Receive_IT(&huart3,(uint8_t*)tmp_uart_rx,1);  
				return;
			}
		}
    else if(F_re_sta==6)//����У����
		{
			cs_data = tmp;
			F_re_sta = 7;
			HAL_UART_Receive_IT(&huart3,(uint8_t*)tmp_uart_rx,1);  
			return;
		}
		else if(F_re_sta ==7)//����֡β
		{
			if(tmp == 0x16)
			{
				//F_re_sta = 8;
				F_re_sta = 0;
				F_Dataval = 1;
				HAL_UART_Receive_IT(&huart3,(uint8_t*)tmp_uart_rx,1);  
				return;
			}
			else
			{
				F_re_sta = 0;
				HAL_UART_Receive_IT(&huart3,(uint8_t*)tmp_uart_rx,1); 
				return ;
			}
		}
	}
 
	if(huart==&huart4)// 485ͨ��
	{
	 
	  u8 tmp = tmp_uart_rx[0];			
		if(F_re_sta==0)  // �޿�ʼ��־���ȴ�֡ͷ
		{
			if(tmp!=0x68) 
			{
				HAL_UART_Receive_IT(&huart3,(uint8_t*)tmp_uart_rx,1);  
				return;//����֡ͷ��δ�ý��ձ�־�򲻽��� 
			}
			if(tmp==0x68)		  //֡ͷ���޿�ʼ��־����ʼ���ղ��ñ�־
			{
				data_len_temp = 0;
				F_re_sta = 2;
				HAL_UART_Receive_IT(&huart3,(uint8_t*)tmp_uart_rx,1);  
				return;
			}
		}
		else if(F_re_sta==2) //��ʼ���յ�ַ����
		{
			
			if(Addr_len==6)
			{
				if(tmp==0x68)
				{
					Addr_len = 0;
					F_re_sta=3;
					HAL_UART_Receive_IT(&huart3,(uint8_t*)tmp_uart_rx,1);  
					return;
				}
				else
				{
					F_re_sta =0;
					Addr_len =0 ;
					HAL_UART_Receive_IT(&huart3,(uint8_t*)tmp_uart_rx,1);  
					return;
				}
			}
			else
			{
				Addr_array[Addr_len] = tmp;
				Addr_len++;
				HAL_UART_Receive_IT(&huart3,(uint8_t*)tmp_uart_rx,1);  
				return;
			}
		}
		else if(F_re_sta==3) //���տ�����
		{
			ctrl_code = tmp;
			if(ctrl_code<=0x80)  //��վ����������֡  80 Ϊ����
			{
				F_re_sta=4;
				HAL_UART_Receive_IT(&huart3,(uint8_t*)tmp_uart_rx,1);  
				return;
			}
			else
			{
				F_re_sta = 0;
				//ctrl_code = 0;
				HAL_UART_Receive_IT(&huart3,(uint8_t*)tmp_uart_rx,1);  
				return;
			}
		}
    else if(F_re_sta==4)//�������ݳ���
		{
			data_len = 	tmp;
			if(data_len<=208)
			{
				if(data_len==0)
				{
					F_re_sta = 6;
					HAL_UART_Receive_IT(&huart3,(uint8_t*)tmp_uart_rx,1);  
					return;
				}
				else
				{
					F_re_sta = 5;
					HAL_UART_Receive_IT(&huart3,(uint8_t*)tmp_uart_rx,1);  
					return;
				}
			}
			else
			{
				F_re_sta = 0;
				HAL_UART_Receive_IT(&huart3,(uint8_t*)tmp_uart_rx,1);  
				return;
			}	
		}
		else if(F_re_sta==5)	  //��ʼ��������
		{
			if(data_len>0)
			{
				data_array[data_len_temp] = tmp;
				data_len_temp++;
				
				if(data_len_temp==data_len)
				{
					F_re_sta = 6;
				}
				if(data_len_temp>data_len)  //ʲô��˼��
				{
					//clear_uart_sta();
					F_re_sta = 0;
					HAL_UART_Receive_IT(&huart3,(uint8_t*)tmp_uart_rx,1);  
					return;					
				}
//				if(data_len_temp>50)
//				{
//					clear_uart_sta();
//					HAL_UART_Receive_IT(&huart3,(uint8_t*)tmp_uart_rx,1);  
//					return;					
//				}
				HAL_UART_Receive_IT(&huart3,(uint8_t*)tmp_uart_rx,1);  
				return;
			}
		}
    else if(F_re_sta==6)//����У����
		{
			cs_data = tmp;
			F_re_sta = 7;
			HAL_UART_Receive_IT(&huart3,(uint8_t*)tmp_uart_rx,1);  
			return;
		}
		else if(F_re_sta ==7)//����֡β
		{
			if(tmp == 0x16)
			{
				//F_re_sta = 8;
				F_re_sta = 0;
				F_Dataval = 1;
				HAL_UART_Receive_IT(&huart3,(uint8_t*)tmp_uart_rx,1);  
				return;
			}
			else
			{
				F_re_sta = 0;
				HAL_UART_Receive_IT(&huart3,(uint8_t*)tmp_uart_rx,1); 
				return ;
			}
		}
	}
  											 
	
	 
	 
	 ///*************��ʾ*******************/
	 
//	 uint8_t i = 0;
//	 u8 tmp = tmp_uart_rx[0];		
//	 if(Receive_Flag==0)  // �޿�ʼ��־���ȴ�֡ͷ
//		 {
//					if(tmp!=0x68) 
//					{
//						HAL_UART_Receive_IT(&huart3,(uint8_t*)tmp_uart_rx,1);  
//						return;//����֡ͷ��δ�ý��ձ�־�򲻽��� 
//					}
//					if(tmp==0x68)		  //֡ͷ���޿�ʼ��־����ʼ���ղ��ñ�־
//					{
//								for(i=0; i<20; i++)
//								{
//									LCD_Receive[i] = 0;  
//								}
//								Receive_index = 0;
//								LCD_Receive[Receive_index] = 0x68; 
//								Receive_Flag = 1;
//								F_Dataval_lcd = 0;  
//					}
//		 }
//		 else if(Receive_Flag==1)
//		 {
//			 
//				if(Receive_index==1)   //����λ��Ϊ1
//			{
//				if(Receive_Temp!=0xA0) //��ַ�ж� 
//				{
//					Receive_Flag = 0;
//					Receive_index = 0;
//					return ;                //�Ǳ�����ַ
//				}
//			}
//			LCD_Receive[Receive_index] = Receive_Temp; 
//			if(LCD_Receive[0]==0x68)
//			{
//				if(Receive_index < 1+1+1+1+LCD_Receive[4]+1) //У��λǰ���������
//					Receive_CRC +=Receive_Temp; 
//				else if(Receive_index == 1+1+1+1+LCD_Receive[4]+1)
//				{
//					if(Receive_CRC!=Receive_Temp)    //У��
//					{
//						Receive_Flag = 0;
//						Receive_index = 0;
//						Receive_Temp = 0;
//						Receive_CRC = 0;
//					//	Err_State = ERRO_FRAME_CHECK_SUM;
//						return ;                     //����У��λ
//					}
//					else
//					{
//						Receive_CRC = 0;           //У��ͨ��
//					}
//					
//				}
//				Receive_index++;
//				if(Receive_index==1+1+1+1+1+LCD_Receive[4]+1+1 && Receive_Temp==0x16) //�������ж�
//				{
//					for(i=0;i<20;i++)
//					{
//						LCD_Receive_last[i]=LCD_Receive[i];   //�����ݱ���
//					}
//					Receive_Flag = 0;
//					Receive_index = 0;
//					F_Dataval_lcd = 1;           //�������
//					Receive_Temp = 0;
//					//Err_State = OK;
//				}
//			}
//				
//		 }
	 
//	 	 uint8_t i = 0;
//	 u8 tmp = tmp_uart_rx[0];		
//	 if(Receive_Flag==0)  // �޿�ʼ��־���ȴ�֡ͷ
//		 {
//					if(tmp!=0x68) 
//					{
//						HAL_UART_Receive_IT(&huart3,(uint8_t*)tmp_uart_rx,1);  
//						return;//����֡ͷ��δ�ý��ձ�־�򲻽��� 
//					}
//					if(tmp==0x68)		  //֡ͷ���޿�ʼ��־����ʼ���ղ��ñ�־
//					{
//								for(i=0; i<20; i++)
//								{
//									LCD_Receive[i] = 0;  
//								}
//								Receive_index = 0;
//								LCD_Receive[Receive_index] = 0x68; 
//								Receive_Flag = 1;
//								F_Dataval_lcd = 0;  
//					}
//		 }
//		 else if(Receive_Flag==1)
//		 {
//			 
//				if(Receive_index==1)   //����λ��Ϊ1
//			{
//				if(Receive_Temp!=0xA0) //��ַ�ж� 
//				{
//					Receive_Flag = 0;
//					Receive_index = 0;
//					return ;                //�Ǳ�����ַ
//				}
//			}
//			LCD_Receive[Receive_index] = Receive_Temp; 
//			if(LCD_Receive[0]==0x68)
//			{
//				if(Receive_index < 1+1+1+1+LCD_Receive[4]+1) //У��λǰ���������
//					Receive_CRC +=Receive_Temp; 
//				else if(Receive_index == 1+1+1+1+LCD_Receive[4]+1)
//				{
//					if(Receive_CRC!=Receive_Temp)    //У��
//					{
//						Receive_Flag = 0;
//						Receive_index = 0;
//						Receive_Temp = 0;
//						Receive_CRC = 0;
//					//	Err_State = ERRO_FRAME_CHECK_SUM;
//						return ;                     //����У��λ
//					}
//					else
//					{
//						Receive_CRC = 0;           //У��ͨ��
//					}
//					
//				}
//				Receive_index++;
//				if(Receive_index==1+1+1+1+1+LCD_Receive[4]+1+1 && Receive_Temp==0x16) //�������ж�
//				{
//					for(i=0;i<20;i++)
//					{
//						LCD_Receive_last[i]=LCD_Receive[i];   //�����ݱ���
//					}
//					Receive_Flag = 0;
//					Receive_index = 0;
//					F_Dataval_lcd = 1;           //�������
//					Receive_Temp = 0;
//					//Err_State = OK;
//				}
//			}
//				
//		 }
//	 u8 tmp = tmp_uart_rx[0];			
//		if(F_re_sta==0)  // �޿�ʼ��־���ȴ�֡ͷ
//		{
//			if(tmp!=0x68) 
//			{
//				HAL_UART_Receive_IT(&huart3,(uint8_t*)tmp_uart_rx,1);  
//				return;//����֡ͷ��δ�ý��ձ�־�򲻽��� 
//			}
//			if(tmp==0x68)		  //֡ͷ���޿�ʼ��־����ʼ���ղ��ñ�־
//			{
//				data_len_temp = 0;
//				F_re_sta = 2;
//				HAL_UART_Receive_IT(&huart3,(uint8_t*)tmp_uart_rx,1);  
//				return;
//			}
//		}
//		else if(F_re_sta==2) //��ʼ���յ�ַ����
//		{
//			
//			if(Addr_len==6)
//			{
//				if(tmp==0x68)
//				{
//					Addr_len = 0;
//					F_re_sta=3;
//					HAL_UART_Receive_IT(&huart3,(uint8_t*)tmp_uart_rx,1);  
//					return;
//				}
//				else
//				{
//					F_re_sta =0;
//					Addr_len =0 ;
//					HAL_UART_Receive_IT(&huart3,(uint8_t*)tmp_uart_rx,1);  
//					return;
//				}
//			}
//			else
//			{
//				Addr_array[Addr_len] = tmp;
//				Addr_len++;
//				HAL_UART_Receive_IT(&huart3,(uint8_t*)tmp_uart_rx,1);  
//				return;
//			}
//		}
// }
//  if(huart==&huart2)////�¶�
//	{	
//		
//		u8 tmp = tmp_uart_rx[0];			
//		if(F_re_sta==0)  // �޿�ʼ��־���ȴ�֡ͷ
//		{
//			if(tmp!=0x68) 
//			{
//				HAL_UART_Receive_IT(&huart2,(uint8_t*)tmp_uart_rx,1);  
//				return;//����֡ͷ��δ�ý��ձ�־�򲻽��� 
//			}
//			if(tmp==0x68)		  //֡ͷ���޿�ʼ��־����ʼ���ղ��ñ�־
//			{
//				data_len_temp = 0;
//				F_re_sta = 2;
//				crc_temp=crc_temp+tmp;
//				HAL_UART_Receive_IT(&huart2,(uint8_t*)tmp_uart_rx,1);  
//				return;
//			}
//		}
//		else if(F_re_sta==2) //��ʼ�����¶�����
//		{
//				T_value[TH_tem] = tmp;
//				crc_temp=crc_temp+T_value[TH_tem];
//				TH_tem++;
//				
//				
//       if(TH_tem==13)
//			{
//        TH_tem=0;
//				F_re_sta=3;
//				
//				
//			}
//			HAL_UART_Receive_IT(&huart2,(uint8_t*)tmp_uart_rx,1);
//			return;
//			
//		}
//		else if(F_re_sta==3) //����У����
//		{
//			cs_data = tmp;
//			if(crc_temp==cs_data)
//			{
//			  F_re_sta = 4;
//				 crc_temp=0;
//			  HAL_UART_Receive_IT(&huart2,(uint8_t*)tmp_uart_rx,1);  
//			  return;
//			}
//			else
//			{
//				 F_re_sta = 0;
//				 crc_temp=0;
//		     for(int i=0;i<13;i++)
//				{
//				 T_value[i]=0;
//				}
//				 HAL_UART_Receive_IT(&huart2,(uint8_t*)tmp_uart_rx,1); 
//			}
//		}	
//		else if(F_re_sta==4)//����β֡
//		{
//			if(tmp == 0x16)
//			{
//		
//				F_re_sta = 0;
//				F_Dataval_wendu = 1; 
//				HAL_UART_Receive_IT(&huart2,(uint8_t*)tmp_uart_rx,1);  
//				return;
//			}
//			else
//			{
//				F_re_sta = 0;
//				HAL_UART_Receive_IT(&huart2,(uint8_t*)tmp_uart_rx,1); 
//				return ;
//			}
//			

//		}
//		
//  											 
//	}
}

void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)//2022.5.9����
{
//	HAL_StatusTypeDef ERR;
//	int i = 0;
//	if(huart->Instance == USART2)
//	{
//		__HAL_UNLOCK(&huart2);
//		ERR = HAL_UART_Receive_IT(&huart2, (uint8_t *)&tmp_uart_rx, 1);   //�ٿ��������ж�
//		if(ERR != HAL_OK)
//		{		//����
//			while(i<1000000)
//			{
//				i++;;
//			}
//		}
// 
//	}
}


//#endif
	
//#ifdef EN_USART2_RX   	//���ʹ���˽���

////���ջ����� 	
//u8 hongwai_RX_BUF[64];  	//���ջ���,���64���ֽ�.
////���յ������ݳ���
//u8 hongwai_RX_CNT=0;   		  
// void USART2_IRQHandler(void)
//{
//	u8 tmp;	    
// 
// 	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET) //���յ�����
//	{	 
//	 			 
//		if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
//		{
//		tmp =USART_ReceiveData(USART2);	//��ȡ���յ�������
//		
//		if(F_re_sta==0)  // �޿�ʼ��־���ȴ�֡ͷ
//		{
//			if(tmp!=0x68) return;//����֡ͷ��δ�ý��ձ�־�򲻽��� 
//			if(tmp==0x68)		  //֡ͷ���޿�ʼ��־����ʼ���ղ��ñ�־
//			{
//				data_len_temp = 0;
//				F_re_sta = 2;
//				//F_Dataval = 1;
//				return;
//			}
//		}
//		else if(F_re_sta==2) //��ʼ���յ�ַ����
//		{
//			
//			if(Addr_len==6)
//			{
//				if(tmp==0x68)
//				{
//					Addr_len = 0;
//					F_re_sta=3;
//					return;
//				}
//				else
//				{
//					F_re_sta =0;
//					Addr_len =0 ;
//					return;
//				}
//			}
//			else
//			{
//				Addr_array[Addr_len] = tmp;
//				Addr_len++;
//				return;
//			}
//		}
//		else if(F_re_sta==3) //���տ�����
//		{
//			ctrl_code = tmp;
//			if(ctrl_code<=0x80)  //��վ����������֡  80 Ϊ����
//			{
//				F_re_sta=4;
//				return;
//			}
//			else
//			{
//				F_re_sta= 0;
//				//ctrl_code = 0;
//				return;
//			}
//		}	
//		else if(F_re_sta==4)//�������ݳ���
//		{
//			data_len = 	tmp;
//			if(data_len<=200)
//			{
//				if(data_len==0)
//				{
//					F_re_sta = 6;
//					return;
//				}
//				else
//				{
//					F_re_sta = 5;
//					return;
//				}
//			}
//			else
//			{
//				F_re_sta = 0;
//				return;
//			}	
//		}
//		else if(F_re_sta==5)	  //��ʼ��������
//		{
//			if(data_len>0)
//			{
//				data_array[data_len_temp] = tmp;
//				data_len_temp++;
//				
//				if(data_len_temp==data_len)
//				{
//					F_re_sta = 6;
//				}
//				if(data_len_temp>data_len)  //ʲô��˼��
//				{
//					clear_uart_sta();
//					return;					
//				}
//				if(data_len_temp>50)
//				{
//					clear_uart_sta();
//					return;					
//				}
//				return;
//			}
//		}
//		else if(F_re_sta==6)//����У����
//		{
//			cs_data = tmp;
//			F_re_sta = 7;
//			return;
//		}
//		else if(F_re_sta ==7)//����֡β
//		{
//			if(tmp == 0x16)
//			{
//				//F_re_sta1 = 8;
//				F_re_sta = 0;
//				F_Dataval1 = 1;
//				return;
//			}
//		}
//	}  											 
//} 
//	}
//#endif		

unsigned char frame_check(void)  //��֡��鲻�ǿ�ܼ��
{ 
	unsigned char i,Addr_err,CHECK;
	Addr_err=0;
	CHECK = 0;
	for(i=0;i<6;i++)
	{
		if(Addr_array[i]!=0x99)   //�㲥��Ҫ���վӦ��   ��ַ������ֽ���ǰ���ֽ��ں�
		Addr_err++;   
	}
	if(Addr_err==0)
	F_guangbo = 1;    //�������99��㲥
	else
	{
		Addr_err = 0;
		for(i=0;i<6;i++)
		{
			if(Addr_array[i]!=self_addr_code_temp[i])  //����Բ��ϱ�����ַ��ADDR_ERR++
			Addr_err++;										  
		}
		if(Addr_err==0)  
		F_benji = 1;   //����������˾�F_BENJI��һ
		else
		{
			Addr_err = 0;
			for(i=0;i<6;i++)
			{
				if(Addr_array[i]!=0xAA)
				Addr_err++;										  
			}
			if(Addr_err==0)
			F_addr = 1;  //��ͨ�ŵ�ַ
			else
			{
				return 0x01;
			}
		}
	}
	CHECK = 0;
	for(i=0;i<6;i++)
	{
		CHECK = Addr_array[i]+CHECK;
	}
	CHECK = CHECK+0x68+0x68+data_len+ctrl_code;  //�ӵ�һ����ʼ����ʼ��У����֮ǰ�������ݵ�ģ256��
	for(i=0;i<data_len;i++)
	CHECK = CHECK+data_array[i];
	//mrnow_tmp1 = CHECK;
	//put2char(CHECK);
	//put2char(cs_data);
	
	if(CHECK!=cs_data)  //����Բ����򷵻�  02  У����� 
	return 0x02;
	else 
	{
		for(i=0;i<data_len;i++)
		{
			data_array[i] = data_array[i]-0x33;  //���ݽ��м�0x33����
		}
		return 0;  
	}
}

void format_uart_t_buf(void)   //�����Ű棿����
{
	unsigned char i;
	for(i=0;i<60;i++)
	{
		UART_T_Buf[i] = 0;
	}

}

void clear_uart_sta1(void)
{
	unsigned char i;
	for(i=0;i<6;i++)  
	Addr_array1[i] =0;  //��ַ
 Addr_len1 = 0;  //��ַ����
	data_len1 = data_len_temp1=0; //���ݳ���
		cs_data1 = 0;  //У����
	 ctrl_code1=0;  //������
	F_re_sta1 = 0; //��ͷ��ʼ����
}
void clear_uart_sta(void)
{
	unsigned char i;
	for(i=0;i<6;i++)
	Addr_array[i] =0;  //��ַ
	Addr_len = 0;  //��ַ����
	data_len = data_len_temp=0; //���ݳ���
	cs_data = 0;  //У����
	ctrl_code = 0;  //������
	F_re_sta = 0; //��ͷ��ʼ����
	HAL_UART_Receive_IT(&huart3, (uint8_t*)tmp_uart_rx, 1);
//	HAL_UART_Receive_IT(&huart2, (uint8_t*)tmp_uart_rx, 1);
}

void Uart_prepare(unsigned char tmp)
{
	unsigned char i;
	format_uart_t_buf();  //���Ҫд�Ķ���
	UART_T_Buf[0]=UART_T_Buf[7] = 0x68; //1 2 3 4 5 6 ���ǵ�ַ��
	for(i=0;i<6;i++)
	{
		UART_T_Buf[i+1] =  self_addr_code_temp[i];  //д��ַ����λ////�����ز�ʹ�õ���ʱ��ַ������Ҫ�Ļ�ȥ
	}
	if(tmp==0)
	{
		UART_T_Buf[8]	= ctrl_code+0x80;   //������80 ��վ����Ӧ��֡    Ҫд�Ķ���   �ѽ��յ��Ŀ��������0x80�ٴ��ͻ�ȥ
		for(i=0;i<4;i++)                
		UART_T_Buf[10+i] = data_array[i]+0x33;
	}
	if(tmp==1)
	{
		UART_T_Buf[8]	= ctrl_code+0xC0;  //C0��վ�쳣Ӧ��֡
	}
}
void Uart_prepare1(unsigned char tmp)
{
	unsigned char i;
	format_uart_t_buf();  //���Ҫд�Ķ���
	UART_T_Buf[0]=UART_T_Buf[7] = 0x68; //1 2 3 4 5 6 ���ǵ�ַ��
	for(i=0;i<6;i++)
	{
		UART_T_Buf[i+1] =  self_addr_code_temp[i];  //д��ַ����λ////�����ز�ʹ�õ���ʱ��ַ������Ҫ�Ļ�ȥ
	}
	if(tmp==0)
	{
		ctrl_code=0x13;
		UART_T_Buf[8]	= ctrl_code+0x80;   //������80 ��վ����Ӧ��֡   
	}
	if(tmp==1)
	{
		UART_T_Buf[8]	= ctrl_code+0xC0;  //C0��վ�쳣Ӧ��֡
	}
}

void Read_response(unsigned char len,unsigned char *array_tmp)
{
	
	unsigned char i,cs_temp;
	cs_temp = 0;
	Uart_prepare(0);      //��վ����Ӧ��֡
	UART_T_Buf[9] = 4 + len;
	
	for(i=0;i<len;i++)
	{
		UART_T_Buf[14+i] = array_tmp[i]+0x33;   //���������ݲ��ּ�33����
	}
	
	for(i=0;i<(14+len);i++)   //У���봦��
	{
		cs_temp =  UART_T_Buf[i] + cs_temp;
	}
	UART_T_Buf[14+len] = cs_temp;   
	UART_T_Buf[15+len] =  0x16;
	//20150202���������޸�
	//	for(i=0;i<4;i++)
	//	put2char(0xFE);
	
//	for(i=0;i<(16+len);i++)
//	put2char(UART_T_Buf[i]);
	for(i=0;i<4;i++)
	{
	UART_S_Buf[i]=0xFE;
	}
	if(F_Dataval==1)
	{
		HAL_UART_Transmit(&huart3,(uint8_t*)UART_S_Buf,4,0xffff);
		HAL_UART_Transmit(&huart3,(uint8_t*)UART_T_Buf,16+len,0xffff);///�����ز��޸�Ϊ3��
		 //RS485_Send_Data(UART_S_Buf,4);
		 //RS485_Send_Data(UART_T_Buf,16+len);
//		UART_T_Buf[0]=0X00
//		
//		//RS485_Send_Data(UART_T_Buf,3);
	}
	if(F_Dataval1==1)
	{
		 //hongwai_Send_Data(UART_T_Buf,16+len);
	}
}
void Read_response1(unsigned char len,unsigned char *array_tmp)
{
	
	unsigned char i,cs_temp;
	cs_temp = 0;
	Uart_prepare1(0);      //��վ����Ӧ��֡
	UART_T_Buf[9] = len;
	
	for(i=0;i<len;i++)
	{
		UART_T_Buf[10+i] = array_tmp[i]+0x33;   //���������ݲ��ּ�33����
	}
	
	for(i=0;i<16;i++)   //У���봦��
	{
		cs_temp =  UART_T_Buf[i] + cs_temp;
	}
	UART_T_Buf[16] = cs_temp;   
	UART_T_Buf[17] =  0x16;
	//20150202���������޸�
	//	for(i=0;i<4;i++)
	//	put2char(0xFE);
	
//	for(i=0;i<(16+len);i++)
//	put2char(UART_T_Buf[i]);
		for(i=0;i<4;i++)
	{
	UART_S_Buf[i]=0xFE;
	}
	if(F_Dataval==1)
	{
		HAL_UART_Transmit(&huart3,(uint8_t*)UART_S_Buf,4,0xffff);
		HAL_UART_Transmit(&huart3,(uint8_t*)UART_T_Buf,18,0xffff);
		 //RS485_Send_Data(UART_S_Buf,4);
		 //RS485_Send_Data(UART_T_Buf,18);
//		UART_T_Buf[0]=0X00
//		
//		//RS485_Send_Data(UART_T_Buf,3);
	}
	if(F_Dataval1==1)
	{
		 //hongwai_Send_Data(UART_T_Buf,18);
	}
}

/***************************************
	�㲥Уʱ 
***************************************/
void Broadcasting_time(void)
{
	unsigned char i,array_temp[6];

	for(i=0;i<6;i++)
	{
		array_temp[i] = data_array[5-i];
		//putchar(array_temp[i]);
	}
//	array_temp[0]=17;
	sdatestructure.Year=array_temp[0];
	sdatestructure.Month=array_temp[1];
	sdatestructure.Date=array_temp[2];
	stimestructure.Hours=array_temp[3];
	stimestructure.Minutes=array_temp[4];
	stimestructure.Seconds=array_temp[5];
	 RTC_Set_Time(array_temp[3],array_temp[4],array_temp[5]);
	 RTC_Set_Date(array_temp[0],array_temp[1],array_temp[2]);
	//ds1302_write_time_uart(array_temp2[0],array_temp[1],array_temp[2],array_temp[3],array_temp[4],array_temp[5]);   //дʱ�䣿��������������
	F_day_updata = 1;
}

unsigned char Password_verification(unsigned char tmp)   //������֤
{

	if(tmp==0)
	{
		if((password_0class[0]==data_array[4])&&(password_0class[1]==data_array[5])&&(password_0class[2]==data_array[6])&&(password_0class[3]==data_array[7]))
		{
			return 0;
		}
		else if((password_1class[0]==data_array[4])&&(password_1class[1]==data_array[5])&&(password_1class[2]==data_array[6])&&(password_1class[3]==data_array[7]))
		{
			return 1;
		}
		else if((password_2class[0]==data_array[4])&&(password_2class[1]==data_array[5])&&(password_2class[2]==data_array[6])&&(password_2class[3]==data_array[7]))
		{
			return 2;
		}
		else
		{
			return 3;
		}
	}
	if(tmp==1)
	{
		if((password_0class[0]==data_array[0])&&(password_0class[1]==data_array[1])&&(password_0class[2]==data_array[2])&&(password_0class[3]==data_array[3]))
		{
			return 0;
		}
		else if((password_1class[0]==data_array[0])&&(password_1class[1]==data_array[1])&&(password_1class[2]==data_array[2])&&(password_1class[3]==data_array[3]))
		{
			return 1;
		}
		else if((password_2class[0]==data_array[0])&&(password_2class[1]==data_array[1])&&(password_2class[2]==data_array[2])&&(password_2class[3]==data_array[3]))
		{
			return 2;
		}
		else
		{
			return 3;
		}
	}
	return 3;
}

void WRITE_DATA_NOMAL(void)
{
	unsigned char i,cs_temp;
	Uart_prepare(0);  //д�������벿��  
	UART_T_Buf[9] = 0x00;//���ݳ���  ����Ӧ��֡  ����Ӧ��֡Ϊʲô����Ϊ00  ���ݳ��Ƚ���֮��ֱ�Ӿ��ǽ�����
	cs_temp = 0;
	for(i=0;i<9;i++)
	{
		cs_temp =  UART_T_Buf[i] + cs_temp;
	}
	UART_T_Buf[10]	= cs_temp;
	UART_T_Buf[11] =  0x16;
	//20150202���������޸�
	//	for(i=0;i<4;i++)
	//	put2char(0xFE);
//	for(i=0;i<12;i++)
//	put2char(UART_T_Buf[i]);
		for(i=0;i<4;i++)
	{
	UART_S_Buf[i]=0xFE;
	}
		if(F_Dataval==1)
	{
		HAL_UART_Transmit(&huart3,(uint8_t*)UART_S_Buf,4,0xffff);
		HAL_UART_Transmit(&huart3,(uint8_t*)UART_T_Buf,12,0xffff);
		 //RS485_Send_Data(UART_S_Buf,4);
		 //RS485_Send_Data(UART_T_Buf,12);
	}
	if(F_Dataval1==1)
	{
		 //hongwai_Send_Data(UART_T_Buf,12);
	}
	
	
//	  //RS485_Send_Data(UART_T_Buf,12);
}
unsigned char Offset_cal()//ֻ���Ӹ�����Դʱ
{
	 unsigned char array_temp[2];
	 unsigned int Uoffset_A,Uoffset_B,Uoffset_C,Ioffset_A,Ioffset_B,Ioffset_C,Ioffset_ABC;
	
	HT7038_Write(0xC9,0x5A); ////ѡ��У��Ĵ���//У������дʹ��
	 HT7038_Write(0xc6,0x5b); ////ʹ��SPI�����Ĵ���������
	
	  HT7038_Write(w_IaRmsoffse,0x0000);
	  HT7038_Write(w_IbRmsoffse,0x0000);
	  HT7038_Write(w_IcRmsoffse,0x0000);
	  HT7038_Write(w_ItRmsoffset,0x0000);
	
//	  HT7038_Write(w_UaRmsoffse,0x0000);
//    HT7038_Write(w_UbRmsoffse,0x0000);
//    HT7038_Write(w_UcRmsoffse,0x0000);
	 	delay_ms(2000);
	
	/*********************����offset***************/
	 Ioffset_A=HT7038_Read(rIaRms)*HT7038_Read(rIaRms)/32768;
	 Ioffset_B=HT7038_Read(rIbRms)*HT7038_Read(rIbRms)/32768;
	 Ioffset_C=HT7038_Read(rIcRms)*HT7038_Read(rIcRms)/32768;
	 Ioffset_ABC=HT7038_Read(rItRms)*HT7038_Read(rItRms)/32768;
	
	  array_temp[0]=Ioffset_A&0xFF;
	  array_temp[1]=(Ioffset_A>>8)&0xFF;
	  MODIFY_EEP_W(Addr_Ioffset_A,array_temp,2,0xA0);	
	  array_temp[0]=Ioffset_B&0xFF;
	  array_temp[1]=(Ioffset_B>>8)&0xFF;
	  MODIFY_EEP_W(Addr_Ioffset_B,array_temp,2,0xA0);	
	  array_temp[0]=Ioffset_C&0xFF;
	  array_temp[1]=(Ioffset_C>>8)&0xFF;
	  MODIFY_EEP_W(Addr_Ioffset_C,array_temp,2,0xA0);	
	  array_temp[0]=Ioffset_ABC&0xFF;
	  array_temp[1]=(Ioffset_ABC>>8)&0xFF;
	  MODIFY_EEP_W(Addr_Ioffset_ABC,array_temp,2,0xA0);	
	
	  HT7038_Write(w_ItRmsoffset,Ioffset_ABC);
		HT7038_Write(w_IaRmsoffse,Ioffset_A);
	  HT7038_Write(w_IbRmsoffse,Ioffset_B);
	  HT7038_Write(w_IcRmsoffse,Ioffset_C);
	/*********************��ѹoffset***************/
	 
//	 Uoffset_A=HT7038_Read(rUaRms)*HT7038_Read(rUaRms)/32768;
//	 Uoffset_B=HT7038_Read(rUbRms)*HT7038_Read(rUbRms)/32768;
//	 Uoffset_C=HT7038_Read(rUcRms)*HT7038_Read(rUcRms)/32768;
//	 
//	  array_temp[0]=Uoffset_A&0xFF;
//	  array_temp[1]=(Uoffset_A>>8)&0xFF;
//	  MODIFY_EEP_W(Addr_Uoffset_A,array_temp,2,0xA0);	
//	  array_temp[0]=Uoffset_B&0xFF;
//	  array_temp[1]=(Uoffset_B>>8)&0xFF;
//	  MODIFY_EEP_W(Addr_Uoffset_B,array_temp,2,0xA0);	
//	  array_temp[0]=Uoffset_C&0xFF;
//	  array_temp[1]=(Uoffset_C>>8)&0xFF;
//	  MODIFY_EEP_W(Addr_Uoffset_C,array_temp,2,0xA0);	
//	 
//	  HT7038_Write(w_UaRmsoffse,Uoffset_A);
//    HT7038_Write(w_UbRmsoffse,Uoffset_B);
//    HT7038_Write(w_UcRmsoffse,Uoffset_C);
	 
		HT7038_Write(0xc9,0x5b); ////�ر�SPIУ��Ĵ�����д����
}
unsigned char cal()
{
	// float Urms_A,Urms_B,Urms_C,Ugain_A,Ugain_B,Ugain_C,Error_A,Error_B,Error_C,Pgain_A,Pgain_B,Pgain_C;
	 unsigned char array_temp[2];
	 signed int Measured_value_A,Measured_value_B,Measured_value_C;
	 signed int True_value=2200;
	
	/**************��ѹ����***********************/
	 HT7038_Write(0xC9,0x5A); ////ѡ��У��Ĵ���//У������дʹ��
	 HT7038_Write(0xc6,0x5b); ////ʹ��SPI�����Ĵ���������
	 HT7038_Write(w_UgainA,0x0000);//��������
	 HT7038_Write(w_UgainB,0x0000);
	 HT7038_Write(w_UgainC,0x0000);
	
				delay_ms(2000);
	
	 Urms_A=(float)HT7038_Read(rUaRms)/8192;	//����ʾ��ѹ��ʼֵ
	 Urms_B=(float)HT7038_Read(rUbRms)/8192;
	 Urms_C=(float)HT7038_Read(rUcRms)/8192;
	
	 Ugain_A=(float)220/Urms_A-1;
	 Ugain_B=(float)220/Urms_B-1;
	 Ugain_C=(float)220/Urms_C-1;
	
	
	 if(Ugain_A>=0) Ugain_A=(int)(Ugain_A*32768);
	 else    Ugain_A=(int)(65536+Ugain_A*32768);//�������棬д��洢оƬ����ht7038��ʼ��ʱ������д�뵽�Ĵ���
	 
	  if(Ugain_B>=0) Ugain_B=(int)(Ugain_B*32768);
	 else    Ugain_B=(int)(65536+Ugain_B*32768);//�������棬д��洢оƬ����ht7038��ʼ��ʱ������д�뵽�Ĵ���
	 
	  if(Ugain_C>=0) Ugain_C=(int)(Ugain_C*32768);
	 else    Ugain_C=(int)(65536+Ugain_C*32768);//�������棬д��洢оƬ����ht7038��ʼ��ʱ������д�뵽�Ĵ���
	
	array_temp[0]=(int)Ugain_A&0xFF;
	array_temp[1]=((int)Ugain_A>>8)&0xFF;
	MODIFY_EEP_W(Addr_Ugain_A,array_temp,2,0xA0);	
	HT7038_Write(w_UgainA,Ugain_A);
	
	array_temp[0]=(int)Ugain_B&0xFF;
	array_temp[1]=((int)Ugain_B>>8)&0xFF;
	MODIFY_EEP_W(Addr_Ugain_B,array_temp,2,0xA0);	
	HT7038_Write(w_UgainB,Ugain_B);
	
	array_temp[0]=(int)Ugain_C&0xFF;
	array_temp[1]=((int)Ugain_C>>8)&0xFF;
	MODIFY_EEP_W(Addr_Ugain_C,array_temp,2,0xA0);	
	HT7038_Write(w_UgainC,Ugain_C);
	
	/*************��������******************/
	
//	
//	HT7038_Write(w_IgainA,0x0000);//��������
//	HT7038_Write(w_IgainC,0x0000);//
//	HT7038_Write(w_IgainB,0x0000);//
//	delay_ms(2000);
//	
//	Irms_A = (float)HT7038_Read(rIaRms)/8192/35; 	//A�����
//	Irms_B = (float)HT7038_Read(rIbRms)/8192/35;   //B�����
//	Irms_C = (float)HT7038_Read(rIcRms)/8192/35;
//	
//	Igain_A=(float)10/Irms_A-1;
//	Igain_B=(float)10/Irms_B-1;
//	Igain_C=(float)10/Irms_C-1;
//	
//	 if(Igain_A>=0) Igain_A=(int)(Igain_A*32768);
//	 else    Igain_A=(int)(65536+Igain_A*32768);//�������棬д��洢оƬ����ht7038��ʼ��ʱ������д�뵽�Ĵ���
//	 
//	  if(Igain_B>=0) Igain_B=(int)(Igain_B*32768);
//	 else    Igain_B=(int)(65536+Igain_B*32768);//�������棬д��洢оƬ����ht7038��ʼ��ʱ������д�뵽�Ĵ���
//	 
//	  if(Igain_C>=0) Igain_C=(int)(Igain_C*32768);
//	 else    Igain_C=(int)(65536+Igain_C*32768);//�������棬д��洢оƬ����ht7038��ʼ��ʱ������д�뵽�Ĵ���
//	
//	array_temp[0]=(int)Igain_A&0xFF;
//	array_temp[1]=((int)Igain_A>>8)&0xFF;
//	MODIFY_EEP_W(Addr_Igain_A,array_temp,2,0xA0);	
//	HT7038_Write(w_IgainA,Igain_A);
//	
//	array_temp[0]=(int)Igain_B&0xFF;
//	array_temp[1]=((int)Igain_B>>8)&0xFF;
//	MODIFY_EEP_W(Addr_Igain_B,array_temp,2,0xA0);	
//	HT7038_Write(w_IgainB,Igain_B);
//	
//	array_temp[0]=(int)Igain_C&0xFF;
//	array_temp[1]=((int)Igain_C>>8)&0xFF;
//	MODIFY_EEP_W(Addr_Igain_C,array_temp,2,0xA0);	
//	HT7038_Write(w_IgainC,Igain_C);
	
	/*************��������******************/
	HT7038_Write(w_PgainA,0x0000);//A���й���������
	HT7038_Write(w_PgainB,0x0000);//B���й���������B831
  HT7038_Write(w_PgainC,0x0000);//C���й���������
	
		delay_ms(2000);
	
	Measured_value_A= HT7038_Read(rPa); //A���й�����
  if(Measured_value_A>=8388608) Measured_value_A = -(16777216-Measured_value_A);
  else Measured_value_A = Measured_value_A;
	Measured_value_A=Measured_value_A*0.032;
  Measured_value_A=abs(Measured_value_A);
	
	HT7038_buf[35]=Measured_value_A;
	
	Measured_value_B= HT7038_Read(rPb); //B���й�����
  if(Measured_value_B>=8388608) Measured_value_B = -(16777216-Measured_value_B);
  else Measured_value_B = Measured_value_B;
	Measured_value_B=Measured_value_B*0.032;
  Measured_value_B=abs(Measured_value_B);
	
	Measured_value_C= HT7038_Read(rPc); //C���й�����
  if(Measured_value_C>=8388608) Measured_value_C = -(16777216-Measured_value_C);
  else Measured_value_C = Measured_value_C;
	Measured_value_C=Measured_value_C*0.032;
  Measured_value_C=abs(Measured_value_C);
	
	Error_A = (float)(Measured_value_A-True_value)/True_value;
	Error_B = (float)(Measured_value_B-True_value)/True_value;
	Error_C = (float)(Measured_value_C-True_value)/True_value;
	
	Pgain_A=-Error_A/(1.0+Error_A);
	Pgain_B=-Error_B/(1.0+Error_B);
	Pgain_C=-Error_C/(1.0+Error_C);
	
	if(Pgain_A>=0) Pgain_A=(int)(Pgain_A*32768);
	else  Pgain_A=(65536+(int)Pgain_A*32768);

	if(Pgain_B>=0) Pgain_B=(int)(Pgain_B*32768);
	else  Pgain_B=(65536+(int)Pgain_B*32768);
	if(Pgain_C>=0) Pgain_C=(int)(Pgain_C*32768);
  else  Pgain_C=(65536+(int)Pgain_C*32768);
	
	array_temp[0]=(int)Pgain_A&0xFF;
	array_temp[1]=((int)Pgain_A>>8)&0xFF;
	MODIFY_EEP_W(Addr_Pgain_A,array_temp,2,0xA0);	
	HT7038_Write(w_PgainA,Pgain_A);
	HT7038_Write(w_QgainA,Pgain_A);//A���޹���������
	HT7038_Write(w_SgainA,Pgain_A);//A�����ڹ�������94
	
	array_temp[0]=(int)Pgain_B&0xFF;
	array_temp[1]=((int)Pgain_B>>8)&0xFF;
	MODIFY_EEP_W(Addr_Pgain_B,array_temp,2,0xA0);	
	HT7038_Write(w_PgainB,Pgain_B);
	HT7038_Write(w_QgainB,Pgain_B);
	HT7038_Write(w_SgainB,Pgain_B);
	
	array_temp[0]=(int)Pgain_C&0xFF;
	array_temp[1]=((int)Pgain_C>>8)&0xFF;
	MODIFY_EEP_W(Addr_Pgain_C,array_temp,2,0xA0);	
	HT7038_Write(w_PgainC,Pgain_C);
	HT7038_Write(w_QgainC,Pgain_C);
	HT7038_Write(w_SgainC,Pgain_C);
	
	HT7038_Write(0xc9,0x5b); ////�ر�SPIУ��Ĵ�����д����
	
}

void ERR_data_sent(unsigned char reason)
{
	unsigned char i,cs_temp;
	cs_temp = 0;
	Uart_prepare(1);  //��վ�쳣Ӧ��֡׼��
	UART_T_Buf[9] = 0x01;//���ݳ���
	UART_T_Buf[10] = reason;  //��ʮλΪԭ��
	for(i=0;i<11;i++)
	{
		cs_temp =  UART_T_Buf[i] + cs_temp;   //��һλΪУ����
	}
	UART_T_Buf[11] = cs_temp; 
	UART_T_Buf[12] =  0x16;
	//20150202���������޸�
	//	for(i=0;i<4;i++)
	//	put2char(0xFE);
	
//	for(i=0;i<13;i++)
//	put2char(UART_T_Buf[i]);
//	//RS485_Send_Data(UART_T_Buf,13);
		for(i=0;i<4;i++)
	{
	UART_S_Buf[i]=0xFE;
	}
		if(F_Dataval==1)
	{
		HAL_UART_Transmit(&huart3,(uint8_t*)UART_S_Buf,4,0xffff);
		HAL_UART_Transmit(&huart3,(uint8_t*)UART_T_Buf,13,0xffff);
		 //RS485_Send_Data(UART_S_Buf,4);
		 //RS485_Send_Data(UART_T_Buf,13);
	}
	if(F_Dataval1==1)
	{
		 //hongwai_Send_Data(UART_T_Buf,13);
	}
}



/************************************У׼��ȡ2022.4.28�¼�***********************/
//����ADֵ��ȡ
unsigned char  Read_DL_AD_Value(unsigned char xiangwei_tmp,unsigned char dian_tmp)//xiangwei_tmp=DI2��dian_tmp=DI0
{
		unsigned char array_temp[8];
	  unsigned char lenth;
	
	if(xiangwei_tmp==1)//A��λ
	{
		if(dian_tmp==0)//0��
		{
		      DectoBCD(array_temp, CurA_cal_tmp[0],3);  //ʮ����ת���ɶ�����ת����ֵ
					lenth = 3;  //���ݳ���
		}
		else if(dian_tmp==1)
		{
		      DectoBCD(array_temp, CurA_cal_tmp[1],3);  //ʮ����ת���ɶ�����ת����ֵ
					lenth = 3;  //���ݳ���
		}

	}
	else if(xiangwei_tmp==2)//B��λ
	{
		if(dian_tmp==0)//0��
		{
		      DectoBCD(array_temp, CurB_cal_tmp[0],3);  //ʮ����ת���ɶ�����ת����ֵ
					lenth = 3;  //���ݳ���
		}
		else if(dian_tmp==1)
		{
		      DectoBCD(array_temp, CurB_cal_tmp[1],3);  //ʮ����ת���ɶ�����ת����ֵ
					lenth = 3;  //���ݳ���
		}

	}
	else if(xiangwei_tmp==3)//C��λ
	{
		if(dian_tmp==0)//0��
		{
		      DectoBCD(array_temp, CurC_cal_tmp[0],3);  //ʮ����ת���ɶ�����ת����ֵ
					lenth = 3;  //���ݳ���
		}
		else if(dian_tmp==1)
		{
		      DectoBCD(array_temp, CurC_cal_tmp[1],3);  //ʮ����ת���ɶ�����ת����ֵ
					lenth = 3;  //���ݳ���
		}

	}

	else 
	{
		ERR_data_sent(ERR_NO_REQUEST);  //û��Ӧ
		return 1;
	}
	Read_response(lenth,array_temp);    //�������ݳ����ټ�������
	return 0;
}



//����б��ֵ��ȡ
unsigned char  Read_DL_XL_Value(unsigned char xiangwei_tmp,unsigned char dian_tmp)//xiangwei_tmp=DI2��dian_tmp=DI0
{
		unsigned char array_temp[8];
	  unsigned char lenth;
	
	if(xiangwei_tmp==1)//A��λ
	{
		if(dian_tmp==0)//0��
		{
		      DectoBCD(array_temp, I1_A_slope[0],3);  //ʮ����ת���ɶ�����ת����ֵ

					lenth = 3;  //���ݳ���
		}
		else if(dian_tmp==1)
		{
		      DectoBCD(array_temp, I1_A_slope[1],3);  //ʮ����ת���ɶ�����ת����ֵ
					lenth = 3;  //���ݳ���
		}

	}
	else if(xiangwei_tmp==2)//B��λ
	{
		if(dian_tmp==0)//0��
		{
		      DectoBCD(array_temp, I1_B_slope[0],3);  //ʮ����ת���ɶ�����ת����ֵ
					lenth = 3;  //���ݳ���
		}
		else if(dian_tmp==1)
		{
		      DectoBCD(array_temp, I1_B_slope[1],3);  //ʮ����ת���ɶ�����ת����ֵ
					lenth = 3;  //���ݳ���
		}

	}
	else if(xiangwei_tmp==3)//C��λ
	{
		if(dian_tmp==0)//0��
		{
		      DectoBCD(array_temp, I1_C_slope[0],3);  //ʮ����ת���ɶ�����ת����ֵ
					lenth = 3;  //���ݳ���
		}
		else if(dian_tmp==1)
		{
		      DectoBCD(array_temp, I1_C_slope[1],3);  //ʮ����ת���ɶ�����ת����ֵ
					lenth = 3;  //���ݳ���
		}

	}

	else 
	{
		ERR_data_sent(ERR_NO_REQUEST);  //û��Ӧ
		return 1;
	}
	Read_response(lenth,array_temp);    //�������ݳ����ټ�������
	return 0;
}
//����ѹб��
unsigned char  Read_DY_XL_Value(unsigned char xiangwei_tmp)//xiangwei_tmp=DI2
{
		unsigned char array_temp[8];
	  unsigned char lenth;
	
	if(xiangwei_tmp==1)//A��λ
	{
		
		      DectoBCD(array_temp, V1_slope[0],3);  //ʮ����ת���ɶ�����ת����ֵ
					lenth = 3;  //���ݳ���

	}
	else if(xiangwei_tmp==2)//B��λ
	{
		
		      DectoBCD(array_temp, V1_slope[1],3);  //ʮ����ת���ɶ�����ת����ֵ
					lenth = 3;  //���ݳ���
	}
	else if(xiangwei_tmp==3)//C��λ
	{
		
		      DectoBCD(array_temp, V1_slope[2],3);  //ʮ����ת���ɶ�����ת����ֵ
					lenth = 3;  //���ݳ���
	}

	else 
	{
		ERR_data_sent(ERR_NO_REQUEST);  //û��Ӧ
		return 1;
	}
	Read_response(lenth,array_temp);    //�������ݳ����ټ�������
	return 0;
}


//��©��б��
unsigned char  Read_LD_XL_Value()//
{
		unsigned char array_temp[8];
	  unsigned char lenth;
	

		      DectoBCD(array_temp, L1_slope,3);  //ʮ����ת���ɶ�����ת����ֵ
					lenth = 3;  //���ݳ���

	
	Read_response(lenth,array_temp);    //�������ݳ����ټ�������
	return 0;
}


/************************************˲��У׼��ȡ***********************/
//˲��ADֵ��ȡ
unsigned char  Read_SD_AD_Value(unsigned char fact_tmp,unsigned char lenth)//fact_tmpΪDI0����ʾ�ڼ�����
{
		unsigned char array_temp[8];
	if((fact_tmp>=0)&&(fact_tmp<=4))  
	{
		if(Type_Cur==0)
		{
			if(fact_tmp==0)
			{
					DectoBCD(array_temp,DLS_Cur_IV_AD_value[0],3);  //ʮ����ת���ɶ�����ת����ֵ
					lenth = 3;  //���ݳ���
			}
			if(fact_tmp==1)
			{
					DectoBCD(array_temp,DLS_Cur_IV_AD_value[1],3);  //ʮ����ת���ɶ�����ת����ֵ
					lenth = 3;  //���ݳ���
			}
			if(fact_tmp==2)
			{
					DectoBCD(array_temp,DLS_Cur_IV_AD_value[2],3);  //ʮ����ת���ɶ�����ת����ֵ
					lenth = 3;  //���ݳ���
			}
			if(fact_tmp==3)
			{
					DectoBCD(array_temp,DLS_Cur_IV_AD_value[3],3);  //ʮ����ת���ɶ�����ת����ֵ
					lenth = 3;  //���ݳ���
			}
			if(fact_tmp==4)
			{
					DectoBCD(array_temp,DLS_Cur_IV_AD_value[4],3);  //ʮ����ת���ɶ�����ת����ֵ
					lenth = 3;  //���ݳ���
			}
		}
		if(Type_Cur==1)
		{
			if(fact_tmp==0)
			{
					DectoBCD(array_temp,DLS_Cur_I_AD_value[0],3);  //ʮ����ת���ɶ�����ת����ֵ
					lenth = 3;  //���ݳ���
			}
			if(fact_tmp==1)
			{
					DectoBCD(array_temp,DLS_Cur_I_AD_value[1],3);  //ʮ����ת���ɶ�����ת����ֵ
					lenth = 3;  //���ݳ���
			}
			if(fact_tmp==2)
			{
					DectoBCD(array_temp,DLS_Cur_I_AD_value[2],3);  //ʮ����ת���ɶ�����ת����ֵ
					lenth = 3;  //���ݳ���
			}
			if(fact_tmp==3)
			{
					DectoBCD(array_temp,DLS_Cur_I_AD_value[3],3);  //ʮ����ת���ɶ�����ת����ֵ
					lenth = 3;  //���ݳ���
			}
			if(fact_tmp==4)
			{
					DectoBCD(array_temp,DLS_Cur_I_AD_value[4],3);  //ʮ����ת���ɶ�����ת����ֵ
					lenth = 3;  //���ݳ���
			}
		}
		if(Type_Cur==2)
		{
			if(fact_tmp==0)
			{
					DectoBCD(array_temp,DLS_Cur_II_AD_value[0],3);  //ʮ����ת���ɶ�����ת����ֵ
					lenth = 3;  //���ݳ���
			}
			if(fact_tmp==1)
			{
					DectoBCD(array_temp,DLS_Cur_II_AD_value[1],3);  //ʮ����ת���ɶ�����ת����ֵ
					lenth = 3;  //���ݳ���
			}
			if(fact_tmp==2)
			{
					DectoBCD(array_temp,DLS_Cur_II_AD_value[2],3);  //ʮ����ת���ɶ�����ת����ֵ
					lenth = 3;  //���ݳ���
			}
			if(fact_tmp==3)
			{
					DectoBCD(array_temp,DLS_Cur_II_AD_value[3],3);  //ʮ����ת���ɶ�����ת����ֵ
					lenth = 3;  //���ݳ���
			}
			if(fact_tmp==4)
			{
					DectoBCD(array_temp,DLS_Cur_II_AD_value[4],3);  //ʮ����ת���ɶ�����ת����ֵ
					lenth = 3;  //���ݳ���
			}
		}
		if(Type_Cur==3)
		{
			if(fact_tmp==0)
			{
					DectoBCD(array_temp,DLS_Cur_III_AD_value[0],3);  //ʮ����ת���ɶ�����ת����ֵ
					lenth = 3;  //���ݳ���
			}
			if(fact_tmp==1)
			{
					DectoBCD(array_temp,DLS_Cur_III_AD_value[1],3);  //ʮ����ת���ɶ�����ת����ֵ
					lenth = 3;  //���ݳ���
			}
			if(fact_tmp==2)
			{
					DectoBCD(array_temp,DLS_Cur_III_AD_value[2],3);  //ʮ����ת���ɶ�����ת����ֵ
					lenth = 3;  //���ݳ���
			}
			if(fact_tmp==3)
			{
					DectoBCD(array_temp,DLS_Cur_III_AD_value[3],3);  //ʮ����ת���ɶ�����ת����ֵ
					lenth = 3;  //���ݳ���
			}
			if(fact_tmp==4)
			{
					DectoBCD(array_temp,DLS_Cur_III_AD_value[4],3);  //ʮ����ת���ɶ�����ת����ֵ
					lenth = 3;  //���ݳ���
			}
		}

	}
	else 
	{
		ERR_data_sent(ERR_NO_REQUEST);  //û��Ӧ
		return 1;
	}
	Read_response(lenth,array_temp);    //�������ݳ����ټ�������
	return 0;
}

//˲��б��ֵ��ȡ
unsigned char  Read_SD_Slope_Value(unsigned char fact_tmp,unsigned char lenth)//fact_tmpΪDI0����ʾ�ڼ�����
{
		unsigned char array_temp[8];
	if((fact_tmp>=0)&&(fact_tmp<=4))  
	{
		if(Type_Cur==0)
		{
			if(fact_tmp==0)
			{
					DectoBCD(array_temp,DLS_Cur_IV_slope[0],3);  //ʮ����ת���ɶ�����ת����ֵ
					lenth = 3;  //���ݳ���
			}
			if(fact_tmp==1)
			{
					DectoBCD(array_temp,DLS_Cur_IV_slope[1],3);  //ʮ����ת���ɶ�����ת����ֵ
					lenth = 3;  //���ݳ���
			}
			if(fact_tmp==2)
			{
					DectoBCD(array_temp,DLS_Cur_IV_slope[2],3);  //ʮ����ת���ɶ�����ת����ֵ
					lenth = 3;  //���ݳ���
			}
			if(fact_tmp==3)
			{
					DectoBCD(array_temp,DLS_Cur_IV_slope[3],3);  //ʮ����ת���ɶ�����ת����ֵ
					lenth = 3;  //���ݳ���
			}
			if(fact_tmp==4)
			{
					DectoBCD(array_temp,DLS_Cur_IV_slope[4],3);  //ʮ����ת���ɶ�����ת����ֵ
					lenth = 3;  //���ݳ���
			}
		}
		if(Type_Cur==1)
		{
			if(fact_tmp==0)
			{
					DectoBCD(array_temp,DLS_Cur_I_slope[0],3);  //ʮ����ת���ɶ�����ת����ֵ
					lenth = 3;  //���ݳ���
			}
			if(fact_tmp==1)
			{
					DectoBCD(array_temp,DLS_Cur_I_slope[1],3);  //ʮ����ת���ɶ�����ת����ֵ
					lenth = 3;  //���ݳ���
			}
			if(fact_tmp==2)
			{
					DectoBCD(array_temp,DLS_Cur_I_slope[2],3);  //ʮ����ת���ɶ�����ת����ֵ
					lenth = 3;  //���ݳ���
			}
			if(fact_tmp==3)
			{
					DectoBCD(array_temp,DLS_Cur_I_slope[3],3);  //ʮ����ת���ɶ�����ת����ֵ
					lenth = 3;  //���ݳ���
			}
			if(fact_tmp==4)
			{
					DectoBCD(array_temp,DLS_Cur_I_slope[4],3);  //ʮ����ת���ɶ�����ת����ֵ
					lenth = 3;  //���ݳ���
			}
		}
		if(Type_Cur==2)
		{
			if(fact_tmp==0)
			{
					DectoBCD(array_temp,DLS_Cur_II_slope[0],3);  //ʮ����ת���ɶ�����ת����ֵ
					lenth = 3;  //���ݳ���
			}
			if(fact_tmp==1)
			{
					DectoBCD(array_temp,DLS_Cur_II_slope[1],3);  //ʮ����ת���ɶ�����ת����ֵ
					lenth = 3;  //���ݳ���
			}
			if(fact_tmp==2)
			{
					DectoBCD(array_temp,DLS_Cur_II_slope[2],3);  //ʮ����ת���ɶ�����ת����ֵ
					lenth = 3;  //���ݳ���
			}
			if(fact_tmp==3)
			{
					DectoBCD(array_temp,DLS_Cur_II_slope[3],3);  //ʮ����ת���ɶ�����ת����ֵ
					lenth = 3;  //���ݳ���
			}
			if(fact_tmp==4)
			{
					DectoBCD(array_temp,DLS_Cur_II_slope[4],3);  //ʮ����ת���ɶ�����ת����ֵ
					lenth = 3;  //���ݳ���
			}
		}
		if(Type_Cur==3)
		{
			if(fact_tmp==0)
			{
					DectoBCD(array_temp,DLS_Cur_III_slope[0],3);  //ʮ����ת���ɶ�����ת����ֵ
					lenth = 3;  //���ݳ���
			}
			if(fact_tmp==1)
			{
					DectoBCD(array_temp,DLS_Cur_III_slope[1],3);  //ʮ����ת���ɶ�����ת����ֵ
					lenth = 3;  //���ݳ���
			}
			if(fact_tmp==2)
			{
					DectoBCD(array_temp,DLS_Cur_III_slope[2],3);  //ʮ����ת���ɶ�����ת����ֵ
					lenth = 3;  //���ݳ���
			}
			if(fact_tmp==3)
			{
					DectoBCD(array_temp,DLS_Cur_III_slope[3],3);  //ʮ����ת���ɶ�����ת����ֵ
					lenth = 3;  //���ݳ���
			}
			if(fact_tmp==4)
			{
					DectoBCD(array_temp,DLS_Cur_III_slope[4],3);  //ʮ����ת���ɶ�����ת����ֵ
					lenth = 3;  //���ݳ���
			}
		}

	}
	else 
	{
		ERR_data_sent(ERR_NO_REQUEST);  //û��Ӧ
		return 1;
	}
	Read_response(lenth,array_temp);    //�������ݳ����ټ�������
	return 0;
}

//˲������ֵ��ȡ
unsigned char  Read_SD_Value(unsigned char fact_tmp,unsigned char lenth)//fact_tmpΪDI0����ʾ�ڼ�����
{
		unsigned char array_temp[8];
	if((fact_tmp>=0)&&(fact_tmp<=4))  
	{
		if(Type_Cur==0)
		{
			if(fact_tmp==0)
			{
					DectoBCD(array_temp,DLS_Cur_III_Value[0],3);  //ʮ����ת���ɶ�����ת����ֵ
					lenth = 3;  //���ݳ���
			}
			if(fact_tmp==1)
			{
					DectoBCD(array_temp,DLS_Cur_III_Value[1],3);  //ʮ����ת���ɶ�����ת����ֵ
					lenth = 3;  //���ݳ���
			}
			if(fact_tmp==2)
			{
					DectoBCD(array_temp,DLS_Cur_III_Value[2],3);  //ʮ����ת���ɶ�����ת����ֵ
					lenth = 3;  //���ݳ���
			}
			if(fact_tmp==3)
			{
					DectoBCD(array_temp,DLS_Cur_III_Value[3],3);  //ʮ����ת���ɶ�����ת����ֵ
					lenth = 3;  //���ݳ���
			}
			if(fact_tmp==4)
			{
					DectoBCD(array_temp,DLS_Cur_III_Value[4],3);  //ʮ����ת���ɶ�����ת����ֵ
					lenth = 3;  //���ݳ���
			}
		}
		if(Type_Cur==1)
		{
			if(fact_tmp==0)
			{
					DectoBCD(array_temp,DLS_Cur_I_Value[0],3);  //ʮ����ת���ɶ�����ת����ֵ
					lenth = 3;  //���ݳ���
			}
			if(fact_tmp==1)
			{
					DectoBCD(array_temp,DLS_Cur_I_Value[1],3);  //ʮ����ת���ɶ�����ת����ֵ
					lenth = 3;  //���ݳ���
			}
			if(fact_tmp==2)
			{
					DectoBCD(array_temp,DLS_Cur_I_Value[2],3);  //ʮ����ת���ɶ�����ת����ֵ
					lenth = 3;  //���ݳ���
			}
			if(fact_tmp==3)
			{
					DectoBCD(array_temp,DLS_Cur_I_Value[3],3);  //ʮ����ת���ɶ�����ת����ֵ
					lenth = 3;  //���ݳ���
			}
			if(fact_tmp==4)
			{
					DectoBCD(array_temp,DLS_Cur_I_Value[4],3);  //ʮ����ת���ɶ�����ת����ֵ
					lenth = 3;  //���ݳ���
			}
		}
		if(Type_Cur==2)
		{
			if(fact_tmp==0)
			{
					DectoBCD(array_temp,DLS_Cur_II_Value[0],3);  //ʮ����ת���ɶ�����ת����ֵ
					lenth = 3;  //���ݳ���
			}
			if(fact_tmp==1)
			{
					DectoBCD(array_temp,DLS_Cur_II_Value[1],3);  //ʮ����ת���ɶ�����ת����ֵ
					lenth = 3;  //���ݳ���
			}
			if(fact_tmp==2)
			{
					DectoBCD(array_temp,DLS_Cur_II_Value[2],3);  //ʮ����ת���ɶ�����ת����ֵ
					lenth = 3;  //���ݳ���
			}
			if(fact_tmp==3)
			{
					DectoBCD(array_temp,DLS_Cur_II_Value[3],3);  //ʮ����ת���ɶ�����ת����ֵ
					lenth = 3;  //���ݳ���
			}
			if(fact_tmp==4)
			{
					DectoBCD(array_temp,DLS_Cur_II_Value[4],3);  //ʮ����ת���ɶ�����ת����ֵ
					lenth = 3;  //���ݳ���
			}
		}
		if(Type_Cur==3)
		{
			if(fact_tmp==0)
			{
					DectoBCD(array_temp,DLS_Cur_III_Value[0],3);  //ʮ����ת���ɶ�����ת����ֵ
					lenth = 3;  //���ݳ���
			}
			if(fact_tmp==1)
			{
					DectoBCD(array_temp,DLS_Cur_III_Value[1],3);  //ʮ����ת���ɶ�����ת����ֵ
					lenth = 3;  //���ݳ���
			}
			if(fact_tmp==2)
			{
					DectoBCD(array_temp,DLS_Cur_III_Value[2],3);  //ʮ����ת���ɶ�����ת����ֵ
					lenth = 3;  //���ݳ���
			}
			if(fact_tmp==3)
			{
					DectoBCD(array_temp,DLS_Cur_III_Value[3],3);  //ʮ����ת���ɶ�����ת����ֵ
					lenth = 3;  //���ݳ���
			}
			if(fact_tmp==4)
			{
					DectoBCD(array_temp,DLS_Cur_III_Value[4],3);  //ʮ����ת���ɶ�����ת����ֵ
					lenth = 3;  //���ݳ���
			}
		}

	}
	else 
	{
		ERR_data_sent(ERR_NO_REQUEST);  //û��Ӧ
		return 1;
	}
	Read_response(lenth,array_temp);    //�������ݳ����ټ�������
	return 0;
}


/***************************************
	����ѹ  XXX.X  2  BCD  
***************************************/
unsigned char Read_variable_vol(unsigned char fact_tmp,unsigned char lenth)  //fact_tmpΪDI1
{
	unsigned char array_temp[8];
	if((fact_tmp>=1)&&(fact_tmp<=3))  //��ABC����ĳһ���ѹֵ
	{
		if(fact_tmp==1)
		{
			  DectoBCD(array_temp,(10*HT7038_buf[1]),2);  //ʮ����ת���ɶ�����ת���ɵ�ѹֵ
		    lenth = 2;  //���ݳ���
		}
		if(fact_tmp==2)
		{
				DectoBCD(array_temp,(10*HT7038_buf[2]),2);  //ʮ����ת���ɶ�����ת���ɵ�ѹֵ
		    lenth = 2;  //���ݳ���
		}
		if(fact_tmp==3)
		{
				DectoBCD(array_temp,(10*HT7038_buf[3]),2);  //ʮ����ת���ɶ�����ת���ɵ�ѹֵ
		    lenth = 2;  //���ݳ���
		}
	}
	else if(fact_tmp==0xFF)  //��������ѹֵ
	{
	  DectoBCD(&array_temp[0],(10*HT7038_buf[1]),2);
		DectoBCD(&array_temp[2],(10*HT7038_buf[2]),2);
		DectoBCD(&array_temp[4],(10*HT7038_buf[3]),2);
		lenth = 6;
	}
	else 
	{
		ERR_data_sent(ERR_NO_REQUEST);  //û��Ӧ
		return 1;
	}
	Read_response(lenth,array_temp);    //�������ݳ����ټ�������
	return 0;
}

/***************************************
	������  XXXXX.X  3  BCD  
***************************************/
unsigned char Read_variable_cur(unsigned char fact_tmp,unsigned char lenth)    //fact_tmpΪDI1
{
	unsigned char array_temp[12];
	if((fact_tmp>=1)&&(fact_tmp<=3))
	{
			if(fact_tmp==1)
		{
			DectoBCD(array_temp,(10*HT7038_buf[4]),3);
		  lenth = 3;
		}
		else if(fact_tmp==2)
		{
			DectoBCD(array_temp,(10*HT7038_buf[5]),3);
			lenth = 3;
		}
		else if(fact_tmp==3)
		{
			DectoBCD(array_temp,(10*HT7038_buf[6]),3);
			lenth = 3;
		}
		
	}
	else if(fact_tmp==0xFF)
	{
		DectoBCD(&array_temp[0],(10*HT7038_buf[4]),3);
		DectoBCD(&array_temp[3],(10*HT7038_buf[5]),3);
		DectoBCD(&array_temp[6],(10*HT7038_buf[6]),3);
		lenth = 9;
	}
	else 
	{
		ERR_data_sent(ERR_NO_REQUEST);
		return 1;
	}
	Read_response(lenth,array_temp);    //�������ݳ����ټ�������
	return 0;
}
/***************************************
	���й�����  XXXXX.X  3  BCD  
***************************************/
unsigned char Read_variable_Power(unsigned char fact_tmp,unsigned char lenth)    //fact_tmpΪDI1
{
	unsigned char array_temp[12];
	if((fact_tmp>=0)&&(fact_tmp<=3))
	{
		if(fact_tmp==0)
		{
      HT7038_buf[10]=abs(HT7038_buf[10])*10;
			DectoBCD(array_temp,(HT7038_buf[10]),3);//�������й�����
		  lenth = 3;
		}
		else if(fact_tmp==1)
		{
			HT7038_buf[7]=abs(HT7038_buf[7])*10;
			DectoBCD(array_temp,(HT7038_buf[7]),3);//A��˲ʱ�й�����
		  lenth = 3;
		}
		else if(fact_tmp==2)
		{
			 HT7038_buf[8]=abs(HT7038_buf[8])*10;
			DectoBCD(array_temp,(HT7038_buf[8]),3);//B��˲ʱ�й�����
			lenth = 3;
		}
		else if(fact_tmp==3)
		{
			HT7038_buf[9]=abs(HT7038_buf[9])*10;
			DectoBCD(array_temp,HT7038_buf[9],3);//C��˲ʱ�й�����
			lenth = 3;
		}

		
	}
	else if(fact_tmp==0xFF)
	{
		  HT7038_buf[10]=abs(HT7038_buf[10])*10;
			DectoBCD(array_temp,(HT7038_buf[10]),3);//�����ܹ���
      HT7038_buf[7]=abs(HT7038_buf[7])*10;
			DectoBCD(&array_temp[3],(HT7038_buf[7]),3);//A��˲ʱ����
		  HT7038_buf[8]=abs(HT7038_buf[8])*10;
			DectoBCD(&array_temp[6],(HT7038_buf[8]),3);//B��˲ʱ����
			HT7038_buf[9]=abs(HT7038_buf[9])*10;
			DectoBCD(&array_temp[9],HT7038_buf[9],3);//C��˲ʱ����
		  lenth = 12;
	}
	else 
	{
		ERR_data_sent(ERR_NO_REQUEST);
		return 1;
	}
	Read_response(lenth,array_temp);    //�������ݳ����ټ�������
	return 0;
}
unsigned char Read_reactive_Power(unsigned char fact_tmp,unsigned char lenth)    //fact_tmpΪDI1
{
	unsigned char array_temp[12];
	if((fact_tmp>=0)&&(fact_tmp<=3))
	{
		if(fact_tmp==0)
		{
      HT7038_buf[22]=abs(HT7038_buf[22])*10;
			DectoBCD(array_temp,(HT7038_buf[22]),3);//�������޹�����
		  lenth = 3;
		}
		else if(fact_tmp==1)
		{
			  HT7038_buf[19]=abs(HT7038_buf[19])*10;
			DectoBCD(array_temp,(HT7038_buf[19]),3);//A��˲ʱ�޹�����
		  lenth = 3;
		}
		else if(fact_tmp==2)
		{
			 HT7038_buf[20]=abs(HT7038_buf[20])*10;
			DectoBCD(array_temp,(HT7038_buf[20]),3);//B��˲ʱ�޹�����
			lenth = 3;
		}
		else if(fact_tmp==3)
		{
			HT7038_buf[21]=abs(HT7038_buf[21])*10;
			DectoBCD(array_temp,HT7038_buf[21],3);//C��˲ʱ�޹�����
			lenth = 3;
		}
	}
	else if(fact_tmp==0xFF)
	{
		  HT7038_buf[22]=abs(HT7038_buf[22]);
			DectoBCD(array_temp,(HT7038_buf[22]*10),3);//�������޹�����
      HT7038_buf[19]=abs(HT7038_buf[19]);
			DectoBCD(&array_temp[3],(HT7038_buf[19]*10),3);//A��˲ʱ�޹�����
		  HT7038_buf[20]=abs(HT7038_buf[20]);
			DectoBCD(&array_temp[6],(HT7038_buf[20]*10),3);//B��˲ʱ�޹�����
			HT7038_buf[21]=abs(HT7038_buf[21]);
			DectoBCD(&array_temp[9],HT7038_buf[21]*10,3);//C��˲ʱ�޹�����
		  lenth = 12;
	}
	else 
	{
		ERR_data_sent(ERR_NO_REQUEST);
		return 1;
	}
	Read_response(lenth,array_temp);    //�������ݳ����ټ�������
	return 0;
}
/***************************************
	����������  XXXXX.X  3  BCD  
***************************************/
unsigned char Read_factor_Power(unsigned char fact_tmp,unsigned char lenth)    //fact_tmpΪDI1
{
	unsigned char array_temp[12];
	if((fact_tmp>=0)&&(fact_tmp<=3))
	{
		if(fact_tmp==0)
		{
      HT7038_buf[14]=abs(HT7038_buf[14]);
			DectoBCD(array_temp,(HT7038_buf[14]),2);//�����ܹ�������
		  lenth = 2;
		}
		else if(fact_tmp==1)
		{
			HT7038_buf[11]=abs(HT7038_buf[11]);
			DectoBCD(array_temp,(HT7038_buf[11]),2);//A�๦������
		  lenth = 2;
		}
		else if(fact_tmp==2)
		{
			HT7038_buf[12]=abs(HT7038_buf[12]);
			DectoBCD(array_temp,(HT7038_buf[12]),2);//B�๦������
			lenth = 2;
		}
		else if(fact_tmp==3)
		{
			HT7038_buf[13]=abs(HT7038_buf[13]);
			DectoBCD(array_temp,(HT7038_buf[13]),2);//C�๦������
			lenth = 2;
		}

		
	}
	else if(fact_tmp==0xFF)
	{
		  HT7038_buf[14]=abs(HT7038_buf[14]);
			DectoBCD(array_temp,(HT7038_buf[14]),2);//�����ܹ�������
			HT7038_buf[11]=abs(HT7038_buf[11]);
			DectoBCD(&array_temp[2],(HT7038_buf[11]),2);//A�๦������
			HT7038_buf[12]=abs(HT7038_buf[12]);
			DectoBCD(&array_temp[4],(HT7038_buf[12]),2);//B�๦������
			HT7038_buf[13]=abs(HT7038_buf[13]);
			DectoBCD(&array_temp[6],(HT7038_buf[13]),2);//C�๦������
		  lenth = 8;
	}
	else 
	{
		ERR_data_sent(ERR_NO_REQUEST);
		return 1;
	}
	Read_response(lenth,array_temp);    //�������ݳ����ټ�������
	return 0;
}/***************************************
	�������� 
***************************************/
unsigned char Energy_reset()
{
	unsigned char array_temp[4];
	signed int tem;
	array_temp[0]=0x00;
	array_temp[1]=0x00;
	array_temp[2]=0x00;
	array_temp[3]=0x00;

	
	MODIFY_EEP_W(Addr_energy_active_he,array_temp,4,0xA0);	
	MODIFY_EEP_W(Addr_energy_active_A,array_temp,4,0xA0);	
	MODIFY_EEP_W(Addr_energy_active_C,array_temp,4,0xA0);	
	MODIFY_EEP_W(Addr_energy_reactive_he,array_temp,4,0xA0);	
	Accumulate_energy_shangci_active_he=0;
	Accumulate_energy_shangci_active_A=0;
  Accumulate_energy_shangci_active_C=0;
	Accumulate_energy_shangci_reactive_he=0;
	
	Accumulate_energy_dangqian_active_he=0;
	Accumulate_energy_dangqian_active_A=0;
  Accumulate_energy_dangqian_active_C=0;
	Accumulate_energy_dangqian_reactive_he=0;
	
	  HT7038_Write(0xC9,0x5A); ////ѡ��У��Ĵ���//У������дʹ��
	
		HT7038_Write(w_EMUCfg,0xF884);// ������Ϊ��������
		HT7038_Write(0xc6,0x5b); ////ʹ��SPI�����Ĵ���������
		delay_ms(10);
			tem = HT7038_Read(rEpa)/3.2; //	A���й�����
	    tem = HT7038_Read(rEpc)/3.2; // C���й�����
	   HT7038_buf[18]= HT7038_Read(rEpt)/3.2; // �����й�����
			tem = HT7038_Read(rEqt)/3.2; //�����޹�����
			delay_ms(10);
		HT7038_Write(w_EMUCfg,0xF804);// ��һ�������������Ϊ������
			HT7038_Write(0xc9,0x5b); ////�ر�SPIУ��Ĵ�����д����

	
	delay_ms(1);
	
//	Read_active_energy(0,4);
//	Read_reactive_energy(0,4);
}
/***************************************
	��Ƶ��  XXXXX.X  3  BCD  
***************************************/
unsigned char Read_Frequency(unsigned char fact_tmp,unsigned char lenth)    //fact_tmpΪDI1
{
	unsigned char array_temp[12];
	  if(fact_tmp==0x00)//����Ƶ��xx.xx 2 Hz
		{
      HT7038_buf[31]=abs(HT7038_buf[31])*100;
			DectoBCD(array_temp,(HT7038_buf[31]),2);//
		  lenth = 2;
		}
		 else 
	  {
		  ERR_data_sent(ERR_NO_REQUEST);
		  return 1;
	  }
     Read_response(lenth,array_temp);    //�������ݳ����ټ�������
	   return 0;
}
void Uart_data_propare(void)
{
	if(isfenzha==1)
	{
   Leak_Cur_uart=0; 
	}
	else
	{
   Leak_Cur_uart=Leak_Cur_disp; 
	}
}
/***************************************
	��ʣ�����  XX  1  BIN  /  XXXX  2  BCD  
***************************************/
unsigned char Read_variable_leak(unsigned char fact_tmp)
{
	unsigned char lenth,array_temp[5];
	//max_phase = 0x01;
	if(fact_tmp==0x00)   //00 ����ʣ����������
	{
		array_temp[0] = max_phase;
		lenth = 1;		
	}
	else if(fact_tmp==0x01)      //��ǰʣ�����ֵ
	{
//		Uart_data_propare();
//		DectoBCD(&array_temp[0],Leak_Cur_uart,2);
		DectoBCD(&array_temp[0],(leak_handle(Leak_Cur_disp_temp)),2);
		lenth = 2;
	}
	else if(fact_tmp==0xFF)   //   //��ǰʣ�����ֵ�������
	{
//		Uart_data_propare();
		array_temp[0] = max_phase;
		//array_temp[0] = 0x01;
//		DectoBCD(&array_temp[1],Leak_Cur_uart,2);
		DectoBCD(&array_temp[0],(leak_handle(Leak_Cur_disp_temp)),2);
		lenth = 3;
	}
	else 
	{
		ERR_data_sent(ERR_NO_REQUEST);
		return 1;
	}
	Read_response(lenth,array_temp);
	return 0;
}

/***************************************
	��ʣ�������λ    XXXX  2  BCD  
***************************************/
unsigned char Read_variable_leak_class(unsigned char fact_tmp,unsigned char lenth)
{
	unsigned char array_temp[5];
	if(fact_tmp==1)
	{
		DectoBCD(&array_temp[0],Leak_Class[D_LCur],2);
		lenth = 2;
	}
	else if(fact_tmp==2)
	{
		DectoBCD(&array_temp[0],Leak_limit_time_class[TH_LCur],2);
		lenth = 2;
	}
	
	else if(fact_tmp==0xff)
	{
		DectoBCD(&array_temp[0],Leak_Class[D_LCur],2);
		DectoBCD(&array_temp[2],Leak_limit_time_class[TH_LCur],2);
		lenth = 4;
	}
	else 
	{
		ERR_data_sent(ERR_NO_REQUEST);
		return 1;
	}
	Read_response(lenth,array_temp);
	return 0;
}
/***************************************
	������Ƶ�ʺ���ƽ������   
***************************************/
unsigned char Read_frequency_power(unsigned char fact_tmp,unsigned char lenth)  //fact_tmpΪDI0
{
	unsigned char array_temp[12];
	
		if(fact_tmp==0x02)//����Ƶ��xx.xx 2 Hz
		{
      HT7038_buf[31]=abs(HT7038_buf[31])*100;
			DectoBCD(array_temp,(HT7038_buf[31]),2);//
		  lenth = 2;
		}
		else if(fact_tmp==0x03)//һ�����й���ƽ������xx.xxxx 3 kW
		{
			//DectoBCD(array_temp,average_active_power*10,3);//
		  lenth = 3;
		}
		else if(fact_tmp==0x25)//һ�����޹���ƽ������xx.xxxx 3 kvar
		{
			//DectoBCD(array_temp,average_reactive_power*10,3);//
		  lenth = 3;
		}
	   else 
	  {
		  ERR_data_sent(ERR_NO_REQUEST);
		  return 1;
	  }
	  Read_response(lenth,array_temp);    //�������ݳ����ټ�������
	   return 0;
}
/***************************************
	������   XXXXXX  3  BCD  
***************************************/
unsigned char Read_active_energy(unsigned char fact_tmp,unsigned char lenth)    //fact_tmpΪDI1
{
	unsigned char array_temp[4];
	if(fact_tmp==0)
	{
			DectoBCD(array_temp,Accumulate_energy_dangqian_active_he/10,4);//�������й�����
			lenth = 4;
	}
	else 
	{
		ERR_data_sent(ERR_NO_REQUEST);
		return 1;
	}
	Read_response(lenth,array_temp);    //�������ݳ����ټ�������
	return 0;
}
/***************************************
	������   XXXXXX  3  BCD  
***************************************/
unsigned char Read_Power(unsigned char fact_tmp,unsigned char lenth) 
{
	unsigned char array_temp[6];
	if(fact_tmp==1)//���й�����
	{
		  HT7038_buf[10]=abs(HT7038_buf[10])*10;
			DectoBCD(array_temp,(HT7038_buf[10]),2);//�������й�����
		  lenth = 2;	
		
	}
	else if(fact_tmp==2)//���޹�����
	{
			HT7038_buf[22]=abs(HT7038_buf[22])*10;
			DectoBCD(array_temp,(HT7038_buf[22]),2);//�������޹�����
		  lenth = 2;
	}
	else if(fact_tmp==3)//�����ڹ���
	{
			 HT7038_buf[26]=abs(HT7038_buf[26])*10;
			DectoBCD(array_temp,(HT7038_buf[26]),2);//���������ڹ���
		  lenth = 2;
	}
	else if(fact_tmp==0xFF)//�����й���
	{
			HT7038_buf[10]=abs(HT7038_buf[10])*10;
			DectoBCD(&array_temp[0],(HT7038_buf[10]),2);//�������й�����
			HT7038_buf[22]=abs(HT7038_buf[22])*10;
			DectoBCD(&array_temp[2],(HT7038_buf[22]),2);//�������޹�����
		  HT7038_buf[26]=abs(HT7038_buf[26])*10;
			DectoBCD(&array_temp[4],(HT7038_buf[26]),2);//���������ڹ���
		  lenth = 6;
	}
	Read_response(lenth,array_temp);    //�������ݳ����ټ�������
	return 0;
}
/***************************************
	����������   XXXXXX  3  BCD  
***************************************/
unsigned char Read_Overload(unsigned char fact_tmp,unsigned char lenth) 
{
	unsigned char array_temp[4];
	unsigned int Ir,Tr;
	if(fact_tmp==1)
	{
			Ir=1.2*Delta_Cur;//���س���ʱ�ѿ۵�������ֵIr
		  DectoBCD(array_temp,Ir,1);
		  lenth = 1;
	}
	else if(fact_tmp==2)
	{
//      if(TH_Long_Cur==0) array_temp[0]=3;
//			else if(TH_Long_Cur==1) array_temp[0]=4;
//			else if(TH_Long_Cur==2) array_temp[0]=6;
//			else if(TH_Long_Cur==3) array_temp[0]=8;
//			else if(TH_Long_Cur==4) array_temp[0]=10;
//			else if(TH_Long_Cur==5) array_temp[0]=12;
//			else if(TH_Long_Cur==6) array_temp[0]=16;
//			else if(TH_Long_Cur==7) array_temp[0]=18;
		array_temp[0]=TH_Long_Cur+3;
			lenth = 2;//���س���ʱʱ���趨ֵtr
	}
	else if(fact_tmp==3)
	{
			;//���س���ʱ��������
	}
	else if(fact_tmp==0xFF)
	{
			Ir=1.2*Delta_Cur;//���س���ʱ�ѿ۵�������ֵIr
		  DectoBCD(array_temp,Ir,1);
//		  if(TH_Long_Cur==0) array_temp[1]=3;
//			else if(TH_Long_Cur==1) array_temp[1]=4;
//			else if(TH_Long_Cur==2) array_temp[1]=6;
//			else if(TH_Long_Cur==3) array_temp[1]=8;
//			else if(TH_Long_Cur==4) array_temp[1]=10;
//			else if(TH_Long_Cur==5) array_temp[1]=12;
//			else if(TH_Long_Cur==6) array_temp[1]=16;
//			else if(TH_Long_Cur==7) array_temp[1]=18;
		array_temp[1]=TH_Long_Cur+3;
		  lenth = 2;//���س���ʱ�����й�����
	}
	Read_response(lenth,array_temp);    //�������ݳ����ټ�������
	return 0;
}
/***************************************
	����������   XXXXXX  3  BCD  
***************************************/
unsigned char Read_Duanyan(unsigned char fact_tmp,unsigned char lenth) 
{
	unsigned char array_temp[4];
	if(fact_tmp==1)
	{
			if(D2_Cur==0)  	array_temp[0]=2;		//��·����ʱ�ѿ۵�������ֵIsd
			else if(D2_Cur==1) array_temp[0]=4;
			else if(D2_Cur==2) array_temp[0]=6;
			else if(D2_Cur==3) array_temp[0]=8;
			else if(D2_Cur==4) array_temp[0]=10;
			else if(D2_Cur==5) array_temp[0]=12;
				lenth=2;	
	}
	else if(fact_tmp==2)
	{
		  array_temp[0]=TH_DL;	 //��·����ʱʱ���趨ֵtsd"0.1s","0.2s","0.3s","0.4s","0.6S","0.8S","1S
		lenth=2;	
			
	}
	else if(fact_tmp==3)
	{
			;//��·����ʱ��������
	}
	else if(fact_tmp==0xFF)//��·����ʱ�����й�����
	{
				if(D2_Cur==0)  	array_temp[0]=2;		//��·����ʱ�ѿ۵�������ֵIsd
			else if(D2_Cur==1) array_temp[0]=4;
			else if(D2_Cur==2) array_temp[0]=6;
			else if(D2_Cur==3) array_temp[0]=8;
			else if(D2_Cur==4) array_temp[0]=10;
			else if(D2_Cur==5) array_temp[0]=12;
		    array_temp[1]=TH_DL;	 //��·����ʱʱ���趨ֵtsd"0.1s","0.2s","0.3s","0.4s","0.6S","0.8S","1S
			//	lenth=2;	;
	}
	Read_response(lenth,array_temp);    //�������ݳ����ټ�������
	return 0;
}
/***************************************
	��˲ʱ����   XXXXXX  3  BCD  
***************************************/
unsigned char Read_SD(unsigned char fact_tmp,unsigned char lenth) 
{
	unsigned char array_temp[4];//��·˲ʱ�ѿ۵�������ֵIitemp[4];
	if(fact_tmp==1)//��·˲ʱ�ѿ۵�������ֵIi
	{
		 // array_temp[0]=Delta_Cur;
		//	lenth=2;
	}
	else if(fact_tmp==2)
	{
			;//��·˲ʱ��������
	}
	else if(fact_tmp==0xFF)
	{
			;//��·˲ʱ������ز���
	}
	Read_response(lenth,array_temp);    //�������ݳ����ټ�������
	return 0;
}
/***************************************
	��©������   XXXXXX  3  BCD  
***************************************/
unsigned char Read_LD(unsigned char fact_tmp,unsigned char lenth) 
{
	unsigned char array_temp[4];
	if(fact_tmp==1)
	{
			;//©�籣������ֵ
	}
	else if(fact_tmp==2)
	{
			;//©�籣����ʱʱ��
	}
	else if(fact_tmp==0x04)
	{
			;//�ʣ�಻��������
	}
	else if(fact_tmp==0x08)
	{
			;//©�籣������
	}
	else if(fact_tmp==0xFF)
	{
			;//©�籣����ز���
	}
	Read_response(lenth,array_temp);    //�������ݳ����ټ�������
	return 0;
}
/***************************************
	���غ�բ��ʱʱ��   XXXXXX  3  BCD  
***************************************/
unsigned char Read_Chz_delaytime(unsigned char fact_tmp,unsigned char lenth) 
{
	unsigned char array_temp[4];
	if(fact_tmp==0)
	{
			;//�غ�բ��ʱʱ��
	}
	Read_response(lenth,array_temp);    //�������ݳ����ټ�������
	return 0;
}
/***************************************
	����ѹ����   XXXXXX  3  BCD  
***************************************/
unsigned char Read_vol_over(unsigned char fact_tmp,unsigned char lenth) 
{
	unsigned char array_temp[4];
	if(fact_tmp==1)
	{
			;//��ѹ��������ֵ
	}
	else if(fact_tmp==2)
	{
			;//��ѹ�غ�բ��ѹ
	}
	else if(fact_tmp==0x04)
	{
			;//��ѹ��բʱ��
	}
	else if(fact_tmp==0x08)
	{
			;//��ѹ��������
	}
	else if(fact_tmp==0xFF)
	{
			;//��ѹ�����й�����
	}
	Read_response(lenth,array_temp);    //�������ݳ����ټ�������
	return 0;
}
/***************************************
	��Ƿѹ����   XXXXXX  3  BCD  
***************************************/
unsigned char Read_vol_under(unsigned char fact_tmp,unsigned char lenth) 
{
	unsigned char array_temp[4];
	if(fact_tmp==1)
	{
			;//Ƿ��������ֵ
	}
	else if(fact_tmp==2)
	{
			;//Ƿѹ�غ�բ��ѹ
	}
	else if(fact_tmp==0x04)
	{
			;//Ƿѹ��բʱ��
	}
	else if(fact_tmp==0x08)
	{
			;//Ƿѹ��������
	}
	else if(fact_tmp==0xFF)
	{
			;//Ƿѹ�����й�����
	}
	Read_response(lenth,array_temp);    //�������ݳ����ټ�������
	return 0;
}
/***************************************
	��Ƿѹ����   XXXXXX  3  BCD  
***************************************/
unsigned char Read_phase_loss(unsigned char fact_tmp,unsigned char lenth) 
{
	unsigned char array_temp[4];
	if(fact_tmp==1)
	{
			;//ȱ�ౣ������
	}
	else if(fact_tmp==2)
	{
			;//ȱ�ౣ��ʱ��
	}
	else if(fact_tmp==0x03)
	{
			;//ȱ�ౣ������
	}
	else if(fact_tmp==0xFF)
	{
			;//ȱ�ౣ���й�����
	}
	Read_response(lenth,array_temp);    //�������ݳ����ټ�������
	return 0;
}
/***************************************
	�����򱣻�   XXXXXX  3  BCD  
***************************************/
unsigned char Read_phase_Error(unsigned char fact_tmp,unsigned char lenth) 
{
	unsigned char array_temp[4];
	if(fact_tmp==1)
	{
			;//���ౣ����ѹ
	}
	else if(fact_tmp==2)
	{
			;//���ౣ��ʱ��
	}
	else if(fact_tmp==0x04)
	{
			;//���ౣ������
	}
	else if(fact_tmp==0xFF)
	{
			;//���ౣ����ز���
	}
	Read_response(lenth,array_temp);    //�������ݳ����ټ�������
	return 0;
}
/***************************************
	���಻ƽ�Ᵽ��   XXXXXX  3  BCD  
***************************************/
unsigned char Read_phase_imblance(unsigned char fact_tmp,unsigned char lenth) 
{
	unsigned char array_temp[4];
	if(fact_tmp==1)
	{
			;//�಻ƽ���ѿ۵����趨ֵIumbal
	}
	else if(fact_tmp==2)
	{
			;//�಻ƽ����ʱʱ��Tumbal
	}
	else if(fact_tmp==0x04)
	{
			;//�಻ƽ�Ᵽ������
	}
	else if(fact_tmp==0xFF)
	{
			;//�಻ƽ�Ᵽ����ز���
	}
	Read_response(lenth,array_temp);    //�������ݳ����ټ�������
	return 0;
}
/***************************************
	��������¼   XXXXXX  3  BCD  
***************************************/
unsigned char Read_Protect_Record(unsigned char fact_tmp,unsigned char lenth) 
{
	unsigned char array_temp[4];
	if(fact_tmp==1)
	{
			;//����������բ����(���س���ʱ����·����ʱ����·˲ʱ)
	}
	else if(fact_tmp==2)
	{
			;//��ѹ������բ��������ѹ��Ƿѹ��ȱ�࣬���࣬�಻�Գƣ�
	}
	else if(fact_tmp==0x04)
	{
			;//ʣ�����������բ����
	}
		else if(fact_tmp==0x08)
	{
			;//�ֶ�������բ����
	}
		else if(fact_tmp==0x10)
	{
			;//ȱ�㱣����բ����
	}
		else if(fact_tmp==0x20)
	{
			;//������բ��������ʱ��Զ�̡�������
	}
		else if(fact_tmp==0x40)
	{
			;//����բ����
	}
	else if(fact_tmp==0xFF)
	{
			;//��բ������ز���
	}
	Read_response(lenth,array_temp);    //�������ݳ����ټ�������
	return 0;
}

/***************************************
	�����������ܴ���   XXXXXX  3  BCD  
***************************************/
unsigned char Read_num_dataclear(void)
{
	unsigned char lenth,array_temp[8];
	int Addr_factor;
	lenth = Lenth_clear_num;
	Addr_factor = Addr_clear_num;
	//EEPROM_R(array_temp,Addr_factor,lenth,0);	
	EEPROM_R(Addr_factor,array_temp,lenth,0xA0);	
	Read_response(lenth,array_temp);
	return 0;
}

/***************************************
	����բ����   XXXX  2  BCD  
	00 ����բ���� 01 ��������բ���� 02 ʣ�����������բ����  03 ����������բ���� 
	04 ��ѹ������բ���� 05 �ֶ�������բ����  06 ȱ�㱣����բ���� 07 ������բ��������ʱ��Զ�̡�������
	FF ��������

***************************************/
unsigned char Read_num_trip(unsigned char fact_tmp)
{
	unsigned char lenth,array_temp[20];
	int Addr_factor;
	Addr_factor = 0;
		if(fact_tmp == 0)
	{
		lenth = Lenth_trip_num;      //����բ����
		Addr_factor = Addr_trip_num;
	} 
	else if(fact_tmp == 1)         //ʣ�����������բ
	{
		lenth = Lenth_close_num;
		Addr_factor = Addr_close_num;
	}
	else if(fact_tmp == 2)         //ʣ�����������բ
	{
		lenth = Lenth_leak_num;
		Addr_factor = Addr_leak_num;
	}
	else if(fact_tmp == 3)         //���ر�����բ
	{
		lenth = Lenth_current_num;
		Addr_factor = Addr_current_num;   
	}
	else if(fact_tmp == 4)
	{
		lenth = Lenth_vol_num;
		Addr_factor = Addr_vol_num;   //��ѹ������բ����
	}
	else if(fact_tmp == 5)
	{
		lenth = Lenth_hand_num; 
		Addr_factor = Addr_hand_num;       //�ֶ�������բ
	}	
	else if(fact_tmp == 6)
	{
		lenth = Lenth_zero_num;
		Addr_factor = Addr_zero_num;  //ȱ�㱣��
	}	
	else if(fact_tmp == 7)
	{
		lenth = Lenth_test_num;
		Addr_factor  = Addr_test_num;  //������բ
	}
	
	else if(fact_tmp == 8)
	{
		lenth = Lenth_2D_num;
		Addr_factor  = Addr_2D_num;  //��·����ʱ
	}
	else if(fact_tmp == 9)
	{
		lenth = Lenth_3D_num;
		Addr_factor  = Addr_3D_num;  //��·˲ʱ
	}
	else if(fact_tmp == 0x0A)
	{
		lenth = Lenth_LD_up_num;
		Addr_factor  = Addr_leakover_num;  //Ƿѹ������բ����
	}
	else if(fact_tmp == 0x0B)
	{
		lenth = Lenth_AJ_sy_num;
		Addr_factor  = Addr_leakprotect_num;  //ȱ�ౣ����բ����
	}
	else if(fact_tmp == 0xFF)
	{
		lenth = 16;
		Addr_factor = Addr_trip_num;   //��բ�ܴ���
	}
	else
	{
		ERR_data_sent(ERR_NO_REQUEST);
		return 1;
	}
	array_temp[0] = 0;
	array_temp[1] = 0;	
	//EEPROM_R(array_temp,Addr_factor,lenth,0);
	EEPROM_R(Addr_factor,array_temp,lenth,0xA0);
	Read_response(lenth,array_temp);
	return 0;
}

/***************************************
	���˳�ʣ�������������   XXXX  2  BCD  
***************************************/
unsigned char Read_num_protectoff(void)
{
	unsigned char lenth,array_temp[8];
	int Addr_factor;
	Addr_factor = Addr_leakquit_num;
	lenth = 2;
	//EEPROM_R(array_temp,Addr_factor,lenth,0);
	EEPROM_R(Addr_factor,array_temp,lenth,0xA0);
	Read_response(lenth,array_temp);
	return 0;
}

/***************************************
	������������ʱ��   XXXXXXXX  4  BCD  
***************************************/
unsigned char Read_time_run(void)
{
	unsigned char i,lenth,array_temp[8];
	int Addr_factor;
	Addr_factor = Addr_protect_time;
	lenth = Lenth_protect_time;
	for(i=0;i<4;i++)
	{
		array_temp[i] = T_run_time_array[i];
	}
	//AT24C64_R(array_temp,Addr_factor,lenth);
	Read_response(lenth,array_temp);
	return 0;
}


void point_just(unsigned char fact,unsigned char *array_tmp)
{
	unsigned char month,day,array_temp_time[15],day_tmp,month_tmp;
	unsigned mon_daya_array[13]={31,31,28,31,30,31,30,31,31,30,31,30,31};  //1 3 5 7 8 10 12
	
	HAL_RTC_GetTime(&hrtc, &stimestructure, RTC_FORMAT_BCD);
	HAL_RTC_GetDate(&hrtc, &sdatestructure, RTC_FORMAT_BCD);
	tim_y = sdatestructure.Year;  //tim_yΪʮ���ƣ�Ҫת��������
	tim_m = sdatestructure.Month;
	tim_d = sdatestructure.Date;
	tim_h = stimestructure.Hours;
	tim_f = stimestructure.Minutes;
	tim_s = stimestructure.Seconds;

	month_tmp = tim_m;
	month = ((month_tmp>>4)&0x0F)*10 + month_tmp&0x0F;   //ʮ����
	day_tmp = tim_d;   //������0x31
	array_tmp[0] = tim_m;  
	day = (((day_tmp>>4)&0x03)*10) + (day_tmp&0x0F);   //ʮ����
	day = day - 1;           //ʮ���Ƽ�1
	fact = fact - 1;         //factΪDI0�����м�1����
	if(day>=fact)
	{
		array_tmp[1] = day-fact;   //array_tmp[0]����   array_tmp[1]���� 
	}
	else
	{
		if((month-1==0)||(month-1==2)||(month-1==4)||(month-1==6)||(month-1==9)||(month-1==11))
		{
			array_tmp[1] =  mon_daya_array[month] - (fact-day) - 1;
		}
		else
		{
			array_tmp[1] =  mon_daya_array[month] - (fact-day);
		}
	}
//	month_tmp = array_temp_time[1];
//	month = ((month_tmp>>4)&0x0F)*10 + month_tmp&0x0F;   //ʮ����
//	day_tmp = array_temp_time[2];   //������0x31
//	array_tmp[0] = array_temp_time[1];  
//	day = (((day_tmp>>4)&0x03)*10) + (day_tmp&0x0F);   //ʮ����
//	day = day - 1;           //ʮ���Ƽ�1
//	fact = fact - 1;         //factΪDI0�����м�1����
//	if(day>=fact)
//	{
//		array_tmp[1] = day-fact;   //array_tmp[0]����   array_tmp[1]���� 
//	}
//	else
//	{
//		array_tmp[1] =  mon_daya_array[month] - (fact-day) - 1;
//	}
}


/****************************************************
//��ʣ���������� 01--08   8 X 9 = 72 
��ʽ�� ʣ���������� ʣ�����ֵ      ���ֵ�ʱ��
			XX��1��     XXXX��2��  YYMMDDhhmmss��6��
			BIN          BCD
******************************************************/
void Read_max_leak(unsigned char fact_tmp)     //fact_tmpΪ�ϼ��յĲ���
{
	unsigned char lenth,array_tmp[3],array_temp[15];
	unsigned int Addr_factor;
	point_just(fact_tmp,array_tmp);           //fact_tmpΪ�ϼ��յĲ���
	Addr_factor = Addr_max_leak+array_tmp[1]*Lenth_max_leak;
	lenth = Lenth_max_leak;
	EEPROM_R(Addr_factor,array_temp,lenth,0xA0);
	Read_response(lenth,array_temp);
}
/****************************************************
////����ѹ���ֵ 01--30   30X 8 = 240
��ʽ�� ��ѹֵ	     ���ֵ�ʱ��
	XXX.X(2)	2    YYMMDDhhmmss��6��
		BCD
******************************************************/
void Read_max_vol(unsigned char tmp_fact,unsigned char fact_tmp)
{
	unsigned char lenth,array_tmp[3],array_temp[15];
	unsigned int Addr_factor;
	point_just(fact_tmp,array_tmp);
	Addr_factor = 0;
	if(tmp_fact==1) Addr_factor = Addr_max_Avol;
	if(tmp_fact==2) Addr_factor = Addr_max_Bvol;
	if(tmp_fact==3) Addr_factor = Addr_max_Cvol;  //ȷ������һ��

	
	lenth = Lenth_max_Avol;	
	Addr_factor += (array_tmp[1]<<3);
	EEPROM_R(Addr_factor,array_temp,lenth,0xA0);
	Read_response(lenth,array_temp);
}

/****************************************************
//���������ֵ 01--08   8 X 9 = 72
��ʽ�� ����ֵ	     ���ֵ�ʱ��
	XXXXX.X��3��   YYMMDDhhmmss��6��
		BCD
******************************************************/
void Read_max_cur(unsigned char tmp_fact,unsigned char fact_tmp)
{
	unsigned char lenth,array_tmp[3],array_temp[15];
	unsigned int Addr_factor;
	point_just(fact_tmp,array_tmp);  //�ǵڼ���
	Addr_factor = 0;
	if(tmp_fact==4) Addr_factor = Addr_max_Acur;
	if(tmp_fact==5) Addr_factor = Addr_max_Bcur;
	if(tmp_fact==6) Addr_factor = Addr_max_Ccur;
	lenth = Lenth_max_Acur;
	Addr_factor += (array_tmp[1]*9);  //array_tmp1Ϊ�ϼ��յĲ���
	EEPROM_R(Addr_factor,array_temp,lenth,0xA0);
	Read_response(lenth,array_temp);
}
//��ʣ��������ֵ��Сֵ  
/****************************************************
//��ʣ���������� 01--30  30X 9 = 270 
��ʽ�� ʣ���������� ʣ�����ֵ      ���ֵ�ʱ��
			XX��1��     XXXX��2��  YYMMDDhhmmss��6��
			BIN          BCD
******************************************************/
void Read_max_min_leak(unsigned char fact_tmp)
{
	unsigned char lenth,array_tmp[3],array_temp[15];
	unsigned int Addr_factor;
	point_just(fact_tmp,array_tmp);
	Addr_factor = 0;
	Addr_factor = Addr_min_leak+array_tmp[1]*Lenth_min_leak;
	lenth = Lenth_min_leak;
  EEPROM_R(Addr_factor,array_temp,lenth,0xA0);
	Read_response(lenth,array_temp);
}

//����ѹ��Сֵ����Сֵ Addr_min_Avol
/****************************************************
////����ѹ��Сֵ 01--30   30 X 8 = 240
��ʽ�� ��ѹֵ	     ���ֵ�ʱ��
	XXX.X(2)	2    YYMMDDhhmmss��6��
		BCD
******************************************************/
void Read_max_min_vol(unsigned char tmp_fact,unsigned char fact_tmp)
{
	unsigned char lenth,array_tmp[3],array_temp[15];
	unsigned int Addr_factor;
	point_just(fact_tmp,array_tmp);
	Addr_factor = 0;
	if(tmp_fact==1) Addr_factor = Addr_min_Avol;
	if(tmp_fact==2) Addr_factor = Addr_min_Bvol;
	if(tmp_fact==3) Addr_factor = Addr_min_Cvol;
	lenth = Lenth_min_Avol;	
	Addr_factor += (array_tmp[1]<<3);
	EEPROM_R(Addr_factor,array_temp,lenth,0xA0);
	Read_response(lenth,array_temp);
}

//��������Сֵ  Addr_min_Acur
/****************************************************
//��������Сֵ 01--30   30 X 9 = 270
��ʽ�� ����ֵ	     ���ֵ�ʱ��
	XXXXX.X��3��   YYMMDDhhmmss��6��
		BCD
******************************************************/
void Read_max_min_cur(unsigned char tmp_fact,unsigned char fact_tmp)
{
	unsigned char lenth,array_tmp[3],array_temp[15];
	unsigned int Addr_factor;
	point_just(fact_tmp,array_tmp);
	Addr_factor = 0;
	if(tmp_fact==4) Addr_factor = Addr_min_Acur;
	if(tmp_fact==5) Addr_factor = Addr_min_Bcur;
	if(tmp_fact==6) Addr_factor = Addr_min_Ccur;
	fact_tmp = fact_tmp - 1;
	lenth = Lenth_min_Acur;
	Addr_factor += (array_tmp[1]*9);
	EEPROM_R(Addr_factor,array_temp,lenth,0xA0);
	Read_response(lenth,array_temp);
}

//ʣ��������� Addr_event_leak
/***********************************************
ʣ��������� 10X15 =150
ʣ����������	XX	1	BIN
ʣ�����ֵ	XXXX	2	BCD
��ʼʱ��	YYMMDDhhmmss	6	
����ʱ��	YYMMDDhhmmss	6	
************************************************/
void Read_event_leakover(unsigned char fact_tmp)
{
	unsigned char lenth,array_temp[20],point_event_leak_tmp,event_point;
	int Addr_factor;
	
	if(point_event_leak==0)
	{
		point_event_leak_tmp = 9;
	}
	else
	{
		point_event_leak_tmp = point_event_leak-1;
	}
	fact_tmp = fact_tmp - 1;           //������1����
	if(point_event_leak_tmp>=fact_tmp)
	{
		event_point = (point_event_leak_tmp-fact_tmp);
	}
	else
	{
		event_point = point_event_leak_tmp+10-fact_tmp;
	}
	Addr_factor = Addr_event_leak+((event_point)*15);
	lenth = Lenth_event_leak;
  EEPROM_R(Addr_factor,array_temp,lenth,0xA0);
	Read_response(lenth,array_temp);
}

//�������Լ� Addr_event_self
void Read_event_leakself(unsigned char fact_tmp)
{
	unsigned char lenth,array_temp[30],event_point,point_event_self_tmp;
	int Addr_factor;
	if(point_event_self==0)
	{
		point_event_self_tmp = 9;
	}
	else
	{
		point_event_self_tmp = point_event_self-1;
	}
	fact_tmp = fact_tmp - 1;
	if(point_event_self_tmp>=fact_tmp)
	{
		event_point = (point_event_self_tmp-fact_tmp);
	}
	else
	{
		event_point = point_event_self_tmp+10-fact_tmp;
	}
	Addr_factor = Addr_event_self+((event_point)*26);
	lenth = Lenth_event_self;
  EEPROM_R(Addr_factor,array_temp,lenth,0xA0);
	Read_response(lenth,array_temp);	
}

//��������բ Addr_event_trip
void Read_event_leaktrip(unsigned char fact_tmp)
{
	unsigned char lenth,array_temp[30],event_point,point_event_trip_tmp;
	int Addr_factor;
	if(point_event_trip_24C256==0)
	{
		point_event_trip_tmp = 9;
	}
	else
	{
		point_event_trip_tmp = point_event_trip_24C256-1;
	}
	fact_tmp = fact_tmp - 1;
	if(point_event_trip_tmp>=fact_tmp)
	{
		event_point = (point_event_trip_tmp-fact_tmp);
	}
	else
	{
		event_point = point_event_trip_tmp+10-fact_tmp;
	}
	Addr_factor = Addr_event_trip+((event_point)*25);
	lenth = Lenth_event_trip;
	EEPROM_R(Addr_factor,array_temp,lenth,0xA0);
	Read_response(lenth,array_temp);
}
//ʣ��������� Addr_event_alarm
void Read_event_leakalarm(unsigned char fact_tmp)
{
	//unsigned char i,cs_temp,lenth,array_temp[20],point_event_alarm_tmp,event_point;
	//int Addr_factor;
	
	/*	if(point_event_alarm==0)
	{
		point_event_alarm_tmp = 9;
	}
	else
	{
		point_event_alarm_tmp = point_event_alarm-1;
	}
	fact_tmp = fact_tmp - 1;
	if(point_event_alarm_tmp>=fact_tmp)
	{
		event_point = (point_event_alarm_tmp-fact_tmp);
	}
	else
	{
		event_point = point_event_alarm_tmp+10-fact_tmp;
	}
	Addr_factor = Addr_event_alarm+((event_point)*15);
	lenth = Lenth_event_alarm;
	AT24C64_R(array_temp,Addr_factor,lenth); 	
	Addr_factor = Addr_event_alarm+(fact_tmp-1)*Lenth_event_alarm;
	lenth = Lenth_event_alarm;
	AT24C64_R(array_temp,Addr_factor,lenth); 
	Read_response(lenth,array_temp);*/
	unsigned char lenth,array_temp[20],point_event_leak_tmp,event_point;
	int Addr_factor;
	
	if(point_event_leak==0)
	{
		point_event_leak_tmp = 9;
	}
	else
	{
		point_event_leak_tmp = point_event_leak-1;
	}
	fact_tmp = fact_tmp - 1;
	if(point_event_leak_tmp>=fact_tmp)
	{
		event_point = (point_event_leak_tmp-fact_tmp);
	}
	else
	{
		event_point = point_event_leak_tmp+10-fact_tmp;
	}
	Addr_factor = Addr_event_leak+((event_point)*15);
	lenth = Lenth_event_leak;
	EEPROM_R(Addr_factor,array_temp,lenth,0xA0);
	Read_response(lenth-3,&array_temp[3]);
	
	
}
//ʣ�������¼ Addr_record_leak1
void Read_event_leakrecord(unsigned char tmp_fact,unsigned char fact_tmp)
{
	unsigned char lenth,array_temp[30],event_point;
	int Addr_factor,point_leak_record_tmp;
	if(point_Leak_record==0)
	{
		point_leak_record_tmp = 256;
	}
	else
	{
		point_leak_record_tmp = point_Leak_record-1;
	}
	fact_tmp = fact_tmp - 1;
	if(point_leak_record_tmp>=fact_tmp)
	{
		event_point = (point_leak_record_tmp-fact_tmp);
	}
	else
	{
		event_point = point_leak_record_tmp+256-fact_tmp;
	}
	Addr_factor = Addr_record_leak1+(tmp_fact-1)*256+(event_point*9);
	lenth = Lenth_record_leak1;
	EEPROM_R(Addr_factor,array_temp,lenth,0xA0);
	Read_response(lenth,array_temp);
}


//��ȡ��ǰʱ��
unsigned char Read_time(unsigned char fact_tmp)
{
	unsigned char i,lenth,array_temp[20],tim_array[10];
	tim_array[0] = 0;
	HAL_RTC_GetTime(&hrtc, &stimestructure, RTC_FORMAT_BCD);
	HAL_RTC_GetDate(&hrtc, &sdatestructure, RTC_FORMAT_BCD);
	tim_y = sdatestructure.Year;  //tim_yΪʮ���ƣ�Ҫת��������
	tim_m = sdatestructure.Month;
	tim_d = sdatestructure.Date;
	tim_h = stimestructure.Hours;
	tim_f = stimestructure.Minutes;
	tim_s = stimestructure.Seconds;
	tim_array[0]=tim_y;
	tim_array[1]=tim_m;
	tim_array[2]=tim_d;
	tim_array[3]=tim_h;
	tim_array[4]=tim_f;
	tim_array[5]=tim_s;
	if(fact_tmp==1)
	{
		lenth = 4;
		for(i=1;i<4;i++)
		{
			array_temp[4-i] = tim_array[i-1];
		}
		array_temp[0] = 0x00;
	}
	else if(fact_tmp==2)
	{
		lenth = 3;
		for(i=0;i<3;i++)
		{
			array_temp[2-i] = tim_array[i+3];
		}
	}
	else
	{
		ERR_data_sent(ERR_NO_REQUEST);
		return 1;
	}
	Read_response(lenth,array_temp);
	/* while(1)
	{
		ds1302_read_time_uart(tim_array);
		for(i=0;i<200;i++)
		{
			delay_5ms();
		}
		//20150202���������޸�
		for(i=0;i<4;i++)
		putchar(0xFE);
		for(i=0;i<7;i++)
		{
			putchar(tim_array[i]);
		}
	}  */
	return 0;
}


//��ȡ��ǰ����
unsigned char Read_factors(unsigned char fact_tmp)
{
	unsigned char lenth,array_temp_U[40];
	if(fact_tmp==0x01)//ͨ�ŵ�ַ
	{
		lenth = Lenth_dev_addr;
		copy_array(array_temp_U,self_addr_code,lenth);		
	}
	else if(fact_tmp==0x02)//�豸��
	{
		lenth = Lenth_dev_id;
		EEPROM_R(Addr_dev_id,array_temp_U,lenth,0xA0);  //�豸�Ÿ���ַһ��
	}	
	else if(fact_tmp==0x03)//�ʲ��������
	{
		unsigned int cs_sum;
		//Addr_factor = Addr_dev_code;
		lenth = Lenth_dev_code;
		//AT24C64_R(array_temp,Addr_factor,lenth);
		//copy_array(dev_code_code,dev_code_code_head,10);
		/* for(i=0;i<6;i++)
		{
			self_addr_code_str[2*i] = (self_addr_code[5-i]>>4)+0x30;
			self_addr_code_str[2*i+1] = (self_addr_code[5-i]&0x0F)+0x30;
		}
		copy_array(&dev_code_code[9],self_addr_code_str,12);
		for(i=0;i<10;i++)
		{
			cs_sum = 3*(dev_code_code[2*i]-0x30)+(dev_code_code[2*i+1]-0x30);
		}
		cs_tmp = cs_sum%10; 
		dev_code_code[21] = cs_tmp+0x30;
		//dev_code_code[21] = 0x35;
		
		for(i=0;i<10;i++)
		{
			dev_code_code[22+i] = 0x20;
		} */
		//EEPROM_R(dev_code_code,Addr_dev_code,32,0);
		EEPROM_R(Addr_dev_code,dev_code_code,32,0xA0);
		copy_array(array_temp_U,dev_code_code,lenth);
	}
	else if(fact_tmp==0x04)//���ѹ
	{
		//Addr_factor = Addr_rated_V;
		lenth = Lenth_rated_V;
		copy_array(array_temp_U,rated_V_code,lenth);
	}
	else if(fact_tmp==0x05)//�����
	{
		//Addr_factor = Addr_rated_I;
		lenth = Lenth_rated_I;
		Cur_Switch_F(Type_Cur);
		copy_array(array_temp_U,frame_current_code,lenth);
	}
	
	else if(fact_tmp==0x06)//��󣨿Ǽܣ�����(Inm)
	{
		//Addr_factor = Addr_frame_current;
		lenth = Lenth_frame_current;
		Cur_Switch_F(Type_Cur);
		copy_array(array_temp_U,frame_current_code,lenth);
	}
	else if(fact_tmp==0x0B)//�豸�ͺ�
	{
		//Addr_factor = Addr_equi_type;
		//EEPROM_R(equi_type_code,Addr_equi_type,10,0);
		
		EEPROM_R(Addr_equi_type,equi_type_code,10,0xA0);
		lenth = Lenth_equi_type;
		copy_array(array_temp_U,equi_type_code,lenth);
	}
	else if(fact_tmp==0x0C)//��������
	{
		//Addr_factor = Addr_production_date;
		lenth = Lenth_production_date;
		copy_array(array_temp_U,production_date_code,lenth);
	}
	else if(fact_tmp==0x0D)//Э��汾��
	{
		//Addr_factor = Addr_protocol_ver;
		lenth = Lenth_protocol_ver;
		copy_array(array_temp_U,protocol_ver_code,lenth);
	}
	else if(fact_tmp==0x0E)//��������
	{
		//Addr_factor = Addr_factory_code;
		//EEPROM_R(factory_code_code,Addr_factory_code,24,0);
		EEPROM_R(Addr_factory_code,factory_code_code,24,0xA0);
		lenth = Lenth_factory_code;
		copy_array(array_temp_U,factory_code_code,lenth);
	}	
	else if(fact_tmp==0x0F)//�̼��汾��
	{
		//Addr_factor = Addr_soft_ver;
		lenth = Lenth_soft_ver;
		copy_array(array_temp_U,soft_ver_code,lenth);
	}
	else if(fact_tmp==0x10)//Ӳ���汾��32
	{
		//Addr_factor = Addr_hard_ver;
		lenth = Lenth_hard_ver;
		copy_array(array_temp_U,hard_ver_code,lenth);
	}
	else if(fact_tmp==0x11)//�ʣ���������ֵ������ 20
	{
		//Addr_factor = Addr_leak_valve;
		lenth = Lenth_leak_valve;
		copy_array(array_temp_U,leak_valve_code,lenth);
	}
	else if(fact_tmp==0x12)//����޲�����ʱ�������10
	{
		//Addr_factor = Addr_leak_time;
		lenth = Lenth_leak_time;
		copy_array(array_temp_U,leak_time_code,lenth);
	}
	else if(fact_tmp==0x13)//��ֶ�ʱ�������10
	{
		//Addr_factor = Addr_break_time;
		lenth = Lenth_break_time;
		//AT24C64_R(array_temp,Addr_factor,lenth);
		copy_array(array_temp_U,break_time_code,lenth);
	}
	else if(fact_tmp==0x14)//�Զ��ֺ�բʱ��24
	{
		//Addr_factor = Addr_auto_closing;
		lenth = Lenth_auto_closing;
		copy_array(array_temp_U,auto_closing_code,lenth);
	}
	else if(fact_tmp==0x15)//ʣ������������ԣ�A�ͻ�AC�ͣ�
	{
		//Addr_factor = Addr_leak_type;
		lenth = Lenth_leak_type;
		copy_array(array_temp_U,leak_type_code,lenth);
	}
	else if(fact_tmp==0x16)//��װ��λ��ֻ���õ���ʽ��������10
	{
		//Addr_factor = Addr_install_phase;
		lenth = Lenth_install_phase;
		copy_array(array_temp_U,install_phase_type_code,lenth);
		//AT24C64_R(array_temp_U,Addr_factor,lenth);
	}

//	else if(fact_tmp==0x17)//����ʱ�������������� 20	BCD  long_delay_action
//	{
//		//Addr_factor = Addr_install_phase;
//		lenth = 20;
//		copy_array(array_temp_U,long_delay_action,lenth);
//	}
//	else if(fact_tmp==0x18)//����ʱ����ʱ������� 10	BCD  long_delay_time
//	{
//		//Addr_factor = Addr_install_phase;
//		lenth = 10;
//		copy_array(array_temp_U,long_delay_time,lenth);
//	}
//	else if(fact_tmp==0x19)//��·����ʱ�������������� 10	BCD  short_delay_action
//	{
//		//Addr_factor = Addr_install_phase;
//		lenth = 10;
//		copy_array(array_temp_U,short_delay_action,lenth);
//	}
//	else if(fact_tmp==0x1A)//��·����ʱ����ʱ������� 20	BCD  short_delay_time
//	{
//		//Addr_factor = Addr_install_phase;
//		lenth = 20;
//		copy_array(array_temp_U,short_delay_time,lenth);
//	}
//	else if(fact_tmp==0x1B)//��·˲ʱ�������������� 10	BCD   instant_action
//	{
//		//Addr_factor = Addr_install_phase;
//		lenth = 10;
//		copy_array(array_temp_U,instant_action,lenth);
//	}
	else
	{
		ERR_data_sent(ERR_NO_REQUEST);
		return 1;
	}
	Read_response(lenth,array_temp_U);
	return 0;
}

//��ȡ��ǰ״̬
/* ˵���и澯�ļ���״̬
1��ʣ��������ˣ������澯�봮�����ã�
2��ִ����բ����ʧ�ܣ�D7+���ϣ�
3���ֳ���������93���и澯
*/

unsigned char Read_state(unsigned char fact_tmp)
{
	unsigned char lenth,array_temp[10];
	stateword[0] = stateword[1] = 0;
	if(isfenzha==0)	    //��բ״̬
	{
		F_analog_trip = 0;
		if(F_trip_ld==1)
		{
			stateword[0] = 0x80+F_gz;  //0x80Ϊ©��澯��������˼
		}
		else
		{
			stateword[0] = F_gz;  //�����5λΪ����״̬
		}
		if(F_set_state==1) 
		{
			stateword[0] = 0x93;  //1001 0111
		}

	}
	else			//��բ״̬
	{
		if(F_gz==0)
		{
			stateword[0] = 0x40;  //�غ�բ
		}
		else if(F_gz==2)//©��
		{
			if (F_Trip!=0x03) 	stateword[0] =(0x40|F_gz);
			else    		stateword[0] =(0x60|F_gz);
		}
		else if((F_gz == 4)||(F_gz==5)||(F_gz==6)||(F_gz == 7)||(F_gz == 8)||(F_gz==9)||(F_gz==0x0A)||(F_gz==0x0B)||(F_gz==0x0D)||(F_gz==0x0F)||(F_gz==0x12))
		{
			if(F_hezha_sta==1)
			{
				stateword[0] =(0x40|F_gz);
			}
			else
			{
				stateword[0] =(0x60|F_gz);
			}
			if((F_analog_trip==1)&&(F_gz==0x0D)) 	
			{
				
				stateword[0] = 0x4D;
			}
		}
		else if((F_gz==0x0C)||(F_gz==0x0B)||(F_gz==0x0E))
		{
			stateword[0] =(0x40|F_gz);
		}
		else
		{
			stateword[0] =(0x60|F_gz);
		}
		if(F_set_state==1)
		{
			stateword[0] = 0xF3;
		}
		if(F_disp_jg==0x55)
		{
			stateword[0] = 0x71;
		}
		
	}

	stateword[1] = point_trip;
	point_trip = 0;
	if((fact_tmp==1)||(fact_tmp==2))  //��״̬��1����2
	{
		array_temp[0] = stateword[fact_tmp-1];
		lenth = 1;
	}
	else if(fact_tmp==0xff)
	{
		array_temp[0] = stateword[0];
		array_temp[1] = stateword[1];  //����
		lenth = 2;
	}
	else
	{
		ERR_data_sent(ERR_NO_REQUEST);
		return 1;
	}
	Read_response(lenth,array_temp);
	return 0;	
}


//��ȡ��ǰ������
unsigned char Read_baud(unsigned char fact_tmp)
{
	unsigned char lenth,array_temp[4];
	if(baud==0) baud_uart = 0x04;
	else if(baud==1) baud_uart = 0x08;
	else if(baud==2) baud_uart = 0x10;   
	else if(baud==3) baud_uart = 0x20;   //�����ʴ��� 9600 ���γ�2
	else baud_uart = 0x08;
	if(fact_tmp==0x03)
	{
		array_temp[0] = baud_uart;
		lenth = 1;
	}
	else
	{
		ERR_data_sent(ERR_NO_REQUEST);
		return 1;
	}
	Read_response(lenth,array_temp);
	return 0;
}

//��ȡ��ǰ������
unsigned char Read_ctrlword(unsigned char fact_tmp)
{
	unsigned char i,lenth,array_temp[10];

	if((fact_tmp>0)&&(fact_tmp<6))
	{
		array_temp[0] = ctrlword[fact_tmp-1];
		lenth = 1;
	}
	else if(fact_tmp==0xff)
	{
		for(i=0;i<6;i++)
		{
			array_temp[i] = ctrlword[i];
		}
		lenth = 5;
	}
	else
	{
		ERR_data_sent(ERR_NO_REQUEST);
		return 1;
	}
	Read_response(lenth,array_temp);
	return 0;	
}

//��ȡ©����Ʋ���
unsigned char Read_leakctrl(unsigned char fact_tmp)
{
	unsigned char lenth,array_temp[20];
	int Addr_factor;
	if(fact_tmp==0x01)//ʣ��������ޱ�������ֵ 2
	{
		Addr_factor = Addr_alarm_value;
		lenth = Lenth_alarm_value;
		EEPROM_R(Addr_factor,array_temp,lenth,0xA0);
	}
	else if(fact_tmp==0x02)//ʣ�������¼�仯��ֵ����ֵ(10-99) 1

	{
		Addr_factor = Addr_record_value;
		lenth = Lenth_record_value;
		EEPROM_R(Addr_factor,array_temp,lenth,0xA0);
	}
	else if(fact_tmp==0x03)//ʣ�������¼���ʱ������ֵ(01-99)

	{
		Addr_factor = Addr_record_time;
		lenth = Lenth_record_time;
		EEPROM_R(Addr_factor,array_temp,lenth,0xA0);
	}
	else if(fact_tmp==0xFF)
	{
		Addr_factor = Addr_alarm_value;
		lenth = Lenth_alarm_value+Lenth_record_value+Lenth_record_time;
		EEPROM_R(Addr_factor,array_temp,lenth,0xA0);
		EEPROM_R(Addr_record_time,&array_temp[3],1,0xA0);	
	}
	else
	{
		ERR_data_sent(ERR_NO_REQUEST);
		return 1;
	}
	//AT24C64_R(array_temp,Addr_factor,lenth);
	Read_response(lenth,array_temp);
	return 0;
}

//��ȡ��ʱ����ʱ��
unsigned char  Read_timing(unsigned char fact_tmp)
{
	unsigned char lenth,array_temp[20],Addr_factor;
	if(fact_tmp==0x01)//��ʱ��������ʱ�� 3
	{
		Addr_factor = Addr_timed_trip;//record_time_code;
		lenth = Lenth_timed_trip;
	}
	else if(fact_tmp==0xFF)
	{
		Addr_factor = Addr_timed_trip;
		lenth = Lenth_timed_trip;
	}
	else
	{
		ERR_data_sent(ERR_NO_REQUEST);
		return 1;
	}
	//AT24C64_R(array_temp,Addr_factor,lenth);
	//if(F_time_compare==0)
	{
		array_temp[0] = timed_trip_code[0];
		array_temp[1] = timed_trip_code[1];
		array_temp[2] = timed_trip_code[2];
	}
	Read_response(lenth,array_temp);
	return 0;
}
//��ȡ��ѹ�������ֵ
unsigned  char Read_vol_setpoint(unsigned char fact_tmp)
{
	unsigned char lenth,array_temp[20];
	if(fact_tmp==0x01)//����ѹ����ֵ 2
	{
		
		over_vol_code[0] = 0x00;
		over_vol_code[1] = 0x25+Vol_g;
		lenth =  Lenth_over_vol;
		copy_array(array_temp,over_vol_code,lenth);
		
	}
	else if(fact_tmp==0x02)//Ƿ��ѹ����ֵ 2
	{

		under_vol_code[0] = 0x00;
		under_vol_code[1] = 0x14+Vol_q;
		if(under_vol_code[1]==0x1A)
		under_vol_code[1] = 0x20;	
		lenth =  Lenth_under_vol;
		copy_array(array_temp,under_vol_code,lenth);
	}
	else if(fact_tmp==0x03)//�����ѹ����ֵ 2
	{
		//Addr_factor = Addr_break_phase;
		lenth =  Lenth_break_phase;
		copy_array(array_temp,break_phase_code,lenth);
	}
	else if(fact_tmp==0xFF)
	{
		//Addr_factor = Addr_over_vol;
		lenth =  Lenth_over_vol+Lenth_break_phase+Lenth_under_vol;
		over_vol_code[0] = 0x00;
		over_vol_code[1] = 0x25+Vol_g;
		under_vol_code[0] = 0x00;
		under_vol_code[1] = 0x14+Vol_q;
		copy_array(array_temp,over_vol_code,2);
		copy_array(&array_temp[2],under_vol_code,2);
		copy_array(&array_temp[4],break_phase_code,2);
	}
	else
	{
		ERR_data_sent(ERR_NO_REQUEST);
		return 1;
	}
	Read_response(lenth,array_temp);
	return 0;
}

void Cur_uart_get(void)
{
	
	unsigned char i;
	unsigned int tmp; 	
	for(i=0;i<3;i++)
	{
		rated_current_code[i] = 0x00;
	}
	
	if(Type_Cur==0)//100 20~100
	{
		
		tmp = 200 + D_Cur*100;  //10Ϊ1��λ
		DectoBCD(rated_current_code,tmp,3);
	}
	if(Type_Cur==1)//250 60-250
	{
		tmp = 600 + D_Cur*100;
		DectoBCD(rated_current_code,tmp,3);
		
	}
	if(Type_Cur==2)//400 200-400
	{
		tmp = 2000 + D_Cur*200;   //20Ϊ1��λ
		DectoBCD(rated_current_code,tmp,3);
	}
	if(Type_Cur==3)//630 210 -630
	{
		tmp = 2100 + D_Cur*300;    //30Ϊ1��λ
		DectoBCD(rated_current_code,tmp,3);	
	}
	if(Type_Cur==4)//100 20~100
	{
		
		tmp = 3200 + D_Cur*800;  //10Ϊ1��λ
		DectoBCD(rated_current_code,tmp,3);
	}
}


//��ȡ�����������ֵ
unsigned char Read_cur_setpoint(unsigned char fact_tmp)
{
	unsigned char lenth,array_temp[20];
	int Addr_factor;
	if(fact_tmp==0x01)//���������ֵ 3
	{
		//Addr_factor = Addr_rated_current;
		lenth =  Lenth_rated_current;
		Cur_uart_get();
		copy_array(array_temp,rated_current_code,lenth);		
	}
	else if(fact_tmp==0x02)    //�������ޱ�������ֵ
	{ 
		Addr_factor = Addr_over_current;
		lenth =  Lenth_over_current;
		EEPROM_R(Addr_factor,array_temp,lenth,0xA0);
	}
	else if(fact_tmp==0xFF)
	{
		//Addr_factor = Addr_rated_current;
		lenth =  Lenth_rated_current+Lenth_over_current;
		Cur_uart_get();
		copy_array(array_temp,rated_current_code,Lenth_rated_current);
		Addr_factor = Addr_over_current;
		EEPROM_R(Addr_factor,&array_temp[Lenth_rated_current],Lenth_over_current,0xA0);
	}
	else
	{
		ERR_data_sent(ERR_NO_REQUEST);
		return 1;
	}
	Read_response(lenth,array_temp);
	return 0;
}

//��ȡԤ��բʱ��
void Read_fenzha_tim(unsigned char fact_tmp)
{
	unsigned char lenth,array_temp[20];
	fact_tmp = fact_tmp+1;
	//Addr_factor = Addr_remote_trip;
	lenth = 2;
	fact_tmp = fact_tmp-1;
	//EEPROM_R(array_temp,Addr_factor,lenth,2);
	copy_array(array_temp,remote_trip_time,2);
	Read_response(lenth,array_temp);
	
	
}
//��ȡԤ��բʱ��
void Read_hezha_tim(unsigned char fact_tmp)
{
	unsigned char lenth,array_temp[20];
	//	Addr_factor = Addr_remote_close;
	fact_tmp =fact_tmp +1;
	lenth =  Lenth_remote_close;
	fact_tmp=fact_tmp -1;
	//AT24C64_R(array_temp,Addr_factor,lenth);
	copy_array(array_temp,remote_close_time,2);
	Read_response(lenth,array_temp);
}

//��ȡģ���ѿ�ʱ��
void Read_trip_tim(unsigned char fact_tmp)
{
	unsigned char lenth,array_temp[20];
	//	Addr_factor = Addr_analog_trip;
	fact_tmp=fact_tmp +1;
	lenth =  Lenth_analog_trip;
	fact_tmp=fact_tmp -1;
	//AT24C64_R(array_temp,Addr_factor,lenth);
	copy_array(array_temp,analog_trip_time,2);
	Read_response(lenth,array_temp);
}
void Read_addr(void)
{
	unsigned char lenth,array_temp_U[40];
	lenth = Lenth_dev_addr;
	copy_array(array_temp_U,self_addr_code_temp,lenth);	
	Read_response1(lenth,array_temp_U);
}

void Write_addr(void)  //д��ַ
{
	unsigned char i,cs_temp,lenth;
	int Addr_factor;
	for(i=0;i<6;i++)
	{
		self_addr_code[i] = data_array[i];
	}
	format_uart_t_buf();  //��0
	UART_T_Buf[0]=UART_T_Buf[7] = 0x68;
	for(i=0;i<6;i++)
	{
		UART_T_Buf[i+1] =  0xAA;  //д����ַǰ�涼����
	}
	UART_T_Buf[8]	= ctrl_code+0x80;
	UART_T_Buf[9] = 0x00;  //�ھ�λ�����ݳ���
	cs_temp = 0;
	for(i=0;i<10;i++)
	{
		cs_temp =  UART_T_Buf[i] + cs_temp;
	}
	UART_T_Buf[10]	= cs_temp;
	UART_T_Buf[11] =  0x16;
	//20150202??????
	//	for(i=0;i<4;i++)
	//	put2char(0xFE);
//	for(i=0;i<12;i++)
//	put2char(UART_T_Buf[i]);	
//	//RS485_Send_Data(UART_T_Buf,12);
		for(i=0;i<4;i++)
	{
	UART_S_Buf[i]=0xFE;
	}
		if(F_Dataval==1)
	{
		HAL_UART_Transmit(&huart3,(uint8_t*)UART_S_Buf,4,0xffff);
		HAL_UART_Transmit(&huart3,(uint8_t*)UART_T_Buf,12,0xffff);
//		 RS485_Send_Data(UART_S_Buf,4);
//		 RS485_Send_Data(UART_T_Buf,12);
	}
	if(F_Dataval1==1)
	{
		 //hongwai_Send_Data(UART_T_Buf,12);
	}
	
	
	delay_ms(5);
	delay_ms(5);
	Addr_factor = Addr_dev_addr;
	lenth = Lenth_dev_addr;
	MODIFY_EEP_W(Addr_factor,self_addr_code,lenth,0xA0);
}

//д��ǰʱ��
unsigned char Write_time(unsigned char fact_tmp)
{
	unsigned char i,array_temp[10];

	if(fact_tmp==1)//��������
	{
	HAL_RTC_GetTime(&hrtc, &stimestructure, RTC_FORMAT_BCD);
  HAL_RTC_GetDate(&hrtc, &sdatestructure, RTC_FORMAT_BCD);
	tim_y1 = sdatestructure.Year;  //tim_yΪʮ���ƣ�Ҫת��������
	tim_m1 = sdatestructure.Month;
	tim_d1 = sdatestructure.Date;
	tim_h1 = stimestructure.Hours;
	tim_f1 = stimestructure.Minutes;
	tim_s1 = stimestructure.Seconds;
//	tim_y=tim_y%2000;  //time_tmp[0]=17   ʮ����ת��Ϊ�����ƴ���24C64��
//	array_temp[0]=(tim_y/10)<<4;
//	array_temp[0]+=(tim_y%10);
//	array_temp2[0]=((array_temp[0]>>4)*10)+(array_temp[0]&0x0F)+2000;	
//	array_temp[1]=(tim_m/10)<<4;
//	array_temp[1]+=(tim_m%10);
//	array_temp[2]=(tim_d/10)<<4;
//	array_temp[2]+=(tim_d%10);
//	array_temp[3]=(tim_h/10)<<4;
//	array_temp[3]+=(tim_h%10);
//	array_temp[4]=(tim_f/10)<<4;
//	array_temp[4]+=(tim_f%10);
//	array_temp[5]=(tim_s/10)<<4;
//	array_temp[5]+=(tim_s%10);
	array_temp[0]=tim_y1;	
	array_temp[1]=tim_m1;
	array_temp[2]=tim_d1;
	array_temp[3]=tim_h1;
	array_temp[4]=tim_f1;
	array_temp[5]=tim_s1;
		for(i=0;i<3;i++)
		{
			array_temp[2-i] = data_array[12+1+i];
		}
//    array_temp[6]=((array_temp[0]>>4)*10)+(array_temp[0]&0x0F);
//		tim_y1=((array_temp[6]/10)<<4)+(array_temp[6]%10);
//		tim_m1=array_temp[1];
//		tim_d1=array_temp[2];
//		sdatestructure.Year=tim_y1;
//	 RTC_Set_Date(tim_y1,tim_m1,tim_d1);
	 RTC_Set_Date(array_temp[0],array_temp[1],array_temp[2]);
	 RTC_Set_Time(tim_h1,tim_f1,tim_s1);
	 
	 	HAL_RTC_GetTime(&hrtc, &stimestructure, RTC_FORMAT_BCD);
    HAL_RTC_GetDate(&hrtc, &sdatestructure, RTC_FORMAT_BCD);
		//ds1302_write_time_uart(array_temp2[0],array_temp[1],array_temp[2],array_temp[3],array_temp[4],array_temp[5]);	
		return 0;
	}
	else if(fact_tmp==2)//ʱ����
	{
	HAL_RTC_GetTime(&hrtc, &stimestructure, RTC_FORMAT_BCD);
    HAL_RTC_GetDate(&hrtc, &sdatestructure, RTC_FORMAT_BCD);
	tim_y = sdatestructure.Year;  //tim_yΪʮ���ƣ�Ҫת��������
	tim_m = sdatestructure.Month;
	tim_d = sdatestructure.Date;
	tim_h = stimestructure.Hours;
	tim_f = stimestructure.Minutes;
	tim_s = stimestructure.Seconds;
//	tim_y=tim_y%2000;  //time_tmp[0]=17   ʮ����ת��Ϊ�����ƴ���24C64��
//	array_temp[0]=(tim_y/10)<<4;
//	array_temp[0]+=(tim_y%10);
//	array_temp2[0]=((array_temp[0]>>4)*10)+(array_temp[0]&0x0F)+2000;	
//	array_temp[1]=(tim_m/10)<<4;
//	array_temp[1]+=(tim_m%10);
//	array_temp[2]=(tim_d/10)<<4;
//	array_temp[2]+=(tim_d%10);
//	array_temp[3]=(tim_h/10)<<4;
//	array_temp[3]+=(tim_h%10);
//	array_temp[4]=(tim_f/10)<<4;
//	array_temp[4]+=(tim_f%10);
//	array_temp[5]=(tim_s/10)<<4;
//	array_temp[5]+=(tim_s%10);
	array_temp[0]=tim_y;	
	array_temp[1]=tim_m;
	array_temp[2]=tim_d;
	array_temp[3]=tim_h;
	array_temp[4]=tim_f;
	array_temp[5]=tim_s;
	for(i=0;i<3;i++)
	{
		array_temp[3+2-i] = data_array[12+i];
	}
 RTC_Set_Time(array_temp[3],array_temp[4],array_temp[5]);
 RTC_Set_Date(array_temp[0],array_temp[1],array_temp[2]);
		
		HAL_RTC_GetTime(&hrtc, &stimestructure, RTC_FORMAT_BCD);
    HAL_RTC_GetDate(&hrtc, &sdatestructure, RTC_FORMAT_BCD);
		//ds1302_write_time_uart(array_temp2[0],array_temp[1],array_temp[2],array_temp[3],array_temp[4],array_temp[5]);	
		return 0;
	}
		else if(fact_tmp==0xFF)//ʱ����
	{
	HAL_RTC_GetTime(&hrtc, &stimestructure, RTC_FORMAT_BCD);
  HAL_RTC_GetDate(&hrtc, &sdatestructure, RTC_FORMAT_BCD);
	tim_y = sdatestructure.Year;  //tim_yΪʮ���ƣ�Ҫת��������
	tim_m = sdatestructure.Month;
	tim_d = sdatestructure.Date;
	tim_h = stimestructure.Hours;
	tim_f = stimestructure.Minutes;
	tim_s = stimestructure.Seconds;

	array_temp[0]=tim_y;	
	array_temp[1]=tim_m;
	array_temp[2]=tim_d;
	array_temp[3]=tim_h;
	array_temp[4]=tim_f;
	array_temp[5]=tim_s;
		for(i=0;i<6;i++)
		{
			array_temp[5-i] = data_array[12+i];
		}
	 RTC_Set_Time(array_temp[3],array_temp[4],array_temp[5]);
	 RTC_Set_Date(array_temp[0],array_temp[1],array_temp[2]);
		
			HAL_RTC_GetTime(&hrtc, &stimestructure, RTC_FORMAT_BCD);
    HAL_RTC_GetDate(&hrtc, &sdatestructure, RTC_FORMAT_BCD);
		//ds1302_write_time_uart(array_temp2[0],array_temp[1],array_temp[2],array_temp[3],array_temp[4],array_temp[5]);	
		return 0;
	}
	else
	{
		ERR_data_sent(ERR_NO_REQUEST);
		return 2;
	}
}

//д��ǰ����
unsigned char  Write_factors(unsigned char fact_tmp)
{
	unsigned char i,array_temp[32],array_tmp[1];
	if(fact_tmp==1)//дͨ�ŵ�ַ 6 BCD
	{
		for(i=0;i<6;i++)
		{
			self_addr_code[i] = data_array[12+i];
			if(array_temp[i]>0x99)
			{
				ERR_data_sent(ERR_BAD_DATA);
				return 1;
			}
		}
		MODIFY_EEP_W(Addr_dev_addr,self_addr_code,6,0xA0);
		return 0;
	}
	else if(fact_tmp==2)//д�豸�� 6 BCD
	{
		for(i=0;i<6;i++)
		{
			dev_id_code[i] = data_array[12+i];
			if(dev_id_code[i]>0x99)
			{
				ERR_data_sent(ERR_BAD_DATA);
				return 1;
			}
		}		
		MODIFY_EEP_W(Addr_dev_id,dev_id_code,6,0xA0);
		return 0;
	}
	else if(fact_tmp==3)//д�ʲ�������� 32 ASCII
	{
		for(i=0;i<32;i++)
		{
			dev_code_code[i] = data_array[12+i];
		}
		WRITE_DATA_NOMAL();
		MODIFY_EEP_W(Addr_dev_code,dev_code_code,32,0xA0);
		return 1;
	} 
	else if(fact_tmp==6)//д�Ǽܵ��� 2 BCD
	{
		array_temp[0]=data_array[12];
		array_temp[1]=data_array[13];
		UART_Cur_Value=BCDtoDec(array_temp,2);
		if(UART_Cur_Value==2500)
		{
		Type_Cur=1;
		}
		else if(UART_Cur_Value==4000)
		{
		Type_Cur=2;
		}
		else if(UART_Cur_Value==6300)
		{
		Type_Cur=3;
		}
		else 
		{
		Type_Cur=0;
		}
		array_tmp[0]=Type_Cur;
		Cur_Switch(Type_Cur);
//		WRITE_DATA_NOMAL();
		MODIFY_EEP_W(Addr_Type_Cur,array_tmp,1,0xA0);
		return 0;
	} 
	else if(fact_tmp==0x0E)//д���Ҵ��� 24 ASCII 
	{
		for(i=0;i<24;i++)
		{
			factory_code_code[i] = data_array[12+i];
		}
		WRITE_DATA_NOMAL();
		MODIFY_EEP_W(Addr_factory_code,factory_code_code,24,0xA0);
		return 1;
	}
	else if(fact_tmp==0x0B)//д�豸���� 10 ASCII 
	{
		for(i=0;i<10;i++)
		{
			equi_type_code[i] = data_array[12+i];
		}
		WRITE_DATA_NOMAL();
		MODIFY_EEP_W(Addr_equi_type,equi_type_code,10,0xA0);
		return 1;
	}

	else if(fact_tmp==0x11)//д�ʣ���������ֵ������ 20 BCD
	{
		for(i=0;i<20;i++)
		{
			leak_valve_code[i] = data_array[12+i];
		}		
		MODIFY_EEP_W(Addr_leak_valve,leak_valve_code,Lenth_leak_valve,0xA0);
		return 0;
	}
	else if(fact_tmp==0x12)//д����޲�����ʱ������� 10 BCD
	{
		for(i=0;i<Lenth_leak_time;i++)
		{
			leak_time_code[i] = data_array[12+i];
		}		
		MODIFY_EEP_W(Addr_leak_time,leak_time_code,Lenth_leak_time,0xA0);
		return 0;
	}
	else if(fact_tmp==0x13)//д��ֶ�ʱ��������� 10 BCD
	{
		for(i=0;i<Lenth_break_time;i++)
		{
			break_time_code[i] = data_array[12+i];
		}		
		MODIFY_EEP_W(Addr_leak_time,leak_time_code,Lenth_leak_time,0xA0);
		return 0;
	}
	
	
	else
	{
		ERR_data_sent(ERR_NO_REQUEST);
		return 2;
	}
}
//д��ǰ������
unsigned char Write_baud(unsigned char fact_tmp)
{
	//baud = data_array[12];
	baud_uart = data_array[12];
	if((baud_uart==0x02)||(baud_uart==0x04)||(baud_uart==0x08)||(baud_uart==0x10)||(baud_uart==0x20)||(baud_uart==0x40))
	{
		if(baud_uart==0x20) baud = 3;
		else if(baud_uart==0x10)baud = 2;
		else if(baud_uart==0x08)baud = 1;
		else if(baud_uart==0x04)baud = 0;
		else baud = 1;
		data_array[0] = baud;
		MODIFY_EEP_W(Addr_baud,data_array,1,0xA0);
		return 0;
	}
	else
	{
		ERR_data_sent(ERR_BAD_DATA);
//	//RS485_Send_Data(data_array,1);
		return 1;
	}
}
//д��ǰ����
unsigned char Write_password(unsigned char fact_tmp)
{
	unsigned char i,array_temp[6];
	if(fact_tmp==1)
	{
		for(i=0;i<4;i++)
		{
			array_temp[i] = data_array[12+i];
			password_0class[i] = data_array[12+i];
			if(array_temp[i]>0x99)
			{
				ERR_data_sent(ERR_BAD_DATA);
				return 1;
			}
		}		
		MODIFY_EEP_W(Addr_0_password,array_temp,4,0xA0);
		return 0;
	}
	else if(fact_tmp==2)
	{
		for(i=0;i<4;i++)
		{
			array_temp[i] = data_array[12+i];
			password_1class[i] = data_array[12+i];
			if(array_temp[i]>0x99)
			{
				ERR_data_sent(ERR_BAD_DATA);
				return 1;
			}
		}		
		MODIFY_EEP_W(Addr_1_password,array_temp,4,0xA0);
		return 0;
	}
	else if(fact_tmp==3)
	{
		for(i=0;i<4;i++)
		{
			array_temp[i] = data_array[12+i];
			password_2class[i] = data_array[12+i];
			if(array_temp[i]>0x99)
			{
				ERR_data_sent(ERR_BAD_DATA);
				return 1;
			}
		}		
		MODIFY_EEP_W(Addr_2_password,array_temp,4,0xA0);
		return 0;
	}
	else
	{
		ERR_data_sent(ERR_NO_REQUEST);
		return 2;
	}
	// for(i=0;i<4;i++)
	// {
	// putchar(password_0class[i]);
	// }
	// for(i=0;i<4;i++)
	// {
	// putchar(password_1class[i]);
	// }
	// for(i=0;i<4;i++)
	// {
	// putchar(password_2class[i]);
	// }
	
}


//д��ǰ������
unsigned char Write_ctrlword(unsigned char fact_tmp)
{
	unsigned char i,array_temp[6];
	if((fact_tmp>=1)&&(fact_tmp<=5))
	{
		array_temp[fact_tmp-1] = data_array[12+0];
		ctrlword[fact_tmp-1] = array_temp[fact_tmp-1];
		//AT24C64_W(ctrlword,Addr_crtl_word1,5);
		// putchar(0x55);
		// putchar(ctrlword[fact_tmp-1]);
		if(fact_tmp==1)
		{
			ctrlword1_analyze();
			//AT24C64_W(&ctrlword[0],Addr_crtl_word1,1);
			MODIFY_EEP_W(Addr_crtl_word1,&ctrlword[0],1,0xA0);
		}
		else if(fact_tmp==2)
		{
			ctrlword2_analyze();
			//AT24C64_W(&ctrlword[1],Addr_crtl_word2,1);
			MODIFY_EEP_W(Addr_crtl_word2,&ctrlword[1],1,0xA0);
		}
		else if(fact_tmp==3)
		{
			ctrlword3_analyze();
			//AT24C64_W(&ctrlword[2],Addr_crtl_word3,1);
			MODIFY_EEP_W(Addr_crtl_word3,&ctrlword[2],1,0xA0);
		}
		else if(fact_tmp==4)
		{
			ctrlword4_analyze();
			//AT24C64_W(&ctrlword[3],Addr_crtl_word4,1);
			MODIFY_EEP_W(Addr_crtl_word4,&ctrlword[3],1,0xA0);
		}
		else if(fact_tmp==5)
		{
			ctrlword5_analyze();
		}
		else
		{
			ERR_data_sent(ERR_NO_REQUEST);
			return 2;
		}
		return 0;
	}

	else if(fact_tmp==0xff)
	{
		for(i=0;i<5;i++)
		{
			ctrlword[i] = data_array[12+i];
		}
		ctrlword1_analyze();
		//AT24C64_W(&ctrlword[0],Addr_crtl_word1,1);
		MODIFY_EEP_W(Addr_crtl_word1,&ctrlword[0],1,0xA0);
		ctrlword2_analyze();
		//AT24C64_W(&ctrlword[1],Addr_crtl_word2,1);
		MODIFY_EEP_W(Addr_crtl_word2,&ctrlword[1],1,0xA0);
		ctrlword3_analyze();
		//AT24C64_W(&ctrlword[2],Addr_crtl_word3,1);
		MODIFY_EEP_W(Addr_crtl_word3,&ctrlword[2],1,0xA0);
		ctrlword4_analyze();
		//AT24C64_W(&ctrlword[3],Addr_crtl_word4,1);
		MODIFY_EEP_W(Addr_crtl_word4,&ctrlword[3],1,0xA0);
		ctrlword5_analyze();
		return 0;
	}
	else 
	{
		ERR_data_sent(ERR_NO_REQUEST);
		return 2;
	}
	
}

//д©����Ʋ���
unsigned char Write_leakctrl(unsigned char fact_tmp)
{
	unsigned char array_temp[6];
	if(fact_tmp==1)//ʣ�������������ֵ 2 BCD
	{
		array_temp[0] = data_array[12];
		array_temp[1] = data_array[12+1];
		if((array_temp[0]>0x99)||(array_temp[1]>0x99))
		{
			ERR_data_sent(ERR_BAD_DATA);
			return 1;
		}
		copy_array(alarm_value_code,array_temp,Lenth_alarm_value);
		Leak_Alarm_Value = BCDtoDec(array_temp,2);
		MODIFY_EEP_W(Addr_alarm_value,alarm_value_code,2,0xA0);
		return 0;
	}
	else if(fact_tmp==2)//ʣ�������¼��ֵ����ֵ 1 BCD
	{
		array_temp[0] = data_array[12];
		
		if((array_temp[0]>0x99)||(array_temp[0]<0x10))
		{
			ERR_data_sent(ERR_BAD_DATA);
			return 1;
		}
		record_value_code[0] = array_temp[0];
		Leak_record_value = BCDtoDec(record_value_code,1);
		MODIFY_EEP_W(Addr_record_value,record_value_code,1,0xA0);
		array_temp[0] = 0;
		MODIFY_EEP_W(Addr_record_value,array_temp,1,0xA0);
		return 0;
	}
	else if(fact_tmp==3)//ʣ�������¼ʱ������ֵ 1 BCD
	{
		array_temp[0] = data_array[12];
		if((array_temp[0]>0x99)||(array_temp[0]<0x01))
		{
			ERR_data_sent(ERR_BAD_DATA);
			return 1;
		}
		record_time_code[0] = array_temp[0];
		Leak_record_time = BCDtoDec(record_time_code,1);	
		Num_leak_record = Leak_record_time*30*1000 + 1;
		MODIFY_EEP_W(Addr_record_time,record_time_code,1,0xA0);
		return 0;
	}
	else if(fact_tmp==0xff)
	{
		array_temp[0] = data_array[12+0];
		array_temp[1] = data_array[12+1];
		array_temp[2] = data_array[12+2];
		array_temp[3] = data_array[12+3];
		if((array_temp[0]>0x99)||(array_temp[1]>0x99)||(array_temp[2]>0x99))
		{
			ERR_data_sent(ERR_BAD_DATA);
			return 1;
		}
		alarm_value_code[0] = array_temp[0];
		alarm_value_code[1] = array_temp[1];
		record_value_code[0] = array_temp[2];
		record_time_code[0] = array_temp[3];
		Leak_Alarm_Value = BCDtoDec(alarm_value_code,2);
		Leak_record_value = BCDtoDec(alarm_value_code,1);
		Leak_record_time = BCDtoDec(record_time_code,1);
		Num_leak_record = Leak_record_time*30*1000 + 1;
		MODIFY_EEP_W(Addr_alarm_value,array_temp,4,0xA0);
		return 0;
	}
	else
	{
		ERR_data_sent(ERR_NO_REQUEST);
		return 2;
	}
}

//д��ʱ����ʱ��
unsigned char Write_timing(unsigned char fact_tmp)
{
	unsigned char array_temp[6];
	if((fact_tmp==0x01)||(fact_tmp==0xff))
	{
		timed_trip_code[0] = array_temp[0] = data_array[12+0];
		timed_trip_code[1] = array_temp[1] = data_array[12+1];
		timed_trip_code[2] = array_temp[2] = data_array[12+2];
		if((array_temp[0]>0x99)||(array_temp[1]>0x99)||(array_temp[2]>0x99))
		{
			ERR_data_sent(ERR_BAD_DATA);
			return 1;
		}
		MODIFY_EEP_W(Addr_timed_trip,array_temp,3,0xA0);
		//MODIFY_EEP_W(array_temp,Addr_timed_trip,3,2);
		
		// if(F_timealarm==1)
		// {
		// F_time_compare = 1;		
		// AT24C64_W(array_temp,Addr_timed_trip,3);
		// }
		/* 		else
		{
			ERR_data_sent(ERR_NO_REQUEST);
			return 2;
		}
		*/
		return 0;
	}
	else
	{
		ERR_data_sent(ERR_NO_REQUEST);
		return 2;
	}
}

//д��ѹ�������ֵ
unsigned char Write_vol_setpoint(unsigned char fact_tmp)
{
	unsigned char i,array_temp[6],array_tmp[3];
	unsigned char tmp1,tmp2,tmp3;
	if(fact_tmp==1)
	{
		over_vol_code[0] = array_temp[0] = data_array[12+0];
		over_vol_code[1] = array_temp[1] = data_array[12+1];
		if((array_temp[0]>0x99)||(array_temp[1]>0x99))
		{
			ERR_data_sent(ERR_BAD_DATA);
			return 1;
		}
		Vol_uart_g = 0;
		tmp1 = ((over_vol_code[1]>>4)&0x0F);
		tmp2 = ((over_vol_code[1]&0x0F));
		tmp3 = (over_vol_code[0]>>4);
		Vol_uart_g = tmp1*100 + tmp2*10 + tmp3;
		if(Vol_uart_g>=295)       Vol_g = 5;
		else if(Vol_uart_g>=285)  Vol_g = 4;
		else if (Vol_uart_g>=275) Vol_g = 3;
		else if (Vol_uart_g>=265) Vol_g = 2;
		else if (Vol_uart_g>=255) Vol_g = 1;
		else if (Vol_uart_g>=245) Vol_g = 0;
		else                    Vol_g = 0;
		//W_EEP(45,Vol_g);//���µĹ�ѹ����ֵд��E2
//		H_H_V = D_HV_Array[Vol_g];//�����������������ֵ
		array_tmp[0]=Vol_g ;
		MODIFY_EEP_W(Addr_Vol_g,array_tmp,1,0xA0);
		
		//	    while(Vol_g!=R_EEP(45))
		//W_EEP(45,Vol_g);		
		MODIFY_EEP_W(Addr_over_vol,array_temp,2,0xA0);
		return 0 ;
	}
	else if(fact_tmp==2)
	{
		under_vol_code[0] = array_temp[0] = data_array[12+0];
		under_vol_code[1] = array_temp[1] = data_array[12+1];
		if((array_temp[0]>0x99)||(array_temp[1]>0x99))
		{
			ERR_data_sent(ERR_BAD_DATA);
			return 1;
		}
		Vol_uart_q = 0;
		tmp1 = ((under_vol_code[1]>>4)&0x0F);
		tmp2 = ((under_vol_code[1]&0x0F));
		tmp3 = (under_vol_code[0]>>4);
		Vol_uart_q = tmp1*100 + tmp2*10 + tmp3;
		if(Vol_uart_q<=144) Vol_q = 0;
		else if (Vol_uart_q<=154) Vol_q = 1;
		else if (Vol_uart_q<=164) Vol_q = 2;
		else if (Vol_uart_q<=174) Vol_q = 3;
		else if (Vol_uart_q<=184) Vol_q = 4;
		else if (Vol_uart_q<=194) Vol_q = 5;
		else if (Vol_uart_q<=204) Vol_q = 6;		
		else                    Vol_q = 6;    
		//W_EEP(46,Vol_q);//���µ�Ƿѹ����ֵд��E2
//		H_L_V = D_LV_Array[Vol_q];//�����������������ֵ
		array_tmp[0]=Vol_q ;
		MODIFY_EEP_W(Addr_Vol_q,array_tmp,1,0xA0);
		//  while(Vol_q!=R_EEP(46))
		//W_EEP(46,Vol_q); 
		//	AT24C64_W(array_temp,Addr_under_vol,1);
		MODIFY_EEP_W(Addr_under_vol,array_temp,2,0xA0);
		return 0;
	}
	else if(fact_tmp==3)
	{
		break_phase_code[0]  = array_temp[0] = data_array[12+0];
		break_phase_code[1]  = array_temp[1] = data_array[12+1];
		if((array_temp[0]>0x99)||(array_temp[1]>0x99))
		{
			ERR_data_sent(ERR_BAD_DATA);
			return 1;
		}

		H_D_V = BCDtoDec(break_phase_code,2)/10;
		H_D_V = ((H_D_V*7)>>1)-109;
		MODIFY_EEP_W(Addr_break_phase,array_temp,2,0xA0);
		//MODIFY_EEP_W(array_temp,Addr_break_phase,2,2);		
		return 0;
	}
	else if((fact_tmp==0xff)||(fact_tmp==0x04))
	{
		over_vol_code[0]  = array_temp[0] = data_array[12+0];
		over_vol_code[1]  = array_temp[1] = data_array[12+1];
		under_vol_code[0] = array_temp[2] = data_array[12+2];
		under_vol_code[1] = array_temp[3] = data_array[12+3];
		break_phase_code[0] = array_temp[4] = data_array[12+4];
		break_phase_code[1] = array_temp[5] = data_array[12+5];
		for(i=0;i<6;i++)
		{
			if(array_temp[i]>0x99)
			{
				ERR_data_sent(ERR_BAD_DATA);
				return 1;
			}
		}
		Vol_uart_g = 0;
		tmp1 = ((over_vol_code[1]>>4)&0x0F);
		tmp2 = ((over_vol_code[1]&0x0F));
		tmp3 = (over_vol_code[0]>>4);
		Vol_uart_g = tmp1*100 + tmp2*10 + tmp3;
		if(Vol_uart_g>=295)      Vol_g = 5;
	  else if(Vol_uart_g>=285) Vol_g = 4;
		else if (Vol_uart_g>=275) Vol_g = 3;
		else if (Vol_uart_g>=265) Vol_g = 2;
		else if (Vol_uart_g>=255) Vol_g = 1;
		else if (Vol_uart_g>=245) Vol_g = 0;
		else                    Vol_g = 0;
		//W_EEP(45,Vol_g);//���µĹ�ѹ����ֵд��E2
//		H_H_V = D_HV_Array[Vol_g];//�����������������ֵ
		//  while(Vol_g!=R_EEP(45))
		//W_EEP(45,Vol_g);	
		array_tmp[0]=Vol_g ;
		MODIFY_EEP_W(Addr_Vol_g,array_tmp,1,0xA0);
		
		Vol_uart_q = 0;
		tmp1 = ((under_vol_code[1]>>4)&0x0F);
		tmp2 = ((under_vol_code[1]&0x0F));
		tmp3 = (under_vol_code[0]>>4);
		Vol_uart_q = tmp1*100 + tmp2*10 + tmp3;
		if(Vol_uart_q<=144) Vol_q = 0;
		else if (Vol_uart_q<=154) Vol_q = 1;
		else if (Vol_uart_q<=164) Vol_q = 2;
		else if (Vol_uart_q<=174) Vol_q = 3;
		else if (Vol_uart_q<=184) Vol_q = 4;
		else                    Vol_q = 4;    
		//W_EEP(46,Vol_q);//���µ�Ƿѹ����ֵд��E2
//		H_L_V = D_LV_Array[Vol_q];//�����������������ֵ
		array_tmp[0]=Vol_q ;
		MODIFY_EEP_W(Addr_Vol_q,array_tmp,1,0xA0);
		//  while(Vol_q!=R_EEP(46))
		//W_EEP(46,Vol_q); 		
		MODIFY_EEP_W(Addr_over_vol,array_tmp,6,0xA0);	
		//MODIFY_EEP_W(array_temp,Addr_over_vol,6,2);
		return 0;
	}
	else
	{
		ERR_data_sent(ERR_NO_REQUEST);
		return 2;
	}
}
unsigned char Write_Overload_setpoint(unsigned char fact_tmp)
{
	if(fact_tmp==0x01)
	{
		//д���س���ʱ�ѿ۵�������ֵIr
	}
	else if(fact_tmp==0x02)
	{
		  //���س���ʱʱ���趨ֵtr
	}
	else if(fact_tmp==0x04)
	{
		  //���س���ʱ��������
	}
	else if(fact_tmp==0xFF)
	{
		  //���س���ʱ�����й�����
	}
}
unsigned char Write_DY_setpoint(unsigned char fact_tmp)
{
	if(fact_tmp==0x01)
	{
		//��·����ʱ�ѿ۵�������ֵIsd
	}
	else if(fact_tmp==0x02)
	{
		  //��·����ʱʱ���趨ֵtsd
	}
	else if(fact_tmp==0x04)
	{
		  //��·����ʱ��������
	}
	else if(fact_tmp==0xFF)
	{
		  //��·����ʱ�����й�����
	}
}
unsigned char Write_SD_setpoint(unsigned char fact_tmp)
{
	if(fact_tmp==0x01)
	{
		//��·˲ʱ�ѿ۵�������ֵIi
	}
	else if(fact_tmp==0x02)
	{
		  //��·˲ʱ��������
	}
	else if(fact_tmp==0xFF)
	{
		  //��·˲ʱ������ز���
	}
}
unsigned char Write_LD_setpoint(unsigned char fact_tmp)
{
	if(fact_tmp==0x01)
	{
		//©�籣������ֵ
	}
	else if(fact_tmp==0x02)
	{
		  //©�籣����ʱʱ��
	}
	else if(fact_tmp==0x04)
	{
		  //�ʣ�಻��������
	}
	else if(fact_tmp==0x08)
	{
		  //©�籣������
	}
	else if(fact_tmp==0xFF)
	{
		  //©�籣����ز���
	}
}
unsigned char Write_Chz_Delaytime_setpoint(unsigned char fact_tmp)
{
	if(fact_tmp==0x00)
	{
		  //д�غ�բ��ʱʱ��
	}
}
unsigned char Write_Overvol_setpoint(unsigned char fact_tmp)
{
	if(fact_tmp==0x01)
	{
		  //��ѹ��������ֵ
	}
	else if(fact_tmp==0x02)
	{
		  //��ѹ�غ�բ��ѹ
	}
	else if(fact_tmp==0x04)
	{
		  //��ѹ��բʱ��
	}
	else if(fact_tmp==0x08)
	{
		  //��ѹ��������
	}
	else if(fact_tmp==0xFF)
	{
		  //��ѹ�����й�����
	}
}
unsigned char Write_Undervol_setpoint(unsigned char fact_tmp)
{
	if(fact_tmp==0x01)
	{
		  //Ƿѹ��������ֵ
	}
	else if(fact_tmp==0x02)
	{
		  //Ƿѹ�غ�բ��ѹ
	}
	else if(fact_tmp==0x04)
	{
		  //Ƿѹ��բʱ��
	}
	else if(fact_tmp==0x08)
	{
		  //Ƿѹ��������
	}
	else if(fact_tmp==0xFF)
	{
		  //Ƿѹ�����й�����
	}
}
unsigned char Write_Lossphase_setpoint(unsigned char fact_tmp)
{
	if(fact_tmp==0x01)
	{
		  //ȱ�ౣ������
	}
	else if(fact_tmp==0x02)
	{
		  //ȱ�ౣ��ʱ��
	}
	else if(fact_tmp==0x03)
	{
		  //ȱ�ౣ������
	}
	else if(fact_tmp==0xFF)
	{
		  //ȱ�ౣ���������
	}
}
unsigned char Write_Errorphase_setpoint(unsigned char fact_tmp)
{
	if(fact_tmp==0x01)
	{
		  //���ౣ����ѹ
	}
	else if(fact_tmp==0x02)
	{
		  //���ౣ��ʱ��
	}
	else if(fact_tmp==0x04)
	{
		  //���ౣ������
	}
	else if(fact_tmp==0xFF)
	{
		  //���ౣ����ز���
	}
}
void Cur_uart_change(unsigned long tmp)
{
	
	unsigned char i,array_tmp[3];
	unsigned int  fact1,fact2;
	if(Type_Cur==0)//100 20~100
	{
		for(i=0;i<9;i++)
		{
			if((tmp>=(15+10*i))&&(tmp<=(14+10*(i+1))))
			{
				D_Cur = i;
				break;
			}
		}
		if(tmp<15)
		{
			D_Cur = 0;
		}
		if(tmp>194)
		{
			D_Cur = 8;
		}
		array_tmp[0]=D_Cur ;
		//W_EEP(0x08,D_Cur);//���µĶ���ص���д��E2
		MODIFY_EEP_W(Addr_D_Cur,array_tmp,1,0xA0);
		Cur_Switch(Type_Cur);
		//while(D_Cur!=R_EEP(0x08))
		//W_EEP(0x08,D_Cur);
//		H_Cur=D_C1_Array[D_Cur];
//		H5_Cur=D_C15_Array[D_Cur];
//		I2=D_C19_Array[D_Cur];
	}
	if(Type_Cur==1)//250 
	{
		for(i=0;i<20;i++)
		{
			if((tmp>=(55+10*i))&&(tmp<=(54+10*(i+1))))
			{
				D_Cur = i;
				break;
			}
		}
		if(tmp<55)
		{
			D_Cur = 0;
		}
		if(tmp>254)
		{
			D_Cur = 19;
		}
		//		W_EEP(0x08,D_Cur);//���µĶ���ص���д��E2
		array_tmp[0]=D_Cur ;
		MODIFY_EEP_W(Addr_D_Cur,array_tmp,1,0xA0);
		Cur_Switch(Type_Cur);
		//	while(D_Cur!=R_EEP(0x08))
		//	W_EEP(0x08,D_Cur);
//		H_Cur=D_C1_Array[D_Cur];
//		H5_Cur=D_C15_Array[D_Cur];
//		I2=D_C19_Array[D_Cur];
	}
	if(Type_Cur==2)//400
	{
		for(i=0;i<11;i++)
		{
			fact1 =195+20*i;
			fact2 =194+20*(i+1);
			if((tmp>=fact1)&&(tmp<=fact2))
			{
				D_Cur = i;
				break;
			}

		}
		if(tmp<194)
		{
			D_Cur = 0;//
		}
		if(tmp>404)
		{
			D_Cur = 10;
		}
		//W_EEP(0x08,D_Cur);//���µĶ���ص���д��E2
		array_tmp[0]=D_Cur ;
		MODIFY_EEP_W(Addr_D_Cur,array_tmp,1,0xA0);
		Cur_Switch(Type_Cur);
		//while(D_Cur!=R_EEP(0x08))
		//W_EEP(0x08,D_Cur);
//		H_Cur=D_C1_Array[D_Cur];
//		H5_Cur=D_C15_Array[D_Cur];
//		I2=D_C19_Array[D_Cur];
	}
	if(Type_Cur==3)//750
	{
		for(i=0;i<16;i++)
		{
			fact1 =195+30*i;
			fact2 =194+30*(i+1);
			if((tmp>=fact1)&&(tmp<=fact2))
			{
				D_Cur = i;
				break;
			}
		}
		
		if(tmp<205)
		{
			D_Cur = 0;
		}
		if(tmp>634)
		{
			D_Cur = 15;
		}
		//putchar(D_Cur);
		//W_EEP(0x08,D_Cur);//���µĶ���ص���д��E2
		array_tmp[0]=D_Cur ;
		MODIFY_EEP_W(Addr_D_Cur,array_tmp,1,0xA0);
		Cur_Switch(Type_Cur);
		//while(D_Cur!=R_EEP(0x08))
		//W_EEP(0x08,D_Cur);
//		H_Cur=D_C1_Array[D_Cur];
//		H5_Cur=D_C15_Array[D_Cur];
//		I2=D_C19_Array[D_Cur];
		
	}
}


//д�����������ֵ
unsigned char Write_cur_setpoint(unsigned char fact_tmp)
{
	unsigned char i,array_temp[6],tmp1,tmp2,tmp3,tmp4,tmp5;
	if(fact_tmp==1)
	{
		rated_current_code[0] = array_temp[0] = data_array[12+0];
		rated_current_code[1] = array_temp[1] = data_array[12+1];
		rated_current_code[2] = array_temp[2] = data_array[12+2];
		for(i=0;i<3;i++)
		{
			if(array_temp[i]>0x99)
			{
				ERR_data_sent(ERR_BAD_DATA);
				return 1;
			}
		}
		tmp1 = (rated_current_code[0]>>4);//��
		//putchar(tmp1);
		tmp2 = (rated_current_code[1]&0x0F);//ʮ
		//putchar(tmp2);
		tmp3 = (rated_current_code[1]>>4);//��
		//putchar(tmp3);
		tmp4 = (rated_current_code[2]&0x0F);//ǧ
		//putchar(tmp4);
		tmp5 = (rated_current_code[2]>>4);//��
		//putchar(tmp5);
		rated_cur = tmp5*10000 + tmp4*1000 + tmp3*100 + tmp2*10 + tmp1;
		Cur_uart_change(rated_cur);
		MODIFY_EEP_W(Addr_rated_current,array_temp,3,0xA0);
		//MODIFY_EEP_W(array_temp,Addr_rated_current,3,2);
		return 0;
	}
	else if(fact_tmp==2)
	{
		over_current_code[0] = array_temp[0] = data_array[12+0];
		if(array_temp[0]>0x99)
		{
			ERR_data_sent(ERR_BAD_DATA);
			return 1;
		}
		MODIFY_EEP_W(Addr_over_current,over_current_code,1,0xA0);
		return 0;
	}
	else if(fact_tmp==0xff)
	{
		for(i=0;i<4;i++)
		{
			if(array_temp[i]>0x99)
			{
				ERR_data_sent(ERR_BAD_DATA);
				return 1;
			}
		}
		rated_current_code[0] = array_temp[0] = data_array[12+0];
		rated_current_code[1] = array_temp[1] = data_array[12+1];
		rated_current_code[2] = array_temp[2] = data_array[12+2];
		over_current_code[0] = array_temp[3] = data_array[12+3];
		for(i=0;i<3;i++)
		{
			if(array_temp[i]>0x99)
			{
				ERR_data_sent(ERR_BAD_DATA);
				return 1;
			}
		}
		tmp1 = (rated_current_code[0]>>4);//��
		tmp2 = (rated_current_code[1]&0x0F);//ʮ
		tmp3 = (rated_current_code[1]>>4);//��
		tmp4 = (rated_current_code[2]&0x0F);//ǧ
		tmp5 = (rated_current_code[2]>>4);//��
		rated_cur = tmp5*10000 + tmp4*1000 + tmp3*100 + tmp2*10 + tmp1;
		Cur_uart_change(rated_cur);
		MODIFY_EEP_W(Addr_over_current,over_current_code,1,0xA0);
		//MODIFY_EEP_W(over_current_code,Addr_over_current,1,2);
		//AT24C64_W(array_temp,Addr_over_current,4);
		return 0;
	}
	else
	{
		ERR_data_sent(ERR_NO_REQUEST);
		return 2;
	}
}

//дԤ��բʱ��
unsigned char Write_fenzha_tim(unsigned char fact_tmp)
{
	unsigned char array_temp[6];
	if(fact_tmp==1)
	{
		remote_trip_time[0] = array_temp[0] = data_array[12];
		remote_trip_time[1] = array_temp[1] = data_array[13];
		if((array_temp[0]>0x99)||(array_temp[1]>0x99))
		{
			ERR_data_sent(ERR_BAD_DATA);
			return 1;
		}
		MODIFY_EEP_W(Addr_remote_trip,array_temp,2,0xA0);
		if(remote_trip_time[0]==0)
		{
			if(isfenzha==0)
			{
				F_yc_fenzha = 1;
			}
			//Trip_Action();
			//F_gz_disp = FZ_YC;
			//Write_Record(trip_reason_remote,1);
		}
		else
		{			
			if(remote_trip_time[1]==0x02)                   //02Ϊ��  60S 1S��50MS  50*60
			{
				T_yc_fenzha = 3000*remote_trip_time[0];
			}	
			if(remote_trip_time[1]==0x03)                   //03��ʾСʱ
			{
				T_yc_fenzha = 60*3000*remote_trip_time[0];
			}
			F_fenzha_js = 1;			
		}
		return 0;		
	}
	else if(fact_tmp==2)
	{
		//Ԥ��բȡ��
		F_fenzha_js = 0;
		remote_trip_time[0] = remote_trip_time[1] = 0;  
		T_yc_fenzha_js = 0;
		T_yc_fenzha = 0;
		
		return 0;	
	}
	else 
	{
		ERR_data_sent(ERR_NO_REQUEST);
		return 2;
	}
}
//дԤ��բʱ��
unsigned char Write_hezha_tim(unsigned char fact_tmp)
{
	unsigned char array_temp[6];
	if(fact_tmp==1)
	{
		remote_close_time[0] = array_temp[0] = data_array[12];
		remote_close_time[1] = array_temp[1] = data_array[13];
		if((array_temp[0]>0x99)||(array_temp[1]>0x99))
		{
			ERR_data_sent(ERR_BAD_DATA);
			return 1;
		}
		MODIFY_EEP_W(Addr_remote_close,array_temp,2,0xA0);
		if(remote_close_time[0]==0)
		{
			if(isfenzha!=0)
			{
				F_yc_hezha = 1;
			}
			ctrl_code = 0x1C;
		}
		else
		{
			if(remote_close_time[1]==0x02)
			{
				T_yc_hezha = 3000*remote_close_time[0];
			}
			if(remote_close_time[1]==0x03)
			{
				T_yc_hezha = 60*3000*remote_close_time[0];
			}
			F_hezha_js = 1;
		}
		return 0;
	}
	else if(fact_tmp==2)
	{
		//Ԥ��բȡ��
		F_hezha_js = 0;
		remote_close_time[0] = remote_close_time[1] = 0;  
		T_yc_fenzha_js = 0;
		T_yc_fenzha = 0;
		return 0;
	}
	else
	{
		ERR_data_sent(ERR_NO_REQUEST);
		return 2;
	}
}
//дģ���ѿ�ʱ��
unsigned char Write_trip_tim(unsigned char fact_tmp)
{
	unsigned char array_temp[6];
	if(fact_tmp==1)
	{
		analog_trip_time[0] = array_temp[0] = data_array[12];
		analog_trip_time[1] = array_temp[1] = data_array[13];
		if((array_temp[0]>0x99)||(array_temp[1]>0x99))
		{
			ERR_data_sent(ERR_BAD_DATA);
			return 1;
		}
		MODIFY_EEP_W(Addr_analog_trip,array_temp,2,0xA0);
		//MODIFY_EEP_W(array_temp,Addr_analog_trip,2,2);		
		if(analog_trip_time[0]==0)
		{
			F_an_fenzha = 1;
		}
		else
		{
			
			if(analog_trip_time[1]==0x02)
			{
				T_an_fenzha = 3000*analog_trip_time[0];
			}	
			if(analog_trip_time[1]==0x03)
			{
				T_an_fenzha = 60*3000*analog_trip_time[0];
			}
			F_an_js = 1;
			
		}
		return 0;		
	}
	else if(fact_tmp==2)
	{
		//Ԥ��բȡ��
		F_an_js = 0;
		analog_trip_time[0] = analog_trip_time[1] = 0;  
		T_an_fenzha = 0;
		return 0;	
	}
	else 
	{
		ERR_data_sent(ERR_NO_REQUEST);
		return 2;
	}
}


unsigned char Event_clear(void)
{
	unsigned char array_temp[20],F_clear_all;
	int Addr_factor,lenth;
	F_clear_all = 0;
	if((DI3==0xFF)&&(DI2==0xff)&&(DI1==0xFF)&&(DI0==0xFF))
	{
		F_clear_all = 1;
		Num_clearall = Num_clearall + 1;
		DectoBCD(array_temp,Num_clearall, 3); 
		MODIFY_EEP_W(Addr_clear_num,array_temp,3,0xA0);
		return 0 ;
	}
	if(((DI3==0x03)&&(DI2==0x81)&&(DI1==00)&&(DI0==0xFF))||(F_clear_all == 1))
	{
		//�ѿ۴���
		array_temp[0] = array_temp[1] = 0;
		MODIFY_EEP_W(Addr_trip_num,array_temp,2,0xA0);
		//close ����
		array_temp[0] = array_temp[1] = 0;
		MODIFY_EEP_W(Addr_close_num,array_temp,2,0xA0);
		//©���ѿ۴���		
		array_temp[0] = array_temp[1] = 0;
		MODIFY_EEP_W(Addr_leak_num,array_temp,2,0xA0);
		//�����ѿ۴���		
		array_temp[0] = array_temp[1] = 0;
		MODIFY_EEP_W(Addr_current_num,array_temp,2,0xA0);
		//��ѹ�ѿ۴���
		array_temp[0] = array_temp[1] = 0;
		MODIFY_EEP_W(Addr_vol_num,array_temp,2,0xA0);
		//�ֶ��ѿ۴���		
		array_temp[0] = array_temp[1] = 0;
		MODIFY_EEP_W(Addr_hand_num,array_temp,2,0xA0);
		//�����ѿ۴���
		array_temp[0] = array_temp[1] = 0;
		MODIFY_EEP_W(Addr_zero_num,array_temp,2,0xA0);
		//�����ѿ۴���		
		array_temp[0] = array_temp[1] = 0;
		MODIFY_EEP_W(Addr_test_num,array_temp,2,0xA0);		
		if(F_clear_all == 0)  return 0 ;
	}	
	if(((DI3==0x03)&&(DI2==0x82)&&(DI1==00)&&(DI0==0xFF))||(F_clear_all == 1))
	{
		Addr_factor = Addr_max_leak;
		lenth =  288;
//		EEPROM_C(Addr_factor,lenth);
		
		if(F_clear_all == 0)  return 0 ;
	}
	if(((DI3==0x03)&&(DI2==0x82)&&(DI1==01)&&(DI0==0xFF))||(F_clear_all == 1))
	{
		Addr_factor = Addr_max_Avol;
		lenth =  288;
//		EEPROM_C(Addr_factor,lenth);	
		
		if(F_clear_all == 0)  return 0 ;		
	}
	if(((DI3==0x03)&&(DI2==0x82)&&(DI1==02)&&(DI0==0xFF))||(F_clear_all == 1))
	{
		Addr_factor = Addr_max_Bvol;
		lenth =  288;
//		EEPROM_C(Addr_factor,lenth);
		
		if(F_clear_all == 0)  return 0 ;
	}
	if(((DI3==0x03)&&(DI2==0x82)&&(DI1==03)&&(DI0==0xFF))||(F_clear_all == 1))
	{
		Addr_factor = Addr_max_Cvol;
		lenth =  288;
//		EEPROM_C(Addr_factor,lenth);
		
		if(F_clear_all == 0)  return 0 ;
	}
	if(((DI3==0x03)&&(DI2==0x82)&&(DI1==04)&&(DI0==0xFF))||(F_clear_all == 1))
	{
		Addr_factor = Addr_max_Acur;
		lenth =  288;
//		EEPROM_C(Addr_factor,lenth);
		
		if(F_clear_all == 0)  return 0 ;
	}
	if(((DI3==0x03)&&(DI2==0x82)&&(DI1==05)&&(DI0==0xFF))||(F_clear_all == 1))
	{
		Addr_factor = Addr_max_Bcur;
		lenth =  288;
//		EEPROM_C(Addr_factor,lenth);
		
		if(F_clear_all == 0)  return 0 ;
	}
	if(((DI3==0x03)&&(DI2==0x82)&&(DI1==06)&&(DI0==0xFF))||(F_clear_all == 1))
	{
		Addr_factor = Addr_max_Ccur;
		lenth =  288;
//		EEPROM_C(Addr_factor,lenth);
		if(F_clear_all == 0)  return 0 ;
	}
	if(((DI3==0x03)&&(DI2==0x83)&&(DI1==00)&&(DI0==0xFF))||(F_clear_all == 1))
	{
		Addr_factor = Addr_min_leak;
		lenth =  288;
//		EEPROM_C(Addr_factor,lenth);
		if(F_clear_all == 0)  return 0 ;
	}
	if(((DI3==0x03)&&(DI2==0x83)&&(DI1==01)&&(DI0==0xFF))||(F_clear_all == 1))
	{
		Addr_factor = Addr_min_Avol;
		lenth =  288;
//		EEPROM_C(Addr_factor,lenth);
		if(F_clear_all == 0)  return 0 ;
	}
	if(((DI3==0x03)&&(DI2==0x83)&&(DI1==02)&&(DI0==0xFF))||(F_clear_all == 1))
	{
		Addr_factor = Addr_min_Bvol;
		lenth =  288;
//		EEPROM_C(Addr_factor,lenth);

		if(F_clear_all == 0)  return 0 ;
	}
	if(((DI3==0x03)&&(DI2==0x83)&&(DI1==03)&&(DI0==0xFF))||(F_clear_all == 1))
	{
		Addr_factor = Addr_min_Cvol;
		lenth =  288;
//		EEPROM_C(Addr_factor,lenth);

		if(F_clear_all == 0)  return 0 ;
	}
	if(((DI3==0x03)&&(DI2==0x83)&&(DI1==04)&&(DI0==0xFF))||(F_clear_all == 1))
	{
		Addr_factor = Addr_min_Acur;
		lenth =  288;
//		EEPROM_C(Addr_factor,lenth);

		if(F_clear_all == 0)  return 0 ;
	}
	if(((DI3==0x03)&&(DI2==0x83)&&(DI1==05)&&(DI0==0xFF))||(F_clear_all == 1))
	{
		Addr_factor = Addr_min_Bcur;
		lenth =  288;
//		EEPROM_C(Addr_factor,lenth);

		if(F_clear_all == 0)  return 0 ;
	}
	if(((DI3==0x03)&&(DI2==0x83)&&(DI1==06)&&(DI0==0xFF))||(F_clear_all == 1))
	{
		Addr_factor = Addr_min_Ccur;
		lenth =  288;
//		EEPROM_C(Addr_factor,lenth);

		if(F_clear_all == 0)  return 0 ;
	}

	if(((DI3==0x03)&&(DI2==0x88)&&(DI1==00)&&(DI0==0xFF))||(F_clear_all == 1))
	{
		Addr_factor = Addr_event_leak;
		lenth =  150;
//		EEPROM_C(Addr_factor,lenth);
		if(F_clear_all == 0)  return 0 ;
	}
	if(((DI3==0x03)&&(DI2==0x8D)&&(DI1==00)&&(DI0==0xFF))||(F_clear_all == 1))
	{
		Addr_factor = Addr_event_self;
		lenth =  260;
//		EEPROM_C(Addr_factor,lenth);

		if(F_clear_all == 0)  return 0 ;
	}
	if(((DI3==0x03)&&(DI2==0x8E)&&(DI1==00)&&(DI0==0xFF))||(F_clear_all == 1))
	{
		Addr_factor = Addr_event_trip;
		lenth =  250;
//		EEPROM_C(Addr_factor,lenth);

		if(F_clear_all == 0)  return 0 ;
	}
	if(((DI3==0x03)&&(DI2==0x8F)&&(DI1==00)&&(DI0==0xFF))||(F_clear_all == 1))
	{
		Addr_factor = Addr_event_alarm;
		lenth =  120;
//		EEPROM_C(Addr_factor,lenth);

		//if(F_clear_all == 0) 
		return 0 ;
	}
	return 1;
}
//void UART_LCD_process(void)
//{
//	if((LCD_Receive_last[3]&0x80))  //����Ϊ�ӻ�->���� 
//		{
//			if((LCD_Receive_last[3]&0x40) == 0) //����
//			{
//				switch(LCD_Receive_last[3]&0x1F)
//				{
//					case 0x11:  Read_Data_process(); break;  //��վ���������
//					
//					case 0x14:            DI3 = LCD_Receive_last[5];
//																DI2 = LCD_Receive_last[6];
//																DI1 = LCD_Receive_last[7];
//																DI0 = LCD_Receive_last[8];
//														//		WorRrespond_process(); break; //��վ����д����
//	//				case Ctrl_WARN:       Warn_process();break;        //
//	//				case Ctrl_PRO:        Protect_process();break;     //
//				}
//			}
//			else  //Ӧ�� LCD_Receive_last[3]&0x40) == 1
//			{
//				if((LCD_Receive_last[3]&0x20) == 0)  //����Ӧ��
//				{
//					switch(LCD_Receive_last[3]&0x1F)  
//					{
//						case 0x11:  WorRrespond_process(); break;  //��վ��������ݴ�վ������Ӧ��
//						case 0x14:/* Response_By_LCD(0); */break;  //��վд���ݴ�վ������Ӧ��
//						case 0x0C:       Warn_process();break;        //��վ���ͱ�����Ϣ��վ������Ӧ��
//						case 0x12:        Protect_process();break;
//					}
//				}
//				else    //�쳣Ӧ�� (LCD_Receive_last[3]&0x20) == 1
//				{
//					//�쳣Ӧ����
//				}
//			}
//		}
//	//USART_LCD_Transmit(15);////���͵�ѹ�������ʵ�ʵʱ����
//	/*��ӦLCD������Ƭ��Ϊ��վ��LCDģ��Ϊ��վ�������ò���Ϊ��վӦ��
//	
//	ctrl_code  0x91->��վ���������   
//	           0x94->��վ����д/�޸�����
//             0x92->��վ������ı�������
//  	
//	*/
//	

//	//ctrl_code
//}
void UART_process(void)
{

	//unsigned char tmp_test[30];//����ָ���
	//unsigned int i;
	//unsigned char pre_I_class,pre_L_class,pre_HV_class,pre_LV_class,pre_state,cs_temp;
	//cs_temp = 0;
	//delay();  //�²ⷢ�͹�������ϵ���ʱ2011.1.24��
	//E485 = 1;
	//for(i=0;i<10000;i++); 
	//COM_type = GETDATA;   //11 ��վ��������� 12���������� 14д���� 18�޸����� 1C�豸���� ������
	if((ctrl_code==0x11)||(ctrl_code==0x12)||(ctrl_code==0x14)||(ctrl_code==0x12)||(ctrl_code==0x18)||(ctrl_code==0x1C)||(ctrl_code==0x1F)||(ctrl_code==0x1E))
	{
		DI0 = data_array[0];
		DI1 = data_array[1];
		DI2 = data_array[2];
		DI3 = data_array[3];
	}
	else if(ctrl_code==0x1B)  //  ��������
	{
		DI0 = data_array[8];
		DI1 = data_array[9];
		DI2 = data_array[10];
		DI3 = data_array[11];
	}
	/****************************
        �㲥
*****************************/

	  	
			if(ctrl_code==0x08)//0x08�㲥Уʱ	
			{
				 DI0 = data_array[0];
			   if(F_guangbo==1)
	      {

					F_guangbo = 0;
					Broadcasting_time();	
						
					TXJZ_SJ=1;
	      }
		  }
			
	     else if(ctrl_code==0x09)//0x09  �㲥У׼����
			 {
				 DI0 = data_array[0];
				if(DI0==0x01)//�㲥����У׼
				{
					unsigned char array_temp[5];
				
					    TXJZ_start=1;
					    F_sssj=10;
				
					
//					 nomal_disp();
					
				  F_guangbo = 0;
					factor_first_init(0);
					
					Type_Cur=data_array[1];
					array_temp[0]=data_array[1] ;
					MODIFY_EEP_W(Addr_Type_Cur,array_temp,1,0xA0); //�����Ǽܵȼ�
					delay_ms(10);		
					
					factors_init();
					delay_ms(50);			
					
//					  ctrlword[1]=0;
//						ctrlword[2]=0;
//					  ctrlword[3]=0;
//						ctrlword2_analyze();
//						ctrlword3_analyze();
//					  ctrlword4_analyze();
					
					F_trip_ld=1;//©��
					F_TB_trip=0;//ͻ��
					F_trip_sy=0;//ʧѹ
					F_trip_xq=0;//ȱ��
					F_trip_gy=0;//��ѹ
					F_trip_qy=0;//Ƿѹ
					F_trip_QL=0;//����
					F_trip_gl=0;//����
					F_ip=0;//����
					F_ip_3=0;//˲ʱ
					duandian=0;//ͣ����բ


				}
				
				
				
				else if(DI0==0x02)//�㲥�˳�У׼
				{
					unsigned char array_temp[30];
								

					  TXJZ_start=0;
					  F_sssj=0;
					 	LEDA_FLAG=1;//������ʼ��ʱ
					 
				 TXJZ_SJ=0;//ͨѶʱ��
				 TXJZ_DY_A=0;//ͨѶ��ѹ
				 TXJZ_DY_B=0;//ͨѶ��ѹ
				 TXJZ_DY_C=0;//ͨѶ��ѹ
				 TXJZ_LD=0;//ͨѶ©��
				 TXJZ_DL_A=0;//ͨѶ����
				 TXJZ_DL_B=0;//ͨѶ����
				 TXJZ_DL_C=0;//ͨѶ����
				 
				 


		EEPROM_R(Addr_crtl_word1,array_temp,1,0xA0);
	  ctrlword[0]=array_temp[0];

		EEPROM_R(Addr_crtl_word2,array_temp,1,0xA0);
    ctrlword[1]=array_temp[0];
		EEPROM_R(Addr_crtl_word3,array_temp,1,0xA0);
     ctrlword[2]=array_temp[0];
		EEPROM_R(Addr_crtl_word4,array_temp,1,0xA0);
     ctrlword[3]=array_temp[0];
		EEPROM_R(Addr_crtl_word5,array_temp,1,0xA0);
	 ctrlword[4]=array_temp[0];
	
				ctrlword1_analyze();
				ctrlword2_analyze();
				ctrlword3_analyze();
				ctrlword4_analyze();
					
				 delay_ms(1000);

				}

			}
	/****************************
		�����룺0x11  ������
*****************************/

			else if(ctrl_code==0x11) //������
	{
		if(DI3==0x02)//��ǰ����
		{
			delay_uart();
			if(DI2==0x01)
			{
				Read_variable_vol(DI1,2);//����ѹ����
			}
			else if(DI2==0x02)
			{
				Read_variable_cur(DI1,3);//����������
			}
					else if(DI2==0x03)
			{
				Read_variable_Power(DI1,3);//���й����ʱ���
			}
				else if(DI2==0x04)
			{
				Read_reactive_Power(DI1,3);//���޹����ʱ���
			}
			else if(DI2==0x06)
			{
				Read_factor_Power(DI1,5);//����������
			}
			else if((DI2==0x07)&&(DI1==0x00))
			{
				 Energy_reset();        //��������  
			}
				else if((DI2==0x07)&&(DI1==0x01))
			{
				  cal();//У׼
			}
				else if((DI2==0x07)&&(DI1==0x02))
			{
				  Offset_cal();//ƫ��У׼
			}
			else if(DI2==0x90)
			{
				Read_variable_leak(DI1);//��ʣ�����
			}
			else if(DI2==0x91)
			{
				Read_variable_leak_class(DI1,2);//��ʣ�������λ  �ʣ���������ֵ
			}
				else if((DI2==0x80)&&(DI1==0x00))
			{
				Read_frequency_power(DI0,5);//������Ƶ�ʺ���ƽ������
			}
			else
			{
				ERR_data_sent(ERR_NO_REQUEST);
			}
		}
		else if(DI3==0x03)//�ۼƼ�¼�����ֵ���¼���¼  
		{
			delay_uart();
			if((DI2==0x30)&&(DI1==0x01))
			{
				Read_num_dataclear();//�����������
			}
			else if((DI2==0x81)&&(DI1==0x00))
			{
				Read_num_trip(DI0);//����բ����
			}
			else if((DI2==0x81)&&(DI1==0x01)&&(DI0==0x01))
			{
				//delay_uart();
				Read_num_protectoff();//���˳�©�籣������
			}
			else if((DI2==0x81)&&(DI1==0x02)&&(DI0==0x01))
			{
				//delay_uart();
				Read_time_run();//��������������ʱ��
			}
			else if(DI2==0x82)
			{
				if(DI1==0x00)
				{
					Read_max_leak(DI0);//��ʣ����������
				}
				else if((DI1>=0x01)&&(DI1<=0x03))
				{
					Read_max_vol(DI1,DI0);//����ѹ���ֵ
				}
				else if((DI1>=0x04)&&(DI1<=0x06))
				{
					Read_max_cur(DI1,DI0);//���������ֵ
				}
				else 
				{
					ERR_data_sent(ERR_NO_REQUEST);
				}
			}
			else if(DI2==0x83)
			{
				
				if(DI1==0x00)
				{
					Read_max_min_leak(DI0);//��ʣ��������ֵ��Сֵ
				}
				else if((DI1>=0x01)&&(DI1<=0x03))
				{
					Read_max_min_vol(DI1,DI0);//  A B C����ѹ���ֵ����Сֵ
				}
				else if((DI1>=0x04)&&(DI1<=0x06))
				{
					Read_max_min_cur(DI1,DI0);// A B C���������ֵ����Сֵ
				}
				else 
				{
					ERR_data_sent(ERR_NO_REQUEST);
				}
			}
			else if(DI2==0x88)
			{
				Read_event_leakover(DI0);//ʣ���������  DI0����
			}
			else if(DI2==0x8D)
			{
				Read_event_leakself(DI0);//�������Լ�  DI0����
			}
			else if(DI2==0x8E)
			{
				Read_event_leaktrip(DI0);//��������բ  DI0����
			}
			else if(DI2==0x8F)
			{
				Read_event_leakalarm(DI0);//ʣ���������   DI0����
			}
			else if(DI2==0x90)
			{
				Read_event_leakrecord(DI1,DI0);//ʣ�������¼   DI0����
			}
			else
			{
				ERR_data_sent(ERR_NO_REQUEST);
			}
		}
		else if(DI3==0x04)//��������
		{
			delay_uart();
			if(DI1==0x01)
			{
				Read_time(DI0);//��ȡ��ǰʱ��
			}
			else if(DI1==0x04)
			{
				Read_factors(DI0);//��ȡ��ǰ����
			}
			else if(DI1==0x05)
			{
				Read_state(DI0);//��ȡ��ǰ����״̬��
			}
			else if(DI1==0x07)
			{
				Read_baud(DI0);//��ȡ��ǰ������
			}
			else if(DI1==0x0C)
			{
				//Read_password(DI0);//��ȡ��ǰ����
			}
			else if(DI1==0x10)
			{
				Read_ctrlword(DI0);//��ȡ��ǰ������
			}
			else if(DI1==0x11)
			{
				Read_leakctrl(DI0);//��ȡ©����Ʋ���
			}
			else if(DI1==0x12)
			{
				Read_timing(DI0);//��ȡ��ʱ����ʱ��
			}
			else if(DI1==0x13)
			{
				Read_vol_setpoint(DI0);//��ȡ��ѹ�������ֵ
			}
			else if(DI1==0x14)
			{
				Read_cur_setpoint(DI0);//��ȡ�����������ֵ
			}
			else
			{
				ERR_data_sent(ERR_NO_REQUEST);
			}
		}
		else if(DI3==0x06)//�ֺ�բʱ��
		{
			delay_uart();
			if(DI2==0x01)
			{
				if(DI1==0x01)
				{
					Read_fenzha_tim(DI0);
				}
				else if(DI1==0x02)
				{
					Read_hezha_tim(DI0);
				}
				else if(DI1==0x03)
				{
					Read_trip_tim(DI0);
				}
				else
				{
					ERR_data_sent(ERR_NO_REQUEST);
				}
			}
		}
		else
		{
			ERR_data_sent(ERR_NO_REQUEST);
		}
		
	}

	
	
	/****************************
		�����룺0x1E   ��˲������ѹ��������©��У׼����
*****************************/
	else if(ctrl_code==0x1E) //��˲������
	{
		if(DI3==0x03)// ��˲��У׼����
		{
			delay_uart();
			if(DI2==0x01)
			{
				if(DI1==0x01)
				{
					Read_SD_AD_Value(DI0,3);//��˲��ADֵ
				}
				else if(DI1==0x02)
				{
					Read_SD_Slope_Value(DI0,3);//��˲��б��ֵ
				}
				else if(DI1==0x03)
				{
					Read_SD_Value(DI0,3);//��˲������ֵ
				}
//				Read_variable_vol(DI1,2);//������
			}
			else if(DI2==0x02)
			{

			}
			
		}
		
		else if(DI3==0x04)// ������У׼����
		{
			if(DI1==0x01)
			{
				Read_DL_AD_Value(DI2,DI0);//������ADֵ
			}
			else if(DI1==0x02)
			{
				Read_DL_XL_Value(DI2,DI0);//������б��ֵ
			}
		}
				
		else if(DI3==0x05)// ����ѹ
		{

				Read_DY_XL_Value(DI2);//��©��б��ֵ

		}
		
		else if(DI3==0x06)// ��©��У׼����
		{

				Read_LD_XL_Value();//��©��б��ֵ

		}
		
		
	}
	
	/****************************
		�����룺0x12  ����������
*****************************/
	else if(ctrl_code==0x12) //����������
	{

	}
	/****************************
		�����룺0x13  ��ͨ�ŵ�ַ
*****************************/
	else if(ctrl_code==0x13) //��ͨ�ŵ�ַ
	{
		delay_uart();
		if(F_addr==1)
		{
			F_addr = 0;
			Read_addr();
		}
		
		
	}
	/****************************
		�����룺0x14  д����
*****************************/
	else if(ctrl_code==0x14) //д����
	{
		if((Password_verification(0)==0)||(Password_verification(0)==1)||(Password_verification(0)==2)) //������֤ͨ��
		{
			if(DI3==0x04)//��������
			{
				delay_uart();
				if(DI1==0x01)
				{
					if(Write_time(DI0)==0)//д��ǰʱ��
					{
						WRITE_DATA_NOMAL();
					}
				}
				else if(DI1==0x04)
				{
					if(Write_factors(DI0)==0)//д��ǰ����
					{
						WRITE_DATA_NOMAL();
					}
				}
				/* else if(DI1==0x07)
			{
				Write_baud(DI0);//д��ǰ������
			}*/
				else if(DI1==0x0C)
				{
					if(Write_password(DI0)==0)//д��ǰ����
					{
						WRITE_DATA_NOMAL();
					}
				}
				else if(DI1==0x10)
				{
					if(Write_ctrlword(DI0)==0)//д��ǰ������
					{
						WRITE_DATA_NOMAL();
					}
				}
				else if(DI1==0x11)
				{
					if(Write_leakctrl(DI0)==0)//д©����Ʋ���
					{
						WRITE_DATA_NOMAL();
					}
				}
				else if(DI1==0x12)
				{
					if(Write_timing(DI0)==0)//д��ʱ����ʱ��
					{
						WRITE_DATA_NOMAL();
					}
				}
				else if(DI1==0x13)
				{
					if(Write_vol_setpoint(DI0)==0)//д��ѹ�������ֵ
					{
						WRITE_DATA_NOMAL();
					}
				}
				else if(DI1==0x14)
				{
					if(Write_cur_setpoint(DI0)==0)//д�����������ֵ
					{
						WRITE_DATA_NOMAL();
					}
				}
				else
				{
					ERR_data_sent(ERR_NO_REQUEST);
				}
			}
			else
			{
				ERR_data_sent(ERR_NO_REQUEST);
			}
			
		}
		else
		{
			ERR_data_sent(ERR_BAD_PASSWORD);
		}
	}

	/****************************
		������:0x15  дͨ�ŵ�ַ
*****************************/
	else if(ctrl_code==0x15) //дͨ�ŵ�ַ
	{
		//if(get_bit(PINC,0)==0)
		{
			delay_uart();
			if(F_addr==1)
			{
				F_addr = 0;
				Write_addr();
			}
		}
	}

	/****************************
		�����룺0x17  ����ͨ������
*****************************/
	else if(ctrl_code==0x17) //����ͨ������
	{
		unsigned char i,cs_temp=0;
		delay_uart();
		if(Write_baud(0)==0)
		{
			format_uart_t_buf();
			UART_T_Buf[0]=UART_T_Buf[7] = 0x68;
			for(i=0;i<6;i++)
			{
				UART_T_Buf[i+1] =  self_addr_code[i];
			}
			UART_T_Buf[8]	= ctrl_code+0x80;
			UART_T_Buf[9] = 0x01;
			UART_T_Buf[10] = baud+0x33; 
			for(i=0;i<11;i++)
			{
				cs_temp =  UART_T_Buf[i] + cs_temp;
			}
			UART_T_Buf[11]	= cs_temp;
			UART_T_Buf[12] =  0x16;
			//20150202���������޸�
//			for(i=0;i<(13);i++)
				for(i=0;i<4;i++)
	{
	UART_S_Buf[i]=0xFE;
	}
				if(F_Dataval==1)
	{
		 //RS485_Send_Data(UART_S_Buf,4);
		 //RS485_Send_Data(UART_T_Buf,14);
	}
	if(F_Dataval1==1)
	{
		 //hongwai_Send_Data(UART_T_Buf,14);
	}
//			//RS485_Send_Data(UART_T_Buf,14);
//			put2char(UART_T_Buf[i]);	
			
			delay_ms(25);
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
		}
	}
	/****************************
		�����룺0x18  �޸�����
*****************************/
	else if(ctrl_code==0x18) //�޸�����
	{
		unsigned char i,cs_temp=0,array_temp[10],F_err;
//		delay_uart();
//		for(i=0;i<4;i++)
//		{
//			put2char(password_0class[i]);
//		}
//		for(i=0;i<4;i++)
//		{
//			put2char(password_1class[i]);
//		}
//		for(i=0;i<4;i++)
//		{
//			put2char(password_2class[i]);
//		}
//		
		if(DI0==0x01)
		{
			if((Password_verification(0)==0))
			{
				for(i=0;i<4;i++)
				{
					array_temp[i] = data_array[8+i];
					password_0class[i] = data_array[8+i];
					if(array_temp[i]>0x99)
					{
						ERR_data_sent(ERR_BAD_DATA);
					}
				}		
				
				format_uart_t_buf();
				UART_T_Buf[0]=UART_T_Buf[7] = 0x68;
				for(i=0;i<6;i++)
				{
					UART_T_Buf[i+1] =  self_addr_code[i];
				}
				UART_T_Buf[8]	= ctrl_code+0x80;
				UART_T_Buf[9] = 0x04;
				UART_T_Buf[10] = password_0class[0]+0x33;
				UART_T_Buf[11] = password_0class[1]+0x33;
				UART_T_Buf[12] = password_0class[2]+0x33;
				UART_T_Buf[13] = password_0class[3]+0x33;
				for(i=0;i<14;i++)
				{
					cs_temp =  UART_T_Buf[i] + cs_temp;
				}
				UART_T_Buf[14]	= cs_temp;
				UART_T_Buf[15] =  0x16;
				//20150202���������޸�
					for(i=0;i<4;i++)
	{
	UART_S_Buf[i]=0xFE;
	}
				if(F_Dataval==1)
				{
					//RS485_Send_Data(UART_S_Buf,4);
					 //RS485_Send_Data(UART_T_Buf,14);
				}
				if(F_Dataval1==1)
				{
					 //hongwai_Send_Data(UART_T_Buf,14);
				}
				MODIFY_EEP_W(Addr_0_password,password_0class,4,0xA0);
			}
			else
			{
				ERR_data_sent(ERR_BAD_PASSWORD);
			}
			
		}
		else if(DI0==0x02)
		{
			if((Password_verification(0)==0)||(Password_verification(0)==1))
			{
				for(i=0;i<4;i++)
				{
					array_temp[i] = data_array[8+i];
					password_1class[i] = data_array[8+i];
					if(array_temp[i]>0x99)
					{
						ERR_data_sent(ERR_BAD_DATA);
					}
				}		
				
				format_uart_t_buf();
				UART_T_Buf[0]=UART_T_Buf[7] = 0x68;
				for(i=0;i<6;i++)
				{
					UART_T_Buf[i+1] =  self_addr_code[i];
				}
				UART_T_Buf[8]	= ctrl_code+0x80;
				UART_T_Buf[9] = 0x04;
				UART_T_Buf[10] = password_1class[0]+0x33;
				UART_T_Buf[11] = password_1class[1]+0x33;
				UART_T_Buf[12] = password_1class[2]+0x33;
				UART_T_Buf[13] = password_1class[3]+0x33;
				for(i=0;i<14;i++)
				{
					cs_temp =  UART_T_Buf[i] + cs_temp;
				}
				UART_T_Buf[14]	= cs_temp;
				UART_T_Buf[15] =  0x16;
				//20150202���������޸�
					for(i=0;i<4;i++)
	{
	UART_S_Buf[i]=0xFE;
	}
				if(F_Dataval==1)
				{
					//RS485_Send_Data(UART_S_Buf,4);
					 //RS485_Send_Data(UART_T_Buf,14);
				}
				if(F_Dataval1==1)
				{
					 //hongwai_Send_Data(UART_T_Buf,14);
				}
				MODIFY_EEP_W(Addr_1_password,password_1class,4,0xA0);

			}
			else
			{
				ERR_data_sent(ERR_BAD_PASSWORD);
			}
		}
		else if(DI0==0x03)
		{
			if((Password_verification(0)==0)||(Password_verification(0)==1)||(Password_verification(0)==2))
			{
				for(i=0;i<4;i++)
				{
					array_temp[i] = data_array[8+i];
					password_2class[i] = data_array[8+i];
					if(array_temp[i]>0x99)
					{
						ERR_data_sent(ERR_BAD_DATA);
					}
				}		
				
				format_uart_t_buf();
				UART_T_Buf[0]=UART_T_Buf[7] = 0x68;
				for(i=0;i<6;i++)
				{
					UART_T_Buf[i+1] =  self_addr_code[i];
				}
				UART_T_Buf[8]	= ctrl_code+0x80;
				UART_T_Buf[9] = 0x04;
				UART_T_Buf[10] = password_2class[0]+0x33;
				UART_T_Buf[11] = password_2class[1]+0x33;
				UART_T_Buf[12] = password_2class[2]+0x33;
				UART_T_Buf[13] = password_2class[3]+0x33;
				for(i=0;i<14;i++)
				{
					cs_temp =  UART_T_Buf[i] + cs_temp;
				}
				UART_T_Buf[14]	= cs_temp;
				UART_T_Buf[15] =  0x16;
				//20150202���������޸�
						for(i=0;i<4;i++)
	{
	UART_S_Buf[i]=0xFE;
	}
				if(F_Dataval==1)
				{
					//RS485_Send_Data(UART_S_Buf,4);
					 //RS485_Send_Data(UART_T_Buf,14);
				}
				if(F_Dataval1==1)
				{
					 //hongwai_Send_Data(UART_T_Buf,14);
				}
				MODIFY_EEP_W(Addr_2_password,password_2class,4,0xA0);
			}
			else
			{
				ERR_data_sent(ERR_BAD_PASSWORD);
			}
		}
		else
		{
			ERR_data_sent(ERR_BAD_PASSWORD);
		}
   delay_uart();
	F_err = 0;
	if(DI0==0x01)//�޸�0�����룬������0��������ԭ������ͬ
	{
		for(i=0;i<4;i++)
		{
			if(data_array[8+i]>0x99)
			{
				F_err = 1;				
			}
		}
		if(F_err==1)
		{
			ERR_data_sent(ERR_BAD_PASSWORD);			
		}
		else
		{
			if((Password_verification(0)==0))
			{
				for(i=0;i<4;i++)
				{
					password_0class[i] = data_array[8+i];
				}				
				format_uart_t_buf();
				UART_T_Buf[0]=UART_T_Buf[7] = 0x68;
				for(i=0;i<6;i++)
				{
					UART_T_Buf[i+1] =  self_addr_code[i];
				}
				UART_T_Buf[8]	= ctrl_code+0x80;
				UART_T_Buf[9] = 0x04;
				UART_T_Buf[10] = password_0class[0]+0x33;
				UART_T_Buf[11] = password_0class[1]+0x33;
				UART_T_Buf[12] = password_0class[2]+0x33;
				UART_T_Buf[13] = password_0class[3]+0x33;
				for(i=0;i<14;i++)
				{
					cs_temp =  UART_T_Buf[i] + cs_temp;
				}
				UART_T_Buf[14]	= cs_temp;
				UART_T_Buf[15] =  0x16;
				//20150202���������޸�
						for(i=0;i<4;i++)
	{
	UART_S_Buf[i]=0xFE;
	}
				if(F_Dataval==1)
				{
					//RS485_Send_Data(UART_S_Buf,4);
					 //RS485_Send_Data(UART_T_Buf,14);
				}
				if(F_Dataval1==1)
				{
					 //hongwai_Send_Data(UART_T_Buf,14);
				}
				MODIFY_EEP_W(Addr_0_password,password_0class,4,0xA0);				
			}
			else
			{
				ERR_data_sent(ERR_BAD_PASSWORD);				
			}
		}
	}		
	else if(DI0==0x02)//�޸�1�����룬0�������1��������Ч
	{
		for(i=0;i<4;i++)
		{
			if(data_array[8+i]>0x99)
			{
				F_err = 1;				
			}
		}
		if(F_err==1)
		{
			ERR_data_sent(ERR_BAD_PASSWORD);			
		}
		else
		{
			if((Password_verification(0)==0)||(Password_verification(0)==1))
			{
				for(i=0;i<4;i++)
				{
					password_1class[i] = data_array[8+i];
				}		
				
				format_uart_t_buf();
				UART_T_Buf[0]=UART_T_Buf[7] = 0x68;
				for(i=0;i<6;i++)
				{
					UART_T_Buf[i+1] =  self_addr_code[i];
				}
				UART_T_Buf[8]	= ctrl_code+0x80;
				UART_T_Buf[9] = 0x04;
				UART_T_Buf[10] = password_1class[0]+0x33;
				UART_T_Buf[11] = password_1class[1]+0x33;
				UART_T_Buf[12] = password_1class[2]+0x33;
				UART_T_Buf[13] = password_1class[3]+0x33;
				for(i=0;i<14;i++)
				{
					cs_temp =  UART_T_Buf[i] + cs_temp;
				}
				UART_T_Buf[14]	= cs_temp;
				UART_T_Buf[15] =  0x16;
				//20150202���������޸�
						for(i=0;i<4;i++)
	{
	UART_S_Buf[i]=0xFE;
	}
				if(F_Dataval==1)
				{
					//RS485_Send_Data(UART_S_Buf,4);
					 //RS485_Send_Data(UART_T_Buf,14);
				}
				if(F_Dataval1==1)
				{
					 //hongwai_Send_Data(UART_T_Buf,14);
				}
				MODIFY_EEP_W(Addr_1_password,password_1class,4,0xA0);
			}
			else
			{
				ERR_data_sent(ERR_BAD_PASSWORD);
			}			
		}	
	}
	else if(DI0==0x03)//�޸�2�����룬0�������1�������2��������Ч
	{
		for(i=0;i<4;i++)
		{
			if(data_array[8+i]>0x99)
			{
				F_err = 1;				
			}
		}
		if(F_err==1)
		{
			ERR_data_sent(ERR_BAD_PASSWORD);			
		}
		else
		{
			if((Password_verification(0)==0)||(Password_verification(0)==1)||(Password_verification(0)==2))
			{
				for(i=0;i<4;i++)
				{
					password_2class[i] = data_array[8+i];
				}		
				
				format_uart_t_buf();
				UART_T_Buf[0]=UART_T_Buf[7] = 0x68;
				for(i=0;i<6;i++)
				{
					UART_T_Buf[i+1] =  self_addr_code[i];
				}
				UART_T_Buf[8]	= ctrl_code+0x80;
				UART_T_Buf[9] = 0x04;
				UART_T_Buf[10] = password_2class[0]+0x33;
				UART_T_Buf[11] = password_2class[1]+0x33;
				UART_T_Buf[12] = password_2class[2]+0x33;
				UART_T_Buf[13] = password_2class[3]+0x33;
				for(i=0;i<14;i++)
				{
					cs_temp =  UART_T_Buf[i] + cs_temp;
				}
				UART_T_Buf[14]	= cs_temp;
				UART_T_Buf[15] =  0x16;
				//20150202���������޸�
						for(i=0;i<4;i++)
	{
	UART_S_Buf[i]=0xFE;
	}
				if(F_Dataval==1)
				{
					//RS485_Send_Data(UART_S_Buf,4);
					 //RS485_Send_Data(UART_T_Buf,14);
				}
				if(F_Dataval1==1)
				{
					 //hongwai_Send_Data(UART_T_Buf,14);
				}
				MODIFY_EEP_W(Addr_2_password,password_2class,4,0xA0);
			}
			else
			{
				ERR_data_sent(ERR_BAD_PASSWORD);
			}			
		}		
	}
	else
	{
		ERR_data_sent(ERR_BAD_PASSWORD);
	}
	}
	/****************************
		�����룺0x19  �豸�澯
*****************************/
	else if(ctrl_code==0x19) //�豸�澯
	{
		
	}
	/****************************
		�����룺0x1A  �豸�澯Ӧ��
*****************************/
	else if(ctrl_code==0x1A) //�豸�澯Ӧ��
	{
		
	} 
	/****************************
		�����룺0x1B  �¼�����
*****************************/
	else if(ctrl_code==0x1B) //�¼�����
	{
		if(Password_verification(1)==0)
		{
			if(Event_clear()==0)
			{
				WRITE_DATA_NOMAL();
			}
		}
		else
		{
			ERR_data_sent(ERR_BAD_PASSWORD);
		}
	} 

	/****************************
		������:0x1C  �豸����
*****************************/
	else if(ctrl_code==0x1C) //�豸����
	{
		F_yc = 1;
		delay_uart();
		if(F_yc==1)
		{
			if((Password_verification(0)==0)||(Password_verification(0)==1)||(Password_verification(0)==2))
			{
				if(DI3==0x06)
				{
					if(DI2==0x01)
					{
						if(DI1==0x01)
						{
							if(Write_fenzha_tim(DI0)==0)
							{
								WRITE_DATA_NOMAL();
							}
							
						}
						else if(DI1==0x02)
						{
							if(Write_hezha_tim(DI0)==0)
							{
								WRITE_DATA_NOMAL();
							}
						}
						else if(DI1==0x03)
						{
							if(Write_trip_tim(DI0)==0)
							{
								WRITE_DATA_NOMAL();
							}
						}
						else
						{
							ERR_data_sent(ERR_NO_REQUEST);
						}
					}
					else
					{
						ERR_data_sent(ERR_NO_REQUEST);
					}
				}
				else
				{
					ERR_data_sent(ERR_NO_REQUEST);
				}
			}
			else
			{
				ERR_data_sent(ERR_BAD_PASSWORD);  //�������
			}
		}
		else
		{
			ERR_data_sent(ERR_NO_REMOTE);  //  Զ�̿���ʧ��
		}
	} 
   else if(ctrl_code==0x1F) //�ڲ���Լ
	{
		//                                   ������ L  D3 D2 D1 D0
		//ʣ�����ϵ��1  50mA  frame��68 addr 68 1F 04 01 00 00 50 У�� 16
		//ʣ�����ϵ��2 100mA  frame��68 addr 68 1F 04 01 01 01 00 У�� 16
		//ʣ�����ϵ��3 300mA  frame��68 addr 68 1F 04 01 02 03 00 У�� 16
		
		//��ѹABC ϵ��1  150V  frame��68 addr 68 1F 04 02 01 01 70 У�� 16
		//��ѹABC ϵ��2  220V  frame��68 addr 68 1F 04 02 02 02 20 У�� 16
		//��ѹABC ϵ��3  280V  frame��68 addr 68 1F 04 02 03 02 80 У�� 16
		
		//����ABC ϵ��1   50A  frame��68 addr 68 1F 04 03 01 00 50 У�� 16
		//����ABC ϵ��2  100A  frame��68 addr 68 1F 04 03 02 01 00 У�� 16
		//����ABC ϵ��3  300A  frame��68 addr 68 1F 04 03 03 03 00 У�� 16
		//����ABC ϵ��4  500A  frame��68 addr 68 1F 04 03 04 05 00 У�� 16
		//����ABC ϵ��5  800A  frame��68 addr 68 1F 04 03 05 08 00 У�� 16
	
		if(DI3==0x02)//
		{
			unsigned int cal_factor;
			unsigned char array_temp[3],i;
			for(i=0;i<3;i++)
			{
			array_temp[i]=data_array[12+i];
			}
			cal_factor=BCDtoDec(array_temp,3);
			if(DI2==0x01)//��ѹ
			{
			//	vol_uart_cal_handle(DI1,DI0,cal_factor);
				  cal();//У׼
				
			}
			else if(DI2==0x02)//����
			{
            Offset_cal();
				//cur_uart_cal_handle(DI1,DI0,cal_factor);
			}
			else if(DI2==0x03)//200mA©��
			{
				
				leak_uart_cal_handle();

           TXJZ_LD=1;
			}
			else if(DI2==0x04)//˲��У׼
			{

				SD_uart_cal_handle(DI1,DI0,cal_factor);//˲����DI1��AD/б�ʣ�DI0�ڼ����㣻
//				WRITE_DATA_NOMAL();

			}
//			else
//			{
//				ERR_data_sent(ERR_NO_REQUEST);
//			}
//			
		}

	}
	else
	{
		ERR_data_sent(ERR_NO_REQUEST); //������
	}
}
void vol_uart_cal_handle(unsigned char tmp,unsigned char temp,unsigned value)
{
	//tmp��λ     temp����(û�ã�    valueҪУ׼��ֵ
	
	      unsigned char array_temp[2],array_tmp[2];
	
	         unsigned char array_temp_1[2];
			  unsigned short int  Vol_cal_tmp,L_cal_tmp=200;
			  signed int L_factor_tmp1,I_A_factor_tmp,V_A_factor_tmp,I_B_factor_tmp,V_B_factor_tmp,I_C_factor_tmp,V_C_factor_tmp;
        	Vol_cal_tmp=220;
	
	         if(tmp==1)
					 { 
//	            Vol_cal_tmp=value;   
	          Vol1_A_temp=V_Array_disp[0];//V_Array_disp/V_Array
				  	V_A_factor_tmp= vol_handle_A(V_Array_disp[0])-Vol_cal_tmp;//A��ѹУ׼
						V1_slope[0]=(Vol_cal_tmp<<20)/(Vol1_A_temp);
						HexToChar(array_temp,V1_slope[0],2);
					  MODIFY_EEP_W(Addr_V1_A_slope,array_temp,2,0xA0);
						 	delay_ms(5);
						 
			     /*****************2022.5.4��д������************************/ 
						 EEPROM_R(Addr_V1_A_slope,array_temp_1,2,0xA0);
						 if((array_temp_1[0]!=array_temp[0])||(array_temp_1[1]!=array_temp[1]))
						 {
						 
											V1_slope[0]=(Vol_cal_tmp<<20)/(Vol1_A_temp);
											HexToChar(array_temp,V1_slope[0],2);
											MODIFY_EEP_W(Addr_V1_A_slope,array_temp,2,0xA0);
											delay_ms(5);						 
									 //����
							  EEPROM_R(Addr_V1_A_slope,array_temp,2,0xA0);
							 	V1_slope[0]=(array_temp[1]<<8)+array_temp[0];
						 }
						 else
						{
						  V1_slope[0]=(array_temp_1[1]<<8)+array_temp_1[0];
						}

						 /**********************************************************/
						 
			    	HexToChar(array_tmp,Vol1_A_temp,2);
						MODIFY_EEP_W(Addr_Vol1_A_temp,array_tmp,2,0xA0);
						 	delay_ms(5);
        	 TXJZ_DY_A =1;
					 }
					 
					 
					else if(tmp==2)
					{	
//					  Vol_cal_tmp=value; 
				  	Vol1_B_temp=V_Array_disp[1];
				  	V_B_factor_tmp=vol_handle_B(V_Array_disp[1])-Vol_cal_tmp;//B��ѹУ׼
						V1_slope[1]=(Vol_cal_tmp<<20)/(Vol1_B_temp);
						HexToChar(array_temp,V1_slope[1],2);
						MODIFY_EEP_W(Addr_V1_B_slope,array_temp,2,0xA0);
							delay_ms(5);
						
						
												 
						/*****************2022.5.4��д������************************/ 
						 EEPROM_R(Addr_V1_B_slope,array_temp_1,2,0xA0);
						 if((array_temp_1[0]!=array_temp[0])||(array_temp_1[1]!=array_temp[1]))
						 {
						 
                 V1_slope[1]=(Vol_cal_tmp<<20)/(Vol1_B_temp);
						     HexToChar(array_temp,V1_slope[1],2);
						     MODIFY_EEP_W(Addr_V1_B_slope,array_temp,2,0xA0);
							 	 delay_ms(5);
							 
							  EEPROM_R(Addr_V1_B_slope,array_temp,2,0xA0);
							 	V1_slope[1]=(array_temp[1]<<8)+array_temp[0];
						 
						 }
						else
						{
						  V1_slope[1]=(array_temp_1[1]<<8)+array_temp_1[0];
						}
						 
						 /**********************************************************/
						
						
						
					
						HexToChar(array_tmp,Vol1_B_temp,2);
						MODIFY_EEP_W(Addr_Vol1_B_temp,array_tmp,2,0xA0);
						 	delay_ms(5);
						TXJZ_DY_B =1;

					}	
						
						
		    	else if(tmp==3)
					{	
//					 Vol_cal_tmp=value; 
					  Vol1_C_temp=V_Array_disp[2];
				  	V_C_factor_tmp= vol_handle_C(V_Array_disp[2])-Vol_cal_tmp;//C��ѹУ׼

						V1_slope[2]=(Vol_cal_tmp<<20)/(Vol1_C_temp);
						HexToChar(array_temp,V1_slope[2],2);
						MODIFY_EEP_W(Addr_V1_C_slope,array_temp,2,0xA0);
							delay_ms(5);
						
																		 
						/*****************2022.5.4��д������************************/ 
						 EEPROM_R(Addr_V1_C_slope,array_temp_1,2,0xA0);
						 if((array_temp_1[0]!=array_temp[0])||(array_temp_1[1]!=array_temp[1]))
						 {
						 
	             V1_slope[2]=(Vol_cal_tmp<<20)/(Vol1_C_temp);
						   HexToChar(array_temp,V1_slope[2],2);
						   MODIFY_EEP_W(Addr_V1_C_slope,array_temp,2,0xA0);
							 	delay_ms(5);
							 
							 
							 	EEPROM_R(Addr_V1_C_slope,array_temp,2,0xA0);
							 	V1_slope[2]=(array_temp[1]<<8)+array_temp[0];
						
						 }
						 else
						{
						  V1_slope[2]=(array_temp_1[1]<<8)+array_temp_1[0];
						}
						 /**********************************************************/
						
						
						
						HexToChar(array_tmp,Vol1_C_temp,2);
						MODIFY_EEP_W(Addr_Vol1_C_temp,array_tmp,2,0xA0);
						 	delay_ms(5);
						TXJZ_DY_C =1;
	        }

}

void cur_uart_cal_handle(unsigned char tmp,unsigned char temp,unsigned value)
{
	
    	unsigned long Cur_cal_tmp[2]={100,250};//500
	// tmp��λ,tempУ׼�㣬valueУ׼���ֵ
	
	       unsigned char array_temp[2],array_tmp[2];
			  unsigned short int  Vol_cal_tmp,L_cal_tmp=200;
			  signed int L_factor_tmp1,I_A_factor_tmp,V_A_factor_tmp,I_B_factor_tmp,V_B_factor_tmp,I_C_factor_tmp,V_C_factor_tmp;
			
			
						if(Type_Cur==0)
						{
							Cur_cal_tmp[0]=50;
							Cur_cal_tmp[1]=125;
							
						}
								
					 if(Type_Cur==1)
						{
							Cur_cal_tmp[0]=100;
							Cur_cal_tmp[1]=250;
							
						}
					 else if(Type_Cur==2)
						{
							Cur_cal_tmp[0]=160;
							Cur_cal_tmp[1]=400;
							
						}
						else if(Type_Cur==3)
						{
							Cur_cal_tmp[0]=252;
							Cur_cal_tmp[1]=630;
							
						}
			
			
	
					if(temp==1)					//����У׼100A
				{
					  if(tmp==1)
						{
								CurA_cal_tmp[0]=I_I_Array_xianshi[0];//I_I_Array_xianshi//I_Array_xianshi
								I_A_factor_tmp=cur_handle_A(I_I_Array_xianshi[0])-Cur_cal_tmp[0];	
								I1_A_slope[0]=(Cur_cal_tmp[0]<<20)/(CurA_cal_tmp[0]);//A����У׼��1
								HexToChar(array_temp,I1_A_slope[0],2);
								HexToChar(array_tmp,CurA_cal_tmp[0],2);
								if(Type_Cur==0)
								{
									MODIFY_EEP_W(Addr100_I1_A_slope,array_temp,2,0xA0);
										delay_ms(5);
									MODIFY_EEP_W(Addr100_CurA_cal_tmp,array_tmp,2,0xA0);
										delay_ms(5);
								}
								else if(Type_Cur==1)
								{
									MODIFY_EEP_W(Addr_I1_A_slope,array_temp,2,0xA0);
										delay_ms(5);
									MODIFY_EEP_W(Addr_CurA_cal_tmp,array_tmp,2,0xA0);
										delay_ms(5);
								}
								else if(Type_Cur==2)
								{
									MODIFY_EEP_W(Addr400_I1_A_slope,array_temp,2,0xA0);
										delay_ms(5);
									MODIFY_EEP_W(Addr400_CurA_cal_tmp,array_tmp,2,0xA0);
										delay_ms(5);
								}
								else if(Type_Cur==3)
								{
									MODIFY_EEP_W(Addr630_I1_A_slope,array_temp,2,0xA0);
										delay_ms(5);
									MODIFY_EEP_W(Addr630_CurA_cal_tmp,array_tmp,2,0xA0);
									delay_ms(5);
								}
								TXJZ_DL_A=1;
						
						}
						
						
						
						else if(tmp==2)
						{
									CurB_cal_tmp[0]=I_I_Array_xianshi[1];
									I_B_factor_tmp=cur_handle_B(I_I_Array_xianshi[1])-Cur_cal_tmp[0];			
									I1_B_slope[0]=(Cur_cal_tmp[0]<<20)/(CurB_cal_tmp[0]);//B����У׼��1
									HexToChar(array_temp,I1_B_slope[0],2);
									HexToChar(array_tmp,CurB_cal_tmp[0],2);
									if(Type_Cur==0)
									{
										MODIFY_EEP_W(Addr100_I1_B_slope,array_temp,2,0xA0);
											delay_ms(5);
										MODIFY_EEP_W(Addr100_CurB_cal_tmp,array_tmp,2,0xA0);
											delay_ms(5);
									}
									else if(Type_Cur==1)
									{
										MODIFY_EEP_W(Addr_I1_B_slope,array_temp,2,0xA0);
											delay_ms(5);
										MODIFY_EEP_W(Addr_CurB_cal_tmp,array_tmp,2,0xA0);
											delay_ms(5);
									}
									else if(Type_Cur==2)
									{
										MODIFY_EEP_W(Addr400_I1_B_slope,array_temp,2,0xA0);
											delay_ms(5);
										MODIFY_EEP_W(Addr400_CurB_cal_tmp,array_tmp,2,0xA0);
											delay_ms(5);
									}
									else if(Type_Cur==3)
									{
										MODIFY_EEP_W(Addr630_I1_B_slope,array_temp,2,0xA0);
											delay_ms(5);
										MODIFY_EEP_W(Addr630_CurB_cal_tmp,array_tmp,2,0xA0);
											delay_ms(5);
									}
									TXJZ_DL_B=1;
						}

						
						else if(tmp==3)
						{
							
									CurC_cal_tmp[0]=I_I_Array_xianshi[2];
									I_C_factor_tmp=cur_handle_C(I_I_Array_xianshi[2])-Cur_cal_tmp[0];					
									I1_C_slope[0]=(Cur_cal_tmp[0]<<20)/(CurC_cal_tmp[0]);//C����У׼��1
									HexToChar(array_temp,I1_C_slope[0],2);
									HexToChar(array_tmp,CurC_cal_tmp[0],2);
									if(Type_Cur==0)
									{
										MODIFY_EEP_W(Addr100_I1_C_slope,array_temp,2,0xA0);
											delay_ms(5);
										MODIFY_EEP_W(Addr100_CurC_cal_tmp,array_tmp,2,0xA0);
											delay_ms(5);
									}
									else if(Type_Cur==1)
									{
										MODIFY_EEP_W(Addr_I1_C_slope,array_temp,2,0xA0);
											delay_ms(5);
										MODIFY_EEP_W(Addr_CurC_cal_tmp,array_tmp,2,0xA0);
											delay_ms(5);
									}
									else if(Type_Cur==2)
									{
										MODIFY_EEP_W(Addr400_I1_C_slope,array_temp,2,0xA0);
											delay_ms(5);
										MODIFY_EEP_W(Addr400_CurC_cal_tmp,array_tmp,2,0xA0);
											delay_ms(5);
									}
									else if(Type_Cur==3)
									{
										MODIFY_EEP_W(Addr630_I1_C_slope,array_temp,2,0xA0);
											delay_ms(5);
										MODIFY_EEP_W(Addr630_CurC_cal_tmp,array_tmp,2,0xA0);
											delay_ms(5);
									}
										TXJZ_DL_C=1;
	          }					
				}

	/***	****************************abc����У׼��2****************/	//	250A
				else if(temp==2)
				{
					   if(tmp==1)
						{
										CurA_cal_tmp[1]=I_I_Array_xianshi[0];
										I_A_factor_tmp=cur_handle_A(I_I_Array_xianshi[0])-Cur_cal_tmp[1];	
										I1_A_slope[1]=((Cur_cal_tmp[1]-Cur_cal_tmp[0])<<20)/(CurA_cal_tmp[1]-CurA_cal_tmp[0]);//a����У׼��2
										HexToChar(array_temp,I1_A_slope[1],2);
										HexToChar(array_tmp,CurA_cal_tmp[1],2);
										if(Type_Cur==0)
										{
											MODIFY_EEP_W(Addr100_I1_A_slope1,array_temp,2,0xA0);
												delay_ms(5);
											MODIFY_EEP_W(Addr100_CurA_cal_tmp1,array_tmp,2,0xA0);
												delay_ms(5);
										}
										else if(Type_Cur==1)
										{
											MODIFY_EEP_W(Addr_I1_A_slope1,array_temp,2,0xA0);
												delay_ms(5);
											MODIFY_EEP_W(Addr_CurA_cal_tmp1,array_tmp,2,0xA0);
												delay_ms(5);
										}
										else if(Type_Cur==2)
										{
											MODIFY_EEP_W(Addr400_I1_A_slope1,array_temp,2,0xA0);
												delay_ms(5);
											MODIFY_EEP_W(Addr400_CurA_cal_tmp1,array_tmp,2,0xA0);
												delay_ms(5);
										}
										else if(Type_Cur==3)
										{
											MODIFY_EEP_W(Addr630_I1_A_slope1,array_temp,2,0xA0);
												delay_ms(5);
											MODIFY_EEP_W(Addr630_CurA_cal_tmp1,array_tmp,2,0xA0);
												delay_ms(5);
										}
										TXJZ_DL_A=1;
										
							}

					  else if(tmp==2)
						{							
										
										CurB_cal_tmp[1]=I_I_Array_xianshi[1];
										I_B_factor_tmp=cur_handle_B(I_I_Array_xianshi[1])-Cur_cal_tmp[1];			
										I1_B_slope[1]=((Cur_cal_tmp[1]-Cur_cal_tmp[0])<<20)/(CurB_cal_tmp[1]-CurB_cal_tmp[0]);//b����У׼��2
										HexToChar(array_temp,I1_B_slope[1],2);
										HexToChar(array_tmp,CurB_cal_tmp[1],2);
										if(Type_Cur==0)
										{
											MODIFY_EEP_W(Addr100_I1_B_slope1,array_temp,2,0xA0);
												delay_ms(5);
											MODIFY_EEP_W(Addr100_CurB_cal_tmp1,array_tmp,2,0xA0);
												delay_ms(5);
										}
										else if(Type_Cur==1)
										{
											MODIFY_EEP_W(Addr_I1_B_slope1,array_temp,2,0xA0);
												delay_ms(5);
											MODIFY_EEP_W(Addr_CurB_cal_tmp1,array_tmp,2,0xA0);
												delay_ms(5);
										}
										else if(Type_Cur==2)
										{
											MODIFY_EEP_W(Addr400_I1_B_slope1,array_temp,2,0xA0);
												delay_ms(5);
											MODIFY_EEP_W(Addr400_CurB_cal_tmp1,array_tmp,2,0xA0);
												delay_ms(5);
										}
										else if(Type_Cur==3)
										{
											MODIFY_EEP_W(Addr630_I1_B_slope1,array_temp,2,0xA0);
												delay_ms(5);
											MODIFY_EEP_W(Addr630_CurB_cal_tmp1,array_tmp,2,0xA0);
												delay_ms(5);
										}
										TXJZ_DL_B=1;
										
						 }			
						
					  else if(tmp==3)
						{
										
										CurC_cal_tmp[1]=I_I_Array_xianshi[2];
										I_C_factor_tmp=cur_handle_C(I_I_Array_xianshi[2])-Cur_cal_tmp[1];					
										I1_C_slope[1]=((Cur_cal_tmp[1]-Cur_cal_tmp[0])<<20)/(CurC_cal_tmp[1]-CurC_cal_tmp[0]);//c����У׼��2
										HexToChar(array_temp,I1_C_slope[1],2);
										HexToChar(array_tmp,CurC_cal_tmp[1],2);
										if(Type_Cur==0)
										{
											MODIFY_EEP_W(Addr100_I1_C_slope1,array_temp,2,0xA0);
												delay_ms(5);
											MODIFY_EEP_W(Addr100_CurC_cal_tmp1,array_tmp,2,0xA0);
												delay_ms(5);
										}
										else if(Type_Cur==1)
										{
											MODIFY_EEP_W(Addr_I1_C_slope1,array_temp,2,0xA0);
												delay_ms(5);
											MODIFY_EEP_W(Addr_CurC_cal_tmp1,array_tmp,2,0xA0);
												delay_ms(5);
										}
										else if(Type_Cur==2)
										{
											MODIFY_EEP_W(Addr400_I1_C_slope1,array_temp,2,0xA0);
												delay_ms(5);
											MODIFY_EEP_W(Addr400_CurC_cal_tmp1,array_tmp,2,0xA0);
												delay_ms(5);
										}
										else if(Type_Cur==3)
										{
											MODIFY_EEP_W(Addr630_I1_C_slope1,array_temp,2,0xA0);
												delay_ms(5);
											MODIFY_EEP_W(Addr630_CurC_cal_tmp1,array_tmp,2,0xA0);
												delay_ms(5);
										}
										TXJZ_DL_C=1;

							}

				}
}
void leak_uart_cal_handle()
{

			      unsigned char array_temp[2],array_tmp[2];
			      unsigned short int  Vol_cal_tmp=220,L_cal_tmp=200;//ͨ�Ų���У׼©�磬������Vol_cal_tmpδ����ֵ��2023-8-14����ֵ220
        	  signed int L_factor_tmp1,I_A_factor_tmp,V_A_factor_tmp,I_B_factor_tmp,V_B_factor_tmp,I_C_factor_tmp,V_C_factor_tmp;
        	  volatile unsigned short int L1_slope;
	
	     
	
	
          Leak1_temp=Leak_Cur_disp_temp;
					L_factor_tmp1=Leak_Cur_disp-L_cal_tmp;

     
						L1_slope=(L_cal_tmp<<20)/(Leak1_temp);
						HexToChar(array_temp,L1_slope,2);
						HexToChar(array_tmp,Leak1_temp,2);
						if((Type_Cur==0)||(Type_Cur==1))
						{
							MODIFY_EEP_W(Addr_L1_slope,array_temp,2,0xA0);
							MODIFY_EEP_W(Addr_Leak1_temp,array_tmp,2,0xA0);
						}

						else if(Type_Cur==2)
						{
							MODIFY_EEP_W(Addr400_L1_slope,array_temp,2,0xA0);
							MODIFY_EEP_W(Addr400_Leak1_temp,array_tmp,2,0xA0);
						}
						else if(Type_Cur==3)
						{
							MODIFY_EEP_W(Addr630_L1_slope,array_temp,2,0xA0);
							MODIFY_EEP_W(Addr630_Leak1_temp,array_tmp,2,0xA0);
						}

}


void SD_uart_cal_handle(unsigned char tmp,unsigned char temp,unsigned int value)//temp:�ڼ�����
{
//	if(F_Corr==1)
	{
	float cal_temp;
	unsigned char array_temp[10],Buf_temp[10],array_tmp[10];
	if(Type_Cur==0) 
	{
		if(temp==0)
	{
	  if(tmp==1)//˲��ADֵ
		{
		 DLS_Cur_IV_AD_value[0]=value;
		 HexToChar(array_tmp,DLS_Cur_IV_AD_value[0],3);	
		 MODIFY_EEP_W(Addr_DLS_Cur_IV_AD_value,array_tmp,3,0xA0);	 

		}
		else if(tmp==2)//˲��б��ֵ
		{
		 DLS_Cur_IV_slope[0]=value;
		 HexToChar(array_tmp,DLS_Cur_IV_slope[0],3);	
		 MODIFY_EEP_W(Addr_DLS_Cur_IV_slope,array_tmp,3,0xA0);

		}
		else if(tmp==3)//˲������ֵ
		{
		 DLS_Cur_IV_Value[0]=value;
		 HexToChar(array_tmp,DLS_Cur_IV_Value[0],3);	
		 MODIFY_EEP_W(Addr_DLS_Cur_IV_Value,array_tmp,3,0xA0); 
		}
		else
		{
		 ERR_data_sent(ERR_NO_REQUEST);
		}
	}
	else if(temp==1)
	{
		if(tmp==1)//˲��ADֵ
		{
		 DLS_Cur_IV_AD_value[1]=value;
		 HexToChar(array_tmp,DLS_Cur_IV_AD_value[1],3);	
		 MODIFY_EEP_W(Addr_DLS_Cur_IV_AD_value+3,array_tmp,3,0xA0);	 

		}
		else if(tmp==2)//˲��б��ֵ
		{
		 DLS_Cur_IV_slope[1]=value;
		 HexToChar(array_tmp,DLS_Cur_IV_slope[1],3);	
		 MODIFY_EEP_W(Addr_DLS_Cur_IV_slope+3,array_tmp,3,0xA0);

		}
		else if(tmp==3)//˲������ֵ
		{
		 DLS_Cur_IV_Value[1]=value;
		 HexToChar(array_tmp, DLS_Cur_IV_Value[1],3);	
		 MODIFY_EEP_W(Addr_DLS_Cur_IV_Value+3,array_tmp,3,0xA0); 
		}
		else
		{
		 ERR_data_sent(ERR_NO_REQUEST);
		}
	}
	else if(temp==2)
	{
		if(tmp==1)//˲��ADֵ
		{
		 DLS_Cur_IV_AD_value[2]=value;
		 HexToChar(array_tmp,DLS_Cur_IV_AD_value[2],3);	
		 MODIFY_EEP_W(Addr_DLS_Cur_IV_AD_value+6,array_tmp,3,0xA0);	 

		}
		else if(tmp==2)//˲��б��ֵ
		{
		 DLS_Cur_IV_slope[2]=value;
		 HexToChar(array_tmp,DLS_Cur_IV_slope[2],3);	
		 MODIFY_EEP_W(Addr_DLS_Cur_IV_slope+6,array_tmp,3,0xA0);

		}
		else if(tmp==3)//˲������ֵ
		{
		 DLS_Cur_IV_Value[2]=value;
		 HexToChar(array_tmp,DLS_Cur_IV_Value[2],3);	
		 MODIFY_EEP_W(Addr_DLS_Cur_IV_Value+6,array_tmp,3,0xA0); 
		}
		else
		{
		 ERR_data_sent(ERR_NO_REQUEST);
		}
	}
	else if(temp==3)
	{
		if(tmp==1)//˲��ADֵ
		{
		 DLS_Cur_IV_AD_value[3]=value;
		 HexToChar(array_tmp,DLS_Cur_IV_AD_value[3],3);	
		 MODIFY_EEP_W(Addr_DLS_Cur_IV_AD_value+9,array_tmp,3,0xA0);	 

		}
		else if(tmp==2)//˲��б��ֵ
		{
		 DLS_Cur_IV_slope[3]=value;
		 HexToChar(array_tmp, DLS_Cur_IV_slope[3],3);	
		 MODIFY_EEP_W(Addr_DLS_Cur_IV_slope+9,array_tmp,3,0xA0);

		}
		else if(tmp==3)//˲������ֵ
		{
		 DLS_Cur_IV_Value[3]=value;
		 HexToChar(array_tmp,DLS_Cur_IV_Value[3],3);	
		 MODIFY_EEP_W(Addr_DLS_Cur_IV_Value+9,array_tmp,3,0xA0); 
		}
		else
		{
		 ERR_data_sent(ERR_NO_REQUEST);
		}
	}
	else if(temp==4)
	{
		if(tmp==1)//˲��ADֵ
		{
		 DLS_Cur_IV_AD_value[4]=value;
		 HexToChar(array_tmp,DLS_Cur_IV_AD_value[4],3);	
		 MODIFY_EEP_W(Addr_DLS_Cur_IV_AD_value+12,array_tmp,3,0xA0);	 

		}
		else if(tmp==2)//˲��б��ֵ
		{
		 DLS_Cur_IV_slope[4]=value;
		 HexToChar(array_tmp,DLS_Cur_IV_slope[4],3);	
		 MODIFY_EEP_W(Addr_DLS_Cur_IV_slope+12,array_tmp,3,0xA0);

		}
		else if(tmp==3)//˲������ֵ
		{
		 DLS_Cur_IV_Value[4]=value;
		 HexToChar(array_tmp,DLS_Cur_IV_Value[4],3);	
		 MODIFY_EEP_W(Addr_DLS_Cur_IV_Value+12,array_tmp,3,0xA0); 
		}
		else
		{
		 ERR_data_sent(ERR_NO_REQUEST);
		}
	}
	}
		if(Type_Cur==1) 
	{
		if(temp==0)
	{
	  if(tmp==1)//˲��ADֵ
		{
		 DLS_Cur_I_AD_value[0]=value;
		 HexToChar(array_tmp,DLS_Cur_I_AD_value[0],3);	
		 MODIFY_EEP_W(Addr_DLS_Cur_I_AD_value,array_tmp,3,0xA0);	 

		}
		else if(tmp==2)//˲��б��ֵ
		{
		 DLS_Cur_I_slope[0]=value;
		 HexToChar(array_tmp,DLS_Cur_I_slope[0],3);	
		 MODIFY_EEP_W(Addr_DLS_Cur_I_slope,array_tmp,3,0xA0);

		}
		else if(tmp==3)//˲������ֵ
		{
		 DLS_Cur_I_Value[0]=value;
		 HexToChar(array_tmp,DLS_Cur_I_Value[0],3);	
		 MODIFY_EEP_W(Addr_DLS_Cur_I_Value,array_tmp,3,0xA0); 
		}
		else
		{
		 ERR_data_sent(ERR_NO_REQUEST);
		}
	}
	else if(temp==1)
	{
		if(tmp==1)//˲��ADֵ
		{
		 DLS_Cur_I_AD_value[1]=value;
		 HexToChar(array_tmp,DLS_Cur_I_AD_value[1],3);	
		 MODIFY_EEP_W(Addr_DLS_Cur_I_AD_value+3,array_tmp,3,0xA0);	 

		}
		else if(tmp==2)//˲��б��ֵ
		{
		 DLS_Cur_I_slope[1]=value;
		 HexToChar(array_tmp,DLS_Cur_I_slope[1],3);	
		 MODIFY_EEP_W(Addr_DLS_Cur_I_slope+3,array_tmp,3,0xA0);

		}
		else if(tmp==3)//˲������ֵ
		{
		 DLS_Cur_I_Value[1]=value;
		 HexToChar(array_tmp, DLS_Cur_I_Value[1],3);	
		 MODIFY_EEP_W(Addr_DLS_Cur_I_Value+3,array_tmp,3,0xA0); 
		}
		else
		{
		 ERR_data_sent(ERR_NO_REQUEST);
		}
	}
	else if(temp==2)
	{
		if(tmp==1)//˲��ADֵ
		{
		 DLS_Cur_I_AD_value[2]=value;
		 HexToChar(array_tmp,DLS_Cur_I_AD_value[2],3);	
		 MODIFY_EEP_W(Addr_DLS_Cur_I_AD_value+6,array_tmp,3,0xA0);	 

		}
		else if(tmp==2)//˲��б��ֵ
		{
		 DLS_Cur_I_slope[2]=value;
		 HexToChar(array_tmp,DLS_Cur_I_slope[2],3);	
		 MODIFY_EEP_W(Addr_DLS_Cur_I_slope+6,array_tmp,3,0xA0);

		}
		else if(tmp==3)//˲������ֵ
		{
		 DLS_Cur_I_Value[2]=value;
		 HexToChar(array_tmp,DLS_Cur_I_Value[2],3);	
		 MODIFY_EEP_W(Addr_DLS_Cur_I_Value+6,array_tmp,3,0xA0); 
		}
		else
		{
		 ERR_data_sent(ERR_NO_REQUEST);
		}
	}
	else if(temp==3)
	{
		if(tmp==1)//˲��ADֵ
		{
		 DLS_Cur_I_AD_value[3]=value;
		 HexToChar(array_tmp,DLS_Cur_I_AD_value[3],3);	
		 MODIFY_EEP_W(Addr_DLS_Cur_I_AD_value+9,array_tmp,3,0xA0);	 

		}
		else if(tmp==2)//˲��б��ֵ
		{
		 DLS_Cur_I_slope[3]=value;
		 HexToChar(array_tmp, DLS_Cur_I_slope[3],3);	
		 MODIFY_EEP_W(Addr_DLS_Cur_I_slope+9,array_tmp,3,0xA0);

		}
		else if(tmp==3)//˲������ֵ
		{
		 DLS_Cur_I_Value[3]=value;
		 HexToChar(array_tmp,DLS_Cur_I_Value[3],3);	
		 MODIFY_EEP_W(Addr_DLS_Cur_I_Value+9,array_tmp,3,0xA0); 
		}
		else
		{
		 ERR_data_sent(ERR_NO_REQUEST);
		}
	}
	else if(temp==4)
	{
		if(tmp==1)//˲��ADֵ
		{
		 DLS_Cur_I_AD_value[4]=value;
		 HexToChar(array_tmp,DLS_Cur_I_AD_value[4],3);	
		 MODIFY_EEP_W(Addr_DLS_Cur_I_AD_value+12,array_tmp,3,0xA0);	 

		}
		else if(tmp==2)//˲��б��ֵ
		{
		 DLS_Cur_I_slope[4]=value;
		 HexToChar(array_tmp,DLS_Cur_I_slope[4],3);	
		 MODIFY_EEP_W(Addr_DLS_Cur_I_slope+12,array_tmp,3,0xA0);

		}
		else if(tmp==3)//˲������ֵ
		{
		 DLS_Cur_I_Value[4]=value;
		 HexToChar(array_tmp,DLS_Cur_I_Value[4],3);	
		 MODIFY_EEP_W(Addr_DLS_Cur_I_Value+12,array_tmp,3,0xA0); 
		}
		else
		{
		 ERR_data_sent(ERR_NO_REQUEST);
		}
	}
	}
		if(Type_Cur==2) 
	{
		if(temp==0)
	{
	  if(tmp==1)//˲��ADֵ
		{
		 DLS_Cur_II_AD_value[0]=value;
		 HexToChar(array_tmp,DLS_Cur_II_AD_value[0],3);	
		 MODIFY_EEP_W(Addr_DLS_Cur_II_AD_value,array_tmp,3,0xA0);	 

		}
		else if(tmp==2)//˲��б��ֵ
		{
		 DLS_Cur_II_slope[0]=value;
		 HexToChar(array_tmp,DLS_Cur_II_slope[0],3);	
		 MODIFY_EEP_W(Addr_DLS_Cur_II_slope,array_tmp,3,0xA0);

		}
		else if(tmp==3)//˲������ֵ
		{
		 DLS_Cur_II_Value[0]=value;
		 HexToChar(array_tmp,DLS_Cur_II_Value[0],3);	
		 MODIFY_EEP_W(Addr_DLS_Cur_II_Value,array_tmp,3,0xA0); 
		}
		else
		{
		 ERR_data_sent(ERR_NO_REQUEST);
		}
	}
	else if(temp==1)
	{
		if(tmp==1)//˲��ADֵ
		{
		 DLS_Cur_II_AD_value[1]=value;
		 HexToChar(array_tmp,DLS_Cur_II_AD_value[1],3);	
		 MODIFY_EEP_W(Addr_DLS_Cur_II_AD_value+3,array_tmp,3,0xA0);	 

		}
		else if(tmp==2)//˲��б��ֵ
		{
		 DLS_Cur_II_slope[1]=value;
		 HexToChar(array_tmp,DLS_Cur_II_slope[1],3);	
		 MODIFY_EEP_W(Addr_DLS_Cur_II_slope+3,array_tmp,3,0xA0);

		}
		else if(tmp==3)//˲������ֵ
		{
		 DLS_Cur_II_Value[1]=value;
		 HexToChar(array_tmp, DLS_Cur_II_Value[1],3);	
		 MODIFY_EEP_W(Addr_DLS_Cur_II_Value+3,array_tmp,3,0xA0); 
		}
		else
		{
		 ERR_data_sent(ERR_NO_REQUEST);
		}
	}
	else if(temp==2)
	{
		if(tmp==1)//˲��ADֵ
		{
		 DLS_Cur_II_AD_value[2]=value;
		 HexToChar(array_tmp,DLS_Cur_II_AD_value[2],3);	
		 MODIFY_EEP_W(Addr_DLS_Cur_II_AD_value+6,array_tmp,3,0xA0);	 

		}
		else if(tmp==2)//˲��б��ֵ
		{
		 DLS_Cur_II_slope[2]=value;
		 HexToChar(array_tmp,DLS_Cur_II_slope[2],3);	
		 MODIFY_EEP_W(Addr_DLS_Cur_II_slope+6,array_tmp,3,0xA0);

		}
		else if(tmp==3)//˲������ֵ
		{
		 DLS_Cur_II_Value[2]=value;
		 HexToChar(array_tmp,DLS_Cur_II_Value[2],3);	
		 MODIFY_EEP_W(Addr_DLS_Cur_II_Value+6,array_tmp,3,0xA0); 
		}
		else
		{
		 ERR_data_sent(ERR_NO_REQUEST);
		}
	}
	else if(temp==3)
	{
		if(tmp==1)//˲��ADֵ
		{
		 DLS_Cur_II_AD_value[3]=value;
		 HexToChar(array_tmp,DLS_Cur_II_AD_value[3],3);	
		 MODIFY_EEP_W(Addr_DLS_Cur_II_AD_value+9,array_tmp,3,0xA0);	 

		}
		else if(tmp==2)//˲��б��ֵ
		{
		 DLS_Cur_II_slope[3]=value;
		 HexToChar(array_tmp, DLS_Cur_II_slope[3],3);	
		 MODIFY_EEP_W(Addr_DLS_Cur_II_slope+9,array_tmp,3,0xA0);

		}
		else if(tmp==3)//˲������ֵ
		{
		 DLS_Cur_II_Value[3]=value;
		 HexToChar(array_tmp,DLS_Cur_II_Value[3],3);	
		 MODIFY_EEP_W(Addr_DLS_Cur_II_Value+9,array_tmp,3,0xA0); 
		}
		else
		{
		 ERR_data_sent(ERR_NO_REQUEST);
		}
	}
	else if(temp==4)
	{
		if(tmp==1)//˲��ADֵ
		{
		 DLS_Cur_II_AD_value[4]=value;
		 HexToChar(array_tmp,DLS_Cur_II_AD_value[4],3);	
		 MODIFY_EEP_W(Addr_DLS_Cur_II_AD_value+12,array_tmp,3,0xA0);	 

		}
		else if(tmp==2)//˲��б��ֵ
		{
		 DLS_Cur_II_slope[4]=value;
		 HexToChar(array_tmp,DLS_Cur_II_slope[4],3);	
		 MODIFY_EEP_W(Addr_DLS_Cur_II_slope+12,array_tmp,3,0xA0);

		}
		else if(tmp==3)//˲������ֵ
		{
		 DLS_Cur_II_Value[4]=value;
		 HexToChar(array_tmp,DLS_Cur_II_Value[4],3);	
		 MODIFY_EEP_W(Addr_DLS_Cur_II_Value+12,array_tmp,3,0xA0); 
		}
		else
		{
		 ERR_data_sent(ERR_NO_REQUEST);
		}
	}
	}
		if(Type_Cur==3) 
	{
		if(temp==0)
	{
	  if(tmp==1)//˲��ADֵ
		{
		 DLS_Cur_III_AD_value[0]=value;
		 HexToChar(array_tmp,DLS_Cur_III_AD_value[0],3);	
		 MODIFY_EEP_W(Addr_DLS_Cur_III_AD_value,array_tmp,3,0xA0);	 

		}
		else if(tmp==2)//˲��б��ֵ
		{
		 DLS_Cur_III_slope[0]=value;
		 HexToChar(array_tmp,DLS_Cur_III_slope[0],3);	
		 MODIFY_EEP_W(Addr_DLS_Cur_III_slope,array_tmp,3,0xA0);

		}
		else if(tmp==3)//˲������ֵ
		{
		 DLS_Cur_III_Value[0]=value;
		 HexToChar(array_tmp,DLS_Cur_III_Value[0],3);	
		 MODIFY_EEP_W(Addr_DLS_Cur_III_Value,array_tmp,3,0xA0); 
		}
		else
		{
		 ERR_data_sent(ERR_NO_REQUEST);
		}
	}
	else if(temp==1)
	{
		if(tmp==1)//˲��ADֵ
		{
		 DLS_Cur_III_AD_value[1]=value;
		 HexToChar(array_tmp,DLS_Cur_III_AD_value[1],3);	
		 MODIFY_EEP_W(Addr_DLS_Cur_III_AD_value+3,array_tmp,3,0xA0);	 

		}
		else if(tmp==2)//˲��б��ֵ
		{
		 DLS_Cur_III_slope[1]=value;
		 HexToChar(array_tmp,DLS_Cur_III_slope[1],3);	
		 MODIFY_EEP_W(Addr_DLS_Cur_III_slope+3,array_tmp,3,0xA0);

		}
		else if(tmp==3)//˲������ֵ
		{
		 DLS_Cur_III_Value[1]=value;
		 HexToChar(array_tmp, DLS_Cur_III_Value[1],3);	
		 MODIFY_EEP_W(Addr_DLS_Cur_III_Value+3,array_tmp,3,0xA0); 
		}
		else
		{
		 ERR_data_sent(ERR_NO_REQUEST);
		}
	}
	else if(temp==2)
	{
		if(tmp==1)//˲��ADֵ
		{
		 DLS_Cur_III_AD_value[2]=value;
		 HexToChar(array_tmp,DLS_Cur_III_AD_value[2],3);	
		 MODIFY_EEP_W(Addr_DLS_Cur_III_AD_value+6,array_tmp,3,0xA0);	 

		}
		else if(tmp==2)//˲��б��ֵ
		{
		 DLS_Cur_III_slope[2]=value;
		 HexToChar(array_tmp,DLS_Cur_III_slope[2],3);	
		 MODIFY_EEP_W(Addr_DLS_Cur_III_slope+6,array_tmp,3,0xA0);

		}
		else if(tmp==3)//˲������ֵ
		{
		 DLS_Cur_III_Value[2]=value;
		 HexToChar(array_tmp,DLS_Cur_III_Value[2],3);	
		 MODIFY_EEP_W(Addr_DLS_Cur_III_Value+6,array_tmp,3,0xA0); 
		}
		else
		{
		 ERR_data_sent(ERR_NO_REQUEST);
		}
	}
	else if(temp==3)
	{
		if(tmp==1)//˲��ADֵ
		{
		 DLS_Cur_III_AD_value[3]=value;
		 HexToChar(array_tmp,DLS_Cur_III_AD_value[3],3);	
		 MODIFY_EEP_W(Addr_DLS_Cur_III_AD_value+9,array_tmp,3,0xA0);	 

		}
		else if(tmp==2)//˲��б��ֵ
		{
		 DLS_Cur_III_slope[3]=value;
		 HexToChar(array_tmp, DLS_Cur_III_slope[3],3);	
		 MODIFY_EEP_W(Addr_DLS_Cur_III_slope+9,array_tmp,3,0xA0);

		}
		else if(tmp==3)//˲������ֵ
		{
		 DLS_Cur_III_Value[3]=value;
		 HexToChar(array_tmp,DLS_Cur_III_Value[3],3);	
		 MODIFY_EEP_W(Addr_DLS_Cur_III_Value+9,array_tmp,3,0xA0); 
		}
		else
		{
		 ERR_data_sent(ERR_NO_REQUEST);
		}
	}
	else if(temp==4)
	{
		if(tmp==1)//˲��ADֵ
		{
		 DLS_Cur_III_AD_value[4]=value;
		 HexToChar(array_tmp,DLS_Cur_III_AD_value[4],3);	
		 MODIFY_EEP_W(Addr_DLS_Cur_III_AD_value+12,array_tmp,3,0xA0);	 

		}
		else if(tmp==2)//˲��б��ֵ
		{
		 DLS_Cur_III_slope[4]=value;
		 HexToChar(array_tmp,DLS_Cur_III_slope[4],3);	
		 MODIFY_EEP_W(Addr_DLS_Cur_III_slope+12,array_tmp,3,0xA0);
		}
		else if(tmp==3)//˲������ֵ
		{
		 DLS_Cur_III_Value[4]=value;
		 HexToChar(array_tmp,DLS_Cur_III_Value[4],3);	
		 MODIFY_EEP_W(Addr_DLS_Cur_III_Value+12,array_tmp,3,0xA0); 
		}
		else
		{
		 ERR_data_sent(ERR_NO_REQUEST);
		}
	}
	}
 }	
}












//��ʼ��IO ����2
//pclk1:PCLK1ʱ��Ƶ��(Mhz)
//bound:������	  
void RS485_Init(u32 bound)
{  
//	huart1.Instance = USART1;
//	huart1.Init.BaudRate = bound;
//	huart1.Init.WordLength = UART_WORDLENGTH_9B;
//	huart1.Init.StopBits = UART_STOPBITS_1;
//	huart1.Init.Parity = UART_PARITY_EVEN;
//	huart1.Init.Mode = UART_MODE_TX_RX;
//	huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
//	huart1.Init.OverSampling = UART_OVERSAMPLING_16;
//	huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
//	huart1.Init.ClockPrescaler = UART_PRESCALER_DIV1;
//	huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
//	if (HAL_UART_Init(&huart1) != HAL_OK)
//	{
//		Error_Handler();
//	}
//	HAL_UART_Receive_IT(&huart1,(uint8_t*)tmp_uart_rx,1);
}





/* USER CODE END 1 */
