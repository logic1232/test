#include "usart.h"	 
#include "delay.h"
#include "rtc.h"
#include "tool.h"
#include "disp.h"
#include "24cxx.h"
#include "ht7038.h"
#include "main.h"
#include "dsp_fft.h"

//LCD
/**************************************
          �ڲ��洢��0ҳ
		  ������У׼ֵ����λ�������֣�
		        �ۼƼ�¼���¼���¼
				���ֲ�������
**************************************/
#define Addr_dianya				1002  //1�ֽ�
#define Addr_dianliu			1001	//1�ֽ�
#define Addr_TX           1003


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
#define Addr_wendu       10301
#define Addr_DIANYA_chonghe				10262
#define Addr_duandian				10263
#define Addr_loudian				10264
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
uint8_t Receive_Temp;        //��������
uint8_t Receive_Flag=0;      //���ձ�־ 1�����ڽ�������
uint8_t Receive_index = 0;   //��������λ������
uint8_t send_array_temp[12];    //���ڴ�ŷ��͵�BCD���� 
uint8_t Receive_CRC;         //����У��λ
uint8_t ID_array[4];  //���ڴ������ʶ����
uint8_t LCD_Receive[100];  //������������
uint8_t LCD_Receive_last[400]; //������������
uint8_t Send[400];  //������������
/************************����״̬��***************************/
uint8_t Work_State;


#define Addr_I_3d 10250


/****************
��������
****************/
void Cur_Switch(unsigned char Type_Cur);
void Cur_uart_change(unsigned long tmp);
 

extern volatile unsigned char DI0,DI1,DI2,DI3;
extern unsigned char F_Dataval1,self_addr_code[6],F_Dataval,F_Dataval_lcd,F_Dataval_wendu;
extern  signed int HT7038_buf[100];
/*���ز���*/
extern unsigned char TH_Long_Cur,F_trip_gl;//����ָ�� 
/*����ʱ����*/
extern unsigned char D2_Cur,TH_DL,F_ip;
/*˲������*/
extern unsigned char D3_Cur,F_ip_3;
/*©�����*/
unsigned int Leak_Value;
extern unsigned char D_LCur,TH_LCur,F_trip_ld;
/*g��ѹ��������*/
unsigned int Over_Vol_Value=250,Over_Vol_Time=1; 
extern unsigned char F_trip_gy,Vol_g,D_GY_yanshi;
/*Ƿѹ����*/
unsigned int Under_Vol_Value=250,Under_Vol_Time=1; 
extern unsigned char F_trip_qy,Vol_q;
/*ȱ�ౣ��*/
unsigned int lossphase_vol_setting=40,lossphase_time_setting=1; 
extern unsigned char F_trip_QX;
/*�ֺ�բ*/
extern unsigned char F_fz,F_hz;
/*��������*/
volatile unsigned char	Lcd_uart_rx[50];
uint8_t Receive_CRC_Lcd;
/*�Ǽܵ���*/
extern unsigned char Type_Cur;
extern unsigned long Delta_Cur;
int kejia;
char F_initialize;     //CJM
extern unsigned char ctrlword[5];
extern unsigned char N_GY_yanshi,N_QY_yanshi,D_GY_yanshi,D_QY_yanshi,D_SY_yanshi;
extern volatile unsigned char D_Cur;
extern volatile unsigned char baud,baud_uart;
extern volatile unsigned char tim_m3,tim_d3,tim_h3,tim_f3,tim_s3;
extern volatile unsigned int  tim_y3;
extern volatile unsigned char TH_TEM_UP,TH_TEM_DOWN;
extern volatile unsigned char TEM_UP,TEM_DOWN;
extern unsigned char mima_set[4]; // �û��趨�����룬���������������ȶ�
extern volatile  unsigned int Num_tripall,Num_triplock,Num_tripleak,Num_tripcur,Num_tripvol,Vol_A_aver,Num_leakover;
extern volatile  unsigned int Num_triphand,Num_tripzero,Num_triptest,Num_tripkey,Num_leakprotect;
extern volatile  unsigned int Num_quitleak,Num_tripdelay,Num_tripinstant;
extern volatile unsigned  long Num_clearall;
extern volatile unsigned char F_leak_maxmin,F_Conter_Updata,F_TB_trip,F_C_IP,F_Special_wave;
extern unsigned char shangdian, duandian, jiaozhun;
extern unsigned char shangdian,duandian,jiaozhun,LD_hezha,DY_hezha,DL_hezha,wendu,F_TX;	
extern  volatile unsigned char F_disp_jg;
extern volatile unsigned char  F_Leak_Delay,F_Disp,F_key,F_disp_tr,F_ld,F_ks,F_TB_gz;
extern volatile unsigned char F_hezha_state,F_fenzha_state,F_hezha_delay,LEDA_FLAG;
extern volatile unsigned int gz_disp;
extern volatile signed long I_I_Array_xianshi[20],CurA_cal_tmp[5],CurB_cal_tmp[5],CurC_cal_tmp[5],Leak1_temp,Vol1_A_temp,Vol1_B_temp,Vol1_C_temp,Leak_temp[3];
extern volatile unsigned int Leak_Cur_disp_temp;
extern volatile unsigned int  Leak_Cur_disp;
extern volatile unsigned short int N_disp,V_factor,L_factor,I_factor,L1_slope;
extern unsigned char 		F_L_err,	F_AVcal_err,			F_BVcal_err,			F_CVcal_err;
extern unsigned char F_cal_finish;
extern float Urms_A,Urms_B,Urms_C;
extern float Ugain_A,Ugain_B,Ugain_C,Igain_A,Igain_B,Igain_C,Pgain_AA,Pgain_BB,Pgain_CC;
extern unsigned int Cur_cal_tmp[2];
extern unsigned int cur_handle_A(unsigned int x);
extern unsigned int cur_handle_B(unsigned int x);
extern unsigned int cur_handle_C(unsigned int x);
extern volatile unsigned short int I1_A_slope[2],I1_B_slope[2],I1_C_slope[2];	
extern unsigned char 			F_AIcal_err,			F_BIcal_err,			F_CIcal_err;
extern unsigned char 			F_aIcal_err,			F_bIcal_err,			F_cIcal_err;
extern volatile unsigned char F_TB_trip,N_anolog_trip,F_ia,F_sssj,F_anolog_trip,LC_N,F_al1,Vol_ch ,F_trip_QL;
extern volatile unsigned	char  F_trip_sy;


void Write_or_Readresponse(uint8_t tmp,unsigned short len,unsigned char *array_temp);
void Read_Data_process(void); 
void WorRrespond_process(void);
void Write_response(uint8_t tmp);
void Warn_process();
void Protect_process();
void USART_LCD_Transmit(unsigned short len,unsigned char ch);
void LCD_Tem_trip(unsigned char phase_tmp,unsigned char gz_disp_tmp);
void ctrlword1_analyze(void);
void ctrlword2_analyze(void);
void ctrlword3_analyze(void);
void ctrlword4_analyze(void);
void RTC_Readtime(void);
void Xiebo(unsigned char ph);

////LCD
enum ERR_STATE
{
	OK = 0x00,            // ����OK 
	ERRO_NULL ,        //ָ��Ϊ�� 
	ERRO_UNKOWN_ID,    // δ֪ID
	ERRO_PARA_NONE,   //������ */
	ERRO_PARA_OUT_RANGE,
	
	//check frame
	ERRO_FRAME_UNCOMP,        // ��������֡���� 
	ERRO_FRAME_0x68,          // ����֡֡��ʼ�� 0x68 ��λ�ò��� 
	ERRO_FRAME_CHECK_SUM,     // ����֡����Ͳ��� 
	ERRO_FRAME_END_0x16,      //����֡������ 0x16 ���� 
	ERRO_NONE_FRAME,          // û���ҵ�֡

}Err_State;     //��������


void check_and_update() {
    int i;
	u8 array_tmp[3]={0};
    if (ctrlword[3] != Lcd_data_array[4]) {
        ctrlword[3] = Lcd_data_array[4];
        MODIFY_EEP_W(Addr_crtl_word4, &ctrlword[3], 1, 0xA0);
				EEPROM_R(Addr_crtl_word4, &ctrlword[3], 1, 0xA0);
				ctrlword4_analyze();
    }
    // ���μ����������
    if (Vol_g != Lcd_data_array[5]) {
        Vol_g = Lcd_data_array[5];
				array_tmp[0]=Vol_g ;
				MODIFY_EEP_W(Addr_Vol_g,array_tmp,1,0xA0);
				EEPROM_R(Addr_Vol_g,array_tmp,1,0xA0);
				Vol_g=array_tmp[0];
    }
    if (Vol_q != Lcd_data_array[6]) {
        Vol_q = Lcd_data_array[6];
				array_tmp[0]=Vol_q ;
				MODIFY_EEP_W(Addr_Vol_q,array_tmp,1,0xA0);
				EEPROM_R(Addr_Vol_q,array_tmp,1,0xA0);
				Vol_q=array_tmp[0];
    }
    if (D_SY_yanshi != Lcd_data_array[7]) {
        D_SY_yanshi = Lcd_data_array[7];
				array_tmp[0]=D_SY_yanshi ;
				MODIFY_EEP_W(Addr_SY_yanshi,array_tmp,1,0xA0);
				EEPROM_R(Addr_SY_yanshi,array_tmp,1,0xA0);
				D_SY_yanshi=array_tmp[0];
    }
    if (D_GY_yanshi != Lcd_data_array[8]) {
        D_GY_yanshi = Lcd_data_array[8];
				array_tmp[0]=D_GY_yanshi ;
				MODIFY_EEP_W(Addr_GY_yanshi,array_tmp,1,0xA0);
				EEPROM_R(Addr_GY_yanshi,array_tmp,1,0xA0);
				D_GY_yanshi=array_tmp[0];
			
    }
    if (D_QY_yanshi != Lcd_data_array[9]) {
        D_QY_yanshi = Lcd_data_array[9];
				array_tmp[0]=D_QY_yanshi ;
				MODIFY_EEP_W(Addr_QY_yanshi,array_tmp,1,0xA0);
				EEPROM_R(Addr_QY_yanshi,array_tmp,1,0xA0);
				D_QY_yanshi=array_tmp[0];
    }
    if (D3_Cur != Lcd_data_array[10]) {
        D3_Cur = Lcd_data_array[10];
				array_tmp[0]=D3_Cur ;
				MODIFY_EEP_W(Addr_D3_Cur,array_tmp,1,0xA0);
				EEPROM_R(Addr_D3_Cur,array_tmp,1,0xA0);
				D3_Cur=array_tmp[0];
    }
    if (D_Cur != Lcd_data_array[11]) {
        D_Cur = Lcd_data_array[11];
				array_tmp[0]=D_Cur ;
				MODIFY_EEP_W(Addr_D_Cur,array_tmp,1,0xA0);
				EEPROM_R(Addr_D_Cur,array_tmp,1,0xA0);
				D_Cur=array_tmp[0];
    }
    if (TH_Long_Cur != Lcd_data_array[12]) {
        TH_Long_Cur = Lcd_data_array[12];
				array_tmp[0]=TH_Long_Cur ;
				MODIFY_EEP_W(Addr_CurLong_Time,array_tmp,1,0xA0);
				EEPROM_R(Addr_CurLong_Time,array_tmp,1,0xA0);
				TH_Long_Cur=array_tmp[0];
    }
    if (D2_Cur != Lcd_data_array[13]) {
        D2_Cur = Lcd_data_array[13];
				array_tmp[0]=D2_Cur ;
				MODIFY_EEP_W(Addr_D2_Cur,array_tmp,1,0xA0);
				EEPROM_R(Addr_D2_Cur,array_tmp,1,0xA0);
				D2_Cur=array_tmp[0];
    }
    if (TH_DL != Lcd_data_array[14]) {
        TH_DL = Lcd_data_array[14];
				array_tmp[0]=TH_DL ;
				MODIFY_EEP_W(Addr_D2_Time,array_tmp,1,0xA0);
				EEPROM_R(Addr_D2_Time,array_tmp,1,0xA0);
				TH_DL=array_tmp[0];
    }
    unsigned int new_baud = (Lcd_data_array[15] << 8) + Lcd_data_array[16];
    if (baud != new_baud) {
        baud = new_baud;
				array_tmp[0]=TH_DL ;
				MODIFY_EEP_W(Addr_D2_Time,array_tmp,1,0xA0);
				EEPROM_R(Addr_D2_Time,array_tmp,1,0xA0);
				TH_DL=array_tmp[0];
    }
    unsigned int new_Type_Cur = (Lcd_data_array[17] << 8) + Lcd_data_array[18];
    if (Type_Cur != new_Type_Cur) {
        Type_Cur = new_Type_Cur;
				array_tmp[0]=Type_Cur ;
				MODIFY_EEP_W(Addr_Type_Cur,array_tmp,1,0xA0);
				EEPROM_R(Addr_Type_Cur,array_tmp,1,0xA0);
				Type_Cur=array_tmp[0];
    }
    unsigned int new_tim_y3 = (Lcd_data_array[19] << 8) + Lcd_data_array[20];
    if (tim_y3 != new_tim_y3) {
        tim_y3 = new_tim_y3;
			 RTC_Set_Time(tim_h3,tim_f3,tim_s3);
			 RTC_Set_Date(tim_y3,tim_m3,tim_d3);
    }
    unsigned int new_tim_m3 = (Lcd_data_array[21] << 8) + Lcd_data_array[22];
    if (tim_m3 != new_tim_m3) {
        tim_m3 = new_tim_m3;
        RTC_Set_Time(tim_h3,tim_f3,tim_s3);
				RTC_Set_Date(tim_y3,tim_m3,tim_d3);
    }
    unsigned int new_tim_d3 = (Lcd_data_array[23] << 8) + Lcd_data_array[24];
    if (tim_d3 != new_tim_d3) {
        tim_d3 = new_tim_d3;
				 RTC_Set_Time(tim_h3,tim_f3,tim_s3);
				 RTC_Set_Date(tim_y3,tim_m3,tim_d3);
    }
    unsigned int new_tim_h3 = (Lcd_data_array[25] << 8) + Lcd_data_array[26];
    if (tim_h3 != new_tim_h3) {
        tim_h3 = new_tim_h3;
				 RTC_Set_Time(tim_h3,tim_f3,tim_s3);
				 RTC_Set_Date(tim_y3,tim_m3,tim_d3);
    }
    unsigned int new_tim_f3 = (Lcd_data_array[27] << 8) + Lcd_data_array[28];
    if (tim_f3 != new_tim_f3) {
        tim_f3 = new_tim_f3;
				 RTC_Set_Time(tim_h3,tim_f3,tim_s3);
				 RTC_Set_Date(tim_y3,tim_m3,tim_d3);
    }
    unsigned int new_tim_s3 = (Lcd_data_array[29] << 8) + Lcd_data_array[30];
    if (tim_s3 != new_tim_s3) {
        tim_s3 = new_tim_s3;
				 RTC_Set_Time(tim_h3,tim_f3,tim_s3);
				 RTC_Set_Date(tim_y3,tim_m3,tim_d3);
    }
    unsigned int new_TH_TEM_UP = (Lcd_data_array[31] << 8) + Lcd_data_array[32];
    if (TH_TEM_UP != new_TH_TEM_UP) {
        TH_TEM_UP = new_TH_TEM_UP;  
				array_tmp[0]=TH_TEM_UP ;
				MODIFY_EEP_W(Addr_temperature_UP,array_tmp,1,0xA0);
				EEPROM_R(Addr_temperature_UP,array_tmp,1,0xA0);
				TH_TEM_UP=array_tmp[0];
    }
    unsigned int new_TH_TEM_DOWN = (Lcd_data_array[33] << 8) + Lcd_data_array[34];
    if (TH_TEM_DOWN != new_TH_TEM_DOWN) {
        TH_TEM_DOWN = new_TH_TEM_DOWN;
				array_tmp[0]=TH_TEM_DOWN ;
				MODIFY_EEP_W(Addr_temperature_DOWN,array_tmp,1,0xA0);
				EEPROM_R(Addr_temperature_DOWN,array_tmp,1,0xA0);
				TH_TEM_DOWN=array_tmp[0];
    }
    for (i = 0; i < 4; i++) {
        if (mima_set[i] != Lcd_data_array[35 + i]) {
            mima_set[i] = Lcd_data_array[35 + i];
						MODIFY_EEP_W(Addr_mima_set,mima_set,4,0xA0);
        }
    }
    for (i = 0; i < 6; i++) {
        if (self_addr_code[i] != Lcd_data_array[39 + i]) {
            self_addr_code[i] = Lcd_data_array[39 + i];
            MODIFY_EEP_W(Addr_dev_addr,self_addr_code,6,0xA0);
        }
    }
    for (i = 0; i < 3; i++) {
        if (ctrlword[i] != Lcd_data_array[45 + i]) {
            ctrlword[i] = Lcd_data_array[45 + i];
            // ���µ�ֵд��洢 (���� write_to_storage ��һ��д��洢�ĺ���)
            MODIFY_EEP_W(Addr_crtl_word1,ctrlword,1,0xA0);
						MODIFY_EEP_W(Addr_crtl_word2,&ctrlword[1],1,0xA0);
						MODIFY_EEP_W(Addr_crtl_word3,&ctrlword[2],1,0xA0);
						ctrlword1_analyze();
						ctrlword2_analyze();
						ctrlword3_analyze();
        }
    }
    if (F_TB_trip != Lcd_data_array[48]) {
        F_TB_trip = Lcd_data_array[48];
				array_tmp[0]=F_TB_trip ;
				MODIFY_EEP_W(Addr_L_TB,array_tmp,1,0xA0);
				EEPROM_R(Addr_L_TB,array_tmp,1,0xA0);
				F_TB_trip=array_tmp[0];
    }
    if (F_Special_wave != Lcd_data_array[49]) {
        F_Special_wave = Lcd_data_array[49];
				array_tmp[0]=F_Special_wave ;
				MODIFY_EEP_W(Addr_L_specialwave,array_tmp,1,0xA0);
				EEPROM_R(Addr_L_specialwave,array_tmp,1,0xA0);
				F_Special_wave=array_tmp[0];
    }
    if (F_ip != Lcd_data_array[50]) {
        F_ip = Lcd_data_array[50];
				array_tmp[0]=F_ip ;
				MODIFY_EEP_W(Addr_I_2d,array_tmp,1,0xA0);
				EEPROM_R(Addr_I_2d,array_tmp,1,0xA0);
				F_ip=array_tmp[0];
    }
    if (F_ip_3 != Lcd_data_array[51]) {
        F_ip_3 = Lcd_data_array[51];
				array_tmp[0]=F_ip_3 ;
				MODIFY_EEP_W(Addr_I_3d,array_tmp,1,0xA0);
				EEPROM_R(Addr_I_3d,array_tmp,1,0xA0);
				F_ip_3=array_tmp[0];
    }
    if (jiaozhun != Lcd_data_array[52]) {
        jiaozhun = Lcd_data_array[52];
				array_tmp[0]=F_ip_3 ;
				MODIFY_EEP_W(Addr_I_3d,array_tmp,1,0xA0);
				EEPROM_R(Addr_I_3d,array_tmp,1,0xA0);
				F_ip_3=array_tmp[0];
    }
    if (shangdian != Lcd_data_array[53]) {
        shangdian = Lcd_data_array[53];
				array_tmp[0]=shangdian ;
				MODIFY_EEP_W(Addr_shangdian,array_tmp,1,0xA0);
				EEPROM_R(Addr_shangdian,array_tmp,1,0xA0);
				shangdian=array_tmp[0];
    }
    if (LD_hezha != Lcd_data_array[54]) {
        LD_hezha = Lcd_data_array[54];
				array_tmp[0]=LD_hezha ;
				MODIFY_EEP_W(Addr_loudian,array_tmp,1,0xA0);
				EEPROM_R(Addr_loudian,array_tmp,1,0xA0);
				LD_hezha=array_tmp[0];
    }
    if (DY_hezha != Lcd_data_array[55]) {
        DY_hezha = Lcd_data_array[55];
				array_tmp[0]=DY_hezha ;
				MODIFY_EEP_W(Addr_dianya,array_tmp,1,0xA0);
				EEPROM_R(Addr_dianya,array_tmp,1,0xA0);
				DY_hezha=array_tmp[0];
    }
    if (DL_hezha != Lcd_data_array[56]) {
        DL_hezha = Lcd_data_array[56];
				array_tmp[0]=DL_hezha ;
				MODIFY_EEP_W(Addr_dianliu,array_tmp,1,0xA0);
				EEPROM_R(Addr_dianliu,array_tmp,1,0xA0);
				DL_hezha=array_tmp[0];
    }
    if (wendu != Lcd_data_array[57]) {
        wendu = Lcd_data_array[57];
				array_tmp[0]=wendu ;
				MODIFY_EEP_W(Addr_wendu,array_tmp,1,0xA0);
				EEPROM_R(Addr_wendu,array_tmp,1,0xA0);
				wendu=array_tmp[0];
    }
    if (F_TX != Lcd_data_array[58]) {
        F_TX = Lcd_data_array[58];
				array_tmp[0]=F_TX ;
				MODIFY_EEP_W(Addr_TX,array_tmp,1,0xA0);
				EEPROM_R(Addr_TX,array_tmp,1,0xA0);
				F_TX=array_tmp[0];
    }
		if (TH_LCur != Lcd_data_array[59]) {
        TH_LCur = Lcd_data_array[59];
				array_tmp[0]=TH_LCur ;
				MODIFY_EEP_W(Addr_TH_LCur,array_tmp,1,0xA0);
				EEPROM_R(Addr_TH_LCur,array_tmp,1,0xA0);
				TH_LCur=array_tmp[0];
    }
		if (F_trip_sy != Lcd_data_array[60]) {
        F_trip_sy = Lcd_data_array[60];
				array_tmp[0]=F_trip_sy ;
				MODIFY_EEP_W(Addr_SY_F,array_tmp,1,0xA0);
				EEPROM_R(Addr_SY_F,array_tmp,1,0xA0);
				F_trip_sy=array_tmp[0];
    }
}

void LCD_Cal(void)
{
			unsigned char array_temp[2],array_tmp[2];
			unsigned short int  Vol_cal_tmp=220,L_cal_tmp=200;
			signed int L_factor_tmp1,I_A_factor_tmp,V_A_factor_tmp,I_B_factor_tmp,V_B_factor_tmp,I_C_factor_tmp,V_C_factor_tmp;
				if(Cal_state==0)
				{				
					Leak1_temp=Leak_Cur_disp_temp;
					L_factor_tmp1=Leak_Cur_disp-L_cal_tmp;
//					if((L_factor_tmp1>-20)&&(L_factor_tmp1<20))//©��У׼
					{       
						L1_slope=(L_cal_tmp<<20)/(Leak1_temp);
						HexToChar(array_temp,L1_slope,2);
						HexToChar(array_tmp,Leak1_temp,2);
//						if(Type_Cur==0)
//						{
//							MODIFY_EEP_W(Addr800_L1_slope,array_temp,2,0xA0);
//							MODIFY_EEP_W(Addr800_Leak1_temp,array_tmp,2,0xA0);
//						}
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
						else if(Type_Cur==4)
						{
							MODIFY_EEP_W(Addr800_L1_slope,array_temp,2,0xA0);
							MODIFY_EEP_W(Addr800_Leak1_temp,array_tmp,2,0xA0);
						}
						
						F_L_err=0;
						F_cal_finish=1;
					}
//					else
//					{
////						L_factor=L_factor;
//						F_L_err=1;
//					}
				}
				if(Cal_state==1)
				{
					
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
	F_cal_finish=1;
				}

				if(Cal_state==2)					//����У׼100A
				{
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
					else if(Type_Cur==4)
						{
							Cur_cal_tmp[0]=320;
							Cur_cal_tmp[1]=800;
							
						}
					
						CurA_cal_tmp[0]=I_I_Array_xianshi[0];//I_I_Array_xianshi//I_Array_xianshi
						I_A_factor_tmp=cur_handle_A(I_I_Array_xianshi[0])-Cur_cal_tmp[0];	
						I1_A_slope[0]=(Cur_cal_tmp[0]<<20)/(CurA_cal_tmp[0]);//A����У׼��1
						HexToChar(array_temp,I1_A_slope[0],2);
						HexToChar(array_tmp,CurA_cal_tmp[0],2);
						if(Type_Cur==0)
						{
							MODIFY_EEP_W(Addr100_I1_A_slope,array_temp,2,0xA0);
							MODIFY_EEP_W(Addr100_CurA_cal_tmp,array_tmp,2,0xA0);
						}
						else if(Type_Cur==1)
						{
							MODIFY_EEP_W(Addr_I1_A_slope,array_temp,2,0xA0);
							MODIFY_EEP_W(Addr_CurA_cal_tmp,array_tmp,2,0xA0);
						}
						else if(Type_Cur==2)
						{
							MODIFY_EEP_W(Addr400_I1_A_slope,array_temp,2,0xA0);
							MODIFY_EEP_W(Addr400_CurA_cal_tmp,array_tmp,2,0xA0);
						}
						else if(Type_Cur==3)
						{
							MODIFY_EEP_W(Addr630_I1_A_slope,array_temp,2,0xA0);
							MODIFY_EEP_W(Addr630_CurA_cal_tmp,array_tmp,2,0xA0);
						}
					  else if(Type_Cur==4)
						{
							MODIFY_EEP_W(Addr800_I1_A_slope,array_temp,2,0xA0);
							MODIFY_EEP_W(Addr800_CurA_cal_tmp,array_tmp,2,0xA0);
						}
						
						
						
						CurB_cal_tmp[0]=I_I_Array_xianshi[1];
						I_B_factor_tmp=cur_handle_B(I_I_Array_xianshi[1])-Cur_cal_tmp[0];			
						I1_B_slope[0]=(Cur_cal_tmp[0]<<20)/(CurB_cal_tmp[0]);//B����У׼��1
						HexToChar(array_temp,I1_B_slope[0],2);
						HexToChar(array_tmp,CurB_cal_tmp[0],2);
						if(Type_Cur==0)
						{
							MODIFY_EEP_W(Addr100_I1_B_slope,array_temp,2,0xA0);
							MODIFY_EEP_W(Addr100_CurB_cal_tmp,array_tmp,2,0xA0);
						}
						else if(Type_Cur==1)
						{
							MODIFY_EEP_W(Addr_I1_B_slope,array_temp,2,0xA0);
							MODIFY_EEP_W(Addr_CurB_cal_tmp,array_tmp,2,0xA0);
						}
						else if(Type_Cur==2)
						{
							MODIFY_EEP_W(Addr400_I1_B_slope,array_temp,2,0xA0);
							MODIFY_EEP_W(Addr400_CurB_cal_tmp,array_tmp,2,0xA0);
						}
						else if(Type_Cur==3)
						{
							MODIFY_EEP_W(Addr630_I1_B_slope,array_temp,2,0xA0);
							MODIFY_EEP_W(Addr630_CurB_cal_tmp,array_tmp,2,0xA0);
						}
						else if(Type_Cur==4)
						{
							MODIFY_EEP_W(Addr800_I1_B_slope,array_temp,2,0xA0);
							MODIFY_EEP_W(Addr800_CurB_cal_tmp,array_tmp,2,0xA0);
						}

						
						
						CurC_cal_tmp[0]=I_I_Array_xianshi[2];
						I_C_factor_tmp=cur_handle_C(I_I_Array_xianshi[2])-Cur_cal_tmp[0];					
						I1_C_slope[0]=(Cur_cal_tmp[0]<<20)/(CurC_cal_tmp[0]);//C����У׼��1
						HexToChar(array_temp,I1_C_slope[0],2);
						HexToChar(array_tmp,CurC_cal_tmp[0],2);
						if(Type_Cur==0)
						{
							MODIFY_EEP_W(Addr100_I1_C_slope,array_temp,2,0xA0);
							MODIFY_EEP_W(Addr100_CurC_cal_tmp,array_tmp,2,0xA0);
						}
						else if(Type_Cur==1)
						{
							MODIFY_EEP_W(Addr_I1_C_slope,array_temp,2,0xA0);
							MODIFY_EEP_W(Addr_CurC_cal_tmp,array_tmp,2,0xA0);
						}
						else if(Type_Cur==2)
						{
							MODIFY_EEP_W(Addr400_I1_C_slope,array_temp,2,0xA0);
							MODIFY_EEP_W(Addr400_CurC_cal_tmp,array_tmp,2,0xA0);
						}
						else if(Type_Cur==3)
						{
							MODIFY_EEP_W(Addr630_I1_C_slope,array_temp,2,0xA0);
							MODIFY_EEP_W(Addr630_CurC_cal_tmp,array_tmp,2,0xA0);
						}
						else if(Type_Cur==4)
						{
							MODIFY_EEP_W(Addr800_I1_C_slope,array_temp,2,0xA0);
							MODIFY_EEP_W(Addr800_CurC_cal_tmp,array_tmp,2,0xA0);
						}
						F_CIcal_err=0;
						F_cal_finish=1;
				}

	/***	****************************abc����У׼��2****************/	//	250A
				if(Cal_state==3)
				{
								
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
						else if(Type_Cur==3)
						{
							Cur_cal_tmp[0]=320;
							Cur_cal_tmp[1]=800;
						}
						CurA_cal_tmp[1]=I_I_Array_xianshi[0];
						I_A_factor_tmp=cur_handle_A(I_I_Array_xianshi[0])-Cur_cal_tmp[1];	
						I1_A_slope[1]=((Cur_cal_tmp[1]-Cur_cal_tmp[0])<<20)/(CurA_cal_tmp[1]-CurA_cal_tmp[0]);//a����У׼��2
						HexToChar(array_temp,I1_A_slope[1],2);
						HexToChar(array_tmp,CurA_cal_tmp[1],2);
						if(Type_Cur==0)
						{
							MODIFY_EEP_W(Addr100_I1_A_slope1,array_temp,2,0xA0);
							MODIFY_EEP_W(Addr100_CurA_cal_tmp1,array_tmp,2,0xA0);
						}
						else if(Type_Cur==1)
						{
							MODIFY_EEP_W(Addr_I1_A_slope1,array_temp,2,0xA0);
							MODIFY_EEP_W(Addr_CurA_cal_tmp1,array_tmp,2,0xA0);
						}
						else if(Type_Cur==2)
						{
							MODIFY_EEP_W(Addr400_I1_A_slope1,array_temp,2,0xA0);
							MODIFY_EEP_W(Addr400_CurA_cal_tmp1,array_tmp,2,0xA0);
						}
						else if(Type_Cur==3)
						{
							MODIFY_EEP_W(Addr630_I1_A_slope1,array_temp,2,0xA0);
							MODIFY_EEP_W(Addr630_CurA_cal_tmp1,array_tmp,2,0xA0);
						}
												else if(Type_Cur==4)
						{
							MODIFY_EEP_W(Addr800_I1_A_slope1,array_temp,2,0xA0);
							MODIFY_EEP_W(Addr800_CurA_cal_tmp1,array_tmp,2,0xA0);
						}
						CurB_cal_tmp[1]=I_I_Array_xianshi[1];
						I_B_factor_tmp=cur_handle_B(I_I_Array_xianshi[1])-Cur_cal_tmp[1];			
						I1_B_slope[1]=((Cur_cal_tmp[1]-Cur_cal_tmp[0])<<20)/(CurB_cal_tmp[1]-CurB_cal_tmp[0]);//b����У׼��2
						HexToChar(array_temp,I1_B_slope[1],2);
						HexToChar(array_tmp,CurB_cal_tmp[1],2);
						if(Type_Cur==0)
						{
							MODIFY_EEP_W(Addr100_I1_B_slope1,array_temp,2,0xA0);
							MODIFY_EEP_W(Addr100_CurB_cal_tmp1,array_tmp,2,0xA0);
						}
						else if(Type_Cur==1)
						{
							MODIFY_EEP_W(Addr_I1_B_slope1,array_temp,2,0xA0);
							MODIFY_EEP_W(Addr_CurB_cal_tmp1,array_tmp,2,0xA0);
						}
						else if(Type_Cur==2)
						{
							MODIFY_EEP_W(Addr400_I1_B_slope1,array_temp,2,0xA0);
							MODIFY_EEP_W(Addr400_CurB_cal_tmp1,array_tmp,2,0xA0);
						}
						else if(Type_Cur==3)
						{
							MODIFY_EEP_W(Addr630_I1_B_slope1,array_temp,2,0xA0);
							MODIFY_EEP_W(Addr630_CurB_cal_tmp1,array_tmp,2,0xA0);
						}
						else if(Type_Cur==4)
						{
							MODIFY_EEP_W(Addr800_I1_B_slope1,array_temp,2,0xA0);
							MODIFY_EEP_W(Addr800_CurB_cal_tmp1,array_tmp,2,0xA0);
						}
						CurC_cal_tmp[1]=I_I_Array_xianshi[2];
						I_C_factor_tmp=cur_handle_C(I_I_Array_xianshi[2])-Cur_cal_tmp[1];					
						I1_C_slope[1]=((Cur_cal_tmp[1]-Cur_cal_tmp[0])<<20)/(CurC_cal_tmp[1]-CurC_cal_tmp[0]);//c����У׼��2
						HexToChar(array_temp,I1_C_slope[1],2);
						HexToChar(array_tmp,CurC_cal_tmp[1],2);
						if(Type_Cur==0)
						{
							MODIFY_EEP_W(Addr100_I1_C_slope1,array_temp,2,0xA0);
							MODIFY_EEP_W(Addr100_CurC_cal_tmp1,array_tmp,2,0xA0);
						}
						else if(Type_Cur==1)
						{
							MODIFY_EEP_W(Addr_I1_C_slope1,array_temp,2,0xA0);
							MODIFY_EEP_W(Addr_CurC_cal_tmp1,array_tmp,2,0xA0);
						}
						else if(Type_Cur==2)
						{
							MODIFY_EEP_W(Addr400_I1_C_slope1,array_temp,2,0xA0);
							MODIFY_EEP_W(Addr400_CurC_cal_tmp1,array_tmp,2,0xA0);
						}
						else if(Type_Cur==3)
						{
							MODIFY_EEP_W(Addr630_I1_C_slope1,array_temp,2,0xA0);
							MODIFY_EEP_W(Addr630_CurC_cal_tmp1,array_tmp,2,0xA0);
						}
						else if(Type_Cur==4)
						{
							MODIFY_EEP_W(Addr800_I1_C_slope1,array_temp,2,0xA0);
							MODIFY_EEP_W(Addr800_CurC_cal_tmp1,array_tmp,2,0xA0);
						}
						F_cIcal_err=0;
						F_cal_finish=1;
				}
}

void LCD_Temp_process(void)
{
	
}

void UART_LCD_process(void)
{
	u8 array_tmp[57]={0};
	u8 index=0;
	//data_array0��1��2��3Ԫ��Ϊʶ���룬��4��ʼ������
	
	if(Lcd_data_array[0]==0x90)
	{
		check_and_update();
		array_tmp[0]=ctrlword[3];
		array_tmp[1]=Vol_g;
		array_tmp[2]=Vol_q;
		array_tmp[3]=D_SY_yanshi ;
		array_tmp[4]=D_GY_yanshi ;
		array_tmp[5] = D_QY_yanshi ;
		array_tmp[6] = D3_Cur;
		array_tmp[7] = D_Cur;
		array_tmp[8] =TH_Long_Cur  ;
		array_tmp[9] = D2_Cur;
		array_tmp[10] = TH_DL;
		array_tmp[11] = ( baud>> 8) & 0xFF;
		array_tmp[12] = baud  & 0xFF;
		array_tmp[13] = ( Type_Cur>> 8) & 0xFF;
		array_tmp[14] = Type_Cur   & 0xFF;
		array_tmp[15] = ( tim_y3>> 8) & 0xFF;
		array_tmp[16] = tim_y3  & 0xFF;
		array_tmp[17] = ( tim_m3>> 8) & 0xFF;
		array_tmp[18] = tim_m3  & 0xFF;
		array_tmp[19] =  ( tim_d3>> 8) & 0xFF;
		array_tmp[20] =  tim_d3  & 0xFF;
		array_tmp[21] =  ( tim_h3>> 8) & 0xFF;
		array_tmp[22] =  tim_h3  & 0xFF;
		array_tmp[23] =  ( tim_f3>> 8) & 0xFF;
		array_tmp[24] =  tim_f3  & 0xFF;
		array_tmp[25] =  ( tim_s3>> 8) & 0xFF;
		array_tmp[26] =  tim_s3  & 0xFF;
		array_tmp[27] = ( TH_TEM_UP >> 8) & 0xFF;
		array_tmp[28] = TH_TEM_UP  & 0xFF;
		array_tmp[29] = ( TH_TEM_DOWN>> 8) & 0xFF;
		array_tmp[30] = TH_TEM_DOWN  & 0xFF;
		array_tmp[31] = mima_set[0];
		array_tmp[32] = mima_set[1];
		array_tmp[33] = mima_set[2];
		array_tmp[34] = mima_set[3];
		array_tmp[35] = self_addr_code[0];
		array_tmp[36] = self_addr_code[1];
		array_tmp[37] = self_addr_code[2];
		array_tmp[38] = self_addr_code[3];
		array_tmp[39] = self_addr_code[4];
		array_tmp[40] = self_addr_code[5];
		array_tmp[41] = ctrlword[0];
		array_tmp[42] =  ctrlword[1];
		array_tmp[43] =  ctrlword[2];
		array_tmp[44] = F_TB_trip;
		array_tmp[45] = F_Special_wave;
		array_tmp[46] = F_ip;
		array_tmp[47] = F_ip_3;
		array_tmp[48] = jiaozhun;
		array_tmp[49] = shangdian;
		array_tmp[50] = LD_hezha;
		array_tmp[51] = DY_hezha;
		array_tmp[52] = DL_hezha;
		array_tmp[53] = wendu;
		array_tmp[54] = F_TX;
		array_tmp[55] = TH_LCur;
		array_tmp[56] = F_trip_sy;
		
		
		
//		ctrlword[3]=Lcd_data_array[4];  //������4
//		Vol_g=Lcd_data_array[5]; //��ѹ��λ
//		Vol_q=Lcd_data_array[6]; //Ƿѹ��λ
//		D_SY_yanshi=Lcd_data_array[7]; //ʧѹ��ʱ
//		D_GY_yanshi=Lcd_data_array[8]; //��ѹ��ʱ
//		D_QY_yanshi=Lcd_data_array[9]; //Ƿѹ��ʱ
//		D3_Cur=Lcd_data_array[10]; //˲ʱ��λ
//		D_Cur=Lcd_data_array[11]; //������λ
//		TH_Long_Cur=Lcd_data_array[12]; //����ʱ��
//		D2_Cur=Lcd_data_array[13];//���ӵ�λ
//		TH_DL=Lcd_data_array[14];//����ʱ��
//		baud=(Lcd_data_array[15]<<8)+(Lcd_data_array[16]);//ͨ������
//		Type_Cur=(Lcd_data_array[17]<<8)+(Lcd_data_array[18]);//�Ǽ�����
//		tim_y3=(Lcd_data_array[19]<<8)+(Lcd_data_array[20]);//���� ��
//		tim_m3=(Lcd_data_array[21]<<8)+(Lcd_data_array[22]);//���� ��
//		tim_d3=(Lcd_data_array[23]<<8)+(Lcd_data_array[24]);//���� ��
//		tim_h3=(Lcd_data_array[25]<<8)+(Lcd_data_array[26]);//ʱ�� ʱ
//		tim_f3=(Lcd_data_array[27]<<8)+(Lcd_data_array[28]);//ʱ�� ��
//		tim_s3=(Lcd_data_array[29]<<8)+(Lcd_data_array[30]);//ʱ�� ��
//		TH_TEM_UP=(Lcd_data_array[31]<<8)+(Lcd_data_array[32]);//���·�բ
//		TH_TEM_DOWN=(Lcd_data_array[33]<<8)+(Lcd_data_array[34]);//���º�բ
//		mima_set[0]=Lcd_data_array[35];//����
//		mima_set[1]=Lcd_data_array[36];//����
//		mima_set[2]=Lcd_data_array[37];//����
//		mima_set[3]=Lcd_data_array[38];//����
//		self_addr_code[0]=Lcd_data_array[39];//ͨ�ŵ�ַ�ֽ�0
//		self_addr_code[1]=Lcd_data_array[40];//ͨ�ŵ�ַ�ֽ�1
//		self_addr_code[2]=Lcd_data_array[41];//ͨ�ŵ�ַ�ֽ�2
//		self_addr_code[3]=Lcd_data_array[42];//ͨ�ŵ�ַ�ֽ�3
//		self_addr_code[4]=Lcd_data_array[43];//ͨ�ŵ�ַ�ֽ�4
//		self_addr_code[5]=Lcd_data_array[44];//ͨ�ŵ�ַ�ֽ�5
//		ctrlword[0]=Lcd_data_array[45];
//		ctrlword[1]=Lcd_data_array[46];
//		ctrlword[2]=Lcd_data_array[47];
//		F_TB_trip = Lcd_data_array[48];
//		F_Special_wave = Lcd_data_array[49];
//		F_ip = Lcd_data_array[50];
//		F_ip_3 = Lcd_data_array[51];
//		jiaozhun = Lcd_data_array[52];
//		shangdian = Lcd_data_array[53];
//		LD_hezha = Lcd_data_array[54];
//		DY_hezha = Lcd_data_array[55];
//		DL_hezha = Lcd_data_array[56];
//		wendu = Lcd_data_array[57];
//		F_TX = Lcd_data_array[58];
		
		USART_LCD_Transmit(57,1); //1Ϊ��λ����
	}
	
	if(Lcd_data_array[0]==0x04)
	{
		array_tmp[0]=Lcd_data_array[4]; //У׼����
		array_tmp[1]=Lcd_data_array[5];		//��ʼУ׼
		Cal_state=array_tmp[0];
		if(array_tmp[1]) 
		{
			LCD_Cal();
			USART_LCD_Transmit(1,3); //1Ϊ��λ����
		}
	}
	
	if(Lcd_data_array[0]==0x05)  //�����־λ
	{
		if(Lcd_data_array[4]==1)
		{F_gz_disp=0x0F;}
	}
	if(Lcd_data_array[0]==0x06)  //��ʼ����־λ
	{
		if(Lcd_data_array[4]==1){
			F_initialize=1;
			
		}
	
		
	}
	
	if(Lcd_data_array[0]==0x32)  //�ֺ�բ����
	{
		array_tmp[0]=Lcd_data_array[4]; //©������
		array_tmp[1]=Lcd_data_array[5]; //�ֶ���բ�ź�
		array_tmp[2]=Lcd_data_array[6]; //�ֶ���բ�ź�
		array_tmp[3]=Lcd_data_array[7]; //���·�բ�ź�
		array_tmp[4]=Lcd_data_array[8]; //���·�բ��
		array_tmp[5]=Lcd_data_array[9];//�����¶�ֵ
		array_tmp[6]=Lcd_data_array[10];//���º�բ�ź�
		
		if(array_tmp[1]==1)//�ֶ���բ�ź�
		{
			//ֻ�ں�բ״̬��������
			if(isfenzha==1)
			{
				F_fz=1 ;
				F_hz=0 ;
				//F_fenzha_state=1;
				USART_LCD_Transmit(10,4);
			}
		}
		//ֻ�ڷ�բ״̬��������
		if(array_tmp[2]==1)  //�ֶ���բ�ź�
		{
			if((isfenzha==0))//ֻ�ڷ�բ״̬�������ã�����û�ڸ������úͲ�ѯҳ��
			{
				F_fz=0 ;
				F_hz=1 ;
				//F_hezha_state=1;
			}
		}
			//©����������
		if(array_tmp[0]==1)
		{

			if(isfenzha!=0)
			{
				F_anolog_trip = 1;
				N_anolog_trip = 0;//û��
				Leak_Test_HIGH;
				delay_ms(50);
				Leak_Test_LOW;
				//Trip_Action();//�ѿ�
			}
		}
		
		if((array_tmp[3]==1)&&(isfenzha == 1))
		{
			LCD_Tem_trip(array_tmp[4],array_tmp[5]);  //�¶ȱ���
		}
	}
	if(Lcd_data_array[0]==0x08)
	{
		USART_LCD_Transmit(60,6);
		USART_LCD_Transmit(60,7);
		USART_LCD_Transmit(60,8);
		USART_LCD_Transmit(60,9);
		USART_LCD_Transmit(60,10);
		USART_LCD_Transmit(72,11);
	}
	if(Lcd_data_array[0]==0x09)
	{
		USART_LCD_Transmit(90,13);
		USART_LCD_Transmit(90,14);
	}

}
void Clear_Send_Data()  //�����������ͱ�־λ
{
	for(uint8_t i=0;i<100;i++)
	{
		Send[i] = 0;    
	}
	Receive_Flag = 0;
	Receive_index = 0;
	F_Dataval_lcd = 0;
	Receive_Temp = 0;
}
void LCD_Send_Data(uint8_t *buf,uint16_t length)  //����ָ����������
{
	for(uint8_t i=0;i<length;i++)
	{
		HAL_UART_Transmit(&huart1,&buf[i],1,100);		///	
//		while(huart3.gState != HAL_UART_STATE_READY)
//		{}
	}	
}
void LCD_Uart_prepare(uint8_t tmp)  //��֡ͷ����ַ��ʶ����  Send[9]��ʼΪ������
{
	unsigned char i;
	Clear_Send_Data();  //���Ҫ���͵�����
	Send[0]=Send[2] = 0x68;//��ʼ�� 
	Send[1] =  0xA0;    //1Ϊ��ַ��
	
	if(tmp==0x00 || tmp==0x10)
	{
		if(tmp==0x00)
		{
		  Send[3]	= 0x51;   //������51 ��վ����Ӧ��֡  
      for(i=0;i<4;i++)
			Send[5+i] = LCD_Receive_last[5+i]; //����ʶ����			
		}
		else if(tmp==0x10)
		{
			Send[3]	= 0x14;   //������51 ��վд����
			Send[5] = DI3;
			Send[6] = DI2;
			Send[7] = DI1;
			Send[8] = DI0;    //����ʶ����
		}
	}
	else if(tmp==0x01)
	{
		Send[3]	= 0x71;  //71��վ�쳣Ӧ��֡
		Send[4] = 1 ;
//		Send[5] = Err_State; //�쳣����
	}
}
void Send_Data2LCD_process(uint8_t *ID_array, uint8_t *array_temp, uint8_t len)//��֡
{
	int i,cs = 0;
	Send[0] = 0x68;//��ʼ����
	Send[1] = 0xA0;
	Send[2] = 0x68;
	Send[3] = 0x14; //������ӻ��������� д���ݹ�����
	Send[4] = 4 + len ;
	for(i = 0;i<4;i++)
	{
		Send[5+i] = ID_array[i];   //����ʶ����
	}
	for(i = 0;i<len;i++)
	{
		Send[9+i] = array_temp[i]; //68 a0 68 94 06 90 01 01 02 20 02 cs 16  ������
	}
	for(i = 0;i<9+len;i++)
	{
		cs += Send[i];   //У��λ
	}
	Send[9+len] = cs;
	Send[10+len] = 0x16; //������
	
	LCD_Send_Data(Send,11+len);
	
}
void Write_or_Readresponse(uint8_t tmp,unsigned short len,unsigned char *array_temp)
{
	
	unsigned char cs_temp;
	unsigned short i;
	cs_temp = 0;
	LCD_Uart_prepare(tmp);      //��վ����Ӧ��֡
	Send[4] = 4 + len;      //�������ܳ���Ϊ���ݼ����ĸ���ʶλ
	
	for(i=0;i<len;i++)
	{
		Send[9+i] = array_temp[i];   //���ݲ���
	}
	
	for(i=0;i<(9+len);i++)   //У���봦��
	{
		cs_temp =  Send[i] + cs_temp;
	}
	Send[9+len]  = cs_temp;   
	Send[10+len] = 0x16;
	//HAL_UART_Transmit(&huart1,&Send[i],11+len,0xffff);
  LCD_Send_Data(Send,11+len);  //���Ͷ�����Ӧ������֡
}
//��վд���վ����ǰ©�����
void Write_or_Read_now_leak_cur(uint8_t tmp) 
{
	uint8_t array_temp[2];
//	DectoBCD(array_temp,Leak_Cur,2);  
	Write_or_Readresponse(tmp,2,array_temp);    //�������ݳ����ټ�������
}
//��վд���վ����ǰ����
void Write_or_Rread_now_energy(uint8_t tmp) 
{
	uint8_t array_temp[3];         
	DectoBCD(array_temp,10*HT7038_buf[18],3);  
	Write_or_Readresponse(tmp,3,array_temp);    //�������ݳ����ټ�������
}
//��վд���վ����ǰ���� 
uint8_t Write_or_Rread_now_power(uint8_t tmp,uint8_t type,uint8_t len)
{
//	uint8_t array_temp[len];
//	if(type == Data_Iden_Act_Power)
//	{
//		DectoBCD(array_temp,Energy_A,len);  //ʮ����ת���ɶ�����ת���ɵ�ѹֵ
//	}
//	else if(type == Data_Iden_Rea_Power)
//	{
//		
//	}
//	else if(type == Data_Iden_App_Power)
//	{
//		
//	}
//	else if(type == Data_Iden_All_Power)
//	{
//		DectoBCD(&array_temp[0],Act_Power,2);
//		
//	}
//	else 
//	{
//		//Err_State = ERRO_UNKOWN_ID;//����Ӧ��
//		return 1;
//	}
//	Write_or_Readresponse(tmp,len,array_temp);    //�������ݳ����ټ�������
//	return 0;
}
/*********************************************��վ����������������*******************************************/
void Read_Data_process(void)  
{

  DI3 = LCD_Receive_last[5];
	DI2 = LCD_Receive_last[6];
	DI1 = LCD_Receive_last[7];
	DI0 = LCD_Receive_last[8];
	

		if(DI3==0x02)//��ǰ����
		{
			delay_uart();
			if(DI2==0x01)
			{
			//	Read_variable_vol(DI1,2);//����ѹ����
			}
			else if(DI2==0x02)
			{
				//Read_variable_cur(DI1,3);//����������
			}
			else if(DI2==0x0C)
			{
				//Read_Frequency(DI1,2);//���ź�Ƶ��
			}
			else if(DI2==0x0D)
			{
				//Read_variable_leak(1);//��ʣ�����
			}
				else if(DI2==0x0E)
			{
				//Read_active_energy(DI1,4);//������
			}
				else if(DI2==0x0F)
			{
				//Read_Power(DI1,2);//�������ࣩ�й�����/�޹�����/���ڹ���/���й���
			}
			else
			{
				//ERR_data_sent(ERR_NO_REQUEST);
			}
		}
		else if(DI3==0x90)//��������
		{
			if(DI2==0x01)//����
			{
				Read_Overload(DI1,2);//�������������
			}
			else if(DI2==0x02)//����
			{
				Read_Duanyan(DI1,2);//�������������
			}
			else if(DI2==0x03)//˲��
			{
				Read_SD(DI1,2);
			}
			else if(DI2==0x04)//©��
			{
				Read_LD(DI1,2);
			}
			else if(DI2==0x05)//�غ�բ��ʱʱ��
			{
				Read_Chz_delaytime(DI1,2);
			}
		}
			else if(DI3==0x91)//��ѹ����
		{
			if(DI2==0x01)
			{
				Read_vol_over(DI1,2);//����ѹ����
			}
			else if(DI2==0x02)
			{
				Read_vol_under(DI1,2);//��Ƿѹ����
			}
			else if(DI2==0x03)
			{
				Read_phase_loss(DI1,2);//ȱ�ౣ��
			}
			else if(DI2==0x04)
			{
				Read_phase_Error(DI1,2);//���ౣ��
			}
			else if(DI2==0x05)
			{
				Read_phase_imblance(DI1,2);//�಻ƽ�Ᵽ��
			}
		}
		else if(DI3==0x93)//������¼
		{
			if(DI2==0x01)
			{
				Read_Protect_Record(DI1,2);//��������¼
			}
		}
		
}
void WorRrespond_process(void) //��վд����
{
//	uint8_t Data_Field_Len = LCD_Receive_last[4]; //�����򳤶�
	uint8_t Data_Len = LCD_Receive_last[8];       //���ݳ���
	uint8_t Data_Temp[LCD_Receive_last[8]];              //���ݻ�����
	  unsigned char array_tmp[3];	
	for(uint8_t i=0;i<Data_Len;i++)
	{
		Data_Temp[i]=LCD_Receive_last[i+9];
	}
	if(DI3 == 0x02)  //��ǰ����
	{
		if(DI2 == 0x01) //��ѹֵ
		{
			
			if(DI1 == 0x01) //A���ѹ
			{
			//	UA_display=BCDtoDec(Data_Temp,2);
			}
			else if(DI1 == 0x02) //B���ѹ
			{
				//UB_display=BCDtoDec(Data_Temp,2);
			}
			else if(DI1 == 0x04) //C���ѹ
			{
				//UC_display=BCDtoDec(Data_Temp,2);
			}
			else if(DI1 == 0xFF) //�����ѹ
			{
//				UA_display=BCDtoDec(&Data_Temp[0],2);
//				UB_display=BCDtoDec(&Data_Temp[2],2);
//				UC_display=BCDtoDec(&Data_Temp[4],2);
			}
		}
		else if(DI2 == 0x02)  //����ֵ
		{
			if(DI1 == 0x01) //A�����
			{
			//	IA_display=BCDtoDec(Data_Temp,2);
			}
			else if(DI1 == 0x02) //B�����
			{
			 // IB_display=BCDtoDec(Data_Temp,2);
			}
			else if(DI1 == 0x04) //C�����
			{
				//IC_display=BCDtoDec(Data_Temp,2);
			}
			else if(DI1 == 0xFF) //�������
			{
//				IA_display=BCDtoDec(&Data_Temp[0],2);
//				IB_display=BCDtoDec(&Data_Temp[2],2);
//				IC_display=BCDtoDec(&Data_Temp[4],2);
			}
		}
		else if(DI2 == 0x0C )  //Ƶ��
		{
		//	Voltage_frequency=BCDtoDec(&Data_Temp[0],2);
		}
		else if(DI2 == 0x0D )  //©�����
		{
			//Leak_Cur=BCDtoDec(&Data_Temp[0],2);
		}
		else if(DI2 == 0x0E )  //����
		{
			//Energy_A=BCDtoDec(&Data_Temp[0],3);
		}
		else if(DI2 == 0x0F )  //����
		{
			if(DI1 == 0x01) //�й�����
			{
			//	Act_Power=BCDtoDec(&Data_Temp[0],2);
			}
			else if(DI1 == 0x02) //�޹�����
			{
//				Rea_Power=BCDtoDec(&Data_Temp[0],2);
			}
			else if(DI1 == 0x04) //���ڹ���
			{
//				App_Power=BCDtoDec(&Data_Temp[0],2);
			}
			else if(DI1 == 0xFF) //���й���
			{
				
			}
		}
		else 
		{
		//	Err_State = ERRO_UNKOWN_ID;    // δ֪ID 
		  return ;
		}
	}
	else if(DI3 == 0x90)  //��������
	{
		if(DI2 == 0x01)   //���س���ʱ
		{
			if(DI1 == 0x01) //����ʱ����
			{
				//overload_cur_setting =BCDtoDec(Data_Temp,1);
			}
			else if(DI1 == 0x02) //����ʱʱ��
			{
				TH_Long_Cur = BCDtoDec(Data_Temp,2)-2;
			}
			else if(DI1 == 0x04) //����ʱ��������
			{
				F_trip_gl =Data_Temp[0];//�澯01���ر�00������02
			}
			else if(DI1 == 0xFF) //���в���
			{
				//overload_cur_setting =BCDtoDec(&Data_Temp[0],1);
				TH_Long_Cur =BCDtoDec(&Data_Temp[1],2)-2;
				F_trip_gl =BCDtoDec(&Data_Temp[3],1);
			}
	
		}
		else if(DI2 == 0x02)   //��·����ʱ
		{
			if(DI1 == 0x01) //����ʱ����
				{
				  D2_Cur = BCDtoDec(Data_Temp,2);
				}
			else if(DI1 == 0x02) //����ʱʱ��
				{
					TH_DL = BCDtoDec(Data_Temp,2)-0;
					if(TH_DL>200)      TH_DL=3; 
					else if(TH_DL==200) TH_DL=2;
					else if(TH_DL==100) TH_DL=1;
					else if(TH_DL==60) TH_DL=0;
				} 
			else if(DI1 == 0x04) //����ʱ��������
				{
					F_ip = Data_Temp[0];
				}
			else if(DI1 == 0xFF) //���в���
				{
					D2_Cur =BCDtoDec(&Data_Temp[0],2);
					TH_DL =BCDtoDec(&Data_Temp[2],2);
					if(TH_DL > 200)      TH_DL=3; 
					else if(TH_DL==200) TH_DL=2;
					else if(TH_DL==100) TH_DL=1;
					else if(TH_DL==60) TH_DL=0;
					F_ip =BCDtoDec(&Data_Temp[4],1);
				}
		}
		else if(DI2 == 0x03)   //��·˲ʱ
		{
			if(DI1 == 0x01) //��·˲ʱ����
				{
					D3_Cur = BCDtoDec(Data_Temp,2);
				}
			else if(DI1 == 0x02) //��·˲ʱ��������
				{
					F_ip_3 =Data_Temp[0];
           if(F_ip_3>=1) F_ip_3=1;
					
			 if(F_ip_3==1)	array_tmp[0] = 0x01 ;
        if(F_ip_3==0)	array_tmp[0] = 0x00;
        MODIFY_EEP_W(Addr_I_3d,array_tmp,1,0xA0);
				}
			else if(DI1 == 0xFF) //���в���
				{
				  D3_Cur =BCDtoDec(&Data_Temp[0],2);
					F_ip_3 =Data_Temp[2];
				}
		}
		else if(DI2 == 0x04)   //©�籣��
		  {
			if(DI1 == 0x01) //©�籣������
				{
					Leak_Value = BCDtoDec(Data_Temp,2);
					if(Leak_Value==1000)	D_LCur=7;
					else if(Leak_Value==800)	D_LCur=6;
					else if(Leak_Value==500)	D_LCur=5;
					else if(Leak_Value==300)	D_LCur=4;
					else if(Leak_Value==200)	D_LCur=3;
					else if(Leak_Value==100)	D_LCur=2;
					else if(Leak_Value==50)	D_LCur=1;
					
				
				}
			else if(DI1 == 0x02) //©�籣����ʱʱ��
				{
					TH_LCur = BCDtoDec(Data_Temp,2);
				}
			else if(DI1 == 0x04) //�ʣ�಻��������
			  {
				  //leak_notact_cur_setting = BCDtoDec(Data_Temp,1);
			  }
			else if(DI1 == 0x08) //©�籣������
				{
					F_trip_ld = BCDtoDec(Data_Temp,1);
				}
			else if(DI1 == 0xFF) //���в���
				{
					Leak_Value = BCDtoDec(&Data_Temp[0],2);
					if(Leak_Value==1000)	D_LCur=7;
					else if(Leak_Value==800)	D_LCur=6;
					else if(Leak_Value==500)	D_LCur=5;
					else if(Leak_Value==300)	D_LCur=4;
					else if(Leak_Value==200)	D_LCur=3;
					else if(Leak_Value==100)	D_LCur=2;
					else if(Leak_Value==50)	D_LCur=1;
					TH_LCur = BCDtoDec(&Data_Temp[2],2);
//					leak_notact_cur_setting = BCDtoDec(&Data_Temp[4],1);
					F_trip_ld =BCDtoDec(&Data_Temp[5],1);
				}
		  }
			else if(DI2 == 0x06)
			{
				if(DI1 == 0x01) //�Ǽܵ���
				{
					kejia = BCDtoDec(Data_Temp,2);
					if(kejia==250) Type_Cur=1;
					else if(kejia==400)Type_Cur=2;
					else if(kejia==630)Type_Cur=3;
					else if(kejia==800)Type_Cur=4;
					array_tmp[0]=Type_Cur;
		      Cur_Switch(Type_Cur);
	     	  MODIFY_EEP_W(Addr_Type_Cur,array_tmp,1,0xA0);
					
				}
			   else if(DI1 == 0x02) //�������λ
				{
					Delta_Cur = BCDtoDec(Data_Temp,2);//�����Ƿ���D_Cur����delta�������ֽ�ֱ�Ӵ�Delta_Cur��ֵ
					Cur_uart_change(Delta_Cur);//delta_Curת����D_Cur
					MODIFY_EEP_W(Addr_Delta_Cur,array_tmp,2,0xA0);
				}
				else if(DI1 == 0xFF)
				{
						kejia = BCDtoDec(&Data_Temp[0],2);
					  if(kejia==250) Type_Cur=1;
						else if(kejia==400)Type_Cur=2;
						else if(kejia==630)Type_Cur=3;
						else if(kejia==800)Type_Cur=4;
						array_tmp[0]=Type_Cur;
						MODIFY_EEP_W(Addr_Type_Cur,array_tmp,1,0xA0);
					  Delta_Cur = BCDtoDec(&Data_Temp[2],2);
					  Cur_uart_change(Delta_Cur);//delta_Curת����D_Cur
					
				}
			}
		}
	else if(DI3 == 0x91)  //��չ���� 
		{
			if(DI2 == 0x01)   //��ѹ����
				{
				if(DI1 == 0x01) //��ѹ������ѹ
					{
						Over_Vol_Value = BCDtoDec(Data_Temp,2);
								if(Over_Vol_Value>=295)      Vol_g = 5;
								else if(Over_Vol_Value>=285) Vol_g = 4;
								else if (Over_Vol_Value>=275) Vol_g = 3;
								else if (Over_Vol_Value>=265) Vol_g = 2;
								else if (Over_Vol_Value>=255) Vol_g = 1;
								else if (Over_Vol_Value>=245) Vol_g = 0;
								else Vol_g = 0;
					}
				else if(DI1 == 0x02) //��ѹ�غ�բ��ѹ
					{
						//Up_VolA_reclose_linmit  =BCDtoDec(Data_Temp,2);
					}
				else if(DI1 == 0x04) //��ѹ������ʱʱ��
					{
						Over_Vol_Time = BCDtoDec(Data_Temp,1);
						D_GY_yanshi=Over_Vol_Time-1;
					}
				else if(DI1 == 0x08) //��ѹ��������
					{
						F_trip_gy =BCDtoDec(Data_Temp,1);
					}
				else if(DI1 == 0xFF) //���в���
					{
						Over_Vol_Value  =BCDtoDec(&Data_Temp[0],2);
										if(Over_Vol_Value>=295)      Vol_g = 5;
	  else if(Over_Vol_Value>=285) Vol_g = 4;
		else if (Over_Vol_Value>=275) Vol_g = 3;
		else if (Over_Vol_Value>=265) Vol_g = 2;
		else if (Over_Vol_Value>=255) Vol_g = 1;
		else if (Over_Vol_Value>=245) Vol_g = 0;
		else                    Vol_g = 0;
					//	Up_VolA_reclose_linmit  =BCDtoDec(&Data_Temp[2],2);
						Over_Vol_Time  =BCDtoDec(&Data_Temp[4],1);
						D_GY_yanshi=Over_Vol_Time-1;
						F_trip_gy =BCDtoDec(&Data_Temp[5],1);
					}
			 }
			else if(DI2 == 0x02)   //Ƿѹ����
			{
				if(DI1 == 0x01) //Ƿѹ������ѹ
					{
						Under_Vol_Value  =BCDtoDec(Data_Temp,2);
						if(Under_Vol_Value<=144) Vol_q = 0;
						else if (Under_Vol_Value<=154) Vol_q = 1;
						else if (Under_Vol_Value<=164) Vol_q = 2;
						else if (Under_Vol_Value<=174) Vol_q = 3;
						else if (Under_Vol_Value<=184) Vol_q = 4;
						else                    Vol_q = 4; 
					}
				else if(DI1 == 0x02) //Ƿѹ�غ�բʱ��
					{
						//Under_Vol_Time  =BCDtoDec(Data_Temp,2);
					}
				else if(DI1 == 0x04) //Ƿѹ������ʱʱ��
					{
						Under_Vol_Time  =BCDtoDec(Data_Temp,1);
						D_GY_yanshi=Under_Vol_Time-1;
					}
				else if(DI1 == 0x08) //Ƿѹ��������
					{
						F_trip_qy =BCDtoDec(Data_Temp,1);
					}
				else if(DI1 == 0xFF) //���в���
					{
						Under_Vol_Value  =BCDtoDec(&Data_Temp[0],2);
							if(Under_Vol_Value<=144) Vol_q = 0;
						else if (Under_Vol_Value<=154) Vol_q = 1;
						else if (Under_Vol_Value<=164) Vol_q = 2;
						else if (Under_Vol_Value<=174) Vol_q = 3;
						else if (Under_Vol_Value<=184) Vol_q = 4;
						else                    Vol_q = 4; 
//						Down_VolA_reclose_linmit  =BCDtoDec(&Data_Temp[2],2);
						Under_Vol_Time  =BCDtoDec(&Data_Temp[4],1);
						D_GY_yanshi=Under_Vol_Time-1;
						F_trip_qy =BCDtoDec(&Data_Temp[5],1);
					}
			 }
			else if(DI2 == 0x03)   //ȱ�ౣ��
			{
				if(DI1 == 0x01) //ȱ�ౣ����ѹ
					{
						lossphase_vol_setting = BCDtoDec(Data_Temp,1);
					}
				else if(DI1 == 0x02)
				{
				    	lossphase_time_setting = BCDtoDec(Data_Temp,2);
				}
				else if(DI1 == 0x04) //ȱ�ౣ������
					{
						  F_trip_QX =BCDtoDec(Data_Temp,1);
					}
				else if(DI1 == 0xFF) //���в���
					{
						lossphase_vol_setting  =BCDtoDec(&Data_Temp[0],1);
						lossphase_time_setting = BCDtoDec(&Data_Temp[1],2);
						F_trip_QX =BCDtoDec(&Data_Temp[3],1); 
					}
			 }
			else if(DI2 == 0x04)   //���ౣ��
				{
					if(DI1 == 0x01) //���ౣ����ѹ
					{
						//misphase_vol_setting  =BCDtoDec(Data_Temp,2);
					}
				else if(DI1 == 0x02) //���ౣ��ʱ��
					{
						//misphase_time_setting  =BCDtoDec(Data_Temp,2);
					}
				else if(DI1 == 0x04) //���ౣ������
					{
						//misphase_pro_index =BCDtoDec(Data_Temp,1);
					}
				else if(DI1 == 0xFF) //���в���
					{
//						misphase_vol_setting  =BCDtoDec(&Data_Temp[0],2);
//						misphase_time_setting  =BCDtoDec(&Data_Temp[2],2);
//						misphase_pro_index =BCDtoDec(&Data_Temp[4],1);
					}
			 }
			else if(DI2 == 0x05)   //�಻ƽ�Ᵽ�� 
			{
				if(DI1 == 0x01) //�಻ƽ�Ᵽ����ѹ
				{
				//	unbalance_vol_setting =BCDtoDec(Data_Temp,1);
				}
				else if(DI1 == 0x02) //�಻ƽ�Ᵽ��ʱ��
				{
					//unbalance_time_setting=BCDtoDec(Data_Temp,2);
				}
				else if(DI1 == 0x04) //�಻ƽ�Ᵽ������
				{
				//	unbalance_pro_index =BCDtoDec(Data_Temp,1);
				}
				else if(DI1 == 0xFF) //���в���
				{
				//	unbalance_vol_setting  =BCDtoDec(&Data_Temp[0],1);
					//unbalance_time_setting  =BCDtoDec(&Data_Temp[1],2);
				//	unbalance_pro_index =BCDtoDec(&Data_Temp[3],1);
				}
			}
		}
	else if(DI3 == 0X94)  //�ֺ�բ����
	{
		if((Data_Temp[0] & 0x80) == 0x80)//��բ
		{
			if(isfenzha==1)//ֻ�ڷ�բ״̬�������ã�����û�ڸ������úͲ�ѯҳ��
				{
					F_fz=0 ;
					F_hz=1 ;
				}
		}
		else if((Data_Temp[0] & 0x80) == 0x00)//��բ
		{
			if(isfenzha==0)
				{
					F_fz=1 ;
					F_hz=0 ;
				}
		}		
	}
	else if(DI3 == 0X95)  //��������
	{
		if(DI2 == 0X00)  //��ǰʱ�������
		{
			if(DI1 == 0X00)  //ʱ��
			{
				
			}
			else if(DI1 == 0x01)
			{
				
			}
		}
	}
	else 
	{
		//Err_State = ERRO_UNKOWN_ID;
		return;
	}
	//Err_State = OK;
	Write_response(0);
	return;
}

	void Write_response(uint8_t tmp)
{
	uint8_t cs = 0x00;
	Send[0] = 0x68;
	Send[1] = 0xA0;
	Send[2] = 0x68;
	if(tmp == 0) //����Ӧ��
	{
		Send[3] = 0xD4;//��վ������Ӧд����
		Send[4] = 0x00;
		for(uint8_t i=0;i<4;i++)
		{
		  cs += Send[i]; //У�������
		}
		Send[5] = cs;
		Send[6] = 0x16;
		LCD_Send_Data(Send,7);
  }
	else 
	{
		Send[3] = 0xF4;//��վ�쳣��Ӧд����
		Send[4] = 0x01;
		Send[5] = Err_State;
		for(uint8_t i=0;i<5;i++)
		{
		 cs += Send[i]; //У�������
		}
		Send[6] = cs;
		Send[7] = 0x16;
		LCD_Send_Data(Send,8);
	}
}
// ��BCD��ת��Ϊʮ������
int bcdToDecimal(unsigned char bcd[], int length) {
    int decimal = 0;
    for (int i = 0; i < length; i++) {
        decimal = decimal * 10 + (bcd[i] >> 4) * 10 + (bcd[i] & 0x0F);
    }
    return decimal;
}

u8 array_tmp_global[100]={0};

void USART_LCD_Transmit(unsigned short len,unsigned char ch)  //����ͨ����0Ϊʵʱ����1��1Ϊ��λ��Ϣ��2Ϊʵʱ����2��3ΪУ׼��Ӧ,4Ϊ�ֺ�բָ�� , 5Ϊ�� 6Ϊг������1�� 7Ϊг������2��8Ϊг������3��9Ϊг������4��10Ϊг������5��11Ϊг������6��12Ϊʵʱ����3��
{
	
	static u8 cnt=0;
	cnt++;
	unsigned char i,cs_temp,array_tmp[len];
	unsigned int array_tmp_32[60]={0};
	unsigned char array_tmp_1[len];
	switch (ch)
  {
  	case 0:
	  DI3 = 0x02;DI2 = 0x10;DI0 = 0x58;
    HexToChar(&array_tmp[0],(10*HT7038_buf[1])/10,2);//UA 
		HexToChar(&array_tmp[2],(10*HT7038_buf[2])/10,2);//UB
		HexToChar(&array_tmp[4],(10*HT7038_buf[3])/10,2); //UC
		HexToChar(&array_tmp[6],(HT7038_buf[4]/10),2);//IA
		HexToChar(&array_tmp[8],(HT7038_buf[5])/10,2);//IB
		HexToChar(&array_tmp[10],(HT7038_buf[6])/10,2); //IC
		HexToChar(&array_tmp[12],(Leak_Cur_disp),2);//©�����
    HexToChar(&array_tmp[14],(HT7038_buf[15]),3);//����
		HexToChar(&array_tmp[17],(HT7038_buf[16]),3);//����
		HexToChar(&array_tmp[20],(HT7038_buf[17]),3);//����
    HexToChar(&array_tmp[23],(HT7038_buf[18]),3);//����
		HexToChar(&array_tmp[26],(HT7038_buf[7]/10),2);//�й�����
		HexToChar(&array_tmp[28],(HT7038_buf[8]/10),2);//�й�����
		HexToChar(&array_tmp[30],(HT7038_buf[9]/10),2);//�й�����
    HexToChar(&array_tmp[32],(HT7038_buf[10]/10),2);//�й�����
		HexToChar(&array_tmp[34],(HT7038_buf[11]),2);//��������
		HexToChar(&array_tmp[36],(HT7038_buf[12]),2);//��������
		HexToChar(&array_tmp[38],(HT7038_buf[13]),2);//��������
    HexToChar(&array_tmp[40],(HT7038_buf[14]),2);//��������

//		HexToChar(&array_tmp[0],cnt,2);//UA 
//		HexToChar(&array_tmp[2],240,2);//UB
//		HexToChar(&array_tmp[4],(10*HT7038_buf[3]),2); //UC
//		HexToChar(&array_tmp[6],10,2);//IA
//		HexToChar(&array_tmp[8],20,2);//IB
//		HexToChar(&array_tmp[10],30,2); //IC
//		
//		HexToChar(&array_tmp[12],(1250),2);//©�����
//		
//		HexToChar(&array_tmp[14],0xaaaa,3);//����
//		
//		HexToChar(&array_tmp[17],0xaaaa,3);//����
//		
//		HexToChar(&array_tmp[20],0xaaaa,3);//����
//		
//    HexToChar(&array_tmp[23],0xaaaa,3);//����

//		HexToChar(&array_tmp[26],2200,2);//�й�����	
//		HexToChar(&array_tmp[28],2200,2);//�й�����	
//		HexToChar(&array_tmp[30],2200,2);//�й�����	
//    HexToChar(&array_tmp[32],2200,2);//�й�����	
//		HexToChar(&array_tmp[34],1,2);//��������	
//		HexToChar(&array_tmp[36],1,2);//��������	
//		HexToChar(&array_tmp[38],1,2);//��������	
//    HexToChar(&array_tmp[40],1,2);//��������
		HexToChar(&array_tmp[42],20,2);//�����¶�1
		HexToChar(&array_tmp[44],20,2);//�����¶�2
		HexToChar(&array_tmp[46],20,2);//�����¶�3
    HexToChar(&array_tmp[48],20,2);//�����¶�4
		HexToChar(&array_tmp[50],26,2);//�����¶�1
		HexToChar(&array_tmp[52],26,2);//�����¶�2
		HexToChar(&array_tmp[54],26,2);//�����¶�3
    HexToChar(&array_tmp[56],26,2);//�����¶�4
		HexToChar(&array_tmp[58],Num_tripall,2);//����բ����
		HexToChar(&array_tmp[60],Num_clearall,2);//�����������
		HexToChar(&array_tmp[62],Num_triplock,2);//������բ����
		HexToChar(&array_tmp[64],Num_tripleak,2);//©����բ����
		HexToChar(&array_tmp[66],Num_tripcur,2);//������բ����
		HexToChar(&array_tmp[68],Num_tripvol,2);//��ѹ��բ����
		HexToChar(&array_tmp[70],Num_triphand,2);//�ֶ�������բ����	
		HexToChar(&array_tmp[72],Num_triptest,2);//������բ����
		HexToChar(&array_tmp[74],Num_tripdelay,2);//������բ����
		HexToChar(&array_tmp[76],Num_tripinstant,2);//��˲��բ����
		HexToChar(&array_tmp[78],Num_leakover,2);//Ƿѹ��բ����
		HexToChar(&array_tmp[80],Num_leakprotect,2);//ȱ����բ����
		
	  Write_or_Readresponse(0x10,len,array_tmp); 
		break;
		
	case 1:
		RTC_Readtime();	
	
		DI3 = 0x90;DI2 = 0x01;DI0 = 0x41;
		array_tmp[0]=ctrlword[3];
		array_tmp[1]=Vol_g;
		array_tmp[2]=Vol_q;
		array_tmp[3]=D_SY_yanshi ;
		array_tmp[4]=D_GY_yanshi ;
		array_tmp[5] = D_QY_yanshi ;
		array_tmp[6] = D3_Cur;
		array_tmp[7] = D_Cur;
		array_tmp[8] =TH_Long_Cur  ;
		array_tmp[9] = D2_Cur;
		array_tmp[10] = TH_DL;
		array_tmp[11] = ( baud>> 8) & 0xFF;
		array_tmp[12] = baud  & 0xFF;
		array_tmp[13] = ( Type_Cur>> 8) & 0xFF;
		array_tmp[14] = Type_Cur   & 0xFF;
		array_tmp[15] = ( tim_y3>> 8) & 0xFF;
		array_tmp[16] = tim_y3  & 0xFF;
		array_tmp[17] = ( tim_m3>> 8) & 0xFF;
		array_tmp[18] = tim_m3  & 0xFF;
		array_tmp[19] =  ( tim_d3>> 8) & 0xFF;
		array_tmp[20] =  tim_d3  & 0xFF;
		array_tmp[21] =  ( tim_h3>> 8) & 0xFF;
		array_tmp[22] =  tim_h3  & 0xFF;
		array_tmp[23] =  ( tim_f3>> 8) & 0xFF;
		array_tmp[24] =  tim_f3  & 0xFF;
		array_tmp[25] =  ( tim_s3>> 8) & 0xFF;
		array_tmp[26] =  tim_s3  & 0xFF;
		array_tmp[27] = ( TH_TEM_UP >> 8) & 0xFF;
		array_tmp[28] = TH_TEM_UP  & 0xFF;
		array_tmp[29] = ( TH_TEM_DOWN>> 8) & 0xFF;
		array_tmp[30] = TH_TEM_DOWN  & 0xFF;
		array_tmp[31] = mima_set[0];
		array_tmp[32] = mima_set[1];
		array_tmp[33] = mima_set[2];
		array_tmp[34] = mima_set[3];
		array_tmp[35] = self_addr_code[0];
		array_tmp[36] = self_addr_code[1];
		array_tmp[37] = self_addr_code[2];
		array_tmp[38] = self_addr_code[3];
		array_tmp[39] = self_addr_code[4];
		array_tmp[40] = self_addr_code[5];
		array_tmp[41] = ctrlword[0];
		array_tmp[42] =  ctrlword[1];
		array_tmp[43] =  ctrlword[2];
		array_tmp[44] = F_TB_trip;
		array_tmp[45] = F_Special_wave;
		array_tmp[46] = F_ip;
		array_tmp[47] = F_ip_3;
		array_tmp[48] = jiaozhun;
		array_tmp[49] = shangdian;
		array_tmp[50] = LD_hezha;
		array_tmp[51] = DY_hezha;
		array_tmp[52] = DL_hezha;
		array_tmp[53] = wendu;
		array_tmp[54] = F_TX;
		array_tmp[55] = TH_LCur;
		array_tmp[56] = F_trip_sy;

		

		Write_or_Readresponse(0x10,len,array_tmp); 
		break;
	case 2:
		DI3 = 0x03;DI2 = 0x10;DI0 = 0x10;
		array_tmp[0]=isfenzha;
		array_tmp[1]=F_disp_jg;
		array_tmp[2]=F_disp_tr;
		array_tmp[3]=F_hezha_state ;
		array_tmp[4]=F_fenzha_state ;
		array_tmp[5] = F_gz_disp ;
		array_tmp[6] = (gz_disp&0xff00)>>8;
		array_tmp[7] = gz_disp&0x00ff;
		array_tmp[8] =(F_ch &0xff00)>>8 ;
		array_tmp[9] = F_ch&0x00ff;

//		array_tmp[0]=isfenzha;
//		array_tmp[1]=F_disp_jg;
//		array_tmp[2]=F_disp_tr;
//		array_tmp[3]=0 ;
//		array_tmp[4]=0 ;
//		array_tmp[5] = F_gz_disp ;
//		array_tmp[6] = 140&0xff00;
//		array_tmp[7] = 140&0x00ff;
//		array_tmp[8] =134 &0xff00 ;
//		array_tmp[9] = 134&0x00ff;
		Write_or_Readresponse(0x10,len,array_tmp); 
		break;
	case 3:
		DI3 = 0x04;DI2 = 0x10;DI0 = 0x10;
		array_tmp[0]=1;
		Write_or_Readresponse(0x10,len,array_tmp); 
		break;
	case 4:
		DI3 = 0x03;DI2 = 0x10;DI0 = 0x10;
//		array_tmp[0]=isfenzha;
//		array_tmp[1]=F_disp_jg;
//		array_tmp[2]=F_disp_tr;
//		array_tmp[3]=F_hezha_state ;
//		array_tmp[4]=F_fenzha_state ;
//		array_tmp[5] = F_gz_disp ;
//		array_tmp[6] = gz_disp&0xff00;
//		array_tmp[7] = gz_disp&0x00ff;
//		array_tmp[8] =F_ch &0xff00 ;
//		array_tmp[9] = F_ch&0x00ff;

		array_tmp[0]=isfenzha;
		Write_or_Readresponse(0x10,len,array_tmp); 
		break;  
	case 5:      //��ʼ�����
		DI3 = 0x06;DI2 = 0x10;DI0 = 0x10;
		array_tmp[0]=1;
		Write_or_Readresponse(0x10,len,array_tmp); 
		break;

	
	case 6:  //г������,UA��
		DI3 = 0x08;DI2 = 0x10;DI0 = 0x10;
	
		Xiebo(0);  //UA
		Harmonic_Content_Calculate(0);
	  for(int i=0;i<30;i++)
		{
			array_tmp_32[i] = (unsigned int)(10*Content_Hwave[2+i]);
		}
		

		for(int i=0;i<30;i++)
		{
			array_tmp[2*i]=(array_tmp_32[i]&0xff00)>>8;
			array_tmp[2*i+1]=(array_tmp_32[i]&0xff);
		}
		
		Write_or_Readresponse(0x10,len,array_tmp); 
		break;
		
	case 7:
		DI3 = 0x09;DI2 = 0x10;DI0 = 0x10;
		Xiebo(1);  //UB
		Harmonic_Content_Calculate(1);
		for(int i=0;i<30;i++)
		{
			array_tmp_32[i] = (unsigned int)(10*Content_Hwave[2+i]);
		}
		
		for(int i=0;i<30;i++)
		{
			array_tmp[2*i]=(array_tmp_32[i]&0xff00)>>8;
			array_tmp[2*i+1]=(array_tmp_32[i]&0xff);
		}
		
		Write_or_Readresponse(0x10,len,array_tmp); 
		break;
		
	case 8:
		DI3 = 0x0A;DI2 = 0x10;DI0 = 0x10;
		Xiebo(2);  //UC
		Harmonic_Content_Calculate(2);
	  for(int i=0;i<30;i++)
		{
			array_tmp_32[i] =(unsigned int)(10*Content_Hwave[2+i]);
		}
		
		for(int i=0;i<30;i++)
		{
			array_tmp[2*i]=(array_tmp_32[i]&0xff00)>>8;
			array_tmp[2*i+1]=(array_tmp_32[i]&0xff);
		}
		
		Write_or_Readresponse(0x10,len,array_tmp); 
		break;
		
	case 9:
		DI3 = 0x0B;DI2 = 0x10;DI0 = 0x10;
		Xiebo(3);  //IA
		Harmonic_Content_Calculate(3);
	  for(int i=0;i<30;i++)
		{
			array_tmp_32[i] = (unsigned int)(10*Content_Hwave[2+i]);
		}
		
		for(int i=0;i<30;i++)
		{
			array_tmp[2*i]=(array_tmp_32[i]&0xff00)>>8;
			array_tmp[2*i+1]=(array_tmp_32[i]&0xff);
		}
		
		Write_or_Readresponse(0x10,len,array_tmp); 
		break;
		
	case 10:
		DI3 = 0x0C;DI2 = 0x10;DI0 = 0x10;
		Xiebo(4);  //IB
		Harmonic_Content_Calculate(4);
	  for(int i=0;i<30;i++)
		{
			array_tmp_32[i] = (unsigned int)(10*Content_Hwave[2+i]);
		}
		
		for(int i=0;i<30;i++)
		{
			array_tmp[2*i]=(array_tmp_32[i]&0xff00)>>8;
			array_tmp[2*i+1]=(array_tmp_32[i]&0xff);
		}
		
		Write_or_Readresponse(0x10,len,array_tmp); 
		break;
		
	case 11:
		DI3 = 0x0D;DI2 = 0x10;DI0 = 0x10;
		Xiebo(5);  //IC	
		Harmonic_Content_Calculate(5);
	  for(int i=0;i<30;i++)
		{
			array_tmp_32[i] = (unsigned int)(10*Content_Hwave[2+i]);
		}
		
		for(int i=0;i<30;i++)
		{
			array_tmp[2*i]=(array_tmp_32[i]&0xff00)>>8;
			array_tmp[2*i+1]=(array_tmp_32[i]&0xff);
		}
		for(int i=0;i<6;i++)
		{
			array_tmp[2*i+60]=(((unsigned int)(100*THD[i]))&0xff00)>>8;  //������г����������ʱ��0
			array_tmp[2*i+1+60]=((unsigned int)(100*THD[i]))&0xff; 
		}
		
		Write_or_Readresponse(0x10,len,array_tmp); 
		break;
		
	case 12:
		DI3 = 0x07;DI2 = 0x10;DI0 = 0x10;
		array_tmp[0] = ((HT7038_buf[22] / 10) & 0xff00) >> 8; // ���޹�����
		array_tmp[1] = (HT7038_buf[22] / 10) & 0xff;
		array_tmp[2] = ((HT7038_buf[19] / 10) & 0xff00) >> 8; // A�޹�����
		array_tmp[3] = (HT7038_buf[19] / 10) & 0xff;
		array_tmp[4] = ((HT7038_buf[20] / 10) & 0xff00) >> 8; // B�޹�����
		array_tmp[5] = (HT7038_buf[20] / 10) & 0xff;
		array_tmp[6] = ((HT7038_buf[21] / 10) & 0xff00) >> 8; // C�޹�����
		array_tmp[7] = (HT7038_buf[21] / 10) & 0xff;

		array_tmp[8] = ((HT7038_buf[26] / 10) & 0xff00) >> 8; // �����ڹ���
		array_tmp[9] = (HT7038_buf[26] / 10) & 0xff;
		array_tmp[10] = ((HT7038_buf[23] / 10) & 0xff00) >> 8; // A���ڹ���
		array_tmp[11] = (HT7038_buf[23] / 10) & 0xff;
		array_tmp[12] = ((HT7038_buf[24] / 10) & 0xff00) >> 8; // B���ڹ���
		array_tmp[13] = (HT7038_buf[24] / 10) & 0xff;
		array_tmp[14] = ((HT7038_buf[25] / 10) & 0xff00) >> 8; // C���ڹ���
		array_tmp[15] = (HT7038_buf[25] / 10) & 0xff;

		array_tmp[16] = ((HT7038_buf[30] / 10) & 0xff00) >> 8; // ���޹�����
		array_tmp[17] = (HT7038_buf[30] / 10) & 0xff;
		array_tmp[18] = ((HT7038_buf[27] / 10) & 0xff00) >> 8; // A�޹�����
		array_tmp[19] = (HT7038_buf[27] / 10) & 0xff;
		array_tmp[20] = ((HT7038_buf[28] / 10) & 0xff00) >> 8; // B�޹�����
		array_tmp[21] = (HT7038_buf[28] / 10) & 0xff;
		array_tmp[22] = ((HT7038_buf[29] / 10) & 0xff00) >> 8; // C�޹�����
		array_tmp[23] = (HT7038_buf[29] / 10) & 0xff;
		
		array_tmp[24] = ((P1/10)&0xff00)>>8; //���й�����
		array_tmp[25] = ((P1/10)&0xff);
		array_tmp[26] = ((P1/10)&0xff00)>>8; //A�й�����
		array_tmp[27] = ((P1/10)&0xff);
		array_tmp[28] = ((P1/10)&0xff00)>>8; //B�й�����
		array_tmp[29] = ((P1/10)&0xff);
		array_tmp[30] = ((P1/10)&0xff00)>>8; //C�й�����
		array_tmp[31] = ((P1/10)&0xff);
		
		array_tmp[32] = ((P1_Reactive/10)&0xff00)>>8; //���޹�����
		array_tmp[33] = ((P1_Reactive/10)&0xff);
		array_tmp[34] = ((P1_Reactive/10)&0xff00)>>8; //A�޹�����
		array_tmp[35] = ((P1_Reactive/10)&0xff);
		array_tmp[36] = ((P1_Reactive/10)&0xff00)>>8; //B�޹�����
		array_tmp[37] = ((P1_Reactive/10)&0xff);
		array_tmp[38] = ((P1_Reactive/10)&0xff00)>>8; //C�޹�����
		array_tmp[39] = ((P1_Reactive/10)&0xff);
		
		array_tmp[40] = ((P1_Apparent/10)&0xff00)>>8; //����������
		array_tmp[41] = ((P1_Apparent/10)&0xff);
		array_tmp[42] = ((P1_Apparent/10)&0xff00)>>8; //A��������
		array_tmp[43] = ((P1_Apparent/10)&0xff);
		array_tmp[44] = ((P1_Apparent/10)&0xff00)>>8; //B��������
		array_tmp[45] = ((P1_Apparent/10)&0xff);
		array_tmp[46] = ((P1_Apparent/10)&0xff00)>>8; //C��������
		array_tmp[47] = ((P1_Apparent/10)&0xff);
		
		array_tmp[48] = (HT7038_buf[31]+3)/10;  //Ƶ��
	  
		array_tmp[49] = ((unsigned int)(1000*Unbal_Vol)&0xff00)>>8;  //��ѹ��ƽ���
		array_tmp[50] = ((unsigned int)(1000*Unbal_Vol)&0xff);
		array_tmp[51] = ((unsigned int)(1000*Unbal_Cur)&0xff00)>>8;  //������ƽ���
		array_tmp[52] = ((unsigned int)(1000*Unbal_Cur)&0xff);	
//		array_tmp[48] = 50;  //Ƶ��
//		array_tmp[49] = 1;  //��ѹ��ƽ���
//		array_tmp[50] = 2;
//		array_tmp[51] = 1;  //������ƽ���
//		array_tmp[52] = 2;	
		
		array_tmp[53] = quadrant;  //����������ָʾ
		array_tmp[54] = (((unsigned int)(Charge_sum))&0xff0000)>>16; //��ʱ����
		array_tmp[55] = (((unsigned int)(Charge_sum))&0xff00)>>8; //��ʱ����
		array_tmp[56] = (((unsigned int)(Charge_sum))&0xff); //��ʱ����
		
		Write_or_Readresponse(0x10,len,array_tmp); 
		break;
case 13:  //������Ϣǰ10��
    DI3 = 0x0E; DI2 = 0x10; DI0 = 0x10;

    for (int i = 0; i < 10; i++) {
        Get_record(i);

        for (int j = 0; j < 9; j++) {
            array_tmp_global[i * 9 + j] = record_array[j];

        }
    }

    for (int i = 0; i < 10; i++) {
        array_tmp_global[1 + i * 9] = BCDtoDec(&array_tmp_global[1 + i * 9], 1);
        array_tmp_global[2 + i * 9] = BCDtoDec(&array_tmp_global[2 + i * 9], 1);
        array_tmp_global[3 + i * 9] = BCDtoDec(&array_tmp_global[3 + i * 9], 1);
        array_tmp_global[4 + i * 9] = BCDtoDec(&array_tmp_global[4 + i * 9], 1);
        array_tmp_global[5 + i * 9] = BCDtoDec(&array_tmp_global[5 + i * 9], 1);
        array_tmp_global[6 + i * 9] = BCDtoDec(&array_tmp_global[6 + i * 9], 1);
        unsigned int a = BCDtoDec(&array_tmp_global[7 + i * 9], 2);
        array_tmp_global[7 + i * 9] = (a >> 8) & 0xff;
        array_tmp_global[8 + i * 9] = a & 0xff;
    }
    Write_or_Readresponse(0x10, len, array_tmp_global);
    break;

case 14:  //������Ϣ��10��
    DI3 = 0x0F; DI2 = 0x10; DI0 = 0x10;
    for (int i = 10; i < 20; i++) {
        Get_record(i);

        for (int j = 0; j < 9; j++) {
            array_tmp_global[(i - 10) * 9 + j] = record_array[j];
        }
    }
    for (int i = 0; i < 10; i++) {
        array_tmp_global[1 + i * 9] = BCDtoDec(&array_tmp_global[1 + i * 9], 1);
        array_tmp_global[2 + i * 9] = BCDtoDec(&array_tmp_global[2 + i * 9], 1);
        array_tmp_global[3 + i * 9] = BCDtoDec(&array_tmp_global[3 + i * 9], 1);
        array_tmp_global[4 + i * 9] = BCDtoDec(&array_tmp_global[4 + i * 9], 1);
        array_tmp_global[5 + i * 9] = BCDtoDec(&array_tmp_global[5 + i * 9], 1);
        array_tmp_global[6 + i * 9] = BCDtoDec(&array_tmp_global[6 + i * 9], 1);
        unsigned int a = BCDtoDec(&array_tmp_global[7 + i * 9], 2);
        array_tmp_global[7 + i * 9] = (a >> 8) & 0xff;
        array_tmp_global[8 + i * 9] = a & 0xff;
    }
    Write_or_Readresponse(0x10, len, array_tmp_global);
    break;


	default:
		break;

}
}
//���ͷֺ�բ��Ϣ����
//0:��բ 1����բ
void Write_Trip_Data2LCD(void)
{
  ID_array[0]=0x94;
	ID_array[1]=0x01; 
	ID_array[2]=0x00; 
	ID_array[3]=0x01;
	
	if(isfenzha == 1)
	{
		Work_State &=  0x7F;  //����״̬λ�ڰ�λ��0
		send_array_temp[0] = Work_State;
		Send_Data2LCD_process(ID_array,send_array_temp,1);
	}
	else
	{
		Work_State |=  0x80;   //����״̬λ�ڰ�λ��1
		send_array_temp[0] = Work_State; 
		Send_Data2LCD_process(ID_array,send_array_temp,1);
	}
	
}
/*****************���������ı�����Ϣ������*****************/
void Warn_process()
{
	return;
}
/*****************��վ�����ѯ����������*****************/
void Protect_process()
{
	return;
}

//void USART1_IRQHandler(void)
//{
//  /* USER CODE BEGIN USART3_4_IRQn 0 */

//  /* USER CODE END USART3_4_IRQn 0 */

//	
//	 uint8_t i = 0;
//	 u8 tmp; //= Lcd_uart_rx[0];		
//	if(__HAL_UART_GET_FLAG(&huart1,UART_FLAG_RXNE)!=RESET) 
//   { 
//	 HAL_UART_IRQHandler(&huart1);  
//		 tmp = Lcd_uart_rx[0];
//   HAL_UART_Receive_IT(&huart1,(uint8_t*)Lcd_uart_rx,1);   
//	 if(Receive_Flag==0)  // �޿�ʼ��־���ȴ�֡ͷ
//		 {
//					if(tmp!=0x68) 
//					{
//						HAL_UART_Receive_IT(&huart1,(uint8_t*)Lcd_uart_rx,1);  
//						return;//����֡ͷ��δ�ý��ձ�־�򲻽��� 
//					}
//					if(tmp==0x68)		  //֡ͷ���޿�ʼ��־����ʼ���ղ��ñ�־
//					{
//								for(i=0; i<20; i++)
//								{
//									LCD_Receive[i] = 0;  
//								}
//						
//								LCD_Receive[Receive_index] = 0x68; 
//										Receive_index = 1;
//								Receive_Flag = 1;
//								F_Dataval_lcd = 0;  
//								Receive_CRC_Lcd=0x68;
//					}
//		 }
//		 else if(Receive_Flag==1)
//		 {
//			 
//				if(Receive_index==1)   //����λ��Ϊ1
//			{
//				if(tmp!=0xA0) //��ַ�ж� 
//				{
//					Receive_Flag = 0;
//					Receive_index = 0;
//						Receive_CRC_Lcd = 0;
//					return ;                //�Ǳ�����ַ
//				}
//			}
//			LCD_Receive[Receive_index] = tmp; 
//			if(LCD_Receive[0]==0x68)
//			{
//				if(Receive_index < 1+1+1+1+LCD_Receive[4]+1) //У��λǰ���������
//					Receive_CRC_Lcd +=tmp; 
//				else if(Receive_index == 1+1+1+1+LCD_Receive[4]+1)
//				{
//					if(Receive_CRC_Lcd!=tmp)    //У��
//					{
//						Receive_Flag = 0;
//						Receive_index = 0;
//						tmp = 0;
//						Receive_CRC_Lcd = 0;
//					//	Err_State = ERRO_FRAME_CHECK_SUM;
//						return ;                     //����У��λ
//					}
//					else
//					{
//						Receive_CRC_Lcd = 0;           //У��ͨ��
//					}
//					
//				}
//				Receive_index++;
//				if(Receive_index==1+1+1+1+1+LCD_Receive[4]+1+1 && tmp==0x16) //�������ж�
//				{
//					for(i=0;i<20;i++)
//					{
//						LCD_Receive_last[i]=LCD_Receive[i];   //�����ݱ���
//					}
//					Receive_Flag = 0;
//					Receive_index = 0;
//					F_Dataval_lcd = 1;           //�������
//					tmp = 0;
//					//Err_State = OK;
//				}
//			}
//				
//		 }
//	 }
//  /* USER CODE BEGIN USART3_4_IRQn 1 */

//  /* USER CODE END USART3_4_IRQn 1 */
//}