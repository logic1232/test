/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
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
#include "main.h"
#include "adc.h"
#include "rtc.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "dma.h"
#include "factor.h"
#include "delay.h"
#include "24cxx.h"
#include "tool.h"
#include "usart.h"
#include "lcd_usart.h"
#include "rtc.h"
#include "disp.h"
#include "24cxx.h"
#include "LCD.h"
#include "state.h"
#include "display_ziku.h"
#include "rtc.h"
#include "ht7038.h"
#include "stdio.h"
#include "stm32_dsp.h"
#include "dsp_fft.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
RTC_DateTypeDef sdatestructure;
RTC_TimeTypeDef stimestructure;

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
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
#define trip_reason_tem 0x18
#define trip_reason_anti_islanding 0x19
#define A_qy 0
// A��Ƿѹ����
#define B_qy 2
// B��Ƿѹ����
#define C_qy 4
// C��Ƿѹ����
#define A_gy 1
// A���ѹ����
#define B_gy 3
// B���ѹ����
#define C_gy 5
// C���ѹ����
#define L_hb 6
// ©�����
#define A_gl 7
// A���������
#define B_gl 8
// B���������
#define C_gl 9
// C���������
#define N_gl 0x0A
// D���������
#define Gz_TD 0x0B
// ͣ�����
// #define FZ_SD 0x0C //�ֶ���բ��δ֪��
#define FZ_UK 0x0c
// δ֪��բ
#define FZ_AJ 0x0d
// ������բ
#define FZ_YC 0x0e
// Զ�̷�բ
#define Tem_N 51
#define Tem_A 53
#define Tem_B 55
#define Tem_C 57

#define Tem_OUT_N 59
#define Tem_OUT_A 61
#define Tem_OUT_B 63
#define Tem_OUT_C 65

#define A_QX 0x10
#define B_QX 0x11
#define C_QX 0x12
#define Gz_QL 0x13
#define A_sy 0x14
#define B_sy 0x15
#define C_sy 0x16
// #define set_bit(val, bitn)    (val |=(1<<(bitn)))
#define clr_bit(val, bitn) (val &= ~(1 << (bitn)))
// #define get_bit(val, bitn)    (val &(1<<(bitn)) )
// #define neg_bit(val, bitn)    (val^=(1<<(bitn)))

extern unsigned char F_re_sta;
extern unsigned char dian[16];

// #define Trip PAout(10)// PC10
// #define Moto PAout(11)// PC11

#define Trip_LED PDout(2) // PB5

#define start HAL_GPIO_WritePin(MOTOR_GPIO_Port, MOTOR_Pin, GPIO_PIN_SET)
#define stop HAL_GPIO_WritePin(MOTOR_GPIO_Port, MOTOR_Pin, GPIO_PIN_RESET)

#define Trip_ON HAL_GPIO_WritePin(TRIP_GPIO_Port, TRIP_Pin, GPIO_PIN_SET)
#define Trip_OFF HAL_GPIO_WritePin(TRIP_GPIO_Port, TRIP_Pin, GPIO_PIN_RESET)

// #define Trip_LED_ON    HAL_GPIO_WritePin(TRIP_LED_GPIO_Port, TRIP_LED_Pin, GPIO_PIN_RESET)
// #define Trip_LED_OFF   HAL_GPIO_WritePin(TRIP_LED_GPIO_Port, TRIP_LED_Pin, GPIO_PIN_SET)

#define RS485_RX_EN HAL_GPIO_WritePin(RS485_TX_EN_GPIO_Port, RS485_TX_EN_Pin, GPIO_PIN_SET)   // ����Ϊ����ģʽ
#define RS485_TX_EN HAL_GPIO_WritePin(RS485_TX_EN_GPIO_Port, RS485_TX_EN_Pin, GPIO_PIN_RESET) // ����Ϊ����ģʽ

#define Leak_Test_HIGH HAL_GPIO_WritePin(Leak_Test_GPIO_Port,Leak_Test_Pin,GPIO_PIN_SET)
#define Leak_Test_LOW HAL_GPIO_WritePin(Leak_Test_GPIO_Port,Leak_Test_Pin,GPIO_PIN_RESET)

// #define LEDA     PBout(13) //SDA
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
// ADC_HandleTypeDef hadc1;
//  DMA_HandleTypeDef hdma_adc1;

// IWDG_HandleTypeDef hiwdg;

// RTC_HandleTypeDef hrtc;

// TIM_HandleTypeDef htim6;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

void SystemClock_Config(void);
// static void MX_GPIO_Init(void);
// static void MX_DMA_Init(void);
// static void MX_ADC1_Init(void);
// static void MX_IWDG_Init(void);
//// static void MX_RTC_Init(void);
// static void MX_TIM6_Init(void);
//  static void MX_USART3_UART_Init(void);
extern unsigned char temp_frame[32];
extern unsigned char frame1[32];
extern unsigned char frame2[32];
u8 at[3];
unsigned int cur_handle_A(unsigned int x);
unsigned int cur_handle_B(unsigned int x);
unsigned int cur_handle_C(unsigned int x);
unsigned int leak_handle(unsigned int x);
unsigned char TEM;
// unsigned 	F_turn_need=0;
unsigned char buff_tap[15] = {0};
unsigned char test_shuju[15] = {0};
extern unsigned char shangdian, duandian, jiaozhun;
unsigned char F_Sample, F_sy_sucess, F_leak_disp = 0, F_2d_trip, F_3d_trip;
unsigned char F_record_write = 0;
void num_handle(unsigned int x);
extern unsigned char tim_disp[7], tim_m, tim_d, tim_h, tim_f, tim_s, sssj_N, sssj_N_xunhuan;
extern unsigned char display_graphic_8x16(unsigned char page, unsigned char column, unsigned char *dp);
extern volatile unsigned char tim_m2, tim_d2, tim_h2, tim_f2, tim_s2;
extern volatile unsigned int tim_y2;
// extern volatile unsigned long int Leak_Cur_Sum1 ;
extern unsigned int tim_y;
extern unsigned int key_connter;
unsigned int Lcd_Count = 0;
extern unsigned char zifu_dian[4];
void data_clear(void);
void hongwai_SendData(unsigned char Data);
void TIM2_PWM_Init(u16 arr, u16 psc);
// void hongwai_Send_Data(u8 *buf,u8 len);
extern unsigned char zuokuohao[4];
extern unsigned char youkuohao[4];
extern volatile unsigned long int A_C_Sum, B_C_Sum, C_C_Sum;
volatile unsigned long int cnt_array4[128], kk = 0, kkk = 0, cnt_array5[64], cnt_array6[64], lll = 0, F_C;
extern void MenuOperate(unsigned char key);
unsigned char F_shishi = 0;
void write_tingdian(void);
extern unsigned char disp_status1;
extern char F_initialize;     //CJM
extern unsigned char mima[4];     // 2022.2.21���ݼ����빦�ܣ��������������飬���ڴ�Ű������������
extern unsigned char mima_set[4]; // �û��趨�����룬���������������ȶ�

extern unsigned char TXJZ_start; // ͨѶУ׼��ʼ��־λ0������1��ʼ
extern unsigned char TXJZ_SJ;    // ͨѶʱ��
// unsigned char TXJZ_DY=0;//ͨѶ��ѹ
extern unsigned char TXJZ_LD; // ͨѶ©��

extern unsigned char TXJZ_DL_A; // ͨѶ����A
extern unsigned char TXJZ_DL_B; // ͨѶ����B
extern unsigned char TXJZ_DL_C; // ͨѶ����C

extern unsigned char TXJZ_DY_A;                                               // ͨѶ��ѹA
extern unsigned char TXJZ_DY_B;                                               // ͨѶ��ѹB
extern unsigned char TXJZ_DY_C;                                               // ͨѶ��ѹC
unsigned char Read_variable_vol(unsigned char fact_tmp, unsigned char lenth); // �����ز�ʱ������û��ʵ����;��ɾ��
unsigned int Point_i, Point_j, Point_k;
unsigned char First_menu = 0, lenth_piont = 5, Cross_Zero_A[2] = {0}, Cross_Zero_B[2] = {0}, Cross_Zero_C[2] = {0}, Samp_first_flag = 1;
extern volatile unsigned long int A_C_Sum, B_C_Sum, C_C_Sum, I_A_Sum, I_B_Sum, I_C_Sum;

unsigned char fenzha_chenggong; // ������բ�ɹ���־0x11Ϊ�ɹ�
extern unsigned char F_queren;
void IWDG_Init(u8 prer, u16 rlr);
void initial_lcd(void);
void initial_lcd1(void);
void initial_lcd_guanjiao(void);
void D3_A_BH_Process(void);
void D3_B_BH_Process(void);
void D3_C_BH_Process(void);
void DW_3D_init(void);
void DW_3D_E2_read(void);
void IWDG_Feed(void);
void Get_A_C(void);
void Get_B_C(void);
void Get_C_C(void);
void D3_BH_Process(void);
void long_process(void);
void institution_init(void);
void My_USART1_Init(void);
void init_devices(void);
void EXTIX_Init(void);
void Wait_selftest(void);
void At24cxxWriteLenByte(u16 WriteAddr, u32 DataToWrite, u8 Len);
void Nomal_Process(void);
void Power_Process(void);
void short_process(void);
void state_init(void);
void clear_flags(void);
void factors_init(void);
void external_E2_read(void);
void USART_LCD_Transmit(unsigned short len, unsigned char ch);
void factor_first_init(unsigned char tmp);
void ctrlword1_analyze(void);
void ctrlword2_analyze(void);
void ctrlword3_analyze(void);
void ctrlword4_analyze(void);
void ctrlword5_analyze(void);
void Cur_Switch(unsigned char Type_Cur);
void TIM3_Int_Init(u16 arr, u16 psc);
void Flag_Updata(void);
void Conter_Updata(void);
void Get_L(void);
void Leak_process(void);
void Lackzero_judge(void);
void V_Sample(unsigned char tmp);
void Cur_sample_process(void);
void Vol_sample_process(void);
void Cur_Sample(unsigned char tmp);
unsigned char loss_phase_trip(unsigned char phase_tmp);
void Record_data_propare(void);
void V_max_process(unsigned char tmp);
void V_min_process(unsigned char tmp);
void Write_V(unsigned char tmp, unsigned int factor1, unsigned char factor2);
void Leak_max_process(void);
void Leak_min_process(void);
void I_max_process(unsigned char tmp);
void I_min_process(unsigned char tmp);
void Write_I(unsigned char tmp, unsigned int factor1, unsigned char factor2);
void Auto_Leak_process(void);
void Normal_Leak_process(void);
void zha_position_init(void);
void c_hezha(void);
unsigned char Trip_Action(void);
void Trip_Process_time(unsigned char tmp);
void rms_make(unsigned char i);
void V_Sample_C(unsigned char tmp);
void Cur_Sample_C(unsigned char tmp);
void Leak_Over_process(void);
void V_Sample_A(void);
void V_Sample_B(void);
void V_Sample_CC(void);
unsigned int vol_handle_A(unsigned int value);
unsigned int vol_handle_B(unsigned int value);
unsigned int vol_handle_C(unsigned int value);
unsigned int vol_handle(unsigned int value);
unsigned int vol_handle_undervol(unsigned int value);
unsigned int vol_handle_anti_islanding_A(unsigned int value);  //���µ���ѹA�ദ����
unsigned int vol_handle_anti_islanding_B(unsigned int value); 
unsigned int vol_handle_anti_islanding_C(unsigned int value); 

unsigned int cur_actionhandle_A(unsigned int x);
unsigned int cur_actionhandle_B(unsigned int x);
unsigned int cur_actionhandle_C(unsigned int x);

unsigned int L_adjust_slope; // 2021.12.26����©��ֵ��б�ʣ�250��400��ͬ

void D3_A_Quick_Process(void);
void D3_B_Quick_Process(void);
void D3_C_Quick_Process(void);

// volatile signed int AD_tmp_V=0;
void hongwai_com_process(void);
void low_vol_SD_process(void);
void Day_updata_process(void);
void hand_short_process(void);
void Record_V(unsigned char tmp, unsigned int factor1, unsigned char factor2);

void mima_input(void);
void mima_check(void);
void mima_change(void);
void Event_clear(void);
void EEPROM_C(unsigned int AT24C64_address, unsigned int count, unsigned char SelectAddr);
void data_clear(void);
void vol_abnormal_check(void);
unsigned int Tem_Array_AD[8], Tem_value[8];
void Temperature_Process(void);
unsigned int get_adc(unsigned int ch);
void Temperature_UP(void);
void Temperature_DOWN(void);

unsigned int Ugain_A, Ugain_B, Ugain_C, Igain_A, Igain_B, Igain_C, Pgain_AA, Pgain_BB, Pgain_CC, Uoffset_A, Uoffset_B, Uoffset_C, Ioffset_A, Ioffset_B, Ioffset_C, Ioffset_ABC; // ht7038
unsigned char cal(void);
float Pgain_A, Pgain_B, Pgain_C; // ht7038
uint8_t LCD_start = 0;
void Read_addr(void);

extern long lBUFOUT[256];
extern long lBUFIN[256];

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

// ���������������ֵ�ĺ���
int max_of_three(int a, int b, int c) {
    int max = a;
    if (b > max) {
        max = b;
    }
    if (c > max) {
        max = c;
    }
    return max;
}

void Delay(u32 count)
{
    u32 i = 0;
    for (; i < count; i++)
        ;
}

void ctrlword1_analyze(void)
{
    F_dataalarm_all = (ctrlword[0] & 0x40) >> 6; // ���ݸ澯
    F_lightalarm = (ctrlword[0] & 0x20) >> 5;    // �ƹ�澯
    F_voicealarm = (ctrlword[0] & 0x10) >> 4;    // ��������
    F_timealarm = (ctrlword[0] & 0x08) >> 3;     // ��ʱ����
    F_classreturn = (ctrlword[0] & 0x04) >> 2;   // ��λ����
    F_chonghezha = (ctrlword[0] & 0x02) >> 1;    // �غ�բ
    // �����ʱ�������ܴ�
    if (F_timealarm == 1)
    {
        F_time_compare = 1;
    }
    else
    {
        F_time_compare = 0;
    }
}
void ctrlword2_analyze(void)
{
    F_dataalarm_qy = (ctrlword[1] & 0x80) >> 7; // Ƿѹ��������բ����
    F_trip_qy = (ctrlword[1] & 0x40) >> 6;
    F_dataalarm_gy = (ctrlword[1] & 0x20) >> 5;
    F_trip_gy = (ctrlword[1] & 0x10) >> 4;
    F_dataalarm_xq = (ctrlword[1] & 0x08) >> 3;
    F_trip_QX = (ctrlword[1] & 0x04) >> 2;
    F_trip_gl = (ctrlword[1] & 0x01) >> 0;
}
void ctrlword3_analyze(void)
{
    F_trip_QL = (ctrlword[2] & 0x01) >> 0; // ȱ�㱣������բ����
}
void ctrlword4_analyze(void)
{
    unsigned char F_GJ_FUNC_tmp, E2_arraymrnow_tmp[5];
    unsigned char array_temp[1];
    D_LCur = (ctrlword[3] >> 4); // ʣ�������λ��ȡ������λ
    //	TH_LCur=((ctrlword[3]&0x0C)>>2);//ȡ������λ  ����޲�����ʱ��
    F_GJ_FUNC_tmp = (ctrlword[3] & 0x03); // ʣ���������ʱ��

    EEPROM_R(Addr_TH_LCur, array_temp, 1, 0xA0);
    TH_LCur = array_temp[0];

    if (D_LCur > 7)
    {
        D_LCur = 0x07;
        ctrlword[3] &= 0x0F;
        ctrlword[3] += (D_LCur << 4);

        MODIFY_EEP_W(Addr_crtl_word4, &ctrlword[3], 1, 0xA0);
    }
    if (D_LCur == 8)
    {
        D_A_LCur = 11;
        // D_A_LCur©���Զ����ٵ�λ  //�趨����ߵ�λ
        Id1_A = D_ACur_Array[D_A_LCur];
        // ���±Ƚ�ֵ
        Id1_L = H_A_L[D_A_LCur];
        // ����Ӧ����ֵ�����������л���λ
        Id1_H = H_A_H[D_A_LCur];
        // ����Ӧ����ֵ�����������л���λ
    }
    else
    {
        Id1 = D_LCur1_Array[D_LCur];
        // ����©�綯����λ��ȷ�����������Ƚ�����
        Id2 = D_LCur2_Array[D_LCur];
        Id3 = D_LCur3_Array[D_LCur];
    }
    if (TH_LCur > 4) // ����޲�����ʱ��
    {
        unsigned char array_tmp[1];
        TH_LCur = 4;
        //		ctrlword[3]&=0xF3 ;
        //		ctrlword[3]+=(TH_LCur<<4);
        //
        //		MODIFY_EEP_W(Addr_crtl_word4,&ctrlword[3],1,0xA0);

        array_tmp[0] = TH_LCur;
        MODIFY_EEP_W(Addr_TH_LCur, array_tmp, 1, 0xA0);
    }
    N_TH = TD_LCur1_Array[TH_LCur];
    // ����©�綯��ʱ�䵵λ��ȷ������ʱ��Ƚ�����
    N_TH2 = TD_LCur2_Array[TH_LCur];
    N_TH3 = TD_LCur3_Array[TH_LCur];

    // �澯�رգ������ѿ�
    if (F_GJ_FUNC_tmp == 0x00)
    {
        F_GJ_FUNC = F_GJ_FUNC_tmp;
        F_trip_ld = 0;
    }
    // �澯����24Сʱ����رգ�����
    else if (F_GJ_FUNC_tmp == 0x01)
    {
        if (F_GJ_FUNC == 0x00)
        {
            F_GJ_FUNC = F_GJ_FUNC_tmp;
            Num_leakquit = Num_leakquit + 1;
            if (Num_leakquit > 10000)
                Num_leakquit = 0;
            DectoBCD(E2_arraymrnow_tmp, Num_leakquit, 2);

            MODIFY_EEP_W(Addr_leakquit_num, E2_arraymrnow_tmp, 2, 0xA0); // ©�����˴���д��E2��
            //			AT24C64_W(E2_arraymrnow_tmp,Addr_leakquit_num+200,2);
        }
        F_trip_ld = 1;
    }
    // �澯�������ã�����
    else if (F_GJ_FUNC_tmp == 0x02)
    {
        if (F_GJ_FUNC == 0x00)
        {
            F_GJ_FUNC = F_GJ_FUNC_tmp;
            Num_leakquit = Num_leakquit + 1;
            if (Num_leakquit > 10000)
                Num_leakquit = 0;
            DectoBCD(E2_arraymrnow_tmp, Num_leakquit, 2);

            MODIFY_EEP_W(Addr_leakquit_num, E2_arraymrnow_tmp, 2, 0xA0);
            //			AT24C64_W(E2_arraymrnow_tmp,Addr_leakquit_num+200,1);
        }
        F_trip_ld = 1;
    }
    // ����
    else
    {
        F_GJ_FUNC = F_GJ_FUNC_tmp;
    }
}

void ctrlword5_analyze(void)
{
    // EEPROM_W(&ctrlword[4],Addr_crtl_word5,1);
    LC_N = ctrlword[4] & 0x03;
    if (LC_N > 3)
    {
        LC_N = 3;
        ctrlword[4] &= 0xFC;
        ctrlword[4] += LC_N;
        MODIFY_EEP_W(Addr_crtl_word5, &ctrlword[4], 1, 0xA0);
    }
    if (LC_N == 0) // ���غ�բ
    {
        F_la = 0;
        F_la2 = 0;
        F_la1 = 0;
    }
    else if (LC_N == 1) // һ���غ�բ
    {
        F_la = 1;
        F_la2 = 0;
        F_la1 = 0;
    }
    else if (LC_N == 2) // �����غ�բ
    {
        F_la = F_la2 = 1;
        F_la1 = 0;
    }
    else // �������غ�բ
    {
        F_la = 1;
        F_la2 = 0;
        F_la1 = 1;
    }
}

void vol_abnormal_check(void)
{

    unsigned char array_temp[2];

    //	  EEPROM_R(Addr_V1_A_slope,array_temp,2,0xA0);
    //	  if((array_temp[1]>0x59)||(array_temp[1]<0x45))
    //		{

    array_temp[0] = 0x65;
    array_temp[1] = 0x48;
    MODIFY_EEP_W(Addr_V1_A_slope, array_temp, 2, 0xA0);
    delay_ms(5);
    EEPROM_R(Addr_V1_A_slope, array_temp, 2, 0xA0);
    delay_ms(5);
    //		}
    V1_slope[0] = (array_temp[1] << 8) + array_temp[0];

    //	  EEPROM_R(Addr_V1_B_slope,array_temp,2,0xA0);
    //	  if((array_temp[1]>0x59)||(array_temp[1]<0x45))
    //		{

    array_temp[0] = 0x00;
    array_temp[1] = 0x48;

    MODIFY_EEP_W(Addr_V1_B_slope, array_temp, 2, 0xA0);
    delay_ms(5);
    EEPROM_R(Addr_V1_B_slope, array_temp, 2, 0xA0);
    delay_ms(5);

    //		}

    V1_slope[1] = (array_temp[1] << 8) + array_temp[0];

    //    EEPROM_R(Addr_V1_C_slope,array_temp,2,0xA0);
    //	  if((array_temp[1]>0x59)||(array_temp[1]<0x45))
    //		{
    //

    array_temp[0] = 0x03;
    array_temp[1] = 0x48;
    MODIFY_EEP_W(Addr_V1_C_slope, array_temp, 2, 0xA0);
    delay_ms(5);
    EEPROM_R(Addr_V1_C_slope, array_temp, 2, 0xA0);
    delay_ms(5);
    //		}
    V1_slope[2] = (array_temp[1] << 8) + array_temp[0];
}

void factors_init(void)
{
    IWDG_Feed(); // ι��
    unsigned char array_temp[10];
    /*****************������Ϣ����****************************/
    EEPROM_R(Addr_FACTORINIT_value, &array_temp[0], 2, 0xA0); // ���ⲿ��־����
    if ((array_temp[0] == 0x55) && (array_temp[1] == 0xAA))   // ����������ɹ�
    {
        IWDG_Feed(); // ι��
        external_E2_read();
    }
    else // ���������ȡ���ɹ���ִ������ɴ�
    {
        IWDG_Feed();
        factor_first_init(0);
        IWDG_Feed();
        external_E2_read();
    }
}
void Read_Cur_calibrae_data(void)
{
    unsigned char i;
    unsigned char array_temp[30];
    /**************************������ADֵ************************/
    AT24CXX_ReadLongByte(Addr_Cur_250, 24, array_temp, 0xA0);
    delay_ms(5);
    for (char i = 0; i < 4; i++)
    {
        unsigned char j;
        j = i << 1;
        Cur_A_temp[i] = (array_temp[j + 1] << 8) + array_temp[j];
        Cur_B_temp[i] = (array_temp[j + 9] << 8) + array_temp[j + 8];
        Cur_C_temp[i] = (array_temp[j + 17] << 8) + array_temp[j + 16];
    }
    /*******************************������б��******************************/

    AT24CXX_ReadLongByte(Addr_Cur_slope_250, 24, array_temp, 0xA0);
    delay_ms(5);

    for (char i = 0; i < 4; i++)
    {
        unsigned char j;
        j = i << 1;
        I_A_slope[i] = (array_temp[j + 1] << 8) + array_temp[j];
        I_B_slope[i] = (array_temp[j + 9] << 8) + array_temp[j + 8];
        I_C_slope[i] = (array_temp[j + 17] << 8) + array_temp[j + 16];
    }
    /****************************������У׼��ֵ*************************/

    AT24CXX_ReadLongByte(Addr_Cur_Disp_250, 24, array_temp, 0xA0);
    delay_ms(5);
    for (char i = 0; i < 4; i++)
    {
        unsigned char j;
        j = i << 1;
        Cur_A_disp[i] = (array_temp[j + 1] << 8) + array_temp[j];
        Cur_B_disp[i] = (array_temp[j + 9] << 8) + array_temp[j + 8];
        Cur_C_disp[i] = (array_temp[j + 17] << 8) + array_temp[j + 16];
    }
    AT24CXX_ReadLongByte(Addr_Leak_ad, 4, array_temp, 0xA0);
    for (char i = 0; i < 3; i++)
    {
        unsigned char j;
        j = i << 1;
        Leak_temp[i] = (array_temp[j + 1] << 8) + array_temp[j];
    }

    AT24CXX_ReadLongByte(Addr_Leak_slope, 4, array_temp, 0xA0);
    delay_ms(5);
    for (char i = 0; i < 3; i++)
    {
        unsigned char j;
        j = i << 1;
        L_slope[i] = (array_temp[j + 1] << 8) + array_temp[j];
    }
}

void Read_SD_Cur_calibrae_data(void)
{
    IWDG_Feed();
    unsigned char array_temp[30];
    if (Type_Cur == 0)
    {
        AT24CXX_ReadLongByte(Addr_DLS_Cur_IV_AD_value, 15, array_temp, 0xA0); // 800�Ǽ�˲��

        DLS_Cur_IV_AD_value[0] = ChartoHex(&array_temp[0], 3); // ADֵ
        DLS_Cur_IV_AD_value[1] = ChartoHex(&array_temp[3], 3);
        DLS_Cur_IV_AD_value[2] = ChartoHex(&array_temp[6], 3);
        DLS_Cur_IV_AD_value[3] = ChartoHex(&array_temp[9], 3);
        DLS_Cur_IV_AD_value[4] = ChartoHex(&array_temp[12], 3);

        AT24CXX_ReadLongByte(Addr_DLS_Cur_IV_slope, 15, array_temp, 0xA0);

        DLS_Cur_IV_slope[0] = ChartoHex(&array_temp[0], 3); // б��ֵ
        DLS_Cur_IV_slope[1] = ChartoHex(&array_temp[3], 3);
        DLS_Cur_IV_slope[2] = ChartoHex(&array_temp[6], 3);
        DLS_Cur_IV_slope[3] = ChartoHex(&array_temp[9], 3);
        DLS_Cur_IV_slope[4] = ChartoHex(&array_temp[12], 3);

        AT24CXX_ReadLongByte(Addr_DLS_Cur_IV_Value, 15, array_temp, 0xA0);

        DLS_Cur_IV_Value[0] = ChartoHex(&array_temp[0], 3); // ����ֵ
        DLS_Cur_IV_Value[1] = ChartoHex(&array_temp[3], 3);
        DLS_Cur_IV_Value[2] = ChartoHex(&array_temp[6], 3);
        DLS_Cur_IV_Value[3] = ChartoHex(&array_temp[9], 3);
        DLS_Cur_IV_Value[4] = ChartoHex(&array_temp[12], 3);
    }

    if (Type_Cur == 1)
    {
        AT24CXX_ReadLongByte(Addr_DLS_Cur_I_AD_value, 15, array_temp, 0xA0); // 250�Ǽ�˲��

        DLS_Cur_I_AD_value[0] = ChartoHex(&array_temp[0], 3);
        DLS_Cur_I_AD_value[1] = ChartoHex(&array_temp[3], 3);
        DLS_Cur_I_AD_value[2] = ChartoHex(&array_temp[6], 3);
        DLS_Cur_I_AD_value[3] = ChartoHex(&array_temp[9], 3);
        DLS_Cur_I_AD_value[4] = ChartoHex(&array_temp[12], 3);

        AT24CXX_ReadLongByte(Addr_DLS_Cur_I_slope, 15, array_temp, 0xA0);

        DLS_Cur_I_slope[0] = ChartoHex(&array_temp[0], 3);
        DLS_Cur_I_slope[1] = ChartoHex(&array_temp[3], 3);
        DLS_Cur_I_slope[2] = ChartoHex(&array_temp[6], 3);
        DLS_Cur_I_slope[3] = ChartoHex(&array_temp[9], 3);
        DLS_Cur_I_slope[4] = ChartoHex(&array_temp[12], 3);

        AT24CXX_ReadLongByte(Addr_DLS_Cur_I_Value, 15, array_temp, 0xA0);

        DLS_Cur_I_Value[0] = ChartoHex(&array_temp[0], 3);
        DLS_Cur_I_Value[1] = ChartoHex(&array_temp[3], 3);
        DLS_Cur_I_Value[2] = ChartoHex(&array_temp[6], 3);
        DLS_Cur_I_Value[3] = ChartoHex(&array_temp[9], 3);
        DLS_Cur_I_Value[4] = ChartoHex(&array_temp[12], 3);
    }

    if (Type_Cur == 2)
    {
        AT24CXX_ReadLongByte(Addr_DLS_Cur_II_AD_value, 15, array_temp, 0xA0); // 400�Ǽ�˲��

        DLS_Cur_II_AD_value[0] = ChartoHex(&array_temp[0], 3);
        DLS_Cur_II_AD_value[1] = ChartoHex(&array_temp[3], 3);
        DLS_Cur_II_AD_value[2] = ChartoHex(&array_temp[6], 3);
        DLS_Cur_II_AD_value[3] = ChartoHex(&array_temp[9], 3);
        DLS_Cur_II_AD_value[4] = ChartoHex(&array_temp[12], 3);

        AT24CXX_ReadLongByte(Addr_DLS_Cur_II_slope, 15, array_temp, 0xA0);

        DLS_Cur_II_slope[0] = ChartoHex(&array_temp[0], 3);
        DLS_Cur_II_slope[1] = ChartoHex(&array_temp[3], 3);
        DLS_Cur_II_slope[2] = ChartoHex(&array_temp[6], 3);
        DLS_Cur_II_slope[3] = ChartoHex(&array_temp[9], 3);
        DLS_Cur_II_slope[4] = ChartoHex(&array_temp[12], 3);

        AT24CXX_ReadLongByte(Addr_DLS_Cur_II_Value, 15, array_temp, 0xA0);

        DLS_Cur_II_Value[0] = ChartoHex(&array_temp[0], 3);
        DLS_Cur_II_Value[1] = ChartoHex(&array_temp[3], 3);
        DLS_Cur_II_Value[2] = ChartoHex(&array_temp[6], 3);
        DLS_Cur_II_Value[3] = ChartoHex(&array_temp[9], 3);
        DLS_Cur_II_Value[4] = ChartoHex(&array_temp[12], 3);
    }

    if (Type_Cur == 3)
    {
        AT24CXX_ReadLongByte(Addr_DLS_Cur_III_AD_value, 15, array_temp, 0xA0); // 630�Ǽ�˲��

        DLS_Cur_III_AD_value[0] = ChartoHex(&array_temp[0], 3);
        DLS_Cur_III_AD_value[1] = ChartoHex(&array_temp[3], 3);
        DLS_Cur_III_AD_value[2] = ChartoHex(&array_temp[6], 3);
        DLS_Cur_III_AD_value[3] = ChartoHex(&array_temp[9], 3);
        DLS_Cur_III_AD_value[4] = ChartoHex(&array_temp[12], 3);

        AT24CXX_ReadLongByte(Addr_DLS_Cur_III_slope, 15, array_temp, 0xA0);

        DLS_Cur_III_slope[0] = ChartoHex(&array_temp[0], 3);
        DLS_Cur_III_slope[1] = ChartoHex(&array_temp[3], 3);
        DLS_Cur_III_slope[2] = ChartoHex(&array_temp[6], 3);
        DLS_Cur_III_slope[3] = ChartoHex(&array_temp[9], 3);
        DLS_Cur_III_slope[4] = ChartoHex(&array_temp[12], 3);

        AT24CXX_ReadLongByte(Addr_DLS_Cur_III_Value, 15, array_temp, 0xA0);

        DLS_Cur_III_Value[0] = ChartoHex(&array_temp[0], 3);
        DLS_Cur_III_Value[1] = ChartoHex(&array_temp[3], 3);
        DLS_Cur_III_Value[2] = ChartoHex(&array_temp[6], 3);
        DLS_Cur_III_Value[3] = ChartoHex(&array_temp[9], 3);
        DLS_Cur_III_Value[4] = ChartoHex(&array_temp[12], 3);
    }
}
void Read_SD_Cur_calibrae_data1(void)
{
    unsigned char array_temp[30];
    //	if(Type_Cur==0)
    {
        AT24CXX_ReadLongByte(Addr_DLS_Cur_IV_AD_value, 15, array_temp, 0xA0); // 800�Ǽ�˲��

        DLS_Cur_IV_AD_value[0] = ChartoHex(&array_temp[0], 3); // ADֵ
        DLS_Cur_IV_AD_value[1] = ChartoHex(&array_temp[3], 3);
        DLS_Cur_IV_AD_value[2] = ChartoHex(&array_temp[6], 3);
        DLS_Cur_IV_AD_value[3] = ChartoHex(&array_temp[9], 3);
        DLS_Cur_IV_AD_value[4] = ChartoHex(&array_temp[12], 3);

        AT24CXX_ReadLongByte(Addr_DLS_Cur_IV_slope, 15, array_temp, 0xA0);

        DLS_Cur_IV_slope[0] = ChartoHex(&array_temp[0], 3); // б��ֵ
        DLS_Cur_IV_slope[1] = ChartoHex(&array_temp[3], 3);
        DLS_Cur_IV_slope[2] = ChartoHex(&array_temp[6], 3);
        DLS_Cur_IV_slope[3] = ChartoHex(&array_temp[9], 3);
        DLS_Cur_IV_slope[4] = ChartoHex(&array_temp[12], 3);

        AT24CXX_ReadLongByte(Addr_DLS_Cur_IV_Value, 15, array_temp, 0xA0);

        DLS_Cur_IV_Value[0] = ChartoHex(&array_temp[0], 3); // ����ֵ
        DLS_Cur_IV_Value[1] = ChartoHex(&array_temp[3], 3);
        DLS_Cur_IV_Value[2] = ChartoHex(&array_temp[6], 3);
        DLS_Cur_IV_Value[3] = ChartoHex(&array_temp[9], 3);
        DLS_Cur_IV_Value[4] = ChartoHex(&array_temp[12], 3);
    }

    //		if(Type_Cur==1)
    {
        AT24CXX_ReadLongByte(Addr_DLS_Cur_I_AD_value, 15, array_temp, 0xA0); // 250�Ǽ�˲��

        DLS_Cur_I_AD_value[0] = ChartoHex(&array_temp[0], 3);
        DLS_Cur_I_AD_value[1] = ChartoHex(&array_temp[3], 3);
        DLS_Cur_I_AD_value[2] = ChartoHex(&array_temp[6], 3);
        DLS_Cur_I_AD_value[3] = ChartoHex(&array_temp[9], 3);
        DLS_Cur_I_AD_value[4] = ChartoHex(&array_temp[12], 3);

        AT24CXX_ReadLongByte(Addr_DLS_Cur_I_slope, 15, array_temp, 0xA0);

        DLS_Cur_I_slope[0] = ChartoHex(&array_temp[0], 3);
        DLS_Cur_I_slope[1] = ChartoHex(&array_temp[3], 3);
        DLS_Cur_I_slope[2] = ChartoHex(&array_temp[6], 3);
        DLS_Cur_I_slope[3] = ChartoHex(&array_temp[9], 3);
        DLS_Cur_I_slope[4] = ChartoHex(&array_temp[12], 3);

        AT24CXX_ReadLongByte(Addr_DLS_Cur_I_Value, 15, array_temp, 0xA0);

        DLS_Cur_I_Value[0] = ChartoHex(&array_temp[0], 3);
        DLS_Cur_I_Value[1] = ChartoHex(&array_temp[3], 3);
        DLS_Cur_I_Value[2] = ChartoHex(&array_temp[6], 3);
        DLS_Cur_I_Value[3] = ChartoHex(&array_temp[9], 3);
        DLS_Cur_I_Value[4] = ChartoHex(&array_temp[12], 3);
    }

    //		if(Type_Cur==2)
    {
        AT24CXX_ReadLongByte(Addr_DLS_Cur_II_AD_value, 15, array_temp, 0xA0); // 400�Ǽ�˲��

        DLS_Cur_II_AD_value[0] = ChartoHex(&array_temp[0], 3);
        DLS_Cur_II_AD_value[1] = ChartoHex(&array_temp[3], 3);
        DLS_Cur_II_AD_value[2] = ChartoHex(&array_temp[6], 3);
        DLS_Cur_II_AD_value[3] = ChartoHex(&array_temp[9], 3);
        DLS_Cur_II_AD_value[4] = ChartoHex(&array_temp[12], 3);

        AT24CXX_ReadLongByte(Addr_DLS_Cur_II_slope, 15, array_temp, 0xA0);

        DLS_Cur_II_slope[0] = ChartoHex(&array_temp[0], 3);
        DLS_Cur_II_slope[1] = ChartoHex(&array_temp[3], 3);
        DLS_Cur_II_slope[2] = ChartoHex(&array_temp[6], 3);
        DLS_Cur_II_slope[3] = ChartoHex(&array_temp[9], 3);
        DLS_Cur_II_slope[4] = ChartoHex(&array_temp[12], 3);

        AT24CXX_ReadLongByte(Addr_DLS_Cur_II_Value, 15, array_temp, 0xA0);

        DLS_Cur_II_Value[0] = ChartoHex(&array_temp[0], 3);
        DLS_Cur_II_Value[1] = ChartoHex(&array_temp[3], 3);
        DLS_Cur_II_Value[2] = ChartoHex(&array_temp[6], 3);
        DLS_Cur_II_Value[3] = ChartoHex(&array_temp[9], 3);
        DLS_Cur_II_Value[4] = ChartoHex(&array_temp[12], 3);
    }

    //		if(Type_Cur==3)
    {
        AT24CXX_ReadLongByte(Addr_DLS_Cur_III_AD_value, 15, array_temp, 0xA0); // 630�Ǽ�˲��

        DLS_Cur_III_AD_value[0] = ChartoHex(&array_temp[0], 3);
        DLS_Cur_III_AD_value[1] = ChartoHex(&array_temp[3], 3);
        DLS_Cur_III_AD_value[2] = ChartoHex(&array_temp[6], 3);
        DLS_Cur_III_AD_value[3] = ChartoHex(&array_temp[9], 3);
        DLS_Cur_III_AD_value[4] = ChartoHex(&array_temp[12], 3);

        AT24CXX_ReadLongByte(Addr_DLS_Cur_III_slope, 15, array_temp, 0xA0);

        DLS_Cur_III_slope[0] = ChartoHex(&array_temp[0], 3);
        DLS_Cur_III_slope[1] = ChartoHex(&array_temp[3], 3);
        DLS_Cur_III_slope[2] = ChartoHex(&array_temp[6], 3);
        DLS_Cur_III_slope[3] = ChartoHex(&array_temp[9], 3);
        DLS_Cur_III_slope[4] = ChartoHex(&array_temp[12], 3);

        AT24CXX_ReadLongByte(Addr_DLS_Cur_III_Value, 15, array_temp, 0xA0);

        DLS_Cur_III_Value[0] = ChartoHex(&array_temp[0], 3);
        DLS_Cur_III_Value[1] = ChartoHex(&array_temp[3], 3);
        DLS_Cur_III_Value[2] = ChartoHex(&array_temp[6], 3);
        DLS_Cur_III_Value[3] = ChartoHex(&array_temp[9], 3);
        DLS_Cur_III_Value[4] = ChartoHex(&array_temp[12], 3);
    }
}

void external_E2_read(void)
{
    unsigned char i;
    unsigned char array_temp[26];
    IWDG_Feed();
    /*******************У׼ϵ��*********************/
    EEPROM_R(Addr_L_factor, array_temp, 2, 0xA0);
    L_factor = (array_temp[0] << 8) + array_temp[1];
    //	if(L_factor>15) L_factor = 15;
    //	if(L_factor<-15) L_factor = -15;
    EEPROM_R(Addr_L_F, array_temp, 1, 0xA0);
    F_cal_L = array_temp[0];

    EEPROM_R(Addr_AV_factor, array_temp, 2, 0xA0);
    V_A_factor = (array_temp[0] << 8) + array_temp[1];
    //	if(V_A_factor>15) V_factor = 15;
    //	if(V_A_factor<-15) V_factor = -15;
    EEPROM_R(Addr_AV_F, array_temp, 1, 0xA0);
    F_cal_V_A = array_temp[0];

    EEPROM_R(Addr_BV_factor, array_temp, 2, 0xA0);
    V_B_factor = (array_temp[0] << 8) + array_temp[1];
    //	if(V_A_factor>15) V_factor = 15;
    //	if(V_A_factor<-15) V_factor = -15;
    EEPROM_R(Addr_BV_F, array_temp, 1, 0xA0);
    F_cal_V_B = array_temp[0];

    EEPROM_R(Addr_CV_factor, array_temp, 2, 0xA0);
    V_C_factor = (array_temp[0] << 8) + array_temp[1];
    //	if(V_A_factor>15) V_factor = 15;
    //	if(V_A_factor<-15) V_factor = -15;
    EEPROM_R(Addr_CV_F, array_temp, 1, 0xA0);
    F_cal_V_C = array_temp[0];

    EEPROM_R(Addr_AI_factor, array_temp, 2, 0xA0);
    I_A_factor = (array_temp[0] << 8) + array_temp[1];
    //	if(I_factor>30) I_factor = 30;
    //	if(I_factor<-30) I_factor = -30;
    EEPROM_R(Addr_AI_F, array_temp, 1, 0xA0);
    F_cal_I_A = array_temp[0];

    EEPROM_R(Addr_BI_factor, array_temp, 2, 0xA0);
    I_B_factor = (array_temp[0] << 8) + array_temp[1];
    //	if(I_factor>30) I_factor = 30;
    //	if(I_factor<-30) I_factor = -30;
    EEPROM_R(Addr_BI_F, array_temp, 1, 0xA0);
    F_cal_I_B = array_temp[0];

    EEPROM_R(Addr_CI_factor, array_temp, 2, 0xA0);
    I_C_factor = (array_temp[0] << 8) + array_temp[1];
    /******************************����У׼ϵ��********************************/
    //	  EEPROM_R(Addr_L1_slope,array_temp,2,0xA0);
    //		L1_slope=(array_temp[1]<<8)+array_temp[0];
    //
    //		EEPROM_R(Addr_Leak1_temp,array_temp,2,0xA0);
    //		Leak1_temp=(array_temp[1]<<8)+array_temp[0];

    //		EEPROM_R(Addr400_L1_slope,array_temp,2,0xA0);
    //		L1_slope=(array_temp[1]<<8)+array_temp[0];
    //
    //		EEPROM_R(Addr400_Leak1_temp,array_temp,2,0xA0);
    //		Leak1_temp=(array_temp[1]<<8)+array_temp[0];

    //		EEPROM_R(Addr630_L1_slope,array_temp,2,0xA0);
    //		L1_slope=(array_temp[1]<<8)+array_temp[0];
    //
    //		EEPROM_R(Addr630_Leak1_temp,array_temp,2,0xA0);
    //		Leak1_temp=(array_temp[1]<<8)+array_temp[0];

    //		EEPROM_R(Addr800_L1_slope,array_temp,2,0xA0);
    //		L1_slope=(array_temp[1]<<8)+array_temp[0];
    //
    //		EEPROM_R(Addr800_Leak1_temp,array_temp,2,0xA0);
    //		Leak1_temp=(array_temp[1]<<8)+array_temp[0];

    EEPROM_R(Addr_V1_A_slope, array_temp, 2, 0xA0);
    V1_slope[0] = (array_temp[1] << 8) + array_temp[0];

    EEPROM_R(Addr_V1_B_slope, array_temp, 2, 0xA0);
    V1_slope[1] = (array_temp[1] << 8) + array_temp[0];

    EEPROM_R(Addr_V1_C_slope, array_temp, 2, 0xA0);
    V1_slope[2] = (array_temp[1] << 8) + array_temp[0];

    ///*************250�Ǽ�*****************/
    //		EEPROM_R(Addr_I1_A_slope,array_temp,2,0xA0);
    //		I1_A_slope[0]=(array_temp[1]<<8)+array_temp[0];
    //
    //		EEPROM_R(Addr_I1_B_slope,array_temp,2,0xA0);
    //		I1_B_slope[0]=(array_temp[1]<<8)+array_temp[0];
    //
    //		EEPROM_R(Addr_I1_C_slope,array_temp,2,0xA0);
    //		I1_C_slope[0]=(array_temp[1]<<8)+array_temp[0];

    //		EEPROM_R(Addr_I1_A_slope1,array_temp,2,0xA0);
    //		I1_A_slope[1]=(array_temp[1]<<8)+array_temp[0];
    //
    //		EEPROM_R(Addr_I1_B_slope1,array_temp,2,0xA0);
    //		I1_B_slope[1]=(array_temp[1]<<8)+array_temp[0];
    //
    //		EEPROM_R(Addr_I1_C_slope1,array_temp,2,0xA0);
    //		I1_C_slope[1]=(array_temp[1]<<8)+array_temp[0];

    //
    //		EEPROM_R(Addr_CurA_cal_tmp,array_temp,2,0xA0);
    //		CurA_cal_tmp[0]=(array_temp[1]<<8)+array_temp[0];
    //
    //    EEPROM_R(Addr_CurB_cal_tmp,array_temp,2,0xA0);
    //		CurB_cal_tmp[0]=(array_temp[1]<<8)+array_temp[0];
    //
    //    EEPROM_R(Addr_CurC_cal_tmp,array_temp,2,0xA0);
    //		CurC_cal_tmp[0]=(array_temp[1]<<8)+array_temp[0];

    //    EEPROM_R(Addr_CurA_cal_tmp1,array_temp,2,0xA0);
    //		CurA_cal_tmp[1]=(array_temp[1]<<8)+array_temp[0];
    //
    //		EEPROM_R(Addr_CurB_cal_tmp1,array_temp,2,0xA0);
    //		CurB_cal_tmp[1]=(array_temp[1]<<8)+array_temp[0];
    //
    //		EEPROM_R(Addr_CurC_cal_tmp1,array_temp,2,0xA0);
    //		CurC_cal_tmp[1]=(array_temp[1]<<8)+array_temp[0];
    //
    EEPROM_R(Addr_Vol1_A_temp, array_temp, 2, 0xA0);
    Vol1_A_temp = (array_temp[1] << 8) + array_temp[0];
    EEPROM_R(Addr_Vol1_B_temp, array_temp, 2, 0xA0);
    Vol1_B_temp = (array_temp[1] << 8) + array_temp[0];
    EEPROM_R(Addr_Vol1_C_temp, array_temp, 2, 0xA0);
    Vol1_C_temp = (array_temp[1] << 8) + array_temp[0];
    ///*************400�Ǽ�*****************/
    //		EEPROM_R(Addr400_I1_A_slope,array_temp,2,0xA0);
    //		I1_400A_slope[0]=(array_temp[1]<<8)+array_temp[0];
    //
    //		EEPROM_R(Addr400_I1_B_slope,array_temp,2,0xA0);
    //		I1_400B_slope[0]=(array_temp[1]<<8)+array_temp[0];
    //
    //		EEPROM_R(Addr400_I1_C_slope,array_temp,2,0xA0);
    //		I1_400C_slope[0]=(array_temp[1]<<8)+array_temp[0];

    //		EEPROM_R(Addr400_I1_A_slope1,array_temp,2,0xA0);
    //		I1_400A_slope[1]=(array_temp[1]<<8)+array_temp[0];
    //
    //		EEPROM_R(Addr400_I1_B_slope1,array_temp,2,0xA0);
    //		I1_400B_slope[1]=(array_temp[1]<<8)+array_temp[0];
    //
    //		EEPROM_R(Addr400_I1_C_slope1,array_temp,2,0xA0);
    //		I1_400C_slope[1]=(array_temp[1]<<8)+array_temp[0];

    //
    //		EEPROM_R(Addr400_CurA_cal_tmp,array_temp,2,0xA0);
    //		CurA400_cal_tmp[0]=(array_temp[1]<<8)+array_temp[0];
    //
    //    EEPROM_R(Addr400_CurB_cal_tmp,array_temp,2,0xA0);
    //		CurB400_cal_tmp[0]=(array_temp[1]<<8)+array_temp[0];
    //
    //    EEPROM_R(Addr400_CurC_cal_tmp,array_temp,2,0xA0);
    //		CurC400_cal_tmp[0]=(array_temp[1]<<8)+array_temp[0];

    //    EEPROM_R(Addr400_CurA_cal_tmp1,array_temp,2,0xA0);
    //		CurA400_cal_tmp[1]=(array_temp[1]<<8)+array_temp[0];
    //
    //		EEPROM_R(Addr400_CurB_cal_tmp1,array_temp,2,0xA0);
    //		CurB400_cal_tmp[1]=(array_temp[1]<<8)+array_temp[0];
    //
    //		EEPROM_R(Addr400_CurC_cal_tmp1,array_temp,2,0xA0);
    //		CurC400_cal_tmp[1]=(array_temp[1]<<8)+array_temp[0];
    ///*************630�Ǽ�*****************/
    //		EEPROM_R(Addr630_I1_A_slope,array_temp,2,0xA0);
    //		I1_630A_slope[0]=(array_temp[1]<<8)+array_temp[0];
    //
    //		EEPROM_R(Addr630_I1_B_slope,array_temp,2,0xA0);
    //		I1_630B_slope[0]=(array_temp[1]<<8)+array_temp[0];
    //
    //		EEPROM_R(Addr630_I1_C_slope,array_temp,2,0xA0);
    //		I1_630C_slope[0]=(array_temp[1]<<8)+array_temp[0];

    //		EEPROM_R(Addr630_I1_A_slope1,array_temp,2,0xA0);
    //		I1_630A_slope[1]=(array_temp[1]<<8)+array_temp[0];
    //
    //		EEPROM_R(Addr630_I1_B_slope1,array_temp,2,0xA0);
    //		I1_630B_slope[1]=(array_temp[1]<<8)+array_temp[0];
    //
    //		EEPROM_R(Addr630_I1_C_slope1,array_temp,2,0xA0);
    //		I1_630C_slope[1]=(array_temp[1]<<8)+array_temp[0];

    //
    //		EEPROM_R(Addr630_CurA_cal_tmp,array_temp,2,0xA0);
    //		CurA630_cal_tmp[0]=(array_temp[1]<<8)+array_temp[0];
    //
    //    EEPROM_R(Addr630_CurB_cal_tmp,array_temp,2,0xA0);
    //		CurB630_cal_tmp[0]=(array_temp[1]<<8)+array_temp[0];
    //
    //    EEPROM_R(Addr630_CurC_cal_tmp,array_temp,2,0xA0);
    //		CurC630_cal_tmp[0]=(array_temp[1]<<8)+array_temp[0];

    //    EEPROM_R(Addr630_CurA_cal_tmp1,array_temp,2,0xA0);
    //		CurA630_cal_tmp[1]=(array_temp[1]<<8)+array_temp[0];
    //
    //		EEPROM_R(Addr630_CurB_cal_tmp1,array_temp,2,0xA0);
    //		CurB630_cal_tmp[1]=(array_temp[1]<<8)+array_temp[0];
    //
    //		EEPROM_R(Addr630_CurC_cal_tmp1,array_temp,2,0xA0);
    //		CurC630_cal_tmp[1]=(array_temp[1]<<8)+array_temp[0];
    ///*************800�Ǽ�*****************/
    //		EEPROM_R(Addr800_I1_A_slope,array_temp,2,0xA0);
    //		I1_800A_slope[0]=(array_temp[1]<<8)+array_temp[0];
    //
    //		EEPROM_R(Addr800_I1_B_slope,array_temp,2,0xA0);
    //		I1_800B_slope[0]=(array_temp[1]<<8)+array_temp[0];
    //
    //		EEPROM_R(Addr800_I1_C_slope,array_temp,2,0xA0);
    //		I1_800C_slope[0]=(array_temp[1]<<8)+array_temp[0];

    //		EEPROM_R(Addr800_I1_A_slope1,array_temp,2,0xA0);
    //		I1_800A_slope[1]=(array_temp[1]<<8)+array_temp[0];
    //
    //		EEPROM_R(Addr800_I1_B_slope1,array_temp,2,0xA0);
    //		I1_800B_slope[1]=(array_temp[1]<<8)+array_temp[0];
    //
    //		EEPROM_R(Addr800_I1_C_slope1,array_temp,2,0xA0);
    //		I1_800C_slope[1]=(array_temp[1]<<8)+array_temp[0];

    //
    //		EEPROM_R(Addr800_CurA_cal_tmp,array_temp,2,0xA0);
    //		CurA800_cal_tmp[0]=(array_temp[1]<<8)+array_temp[0];
    //
    //    EEPROM_R(Addr800_CurB_cal_tmp,array_temp,2,0xA0);
    //		CurB800_cal_tmp[0]=(array_temp[1]<<8)+array_temp[0];
    //
    //    EEPROM_R(Addr800_CurC_cal_tmp,array_temp,2,0xA0);
    //		CurC800_cal_tmp[0]=(array_temp[1]<<8)+array_temp[0];

    //    EEPROM_R(Addr800_CurA_cal_tmp1,array_temp,2,0xA0);
    //		CurA800_cal_tmp[1]=(array_temp[1]<<8)+array_temp[0];
    //
    //		EEPROM_R(Addr800_CurB_cal_tmp1,array_temp,2,0xA0);
    //		CurB800_cal_tmp[1]=(array_temp[1]<<8)+array_temp[0];
    //
    //		EEPROM_R(Addr800_CurC_cal_tmp1,array_temp,2,0xA0);
    //		CurC800_cal_tmp[1]=(array_temp[1]<<8)+array_temp[0];
    //	if(I_factor>30) I_factor = 30;
    //	if(I_factor<-30) I_factor = -30;
    EEPROM_R(Addr_CI_F, array_temp, 1, 0xA0);
    F_cal_I_C = array_temp[0];

    EEPROM_R(Addr_temperature_UP, array_temp, 1, 0xA0);
    TH_TEM_UP = array_temp[0];
    TEM_UP = TEM_UP_arry[TH_TEM_UP];

    EEPROM_R(Addr_temperature_DOWN, array_temp, 1, 0xA0);
    TH_TEM_DOWN = array_temp[0];
    TEM_DOWN = TEM_DOWN_arry[TH_TEM_DOWN];
    // ��������*********************/
    EEPROM_R(Addr_I_ia, array_temp, 1, 0xA0);
    F_ia = array_temp[0];
    EEPROM_R(Addr_L_TB, array_temp, 1, 0xA0);
    F_TB_trip = array_temp[0];
    EEPROM_R(Addr_L_specialwave, array_temp, 1, 0xA0);
    F_Special_wave = array_temp[0];
    EEPROM_R(Addr_C_IP, array_temp, 1, 0xA0);
    F_C_IP = array_temp[0];
    EEPROM_R(Addr_L_JC, array_temp, 1, 0xA0);
    F_jiance = array_temp[0];
    EEPROM_R(Addr_F_gc, array_temp, 1, 0xA0);
    F_gc = array_temp[0];

    EEPROM_R(Addr_I_2d, array_temp, 1, 0xA0);
    F_ip = array_temp[0];
    EEPROM_R(Addr_I_3d, array_temp, 1, 0xA0); // 17.6.21��
    F_ip_3 = array_temp[0];

    EEPROM_R(Addr_D_Cur, array_temp, 1, 0xA0);
    D_Cur = array_temp[0];
    EEPROM_R(Addr_D2_Cur, array_temp, 1, 0xA0);
    D2_Cur = array_temp[0];
    EEPROM_R(Addr_D3_Cur, array_temp, 1, 0xA0);
    D3_Cur = array_temp[0];
    IWDG_Feed();
    EEPROM_R(Addr_D2_Time, array_temp, 1, 0xA0);
    TH_DL = array_temp[0];
    EEPROM_R(Addr_CurLong_Time, array_temp, 1, 0xA0);
    TH_Long_Cur = array_temp[0];
    if (TH_Long_Cur > 7)
    {
        TH_Long_Cur = 0;
    }
    // putchar(D_Cur);
    EEPROM_R(Addr_Type_Cur, array_temp, 1, 0xA0);
    Type_Cur = array_temp[0];
    if (Type_Cur > 4)
    {
        Type_Cur = 1;
    }
    if ((Type_Cur == 0) && (D_Cur >= 9))
    {
        D_Cur = 9;
    }
    if ((Type_Cur == 1) && (D_Cur >= 19))
    {
        D_Cur = 19;
    }
    if ((Type_Cur == 2) && (D_Cur >= 12))
    {
        D_Cur = 12;
    }
    if ((Type_Cur == 3) && (D_Cur >= 14))
    {
        D_Cur = 14;
    }
    if ((Type_Cur == 4) && (D_Cur >= 7))
    {
        D_Cur = 6;
    }
    Cur_Switch(Type_Cur);
    IWDG_Feed();
    /*******************�����֣�������λ���Ǽܵȼ�����Ƿѹ��λ*********************/
    EEPROM_R(Addr_crtl_word1, ctrlword, 5, 0xA0); // ��5��������
    delay_ms(5);
    ctrlword1_analyze();
    ctrlword2_analyze();
    ctrlword3_analyze();
    ctrlword4_analyze();
    ctrlword5_analyze();
    IWDG_Feed();
    EEPROM_R(Addr_Vol_g, array_temp, 1, 0xA0);
    Vol_g = array_temp[0];
    if (Vol_g > 6)
    {
        array_temp[0] = 0x05;
        MODIFY_EEP_W(Addr_Vol_g, array_temp, 1, 0xA0);
        Vol_g = 0x04;
    }
    EEPROM_R(Addr_Vol_q, array_temp, 1, 0xA0);
    Vol_q = array_temp[0];
    if (Vol_q > 6)
    {
        array_temp[0] = 0x05;
        MODIFY_EEP_W(Addr_Vol_q, array_temp, 1, 0xA0);
        Vol_q = 0x04;
    }
    EEPROM_R(Addr_Vol_ch, array_temp, 1, 0xA0);
    Vol_ch = array_temp[0];
    over_vol_code[0] = 0x00;
    over_vol_code[1] = 0x25 + Vol_g;
    IWDG_Feed();
    EEPROM_R(Addr_data_clear, array_temp, 1, 0xA0);
    F_data_clear = array_temp[0];

    EEPROM_R(Addr_SY_F, array_temp, 1, 0xA0);
    F_trip_sy = array_temp[0];

    EEPROM_R(Addr_SY_yanshi, array_temp, 1, 0xA0);
    D_SY_yanshi = array_temp[0];
    if (D_SY_yanshi > 9)
    {
        array_temp[0] = 0;
        MODIFY_EEP_W(Addr_SY_yanshi, array_temp, 1, 0xA0);
        D_SY_yanshi = 0;
    }

    EEPROM_R(Addr_QY_yanshi, array_temp, 1, 0xA0);
    D_QY_yanshi = array_temp[0]; // 0000 01111
    if (D_QY_yanshi > 9)
    {
        array_temp[0] = 0;
        MODIFY_EEP_W(Addr_QY_yanshi, array_temp, 1, 0xA0);
        D_QY_yanshi = 0;
    }

    EEPROM_R(Addr_GY_yanshi, array_temp, 1, 0xA0);
    D_GY_yanshi = array_temp[0]; // 0000 01111
    if (D_GY_yanshi > 9)
    {
        array_temp[0] = 0;
        MODIFY_EEP_W(Addr_GY_yanshi, array_temp, 1, 0xA0);
        D_GY_yanshi = 0;
    }
    IWDG_Feed();
    EEPROM_R(Addr_QX_BAOHU, array_temp, 1, 0xA0);
    Vol_down = array_temp[0];
    if (Vol_down > 6)
    {
        array_temp[0] = 0;
        MODIFY_EEP_W(Addr_QX_BAOHU, array_temp, 1, 0xA0);
        Vol_down = 0;
    }
    EEPROM_R(Addr_QL_BAOHU, array_temp, 1, 0xA0);
    Vol_up = array_temp[0];
    if (Vol_up > 5)
    {
        array_temp[0] = 0;
        MODIFY_EEP_W(Addr_QL_BAOHU, array_temp, 1, 0xA0);
        Vol_up = 0;
    }
    IWDG_Feed();
    EEPROM_R(Addr_shangdian, array_temp, 1, 0xA0);
    shangdian = array_temp[0];
    EEPROM_R(Addr_dianya, array_temp, 1, 0xA0);
    DY_hezha = array_temp[0];
    EEPROM_R(Addr_dianliu, array_temp, 1, 0xA0);
    DL_hezha = array_temp[0];
    EEPROM_R(Addr_loudian, array_temp, 1, 0xA0);
    LD_hezha = array_temp[0];

    EEPROM_R(Addr_TX, array_temp, 1, 0xA0);
    F_TX = array_temp[0];

    EEPROM_R(Addr_jiaozhun, array_temp, 1, 0xA0);
    F_Corr = jiaozhun = array_temp[0];
    EEPROM_R(Addr_wendu, array_temp, 1, 0xA0);
    wendu = array_temp[0];
    EEPROM_R(Addr_DIANYA_chonghe, array_temp, 1, 0xA0);
    F_dianya_chonghe = array_temp[0];
    EEPROM_R(Addr_duandian, array_temp, 1, 0xA0);
    duandian = array_temp[0];
    IWDG_Feed();
    EEPROM_R(Addr_Vol_q, array_temp, 1, 0xA0);
    Vol_q = array_temp[0];
    //	under_vol_code[0]=0x00 ;
    //	under_vol_code[1]=0x14+Vol_q ;
    //	if(under_vol_code[1]==0x1A)
    //		under_vol_code[1] = 0x20;
    /*******************�����ʣ��豸��ַ*********************/
    EEPROM_R(Addr_baud, array_temp, 1, 0xA0);
    baud = array_temp[0];

    if (baud == 0)
    {
        RS485_Init(1200);
    }
    else if (baud == 1)
    {
        RS485_Init(2400);
    }
    else if (baud == 2)
    {
        RS485_Init(4800);
    }
    else if (baud == 3)
    {
        RS485_Init(9600);
    }

    //	Uart2_Init();
    EEPROM_R(Addr_dev_addr, self_addr_code, 6, 0xA0);
    if ((self_addr_code[0] > 0x99) || (self_addr_code[1] > 0x99) || (self_addr_code[2] > 0x99) || (self_addr_code[3] > 0x99) || (self_addr_code[4] > 0x99) || (self_addr_code[5] > 0x99))
    {

        self_addr_code[0] = 0x00;
        self_addr_code[1] = 0x00;
        self_addr_code[2] = 0x00;
        self_addr_code[3] = 0x00;
        self_addr_code[4] = 0x00;
        self_addr_code[5] = 0x00;
        // Rewrite_buffer(0);
        MODIFY_EEP_W(Addr_dev_addr, self_addr_code, 6, 0xA0);
    }
    /*******************����+����*********************/
    EEPROM_R(Addr_0_password, array_temp, 12, 0xA0);
    for (i = 0; i < 4; i++)
    {
        password_0class[i] = array_temp[i];
        password_1class[i] = array_temp[i + 4];
        password_2class[i] = array_temp[i + 8];
    }

    /********************������************************/
    EEPROM_R(Addr_clear_num, array_temp, 3, 0xA0);
    Num_clearall = BCDtoDec(array_temp, 3);

    EEPROM_R(Addr_trip_num, array_temp, 2, 0xA0);
    Num_tripall = BCDtoDec(array_temp, 2);

    EEPROM_R(Addr_close_num, array_temp, 2, 0xA0);
    Num_triplock = BCDtoDec(array_temp, 2);

    EEPROM_R(Addr_leak_num, array_temp, 2, 0xA0);
    Num_tripleak = BCDtoDec(array_temp, 2);

    EEPROM_R(Addr_current_num, array_temp, 2, 0xA0);
    Num_tripcur = BCDtoDec(array_temp, 2);
    IWDG_Feed();
    EEPROM_R(Addr_vol_num, array_temp, 2, 0xA0);
    Num_tripvol = BCDtoDec(array_temp, 2);

    EEPROM_R(Addr_hand_num, array_temp, 2, 0xA0);
    Num_triphand = BCDtoDec(array_temp, 2);

    EEPROM_R(Addr_zero_num, array_temp, 2, 0xA0);
    Num_tripzero = BCDtoDec(array_temp, 2);

    EEPROM_R(Addr_test_num, array_temp, 2, 0xA0);
    Num_triptest = BCDtoDec(array_temp, 2);

    EEPROM_R(Addr_2D_num, array_temp, 2, 0xA0);
    Num_tripdelay = BCDtoDec(array_temp, 2);

    EEPROM_R(Addr_3D_num, array_temp, 2, 0xA0);
    Num_tripinstant = BCDtoDec(array_temp, 2);

    EEPROM_R(Addr_leakover_num, array_temp, 2, 0xA0);
    Num_leakover = BCDtoDec(array_temp, 2);

    EEPROM_R(Addr_leakprotect_num, array_temp, 2, 0xA0);
    Num_leakprotect = BCDtoDec(array_temp, 2);

    EEPROM_R(Addr_leakquit_num, array_temp, 2, 0xA0);
    /*���˴���*/
    Num_leakquit = BCDtoDec(array_temp, 2);
    EEPROM_R(Addr_protect_time, T_run_time_array, 4, 0xA0);
    // ����ʱ��
    Sum_run_time = BCDtoDec(T_run_time_array, 4); // ��������
    // �豸��
    EEPROM_R(Addr_dev_id, dev_id_code, 6, 0xA0); // �ʲ��������
    EEPROM_R(Addr_dev_code, dev_code_code, 32, 0xA0);
    EEPROM_R(Addr_equi_type, equi_type_code, 10, 0xA0);
    // ���ϴ���
    EEPROM_R(Addr_factory_code, factory_code_code, 24, 0xA0);
    /**********************�¼���¼*****************************/
    // ��բ�¼�ָ��
    EEPROM_R(Addr_point_event_trip, &array_temp[1], 1, 0xA0);
    point_event_trip = array_temp[1];
    EEPROM_R(Addr_point_event_trip_24C256, &array_temp[1], 1, 0xA0);
    point_event_trip_24C256 = array_temp[1];
    // �Լ�ʱ��
    EEPROM_R(Addr_point_event_self, &array_temp[1], 1, 0xA0);
    point_event_self = array_temp[1];

    // ©�糬���¼�ָ��
    EEPROM_R(Addr_point_event_leak, array_temp, 1, 0xA0);
    point_event_leak = array_temp[0];
    IWDG_Feed();
    /**********************��ֵ��¼*****************************/
    //	EEPROM_R(Addr_max_Avol_TD,array_temp,4,0xA0);
    //	V_MAX[0]=BCDtoDec(array_temp,2);
    //
    //	EEPROM_R(Addr_max_Bvol_TD,array_temp,4,0xA0);
    //	V_MAX[1]=BCDtoDec(array_temp,2);
    //
    //	EEPROM_R(Addr_max_Cvol_TD,array_temp,4,0xA0);
    //	V_MAX[2]=BCDtoDec(array_temp,2);
    EEPROM_R(Addr_record_time, array_temp, 1, 0xA0);
    Leak_record_time = BCDtoDec(array_temp, 1);
    Num_leak_record = Leak_record_time * 3000;

    EEPROM_R(Addr_point_leakrecord, array_temp, 2, 0xA0);
    point_Leak_record = BCDtoDec(array_temp, 2);

    EEPROM_R(Addr_point_leak_max, array_temp, 1, 0xA0);
    point_leak_max = array_temp[0];

    EEPROM_R((Addr_max_leak + point_leak_max * 9), array_temp, 1, 0xA0);
    old_year = array_temp[8];
    old_month = array_temp[7];
    old_day = array_temp[6];
    IWDG_Feed();
    EEPROM_R(Addr_point_Avol_max, array_temp, 1, 0xA0);
    point_Avol_max = array_temp[0];

    EEPROM_R(Addr_point_Bvol_max, array_temp, 1, 0xA0);
    point_Bvol_max = array_temp[0];
    EEPROM_R(Addr_point_Cvol_max, array_temp, 1, 0xA0);
    point_Cvol_max = array_temp[0];
    EEPROM_R(Addr_point_Acur_max, array_temp, 1, 0xA0);
    point_Acur_max = array_temp[0];
    EEPROM_R(Addr_point_Bcur_max, array_temp, 1, 0xA0);
    point_Bcur_max = array_temp[0];
    EEPROM_R(Addr_point_Ccur_max, array_temp, 1, 0xA0);
    point_Ccur_max = array_temp[0];

    EEPROM_R(Addr_point_leak_min, array_temp, 1, 0xA0);
    point_leak_min = array_temp[0];
    EEPROM_R(Addr_point_Avol_min, array_temp, 1, 0xA0);
    point_Avol_min = array_temp[0];
    EEPROM_R(Addr_point_Bvol_min, array_temp, 1, 0xA0);
    point_Bvol_min = array_temp[0];
    EEPROM_R(Addr_point_Cvol_min, array_temp, 1, 0xA0);
    point_Cvol_min = array_temp[0];
    EEPROM_R(Addr_point_Acur_min, array_temp, 1, 0xA0);
    point_Acur_min = array_temp[0];
    EEPROM_R(Addr_point_Bcur_min, array_temp, 1, 0xA0);
    point_Bcur_min = array_temp[0];
    EEPROM_R(Addr_point_Ccur_min, array_temp, 1, 0xA0);
    point_Ccur_min = array_temp[0];
    IWDG_Feed();
    EEPROM_R(Addr_alarm_value, alarm_value_code, 2, 0xA0);
    Leak_Alarm_Value = BCDtoDec(alarm_value_code, 2);
    // ʣ�������¼�仯��ֵ����ֵ(10-99)
    EEPROM_R(Addr_record_value, record_value_code, 1, 0xA0);
    // ʣ�������¼���ʱ������ֵ(01-99)
    EEPROM_R(Addr_record_time, record_time_code, 1, 0xA0);
    // ��ʱ��������ʱ�� 3
    EEPROM_R(Addr_timed_trip, timed_trip_code, 3, 0xA0);
    // �����ѹ����ֵ 2
    EEPROM_R(Addr_break_phase, break_phase_code, 2, 0xA0);
    // �������ޱ���
    EEPROM_R(Addr_over_current, over_current_code, 1, 0xA0);

    // ������2022.2.21��������ݼ�
    EEPROM_R(Addr_mima_set, array_temp, 4, 0xA0);
    mima_set[0] = array_temp[0];
    mima_set[1] = array_temp[1];
    mima_set[2] = array_temp[2];
    mima_set[3] = array_temp[3];

    // putchar(0xCC);
    /*******���հ汾У׼�¼�ϵ��***********/
    Read_Cur_calibrae_data(); // ���������У׼����

    Read_SD_Cur_calibrae_data(); // ��˲����ز���
    Read_SD_Cur_calibrae_data1();

    AT24CXX_ReadLongByte(Addr_Vol_ad, 9, array_temp, 0xA0);

    Vol_A_temp[0] = ChartoHex(&array_temp[0], 3);
    Vol_B_temp[0] = ChartoHex(&array_temp[3], 3);
    Vol_C_temp[0] = ChartoHex(&array_temp[6], 3);

    AT24CXX_ReadLongByte(Addr_Vol_slope, 6, array_temp, 0xA0);

    V_A_slope[0] = ChartoHex(&array_temp[0], 2);
    V_B_slope[0] = ChartoHex(&array_temp[2], 2);
    V_C_slope[0] = ChartoHex(&array_temp[4], 2);
    AT24CXX_ReadLongByte(Addr_Vol_Disp, 6, array_temp, 0xA0);

    Vol_A_disp[0] = ChartoHex(&array_temp[0], 2);
    Vol_B_disp[0] = ChartoHex(&array_temp[2], 2);
    Vol_C_disp[0] = ChartoHex(&array_temp[4], 2);

    AT24CXX_ReadLongByte(Addr_Leak_ad, 6, array_temp, 0xA0);
    for (char i = 0; i < 3; i++)
    {
        unsigned char j;
        j = i << 1;
        Leak_temp[i] = (array_temp[j + 1] << 8) + array_temp[j];
    }

    AT24CXX_ReadLongByte(Addr_Leak_slope, 6, array_temp, 0xA0);

    for (char i = 0; i < 3; i++)
    {
        unsigned char j;
        j = i << 1;
        L_slope[i] = (array_temp[j + 1] << 8) + array_temp[j];
    }

    AT24CXX_ReadLongByte(Addr_Leak_Disp, 6, array_temp, 0xA0);

    for (char i = 0; i < 3; i++)
    {
        unsigned char j;
        j = i << 1;
        Leak_disp[i] = (array_temp[j + 1] << 8) + array_temp[j];
    }
}

void factor_first_init(unsigned char tmp)
{

    int Addr_factor;
    unsigned char array_temp[30], array_tmp[150];
    unsigned int lenth;

    array_temp[0] = 0x66;
    array_temp[1] = 0x66;
    MODIFY_EEP_W(Addr_Ugain_A, array_temp, 2, 0xA0);
    MODIFY_EEP_W(Addr_Ugain_B, array_temp, 2, 0xA0);
    MODIFY_EEP_W(Addr_Ugain_C, array_temp, 2, 0xA0);

    array_temp[0] = 0xA3;
    array_temp[1] = 0x30;
    MODIFY_EEP_W(Addr_Igain_A, array_temp, 2, 0xA0);
    MODIFY_EEP_W(Addr_Igain_B, array_temp, 2, 0xA0);
    MODIFY_EEP_W(Addr_Igain_C, array_temp, 2, 0xA0);

    array_temp[0] = 0x08;
    array_temp[1] = 0x06;
    MODIFY_EEP_W(Addr_Pgain_A, array_temp, 2, 0xA0);
    MODIFY_EEP_W(Addr_Pgain_B, array_temp, 2, 0xA0);
    MODIFY_EEP_W(Addr_Pgain_C, array_temp, 2, 0xA0);

    array_temp[0] = 0x73;
    array_temp[1] = 0x22;
    MODIFY_EEP_W(Addr_Ioffset_A, array_temp, 2, 0xA0);
    MODIFY_EEP_W(Addr_Ioffset_B, array_temp, 2, 0xA0);
    MODIFY_EEP_W(Addr_Ioffset_C, array_temp, 2, 0xA0);

    // �¼�����
    Addr_factor = Addr_max_leak;
    lenth = 288;
    EEPROM_C(Addr_factor, lenth, 0xA0);
    delay_ms(5);
    IWDG_Feed();
    Addr_factor = Addr_max_Avol;
    lenth = 288;
    EEPROM_C(Addr_factor, lenth, 0xA0);
    delay_ms(5);
    IWDG_Feed();
    Addr_factor = Addr_max_Bvol;
    lenth = 288;
    IWDG_Feed();
    EEPROM_C(Addr_factor, lenth, 0xA0);
    delay_ms(5);
    IWDG_Feed();
    Addr_factor = Addr_max_Cvol;
    lenth = 288;
    EEPROM_C(Addr_factor, lenth, 0xA0);
    delay_ms(5);
    IWDG_Feed();
    Addr_factor = Addr_max_Acur;
    lenth = 288;
    EEPROM_C(Addr_factor, lenth, 0xA0);
    delay_ms(5);
    IWDG_Feed();
    Addr_factor = Addr_max_Bcur;
    lenth = 288;
    EEPROM_C(Addr_factor, lenth, 0xA0);
    delay_ms(5);
    IWDG_Feed();
    Addr_factor = Addr_max_Ccur;
    lenth = 288;
    IWDG_Feed();
    EEPROM_C(Addr_factor, lenth, 0xA0);
    delay_ms(5);
    //
    //
    array_temp[0] = 3;
    MODIFY_EEP_W(Addr_temperature_UP, array_temp, 1, 0xA0);
    array_temp[0] = 3; //;
    MODIFY_EEP_W(Addr_temperature_DOWN, array_temp, 1, 0xA0);

    /**********���ܵ�λ�ָ���������*******************/
    /***********��ѹУ׼����**************/
    array_temp[0] = 0x06;
    array_temp[1] = 0x1D;
    array_temp[2] = 0x00;
    array_temp[3] = 0x20;
    array_temp[4] = 0x1D;
    array_temp[5] = 0x00;
    array_temp[6] = 0x29;
    array_temp[7] = 0x1D;
    array_temp[8] = 0x00;
    MODIFY_EEP_W(Addr_Vol_ad, array_temp, 9, 0xA0); //
    array_temp[0] = 0x22;
    array_temp[1] = 0x08;
    array_temp[2] = 0x22;
    array_temp[3] = 0x08;
    array_temp[4] = 0x35;
    array_temp[5] = 0x08;
    MODIFY_EEP_W(Addr_Vol_slope, array_temp, 6, 0xA0); //
    array_temp[0] = 0x20;
    array_temp[1] = 0x4E;
    array_temp[2] = 0x20;
    array_temp[3] = 0x4E;
    array_temp[4] = 0x20;
    array_temp[5] = 0x4E;
    MODIFY_EEP_W(Addr_Vol_Disp, array_temp, 6, 0xA0); //
                                                      /***********����У׼����**************/
    array_temp[0] = 0xE8;
    array_temp[1] = 0x03; // 03E8=1000
    array_temp[2] = 0x88;
    array_temp[3] = 0x13; // 1388=5000
    array_temp[4] = 0x10;
    array_temp[5] = 0x27; // 2710=10000
    array_temp[6] = 0x60;
    array_temp[7] = 0xEA; // EA60=60000

    array_temp[8] = 0xE8;
    array_temp[9] = 0x03;
    array_temp[10] = 0x88;
    array_temp[11] = 0x13;
    array_temp[12] = 0x10;
    array_temp[13] = 0x27;
    array_temp[14] = 0x60;
    array_temp[15] = 0xEA;

    array_temp[16] = 0xE8;
    array_temp[17] = 0x03;
    array_temp[18] = 0x88;
    array_temp[19] = 0x13;
    array_temp[20] = 0x10;
    array_temp[21] = 0x27;
    array_temp[22] = 0x60;
    array_temp[23] = 0xEA;
    MODIFY_EEP_W(Addr_Cur_Disp_250, array_temp, 24, 0xA0);
    IWDG_Feed();
    delay_ms(5);
    array_temp[0] = 0xAB;
    array_temp[1] = 0x01;
    array_temp[2] = 0x2C;
    array_temp[3] = 0x0A;
    array_temp[4] = 0xF3;
    array_temp[5] = 0x14;
    array_temp[6] = 0x48;
    array_temp[7] = 0x7D;

    array_temp[8] = 0x5D;
    array_temp[9] = 0x03;
    array_temp[10] = 0xF6;
    array_temp[11] = 0x0B;
    array_temp[12] = 0x73;
    array_temp[13] = 0x16;
    array_temp[14] = 0x11;
    array_temp[15] = 0x7F;

    array_temp[16] = 0x6A;
    array_temp[17] = 0x02;
    array_temp[18] = 0xE7;
    array_temp[19] = 0x0A;
    array_temp[20] = 0x61;
    array_temp[21] = 0x15;
    array_temp[22] = 0x96;
    array_temp[23] = 0x7D;
    MODIFY_EEP_W(Addr_Cur_250, array_temp, 24, 0xA0);
    IWDG_Feed();
    delay_ms(5);
    array_temp[0] = 0x5E;
    array_temp[1] = 0x09;
    array_temp[2] = 0x8D;
    array_temp[3] = 0x07;
    array_temp[4] = 0x3F;
    array_temp[5] = 0x07;
    array_temp[6] = 0x7C;
    array_temp[7] = 0x07;

    array_temp[8] = 0xA5;
    array_temp[9] = 0x04;
    array_temp[10] = 0x54;
    array_temp[11] = 0x07;
    array_temp[12] = 0x72;
    array_temp[13] = 0x07;
    array_temp[14] = 0x77;
    array_temp[15] = 0x07;

    array_temp[16] = 0x78;
    array_temp[17] = 0x06;
    array_temp[18] = 0x67;
    array_temp[19] = 0x07;
    array_temp[20] = 0x75;
    array_temp[21] = 0x07;
    array_temp[22] = 0x7F;
    array_temp[23] = 0x07;
    MODIFY_EEP_W(Addr_Cur_slope_250, array_temp, 24, 0xA0);
    delay_ms(5);
    /***********©��У׼����**************/
    array_temp[0] = 0x5F;
    array_temp[1] = 0x08;
    array_temp[2] = 0xF8;
    array_temp[3] = 0x5A;
    MODIFY_EEP_W(Addr_Leak_ad, array_temp, 4, 0xA0);
    array_temp[0] = 0x72; // 5000/////////////////////
    array_temp[1] = 0x94;
    array_temp[2] = 0x30; // 60000
    array_temp[3] = 0x75;
    MODIFY_EEP_W(Addr_Leak_Disp, array_temp, 4, 0xA0);
    array_temp[0] = 0x16;
    array_temp[1] = 0x03;
    array_temp[2] = 0x33;
    array_temp[3] = 0x05;
    MODIFY_EEP_W(Addr_Leak_slope, array_temp, 4, 0xA0);
    delay_ms(5);
    /***********************************************************/
    /**********************800�Ǽ�˲��У׼******************/
    array_temp[0] = 0x20; // 84000
    array_temp[1] = 0x48;
    array_temp[2] = 0x01;

    array_temp[3] = 0xA0; // 100000
    array_temp[4] = 0x86;
    array_temp[5] = 0x01;

    array_temp[6] = 0xA0; // 100000
    array_temp[7] = 0x86;
    array_temp[8] = 0x01;

    array_temp[9] = 0xA0;
    array_temp[10] = 0x86;
    array_temp[11] = 0x01;

    array_temp[12] = 0xA0;
    array_temp[13] = 0x86;
    array_temp[14] = 0x01;
    MODIFY_EEP_W(Addr_DLS_Cur_IV_AD_value, array_temp, 15, 0xA0); // 800�Ǽ�˲������ADֵ
    delay_ms(5);
    array_temp[0] = 0x17; // 23
    array_temp[1] = 0x00;
    array_temp[2] = 0x00;

    array_temp[3] = 0x0A; // 10
    array_temp[4] = 0x00;
    array_temp[5] = 0x00;

    array_temp[6] = 0x08; // 8
    array_temp[7] = 0x00;
    array_temp[8] = 0x00;

    array_temp[9] = 0x06; // 6
    array_temp[10] = 0x00;
    array_temp[11] = 0x00;

    array_temp[12] = 0x04; // 4
    array_temp[13] = 0x00;
    array_temp[14] = 0x00;
    MODIFY_EEP_W(Addr_DLS_Cur_IV_slope, array_temp, 15, 0xA0); // 800�Ǽ�˲������б��ֵ
    delay_ms(5);
    array_temp[0] = 0x00; // 0
    array_temp[1] = 0x00;
    array_temp[2] = 0x00;

    array_temp[3] = 0x74; // 3700
    array_temp[4] = 0x0E;
    array_temp[5] = 0x00;

    array_temp[6] = 0x74; // 3700
    array_temp[7] = 0x0E;
    array_temp[8] = 0x00;

    array_temp[9] = 0x74; // 3700
    array_temp[10] = 0x0E;
    array_temp[11] = 0x00;

    array_temp[12] = 0x74; // 3700
    array_temp[13] = 0x0E;
    array_temp[14] = 0x00;
    MODIFY_EEP_W(Addr_DLS_Cur_IV_Value, array_temp, 15, 0xA0); // 800�Ǽ�˲������ֵ
    delay_ms(5);
    /**********************250�Ǽ�˲��У׼******************/
    array_temp[0] = 0xD0; // 66000
    array_temp[1] = 0x01;
    array_temp[2] = 0x01;

    array_temp[3] = 0x00; // 76800
    array_temp[4] = 0x2C;
    array_temp[5] = 0x01;

    array_temp[6] = 0x90; // 90000
    array_temp[7] = 0x5F;
    array_temp[8] = 0x01;

    array_temp[9] = 0x90; // 90000
    array_temp[10] = 0x5F;
    array_temp[11] = 0x01;

    array_temp[12] = 0x90; // 90000
    array_temp[13] = 0x5F;
    array_temp[14] = 0x01;
    MODIFY_EEP_W(Addr_DLS_Cur_I_AD_value, array_temp, 15, 0xA0); // 250�Ǽ�˲������ADֵ
    delay_ms(5);
    array_temp[0] = 0x3C; // 60
    array_temp[1] = 0x00;
    array_temp[2] = 0x00;

    array_temp[3] = 0x0C; // 12
    array_temp[4] = 0x00;
    array_temp[5] = 0x00;

    array_temp[6] = 0x08; // 8
    array_temp[7] = 0x00;
    array_temp[8] = 0x00;

    array_temp[9] = 0x04; // 4
    array_temp[10] = 0x00;
    array_temp[11] = 0x00;

    array_temp[12] = 0x04; // 4
    array_temp[13] = 0x00;
    array_temp[14] = 0x00;
    MODIFY_EEP_W(Addr_DLS_Cur_I_slope, array_temp, 15, 0xA0); // 250�Ǽ�˲������б��ֵ
    delay_ms(5);
    array_temp[0] = 0x00; // 0
    array_temp[1] = 0x00;
    array_temp[2] = 0x00;

    array_temp[3] = 0x4C; // 1100
    array_temp[4] = 0x04;
    array_temp[5] = 0x00;

    array_temp[6] = 0xD0; // 20000
    array_temp[7] = 0x07;
    array_temp[8] = 0x00;

    array_temp[9] = 0xB8; // 30000
    array_temp[10] = 0x0B;
    array_temp[11] = 0x00;

    array_temp[12] = 0xB8; // 30000
    array_temp[13] = 0x0B;
    array_temp[14] = 0x00;
    MODIFY_EEP_W(Addr_DLS_Cur_I_Value, array_temp, 15, 0xA0); // 250�Ǽ�˲������ֵ
    delay_ms(5);
    /**********************400�Ǽ�˲��У׼******************/
    array_temp[0] = 0xE8;
    array_temp[1] = 0x80;
    array_temp[2] = 0x00;

    array_temp[3] = 0xA8;
    array_temp[4] = 0x93;
    array_temp[5] = 0x00;

    array_temp[6] = 0x18;
    array_temp[7] = 0xAB;
    array_temp[8] = 0x00;

    array_temp[9] = 0x90;
    array_temp[10] = 0x5F;
    array_temp[11] = 0x01;

    array_temp[12] = 0x90;
    array_temp[13] = 0x5F;
    array_temp[14] = 0x01;
    MODIFY_EEP_W(Addr_DLS_Cur_II_AD_value, array_temp, 15, 0xA0); // 400�Ǽ�˲������ADֵ
    delay_ms(5);
    array_temp[0] = 0x1E;
    array_temp[1] = 0x00;
    array_temp[2] = 0x00;

    array_temp[3] = 0x06;
    array_temp[4] = 0x00;
    array_temp[5] = 0x00;

    array_temp[6] = 0x06;
    array_temp[7] = 0x00;
    array_temp[8] = 0x00;

    array_temp[9] = 0x03;
    array_temp[10] = 0x00;
    array_temp[11] = 0x00;

    array_temp[12] = 0x03;
    array_temp[13] = 0x00;
    array_temp[14] = 0x00;
    MODIFY_EEP_W(Addr_DLS_Cur_II_slope, array_temp, 15, 0xA0); // 400�Ǽ�˲������б��ֵ
    delay_ms(5);
    array_temp[0] = 0x00;
    array_temp[1] = 0x00;
    array_temp[2] = 0x00;

    array_temp[3] = 0x4C;
    array_temp[4] = 0x04;
    array_temp[5] = 0x00;

    array_temp[6] = 0x6C;
    array_temp[7] = 0x07;
    array_temp[8] = 0x00;

    array_temp[9] = 0x54;
    array_temp[10] = 0x0B;
    array_temp[11] = 0x00;

    array_temp[12] = 0xB8;
    array_temp[13] = 0x0B;
    array_temp[14] = 0x00;
    MODIFY_EEP_W(Addr_DLS_Cur_II_Value, array_temp, 15, 0xA0); // 400�Ǽ�˲������ֵ
    delay_ms(5);
    /**********************630�Ǽ�˲��У׼******************/
    array_temp[0] = 0x38;
    array_temp[1] = 0xF9;
    array_temp[2] = 0x00;

    array_temp[3] = 0x78;
    array_temp[4] = 0x31;
    array_temp[5] = 0x01;

    array_temp[6] = 0xA0;
    array_temp[7] = 0x54;
    array_temp[8] = 0x01;

    array_temp[9] = 0x44;
    array_temp[10] = 0x74;
    array_temp[11] = 0x01;

    array_temp[12] = 0xF0;
    array_temp[13] = 0x49;
    array_temp[14] = 0x02;
    MODIFY_EEP_W(Addr_DLS_Cur_III_AD_value, array_temp, 15, 0xA0); // 630�Ǽ�˲������ADֵ
    delay_ms(5);
    array_temp[0] = 0x1D;
    array_temp[1] = 0x00;
    array_temp[2] = 0x00;

    array_temp[3] = 0x12;
    array_temp[4] = 0x00;
    array_temp[5] = 0x00;

    array_temp[6] = 0x0A;
    array_temp[7] = 0x00;
    array_temp[8] = 0x00;

    array_temp[9] = 0x09;
    array_temp[10] = 0x00;
    array_temp[11] = 0x00;

    array_temp[12] = 0x04;
    array_temp[13] = 0x00;
    array_temp[14] = 0x00;
    MODIFY_EEP_W(Addr_DLS_Cur_III_slope, array_temp, 15, 0xA0); // 630�Ǽ�˲������б��ֵ
    delay_ms(5);
    array_temp[0] = 0x00;
    array_temp[1] = 0x00;
    array_temp[2] = 0x00;

    array_temp[3] = 0x98;
    array_temp[4] = 0x08;
    array_temp[5] = 0x00;

    array_temp[6] = 0xB8;
    array_temp[7] = 0x0B;
    array_temp[8] = 0x00;

    array_temp[9] = 0x3C;
    array_temp[10] = 0x0F;
    array_temp[11] = 0x00;

    array_temp[12] = 0xC0;
    array_temp[13] = 0x12;
    array_temp[14] = 0x00;
    MODIFY_EEP_W(Addr_DLS_Cur_III_Value, array_temp, 15, 0xA0); // 630�Ǽ�˲������ֵ
    delay_ms(5);
    /********************************************************************/

    IWDG_Feed();
    array_temp[0] = 0x00;
    MODIFY_EEP_W(Addr_I_2d, array_temp, 1, 0xA0); // ���ܱ����Ƿ�����ʼ��  ����

    array_temp[0] = 0x01;
    MODIFY_EEP_W(Addr_I_3d, array_temp, 1, 0xA0); // ���ܱ����Ƿ�����ʼ��  ����

    array_temp[0] = 0x01;
    MODIFY_EEP_W(Addr_I_ia, array_temp, 1, 0xA0); // �����غ�բ

    array_temp[0] = 0x00;
    MODIFY_EEP_W(Addr_L_TB, array_temp, 1, 0xA0); // ͻ��

    array_temp[0] = 0x00;
    MODIFY_EEP_W(Addr_L_specialwave, array_temp, 1, 0xA0); // �ز�2022.2.24

    array_temp[0] = 0x01;
    MODIFY_EEP_W(Addr_shangdian, array_temp, 1, 0xA0); // �ϵ��բ2022.2.24
    MODIFY_EEP_W(Addr_dianya, array_temp, 1, 0xA0);    // �ϵ��բ2022.2.24
    MODIFY_EEP_W(Addr_loudian, array_temp, 1, 0xA0);   // �ϵ��բ2022.2.24
    MODIFY_EEP_W(Addr_dianliu, array_temp, 1, 0xA0);   // �ϵ��բ2022.2.24
    MODIFY_EEP_W(Addr_wendu, array_temp, 1, 0xA0);
    MODIFY_EEP_W(Addr_TX, array_temp, 1, 0xA0);
    array_temp[0] = 0x00;
    MODIFY_EEP_W(Addr_C_IP, array_temp, 1, 0xA0); // ��·��ʱ

    array_temp[0] = 0x00;
    MODIFY_EEP_W(Addr_L_JC, array_temp, 1, 0xA0);

    array_temp[0] = 0x01;
    MODIFY_EEP_W(Addr_F_gc, array_temp, 1, 0xA0);
    IWDG_Feed();
    ctrlword[0] = 0x74;
    ctrlword[1] = 0x55; // ��ѹ����
    ctrlword[2] = 0x00;
    ctrlword[3] = 0x6A; // ©�絵λ�޸�Ϊ1000//ʱ�䵵λ�ĳ�500ms
    ctrlword[4] = 0x61;
    MODIFY_EEP_W(Addr_crtl_word1, ctrlword, 5, 0xA0); // �ѿ�����д��ȥ
    delay_ms(5);
    array_temp[0] = 0x02;
    MODIFY_EEP_W(Addr_TH_LCur, array_temp, 1, 0xA0);
    ctrlword1_analyze();
    ctrlword2_analyze();
    ctrlword3_analyze();
    ctrlword4_analyze();
    delay_ms(5);
    IWDG_Feed();
    array_temp[0] = 0x02;
    MODIFY_EEP_W(Addr_Type_Cur, array_temp, 1, 0xA0); // �����Ǽܵȼ�

    array_temp[0] = 0x03;
    MODIFY_EEP_W(Addr_Vol_g, array_temp, 1, 0xA0); // ��ѹ��λ

    array_temp[0] = 0x02;
    MODIFY_EEP_W(Addr_Vol_q, array_temp, 1, 0xA0); // Ƿѹ��λ

    array_temp[0] = 0x01;
    MODIFY_EEP_W(Addr_Vol_ch, array_temp, 1, 0xA0); // ��Ƿѹ�غ�բ

    IWDG_Feed();
    //  D_QY_yanshi=((key_state)&0x07);//0000 01111
    array_tmp[0] = 0x00;
    MODIFY_EEP_W(Addr_QY_yanshi, array_tmp, 1, 0xA0);

    array_tmp[0] = 0x00;
    MODIFY_EEP_W(Addr_GY_yanshi, array_tmp, 1, 0xA0);

    IWDG_Feed();
    array_temp[0] = 0x00;
    MODIFY_EEP_W(Addr_data_clear, array_temp, 1, 0xA0);

    array_temp[0] = 0x00;
    MODIFY_EEP_W(Addr_SY_F, array_temp, 1, 0xA0);

    array_tmp[0] = 0x03;
    MODIFY_EEP_W(Addr_QX_BAOHU, array_tmp, 1, 0xA0);
    array_tmp[0] = 0x03;
    MODIFY_EEP_W(Addr_QL_BAOHU, array_tmp, 1, 0xA0);

    array_temp[0] = 0x00;
    MODIFY_EEP_W(Addr_D_A_Lcur, array_temp, 1, 0xA0); // ©���Զ���λ

    array_temp[0] = 19;                            // 0x00;
    MODIFY_EEP_W(Addr_D_Cur, array_temp, 1, 0xA0); // ������λ

    array_temp[0] = 0;                              // 0x00;
    MODIFY_EEP_W(Addr_D2_Cur, array_temp, 1, 0xA0); // ���ε�λ

    array_temp[0] = 0x03;                           // 0x00;
    MODIFY_EEP_W(Addr_D3_Cur, array_temp, 1, 0xA0); // ���ε�λ

    array_temp[0] = 0;                               // 0x00;
    MODIFY_EEP_W(Addr_D2_Time, array_temp, 1, 0xA0); // ��·����ʱ��λ

    array_tmp[0] = 0x04;
    MODIFY_EEP_W(Addr_CurLong_Time, array_tmp, 1, 0xA0);

    array_temp[0] = 0x00;
    MODIFY_EEP_W(Addr_SY_yanshi, array_temp, 1, 0xA0);

    IWDG_Feed();
    array_temp[0] = 0x55;
    array_temp[1] = 0xAA;
    MODIFY_EEP_W(Addr_FACTORINIT_value, array_temp, 2, 0xA0);

    IWDG_Feed();
    array_temp[0] = 0;
    array_temp[1] = 0;
    MODIFY_EEP_W(Addr_L_factor, array_temp, 2, 0xA0);
    array_temp[0] = 0;
    array_temp[1] = 0;
    MODIFY_EEP_W(Addr_AV_factor, array_temp, 2, 0xA0);
    array_temp[0] = 0;
    array_temp[1] = 0;
    MODIFY_EEP_W(Addr_BV_factor, array_temp, 2, 0xA0);
    array_temp[0] = 0;
    array_temp[1] = 0;
    MODIFY_EEP_W(Addr_CV_factor, array_temp, 2, 0xA0);
    IWDG_Feed();
    array_temp[0] = 0;
    array_temp[1] = 0;
    MODIFY_EEP_W(Addr_AI_factor, array_temp, 2, 0xA0);
    array_temp[0] = 0;
    array_temp[1] = 0;
    MODIFY_EEP_W(Addr_BI_factor, array_temp, 2, 0xA0);
    array_temp[0] = 0;
    array_temp[1] = 0;
    MODIFY_EEP_W(Addr_CI_factor, array_temp, 2, 0xA0);
    /********************************����У׼б��*********************/
    IWDG_Feed();
    array_temp[0] = 0xEA;
    array_temp[1] = 0x60;
    MODIFY_EEP_W(Addr_L1_slope, array_temp, 2, 0xA0);

    array_temp[0] = 0x84;
    array_temp[1] = 0x3F;
    MODIFY_EEP_W(Addr_Leak1_temp, array_temp, 2, 0xA0);

    array_temp[0] = 0x65;
    array_temp[1] = 0x48;
    MODIFY_EEP_W(Addr_V1_A_slope, array_temp, 2, 0xA0);

    array_temp[0] = 0x00;
    array_temp[1] = 0x48;
    MODIFY_EEP_W(Addr_V1_B_slope, array_temp, 2, 0xA0);

    array_temp[0] = 0x03;
    array_temp[1] = 0x48;
    MODIFY_EEP_W(Addr_V1_C_slope, array_temp, 2, 0xA0);
    /***********250�Ǽ�******************/
    array_temp[0] = 0x19;
    array_temp[1] = 0x3D;
    MODIFY_EEP_W(Addr_I1_A_slope, array_temp, 2, 0xA0);
    array_temp[0] = 0x38;
    array_temp[1] = 0x40;
    MODIFY_EEP_W(Addr_I1_B_slope, array_temp, 2, 0xA0);
    array_temp[0] = 0xC0;
    array_temp[1] = 0x3B;
    MODIFY_EEP_W(Addr_I1_C_slope, array_temp, 2, 0xA0);

    array_temp[0] = 0x26;
    array_temp[1] = 0x6A;
    MODIFY_EEP_W(Addr_I1_A_slope1, array_temp, 2, 0xA0);
    array_temp[0] = 0x18;
    array_temp[1] = 0x6A;
    MODIFY_EEP_W(Addr_I1_B_slope1, array_temp, 2, 0xA0);
    array_temp[0] = 0x42;
    array_temp[1] = 0x6A;
    MODIFY_EEP_W(Addr_I1_C_slope1, array_temp, 2, 0xA0);

    array_temp[0] = 0x30;
    array_temp[1] = 0x1A;
    MODIFY_EEP_W(Addr_CurA_cal_tmp, array_temp, 2, 0xA0);
    array_temp[0] = 0xEA;
    array_temp[1] = 0x18;
    MODIFY_EEP_W(Addr_CurB_cal_tmp, array_temp, 2, 0xA0);
    array_temp[0] = 0xC7;
    array_temp[1] = 0x1A;
    MODIFY_EEP_W(Addr_CurC_cal_tmp, array_temp, 2, 0xA0);

    array_temp[0] = 0xCC;
    array_temp[1] = 0x30;
    MODIFY_EEP_W(Addr_CurA_cal_tmp1, array_temp, 2, 0xA0);
    array_temp[0] = 0x89;
    array_temp[1] = 0x2F;
    MODIFY_EEP_W(Addr_CurB_cal_tmp1, array_temp, 2, 0xA0);
    array_temp[0] = 0x5D;
    array_temp[1] = 0x31;
    MODIFY_EEP_W(Addr_CurC_cal_tmp1, array_temp, 2, 0xA0);
    //				array_temp[0]=0x5D;
    //		array_temp[1]=0x52;
    //		MODIFY_EEP_W(Addr_I1_A_slope,array_temp,2,0xA0);
    //
    //		array_temp[0]=0xB1;
    //		array_temp[1]=0x50;
    //		MODIFY_EEP_W(Addr_I1_B_slope,array_temp,2,0xA0);
    //
    //		array_temp[0]=0x8F;
    //		array_temp[1]=0x51;
    //		MODIFY_EEP_W(Addr_I1_C_slope,array_temp,2,0xA0);
    //
    //	  array_temp[0]=0xBF;
    //		array_temp[1]=0x52;
    //		MODIFY_EEP_W(Addr_I1_A_slope1,array_temp,2,0xA0);
    //
    //		array_temp[0]=0x94;
    //		array_temp[1]=0x52;
    //		MODIFY_EEP_W(Addr_I1_B_slope1,array_temp,2,0xA0);
    //
    //		array_temp[0]=0xF8;
    //		array_temp[1]=0x52;
    //		MODIFY_EEP_W(Addr_I1_C_slope1,array_temp,2,0xA0);
    //
    //		array_temp[0]=0xAF;
    //		array_temp[1]=0x13;
    //		MODIFY_EEP_W(Addr_CurA_cal_tmp,array_temp,2,0xA0);
    //		array_temp[0]=0xAF;
    //		array_temp[1]=0x13;
    //		MODIFY_EEP_W(Addr_CurB_cal_tmp,array_temp,2,0xA0);
    //		array_temp[0]=0xAF;
    //		array_temp[1]=0x13;
    //		MODIFY_EEP_W(Addr_CurC_cal_tmp,array_temp,2,0xA0);
    //		array_temp[0]=0xAF;
    //		array_temp[1]=0x13;
    //		MODIFY_EEP_W(Addr_CurA_cal_tmp1,array_temp,2,0xA0);
    //		array_temp[0]=0xAF;
    //		array_temp[1]=0x13;
    //		MODIFY_EEP_W(Addr_CurB_cal_tmp1,array_temp,2,0xA0);
    //		array_temp[0]=0xAF;
    //		array_temp[1]=0x13;
    //		MODIFY_EEP_W(Addr_CurC_cal_tmp1,array_temp,2,0xA0);
    array_temp[0] = 0xD1;
    array_temp[1] = 0x10;
    MODIFY_EEP_W(Addr_Vol1_A_temp, array_temp, 2, 0xA0);
    array_temp[0] = 0x3B;
    array_temp[1] = 0x11;
    MODIFY_EEP_W(Addr_Vol1_B_temp, array_temp, 2, 0xA0);
    array_temp[0] = 0xC9;
    array_temp[1] = 0x10;
    MODIFY_EEP_W(Addr_Vol1_C_temp, array_temp, 2, 0xA0);

    /**************100�Ǽ�*******************/
    IWDG_Feed();
    array_temp[0] = 0x2A;
    array_temp[1] = 0x5D;
    MODIFY_EEP_W(Addr100_L1_slope, array_temp, 2, 0xA0);

    array_temp[0] = 0x84;
    array_temp[1] = 0x3F;
    MODIFY_EEP_W(Addr100_Leak1_temp, array_temp, 2, 0xA0);

    array_temp[0] = 0x47;
    array_temp[1] = 0x42;
    MODIFY_EEP_W(Addr_I1_A_slope, array_temp, 2, 0xA0);
    array_temp[0] = 0xD2;
    array_temp[1] = 0x3E;
    MODIFY_EEP_W(Addr_I1_B_slope, array_temp, 2, 0xA0);
    array_temp[0] = 0x3D;
    array_temp[1] = 0x40;
    MODIFY_EEP_W(Addr_I1_C_slope, array_temp, 2, 0xA0);

    array_temp[0] = 0xD6;
    array_temp[1] = 0x44;
    MODIFY_EEP_W(Addr_I1_A_slope1, array_temp, 2, 0xA0);
    array_temp[0] = 0x9B;
    array_temp[1] = 0x43;
    MODIFY_EEP_W(Addr_I1_B_slope1, array_temp, 2, 0xA0);
    array_temp[0] = 0x21;
    array_temp[1] = 0x44;
    MODIFY_EEP_W(Addr_I1_C_slope1, array_temp, 2, 0xA0);

    array_temp[0] = 0x12;
    array_temp[1] = 0x0C;
    MODIFY_EEP_W(Addr_CurA_cal_tmp, array_temp, 2, 0xA0);
    array_temp[0] = 0xBC;
    array_temp[1] = 0x0C;
    MODIFY_EEP_W(Addr_CurB_cal_tmp, array_temp, 2, 0xA0);
    array_temp[0] = 0x74;
    array_temp[1] = 0x0C;
    MODIFY_EEP_W(Addr_CurC_cal_tmp, array_temp, 2, 0xA0);

    array_temp[0] = 0xB6;
    array_temp[1] = 0x1D;
    MODIFY_EEP_W(Addr_CurA_cal_tmp1, array_temp, 2, 0xA0);
    array_temp[0] = 0x7C;
    array_temp[1] = 0x1E;
    MODIFY_EEP_W(Addr_CurB_cal_tmp1, array_temp, 2, 0xA0);
    array_temp[0] = 0x11;
    array_temp[1] = 0x1E;
    MODIFY_EEP_W(Addr_CurC_cal_tmp1, array_temp, 2, 0xA0);
    /**************400�Ǽ�*******************/
    IWDG_Feed();
    array_temp[0] = 0x40;
    array_temp[1] = 0x3F;
    MODIFY_EEP_W(Addr400_L1_slope, array_temp, 2, 0xA0);

    array_temp[0] = 0x84;
    array_temp[1] = 0x3F;
    MODIFY_EEP_W(Addr400_Leak1_temp, array_temp, 2, 0xA0);

    array_temp[0] = 0x99;
    array_temp[1] = 0x4E;
    MODIFY_EEP_W(Addr400_I1_A_slope, array_temp, 2, 0xA0);
    array_temp[0] = 0xB7;
    array_temp[1] = 0x51;
    MODIFY_EEP_W(Addr400_I1_B_slope, array_temp, 2, 0xA0);
    array_temp[0] = 0x27;
    array_temp[1] = 0x4D;
    MODIFY_EEP_W(Addr400_I1_C_slope, array_temp, 2, 0xA0);

    array_temp[0] = 0x46;
    array_temp[1] = 0x6C;
    MODIFY_EEP_W(Addr400_I1_A_slope1, array_temp, 2, 0xA0);
    array_temp[0] = 0x2B;
    array_temp[1] = 0x6C;
    MODIFY_EEP_W(Addr400_I1_B_slope1, array_temp, 2, 0xA0);
    array_temp[0] = 0x0F;
    array_temp[1] = 0x6C;
    MODIFY_EEP_W(Addr400_I1_C_slope1, array_temp, 2, 0xA0);

    array_temp[0] = 0x92;
    array_temp[1] = 0x20;
    MODIFY_EEP_W(Addr400_CurA_cal_tmp, array_temp, 2, 0xA0);
    array_temp[0] = 0x54;
    array_temp[1] = 0x1F;
    MODIFY_EEP_W(Addr400_CurB_cal_tmp, array_temp, 2, 0xA0);
    array_temp[0] = 0x2E;
    array_temp[1] = 0x21;
    MODIFY_EEP_W(Addr400_CurC_cal_tmp, array_temp, 2, 0xA0);

    array_temp[0] = 0x09;
    array_temp[1] = 0x44;
    MODIFY_EEP_W(Addr400_CurA_cal_tmp1, array_temp, 2, 0xA0);
    array_temp[0] = 0xD4;
    array_temp[1] = 0x42;
    MODIFY_EEP_W(Addr400_CurB_cal_tmp1, array_temp, 2, 0xA0);
    array_temp[0] = 0xB7;
    array_temp[1] = 0x44;
    MODIFY_EEP_W(Addr400_CurC_cal_tmp1, array_temp, 2, 0xA0);
    /**************630�Ǽ�*******************/
    IWDG_Feed();
    array_temp[0] = 0xE3;
    array_temp[1] = 0x3F;
    MODIFY_EEP_W(Addr630_L1_slope, array_temp, 2, 0xA0);

    array_temp[0] = 0x84;
    array_temp[1] = 0x3F;
    MODIFY_EEP_W(Addr630_Leak1_temp, array_temp, 2, 0xA0);

    array_temp[0] = 0x73;
    array_temp[1] = 0x76;
    MODIFY_EEP_W(Addr630_I1_A_slope, array_temp, 2, 0xA0);
    array_temp[0] = 0x12;
    array_temp[1] = 0x7B;
    MODIFY_EEP_W(Addr630_I1_B_slope, array_temp, 2, 0xA0);
    array_temp[0] = 0x94;
    array_temp[1] = 0x74;
    MODIFY_EEP_W(Addr630_I1_C_slope, array_temp, 2, 0xA0);

    array_temp[0] = 0x87;
    array_temp[1] = 0xA8;
    MODIFY_EEP_W(Addr630_I1_A_slope1, array_temp, 2, 0xA0);
    array_temp[0] = 0x54;
    array_temp[1] = 0xA8;
    MODIFY_EEP_W(Addr630_I1_B_slope1, array_temp, 2, 0xA0);
    array_temp[0] = 0x74;
    array_temp[1] = 0xA8;
    MODIFY_EEP_W(Addr630_I1_C_slope1, array_temp, 2, 0xA0);

    array_temp[0] = 0x0A;
    array_temp[1] = 0x22;
    MODIFY_EEP_W(Addr630_CurA_cal_tmp, array_temp, 2, 0xA0);
    array_temp[0] = 0xC3;
    array_temp[1] = 0x20;
    MODIFY_EEP_W(Addr630_CurB_cal_tmp, array_temp, 2, 0xA0);
    array_temp[0] = 0x96;
    array_temp[1] = 0x22;
    MODIFY_EEP_W(Addr630_CurC_cal_tmp, array_temp, 2, 0xA0);

    array_temp[0] = 0xED;
    array_temp[1] = 0x45;
    MODIFY_EEP_W(Addr630_CurA_cal_tmp1, array_temp, 2, 0xA0);
    array_temp[0] = 0xB1;
    array_temp[1] = 0x44;
    MODIFY_EEP_W(Addr630_CurB_cal_tmp1, array_temp, 2, 0xA0);
    array_temp[0] = 0x7D;
    array_temp[1] = 0x46;
    MODIFY_EEP_W(Addr630_CurC_cal_tmp1, array_temp, 2, 0xA0);
    /**************800�Ǽ�*******************/
    IWDG_Feed();
    array_temp[0] = 0xEA;
    array_temp[1] = 0x60;
    MODIFY_EEP_W(Addr800_L1_slope, array_temp, 2, 0xA0);

    array_temp[0] = 0x84;
    array_temp[1] = 0x3F;
    MODIFY_EEP_W(Addr800_Leak1_temp, array_temp, 2, 0xA0);

    array_temp[0] = 0xDC;
    array_temp[1] = 0x5A;
    MODIFY_EEP_W(Addr800_I1_A_slope, array_temp, 2, 0xA0);
    array_temp[0] = 0xDC;
    array_temp[1] = 0x5A;
    MODIFY_EEP_W(Addr800_I1_B_slope, array_temp, 2, 0xA0);
    array_temp[0] = 0xDC;
    array_temp[1] = 0x5A;
    MODIFY_EEP_W(Addr800_I1_C_slope, array_temp, 2, 0xA0);

    array_temp[0] = 0x9D;
    array_temp[1] = 0x64;
    MODIFY_EEP_W(Addr800_I1_A_slope1, array_temp, 2, 0xA0);
    array_temp[0] = 0x9D;
    array_temp[1] = 0x64;
    MODIFY_EEP_W(Addr800_I1_B_slope1, array_temp, 2, 0xA0);
    array_temp[0] = 0x9D;
    array_temp[1] = 0x64;
    MODIFY_EEP_W(Addr800_I1_C_slope1, array_temp, 2, 0xA0);

    array_temp[0] = 0x4F;
    array_temp[1] = 0x0C;
    MODIFY_EEP_W(Addr800_CurA_cal_tmp, array_temp, 2, 0xA0);
    array_temp[0] = 0x4F;
    array_temp[1] = 0x0C;
    MODIFY_EEP_W(Addr800_CurB_cal_tmp, array_temp, 2, 0xA0);
    array_temp[0] = 0x4F;
    array_temp[1] = 0x0C;
    MODIFY_EEP_W(Addr800_CurC_cal_tmp, array_temp, 2, 0xA0);

    array_temp[0] = 0xEB;
    array_temp[1] = 0x4B;
    MODIFY_EEP_W(Addr800_CurA_cal_tmp1, array_temp, 2, 0xA0);
    array_temp[0] = 0xEB;
    array_temp[1] = 0x4B;
    MODIFY_EEP_W(Addr800_CurB_cal_tmp1, array_temp, 2, 0xA0);
    array_temp[0] = 0xEB;
    array_temp[1] = 0x4B;
    MODIFY_EEP_W(Addr800_CurC_cal_tmp1, array_temp, 2, 0xA0);
    /******************************************************************************************/
    IWDG_Feed();
    array_temp[0] = 0;
    MODIFY_EEP_W(Addr_AV_F, array_temp, 1, 0xA0);
    array_temp[0] = 0;
    MODIFY_EEP_W(Addr_BV_F, array_temp, 1, 0xA0);
    array_temp[0] = 0;
    MODIFY_EEP_W(Addr_CV_F, array_temp, 1, 0xA0);
    array_temp[0] = 0;
    MODIFY_EEP_W(Addr_AI_F, array_temp, 1, 0xA0);
    array_temp[0] = 0;
    MODIFY_EEP_W(Addr_BI_F, array_temp, 1, 0xA0);
    array_temp[0] = 0;
    MODIFY_EEP_W(Addr_CI_F, array_temp, 1, 0xA0);
    // AT24C64_W(array_temp,16,1);
    array_temp[0] = 0xAA;
    // AT24C64_W(array_temp,17,1)
    //    array_tmp[0] = 0x01;
    //    MODIFY_EEP_W(Addr_shangdian,array_tmp,1,0xA0);
    array_tmp[0] = 0x00;
    MODIFY_EEP_W(Addr_jiaozhun, array_tmp, 1, 0xA0);

    array_tmp[0] = 0x01;
    MODIFY_EEP_W(Addr_DIANYA_chonghe, array_tmp, 1, 0xA0);
    array_tmp[0] = 0x00;
    MODIFY_EEP_W(Addr_duandian, array_tmp, 1, 0xA0);
    /*          �ۼƼ�¼����          */
    // ���������ܴ��� 000000
    IWDG_Feed();
    array_temp[0] = array_temp[1] = array_temp[2] = 0;
    lenth = Lenth_clear_num;
    Addr_factor = Addr_clear_num;
    MODIFY_EEP_W(Addr_factor, array_temp, lenth, 0xA0);
    // �ѿ۴���
    array_temp[0] = array_temp[1] = 0;
    MODIFY_EEP_W(Addr_trip_num, array_temp, 2, 0xA0);
    // close ����
    array_temp[0] = array_temp[1] = 0;
    MODIFY_EEP_W(Addr_close_num, array_temp, 2, 0xA0);
    // ©���ѿ۴���
    array_temp[0] = array_temp[1] = 0;
    MODIFY_EEP_W(Addr_leak_num, array_temp, 2, 0xA0);
    // �����ѿ۴���
    array_temp[0] = array_temp[1] = 0;
    MODIFY_EEP_W(Addr_current_num, array_temp, 2, 0xA0);
    // ��ѹ�ѿ۴���
    array_temp[0] = array_temp[1] = 0;
    MODIFY_EEP_W(Addr_vol_num, array_temp, 2, 0xA0);
    // �ֶ��ѿ۴���
    array_temp[0] = array_temp[1] = 0;
    MODIFY_EEP_W(Addr_hand_num, array_temp, 2, 0xA0);
    // �����ѿ۴���
    array_temp[0] = array_temp[1] = 0;
    MODIFY_EEP_W(Addr_zero_num, array_temp, 2, 0xA0);
    // �����ѿ۴���
    array_temp[0] = array_temp[1] = 0;
    MODIFY_EEP_W(Addr_test_num, array_temp, 2, 0xA0);
    // �˳�©�籣������
    IWDG_Feed();
    // ����ʱ��
    array_temp[0] = array_temp[1] = 0;
    MODIFY_EEP_W(Addr_leakquit_num, array_temp, 2, 0xA0);

    // ��·���Ӵ���
    array_temp[0] = array_temp[1] = 0;
    MODIFY_EEP_W(Addr_2D_num, array_temp, 2, 0xA0);
    // ʣ����������˳���������
    array_temp[0] = 0;
    MODIFY_EEP_W(Addr_leakprotect_num, array_temp, 2, 0xA0);
    // ʣ��������޴���
    array_temp[0] = 0;
    MODIFY_EEP_W(Addr_leakover_num, array_temp, 2, 0xA0);
    // ʣ������仯����
    //	array_temp[0] = 0;
    //	MODIFY_EEP_W(Addr_leakchange_num,array_temp,1);
    // �Լ����
    //	array_temp[0] = 0;
    //	MODIFY_EEP_W(Addr_tripkey_num,array_temp,1);
    // ��·��˲����
    array_temp[0] = array_temp[1] = 0;
    MODIFY_EEP_W(Addr_3D_num, array_temp, 2, 0xA0);
    Sum_run_time = 0;
    DectoBCD(array_temp, Sum_run_time, 4);
    MODIFY_EEP_W(Addr_protect_time, array_temp, 4, 0xA0);

    if (tmp == 0x01)
    {
        tim_y = 2017;
        tim_m = 6;
        ;
        tim_d = 11;
        tim_h = 1;
        tim_f = 1;
        tim_s = 0;
    }
    else
    {
        tim_y = 2017;
        tim_m = 6;
        ;
        tim_d = 11;
        tim_h = 1;
        tim_f = 1;
        tim_s = 0;
    }
    IWDG_Feed();
    RTC_Set_Time(array_temp[3], array_temp[4], array_temp[5]);
    RTC_Set_Date(array_temp[0], array_temp[1], array_temp[2]);
    // �豸��ַ

    Addr_factor = Addr_dev_addr;
    lenth = Lenth_dev_addr;
    self_addr_code[0] = 0x00;
    self_addr_code[1] = 0x00;
    self_addr_code[2] = 0x00;
    self_addr_code[3] = 0x00;
    self_addr_code[4] = 0x00;
    self_addr_code[5] = 0x00; // lpb,�豸�ϵ��Զ��ظ���ʼ��ַ
    MODIFY_EEP_W(Addr_factor, self_addr_code, lenth, 0xA0);
    // �豸ID
    Addr_factor = Addr_dev_id;
    lenth = Lenth_dev_id;
    MODIFY_EEP_W(Addr_factor, dev_id_code, lenth, 0xA0);
    // �ʲ��������
    Addr_factor = Addr_dev_code;
    lenth = Lenth_dev_code;
    MODIFY_EEP_W(Addr_factor, dev_code_code, lenth, 0xA0);
    // �豸�ͺ�
    Addr_factor = Addr_equi_type;
    lenth = Lenth_equi_type;
    MODIFY_EEP_W(Addr_factor, equi_type_code, lenth, 0xA0);
    IWDG_Feed();

    IWDG_Feed();
    Addr_factor = Addr_factory_code;
    lenth = Lenth_factory_code;
    MODIFY_EEP_W(Addr_factor, factory_code_code, lenth, 0xA0);
    // ʣ��������ޱ�������ֵ 2
    Addr_factor = Addr_alarm_value;
    lenth = Lenth_alarm_value;
    MODIFY_EEP_W(Addr_factor, alarm_value_code, lenth, 0xA0);
    // ʣ�������¼�仯��ֵ����ֵ(10-99)
    Addr_factor = Addr_record_value;
    lenth = Lenth_record_value;
    MODIFY_EEP_W(Addr_factor, record_value_code, lenth, 0xA0);
    // ʣ�������¼���ʱ������ֵ(01-99)
    Addr_factor = Addr_record_time;
    lenth = Lenth_record_time;
    MODIFY_EEP_W(Addr_factor, record_time_code, lenth, 0xA0);
    // ��ʱ��������ʱ�� 3
    Addr_factor = Addr_timed_trip;
    lenth = Lenth_timed_trip;
    MODIFY_EEP_W(Addr_factor, timed_trip_code, lenth, 0xA0);
    IWDG_Feed();
    // ����ѹ����ֵ 2
    Addr_factor = Addr_over_vol;
    lenth = Lenth_over_vol;
    MODIFY_EEP_W(Addr_factor, over_vol_code, lenth, 0xA0);
    // Ƿ��ѹ����ֵ 2
    Addr_factor = Addr_under_vol;
    lenth = Lenth_under_vol;
    MODIFY_EEP_W(Addr_factor, under_vol_code, lenth, 0xA0);

    IWDG_Feed();
    // �����ѹ����ֵ 2
    Addr_factor = Addr_break_phase;
    lenth = Lenth_break_phase;
    MODIFY_EEP_W(Addr_factor, break_phase_code, lenth, 0xA0);
    // ���������ֵ 3
    Addr_factor = Addr_rated_current;
    lenth = Lenth_rated_current;
    MODIFY_EEP_W(Addr_factor, rated_current_code, lenth, 0xA0);
    // �������ޱ���
    Addr_factor = Addr_over_current;
    lenth = Lenth_over_current;
    MODIFY_EEP_W(Addr_factor, over_current_code, lenth, 0xA0);

    // ����
    array_temp[0] = 0x00;
    array_temp[1] = 0x00;
    array_temp[2] = 0x00;
    array_temp[3] = 0x00;
    MODIFY_EEP_W(Addr_0_password, array_temp, 4, 0xA0);
    array_temp[0] = 0x01;
    array_temp[1] = 0x11;
    array_temp[2] = 0x11;
    array_temp[3] = 0x11;
    MODIFY_EEP_W(Addr_1_password, array_temp, 4, 0xA0);
    array_temp[0] = 0x02;
    array_temp[1] = 0x22;
    array_temp[2] = 0x22;
    array_temp[3] = 0x22;
    MODIFY_EEP_W(Addr_2_password, array_temp, 4, 0xA0);
    // ������
    array_temp[0] = 0x01;
    MODIFY_EEP_W(Addr_baud, array_temp, 1, 0xA0);

    IWDG_Feed();
    /*      �¼���¼ָ������            */
    //  ©���¼�ĵ�ַָ��
    array_temp[0] = 0x00;
    array_temp[1] = 0x00;
    MODIFY_EEP_W(Addr_point_leakrecord, array_temp, 2, 0xA0);

    array_temp[0] = 0x00;
    MODIFY_EEP_W(Addr_point_leak_max, array_temp, 1, 0xA0);

    array_temp[0] = 0x00;
    MODIFY_EEP_W(Addr_point_Avol_max, array_temp, 1, 0xA0);

    array_temp[0] = 0x00;
    MODIFY_EEP_W(Addr_point_Bvol_max, array_temp, 1, 0xA0);

    array_temp[0] = 0x00;
    MODIFY_EEP_W(Addr_point_Cvol_max, array_temp, 1, 0xA0);

    array_temp[0] = 0x00;
    MODIFY_EEP_W(Addr_point_Acur_max, array_temp, 1, 0xA0);

    array_temp[0] = 0x00;
    MODIFY_EEP_W(Addr_point_Bcur_max, array_temp, 1, 0xA0);

    array_temp[0] = 0x00;
    MODIFY_EEP_W(Addr_point_Ccur_max, array_temp, 1, 0xA0);
    IWDG_Feed();
    array_temp[0] = 0x00;
    MODIFY_EEP_W(Addr_point_leak_min, array_temp, 1, 0xA0);

    array_temp[0] = 0x00;
    MODIFY_EEP_W(Addr_point_Avol_min, array_temp, 1, 0xA0);

    array_temp[0] = 0x00;
    MODIFY_EEP_W(Addr_point_Bvol_min, array_temp, 1, 0xA0);

    array_temp[0] = 0x00;
    MODIFY_EEP_W(Addr_point_Cvol_min, array_temp, 1, 0xA0);

    array_temp[0] = 0x00;
    MODIFY_EEP_W(Addr_point_Acur_min, array_temp, 1, 0xA0);

    array_temp[0] = 0x00;
    MODIFY_EEP_W(Addr_point_Bcur_min, array_temp, 1, 0xA0);

    array_temp[0] = 0x00;
    MODIFY_EEP_W(Addr_point_Ccur_min, array_temp, 1, 0xA0);

    array_temp[0] = 0;
    MODIFY_EEP_W(Addr_point_event_trip, array_temp, 1, 0xA0);

    array_temp[0] = 0;
    MODIFY_EEP_W(Addr_point_event_trip_24C256, array_temp, 1, 0xA0);
    IWDG_Feed();
    array_temp[0] = 0;
    MODIFY_EEP_W(Addr_point_event_self, array_temp, 1, 0xA0);

    array_temp[0] = 0;
    array_temp[1] = 0;
    array_temp[2] = 0;
    array_temp[3] = 0;
    MODIFY_EEP_W(Addr_mima_set, array_temp, 4, 0xA0);

    // Rewrite_buffer(0);
    // pw1 = 0x12;pw2 = 0x34;pw3 = 0x56;pw4 = 0x78;
    // IapEraseSector(512);
    // IapEraseSector(1024);
    Addr_factor = 10500;
    lenth = 1000;
    //	EEPROM_C(Addr_factor,lenth);
    //	EEPROM_R(Addr_FACTORINIT_value,array_tmp,150);
    //	MODIFY_EEP_W(Addr_FACTORINIT_value,array_tmp,150);
}

void clear_flags(void)
{
    // �����غ�բǰ��©����ϼ�¼״̬
    if ((F_Trip == 1) || (F_Trip == 2))
    {
        F_Trip = 2;
    }
    else
    {
        F_Trip = 0;
    }
    // F_gz = 0;
    GZ_ph = 0;
    GZ_ph_disp = 0;
    F_TB_start = 0;
    F_TB_gz = 0;
    F_gz_clear = 1;
    F_L_Lock = 0;
    // F_fenzha_G_Array[0]=F_fenzha_G_Array[1]=F_fenzha_G_Array[2]=0 ;
    // F_fenzha_Q_Array[0]=F_fenzha_Q_Array[1]=F_fenzha_Q_Array[2]=0 ;
    F_qxTrip = F_qyTrip = F_gyTrip = F_syTrip = 0; // ȱ�� ��ѹ Ƿѹ ��բ
    F_I_Lock = 0;
    F_GTrip = F_QTrip = 0;
    F_ITrip = F_VTrip = F_UTrip = F_STrip = 0;
    // �����غ�բǰ�Ĺ��������ϼ�¼״̬
    if (F_I_STA == 1)
        F_I_STA = 2;
    else
    {
        F_I_STA = 0;
        F_I_Array[0] = F_I_Array[1] = F_I_Array[2] = F_I_Array[3] = 0;
    }
    T_64_xs = T_64_6s = 0;
    T_64_31s = 0;
    T_64_11s = 0;
    F_L_hezha = F_I_hezha = F_V_hezha = F_UP_hezha = 0;
    T_64_40s = 0;
    F_fz = 0;
    //	if(isfenzha!=0)
    //	//�������ϱ�־����
    //	F_ks=0 ;
    // ���ٶ�����־
    //	F_disp_jg = 0;
    F_disp_tr = 0;
    F_gz_disp = 0x0F;
    F_analog_trip = 0;
    F_tim_gz = 0;
}
/*************************************************
                д��¼����

Record_data_propare()
Write_Record(unsigned char gz_r,unsigned char gz_p)
**************************************************/

void Write_Leak_Record(void)
{
    unsigned char i;
    unsigned char array_temp_R[14], time_tmp[7];
    unsigned int addr_tmp;
    IWDG_Feed(); // ι��
    //	ds1302_read_time_uart(time_tmp);
    HAL_RTC_GetTime(&hrtc, &stimestructure, RTC_FORMAT_BCD);
    HAL_RTC_GetDate(&hrtc, &sdatestructure, RTC_FORMAT_BCD);
    tim_y = sdatestructure.Year; // tim_yΪʮ���ƣ�Ҫת��������
    tim_m = sdatestructure.Month;
    tim_d = sdatestructure.Date;
    tim_h = stimestructure.Hours;
    tim_f = stimestructure.Minutes;
    tim_s = stimestructure.Seconds;
    //	tim_y=tim_y%2000;  //time_tmp[0]=17   ʮ����ת��Ϊ�����ƴ���24C64��
    //	time_tmp[0]=(tim_y/10)<<4;
    //	time_tmp[0]+=(tim_y%10);
    //	time_tmp[1]=(tim_m/10)<<4;
    //	time_tmp[1]+=(tim_m%10);
    //	time_tmp[2]=(tim_d/10)<<4;
    //	time_tmp[2]+=(tim_d%10);
    //	time_tmp[3]=(tim_h/10)<<4;
    //	time_tmp[3]+=(tim_h%10);
    //	time_tmp[4]=(tim_f/10)<<4;
    //	time_tmp[4]+=(tim_f%10);
    //	time_tmp[5]=(tim_s/10)<<4;
    //	time_tmp[5]+=(tim_s%10);
    time_tmp[0] = tim_y;
    time_tmp[1] = tim_m;
    time_tmp[2] = tim_d;
    time_tmp[3] = tim_h;
    time_tmp[4] = tim_f;
    time_tmp[5] = tim_s;

    for (i = 0; i < 6; i++)
    {
        array_temp_R[3 + i] = time_tmp[5 - i]; // array_temp_R[3]=time_tmp[5]    array_temp_R[4]=time_tmp[4]
    }
    array_temp_R[0] = max_phase;                  // 0x01;
    DectoBCD(&array_temp_R[1], Leak_Cur_disp, 2); // Leak_Cur_disp  Ϊʮ����
    point_Leak_record = point_Leak_record + 1;
    if (point_Leak_record == 512)
        point_Leak_record = 0;
    addr_tmp = Addr_record_leak1 + (point_Leak_record * 9);
    MODIFY_EEP_W(addr_tmp, array_temp_R, 9, 0xA0); // ��ʼ��ַ  д��¼   ��д����д��
    DectoBCD(array_temp_R, point_Leak_record, 2);
    MODIFY_EEP_W(Addr_point_leakrecord, array_temp_R, 2, 0xA0);
}

void Write_Selftest_Record(unsigned char self_method)
{
    unsigned char Buf_temp[30], time_tmp[7], i, E2_temp[2];
    Buf_temp[0] = fenzha_chenggong;
    //	ds1302_read_time_uart(time_tmp);
    HAL_RTC_GetTime(&hrtc, &stimestructure, RTC_FORMAT_BCD);
    HAL_RTC_GetDate(&hrtc, &sdatestructure, RTC_FORMAT_BCD);
    tim_y = sdatestructure.Year; // tim_yΪʮ���ƣ�Ҫת��������
    tim_m = sdatestructure.Month;
    tim_d = sdatestructure.Date;
    tim_h = stimestructure.Hours;
    tim_f = stimestructure.Minutes;
    tim_s = stimestructure.Seconds;
    //	tim_y=tim_y%2000;  //time_tmp[0]=17   ʮ����ת��Ϊ�����ƴ���24C64��
    time_tmp[0] = tim_y;
    time_tmp[1] = tim_m;
    time_tmp[2] = tim_d;
    time_tmp[3] = tim_h;
    time_tmp[4] = tim_f;
    time_tmp[5] = tim_s;
    for (i = 0; i < 6; i++)
    {
        Buf_temp[1 + i] = time_tmp[5 - i];
    }
    Buf_temp[7] = self_method;
    Buf_temp[8] = max_phase;                         // 0x01;
    DectoBCD(&Buf_temp[9], Leak_Cur_disp_record, 2); // ©��
    DectoBCD(&Buf_temp[11], ((vol_handle_A(V_Array_record[0])) * 10), 2);
    DectoBCD(&Buf_temp[13], ((vol_handle_B(V_Array_record[1])) * 10), 2);
    DectoBCD(&Buf_temp[15], ((vol_handle_C(V_Array_record[2])) * 10), 2);
    DectoBCD(&Buf_temp[17], ((cur_handle_A(I_Array_record[0])) * 10), 3);
    DectoBCD(&Buf_temp[20], ((cur_handle_B(I_Array_record[1])) * 10), 3);
    DectoBCD(&Buf_temp[23], ((cur_handle_C(I_Array_record[2])) * 10), 3);
    MODIFY_EEP_W((Addr_event_self + 26 * point_event_self), Buf_temp, 25, 0xA0);

    point_event_self = point_event_self + 1;
    if (point_event_self >= 10)
    {
        point_event_self = 0x00;
    }
    E2_temp[0] = point_event_self;
    MODIFY_EEP_W(Addr_point_event_self, E2_temp, 1, 0xA0);
}

void Record_data_propare(void)
{
    // unsigned int tmp_A1,tmp_A2;
    //  tmp_A1 = vol_handle_A(Vol_A_aver)
    //  tmp_A2 = (tmp_A1<<2)-(tmp_A1>>1);
    //  V_Array[0] = tmp_A2-109;
    Leak_Cur_disp_record = Leak_Cur_disp;
    V_Array_record[0] = V_Array[0];
    V_Array_record[1] = V_Array[1];
    V_Array_record[2] = V_Array[2];
    I_Array_record[0] = I_Array_xianshi[0];
    I_Array_record[1] = I_Array_xianshi[1];
    I_Array_record[2] = I_Array_xianshi[2];
}

// STC�޸�
void Write_Record(unsigned char gz_r, unsigned char gz_p)
{
    unsigned char Buf_temp[30];
    unsigned char i, E2_temp[2], time_tmp[8], F_norecord;
    IWDG_Feed(); // ι��
    /***********����բ����***********/
    F_norecord = 0;
    F_gz = gz_r;
    if (F_gz == 0x0B)
        F_gz = 0;
    point_trip = point_trip + 1;
    if (point_trip == 0x08)
        point_trip = 0x07;

    if (1)
    {
        Num_tripall = Num_tripall + 1;
        DectoBCD(Buf_temp, Num_tripall, 2);
        MODIFY_EEP_W(Addr_trip_num, Buf_temp, 2, 0xA0);
    }
    if (gz_r == trip_reason_leak)
    {

        if (F_gc == 1)
        {
            Num_tripleak = Num_tripleak + 1;
            DectoBCD(BCD_temp, Num_tripleak, 2);
            MODIFY_EEP_W(Addr_leak_num, BCD_temp, 2, 0xA0);
        }
        else
        {
            F_norecord = 1;
            Num_tripall = Num_tripall - 1;
            DectoBCD(Buf_temp, Num_tripall, 2);
            MODIFY_EEP_W(Addr_trip_num, Buf_temp, 2, 0xA0);
        }
    }
    /***********��������բ����***********�������غ�բ����բ*/
    if (gz_r == trip_reason_lock)
    {
        if (F_L_Lock == 1)
        {
            Num_triplock = Num_triplock + 1;
            DectoBCD(Buf_temp, Num_triplock, 2);
            MODIFY_EEP_W(Addr_close_num, Buf_temp, 2, 0xA0);
        }
    }
    /***********ʣ�������բ����*********/

    /***************����������բ����*********/
    if (gz_r == trip_reason_cur)
    {
        if (F_gc == 1)
        {
            Num_tripcur = Num_tripcur + 1;
            DectoBCD(Buf_temp, Num_tripcur, 2);
            MODIFY_EEP_W(Addr_current_num, Buf_temp, 2, 0xA0);
        }
        else
        {
            F_norecord = 1;
            Num_tripall = Num_tripall - 1;
            DectoBCD(Buf_temp, Num_tripall, 2);
            MODIFY_EEP_W(Addr_trip_num, Buf_temp, 2, 0xA0);
        }
    }
    /***************��ѹ������բ����*********/
    if (gz_r == trip_reason_overvoltage)
    {

        //		if(F_gc==1)
        //		{
        Num_tripvol = Num_tripvol + 1;
        DectoBCD(Buf_temp, Num_tripvol, 2);
        MODIFY_EEP_W(Addr_vol_num, Buf_temp, 2, 0xA0);
        //		}
        //		else
        //		{
        //			F_norecord = 1;
        //			Num_tripall=Num_tripall-1 ;
        //			DectoBCD(Buf_temp,Num_tripall,2);
        //			MODIFY_EEP_W(Addr_trip_num,Buf_temp,2);
        //		}
    }
    if (gz_r == trip_reason_undervoltage)
    {
        Num_leakover = Num_leakover + 1;
        DectoBCD(Buf_temp, Num_leakover, 2);
        MODIFY_EEP_W(Addr_leakover_num, Buf_temp, 2, 0xA0);
    }
    if (gz_r == trip_reason_phase)
    {
        Num_leakprotect = Num_leakprotect + 1;
        DectoBCD(Buf_temp, Num_leakprotect, 2);
        MODIFY_EEP_W(Addr_leakprotect_num, Buf_temp, 2, 0xA0);
    }
    /***************�ֶ�����*********/
    if (gz_r == trip_reason_hand)
    {
        Num_triphand = Num_triphand + 1;
        DectoBCD(Buf_temp, Num_triphand, 2);
        MODIFY_EEP_W(Addr_hand_num, Buf_temp, 2, 0xA0);
    }
    /***************ȱ�����*********/
    if (gz_r == trip_reason_zero)
    {
        Num_tripzero = Num_tripzero + 1;
        DectoBCD(Buf_temp, Num_tripzero, 2);
        MODIFY_EEP_W(Addr_zero_num, Buf_temp, 2, 0xA0);
    }
    /***************������բ����*********/
    if ((gz_r == trip_reason_timer) || (gz_r == trip_reason_key) || (gz_r == trip_reason_remote))
    {
        Num_triptest = Num_triptest + 1;
        DectoBCD(Buf_temp, Num_triptest, 2);
        MODIFY_EEP_W(Addr_test_num, Buf_temp, 2, 0xA0);
    }
    //	if(gz_r==trip_reason_key)
    //	{
    //	Num_tripkey=Num_tripkey+1;
    //	DectoBCD(Buf_temp,Num_tripkey,2);
    //	MODIFY_EEP_W(Addr_tripkey_num,Buf_temp,2);
    //	}
    /***************�˳���������*********/
    if (gz_r == trip_reason_quit)
    {
        Num_quitleak = Num_quitleak + 1;
        DectoBCD(Buf_temp, Num_quitleak, 2);
        MODIFY_EEP_W(Addr_leakquit_num, Buf_temp, 2, 0xA0);
    }
    if (gz_r == trip_reason_short)
    {
        Num_tripdelay = Num_tripdelay + 1;
        DectoBCD(Buf_temp, Num_tripdelay, 2);
        MODIFY_EEP_W(Addr_2D_num, Buf_temp, 2, 0xA0);
    }
    if (gz_r == trip_reason_3D_cur)
    {
        Num_tripinstant = Num_tripinstant + 1;
        DectoBCD(Buf_temp, Num_tripinstant, 2);
        MODIFY_EEP_W(Addr_3D_num, Buf_temp, 2, 0xA0);
    }
    /************©����բ,��¼***********/
    Buf_temp[0] = gz_r;

    HAL_RTC_GetTime(&hrtc, &stimestructure, RTC_FORMAT_BCD);
    HAL_RTC_GetDate(&hrtc, &sdatestructure, RTC_FORMAT_BCD);
    tim_y = sdatestructure.Year; // tim_yΪʮ���ƣ�Ҫת��������
    tim_m = sdatestructure.Month;
    tim_d = sdatestructure.Date;
    tim_h = stimestructure.Hours;
    tim_f = stimestructure.Minutes;
    tim_s = stimestructure.Seconds;
    time_tmp[0] = tim_y;
    time_tmp[1] = tim_m;
    time_tmp[2] = tim_d;
    time_tmp[3] = tim_h;
    time_tmp[4] = tim_f;
    time_tmp[5] = tim_s;

    for (i = 0; i < 6; i++)
    {
        Buf_temp[1 + i] = time_tmp[5 - i];
    }

    DectoBCD(&Buf_temp[7], gz_disp, 2); // ����ֵ
    // gz_disp = 0;

    MODIFY_EEP_W((9 * point_event_trip), Buf_temp, 9, 0xA0); // ��ַ����

//    if (point_event_trip <= 9)
//    {
//        MODIFY_EEP_W((9 * point_event_trip), Buf_temp, 9, 0xA0);
//        // AT24C64_W(Buf_temp,(10*point_event_trip+10500),10);
//        // //			EEPROM_R(Buf_temp,(10*point_event_trip),10,1);
//    }

//    if (point_event_trip > 9)
//    {
//        MODIFY_EEP_W((9 * (point_event_trip - 10)), Buf_temp, 9, 0xA0);
//        // AT24C64_W(Buf_temp,(10*point_event_trip+11000),10);
//        // //			EEPROM_R(Buf_temp,(10*(point_event_trip-10)),10,2);
//    }
    point_event_trip = point_event_trip + 1;
    if (point_event_trip >= 20)
    {
        point_event_trip = 0x00;
    }
    E2_temp[0] = point_event_trip;
    // MODIFY_EEP_W(E2_temp,Addr_point_event_trip,1,0);

    MODIFY_EEP_W(Addr_point_event_trip, E2_temp, 1, 0xA0);

    EEPROM_R(Addr_point_event_trip, Buf_temp, 1, 0xA0); // 2017 6 10 �㽭�޸Ĺ�

    /*�����Ǽ�¼��24C256�еļ�¼*******************/
    if (F_norecord == 0)
    {
        Buf_temp[0] = gz_r; // ����ԭ��
        Buf_temp[1] = gz_p; // ������λ,�˴����޸�

        //		ds1302_read_time_uart(&Buf_temp[2]);  // [1][0]   ��[2]��ʼ��

        HAL_RTC_GetTime(&hrtc, &stimestructure, RTC_FORMAT_BCD);
        HAL_RTC_GetDate(&hrtc, &sdatestructure, RTC_FORMAT_BCD);
        tim_y = sdatestructure.Year; // tim_yΪʮ���ƣ�Ҫת��������
        tim_m = sdatestructure.Month;
        tim_d = sdatestructure.Date;
        tim_h = stimestructure.Hours;
        tim_f = stimestructure.Minutes;
        tim_s = stimestructure.Seconds;
        Buf_temp[2] = tim_y;
        Buf_temp[3] = tim_m;
        Buf_temp[4] = tim_d;
        Buf_temp[5] = tim_h;
        Buf_temp[6] = tim_f;
        Buf_temp[7] = tim_s;
        //	  tim_y=tim_y%2000;  //time_tmp[0]=17   ʮ����ת��Ϊ�����ƴ���24C64��
        //	  Buf_temp[2]=(tim_y/10)<<4;
        //	  Buf_temp[2]+=(tim_y%10);
        //	  Buf_temp[3]=(tim_m/10)<<4;
        //	  Buf_temp[3]+=(tim_m%10);
        //  	Buf_temp[4]=(tim_d/10)<<4;
        //  	Buf_temp[4]+=(tim_d%10);
        //  	Buf_temp[5]=(tim_h/10)<<4;
        //  	Buf_temp[5]+=(tim_h%10);
        //  	Buf_temp[6]=(tim_f/10)<<4;
        //  	Buf_temp[6]+=(tim_f%10);
        //  	Buf_temp[7]=(tim_s/10)<<4;
        //  	Buf_temp[7]+=(tim_s%10);

        copy_array(time_tmp, &Buf_temp[2], 6);
        for (i = 0; i < 6; i++)
        {
            Buf_temp[2 + i] = time_tmp[5 - i];
        }
        if (gz_r == 0x0B)
        {
            Leak_Cur_disp_record = 0;
            V_Array_record[0] = V_Array_record[1] = V_Array_record[2] = 0;
            I_Array_record[0] = I_Array_record[1] = I_Array_record[2] = 0;
        }
        DectoBCD(&Buf_temp[8], Leak_Cur_disp_record, 2); // ©��
        DectoBCD(&Buf_temp[10], ((vol_handle_A(V_Array_record[0])) * 10), 2);
        DectoBCD(&Buf_temp[12], ((vol_handle_B(V_Array_record[1])) * 10), 2);
        DectoBCD(&Buf_temp[14], ((vol_handle_C(V_Array_record[2])) * 10), 2);
        DectoBCD(&Buf_temp[16], ((cur_handle_A(I_Array_record[0])) * 10), 3);
        DectoBCD(&Buf_temp[19], ((cur_handle_B(I_Array_record[1])) * 10), 3);
        DectoBCD(&Buf_temp[22], ((cur_handle_C(I_Array_record[2])) * 10), 3);
        MODIFY_EEP_W((Addr_event_trip + 25 * point_event_trip_24C256), Buf_temp, 25, 0xA0);
        point_event_trip_24C256 = point_event_trip_24C256 + 1;
        if (point_event_trip_24C256 >= 10)
        {
            point_event_trip_24C256 = 0x00;
        }
        E2_temp[0] = point_event_trip_24C256;
        MODIFY_EEP_W(Addr_point_event_trip_24C256, E2_temp, 1, 0xA0);
    }
}

// �ⲿ�ж�0�������
// void EXTI0_IRQHandler(void)
//{
////	delay_ms(1);//����
//	EXTI_ClearITPendingBit(EXTI_Line0); //���LINE0�ϵ��жϱ�־λ
//	if(F_Vsam_begin==1)
//	{
////		Adc_Init();
////	  V_Array[0]=Get_Adc(ADC_Channel_7);
//		if(vol_handle_A(V_Array[0])>=79)
//		{
//			T = 0;
//			Leak_Cur_Sum=0;
//			A_C_Sum=0;
//			B_C_Sum=0;
//			C_C_Sum=0;
//			F_qingling=0;
//		}
//		else
//		{
//			F_qingling=1;
//		}
//	}
//	F_Sample = 1;
//	N_Tingdian = 0;
//}

void Flag_Updata(void)
{
		if(T_30s==1500) F_Harmonic_Content=1;
	
	
    if ((T == 7) && (T_64_1min == 2999))
    {
        F_sssj = 0;
        //			F_initial_lcd=1;
    }
    if ((T == 7) && (T_64_6 == 20)) // һ���򵥵��ϵ���ʱ
    {
        F_Delay = 1;
        F_L_Delay = 1;
    }

    //	if((T==9)&&(T_64_2min==2999))
    //		{
    //			F_sssj = 0;
    //		}
    /************ ��ʾ����*************/
    // ÿ��1000ms����һ����ʾ
    if ((T == 16) && (T_64_25 == 50))
    {
        F_Disp = 1;
				F_lcd_realtime=1;

				
    }
		
		if((T==16)&&(T_1min==3000))
		{
			F_lcd_transmit_D=1;
			F_bill = 1;
		}


		
    if ((T == 20) && (T_64_25 == 50))
    {
        F_HT7038_Read = 1; /// �����������������ʾͬ��
    }
    /************ ��ֵ�жϲ�����*************/
    // ÿ��40ms�ж�һ�ΰ���
    if ((T == 8) && (T_64_1 == 1))
    {
        F_Buttom = 1;
        //		F_initial_lcd=1;
    }
    /************ �����������ж�*************/

    if ((T == 35) && (T_64_4 == 4))
    {
        F_Vol = 10;
				F_anti_islanding = 1;
    }
    if ((T == 35) && (T_64_4_Re == 200)) // 2020/11/5
    {
        F_Vol_Re = 10;
    }
    if ((T == 39) && (T_64_500ms == 100))
    {
        F_Vsam_begin = 1;
    }
    if ((T == 40) && (T_64_200ms == 200) && (isfenzha != 0))
    {
        F_Leak_Delay = 1;
    }
    /*****************�¶Ȳɼ�*********************/
    if ((T == 41) && (T_T >= 10))
    {
        F_T = T_T / 10;
    }
    /*******************************************/
    /************ ����Ӧ������־*************/
    // 6000))//ÿ��120��������Ӧ��λ����
    if ((T == 4) && (T_64_2m == 60))
    {
        F_Compare = 1;
    }
    /************ 10s �ް���*************�޸�Ϊ6s*/
    // ÿ��10s�ް�������
    if ((T == 5) && (T_64_10s == 2500)) // ֮ǰ250����10s����©��澯�й�ϵ��
    {
        F_nokey = 1;
				//F_lcd_transmit_D=1;  //10s����һ�ε�λ��Ϣ
    }
    /************©���ѿۺ�20s��բ*********/
    if ((T == 6) && (T_64_xs == N_Trip_Array[N_Trip]))
    {
        // putchar(0xDD);
        // putchar(N_Trip);
        F_Trip = 2;
        T_64_xs = 0;
        F_L_hezha = 1;
    }
    /**********©���غ�բ��6s���쳣,ȡ������****/
    // �غ�բ��6s���쳣ȡ��������־
    if ((T == 7) && (T_64_6s == 300)) //
    {
        F_Trip = 0;
        N_Trip = 0;
        T_64_6s = 0;
			
    }
    // 20s ��բ
    if ((T == 9) && (T_64_31s == 1000))
    {
        F_I_STA = 2;
        T_64_31s = 0;
        F_I_hezha = 1;
    }

    if ((T == 10) && (T_64_11s == 45000))
    {
        T_64_11s = 0;
        F_I_STA = 0;
    }
    if ((T == 12) && (T_leak_record == Num_leak_record))
    {
        T_leak_record = 0;
        F_leak_record = 1;
    }
    if ((T == 13) && (T_day_updata == 250)) // 5min 15000  ���Ը�Ϊ1min 3000 �޸�Ϊ5s���һ�� 50
    {
        T_day_updata = 0;
        F_day_updata = 1;
    }
    if ((T == 14) && (T_run_time == 3000))
    {
        T_run_time = 0;
        F_run_time = 1;
    }

    if ((T == 15) && (T_yc_fenzha_js == T_yc_fenzha) && (F_fenzha_js == 1))
    {
        F_fenzha_js = 0;
        T_yc_fenzha_js = 0;
        if (isfenzha != 0)
        {
            F_yc_fenzha = 1;
        }
    }
    if ((T == 16) && (T_yc_hezha_js == T_yc_hezha) && (F_hezha_js == 1))
    {
        F_hezha_js = 0;
        T_yc_hezha_js = 0;
        if (isfenzha == 0)
        {
            F_yc_hezha = 1;
        }
    }
    if ((T == 17) && (T_an_fenzha_js == T_an_fenzha) && (F_an_js == 1))
    {
        F_an_js = 0;
        T_an_fenzha_js = 0;
        F_an_fenzha = 1;
    }

    if ((T == 18) && (T_set_state == 500))
    {
        F_set_state = 0;
        F_trip_ld = 0;
        F_clear_al = 1;
    }
    if ((T == 19) && (T_time_trip == 750)) // 15s����Ƿ�ʱ����
    {
        F_time_trip = 1;
    }
    //		if((T==20)&&(T_64_100ms==200)) //15s����Ƿ�ʱ����
    //	{
    //		F_hezha_set = 1;
    //	}
}

void Conter_Updata(void)
{
		
	
		T_30s++;
		if(T_30s>1501) T_30s=0;
	
    if (F_hezha_state == 1)
    {
        N_hezha_time++;
        if (N_hezha_time >= 6000) // ��ʱ��բʧ�ܣ�ֹͣ
        {
            stop;
            F_disp_jg = 0x55;
            N_hezha_time = 0;
            F_hezha_state = 0;
        }
    }
    if (F_hezha_delay == 1)
    {
        T_64_hezha_delay = T_64_hezha_delay + 1;
        if (T_64_hezha_delay >= 200)
        {
            // put2char(0x33);
            stop;
            T_64_hezha_delay = 0;
            F_hezha_delay = 0;
            F_initial_lcd = 1;
        }
    }
    if (F_fenzha_state == 1) // ��ʱ��բʧ�ܣ�ֹͣ
    {
        N_fenzha_time++;
        if (N_fenzha_time >= 6000)
        {
            stop;
            F_disp_tr = 1;
            N_fenzha_time = 0;
            F_fenzha_state = 0;

            fenzha_chenggong = 0x00;
            Write_Selftest_Record(0x0E);
        }
    }
    if (F_display == 0)
    {
        N_display_time++;
        if (N_display_time >= 30000)
        {
            F_display = 1;
            N_display_time = 0;
        }
    }
    if (F_display == 1) // ÿ��30*2*5*2��ˢ��mrnow
    {
        clear_screen();
        initial_lcd();
        F_display = 0;
    }
    if ((F_sssj == 0) || (F_key == 1))
    {
        T_64_1min = T_64_1min + 1; // 20MSһ��  20*150=300MS ̫��
        if (T_64_1min >= 3000)
            T_64_1min = 0;
    }
    T_64_2min = T_64_2min + 1; // 20MSһ��  20*150=300MS ̫��
    if (T_64_2min >= 1501)
        T_64_2min = 0;
    if (F_sssj == 0)
    {
        T_sssj_N = T_sssj_N + 1;
        if (T_sssj_N >= 150)
        {
            T_sssj_N = 0;
            sssj_N_xunhuan++;
            //			F_initial_lcd=0;
            if (sssj_N_xunhuan > 6) // �����¶���ʾ��3��Ϊ2
            {
                sssj_N_xunhuan = 1;
            }
        }
    }
    if (F_Vsam_begin == 0)
    {
        T_64_500ms = T_64_500ms + 1;
        if (T_64_500ms >= 101)
        {
            T_64_500ms = 0;
        }
    }
    ////wend

    if (F_T == 0)
    {
        T_T++;
        if (T_T >= 10)
            T_T = 0;
    }

    if ((F_Leak_Delay == 0) && (isfenzha != 0))
    {
        T_64_200ms = T_64_200ms + 1;
        if (T_64_200ms >= 201)
        {
            T_64_200ms = 0;
        }
    }
    //	if(F_shangdian_hezha==1)
    //	{
    //	T_64_100ms=T_64_100ms+1;
    //		if(T_64_100ms>=201) {T_64_100ms = 0;}
    //	}
    T_64_6 = T_64_6 + 1;
    if (T_64_6 == 30)
        T_64_6 = 0;

    T_64_1 = T_64_1 + 1;
    if (T_64_1 == 2)
        T_64_1 = 0;

    T_64_2 = T_64_2 + 1;
    if (T_64_2 == 3)
        T_64_2 = 0;

    T_64_3 = T_64_3 + 1;
    if (T_64_3 == 4)
        T_64_3 = 0;

    T_64_4 = T_64_4 + 1;
    if (T_64_4 >= 5)
        T_64_4 = 0; // 5T_64_4_Re

    T_64_4_Re = T_64_4_Re + 1;
    if (T_64_4_Re >= 201)
        T_64_4_Re = 0;
		
		T_1min = T_1min + 1;
		if (T_1min == 3001) T_1min=1;

    T_64_25 = T_64_25 + 1;
    if (T_64_25 == 51)
        T_64_25 = 0; // 1000ms

    if (T_64_15m == 45001)
        T_64_15m = 0;
    if (F_Updata == 0)
        T_64_20m = T_64_20m + 1;

    if (T_64_20m == 4001)
        T_64_20m = 0;
    T_64_2m = T_64_2m + 1;
    if (T_64_2m == 61)
        T_64_2m = 0;

    if (F_key == 1)
        T_64_10s = T_64_10s + 1;
		
    if (F_Trip == 1)
    {
        T_64_xs = T_64_xs + 1;
    }
    if (T_64_xs == N_Trip_Array[N_Trip] + 1)
        T_64_xs = 0;

    if ((F_Trip == 2) && (F_ZW == 1))
        T_64_6s = T_64_6s + 1;
    if (T_64_6s == 301)
        T_64_6s = 0;

    //		if(F_key==1)  T_64_6s=T_64_6s+1 ;
    //	  if(T_64_6s>=301)T_64_6s=0 ;

    if ((F_I_STA == 1) && (isfenzha == 0))
    {
        T_64_31s = T_64_31s + 1;
        if (T_64_31s >= 1501)
            T_64_31s = 0;
    }

    if ((F_I_STA == 2) && (isfenzha != 0))
    {
        T_64_11s = T_64_11s + 1;
        if (T_64_11s == 45001)
            T_64_11s = 0;
    }

    T_leak_record = T_leak_record + 1;
    T_day_updata = T_day_updata + 1;
    T_run_time = T_run_time + 1;

    if (F_fenzha_js == 1)
        T_yc_fenzha_js = T_yc_fenzha_js + 1;
    if (F_hezha_js == 1)
        T_yc_hezha_js = T_yc_hezha_js + 1;
    if (F_an_js == 1)
        T_an_fenzha_js = T_an_fenzha_js + 1;
    if (F_set_state == 1)
        T_set_state = T_set_state + 1;
    if (F_time_compare == 1)
        T_time_trip = T_time_trip + 1;
    if (F_gz_clear == 1)
    {
        if (isfenzha != 0)
        {
            F_gz_clear = 0;
            F_gz = 0x00;
        }
    }
    //			if(F_hezha_sta==1)
    //		{
    //			if(isfenzha!=0)
    //			{
    //
    //				stop ;
    //				hezha_num = 0;
    //				ci_shu = 0;
    //				F_ZW=1 ;
    //				F_gz=0x00 ;
    //				F_gz_disp = 0x0F;
    //				//F_disp_jg=0 ;
    //				//�������ϱ�־����
    //				//status=isfenzha ;
    //				F_disp_h=0 ;
    //				F_Dataval=0 ;
    //				F_guocheng = 0;
    //				F_hezha_sta = 0;
    //				F_Disp=1 ;
    //				back_button();
    //			}
    //		}
    T_delay = T_delay + 1;
    if (T_delay >= 200)
        T_delay = 200;
    //	      T_T++;
    //				if(T_T>=81) T_T=0;//T_Tÿ10ms��1����ʮ����100ms���ǰ˴Σ����˸��¶�
}

void Nomal_Process(void)
{

    IWDG_Feed();
    if (isfenzha != 0)
    {
        if (F_disp_jg != 0)
        {
            F_disp_jg = 0x00;
        }
    }
    if (F_trip_ld)
    {
        if (F_al1)
        {
            if (LouD_GaoJing < 10)
            {
                clear_screen();
                Lcd12864_Write16CnCHAR(0, 32, 0, "©��澯");
                LouD_GaoJing++;
            }
        }
        else
            LouD_GaoJing = 0;
    }
    if ((F_Disp == 1) && ((F_key == 0) || (F_key == 9)))
    {
        IWDG_Feed();
        F_Disp = 0;
        if (Leak_Cur_disp <= 15)
            Leak_Cur_disp = 0;
        L_Cur = Leak_Cur_disp;
        nomal_disp();
        // ��ѹ�쳣��ʾ��2023-8-4
        if ((vol_handle_A(V_Array[0]) >= 550) || (vol_handle_B(V_Array[1]) >= 550) || (vol_handle_C(V_Array[2]) >= 550) || (vol_handle_A(V_Array[0]) <= 10) || (vol_handle_B(V_Array[1]) <= 10) || (vol_handle_C(V_Array[2]) <= 10))
        {

            vol_abnormal_check();
        }
    }

    if (F_Buttom == 1)
    {
        //	HAL_GPIO_TogglePin(GPIOC, TRIP_Pin);//���԰����೤ʱ�䴦��һ��
        F_Buttom = 0;
        short_process();
        long_process();

        /*********�¶Ȳ���*******/
        //		for(uint8_t i=0;i<4;i++)
        //		{
        //			ADC_ConvertedValue[8+i]=get_adc(8+i);
        //		}
        //			HAL_ADC_Stop(&hadc1);
    }

    if (F_gz_disp != 0x0F)
    {
        // key_state=0x0000 ;
        F_key = 0;
    }
}

void Power_Process(void)
{
    //	printf("A=%d    B=%d    C=%d\r\n",Phase_Differ[0],Phase_Differ[1],Phase_Differ[2]);
    //	printf("*************************************\r\n");
    if ((Power_A_Value >= 8) && (Power_B_Value >= 8) && (Power_C_Value >= 8))
    {
        if (Samp_start_end_flag == 1) // 64��ɼ���־λ��λ1��������������ʼ������ж�
        {
            /*************************��������ë���˲�20210808***********************/
            for (int Poin_k = 0; Poin_k < 69; Poin_k++)
            {
                if (Zhou_bo_IA[Poin_k + 1] > 2 * Zhou_bo_IA[Poin_k]) // A����
                {
                    if (Zhou_bo_IA[Poin_k] == 0)
                    {
                        Zhou_bo_IA[Poin_k + 1] = Zhou_bo_IA[Poin_k + 1];
                    }
                    else
                    {
                        Zhou_bo_IA[Poin_k + 1] = Zhou_bo_IA[Poin_k];
                    }
                }
                else
                {
                    Zhou_bo_IA[Poin_k + 1] = Zhou_bo_IA[Poin_k + 1];
                }
                if (Zhou_bo_IB[Poin_k + 1] > 2 * Zhou_bo_IB[Poin_k]) // B����
                {
                    if (Zhou_bo_IB[Poin_k] == 0)
                    {
                        Zhou_bo_IB[Poin_k + 1] = Zhou_bo_IB[Poin_k + 1];
                    }
                    else
                    {
                        Zhou_bo_IB[Poin_k + 1] = Zhou_bo_IB[Poin_k];
                    }
                }
                else
                {
                    Zhou_bo_IB[Poin_k + 1] = Zhou_bo_IB[Poin_k + 1];
                }
                if (Zhou_bo_IC[Poin_k + 1] > 2 * Zhou_bo_IC[Poin_k]) // C����
                {
                    if (Zhou_bo_IC[Poin_k] == 0)
                    {
                        Zhou_bo_IC[Poin_k + 1] = Zhou_bo_IC[Poin_k + 1];
                    }
                    else
                    {
                        Zhou_bo_IC[Poin_k + 1] = Zhou_bo_IC[Poin_k];
                    }
                }
                else
                {
                    Zhou_bo_IC[Poin_k + 1] = Zhou_bo_IC[Poin_k + 1];
                }
            }
            /********************************************************************/
            for (Point_i = 0; Point_i < 70; Point_i++) // 200
            {
                if (Point_i <= 63)
                {
                    // �ڶ���  �ҵ�ѹ�����
                    if ((Zhou_bo_UA[Point_i] <= 0) && (Zhou_bo_UA[Point_i + 1] >= 0) && (Cross_Zero_A[0] == 0))
                    {
                        Re_dot_U[0] = Point_i + 1; // A��ѹ���
                        if (Point_i < 63)
                            Cross_Zero_A[0] = 1; // ��⵽�������λ70
                        else
                        {
                            Cross_Zero_A[0] = 0; // ��⵽�������0,�����жϹ����
                        }
                    }
                    if ((Zhou_bo_UB[Point_i] <= 0) && (Zhou_bo_UB[Point_i + 1] >= 0) && (Cross_Zero_B[0] == 0))
                    {
                        Re_dot_U[1] = Point_i + 1; // B��ѹ���
                        if (Point_i < 63)
                            Cross_Zero_B[0] = 1; // ��⵽�������λ
                        else
                        {
                            Cross_Zero_B[0] = 0; // ��⵽�������0,�����жϹ����
                        }
                    }
                    if ((Zhou_bo_UC[Point_i] <= 0) && (Zhou_bo_UC[Point_i + 1] >= 0) && (Cross_Zero_C[0] == 0))
                    {
                        Re_dot_U[2] = Point_i + 1; // C��ѹ���
                        if (Point_i < 63)
                            Cross_Zero_C[0] = 1; // ��⵽�������λ
                        else
                        {
                            Cross_Zero_C[0] = 0; // ��⵽�������0,�����жϹ����
                        }
                    }

                    /*************************������ ���������Ѱ��*********************/
                    if ((Zhou_bo_IA[Point_i] > Zhou_bo_IA[Point_i + 1]) && (Zhou_bo_IA[Point_i + 1] > Zhou_bo_IA[Point_i + 2]) && (Zhou_bo_IA[Point_i + 2] < Zhou_bo_IA[Point_i + 3]) && (Zhou_bo_IA[Point_i + 3] < Zhou_bo_IA[Point_i + 4]) && (Cross_Zero_A[1] == 0))
                    {
                        if (Zhou_bo_IA[Point_i + 2] < 20)
                        {
                            Re_dot_I[0] = Point_i + 2;
                            Cross_Zero_A[1] = 1;
                        }
                        else
                        {
                            Cross_Zero_A[1] = 0;
                        }
                    }
                    if ((Zhou_bo_IB[Point_i] > Zhou_bo_IB[Point_i + 1]) && (Zhou_bo_IB[Point_i + 1] > Zhou_bo_IB[Point_i + 2]) && (Zhou_bo_IB[Point_i + 2] < Zhou_bo_IB[Point_i + 3]) && (Zhou_bo_IB[Point_i + 3] < Zhou_bo_IB[Point_i + 4]) && (Cross_Zero_B[1] == 0))
                    {
                        if (Zhou_bo_IB[Point_i + 2] < 20)
                        {
                            Re_dot_I[1] = Point_i + 2;
                            Cross_Zero_B[1] = 1;
                        }
                        else
                        {
                            Cross_Zero_B[1] = 0;
                        }
                    }
                    if ((Zhou_bo_IC[Point_i] > Zhou_bo_IC[Point_i + 1]) && (Zhou_bo_IC[Point_i + 1] > Zhou_bo_IC[Point_i + 2]) && (Zhou_bo_IC[Point_i + 2] < Zhou_bo_IC[Point_i + 3]) && (Zhou_bo_IC[Point_i + 3] < Zhou_bo_IC[Point_i + 4]) && (Cross_Zero_C[1] == 0))
                    {
                        if (Zhou_bo_IC[Point_i + 2] < 20)
                        {
                            Re_dot_I[2] = Point_i + 2;
                            Cross_Zero_C[1] = 1;
                        }
                        else
                        {
                            Cross_Zero_C[1] = 0;
                        }
                    }
                }
            }

            /*	***********************���Ĳ� ������ѹ��λ��*************/
            if ((Cross_Zero_A[0] == 1) && (Cross_Zero_B[0] == 1) && (Cross_Zero_C[0] == 1) && (Cross_Zero_A[1] == 1) && (Cross_Zero_B[1] == 1) && (Cross_Zero_C[1] == 1))
            {
                for (int PH = 0; PH < 3; PH++)
                {
                    Phase_Differ[PH] = Re_dot_U[PH] - Re_dot_I[PH] - 5; // ��ѹ���������� /-5
                    if (Phase_Differ[PH] < 0)
                        Phase_Differ[PH] = -Phase_Differ[PH];
                    else
                        Phase_Differ[PH] = Phase_Differ[PH];
                    if (Phase_Differ[PH] <= 16) // 16
                    {
                        Phase_Differ[PH] = Phase_Differ[PH];
                        Cross_Zero[PH] = 1;
                    }
                    else
                    {
                        Cross_Zero[PH] = 0;
                        Phase_Differ[PH] = 0;
                    }
                }
                // ���岽 ͨ����λ����������ת������ֵ���������ӣ�Power_factor[PH]=
                // ����ֵ*1000 ��1000  995   981   957   924    882   831   773  707   634   556    471   383   290   195    98    0
                // ������      0    1     2     3     4      5     6     7    8     9     10    11    12    13    14    15    16
                // ���Ƕ�      0  5.625/11.25/16.875/22.5/28.125/33.75/39.375/45/50.625/56.25/61.875/67.5/73.125/78.75/84.375/90
                if ((Cross_Zero[0] == 1) && (Cross_Zero[1] == 1) && (Cross_Zero[2] == 1))
                {
                    //					HAL_UART_Transmit(&huart3,(uint8_t*)UART_S_Bu1f,4,0xffff);

                    Phase_Differ_buffer[0] += Phase_Differ[0];
                    Phase_Differ_buffer[1] += Phase_Differ[1];
                    Phase_Differ_buffer[2] += Phase_Differ[2];

                    Phase_Differ_A[Fun_Power] = Phase_Differ[0]; // ʵ��16����ֵ��Ϊȥ���쳣�����Ƚ��ṩ����
                    Phase_Differ_B[Fun_Power] = Phase_Differ[1]; // 20210815ȥ�쳣��
                    Phase_Differ_C[Fun_Power] = Phase_Differ[2];

                    Fun_Power++;
                    //					printf("A=%d B=%d C=%d\r\n",Phase_Differ[0],Phase_Differ[1],Phase_Differ[2]);
                    if (Fun_Power == 4) // 16
                    {
                        //						printf("*************************************\r\n");
                        Fun_Power = 0;
                        Phase_Differ_average[0] = ((Phase_Differ_buffer[0] / 4)) * 10; // 16�ܲ�ȡƽ��ֵ
                        Phase_Differ_average[1] = ((Phase_Differ_buffer[1] / 4)) * 10;
                        Phase_Differ_average[2] = ((Phase_Differ_buffer[2] / 4)) * 10;

                        //						printf("AV1=%d   BV1=%d   CV1=%d\r\n",Phase_Differ_average[0],Phase_Differ_average[1],Phase_Differ_average[2]);

                        /**********************ƽ��ֵ��16�����Ƚ�ȥ�쳣��****************/
                        for (int YiChang = 0; YiChang < 4; YiChang++) // 16  20210824�޸�
                        {
                            Phase_Differ_A_one[YiChang] = Phase_Differ_average[0] - Phase_Differ_A[YiChang] * 10;
                            Phase_Differ_B_one[YiChang] = Phase_Differ_average[1] - Phase_Differ_B[YiChang] * 10;
                            Phase_Differ_C_one[YiChang] = Phase_Differ_average[2] - Phase_Differ_C[YiChang] * 10;
                            /********************************************************************/
                            if ((Phase_Differ_A_one[YiChang] < -20) || (Phase_Differ_A_one[YiChang] > 20)) // A��
                            {
                                Phase_Differ_A_one[YiChang] = 0;
                                Phase_Differ_A[YiChang] = 0;
                            }
                            else
                            {
                                Phase_Differ_A_Two += Phase_Differ_A[YiChang];
                                Phase_Differ_A[YiChang] = 0;
                                Phase_Differ_A_one[YiChang] = 0;
                                YiChang_A_Flag++;
                            }
                            /**************************************************************************/
                            if ((Phase_Differ_B_one[YiChang] < -20) || (Phase_Differ_B_one[YiChang] > 20)) // B��
                            {
                                Phase_Differ_B_one[YiChang] = 0;
                                Phase_Differ_B[YiChang] = 0;
                            }
                            else
                            {
                                Phase_Differ_B_Two += Phase_Differ_B[YiChang];
                                Phase_Differ_B[YiChang] = 0;
                                Phase_Differ_B_one[YiChang] = 0;
                                YiChang_B_Flag++;
                            }
                            /**************************************************************************/
                            if ((Phase_Differ_C_one[YiChang] < -20) || (Phase_Differ_C_one[YiChang] > 20)) // C��
                            {
                                Phase_Differ_C_one[YiChang] = 0;
                                Phase_Differ_C[YiChang] = 0;
                            }
                            else
                            {
                                Phase_Differ_C_Two += Phase_Differ_C[YiChang];
                                Phase_Differ_C[YiChang] = 0;
                                Phase_Differ_C_one[YiChang] = 0;
                                YiChang_C_Flag++;
                            }
                        }
                        /******************��ȥ���쳣���ƽ��ֵ*******************/
                        Phase_Differ_A_Two_Av = (Phase_Differ_A_Two / YiChang_A_Flag) * 10 + 5;
                        Phase_Differ_B_Two_Av = (Phase_Differ_B_Two / YiChang_B_Flag) * 10 + 5;
                        Phase_Differ_C_Two_Av = (Phase_Differ_C_Two / YiChang_C_Flag) * 10 + 5;

                        //						printf("av2=%d   bv2=%d   cv2=%d\r\n",Phase_Differ_A_Two_Av,Phase_Differ_B_Two_Av,Phase_Differ_C_Two_Av);
                        //						printf("*************************************\r\n");

                        Phase_Differ_A_Two = 0;
                        Phase_Differ_B_Two = 0;
                        Phase_Differ_C_Two = 0;

                        YiChang_A_Flag = 0;
                        YiChang_B_Flag = 0;
                        YiChang_C_Flag = 0;

                        //						Phase_Differ_average[0]=((Phase_Differ_buffer[0]/16))*10-(Power_Add[0]);
                        //						Phase_Differ_average[1]=((Phase_Differ_buffer[1]/16))*10-(Power_Add[1]);
                        //						Phase_Differ_average[2]=((Phase_Differ_buffer[2]/16))*10-(Power_Add[2]);

                        Power_factor[0] = Power_pool[Phase_Differ_A_Two_Av];
                        Power_factor[1] = Power_pool[Phase_Differ_B_Two_Av];
                        Power_factor[2] = Power_pool[Phase_Differ_C_Two_Av];
                        //						Power_factor[0]=Power_pool[Phase_Differ_average[0]];
                        //						Power_factor[1]=Power_pool[Phase_Differ_average[1]];
                        //						Power_factor[2]=Power_pool[Phase_Differ_average[2]];

                        Phase_Differ_buffer[0] = 0;
                        Phase_Differ_buffer[1] = 0;
                        Phase_Differ_buffer[2] = 0;
                    }
                    //					Power_factor_test[0]+=Power_factor[0];//���Լ���20210807
                    //					Power_factor_test[1]+=Power_factor[1];
                    //					Power_factor_test[2]+=Power_factor[2];

                    //						Power_factor_testA[Fun_Power_test]=Power_factor[0];
                    //						Power_factor_testB[Fun_Power_test]=Power_factor[1];
                    //						Power_factor_testC[Fun_Power_test]=Power_factor[2];

                    //					Fun_Power_test++;
                    //					if(Fun_Power_test==1)//4
                    //					{
                    //						Fun_Power_test=0;

                    //						Power_factor_test_Ave[0]=(Power_factor_testA[0]+Power_factor_testA[1]+Power_factor_testA[2]+Power_factor_testA[3]);
                    //						Power_factor_test_Ave[1]=(Power_factor_testB[0]+Power_factor_testB[1]+Power_factor_testB[2]+Power_factor_testB[3]);
                    //						Power_factor_test_Ave[2]=(Power_factor_testC[0]+Power_factor_testC[1]+Power_factor_testC[2]+Power_factor_testC[3]);
                    //
                    //					}
                }
            }
            Cross_Zero[0] = 0;
            Cross_Zero[1] = 0;
            Cross_Zero[2] = 0;

            Cross_Zero_A[0] = 0;
            Cross_Zero_B[0] = 0;
            Cross_Zero_C[0] = 0;

            Cross_Zero_A[1] = 0;
            Cross_Zero_B[1] = 0;
            Cross_Zero_C[1] = 0;

            Re_dot_I[0] = 0;
            Re_dot_I[1] = 0;
            Re_dot_I[2] = 0;

            Re_dot_U[0] = 0;
            Re_dot_U[1] = 0;
            Re_dot_U[2] = 0;

            Phase_Differ[0] = 0;
            Phase_Differ[1] = 0;
            Phase_Differ[2] = 0;
        }
        Samp_start_end_flag = 0; // 200�������־λ���㣬��ʼ����
    }
    else
    {
        Power_factor[0] = 0;
        Power_factor[1] = 0;
        Power_factor[2] = 0;

        //		Power_factor_test_Ave[0]=0;
        //		Power_factor_test_Ave[1]=0;
        //		Power_factor_test_Ave[2]=0;
    }
}

void short_process(void)
{
    unsigned char tmp;
    IWDG_Feed();
    tmp = Read_key();
    //	F_sssj=1;
    if (tmp != 0)
    {
        key_process(tmp);

        if (F_key == 2)
        {

            Fun_Record_CX();
        }
        if (F_key == 3)
        {

            if (key_state == 0x42100)
                Trip_Num_LOCK();
            if (key_state == 0x42101)
                Trip_Num_LD();
            if (key_state == 0x42102)
                Trip_Num_DY();
            if (key_state == 0x42103)
                Trip_Num_TEST();
            if (key_state == 0x42104)
                Trip_Num_Instant();
            if (key_state == 0x42105)
                Trip_Num_Check();
        }

        if (F_key == 4)
        {
            Fun_Shiyan_CX();
        }

        if (F_key == 5)
        {
            if (D_LCur == 8)
                F_auto_ld = 1;
            else
                F_auto_ld = 0;
            if (key_state == 0x11100)
                Fun_GJ(); // ©��澯
            //			if (key_state==0x11101)
            //		   Fun_auto_LD();           //�Զ���λ
            if (key_state == 0x11102)
                Fun_SC(); // ͻ�䱣��
            if (key_state == 0x11103)
                Fun_SW(); // �ز�����
            if (key_state == 0x11104)
                // Fun_SD_hezha();          //�ϵ��բ
                Fun_DZ();
            if (key_state == 0x11105)
                Fun_GY(); // ��ѹ����
            if (key_state == 0x11106)
                Fun_QY(); // Ƿѹ����
            if (key_state == 0x11107)
                Fun_QX(); // ȱ�ౣ��
            if (key_state == 0x11108)
                Fun_SY(); // ʧѹ����
            if (key_state == 0x11109)
                Fun_OP(); // ��������
            if (key_state == 0x1110A)
                Fun_S_Delay(); // ���ӱ���
            if (key_state == 0x1110B)
                Fun_Instant(); // ˲ʱ����
            if (key_state == 0x1110C)
                //			 Fun_Corr_Slec(); 			//У׼����
                Fun_SD_hezha(); // �ϵ��բ
            //			if (key_state==0x1110E)
            //			 Fun_DZ();                //���㱣��
            if (key_state == 0x1110D)
                Fun_LD_hezha();
            if (key_state == 0x1110E)
                Fun_DY_hezha();
            if (key_state == 0x1110F)
                Fun_DL_hezha();
            if (key_state == 0x11110)
                Fun_Corr_Slec();
            if (key_state == 0x11111)
                Fun_TX_switch();
            //			if (key_state==0x1110D)
            //			 Fun_TD_fenzha();         //ͣ����բ
            //			if (key_state==0x1110E)
            //			 Fun_DZ();                //���㱣��
        }

        if (F_key == 6)
        {
            clear_screen();
            mima_input();
        }

        if (F_key == 7)
        {

            if ((key_state >= 0x21100) && (key_state <= 0x211FF))
                Fun_FZ();
            if ((key_state >= 0x22100) && (key_state <= 0x221FF))
                Fun_YS();
            if ((key_state >= 0x23100) && (key_state <= 0x231FF))
                Fun_GY_Val();
            if ((key_state >= 0x24100) && (key_state <= 0x241FF))
                Fun_QY_Val();
            if ((key_state >= 0x3D100) && (key_state <= 0x3D1FF))
                Fun_ST(); // ʧѹʱ�� ����
            if ((key_state >= 0x3E100) && (key_state <= 0x3E1FF))
                Fun_GT(); // ��ѹʱ�� ����
            if ((key_state >= 0x3F100) && (key_state <= 0x3F1FF))
                Fun_QT(); // Ƿѹʱ�� ����
            if ((key_state >= 0x40100) && (key_state <= 0x401FF))
                Fun_Instant_Val(); // ����˲ʱ������λ ����
            if ((key_state >= 0x25100) && (key_state <= 0x251FF))
                Fun_OP_Val(); // ������λ
            if ((key_state >= 0x26100) && (key_state <= 0x261FF))
                Fun_OP_T(); // ����ʱ��
            if ((key_state >= 0x27100) && (key_state <= 0x271FF))
                Fun_Delay_Val(); // ���ӵ�λ
            if ((key_state >= 0x28100) && (key_state <= 0x281FF))
                Fun_Delay_T(); // ����ʱ��
            if ((key_state >= 0x29100) && (key_state <= 0x291FF))
                Fun_Com_S(); // ͨ������
            if ((key_state >= 0x2A100) && (key_state <= 0x2A1FF))
                Fun_Type_Cur(); // �Ǽ�����
            if ((key_state >= 0x2B100) && (key_state <= 0x2B1FF))
                Fun_Time_Y(); // ʱ�� �� ����
            if ((key_state >= 0x2C100) && (key_state <= 0x2C1FF))
                Fun_Time_M(); // ʱ�� �� ����
            if ((key_state >= 0x2D101) && (key_state <= 0x2D1FF))
                Fun_Time_D(); // ʱ�� �� ����
            if ((key_state >= 0x2E100) && (key_state <= 0x2E1FF))
                Fun_Time_H(); // ʱ�� ʱ ����
            if ((key_state >= 0x2F100) && (key_state <= 0x2F1FF))
                Fun_Time_F(); // ʱ�� �� ����
            if ((key_state >= 0x30100) && (key_state <= 0x301FF))
                Fun_Time_S(); // ʱ�� �� ����
            if ((key_state >= 0x31100) && (key_state <= 0x311FF))
                Fun_Com_D_1(); // ��ַ ��1λ ����
            if ((key_state >= 0x32100) && (key_state <= 0x321FF))
                Fun_Com_D_2(); // ��ַ ��2λ ����
            if ((key_state >= 0x33100) && (key_state <= 0x331FF))
                Fun_Com_D_3(); // ��ַ ��3λ ����
            if ((key_state >= 0x34100) && (key_state <= 0x341FF))
                Fun_Com_D_4(); // ��ַ ��4λ ����
            if ((key_state >= 0x35100) && (key_state <= 0x351FF))
                Fun_Com_D_5(); // ��ַ ��5λ ����
            if ((key_state >= 0x36100) && (key_state <= 0x361FF))
                Fun_Com_D_6(); // ��ַ ��6λ ����
            if ((key_state >= 0x37100) && (key_state <= 0x371FF))
                Fun_Com_D_7(); // ��ַ ��7λ ����
            if ((key_state >= 0x38100) && (key_state <= 0x381FF))
                Fun_Com_D_8(); // ��ַ ��8λ ����
            if ((key_state >= 0x39100) && (key_state <= 0x391FF))
                Fun_Com_D_9(); // ��ַ ��9λ ����
            if ((key_state >= 0x3A100) && (key_state <= 0x3A1FF))
                Fun_Com_D_10(); // ��ַ ��10λ ����
            if ((key_state >= 0x3B100) && (key_state <= 0x3B1FF))
                Fun_Com_D_11(); // ��ַ ��11λ ����
            if ((key_state >= 0x3C100) && (key_state <= 0x3C1FF))
                Fun_Com_D_12(); // ��ַ ��12λ ����
            if ((key_state >= 0x50100) && (key_state <= 0x501FF))
                Temperature_UP(); // �¶�����
            if ((key_state >= 0x51100) && (key_state <= 0x511FF))
                Temperature_DOWN(); // �¶�����

            if (key_state >= 0x20000000)
            {
                if (key_state == 0x20000000)
                {
                    key_state = (unsigned int)(((key_state >> 12) | (mima[0])) << 12);
                    key_state = (unsigned int)(((key_state >> 8) | (mima[1])) << 8);
                    key_state = (unsigned int)(((key_state >> 4) | (mima[2])) << 4);
                    key_state = (unsigned int)(key_state) | (mima[3]);
                }

                mima_change();
            }
        }

        if (F_key == 8)
        {
            data_clear();
            clear_screen();
            Lcd12864_Write16CnCHAR(0, 16, 2, "�����������");
            HAL_Delay(1000);
            F_key = 0;
        }
    }
}

unsigned char fenzha(void)
{
    if (isfenzha != 0)
    {
        start;
        F_disp_tr = 0;
        F_fenzha_state = 1;
        N_fenzha_time = 0;
        //		F_initial_lcd_hezha=1;
    }
    return 0;
}

/* ��բ�������,��բʱ��ԼΪ120s,ͣ��ʱ��Ϊ10s, ����3��,
��բ�ɹ�����1,��բ���ɹ�����0                         */
unsigned char hezha(void)
{
    if (isfenzha == 0)
    {
        start;
        F_hezha_state = 1;
        N_hezha_time = 0;
        //		F_initial_lcd_hezha=1;
    }
    return 0;
}

void V_max_process(unsigned char tmp)
{
    if (tmp >= 4)
        tmp = 1;
    if (V_MAX_tmp[tmp - 1] > V_MAX[tmp - 1])
    {
        V_MAX[tmp - 1] = V_MAX_tmp[tmp - 1];
        Write_V(tmp, V_MAX[tmp - 1], 0);
        Record_V(tmp, V_MAX[tmp - 1], 0);
    }
}

void V_min_process(unsigned char tmp)
{
    if (tmp >= 4)
        tmp = 1;
    if (V_MIN_tmp[tmp - 1] < V_MIN[tmp - 1])
    {
        V_MIN[tmp - 1] = V_MIN_tmp[tmp - 1];
        Write_V(tmp, V_MIN[tmp - 1], 1);
        Record_V(tmp, V_MIN[tmp - 1], 1);
    }
}

void Write_V(unsigned char tmp, unsigned int factor1, unsigned char factor2)
{
    unsigned char day, array_temp_V[15], array_temp_time[10], i, day_tmp;
    unsigned int addr_tmp;

    //	ds1302_read_time_uart(array_temp_time);

    HAL_RTC_GetTime(&hrtc, &stimestructure, RTC_FORMAT_BCD);
    HAL_RTC_GetDate(&hrtc, &sdatestructure, RTC_FORMAT_BCD);
    tim_y = sdatestructure.Year; // tim_yΪʮ���ƣ�Ҫת��������
    tim_m = sdatestructure.Month;
    tim_d = sdatestructure.Date;
    tim_h = stimestructure.Hours;
    tim_f = stimestructure.Minutes;
    tim_s = stimestructure.Seconds;
    array_temp_time[0] = tim_y;

    array_temp_time[1] = tim_m;

    array_temp_time[2] = tim_d;

    array_temp_time[3] = tim_h;

    array_temp_time[4] = tim_f;

    array_temp_time[5] = tim_s;

    day_tmp = array_temp_time[2];
    day = (((day_tmp >> 4) & 0x03) * 10) + (day_tmp & 0x0F);
    day = day - 1;
    if ((day >= 0) && (day < 32))
    {
        if (factor2 == 0)
        {
            if (tmp == 1)
                addr_tmp = Addr_max_Avol + (day << 3);
            else if (tmp == 2)
                addr_tmp = Addr_max_Bvol + (day << 3);
            else if (tmp == 3)
                addr_tmp = Addr_max_Cvol + (day << 3);
            else
                addr_tmp = Addr_max_Avol + (day << 3);
        }
        if (factor2 == 1)
        {
            if (tmp == 1)
                addr_tmp = Addr_min_Avol + (day << 3);
            else if (tmp == 2)
                addr_tmp = Addr_min_Bvol + (day << 3);
            else if (tmp == 3)
                addr_tmp = Addr_min_Cvol + (day << 3);
            else
                addr_tmp = Addr_min_Avol + (day << 3);
        }
        DectoBCD(array_temp_V, (vol_handle(factor1) * 10), 2);
        for (i = 0; i < 6; i++)
        {
            array_temp_V[2 + i] = array_temp_time[5 - i];
        }
        MODIFY_EEP_W(addr_tmp, array_temp_V, 8, 0xA0);
    }
}
void Record_V(unsigned char tmp, unsigned int factor1, unsigned char factor2)
{
    unsigned char array_temp_V[15], i, array_temp_time[10];
    unsigned int addr_tmp;
    HAL_RTC_GetTime(&hrtc, &stimestructure, RTC_FORMAT_BCD);
    HAL_RTC_GetDate(&hrtc, &sdatestructure, RTC_FORMAT_BCD);

    tim_m = sdatestructure.Month;
    tim_d = sdatestructure.Date;

    array_temp_time[1] = tim_m;
    array_temp_time[2] = tim_d;
    if (factor2 == 0)
    {
        if (tmp == 1)
            addr_tmp = Addr_max_Avol_TD;
        else if (tmp == 2)
            addr_tmp = Addr_max_Bvol_TD;
        else if (tmp == 3)
            addr_tmp = Addr_max_Cvol_TD;
        else
            addr_tmp = Addr_max_Avol_TD;
    }
    if (factor2 == 1)
    {
        if (tmp == 1)
            addr_tmp = Addr_min_Avol_TD;
        else if (tmp == 2)
            addr_tmp = Addr_min_Bvol_TD;
        else if (tmp == 3)
            addr_tmp = Addr_min_Cvol_TD;
        else
            addr_tmp = Addr_min_Avol_TD;
    }
    DectoBCD(array_temp_V, factor1, 2);
    for (i = 0; i < 2; i++)
    {
        array_temp_V[2 + i] = array_temp_time[2 - i];
    }
    MODIFY_EEP_W(addr_tmp, array_temp_V, 4, 0xA0);
}

void Write_leak(unsigned int factor1, unsigned char factor2)
{
    unsigned char day, array_temp_L[15], array_temp_time[10], i, day_tmp;
    unsigned int addr_tmp;
    //	ds1302_read_time_uart(array_temp_time);
    HAL_RTC_GetTime(&hrtc, &stimestructure, RTC_FORMAT_BCD);
    HAL_RTC_GetDate(&hrtc, &sdatestructure, RTC_FORMAT_BCD);
    tim_y = sdatestructure.Year; // tim_yΪʮ���ƣ�Ҫת��������
    tim_m = sdatestructure.Month;
    tim_d = sdatestructure.Date;
    tim_h = stimestructure.Hours;
    tim_f = stimestructure.Minutes;
    tim_s = stimestructure.Seconds;
    array_temp_time[0] = tim_y;

    array_temp_time[1] = tim_m;

    array_temp_time[2] = tim_d;

    array_temp_time[3] = tim_h;

    array_temp_time[4] = tim_f;

    array_temp_time[5] = tim_s;
    day_tmp = array_temp_time[2];
    day = (((day_tmp >> 4) & 0x03) * 10) + (day_tmp & 0x0F);
    day = day - 1;
    if ((day >= 0) && (day < 32))
    {
        if (factor2 == 0)
        {
            addr_tmp = Addr_max_leak + day * 9;
        }
        if (factor2 == 1)
        {
            addr_tmp = Addr_min_leak + day * 9;
        }

        array_temp_L[0] = max_phase;
        DectoBCD(&array_temp_L[1], factor1, 2);
        for (i = 0; i < 6; i++)
        {
            array_temp_L[3 + i] = array_temp_time[5 - i];
        }
        MODIFY_EEP_W(addr_tmp, array_temp_L, 9, 0xA0);
    }
}

void Leak_max_process(void)
{
    if (Leak_MAX_tmp > Leak_MAX + 1)
    {
        Leak_MAX = Leak_MAX_tmp;
        Write_leak(Leak_MAX, 0);
    }
}

void Leak_min_process(void)
{
    if (Leak_MIN_tmp < Leak_MIN)
    {
        Leak_MIN = Leak_MIN_tmp;
        Write_leak(Leak_MIN, 1);
    }
}

void I_max_process(unsigned char tmp)
{
    if (tmp >= 4)
        tmp = 1;
    if (I_MAX_tmp[tmp - 1] > I_MAX[tmp - 1])
    {
        I_MAX[tmp - 1] = I_MAX_tmp[tmp - 1];
        Write_I(tmp, I_MAX[tmp - 1], 0);
    }
}

void I_min_process(unsigned char tmp)
{
    if (tmp >= 4)
        tmp = 1;
    if (I_MIN_tmp[tmp - 1] < I_MIN[tmp - 1])
    {
        I_MIN[tmp - 1] = I_MIN_tmp[tmp - 1];
        Write_I(tmp, I_MIN[tmp - 1], 1);
    }
}

void Write_I(unsigned char tmp, unsigned int factor1, unsigned char factor2)
{
    unsigned char day, array_temp_I[20], array_temp_time[10], i, day_tmp;
    unsigned int addr_tmp;
    HAL_RTC_GetTime(&hrtc, &stimestructure, RTC_FORMAT_BCD);
    HAL_RTC_GetDate(&hrtc, &sdatestructure, RTC_FORMAT_BCD);
    tim_y = sdatestructure.Year; // tim_yΪʮ���ƣ�Ҫת��������
    tim_m = sdatestructure.Month;
    tim_d = sdatestructure.Date;
    tim_h = stimestructure.Hours;
    tim_f = stimestructure.Minutes;
    tim_s = stimestructure.Seconds;
    array_temp_time[0] = tim_y;

    array_temp_time[1] = tim_m;

    array_temp_time[2] = tim_d;

    array_temp_time[3] = tim_h;

    array_temp_time[4] = tim_f;

    array_temp_time[5] = tim_s;
    day_tmp = array_temp_time[2];
    day = (((day_tmp >> 4) & 0x03) * 10) + (day_tmp & 0x0F);
    day = day - 1;
    if ((day >= 0) && (day < 32))
    {
        if (factor2 == 0)
        {
            if (tmp == 1)
                addr_tmp = Addr_max_Acur + day * 9;
            else if (tmp == 2)
                addr_tmp = Addr_max_Bcur + day * 9;
            else if (tmp == 3)
                addr_tmp = Addr_max_Ccur + day * 9;
            else
                addr_tmp = Addr_max_Acur + (day * 9);
        }
        if (factor2 == 1)
        {
            if (tmp == 1)
                addr_tmp = Addr_min_Acur + (day * 9);
            else if (tmp == 2)
                addr_tmp = Addr_min_Bcur + (day * 9);
            else if (tmp == 3)
                addr_tmp = Addr_min_Ccur + (day * 9);
            else
                addr_tmp = Addr_min_Acur + (day * 9);
        }
        if (tmp == 1)
        {
            DectoBCD(array_temp_I, (cur_handle_A(factor1) * 10), 3); // �˴�ʲô��˼������������
        }
        if (tmp == 2)
        {
            DectoBCD(array_temp_I, (cur_handle_B(factor1) * 10), 3); // �˴�ʲô��˼������������
        }
        if (tmp == 3)
        {
            DectoBCD(array_temp_I, (cur_handle_C(factor1) * 10), 3); // �˴�ʲô��˼������������
        }

        for (i = 0; i < 6; i++)
        {
            array_temp_I[3 + i] = array_temp_time[5 - i];
        }
        MODIFY_EEP_W(addr_tmp, array_temp_I, 9, 0xA0);
        //		delay_ms(5);
        //		  for(int i;i<15;i++)
        //		{
        //			EEPROM_R(addr_tmp,buff_tap,9,0xA0);
        //		  test_shuju[i]=buff_tap[i];
        //		}
    }
}
void hezha_process(void)
{
    IWDG_Feed(); // ι��

    // �ϵ��բ
    if (F_shangdian_hezha == 1)
    {
        // putchar(0xAE);
        if (F_Vsam_begin == 1)
        {
            delay_ms(500);
            //		delay_ms(500);
            //		delay_ms(500);
            //	  delay_ms(500);
            F_sssj = 0;
            if (F_tim_gz == 1)
            {
                F_gz = 0x0B; // ͣ�����
            }
            c_hezha();
            F_shangdian_hezha = 0;
            F_Leak_Delay = 0;
        }
    }
    // ȱ���բ
    if ((F_QX_hezha == 1) && (DY_hezha == 1))
    {
        F_wait_DY_Normal = 0;
        F_qxTrip = 0;
        F_QX_hezha = 0;
        F_TB_start = 0;
        F_sssj = 0;

        if (isfenzha == 0)
        {
            delay_ms(5);
            if (isfenzha == 0)
            {
                delay_ms(5);
                if (isfenzha == 0)
                {
                    hezha();
                    //			  F_QX_hezha=0 ;
                }
            }
        }
        F_Leak_Delay = 0;
    }
    // Ƿѹ��բ
    if ((F_QY_hezha == 1) && (DY_hezha == 1))
    {
        F_wait_DY_Normal = 0;
        F_qyTrip = 0;
        F_QY_hezha = 0;
        F_TB_start = 0;
        F_sssj = 0;
        if (isfenzha == 0)
        {
            delay_ms(5);
            if (isfenzha == 0)
            {
                delay_ms(5);
                if (isfenzha == 0)
                {
                    hezha();
                    //			  F_QY_hezha=0 ;
                }
            }
        }
    }
    // ʧѹ��բ
    if ((F_SY_hezha == 1) && (DY_hezha == 1))
    {
        F_wait_DY_Normal = 0;
        F_syTrip = 0;
        F_SY_hezha = 0;
        F_TB_start = 0;
        F_sssj = 0;
        if (isfenzha == 0)
        {
            delay_ms(5);
            if (isfenzha == 0)
            {
                delay_ms(5);
                if (isfenzha == 0)
                {
                    hezha();
                    //			  F_SY_hezha=0 ;
                }
            }
        }
        F_Leak_Delay = 0;
    }
    // ��ѹ��բ
    if ((F_GY_hezha == 1) && (DY_hezha == 1))
    {
        F_wait_DY_Normal = 0;
        F_gyTrip = 0;
        F_GY_hezha = 0;
        F_TB_start = 0;
        F_sssj = 0;
        if (isfenzha == 0)
        {
            delay_ms(5);
            if (isfenzha == 0)
            {
                delay_ms(5);
                if (isfenzha == 0)
                {
                    hezha();
                    //			  F_GY_hezha=0 ;
                }
            }
        }
        F_Leak_Delay = 0;
    }
    if (F_QL_hezha == 1)
    {
        F_wait_DY_Normal = 0;
        //		F_tingdian_fenzha=0;
        F_lzTrip = 0;
        F_QL_hezha = 0;
        F_TB_start = 0;
        F_sssj = 0;
        if (isfenzha == 0)
        {
            delay_ms(5);
            if (isfenzha == 0)
            {
                delay_ms(5);
                if (isfenzha == 0)
                {
                    hezha();
                    //			  F_QL_hezha=0 ;
                }
            }
        }
        F_Leak_Delay = 0;
    }
    // Զ�̺�բ
    if (F_yc_hezha == 1)
    {
        F_wait_DY_Normal = 0;
        F_yc_fenzha = 0;
        F_yc_hezha = 0;
        // clear_uart_sta();
        F_Dataval = 0;
        F_sssj = 0;
        if (isfenzha == 0)
        {
            delay_ms(5);
            if (isfenzha == 0)
            {
                delay_ms(5);
                if (isfenzha == 0)
                {
                    c_hezha();
                    //			  F_yc_hezha=0 ;
                }
            }
        }
        //		c_hezha();
    }
    // ����״̬,��ť��բ
    if (F_hz == 1)
    {
        F_wait_DY_Normal = 0;
        delay_ms(5);
        if ((F_hz == 1) && (isfenzha == 0))
        {
            //			if(isfenzha==0)
            {
                //				delay_ms(2);
                //				if(isfenzha==0)
                {
                    c_hezha();
                }
            }
            //			c_hezha();
            F_Leak_Delay = 0;
            // hezha();
            F_hz = 0;
        }
    }
    // ©�紦���е��غ�բ
    if ((F_L_hezha == 1) && (LD_hezha == 1))
    {
        F_wait_DY_Normal = 0;
        F_L_hezha = 0;
        if ((isfenzha == 0) && (F_L_Lock == 0))
        {
            F_TB_start = 0;
            F_sssj = 0;
            hezha();
            F_Leak_Delay = 0;
        }
    }
    if (F_wait_DY_Normal == 2)
    {
        delay_ms(5);
        if (isfenzha == 0)
        {
            F_wait_DY_Normal = 0;
            F_tingdian_fenzha = 0;
            c_hezha();
            F_Leak_Delay = 0;
            // hezha();//������ע���޸Ļ�ȥ20150510
            F_hz = 0;
        }
    }
    // �����������е��غ�բ
    if ((F_I_hezha == 1) && (DL_hezha == 1))
    {
        F_wait_DY_Normal = 0;
        // �ڷ�բ�Ҳ�������������غ�բ
        F_I_hezha = 0;
        F_sssj = 0;
        // if((isfenzha==0)&&(F_I_Lock==0))
        {
            F_TB_start = 0;
            hezha();
            F_I_hezha = 0;
            T_64_31s = 0;
        }
    }
		//���µ���ѹ�����е��غ�բ
		if (F_anti_islanding_hezha)
		{
			  F_wait_DY_Normal = 0;
        F_anti_islanding_trip = 0;
        F_anti_islanding_hezha = 0;
        if (isfenzha == 0)
        {
            delay_ms(5);
            if (isfenzha == 0)
            {
                delay_ms(5);
                if (isfenzha == 0)
                {
                    hezha();
                }
            }
        }
		}

    /*********�¶Ⱥ�բ******************/

//    if (F_tem_hezha == 1)
//    {

//        F_temTrip = 0;
//        F_tem_hezha = 0;
//        F_TB_start = 0;
//        F_sssj = 0;
//        if (isfenzha == 0)
//        {
//            delay_ms(5);
//            if (isfenzha == 0)
//            {
//                delay_ms(5);
//                if (isfenzha == 0)
//                {
//                    hezha();
//                }
//            }
//        }
//    }
}
void fenzha_process(void)
{
    //
    //	if(F_tingdian_fenzha==1)
    //	{
    //		F_tingdian_fenzha = 0;
    //		if(isfenzha!=0)
    //		{
    //			Trip_Action();
    //		}
    //	}
    // �ֶ�������բ
    IWDG_Feed(); // ι��
    if (F_fz == 1)
    {
        delay_ms(5);
        if ((F_fz == 1) && (isfenzha != 0))
        {
            F_ch = 0;
            F_gz_disp = FZ_AJ;
            Record_data_propare();
            Trip_Action();
            fenzha_chenggong = 0x11;
            Write_Selftest_Record(0x0E);
            gz_disp = 0;
            F_record_write = 1;
            gz_reason = trip_reason_key;
            // putchar(gz_reason);
            GZ_ph = 1;
            // Write_Record(trip_reason_lock,1);
            F_STrip = 1;
            // д������բ��¼
            F_fz = 0;
            // �ֶ���բ������־
        }
    }
    // ԤԼԶ�̷�բ
    if (F_yc_fenzha == 1)
    {
        F_yc_hezha = 0;
        F_yc_fenzha = 0;
        Record_data_propare();
        Trip_Action();
        fenzha_chenggong = 0x11;
        Write_Selftest_Record(0x0D);
        F_gz_disp = FZ_YC;
        // gz_reason = trip_reason_lock;
        gz_reason = trip_reason_remote;
        GZ_ph = 1;
        F_record_write = 1;
        // Write_Record(trip_reason_remote,1);
    }
    // ԤԼģ���բ
    if (F_an_fenzha == 1)
    {
        F_analog_trip = 1;
        F_an_fenzha = 0;
        Trip_Process_time(1);
    }
    // 15s��ʱ���鿴�Ƿ�ʱ�䵽������ʱ������բ
    if (F_time_trip == 1)
    {
        unsigned char tim_array[8];
        F_time_trip = 0;
        T_time_trip = 0;
        //		ds1302_read_time_uart(tim_array);
        HAL_RTC_GetTime(&hrtc, &stimestructure, RTC_FORMAT_BCD);
        HAL_RTC_GetDate(&hrtc, &sdatestructure, RTC_FORMAT_BCD);
        tim_y = sdatestructure.Year; // tim_yΪʮ���ƣ�Ҫת��������
        tim_m = sdatestructure.Month;
        tim_d = sdatestructure.Date;
        tim_h = stimestructure.Hours;
        tim_f = stimestructure.Minutes;
        tim_s = stimestructure.Seconds;
        tim_array[0] = tim_y;

        tim_array[1] = tim_m;

        tim_array[2] = tim_d;

        tim_array[3] = tim_h;

        tim_array[4] = tim_f;

        tim_array[5] = tim_s;
        //	tim_y=tim_y%2000;  //time_tmp[0]=17   ʮ����ת��Ϊ�����ƴ���24C64��
        //	tim_array[0]=(tim_y/10)<<4;
        //	tim_array[0]+=(tim_y%10);
        //	tim_array[1]=(tim_m/10)<<4;
        //	tim_array[1]+=(tim_m%10);
        //	tim_array[2]=(tim_d/10)<<4;
        //	tim_array[2]+=(tim_d%10);
        //	tim_array[3]=(tim_h/10)<<4;
        //	tim_array[3]+=(tim_h%10);
        //	tim_array[4]=(tim_f/10)<<4;
        //	tim_array[4]+=(tim_f%10);
        //	tim_array[5]=(tim_s/10)<<4;
        //	tim_array[5]+=(tim_s%10);

        if ((F_timer_triped == 0) && (timed_trip_code[0] == tim_array[4]) && (timed_trip_code[1] == tim_array[3]) && (timed_trip_code[2] == tim_array[2]))
        {
            Trip_Process_time(0);
            F_timer_triped = 1;
        }
        if ((F_timer_triped == 1) && (timed_trip_code[0] != tim_array[4]))
        {
            F_timer_triped = 0;
        }
    }
}

void Trip_Process_time(unsigned char tmp)
{

    // ��������,���ѿ�

    // if((F_al_key==1)||(F_al_temp==1)||(F_al_uart==1))
    if (F_trip_ld)
    {
        // F_al1Ϊ�澯������ر�־λ,��©ʱ�澯����˸��ţ��7.15�޸ģ�
        F_al1 = 5;
        // ��������˸
    }
    else
    {
        // ��һ���ѿ�
        if (F_Trip == 0)
        {
            Leak_Cur_disp = 989;
            gz_disp = Leak_Cur_disp;
            Record_data_propare();
            Leak_Cur_disp = 989;
            Trip_Action();
            Leak_Cur_disp = 0;
            F_gz_disp = L_hb;
            F_ch = 0;
            //			fenzha_chenggong = 0x11;
            //			Write_Selftest_Record(0x0C);
            if (tmp == 0)
            {
                // Write_Record(trip_reason_timer,1);
                gz_reason = trip_reason_timer;
                GZ_ph = 1;
                F_record_write = 1;
            }
            if (tmp == 1)
            {
                // Write_Record(trip_reason_remote,1);
                gz_reason = trip_reason_remote;
                GZ_ph = 1;
                F_record_write = 1;
            }
            if (F_la == 1)
            {
                F_Trip = 1;
                // �������غ�բ
            }
            else
            {
                F_Trip = 3;
                F_ch = 3;
                F_L_Lock = 1;
            }
        }
        // �����ڶ����ѿ�
        if (F_Trip == 2)
        {
            if (F_la2 == 1)
            {
                gz_disp = Leak_Cur_disp;
                Record_data_propare();
                Trip_Action();
                N_Trip = N_Trip + 1;
                rms_make(N_Trip);

                F_Trip = 1;
                T_64_xs = 0;
                if (N_Trip == 3)
                {
                    F_Trip = 3;
                    F_L_Lock = 1;
                    N_Trip = 0;
                }
            }
            else
            {
                F_Trip = 3;
                F_L_Lock = 1;
                gz_disp = Leak_Cur_disp;
                Record_data_propare();
                Trip_Action();
                rms_make(3);
                F_ch = 3;
            }
        }
    }
}

void rms_make(unsigned char i)
{
    // rms=sqrtf((float)rms_last)*4.242 ;
    // if(rms<0)rms=0 ;
    // L_Cur=((int)(rms));

    F_gz_disp = L_hb;
    F_ch = i;
    if (F_TB_gz == 1)
    {
        F_record_write = 1;
        gz_reason = trip_reason_leak;
        // putchar(gz_reason);
        GZ_ph = 1;
        // Write_Record(trip_reason_leak,GZ_ph);
    }
    else
    {
        // putchar(0xB1);
        F_record_write = 1;
        gz_reason = trip_reason_leak;
        // putchar(gz_reason);
        GZ_ph = 1;
        // Write_Record(trip_reason_leak,1);
    }
    // Write_Record(trip_reason_leak,1);
}

unsigned char Trip_Action(void)
{
    unsigned int ci_shu1;
    // �ѿ�ʱ�����
    //	if(F_anolog_trip == 1)
    //	{
    ////		RELAY1 = 0;
    //		F_anolog_trip = 0;
    //	}
    if (isfenzha != 0) // ��բ״̬
    {
        ci_shu1 = 0;
        F_guocheng = 1;
        F_ZW = 0;
        // Trip_LED_ON ;
        while ((isfenzha != 0) && (ci_shu1 < 300))
        {
            Trip_ON;
            delay_ms(5);
            ci_shu1++;
            IWDG_Feed();
            //			initial_lcd();
        }
        Trip_OFF;
        // Trip_LED_OFF ;
        F_disp_tr = 0;
        // �ѿ۹��ϱ�־����0923
        if (ci_shu1 >= 300)
        {
            fenzha();
            F_guocheng = 0;
        }
        ci_shu1 = 0;
        F_initial_lcd_hezha = 1;
    }
    if (isfenzha == 0)
    {
        F_guocheng = 0;
        return 1;
        // ��բ�ɹ�
    }
    if (isfenzha != 0)
    {
        F_disp_tr = 1;
        F_ZW = 1;
        F_guocheng = 0;
        return 0;
        // ����λD7
        // ��բʧ��
    }
    return 0;
}
void c_hezha(void)
{
    // Trip_LED_OFF ;
    F_sssj = 0;
    //	F_V_Nomal=0 ;
    //	F_VL=0 ;
    //	F_VH=0 ;
    F_anolog_trip = 0;
    F_Leak_Delay = 0;
    delay_ms(5);
    delay_ms(5);
    delay_ms(5);
    delay_ms(5);
    delay_ms(5);
    delay_ms(5);
    V_Sample_C(1);
    V_Sample_C(2);
    V_Sample_C(3);
    delay_ms(5);

    // asm("wdr");
    // ����ȫ��
    if ((F_trip_qy == 1) && (F_trip_gy == 1)) //&&(F_dianya_chonghe==1)
    {
        // ��ѹ����
        if (F_V_Nomal == 1)
        {
            hezha();
            clear_flags();
        }
        else
        {
            //			dispbit[0]=0x5e ;
            //			dispbit[1]=0x6e ;
            //			dispbit[2]=0x40 ;
            //			dispbit[3]=0x40 ;
            //			display();
            if (F_shangdian_hezha == 1)
            {
                F_wait_DY_Normal = 1;
            }
            clear_screen();
            Lcd12864_Write16CnCHAR(0, 32, 1, "��ѹ�쳣");
            Lcd12864_Write16CnCHAR(0, 32, 3, "���ɺ�բ");
            if ((F_shangdian_hezha == 1) && (F_N_shangdian == 0))
            {
                F_shangdian_2 = 1;
                F_N_shangdian = 2;
            }
            delay_ms(1000);
            F_QUIT = 1;
        }
    }
    else if ((F_trip_qy == 1) && (F_trip_gy == 0))
    {
        // ��ѹ����������ֵ
        if (F_VL == 1)
        {
            hezha();
            clear_flags();
        }
        else
        {
            //			if(F_shangdian_hezha==1)
            //			{
            //
            //			}
            if (F_shangdian_hezha == 1)
            {
                F_wait_DY_Normal = 1;
            }
            clear_screen();
            Lcd12864_Write16CnCHAR(0, 32, 1, "��ѹ�쳣");
            Lcd12864_Write16CnCHAR(0, 32, 3, "���ɺ�բ");
            if ((F_shangdian_hezha == 1) && (F_N_shangdian == 0))
            {
                F_shangdian_2 = 1;
                F_N_shangdian = 2;
            }
            delay_ms(1000);
            F_QUIT = 1;
        }
    }
    else if ((F_trip_qy == 0) && (F_trip_gy == 1))
    {
        delay_ms(5);
        // ��ѹ����������ֵ
        if (F_VH == 1)
        {
            hezha();
            clear_flags();
        }
        else
        {
            //			if(F_shangdian_hezha==1)
            //			{
            //
            //			}

            if (F_shangdian_hezha == 1)
            {
                F_wait_DY_Normal = 1;
            }
            clear_screen();
            Lcd12864_Write16CnCHAR(0, 32, 1, "��ѹ�쳣");
            Lcd12864_Write16CnCHAR(0, 32, 3, "���ɺ�բ");
            if ((F_shangdian_hezha == 1) && (F_N_shangdian == 0))
            {
                F_shangdian_2 = 1;
                F_N_shangdian = 2;
            }
            delay_ms(1000);
            F_QUIT = 1;
        }
    }
    else if ((F_trip_qy == 0) && (F_trip_gy == 0))
    {
        hezha();
        clear_flags();
    }
}

void Trip_Process(void)
{

    // ��������,���ѿ�
    // F_al_uart �Ѿ��޸�ΪF_trip_ld
    // if((F_al_key==1)||(F_al_temp==1)||(F_al_uart==1))

    if (F_trip_ld)
    {
        F_al1 = 50;
        if (F_anolog_trip == 1)
        {
            //			RELAY1 = 0;
        }
    }
    else
    {
        T_64_xs = 0;
        // ��һ���ѿ�
        if ((F_Trip == 3) || (F_Trip == 1))
        {
            F_Trip = 0;
            N_Trip = 0;
        }
        if (F_Trip == 0)
        {
            gz_disp = Leak_Cur_disp;
            Record_data_propare();
            //			Leak_Over_process();//©�糬�޼�¼20201201Y
            Trip_Action();
            F_gz_disp = L_hb;
            F_ch = 0;
            if (F_TB_gz == 1)
            {
                if (F_anolog_trip == 1)
                {
                    gz_reason = trip_reason_leak;
                    F_anolog_trip = 0;
                }
                else
                    gz_reason = trip_reason_leak;
                GZ_ph = 1;
                F_record_write = 1;
                // putchar(gz_reason);
            }
            else
            {
                if (F_anolog_trip == 1)
                {
                    gz_reason = trip_reason_leak;
                    F_anolog_trip = 0;
                }
                else
                    gz_reason = trip_reason_leak;
                GZ_ph = 1;
                F_record_write = 1;
                // putchar(gz_reason);
            }
            ctrlword5_analyze();
            if (F_la == 1)
            {
                F_Trip = 1;
                // �������غ�բ
            }
            else
            {
                F_Trip = 3;
                F_ch = 0;
                F_L_Lock = 1;
            }
        }
        // �����ڶ����ѿ�
        if (F_Trip == 2)
        {
            ctrlword5_analyze();
            if (F_la1 == 0)
            {
                if (F_la2 == 1)
                {
                    gz_disp = Leak_Cur_disp;
                    F_gz_disp = L_hb;
                    Record_data_propare();
                    Trip_Action();
                    N_Trip = N_Trip + 1;
                    rms_make(N_Trip);
                    F_Trip = 1;
                    T_64_xs = 0;
                    if (N_Trip >= 3)
                    {
                        F_Trip = 3;
                        F_L_Lock = 1;
                        N_Trip = 0;
                    }
                }
                else
                {
                    F_Trip = 3;
                    F_L_Lock = 1;
                    F_gz_disp = L_hb;
                    gz_disp = Leak_Cur_disp;
                    Record_data_propare();
                    Trip_Action();
                    gz_reason = trip_reason_lock;
                    //				rms_make(3);
                    F_ch = 1;
                }
            }
            else if (F_la1 == 1)
            {
                F_gz_disp = L_hb;
                gz_disp = Leak_Cur_disp;
                Record_data_propare();
                Trip_Action();
                N_Trip = 0;
                rms_make(N_Trip);
                F_Trip = 1;
                T_64_xs = 0;
            }
        }
    }
}

void Switch_pos_judge(void)
{
    N_BASE = N_BASE - 1;
    if (N_BASE <= 0)
        N_BASE = 0;
    // ������ΪӦ�ں�բλ��,��բλ�ô��ڷ�բ,���ж�Ϊδ֪��բ,д��¼д�ɶ�·����

    if (F_ZW == 1)
    {
        //		Trip_LED_OFF;
        if ((F_guocheng == 0) && (isfenzha == 0))
        {
            //			Trip_LED_ON;
            N_BASE = N_BASE + 2;
            if (N_BASE >= 500) // old code 500
            {
                N_BASE = 0;
                F_UTrip = 1;
                // δ֪�ѿ۱�־
                F_ZW = 0;
                F_disp_tr = 0;
                // PutStr("\nduan_lu_bao_hu");
                //				if(F_trip_gl==1)  //���ɵ㴦�������
                //				{
                //					Cur_Sample_C(1);
                //					Cur_Sample_C(2);
                //					Cur_Sample_C(3);
                //					Cur_Sample_C(4);
                //
                //				}
                F_ch = 0;
                F_gz_disp = FZ_UK;
                gz_disp = 0;
                Record_data_propare();
                gz_reason = trip_reason_hand;
                GZ_ph = 1;
                F_record_write = 1;
                // Write_Record(trip_reason_hand,1);
                // д��·��բ��¼
            }
            // Trip_Action();
        }
    }
    // ������ΪӦ�ڷ�բλ��,��Ϊ�ֶ���բ,����������б�־

    if (F_ZW == 0)
    {
        //		Trip_LED_ON;
        if ((F_guocheng == 0) && (isfenzha != 0))
        {
            //			Trip_LED_OFF;
            N_BASE = N_BASE + 2;
            if (N_BASE >= 500)
            {
                N_BASE = 0;
                F_ZW = 1;
                clear_flags();
                F_gz_disp = 0X0F;
                F_gz = 0x00;
            }
        }
    }
}

void Leak_Over_process(void)
{
    unsigned char time_tmp[8], i;
    if (F_Leak_Alarm == 0)
    {
        if (Leak_Cur_disp >= Leak_Alarm_Value)
        //				if(200>=Leak_Alarm_Value)
        {

            F_Leak_Alarm = 1;               // �澯��1
            Leak_Over_array[0] = max_phase; // 0x01;
            DectoBCD(&Leak_Over_array[1], Leak_Cur_disp, 2);
            //			ds1302_read_time_uart(time_tmp);
            HAL_RTC_GetTime(&hrtc, &stimestructure, RTC_FORMAT_BCD);
            HAL_RTC_GetDate(&hrtc, &sdatestructure, RTC_FORMAT_BCD);
            tim_y = sdatestructure.Year; // tim_yΪʮ���ƣ�Ҫת��������
            tim_m = sdatestructure.Month;
            tim_d = sdatestructure.Date;
            tim_h = stimestructure.Hours;
            tim_f = stimestructure.Minutes;
            tim_s = stimestructure.Seconds;
            time_tmp[0] = tim_y;

            time_tmp[1] = tim_m;

            time_tmp[2] = tim_d;

            time_tmp[3] = tim_h;

            time_tmp[4] = tim_f;

            time_tmp[5] = tim_s;
            for (i = 0; i < 6; i++)
            {
                Leak_Over_array[3 + i] = time_tmp[5 - i];
            }
        }
    }
    else
    {
        if (Leak_Cur_disp < Leak_Alarm_Value)
        //		if(0<Leak_Alarm_Value)
        {
            F_Leak_Alarm = 0;
            //			ds1302_read_time_uart(time_tmp);
            HAL_RTC_GetTime(&hrtc, &stimestructure, RTC_FORMAT_BCD);
            HAL_RTC_GetDate(&hrtc, &sdatestructure, RTC_FORMAT_BCD);
            tim_y = sdatestructure.Year; // tim_yΪʮ���ƣ�Ҫת��������
            tim_m = sdatestructure.Month;
            tim_d = sdatestructure.Date;
            tim_h = stimestructure.Hours;
            tim_f = stimestructure.Minutes;
            tim_s = stimestructure.Seconds;
            time_tmp[0] = tim_y;

            time_tmp[1] = tim_m;

            time_tmp[2] = tim_d;

            time_tmp[3] = tim_h;

            time_tmp[4] = tim_f;

            time_tmp[5] = tim_s;
            for (i = 0; i < 6; i++)
            {
                Leak_Over_array[9 + i] = time_tmp[5 - i];
            }
            MODIFY_EEP_W((Addr_event_leak + 15 * point_event_leak), Leak_Over_array, 15, 0xA0);
            point_event_leak = point_event_leak + 1;
            if (point_event_leak >= 10)
                point_event_leak = 0x00;
            time_tmp[0] = point_event_leak;
            MODIFY_EEP_W(Addr_point_event_leak, time_tmp, 1, 0xA0);
        }
    }
}
/*********************************************
                ��ѹ������
vol_handle(unsigned int value)
V_Sample(unsigned char tmp)
loss_phase_trip(unsigned char phase_tmp)
under_vol_trip(unsigned char phase_tmp)
up_vol_trip(unsigned char phase_tmp)
loss_phase_process(int upset_value,int downset_value)
under_vol_prcoess(int upset_value,int downset_value)
up_vol_prcoess(int upset_value)
Vol_Process(void)
Vol_sample_process(void)
**********************************************/
unsigned int vol_handle(unsigned int value)
{
    unsigned int V_t;
    V_t = value;

    //	  V_t=(V_t*V1_slope[0])>>20;

    return (V_t);
}

void V_Sample_C(unsigned char tmp) // 220ms����һ��
{
    // �ɼ�A\B\C���ѹ
    // asm("wdr");
    //	signed int tmp_A1,tmp_A2;
    //   if((tmp+4)==5)
    //	{
    //	  AD_result=Get_Adc(ADC_Channel_7);
    //	}
    //	else if((tmp+4)==6)
    //	{
    //		AD_result=Get_Adc(ADC_Channel_14);
    //	}
    //  else
    //	{
    //		AD_result=Get_Adc(ADC_Channel_15);
    //	}
    if ((tmp - 1) < 3)
    {
        //		V_Array[tmp-1]=AD_result ;
        // if(tmp==1)
        // {
        // tmp_A1 = (Vol_A_aver>>1)+(Vol_A_aver>>4);
        // tmp_A2 = (tmp_A1<<2)-(tmp_A1>>1)-109;
        // if(tmp_A2>0)
        // V_Array[0] = tmp_A2;
        // }
        if (V_MAX_tmp[tmp - 1] < V_Array[tmp - 1])
        {
            V_MAX_tmp[tmp - 1] = V_Array[tmp - 1];
        }
        if (V_MIN_tmp[tmp - 1] > V_Array[tmp - 1])
        {
            V_MIN_tmp[tmp - 1] = V_Array[tmp - 1];
        }
    }
    //	Get_Advalue(4);//�Ƿ���Ҫ����Ҫ����ͨ���л������Ƿ���Ӱ�졣
    if (tmp == 3)
    {
        //		if((vol_handle_A(V_Array[0])<H_H_V)&&(vol_handle_A(V_Array[0])>H_L_V)&&(vol_handle_B(V_Array[1])<H_H_V)&&(V_Array[1]>H_L_V)&&(V_Array[2]<H_H_V)&&(V_Array[2]>H_L_V))
        //		F_V_Nomal=1 ;
        //		else
        //		F_V_Nomal=0 ;
        // ��ǰ��ѹֵ�����ޱ�־
        if ((vol_handle_A(V_Array[0]) < H_H_V) && (vol_handle_B(V_Array[1]) < H_H_V) && (vol_handle_C(V_Array[2]) < H_H_V))
            F_VH = 1;
        else
            F_VH = 0;
        // ��ǰ��ѹֵ������
        if ((vol_handle_A(V_Array[0]) > H_L_V) && (vol_handle_B(V_Array[1]) > H_L_V) && (vol_handle_C(V_Array[2]) > H_L_V))
            F_VL = 1;
        else
            F_VL = 0;
        // ��ǰ��ѹֵ������
        if ((F_VL == 1) && (F_VH == 1))
        {
            F_V_Nomal = 1;
        }
        else
        {
            F_V_Nomal = 0;
        }
    }
}

void V_Sample(unsigned char tmp) // 220ms����һ��
{
    //	signed int tmp_A1,tmp_A2;
    // �ɼ�A\B\C���ѹ
    // asm("wdr");

    if (F_Vol_Re == 10)
    {
        //		F_Vol_Re=0;
        if ((tmp - 1) < 3)
        {
            //			V_Array[tmp-1]=AD_result ;
            if (V_MAX_tmp[tmp - 1] < V_Array[tmp - 1]) // ȡ����¼ֵ
            {
                V_MAX_tmp[tmp - 1] = V_Array[tmp - 1];
            }
            if (V_MIN_tmp[tmp - 1] > V_Array[tmp - 1])
            {
                V_MIN_tmp[tmp - 1] = V_Array[tmp - 1];
            }
        }
    }

    //	Get_Advalue(4);//�Ƿ���Ҫ����Ҫ����ͨ���л������Ƿ���Ӱ�졣
    //	AD_result=Get_Adc(ADC_Channel_0);   // ©��ͨ��

    if (tmp == 3)
    {
        //		if((vol_handle_A(V_Array[0])<H_H_V)&&(vol_handle_A(V_Array[0])>H_L_V)&&(vol_handle_B(V_Array[1])<H_H_V)&&(V_Array[1]>H_L_V)&&(V_Array[2]<H_H_V)&&(V_Array[2]>H_L_V))
        //		F_V_Nomal=1 ;
        //		else
        //		F_V_Nomal=0 ;
        // ��ǰ��ѹֵ�����ޱ�־
        if ((vol_handle_A(V_Array[0]) < H_H_V) && (vol_handle_B(V_Array[1]) < H_H_V) && (vol_handle_C(V_Array[2]) < H_H_V))
            F_VH = 1;
        else
            F_VH = 0;
        // ��ǰ��ѹֵ������
        if ((vol_handle_A(V_Array[0]) > H_L_V) && (vol_handle_B(V_Array[1]) > H_L_V) && (vol_handle_C(V_Array[2]) > H_L_V))
            F_VL = 1;
        else
            F_VL = 0;
        // ��ǰ��ѹֵ������
        if ((F_VL == 1) && (F_VH == 1))
        {
            F_V_Nomal = 1;
        }
        else
        {
            F_V_Nomal = 0;
        }
    }
}

// phase_tmpȡֵ��Χ1,2,3
unsigned char loss_phase_trip(unsigned char phase_tmp)
{
    N_qx_hezha = 0;
    Record_data_propare();
    gz_disp = vol_handle(V_Array[phase_tmp - 1]);
    // if(F_trip_xq==1)
    {
        Trip_Action();
    }
    F_qxTrip = 1;
    if (phase_tmp == 1)
    {
        F_gz_disp = 0x10;
    }
    else if (phase_tmp == 2)
    {
        F_gz_disp = 0x11;
    }
    else if (phase_tmp == 3)
    {
        F_gz_disp = 0x12;
    }
    //	F_gz_disp=2*(phase_tmp-1);
    F_record_write = 1;
    gz_reason = trip_reason_phase;
    // putchar(gz_reason);
    GZ_ph = phase_tmp;
    // Write_Record(trip_reason_phase,phase_tmp);
    return 0;
}
unsigned char low_vol_trip(unsigned char phase_tmp)
{
    N_sy_hezha = 0;
    //	if(phase_tmp==1)
    //	{
    //		F_gz_disp=0x14;
    //	}
    //	else if(phase_tmp==2)
    //	{
    //		F_gz_disp=0x15;
    //	}
    //	else if(phase_tmp==3)
    //	{
    //		F_gz_disp=0x16;
    //	}
    Record_data_propare();
    //	gz_disp=vol_handle(V_Array[phase_tmp-1]);
    // if(F_qy==1)
    {
        Trip_Action();
    }
    //	F_sy_sucess=1;

    write_tingdian();

    F_syTrip = 1;
    //	F_gz_disp=2*(phase_tmp-1);
    F_record_write = 1;
    gz_reason = trip_reason_undervoltage;
    GZ_ph = phase_tmp;
    return 0;
}

// phase_tmpȡֵ��Χ1,2,3
unsigned char under_vol_trip(unsigned char phase_tmp)
{
    N_qy_hezha = 0;
    Record_data_propare();
    gz_disp = vol_handle(V_Array[phase_tmp - 1]);
    // if(F_qy==1)
    {
        Trip_Action();
    }
    F_qyTrip = 1;
    F_gz_disp = 2 * (phase_tmp - 1);
    F_record_write = 1;
    gz_reason = trip_reason_undervoltage;
    GZ_ph = phase_tmp;
    return 0;
}

unsigned char anti_islanding_trip(unsigned char phase_tmp)  //���µ��ѿ�
{
		N_anti_islanding_hezha = 0;
		//�ֹ�ѹ��Ƿѹ
		
		gz_disp = max_of_three(vol_handle_anti_islanding_A(U_Array_xianshi[0]),vol_handle_anti_islanding_B(U_Array_xianshi[1]),vol_handle_anti_islanding_C(U_Array_xianshi[2]));
		
	  Trip_Action();
		F_anti_islanding_trip =1;
		F_gz_disp = 2 * (phase_tmp - 1) + 1;
		gz_reason = trip_reason_anti_islanding;
		GZ_ph = phase_tmp;
	
		return 0;
	//������
}

// phase_tmpȡֵ��Χ1,2,3
unsigned char up_vol_trip(unsigned char phase_tmp)
{
    N_gy_hezha = 0;
    Record_data_propare();
    gz_disp = vol_handle(V_Array[phase_tmp - 1]);
    // if(F_trip_gy==1)
    {
        Trip_Action();
    };
    F_gyTrip = 1;
    F_gz_disp = 2 * (phase_tmp - 1) + 1;
    F_record_write = 1;
    gz_reason = trip_reason_overvoltage;
    // putchar(gz_reason);
    GZ_ph = phase_tmp;
    // Write_Record(trip_reason_overvoltage,phase_tmp);
    return 0;
}
unsigned char lack_vol_trip(unsigned char phase_tmp)
{
    Record_data_propare();

    Trip_Action();
    F_lzTrip = 1;
    F_gz_disp = Gz_QL;
    F_record_write = 1;
    gz_reason = trip_reason_zero;
    // putchar(gz_reason);
    GZ_ph = 1;
    // Write_Record(trip_reason_overvoltage,phase_tmp);
    return 0;
}

/*˵��������ֵ1,2,3������һ�¶���,0��ʾ�޶���*/
unsigned char loss_phase_process(int upset_value, int downset_value)
{
    //	if((V_Array[0]<=10)||(V_Array[1]<=10)||(V_Array[2]<=10))//��ѹ����ԭ��δ�ҵ������ɼ�������ѹΪ0ʱ��ִ��ȱ����բ����
    //	{
    //		return 0 ;
    //	}
    if ((vol_handle_A(V_Array[0]) >= upset_value))
    {
        if ((V_Array[0] == 0) && (V_Array[1] == 0) && (V_Array[2] == 0)) // ��ѹ����ԭ��δ�ҵ������ɼ�������ѹΪ0ʱ��ִ��ȱ����բ����
        {
            return 0;
        }
        if (vol_handle_B(V_Array[1]) < downset_value)
        {
            N_a_bqx_trip = N_a_bqx_trip + 2;
            if (N_a_bqx_trip >= 20)
            {
                N_a_bqx_trip = 0;
                loss_phase_trip(2);
                return 2;
            }
        }
        else if (vol_handle_C(V_Array[2]) < downset_value)
        {
            N_a_cqx_trip = N_a_cqx_trip + 2;
            if (N_a_bqx_trip >= 20)
            {
                N_a_cqx_trip = 0;
                loss_phase_trip(3);
                return 3;
            }
        }
        else
        {
            if (N_a_bqx_trip >= 1)
            {
                N_a_bqx_trip--;
            }
            if (N_a_cqx_trip >= 1)
            {
                N_a_cqx_trip--;
            }
            return 0;
        }
    }
    if ((vol_handle_B(V_Array[1]) >= upset_value))
    {
        if ((V_Array[0] == 0) && (V_Array[1] == 0) && (V_Array[2] == 0)) // ��ѹ����ԭ��δ�ҵ������ɼ�������ѹΪ0ʱ��ִ��ȱ����բ����
        {
            return 0;
        }
        if (vol_handle_A(V_Array[0]) < downset_value)
        {
            N_b_aqx_trip = N_b_aqx_trip + 2;
            if (N_b_aqx_trip >= 20)
            {
                N_b_aqx_trip = 0;
                loss_phase_trip(1);
                return 1;
            }
        }
        else if (vol_handle_C(V_Array[2]) < downset_value)
        {
            N_b_cqx_trip = N_b_cqx_trip + 2;
            if (N_b_cqx_trip >= 20)
            {
                N_b_cqx_trip = 0;
                loss_phase_trip(3);
                return 3;
            }
        }
        else
        {
            if (N_b_aqx_trip >= 1)
            {
                N_b_aqx_trip--;
            }
            if (N_b_cqx_trip >= 1)
            {
                N_b_cqx_trip--;
            }
            return 0;
        }
    }
    if (vol_handle_C(V_Array[2]) >= upset_value)
    {
        if ((V_Array[0] == 0) && (V_Array[1] == 0) && (V_Array[2] == 0)) // ��ѹ����ԭ��δ�ҵ������ɼ�������ѹΪ0ʱ��ִ��ȱ����բ����
        {
            return 0;
        }
        if (vol_handle_A(V_Array[0]) < downset_value)
        {
            N_c_aqx_trip = N_c_aqx_trip + 2;
            if (N_c_aqx_trip >= 20)
            {
                N_c_aqx_trip = 0;
                loss_phase_trip(1);
                return 1;
            }
        }
        else if (vol_handle_B(V_Array[1]) < downset_value)
        {
            N_c_bqx_trip = N_c_bqx_trip + 2;
            if (N_c_bqx_trip >= 20)
            {
                N_c_bqx_trip = 0;
                loss_phase_trip(2);
                return 2;
            }
        }
        else
        {
            if (N_c_aqx_trip >= 1)
            {
                N_c_aqx_trip--;
            }
            if (N_c_bqx_trip >= 1)
            {
                N_c_bqx_trip--;
            }
            return 0;
        }
    }
    return 0;
}

unsigned char under_vol_prcoess(int upset_value, int downset_value)
{
    if ((V_Array[0] <= 10) || (V_Array[1] <= 10) || (V_Array[2] <= 10)) // ��ѹ����ԭ��δ�ҵ������ɼ�������ѹΪ0ʱ��ִ��ȱ����բ����
    {
        return 0;
    }
    if ((vol_handle_A(V_Array[0]) > upset_value))
    {
        N_aqy_trip = N_aqy_trip - 1;
        if (N_aqy_trip <= 0)
            N_aqy_trip = 0;
    }
    if ((vol_handle_A(V_Array[0]) > downset_value) && (vol_handle_A(V_Array[0]) < upset_value))
    {
        N_aqy_trip = N_aqy_trip + 2;
        if (N_aqy_trip >= T_L_V)
        {
            N_aqy_trip = 0;
            under_vol_trip(1);
            return 1;
        }
    }

    if ((vol_handle_B(V_Array[1]) > upset_value))
    {
        N_bqy_trip = N_bqy_trip - 1;
        if (N_bqy_trip <= 0)
            N_bqy_trip = 0;
    }
    if ((vol_handle_B(V_Array[1]) > downset_value) && (vol_handle_B(V_Array[1]) < upset_value))
    {
        N_bqy_trip = N_bqy_trip + 2;
        if (N_bqy_trip >= T_L_V)
        {
            N_bqy_trip = 0;
            under_vol_trip(2);
            return 2;
        }
    }

    if ((vol_handle_C(V_Array[2]) > upset_value))
    {
        N_cqy_trip = N_cqy_trip - 1;
        if (N_cqy_trip <= 0)
            N_cqy_trip = 0;
    }
    if ((vol_handle_C(V_Array[2]) > downset_value) && (vol_handle_C(V_Array[2]) < upset_value))
    {
        N_cqy_trip = N_cqy_trip + 2;
        if (N_cqy_trip >= T_L_V)
        {
            N_cqy_trip = 0;
            under_vol_trip(3);
            return 3;
        }
    }

    return 0;
}
unsigned char low_vol_prcoess(void)
{
	if(vol_handle_undervol(ADC_ConvertedValue[0])<2200)  //2481��Ӧ2V��ѹ
	{    
			N_asy_trip = N_asy_trip + 2;
			if (N_asy_trip >= T_S_V)
			{
					N_asy_trip = 0;
					Trip_ON;
					low_vol_trip(2);
			}
	}
	else
	{
			N_asy_trip = N_asy_trip - 1;
			if (N_asy_trip <= 0)
			{
					N_asy_trip = 0;
			}
	}
	
//    if ((vol_handle_A(V_Array[0]) <= 44) && (vol_handle_B(V_Array[1]) <= 44) && (vol_handle_C(V_Array[2]) <= 44))
//    {
//        N_asy_trip = N_asy_trip + 2;
//        if (N_asy_trip >= T_S_V)
//        {
//            N_asy_trip = 0;
//            Trip_ON;
//            low_vol_trip(2);
//        }
//    }
//    else
//    {
//        N_asy_trip = N_asy_trip - 1;
//        if (N_asy_trip <= 0)
//        {
//            N_asy_trip = 0;
//        }
//    }

    return 0;
}

unsigned char up_vol_prcoess(int upset_value)
{
    if ((vol_handle_A(V_Array[0]) < upset_value))
    {
        N_agy_trip = N_agy_trip - 1;
        if (N_agy_trip <= 0)
            N_agy_trip = 0;
    }
    else
    {
        N_agy_trip = N_agy_trip + 2;
        if (N_agy_trip >= T_H_V)
        {
            N_agy_trip = 0;
            up_vol_trip(1);
            return 1;
        }
    }

    if (vol_handle_B(V_Array[1]) < upset_value)
    {
        N_bgy_trip = N_bgy_trip - 1;
        if (N_bgy_trip <= 0)
            N_bgy_trip = 0;
    }
    else
    {
        N_bgy_trip = N_bgy_trip + 2;
        if (N_bgy_trip >= T_H_V)
        {
            N_bgy_trip = 0;
            up_vol_trip(2);
            return 2;
        }
    }

    if (vol_handle_C(V_Array[2]) < upset_value)
    {
        N_cgy_trip = N_cgy_trip - 1;
        if (N_cgy_trip <= 0)
            N_cgy_trip = 0;
    }
    else
    {
        N_cgy_trip = N_cgy_trip + 2;
        if (N_cgy_trip >= T_H_V)
        {
            N_cgy_trip = 0;
            up_vol_trip(3);
            return 3;
        }
    }

    return 0;
}
void lack_vol_process(void)
{
    //		if(N_QL>=10)
    //		{
    //			N_QL=0 ;
    //			lack_vol_trip(2);
    //		}
    if (F_QL_TRIP == 1)
    {
        //			delay_ms(5);
        //			delay_ms(5);
        //			delay_ms(5);
        //	  	delay_ms(5);
        delay_ms(5);
        if (F_QL_TRIP == 1)
        {
            F_QL_TRIP = 0;
            lack_vol_trip(2);
        }
    }
}

void lackzero_vol_process(void)
{
    if ((V_temp_tmp[0] > 40) || (V_temp_tmp[1] > 40) || (V_temp_tmp[2] > 40)) // ��һ��ȱ���ж����������ֵ
    {
        N_a_bql_trip = N_a_bql_trip + 2;
        if (N_a_bql_trip >= 8)
        {
            N_a_bql_trip = 0;
            lack_vol_trip(2);
        }
    }
    else
    {
        if (N_a_bql_trip >= 1)
        {
            N_a_bql_trip--;
        }
    }
    Lackzero_judge(); // �ڶ����ж������ֵ
    if (F_QL_TRIP == 1)
    {
        delay_ms(5);
        delay_ms(5);
        if (F_QL_TRIP == 1)
        {
            F_QL_TRIP = 0;
            lack_vol_trip(2);
        }
    }
}
void Vol_Process(void)
{
    // ��բ״̬�ж�ȱ�ࡢǷѹ����ѹ
    if (F_VLH == 0)
    {
        if ((V_Array[0] <= 450) && (V_Array[1] <= 450) && (V_Array[2] <= 450)) //
            F_VLH = 1;
    }
    if (F_VLH == 1)
    {
        if ((V_Array[0] >= 900) || (V_Array[1] >= 900) || (V_Array[2] >= 900)) //
            F_VLH = 2;
        F_shiya_hezha = 1;
    }

    V_temp[0] = (vol_handle_A(V_Array[0]));
    V_temp[1] = (vol_handle_B(V_Array[1]));
    V_temp[2] = (vol_handle_C(V_Array[2]));
    V_temp_tmp[0] = (V_temp[0] - V_temp[1]) / 10;
    if (V_temp_tmp[0] < 0)
        V_temp_tmp[0] = -V_temp_tmp[0];
    V_temp_tmp[1] = (V_temp[0] - V_temp[2]) / 10;
    if (V_temp_tmp[1] < 0)
        V_temp_tmp[1] = -V_temp_tmp[1];
    V_temp_tmp[2] = (V_temp[1] - V_temp[2]) / 10;
    if (V_temp_tmp[2] < 0)
        V_temp_tmp[2] = -V_temp_tmp[2];

    if (isfenzha != 0)
    {
        // ���ౣ��
        F_trip_xq = 1; // �㽭�Ĺ�
        //		if((F_trip_qy==1)&&(F_qxallTrip==0)&&(F_trip_xq==1))
        //				if((F_trip_qy==1)&&(F_trip_xq==1)&&(F_trip_QX==1))
        if ((F_trip_xq == 1) && (F_trip_QX == 1))
        {
            loss_phase_process(130, 100);
            // 175V
        }
        if ((F_trip_sy == 1) && (T_delay >= 150))
        {
            low_vol_prcoess();
        }

        // Ƿѹ����
        if ((F_trip_qy == 1) && (F_hezha_delay == 0))
        {
            under_vol_prcoess(H_L_V, 110);
        }
        // ��ѹ����
        if ((F_trip_gy == 1) && (F_hezha_delay == 0))
        {
            up_vol_prcoess(H_H_V);
        }
        if (F_trip_QL == 1)
        {
            if (((vol_handle_A(V_Array[0])) < 130) || ((vol_handle_B(V_Array[1])) < 130) || ((vol_handle_C(V_Array[2])) < 130)) // ���о��Ƿ�����ȱ����բ
            {
                loss_phase_process(130, 100);
            }
            else if (((vol_handle_A(V_Array[0])) < H_L_V) || ((vol_handle_B(V_Array[1])) < H_L_V) || ((vol_handle_C(V_Array[2])) < H_L_V)) // ���о��Ƿ�����Ƿѹ��բ
            {
                under_vol_prcoess(H_L_V, 110);
            }
            else if (((vol_handle_A(V_Array[0])) > H_H_V) || ((vol_handle_B(V_Array[1])) > H_H_V) || ((vol_handle_C(V_Array[2])) > H_H_V)) // ���о��Ƿ������ѹ��բ
            {
                up_vol_prcoess(H_H_V);
            }
            else
            {
                lackzero_vol_process();
            }

            //			lack_vol_process();
        }
        //		if(F_trip_QL==1)
        //		{
        //			lose_vol_process(V_UP,V_DOWN);
        //		}
    }
    // ��բ״̬�ж��غ�բ
    else
    {
        if (F_wait_DY_Normal == 1)
        {
            if (F_V_Nomal == 1)
            {
                N_shangdian_hezha = N_shangdian_hezha + 2;
            }
            else
            {
                N_shangdian_hezha = N_shangdian_hezha - 1;
                if (N_shangdian_hezha <= 0)
                    N_shangdian_hezha = 0;
            }
            if (N_shangdian_hezha >= 50)
            {
                F_wait_DY_Normal = 2;
                N_shangdian_hezha = 0;
                //				F_qxTrip=0 ;
            }
        }
        // �����غ�բ
        if ((F_dianya_chonghe == 1) && (F_qxTrip != 0))
        {
            if (F_V_Nomal == 1)
            {
                N_qx_hezha = N_qx_hezha + 2;
            }
            else
            {
                N_qx_hezha = N_qx_hezha - 1;
                if (N_qx_hezha <= 0)
                    N_qx_hezha = 0;
            }
            if (N_qx_hezha >= 250)
            {
                F_QX_hezha = 1;
                N_qx_hezha = 0;
                F_qxTrip = 0;
            }
        }
        // Ƿѹ�غ�բ
        if ((F_dianya_chonghe == 1) && (F_qyTrip == 1))
        {
            if (F_V_Nomal == 1)
            {
                N_qy_hezha = N_qy_hezha + 2;
            }
            else
            {
                N_qy_hezha = N_qy_hezha - 1;
                if (N_qy_hezha <= 0)
                    N_qy_hezha = 0;
            }
            if (N_qy_hezha >= 250)
            {
                F_QY_hezha = 1;
                N_qy_hezha = 0;
                F_qyTrip = 0;
            }
        }
        // ��ѹ�غ�բ
        if ((F_dianya_chonghe == 1) && (F_gyTrip == 1))
        {
            if (F_V_Nomal == 1)
            {
                N_gy_hezha = N_gy_hezha + 2;
            }
            else
            {
                N_gy_hezha = N_gy_hezha - 1;
                if (N_gy_hezha <= 0)
                    N_gy_hezha = 0;
            }
            if (N_gy_hezha >= 250)
            {
                F_GY_hezha = 1;
                N_gy_hezha = 0;
                F_gyTrip = 0;
            }
        }
        // ȱ���غ�բ
        if ((F_dianya_chonghe == 1) && (F_lzTrip == 1)) // ȱ���غ�բ
        {
            if (((BQL_Judge_tmp > 1900) && (BQL_Judge_tmp < 2100)) && ((AQL_Judge_tmp > 1900) && (AQL_Judge_tmp < 2100)) && ((CQL_Judge_tmp > 1900) && (CQL_Judge_tmp < 2100))) // �з�ֵ
            {
                if (F_V_Nomal == 1)
                {
                    N_lz_hezha = N_lz_hezha + 2;
                }
                else
                {
                    N_lz_hezha = N_lz_hezha - 1;
                    if (N_lz_hezha <= 0)
                        N_lz_hezha = 0;
                }
                if (N_lz_hezha >= 30)
                {
                    F_QL_hezha = 1;
                    N_lz_hezha = 0;
                    F_lzTrip = 0;
                }
            }
        }

        // if((F_dianya_chonghe==1)&&(F_syTrip==1)&&(F_shiya_hezha==1))
        if ((F_dianya_chonghe == 1) && (F_syTrip == 1))
        {
            if (F_V_Nomal == 1)
            {
                N_sy_hezha = N_sy_hezha + 2;
            }
            else
            {
                N_sy_hezha = N_sy_hezha - 1;
                if (N_sy_hezha <= 0)
                    N_sy_hezha = 0;
            }
            if (N_sy_hezha >= 200)
            {
                F_shiya_hezha = 0;
                F_SY_hezha = 1;
                N_sy_hezha = 0;
                F_syTrip = 0;
            }
        }
    }
}

void Anti_Islanding_Overvol(unsigned int overvalue) //���µ���ѹ
{
		if ((vol_handle_anti_islanding_A(U_Array_xianshi[0]) < overvalue))  //A��
    {
        N_anti_islanding_over_A = N_anti_islanding_over_A - 1;
        if (N_anti_islanding_over_A <= 0)
            N_anti_islanding_over_A = 0;
    }
    else
    {
        N_anti_islanding_over_A = N_anti_islanding_over_A + 2;
        if (N_anti_islanding_over_A >= 10)
        {
            N_anti_islanding_over_A = 0;
						anti_islanding_trip(1);//������
        }
    }
		
		if ((vol_handle_anti_islanding_B(U_Array_xianshi[1]) < overvalue))  //B��
    {
        N_anti_islanding_over_B = N_anti_islanding_over_B - 1;
        if (N_anti_islanding_over_B <= 0)
            N_anti_islanding_over_B = 0;
    }
    else
    {
        N_anti_islanding_over_B = N_anti_islanding_over_B + 2;
        if (N_anti_islanding_over_B >= 10)
        {
            N_anti_islanding_over_B = 0;
						anti_islanding_trip(2);//������
        }
    }
		
		if ((vol_handle_anti_islanding_C(U_Array_xianshi[2]) < overvalue))  //C��
    {
        N_anti_islanding_over_C = N_anti_islanding_over_C - 1;
        if (N_anti_islanding_over_C <= 0)
            N_anti_islanding_over_C = 0;
    }
    else
    {
        N_anti_islanding_over_C = N_anti_islanding_over_C + 2;
        if (N_anti_islanding_over_C >= 10)
        {
            N_anti_islanding_over_C = 0;
						anti_islanding_trip(3);//������
        }
    }
}

void Anti_Islanding_Undervol(unsigned int undervalue) //���µ�Ƿѹ
{
		if ((vol_handle_anti_islanding_A(U_Array_xianshi[0]) < undervalue))  //A��
    {
        N_anti_islanding_under_A = N_anti_islanding_under_A - 1;
        if (N_anti_islanding_under_A <= 0)
            N_anti_islanding_under_A = 0;
    }
    else
    {
        N_anti_islanding_under_A = N_anti_islanding_under_A + 2;
        if (N_anti_islanding_under_A >= 10)
        {
            N_anti_islanding_under_A = 0;
						anti_islanding_trip(1);//������
        }
    }
		
		if ((vol_handle_anti_islanding_B(U_Array_xianshi[1]) < undervalue))  //B��
    {
        N_anti_islanding_under_B = N_anti_islanding_under_B - 1;
        if (N_anti_islanding_under_B <= 0)
            N_anti_islanding_under_B = 0;
    }
    else
    {
        N_anti_islanding_under_B = N_anti_islanding_under_B + 2;
        if (N_anti_islanding_under_B >= 10)
        {
            N_anti_islanding_under_B = 0;
						anti_islanding_trip(2);//������
        }
    }
		
		if ((vol_handle_anti_islanding_C(U_Array_xianshi[2]) < undervalue))  //C��
    {
        N_anti_islanding_under_C = N_anti_islanding_under_C - 1;
        if (N_anti_islanding_under_C <= 0)
            N_anti_islanding_under_C = 0;
    }
    else
    {
        N_anti_islanding_under_C = N_anti_islanding_under_C + 2;
        if (N_anti_islanding_under_C >= 10)
        {
            N_anti_islanding_under_C = 0;
						anti_islanding_trip(3);//������
        }
    }
}

//�жϵ�ǰ���µ�����״̬Ϊ�������쳣�������ж��Ƿ�����غ�բ
void Anti_Islanding_State_Judge(void)
{
	unsigned int upset_value = 250;
	unsigned int downset_value = 190;
	unsigned int a,b,c;
	a = vol_handle_anti_islanding_A(U_Array_xianshi[0]);
	b = vol_handle_anti_islanding_B(U_Array_xianshi[1]);
	c = vol_handle_anti_islanding_C(U_Array_xianshi[2]);
	if((a<upset_value)&&(b<upset_value)&&(c<upset_value)&&(a>downset_value)&&(b>downset_value)&&(c>downset_value))
		F_anti_islanding_normal = 1;
	else
		F_anti_islanding_normal = 0;
}

void Anti_Islanding_Process(void)  //���µ���������
{
	if (isfenzha != 0)  //��բ״̬
  {
		if((F_anti_islanding==1)&&(F_anti_islanding_switch==1)) //��ʱ��־�ͱ������ر�־λ
		{
			F_anti_islanding=0;
			Anti_Islanding_Overvol(250);
			Anti_Islanding_Undervol(190);
			
			Anti_Islanding_State_Judge();//�жϵ�ǰ���µ�����״̬Ϊ�������쳣�������ж��Ƿ�����غ�բ
			
		}
	}
	else  //��բ״̬�ж��غ�բ
	{
		// ���µ��غ�բ
		if ((F_anti_islanding_chonghe == 1) && (F_anti_islanding_trip == 1))
		{
				if (F_anti_islanding_normal == 1)
				{
						N_anti_islanding_hezha = N_anti_islanding_hezha + 2;
				}
				else
				{
						N_anti_islanding_hezha = N_anti_islanding_hezha - 1;
						if (N_anti_islanding_hezha <= 0)
								N_anti_islanding_hezha = 0;
				}
				if (N_anti_islanding_hezha >= 250)
				{
						F_anti_islanding_hezha= 1;  //��բ������־
						N_anti_islanding_hezha = 0;  //��������
						F_anti_islanding_trip = 0;  //�ѿ�״̬����
				}
		}
	}
}

// ��ѹ�����봦��
void Vol_sample_process(void) // ʵ�ʲ���Ϊ50ms����һ��
{
    IWDG_Feed(); // ι��
    if ((F_Vol == 10) && (F_Delay == 1) && (F_Vsam_begin == 1))
    {
        F_Vol = 0;

        T_V = T_V + 1;
        V_Sample(V_point); // ��ѹ����
        V_point++;
        if (V_point == 4)
        {
            V_point = 1;
        }
        Vol_Process();
        if (T_V > 100) // 20ms X 100 = 2S ����һ��
        {
            T_V = 0;
            V_max_process(FN_Vol + 1); // ��ѹ��ֵ��¼
            V_min_process(FN_Vol + 1);
            Leak_max_process(); // ©����ֵ��¼
            Leak_min_process();
            FN_Vol = FN_Vol + 1;
            if (FN_Vol >= 3)
                FN_Vol = 0;
        }
    }
}
void Tem_trip(phase_tmp)
{
    N_tem_hezha = 0;
    gz_disp = Tem_value[phase_tmp];

    Trip_Action();

    F_temTrip = 1;
    F_gz_disp = 2 * (phase_tmp) + 51;

    gz_reason = trip_reason_tem;
}

void LCD_Tem_trip(unsigned char phase_tmp,unsigned char gz_disp_tmp)
{
    N_tem_hezha = 0;
    gz_disp = gz_disp_tmp;

    Trip_Action();

    F_temTrip = 1;
    F_gz_disp = 2 * (phase_tmp) + 51;

    gz_reason = trip_reason_tem;
}

void Temperature_Process(void)
{
    if (wendu == 1)
    {
        if (F_tem == 1) // 200ms
        {
            if (isfenzha != 0) // ��բ
            {
                if ((Tem_value[0] >= TEM_UP) || (Tem_value[1] >= TEM_UP) || (Tem_value[2] >= TEM_UP) || (Tem_value[3] >= TEM_UP) || (Tem_value[4] >= TEM_UP) || (Tem_value[5] >= TEM_UP) || (Tem_value[6] >= TEM_UP) || (Tem_value[7] >= TEM_UP))
                {
                    N_tem_trip = N_tem_trip + 2;
                    if (N_tem_trip >= 5)
                    {
                        N_tem_trip = 0;
                        if (Tem_value[0] >= TEM_UP)
                            Tem_trip(0);
                        else if (Tem_value[1] >= TEM_UP)
                            Tem_trip(1);
                        else if (Tem_value[2] >= TEM_UP)
                            Tem_trip(2);
                        else if (Tem_value[3] >= TEM_UP)
                            Tem_trip(3);
                        else if (Tem_value[4] >= TEM_UP)
                            Tem_trip(4);
                        else if (Tem_value[5] >= TEM_UP)
                            Tem_trip(5);
                        else if (Tem_value[6] >= TEM_UP)
                            Tem_trip(6);
                        else if (Tem_value[7] >= TEM_UP)
                            Tem_trip(7);

                        //	low_vol_trip(2);//**********�¶���բ�����滻****
                    }
                }
                else
                {
                    N_tem_trip = N_tem_trip - 1;
                    if (N_tem_trip <= 0)
                    {
                        N_tem_trip = 0;
                    }
                }
            }

            else // ��բ
            {
                /**************�¶��غ�բ******************/
                if (F_temTrip == 1)
                {
                    if ((Tem_value[0] < TEM_DOWN) && (Tem_value[1] < TEM_DOWN) && (Tem_value[2] < TEM_DOWN) && (Tem_value[3] < TEM_DOWN) && (Tem_value[4] < TEM_DOWN) && (Tem_value[5] < TEM_DOWN) && (Tem_value[6] < TEM_DOWN) && (Tem_value[7] < TEM_DOWN))
                    {
                        N_tem_hezha = N_tem_hezha + 2;
                    }
                    else
                    {
                        N_tem_hezha = N_tem_hezha - 1;
                        if (N_tem_hezha <= 0)
                            N_tem_hezha = 0;
                    }
                    if (N_tem_hezha >= 25)
                    {
                        F_tem_hezha = 1;
                        N_tem_hezha = 0;
                        F_temTrip = 0;
                    }
                }
            }

            F_tem = 0; // 200ms
        }
    }
}

void Cur_Switch(unsigned char Type_Cur)
{
    unsigned char array_temp[26];
    // Type_Cur=1;

    switch (Type_Cur)
    {
    case 0:
    {
        // Delta_Cur = 20 + D_Cur*10;  //��λֵ
        Delta_Cur = D_Cur * 10 + 50;

        if (Delta_Cur == 60)
            Delta_Cur = 63;
        if (Delta_Cur == 130)
            Delta_Cur = 125;
        DLD_Cur = (Delta_Cur * (2 * D2_Cur + 2)); // ����֮����ֵ
        DLS_Cur = (Delta_Cur * (2 * D3_Cur + 4)); // ˲������֮����ֵ
        H_Cur = 1.15 * Delta_Cur * Delta_Cur;
        // H5_Cur=((375*Delta_Cur*Delta_Cur)<<TH_Long_Cur);//375=1.5*15/0.06
        H5_Cur = ((280 * Delta_Cur * Delta_Cur) * (R_SD[TH_Long_Cur] + 3)); // 375=1.5*15/0.06
        I3 = DLS_Cur;                                                       // ����10��ԭ��������ʾֵ���бȽϣ�����С�������ԭ����ʾֵ��������10����
        I3_1 = DLS_Cur;
        I2 = DLD_Cur;
        frame_current_code[0] = '1';
        frame_current_code[1] = '2';
        frame_current_code[2] = '5';
        frame_current_code[3] = frame_current_code[4] = frame_current_code[5] = 0x20;
        /*************125�Ǽ�*****************/
        EEPROM_R(Addr_L1_slope, array_temp, 2, 0xA0);
        L1_slope = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr_Leak1_temp, array_temp, 2, 0xA0);
        Leak1_temp = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr100_I1_A_slope, array_temp, 2, 0xA0);
        I1_A_slope[0] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr100_I1_B_slope, array_temp, 2, 0xA0);
        I1_B_slope[0] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr100_I1_C_slope, array_temp, 2, 0xA0);
        I1_C_slope[0] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr100_I1_A_slope1, array_temp, 2, 0xA0);
        I1_A_slope[1] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr100_I1_B_slope1, array_temp, 2, 0xA0);
        I1_B_slope[1] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr100_I1_C_slope1, array_temp, 2, 0xA0);
        I1_C_slope[1] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr100_CurA_cal_tmp, array_temp, 2, 0xA0);
        CurA_cal_tmp[0] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr100_CurB_cal_tmp, array_temp, 2, 0xA0);
        CurB_cal_tmp[0] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr100_CurC_cal_tmp, array_temp, 2, 0xA0);
        CurC_cal_tmp[0] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr100_CurA_cal_tmp1, array_temp, 2, 0xA0);
        CurA_cal_tmp[1] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr100_CurB_cal_tmp1, array_temp, 2, 0xA0);
        CurB_cal_tmp[1] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr100_CurC_cal_tmp1, array_temp, 2, 0xA0);
        CurC_cal_tmp[1] = (array_temp[1] << 8) + array_temp[0];
        break;
    }
    case 1:
    {
        // Delta_Cur = 60 + D_Cur*10;  //???
        Delta_Cur = D_Cur * 10 + 60;
        if (Delta_Cur == 60)
            Delta_Cur = 63;
        DLD_Cur = (Delta_Cur * (2 * D2_Cur + 2)); //??????
        DLS_Cur = (Delta_Cur * (2 * D3_Cur + 4)); //????????
                                                  //			H_Cur=D_C2_Array[D_Cur]-100;
                                                  //			H5_Cur=((D_C25_15Array[D_Cur]-500)<<TH_Long_Cur); //???
                                                  //			I2=D_C29_Array[D_Cur];
                                                  //			I2=(D_C2_2d_2Array[D_Cur]*(2*D2_Cur+2))<<1;
        H_Cur = 1.15 * Delta_Cur * Delta_Cur;
        // H5_Cur=((375*Delta_Cur*Delta_Cur)<<TH_Long_Cur);//375=1.5*15/0.06
        H5_Cur = ((310 * Delta_Cur * Delta_Cur) * (R_SD[TH_Long_Cur] + 1)); // 375=1.5*15/0.06
        I3 = DLS_Cur;                                                       // ����10��ԭ��������ʾֵ���бȽϣ�����С�������ԭ����ʾֵ��������10����
        if (DLS_Cur < 1000)
        {
            I3_1 = (DLS_Cur * 7 >> 3) + (DLS_Cur >> 5); // ��С��0.9
        }
        else
        {
            I3_1 = 900 + ((DLS_Cur - 1000) >> 2) + ((DLS_Cur - 1000) >> 4) + ((DLS_Cur - 1000) >> 5);
        }
        // I3 = I3 - (I3>>6);
        I2 = DLD_Cur;
        //			if(DLD_Cur<=1000)//������
        //			{
        //				 I2 =  (unsigned long)(DLD_Cur*10);
        //			}
        //			else if((DLD_Cur>1000)&&(DLD_Cur<=1500))
        //			{
        //				 I2 = 10000 + (unsigned long)(DLD_Cur-1000)*5;
        //			}
        //	  	else if((DLD_Cur>1500)&&(DLD_Cur<=2500))
        //			{
        //				 I2 = 12500 + (unsigned long)(DLD_Cur-1500)*3;
        //			}
        //			else if((DLD_Cur>2500)&&(DLD_Cur<=3000))
        //			{
        //				 I3 = 15500 + ((unsigned long)((DLD_Cur-2000)*3)>>1);
        //			}
        //
        //
        //			if(DLS_Cur<=1000)
        //			{
        //				 I3 =  (unsigned long)(DLS_Cur*10);
        //			}
        //			else if((DLS_Cur>1000)&&(DLS_Cur<=1500))
        //			{
        //				 I3 = 10000 + (unsigned long)(DLS_Cur-1000)*5;
        //			}
        //	  	else if((DLS_Cur>1500)&&(DLS_Cur<=2500))
        //			{
        //				 I3 = 12500 + (unsigned long)(DLS_Cur-1500)*3;
        //			}
        //			else if((DLS_Cur>2500)&&(DLS_Cur<=3000))
        //			{
        //				 I3 = 15500 + ((unsigned long)((DLS_Cur-2000)*3)>>1);
        //			}

        frame_current_code[0] = '2';
        frame_current_code[1] = '5';
        frame_current_code[2] = '0';
        frame_current_code[3] = frame_current_code[4] = frame_current_code[5] = 0x20;
        /******************************����У׼ϵ��********************************/
        EEPROM_R(Addr_L1_slope, array_temp, 2, 0xA0);
        L1_slope = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr_Leak1_temp, array_temp, 2, 0xA0);
        Leak1_temp = (array_temp[1] << 8) + array_temp[0];

        //		EEPROM_R(Addr_V1_A_slope,array_temp,2,0xA0);
        //		V1_slope[0]=(array_temp[1]<<8)+array_temp[0];

        //
        //		EEPROM_R(Addr_V1_B_slope,array_temp,2,0xA0);
        //		V1_slope[1]=(array_temp[1]<<8)+array_temp[0];
        //
        //		EEPROM_R(Addr_V1_C_slope,array_temp,2,0xA0);
        //		V1_slope[2]=(array_temp[1]<<8)+array_temp[0];

        /*************250�Ǽ�*****************/
        EEPROM_R(Addr_I1_A_slope, array_temp, 2, 0xA0);
        I1_A_slope[0] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr_I1_B_slope, array_temp, 2, 0xA0);
        I1_B_slope[0] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr_I1_C_slope, array_temp, 2, 0xA0);
        I1_C_slope[0] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr_I1_A_slope1, array_temp, 2, 0xA0);
        I1_A_slope[1] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr_I1_B_slope1, array_temp, 2, 0xA0);
        I1_B_slope[1] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr_I1_C_slope1, array_temp, 2, 0xA0);
        I1_C_slope[1] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr_CurA_cal_tmp, array_temp, 2, 0xA0);
        CurA_cal_tmp[0] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr_CurB_cal_tmp, array_temp, 2, 0xA0);
        CurB_cal_tmp[0] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr_CurC_cal_tmp, array_temp, 2, 0xA0);
        CurC_cal_tmp[0] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr_CurA_cal_tmp1, array_temp, 2, 0xA0);
        CurA_cal_tmp[1] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr_CurB_cal_tmp1, array_temp, 2, 0xA0);
        CurB_cal_tmp[1] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr_CurC_cal_tmp1, array_temp, 2, 0xA0);
        CurC_cal_tmp[1] = (array_temp[1] << 8) + array_temp[0];

        //		EEPROM_R(Addr_Vol1_A_temp,array_temp,2,0xA0);
        //		Vol1_A_temp=(array_temp[1]<<8)+array_temp[0];
        //		EEPROM_R(Addr_Vol1_B_temp,array_temp,2,0xA0);
        //		Vol1_B_temp=(array_temp[1]<<8)+array_temp[0];
        //		EEPROM_R(Addr_Vol1_C_temp,array_temp,2,0xA0);
        //		Vol1_C_temp=(array_temp[1]<<8)+array_temp[0];
        //

        break;
    }

    case 2:
    {
        Delta_Cur = 160 + D_Cur * 20;             // ��λֵ
        DLD_Cur = (Delta_Cur * (2 * D2_Cur + 2)); // ����֮����ֵ
        DLS_Cur = (Delta_Cur * (2 * D3_Cur + 4)); // ˲������֮����ֵ
        //		  H_Cur=D_C3_Array[D_Cur];
        //			H5_Cur=(D_C35_15Array[D_Cur]<<TH_Long_Cur);
        //			I2=D_C29_Array[D_Cur];
        H_Cur = 1.15 * Delta_Cur * Delta_Cur;
        // H5_Cur=((375*Delta_Cur*Delta_Cur)<<TH_Long_Cur);//375=1.5*15/0.06
        H5_Cur = ((355 * Delta_Cur * Delta_Cur) * (R_SD[TH_Long_Cur] + 2)); // 375=1.5*15/0.06
        I3 = DLS_Cur;                                                       // ����10��ԭ��������ʾֵ���бȽϣ�����С�������ԭ����ʾֵ��������10����
        I3_1 = DLS_Cur;
        // I3=(I3*7>>3)+(I3>>5);  //��С��0.9
        // I3 = I3 - (I3>>6);
        I2 = DLD_Cur;
        //			I2=(D_C3_2d_2Array[D_Cur]*(2*D2_Cur+2));
        //				if(DLD_Cur<=1000)//������
        //				{
        //				 I2=((unsigned long)(DLD_Cur*61)>>3);
        //				}
        //				  else if((DLD_Cur>1000)&&(DLD_Cur<=2000))
        //				{
        //					I2=7320+(unsigned long)((DLD_Cur-1000)*47/6);
        //				}
        //				  else if((DLD_Cur>2000)&&(DLD_Cur<=3000))
        //				{
        //					I2=15100+(unsigned long)((DLD_Cur-2000)*17/8);
        //				}
        //				  else if((DLD_Cur>3000)&&(DLD_Cur<=4000))
        //				{
        //					I2=17300+(unsigned long)((DLD_Cur-3000)*6);
        //				}
        //				else
        //				{
        //					I3=23300+((unsigned long)(DLS_Cur-4000)>>4);
        //				}

        //				if(DLS_Cur<=1000)
        //				{
        //				 I3=((unsigned long)(DLS_Cur*61)>>3);
        //				}
        //				  else if((DLS_Cur>1000)&&(DLS_Cur<=2000))
        //				{
        //					I3=7320+(unsigned long)((DLS_Cur-1000)*47/6);
        //				}
        //				  else if((DLS_Cur>2000)&&(DLS_Cur<=3000))
        //				{
        //					I3=15100+(unsigned long)((DLS_Cur-2000)*17/8);
        //				}
        //				  else if((DLS_Cur>3000)&&(DLS_Cur<=4000))
        //				{
        //					I3=17300+(unsigned long)((DLS_Cur-3000)*6);
        //				}
        //				else
        //				{
        //					I3=23300+((unsigned long)(DLS_Cur-4000)>>4);
        //				}

        //				if(D3_Cur==0)
        //			{
        //				I3=D_C3_3d_6Array[D_Cur];
        //			}
        //		  else if(D3_Cur==1)
        //			{
        //				I3=D_C3_3d_8Array[D_Cur];
        //			}
        //			else if(D3_Cur==2)
        //			{
        //				I3=D_C3_3d_10Array[D_Cur];
        //			}
        //			else if(D3_Cur==3)
        //			{
        //				I3=D_C3_3d_12Array[D_Cur];
        //			}
        frame_current_code[0] = '4';
        frame_current_code[1] = '0';
        frame_current_code[2] = '0';
        frame_current_code[3] = frame_current_code[4] = frame_current_code[5] = 0x20;
        /*************400�Ǽ�*****************/
        EEPROM_R(Addr400_L1_slope, array_temp, 2, 0xA0);
        L1_slope = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr400_Leak1_temp, array_temp, 2, 0xA0);
        Leak1_temp = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr400_I1_A_slope, array_temp, 2, 0xA0);
        I1_A_slope[0] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr400_I1_B_slope, array_temp, 2, 0xA0);
        I1_B_slope[0] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr400_I1_C_slope, array_temp, 2, 0xA0);
        I1_C_slope[0] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr400_I1_A_slope1, array_temp, 2, 0xA0);
        I1_A_slope[1] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr400_I1_B_slope1, array_temp, 2, 0xA0);
        I1_B_slope[1] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr400_I1_C_slope1, array_temp, 2, 0xA0);
        I1_C_slope[1] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr400_CurA_cal_tmp, array_temp, 2, 0xA0);
        CurA_cal_tmp[0] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr400_CurB_cal_tmp, array_temp, 2, 0xA0);
        CurB_cal_tmp[0] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr400_CurC_cal_tmp, array_temp, 2, 0xA0);
        CurC_cal_tmp[0] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr400_CurA_cal_tmp1, array_temp, 2, 0xA0);
        CurA_cal_tmp[1] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr400_CurB_cal_tmp1, array_temp, 2, 0xA0);
        CurB_cal_tmp[1] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr400_CurC_cal_tmp1, array_temp, 2, 0xA0);
        CurC_cal_tmp[1] = (array_temp[1] << 8) + array_temp[0];
        break;
    }
    case 3:
    {
        // Delta_Cur = 210+D_Cur*30;  //��λֵ
        Delta_Cur = D_Cur * 30 + 220;

        if (Delta_Cur == 250)
            Delta_Cur = 252;
        if (Delta_Cur == 640)
            Delta_Cur = 630;

        DLD_Cur = (Delta_Cur * (2 * D2_Cur + 2)); // ����֮����ֵ
        DLS_Cur = (Delta_Cur * (2 * D3_Cur + 4)); // ˲������֮����ֵ
        H_Cur = 1.15 * Delta_Cur * Delta_Cur;
        // H5_Cur=((375*Delta_Cur*Delta_Cur)<<TH_Long_Cur);//375=1.5*15/0.06
        H5_Cur = ((340 * Delta_Cur * Delta_Cur) * (R_SD[TH_Long_Cur] + 2)); // 375=1.5*15/0.06
        I3 = DLS_Cur;                                                       // ����10��ԭ��������ʾֵ���бȽϣ�����С�������ԭ����ʾֵ��������10����
        I3_1 = DLS_Cur;
        // I3=(I3*7>>3)+(I3>>5);  //��С��0.9
        // I3 = I3 - (I3>>6);
        I2 = DLD_Cur;
        //			 H_Cur=D_C4_Array[D_Cur];
        //		 	H5_Cur=(D_C45_15Array[D_Cur]<<TH_Long_Cur);
        //			I2=D_C29_Array[D_Cur];

        //				I2=(D_C4_2d_2Array[D_Cur]*(2*D2_Cur+2));
        //				if(DLD_Cur<=600)//������
        //			   {
        //					 I2=(DLD_Cur*39)>>3;
        //				 }
        //				  else if((DLD_Cur>600)&&(DLD_Cur<=1000))
        //				{
        //				  I2=(DLD_Cur*39)>>3;
        //				}
        //          else if((DLD_Cur>1000)&&(DLD_Cur<=1500))
        //				{
        //				  I2=(DLD_Cur*39)>>3;
        //				}
        //				 else if((DLD_Cur>1500)&&(DLD_Cur<=2000))
        //				{
        //				  I2=(DLD_Cur*19)>>2;
        //				}
        //				else if((DLD_Cur>2000)&&(DLD_Cur<=2100))
        //				{
        //					 I2=(DLD_Cur*38)>>3;
        //				}
        //				else if((DLD_Cur>2100)&&(DLD_Cur<=2300))
        //				{
        //					 I2=(DLD_Cur*37)>>3;
        //				}
        //				else if((DLD_Cur>2300)&&(DLD_Cur<=2550))
        //				{
        //					 I2=(DLD_Cur*36)>>3;
        //				}
        //					else if((DLD_Cur>2550)&&(DLD_Cur<=2750))
        //				{
        //					 I2=(DLD_Cur*35)>>3;
        //				}
        //					else if((DLD_Cur>2750)&&(DLD_Cur<=3000))
        //				{
        //					 I2=(DLD_Cur*34)>>3;
        //				}
        //					else if((DLD_Cur>3000)&&(DLD_Cur<=3300))
        //				{
        //					 I2=(DLD_Cur*33)>>3;
        //				}
        //					else if((DLD_Cur>3300)&&(DLD_Cur<=3600))
        //				{
        //					 I2=(DLD_Cur*32)>>3;
        //				}
        //					else if((DLD_Cur>3600)&&(DLD_Cur<=3900))
        //				{
        //					 I2=(DLD_Cur*31)>>3;
        //				}
        //
        //
        //
        //          if(DLS_Cur<=2000)
        //				{
        //				  I3=(DLS_Cur*19)>>2;
        //				}
        //				else if((DLS_Cur>2000)&&(DLS_Cur<=2100))
        //				{
        //					 I3=(DLS_Cur*38)>>3;
        //				}
        //				else if((DLS_Cur>2100)&&(DLS_Cur<=2300))
        //				{
        //					 I3=(DLS_Cur*37)>>3;
        //				}
        //				else if((DLS_Cur>2300)&&(DLS_Cur<=2550))
        //				{
        //					 I3=(DLS_Cur*36)>>3;
        //				}
        //					else if((DLS_Cur>2550)&&(DLS_Cur<=2750))
        //				{
        //					 I3=(DLS_Cur*35)>>3;
        //				}
        //					else if((DLS_Cur>2750)&&(DLS_Cur<=3000))
        //				{
        //					 I3=(DLS_Cur*34)>>3;
        //				}
        //					else if((DLS_Cur>3000)&&(DLS_Cur<=3500))
        //				{
        //					 I3=(DLS_Cur*33)>>3;
        //				}
        //					else if((DLS_Cur>3500)&&(DLS_Cur<3900))
        //				{
        //					 I3=(DLS_Cur*32)>>3;
        //				}
        //					else if((DLS_Cur>=3900)&&(DLS_Cur<=4200))
        //				{
        //					 I3=(DLS_Cur*30)>>3;
        //				}
        //					else if((DLS_Cur>4200)&&(DLS_Cur<=4500))
        //				{
        //					 I3=(DLS_Cur*27)>>3;
        //				}
        //					else if((DLS_Cur>4500)&&(DLS_Cur<=5100))
        //				{
        //					 I3=(DLS_Cur*25)>>3;
        //				}
        //					else if((DLS_Cur>5100)&&(DLS_Cur<=5400))
        //				{
        //					 I3=(DLS_Cur*24)>>3;
        //				}
        //					else if((DLS_Cur>5400)&&(DLS_Cur<=5700))
        //				{

        //					I3=(DLS_Cur*22)>>3;
        //				}
        //					else if((DLS_Cur>5700)&&(DLS_Cur<=6300))
        //				{
        //					 I3=(DLS_Cur*21)>>3;
        //				}
        //					else if((DLS_Cur>6300)&&(DLS_Cur<=7000))
        //				{
        //					 I3=(DLS_Cur*20)>>3;
        //				}
        //				else
        //				{
        //					I3=DLS_Cur*15;
        //				}
        //			if(D2_Cur==0)
        //			{
        //				I2=D_C4_2d_2Array[D_Cur];
        //			}
        //		  else if(D2_Cur==1)
        //			{
        //				I2=D_C4_2d_4Array[D_Cur];
        //			}
        //			else if(D2_Cur==2)
        //			{
        //				I2=D_C4_2d_6Array[D_Cur];
        //			}
        //			else if(D2_Cur==3)
        //			{
        //				I2=D_C4_2d_8Array[D_Cur];
        //			}
        //				else if(D2_Cur==4)
        //			{
        //				I2=D_C4_2d_10Array[D_Cur];
        //			}
        //          if(DLS_Cur<=2000)
        //				{
        //				 I3=DLS_Cur*20;
        //				}
        //				else if((DLS_Cur>2000)&&(DLS_Cur<=3000))
        //				{
        //					 I3=DLS_Cur*19;
        //				}
        //				else if((DLS_Cur>3000)&&(DLS_Cur<4000))
        //				{
        //					 I3=DLS_Cur*18;
        //				}
        //				  else if((DLS_Cur>=4000)&&(DLS_Cur<5000))
        //				{
        //					 I3=DLS_Cur*17;
        //				}
        //				else if((DLS_Cur>=5000)&&(DLS_Cur<6000))
        //				{
        //					I3=DLS_Cur*16;
        //				}
        //				else
        //				{
        //					I3=DLS_Cur*15;
        //				}

        //				if(D3_Cur==0)
        //			{
        //				I3=D_C4_3d_6Array[D_Cur];
        //			}
        //		  else if(D3_Cur==1)
        //			{
        //				I3=D_C4_3d_8Array[D_Cur];
        //			}
        //			else if(D3_Cur==2)
        //			{
        //				I3=D_C4_3d_10Array[D_Cur];
        //			}
        //			else if(D3_Cur==3)
        //			{
        //				I3=D_C4_3d_12Array[D_Cur];
        //			}
        frame_current_code[0] = '6';
        frame_current_code[1] = '3';
        frame_current_code[2] = '0';
        frame_current_code[3] = frame_current_code[4] = frame_current_code[5] = 0x20;
        /*************630�Ǽ�*****************/
        EEPROM_R(Addr630_L1_slope, array_temp, 2, 0xA0);
        L1_slope = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr630_Leak1_temp, array_temp, 2, 0xA0);
        Leak1_temp = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr630_I1_A_slope, array_temp, 2, 0xA0);
        I1_A_slope[0] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr630_I1_B_slope, array_temp, 2, 0xA0);
        I1_B_slope[0] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr630_I1_C_slope, array_temp, 2, 0xA0);
        I1_C_slope[0] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr630_I1_A_slope1, array_temp, 2, 0xA0);
        I1_A_slope[1] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr630_I1_B_slope1, array_temp, 2, 0xA0);
        I1_B_slope[1] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr630_I1_C_slope1, array_temp, 2, 0xA0);
        I1_C_slope[1] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr630_CurA_cal_tmp, array_temp, 2, 0xA0);
        CurA_cal_tmp[0] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr630_CurB_cal_tmp, array_temp, 2, 0xA0);
        CurB_cal_tmp[0] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr630_CurC_cal_tmp, array_temp, 2, 0xA0);
        CurC_cal_tmp[0] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr630_CurA_cal_tmp1, array_temp, 2, 0xA0);
        CurA_cal_tmp[1] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr630_CurB_cal_tmp1, array_temp, 2, 0xA0);
        CurB_cal_tmp[1] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr630_CurC_cal_tmp1, array_temp, 2, 0xA0);
        CurC_cal_tmp[1] = (array_temp[1] << 8) + array_temp[0];
        /*************400�Ǽ�*****************/
        //		EEPROM_R(Addr400_L1_slope,array_temp,2,0xA0);
        //		L1_slope=(array_temp[1]<<8)+array_temp[0];
        //
        //		EEPROM_R(Addr400_Leak1_temp,array_temp,2,0xA0);
        //		Leak1_temp=(array_temp[1]<<8)+array_temp[0];
        //
        //		EEPROM_R(Addr400_I1_A_slope,array_temp,2,0xA0);
        //		I1_A_slope[0]=(array_temp[1]<<8)+array_temp[0];
        //
        //		EEPROM_R(Addr400_I1_B_slope,array_temp,2,0xA0);
        //		I1_B_slope[0]=(array_temp[1]<<8)+array_temp[0];
        //
        //		EEPROM_R(Addr400_I1_C_slope,array_temp,2,0xA0);
        //		I1_C_slope[0]=(array_temp[1]<<8)+array_temp[0];

        //		EEPROM_R(Addr400_I1_A_slope1,array_temp,2,0xA0);
        //		I1_A_slope[1]=(array_temp[1]<<8)+array_temp[0];
        //
        //		EEPROM_R(Addr400_I1_B_slope1,array_temp,2,0xA0);
        //		I1_B_slope[1]=(array_temp[1]<<8)+array_temp[0];
        //
        //		EEPROM_R(Addr400_I1_C_slope1,array_temp,2,0xA0);
        //		I1_C_slope[1]=(array_temp[1]<<8)+array_temp[0];

        //
        //		EEPROM_R(Addr400_CurA_cal_tmp,array_temp,2,0xA0);
        //		CurA_cal_tmp[0]=(array_temp[1]<<8)+array_temp[0];
        //
        //    EEPROM_R(Addr400_CurB_cal_tmp,array_temp,2,0xA0);
        //		CurB_cal_tmp[0]=(array_temp[1]<<8)+array_temp[0];
        //
        //    EEPROM_R(Addr400_CurC_cal_tmp,array_temp,2,0xA0);
        //		CurC_cal_tmp[0]=(array_temp[1]<<8)+array_temp[0];

        //    EEPROM_R(Addr400_CurA_cal_tmp1,array_temp,2,0xA0);
        //		CurA_cal_tmp[1]=(array_temp[1]<<8)+array_temp[0];
        //
        //		EEPROM_R(Addr400_CurB_cal_tmp1,array_temp,2,0xA0);
        //		CurB_cal_tmp[1]=(array_temp[1]<<8)+array_temp[0];
        //
        //		EEPROM_R(Addr400_CurC_cal_tmp1,array_temp,2,0xA0);
        //		CurC_cal_tmp[1]=(array_temp[1]<<8)+array_temp[0];
        break;
    }
    case 4:
    {
        Delta_Cur = 320 + D_Cur * 80;             // ��λֵ
        DLD_Cur = (Delta_Cur * (2 * D2_Cur + 2)); // ����֮����ֵ
        DLS_Cur = (Delta_Cur * (2 * D3_Cur + 4)); // ˲������֮����ֵ
        H_Cur = 1.15 * Delta_Cur * Delta_Cur;
        //	H5_Cur=((375*Delta_Cur*Delta_Cur)<<TH_Long_Cur);//375=1.5*15/0.06
        H5_Cur = ((310 * Delta_Cur * Delta_Cur) * (R_SD[TH_Long_Cur] + 1)); // 375=1.5*15/0.06
        I3 = DLS_Cur;                                                       // ����10��ԭ��������ʾֵ���бȽϣ�����С�������ԭ����ʾֵ��������10����
        I3_1 = DLS_Cur;
        I2 = DLD_Cur;
        frame_current_code[0] = '8';
        frame_current_code[1] = '0';
        frame_current_code[2] = '0';
        frame_current_code[3] = frame_current_code[4] = frame_current_code[5] = 0x20;
        /*************800�Ǽ�*****************/
        EEPROM_R(Addr800_L1_slope, array_temp, 2, 0xA0);
        L1_slope = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr800_Leak1_temp, array_temp, 2, 0xA0);
        Leak1_temp = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr800_I1_A_slope, array_temp, 2, 0xA0);
        I1_A_slope[0] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr800_I1_B_slope, array_temp, 2, 0xA0);
        I1_B_slope[0] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr800_I1_C_slope, array_temp, 2, 0xA0);
        I1_C_slope[0] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr800_I1_A_slope1, array_temp, 2, 0xA0);
        I1_A_slope[1] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr800_I1_B_slope1, array_temp, 2, 0xA0);
        I1_B_slope[1] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr800_I1_C_slope1, array_temp, 2, 0xA0);
        I1_C_slope[1] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr800_CurA_cal_tmp, array_temp, 2, 0xA0);
        CurA_cal_tmp[0] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr800_CurB_cal_tmp, array_temp, 2, 0xA0);
        CurB_cal_tmp[0] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr800_CurC_cal_tmp, array_temp, 2, 0xA0);
        CurC_cal_tmp[0] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr800_CurA_cal_tmp1, array_temp, 2, 0xA0);
        CurA_cal_tmp[1] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr800_CurB_cal_tmp1, array_temp, 2, 0xA0);
        CurB_cal_tmp[1] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr800_CurC_cal_tmp1, array_temp, 2, 0xA0);
        CurC_cal_tmp[1] = (array_temp[1] << 8) + array_temp[0];
        break;
    }
    }
}

void Cur_Switch_F(unsigned char Type_Cur)
{

    // Type_Cur=1;

    switch (Type_Cur)
    {
    case 0:
    {
        frame_current_code[0] = '8';
        frame_current_code[1] = '0';
        frame_current_code[2] = '0';
        frame_current_code[3] = frame_current_code[4] = frame_current_code[5] = 0x20;
        break;
    }
    case 1:
    {
        frame_current_code[0] = '2';
        frame_current_code[1] = '5';
        frame_current_code[2] = '0';
        frame_current_code[3] = frame_current_code[4] = frame_current_code[5] = 0x20;

        break;
    }
    case 2:
    {
        frame_current_code[0] = '4';
        frame_current_code[1] = '0';
        frame_current_code[2] = '0';
        frame_current_code[3] = frame_current_code[4] = frame_current_code[5] = 0x20;

        break;
    }
    case 3:
    {
        frame_current_code[0] = '6';
        frame_current_code[1] = '3';
        frame_current_code[2] = '0';
        frame_current_code[3] = frame_current_code[4] = frame_current_code[5] = 0x20;
        break;
    }
    case 4:
    {
        frame_current_code[0] = '8';
        frame_current_code[1] = '0';
        frame_current_code[2] = '0';
        frame_current_code[3] = frame_current_code[4] = frame_current_code[5] = 0x20;
        break;
    }
    }
}

unsigned int cur_handle(unsigned int x)
{
    int y;
    int y1;
    // ������ܵȼ�Ϊ20~100Aʱ
    if (Type_Cur == 0)
        x = (x / 5) >> 2; // xΪ�ɳ�����ֵ 0-4096
    // ������ܵȼ�Ϊ60~250Aʱ
    if (Type_Cur == 1) // ��Ҫ�Ķ�
    {
        x = (x * 53) >> 10;
    }
    // ������ܵȼ�Ϊ200~400Aʱ
    if (Type_Cur == 2)
    {
        x = (x * 83) >> 10;
    }
    // ������ܵȼ�Ϊ60~250Aʱ
    if (Type_Cur == 3)
    {
        x = (x * 107) >> 10;
    }
    //	if(x>=760) I_factor_tmp = I_factor;
    //	else if(x>=600) I_factor_tmp = I_factor>>1;
    //	else if(x>=400) I_factor_tmp = I_factor>>2;
    //	else if(x>=200)  I_factor_tmp = I_factor>>3;
    //	else            I_factor_tmp = I_factor>>4;
    //	if(160<x<200)
    //	{
    //		x=x-5;
    //	}
    y1 = x; // ���ڷ���ʱ�ۿ�����
    y = y1;
    y1 = 0;
    //	if(y<100)
    //	y = y-10;
    if (y <= 10)
        y = 0;
    return y;
}

// void Cur_Sample_C(unsigned char tmp)
//{
//	unsigned char i ;
//	i=tmp-1 ;
////	F_Cur = 0;
//	if(i==0)
//	{
//	  AD_result=Get_Adc(ADC_Channel_10);
//	}
//	else if(i==1)
//	{
//		AD_result=Get_Adc(ADC_Channel_11);
//	}
//  else
//	{
//		AD_result=Get_Adc(ADC_Channel_12);
//	}
//	if(I_MAX_tmp[i]<I_Array[i])
//	{
//		I_MAX_tmp[i] = I_Array[i];
//	}
//	if(I_MIN_tmp[i]>I_Array[i])
//	{
//		I_MIN_tmp[i] = I_Array[i];
//	}
////	AD_result=Get_Adc(ADC_Channel_0);
//}

// void Cur_Sample(unsigned char tmp)
//{
//	unsigned char i ;
//	i=tmp-1 ;
////	F_Cur = 0;
//
//	if(i==0)
//	{
//	  AD_result=Get_Adc(ADC_Channel_10);
//	}
//	else if(i==1)
//	{
//		AD_result=Get_Adc(ADC_Channel_11);
//	}
//  else
//	{
//		AD_result=Get_Adc(ADC_Channel_12);
//	}
//
//	if(i<4)
//	{
//		I_Array[i]=AD_result ;
//		if(I_MAX_tmp[i]<I_Array[i])
//		{
//			I_MAX_tmp[i] = I_Array[i];
//		}
//		if(I_MIN_tmp[i]>I_Array[i])
//		{
//			I_MIN_tmp[i] = I_Array[i];
//		}
//	}
////	AD_result=Get_Adc(ADC_Channel_0);
//}

void Cur_Process(void)
{
    unsigned char i;
    if (F_trip_gl == 1)
    {
			for (i = 0; i < 3; i++)
			{
				if(isfenzha==0)
				{
					I_Array[i] = 0;
				}	
				I2_Array[i]=(long)I_Array[i]*(long)I_Array[i];   //  �Ե�������ƽ��
				if(I2_Array[i]>H_Cur)
				{
					I2_Array_Sum[i]=I2_Array_Sum[i]+I2_Array[i];
				}
				else
				{
					I2_Array_Sum[i]=I2_Array_Sum[i]-0.5*I2_Array[i];
					if(I2_Array_Sum[i]<0)
					{
						I2_Array_Sum[i]=0;
					}
				}
            // �Ȼ����ѿ۴���
            // ��ĳһ�೬��
            if (I2_Array_Sum[i] >= H5_Cur)
            {
                I2_Array_Sum[i] = H5_Cur - (H_Cur << 2);
                I2_Array_Sum[i] = 0;
                // ����û�й������Ϸ���
                if (F_I_STA == 0)
                {
                    Record_data_propare();
                    if (i == 0)
                    {
                        gz_disp = cur_handle_A(I_Array_xianshi[0]); // cur_handle����Ϊʵ��Ҫ��ʾ��ֵ
                    }
                    else if (i == 1)
                    {
                        gz_disp = cur_handle_B(I_Array_xianshi[1]); // cur_handle����Ϊʵ��Ҫ��ʾ��ֵ
                    }
                    else if (i == 2)
                    {
                        gz_disp = cur_handle_C(I_Array_xianshi[2]); // cur_handle����Ϊʵ��Ҫ��ʾ��ֵ
                    }
                    Trip_Action();
                    F_record_write = 1;
                    gz_reason = trip_reason_cur;
                    // putchar(gz_reason);
                    GZ_ph = i + 1;
                    // Write_Record(trip_reason_cur,(i+1));
                    F_gz_disp = A_gl + i;

                    // д������բ��¼
                    // ����غ�բ���ܿ���
                    if (F_ia == 1)
                    {
                        F_ch = 0;
                        F_I_STA = 1;
                    }
                    // ��������غ�բ���ܹر�
                    else
                    {
                        F_I_STA = 3;
                        F_I_Lock = 1;
                        F_ch = 1;
                    }
                    // �������غ�բ
                }
                // �����ڶ����ѿ�
                /*	else if(F_I_STA == 1)//�����������ѷ���һ��,����ִ���ѿ�,ֻ�Ǽ�һ�¼�¼
                                                                {

                                                                }*/
                // �غ�բ��10s���ַ��������ѿ�
                else if (F_I_STA == 2)
                {
                    F_I_STA = 3;
                    // д������բ��¼
                    F_ch = 1;
                    Record_data_propare();
                    if (i == 0)
                    {
                        gz_disp = cur_handle_A(I_Array_xianshi[0]); // cur_handle����Ϊʵ��Ҫ��ʾ��ֵ
                    }
                    else if (i == 1)
                    {
                        gz_disp = cur_handle_B(I_Array_xianshi[1]); // cur_handle����Ϊʵ��Ҫ��ʾ��ֵ
                    }
                    else if (i == 2)
                    {
                        gz_disp = cur_handle_C(I_Array_xianshi[2]); // cur_handle����Ϊʵ��Ҫ��ʾ��ֵ
                    }
                    // if(F_trip_gl==1)
                    {
                        Trip_Action();
                    }
                    F_record_write = 1;
                    gz_reason = trip_reason_cur;
                    // putchar(gz_reason);
                    GZ_ph = i + 1;
                    // Write_Record(trip_reason_cur,(i+1));
                    F_I_Lock = 1;
                    F_gz_disp = A_gl + i; // i����˼����һ�෢����������
                }
            }
        }
    }

    // end of else

    // end of for(i=0;i<4;i++)

    F_ITrip = F_I_STA;
    // end of if(F_tb)
}

// ���������봦��
void Cur_sample_process(void)
{
    IWDG_Feed(); // ι��
    if (F_Delay == 1)
    {
        if (F_Cur == 10) // �Ժ�20ms����һ��
        {
            I_Array[0] = cur_handle_A(I_Array_xianshi[0]);
            I_Array[1] = cur_handle_B(I_Array_xianshi[1]);
            I_Array[2] = cur_handle_C(I_Array_xianshi[2]);

            if (I_MAX_tmp[0] < I_Array_xianshi[0])
            {
                I_MAX_tmp[0] = I_Array_xianshi[0];
            }
            if (I_MIN_tmp[0] > I_Array_xianshi[0])
            {
                I_MIN_tmp[0] = I_Array_xianshi[0];
            }
            if (I_MAX_tmp[1] < I_Array_xianshi[1])
            {
                I_MAX_tmp[1] = I_Array_xianshi[1];
            }
            if (I_MIN_tmp[1] > I_Array_xianshi[1])
            {
                I_MIN_tmp[1] = I_Array_xianshi[1];
            }
            if (I_MAX_tmp[2] < I_Array_xianshi[2])
            {
                I_MAX_tmp[2] = I_Array_xianshi[2];
            }
            if (I_MIN_tmp[2] > I_Array_xianshi[2])
            {
                I_MIN_tmp[2] = I_Array_xianshi[2];
            }
            //				SMG_CLK=0;
            T_I = T_I + 1;
            if (T_I == 501) // 20ms X 100 = 2S ����һ��
            {
                T_I = 0;
                I_max_process(F_Cur_m + 1);
                I_min_process(F_Cur_m + 1);
                F_Cur_m = F_Cur_m + 1;
                if (F_Cur_m >= 3)
                    F_Cur_m = 0;
            }
            if (F_powerup_re == 1)
            {
                F_Record = 1;
                F_powerup_re = 0;
            }
            F_Cur = 0;
            Cur_Process();
        }
    }
}

/*********************************************
                ©�紦����
**********************************************
Get_L(void)
signed int Get_AB(void)
signed int min(void)
void Clear_TB_array(void)
unsigned int Get_Delta_Leak(signed int tmp_a,signed int tmp_b)
void Leak_process(void)
void Quick_process(void)
void Auto_Leak_process(void)
void Normal_Leak_process(void)
**********************************************/

void Get_L(void)
{
    AD_tmp = 0;
    AD_tmp = ADC_ConvertedValue[7];
    Leak_Cur_Sum = Leak_Cur_Sum + AD_tmp;
}

void TB_leak_process(void)
{
    if (F_Leak_Delay == 0)
    {
        Lea_Cur_old = Leak_Cur_disp;
    }
    if (F_Leak_Delay == 1)
    {
        if (Leak_Cur_disp >= Lea_Cur_old)
        {
            Delta_Leak_Cur = Leak_Cur_disp - Lea_Cur_old;
        }
        else
        {
            Delta_Leak_Cur = Lea_Cur_old - Leak_Cur_disp;
        }

        if (Delta_Leak_Cur < 0)
            Delta_Leak_Cur = 0;
        if (Delta_Leak_Cur >= 40)
        {
            N_TB_T = N_TB_T + 6;
        }
        else
        {
            N_TB_T = N_TB_T - 2;
            if (N_TB_T < 0)
                N_TB_T = 0;
        }
        if (N_TB_T > N_TH)
        {
            N_TB_T = 0;
            if (isfenzha != 0)
            {
                Trip_Process();
            }
        }
        if (N_TB_T == 0)
        {
            Lea_Cur_old = Leak_Cur_disp;
        }
    }
}

void Leak_process(void)
{

    int leak_tmp = 0;
    Leak_Cur = 0;
    //	Leak_Cur=(Leak_Cur_Sum>>6)+(Leak_Cur_Sum>>7)+(Leak_Cur_Sum>>9);//0.25��
    leak_tmp = leak_handle(Leak_Cur_Sum);
    //	leak_tmp=leak_handle(Leak_xianshi_disp);
    if (leak_tmp < 0)
        Leak_Cur_disp = 0;
    else
        Leak_Cur_disp = leak_tmp;

    if (isfenzha == 0)
        F_leak_disp = 0;

    if (F_leak_disp < 2)
    {
        Leak_Cur_disp = 0;
        F_leak_disp++;
    }
    else
    {
        Leak_Cur_disp = leak_tmp;
        //				Leak_Cur_disp = 1000;
        //		Leak_Cur_disp_cal= leak_tmp;
    }
    Leak_Over_process(); // 20201202����©��澯��¼����Y

    //		Leak_Cur_disp_cal= leak_tmp;
    //		if(leak_tmp<=10) leak_tmp = 0;
    if (Leak_Cur_disp > Leak_MAX_tmp)
    {
        Leak_MAX_tmp = Leak_Cur_disp;
    }
    if (Leak_Cur_disp < Leak_MIN_tmp)
    {
        Leak_MIN_tmp = Leak_Cur_disp;
    }
    Leak_Cur_Sum = 0;
    ////	if(D_LCur==8)  //�Զ����ٵ�λ
    ////	{
    ////		Auto_Leak_process();
    ////	}
    //	else
    //	{
    Normal_Leak_process(); // 0.05 0.1 0.3 0.5 0.8 1
    //	}
    //	N_T=0 ;
    if (N_T >= N_TH)
    {
        N_T = 0;
        if ((isfenzha != 0) && (F_jiance != 1))
        {
            Trip_Process();
        }
    }
    // ����ò��������
    else
    {
        if (F_al1)
            F_al1--;
    }
    if ((F_TB_trip == 1) || (F_Special_wave == 1))
    {
        TB_leak_process();
    }
}

void Quick_process(void)
{
    if (isfenzha != 0) // �ں�բλ��
    {
        // ֻ����0.2s������10���Ŀ��ٶ���
        if (TH_LCur == 0)
        {
            Id3 = D_LCur3_Array[D_LCur];
            Id4 = D_LCur4_Array[D_LCur];
            if ((AD_result >= Id3) || (AD_result < Id4))
            {

                N_K = N_K + 2;
                // N_K=N_K+20;
                if (N_K >= 37)
                {
                    F_ks = 1;
                    N_K = 0;
                    N_T = 0;
                    if ((isfenzha != 0) && (F_jiance != 1))
                    {
                        Trip_Process();
                    }
                    // ���ٶ�����բ����,
                }
            }
            else
            {
                N_K = N_K - 2;
                if (N_K <= 0)
                    N_K = 0;
            }
        }
    }
}

void Auto_Leak_process(void)
{
    // ����ǵ�һ���ϵ�
    // F_compare�ϵ�Ϊ2,����Ϊ1

    if (F_Compare == 2)
    {
        F_Compare = 0;
        D_A_LCur = 11;
        // D_A_LCur©���Զ����ٵ�λ  //�趨����ߵ�λ
        Id1_A = D_ACur_Array[D_A_LCur];
        // ���±Ƚ�ֵ
        Id1_L = H_A_L[D_A_LCur];
        // ����Ӧ����ֵ,���������л���λ
        Id1_H = H_A_H[D_A_LCur];
        // ����Ӧ����ֵ,���������л���λ
        // putchar(D_A_LCur);
    }
    // end of if(F_Compare==2)
    if (F_Trip == 0)
    {
        // N_A_L �Զ����ټ�������
        if (N_A_L >= 12000)
        {
            D_A_LCur = D_A_LCur - 1;
            if (D_A_LCur < 0)
                D_A_LCur = 0;
            N_A_H = N_A_L = 0;
            // putchar(D_A_LCur);
            // �л���λ,����������
        }
        // �����л���λ
        if (N_A_H >= 12000)
        {
            D_A_LCur = D_A_LCur + 1;
            if (D_A_LCur >= 11)
                D_A_LCur = 11;
            N_A_H = N_A_L = 0;
            // putchar(D_A_LCur);
            // �л���λ,����������
        }
    }
    // end of if(F_Trip==0)
    // ��һ���ѿۺ�,��λ���ѿ�ǰ����1
    if (F_Trip == 2)
    {
        D_A_LCur = D_S + 1;
        if (D_A_LCur >= 11)
            D_A_LCur = 11;
        N_A_H = N_A_L = 0;
    }
    // ��������
    if (F_Trip == 3)
    {
        N_A_H = N_A_L = 0;
    }
    Id1_A = D_ACur_Array[D_A_LCur];
    // ����Ӧ��λֵ,�����ѿ�
    Id1_L = H_A_L[D_A_LCur];
    // ����Ӧ����ֵ,���������л���λ
    Id1_H = H_A_H[D_A_LCur];
    // ����Ӧ����ֵ,���������л���λ
    // �ȽϺͼ���
    if (Leak_Cur_disp >= Id1_H)
    {
        N_A_H = N_A_H + 2;
        N_A_L = N_A_L - 1;
    }
    else if (Leak_Cur_disp > Id1_L)
    {
        N_A_H = N_A_H - 1;
        N_A_L = N_A_L - 1;
    }
    else
    {
        N_A_L = N_A_L + 2;
        N_A_H = N_A_H - 1;
    }
    if (N_A_H < 0)
        N_A_H = 0;
    if (N_A_L < 0)
        N_A_L = 0;
    if (Leak_Cur_disp >= Id1_A)
        N_T = N_T + 2;
    // ���ڶ�������75%
    else if (Leak_Cur_disp < ((Id1_A - Id1_A) >> 2))
    {
        N_T = N_T - 1;
        if (N_T <= 0)
            N_T = 0;
    }
}

void Normal_Leak_process(void)
{
    Id1 = D_LCur1_Array[D_LCur];
    Id2 = D_LCur2_Array[D_LCur];

    Id45 = D_LCur45_Array[D_LCur];

    Id1_delta = D_LCur_delta_Array[D_LCur];
    N_TH = TD_LCur1_Array[TH_LCur];

    if (TH_LCur == 4) // 0.1S��λ
    {
        if (Leak_Cur_disp >= Id45)
        {
            N_T = N_T + 32;
        }
        else if (Leak_Cur_disp >= Id2)
        {
            N_T = N_T + 6;
        }
        else if (Leak_Cur_disp >= Id1)
        {
            N_T = N_T + 6;
        }
        else if (Leak_Cur_disp < (Id1 - (Id1 >> 2))) // Id1-Id2/4
        {
            N_T = N_T - 1;
            if (N_T <= 0)
                N_T = 0;
        }
    }

    else if (TH_LCur == 1) // 0.3S��λ
    {
        if (Leak_Cur_disp >= Id45)
        {
            N_T = N_T + 10;
        }
        else if (Leak_Cur_disp >= Id2)
        {
            N_T = N_T + 8;
        }
        else if (Leak_Cur_disp >= Id1)
        {
            N_T = N_T + 6;
        }
        else if (Leak_Cur_disp < (Id1 - (Id1 >> 2))) // Id1-Id2/4
        {
            N_T = N_T - 1;
            if (N_T <= 0)
                N_T = 0;
        }
    }
    else if (TH_LCur == 2) // 0.5S��λ
    {
        if (Leak_Cur_disp >= Id45)
        {
            N_T = N_T + 9;
        }
        else if (Leak_Cur_disp >= Id2)
        {
            N_T = N_T + 8;
        }
        else if (Leak_Cur_disp >= Id1)
        {
            N_T = N_T + 6;
        }
        else if (Leak_Cur_disp < (Id1 - (Id1 >> 2))) // Id1-Id2/4
        {
            N_T = N_T - 1;
            if (N_T <= 0)
                N_T = 0;
        }
    }
    else if (TH_LCur == 3) // 1S��λ
    {
        if (Leak_Cur_disp >= Id45)
        {
            N_T = N_T + 10;
        }
        else if (Leak_Cur_disp >= Id2)
        {
            N_T = N_T + 8;
        }
        else if (Leak_Cur_disp >= Id1)
        {
            N_T = N_T + 6;
        }
        else if (Leak_Cur_disp < (Id1 - (Id1 >> 2))) // Id1-Id2/4
        {
            N_T = N_T - 1;
            if (N_T <= 0)
                N_T = 0;
        }
    }

    else
    {
        if (Leak_Cur_disp >= Id45)
        {
            N_T = N_T + 12;
        }
        else if (Leak_Cur_disp >= Id2)
        {
            N_T = N_T + 8;
        }
        else if (Leak_Cur_disp >= Id1)
        {
            N_T = N_T + 6;
        }
        else if (Leak_Cur_disp < (Id1 - (Id1 >> 2))) // Id1-Id2/4
        {
            N_T = N_T - 1;
            if (N_T <= 0)
                N_T = 0;
        }
    }
}

void DLS_DLD_process(void)
{

    if (F_C_IP == 1)
    {
        if (I_Array[3] >= H_DLD_Cur)
        {
            N_DLS = N_DLS + 2;
            if (N_DLS >= 20)
            {
                N_DLS = 0;
                Record_data_propare();
                gz_disp = 999;
                // if(F_trip_gl==1)
                {
                    Trip_Action();
                }
                gz_reason = trip_reason_cur;
                GZ_ph = 1;
                F_gz_disp = A_gl;
                F_record_write = 1;
                // putchar(gz_reason);
            }
        }
        else
        {
            if (N_DLS >= 1)
            {
                N_DLS = N_DLS - 1;
            }
        }
    }
}

void Wait_selftest(void)
{
    unsigned char i;

        if (F_initialize==1)
        {
            clear_screen();
            Lcd12864_Write16CnCHAR(0, 16, 2, "��ʼ������...\r");

            factor_first_init(0);
			F_initialize=0;
			USART_LCD_Transmit(1,5);
            delay_ms(1000);
            delay_ms(1000);
			
        }
    
}

void Day_factors_clear(void)
{
    F_Cur_m = 0;
    FN_Vol = 0;

    Leak_MAX = Leak_MAX_tmp = 0;
    Leak_MIN = Leak_MIN_tmp = Id1;
    //		Leak_MIN = Leak_MIN_tmp = 10000;
    V_MAX[0] = V_MAX[1] = V_MAX[2] = 0;
    V_MAX_tmp[0] = V_MAX_tmp[1] = V_MAX_tmp[2] = 0;
    V_MIN[0] = V_MIN[1] = V_MIN[2] = 60000; // old code is 3000
    V_MIN_tmp[0] = V_MIN_tmp[1] = V_MIN_tmp[2] = 60000;

    I_MAX[0] = I_MAX[1] = I_MAX[2] = I_MAX[3] = 0;
    I_MAX_tmp[0] = I_MAX_tmp[1] = I_MAX_tmp[2] = 0;
    I_MIN[0] = I_MIN[1] = I_MIN[2] = I_MIN[3] = 60000;                 // I2 ;
    I_MIN_tmp[0] = I_MIN_tmp[1] = I_MIN_tmp[2] = I_MIN_tmp[3] = 60000; // I2 ;
}

void state_init(void)
{
    IWDG_Feed(); // ι��
    unsigned char tim_array[8];
    N_T = 0;
    //	F_asy_sta=0;
    //	F_bsy_sta=0;
    //	F_csy_sta=0;
    key_state = 0x0000;
    F_record_write = 0;
    F_anolog_trip = 0;
    F_chonghezha = 0;
    F_Vol_Re = 0;
    F_Compare = 2;
    N_Trip = 0;
    F_Delay = 0;
    F_L_Delay = 0; // ����ϵ���ٶ���
    F_Leak_Delay = 0;
    F_key = 0;
    N_K = 0;
    F_cd_set = 0;
    F_cal = 0;
    F_gz_disp = 0x0F;
    F_hezha_sta = 0;
    disp_status = 0;
    V_point = 1;
    F_Disp = 1;
    F_tingdian_V = 0;
    F_powerup_re = 1;
    F_Vsam_begin = 0;
    F_display = 0;
    F_Dataval = 0;
    F_Powerup = 0;
    N_Tingdian = 0;
    F_I_Lock = 0;
    T_64_200ms = 0;
    F_tingdian_fenzha = 0;
    N_I2[0] = N_I2[1] = N_I2[2] = N_I2[3] = 0;

    if (isfenzha == 0)
    {
        F_ZW = 0;
    }
    else
    {
        F_ZW = 1;
    }
    // clear_uart_sta();
    F_re_sta = 0;
    HAL_UART_Receive_IT(&huart3, (uint8_t *)tmp_uart_rx, 1);
    //	ds1302_read_time_uart(tim_array);
    HAL_RTC_GetTime(&hrtc, &stimestructure, RTC_FORMAT_BCD);
    HAL_RTC_GetDate(&hrtc, &sdatestructure, RTC_FORMAT_BCD);
    tim_y = sdatestructure.Year; // tim_yΪʮ���ƣ�Ҫת��������
    tim_m = sdatestructure.Month;
    tim_d = sdatestructure.Date;
    tim_h = stimestructure.Hours;
    tim_f = stimestructure.Minutes;
    tim_s = stimestructure.Seconds;
    tim_array[0] = tim_y;

    tim_array[1] = tim_m;

    tim_array[2] = tim_d;

    tim_array[3] = tim_h;

    tim_array[4] = tim_f;

    tim_array[5] = tim_s;
    old_day = tim_array[2];
    //	Day_factors_clear();//������Ҫ�޸ģ���ȡ��ǰ��¼�Ϳ�����ɵ���������ݲ���?
}

void Cur_quick_protect(void)
{
    if ((TT_1 <= 63) && (F_Sample == 1))
    {
        Get_A_C();

        Get_B_C();

        Get_C_C();
    }
    TT_1 = TT_1 + 1;
    if ((TT_1 == 16) && (F_Sample == 0)) // ��ʱ10ms
    {
        F_Sample = 1;
        TT_1 = 0;
    }
    if (TT_1 >= 64)
    {
        I_Array_action[0] = A_C_Sum; // ��������
        I_Array_action[1] = B_C_Sum;
        I_Array_action[2] = C_C_Sum;
        D3_A_Quick_Process();

        D3_B_Quick_Process();

        D3_C_Quick_Process();
        TT_1 = 0;
        A_C_Sum = 0;
        B_C_Sum = 0;
        C_C_Sum = 0;
        ;
        T_64_1000ms++;
        //		if(T_64_1000ms==1) //��ʱ40ms
        //		{
        //			F_Sample=1;
        //		}
        if (T_64_1000ms == 100)
        {
            N_B3D = 0;
            N_A3D = 0;
            N_C3D = 0;
            N_B2D = 0;
            N_A2D = 0;
            N_C2D = 0;
            T_64_1000ms = 0;
            F_quick_protect = 1;
            //				isfenzha=0;
        }
    }
}
void D3_A_Quick_Process(void)
{
    if (F_ip_3 == 1)
    {

        if ((cur_actionhandle_A(I_Array_action[0])) >= I3)
        {
            N_A3D = N_A3D + 2;
            // N_K=N_K+20;
            // 2014��9��10������ٶ����󶯣��ӳ�����ʱ��19 �޸�Ϊ25
            if (N_A3D >= 1) // һ������12���㼰��ΪӦ�ö���
            {
                N_A3D = 0;

                gz_reason = trip_reason_3D_cur;
                GZ_ph = 0x01;

                gz_disp = (cur_actionhandle_A(I_Array_action[0])); // ���㣬�˴�Ӧ���޸�
                Trip_ON;
                //				Write_Quick_Record(gz_reason,GZ_ph);
            }
        }
        //		else
        //		{

        //		}
    }

    if (F_ip == 1)
    {
        //		I2_1=(I2*7>>3)+(I2>>5);//0.9��
        N_T_TH = N_TH_DL[TH_DL];
        if ((cur_handle_A(I_Array_action[0])) >= I2)
        {
            N_A2D = N_A2D + 2;
            // N_K=N_K+20;
            // 2014��9��10������ٶ����󶯣��ӳ�����ʱ��19 �޸�Ϊ25
            if (N_A2D >= N_T_TH) // һ������12���㼰��ΪӦ�ö���
            {
                {
                    N_A2D = 0;
                    gz_reason = trip_reason_short;
                    GZ_ph = 0x01;
                    gz_disp = (cur_handle_A(I_Array_action[0])); // ���㣬�˴�Ӧ���޸�
                    Trip_ON;
                    //					Write_Quick_Record(gz_reason,GZ_ph);
                }
            }
        }
        else
        {
        }
    }
}
void D3_B_Quick_Process(void)
{
    if (F_ip_3 == 1)
    {
        if ((cur_actionhandle_B(I_Array_action[1])) >= I3)
        {
            N_B3D = N_B3D + 2;
            if (N_B3D >= 1) // һ������12���㼰��ΪӦ�ö���
            {
                N_B3D = 0;
                {
                    gz_reason = trip_reason_3D_cur;
                    GZ_ph = 0x02;
                    gz_disp = (cur_actionhandle_B(I_Array_action[1])); // ���㣬�˴�Ӧ���޸�
                    Trip_ON;
                    //					Write_Quick_Record(gz_reason,GZ_ph);
                }
            }
        }
        else
        {
            //				N_B3D=N_B3D-1 ;
            //				if(N_B3D<=0)
            //				N_B3D=0 ;
        }
    }
    if (F_ip == 1)
    {
        //		I2_1=(I2*7>>3)+(I2>>5);//0.9��
        N_T_TH = N_TH_DL[TH_DL];

        if ((cur_handle_B(I_Array_action[1])) >= I2)
        {
            N_B2D = N_B2D + 2;

            if (N_B2D >= N_T_TH) // һ������12���㼰��ΪӦ�ö���
            {
                {
                    N_B2D = 0;
                    gz_reason = trip_reason_short;
                    GZ_ph = 0x02;
                    gz_disp = (cur_handle_B(I_Array_action[1])); // ���㣬�˴�Ӧ���޸�
                    Trip_ON;
                    //					Write_Quick_Record(gz_reason,GZ_ph);
                }
            }
        }
        else
        {
            //				N_B2D=N_B2D-1 ;
            //				if(N_B2D<=0)
            //				N_B2D=0 ;
        }
    }
}

void D3_C_Quick_Process(void)
{
    if (F_ip_3 == 1)
    {
        if ((cur_actionhandle_C(I_Array_action[2])) >= I3)
        {
            N_C3D = N_C3D + 2;
            if (N_C3D >= 1) // һ������12���㼰��ΪӦ�ö���
            {
                {
                    N_C3D = 0;
                    gz_reason = trip_reason_3D_cur;
                    GZ_ph = 0x04;
                    gz_disp = (cur_actionhandle_C(I_Array_action[2])); // ���㣬�˴�Ӧ���޸�
                    Trip_ON;
                    //					Write_Quick_Record(gz_reason,GZ_ph);
                }
            }
        }
        //		else
        {
        }
    }
    if (F_ip == 1)
    {
        //		  I2_1=(I2*7>>3)+(I2>>5);//0.9��
        N_T_TH = N_TH_DL[TH_DL];
        if ((cur_handle_C(I_Array_action[2])) >= I2)
        {
            N_C2D = N_C2D + 2;
            if (N_C2D >= N_T_TH) // һ������12���㼰��ΪӦ�ö���
            {
                N_C2D = 0;
                gz_reason = trip_reason_short;
                GZ_ph = 0x04;
                gz_disp = (cur_handle_C(I_Array_action[2])); // ���㣬�˴�Ӧ���޸�
                Trip_ON;
                //				Write_Quick_Record(gz_reason,GZ_ph);
            }
        }
        else
        {
        }
    }
}

void Power_Sample_A(void)
{
    I_A_Sum = 0;
		//U_A_Sum = 0;
	  AD_tmp_V_Power[0]=0;
    AD_tmp_V_Power[0]=ADC_ConvertedValue[3];
		U_A_Sum += AD_tmp_V_Power[0];


    /*******************����************************************/
    for (int I_Count = 0; I_Count < 2; I_Count++)
    {
        AD_tmp_I_Power[0] = 0;
        AD_tmp_I_Power[0] = ADC_ConvertedValue[1]; // �����ɼ�
        //		AD_tmp_I_Power[0]=200;//�����ɼ�
        I_A_Sum += AD_tmp_I_Power[0];
    }
    AD_tmp_Power[0] = I_A_Sum >> 1;
    A_C_Sum += I_A_Sum >> 1;
		
		

    //		for(int I_Count=0;I_Count<2;I_Count++)
    //	{
    //		AD_tmp_I_PowerA[I_Count]=ADC_ConvertedValue[1];
    //	}
    //	if(AD_tmp_I_PowerA[1]>4*AD_tmp_I_PowerA[0])//�����һ�������ǰһ����4���͸�ֵǰһ����
    //	{
    //		AD_tmp_I_PowerA[1]=AD_tmp_I_PowerA[0];
    //	}
    //	else
    //	{
    //		AD_tmp_I_PowerA[1]=AD_tmp_I_PowerA[1];
    //	}
    //	I_A_Sum=AD_tmp_I_PowerA[0]+AD_tmp_I_PowerA[1];
    //	AD_tmp_Power[0]=I_A_Sum>>1;
    //	A_C_Sum+=I_A_Sum>>1;
}
void Power_Sample_B(void)
{
    I_B_Sum = 0;
		//U_B_Sum = 0;
    
    AD_tmp_V_Power[1]=0;
    AD_tmp_V_Power[1]=ADC_ConvertedValue[4];
		U_B_Sum += AD_tmp_V_Power[1];

    /*****************��ѹ******************/
    /*
    if(AD_tmp_V_Power[1]<0)
    {
        AD_tmp_V_Power[1]=-AD_tmp_V_Power[1];
    }
    else
    {
        AD_tmp_V_Power[1]=AD_tmp_V_Power[1];
    }
		*/
    /*******************����*******************/
    for (int I_Count = 0; I_Count < 2; I_Count++)
    {
        AD_tmp_I_Power[1] = 0;
        AD_tmp_I_Power[1] = ADC_ConvertedValue[2];
        I_B_Sum += AD_tmp_I_Power[1];
    }
    AD_tmp_Power[1] = I_B_Sum >> 1;
    B_C_Sum += I_B_Sum >> 1;
    //		for(int I_Count=0;I_Count<2;I_Count++)
    //	{
    //		AD_tmp_I_PowerB[I_Count]=ADC_ConvertedValue[2];
    //	}
    //	if(AD_tmp_I_PowerB[1]>4*AD_tmp_I_PowerB[0])//�����һ�������ǰһ����4���͸�ֵǰһ����
    //	{
    //		AD_tmp_I_PowerB[1]=AD_tmp_I_PowerB[0];
    //	}
    //	else
    //	{
    //		AD_tmp_I_PowerB[1]=AD_tmp_I_PowerB[1];
    //	}
    //	I_B_Sum=AD_tmp_I_PowerB[0]+AD_tmp_I_PowerB[1];
    //	AD_tmp_Power[1]=I_B_Sum>>1;
    //	B_C_Sum+=I_B_Sum>>1;
}

void Power_Sample_C(void)
{
    I_C_Sum = 0;
		//U_C_Sum = 0;
	  AD_tmp_V_Power[2]=0;
    AD_tmp_V_Power[2]=ADC_ConvertedValue[5];
		U_C_Sum += AD_tmp_V_Power[2];
    /*
    AD_tmp_V_Power[2]=0;
    AD_tmp_V_Power_Zero[2]=0;
    AD_tmp_V_Power[2]=ADC_ConvertedValue[6]-ADC_ConvertedValue[7];
    AD_tmp_V_Power_Zero[2]=AD_tmp_V_Power[2];//��������ݲɼ�����

    if(AD_tmp_V_Power[2]<0)
    {
        AD_tmp_V_Power[2]=-AD_tmp_V_Power[2];
    }
    else
    {
        AD_tmp_V_Power[2]=AD_tmp_V_Power[2];
    }
*/
    /**************����***************************/
    for (int I_Count = 0; I_Count < 2; I_Count++) // �˲�
    {
        AD_tmp_I_Power[2] = 0;
        AD_tmp_I_Power[2] = ADC_ConvertedValue[6];
        I_C_Sum += AD_tmp_I_Power[2];
    }
    AD_tmp_Power[2] = I_C_Sum >> 1;
    C_C_Sum += I_C_Sum >> 1;
    //		for(int I_Count=0;I_Count<2;I_Count++)
    //	{
    //		AD_tmp_I_PowerC[I_Count]=ADC_ConvertedValue[3];
    //	}
    //	if(AD_tmp_I_PowerC[1]>4*AD_tmp_I_PowerC[0])//�����һ�������ǰһ����4���͸�ֵǰһ����
    //	{
    //		AD_tmp_I_PowerC[1]=AD_tmp_I_PowerC[0];
    //	}
    //	else
    //	{
    //		AD_tmp_I_PowerC[1]=AD_tmp_I_PowerC[1];
    //	}
    //	I_C_Sum=AD_tmp_I_PowerC[0]+AD_tmp_I_PowerC[1];
    //	AD_tmp_Power[2]=I_C_Sum>>1;
    //	C_C_Sum+=I_C_Sum>>1;
}
////****************ԭ���¶Ȳɼ�����***************/

void Temp_Sample(void) // �¶Ȳɼ�
{
    Tem_Array_AD[0] = ADC_ConvertedValue[10] / 1;
    Tem_Array_AD[1] = ADC_ConvertedValue[11] / 1;
    Tem_Array_AD[2] = ADC_ConvertedValue[9] / 1;
    Tem_Array_AD[3] = ADC_ConvertedValue[8] / 1;
    Tem_Array_AD[4] = ADC_ConvertedValue[4] / 1;
    Tem_Array_AD[5] = ADC_ConvertedValue[5] / 1;
    Tem_Array_AD[6] = ADC_ConvertedValue[6] / 1;
    Tem_Array_AD[7] = ADC_ConvertedValue[7] / 1;
    int i;
    for (i = 0; i < 8; i++)
    {
        if (Tem_Array_AD[i] <= 1228)
        {
            Tem_value[i] = 135 - (Tem_Array_AD[i] * 7 / 100);
        }
        else if (Tem_Array_AD[i] <= 4160)
        {
            Tem_value[i] = 64 - (Tem_Array_AD[i] * 1 / 65);
        }
        else
        {
            Tem_value[i] = 0;
        }
    }
}

/*********23-12-8zzz�¶Ȳɼ�����*****/
// void Temp_Sample(unsigned int i)//�¶Ȳɼ�
//{
//	int I;
//	if(i>=5) I=i+3;
//	Tem_Array_AD[i]=ADC_ConvertedValue[I+7]/1;    ///i=1,2,3,4,5,6,7,8,,,I��Ӧ,1,2,3,4,8 9 10 11,,,,I+7��Ӧ 8 9 10 11 15 16 17 18
//		if(Tem_Array_AD[i]<=1228)
//		{
//		Tem_value[i] = 135-(Tem_Array_AD[i]*7/100);
//		}
//		else if(Tem_Array_AD[i]<=4160)
//		{
//		Tem_value[i] = 64-(Tem_Array_AD[i]*1/65);
//		}
//		else
//		{
//		 Tem_value[i] =0;
//		}
// }

// uint16_t AD_GET()
//{
//     //����ADC1
//		HAL_ADC_Start(&hadc1);
//     //�ȴ�ADCת����ɣ���ʱΪ50ms
//     HAL_ADC_PollForConversion(&hadc1,50);
//     //�ж�ADC�Ƿ�ת���ɹ�
//     if(HAL_IS_BIT_SET(HAL_ADC_GetState(&hadc1),HAL_ADC_STATE_REG_EOC))
//			{
//          //��ȡֵ
//        return HAL_ADC_GetValue(&hadc1);
//			}
//			 //HAL_ADC_Stop(&hadc1);
//     return 0;
// }

/*
ch 6: 12V��ѹ
ch 8: B����
ch 9: C����
ch 10: A��ѹ
ch 11: B��ѹ
ch 12: C��ѹ
ch 14: A����
ch 15: ©��
*/
unsigned int get_adc(unsigned int ch)
{

    ADC_ChannelConfTypeDef _adc;
    _adc.Channel = ch;
    _adc.Rank = 1;
    _adc.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;

    if (HAL_ADC_ConfigChannel(&hadc1, &_adc) != HAL_OK)
    {
        Error_Handler();
    }

    // ���� ADC ת��
    if (HAL_ADC_Start(&hadc1) != HAL_OK)
    {
        Error_Handler();
    }

    // �ȴ� ADC ת�����
    HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);

    // ��ȡ ADC ת��ֵ
    uint16_t adc_value = HAL_ADC_GetValue(&hadc1);

    return adc_value;
}

// unsigned int get_adc(unsigned int ch)
//{

//	ADC_ChannelConfTypeDef _adc;

//	//	_adc.Channel=ch;
//	//	_adc.Rank=1;
////	_adc.SamplingTime = ADC_SAMPLETIME_7CYCLES_5; // ADC

//	//_adc.Rank = ADC_RANK_CHANNEL_NUMBER;
////	_adc.Rank = 2;

//	switch (ch) // ����ҳ�����PgDnֵ�����ж�Ӧҳ��Ĵ���
//	{

//	case 0:
//		_adc.Channel = ADC_CHANNEL_6;
//		break;
//	case 1:
//		_adc.Channel = ADC_CHANNEL_8;
//		break;
//	case 2:
//		_adc.Channel = ADC_CHANNEL_9;
//		break;
//	case 3:
//		_adc.Channel = ADC_CHANNEL_10;
//		break;
//	case 4:
//		_adc.Channel = ADC_CHANNEL_11;
//		break;
//	case 5:
//		_adc.Channel = ADC_CHANNEL_12;
//		break;
//	case 6:
//		_adc.Channel = ADC_CHANNEL_14;
//		break;
//	case 7:
//		_adc.Channel = ADC_CHANNEL_15;
//		break;
//	default:;
//		break;
//	}

//	HAL_ADC_ConfigChannel(&hadc1, &_adc);
//	if (HAL_ADC_ConfigChannel(&hadc1, &_adc) != HAL_OK)
//	{
//		Error_Handler();
//	}

//	HAL_ADC_Start(&hadc1);
//	HAL_ADC_PollForConversion(&hadc1, 0xffff);
//	if (HAL_IS_BIT_SET(HAL_ADC_GetState(&hadc1), HAL_ADC_STATE_REG_EOC)) // �����ж�ת����ɱ�־λ�Ƿ�����,HAL_ADC_STATE_REG_EOC��ʾת����ɱ�־λ��ת�����ݿ���
//	{
//		// ��ȡADCת�����ݣ�����Ϊ12λ���鿴�����ֲ��֪���Ĵ���Ϊ16λ�洢ת�����ݣ������Ҷ��룬��ת�������ݷ�ΧΪ0~2^12-1,��0~4095.
//		return (unsigned int)HAL_ADC_GetValue(&hadc1);
//	}
//	return 0;
//}

// ��ʱ��3�жϷ������
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) // TIM3�ж�
{

    if (htim->Instance == htim6.Instance) // ���TIM3�����жϷ������
    {
			//HAL_ADC_Start_DMA(&hadc1,ADC_ConvertedValue,8);
//			HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
//        // HAL_ADC_Stop(&hadc1);
//        // HAL_ADCEx_Calibration_Start(&hadc1);
//        // HAL_ADC_Start_DMA(&hadc1,ADC_ConvertedValue,8);

// HAL_GPIO_TogglePin(LED_GPIO_Port,LED_Pin);

//        // HAL_ADCEx_Calibration_Start(&hadc1);

//        u16 AD_Vol_Check;

//  		HAL_GPIO_WritePin(GPIOB,LED_Pin,GPIO_PIN_SET);
//        ADC_ConvertedValue[0] = get_adc(6);
//        ADC_ConvertedValue[1] = get_adc(8);
//        ADC_ConvertedValue[2] = get_adc(9);
//        ADC_ConvertedValue[3] = get_adc(10);
//        ADC_ConvertedValue[4] = get_adc(11);
//        ADC_ConvertedValue[5] = get_adc(12);
//        ADC_ConvertedValue[6] = get_adc(14);
//        ADC_ConvertedValue[7] = get_adc(15);
			

//        //		for (uint8_t i = 0; i < 8; i++)  //�˷������У��ڶ�ʱ���������޷���ɣ��д����
//        //		{
//        //			ADC_ConvertedValue[i] = get_adc(i);
//        //		}
//        //		HAL_ADC_Stop(&hadc1);

        if (F_quick_protect == 0) // �ϵ�������ٱ���
        {
            Cur_quick_protect();
        }
        else
        {

            if (T <= 63)
            {
                if (Low_vol_begin == 1)
                {
                    if ((F_trip_sy == 1) && (T_delay >= 150))
                    {
                        low_vol_prcoess();  
                    }
                }
               
                Power_Sample_A();  //�����ɼ��ͷ��µ������ɼ�
                Power_Sample_B();
                Power_Sample_C();
               
                Get_L();
                Switch_pos_judge();
                Flag_Updata();
                if (T == 32)
                {
                    if ((F_hezha_state == 1) && (isfenzha != 0)) // ��բ�ɹ�
                    {
                        F_hezha_state = 0;
                        F_hezha_delay = 1;
                        F_ZW = 1;
                        F_gz = 0x00;
                        F_gz_disp = 0x0F;
                        F_disp_h = 0;
                        F_Dataval = 0;
                        F_guocheng = 0;
                        F_hezha_sta = 0;
                        F_Disp = 1;
                        F_initial_lcd_hezha = 1;
                    }
                    if ((F_fenzha_state == 1) && (isfenzha == 0)) // ��բ�ɹ�
                    {
                        stop;
                        F_disp_tr = 0;
                        F_fenzha_state = 0;
                        F_ZW = 0;
                        F_guocheng = 0;
                        N_fenzha_time = 0;
                        F_Disp = 1;
                        key_state = 0;
                    }
                    if (LEDA_FLAG == 1)
                    {
                        if (Lcd_Count <= 3000)
                            Lcd_Count++;
                        else
                        {
                            // LEDA_OFF;
                            LEDA_FLAG = 0;
                            Lcd_Count = 0;
                        }
                    }
                    Conter_Updata();
                    // F_HT7038_Read=1;
                }
                T = T + 1;

                if (T >= 64)
                {

                    if (F_Leak_Delay == 1)
                    {
                        F_L_AD++;
                        Leak_xianshi_sum += Leak_Cur_Sum;
                        if (F_L_AD >= 16)
                        {
                            F_L_AD = 0;
                            Leak_xianshi_disp = Leak_xianshi_sum >> 4;
                            Leak_xianshi_sum = 0;
                        }
                        Leak_Cur_disp_temp = Leak_Cur_Sum;
                        Leak_process();
                    }

                    F_C_AD++;
                    A_C_Sum_disp += A_C_Sum;
                    B_C_Sum_disp += B_C_Sum;
                    C_C_Sum_disp += C_C_Sum;
                    if (F_C_AD >= 64)
                    {
                        I_I_Array_xianshi[0] = A_C_Sum_disp >> 6;
                        I_I_Array_xianshi[1] = B_C_Sum_disp >> 6;
                        I_I_Array_xianshi[2] = C_C_Sum_disp >> 6;
                        A_C_Sum_disp = 0;
                        B_C_Sum_disp = 0;
                        C_C_Sum_disp = 0;
                        F_C_AD = 0;
                    }
                    I_Array_xianshi[0] = A_C_Sum; // ��������
                    I_Array_xianshi[1] = B_C_Sum;
                    I_Array_xianshi[2] = C_C_Sum;
										
										U_Array_xianshi[0] = U_A_Sum;  //���µ���ѹ
										U_Array_xianshi[1] = U_B_Sum;
										U_Array_xianshi[2] = U_C_Sum;
										

                    D3_A_BH_Process();
                    D3_B_BH_Process();
                    D3_C_BH_Process();
                    Num_Cur_protect++;
                    if (Num_Cur_protect >= 5) // ÿ100ms���س���ʱ�����Ƚϴ���
                    {
                        Num_Cur_protect = 0;
                        F_Cur = 10;
                    }
                    A_C_Sum = 0;
                    B_C_Sum = 0;
                    C_C_Sum = 0;
										U_A_Sum = 0;
										U_B_Sum = 0;
										U_C_Sum = 0;

                   // Temp_Sample();

                    T = 0;

                    Num_tem_protect++;
                    if (Num_tem_protect >= 10) // 20ms��10=200ms
                    {
                        F_tem = 1; //
                        Num_tem_protect = 0;
                    }
                }
                //  HAL_GPIO_WritePin(GPIOC,TRIP_Pin,GPIO_PIN_RESET);
            }
        }
				//HAL_GPIO_WritePin(GPIOB,LED_Pin,GPIO_PIN_RESET);
    }
}

void Lackzero_judge(void)
{
    //	QL_A_tmp=((A_V_Sum1*V_A_slope[0])>>10)/AD_tmp_VA_Max;

    if ((AQL_Judge_tmp <= 1850) || (AQL_Judge_tmp >= 2100))
    {

        N_QL_A = N_QL_A + 1;
        if (N_QL_A >= 3)
        {
            F_QLA_TRIP = 1;
            N_QL_A = 0;
        }
    }
    else
    {
        N_QL_A--;
        F_QLA_TRIP = 0;
        if (N_QL_A < 0)
            N_QL_A = 0;
    }
    if ((BQL_Judge_tmp <= 1850) || (BQL_Judge_tmp >= 2100))
    {

        N_QL_B = N_QL_B + 1;
        if (N_QL_B >= 3)
        {
            F_QLB_TRIP = 1;
            N_QL_B = 0;
        }
    }
    else
    {
        N_QL_B--;
        F_QLB_TRIP = 0;
        if (N_QL_B < 0)
            N_QL_B = 0;
    }
    if ((CQL_Judge_tmp <= 1850) || (CQL_Judge_tmp >= 2100))
    {

        N_QL_C = N_QL_C + 1;
        if (N_QL_C >= 3)
        {
            F_QLC_TRIP = 1;
            N_QL_C = 0;
        }
    }
    else
    {
        N_QL_C--;
        F_QLC_TRIP = 0;
        if (N_QL_C < 0)
            N_QL_C = 0;
    }
    if ((F_QLA_TRIP == 1) && (F_QLB_TRIP == 1) && (F_QLC_TRIP == 1))
    {
        F_QLA_TRIP = 0;
        F_QLB_TRIP = 0;
        F_QLC_TRIP = 0;
        if (isfenzha != 0)
            F_QL_TRIP = 1;
        else
        {
            F_QL_TRIP = 0;
        }
    }
    else
    {
        F_QL_TRIP = 0;
    }
}
// ����ʱ��
void Run_time_process(void)
{
    IWDG_Feed();         // ι��
    if (F_run_time == 1) // ������ʱ�� 1min
    {
        F_run_time = 0;
        Sum_run_time = Sum_run_time + 1;
        if (Sum_run_time > 99999999)
        {
            Sum_run_time = 0;
        }
        DectoBCD(T_run_time_array, Sum_run_time, 4);
        MODIFY_EEP_W(Addr_protect_time, T_run_time_array, 4, 0xA0);
        IWDG_Feed(); // ι��
    }
}

void uart_com_process(void)
{

    unsigned char sta;
    // ���ڴ���
    if (F_Dataval_lcd == 1)
    {
        UART_LCD_process();
        F_Dataval_lcd = 0;
				F_lcd_realtime=0;  //���ʵʱ���ݷ��͵ı�־λ����ֹ֡����
    }
    if (F_Dataval == 1)
    {
        //clear_screen();

        // RS485_TX_EN; // ����Ϊ����ģʽ
        delay_ms(5);
        sta = frame_check();
        F_debug = 1;
        if (sta == 0)
        {
            UART_process();
        }
        F_Dataval = 0;
        //		clear_uart_sta();
        delay_ms(5);
        delay_ms(5);
        // RS485_RX_EN; // ����Ϊ����ģʽ
    }
}

unsigned char read_tingdian(void)
{
    unsigned char tmp, tingdian[2];
    EEPROM_R(Addr_tingdian, tingdian, 1, 0xA0);
    tmp = tingdian[0];
    tingdian[0] = 0x00;
    return tmp;
}
void clear_tingdian(void)
{
    unsigned char tingdian[2];
    tingdian[0] = 0x00;
    MODIFY_EEP_W(Addr_tingdian, tingdian, 1, 0xA0);
}

void long_process(void)
{
    IWDG_Feed(); // ι��
    long_key_temp = get_key();
    if (long_key_temp != 0)
    {
        //		if(F_Corr==0)
        //		{
        N_key_temp++;
        if ((N_key_temp > 100) && (long_key_temp != 0x07))
        {
            //				if(F_Corr==0)
            {
                long_key_process(long_key_temp);
                N_key_temp = 0;
            }
        }
        //	  }
        //		if((N_key_temp>120)&&(long_key_temp==0x07))//�������λ������Ҫʱ�����
        //		{
        //			long_key_process(long_key_temp);
        //			N_key_temp = 0;
        //		}
    }
    if (long_key_temp == 0)
    {
        N_key_temp = N_key_temp - 2;
        if (N_key_temp < 0)
        {
            N_key_temp = 0;
        }
    }
}

void Get_A_C(void)
{
    AD_tmp = 0;
    AD_tmp = ADC_ConvertedValue[1];
    A_C_Sum = A_C_Sum + AD_tmp;
}
void Get_B_C(void)
{
    AD_tmp = 0;
    AD_tmp = ADC_ConvertedValue[2];
    B_C_Sum = B_C_Sum + AD_tmp;
}

void Get_C_C(void)
{
    AD_tmp = 0;
    AD_tmp = ADC_ConvertedValue[6];
    C_C_Sum = C_C_Sum + AD_tmp;
}

void DW_3D_E2_read(void)
{
    IWDG_Feed(); // ι��
    unsigned char array_temp[26];

    // ��������*********************/
    EEPROM_R(Addr_I_2d, array_temp, 1, 0xA0);
    F_ip = array_temp[0];
    EEPROM_R(Addr_I_3d, array_temp, 1, 0xA0); // 17.6.21��
    F_ip_3 = array_temp[0];
    /*******************�����֣�������λ���Ǽܵȼ�����Ƿѹ��λ*********************/
    EEPROM_R(Addr_crtl_word1, ctrlword, 5, 0xA0); // ��5��������
    //	delay_ms(5);
    ctrlword4_analyze();
    EEPROM_R(Addr_DD_LL, array_temp, 1, 0xA0);
    F_DD_L[0] = array_temp[0];
    if (F_DD_L[0] == 1)
    {
        F_trip_ld = 0;
        ctrlword[3] &= 0xFC;
        MODIFY_EEP_W(Addr_crtl_word4, &ctrlword[3], 1, 0xA0);
        ctrlword4_analyze();
        F_DD_L[0] = 0;
    }
    else
    {
        F_DD_L[0] = 0;
    }
    MODIFY_EEP_W(Addr_DD_LL, F_DD_L, 1, 0xA0);
    EEPROM_R(Addr_D_Cur, array_temp, 1, 0xA0);
    D_Cur = array_temp[0];
    EEPROM_R(Addr_D2_Cur, array_temp, 1, 0xA0);
    D2_Cur = array_temp[0];
    EEPROM_R(Addr_D3_Cur, array_temp, 1, 0xA0);
    D3_Cur = array_temp[0];

    EEPROM_R(Addr_D2_Time, array_temp, 1, 0xA0);
    TH_DL = array_temp[0];
    EEPROM_R(Addr_CurLong_Time, array_temp, 1, 0xA0);
    TH_Long_Cur = array_temp[0];
    if (TH_Long_Cur > 7)
    {
        TH_Long_Cur = 0;
    }
    // putchar(D_Cur);
    EEPROM_R(Addr_Type_Cur, array_temp, 1, 0xA0);
    Type_Cur = array_temp[0];
    if (Type_Cur > 4)
    {
        Type_Cur = 0;
    }
    if ((Type_Cur == 0) && (D_Cur >= 9))
    {
        D_Cur = 9;
    }
    if ((Type_Cur == 1) && (D_Cur >= 19))
    {
        D_Cur = 19;
    }
    if ((Type_Cur == 2) && (D_Cur >= 12))
    {
        D_Cur = 12;
    }
    if ((Type_Cur == 3) && (D_Cur >= 14))
    {
        D_Cur = 14;
    }
    if ((Type_Cur == 4) && (D_Cur >= 7))
    {
        D_Cur = 6;
    }
    Cur_Switch(Type_Cur);
}

void D3_A_BH_Process(void)

{

    if (isfenzha != 0) // �ں�բλ��
    {
        if (F_ip_3 == 1)
        {
            if ((cur_actionhandle_A(I_Array_xianshi[0])) >= I3)
            {
                N_A3D = N_A3D + 2;
                // N_K=N_K+20;
                if (N_A3D >= 3) // һ������12���㼰��ΪӦ�ö���
                {
                    //						if(F_I_STA==0)
                    {
                        F_ch = 0;
                        Record_data_propare();                            // ��Ҫд���©�磬��ѹ������ֵ׼������д��
                        gz_disp = cur_actionhandle_A(I_Array_xianshi[0]); // ���㣬�˴�Ӧ���޸�
                        // if(F_trip_gl==1)
                        {
                            Trip_Action();
                        }
                        gz_reason = trip_reason_3D_cur;
                        F_record_write = 1;
                        F_3d_trip = 1;
                        // putchar(gz_reason);
                        GZ_ph = 1;
                        // Write_Record(trip_reason_cur,(i+1));
                        F_gz_disp = A_gl;
                        if (F_ia == 1) // F_ia  ©���غ�բ��־λ
                        {
                            F_I_STA = 1;
                            F_ch = 0;
                            F_I_Lock = 0;
                        }
                        // ���©���غ�բ���ܿ�
                        else
                        {
                            F_ch = 1;
                            F_I_STA = 3; // ֱ����3
                            F_I_Lock = 1;
                        }
                        // �������غ�բ
                    }
                    // �����ڶ����ѿ�
                    if (F_I_STA == 2)
                    {
                        F_ch = 1;
                        gz_disp = 999; // ���㣬�˴�Ӧ���޸�
                        Record_data_propare();
                        // if(F_trip_gl==1)
                        {
                            Trip_Action();
                        }

                        F_record_write = 1;
                        gz_reason = trip_reason_3D_cur;
                        // putchar(gz_reason);
                        GZ_ph = 1;
                        // Write_Record(trip_reason_cur,1);
                        F_I_STA = 3;
                        F_I_Lock = 1;

                        F_gz_disp = A_gl;

                        // д������բ��¼
                    }
                }
            }
            else
            {
                N_A3D = N_A3D - 1;
                if (N_A3D <= 0)
                    N_A3D = 0;
            }
        }
        if (F_ip == 1)
        {
            N_T_TH = N_TH_DL[TH_DL];
            if ((cur_handle_A(I_Array_xianshi[0])) >= I2)
            {
                N_A2D = N_A2D + 2;
                // N_K=N_K+20;
                // 2014��9��10������ٶ����󶯣��ӳ�����ʱ��19 �޸�Ϊ25
                if (N_A2D >= N_T_TH) // һ������12���㼰��ΪӦ�ö���
                {
                    //						if(F_I_STA==0)
                    {
                        F_ch = 0;
                        Record_data_propare();                      // ��Ҫд���©�磬��ѹ������ֵ׼������д��
                        gz_disp = cur_handle_A(I_Array_xianshi[0]); // ���㣬�˴�Ӧ���޸�
                        // if(F_trip_gl==1)
                        {
                            Trip_Action();
                        }
                        gz_reason = trip_reason_short;
                        F_record_write = 1;
                        // putchar(gz_reason);
                        GZ_ph = 1;
                        // Write_Record(trip_reason_cur,(i+1));
                        F_gz_disp = A_gl;
                        if (F_ia == 1) // F_ia  ©���غ�բ��־λ
                        {
                            F_I_STA = 1;
                            F_ch = 0;
                            F_I_Lock = 0;
                        }
                        // ���©���غ�բ���ܿ�
                        else
                        {
                            F_ch = 1;
                            F_I_STA = 3; // ֱ����3
                            F_I_Lock = 1;
                        }
                        // �������غ�բ
                    }
                    // �����ڶ����ѿ�
                    if (F_I_STA == 2)
                    {
                        F_ch = 1;
                        gz_disp = 997; // ���㣬�˴�Ӧ���޸�
                        Record_data_propare();
                        // if(F_trip_gl==1)
                        {
                            Trip_Action();
                        }

                        F_record_write = 1;
                        gz_reason = trip_reason_short;
                        // putchar(gz_reason);
                        GZ_ph = 1;
                        // Write_Record(trip_reason_cur,1);
                        F_I_STA = 3;
                        F_I_Lock = 1;

                        F_gz_disp = A_gl;

                        // д������բ��¼
                    }
                }
            }
            else
            {
                N_A2D = N_A2D - 1;
                if (N_A2D <= 0)
                    N_A2D = 0;
            }
        }
    }
}

void D3_B_BH_Process(void)
{
    if (isfenzha != 0) // �ں�բλ��
    {
        if (F_ip_3 == 1)
        {
            if ((cur_actionhandle_B(I_Array_xianshi[1])) >= I3)
            {
                N_B3D = N_B3D + 2;
                // N_K=N_K+20;
                if (N_B3D >= 3) // һ������12���㼰��ΪӦ�ö���
                {
                    //						if(F_I_STA==0)
                    {
                        F_ch = 0;
                        Record_data_propare();                            // ��Ҫд���©�磬��ѹ������ֵ׼������д��
                        gz_disp = cur_actionhandle_B(I_Array_xianshi[1]); // ���㣬�˴�Ӧ���޸�
                        // if(F_trip_gl==1)
                        {
                            Trip_Action();
                        }
                        gz_reason = trip_reason_3D_cur;
                        F_record_write = 1;
                        // putchar(gz_reason);
                        GZ_ph = 2;
                        // Write_Record(trip_reason_cur,(i+1));
                        F_gz_disp = A_gl + 1;
                        if (F_ia == 1) // F_ia  ©���غ�բ��־λ
                        {
                            F_I_STA = 1;
                            F_ch = 0;
                            F_I_Lock = 0;
                        }
                        // ���©���غ�բ���ܿ�
                        else
                        {
                            F_ch = 1;
                            F_I_STA = 3; // ֱ����3
                            F_I_Lock = 1;
                        }
                        // �������غ�բ
                    }
                    // �����ڶ����ѿ�
                    if (F_I_STA == 2)
                    {
                        F_ch = 1;
                        gz_disp = 999; // ���㣬�˴�Ӧ���޸�
                        Record_data_propare();
                        // if(F_trip_gl==1)
                        {
                            Trip_Action();
                        }
                        F_record_write = 1;
                        gz_reason = trip_reason_3D_cur;
                        // putchar(gz_reason);
                        GZ_ph = 2;
                        // Write_Record(trip_reason_cur,1);
                        F_I_STA = 3;
                        F_I_Lock = 1;
                        F_gz_disp = A_gl + 1;

                        // д������բ��¼
                    }
                }
            }
            else
            {
                N_B3D = N_B3D - 1;
                if (N_B3D <= 0)
                    N_B3D = 0;
            }
        }
        if (F_ip == 1)
        {
            N_T_TH = N_TH_DL[TH_DL];
            if ((cur_handle_B(I_Array_xianshi[1])) >= I2)
            {
                N_B2D = N_B2D + 2;
                // N_K=N_K+20;
                // 2014��9��10������ٶ����󶯣��ӳ�����ʱ��19 �޸�Ϊ25
                if (N_B2D >= N_T_TH) // һ������12���㼰��ΪӦ�ö���
                {
                    if (F_I_STA == 0)
                    {
                        F_ch = 0;
                        Record_data_propare();                      // ��Ҫд���©�磬��ѹ������ֵ׼������д��
                        gz_disp = cur_handle_B(I_Array_xianshi[1]); // ���㣬�˴�Ӧ���޸�
                        {
                            Trip_Action();
                        }
                        gz_reason = trip_reason_short;
                        F_record_write = 1;
                        // putchar(gz_reason);
                        GZ_ph = 2;
                        // Write_Record(trip_reason_cur,(i+1));
                        F_gz_disp = A_gl + 1;
                        if (F_ia == 1) // F_ia  ©���غ�բ��־λ
                        {
                            F_I_STA = 1;
                            F_ch = 0;
                            F_I_Lock = 0;
                        }
                        // ���©���غ�բ���ܿ�
                        else
                        {
                            F_ch = 1;
                            F_I_STA = 3; // ֱ����3
                            F_I_Lock = 1;
                        }
                        // �������غ�բ
                    }
                    // �����ڶ����ѿ�
                    if (F_I_STA == 2)
                    {
                        F_ch = 1;
                        gz_disp = 997; // ���㣬�˴�Ӧ���޸�
                        Record_data_propare();
                        // if(F_trip_gl==1)
                        {
                            Trip_Action();
                        }
                        F_record_write = 1;
                        gz_reason = trip_reason_short;
                        // putchar(gz_reason);
                        GZ_ph = 2;
                        // Write_Record(trip_reason_cur,1);
                        F_I_STA = 3;
                        F_I_Lock = 1;
                        F_gz_disp = A_gl + 1;

                        // д������բ��¼
                    }
                }
            }
            else
            {
                N_B2D = N_B2D - 1;
                if (N_B2D <= 0)
                    N_B2D = 0;
            }
        }
    }
}

void D3_C_BH_Process(void)
{
    if (isfenzha != 0) // �ں�բλ��
    {
        if (F_ip_3 == 1)
        {
            if ((cur_actionhandle_C(I_Array_xianshi[2])) >= I3)
            {
                N_C3D = N_C3D + 2;
                // N_K=N_K+20;

                if (N_C3D >= 3) // һ������12���㼰��ΪӦ�ö���
                {
                    //						if(F_I_STA==0)
                    {
                        F_ch = 0;
                        Record_data_propare();                            // ��Ҫд���©�磬��ѹ������ֵ׼������д��
                        gz_disp = cur_actionhandle_C(I_Array_xianshi[2]); // ���㣬�˴�Ӧ���޸�
                        // if(F_trip_gl==1)
                        {
                            Trip_Action();
                        }
                        gz_reason = trip_reason_3D_cur;
                        F_record_write = 1;
                        // putchar(gz_reason);
                        GZ_ph = 3;
                        // Write_Record(trip_reason_cur,(i+1));
                        F_gz_disp = A_gl + 2;
                        if (F_ia == 1) // F_ia  ©���غ�բ��־λ
                        {
                            F_I_STA = 1;
                            F_ch = 0;
                            F_I_Lock = 0;
                        }
                        // ���©���غ�բ���ܿ�
                        else
                        {
                            F_ch = 1;
                            F_I_STA = 3; // ֱ����3
                            F_I_Lock = 1;
                        }
                        // �������غ�բ
                    }
                    // �����ڶ����ѿ�
                    if (F_I_STA == 2)
                    {
                        F_ch = 1;
                        gz_disp = 999; // ���㣬�˴�Ӧ���޸�
                        Record_data_propare();
                        // if(F_trip_gl==1)
                        {
                            Trip_Action();
                        }

                        F_record_write = 1;
                        gz_reason = trip_reason_3D_cur;
                        // putchar(gz_reason);
                        GZ_ph = 3;
                        // Write_Record(trip_reason_cur,1);
                        F_I_STA = 3;
                        F_I_Lock = 1;
                        F_gz_disp = A_gl + 2;

                        // д������բ��¼
                    }
                }
            }
            else
            {
                N_C3D = N_C3D - 1;
                if (N_C3D <= 0)
                    N_C3D = 0;
            }
        }
        if (F_ip == 1)
        {
            N_T_TH = N_TH_DL[TH_DL];
            if ((cur_handle_C(I_Array_xianshi[2])) >= I2)
            {
                N_C2D = N_C2D + 2;
                // N_K=N_K+20;
                // 2014��9��10������ٶ����󶯣��ӳ�����ʱ��19 �޸�Ϊ25
                if (N_C2D >= N_T_TH) // һ������12���㼰��ΪӦ�ö���
                {
                    //						if(F_I_STA==0)
                    {
                        F_ch = 0;
                        Record_data_propare();                      // ��Ҫд���©�磬��ѹ������ֵ׼������д��
                        gz_disp = cur_handle_C(I_Array_xianshi[2]); // ���㣬�˴�Ӧ���޸�
                        // if(F_trip_gl==1)
                        {
                            Trip_Action();
                        }
                        gz_reason = trip_reason_short;
                        F_record_write = 1;
                        // putchar(gz_reason);
                        GZ_ph = 3;
                        // Write_Record(trip_reason_cur,(i+1));
                        F_gz_disp = A_gl + 2;
                        if (F_ia == 1) // F_ia  ©���غ�բ��־λ
                        {
                            F_I_STA = 1;
                            F_ch = 0;
                            F_I_Lock = 0;
                        }
                        // ���©���غ�բ���ܿ�
                        else
                        {
                            F_ch = 1;
                            F_I_STA = 3; // ֱ����3
                            F_I_Lock = 1;
                        }
                        // �������غ�բ
                    }
                    // �����ڶ����ѿ�
                    if (F_I_STA == 2)
                    {
                        F_ch = 1;
                        gz_disp = 997; // ���㣬�˴�Ӧ���޸�
                        Record_data_propare();
                        // if(F_trip_gl==1)
                        {
                            Trip_Action();
                        }

                        F_record_write = 1;
                        gz_reason = trip_reason_short;
                        // putchar(gz_reason);
                        GZ_ph = 3;
                        // Write_Record(trip_reason_cur,1);
                        F_I_STA = 3;
                        F_I_Lock = 1;
                        F_gz_disp = A_gl + 2;

                        // д������բ��¼
                    }
                }
            }
            else
            {
                N_C2D = N_C2D - 2;
                if (N_C2D <= 0)
                    N_C2D = 0;
            }
        }
    }
}
unsigned int cur_handle_A(unsigned int x)
{
    F_Corr = 0;
    unsigned int y;
    if (Type_Cur == 0)
    {

        if (x <= CurA_cal_tmp[0])
        {
            x = (x * I1_A_slope[0]) >> 20;
        }
        else if (x > CurA_cal_tmp[0])
        {
            x = 50 + (((x - CurA_cal_tmp[0]) * I1_A_slope[1]) >> 20);
        }
        else
        {
        }
    }
    // ������ܵȼ�Ϊ60~250Aʱ
    if (Type_Cur == 1) // ��Ҫ�Ķ�
    {

        if (x <= CurA_cal_tmp[0])
        {
            x = (x * I1_A_slope[0]) >> 20;
        }
        else if (x > CurA_cal_tmp[0])
        {
            x = 100 + (((x - CurA_cal_tmp[0]) * I1_A_slope[1]) >> 20);
        }
        else
        {
        }
        if (x <= 99)
            x = 2 * x - 100;
    }
    // ������ܵȼ�Ϊ200~400Aʱ
    if (Type_Cur == 2)
    {

        if (x <= CurA_cal_tmp[0])
        {
            x = (x * I1_A_slope[0]) >> 20;
        }
        else if (x > CurA_cal_tmp[0])
        {
            x = 160 + (((x - CurA_cal_tmp[0]) * I1_A_slope[1]) >> 20);
        }
        else
        {
        }
    }
    // ������ܵȼ�Ϊ60~250Aʱ
    if (Type_Cur == 3)
    {

        if (x <= CurA_cal_tmp[0])
        {
            x = (x * I1_A_slope[0]) >> 20;
        }
        else if (x > CurA_cal_tmp[0])
        {
            x = 252 + (((x - CurA_cal_tmp[0]) * I1_A_slope[1]) >> 20);
        }
        else
        {
        }
    }
    if (Type_Cur == 4)
    {

        if (x <= CurA_cal_tmp[0])
        {
            x = (x * I1_A_slope[0]) >> 20;
        }
        else if (x > CurA_cal_tmp[0])
        {
            x = 320 + (((x - CurA_cal_tmp[0]) * I1_A_slope[1]) >> 20);
        }
        else
        {
        }
    }
    I_A_vaule = x;
    if (I_A_vaule <= 21)
        I_A_vaule = 0;
    IA_uart_temp = y;
    return I_A_vaule;
}

unsigned int cur_handle_B(unsigned int x)
{
    F_Corr = 0;
    unsigned int y;
    if (Type_Cur == 0)
    {

        if (x <= CurB_cal_tmp[0])
        {
            x = (x * I1_B_slope[0]) >> 20;
        }
        else if (x > CurB_cal_tmp[0])
        {
            x = 50 + (((x - CurB_cal_tmp[0]) * I1_B_slope[1]) >> 20);
        }
        else
        {
        }
    }
    // ������ܵȼ�Ϊ60~250Aʱ
    if (Type_Cur == 1) // ��Ҫ�Ķ�
    {

        if (x <= CurB_cal_tmp[0])
        {
            x = (x * I1_B_slope[0]) >> 20;
        }
        else if (x > CurB_cal_tmp[0])
        {
            x = 100 + (((x - CurB_cal_tmp[0]) * I1_B_slope[1]) >> 20);
        }
        else
        {
        }
        if (x <= 99)
            x = 2 * x - 100;
    }
    // ������ܵȼ�Ϊ200~400Aʱ
    if (Type_Cur == 2)
    {
        //         y = (x>>10)+(x>>11)+(((x>>10)+(x>>11))>>2);
        //		     x=(x>>11)+(x>>12);

        if (x <= CurB_cal_tmp[0])
        {
            x = (x * I1_B_slope[0]) >> 20;
        }
        else if (x > CurB_cal_tmp[0])
        {
            x = 160 + (((x - CurB_cal_tmp[0]) * I1_B_slope[1]) >> 20);
        }
        else
        {
        }
    }
    if (Type_Cur == 3)
    {
        //         y = (x>>10)+(x>>11)+(((x>>10)+(x>>11))>>2);
        //		     x=(x>>13)+(x>>14);

        if (x <= CurB_cal_tmp[0])
        {
            x = (x * I1_B_slope[0]) >> 20;
        }
        else if (x > CurB_cal_tmp[0])
        {
            x = 252 + (((x - CurB_cal_tmp[0]) * I1_B_slope[1]) >> 20);
        }
        else
        {
        }
    }
    if (Type_Cur == 4)
    {

        if (x <= CurB_cal_tmp[0])
        {
            x = (x * I1_B_slope[0]) >> 20;
        }
        else if (x > CurB_cal_tmp[0])
        {
            x = 320 + (((x - CurB_cal_tmp[0]) * I1_B_slope[1]) >> 20);
        }
        else
        {
        }
    }
    I_B_vaule = x;
    if (I_B_vaule <= 21)
        I_B_vaule = 0;
    IB_uart_temp = y;
    return I_B_vaule;
}

unsigned int cur_handle_C(unsigned int x)
{
    F_Corr = 0;
    unsigned int y;
    if (Type_Cur == 0)
    {

        if (x <= CurC_cal_tmp[0])
        {
            x = (x * I1_C_slope[0]) >> 20;
        }
        else if (x > CurC_cal_tmp[0])
        {
            x = 50 + (((x - CurC_cal_tmp[0]) * I1_C_slope[1]) >> 20);
        }
        else
        {
        }
    }
    // ������ܵȼ�Ϊ60~250Aʱ
    if (Type_Cur == 1) // ��Ҫ�Ķ�
    {

        if (x <= CurC_cal_tmp[0])
        {
            x = (x * I1_C_slope[0]) >> 20;
        }
        else if (x > CurC_cal_tmp[0])
        {
            x = 100 + (((x - CurC_cal_tmp[0]) * I1_C_slope[1]) >> 20);
        }
        else
        {
        }

        if (x <= 99)
            x = 2 * x - 100;
    }
    // ������ܵȼ�Ϊ200~400Aʱ
    if (Type_Cur == 2)
    {
        //        y = (x>>10)+(x>>11);
        //		   x=(x>>13)+(x>>14);

        if (x <= CurC_cal_tmp[0])
        {
            x = (x * I1_C_slope[0]) >> 20;
        }
        else if (x > CurC_cal_tmp[0])
        {
            x = 160 + (((x - CurC_cal_tmp[0]) * I1_C_slope[1]) >> 20);
        }
        else
        {
        }
    }
    // ������ܵȼ�Ϊ60~250Aʱ
    if (Type_Cur == 3)
    {
        //         y = (x>>10)+(x>>11)+(((x>>10)+(x>>11))>>2);
        //		     x=(x>>13)+(x>>14);

        if (x <= CurC_cal_tmp[0])
        {
            x = (x * I1_C_slope[0]) >> 20;
        }
        else if (x > CurC_cal_tmp[0])
        {
            x = 252 + (((x - CurC_cal_tmp[0]) * I1_C_slope[1]) >> 20);
        }
        else
        {
        }
    }
    if (Type_Cur == 4)
    {

        if (x <= CurC_cal_tmp[0])
        {
            x = (x * I1_C_slope[0]) >> 20;
        }
        else if (x > CurC_cal_tmp[0])
        {
            x = 320 + (((x - CurC_cal_tmp[0]) * I1_C_slope[1]) >> 20);
        }
        else
        {
        }
    }

    I_C_vaule = x;
    if (I_C_vaule <= 21)
        I_C_vaule = 0;
    IC_uart_temp = y;
    return I_C_vaule;
}

unsigned int cur_actionhandle_A(unsigned int x)
{
    // ������ܵȼ�Ϊ20~100Aʱ
    unsigned int y;
    if (Type_Cur == 0)
    {
        if (x <= 46200)
        {
            x = x / 66;
        }
        else
        {
            x = 700 + (x - 46200) / 24; // 15
        }

        //				else
        //				{
        //				  x= 2000+(x-76800)/8;
        //				}
    }
    // ������ܵȼ�Ϊ60~250Aʱ
    if (Type_Cur == 1) // ��Ҫ�Ķ�//DLS_Cur_Value[0]=DLS_Cur_AD_value[0]/DLS_Cur_slope[0];˲������ֵ=˲������ADֵ/˲��б��
    {

        if (x <= 66000) // 1100
        {
            x = x / 60;
        }
        else if (x < 76800) // 2000
        {
            x = 1100 + (x - 66000) / 12; // 15
        }
        else
        {
            x = 2000 + (x - 76800) / 8;
        }
        //				if((x>850)&&(x<2200)) x=x;
        //				else if((x>2200)&&(x<2900)) x=x+300;
        //				else if(x>2900) x=x;
        if ((x > 850) && (x < 2200))
            x = x + 100;
        else if ((x > 2200) && (x < 2900))
            x = x + 200;
    }
    // ������ܵȼ�Ϊ200~400Aʱ
    if (Type_Cur == 2)
    {
        if (x <= 41800) // 1100
        {
            x = x / 38;
        }
        else if (x < 77900)
        {
            x = 1100 + (x - 41800) / 19;
        }
        else
        {
            x = 3000 + (x - 77900) / 3;
        }

        if ((x > 2800) && (x < 3400))
            x = x + 500;
        else if (x > 4000)
            x = x - 300;
    }
    // ������ܵȼ�Ϊ60~250Aʱ
    if (Type_Cur == 3)
    {

        if (x <= 30800)
        {
            x = x / 28;
        }
        else if (x < 62300)
        {
            x = 1100 + (x - 30800) / 15;
        }
        else if (x < 75500)
        {
            x = 3200 + (x - 62300) / 4;
        }
        else
        {
            x = 6500 + (x - 75500) / 2;
        }
        if (x >= 4300)
            x = x - 500;
    }
    if (Type_Cur == 4)
    {

        if (x <= 30800)
        {
            x = x / 28;
        }
        else if (x < 62300)
        {
            x = 1100 + (x - 30800) / 25;
        }
        else if (x < 87260)
        {
            x = 2360 + (x - 62300) / 24;
        }
        else if (x < 96860)
        {
            x = 3400 + (x - 87260) / 6;
        }
        else if (x < 103260)
        {
            x = 5000 + (x - 96860) / 2;
        }
        else if (x < 106460)
        {
            x = 8200 + (x - 103260) / 2;
        }
        else
        {
            x = 9100 + (x - 106460) / 1;
        }
        if ((x > 6000) && (x < 9800))
            x = x - 1000;
    }

    IA_action_temp = x;
    return IA_action_temp;
}

unsigned int cur_actionhandle_B(unsigned int x)
{
    // ������ܵȼ�Ϊ20~100Aʱ
    unsigned int y;
    if (Type_Cur == 0)
    {
        if (x <= 46200)
        {
            x = x / 66;
        }
        else
        {
            x = 700 + (x - 46200) / 24; // 15
        }

        //				else
        //				{
        //				  x= 2000+(x-76800)/8;
        //				}
    }
    // ������ܵȼ�Ϊ60~250Aʱ
    if (Type_Cur == 1) // ��Ҫ�Ķ�//DLS_Cur_Value[0]=DLS_Cur_AD_value[0]/DLS_Cur_slope[0];˲������ֵ=˲������ADֵ/˲��б��
    {

        if (x <= 66000) // 1100
        {
            x = x / 60;
        }
        else if (x < 76800) // 2000
        {
            x = 1100 + (x - 66000) / 12; // 15
        }
        else
        {
            x = 2000 + (x - 76800) / 8;
        }
        //				if((x>850)&&(x<2200)) x=x;
        //				else if((x>2200)&&(x<2900)) x=x+200;
        //				else if(x>2900) x=x;
        if ((x > 850) && (x < 2200))
            x = x + 150;
        // else if((x>2200)&&(x<2900)) x=x+100;
    }
    // ������ܵȼ�Ϊ200~400Aʱ
    if (Type_Cur == 2)
    {
        if (x <= 41800) // 1100
        {
            x = x / 38;
        }
        else if (x < 77900)
        {
            x = 1100 + (x - 41800) / 19;
        }
        else
        {
            x = 3000 + (x - 77900) / 3;
        }
        if ((x > 2800) && (x < 3400))
            x = x + 500;
        else if (x > 4000)
            x = x - 300;
    }
    // ������ܵȼ�Ϊ60~250Aʱ
    if (Type_Cur == 3)
    {

        if (x <= 30800)
        {
            x = x / 28;
        }
        else if (x < 62300)
        {
            x = 1100 + (x - 30800) / 15;
        }
        else if (x < 75500)
        {
            x = 3200 + (x - 62300) / 4;
        }
        else
        {
            x = 6500 + (x - 75500) / 2;
        }
        if (x >= 4300)
            x = x - 950;
    }
    if (Type_Cur == 4)
    {

        if (x <= 30800)
        {
            x = x / 28;
        }
        else if (x < 62300)
        {
            x = 1100 + (x - 30800) / 25;
        }
        else if (x < 87260)
        {
            x = 2360 + (x - 62300) / 24;
        }
        else if (x < 96860)
        {
            x = 3400 + (x - 87260) / 6;
        }
        else if (x < 103260)
        {
            x = 5000 + (x - 96860) / 2;
        }
        else if (x < 106460)
        {
            x = 8200 + (x - 103260) / 2;
        }
        else
        {
            x = 9100 + (x - 106460) / 1;
        }
        if ((x > 6000) && (x < 9800))
            x = x - 1000;
    }

    IB_action_temp = x;
    return IB_action_temp;
}

unsigned int cur_actionhandle_C(unsigned int x)
{
    // ������ܵȼ�Ϊ20~100Aʱ
    unsigned int y;
    if (Type_Cur == 0)
    {
        if (x <= 46200)
        {
            x = x / 66;
        }
        else
        {
            x = 700 + (x - 46200) / 24; // 15
        }

        //				else
        //				{
        //				  x= 2000+(x-76800)/8;
        //				}
    }
    // ������ܵȼ�Ϊ60~250Aʱ
    if (Type_Cur == 1) // ��Ҫ�Ķ�//DLS_Cur_Value[0]=DLS_Cur_AD_value[0]/DLS_Cur_slope[0];˲������ֵ=˲������ADֵ/˲��б��
    {

        if (x <= 66000) // 1100
        {
            x = x / 60;
        }
        else if (x < 76800) // 2000
        {
            x = 1100 + (x - 66000) / 12; // 15
        }
        else
        {
            x = 2000 + (x - 76800) / 8;
        }
        //				if((x>850)&&(x<2200)) x=x;
        //				else if((x>2200)&&(x<2900)) x=x+300;
        //				else if(x>2900) x=x;
        if ((x > 850) && (x < 2200))
            x = x + 100;
        else if ((x > 2200) && (x < 2900))
            x = x + 200;
    }
    // ������ܵȼ�Ϊ200~400Aʱ
    if (Type_Cur == 2)
    {
        if (x <= 41800) // 1100
        {
            x = x / 38;
        }
        else if (x < 77900)
        {
            x = 1100 + (x - 41800) / 19;
        }
        else
        {
            x = 3000 + (x - 77900) / 3;
        }

        if ((x > 2800) && (x < 3400))
            x = x + 500;
        else if (x > 4000)
            x = x - 300;
    }
    // ������ܵȼ�Ϊ60~250Aʱ
    if (Type_Cur == 3)
    {

        if (x <= 30800)
        {
            x = x / 28;
        }
        else if (x < 62300)
        {
            x = 1100 + (x - 30800) / 15;
        }
        else if (x < 75500)
        {
            x = 3200 + (x - 62300) / 4;
        }
        else
        {
            x = 6500 + (x - 75500) / 2;
        }
        if (x >= 4300)
            x = x - 500;
    }
    if (Type_Cur == 4)
    {

        if (x <= 30800)
        {
            x = x / 28;
        }
        else if (x < 62300)
        {
            x = 1100 + (x - 30800) / 25;
        }
        else if (x < 87260)
        {
            x = 2360 + (x - 62300) / 24;
        }
        else if (x < 96860)
        {
            x = 3400 + (x - 87260) / 6;
        }
        else if (x < 103260)
        {
            x = 5000 + (x - 96860) / 2;
        }
        else if (x < 106460)
        {
            x = 8200 + (x - 103260) / 2;
        }
        else
        {
            x = 9100 + (x - 106460) / 1;
        }
        if ((x > 6000) && (x < 9800))
            x = x - 1000;
    }

    IC_action_temp = x;
    return IC_action_temp;
}
void V_Sample_A(void)
{
    AD_tmp_V = 0;
    AD_tmp_V = ADC_ConvertedValue[6];
    A_V_Sum1 = AD_tmp_V + A_V_Sum1;
    if (AD_tmp_VA_Max <= AD_tmp_V)
        AD_tmp_VA_Max = AD_tmp_V;
    //	if(AD_tmp_V>=2800)
    //	{
    //		A_QL=1;
    //	}
    if (AD_tmp_V >= 3100)
    {
        N_TD_A = N_TD_A + 1;
    }
}
void V_Sample_B(void)
{
    AD_tmp_V = 0;
    AD_tmp_V = ADC_ConvertedValue[5];
    B_V_Sum1 = AD_tmp_V + B_V_Sum1;
    if (AD_tmp_VB_Max <= AD_tmp_V)
        AD_tmp_VB_Max = AD_tmp_V;
    //	if(AD_tmp_V>=2800)
    //	{
    //		B_QL=1;
    //	}
    if (AD_tmp_V >= 3100)
    {
        N_TD_B = N_TD_B + 1;
    }
}
void V_Sample_CC(void)
{
    AD_tmp_V = 0;
    AD_tmp_V = ADC_ConvertedValue[4];
    C_V_Sum1 = AD_tmp_V + C_V_Sum1;
    if (AD_tmp_VC_Max <= AD_tmp_V)
        AD_tmp_VC_Max = AD_tmp_V;
    //	if(AD_tmp_V>=2800)
    //	{
    //		C_QL=1;
    //	}
    if (AD_tmp_V >= 3100)
    {
        N_TD_C = N_TD_C + 1;
    }
}

unsigned int leak_handle(unsigned int x)
{
    unsigned int Leak_t;
    //	Num_Lv_handle();
    Leak_t = x;

    Leak_t = (Leak_t * L1_slope) >> 20;
    if (Leak_t <= 19)
    {
        Leak_t = 0;
    }

    return (Leak_t);
}

unsigned int vol_handle_undervol(unsigned int value) //ʧѹ����
{
	unsigned int undervol;
	undervol = value; //*undervol_slope;
	
	return undervol;

}
unsigned int vol_handle_anti_islanding_A(unsigned int value)  //���µ���ѹA�ദ����
{
	unsigned int V;
	
	
	return V;
}

unsigned int vol_handle_anti_islanding_B(unsigned int value)  //���µ���ѹB�ദ����
{
	unsigned int V;
	
	
	return V;
}

unsigned int vol_handle_anti_islanding_C(unsigned int value)  //���µ���ѹC�ദ����
{
	unsigned int V;
	
	
	return V;
}

unsigned int vol_handle_A(unsigned int value)
{
    unsigned int V_t;
    V_t = value;
    //		if(F_Corr==0)
    //		{
    //		  V_t=(V_t*V1_slope[0])>>20;
    //		}
    //		else
    //		{
    //			V_t=(V_t*V_A_slope[0])>>10;
    //      V_t=V_t/100;
    //
    //		}
    //	  V_t=(V_t*V1_slope[0])>>20;

    return (V_t);
}

unsigned int vol_handle_B(unsigned int value)
{
    unsigned int V_t;
    V_t = value;
    //		if(F_Corr==0)
    //		{
    //		  V_t=(V_t*V1_slope[1])>>20;
    ////      V_t=V_t/10;
    //		}
    //		else
    //		{
    //			V_t=(V_t*V_B_slope[0])>>10;
    //      V_t=V_t/100;
    //
    //		}
    // V_t=(V_t*V1_slope[1])>>20;

    return (V_t);
}
unsigned int vol_handle_C(unsigned int value)
{
    unsigned int V_t;
    V_t = value;
    //		if(F_Corr==0)
    //		{
    //		  V_t=(V_t*V1_slope[2])>>20;
    ////      V_t=V_t/10;
    //		}
    //		else
    //		{
    //			V_t=(V_t*V_C_slope[0])>>10;
    //      V_t=V_t/100;
    //
    //		}

    // V_t=(V_t*V1_slope[2])>>20;
    return (V_t);
}

void Day_updata_process(void)
{
    IWDG_Feed(); // ι��
    if (F_day_updata == 1)
    {
        unsigned char tim_array_tmp[10];
        F_day_updata = 0;
        HAL_RTC_GetTime(&hrtc, &stimestructure, RTC_FORMAT_BCD);
        HAL_RTC_GetDate(&hrtc, &sdatestructure, RTC_FORMAT_BCD);
        tim_y = sdatestructure.Year; // tim_yΪʮ���ƣ�Ҫת��������
        tim_m = sdatestructure.Month;
        tim_d = sdatestructure.Date;
        //			now_month = tim_array_tmp[1];
        //			now_day = tim_array_tmp[2];
        now_month = tim_m;
        now_day = tim_d;
        if ((now_day != old_day) || (now_month != old_month))
        //		if(now_day!=old_day)
        {
            Day_factors_clear();
            old_day = now_day;
            old_month = now_month;
            //					if(baud==3)
            //				{
            //					RS485_Init(9600);
            //				}
            //				else if(baud==2)
            //				{
            //					RS485_Init(4800);
            //				}
            //				else if(baud==1)
            //				{
            //					RS485_Init(2400);
            //				}
            //				else if(baud==0)
            //				{
            //					RS485_Init(1200);
            //				}
            // clear_uart_sta();
            F_Dataval = 0;
        }
    }
}
void write_tingdian(void)
{
    unsigned char tingdian[2];
    tingdian[0] = 0x55;
    MODIFY_EEP_W(Addr_tingdian, tingdian, 1, 0xA0);
}

unsigned int cur_cal_handle(unsigned int x)
{
    int y;
    int y1;
    // ������ܵȼ�Ϊ20~100Aʱ
    if (Type_Cur == 0)
    {
        x = (x * 103) >> 10;
        y1 = x;
    }
    // ������ܵȼ�Ϊ60~250Aʱ
    if (Type_Cur == 1) // ��Ҫ�Ķ�
    {
        x = (x * 98) >> 11;
        y1 = x;
    }
    // ������ܵȼ�Ϊ200~400Aʱ
    if (Type_Cur == 2)
    {
        x = (x * 31) >> 9;
        y1 = x;
    }
    // ������ܵȼ�Ϊ60~250Aʱ
    if (Type_Cur == 3)
    {
        x = (x * 92) >> 10;
        y1 = x;
    }
    y = y1;
    y1 = 0;
    if (y <= 10)
        y = 0;
    return y;
}

unsigned int vol_cal_handle(unsigned int value)
{
    unsigned int V_t;
    V_t = value;

    if (V_t < 300)
        return 0;
    else
    {
        V_t = (V_t * 78) >> 9;
    }
    //  qian1=V_t;
    return (V_t);
}

void hand_short_process(void)
{
    IWDG_Feed(); // ι��
//    if (WF == 1)
//    {
//        delay_ms(5);
//        if (WF == 1)
//        {
//            if (isfenzha == 1)
//            {
//                F_fz = 1;
//                F_hz = 0;
//            }
//        }
//    }
//    if (WH == 1)
//    {
//        delay_ms(5);
//        if (WH == 1)
//        {
//            if (isfenzha == 0)
//            {
//                F_fz = 0;
//                F_hz = 1;
//            }
//        }
//    }
    if (WF == 1)
    {
        delay_ms(5);
        if (WF == 1)
        {
            if (isfenzha == 1)
            {
                F_fz = 1;
                F_hz = 0;
            }
        }
    }
    if (WH == 1)
    {
        delay_ms(5);
        if (WH == 1)
        {
            if (isfenzha == 0)
            {
                F_fz = 0;
                F_hz = 1;
            }
        }
    }
}

void IWDG_Feed(void)
{
    // HAL_IWDG_Refresh(&hiwdg); //ι��
}

void data_clear(void)
{
    int Addr_factor;
    unsigned char array_temp[10];
    unsigned int lenth;
    unsigned char Buf_temp[30];
    // �¼�����
    clear_screen();
    Lcd12864_Write16CnCHAR(0, 16, 2, "����������...");
    Num_clearall = Num_clearall + 1;
    DectoBCD(Buf_temp, Num_clearall, 3);
    MODIFY_EEP_W(Addr_clear_num, Buf_temp, 3, 0xA0);

    Addr_factor = Addr_max_leak;
    lenth = 288;
    EEPROM_C(Addr_factor, lenth, 0xA0);
    delay_ms(5);
    IWDG_Feed();
    Addr_factor = Addr_max_Avol;
    lenth = 288;
    EEPROM_C(Addr_factor, lenth, 0xA0);
    delay_ms(5);
    IWDG_Feed();
    Addr_factor = Addr_max_Bvol;
    lenth = 288;
    IWDG_Feed();
    EEPROM_C(Addr_factor, lenth, 0xA0);
    delay_ms(5);
    IWDG_Feed();
    Addr_factor = Addr_max_Cvol;
    lenth = 288;
    EEPROM_C(Addr_factor, lenth, 0xA0);
    delay_ms(5);
    IWDG_Feed();
    Addr_factor = Addr_max_Acur;
    lenth = 288;
    EEPROM_C(Addr_factor, lenth, 0xA0);
    delay_ms(5);
    IWDG_Feed();
    Addr_factor = Addr_max_Bcur;
    lenth = 288;
    EEPROM_C(Addr_factor, lenth, 0xA0);
    delay_ms(5);
    IWDG_Feed();
    Addr_factor = Addr_max_Ccur;
    lenth = 288;
    IWDG_Feed();
    EEPROM_C(Addr_factor, lenth, 0xA0);
    delay_ms(5);
    //	Leak_MAX_ualue=0;

    /*          �ۼƼ�¼����          */
    // ���������ܴ��� 000000
    IWDG_Feed();
    //	array_temp[0] = array_temp[1]=array_temp[2] = 0;
    //	lenth=Lenth_clear_num ;
    //	Addr_factor=Addr_clear_num ;
    //	MODIFY_EEP_W(Addr_factor,array_temp,lenth);
    // �ѿ۴���
    array_temp[0] = array_temp[1] = 0;
    MODIFY_EEP_W(Addr_trip_num, array_temp, 2, 0xA0);
    Num_tripall = 0;
    // close ����
    array_temp[0] = array_temp[1] = 0;
    MODIFY_EEP_W(Addr_close_num, array_temp, 2, 0xA0);
    Num_triplock = 0;
    // ©���ѿ۴���
    array_temp[0] = array_temp[1] = 0;
    MODIFY_EEP_W(Addr_leak_num, array_temp, 2, 0xA0);
    Num_tripleak = 0;
    // �����ѿ۴���
    array_temp[0] = array_temp[1] = 0;
    MODIFY_EEP_W(Addr_current_num, array_temp, 2, 0xA0);
    Num_tripcur = 0;
    // ��ѹ�ѿ۴���
    array_temp[0] = array_temp[1] = 0;
    MODIFY_EEP_W(Addr_vol_num, array_temp, 2, 0xA0);
    Num_tripvol = 0;
    // �ֶ��ѿ۴���
    array_temp[0] = array_temp[1] = 0;
    MODIFY_EEP_W(Addr_hand_num, array_temp, 2, 0xA0);
    Num_triphand = 0;
    // �����ѿ۴���
    array_temp[0] = array_temp[1] = 0;
    MODIFY_EEP_W(Addr_zero_num, array_temp, 2, 0xA0);
    Num_tripzero = 0;
    // �����ѿ۴���
    array_temp[0] = array_temp[1] = 0;
    MODIFY_EEP_W(Addr_test_num, array_temp, 2, 0xA0);
    Num_triptest = 0;
    // ��·���Ӵ���
    array_temp[0] = array_temp[1] = 0;
    MODIFY_EEP_W(Addr_2D_num, array_temp, 2, 0xA0);
    Num_tripdelay = 0;

    // ʣ������仯����
    //	array_temp[0] = 0;
    //	MODIFY_EEP_W(Addr_leakchange_num,array_temp,1);
    // �Լ����
    //	array_temp[0] = 0;
    //	MODIFY_EEP_W(Addr_tripkey_num,array_temp,1);
    // ��·��˲����
    array_temp[0] = array_temp[1] = 0;
    MODIFY_EEP_W(Addr_3D_num, array_temp, 2, 0xA0);
    Num_tripinstant = 0;
    IWDG_Feed();
    /*      �¼���¼ָ������            */
    //  ©���¼�ĵ�ַָ��

    array_temp[0] = 0;
    MODIFY_EEP_W(Addr_point_event_trip, array_temp, 1, 0xA0);

    array_temp[0] = 0;
    MODIFY_EEP_W(Addr_point_event_trip_24C256, array_temp, 1, 0xA0);
    IWDG_Feed();
    array_temp[0] = 0;
    MODIFY_EEP_W(Addr_point_event_self, array_temp, 1, 0xA0);
    // Rewrite_buffer(0);
    // pw1 = 0x12;pw2 = 0x34;pw3 = 0x56;pw4 = 0x78;
    // IapEraseSector(512);
    // IapEraseSector(1024);
    Addr_factor = 10500;
    lenth = 1000;
    //	EEPROM_C(Addr_factor,lenth);
    //	EEPROM_R(Addr_FACTORINIT_value,array_tmp,150);
    //	MODIFY_EEP_W(Addr_FACTORINIT_value,array_tmp,150);
}

void CurrentDataReadFun()
{
    signed int temp = 0;

//    HT7038_buf[0] = HT7038_Read(rDeviceID);

    HT7038_buf[1] = HT7038_Read(rUaRms) / 8192; // A���ѹ
    HT7038_buf[2] = HT7038_Read(rUbRms) / 8192; // B���ѹ
    HT7038_buf[3] = HT7038_Read(rUcRms) / 8192; // C���ѹ

    V_Array_disp[0] = HT7038_buf[1];
    V_Array_disp[1] = HT7038_buf[2];
    V_Array_disp[2] = HT7038_buf[3];
	
		V_Array[0] = HT7038_buf[1];
		V_Array[1] = HT7038_buf[2];
		V_Array[2] = HT7038_buf[3];

    HT7038_buf[4] = HT7038_Read(rIaRms) / 8192 / 3.5; // A�����
    HT7038_buf[5] = HT7038_Read(rIbRms) / 8192 / 3.5; // B�����
    HT7038_buf[6] = HT7038_Read(rIcRms) / 8192 / 3.5; // C�����

    temp = HT7038_Read(rPa); // A���й�����
    if (temp >= 8388608)
        HT7038_buf[7] = -(16777216 - temp);
    else
        HT7038_buf[7] = temp;
    HT7038_buf[7] = HT7038_buf[7] * 0.032;
    fuhao[0] = HT7038_buf[7] >> 31;
    HT7038_buf[7] = abs(HT7038_buf[7]);

    temp = HT7038_Read(rPb); // B���й�����
    if (temp >= 8388608)
        HT7038_buf[8] = -(16777216 - temp);
    else
        HT7038_buf[8] = temp;
    HT7038_buf[8] = HT7038_buf[8] * 0.032;
    fuhao[1] = HT7038_buf[8] >> 31;
    HT7038_buf[8] = abs(HT7038_buf[8]);

    temp = HT7038_Read(rPc); // 8388608; //C���й�����
    if (temp >= 8388608)
        HT7038_buf[9] = -(16777216 - temp);
    else
        HT7038_buf[9] = temp;
    HT7038_buf[9] = HT7038_buf[9] * 0.032;
    fuhao[2] = HT7038_buf[9] >> 31;
    HT7038_buf[9] = abs(HT7038_buf[9]);

    temp = HT7038_Read(rPt); // 8388608; //�����й�����
    if (temp >= 8388608)
        HT7038_buf[10] = -(16777216 - temp);
    else
        HT7038_buf[10] = temp;
    HT7038_buf[10] = HT7038_buf[10] * 0.064;
    fuhao[3] = HT7038_buf[10] >> 31;
    HT7038_buf[10] = abs(HT7038_buf[10]);

    temp = HT7038_Read(rPfa); // A�๦������
    if (temp >= 8388608)
        HT7038_buf[11] = -(16777216 - temp) / 8388.608;
    else
        HT7038_buf[11] = temp / 8388.608;
    fuhao[8] = HT7038_buf[11] >> 31;
    HT7038_buf[11] = abs(HT7038_buf[11]);

    temp = HT7038_Read(rPfb); // B�๦������
    if (temp >= 8388608)
        HT7038_buf[12] = -(16777216 - temp) / 8388.608;
    else
        HT7038_buf[12] = temp / 8388.608;
    fuhao[9] = HT7038_buf[12] >> 31;
    HT7038_buf[12] = abs(HT7038_buf[12]);

    temp = HT7038_Read(rPfc); // C�๦������
    if (temp >= 8388608)
        HT7038_buf[13] = -(16777216 - temp) / 8388.608;
    else
        HT7038_buf[13] = temp / 8388.608;
    fuhao[10] = HT7038_buf[13] >> 31;
    HT7038_buf[13] = abs(HT7038_buf[13]);

    temp = HT7038_Read(rPft); // ���๦������
    if (temp >= 8388608)
        HT7038_buf[14] = -(16777216 - temp) / 8388.608;
    else
        HT7038_buf[14] = temp / 8388.608;
    fuhao[11] = HT7038_buf[14] >> 31;
    HT7038_buf[14] = abs(HT7038_buf[14]);

    /********�й�����***************/
    HT7038_buf[15] = HT7038_Read(rEpa) / 19.2; // 8388.608; 	//A���й����� 
    HT7038_buf[16] = HT7038_Read(rEpb) / 19.2; // 8388.608; //B���й�����
    HT7038_buf[17] = HT7038_Read(rEpc) / 19.2; // 8388.608; //C���й�����
    HT7038_buf[18] = HT7038_Read(rEpt) / 19.2; // 8388.608; //�����й�����

    //	delay_ms(1000);
    //    Accumulate_energy_dangqian_active_he=Accumulate_energy_dangqian_active_he+HT7038_buf[18];
    //		Accumulate_energy_dangqian_active_A=Accumulate_energy_dangqian_active_A+HT7038_buf[15];
    //		Accumulate_energy_dangqian_active_C=Accumulate_energy_dangqian_active_C+HT7038_buf[17];

    //
    //		Write_Energy(Addr_energy_active_he,Accumulate_energy_dangqian_active_he);
    //		Write_Energy(Addr_energy_active_A,Accumulate_energy_dangqian_active_A);
    //		Write_Energy(Addr_energy_active_C,Accumulate_energy_dangqian_active_C);

    // ��ǰ�ĵ���д��洢������������ʾ���ϴεĵ������ں�HT7038_buf[18]�ۼ�
    // AT24CXX_WriteLenByte(Addr_energy,HT7038_buf[18],10);
    // MODIFY_EEP_W_()

    /**********	���޹�����*****************/
    HT7038_buf[27] = HT7038_Read(rEqa) / 19.2; // A���޹�����
    HT7038_buf[28] = HT7038_Read(rEqb) / 19.2; // B���޹�����
    HT7038_buf[29] = HT7038_Read(rEqc) / 19.2; // C���޹�����
    HT7038_buf[30] = HT7038_Read(rEqt) / 19.2; // �����޹�����

    Accumulate_energy_dangqian_reactive_he = Accumulate_energy_shangci_reactive_he + HT7038_buf[30];
    //	  Write_Energy(Addr_energy_reactive_he,Accumulate_energy_dangqian_reactive_he);

    /**********�޹�����********************************/
    temp = HT7038_Read(rQa); // A���޹�����
    if (temp >= 8388608)
        HT7038_buf[19] = -(16777216 - temp);
    else
        HT7038_buf[19] = temp;
    HT7038_buf[19] = HT7038_buf[19] * 0.032;
    fuhao[4] = HT7038_buf[19] >> 31;
    HT7038_buf[19] = abs(HT7038_buf[19]);

    temp = HT7038_Read(rQb); // B���޹�����
    if (temp >= 8388608)
        HT7038_buf[20] = -(16777216 - temp);
    else
        HT7038_buf[20] = temp;
    HT7038_buf[20] = HT7038_buf[20] * 0.032;
    fuhao[5] = HT7038_buf[20] >> 31;
    HT7038_buf[20] = abs(HT7038_buf[20]);

    temp = HT7038_Read(rQc); // 8388608; //C���޹�����
    if (temp >= 8388608)
        HT7038_buf[21] = -(16777216 - temp);
    else
        HT7038_buf[21] = temp;
    HT7038_buf[21] = HT7038_buf[21] * 0.032;
    fuhao[6] = HT7038_buf[21] >> 31;
    HT7038_buf[21] = abs(HT7038_buf[21]);

    temp = HT7038_Read(rQt); // 8388608; //�����޹�����
    if (temp >= 8388608)
        HT7038_buf[22] = -(16777216 - temp);
    else
        HT7038_buf[22] = temp;
    HT7038_buf[22] = HT7038_buf[22] * 0.064;
    fuhao[7] = HT7038_buf[22] >> 31;
    HT7038_buf[22] = abs(HT7038_buf[22]);

    /********************���ڹ���**************/
    temp = HT7038_Read(rSa); // A�����ڹ���
    if (temp >= 8388608)
        HT7038_buf[23] = (16777216 - temp);
    else
        HT7038_buf[23] = temp;
    HT7038_buf[23] = HT7038_buf[23] * 0.032;

    temp = HT7038_Read(rSb); // B�����ڹ���
    if (temp >= 8388608)
        HT7038_buf[24] = (16777216 - temp);
    else
        HT7038_buf[24] = temp;
    HT7038_buf[24] = HT7038_buf[24] * 0.032;

    temp = HT7038_Read(rSc); // 8388608; //C�����ڹ���
    if (temp >= 8388608)
        HT7038_buf[25] = (16777216 - temp);
    else
        HT7038_buf[25] = temp;
    HT7038_buf[25] = HT7038_buf[25] * 0.032;

    temp = HT7038_Read(rSt); // 8388608; //�������ڹ���
    if (temp >= 8388608)
        HT7038_buf[26] = (16777216 - temp);
    else
        HT7038_buf[26] = temp;
    HT7038_buf[26] = HT7038_buf[26] * 0.064;

    /***********����Ƶ��************/
    HT7038_buf[31] = 10 * HT7038_Read(rFreq) / 8192;

    HT7038_buf[32] = HT7038_Read(w_UgainA);
		
		/**********	�����ڵ���*****************/
    HT7038_buf[33] = HT7038_Read(rEsa) / 19.2; // A�����ڵ���
    HT7038_buf[34] = HT7038_Read(rEsb) / 19.2; // B�����ڵ���
    HT7038_buf[35] = HT7038_Read(rEsc) / 19.2; // C�����ڵ���
    HT7038_buf[36] = HT7038_Read(rEst) / 19.2; // �������ڵ���

}

/*******��ʱ�Ʒ�**************/
/*******************
��ʱ�Ʒѹ��ܣ�   ��ʱ�Ʒѣ���ͬ�·ݼ��ƽ��ʱ�ο����������֣�Ŀǰֻ���죨24Сʱ��Ϊ����
n���Ӹ���һ�ε�ѣ�����Ҫ����n���������ĵĵ���*��ʱ�εĵ��
��
��
ƽ
��
+��ѹ������ƽ���
*****************************/
void Time_bill(void)//1����һ��
{
	unsigned int A_Phase_Vol = HT7038_buf[1];
	unsigned int B_Phase_Vol = HT7038_buf[2];
	unsigned int C_Phase_Vol = HT7038_buf[3];
	unsigned int A_Phase_Cur = HT7038_buf[4];
	unsigned int B_Phase_Cur = HT7038_buf[5];
	unsigned int C_Phase_Cur = HT7038_buf[6];

	unsigned char hour = stimestructure.Hours;
	
	/***********�Ƽ�*******************/
	int J_Begin,J_Over,F_Begin,F_Over,P_Begin,P_Over,G_Begin,G_Over; //���ƽ��
	
	float rateJFPG;
	float Charge;   //Charge_sum=0ȫ�ֱ���
	float Energy_dangqian,Energy_nmins=0;//Energy_shangci=0ȫ�ֱ���
	float Energy_dangqian_Reactive,Energy_dangqian_Apparent=0;

	//����n�������ĵ�����ĿǰΪ1���ӣ�
	HT7038_buf[18] = HT7038_Read(rEpt) / 3.2; //�����й�����
	Energy_dangqian = HT7038_buf[18];    //���ζ�������
	Energy_dangqian_Reactive = HT7038_buf[30];  
	Energy_dangqian_Apparent = HT7038_buf[36]; 
	
	Energy_nmins=Energy_dangqian-Energy_shangci;  //���㱾�ε������ϴζ������ܲ�ֵ
	Energy_shangci=Energy_dangqian;  //����ǰ��ֵΪ�ϴ�
	
	if (((hour >=10)&&(hour<11))||((hour>=19)&&(hour<21)))  //��
			rateJFPG = 1.6;
	else if (((hour >= 8) && (hour < 10))||((hour>=18)&&(hour<19))||((hour>=21)&&(hour<23)))  //��
			rateJFPG = 1.6;
	else if ((hour >= 12) && (hour < 17))  //ƽ 
			rateJFPG = 1.0;
	else if ((hour >= 23) || (hour < 8))  //��
			rateJFPG = 0.4;

  Charge=rateJFPG*Energy_nmins;//�շ�=��ǰʱ�ε��*n�������ĵ���
	Charge_sum=Charge+Charge_sum;  //�ܵ��
	
	
	/*******��ѹ������ƽ���*************/
	int Average_Vol,Average_Cur;

	 Average_Vol=(A_Phase_Vol+B_Phase_Vol+C_Phase_Vol)/3;
	 Average_Cur=(A_Phase_Cur+B_Phase_Cur+C_Phase_Cur)/3;
	
	if((A_Phase_Vol>=B_Phase_Vol)&&(A_Phase_Vol>=C_Phase_Vol))          Unbal_Vol=(float)A_Phase_Vol/(float)Average_Vol;  //Unbal_VolΪ��ѹ��ƽ���
	else if(((B_Phase_Vol>=A_Phase_Vol)&&(B_Phase_Vol>=C_Phase_Vol)))   Unbal_Vol=(float)B_Phase_Vol/(float)Average_Vol;
	else if(((C_Phase_Vol>=A_Phase_Vol)&&(C_Phase_Vol>=B_Phase_Vol)))   Unbal_Vol=(float)C_Phase_Vol/(float)Average_Vol;

	if((A_Phase_Cur>=B_Phase_Cur)&&(A_Phase_Cur>=C_Phase_Cur))          Unbal_Cur=(float)A_Phase_Cur/(float)Average_Cur;  //Unbal_Cur Ϊ������ƽ���
	else if(((B_Phase_Cur>=A_Phase_Cur)&&(B_Phase_Cur>=C_Phase_Cur)))   Unbal_Cur=(float)B_Phase_Cur/(float)Average_Cur;
	else if(((C_Phase_Cur>=A_Phase_Cur)&&(C_Phase_Cur>=B_Phase_Cur)))   Unbal_Cur=(float)C_Phase_Cur/(float)Average_Cur;
	
	
	/*******����������15mins������1���� ,һ��������һ��************/

	mins++;
	if(is_First==1)//����ǵ�һ���������ڣ���һ��15���ӣ�
	{
		E[mins]=Energy_dangqian;//ÿ���Ӽ�¼һ�ε���
		E_Reactive[mins]=Energy_dangqian_Reactive;
		E_Apparent[mins]=Energy_dangqian_Apparent;
//		P1=E[mins]*4;  //1/4Сʱ
//		P1_Reactive=E_Reactive[mins]*4;
//		P1_Apparent=E_Apparent[mins]*4;
				if(mins==15)
			  {
					P1=(E[mins]-E[1])*4;  //1/4Сʱ
					P1_Reactive=(E_Reactive[mins]-E_Reactive[1])*4;
					P1_Apparent=(E_Apparent[mins]-E_Apparent[1])*4;
					mins=0;
					is_First=0;
				}	 
	}
	else if(is_First==0)//������ǵ�һ����������
	{
		E[mins]=Energy_dangqian;//����ǰ�������θ���ǰ�������
		E_Reactive[mins]=Energy_dangqian_Reactive;
		E_Apparent[mins]=Energy_dangqian_Apparent;
		if(mins<=14)
		{
			P2=(E[mins]-E[mins+1])*4;
			P2_Reactive=(E_Reactive[mins]-E_Reactive[mins+1])*4;
			P2_Apparent=(E_Apparent[mins]-E_Apparent[mins+1])*4;
		}
		else if(mins==15)
		{
			P2=(E[mins]-E[1])*4;
			P2_Reactive=(E_Reactive[mins]-E_Reactive[1])*4;
			P2_Apparent=(E_Apparent[mins]-E_Apparent[1])*4;
			mins=0;
		}
	}
		if(P1>P2)//ȡ�ϴ�ֵ���浽P1��
		{
			P1=P1;  //
		}
		else
		{
			P1=P2;//��¼ʱ��
		}
		if(P1_Reactive>P2_Reactive)//ȡ�ϴ�ֵ���浽P1��
		{
			P1_Reactive=P1_Reactive;  //
		}
		else
		{
			P1_Reactive=P2_Reactive;//��¼ʱ��
		}
		if(P1_Apparent>P2_Apparent)//ȡ�ϴ�ֵ���浽P1��
		{
			P1_Apparent=P1_Apparent;  //
		}
		else
		{
			P1_Apparent=P2_Apparent;//��¼ʱ��
		}
	
	
	//����������ָʾ
	u8 PFlag,F_Active,F_Reactive=0;
	PFlag = HT7038_Read(rPFlag);
	F_Active = PFlag & (1<<3);
	F_Reactive = PFlag & (1<<7);
	if((F_Active==0)&&(F_Reactive==0)) quadrant=1;
	if((F_Active==1)&&(F_Reactive==0)) quadrant=2;
	if((F_Active==1)&&(F_Reactive==1)) quadrant=3;
	if((F_Active==0)&&(F_Reactive==1)) quadrant=4;
}


/*
���������ɼ�г��
��� 
0��UA
1��UB
2��UC
3��IA
4��IB
5��IC
*/
void Xiebo(unsigned char ph)  
{
    HT7038_Write(0xC9, 0x5A); ////ѡ��У��Ĵ���//У������дʹ��

    // HT7038_Write(0xC5,0x000000);//�������ݶ�ָ�����ùر��Զ�ͬ���������ݹ���

    // HT7038_Write(0xC0,0x00CCC0); //�����������ܣ�0xC0 ���ͨ��ѡ��+������

    // delay_ms(60);//�ȴ������������

    HT7038_Write(0xC1, 0x000000); // �������ݶ�ָ������
    HT7038_Write(0xC5, 0x000000); // �������ݶ�ָ�����ÿ����Զ�ͬ���������ݹ���
    HT7038_Write(0xC5, 0x000002); // �������ݶ�ָ�����ÿ����Զ�ͬ���������ݹ���

    for (int a = 0; a <= 1024; a++)
    {
        HT7038_Write(0xC1, a);
        ATT[a] = HT7038_Read(0x7F);  //ATT[a]��ʽΪ 7��Ԫ��Ϊһ�飬˳��ΪUA��UB��UC��IA��IB��IC�����߸�Ԫ��Ϊ0
        //		if(ATT[a]>32768) ATT[a]=ATT[a]-65536;
        //		else ATT[a]=ATT[a];
    }
		switch(ph)
		{
			case 0:
				for(int i = 0; i < 128; i ++)  //UA
				{
					ATT_UA[i] = ATT[i*7];
					ATT_UA[i+128] = ATT[i*7];
				}
				break;
			case 1:
				for(int i = 0; i < 128; i ++)  //UB
				{
					ATT_UB[i] = ATT[i*7+1];
					ATT_UB[i+128] = ATT[i*7+1];
				}
				break;
			case 2:
				for(int i = 0; i < 128; i ++)  //UC
				{
					ATT_UC[i] = ATT[i*7+2];
					ATT_UC[i+128] = ATT[i*7+2];
				}
				break;
			case 3:
				for(int i = 0; i < 128; i ++)  //IA
				{
					ATT_IA[i] = ATT[i*7+3];
					ATT_IA[i+128] = ATT[i*7+3];
				}
				break;
			case 4:
				for(int i = 0; i < 128; i ++)  //IB
				{
					ATT_IB[i] = ATT[i*7+4];
					ATT_IB[i+128] = ATT[i*7+4];
				}
				break;
			case 5:
				for(int i = 0; i < 128; i ++)  //IC
				{
					ATT_IC[i] = ATT[i*7+5];
					ATT_IC[i+128] = ATT[i*7+5];
				}
				break;
			default:
				break;
		}

    HT7038_Write(0xC5, 0x000002); // �������ݶ�ָ�����ÿ����Զ�ͬ���������ݹ���
    delay_ms(50);
    HT7038_buf[33] = HT7038_Read(w_PtrWavebuff);
    HT7038_buf[34] = HT7038_Read(0x7F);
}


	uint8_t test_isfenzha=0;
/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void)
{
    /* USER CODE BEGIN 1 */
    unsigned int tingdian_tmp;
    unsigned char array_temp[2];
    /* USER CODE END 1 */

    /* MCU Configuration--------------------------------------------------------*/

    /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    HAL_Init();

    /* USER CODE BEGIN Init */
    delay_init(48);
    /* USER CODE END Init */

    /* Configure the system clock */
    SystemClock_Config();

    /* USER CODE BEGIN SysInit */
		MX_DMA_Init();
    /* USER CODE END SysInit */

    /* Initialize all configured peripherals */
    MX_GPIO_Init();
    MX_ADC1_Init();
    MX_TIM6_Init();
    MX_UART4_Init();
    MX_USART1_UART_Init();
    MX_USART3_UART_Init();
    MX_RTC_Init();
    /* USER CODE BEGIN 2 */

    IWDG_Feed(); // ι��
    EEPROM_R(Addr_Type_Cur, array_temp, 1, 0xA0);
    Type_Cur = array_temp[0];
    Cur_Switch(Type_Cur);
    DW_3D_E2_read();

    HAL_TIM_Base_Start_IT(&htim6);
    initial_lcd();
    clear_screen();

    HT7038Reset();        // ht7038��λ
    HT7038_EEP_Initial(); // ht7038�Ĵ����洢��ȡ
    HT7038_Init();        // ����ht7038ģ�鹦��
                          //	LEDA_ON;
    LEDA_FLAG = 1;

    Wait_selftest(); // �ȴ���ʼ��
    N_Tingdian = 0;
    F_gz = 0x00;
    F_gz_disp = 0x0f; // �޹���
    clear_flags();    // ��Ҫ��

    IWDG_Feed(); // ι��

    factors_init();
    state_init();

    F_Disp = 1;
    F_key = 0;

    sssj_N = 1;
    sssj_N_xunhuan = 1;
    F_re_sta = 0;
    clear_flags();
    F_sssj = 0;
    tingdian_tmp = 0x00;
    tingdian_tmp = read_tingdian();
    if (tingdian_tmp == 0x55)
    {
        tingdian_tmp = 0;
        clear_tingdian();
        if (shangdian != 0)
        {
            F_record_write = 1;
            gz_reason = trip_reason_powerdown;
            F_tim_gz = 1;
            GZ_ph = 1;
        }
        if (isfenzha == 0)
        {
            F_gz = 0;
        }
    }
    if ((isfenzha == 0) && (shangdian == 1)) // isfenzha==1Ϊ��բ״̬
    {
        if (isfenzha == 0)
        {
            delay_ms(2);
            if (isfenzha == 0)
            {
                F_shangdian_hezha = 1;
            }
        }
    }
   

    USART_LCD_Transmit(57,1); //1Ϊ��λ����
//		HAL_UART_Receive_IT(&huart1,(uint8_t*)tmp_uart_rx_1,100);
		HAL_ADCEx_Calibration_Start(&hadc1);
		HAL_ADC_Start_DMA(&hadc1,ADC_ConvertedValue,8);
		HAL_ADC_Start_DMA(&hadc1,ADC_ConvertedValue,8);
		HAL_ADC_Start_DMA(&hadc1,ADC_ConvertedValue,8);
		
		
//		
//    /* USER CODE END 2 */
//		uint8_t array_test[1]={0x55};
//    /* Infinite loop */
//    /* USER CODE BEGIN WHILE */
//		uint8_t buffercui[180];
//		  for (int i = 0; i < 20; i++) {
//        buffercui[9*i] = 0XFF;
//			   buffercui[9*i+1] = 0XFF;
//			   buffercui[9*i+2] = 0XFF;
//			   buffercui[9*i+3] = 0XFF;
//			   buffercui[9*i+4] = 0XFF;
//			   buffercui[9*i+5] = 0XFF;
//			   buffercui[9*i+6] = 0XFF;
//			   buffercui[9*i+7] = 0XFF;
//			   buffercui[9*i+8] = 0XFF;
//			 
//			  
//			  
//    }
//			
//			MODIFY_EEP_W(0,buffercui,180,0xA0);
//	gz_disp=2222;
//Write_Record(1,0);
//	Write_Record(1,0);  
//EEPROM_R(0,buffercui,180,0xA0);
    while (1)
    {
			
				Wait_selftest(); // �ȴ���ʼ��
				//HAL_UART_Transmit(&huart3,(uint8_t*)(array_test),1,0xffff);
				//test_isfenzha=isfenzha;
//            USART_LCD_Transmit(82, 0); // ����Ϊ���ݳ��ȣ�������ʶ����  //0Ϊʵʱ����
//            delay_ms(1000);
//            USART_LCD_Transmit(41, 1); // 1Ϊ��λ����
				uart_com_process();
            //delay_ms(10);
				if(F_lcd_transmit_D==1)//1min����һ�ε�λ��Ϣ  
				{
					USART_LCD_Transmit(57,1); //1Ϊ��λ����
					F_lcd_transmit_D=0;
					F_lcd_realtime=0;
				}
				if(F_lcd_realtime==1) //1s����һ��ʵʱ��Ϣ
				{
						USART_LCD_Transmit(90,13);
						USART_LCD_Transmit(90,14);
					HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
					if(F_lcd_firsttime==0) //�ϵ�1s����һ�ε�λ��Ϣ
					{
						USART_LCD_Transmit(57, 1); // 1Ϊ��λ����
						F_lcd_firsttime=2;
						delay_ms(10);
					}
					if(F_lcd_cnt==0)
					USART_LCD_Transmit(82, 0);//ʵʱ����1
					if(F_lcd_cnt==1)
					USART_LCD_Transmit(10,2); //ʵʱ����2
					if(F_lcd_cnt==2)
					USART_LCD_Transmit(57,12); //ʵʱ����3
				
					F_lcd_cnt++;
					if(F_lcd_cnt==3) F_lcd_cnt=0;
					F_lcd_realtime=0;
				}
				if (F_HT7038_Read == 1)
				{
					CurrentDataReadFun();
					F_HT7038_Read = 0;
				}
				hand_short_process(); // �ⲿ�̽ӷֺ�բ
				IWDG_Feed();
				if (isfenzha == 0) // ��բ״̬
				{
						hezha_process();
				}
				else
				{
						fenzha_process();
				}
				Cur_sample_process();  // ���������봦��
				Vol_sample_process();  // ��ѹ�����봦��
				//Anti_Islanding_Process();
				//Temperature_Process(); // �¶ȴ���		//������2023.2.7
				Run_time_process();
				Day_updata_process();
				if (F_record_write == 1) // �������ϣ�����д���ϼ�¼��־λ
				{
						if (F_guocheng == 0)
						{
								Write_Record(gz_reason, GZ_ph); //////
								F_record_write = 0;
						}
				}
				if (F_leak_record == 1) // ��ֵ��ʱ������ϼ�¼��
				{
						F_leak_record = 0;
						T_leak_record = 0;
						Write_Leak_Record();
				}
				if(F_bill==1) //1min һ�� 
				{
					Time_bill();
					F_bill=0;
				}
//				if(F_Harmonic_Content==1)  //30sһ��
//				{
//					Harmonic_Content_Calculate();
//					F_Harmonic_Content=0;
//				}
				

        /* USER CODE END WHILE */

        /* USER CODE BEGIN 3 */
    }
    /* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
    RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

    /** Initializes the RCC Oscillators according to the specified parameters
     * in the RCC_OscInitTypeDef structure.
     */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI | RCC_OSCILLATORTYPE_LSI;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
    RCC_OscInitStruct.LSIState = RCC_LSI_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI_DIV2;
    RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL12;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        Error_Handler();
    }

    /** Initializes the CPU, AHB and APB buses clocks
     */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
    {
        Error_Handler();
    }
    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC | RCC_PERIPHCLK_ADC;
    PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;
    PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV4;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
    {
        Error_Handler();
    }
}

/* USER CODE BEGIN 4 */
// �ض���fputc����
int fputc(int ch, FILE *f)
{
    while ((USART1->SR & 0X40) == 0)
        ; // ѭ�����ͣ�ֱ���������
    USART1->DR = (u8)ch;
    return ch;
}
/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void)
{
    /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */
    __disable_irq();
    while (1)
    {
    }
    /* USER CODE END Error_Handler_Debug */
}

#ifdef USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t *file, uint32_t line)
{
    /* USER CODE BEGIN 6 */
    /* User can add his own implementation to report the file name and line number,
       ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
    /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
