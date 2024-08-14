//#include "stm32f10x.h"
#include "disp.h"
#include "delay.h"
//#include "sys.h" 
#include "24cxx.h"
#include "tool.h"
//#include "tool.h"
#include "rtc.h"
#include "LCD.h"
#include "display_ziku.h"
#include "string.h"
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
#define Addr_loudian				10264
#define Addr_dianya				1002  //1�ֽ�
#define Addr_dianliu			1001	//1�ֽ�
#define Addr_TX           1003
#define Addr_jiaozhun       10300
#define Addr_wendu       10301
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

#define Addr_energy_active_he 12044  //���ܴ洢����20�ֽ�
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
#define Addr_energy_active_A  12048  //A���й����ܴ洢����4�ֽ�,32λ
#define Addr_energy_active_C  12052  //B���й����ܴ洢����4�ֽ�,32λ
#define Addr_energy_reactive_he  12056 //�����޹������ܴ洢����4�ֽ�,32λ
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

#define Addr_energy_active_he 12044  //���ܴ洢����20�ֽ�

#define Addr_energy_active_A  12048  //A���й����ܴ洢����4�ֽ�,32λ
#define Addr_energy_active_C  12052  //B���й����ܴ洢����4�ֽ�,32λ
#define Addr_energy_reactive_he  12056 //�����޹������ܴ洢����4�ֽ�,32λ


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



#define Tem_IN_N 55
#define Tem_IN_A 65 
#define Tem_IN_B 57
#define Tem_IN_C 63

#define Tem_OUT_N 59
#define Tem_OUT_A 51
#define Tem_OUT_B 61
#define Tem_OUT_C 53


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
unsigned int cur_handle_A(unsigned int x);
unsigned int cur_handle_B(unsigned int x);
unsigned int cur_handle_C(unsigned int x);
extern unsigned char F_initial_lcd;
extern unsigned char F_initial_lcd_hezha;
extern unsigned char Vol_g_T,Vol_q_T,Vol_s_T,F_C_IP,TH_Long_Cur,F_TB_trip,N_anolog_trip,F_ia,F_ip_3,F_sssj,F_cd_set,F_ip,F_cal,point_event_trip,point_event_trip_24C256,F_anolog_trip,LC_N,GZ_ph_disp,F_ch,F_gz_disp,F_al1,disp_status,D_LCur,TH_LCur,Vol_g,Vol_q,Vol_ch ,F_Special_wave;
extern unsigned char  LOGO_RENMIN[1024];
extern unsigned char 		F_L_err,	F_AVcal_err,			F_BVcal_err,			F_CVcal_err;
extern unsigned char  gang[2];
extern unsigned char F_cal_finish;
extern unsigned int vol_cal_handle(unsigned int value);
extern unsigned int cur_cal_handle(unsigned int x);
extern unsigned char 			F_AIcal_err,			F_BIcal_err,			F_CIcal_err;
extern unsigned char 			F_aIcal_err,			F_bIcal_err,			F_cIcal_err;
extern unsigned int vol_handle_A(unsigned int value);
extern unsigned int vol_handle_B(unsigned int value);
extern unsigned int vol_handle_C(unsigned int value);
extern unsigned int leak_handle(unsigned int x);
extern unsigned char  zuokuohao[4];
extern unsigned char  youkuohao[4];
extern unsigned int NUM_test,NUM_test1;
unsigned char F_shishichaxun=0;
unsigned char F_init_chenggong=0;
extern unsigned char Type_cur_Temp;
extern unsigned char  maohao[16];
extern volatile unsigned char  F_dianya_chonghe;
void RS485_Init(u32 bound);
extern signed int HT7038_buf[40];
extern volatile unsigned char tim_m3,tim_d3,tim_h3,tim_f3,tim_s3;
extern volatile unsigned int  tim_y3;
extern volatile unsigned	char  F_trip_QX,F_trip_QL;
extern unsigned char  qirigang[16];
extern unsigned char  xiaogang[16];
extern unsigned char  xiaomaohao[16];
extern  volatile signed int I_A_factor,V_A_factor,I_B_factor,V_B_factor,I_C_factor,V_C_factor,V1_slope[3];
extern volatile unsigned short int I1_A_slope[2],I1_B_slope[2],I1_C_slope[2];	
extern volatile unsigned short int I1_400A_slope[2],I1_400B_slope[2],I1_400C_slope[2];
extern volatile unsigned short int I1_630A_slope[2],I1_630B_slope[2],I1_630C_slope[2];	
extern volatile unsigned short int I1_800A_slope[2],I1_800B_slope[2],I1_800C_slope[2];	
extern unsigned char N_GY_yanshi,N_QY_yanshi,D_GY_yanshi,D_QY_yanshi,D_SY_yanshi;
extern unsigned char LouD_GaoJing;
extern unsigned char fuhao[12];///ht7038zzz
extern signed int Accumulate_energy_dangqian_active_he ; //������ܺ����й�
extern  signed int Accumulate_energy_shangci_active_he;
extern  signed int Accumulate_energy_dangqian_active_A ; //�������A���й�
extern  signed int Accumulate_energy_shangci_active_A;
extern  signed int Accumulate_energy_dangqian_active_C ; //�������C���й�
extern  signed int Accumulate_energy_shangci_active_C;
extern  signed int Accumulate_energy_dangqian_reactive_he ; //������ܺ����޹�
extern signed int Accumulate_energy_shangci_reactive_he;
volatile  unsigned int Func_Index=0;     
	unsigned char lishijilu_1[5]={0},lishijilu_2[5]={0},lishijilu_3[5]={0},guzhang_wei=0;
	unsigned char nian[3]={0},yue[3]={0},ri[3]={0},shi[3]={0},fen[3]={0},miao[3]={0};
	unsigned char add_1_1[2]={0},add_2_1[2]={0},add_3_1[2]={0},add_4_1[2]={0},add_5_1[2]={0},add_6_1[2]={0};
	unsigned char add_1_2[2]={0},add_2_2[2]={0},add_3_2[2]={0},add_4_2[2]={0},add_5_2[2]={0},add_6_2[2]={0};
	void (*Func_Ptr)();				
	unsigned char F_up_down_switch=0;
	unsigned char zifu_dian[5]={0};
	extern  unsigned char  DIANYA[4][5], dianliu[7][6],shijian[4][5],DIANYA_1[5][5],cishu[3][2],kaiguan[2][3];
	extern unsigned char queding(unsigned char dat);
	void I_VAL_handle(void);
char V_Code[5]="20.03"; 
	extern  unsigned int Lcd_Count;
	extern unsigned char shangdian,duandian,jiaozhun,wendu,F_TX;
u16 a;
u8 b,c,d,e,f;
	extern signed char F_cal_L,F_cal_V_A,F_cal_V_B,F_cal_V_C,F_cal_I_A,F_cal_I_B,F_cal_I_C;
	unsigned char GZ_re_disp (unsigned char re);
void disp_data_prepare(void);
extern volatile unsigned char F_hezha_state,F_fenzha_state,F_hezha_delay,LEDA_FLAG;
extern unsigned char Vol_up,Vol_down;
extern unsigned char F_Sample,F_leak_disp;
unsigned char abnormal_disp(void);
unsigned char guzhang_disp(void);
unsigned char F_cd_set_disp=0;
void I_VAL_handle(void);
volatile unsigned char dii;
	extern volatile unsigned int Leak_Cur_disp_cal;
extern unsigned int cur_handle(unsigned int x);
extern volatile unsigned int T_64_1min,T_64_2min;
	extern void ctrlword4_analyze(void);
extern unsigned int vol_handle(unsigned int value);
extern unsigned int vol_handle_A(unsigned int value);
void back_button(void);
extern void Cur_Switch(unsigned char tmp);
//void RS485_hongwai_Init(u32 bound);
extern unsigned char T_64_6s,T_64_10s;
extern volatile unsigned int Leak_Cur_disp_temp;
extern volatile signed  int I_Array[20],I_Array_xianshi[20];
extern volatile signed long I_I_Array_xianshi[20],CurA_cal_tmp[5],CurB_cal_tmp[5],CurC_cal_tmp[5],Leak1_temp,Vol1_A_temp,Vol1_B_temp,Vol1_C_temp,Leak_temp[3];
extern unsigned short int L_slope[3];
extern volatile signed long CurA400_cal_tmp[5],CurB400_cal_tmp[5],CurC400_cal_tmp[5];
extern volatile signed long CurA630_cal_tmp[5],CurB630_cal_tmp[5],CurC630_cal_tmp[5];
extern volatile signed long CurA800_cal_tmp[5],CurB800_cal_tmp[5],CurC800_cal_tmp[5];
extern volatile signed long V_A_slope[3];
extern unsigned int Cur_cal_tmp[2];

extern unsigned char TXJZ_start;//ͨѶУ׼��ʼ��־λ0������1��ʼ
extern unsigned char TXJZ_SJ;//ͨѶʱ��
//unsigned char TXJZ_DY=0;//ͨѶ��ѹ
extern unsigned char TXJZ_LD;//ͨѶ©��

extern unsigned char TXJZ_DL_A;//ͨѶ����A
extern unsigned char TXJZ_DL_B;//ͨѶ����B
extern unsigned char TXJZ_DL_C;//ͨѶ����C

extern unsigned char TXJZ_DY_A;//ͨѶ��ѹA
extern unsigned char TXJZ_DY_B;//ͨѶ��ѹB
extern unsigned char TXJZ_DY_C;//ͨѶ��ѹC


unsigned char noguzhang_disp(void);
extern volatile unsigned char D2_Cur,TH_DL,D3_Cur; 

extern unsigned char  dian[16];

unsigned char table[]=
{
	0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71,0x3d,0x76 
}
;
//0~H
unsigned char func_buf[34]=
{
	0x67,0x6e,0x3d,0x6e,0x3d,0x0e,0x78,0x7c,0x77,0x3e,0x3d,0x38,0x38,0x5e,0x67,0x77,0x3d,0x77,0x5e,0x77,0x38,0x77,0x5e,0x7c,0X6D,0X73,0x37,0x06,0x00,0x00,0x6e,0x39,0x39,0x5e 
}
;
// q    y    g    y    g    j   t     b    a    u    g    l    l    d    q    a   g    a     d    a    l    a   d     b   s    p    n    i     0    0    y   c     c   d 
unsigned char nor_disp_led_buf[9]=
{
	0x38,0x77,0x7c,0x39,0x77,0x7c,0x39,0x00,0x71 
};
extern volatile unsigned int T_48_10s,Vol_A_aver;
extern volatile unsigned int Num_quitleak,Num_tripdelay,Num_tripinstant;
extern volatile unsigned int key_state;
unsigned int volatile key_connter = 0,nor_disp_num_buf[20];
volatile unsigned int key_flag = 0,F_ent=0;
extern volatile unsigned char  F_Leak_Delay,F_Disp,F_key,F_disp_tr,F_ld,F_ks,F_TB_gz,F_fz,F_hz;
extern  volatile unsigned char F_disp_jg;
extern volatile unsigned char  F_trip_ld,F_trip_gl,F_trip_qy,F_trip_gy,F_MODE,F_nokey,F_trip_sy,F_data_clear,F_Corr,F_auto_ld;
extern unsigned char F_C_IP,TH_Long_Cur,F_TB_trip,N_anolog_trip,F_ia,F_ip_3,F_sssj,F_cd_set,F_ip,F_cal,point_event_trip,point_event_trip_24C256,F_anolog_trip,LC_N,GZ_ph_disp,F_ch,F_gz_disp,F_al1,disp_status,D_LCur,TH_LCur,Vol_g,Vol_q,Vol_ch,Vol_s_T,F_Special_wave ;
extern volatile unsigned int Leak_Cur_disp_temp,Leak_xianshi_disp;
extern volatile unsigned char D_Cur,Type_Cur,baud;
extern  unsigned char ctrlword[5];
extern volatile unsigned int T_64_1min,T_64_2min,Leak_Cur_disp,L_Cur,A_Vol,B_Vol,C_Vol,A_Cur,B_Cur,C_Cur,Z_Cur,I_VAL,V_Array_record[3],V_sample[3],V_Array[3],V_Array_disp[3],Power_A_Value,Power_B_Value,Power_C_Value;
//volatile unsigned long V_Array[3];
extern volatile signed int I_Array[20];
extern volatile unsigned int gz_disp;
unsigned char dispbit[8];
volatile unsigned char disp_num=0,Cal_state=0;
volatile unsigned char disp_status1=0,disp_gz=0,SET_D_Cur=0 ;
extern volatile unsigned short int N_disp,V_factor,L_factor,I_factor,L1_slope;
unsigned char key_value_tmp =0,record_array[12]={0};
extern  unsigned char Type_Cur_change;

extern float Power_factor[3],Active_Pow[3],Total_power[3];
extern void Write_Selftest_Record(unsigned char self_method);
extern unsigned char fenzha_chenggong;//������բ�ɹ���־0x11Ϊ�ɹ�

unsigned int Leak_Class[8]=
{
30,50,100,200,300,500,800,1000
}
;
 unsigned char DIANYA2[6][6]=
{
    "250V","260V","270V","280V" ,"290V", "300V"
};


unsigned char DIANYA3[6][6]=
{
    "140V","150V","160V","170V","180V","190V"  
};
 unsigned char dianliu1[9][6]=
{
 "0.03A","0.05A","0.1A","0.2A","0.3A","0.5A","0.8A","1A","Auto"
};


volatile unsigned char tim_disp[7]={0},tim_m,tim_d,tim_h,tim_f,tim_s,sssj_N,sssj_N_xunhuan;
volatile unsigned char tim_m1,tim_d1,tim_h1,tim_f1,tim_s1;
volatile unsigned int  tim_y;
volatile unsigned int  tim_y1;


volatile unsigned char tim_m2,tim_d2,tim_h2,tim_f2,tim_s2;
volatile unsigned int  tim_y2;

volatile unsigned int SET_I_VAL, gz_disp1,gz_disp_uart;

/**********************************��-ͨ�ŵ�ַ************************************/
extern unsigned char self_addr_code[6];
extern unsigned char self_addr_code_temp[6];
extern volatile  unsigned char F_gc;
/**********************************��-ͨ�ŵ�ַ************************************/
extern volatile unsigned char F_jiance;



unsigned char   mima[4];//2022.2.21���ݼ����빦�ܣ��������������飬���ڴ�Ű������������
unsigned char   mima_set[4];//�û��趨�����룬���������������ȶ�

unsigned char dispbit[8],array_temps[30];
extern volatile unsigned char point_event_leak,F_hezha_sta,point_event_self;
unsigned int Password_key=0;
volatile unsigned char pass_key[4];
extern  unsigned char password_0class[4],password_1class[4],password_2class[4];
int shuzi,weizhi,i;
extern unsigned char F_queren;


unsigned char check_reason=0;//��������У���ԭ����ȷ��������ȷ���ǽ���������û��ǳ�ʼ������

unsigned char mima0[2]={0},mima1[2]={0},mima2[2]={0},mima3[2]={0};
extern volatile unsigned int V_Array_disp[3],Re_point_VA,Samp_start_end_flag,Re_j,Re_dot_U[3],Re_dot_I[3],Re_UA_j,Re_UB_j,Re_UC_j,Re_IA_j,Re_IB_j,Re_IC_j;
extern volatile signed int Zhou_bo_UA[70],Zhou_bo_UB[70],Zhou_bo_UC[70],Zhou_bo_IA[70],Zhou_bo_IB[70],Zhou_bo_IC[70];
extern volatile signed int Zhou_bo_Ins_UA[64],Zhou_bo_Ins_UB[64],Zhou_bo_Ins_UC[64],Zhou_bo_De_IA[64],Zhou_bo_De_IB[64],Zhou_bo_De_IC[64];
extern volatile signed int Zhou_bo_De_UA[64],Zhou_bo_De_UB[64],Zhou_bo_De_UC[64],Zhou_bo_Ins_IA[64],Zhou_bo_Ins_IB[64],Zhou_bo_Ins_IC[64];
extern volatile signed int Re_Zhou_bo_UA[64],Re_Zhou_bo_UB[64],Re_Zhou_bo_UC[64];
extern volatile signed int Re_Zhou_bo_IA[64],Re_Zhou_bo_IB[64],Re_Zhou_bo_IC[64];
extern unsigned char Cross_Zero_A[2],Cross_Zero_B[2],Cross_Zero_C[2],Samp_first_flag;
extern volatile signed int Zhou_bojilu_V[640],Zhou_bojilu_A[640],Phase_Differ[3],Cross_Zero[3],Phase_Differ1[3],Phase_Differ_A[16],Phase_Differ_B[16],Phase_Differ_C[16];
extern float Power_factor[3],Active_Pow[3],Total_power[3],Zhou_bojilu[600],UI_AD_multi[3],Power_pool[170],Phase_Differ_buffer[3],Power_factor_test[3],Power_factor_test_Ave[3];
extern float Power_factor_testA[4],Power_factor_testB[4],Power_factor_testC[4],Phase_Differ_A_Two,Phase_Differ_B_Two,Phase_Differ_C_Two;
extern volatile signed int Phase_Differ_average[3],QPhase_Differ_average[3],Phase_Differ_buffer1[3],Phase_Differ_A_Two_Av,Phase_Differ_B_Two_Av,Phase_Differ_C_Two_Av;
extern volatile signed int Phase_Differ_A_one[16],Phase_Differ_B_one[16],Phase_Differ_C_one[16];

extern unsigned int Tem_Array_AD[8],Tem_value[8] ;
//ht7038
unsigned char array_temp[2];
	 signed int Measured_value_A,Measured_value_B,Measured_value_C;
//	 signed int True_value=11000;
extern float Ugain_A,Ugain_B,Ugain_C,Igain_A,Igain_B,Igain_C,Pgain_AA,Pgain_BB,Pgain_CC;
extern float Urms_A,Urms_B,Urms_C;
extern unsigned int Uoffset_A,Uoffset_B,Uoffset_C,Ioffset_A,Ioffset_B,Ioffset_C;
void Up_key_state(void)
{
	unsigned char up_tmp;	
	
	if(Type_Cur==0)
	{
		up_tmp = 0x08;
	}
	else if(Type_Cur==1)
	{
		up_tmp = 0x13;
	}
	else if(Type_Cur==2)
	{
		up_tmp = 0x0A;
	}
	else if(Type_Cur==3)
	{
		up_tmp = 0x0E;
	}
	else if(Type_Cur==4)
	{
		up_tmp = 0x02;
	}
	else
	{
		Type_Cur = 1;
		up_tmp = 0x0E;
	}
		if((key_state>=0x10005000)&&(key_state<0x10005009))key_state+=0x00000001;//5.����Ӽ��ϼ�
		else if((key_state>=0x10005100)&&(key_state<0x10005109))key_state+=0x00000001;
		else if((key_state>=0x10005200)&&(key_state<0x10005209))key_state+=0x00000001;
		else if((key_state>=0x10005300)&&(key_state<0x10005309))key_state+=0x00000001;
	
		else if((key_state>=0x10006000)&&(key_state<0x10006009))key_state+=0x00000001;//6.����Ӽ��ϼ�
		else if((key_state>=0x10006100)&&(key_state<0x10006109))key_state+=0x00000001;
		else if((key_state>=0x10006200)&&(key_state<0x10006209))key_state+=0x00000001;
		else if((key_state>=0x10006300)&&(key_state<0x10006309))key_state+=0x00000001;
	
		else if((key_state>=0x10008000)&&(key_state<0x10008009))key_state+=0x00000001;//8.����Ӽ��ϼ�
		else if((key_state>=0x10008100)&&(key_state<0x10008109))key_state+=0x00000001;
		else if((key_state>=0x10008200)&&(key_state<0x10008209))key_state+=0x00000001;
		else if((key_state>=0x10008300)&&(key_state<0x10008309))key_state+=0x00000001;
	  
	  else if((key_state>=0x5000)&&(key_state<0x5007))key_state+=0x0001;//�ʣ�ද������//�ϼ���������
		else if((key_state>=0x5100)&&(key_state<0x5103))key_state+=0x0001;//����޲�����ʱ��
		else if((key_state>=0x5200)&&(key_state<(0x5200+up_tmp)))key_state+=0x0001;//�������λ
		else if((key_state>=0x5300)&&(key_state<0x5304))key_state+=0x0001;//���س���ʱʱ��
		else if((key_state>=0x5400)&&(key_state<0x5404))key_state+=0x0001;//��·����ʱ������λ
		else if((key_state>=0x5500)&&(key_state<0x5503))key_state+=0x0001;//��·����ʱʱ�䵵λ
		else if((key_state>=0x5600)&&(key_state<0x5605))key_state+=0x0001;//��·˲ʱ��λ
		
		
		else if((key_state>=0x5700)&&(key_state<0x5704))key_state+=0x0001;//��ѹ��λ
		else if((key_state>=0x5800)&&(key_state<0x580A))key_state+=0x0001;//��ѹʱ�䵵λ
		else if((key_state>=0x5900)&&(key_state<0x5905))key_state+=0x0001;//Ƿѹ��λ
		else if((key_state>=0x5A00)&&(key_state<0x5A0A))key_state+=0x0001;//Ƿѹʱ�䵵λ
		else if((key_state>=0x5B00)&&(key_state<0x5B03))key_state+=0x0001;//©���غϴ���
		
		else if((key_state>=0x5C00)&&(key_state<0x5C06))key_state+=0x0001;//���಻ƽ�������ֵ��λ
		else if((key_state>=0x5D00)&&(key_state<0x5D09))key_state+=0x0001;//���಻ƽ�����������ֵ��λ
		else if((key_state>=0x5E00)&&(key_state<0x5E09))key_state+=0x0001;//���಻ƽ�����ʱ�䵵λ
		else if((key_state>=0x5F00)&&(key_state<0x5F03))key_state+=0x0001;//���಻ƽ���������ʱ�䵵λ
		
	
}

void Down_key_state(void)
{
	if((key_state>=0x10005001)&&(key_state<=0x10005009))key_state-=0x00000001;//5.����Ӽ��¼�
	if((key_state>=0x10005101)&&(key_state<=0x10005109))key_state-=0x00000001;
	if((key_state>=0x10005201)&&(key_state<=0x10005209))key_state-=0x00000001;
	if((key_state>=0x10005301)&&(key_state<=0x10005309))key_state-=0x00000001;
	
	if((key_state>=0x10006001)&&(key_state<=0x10006009))key_state-=0x00000001;//6.����Ӽ��¼�
	if((key_state>=0x10006101)&&(key_state<=0x10006109))key_state-=0x00000001;
	if((key_state>=0x10006201)&&(key_state<=0x10006209))key_state-=0x00000001;
	if((key_state>=0x10006301)&&(key_state<=0x10006309))key_state-=0x00000001;
	
	if((key_state>=0x10008001)&&(key_state<=0x10008009))key_state-=0x00000001;//8.����Ӽ��¼�
	if((key_state>=0x10008101)&&(key_state<=0x10008109))key_state-=0x00000001;
	if((key_state>=0x10008201)&&(key_state<=0x10008209))key_state-=0x00000001;
	if((key_state>=0x10008301)&&(key_state<=0x10008309))key_state-=0x00000001;
	
	if((key_state>=0x5001)&&(key_state<=0x5007))key_state-=0x0001;//�ʣ�ද������//�¼�����ѡ��
	if((key_state>=0x5101)&&(key_state<=0x5103))key_state-=0x0001;//����޲�����ʱ��
	if((key_state>=0x5201)&&(key_state<=0x5215))key_state-=0x0001;//�������λ
	if((key_state>=0x5301)&&(key_state<=0x5304))key_state-=0x0001;//���س���ʱʱ��
	if((key_state>=0x5401)&&(key_state<=0x5404))key_state-=0x0001;//��·����ʱ������λ
	if((key_state>=0x5501)&&(key_state<=0x5503))key_state-=0x0001;//��·����ʱʱ�䵵λ
	if((key_state>=0x5601)&&(key_state<=0x5605))key_state-=0x0001;//��·˲ʱ��λ
	
	
	if((key_state>=0x5701)&&(key_state<=0x5704))key_state-=0x0001;//��ѹ��λ
	if((key_state>=0x5801)&&(key_state<=0x580A))key_state-=0x0001;//��ѹʱ�䵵λ
	if((key_state>=0x5901)&&(key_state<=0x5905))key_state-=0x0001;//Ƿѹ��λ
	if((key_state>=0x5A01)&&(key_state<=0x5A0A))key_state-=0x0001;//Ƿѹʱ�䵵λ
	if((key_state>=0x5B01)&&(key_state<=0x5B03))key_state-=0x0001;//©���غϴ���
	
	if((key_state>=0x5C01)&&(key_state<=0x5C06))key_state-=0x0001;//���಻ƽ�������ֵ��λ
	if((key_state>=0x5D01)&&(key_state<=0x5D09))key_state-=0x0001;//���಻ƽ�����������ֵ��λ
	if((key_state>=0x5E01)&&(key_state<=0x5E09))key_state-=0x0001;//���಻ƽ�����ʱ�䵵λ
	if((key_state>=0x5F01)&&(key_state<=0x5F03))key_state-=0x0001;//���಻ƽ���������ʱ�䵵λ
	
	
}


void Up_key_state(void);
void Down_key_state(void);
void disp_set(unsigned int tmp);
void menu_disp( unsigned int tmp);
void Ld_disp(unsigned int tmp);
void Dy_disp(unsigned int tmp);
void Dl_disp(unsigned int tmp);
void Ls_disp(unsigned int tmp);
void Sj_disp(unsigned char tmp);
void Get_record(unsigned int tmp);
//void GZ_re_disp(unsigned char re);
void Sf_disp(unsigned int tmp);
void num_handle(unsigned int x);

void Cur250_calibrate_tmp(void);
void Cur400_630_calibrate_tmp(void);
extern void Read_Cur_calibrae_data(void);

extern volatile unsigned char F_gz_clear,F_time_compare,T_50hz_tmp,F_sys_pulse,F_Leak_Alarm,F_qxATrip,F_qxBTrip,F_qxCTrip,F_qxallTrip;


void KEY_Init(void) //IO��ʼ��
{ 
// 	GPIO_InitTypeDef GPIO_InitStructure;
// 
// 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//ʹ��ʱ��

//	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_5|GPIO_Pin_4;//KEY0-KEY2
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
// 	GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIOb2,3,4
//	
//	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO, ENABLE);	 //ʹ��PB,PE�˿�ʱ�� 	
//	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
// GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;				 //բλ�ü��
// GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_IPU; 		 //��������
// GPIO_Init(GPIOB, &GPIO_InitStructure);	  
//	
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
//	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_12;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //PA0���ó����룬Ĭ������	  
//	GPIO_Init(GPIOC, &GPIO_InitStructure);//��ʼ��GPIOC
//	
//		
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
//	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_1|GPIO_Pin_0|GPIO_Pin_6;
//	GPIO_InitStructure.GPIO_Mode =   GPIO_Mode_IPU; //PA0���ó����룬Ĭ������	  
//	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOC
//	
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
//	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_9|GPIO_Pin_8;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //PA0���ó����룬Ĭ������	  
//	GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIOC	
	
}

//����������
//���ذ���ֵ
//mode:0,��֧��������;1,֧��������;
//0��û���κΰ�������
//1��KEY0����
//2��KEY1����
//3��KEY2���� 
//4��KEY3���� WK_UP
//ע��˺�������Ӧ���ȼ�,KEY0>KEY1>KEY2>KEY3!!
void  tiaozheng_key_state(unsigned int x0,unsigned int value,unsigned char moshi)
{

		
			      if((key_state>>12)==(x0>>12))        
					{
						  if(moshi==1)
							{
									key_state++;
									if(key_state>=(x0+value))
									{
										key_state=x0;
									}
							}
							else
							{
								key_state--;
								if(key_state<x0)
								{
									key_state=(x0+value-1);
								}					
							}

					}

}
void shijian_tiaozheng(unsigned char temp[3],unsigned char e,unsigned char f)
{
	temp[0]=e+0x30;
	temp[1]=f+0x30;

	temp[2]='\0';
}
/***************************************���������ַ���**********************************************/
void generate_chuan(unsigned char p[5],unsigned char a,unsigned char b,unsigned char c,unsigned char d)
	{
		p[0]=a+0x30;

		p[1]=b+0x30;

		p[2]=c+0x30;

		p[3]=d+0x30;

		p[4]='\0';	
	}
/***************************************��ʾ���������ַ���**********************************************/
	void xianshishuju_dianliu(unsigned int dat)
{

	if(dat>=1000)
	{
		zifu_dian[0]=(dat/1000)+0x30;
		zifu_dian[1]=((dat%1000)/100)+0x30;
		zifu_dian[2]=((dat%100)/10)+0x30;
		zifu_dian[3]=((dat%100)%10)+0x30;
		zifu_dian[4]='A';
		zifu_dian[3]='5';
	}
	else if(dat>=100)
	{
		zifu_dian[0]=(dat/100)+0x30;
		zifu_dian[1]=((dat%100)/10)+0x30;
		zifu_dian[2]=((dat%100)%10)+0x30;
		zifu_dian[4]='\0';
			zifu_dian[3]='A';
	
	}
	else if((10<=dat)&&(dat<100))
	{
		zifu_dian[0]=(dat/10)+0x30;
		zifu_dian[1]=(dat%10)+0x30;
		zifu_dian[3]='\0';
			zifu_dian[2]='A';

	}
	else if((0<=dat)&&(dat<10))
	{
		zifu_dian[0]=dat+0x30;
		zifu_dian[2]='\0';
			zifu_dian[1]='A';
	}
	else
	{
		memset(zifu_dian,0,5);
	
	}


}	
void xianshishuju2(unsigned int dat)
{

		zifu_dian[0]=(dat/100000)+0x30;
		zifu_dian[1]=((dat%100000)/10000)+0x30;
		zifu_dian[2]=((dat%10000)/1000)+0x30;
		zifu_dian[3]=((dat%1000)/100)+0x30;
		zifu_dian[4]=((dat%100)/10)+0x30;
		zifu_dian[5]=((dat%100)%10)+0x30;
		zifu_dian[6]='\0';
	

}	
void xianshishuju3(unsigned int dat)
{

		zifu_dian[0]=(dat/1000)+0x30;
		zifu_dian[1]=((dat%1000)/100)+0x30;
		zifu_dian[2]=((dat%100)/10)+0x30;
		zifu_dian[3]=((dat%100)%10)+0x30;
		zifu_dian[4]='\0';
	

}	
void xianshishuju(unsigned int dat)
{
	if(dat>=1000)
	{
		zifu_dian[0]=(dat/1000)+0x30;
		zifu_dian[1]=((dat%1000)/100)+0x30;
		zifu_dian[2]=((dat%100)/10)+0x30;
		zifu_dian[3]=((dat%100)%10)+0x30;
		zifu_dian[4]='\0';
	
	}
	else if(dat>=100)
	{
		zifu_dian[0]=(dat/100)+0x30;
		zifu_dian[1]=((dat%100)/10)+0x30;
		zifu_dian[2]=((dat%100)%10)+0x30;
		zifu_dian[3]='\0';
	
	}
	else if((10<=dat)&&(dat<100))
	{
		zifu_dian[0]=(dat/10)+0x30;
		zifu_dian[1]=(dat%10)+0x30;
		zifu_dian[2]='\0';

	}
	else if((0<=dat)&&(dat<10))
	{
		zifu_dian[0]=dat+0x30;
		zifu_dian[1]='\0';
	}
	else
	{
		memset(zifu_dian,0,5);
	
	}


}	
void xianshishuju1(unsigned int dat)
{
	  	if(dat>=100000)
	{
		zifu_dian[0]=(dat/100000)+0x30;
		zifu_dian[1]=((dat%100000)/10000)+0x30;
		zifu_dian[2]=((dat%10000)/1000)+0x30;
		zifu_dian[3]=((dat%1000)/100)+0x30;
		zifu_dian[4]=((dat%100)/10)+0x30;
		zifu_dian[5]=((dat%100)%10)+0x30;
		zifu_dian[6]='\0';
	
	}
  else	if(dat>=10000)
	{
		zifu_dian[0]=(dat/10000)+0x30;
		zifu_dian[1]=((dat%10000)/1000)+0x30;
		zifu_dian[2]=((dat%1000)/100)+0x30;
		zifu_dian[3]=((dat%100)/10)+0x30;
		zifu_dian[4]=((dat%100)%10)+0x30;
		zifu_dian[5]='\0';
	
	}
	else if(dat>=1000)
	{
		zifu_dian[0]=(dat/1000)+0x30;
		zifu_dian[1]=((dat%1000)/100)+0x30;
		zifu_dian[2]=((dat%100)/10)+0x30;
		zifu_dian[3]=((dat%100)%10)+0x30;
		zifu_dian[4]='\0';
	
	}
	else if(dat>=100)
	{
		zifu_dian[0]=(dat/1000)+0x30;
		zifu_dian[1]=((dat%1000)/100)+0x30;
		zifu_dian[2]=((dat%100)/10)+0x30;
		zifu_dian[3]=((dat%100)%10)+0x30;
		zifu_dian[4]='\0';
//		zifu_dian[0]=(dat/100)+0x30;
//		zifu_dian[1]=((dat%100)/10)+0x30;
//		zifu_dian[2]=((dat%100)%10)+0x30;
//		zifu_dian[3]='\0';
	
	}
	else if((10<=dat)&&(dat<100))
	{
		zifu_dian[0]=(dat/1000)+0x30;
		zifu_dian[1]=((dat%1000)/100)+0x30;
		zifu_dian[2]=((dat%100)/10)+0x30;
		zifu_dian[3]=((dat%100)%10)+0x30;
		zifu_dian[4]='\0';
//		zifu_dian[0]=(dat/10)+0x30;
//		zifu_dian[1]=(dat%10)+0x30;
//		zifu_dian[2]='\0';

	}
	else if((0<=dat)&&(dat<10))
	{
		zifu_dian[0]=(dat/1000)+0x30;
		zifu_dian[1]=((dat%1000)/100)+0x30;
		zifu_dian[2]=((dat%100)/10)+0x30;
		zifu_dian[3]=((dat%100)%10)+0x30;
		zifu_dian[4]='\0';
//		zifu_dian[0]=dat+0x30;
//		zifu_dian[1]='\0';
	}
	else
	{
		memset(zifu_dian,0,5);
	
	}
//		putchar(zifu_dian[0]);
//	putchar(zifu_dian[1]);
//	putchar(zifu_dian[2]);

}	

	
void shishishuju(unsigned char temp_s)
{
		
	if(temp_s==1)//��һ����ʾ��ѹ����
	{
    clear_screen();
		
		Lcd12864_Write16CnCHAR(0,0,0,"I��:      L:\rUa:   V Ia:   V\rUb:   V Ib:   V\rUc:   V Ic:   V\r");
		xianshishuju(Leak_Cur_disp);
		display_ASCIIstring_8x16(1,96,(unsigned char*)zifu_dian);

		if(D_LCur==0)
			{
				display_ASCIIstring_8x16(1,35,"0.03A");

			}
			else if(D_LCur==1)
			{
				display_ASCIIstring_8x16(1,35,"0.05A");

			}
			else if(D_LCur==2)
			{
				display_ASCIIstring_8x16(1,35,"0.1A");

			}
			else if(D_LCur==3)
			{
				display_ASCIIstring_8x16(1,35,"0.2A");

			}
						else if(D_LCur==4)
			{
				display_ASCIIstring_8x16(1,35,"0.3A");
			}
			else if(D_LCur==5)
			{
				display_ASCIIstring_8x16(1,35,"0.5A");

			}
			else if(D_LCur==6)
			{
				display_ASCIIstring_8x16(1,35,"0.8A");

			}
			else if(D_LCur==7)
			{
				display_ASCIIstring_8x16(1,35,"1A");
			}
			else if(D_LCur==8)
			{
				display_ASCIIstring_8x16(1,35,"Auto");
			}
		
		
		
	 Lcd12864_Write16CnCHAR(0,0,2,"Ua:   V\rUb:   V\rUc:   V\r");
	 Lcd12864_Write16CnCHAR(0,64,2,"Ia:   A\r");
	 Lcd12864_Write16CnCHAR(0,64,4,"Ib:   A\r");
	 Lcd12864_Write16CnCHAR(0,64,6,"Ic:   A\r");
		
			xianshishuju(HT7038_buf[4]);          	//��������
			display_ASCIIstring_8x16(3,91,zifu_dian);	
	 



			
			xianshishuju(HT7038_buf[5]);
			display_ASCIIstring_8x16(5,91,zifu_dian);			
			xianshishuju(HT7038_buf[6]);
			display_ASCIIstring_8x16(7,91,zifu_dian);
		
		
		xianshishuju(HT7038_buf[1]);//��ѹ����
		display_ASCIIstring_8x16(3,27,zifu_dian);

		xianshishuju(HT7038_buf[2]);
		display_ASCIIstring_8x16(5,27,zifu_dian);
		
		xianshishuju(HT7038_buf[3]);
		display_ASCIIstring_8x16(7,27,zifu_dian);

///***�¶�N  A  B****/
//			xianshishuju(Tem_value[0]);

//		display_ASCIIstring_8x16(3,27,zifu_dian);

//		xianshishuju(Tem_value[1]);
//		display_ASCIIstring_8x16(5,27,zifu_dian);
//		
//		xianshishuju(Tem_value[2]);
//		display_ASCIIstring_8x16(7,27,zifu_dian);
	}
	else if (temp_s==2)
	{
		clear_screen(); 
	//�й�������
	 Lcd12864_Write16CnCHAR(0,0,0,"Ps:          kw");
	 Lcd12864_Write16CnCHAR(0,0,2,"Pa:          kw\r");
	 Lcd12864_Write16CnCHAR(0,0,4,"Pb:          kw\r");
	 Lcd12864_Write16CnCHAR(0,0,6,"Pc:          kw\r"); 
//	 Lcd12864_Write16CnCHAR(0,64,0,"PFs: ");
//	 Lcd12864_Write16CnCHAR(0,64,2,"PFa: ");
//	 Lcd12864_Write16CnCHAR(0,64,4,"PFb: ");
//	 Lcd12864_Write16CnCHAR(0,64,6,"PFc: ");
		xianshishuju2(HT7038_buf[10]);          	//�й�������
		if(fuhao[3]==0xFF)
		{
		display_graphic_8x16(1,29,xiaogang);//36
		}
	 display_ASCIIstring_8x16(1,45,zifu_dian);//29
   display_graphic_8x16(1,69,dian);//36
   display_ASCIIstring_8x16(1,76,&zifu_dian[3]);//44
		

	 xianshishuju2(HT7038_buf[7]);          	//�й�������
	 if(fuhao[0]==0xFF)
		{
		display_graphic_8x16(3,29,xiaogang);//36
		}
	 display_ASCIIstring_8x16(3,45,zifu_dian);//29
   display_graphic_8x16(3,69,dian);//36
   display_ASCIIstring_8x16(3,76,&zifu_dian[3]);//44
		

	 xianshishuju2(HT7038_buf[8]);   
   if(fuhao[1]==0xFF)
		{
		display_graphic_8x16(5,29,xiaogang);//36
		}		
	 display_ASCIIstring_8x16(5,45,zifu_dian);
   display_graphic_8x16(5,69,dian);
   display_ASCIIstring_8x16(5,76,&zifu_dian[3]);
	 

	 xianshishuju2(HT7038_buf[9]);  
    if(fuhao[2]==0xFF)
		{
		display_graphic_8x16(7,29,xiaogang);//36
		}		
	 display_ASCIIstring_8x16(7,45,zifu_dian);
   display_graphic_8x16(7,69,dian);
   display_ASCIIstring_8x16(7,76,&zifu_dian[3]);
		
		//��������
//		 xianshishuju(HT7038_buf[14]);          	//����ϵ������
//		if(fuhao[11]==0xFF)
//		{
//		display_graphic_8x16(1,80,xiaogang);//36
//		}
//	 display_ASCIIstring_8x16(1,100,zifu_dian);
//  // display_graphic_8x16(1,63,dian);	 
//   //display_ASCIIstring_8x16(1,71,&zifu_dian[1]);	
//		
//		
//	 xianshishuju(HT7038_buf[11]);          	//����ϵ������
//		if(fuhao[8]==0xFF)
//		{
//		display_graphic_8x16(3,80,xiaogang);//36
//		}
//	 display_ASCIIstring_8x16(3,100,zifu_dian);
// //  display_graphic_8x16(3,63,dian);	 
//  // display_ASCIIstring_8x16(3,71,&zifu_dian[1]);
//		
//	 xianshishuju(HT7038_buf[12]);   
//   if(fuhao[9]==0xFF)
//		{
//		display_graphic_8x16(5,80,xiaogang);//36
//		}		
//	 display_ASCIIstring_8x16(5,100,zifu_dian);
//  // display_graphic_8x16(5,63,dian); 
//   //display_ASCIIstring_8x16(5,71,&zifu_dian[1]);
//	 
//	 xianshishuju(HT7038_buf[13]);     
//    if(fuhao[10]==0xFF)
//		{
//		display_graphic_8x16(7,80,xiaogang);//36
//		}		
//	 display_ASCIIstring_8x16(7,100,zifu_dian); 
//  // display_graphic_8x16(7,63,dian); 
//  // display_ASCIIstring_8x16(7,71,&zifu_dian[1]);
		
		
	}
	
	
	else if (temp_s==3)
	{
		clear_screen();
	//	Lcd12864_Write16CnCHAR(0,16,0,"����ϵ��/P_F");
		
	 Lcd12864_Write16CnCHAR(0,0,0,"PFs:     ");
	 Lcd12864_Write16CnCHAR(0,0,2,"PFa:     ");
	 Lcd12864_Write16CnCHAR(0,0,4,"PFb:     ");
	 Lcd12864_Write16CnCHAR(0,0,6,"PFc:     ");
		
		
		
		
	 xianshishuju3(HT7038_buf[14]);          	//����ϵ������
		if(fuhao[11]==0xFF)
		{
		display_graphic_8x16(1,40,xiaogang);//36
		}
	 display_ASCIIstring_8x16(1,56,zifu_dian);
   display_graphic_8x16(1,63,dian);	 
   display_ASCIIstring_8x16(1,71,&zifu_dian[1]);	
		
		
	 xianshishuju3(HT7038_buf[11]);          	//����ϵ������
		if(fuhao[8]==0xFF)
		{
		display_graphic_8x16(3,40,xiaogang);//36
		}
	 display_ASCIIstring_8x16(3,56,zifu_dian);
   display_graphic_8x16(3,63,dian);	 
   display_ASCIIstring_8x16(3,71,&zifu_dian[1]);
		
	 xianshishuju3(HT7038_buf[12]);   
   if(fuhao[9]==0xFF)
		{
		display_graphic_8x16(5,40,xiaogang);//36
		}		
	 display_ASCIIstring_8x16(5,56,zifu_dian);
   display_graphic_8x16(5,63,dian); 
   display_ASCIIstring_8x16(5,71,&zifu_dian[1]);
	 
	 xianshishuju3(HT7038_buf[13]);     
    if(fuhao[10]==0xFF)
		{
		display_graphic_8x16(7,40,xiaogang);//36
		}		
	 display_ASCIIstring_8x16(7,56,zifu_dian); 
   display_graphic_8x16(7,63,dian); 
   display_ASCIIstring_8x16(7,71,&zifu_dian[1]);
		
	}	
	
		else if (temp_s==4)
	{
		clear_screen();


	 Lcd12864_Write16CnCHAR(0,0,0,"Fs:         kwh");
	 Lcd12864_Write16CnCHAR(0,0,2,"Fa:         kwh\r");
	 Lcd12864_Write16CnCHAR(0,0,4,"Fb:         kwh\r");
	 Lcd12864_Write16CnCHAR(0,0,6,"Fc:         kwh\r");
		
	xianshishuju2(HT7038_buf[18]);          	//�����й�����

		display_ASCIIstring_8x16(1,29,zifu_dian);//29
   display_graphic_8x16(1,53,dian);//36
   display_ASCIIstring_8x16(1,60,&zifu_dian[3]);//44
		

	xianshishuju2(HT7038_buf[15]);          	//A���й�����
 
		display_ASCIIstring_8x16(3,29,zifu_dian);//29
   display_graphic_8x16(3,53,dian);//36
   display_ASCIIstring_8x16(3,60,&zifu_dian[3]);//44
		

	 xianshishuju2(HT7038_buf[16]);          	
	 display_ASCIIstring_8x16(5,29,zifu_dian);
   display_graphic_8x16(5,53,dian);
   display_ASCIIstring_8x16(5,60,&zifu_dian[3]);
	 

	 xianshishuju2(HT7038_buf[17]);          	
	 display_ASCIIstring_8x16(7,29,zifu_dian);
   display_graphic_8x16(7,53,dian);
   display_ASCIIstring_8x16(7,60,&zifu_dian[3]);
		
	}	
	
	
	
	
	
	else if (temp_s==5)
	{

		 clear_screen();
	
		if(isfenzha==0)
		{
			Lcd12864_Write16CnCHAR(0,32,0,"��բ����\r");
		}

		      else if((F_trip_ld==1)&&(F_al1))
		{				
			 Lcd12864_Write16CnCHAR(0,0,0,"©��澯");
          				  xianshishuju(Leak_Cur_disp);
					display_ASCIIstring_8x16(1,73,(unsigned char*)zifu_dian);
			   Lcd12864_Write16CnCHAR(0,105,0,"mA");
		}
				
		
		else if((isfenzha!=0)||(F_trip_ld==0))
		{
			Lcd12864_Write16CnCHAR(0,32,0,"��բ����\r");
		}
		
		Lcd12864_Write16CnCHAR(0,0,0,"\r©�絵λ:\r�����:\r");
			if(D_LCur==0)
			{
				display_ASCIIstring_8x16(3,83,"30mA");

			}
			else if(D_LCur==1)
			{
				display_ASCIIstring_8x16(3,83,"50mA");

			}
			else if(D_LCur==2)
			{
				display_ASCIIstring_8x16(3,83,"100mA");

			}
			else if(D_LCur==3)
			{
				display_ASCIIstring_8x16(3,83,"200mA");

			}
						else if(D_LCur==4)
			{
				display_ASCIIstring_8x16(3,83,"300mA");
			}
			else if(D_LCur==5)
			{
				display_ASCIIstring_8x16(3,83,"500mA");

			}
			else if(D_LCur==6)
			{
				display_ASCIIstring_8x16(3,83,"800mA");

			}
			else if(D_LCur==7)
			{
				display_ASCIIstring_8x16(3,83,"1000mA");
			}
			else if(D_LCur==8)
			{
				display_ASCIIstring_8x16(3,83,"Auto");
			}
//		  if(TH_LCur==0)
//			{
//				display_ASCIIstring_8x16(3,83,"0.2S");

//			}
//			else if(TH_LCur==1)
//			{
//				display_ASCIIstring_8x16(3,83,"0.3S");

//			}
//			else if(TH_LCur==2)
//			{
//				display_ASCIIstring_8x16(3,83,"0.5S");

//			}
//			else if(TH_LCur==3)
//			{
//				display_ASCIIstring_8x16(3,83,"1S");
//			}
//			else if(TH_LCur==4)
//			{
//				display_ASCIIstring_8x16(3,83,"0.1S");
//			}
		
		xianshishuju_dianliu(SET_I_VAL);
		display_ASCIIstring_8x16(5,83,zifu_dian);

		
	HAL_RTC_GetTime(&hrtc, &stimestructure, RTC_FORMAT_BCD);
  HAL_RTC_GetDate(&hrtc, &sdatestructure, RTC_FORMAT_BCD);

				nian[0]=( sdatestructure.Year>>4)+0x30;				
				nian[1]=(sdatestructure.Year&0x0F)+0x30;	
				nian[2]='\0';
	
				yue[0]=(sdatestructure.Month>>4)+0x30;
				yue[1]=(sdatestructure.Month&0x0F)+0x30;
				yue[2]='\0';

				ri[0]=(sdatestructure.Date>>4)+0x30;
				ri[1]=(sdatestructure.Date&0x0F)+0x30;
				ri[2]='\0';

				shi[0]=(stimestructure.Hours>>4)+0x30;
				shi[1]=(stimestructure.Hours&0x0F)+0x30;
				shi[2]='\0';

				fen[0]=(stimestructure.Minutes>>4)+0x30;
				fen[1]=(stimestructure.Minutes&0x0F)+0x30;
				fen[2]='\0';
				
				miao[0]=(stimestructure.Seconds>>4)+0x30;
				miao[1]=(stimestructure.Seconds&0x0F)+0x30;
				miao[2]='\0';
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

	else if(temp_s==6)
	{
    clear_screen();
		
		Lcd12864_Write16CnCHAR(0,0,0,"Tn->  \rTa->    \rTb->    \rTc->    \r");
		Lcd12864_Write16CnCHAR(0,64,0,"Tn<-   \r");
		Lcd12864_Write16CnCHAR(0,64,2,"Ta<-   \r");
	  Lcd12864_Write16CnCHAR(0,64,4,"Tb<-   \r");
	  Lcd12864_Write16CnCHAR(0,64,6,"Tc<-   \r");

/***�¶�N  A  B****/
		xianshishuju(Tem_value[2]);
		display_ASCIIstring_8x16(1,38,zifu_dian);

		xianshishuju(Tem_value[7]);
		display_ASCIIstring_8x16(3,38,zifu_dian);
		
		xianshishuju(Tem_value[3]);
		display_ASCIIstring_8x16(5,38,zifu_dian);
		
		xianshishuju(Tem_value[6]);
		display_ASCIIstring_8x16(7,38,zifu_dian);
		
		xianshishuju(Tem_value[4]);
		display_ASCIIstring_8x16(1,102,zifu_dian);

		xianshishuju(Tem_value[0]);
		display_ASCIIstring_8x16(3,102,zifu_dian);
		
		xianshishuju(Tem_value[5]);
		display_ASCIIstring_8x16(5,102,zifu_dian);
		
		xianshishuju(Tem_value[1]);
		display_ASCIIstring_8x16(7,102,zifu_dian);
		
		
		
		
	}
	
	
	
	
	
	
	
	
	
//	else if (temp_s==3)
//	{
//		clear_screen();
//		Lcd12864_Write16CnCHAR(0,16,0,"�ܹ���/kw");

//	 Lcd12864_Write16CnCHAR(0,0,2,"Ta:     kw");
//	 Lcd12864_Write16CnCHAR(0,0,4,"Tb:     kw");
//	 Lcd12864_Write16CnCHAR(0,0,6,"Tc:     kw ");
//		

//	 xianshishuju1(nor_disp_num_buf[15]);          	//�ܹ�������
//	 display_ASCIIstring_8x16(3,29,zifu_dian);
//   display_graphic_8x16(3,53,dian);
//   display_ASCIIstring_8x16(3,60,&zifu_dian[3]);
//		

//	 xianshishuju1(nor_disp_num_buf[16]);          	
//	 display_ASCIIstring_8x16(5,29,zifu_dian);
//   display_graphic_8x16(5,53,dian); 
//   display_ASCIIstring_8x16(5,60,&zifu_dian[3]);
//	 
//	 
//	 xianshishuju1(nor_disp_num_buf[17]);          	
//	 display_ASCIIstring_8x16(7,29,zifu_dian);
//   display_graphic_8x16(7,53,dian);	 
//   display_ASCIIstring_8x16(7,60,&zifu_dian[3]);
//	
//	}
//	else if (temp_s==3)
//	{
//     clear_screen();
//		Lcd12864_Write16CnCHAR(0,0,0,"L1        \rA1       \rB1       \rC1       \r");
//		Lcd12864_Write16CnCHAR(0,64,2,"A2    \r");
//		Lcd12864_Write16CnCHAR(0,64,4,"B2    \r");
//		Lcd12864_Write16CnCHAR(0,64,6,"C2    \r");
//		xianshishuju(Leak1_temp);//ld
//		display_ASCIIstring_8x16(1,27,zifu_dian);
//		
//		xianshishuju(Leak_temp[0]);
//		display_ASCIIstring_8x16(3,27,zifu_dian);//A1B1C1
//		xianshishuju(Leak_temp[0]/10);
//		display_ASCIIstring_8x16(5,27,zifu_dian);
//		xianshishuju(Leak_temp[0]/100);
//		display_ASCIIstring_8x16(7,27,zifu_dian);
//		
//		xianshishuju(Leak_temp[1]);          	
//		display_ASCIIstring_8x16(3,91,zifu_dian);//A2B2C2		
//		xianshishuju(Leak_temp[1]);
//		display_ASCIIstring_8x16(5,91,zifu_dian);			
//		xianshishuju(Leak_temp[1]/10);
//		display_ASCIIstring_8x16(7,91,zifu_dian);
//		
//	}
//	else if (temp_s==4)
//	{
//     clear_screen();
//		Lcd12864_Write16CnCHAR(0,0,0,"L2        \rKA       \rKB       \rKC       \r");
//    Lcd12864_Write16CnCHAR(0,64,2,"ka    \r");//����ʵʱADֵ
//		Lcd12864_Write16CnCHAR(0,64,4,"kb    \r");
//		Lcd12864_Write16CnCHAR(0,64,6,"kc    \r");
//		xianshishuju(Leak1_temp);//ld
//		display_ASCIIstring_8x16(1,27,zifu_dian);
//		
//		xianshishuju(L_slope[0]);
//		display_ASCIIstring_8x16(3,27,zifu_dian);//��ѹADֵ
//		xianshishuju(L_slope[0]/10);
//		display_ASCIIstring_8x16(5,27,zifu_dian);
//		xianshishuju(L_slope[0]/100);
//		display_ASCIIstring_8x16(7,27,zifu_dian);
//    
//		xianshishuju(L_slope[1]);          	
//		display_ASCIIstring_8x16(3,91,zifu_dian);//����ʵʱADֵ		
//		xianshishuju(L_slope[1]/10);
//		display_ASCIIstring_8x16(5,91,zifu_dian);			
//		xianshishuju(L_slope[1]/100);
//		display_ASCIIstring_8x16(7,91,zifu_dian);
		
//		xianshishuju(I_I_Array_xianshi[0]);          	
//		display_ASCIIstring_8x16(3,91,zifu_dian);//����ʵʱADֵ		
//		xianshishuju(I_I_Array_xianshi[1]);
//		display_ASCIIstring_8x16(5,91,zifu_dian);			
//		xianshishuju(I_I_Array_xianshi[2]);
//		display_ASCIIstring_8x16(7,91,zifu_dian);
		
//	}

//	else if (temp_s==4)
//	{
//		clear_screen();
//		Lcd12864_Write16CnCHAR(0,16,0,"�й�����/kw");

//	 Lcd12864_Write16CnCHAR(0,0,2,"Pa:     kw");
//	 Lcd12864_Write16CnCHAR(0,0,4,"Pb:     kw\r");
//	 Lcd12864_Write16CnCHAR(0,0,6,"Pc:     kw\r");
//		

//	 xianshishuju1(nor_disp_num_buf[12]);          	//�й�������
//	 display_ASCIIstring_8x16(3,29,zifu_dian);//29
//   display_graphic_8x16(3,53,dian);//36
//   display_ASCIIstring_8x16(3,60,&zifu_dian[3]);//44
//		

//	 xianshishuju1(nor_disp_num_buf[13]);          	
//	 display_ASCIIstring_8x16(5,29,zifu_dian);
//   display_graphic_8x16(5,53,dian);
//   display_ASCIIstring_8x16(5,60,&zifu_dian[3]);
//	 

//	 xianshishuju1(nor_disp_num_buf[14]);          	
//	 display_ASCIIstring_8x16(7,29,zifu_dian);
//   display_graphic_8x16(7,53,dian);
//   display_ASCIIstring_8x16(7,60,&zifu_dian[3]);

//		
//	}
//		else if (temp_s==5)
//	{
//		clear_screen();
//		Lcd12864_Write16CnCHAR(0,16,0,"����ϵ��/P_F");

//	 Lcd12864_Write16CnCHAR(0,0,2,"PFa:   ");
//	 Lcd12864_Write16CnCHAR(0,0,4,"PFb:   ");
//	 Lcd12864_Write16CnCHAR(0,0,6,"PFc:   ");
//		
//	 xianshishuju1(nor_disp_num_buf[9]);          	//����ϵ������

//	 display_ASCIIstring_8x16(3,40,zifu_dian);
//   display_graphic_8x16(3,47,dian);	 
//   display_ASCIIstring_8x16(3,55,&zifu_dian[1]);
//		
//	 xianshishuju1(nor_disp_num_buf[10]);          	
//	 display_ASCIIstring_8x16(5,40,zifu_dian);
//   display_graphic_8x16(5,47,dian); 
//   display_ASCIIstring_8x16(5,55,&zifu_dian[1]);
//	 
//	 xianshishuju1(nor_disp_num_buf[11]);          	
//	 display_ASCIIstring_8x16(7,40,zifu_dian); 
//   display_graphic_8x16(7,47,dian); 
//   display_ASCIIstring_8x16(7,55,&zifu_dian[1]);
//		
//	}	

}	
	

void long_key_process(unsigned char key_tmp)
{
		if(key_tmp==0x01)//У��0.5-1.5֮��
		{	

			clear_screen();
			Lcd12864_Write16CnCHAR(0,32,0,"����У׼\r\r  ©��У׼:");		
			F_cal = 1;
			Cal_state = 0;
			F_sssj=3;
    	F_key=9;			

	 }

}

unsigned char get_key(void)
{
    
}

unsigned char Read_key(void)
{
    if(key_flag==0)
    {
        if(get_key()!=0x00)
        {
						key_flag=1 ;
            return 0 ;
        }
        else 
        {
            key_connter=0 ;
            key_flag=0 ;
            return 0 ;
        }
    }
    else 
    {
        if(get_key()!=0x00)
        {
            key_connter++;
            key_value_tmp=get_key();
            return 0 ;
        }
        else 
        {
            key_flag=0 ;
            if(key_connter<1)
            {
                key_connter=0 ;
                return 0 ;
            }
						else if(key_connter>=1)
						{
							  key_connter=0 ;
								F_nokey = 0;
								T_64_10s = 0;
                return key_value_tmp ;
						}
						
            else
						{
                key_connter=0 ;
                return 0 ;
            }
        }
    }
}
void Cur250_calibrate_tmp(void)
{
	unsigned char array_tmp[24];
	array_tmp[0]=0xAB;
	array_tmp[1]=0x01;
	array_tmp[2]=0x2C;
	array_tmp[3]=0x0A;
	array_tmp[4]=0xF3;
	array_tmp[5]=0x14;
	array_tmp[6]=0x48;
	array_tmp[7]=0x7D;		
	
	array_tmp[8]=0x5D;
	array_tmp[9]=0x03;
	array_tmp[10]=0xF6;
	array_tmp[11]=0x0B;
	array_tmp[12]=0x73;
	array_tmp[13]=0x16;
	array_tmp[14]=0x11;
	array_tmp[15]=0x7F;	
	
	array_tmp[16]=0x6A;
	array_tmp[17]=0x02;
	array_tmp[18]=0xE7;
	array_tmp[19]=0x0A;
	array_tmp[20]=0x61;
	array_tmp[21]=0x15;
	array_tmp[22]=0x96;
	array_tmp[23]=0x7D;
	MODIFY_EEP_W(Addr_Cur_250,array_tmp,24,0xA0);
	delay_ms(5);
	array_tmp[0]=0x5E;
	array_tmp[1]=0x09;
	array_tmp[2]=0x8D;
	array_tmp[3]=0x07;
	array_tmp[4]=0x3F;
	array_tmp[5]=0x07;
	array_tmp[6]=0x7C;
	array_tmp[7]=0x07;	
	
	array_tmp[8]=0xA5;
	array_tmp[9]=0x04;
	array_tmp[10]=0x54;
	array_tmp[11]=0x07;
	array_tmp[12]=0x72;
	array_tmp[13]=0x07;
	array_tmp[14]=0x77;
	array_tmp[15]=0x07;	
	
	array_tmp[16]=0x78;
	array_tmp[17]=0x06;
	array_tmp[18]=0x67;
	array_tmp[19]=0x07;
	array_tmp[20]=0x75;
	array_tmp[21]=0x07;
	array_tmp[22]=0x7F;
	array_tmp[23]=0x07;	
	MODIFY_EEP_W(Addr_Cur_slope_250,array_tmp,24,0xA0);
	delay_ms(5);
	array_tmp[0]=0x45;
	array_tmp[1]=0x0A;
	array_tmp[2]=0x4B;
	array_tmp[3]=0x5D;
	MODIFY_EEP_W(Addr_Leak_ad,array_tmp,4,0xA0);
	delay_ms(5);
	array_tmp[0]=0x64;
	array_tmp[1]=0x09;
	array_tmp[2]=0x59;
	array_tmp[3]=0x0A;		
	MODIFY_EEP_W(Addr_Leak_slope,array_tmp,4,0xA0);
	delay_ms(5);
}
void Cur400_630_calibrate_tmp(void)
{
	unsigned char array_tmp[24];
	array_tmp[0]=0xAA;
	array_tmp[1]=0x02;
	array_tmp[2]=0x60;
	array_tmp[3]=0x07;
	array_tmp[4]=0xDD;
	array_tmp[5]=0x0C;
	array_tmp[6]=0x68;
	array_tmp[7]=0x44;		

	array_tmp[8]=0x7B;
	array_tmp[9]=0x03;
	array_tmp[10]=0xF8;
	array_tmp[11]=0x07;
	array_tmp[12]=0x9E;
	array_tmp[13]=0x0D;
	array_tmp[14]=0xFA;
	array_tmp[15]=0x44;	
	
	array_tmp[16]=0x5A;
	array_tmp[17]=0x02;
	array_tmp[18]=0xDD;
	array_tmp[19]=0x06;
	array_tmp[20]=0x60;
	array_tmp[21]=0x0C;
	array_tmp[22]=0x69;
	array_tmp[23]=0x44;
	MODIFY_EEP_W(Addr_Cur_250,array_tmp,24,0xA0);
	delay_ms(5);
	array_tmp[0]=0xDD;
	array_tmp[1]=0x05;
	array_tmp[2]=0x44;
	array_tmp[3]=0x0D;
	array_tmp[4]=0x3C;
	array_tmp[5]=0x0E;
	array_tmp[6]=0x10;
	array_tmp[7]=0x0E;		

	array_tmp[8]=0x7D;
	array_tmp[9]=0x04;
	array_tmp[10]=0xEC;
	array_tmp[11]=0x0D;
	array_tmp[12]=0xD4;
	array_tmp[13]=0x0D;
	array_tmp[14]=0x1C;
	array_tmp[15]=0x0E;	
	
	array_tmp[16]=0xA4;
	array_tmp[17]=0x06;
	array_tmp[18]=0xDA;
	array_tmp[19]=0x0D;
	array_tmp[20]=0x2C;
	array_tmp[21]=0x0E;
	array_tmp[22]=0xF1;
	array_tmp[23]=0x0D;
	MODIFY_EEP_W(Addr_Cur_slope_250,array_tmp,24,0xA0);
	delay_ms(5);
	array_tmp[0]=0xA2;
	array_tmp[1]=0x10;
	array_tmp[2]=0x1D;
	array_tmp[3]=0xAA;
	MODIFY_EEP_W(Addr_Leak_ad,array_tmp,4,0xA0);
	delay_ms(5);
	array_tmp[0]=0x52;
	array_tmp[1]=0x05;
	array_tmp[2]=0x99;
	array_tmp[3]=0x05;		
	MODIFY_EEP_W(Addr_Leak_slope,array_tmp,4,0xA0);
	delay_ms(5);
}
void Ld_function_process(void)
{
    unsigned char array_tmp[3];
    if((key_state==0x11100)||(key_state==0x11101))//©��澯
    {
        F_trip_ld=((key_state)&0x01);//ȡ����־λ
        if(F_trip_ld==0)ctrlword[3]&=0xFC ;//�����ַ���
        if(F_trip_ld==1)
        {
            ctrlword[3]&=0xFC ;
            ctrlword[3]+=0x02 ;
        }
        array_tmp[0]=ctrlword[3];

        MODIFY_EEP_W(Addr_crtl_word4,array_tmp,1,0xA0);//�洢
				ctrlword4_analyze();
        F_ent=1 ;
//				key_state=0x1100;
    }
    if((key_state>=0x12100)&&(key_state<=0x12106))//�©��
    {
        D_LCur=((key_state)&0x0F);
        ctrlword[3]&=0x0F ;
        ctrlword[3]+=(D_LCur<<4);
        array_tmp[0]=ctrlword[3];
        MODIFY_EEP_W(Addr_crtl_word4,array_tmp,1,0xA0);
				ctrlword4_analyze();
      
        F_ent=1 ;
    }
    if((key_state>=0x13100)&&(key_state<=0x13103))//�ֶ�ʱ��
    {
          TH_LCur=((key_state)&0x07);
//        ctrlword[3]&=0xF3 ;
//        ctrlword[3]+=(TH_LCur<<2);
//        array_tmp[0]=ctrlword[3];
//        MODIFY_EEP_W(Addr_crtl_word4,array_tmp,1,0xA0);
//				ctrlword4_analyze();
					array_tmp[0]=TH_LCur;
		      MODIFY_EEP_W(Addr_TH_LCur ,array_tmp,1,0xA0);
			
        F_ent=1 ;
    }
//		if((key_state>=0x14100)&&(key_state<=0x14101))//ͻ�䱣��
//		{
//				F_TB_trip=(key_state&0x01);
//		
//        if(F_TB_trip==1)	{array_tmp[0] = 0x01 ;F_Leak_Delay = 0;}
//        else if(F_TB_trip==0)	array_tmp[0] = 0x00;
//        else array_tmp[0] = 0x00;
//				MODIFY_EEP_W(Addr_L_TB,array_tmp,1);
//				F_ent=1 ;
//		}
		if((key_state>=0x14100)&&(key_state<=0x14103))//�غ�բ����
    {
        
				LC_N=((key_state)&0x03);
				
        ctrlword[4]&=0xFC ;
        ctrlword[4]+=LC_N;
        array_tmp[0]=ctrlword[4];
			
        MODIFY_EEP_W(Addr_crtl_word5,array_tmp,1,0xA0);
        F_ent=1 ;
    }
			if((key_state>=0x15100)&&(key_state<=0x15101))//ͻ�䱣��
			{
				F_TB_trip=(key_state&0x01);
		
        if(F_TB_trip==1)	{array_tmp[0] = 0x01 ;F_Leak_Delay = 0;}
        else if(F_TB_trip==0)	array_tmp[0] = 0x00;
        else array_tmp[0] = 0x00;
				MODIFY_EEP_W(Addr_L_TB,array_tmp,1,0xA0);

				F_ent=1 ;
			}
			if((key_state>=0x16100)&&(key_state<=0x16101))//©����
			{
			F_jiance=((key_state)&0x01);
						if(F_jiance==1)
		{
			array_tmp[0] = 0x01 ;
		}
		else if(F_jiance==0)
		{
			array_tmp[0] = 0x00 ;
		}
		else
		{
			array_tmp[0] = 0x00 ;		
		}
		
		F_ent=1 ;
	MODIFY_EEP_W(Addr_L_JC,array_tmp,1,0xA0);
			}
}

void Else_function_process(void)
{
    unsigned char array_tmp[1];
  if((key_state==0x61100)||(key_state==0x61101))                 //�ϵ��բ
	{
	      shangdian=(key_state&0x01);
        if(shangdian==1)	array_tmp[0] = 0x01;
        if(shangdian==0)	array_tmp[0] = 0x00;
        MODIFY_EEP_W(Addr_shangdian,array_tmp,1,0xA0);
				F_ent=1 ;
	}
//  if((key_state==0x62100)||(key_state==0x62101))                 //ͣ����բ
//	{
//	      duandian=(key_state&0x01);
//        if(duandian==1)	array_tmp[0] = 0x01 ;
//        if(duandian==0)	array_tmp[0] = 0x00;
//        MODIFY_EEP_W(Addr_duandian,array_tmp,1,0xA0);
//				F_ent=1 ;
//	}		
	if((key_state>=0x63100)&&(key_state<=0x63103))//������
    {

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
			
				
		//		Uart2_Init();			//lpb
	 }        
  }
if((key_state>=0x64100)&&(key_state<=0x64103))//
    {	
//				EEPROM_R(Addr_Type_Cur,array_temp,1);
			  array_tmp[0]=Type_cur_Temp;
//	        Type_Cur=array_temp[0];								
				MODIFY_EEP_W(Addr_Type_Cur,array_tmp,1,0xA0);
				EEPROM_R(Addr_Type_Cur,array_tmp,1,0xA0);
		     Type_Cur=	array_tmp[0];
			if(Type_Cur==0)
			{
				if(Type_Cur_change==1) //3
				{
					D_Cur=9;
					array_tmp[0]=D_Cur ;
					MODIFY_EEP_W(Addr_D_Cur,array_tmp,1,0xA0);
				}
			}
			else if(Type_Cur==1)
			{
				if(Type_Cur_change==1)//20
				{				
					D_Cur=19;
					array_tmp[0]=D_Cur ;
					MODIFY_EEP_W(Addr_D_Cur,array_tmp,1,0xA0);
				}
//				Cur250_calibrate_tmp(); 
			}
			else if(Type_Cur==2)
			{
				if(Type_Cur_change==1)//11  20201201���л��Ǽܵ�λΪ���ֵ
				{
					D_Cur=12;
					array_tmp[0]=D_Cur ;
					MODIFY_EEP_W(Addr_D_Cur,array_tmp,1,0xA0);
				}
//				Cur400_630_calibrate_tmp(); 
			}
			else if(Type_Cur==3)
			{
				if(Type_Cur_change==1)//15
				{				
					D_Cur=14;
					array_tmp[0]=D_Cur;
					MODIFY_EEP_W(Addr_D_Cur,array_tmp,1,0xA0);
				}
//				Cur400_630_calibrate_tmp(); 
			}
			else if(Type_Cur==4)
			{
				if(Type_Cur_change==1)//15
				{				
					D_Cur=6;
					array_tmp[0]=D_Cur;
					MODIFY_EEP_W(Addr_D_Cur,array_tmp,1,0xA0);
				}
//				Cur400_630_calibrate_tmp(); 
			}
//			MODIFY_EEP_W(Addr_D_Cur,array_tmp,1);
			Read_Cur_calibrae_data();
			Cur_Switch(Type_Cur);
    }
if((key_state>=0x65100)&&(key_state<=0x65109))//
    {	
				self_addr_code[0]=self_addr_code[0];
				self_addr_code[1]=self_addr_code[1] ;
				self_addr_code[2]=self_addr_code[2];
				self_addr_code[3]=self_addr_code[3] ;
				self_addr_code[4]=self_addr_code[4];
				self_addr_code[5]=self_addr_code_temp[5] ;											//lpb,�豸�ϵ��Զ��ظ���ʼ��ַ
				MODIFY_EEP_W(Addr_dev_addr,self_addr_code,Lenth_dev_addr,0xA0);
    }
		  if((key_state>=0x66100)&&(key_state<=0x66109))//
    {	
				self_addr_code[0]=self_addr_code[0];
				self_addr_code[1]=self_addr_code[1] ;
				self_addr_code[2]=self_addr_code[2];
				self_addr_code[3]=self_addr_code[3] ;
				self_addr_code[4]=self_addr_code[4];
				self_addr_code[5]=self_addr_code_temp[5] ;											
				MODIFY_EEP_W(Addr_dev_addr,self_addr_code,Lenth_dev_addr,0xA0);
    }
		  if((key_state>=0x67100)&&(key_state<=0x67109))//
    {	
				self_addr_code[0]=self_addr_code[0];
				self_addr_code[1]=self_addr_code[1] ;
				self_addr_code[2]=self_addr_code[2];
				self_addr_code[3]=self_addr_code[3] ;
				self_addr_code[4]=self_addr_code_temp[4];
				self_addr_code[5]=self_addr_code[5] ;											
				MODIFY_EEP_W(Addr_dev_addr,self_addr_code,Lenth_dev_addr,0xA0);
    }
		  if((key_state>=0x68100)&&(key_state<=0x68109))//
    {	
				self_addr_code[0]=self_addr_code[0];
				self_addr_code[1]=self_addr_code[1] ;
				self_addr_code[2]=self_addr_code[2];
				self_addr_code[3]=self_addr_code[3] ;
				self_addr_code[4]=self_addr_code_temp[4];
				self_addr_code[5]=self_addr_code[5] ;											
				MODIFY_EEP_W(Addr_dev_addr,self_addr_code,Lenth_dev_addr,0xA0);
    }
		  if((key_state>=0x69100)&&(key_state<=0x69109))//
    {	
				self_addr_code[0]=self_addr_code[0];
				self_addr_code[1]=self_addr_code[1] ;
				self_addr_code[2]=self_addr_code[2];
				self_addr_code[3]=self_addr_code_temp[3] ;
				self_addr_code[4]=self_addr_code[4];
				self_addr_code[5]=self_addr_code[5] ;											
				MODIFY_EEP_W(Addr_dev_addr,self_addr_code,Lenth_dev_addr,0xA0);
    }
		  if((key_state>=0x6a100)&&(key_state<=0x6a109))//
    {	
				self_addr_code[0]=self_addr_code[0];
				self_addr_code[1]=self_addr_code[1] ;
				self_addr_code[2]=self_addr_code[2];
				self_addr_code[3]=self_addr_code_temp[3] ;
				self_addr_code[4]=self_addr_code[4];
				self_addr_code[5]=self_addr_code[5] ;											
				MODIFY_EEP_W(Addr_dev_addr,self_addr_code,Lenth_dev_addr,0xA0);
    }
		  if((key_state>=0x6b100)&&(key_state<=0x6b109))//
    {	
				self_addr_code[0]=self_addr_code[0];
				self_addr_code[1]=self_addr_code[1] ;
				self_addr_code[2]=self_addr_code_temp[2];
				self_addr_code[3]=self_addr_code[3] ;
				self_addr_code[4]=self_addr_code[4];
				self_addr_code[5]=self_addr_code[5] ;											
				MODIFY_EEP_W(Addr_dev_addr,self_addr_code,Lenth_dev_addr,0xA0);
    }
		  if((key_state>=0x6c100)&&(key_state<=0x6c109))//
    {	
				self_addr_code[0]=self_addr_code[0];
				self_addr_code[1]=self_addr_code[1] ;
				self_addr_code[2]=self_addr_code_temp[2];
				self_addr_code[3]=self_addr_code[3] ;
				self_addr_code[4]=self_addr_code[4];
				self_addr_code[5]=self_addr_code[5] ;											
				MODIFY_EEP_W(Addr_dev_addr,self_addr_code,Lenth_dev_addr,0xA0);
    }
		  if((key_state>=0x6d100)&&(key_state<=0x6d109))//
    {	
				self_addr_code[0]=self_addr_code[0];
				self_addr_code[1]=self_addr_code_temp[1] ;
				self_addr_code[2]=self_addr_code[2];
				self_addr_code[3]=self_addr_code[3] ;
				self_addr_code[4]=self_addr_code[4];
				self_addr_code[5]=self_addr_code[5] ;											
				MODIFY_EEP_W(Addr_dev_addr,self_addr_code,Lenth_dev_addr,0xA0);
    }
		  if((key_state>=0x6e100)&&(key_state<=0x6e109))//
    {	
				self_addr_code[0]=self_addr_code[0];
				self_addr_code[1]=self_addr_code_temp[1] ;
				self_addr_code[2]=self_addr_code[2];
				self_addr_code[3]=self_addr_code[3] ;
				self_addr_code[4]=self_addr_code[4];
				self_addr_code[5]=self_addr_code[5] ;											
				MODIFY_EEP_W(Addr_dev_addr,self_addr_code,Lenth_dev_addr,0xA0);
    }
		  if((key_state>=0x73100)&&(key_state<=0x73109))//
    {	
				self_addr_code[0]=self_addr_code_temp[0];
				self_addr_code[1]=self_addr_code[1] ;
				self_addr_code[2]=self_addr_code[2];
				self_addr_code[3]=self_addr_code[3] ;
				self_addr_code[4]=self_addr_code[4];
				self_addr_code[5]=self_addr_code[5] ;											
				MODIFY_EEP_W(Addr_dev_addr,self_addr_code,Lenth_dev_addr,0xA0);
    }
		  if((key_state>=0x74100)&&(key_state<=0x74109))//
    {	
				self_addr_code[0]=self_addr_code_temp[0];
				self_addr_code[1]=self_addr_code[1] ;
				self_addr_code[2]=self_addr_code[2];
				self_addr_code[3]=self_addr_code[3] ;
				self_addr_code[4]=self_addr_code[4];
				self_addr_code[5]=self_addr_code[5] ;											
				MODIFY_EEP_W(Addr_dev_addr,self_addr_code,Lenth_dev_addr,0xA0);
    }
//		  if((key_state==0x74100)||(key_state==0x74101))                 //�ϵ��բ
//	{
//	      F_data_clear=(key_state&0x01);
//        if(F_data_clear==1)	
//        {
//					array_tmp[0] = 0x01 ;
////					MODIFY_EEP_W(Addr_data_clear,array_tmp,1);
////					data_clear();
//				}
//        if(F_data_clear==0)	array_tmp[0] = 0x00;
//        MODIFY_EEP_W(Addr_data_clear,array_tmp,1);
//	}
//////////////		if((key_state==0x71100)||(key_state==0x71101))                 //У׼��λѡ��
//////////////	{
//////////////	      jiaozhun=(key_state&0x01);
//////////////        if(jiaozhun==1)	
//////////////				{
//////////////					array_tmp[0] = 0x01;//T
//////////////		      F_Corr=1;
//////////////				}
//////////////        if(jiaozhun==0)
//////////////				{
//////////////					array_tmp[0] = 0x00;//K
//////////////		      F_Corr=0;
//////////////				}
//////////////        MODIFY_EEP_W(Addr_jiaozhun,array_tmp,1,0xA0);
//////////////				F_ent=1 ;
//////////////	}
}


void Dy_function_process(void)
{
    unsigned char array_tmp[1];
	  if((key_state==0x21100)||(key_state==0x21101))//ʧѹ����
		{
		F_trip_sy=((key_state)&0x01);
		array_tmp[0]=F_trip_sy;
		MODIFY_EEP_W(Addr_SY_F,array_tmp,1,0xA0);
		F_ent=1 ;
		}
		if((key_state==0x22100)||(key_state==0x22101))// ȱ�ౣ��
    {
        F_trip_QX=(key_state&0x01);
        if(F_trip_QX==1)	ctrlword[1]|=0x04 ; 
        if(F_trip_QX==0)	ctrlword[1]&=(~0x04);
//        MODIFY_EEP_W(Addr_QX_BAOHU,array_tmp,1);
			array_tmp[0]=ctrlword[1];
			MODIFY_EEP_W(Addr_crtl_word2,array_tmp,1,0xA0);
				F_ent=1 ;
    }
				
		if((key_state==0x23100)||(key_state==0x23101))//��ѹ����
    {
        F_trip_gy=((key_state)&0x01);
        if(F_trip_gy==1)ctrlword[1]|=0x10 ;
        if(F_trip_gy==0)ctrlword[1]&=(~0x10);
        array_tmp[0]=ctrlword[1];
        MODIFY_EEP_W(Addr_crtl_word2,array_tmp,1,0xA0);
        F_ent=1 ;
        
    }
		if((key_state==0x24100)||(key_state==0x24101))//Ƿѹ����
    {
        F_trip_qy=((key_state)&0x01);
        if(F_trip_qy==1)ctrlword[1]|=0x40 ;
        if(F_trip_qy==0)ctrlword[1]&=(~0x40);
        array_tmp[0]=ctrlword[1];
        MODIFY_EEP_W(Addr_crtl_word2,array_tmp,1,0xA0);
        F_ent=1 ;
		
    }
			if((key_state>=0x25100)&&(key_state<=0x25105))   //��ѹ��λ
	{
		Vol_g=((key_state)&0x07);
		array_tmp[0]=Vol_g ;
		MODIFY_EEP_W(Addr_Vol_g,array_tmp,1,0xA0);
		F_ent=1 ;
	}
	    if((key_state>=0x26100)&&(key_state<=0x26105))   //Ƿѹ��λ
    {
        Vol_q=((key_state)&0x07);
        array_tmp[0]=Vol_q ;
        MODIFY_EEP_W(Addr_Vol_q,array_tmp,1,0xA0);
        F_ent=1 ;
    }
			if((key_state>=0x27100)&&(key_state<=0x27109))   //ʧѹ��ʱ
	{
		D_SY_yanshi=((key_state)&0x0F);
		array_tmp[0]=D_SY_yanshi ;
		MODIFY_EEP_W(Addr_SY_yanshi,array_tmp,1,0xA0);
		F_ent=1 ;
	}
		 if((key_state>=0x28100)&&(key_state<=0x28109))//��ѹ��λ��ʱ
    {
        D_GY_yanshi=((key_state)&0x0F);//0000 01111
        array_tmp[0]=D_GY_yanshi ;
        MODIFY_EEP_W(Addr_GY_yanshi,array_tmp,1,0xA0);
				F_ent=1 ;
    }
		 if((key_state>=0x29100)&&(key_state<=0x29109))//Ƿѹ��λ��ʱ
    {
        D_QY_yanshi=((key_state)&0x0F);//0000 01111
        array_tmp[0]=D_QY_yanshi ;
        MODIFY_EEP_W(Addr_QY_yanshi,array_tmp,1,0xA0);
				F_ent=1 ;
    }
		 if((key_state==0x2a100)||(key_state==0x2a101))// ���㱣��
    {
        F_trip_QL=(key_state&0x01);
        if(F_trip_QL==1)	ctrlword[2]|=0x01 ;
        if(F_trip_QL==0)	ctrlword[2]&=(~0x01);
//        MODIFY_EEP_W(Addr_QL_BAOHU,array_tmp,1);
			        array_tmp[0]=ctrlword[2];
        MODIFY_EEP_W(Addr_crtl_word3,array_tmp,1,0xA0);
				F_ent=1 ;
    }
		if((key_state==0x2b100)||(key_state==0x2b101))  // ��ѹ�غ�
    {
        F_dianya_chonghe=(key_state&0x01);
        if(F_dianya_chonghe==1)	array_tmp[0] = 0x01 ;
        if(F_dianya_chonghe==0)	array_tmp[0] = 0x00;
        MODIFY_EEP_W(Addr_DIANYA_chonghe,array_tmp,1,0xA0);
				F_ent=1 ;
    }
				if((key_state>=0x2c100)&&(key_state<=0x2c105))   //ȱ�㵵λ
			{
				Vol_up=((key_state)&0x07);
				array_tmp[0]=Vol_up ;
				MODIFY_EEP_W(Addr_QL_BAOHU,array_tmp,1,0xA0);
				F_ent=1 ;
			}
	    if((key_state>=0x2d100)&&(key_state<=0x2d106))   //ȱ�㵵λ
			{
					Vol_down=((key_state)&0x07);
					array_tmp[0]=Vol_down ;
					MODIFY_EEP_W(Addr_QX_BAOHU,array_tmp,1,0xA0);
					F_ent=1 ;
			}
//    if((key_state==0x1D100)||(key_state==0x1D101))//��ѹ����
//    {
//        F_trip_gy=((key_state)&0x01);
//        if(F_trip_gy==1)ctrlword[1]|=0x10 ;
//        if(F_trip_gy==0)ctrlword[1]&=(~0x10);
//        array_tmp[0]=ctrlword[1];
//        MODIFY_EEP_W(Addr_crtl_word2,array_tmp,1);
//        F_ent=1 ;
//        
//    }
//		 if((key_state>=0x1E100)&&(key_state<=0x1E104))//��ѹ��λ
//    {
//        Vol_g=((key_state)&0x07);//0000 01111
//        array_tmp[0]=Vol_g ;
//        MODIFY_EEP_W(Addr_Vol_g,array_tmp,1);
//				F_ent=1 ;
//    }
//		 if((key_state>=0x21100)&&(key_state<=0x21109))//��ѹ��λ��ʱ
//    {
//        D_GY_yanshi=((key_state)&0x0F);//0000 01111
//        array_tmp[0]=D_GY_yanshi ;
//        MODIFY_EEP_W(Addr_GY_yanshi,array_tmp,1);
//				F_ent=1 ;
//    }
//    if((key_state==0x22100)||(key_state==0x22101))//Ƿѹ����
//    {
//        F_trip_qy=((key_state)&0x01);
//        if(F_trip_qy==1)ctrlword[1]|=0x40 ;
//        if(F_trip_qy==0)ctrlword[1]&=(~0x40);
//        array_tmp[0]=ctrlword[1];
//        MODIFY_EEP_W(Addr_crtl_word2,array_tmp,1);
//        F_ent=1 ;
//		
//    }
//    if((key_state>=0x23100)&&(key_state<=0x23105))//Ƿѹ��λ
//    {
//        Vol_q=((key_state)&0x07);
//        array_tmp[0]=Vol_q ;
//        MODIFY_EEP_W(Addr_Vol_q,array_tmp,1);
//        F_ent=1 ;
//    }
//		 if((key_state>=0x24100)&&(key_state<=0x24109))//Ƿѹ��λ��ʱ
//    {
//        D_QY_yanshi=((key_state)&0x0F);//0000 01111
//        array_tmp[0]=D_QY_yanshi ;
//        MODIFY_EEP_W(Addr_QY_yanshi,array_tmp,1);
//				F_ent=1 ;
//    }
//		
//				 if((key_state==0x25100)||(key_state==0x25101))// ȱ�ౣ��
//    {
//        F_trip_QX=(key_state&0x01);
//        if(F_trip_QX==1)	array_tmp[0] = 0x01 ;
//        if(F_trip_QX==0)	array_tmp[0] = 0x00;
//        MODIFY_EEP_W(Addr_QX_BAOHU,array_tmp,1);
//				F_ent=1 ;
//    }
//					 if((key_state==0x26100)||(key_state==0x26101))// ȱ�ౣ��
//    {
//        F_trip_QL=(key_state&0x01);
//        if(F_trip_QL==1)	array_tmp[0] = 0x01 ;
//        if(F_trip_QL==0)	array_tmp[0] = 0x00;
//        MODIFY_EEP_W(Addr_QL_BAOHU,array_tmp,1);
//				F_ent=1 ;
//    }
//    
//					 if((key_state==0x27100)||(key_state==0x27101))// ȱ�ౣ��
//    {
//        shangdian=(key_state&0x01);
//        if(shangdian==1)	array_tmp[0] = 0x01 ;
//        if(shangdian==0)	array_tmp[0] = 0x00;
//        MODIFY_EEP_W(Addr_shangdian,array_tmp,1);
//				F_ent=1 ;
//    }
//					 if((key_state==0x28100)||(key_state==0x28101))//
//    {
//        duandian=(key_state&0x01);
//        if(duandian==1)	array_tmp[0] = 0x01 ;
//        if(duandian==0)	array_tmp[0] = 0x00;
//        MODIFY_EEP_W(Addr_duandian,array_tmp,1);
//				F_ent=1 ;
//    }
//				if((key_state>=0x29100)&&(key_state<=0x29103))//�غ�բ����
//    {
//				LC_N=((key_state)&0x0F);
//        ctrlword[4]&=0xFC ;
//        ctrlword[4]+=LC_N;
//        array_tmp[0]=ctrlword[4];
//        MODIFY_EEP_W(Addr_crtl_word5,array_tmp,1);
//        F_ent=1 ;
//    }
//				 if((key_state==0x2A100)||(key_state==0x2A101))// ȱ�ౣ��
//    {
//        F_dianya_chonghe=(key_state&0x01);
//        if(F_dianya_chonghe==1)	array_tmp[0] = 0x01 ;
//        if(F_dianya_chonghe==0)	array_tmp[0] = 0x00;
//        MODIFY_EEP_W(Addr_DIANYA_chonghe,array_tmp,1);
//				F_ent=1 ;
//    }
//				if((key_state==0x2B100)||(key_state==0x2B101))//�����غ�բ
//    {
//        F_ia=(key_state&0x01);
//        if(F_ia==1)	array_tmp[0] = 0x01 ;
//        if(F_ia==0)	array_tmp[0] = 0x00;
//        MODIFY_EEP_W(Addr_I_ia,array_tmp,1);
//				F_ent=1 ;
//    }
}

void Gl_function_process(void)
{
    unsigned char array_tmp[1];
	if((key_state==0x31100)||(key_state==0x31101))  //��������
    {
        F_trip_gl=(key_state&0x01);
        if(F_trip_gl==1)ctrlword[1]|=0x01 ;
        if(F_trip_gl==0)ctrlword[1]&=(~0x01);
        array_tmp[0]=ctrlword[1];
        MODIFY_EEP_W(Addr_crtl_word2,array_tmp,1,0xA0);
				F_ent=1 ;
    }
		if((key_state>=0x32100)&&(key_state<=0x32115))  //������λ     
    {
 				D_Cur=key_state-0x32100 ;
        array_tmp[0]=D_Cur ;
        MODIFY_EEP_W(Addr_D_Cur,array_tmp,1,0xA0);
				Cur_Switch(Type_Cur);
				F_ent=1 ;
		
    }
		 if((key_state>=0x33100)&&(key_state<=0x33104)) //����ʱ��    
		{
					TH_Long_Cur=key_state-0x33100 ;
					array_tmp[0]=TH_Long_Cur ;
					MODIFY_EEP_W(Addr_CurLong_Time,array_tmp,1,0xA0);
					Cur_Switch(Type_Cur);
					F_ent=1 ;
			
		}
		if((key_state==0x34100)||(key_state==0x34101))   //���ӱ��� 
    {
        F_ip=(key_state&0x01);
        if(F_ip==1)	array_tmp[0] = 0x01 ;
        if(F_ip==0)	array_tmp[0] = 0x00;
        MODIFY_EEP_W(Addr_I_2d,array_tmp,1,0xA0);
				F_ent=1 ;
    }
	 if((key_state>=0x35100)&&(key_state<=0x35105))   //���ӵ�λ     
			{
					D2_Cur=key_state-0x35100 ;
					array_tmp[0]=D2_Cur ;
					MODIFY_EEP_W(Addr_D2_Cur,array_tmp,1,0xA0);
					Cur_Switch(Type_Cur);
					F_ent=1 ;
			
			}	
			 if((key_state>=0x36100)&&(key_state<=0x36103))//����ʱ��     
			{
					TH_DL=key_state-0x36100 ;
					array_tmp[0]=TH_DL ;
					MODIFY_EEP_W(Addr_D2_Time,array_tmp,1,0xA0);
					Cur_Switch(Type_Cur);
					F_ent=1 ;
			
			}		
			 if((key_state==0x37100)||(key_state==0x37101))//˲������
    {
        F_ip_3=(key_state&0x01);
        if(F_ip_3==1)	array_tmp[0] = 0x01 ;
        if(F_ip_3==0)	array_tmp[0] = 0x00;
        MODIFY_EEP_W(Addr_I_3d,array_tmp,1,0xA0);
				F_ent=1 ;
    }
		if((key_state>=0x38100)&&(key_state<=0x38105))   //����ʱ��     
			{
					D3_Cur=key_state-0x38100 ;
					array_tmp[0]=D3_Cur ;
					MODIFY_EEP_W(Addr_D3_Cur,array_tmp,1,0xA0);
					Cur_Switch(Type_Cur);
					F_ent=1 ;
			
			}		
				if((key_state==0x39100)||(key_state==0x39101))//�����غ�բ
    {
        F_ia=(key_state&0x01);
        if(F_ia==1)	array_tmp[0] = 0x01 ;
        if(F_ia==0)	array_tmp[0] = 0x00;
        MODIFY_EEP_W(Addr_I_ia,array_tmp,1,0xA0);
				F_ent=1 ;
    }
}			
			

unsigned char GZ_re_disp (unsigned char re)
{
		if(re==trip_reason_undervoltage)//Ƿѹ����
		{

			return 0;
		}
		//��ѹ��GY��
		else if(re ==trip_reason_overvoltage )
		{

			return 1;
		}
		//©�硰ld��
		else if(re ==trip_reason_leak)
		{

			return 2;
		}
		//������GL��
		else if(re ==trip_reason_cur)
		{

			return 3;
		}
		//ͣ�硰tD��
		else if(re==trip_reason_powerdown)
		{

			return 4;
		}
		//�ֶ��Ͷ�·Ϊδ֪��UN��
		else if(re==trip_reason_hand)
		{

			return 5;
		}
		//������AJ��
		else if(re==trip_reason_key)
		{

			return 6;
		}
		//Զ�̡�YC��
		else if(re==trip_reason_remote)
		{

			return 7;
		}
		else if(re==trip_reason_phase)//ȱ�����
		{
			return 9;
		}
		else if(re==trip_reason_zero)//ȱ�����
		{
			return 10;
		}
		else if(re==trip_reason_short)//���ӹ���
		{
			return 11;
		}
		else if(re==trip_reason_3D_cur)//˲������
		{
			return 12;
		}
		else if(re==trip_reason_lowvoltage)//ʧѹ����
		{
			return 13;
		}
		else 
		{

			return 8;
		}
		


}

		unsigned int point_tmp,tmp;
void Get_record(unsigned int tmp1)
{
	 	
	
			tmp = tmp1;
	
//		if((point_event_trip-1)>=0)  point_tmp = point_event_trip-1;
//		if(point_tmp>=tmp)
//		{
//			point_tmp = point_tmp - tmp;
//		}
//		else
//		{
//			point_tmp = point_tmp - tmp+20;
//		}
	if(point_event_trip+tmp<20)
	{
		point_tmp=point_event_trip+tmp;
	}
	else
	{
		point_tmp=point_event_trip+tmp-20;
	}

//		if(point_tmp<=9)
//		{
			EEPROM_R((9*point_tmp),record_array,9,0xA0);
//			
//		}
//		if(point_tmp>9)
//		{
//			EEPROM_R((10*(point_tmp-10)),record_array,10,0xA0);	

//		}
		
}

void Ls_function_process(void)
{

		unsigned char  array_temp[10];
		unsigned int  tmp;
	if((key_state>=0x41100)&&(key_state<=0x41120))	
		{
			
				tmp = key_state - 0x41100;

				generate_chuan(lishijilu_1,0,0,(tmp+1)/10,(tmp+1)%10);   //15,7,23,��
			
				Get_record(tmp);

				shijian_tiaozheng(nian,record_array[6]>>4,record_array[6]&0x0F);//�����ǿ��Ե���ʱ�䣬���ǽ���ʱ�䴦����п�����ʾ������
			
				shijian_tiaozheng(yue,record_array[5]>>4,record_array[5]&0x0F);						
			
				shijian_tiaozheng(ri,record_array[4]>>4,record_array[4]&0x0F);

				shijian_tiaozheng(shi,record_array[3]>>4,record_array[3]&0x0F);
				
				shijian_tiaozheng(fen,record_array[2]>>4,record_array[2]&0x0F);

				shijian_tiaozheng(miao,record_array[1]>>4,record_array[1]&0x0F);

				guzhang_wei=GZ_re_disp(record_array[0]);//9������λ
		
			   generate_chuan(lishijilu_2,record_array[8]>>4,record_array[8]&0x0F,record_array[7]>>4,record_array[7]&0x0F);

		}
	  if((key_state>=0x42100)&&(key_state<=0x42106))	
//    if((key_state>=0x4100)&&(key_state<=0x4102))
    {

				if(key_state==0x42100)
				{
					 
					EEPROM_R(Addr_trip_num,array_temp,3,0xA0);                    	//	����բ����
					generate_chuan(lishijilu_1,array_temp[1]>>4,array_temp[1]&0x0F,array_temp[0]>>4,array_temp[0]&0x0F); 
						
					EEPROM_R(Addr_clear_num,array_temp,3,0xA0);                    	//	�����������
				generate_chuan(lishijilu_2,array_temp[1]>>4,array_temp[1]&0x0F,array_temp[0]>>4,array_temp[0]&0x0F); 	
					
				}
				if(key_state==0x42101)
				{
					EEPROM_R(Addr_close_num,array_temp,3,0xA0);
//				EEPROM_R(Addr_vol_num,array_temp,3);                    	//	������բ����
				generate_chuan(lishijilu_1,array_temp[1]>>4,array_temp[1]&0x0F,array_temp[0]>>4,array_temp[0]&0x0F); 
					
				EEPROM_R(Addr_leak_num,array_temp,3,0xA0);	
//				EEPROM_R(Addr_current_num,array_temp,3);                  //©����բ����
				generate_chuan(lishijilu_2,array_temp[1]>>4,array_temp[1]&0x0F,array_temp[0]>>4,array_temp[0]&0x0F);  
	
			
				}
				if(key_state==0x42102)
				{ 
//				EEPROM_R(Addr_hand_num,array_temp,3);                     //������բ����
					EEPROM_R(Addr_current_num,array_temp,3,0xA0);
				generate_chuan(lishijilu_1,array_temp[1]>>4,array_temp[1]&0x0F,array_temp[0]>>4,array_temp[0]&0x0F);	                        //�ϵ���բ����
				
				  EEPROM_R(Addr_vol_num,array_temp,3,0xA0);	
//				EEPROM_R(Addr_zero_num,array_temp,3);                     //��ѹ��բ����           	//	
				generate_chuan(lishijilu_2,array_temp[1]>>4,array_temp[1]&0x0F,array_temp[0]>>4,array_temp[0]&0x0F); 		

				}
//					if(key_state==0x42103)
//				{
//        EEPROM_R(Addr_test_num,array_temp,3);                     //������բ���� 
//				generate_chuan(lishijilu_1,array_temp[1]>>4,array_temp[1]&0x0F,array_temp[0]>>4,array_temp[0]&0x0F);                                                         //ʧѹ��բ���� 
//				EEPROM_R(Addr_hand_num,array_temp,3);                     //�ֶ�������բ����
//				generate_chuan(lishijilu_2,array_temp[1]>>4,array_temp[1]&0x0F,array_temp[0]>>4,array_temp[0]&0x0F); 	
//				}
         if(key_state==0x42103)
				 {
				EEPROM_R(Addr_hand_num,array_temp,3,0xA0);                     //�ֶ�������բ����
				generate_chuan(lishijilu_1,array_temp[1]>>4,array_temp[1]&0x0F,array_temp[0]>>4,array_temp[0]&0x0F);	
				EEPROM_R(Addr_test_num,array_temp,3,0xA0);	
//				EEPROM_R(Addr_zero_num,array_temp,3);                    //������բ����           	
				generate_chuan(lishijilu_2,array_temp[1]>>4,array_temp[1]&0x0F,array_temp[0]>>4,array_temp[0]&0x0F); 
				 }
				 if(key_state==0x42104)
				 {
				EEPROM_R(Addr_2D_num,array_temp,3,0xA0);                     //��·������բ����
				generate_chuan(lishijilu_1,array_temp[1]>>4,array_temp[1]&0x0F,array_temp[0]>>4,array_temp[0]&0x0F);	
				EEPROM_R(Addr_3D_num,array_temp,3,0xA0);	
//				EEPROM_R(Addr_zero_num,array_temp,3);                    //��·˲ʱ��բ����           	
				generate_chuan(lishijilu_2,array_temp[1]>>4,array_temp[1]&0x0F,array_temp[0]>>4,array_temp[0]&0x0F); 	 
				 }
				 if(key_state==0x42105)
				 {
				EEPROM_R(Addr_leakover_num,array_temp,2,0xA0);	                    //ʣ��������޴���
			  generate_chuan(lishijilu_1,0,0,array_temp[0]>>4,array_temp[0]&0x0F); 	 
					 
				EEPROM_R(Addr_leakprotect_num,array_temp,2,0xA0);                     //�Լ����
				generate_chuan(lishijilu_2,0,0,array_temp[0]>>4,array_temp[0]&0x0F);
				 }
//				 if(key_state==0x42106)
//				 {
//				EEPROM_R(Addr_leakprotect_num,array_temp,3);	                                                            //ʣ����������˳���������
//			  generate_chuan(lishijilu_1,array_temp[1]>>4,array_temp[1]&0x0F,array_temp[0]>>4,array_temp[0]&0x0F);
//				EEPROM_R(Addr_leakchange_num,array_temp,3);                      //ʣ������仯����
//				generate_chuan(lishijilu_2,array_temp[1]>>4,array_temp[1]&0x0F,array_temp[0]>>4,array_temp[0]&0x0F);					 
//				 }
    }
    if((key_state>=0x43100)&&(key_state<=0x43114))	
		{
//			if(NUM_test1==0)
//			{
//				NUM_test=0;
//			}
//			else
//			{
//				tmp= key_state - 0x43100;
//				Get_record(tmp);
//			  guzhang_wei=GZ_re_disp(record_array[0]);//9������λ
//			if(key_value_tmp==0x01)
//			{
//			while(guzhang_wei!=6)
//			{
//				key_state++;
//				tmp = key_state - 0x43100;
//				Get_record(tmp);
//			  guzhang_wei=GZ_re_disp(record_array[0]);//9������λ
//					if(key_state==0x43113) 
//					{
//						key_state=0x43100;
//						tmp= key_state - 0x43100;
//				    Get_record(tmp);
//			      guzhang_wei=GZ_re_disp(record_array[0]);//9������λ
//						
//						break;
//					}
//				}	
//			
//		  }
//		  
//			if(key_value_tmp==0x80)
//			{
//			while(guzhang_wei!=6)
//			 {
//				
//				key_state--;
//				tmp = key_state - 0x43100;
//				Get_record(tmp);
//			  guzhang_wei=GZ_re_disp(record_array[0]);//9������λ
//				 if(key_state==0x43100)
//				 {
//         key_state=0x43113;
//				 tmp= key_state - 0x43100;
//				 Get_record(tmp);
//			   guzhang_wei=GZ_re_disp(record_array[0]);//9������λ
//				 break;
//				 }
//				 
//				 
//		   }
//	  	}
//			if((key_value_tmp==0x01)&&(guzhang_wei==6))	
//    {		 
//				shijian_tiaozheng(nian,record_array[6]>>4,record_array[6]&0x0F);//�����ǿ��Ե���ʱ�䣬���ǽ���ʱ�䴦����п�����ʾ������
//			
//				shijian_tiaozheng(yue,record_array[5]>>4,record_array[5]&0x0F);						
//			
//				shijian_tiaozheng(ri,record_array[4]>>4,record_array[4]&0x0F);

//				shijian_tiaozheng(shi,record_array[3]>>4,record_array[3]&0x0F);
//				
//				shijian_tiaozheng(fen,record_array[2]>>4,record_array[2]&0x0F);

//				shijian_tiaozheng(miao,record_array[1]>>4,record_array[1]&0x0F);
//		
//			  generate_chuan(lishijilu_2,record_array[8]>>4,record_array[8]&0x0F,record_array[7]>>4,record_array[7]&0x0F);
//				
//				NUM_test++;
//			if(NUM_test>NUM_test1)
//				NUM_test=1;
//			

//		}
//			else if((key_value_tmp==0x80)&&(guzhang_wei==6))
//    {		 
//			
//				shijian_tiaozheng(nian,record_array[6]>>4,record_array[6]&0x0F);//�����ǿ��Ե���ʱ�䣬���ǽ���ʱ�䴦����п�����ʾ������
//			
//				shijian_tiaozheng(yue,record_array[5]>>4,record_array[5]&0x0F);						
//			
//				shijian_tiaozheng(ri,record_array[4]>>4,record_array[4]&0x0F);

//				shijian_tiaozheng(shi,record_array[3]>>4,record_array[3]&0x0F);
//				
//				shijian_tiaozheng(fen,record_array[2]>>4,record_array[2]&0x0F);

//				shijian_tiaozheng(miao,record_array[1]>>4,record_array[1]&0x0F);
//		
//			   generate_chuan(lishijilu_2,record_array[8]>>4,record_array[8]&0x0F,record_array[7]>>4,record_array[7]&0x0F);
//				
//				NUM_test--;
//        if(NUM_test==0)
//				{
//					NUM_test=NUM_test1;				
//				}			
//				
//		}	
//	  }		
//		generate_chuan(lishijilu_1,0,0,(NUM_test)/10,(NUM_test)%10);


//			if(key_value_tmp==0x01)//�ϼ���
//				{
//					key_state++;

//				  if(key_state==0x43114) 				key_state=0x43100;
//					
//				}
//		  	if(key_value_tmp==0x80)//�¼���
//				{
//					key_state--;

//					if(key_state==0x430FF)
//					{
//						key_state=0x43114;
//					}

//				}



	}
}
void Sf_function_process(void)
{
	unsigned char array_tmp[2];
	if((key_state>=0x51000)&&(key_state<0x5F000))
	{
   RTC_Set_Time(tim_h3,tim_f3,tim_s3);
	 RTC_Set_Date(tim_y3,tim_m3,tim_d3);
	}
//	if((key_state>=0x51000)&&(key_state<=0x5F000))
//	{
//		array_tmp[0]=baud ;
//    MODIFY_EEP_W(Addr_baud,array_tmp,1); 
//		if(baud==3)
//		{
//			RS485_Init(9600);	
//		}
//		else if(baud==2)
//		{
//			RS485_Init(4800);	
//		}
//		else if(baud==1)
//		{
//			RS485_Init(2400);	
//		}
//		else if(baud==0)
//		{
//			RS485_Init(1200);	
//		}
////		Uart2_Init();			//lpb

//	}
}


void Sj_function_process()
{
	F_sssj = 1;
	sssj_N = 1;
	F_key = 0;
	F_Disp = 1;
}

unsigned char key_process(unsigned char key)
{
	 unsigned int temp_state_value,temp_state_value_1,tmp;

if(key==0x08)//���Ҳ��բ��
	{
		//ֻ�ں�բ״̬��������
		if(isfenzha==1)
		{
			F_fz=1 ;
			F_hz=0 ;
		}
	}
	//ֻ�ڷ�բ״̬��������
	if(key==0x04)  //S3
	{
		if((isfenzha==0)&&(F_key==0))//ֻ�ڷ�բ״̬�������ã�����û�ڸ������úͲ�ѯҳ��
		{
			F_fz=0 ;
			F_hz=1 ;
		}
	}
		//©����������
    if(key==0x02)
    {

			if(isfenzha!=0)
			{
				F_anolog_trip = 1;
				N_anolog_trip = 0;//û��
//				RELAY1 = 1;
			}
    }
		

		
		


		if((F_key == 0 )&&(key==0x10))//��բ��Ϣ
		{
			if(key == 0x10)//���
			{
			F_gz_disp=0x0f;//
			 F_key = 2 ;
			 key_state=0x00041100;
			 Ls_function_process();	

			}
			
			return 0;		
		}
		
		
		
		else if((F_key == 0 )&&(key==0x40))//��բ����
		{
			if(key == 0x40)//�Ҽ�
			{
			 F_gz_disp=0x0f;//
			 F_key = 3 ;
			 key_state=0x00042100;
			 Ls_function_process();	

			}
			
			return 0;		
		}
		
  else if((F_key == 0 )&&(key==0x01))//�Լ��ѯ
  {
   if(key == 0x01)//�ϼ�
   {
    F_gz_disp=0x0f;//
    F_key = 4 ;

    key_state=0x00043100;
    Ls_function_process(); 
   }
	
   return 0;  
  }
	
	
	 if (F_key ==4 )
	 {
		 
			if(key == 0x40)//�Ҽ�
			{
			 F_gz_disp=0x0f;//
			 F_key = 3 ;
			 key_state=0x00042100;
			 Ls_function_process();	
			}

		else if(key == 0x10)//���
			{
			F_gz_disp=0x0f;//
			 F_key = 2 ;
			 key_state=0x00041100;
			 Ls_function_process();	

			}
	  
	 }

	
	
	
		
		else if((F_key == 0 )&&(key==0x80))//���ܿ�������
		{
			if(key == 0x80)//�¼�
			{
			 F_gz_disp=0x0f;//������ʾ��־λ�������ֹ�ڳ��ֹ���ʱ���ܽ������ý���
			 F_key = 5 ;
			 key_state=0x00011100;
			}
			return 0;		
		}
		
		
		
		else if((F_key == 6 )&&(key==0x20))//����У��
		{
			if(key == 0x20)//ȷ����
			{
			   mima_check();
			 
			}
			return 0;		
		}
		
		
		
		if((F_key == 0 )&&(key==0x20)&&(F_gz_disp==0x0f))//��������,����(F_gz_disp==0x0f)�����ƣ����ڹ�����ʾʱ��ȷ����������������ʹ��
		{
			if(key == 0x20)//ȷ����
			{
			   check_reason=0x20;//����У��ԭ��
				
			 F_gz_disp=0x0f;//������ʾ��־λ�������ֹ�ڳ��ֹ���ʱ���ܽ������ý���
			 F_key = 6 ;
			 key_state=0x10000000;
			 
			}
			
			return 0;		
		}
		
			
		 if((F_key == 0 )&&(key==0x81)&&(F_gz_disp==0x0f))//��������,����(F_gz_disp==0x0f)�����ƣ����ڹ�����ʾʱ��ȷ����������������ʹ��
		{
			if(key == 0x81)
			{
			   check_reason=0x81;//����У��ԭ��
				
			 F_gz_disp=0x0f;//������ʾ��־λ�������ֹ�ڳ��ֹ���ʱ���ܽ������ý���
			 F_key = 6 ;
			 key_state=0x10000000;
			 
			}
			
			return 0;		
		}
		
			
		if((F_key == 6 )&&(key==0x81))//����У��
		{
			if(key == 0x81)//�ϼ���
			{
			   mima_check();
			}
			return 0;		
		}
		
			
	

    if((F_key==1)||(F_key==2)||(F_key==3)||(F_key==4)||(F_key==5)||(F_key==6)||(F_key==7)||(F_key==9))//(F_key==1)��բ��Ϣ��ѯҳ��,(F_key==2)���ý���,(F_key==3)��բ������ѯ,(F_key==5)�¼����ÿ��أ�(F_key==6)�����������,(F_key==7)��������ҳ��,(F_key==9)У׼ҳ�棬(F_key==8)��������
		{
				if(key==0x04)//��λ�����˳�ʹ��
				{
										 clear_screen();
					 F_key = 0 ;	    
           F_queren=1;//�������ý��棨F_key==7��ȷ�ϼ�������־
           NUM_test=0;//�Լ���բ����
		
					
						key_state=0x00000000;//��������ʱ����
						mima[0]=0;
						mima[1]=0;
						mima[2]=0;
						mima[3]=0;

					  F_sssj=0;//�˳�У׼ҳ��
					  F_cal=0;//�˳�У׼ҳ��
					return 0;		
				}		
		}

		
		
		


	
		if(F_cal==1)
		{
			
			  if(key==0x80)//�¼�
			{
				Cal_state ++;
				if(Cal_state==4)
				Cal_state = 0;	
			}
			  else	if(key==0x01)//�ϼ�
			{
				if(Cal_state>=1)
				{
					Cal_state --;
				}
				
			}
		else if(key ==0x20)
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
					/*
					  Vol1_A_temp=V_Array_disp[0];//V_Array_disp/V_Array
				  	V_A_factor_tmp= vol_handle_A(V_Array_disp[0])-Vol_cal_tmp;//A��ѹУ׼
						V1_slope[0]=(Vol_cal_tmp<<20)/(Vol1_A_temp);
						HexToChar(array_temp,V1_slope[0],2);
					  MODIFY_EEP_W(Addr_V1_A_slope,array_temp,2,0xA0);
					
						HexToChar(array_tmp,Vol1_A_temp,2);
						MODIFY_EEP_W(Addr_Vol1_A_temp,array_tmp,2,0xA0);
						F_AVcal_err=0;
					
					
					
				  	Vol1_B_temp=V_Array_disp[1];
				  	V_B_factor_tmp=vol_handle_B(V_Array_disp[1])-Vol_cal_tmp;//B��ѹУ׼
						V1_slope[1]=(Vol_cal_tmp<<20)/(Vol1_B_temp);
						HexToChar(array_temp,V1_slope[1],2);
						MODIFY_EEP_W(Addr_V1_B_slope,array_temp,2,0xA0);
					
						HexToChar(array_tmp,Vol1_B_temp,2);
						MODIFY_EEP_W(Addr_Vol1_B_temp,array_tmp,2,0xA0);
						F_BVcal_err=0;
						F_cal_finish=1;
		
					
					Vol1_C_temp=V_Array_disp[2];
					V_C_factor_tmp= vol_handle_C(V_Array_disp[2])-Vol_cal_tmp;//C��ѹУ׼

						V1_slope[2]=(Vol_cal_tmp<<20)/(Vol1_C_temp);
						HexToChar(array_temp,V1_slope[2],2);
						MODIFY_EEP_W(Addr_V1_C_slope,array_temp,2,0xA0);
						HexToChar(array_tmp,Vol1_C_temp,2);
						MODIFY_EEP_W(Addr_Vol1_C_temp,array_tmp,2,0xA0);
						F_CVcal_err=0;

						F_cal_finish=1;
							*/


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
/*************************************************/
			if(key==0x04)//�˳������Ѿ���Ϊ��λ����
			{
				Cal_state = 0;
				F_Disp = 1;
				F_cal = 0;
				F_sssj=0;
				F_ent = 0;
			}
			return 0;
		}
	
		//����״̬����ȷ������ʵ�ֹ�����ʾ�˳�
		if((key==0x20)&&(F_gz_disp!=0x0f))//ȷ����
		{
			
			F_gz_disp = 0x0F;
			F_Disp = 1 ;
			F_key=0 ;
			disp_status = 0;
			Func_Index=0;
			N_disp = 79;
		}
		
		if(F_key!=0) 
    {

      if(key==0x80)//���¼�
			 {
		
					         tiaozheng_key_state(0x11100,18,1);         //©��澯��   0���أ�1����
             if(D_LCur!=8)
						 {
									  tiaozheng_key_state(0x21100,8,0);					//�©�磺 0.05A,0.1A,0.3A,0.5A,0.8A,1A,AUTO
						 }

										tiaozheng_key_state(0x22100,5,0);       //�ֶ�ʱ�䣺200ms,300ms,500ms,1000ms

					       tiaozheng_key_state(0x14100,4,1);  //©���غ�բ����
					 
					        	tiaozheng_key_state(0x15100,2,1);      //ͻ�䱣����0���أ�1����
					 
					 tiaozheng_key_state(0x16100,2,1);               //©����  
					 
//					  tiaozheng_key_state(0x21100,2,1);              //ʧѹ����
//					 
//					 tiaozheng_key_state(0x22100,2,1);               //ȱ�ౣ�� 
//					 
//					 tiaozheng_key_state(0x23100,2,1);               //��ѹ����
//					 
//					 tiaozheng_key_state(0x24100,2,1);               //Ƿѹ����
					 tiaozheng_key_state(0x23100,6,0);               //��ѹ��λ
					 tiaozheng_key_state(0x24100,6,0);               //Ƿѹ��λ
						 if(Type_Cur_change==1)
						 {
					 					if(Type_Cur==0)               //������λ
										{
											temp_state_value_1 = 0x09;
										}
										else if(Type_Cur==1)
										{
											temp_state_value_1 = 0x14;
										}
										else if(Type_Cur==2)
										{
											temp_state_value_1 = 0x0E;
										}
										else if(Type_Cur==3)
										{
											temp_state_value_1 = 0x0F;
										}
										else if(Type_Cur==4)
										{
											temp_state_value_1 = 0x07;
										}
										else
										{
											Type_Cur = 1;
											temp_state_value_1 = 0x14;
										}
						}	
					 tiaozheng_key_state(0x25100,temp_state_value_1,0); //��λѡ��
					 tiaozheng_key_state(0x26100,8,0);               //��������ʱ��
					 tiaozheng_key_state(0x3D100,10,0);               //ʧѹ��ʱ
					 tiaozheng_key_state(0x3E100,10,0);               //��ѹ��ʱ
					 tiaozheng_key_state(0x3F100,10,0);               //Ƿѹ��ʱ
//					 tiaozheng_key_state(0x2a100,2,1);               //���㱣��
//					 tiaozheng_key_state(0x2b100,2,1);               //��ѹ�غ�
//					 tiaozheng_key_state(0x2c100,6,1); 
//					 tiaozheng_key_state(0x2d100,7,1); 
//					 tiaozheng_key_state(0x31100,2,1);               //��������


//					 tiaozheng_key_state(0x32100,2,1);               //����������λ

//					 tiaozheng_key_state(0x34100,2,1);               //���ӱ���
					 tiaozheng_key_state(0x27100,6,0);               //���ӱ�����λ 
					 tiaozheng_key_state(0x28100,7,0);               //����ʱ��
//					 tiaozheng_key_state(0x37100,2,1);               //˲ʱ����
					 tiaozheng_key_state(0x40100,6,0);               //˲ʱ��λ
//					 tiaozheng_key_state(0x39100,2,1);               //�����غ�բ
					 tiaozheng_key_state(0x41100,20,1);    					 //��¼��ѯ
					 tiaozheng_key_state(0x42100,6,1);               //��բ����
				 	 tiaozheng_key_state(0x43100,20,0);
										Ls_function_process();
					 tiaozheng_key_state(0x2B100,100,0);   //ϵͳ���ã���
										
				   tiaozheng_key_state(0x2C100,13,0);   //ϵͳ���ã���
										
					 tiaozheng_key_state(0x2D101,31,0);   //ϵͳ���ã���
										
					 tiaozheng_key_state(0x2E100,25,0);   //ϵͳ���ã�ʱ
										
					 tiaozheng_key_state(0x2F100,61,0);   //ϵͳ���ã���
										
					 tiaozheng_key_state(0x30100,61,0);   //ϵͳ���ã���							
					 tiaozheng_key_state(0x61100,2,1);		//�ϵ��բ		
					 tiaozheng_key_state(0x62100,2,1);		//ͣ����բ	
           tiaozheng_key_state(0x29100,4,0);    //������
           tiaozheng_key_state(0x2A100,5,0);    //�Ǽܵȼ�
//				   if(Type_Cur==0)               //������λ
//				  	{
//						 if(D_Cur>3) D_Cur=2;
//						}
//					 else if(Type_Cur==1)
//						{
//						 if(D_Cur>19) D_Cur=19;
//						}
//						else if(Type_Cur==2)
//						{
//						 if(D_Cur>11) D_Cur=11;
//						}
//						else if(Type_Cur==3)
//						{
//						 if(D_Cur>15) D_Cur=14;
//						}
					 tiaozheng_key_state(0x31100,10,0);
					 tiaozheng_key_state(0x32100,15,0);
					 tiaozheng_key_state(0x33100,10,0);
					 tiaozheng_key_state(0x34100,10,0);
					 tiaozheng_key_state(0x35100,10,0);
					 tiaozheng_key_state(0x36100,10,0);
					 tiaozheng_key_state(0x37100,10,0);
					 tiaozheng_key_state(0x38100,10,0);
					 tiaozheng_key_state(0x39100,10,0);
					 tiaozheng_key_state(0x3A100,10,0);
					 tiaozheng_key_state(0x3B100,10,0);
					 tiaozheng_key_state(0x3C100,10,0);//					 
//					 tiaozheng_key_state(0x75100,2,1);
					 tiaozheng_key_state(0x71100,2,1);
					 
					tiaozheng_key_state(0x50100,6,0);		
					tiaozheng_key_state(0x51100,5,0);	
				}
			 
			 
			 
			 if(key==0x01)//���ϼ�
			 {
					 	tiaozheng_key_state(0x11100,18,0);         //©��澯��   0���أ�1����

             if(D_LCur!=8)
						 {
									  tiaozheng_key_state(0x21100,8,1);					//�©�磺 0.05A,0.1A,0.3A,0.5A,0.8A,1A,AUTO
						 }

						tiaozheng_key_state(0x22100,5,1);       //�ֶ�ʱ�䣺200ms,300ms,500ms,1000ms

//					        	tiaozheng_key_state(0x14100,2,0);      //ͻ�䱣����0���أ�1����
					 tiaozheng_key_state(0x14100,4,0);  //©���غ�բ����
					 tiaozheng_key_state(0x15100,2,0);  //ͻ�䱣��
					 tiaozheng_key_state(0x16100,2,0);               //©���� 

//           tiaozheng_key_state(0x21100,7,0); 					     //ʧѹ����
//					 tiaozheng_key_state(0x22100,2,0);               //ȱ�ౣ�� 
//					 tiaozheng_key_state(0x23100,2,0);               //��ѹ����
//					 tiaozheng_key_state(0x24100,2,0);               //Ƿѹ����
					 tiaozheng_key_state(0x23100,6,1);               //��ѹ��λ
					 tiaozheng_key_state(0x24100,6,1);               //Ƿѹ��λ
							 if(Type_Cur_change=1)
						 {
					 					if(Type_Cur==0)               //������λ  125
										{
											temp_state_value_1 = 0x09;
										}
										else if(Type_Cur==1)//250
										{
											temp_state_value_1 = 0x14;
										}
										else if(Type_Cur==2)//400
										{
											temp_state_value_1 = 0x0E;
										}
										else if(Type_Cur==3)//630
										{
											temp_state_value_1 = 0x0F;
										}
										else if(Type_Cur==4)
										{
											temp_state_value_1 = 0x07;
										}
										else
										{
											Type_Cur = 1;
											temp_state_value_1 = 0x14;
										}
						}	
										tiaozheng_key_state(0x25100,temp_state_value_1,1); //��λѡ��	
					 tiaozheng_key_state(0x26100,8,1);               //��������ʱ��										
					 tiaozheng_key_state(0x3D100,10,1);               //ʧѹ��ʱ
					 tiaozheng_key_state(0x3E100,10,1);               //��ѹ��ʱ
					 tiaozheng_key_state(0x3F100,10,1);               //Ƿѹ��ʱ
//					 tiaozheng_key_state(0x2a100,2,0);               //���㱣��
//					 tiaozheng_key_state(0x2b100,2,0);               //��ѹ�غ�
//					 tiaozheng_key_state(0x2c100,6,0); 
//					 tiaozheng_key_state(0x2d100,7,0); 
//					  tiaozheng_key_state(0x31100,2,0);               //��������

//					 tiaozheng_key_state(0x32100,2,1);               //����������λ

//					 tiaozheng_key_state(0x34100,2,0);               //���ӱ���
					 tiaozheng_key_state(0x27100,6,1);               //���ӱ�����λ 
					 tiaozheng_key_state(0x28100,7,1);               //����ʱ��
//					 tiaozheng_key_state(0x37100,2,0);               //˲ʱ����
					 tiaozheng_key_state(0x40100,6,1);               //˲ʱ��λ
//					 tiaozheng_key_state(0x39100,2,0);               //�����غ�բ
					 tiaozheng_key_state(0x41100,20,0);    					 //��¼��ѯ
					 tiaozheng_key_state(0x42100,6,0);               //��բ����
					 tiaozheng_key_state(0x43100,20,1);
										Ls_function_process();
					 tiaozheng_key_state(0x2B100,100,1);   //ϵͳ���ã���
										
				   tiaozheng_key_state(0x2C100,13,1);   //ϵͳ���ã���
										
					 tiaozheng_key_state(0x2D101,31,1);   //ϵͳ���ã���
										
					 tiaozheng_key_state(0x2E100,25,1);   //ϵͳ���ã�ʱ
										
					 tiaozheng_key_state(0x2F100,61,1);   //ϵͳ���ã���
										
					 tiaozheng_key_state(0x30100,61,1);   //ϵͳ���ã���		
					 tiaozheng_key_state(0x56100,61,1);   //ϵͳ���ã���							
					 tiaozheng_key_state(0x61100,2,0);		//�ϵ��բ		
					 tiaozheng_key_state(0x62100,2,0);		//ͣ����բ	
           tiaozheng_key_state(0x29100,4,1);    //������
           tiaozheng_key_state(0x2A100,5,1);    //�Ǽܵȼ�

					 tiaozheng_key_state(0x31100,10,1);
					 tiaozheng_key_state(0x32100,15,1);
					 tiaozheng_key_state(0x33100,10,1);
					 tiaozheng_key_state(0x34100,10,1);
					 tiaozheng_key_state(0x35100,10,1);
					 tiaozheng_key_state(0x36100,10,1);
					 tiaozheng_key_state(0x37100,10,1);
					 tiaozheng_key_state(0x38100,10,1);
					 tiaozheng_key_state(0x39100,10,1);
					 tiaozheng_key_state(0x3A100,10,1);
					 tiaozheng_key_state(0x3B100,10,1);
					 tiaozheng_key_state(0x3C100,10,1);							 
						tiaozheng_key_state(0x71100,2,0);		
						
					tiaozheng_key_state(0x50100,6,1);		
					tiaozheng_key_state(0x51100,5,1);	
				}
//////////	     //����
//////////       if(key==0x40)
//////////        {
//////////					if(F_up_down_switch==1)
//////////					{
//////////						    key_state=key_state&0xFF000;			
//////////							F_up_down_switch=0;				
//////////					}
//////////					else
//////////					{
//////////					 if(((key_state>>12)&0x0F)>0x00)
//////////					 {
//////////							key_state=((key_state>>12)&0xFF)<<12;
//////////						  if((key_state==0x74000)||(key_state==0x73000))key_state=0x60000;
//////////						  key_state=((key_state>>12)&0xF0)<<12;
////////////					  F_sssj = 1;				
//////////					 }
//////////					 else if(((key_state>>16)&0x0F)>0x00)
//////////					 {
//////////							key_state=((key_state>>16)&0xF0)<<16;
//////////						 F_key=0;
//////////						 F_shishichaxun=0;					
////////////					  F_sssj = 1;				
//////////					 }

//////////				 }	
//////////			
//////////					
//////////         }
    }
		
		
		
		/********************************��������****************************/
		if((key_state&0xF0000000)==0x10000000)
		{
			if(key==0x40)//�Ҽ���λ
			{
			
					key_state=key_state&0xF00FFFFF;
					if((key_state>=0x10000000)&&(key_state<0x10010000))key_state+=0x00010000;//0λ
		  		else if((key_state>=0x10010000)&&(key_state<0x10020000))key_state+=0x00010000;//1
					else if((key_state>=0x10020000)&&(key_state<0x10030000))key_state+=0x00010000;//2
						
			}
			
			
				if(key==0x10)//�����λ
			{
				  key_state=key_state&0xF00FFFFF;
	        if((key_state<0x10040000)&&(key_state>=0x10030000))key_state-=0x00010000;
		  		else if((key_state<0x10030000)&&(key_state>=0x10020000))key_state-=0x00010000;
					else if((key_state<0x10020000)&&(key_state>=0x10010000))key_state-=0x00010000;
			}
			if(key==0x01)//�ϼ�
			{

//				
//				key_state=key_state&0xF00FFFFF;
//				if((key_state>=0x10000000)&&(key_state<0x10008999))key_state+=0x00001000;//��0λ//����ʵ�֣���������
//        else if((key_state>=0x10010000)&&(key_state<0x10019899))key_state+=0x00000100;//1
//				else if((key_state>=0x10020000)&&(key_state<0x10029989))key_state+=0x00000010;//2
//				else if((key_state>=0x10030000)&&(key_state<0x10039999))key_state+=0x00000001;//3
				
				 if((weizhi==0)&&(mima[0]<9))
				 {
					 key_state+=0x00001000;
				 }
				else if((weizhi==1)&&(mima[1]<9))
				{
					key_state+=0x00000100;
				}
				else if((weizhi==2)&&(mima[2]<9))
				{
					key_state+=0x00000010;
				}
				else if((weizhi==3)&&(mima[3]<9))
				{
					key_state+=0x00000001;
				}
				
						
			}
			if(key==0x80)//�¼�
			{

		    if((weizhi==0)&&(mima[0]>0))key_state-=0x00001000;
				else if((weizhi==1)&&(mima[1]>0))key_state-=0x00000100;
				else if((weizhi==2)&&(mima[2]>0))key_state-=0x00000010;
				else if((weizhi==3)&&(mima[3]>0))key_state-=0x00000001;
				
			}
			
				
		}
		
		
		
				/********************************�����޸�****************************/
		if((key_state&0xF0000000)==0x20000000)
		{
			if(key==0x40)//�Ҽ���λ
			{
			
					key_state=key_state&0xF00FFFFF;
					if((key_state>=0x20000000)&&(key_state<0x20010000))key_state+=0x00010000;//0λ
		  		else if((key_state>=0x20010000)&&(key_state<0x20020000))key_state+=0x00010000;//1
					else if((key_state>=0x20020000)&&(key_state<0x20030000))key_state+=0x00010000;//2
				 
			}
			
			
			
			if(key==0x20)//ȷ����λ
			{
			
					key_state=key_state&0xF00FFFFF;
					if((key_state>=0x20000000)&&(key_state<0x20010000))
					{
					   MODIFY_EEP_W(Addr_mima_set,mima,4,0xA0);
						  key_state+=0x00010000;//0λ
						  key_state=(unsigned int)(((key_state>>12)|(mima[0]))<<12);
              key_state=(unsigned int)(((key_state>>8)|(mima[1]))<<8);
              key_state=(unsigned int)(((key_state>>4)|(mima[2]))<<4);
               key_state=(unsigned int)(key_state)|(mima[3]);
					}
		  		else if((key_state>=0x20010000)&&(key_state<0x20020000))
					{
						MODIFY_EEP_W(Addr_mima_set,mima,4,0xA0);
					  key_state+=0x00010000;//1
						 key_state=(unsigned int)(((key_state>>12)|(mima[0]))<<12);
   key_state=(unsigned int)(((key_state>>8)|(mima[1]))<<8);
   key_state=(unsigned int)(((key_state>>4)|(mima[2]))<<4);
   key_state=(unsigned int)(key_state)|(mima[3]);
					}
						
					else if((key_state>=0x20020000)&&(key_state<0x20030000))
					{
						MODIFY_EEP_W(Addr_mima_set,mima,4,0xA0);
						key_state+=0x00010000;//2
						 key_state=(unsigned int)(((key_state>>12)|(mima[0]))<<12);
             key_state=(unsigned int)(((key_state>>8)|(mima[1]))<<8);
              key_state=(unsigned int)(((key_state>>4)|(mima[2]))<<4);
              key_state=(unsigned int)(key_state)|(mima[3]);
					}
					else if(key_state>=0x20030000)
					{
						 MODIFY_EEP_W(Addr_mima_set,mima,4,0xA0);
						  key_state=0x31100;
						 key_state=(unsigned int)(((key_state>>12)|(mima[0]))<<12);
              key_state=(unsigned int)(((key_state>>8)|(mima[1]))<<8);
               key_state=(unsigned int)(((key_state>>4)|(mima[2]))<<4);
              key_state=(unsigned int)(key_state)|(mima[3]);
					}
					
				 
			}

			
			if((key==0x20)&&(weizhi==3))
			{
			   
							   key_state=0x31100;

			}
			
			
			
			
				if(key==0x10)//�����λ
			{
				  key_state=key_state&0xF00FFFFF;
	        if((key_state<0x20040000)&&(key_state>=0x20030000))key_state-=0x00010000;
		  		else if((key_state<0x20030000)&&(key_state>=0x20020000))key_state-=0x00010000;
					else if((key_state<0x20020000)&&(key_state>=0x20010000))key_state-=0x00010000;
			}
			if(key==0x01)//�ϼ�
			{

				 if((weizhi==0)&&(mima[0]<9))key_state+=0x00001000;
				 else if((weizhi==1)&&(mima[1]<9))key_state+=0x00000100;
				 else if((weizhi==2)&&(mima[2]<9))key_state+=0x00000010;
				 else if((weizhi==3)&&(mima[3]<9))key_state+=0x00000001;									
			}
			if(key==0x80)//�¼�
			{

		     if((weizhi==0)&&(mima[0]>0))
				 {
				   key_state-=0x00001000;
					  mima[0]=((key_state>>12)&0x0000000f);
				 }
				 else if((weizhi==1)&&(mima[1]>0))key_state-=0x00000100;
				 else if((weizhi==2)&&(mima[2]>0))key_state-=0x00000010;
				 else if((weizhi==3)&&(mima[3]>0))key_state-=0x00000001;
				return 1;
				
			}
			
				
		}
		
		
		

		

}

/***��������ֵ����***/

void I_VAL_handle()
{
    //if(!disp_num)
    SET_D_Cur=D_Cur ;
    //������ܵȼ�Ϊ20~100A
    //������ܵȼ�Ϊ60~250A
    
		if(Type_Cur==0)	
    {
        if(SET_D_Cur>=9)
        SET_D_Cur=8 ;
        SET_I_VAL=SET_D_Cur*10+50 ;
				
				if(SET_I_VAL==60)	SET_I_VAL=63;
				if(SET_I_VAL==130)	SET_I_VAL=125;
    }
		if(Type_Cur==1)
    {
        //if(SET_D_Cur==20)
        //SET_D_Cur=0 ;
        SET_I_VAL=SET_D_Cur*10+60 ;
			
				if(SET_I_VAL==60)	SET_I_VAL=63;
    }
    //������ܵȼ�Ϊ200~400A
    if(Type_Cur==2)
    {
        if(SET_D_Cur>=12)
        SET_D_Cur=12 ;
        SET_I_VAL=SET_D_Cur*20+160 ;
				
    }
  
    if(Type_Cur==3)
    {
        if(SET_D_Cur>=15)
        {
            SET_D_Cur=14 ;
        }
        SET_I_VAL=SET_D_Cur*30+220 ;
				
								
				if(SET_I_VAL==250)	SET_I_VAL=252;
				if(SET_I_VAL==640)	SET_I_VAL=630;
				
    }
		if(Type_Cur==4)	
    {
        if(SET_D_Cur>=7)
        SET_D_Cur=6 ;
        SET_I_VAL=SET_D_Cur*80+320 ;
				if(SET_I_VAL==640)	SET_I_VAL=630;
    }

}




void disp_data_prepare(void)
{
		A_Cur=I_I_Array_xianshi[0];
//	  A_Cur=800;
  	B_Cur=I_I_Array_xianshi[1];
	  C_Cur=I_I_Array_xianshi[2];
	  Z_Cur=I_Array_xianshi[3];
	  //V_Array[0] = V_Array[1] = V_Array[2] = 810;
    nor_disp_num_buf[0]=leak_handle(Leak_xianshi_disp);
    //©��
	  if(isfenzha==0)
		{
			nor_disp_num_buf[0] = 0;
		}
    nor_disp_num_buf[1]=vol_handle_A(V_Array_disp[0]);
    //A���ѹ
    nor_disp_num_buf[2]=vol_handle_B(V_Array_disp[1]);
    //B���ѹ
    nor_disp_num_buf[3]=vol_handle_C(V_Array_disp[2]);
    //C���ѹ
		
		

		nor_disp_num_buf[4]=cur_handle_A(A_Cur);
	if(nor_disp_num_buf[4]<10) nor_disp_num_buf[4] = 0;
	//A�����
	nor_disp_num_buf[5]=cur_handle_B(B_Cur);
	if(nor_disp_num_buf[5]<10) nor_disp_num_buf[5] = 0;	
	//B�����
	nor_disp_num_buf[6]=cur_handle_C(C_Cur);
	if(nor_disp_num_buf[6]<10) nor_disp_num_buf[6] = 0;
	//C�����
		nor_disp_num_buf[7]=Leak_Class[D_LCur];
    //©�絵λ
    I_VAL_handle();
    nor_disp_num_buf[8]=SET_I_VAL;
    //��������λ
		
		
		Power_A_Value=cur_handle_A(A_Cur);
		Power_B_Value=cur_handle_B(B_Cur);
		Power_C_Value=cur_handle_C(C_Cur);
	
		Total_power[0]=vol_handle_A(V_Array_disp[0])*Power_A_Value;//A���ܹ���=��ѹ��ʾ*������ʾ
		Total_power[1]=vol_handle_B(V_Array_disp[1])*Power_B_Value;
		Total_power[2]=vol_handle_C(V_Array_disp[2])*Power_C_Value;
		
		nor_disp_num_buf[15]=Total_power[0]/100;//A���ܹ���
		nor_disp_num_buf[16]=Total_power[1]/100;//B���ܹ���
		nor_disp_num_buf[17]=Total_power[2]/100;//C���ܹ���
		
		
		Active_Pow[0]=Total_power[0]*Power_factor[0];//˲ʱ�й�����//X_power
		Active_Pow[1]=Total_power[1]*Power_factor[1];
		Active_Pow[2]=Total_power[2]*Power_factor[2];
		
		nor_disp_num_buf[12]=Active_Pow[0]/100000;//A���й�����100
		nor_disp_num_buf[13]=Active_Pow[1]/100000;//B���й�����
		nor_disp_num_buf[14]=Active_Pow[2]/100000;//C���й�����
		
		nor_disp_num_buf[9]=Power_factor[0];//A�๦������Power_factor
		nor_disp_num_buf[10]=Power_factor[1];//B�๦������
		nor_disp_num_buf[11]=Power_factor[2];//C�๦������
		
		
}

unsigned char abnormal_disp(void)
{
		if(isfenzha!=0) 	
	{
		if(F_disp_jg!=0)
		{
			F_disp_jg=0x00;
		}
	}
    //��������բ���ɹ�
    if(F_disp_jg==0x55)
    {

			clear_screen();
			Lcd12864_Write16CnCHAR(0,32,0,"��բʧ��");
        return 0 ;
    }
    //����ѿ۲��ɹ�
    if(F_disp_tr==1)
    {

			clear_screen();
			Lcd12864_Write16CnCHAR(0,32,0,"��բʧ��");
        return 0 ;
    }
		return 1;
}
//unsigned char abnormal_disp(void)
//{
//	if(isfenzha!=0) 	
//	{
//		if(F_disp_jg!=0)
//		{
//			F_disp_jg=0x00;
//		}
//	}
//	//��������բ���ɹ�
//	if(F_disp_jg==0x55)
//	{
//			clear_screen();
//			Lcd12864_Write16CnCHAR(0,16,3,"��բʧ��...");
//			return 0;		
//	}
//	//����ѿ۲��ɹ�
//	if(F_disp_tr==1)
//	{
//		dispbit[0]=0x78 ;
//		dispbit[1]=0x70 ;
//		dispbit[2]=0x40 ;
//		dispbit[3]=0x79 ;
//		display();
//		return 0 ;
//	}
//	return 1;
//}
unsigned char guzhang_disp(void)
{
	//����ں�բ״̬
    if(isfenzha!=0)
    {
        F_gz_disp=0x0F ;
			  return 0;
    }
    //�ָ�������ʾ
    //����ڷ�բ״̬����ʾ����
    else 
    {

        if(disp_num)
        {
            disp_num=0 ;
           key_state = 0;
        }
        //������ʾ״̬�ͼ���������
        if(!disp_gz)
        {
            disp_status=0 ;
            disp_status1=0 ;
            disp_gz=1 ;
        }
        if(disp_status==0)
        {
            //Ƿѹ��QY��

					gz_disp_uart=gz_disp ;
					clear_screen();
						if(F_gz_disp==A_qy||F_gz_disp==B_qy||F_gz_disp==C_qy)
            {

							xianshishuju(gz_disp);

							
							Lcd12864_Write16CnCHAR(0,32,0,"Ƿѹ����\r ����ֵ");
							
						
							if(F_gz_disp==A_qy)
							{
								display_ASCIIstring_8x16(3,75,"Ua:    V");
								
							
							}
							else	if(F_gz_disp==B_qy)
							{
								display_ASCIIstring_8x16(3,75,"Ub:    V");
							
							}
							else	if(F_gz_disp==C_qy)
							{
								display_ASCIIstring_8x16(3,75,"Uc:    V");
							
							}
							display_ASCIIstring_8x16(3,100,zifu_dian);
							
							Lcd12864_Write16CnCHAR(0,0,4," �غ�բ����:");
							xianshishuju(F_ch);
							display_ASCIIstring_8x16(5,110,zifu_dian);

							Lcd12864_Write16CnCHAR(0,0,6," Ƿѹ��λ:");
							display_ASCIIstring_8x16(7,88,DIANYA3[Vol_q]);
							
							
            }
							if(F_gz_disp==A_QX||F_gz_disp==B_QX||F_gz_disp==C_QX	)
            {

							xianshishuju(gz_disp);
							Lcd12864_Write16CnCHAR(0,32,0,"ȱ�����\r ����ֵ");
							
						
							if(F_gz_disp==A_QX)
							{
								display_ASCIIstring_8x16(3,75,"Ua:    V");
								
							
							}
							else	if(F_gz_disp==B_QX)
							{
								display_ASCIIstring_8x16(3,75,"Ub:    V");
							
							}
							else	if(F_gz_disp==C_QX)
							{
								display_ASCIIstring_8x16(3,75,"Uc:    V");
							
							}
							display_ASCIIstring_8x16(3,100,zifu_dian);
							
							Lcd12864_Write16CnCHAR(0,0,4," �غ�բ����:");
							xianshishuju(F_ch);
							display_ASCIIstring_8x16(5,110,zifu_dian);				
            }
            //��ѹ��GY��
            if(F_gz_disp==A_gy||F_gz_disp==B_gy||F_gz_disp==C_gy)
            {

							xianshishuju(gz_disp);
					
							Lcd12864_Write16CnCHAR(0,32,0,"��ѹ����\r ����ֵ");
						
							
							if(F_gz_disp==A_gy)
							{
								display_ASCIIstring_8x16(3,75,"Ua:    V");
								
							
							}
							else	if(F_gz_disp==B_gy)
							{
								display_ASCIIstring_8x16(3,75,"Ub:    V");
							
							}
							else	if(F_gz_disp==C_gy)
							{
								display_ASCIIstring_8x16(3,75,"Uc:    V");
							
							}
							display_ASCIIstring_8x16(3,100,zifu_dian);
							
									Lcd12864_Write16CnCHAR(0,0,4," �غ�բ����:");
							xianshishuju(F_ch);
							
							display_ASCIIstring_8x16(5,110,zifu_dian);
							Lcd12864_Write16CnCHAR(0,0,6," ��ѹ��λ:");
							display_ASCIIstring_8x16(7,88,DIANYA2[Vol_g]);
	
            }

            //©�硰ld��
            if(F_gz_disp==L_hb)
            {

							xianshishuju(gz_disp);
							Lcd12864_Write16CnCHAR(0,32,0,"©�����\r ����ֵ      mA");
							display_ASCIIstring_8x16(3,76,zifu_dian);
							Lcd12864_Write16CnCHAR(0,0,4," �غ�բ����:");
							xianshishuju(F_ch);
							
							display_ASCIIstring_8x16(5,110,zifu_dian);
							Lcd12864_Write16CnCHAR(0,0,6," �©��:");
							display_ASCIIstring_8x16(7,88,dianliu1[D_LCur]);
							
							
            }
            //������GL��
            if((F_gz_disp>L_hb)&&(F_gz_disp<Gz_TD))
            {

                SET_D_Cur=D_Cur ;
                I_VAL_handle();
                gz_disp1=SET_I_VAL ;
								xianshishuju(gz_disp);

							
							Lcd12864_Write16CnCHAR(0,32,0,"��������\r ����ֵ");
							if(F_gz_disp==A_gl)
							{
								display_ASCIIstring_8x16(3,75,"Ia:    A");
							
							}
							else if(F_gz_disp==B_gl)
							{
								display_ASCIIstring_8x16(3,75,"Ib:    A");
							}
							else if(F_gz_disp==C_gl)
							{
								display_ASCIIstring_8x16(3,75,"Ic:    A");
							}
							else if(F_gz_disp==N_gl)
							{
								display_ASCIIstring_8x16(3,75,"In:    A");
							}
							display_ASCIIstring_8x16(3,100,zifu_dian);
							
								Lcd12864_Write16CnCHAR(0,0,4," �غ�բ����:");
							xianshishuju(F_ch);
							
							display_ASCIIstring_8x16(5,110,zifu_dian);
							Lcd12864_Write16CnCHAR(0,0,6," ������λ:    ");

								I_VAL_handle();
	
							xianshishuju_dianliu(SET_I_VAL);
	
							display_ASCIIstring_8x16(7,92,zifu_dian);    //��������
            }
            //ͣ�硰tD��
            if(F_gz_disp==Gz_TD)
            {

							Lcd12864_Write16CnCHAR(0,32,0,"ͣ�����");
            }
            //�ֶ��Ͷ�·Ϊδ֪��UN��
            if(F_gz_disp==FZ_UK)
            {

							Lcd12864_Write16CnCHAR(0,32,0,"δ֪����");
            }
            //������AJ��
            if(F_gz_disp==FZ_AJ)
            {


        			Lcd12864_Write16CnCHAR(0,32,0,"������բ");

            }
            //Զ�̡�YC��
            if(F_gz_disp==FZ_YC)
            {

							Lcd12864_Write16CnCHAR(0,32,0,"Զ�̷�բ");
            }
            if(F_gz_disp==Gz_QL)
            {


							Lcd12864_Write16CnCHAR(0,32,0,"ȱ���բ");
            }
						
            if(F_gz_disp==Gz_QL)
            {


							Lcd12864_Write16CnCHAR(0,32,0,"ȱ���բ");
            }
						if(F_gz_disp==Tem_IN_N)
            {
							Lcd12864_Write16CnCHAR(0,32,0,"N->���·�բ");
            }
						if(F_gz_disp==Tem_IN_A)
            {

							Lcd12864_Write16CnCHAR(0,32,0,"A->���·�բ");
            }
						if(F_gz_disp==Tem_IN_B)
            {

							Lcd12864_Write16CnCHAR(0,32,0,"B->���·�բ");
            }
						if(F_gz_disp==Tem_IN_C)
            {
							Lcd12864_Write16CnCHAR(0,32,0,"C->���·�բ");
            }
							if(F_gz_disp==Tem_OUT_N)
            {
							Lcd12864_Write16CnCHAR(0,32,0,"N<-���·�բ");
            }
						if(F_gz_disp==Tem_OUT_A)
            {

							Lcd12864_Write16CnCHAR(0,32,0,"A<-���·�բ");
            }
						if(F_gz_disp==Tem_OUT_B)
            {

							Lcd12864_Write16CnCHAR(0,32,0,"B<-���·�բ");
            }
						if(F_gz_disp==Tem_OUT_C)
            {
							Lcd12864_Write16CnCHAR(0,32,0,"C<-���·�բ");
            }
 
        }

				if(++disp_status1>=3) 
        {
            disp_status1=0 ;
            disp_status++;
					

            if(disp_status>=2)
							disp_status=0 ;

        }
        return 0 ;
    }
		return 1;
}




unsigned char nogz_disp(void)
{
	 unsigned char array_tmp[2];


		if(++disp_status1>=2)
		{
			disp_status1 = 0;
			if(Func_Index==59)
			{
					clear_screen();
#ifdef 				F_vison

					{
						display_ASCIIstring_8x16(1,5,"TestVer.");
						Lcd12864_Write16CnCHAR(0,65,0,"����\rIa:   A Ib:   A\rIc:   A In:   A\r ���ص�λ:    A");
					}
					
#else
					Lcd12864_Write16CnCHAR(0,32,0,"ʵʱ����\rIa:   A Ib:   A\rIc:   A In:   A\r ���ص�λ:    A");
#endif
				
					xianshishuju(nor_disp_num_buf[4]);
					display_ASCIIstring_8x16(3,27,zifu_dian);		
					xianshishuju(nor_disp_num_buf[5]);
					display_ASCIIstring_8x16(3,91,zifu_dian);			
					xianshishuju(nor_disp_num_buf[6]);
					display_ASCIIstring_8x16(5,27,zifu_dian);
	
		
					EEPROM_R(Addr_Type_Cur,array_tmp,1,0xA0);
			
					Type_Cur=array_tmp[0];
				


					I_VAL_handle();
	
					xianshishuju_dianliu(SET_I_VAL);
	
					display_ASCIIstring_8x16(7,84,zifu_dian);    

//					Func_Index++;
		  }
			else if(Func_Index==60)
			{

					clear_screen();
				

#ifdef 				F_vison	
						{				
						display_ASCIIstring_8x16(1,5,"TestVer.");
						Lcd12864_Write16CnCHAR(0,65,0,"��ѹ\rUa:   V Ub:   V\rUc:   V Un:   V\r��:     Ƿ:");
					}
#else
					Lcd12864_Write16CnCHAR(0,32,0,"ʵʱ��ѹ\rUa:   V Ub:   V\rUc:   V Un:   V\r��:     Ƿ:");
#endif					
					xianshishuju(nor_disp_num_buf[1]);
					display_ASCIIstring_8x16(3,27,zifu_dian);
					xianshishuju(nor_disp_num_buf[2]);
					display_ASCIIstring_8x16(3,91,zifu_dian);
					xianshishuju(nor_disp_num_buf[3]);
					display_ASCIIstring_8x16(5,27,zifu_dian);
					display_ASCIIstring_8x16(7,28,DIANYA[Vol_g]);
					display_ASCIIstring_8x16(7,91,DIANYA_1[Vol_q]);
//					Func_Index++;
		 }
			else if(Func_Index==61)
			{
					clear_screen();
          if((F_trip_ld)&&(F_al1))
					{				
						 Lcd12864_Write16CnCHAR(0,32,0,"©��澯");
						Lcd12864_Write16CnCHAR(0,65,0,"\r\r�©��:    \r�ֶ�ʱ��:    ");
//							xianshishuju(nor_disp_num_buf[0]);
					display_ASCIIstring_8x16(5,78,dianliu[D_LCur]);
					display_ASCIIstring_8x16(7,78,shijian[TH_LCur]);
					}
					else
					{
#ifdef 			F_vison	
						{						
						display_ASCIIstring_8x16(1,5,"TestVer.");
						Lcd12864_Write16CnCHAR(0,65,0,"ʣ�����\rʵʱ©��:     mA\r�©��:    \r�ֶ�ʱ��:    ");
					}
#else
						Lcd12864_Write16CnCHAR(0,16,0,"ʵʱʣ�����\rʵʱ©��:     mA\r�©��:    \r�ֶ�ʱ��:    ");
#endif		
					xianshishuju(nor_disp_num_buf[0]);
					clear_define_screen(2,4,92,108);
					display_ASCIIstring_8x16(3,78,zifu_dian);
					display_ASCIIstring_8x16(5,78,dianliu[D_LCur]);
					display_ASCIIstring_8x16(7,78,shijian[TH_LCur]);
					}

					Func_Index=59;
			}
			return 0;

	}
		return 0;
}


unsigned char nomal_disp(void)
{
		if(F_hezha_state==1)
	{

			clear_screen();
			Lcd12864_Write16CnCHAR(0,24,0,"�Ժ�բ��...");
		
		
		
		
		
		
		
		HAL_RTC_GetTime(&hrtc, &stimestructure, RTC_FORMAT_BCD);
  HAL_RTC_GetDate(&hrtc, &sdatestructure, RTC_FORMAT_BCD);

				nian[0]=( sdatestructure.Year>>4)+0x30;				
				nian[1]=(sdatestructure.Year&0x0F)+0x30;	
				nian[2]='\0';
	
				yue[0]=(sdatestructure.Month>>4)+0x30;
				yue[1]=(sdatestructure.Month&0x0F)+0x30;
				yue[2]='\0';

				ri[0]=(sdatestructure.Date>>4)+0x30;
				ri[1]=(sdatestructure.Date&0x0F)+0x30;
				ri[2]='\0';

				shi[0]=(stimestructure.Hours>>4)+0x30;
				shi[1]=(stimestructure.Hours&0x0F)+0x30;
				shi[2]='\0';

				fen[0]=(stimestructure.Minutes>>4)+0x30;
				fen[1]=(stimestructure.Minutes&0x0F)+0x30;
				fen[2]='\0';
				
				miao[0]=(stimestructure.Seconds>>4)+0x30;
				miao[1]=(stimestructure.Seconds&0x0F)+0x30;
				miao[2]='\0';
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
//		  delay_ms(500);
//		  delay_ms(500);
//		  initial_lcd();
		return 0;		
	}
//	if(F_hezha_delay==1)
//	{
//	//		if(F_initial_lcd_hezha==1)
////		{
////			initial_lcd();
////			F_initial_lcd_hezha=0;
////		}
//			clear_screen();
//			Lcd12864_Write16_1CnCHAR(0,16,3,"���ں�բ...");
////		  delay_ms(500);
////		  delay_ms(500);
////		  initial_lcd();
//		return 0;	
//	}
	if(F_fenzha_state==1)
	{
//		if(F_initial_lcd_hezha==1)
//		{
//			initial_lcd();
//			F_initial_lcd_hezha=0;
//		}
			clear_screen();
			Lcd12864_Write16CnCHAR(0,16,3,"���ڷ�բ...");
			return 0;		
	}
//	if(F_disp_jg==0x55)
//	{
//			clear_screen();
//			Lcd12864_Write16CnCHAR(0,16,3,"��բʧ��...");
//			return 0;		
//	}
		disp_data_prepare(); 
		if((F_sssj==0)&&(F_gz_disp==0x0f))
		{
			shishishuju(sssj_N_xunhuan);
			return 0;
		}
		if((F_sssj==2)&&(F_gz_disp==0x0f))
		{
			shishishuju(sssj_N);
			return 0;
		}
	  
	if((F_cal==1)&&(F_sssj==3))               //У׼����
	{
		if(Cal_state==0)	//©��У׼
		{
			if(F_L_err==0)
			{
				 F_key=9;
			   clear_screen();
				xianshishuju(Leak_Cur_disp);
				Lcd12864_Write16CnCHAR(0,32,0,"����У׼\r\r  ©��У׼:");				
				if(F_cal_finish==1)
				{
					display_ASCIIstring_8x16_fanxian(5,92,zifu_dian);
				}
				else
				{
					display_ASCIIstring_8x16_frame(5,92,zifu_dian);
				}
				display_graphic_1x16(5,92,gang);

				F_cal_finish=0;
			}

		
		}
			if(Cal_state==1)	//��ѹ+
		{
		
     		clear_screen();
				Lcd12864_Write16CnCHAR(0,32,0,"��ѹУ׼: \r  A ���ѹ:   V\r  B ���ѹ:   V\r  C ���ѹ:   V");
				
				if(F_cal_finish==1)
				{

					xianshishuju(HT7038_buf[1]);
					display_ASCIIstring_8x16_fanxian(3,92,zifu_dian);

					xianshishuju(HT7038_buf[2]);
					display_ASCIIstring_8x16_fanxian(5,92,zifu_dian);

					xianshishuju(HT7038_buf[3]);
					display_ASCIIstring_8x16_fanxian(7,92,zifu_dian); 
					
				}
				else
				{

					xianshishuju(nor_disp_num_buf[1]);
					display_ASCIIstring_8x16_frame(3,92,zifu_dian);

					xianshishuju(nor_disp_num_buf[2]);
					display_ASCIIstring_8x16_frame(5,92,zifu_dian);

					xianshishuju(nor_disp_num_buf[3]);
					display_ASCIIstring_8x16_frame(7,92,zifu_dian);
				}
				display_graphic_1x16(3,92,gang);
				display_graphic_1x16(5,92,gang);
				display_graphic_1x16(7,92,gang);
				if(F_cal_finish==1)
				{
					delay_ms(500);
				}
        F_cal_finish=0;


		}
		  if(Cal_state==2)	//����100
		{

          clear_screen();
				if(Type_Cur==0)
				{
					Lcd12864_Write16CnCHAR(0,16,0,"50A����У׼: \r  A �����:   A\r  B �����:   A\r  C �����:   A");
					
				}
						
			 else if(Type_Cur==1)
				{
					Lcd12864_Write16CnCHAR(0,16,0,"100A����У׼: \r  A �����:   A\r  B �����:   A\r  C �����:   A");
					
				}
			 else if(Type_Cur==2)
				{
					Lcd12864_Write16CnCHAR(0,16,0,"160A����У׼: \r  A �����:   A\r  B �����:   A\r  C �����:   A");
				}
				else if(Type_Cur==3)
				{
					Lcd12864_Write16CnCHAR(0,16,0,"252A����У׼: \r  A �����:   A\r  B �����:   A\r  C �����:   A");
				}
				else if(Type_Cur==4)
				{
					Lcd12864_Write16CnCHAR(0,16,0,"320A����У׼: \r  A �����:   A\r  B �����:   A\r  C �����:   A");
				}

				if(F_cal_finish==1)
				{

					xianshishuju(nor_disp_num_buf[4]); 
					display_ASCIIstring_8x16_fanxian(3,92,zifu_dian);

					xianshishuju(nor_disp_num_buf[5]); 
					display_ASCIIstring_8x16_fanxian(5,92,zifu_dian);

					xianshishuju(nor_disp_num_buf[6]); 
					display_ASCIIstring_8x16_fanxian(7,92,zifu_dian);
				}
				else
				{

					xianshishuju(nor_disp_num_buf[4]); 
					display_ASCIIstring_8x16_frame(3,92,zifu_dian);

					xianshishuju(nor_disp_num_buf[5]); 
					display_ASCIIstring_8x16_frame(5,92,zifu_dian);

					xianshishuju(nor_disp_num_buf[6]);      
					display_ASCIIstring_8x16_frame(7,92,zifu_dian);
				}
					display_graphic_1x16(3,92,gang);
				  display_graphic_1x16(5,92,gang);
				  display_graphic_1x16(7,92,gang);

				if(F_cal_finish==1)
				{
					delay_ms(500);
				}
        F_cal_finish=0;

		
		}
		
				if(Cal_state==3)	//����250
		 {

          clear_screen();
			 	if(Type_Cur==0)
				{
					Lcd12864_Write16CnCHAR(0,16,0,"125A����У׼: \r  A �����:   A\r  B �����:   A\r  C �����:   A");
					
				}
			 else if(Type_Cur==1)
				{
					Lcd12864_Write16CnCHAR(0,16,0,"250A����У׼: \r  A �����:   A\r  B �����:   A\r  C �����:   A");
					
				}
			 else if(Type_Cur==2)
				{
					Lcd12864_Write16CnCHAR(0,16,0,"400A����У׼: \r  A �����:   A\r  B �����:   A\r  C �����:   A");
				}
			 else if(Type_Cur==3)
				{
					Lcd12864_Write16CnCHAR(0,16,0,"630A����У׼: \r  A �����:   A\r  B �����:   A\r  C �����:   A");
				}
				else if(Type_Cur==4)
				{
					Lcd12864_Write16CnCHAR(0,16,0,"800A����У׼: \r  A �����:   A\r  B �����:   A\r  C �����:   A");
				}
				if(F_cal_finish==1)
				{
//					 xianshishuju(cur_handle_A(I_I_Array_xianshi[0]));
					xianshishuju(nor_disp_num_buf[4]); 
					display_ASCIIstring_8x16_fanxian(3,92,zifu_dian);
//				  xianshishuju(cur_handle_A(I_I_Array_xianshi[1]));
					xianshishuju(nor_disp_num_buf[5]); 
					display_ASCIIstring_8x16_fanxian(5,92,zifu_dian);
//					xianshishuju(cur_handle_A(I_I_Array_xianshi[2]));
					xianshishuju(nor_disp_num_buf[6]); 
					display_ASCIIstring_8x16_fanxian(7,92,zifu_dian);
				}
				else
				{
//					xianshishuju(cur_handle_A(I_I_Array_xianshi[0]));
					xianshishuju(nor_disp_num_buf[4]); 
					display_ASCIIstring_8x16_frame(3,92,zifu_dian);
//				  xianshishuju(cur_handle_A(I_I_Array_xianshi[1]));
					xianshishuju(nor_disp_num_buf[5]); 
					display_ASCIIstring_8x16_frame(5,92,zifu_dian);
//					xianshishuju(cur_handle_A(I_I_Array_xianshi[2]));
					xianshishuju(nor_disp_num_buf[6]); 
					display_ASCIIstring_8x16_frame(7,92,zifu_dian);
				}
					display_graphic_1x16(3,92,gang);
				  display_graphic_1x16(5,92,gang);
				  display_graphic_1x16(7,92,gang);

				if(F_cal_finish==1)
				{
					delay_ms(500);
				}
        F_cal_finish=0;

		
		}

		return 0;
 }
	
 		if(F_sssj==10)//ͨ��У׼ҳ��//YJK
		{
//			  LEDA_ON;
				clear_screen();
				Lcd12864_Write16CnCHAR(0,0,0,"ʱ��");
			  Lcd12864_Write16CnCHAR(0,0,2,"��ѹ");
			  Lcd12864_Write16CnCHAR(0,0,4,"©��");
			  Lcd12864_Write16CnCHAR(0,0,6,"����");
			
			
			  if(TXJZ_SJ==1)//ʱ��
				{

        HAL_RTC_GetTime(&hrtc, &stimestructure, RTC_FORMAT_BCD);
        HAL_RTC_GetDate(&hrtc, &sdatestructure, RTC_FORMAT_BCD);
		
				nian[0]=( sdatestructure.Year>>4)+0x30;				
				nian[1]=(sdatestructure.Year&0x0F)+0x30;	
				nian[2]='\0';
	
				yue[0]=(sdatestructure.Month>>4)+0x30;
				yue[1]=(sdatestructure.Month&0x0F)+0x30;
				yue[2]='\0';

				ri[0]=(sdatestructure.Date>>4)+0x30;
				ri[1]=(sdatestructure.Date&0x0F)+0x30;
				ri[2]='\0';

				shi[0]=(stimestructure.Hours>>4)+0x30;
				shi[1]=(stimestructure.Hours&0x0F)+0x30;
				shi[2]='\0';

				fen[0]=(stimestructure.Minutes>>4)+0x30;
				fen[1]=(stimestructure.Minutes&0x0F)+0x30;
				fen[2]='\0';
				
				miao[0]=(stimestructure.Seconds>>4)+0x30;
				miao[1]=(stimestructure.Seconds&0x0F)+0x30;
				miao[2]='\0';
//				display_ASCIIstring_8x16(7,8,nian);
//				display_graphic_8x16(7,24,qirigang);	
				display_ASCIIstring_8x16(1,36,yue);
//				display_graphic_8x16(7,45,qirigang);	
				display_ASCIIstring_8x16(1,52,ri);
				
//				display_graphic_8x16(1,65,xiaogang);	
				display_ASCIIstring_8x16(1,71,shi);
				display_graphic_8x16(1,87,xiaomaohao);	
				display_ASCIIstring_8x16(1,92,fen);
				display_graphic_8x16(1,108,xiaomaohao);	
				display_ASCIIstring_8x16(1,113,miao);
				}
			
			
				
							
			  if(TXJZ_DY_A==1)//a��ѹ
				{
					xianshishuju(nor_disp_num_buf[1]);//A
					display_ASCIIstring_8x16(3,40,zifu_dian);
				}
				
				 if(TXJZ_DY_B==1)//B��ѹ
				{
					xianshishuju(nor_disp_num_buf[2]);//B
					display_ASCIIstring_8x16(3,70,zifu_dian);
				}
				
				 if(TXJZ_DY_C==1)//c��ѹ
				{
					xianshishuju(nor_disp_num_buf[3]);//C
					display_ASCIIstring_8x16(3,100,zifu_dian);
				}
			
				
				
				if(TXJZ_LD==1)//©��
				{
				   xianshishuju(Leak_Cur_disp);
			
					display_ASCIIstring_8x16(5,40,zifu_dian);
				
				}
				
			
			  if(TXJZ_DL_A==1)//A����
				{

					xianshishuju(nor_disp_num_buf[4]); //A
					display_ASCIIstring_8x16(7,40,zifu_dian);
				}
				
				if(TXJZ_DL_B==1)//B����
				{
					xianshishuju(nor_disp_num_buf[5]); //B
					display_ASCIIstring_8x16(7,70,zifu_dian);
				}
				
				if(TXJZ_DL_C==1)//C����
				{
					xianshishuju(nor_disp_num_buf[6]); //C
					display_ASCIIstring_8x16(7,100,zifu_dian);
				}
			
			return 0;
		}
 
 
 
 	if(abnormal_disp()==0)
	{
		
		return 0;
	}
		if(F_gz_disp!=0x0f)
    {
				if(guzhang_disp()==0)
				{
//					LEDA_ON;
					LEDA_FLAG=1;
					Lcd_Count=0;
				return 0;
				}
    }
    if(F_gz_disp==0x0f)
    {
		
			  if(nogz_disp()==0)
				return 0;
     }
		return 0;
}


/*****************�������Լ�*******************/
void Get_Selftest_Record(unsigned int N_tmp)
{
	
	unsigned char lenth,event_point,point_event_self_tmp;
	int Addr_factor;
	if(point_event_self==0)
	{
		point_event_self_tmp = 9;
	}
	else
	{
		point_event_self_tmp = point_event_self-1;
	}
	N_tmp = N_tmp - 1;
	if(point_event_self_tmp>=N_tmp)
	{
		event_point = (point_event_self_tmp-N_tmp);
	}
	else
	{
		event_point = point_event_self_tmp+10-N_tmp;
	}
	Addr_factor = Addr_event_self+((event_point)*26);
	lenth = Lenth_event_self;
  EEPROM_R(Addr_factor,array_temps,lenth,0xA0);

}


//void back_button()
//{
//    key_state = 0;
//    nomal_disp();
//    
//}


void mima_input()//������������//�����2022.2.21д�Ĺ��ܺ���
{
//	int shuzi,weizhi,i;
	Lcd12864_Write16CnCHAR(0,33,0,"��������");
	weizhi=(key_state >> 16)&0x0f;//�ڼ�λ����

	if(weizhi==0)
	{
	  mima[0]=((key_state>>12)&0x0000000f);//���������ֵ	
		Lcd12864_Write16CnCHAR(0,32,4,"��");
	}

	else if(weizhi==1)
	{
	  mima[1]=((key_state>>8)&0x0000000f);	
		Lcd12864_Write16CnCHAR(0,49,4,"��");//��ʾѡ�е���
	}
	else if(weizhi==2)
	{
	 mima[2]=((key_state>>4)&0x0000000f);
		Lcd12864_Write16CnCHAR(0,66,4,"��");
	}
	else if(weizhi==3)
	{
	   mima[3]=key_state&0x0000000f;	
		Lcd12864_Write16CnCHAR(0,83,4,"��");
	}
	
	
		xianshishuju(mima[0]);
	  Lcd12864_Write16CnCHAR(0,32,2,zifu_dian);
		xianshishuju(mima[1]);
	  Lcd12864_Write16CnCHAR(0,49,2,zifu_dian);	
		xianshishuju(mima[2]);
	  Lcd12864_Write16CnCHAR(0,66,2,zifu_dian);
		xianshishuju(mima[3]);
	  Lcd12864_Write16CnCHAR(0,83,2,zifu_dian);
}



void mima_check()//��������������趨��������бȶ�//�����2022.2.21
{
	 	//������2022.2.21��������ݼ�
	EEPROM_R(Addr_mima_set,mima_set,4,0xA0);
	
   if((mima[0]==mima_set[0])&&(mima[1]==mima_set[1])&&(mima[2]==mima_set[2])&&(mima[3]==mima_set[3]))
	 {
		 clear_screen();
	   Lcd12864_Write16CnCHAR(0,33,2,"������ȷ");
		 if(check_reason==0x20)
		 {
		 		F_key=7;
			  key_state=0x21100;
		 }
		 else if(check_reason==0x81)
		 {
	       F_key=8;
		 } 
		 

		 HAL_Delay(500);

	 }
	 else
	 {
	   clear_screen();
	   Lcd12864_Write16CnCHAR(0,33,2,"�������");
		 HAL_Delay(800);
	   F_key=0;//�������󷵻ص����Խ���

		 key_state=0x00000000;//��������ʱ����
						mima[0]=0;
						mima[1]=0;
						mima[2]=0;
						mima[3]=0;
	 }
}


void mima_change()//�޸�����//�����2022.2.23
{

	EEPROM_R(Addr_mima_set,mima,4,0xA0);
  unsigned char mima0[2],mima1[2],mima2[2],mima3[2];
	weizhi=(key_state >> 16)&0x0f;//�ڼ�λ����
	

    clear_screen();       
    Lcd12864_Write16CnCHAR(0,0,0,"19�޸�����\r");
		display_graphic_8x16(1,86,maohao);


	  mima[0]=((key_state>>12)&0x0000000f);//���������ֵ	
		mima0[0]=mima[0]+0x30;
		mima0[1]='\0';
	
	  mima[1]=((key_state>>8)&0x0000000f);	
		mima1[0]=mima[1]+0x30;
		mima1[1]='\0';
	
  	mima[2]=((key_state>>4)&0x0000000f);
		mima2[0]=mima[2]+0x30;
		mima2[1]='\0';

	  mima[3]=key_state&0x0000000f;	
		mima3[0]=mima[3]+0x30;
		mima3[1]='\0';

display_ASCIIstring_8x16(1,96,mima0);
display_ASCIIstring_8x16(1,104,mima1);
display_ASCIIstring_8x16(1,112,mima2);
display_ASCIIstring_8x16(1,120,mima3);
		   
	if(((key_state >> 16)&0x0f)==0)
	{
	  mima[0]=((key_state>>12)&0x0000000f);//���������ֵ	
		mima0[0]=mima[0]+0x30;
		mima0[1]='\0';
		display_ASCIIstring_8x16_fanxian(1,96,mima0);
	}

	else if(((key_state >> 16)&0x0f)==1)
	{
		
	  mima[1]=((key_state>>8)&0x0000000f);	
		mima1[0]=mima[1]+0x30;
		mima1[1]='\0';
		display_ASCIIstring_8x16_fanxian(1,104,mima1);
	}
	else if(((key_state >> 16)&0x0f)==2)
	{
	  mima[2]=((key_state>>4)&0x0000000f);
		mima2[0]=mima[2]+0x30;
		mima2[1]='\0';
		display_ASCIIstring_8x16_fanxian(1,112,mima2);
		
	}
	else if(((key_state >> 16)&0x0f)==3)
	{
	  mima[3]=key_state&0x0000000f;	
		mima3[0]=mima[3]+0x30;
		mima3[1]='\0';
		display_ASCIIstring_8x16_fanxian(1,120,mima3);
		
	}
		

	 Lcd12864_Write16CnCHAR(0,0,3,"20ͨ�ŵ�ַ\r");
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
				display_ASCIIstring_8x16(6,118,add_1_2);
}



