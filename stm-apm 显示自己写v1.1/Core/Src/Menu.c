#include "menu.h"
#include "lcd.h"
#include "display_ziku.h"
#include "gpio.h"
#include "rtc.h"
#include "tool.h"
#include <stdbool.h>
#include <stdlib.h>
#define TOTAL_SCREENS 13 // ��ѯ���ֽ���ҳ��
#define ITEMS_PER_PAGE 2

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
#define A_QX 0x10 // ȱ��
#define B_QX 0x11
#define C_QX 0x12
#define Gz_QL 0x13
#define A_sy 0x14
#define B_sy 0x15
#define C_sy 0x16
#define Tem_IN_N 55
#define Tem_IN_A 65
#define Tem_IN_B 57
#define Tem_IN_C 63

#define Tem_OUT_N 59
#define Tem_OUT_A 51
#define Tem_OUT_B 61
#define Tem_OUT_C 53
extern const int BUFFER_SIZE;
extern int write_ptr; // д��ָ�룬��ʼλ��Ϊ0
extern int read_ptr;  // ��ȡָ�룬��ʼλ��Ϊ0
char F_GUZHANG = 0;   // ʵ���˳�����
extern volatile unsigned char F_Dataval;
RTC_DateTypeDef sdatestructure;
RTC_TimeTypeDef stimestructure;
char F_AEorREorALLE; // �й�����1or�޹�����2or�ܵ���3��־λ
char f_f = 1;
int a1; // �˵�����ָ��
extern bool F_initialization;
char qiehuan = 0; // ������ȷor����
int one = 1;
volatile unsigned char tim_m3, tim_d3, tim_h3, tim_f3, tim_s3, tim_m3temp, tim_d3temp, tim_h3temp, tim_f3temp, tim_s3temp, tim_y3, tim_y3temp; // ʱ�����
unsigned char nian_qian[3] = {0};                                                                                                              // ʱ�����
volatile unsigned char SET_D_Cur = 0;                                                                                                          // ������λ��
unsigned char mima[4];                                                                                                                         // ���������
unsigned char mima_set[4], mima_settemp[4];                                                                                                    // �趨������
unsigned char mima_set_compare[4];                                                                                                             // ����������ʱ��������ٺ�
char F_jiaozhuned;                                                                                                                             // У׼��ɱ�־λ
volatile unsigned char Cal_state = 0;                                                                                                          // ��ʾУ׼����
char F_adjustbegin;                                                                                                                            // ��ʼУ׼��־λ
uint8_t F_adjustswitch;                                                                                                                        // У׼�����л���־λ
volatile unsigned int SET_I_VAL;                                                                                                               // ��������ɶ
char isfenzha = 1;                                                                                                                             // ��բָʾ
extern int F_Y, F_Ypro;                                                                                                                        // �˵��ڼ�ҳ��־λ
int array_size;
extern int a;             // �˵�λ��ָ��
extern int b;             // �˵���������ָ��
char F_Ftoer;             // ��ѯ����Ͳ˵��������ֱ�־λ
extern char F_MAINormenu; // �жϷ��滹�ǲ˵���־���Ǳ������� 0���� 1�������� 2��������
extern unsigned char maohao[16];
extern int key;
static int current_screen = 0;
extern int F_mainchange;
volatile unsigned char D_LCur = 4, D_A_LCur = 0, LC_N = 0, TH_LCur, Vol_g, Vol_q, TH_LCurtemp, Vol_gtemp, Vol_qtemp, D3_Curtemp;                              // ©�������λָ��
unsigned char N_GY_yanshi = 0, N_QY_yanshi = 0, D_GY_yanshi = 0, D3_Cur = 0, D_QY_yanshi = 0, D_SY_yanshi, D_SY_yanshitemp, D_GY_yanshitemp, D_QY_yanshitemp; // �ڶ�ҳ��λָ��
unsigned char D2_Cur = 0, TH_DL = 0, TH_Long_Cur = 0, D_Cur, D_Curtemp, TH_Long_Curtemp, D2_Curtemp, TH_DLtemp, Type_Cur, Type_Curtemp;                       //     ����ҳ��λָ��
unsigned char baud, TH_TEM_UP, TH_TEM_DOWN, TH_TEM_UPtemp, TH_TEM_DOWNtemp, baudtemp;                                                                         // ����ҳ��λָ��
bool F_Special_wave, F_trip_ld, F_auto_ld, F_TB_trip, F_TB_triptemp, F_Special_wavetemp;                                                                      // ������һҳָ��
bool F_trip_QX, F_trip_qy, F_trip_gy, F_trip_QL;                                                                                                              // �����ڶ�ҳָ��
bool F_ip_3, F_ip, F_trip_gl, F_trip_sy, F_iptemp, F_ip_3temp, F_trip_sytemp;                                                                                 // ��������ҳָ��
bool DY_hezha, LD_hezha, shangdian, jiaozhun, jiaozhuntemp, shangdiantemp, LD_hezhatemp, DY_hezhatemp;                                                        // ��������ҳָ��
bool F_TX, wendu, DL_hezha, DL_hezhatemp, wendutemp, F_TXtemp;                                                                                                // ��������ҳָ��
volatile unsigned int Num_tripall, Num_clearall, Num_triplock, Num_tripleak, Num_tripcur, Num_tripvol, Num_triphand, Num_triptest, Num_tripdelay, Num_tripinstant, Num_leakover, Num_leakprotect;
extern unsigned char F_LEAK_OPEN_CLOSE, F_open;                                                     // ���ڷ���������ֲ�ͬ���ͷֺ�բ
int current_page = 0;                                                                               // ���ݽ���ҳ��
volatile unsigned char F_disp_jg, F_disp_tr, F_hezha_state, F_fenzha_state, F_gz_disp = 0x0F, F_ch; // ���Ϻͷֺ�բ״̬��ر�־λ
volatile unsigned int gz_disp;
extern char F_FENHEZHA;
extern uint8_t max_value; // ad������¶�
extern uint8_t tem;
volatile unsigned char DI0, DI1, DI2, DI3;
unsigned char self_addr_code[6];
unsigned char self_addr_codetemp[6];
unsigned char add_1_1[2] = {0}, add_2_1[2] = {0}, add_3_1[2] = {0}, add_4_1[2] = {0}, add_5_1[2] = {0}, add_6_1[2] = {0};
unsigned char add_1_2[2] = {0}, add_2_2[2] = {0}, add_3_2[2] = {0}, add_4_2[2] = {0}, add_5_2[2] = {0}, add_6_2[2] = {0};
volatile unsigned int Leak_Cur_disp = 0;
extern unsigned char zifu_dian[5];
volatile signed int HT7038_buf1[300] = {0}, HT7038_buf11[300] = {0};
extern int p_c_day;
uint8_t faultdata_buffer[180];
extern unsigned char Lcd_data_array[4][100];
unsigned char ctrlword[5], ctrlwordtemp[5];
unsigned char nian[3] = {0}, yue[3] = {0}, ri[3] = {0}, shi[3] = {0}, fen[3] = {0}, miao[3] = {0};
unsigned char dianliu[9][6] =
    {
        "0.03A", "0.05A", "0.1A", "0.2A", "0.3A", "0.5A", "0.8A", "1A", "Auto"};
unsigned char shijian[5][6] =
    {
        "0.2s", "0.3s", "0.5s", "1s", "0.1s"};
unsigned char DIANYA[6][6] =
    {
        "250V", "260V", "270V", "280V", "290V", "300V"};
unsigned char DIANYA1[6][8] =
    {
        "250V", "260V", "270V", "280V", "290V", "300V"};

unsigned char hz_up[6][8] =
    {
        "50Hz", "52Hz", "54Hz", "56Hz", "58Hz", "60Hz"};
unsigned char hz_down[6][8] =
    {
        "40Hz", "42Hz", "44Hz", "46Hz", "48Hz", "50Hz"};
unsigned char DIANYA_1[6][6] =
    {
        "140V", "150V", "160V", "170V", "180V", "190V"};
unsigned char DIANYA_11[6][8] =
    {
        "140V", "150V", "160V", "170V", "180V", "190V"};
unsigned char SY_yanshi[10][6] =
    {
        "1s", "2s", "3s", "4s", "5s", "6s", "7s", "8s", "9s", "10s"};
unsigned char GY_yanshi[10][6] =
    {
        "1s", "2s", "3s", "4s", "5s", "6s", "7s", "8s", "9s", "10s"

};
unsigned char QY_yanshi[10][6] =
    {
        "1s", "2s", "3s", "4s", "5s", "6s", "7s", "8s", "9s", "10s"

};
unsigned char D3_DW[6][6] =
    {
        "4r", "6r", "8r", "10r", "12r", "14r"

};
unsigned char GUOLIU_T[8][6] =
    {
        //"15s","30s","60s","120s","240s"
        "3s", "4s", "6s", "8s", "10s", "12s", "16s", "18s"

};
unsigned char D2_DW[6][6] =
    {
        "2r", "4r", "6r", "8r", "10r", "12r"

};
unsigned char D2_T[7][6] =
    {
        //"0.1s","0.2s","0.3s","0.4s","27S"
        "0.1s", "0.2s", "0.3s", "0.4s", "0.6s", "0.8s", "1s"

};
unsigned char Type_cur_show[5][6] =
    {

        "125A", "250A", "400A", "630A", "800A"

};

unsigned char TEM_UP_show[6][6] =
    {
        "50", "60", "70", "80", "90", "100"};
unsigned char TEM_UP_show1[6][8] =
    {
        "50", "60", "70", "80", "90", "100"};

unsigned char TEM_DOWN_show[5][6] =
    {
        "10", "20", "30", "40", "50"};
unsigned char botelv[4][6] =
    {
        "1200", "2400", "4800", "9600"

};
unsigned char guoliu_type1[9][6] =
    {
        "50A", "63A", "70A", "80A", "90A", "100A", "110A", "120A", "125A"};
unsigned char guoliu_type2[20][6] =
    {
        "63A", "70A", "80A", "90A", "100A", "110A", "120A", "130A", "140A", "150A", "160A", "170A", "180A", "190A", "200A", "210A", "220A", "230A", "240A", "250A"};
unsigned char guoliu_type21[20][8] =
    {
        "63A", "70A", "80A", "90A", "100A", "110A", "120A", "130A", "140A", "150A", "160A", "170A", "180A", "190A", "200A", "210A", "220A", "230A", "240A", "250A"};
unsigned char guoliu_type3[13][6] =
    {
        "160A", "180A", "200A", "220A", "240A", "260A", "280A", "300A", "320A", "340A", "360A", "380A", "400A"};
unsigned char power_waring[13][8] =
    {
        "70kW", "75kW", "80kW", "85kW", "90kW", "95kW", "100kW", "105kW", "110kW", "115kW", "120kW", "125kW", "130kW"};
unsigned char u_UB_waring[6][8] =
    {
        "80%", "84%", "88%", "92%", "96%", "100%"};
unsigned char i_UB_waring[6][8] =
    {
        "80%", "84%", "88%", "92%", "96%", "100%"};
unsigned char Powerconsumption_warning[4][8] =
    {
        "1000kWh", "2000kWh", "3000kWh", "4000kWh"};

unsigned char p_waring[10][8] =
    {
        "60kW", "70kW", "80kW", "90kW", "100kW", "110kW", "120kW", "130kW", "140kW", "150kW"};
unsigned char q_waring[10][8] =
    {
        "60kvar", "70kvar", "80kvar", "90kvar", "100kvar", "110kvar", "120kvar", "130kvar", "140kvar", "150kvar"};
unsigned char s_warning[10][8] =
    {
        "60kvar", "70kvar", "80kvar", "90kvar", "100kvar", "110kvar", "120kvar", "130kvar", "140kvar", "150kvar"};
unsigned char Cos_warning[5][8] =
    {
        "0.6", "0.7", "0.8", "0.9", "1"};
unsigned char guoliu_type4[14][6] =
    {
        "252A", "280A", "310A", "340A", "370A", "400A", "430A", "460A", "490A", "520A", "550A", "580A", "610A", "630A"};
unsigned char guoliu_type5[7][6] =
    {
        "320A", "400A", "480A", "560A", "630A", "710A", "790A"};
unsigned char guzhang_yuanyin[13][5] =
    {
        "Ƿѹ", "��ѹ", "©��", "����", "ͣ��", "�ֶ�", "����", "Զ��", "����", "ȱ��", "ȱ��", "����", "��˲"};

fault fault_buffer[20];
unsigned char guoliu_show[20][6] = {0};

char D_Cur_P;
extern unsigned char dian[16];
unsigned char qirigang[16] = {
    0x00,
    0x00,
    0xC0,
    0x38,
    0x06,
    0x00,
    0x00,
    0x00,
    0x30,
    0x0E,
    0x01,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
};
extern uint8_t temperature[8];
unsigned char xiaogang[16] = {
    0x00,
    0x80,
    0x80,
    0x80,
    0x80,
    0x80,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
};
unsigned char xiaomaohao[16] = {
    0x00,
    0x30,
    0x30,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x0C,
    0x0C,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
};
void showScreen(int screenIndex);
void mainmenu();    // ���˵�
void meun1();       // �˵�1����
void meun2();       // �˵�2����
void meun3();       // �˵�3����
void meun4();       // �˵�4����
void meun5();       // �˵�5����
void meun();        // ��ѯ������
void screenbase1(); // ��ѯ1����
void screenbase2(); // ��ѯ2����
void screenbase3(); // ��ѯ3����
void screenbase4(); // ��ѯ4����
void screenbase5(); // ��ѯ5����
void screenbase6(); // ��ѯ6����
void screenbase7(); // ��ѯ7����
void screenbase8();
void screenbase9();
void screenbase10();
void screenbase11();
void screenbase12();
void screenbase13();
void demand();
void menu_fault();
void power_quality();
void displayExceededVoltages();
void meun_data();   // ��բ������ѯ����
void meun_adjust(); // У׼����
void meun_protect1();
void meun_protect2();
void meun_protect3();
void meun_protect4();
void meun_protect5();
void Power_parameters(); // ���ܲ���
void Disp_Write_time(void);
void menu_mimaset(); // �޸�����
int mimaset();
void timechange();
void warning_setting();
void Disp_date(void);
void Disp_time(void);
void fenzhaing();   // ���ڷ�բ...
void hezhaing();    // ���ں�բ...
void problemdisp(); // ������ʾ���
void updata_c();    // ���¸��ĵ�λ
void judge();       // �жϵ�λ�Ƿ����
void ctrlword4_analyze(void);
void ctrlword2_analyze(void);
void ctrlword3_analyze(void);
void I_VAL_handle();
void faultdisp();
void USART_LCD_Transmit(unsigned char len, unsigned char ch);
void value_to_ascii1(int value, char *ascii_array)
{
    char temp_str[12]; // ��ʱ��������ַ���������Ҫ�㹻��������������������

    // ������ת��Ϊ�ַ���
    sprintf(temp_str, "%02d", value);

    // ���ַ����е�ÿ���ַ�ת��Ϊ ASCII ֵ����ŵ�������
    for (int i = 0; i < strlen(temp_str); ++i)
    {
        ascii_array[i] = temp_str[i];
    }
    ascii_array[strlen(temp_str)] = '\0'; // ����ַ���������
}
void int_to_ascii(int num, char *str)
{
    sprintf(str, "%d", num); // ʹ�� sprintf ��������ʽ�����ַ�����
}
void disp_data(int x, int y, char i, int value) // ��ʾ����
{
    if (value > 999)
    {
        value = 999;
    }
    value_to_ascii(value, zifu_dian);
    if (i == 16)
        Lcd12864_Write16CnCHAR(0, x, y, zifu_dian);
    else if (i == 14)
        Lcd12864_Write14CnCHAR(0, x, y, zifu_dian);
}
typedef struct meun
{
    char *NAME;
    unsigned char (*A)[6]; // ʹ��ָ�������ָ��
    unsigned char *value;
    unsigned char array_size;
    void (*func)(void);
} meuntype;
void displayMenu(meuntype menu[], int totalItems, int page)
{
    int x;
    int start = page * ITEMS_PER_PAGE;
    int end = start + ITEMS_PER_PAGE;
    if (end > totalItems)
        end = totalItems;
    for (int i = 0; i < totalItems; i++)
    {
        Lcd12864_Write16CnCHAR(0, 0, 2 * i, menu[i].NAME);
        x = strlen(menu[i].NAME);
        display_graphic_8x16(2 * i + 1, 8 * x + 2, maohao);
    }
    if (key == KEY_LEFT_PRES && *(menu[a].value) < menu[a].array_size)
    {
        clear_screen();
        (*(menu[a].value))++;
    }
    else if (key == KEY_RIGHRT_PRES && *(menu[a].value) > 0)
    {
        clear_screen();
        (*(menu[a].value))--;
    }

    switch (a) // a�ǰ��˼��� d���жϳ������м���    //���switch��ѡ������һ��
    {
    case 0:
        if (a < totalItems)
        {

            display_ASCIIstring_8x16_fanxian(1, 93, menu[0].A[*(menu[0].value)]);
            if (totalItems > 1)
                display_ASCIIstring_8x16(3, 93, menu[1].A[*(menu[1].value)]);
            if (totalItems > 2)
                display_ASCIIstring_8x16(5, 93, menu[2].A[*(menu[2].value)]);
            if (totalItems > 3)
                display_ASCIIstring_8x16(7, 93, menu[3].A[*(menu[3].value)]);
        }

        break;
    case 1:
        if (a < totalItems)
        {

            display_ASCIIstring_8x16(1, 93, menu[0].A[*(menu[0].value)]);
            if (totalItems > 1)
                display_ASCIIstring_8x16_fanxian(3, 93, menu[1].A[*(menu[1].value)]);
            if (totalItems > 2)
                display_ASCIIstring_8x16(5, 93, menu[2].A[*(menu[2].value)]);
            if (totalItems > 3)
                display_ASCIIstring_8x16(7, 93, menu[3].A[*(menu[3].value)]);
        }
        break;

    case 2:
        if (a < totalItems)
        {

            display_ASCIIstring_8x16(1, 93, menu[0].A[*(menu[0].value)]);
            if (totalItems > 1)
                display_ASCIIstring_8x16(3, 93, menu[1].A[*(menu[1].value)]);
            if (totalItems > 2)
                display_ASCIIstring_8x16_fanxian(5, 93, menu[2].A[*(menu[2].value)]);
            if (totalItems > 3)
                display_ASCIIstring_8x16(7, 93, menu[3].A[*(menu[3].value)]);
        }
        break;
    case 3:
        if (a < totalItems)
        {

            display_ASCIIstring_8x16(1, 93, menu[0].A[*(menu[0].value)]);
            if (totalItems > 1)
                display_ASCIIstring_8x16(3, 93, menu[1].A[*(menu[1].value)]);
            if (totalItems > 2)
                display_ASCIIstring_8x16(5, 93, menu[2].A[*(menu[2].value)]);
            if (totalItems > 3)
                display_ASCIIstring_8x16_fanxian(7, 93, menu[3].A[*(menu[3].value)]);
        }
        break;
    }
    if (key == KEY_UP_PRES)
    {
        a++;
        if (a > totalItems - 1) //&&F_Y!=4
        {
            clear_screen();
            a = 0;
            clear_screen();
            //		if(F_Y==4) F_Y=5;        //�����ṹ��˵�
            if (F_Y == 3)
                F_Y = 5;
            if (F_Y == 2)
                F_Y = 3;
            if (F_Y == 1)
                F_Y = 2;
            if (F_Y == 0)
                F_Y = 1;
        }
        //	}else if(a>totalItems-1&&F_Y==4) a=totalItems-1;
    }
    else if (key == KEY_DOWN_PRES)
    {
        a--;
        if (a < 0)
        {
            a = 0;
            clear_screen();
            if (F_Y == 1)
                F_Y = 0;
            if (F_Y == 2)
                F_Y = 1;
            if (F_Y == 3)
                F_Y = 2;
            if (F_Y == 4)
                F_Y = 3;
        }
    }

    else if (key == KEY_AFFIRM_PRES) // ȷ��֮��Ҫ�����ݱȽϣ��б����������
    {
        judge();
        a++;
        if (a > totalItems - 1 && F_Y != 4)
        {
            clear_screen();
            a = 0;
            clear_screen();
            if (F_Y == 3)
                F_Y = 5;
            if (F_Y == 2)
                F_Y = 3;
            if (F_Y == 1)
                F_Y = 2;
            if (F_Y == 0)
                F_Y = 1;
        }
        else if (a > totalItems - 1 && F_Y == 4)
            a = totalItems - 1;

        /* USER CODE END WHILE */

        /* USER CODE BEGIN 3 */
    }
}
void MEUN() // �жϲ�ͬ�˵��ı�־λȷ��չʾʲô
{
    for (int i = 0; i < 300; i++)
    {
        HT7038_buf1[i] = HT7038_buf11[i];
    }
    if (F_initialization == 0)

    {
        Lcd12864_Write16CnCHAR(0, 0, 3, " ���ڳ�ʼ��...");
    }

    else
    {
        if (((F_hezha_state != 0) || (F_fenzha_state != 0)) && (F_gz_disp == 0x0F))
        {
            if (F_hezha_state == 1)
            {
                hezhaing(); // ���ں�բ
            }
            else if (F_fenzha_state == 1)
            {
                fenzhaing(); // ���ڷ�բ
            }
        }
        else if (F_gz_disp == 0x0F) // δ��������
        {
            if (F_MAINormenu == 0)
            {
                meun();
            }
            else if (F_MAINormenu == 7 && F_Y == 0)
            {
                mimaset();
            }
            else if (F_MAINormenu == 10 && F_Y == 0)
            {
                mainmenu();
            }
            else if (F_MAINormenu == 1 && F_Y == 0)
            {
                meun1();
            }
            else if (F_MAINormenu == 1 && F_Y == 1)
            {
                meun2();
            }
            else if (F_MAINormenu == 1 && F_Y == 2)
            {
                meun3();
            }
            else if (F_MAINormenu == 1 && F_Y == 3)
            {
                meun4();
            }
            else if (F_MAINormenu == 1 && F_Y == 4)
            {
                meun5();
            }
            else if (F_MAINormenu == 1 && F_Y == 5) // �޸�ʱ������
            {
                timechange();
            }
            else if (F_MAINormenu == 1 && F_Y == 6) // �޸�����͵�λ����
            {
                menu_mimaset();
            }
            else if (F_MAINormenu == 2 && F_Ypro == 0) // ��������
            {
                meun_protect1();
            }
            else if (F_MAINormenu == 2 && F_Ypro == 1) // ��������
            {
                meun_protect2();
            }
            else if (F_MAINormenu == 2 && F_Ypro == 2) // ��������
            {
                meun_protect3();
            }
            else if (F_MAINormenu == 2 && F_Ypro == 3) // ��������
            {
                meun_protect4();
            }
            else if (F_MAINormenu == 2 && F_Ypro == 4) // ��������
            {
                meun_protect5();
            }
            else if (F_MAINormenu == 4) // F_MAINormenu==4��բ��������
            {
                menu_fault(); // ��բ��������
            }
            else if (F_MAINormenu == 5)
            {
                meun_adjust(); // У׼����
            }
            else if (F_FENHEZHA == 1 && F_MAINormenu == 3)
            {
                fenzhaing(); // ���ڷ�բ
            }
            else if (F_FENHEZHA == 2 && F_MAINormenu == 3)
            {
                hezhaing(); // ���ں�բ
            }
            else if (F_MAINormenu == 6 && F_AEorREorALLE == 0)
            {
                Power_parameters();
            }
            else if (F_MAINormenu == 6 && F_AEorREorALLE == 1)
            {
                screenbase3();
            }
            else if (F_MAINormenu == 6 && F_AEorREorALLE == 2)
            {
                screenbase9();
            }
            else if (F_MAINormenu == 8)
            {
                power_quality(); // ����Ʒ��se9();
            }
            else if (F_MAINormenu == 9)
            {
                warning_setting();
                //				 demand();//
            }
            else if (F_MAINormenu == 12)
            {
                meun_data();
            }
            else if (F_MAINormenu == 13)
            {
                faultdisp();
            }
            else if (F_MAINormenu == 15)
            {
                displayExceededVoltages();
            }
        }
        else if (F_gz_disp != 0x0F) // �й���,��ʾ������ؽ���
        {
            problemdisp();
            if (key == KEY_AFFIRM_PRES) // ����״̬����ȷ������ʵ�ֹ�����ʾ�˳�
            {

                USART_LCD_Transmit(1, 4);
            }
        }
    }
}
void meun1() // �˵�1
{

    meuntype menu[] = {
        {"1©�緧ֵ", dianliu, &D_LCur, 7},
        {"2©����ʱ", shijian, &TH_LCur, 4},
        {"3��ѹ��λ", DIANYA, &Vol_g, 5},
        {"4Ƿѹ��λ", DIANYA_1, &Vol_q, 5},

    };
    int totalItems = sizeof(menu) / sizeof(menu[0]);
    displayMenu(menu, totalItems, 0);
    ctrlword[3] &= 0x0F;
    ctrlword[3] += (D_LCur << 4);
    ctrlword4_analyze();
}
void meun2() // �˵�2
{

    meuntype menu[] = {
        {"5ʧѹ��ʱ", SY_yanshi, &D_SY_yanshi, 9},
        {"6��ѹ��ʱ", GY_yanshi, &D_GY_yanshi, 9},
        {"7Ƿѹ��ʱ", QY_yanshi, &D_QY_yanshi, 9},
        {"8˲ʱ��λ", D3_DW, &D3_Cur, 5},

    };
    int totalItems = sizeof(menu) / sizeof(menu[0]);
    displayMenu(menu, totalItems, 0);
}
void meun3() // �˵�3
{
    if (Type_Cur == 0)
    {
        D_Cur_P = 8;
        for (int i = 0; i < 9; ++i)
        {
            strcpy((char *)guoliu_show[i], (char *)guoliu_type1[i]);
        }
    }
    if (Type_Cur == 1)
    {
        D_Cur_P = 19;
        for (int i = 0; i < 20; ++i)
        {
            strcpy((char *)guoliu_show[i], (char *)guoliu_type2[i]);
        }
    }
    if (Type_Cur == 2)
    {
        D_Cur_P = 12;
        for (int i = 0; i < 13; ++i)
        {
            strcpy((char *)guoliu_show[i], (char *)guoliu_type3[i]);
        }
    }
    if (Type_Cur == 3)
    {
        D_Cur_P = 13;
        for (int i = 0; i < 14; ++i)
        {
            strcpy((char *)guoliu_show[i], (char *)guoliu_type4[i]);
        }
    }
    if (Type_Cur == 4)
    {
        D_Cur_P = 7;
        for (int i = 0; i < 7; ++i)
        {
            strcpy((char *)guoliu_show[i], (char *)guoliu_type5[i]);
        }
    }

    meuntype menu[] = {
        {"9������λ", guoliu_show, &D_Cur, D_Cur_P},
        {"10����ʱ��", GUOLIU_T, &TH_Long_Cur, 7},
        {"11���ӵ�λ", D2_DW, &D2_Cur, 5},
        {"12����ʱ��", D2_T, &TH_DL, 5},

    };
    int totalItems = sizeof(menu) / sizeof(menu[0]);
    displayMenu(menu, totalItems, 0);
}
void meun4() // �˵�3
{
    meuntype menu[] = {
        {"13���·�բ", TEM_UP_show, &TH_TEM_UP, 5},
        {"14���º�բ", TEM_DOWN_show, &TH_TEM_DOWN, 4},
        {"15ͨ������", botelv, &baud, 3},
        {"16�Ǽ�����", Type_cur_show, &Type_Cur, 4}, // ���û������������

    };
    int totalItems = sizeof(menu) / sizeof(menu[0]);
    displayMenu(menu, totalItems, 0);
}
void meun5() // �˵�4
{
    meuntype menu[] = {
        {"17����", TEM_UP_show, &TH_TEM_UP, 5},
        {"18ʱ��", TEM_DOWN_show, &TH_TEM_DOWN, 4},
        //        {"15ͨ������", botelv,&baud,5},
        //        {"16�Ǽ�����", D2_T,&TH_DL,5},            //���û������������

    };
    int totalItems = sizeof(menu) / sizeof(menu[0]);
    displayMenu(menu, totalItems, 1);
}
void (*screenbase_funcs[13])() = {
    screenbase1, screenbase2, screenbase3, screenbase4, screenbase5, screenbase6, screenbase7, screenbase8, screenbase9, screenbase10};
void meun() // ����
{
    screenbase_funcs[F_mainchange]();
    //	 if(F_mainchange==1)
    //	 {
    //		  showScreen(current_screen);

    //    // ���±�־λ��չʾ��һ������
    //    current_screen = (current_screen + 1) % TOTAL_SCREENS;
    ////		 Lcd12864_Write16CnCHAR(0,32,0,"��բ����\r");
    //		 F_mainchange=0;
    //
    //	 }
    //	 if(F_mainchange==2)
    //	 {
    //		  showScreen(current_screen);

    //    // ���±�־λ��չʾ��һ������
    //    current_screen = (current_screen -1) % TOTAL_SCREENS;
    ////		 Lcd12864_Write16CnCHAR(0,32,0,"��բ����\r");
    //		 F_mainchange=0;
    //
    //	 }
}
void showScreen(int screenIndex)
{ // ��ѯ��չʾʵ��
    // ���ݴ���� screenIndex չʾ��Ӧ�Ľ���
    switch (screenIndex)
    {
    case 0:
        screenbase1();

        break;
    case 1:
        screenbase2();

        break;
    case 2:
        screenbase3();

        break;
    case 3:
        screenbase4();

        break;
    case 4:
        screenbase5();

        break;
    case 5:
        screenbase6();

        break;
    case 6:
        screenbase7();

        break;
    case 7:
        screenbase8();

        break;
    case 8:
        screenbase9();

        break;
    case 9:
        screenbase10();

        break;
    case 10:
        screenbase11();

        break;
    case 11:
        screenbase12();

        break;
    case 12:
        screenbase13();

        break;
    default:

        break;
    }
    // screenbase1();
}

void screenbase1() // ��ѯ1����
{
    switch (HT7038_buf1[46])
    {
    case 0:
        Lcd12864_Write16CnCHAR(0, 5, 0, "�J");
        break;
    case 1:
        Lcd12864_Write16CnCHAR(0, 5, 0, "�J");
        break;
    case 2:
        Lcd12864_Write16CnCHAR(0, 5, 0, "�I");
        break;
    case 3:
        Lcd12864_Write16CnCHAR(0, 5, 0, "�L");
        break;
    case 4:
        Lcd12864_Write16CnCHAR(0, 5, 0, "�K");
        break;
    }
    int_to_ascii(HT7038_buf1[43], zifu_dian);
    Lcd12864_Write14CnCHAR(0, 95, 0, zifu_dian);
    Lcd12864_Write14CnCHAR(0, 111, 0, "hz");
    if (isfenzha == 0)
    {
        Lcd12864_Write16CnCHAR(0, 32, 0, "��բ����");
    }

    else if ((F_trip_ld == 1) && Leak_Cur_disp > 15)
    {
        Lcd12864_Write16CnCHAR(0, 0, 0, "©��澯");
        xianshishuju(Leak_Cur_disp);
        display_ASCIIstring_8x16(1, 73, (unsigned char *)zifu_dian);
        Lcd12864_Write16CnCHAR(0, 105, 0, "mA");
    }

    else if ((isfenzha != 0) || (F_trip_ld == 0))
    {
        Lcd12864_Write14CnCHAR(0, 32, 0, "��բ����\r");
    }

    Lcd12864_Write16CnCHAR(0, 0, 0, "\r©�絵λ:\r�����:\r");
    if (D_LCur == 0)
    {
        display_ASCIIstring_8x16(3, 83, "30mA");
    }
    else if (D_LCur == 1)
    {
        display_ASCIIstring_8x16(3, 83, "50mA");
    }
    else if (D_LCur == 2)
    {
        display_ASCIIstring_8x16(3, 83, "100mA");
    }
    else if (D_LCur == 3)
    {
        display_ASCIIstring_8x16(3, 83, "200mA");
    }
    else if (D_LCur == 4)
    {
        display_ASCIIstring_8x16(3, 83, "300mA");
    }
    else if (D_LCur == 5)
    {
        display_ASCIIstring_8x16(3, 83, "500mA");
    }
    else if (D_LCur == 6)
    {
        display_ASCIIstring_8x16(3, 83, "800mA");
    }
    else if (D_LCur == 7)
    {
        display_ASCIIstring_8x16(3, 75, "1000mA");
    }
    else if (D_LCur == 8)
    {
        display_ASCIIstring_8x16(3, 83, "Auto");
    }

    I_VAL_handle();
    xianshishuju_dianliu(SET_I_VAL);
    display_ASCIIstring_8x16(5, 83, zifu_dian);

    HAL_RTC_GetTime(&hrtc, &stimestructure, RTC_FORMAT_BCD);
    HAL_RTC_GetDate(&hrtc, &sdatestructure, RTC_FORMAT_BCD);

    nian[0] = (sdatestructure.Year >> 4) + 0x30;
    nian[1] = (sdatestructure.Year & 0x0F) + 0x30;
    nian[2] = '\0';

    yue[0] = (sdatestructure.Month >> 4) + 0x30;
    yue[1] = (sdatestructure.Month & 0x0F) + 0x30;
    yue[2] = '\0';

    ri[0] = (sdatestructure.Date >> 4) + 0x30;
    ri[1] = (sdatestructure.Date & 0x0F) + 0x30;
    ri[2] = '\0';

    shi[0] = (stimestructure.Hours >> 4) + 0x30;
    shi[1] = (stimestructure.Hours & 0x0F) + 0x30;
    shi[2] = '\0';

    fen[0] = (stimestructure.Minutes >> 4) + 0x30;
    fen[1] = (stimestructure.Minutes & 0x0F) + 0x30;
    fen[2] = '\0';

    miao[0] = (stimestructure.Seconds >> 4) + 0x30;
    miao[1] = (stimestructure.Seconds & 0x0F) + 0x30;
    miao[2] = '\0';
    display_ASCIIstring_8x16(7, 8, nian);
    display_graphic_8x16(7, 24, qirigang);
    display_ASCIIstring_8x16(7, 29, yue);
    display_graphic_8x16(7, 45, qirigang);
    display_ASCIIstring_8x16(7, 50, ri);

    display_graphic_8x16(7, 65, xiaogang);
    display_ASCIIstring_8x16(7, 71, shi);
    display_graphic_8x16(7, 87, xiaomaohao);
    display_ASCIIstring_8x16(7, 92, fen);
    display_graphic_8x16(7, 108, xiaomaohao);
    display_ASCIIstring_8x16(7, 113, miao);
}

void screenbase2() // ��ѯ2����
{
    Lcd12864_Write16CnCHAR(0, 0, 0, "Tn->");
    Lcd12864_Write16CnCHAR(0, 0, 2, "Ta->");
    Lcd12864_Write16CnCHAR(0, 0, 4, "Tb->");
    Lcd12864_Write16CnCHAR(0, 0, 6, "Tc->");
    Lcd12864_Write16CnCHAR(0, 64, 0, "Tn<-");
    Lcd12864_Write16CnCHAR(0, 64, 2, "Ta<-");
    Lcd12864_Write16CnCHAR(0, 64, 4, "Tb<-");
    Lcd12864_Write16CnCHAR(0, 64, 6, "Tc<-");
    xianshishuju(temperature[0]);
    display_ASCIIstring_8x16(1, 38, zifu_dian);

    xianshishuju(temperature[2]);
    display_ASCIIstring_8x16(3, 38, zifu_dian);

    xianshishuju(temperature[4]);
    display_ASCIIstring_8x16(5, 38, zifu_dian);

    xianshishuju(temperature[6]);
    display_ASCIIstring_8x16(7, 38, zifu_dian);

    xianshishuju(temperature[1]);
    display_ASCIIstring_8x16(1, 102, zifu_dian);

    xianshishuju(temperature[3]);
    display_ASCIIstring_8x16(3, 102, zifu_dian);

    xianshishuju(temperature[5]);
    display_ASCIIstring_8x16(5, 102, zifu_dian);

    xianshishuju(temperature[7]);
    display_ASCIIstring_8x16(7, 102, zifu_dian);
}
void screenbase3() // ��ѯ3����      �й�����
{
    //		clear_screen();

    ////if(F_Dataval==0)
    {
        Lcd12864_Write16CnCHAR(0, 0, 0, "Fs:");
        for (int i = 0; i < 4; i++)
        {
            Lcd12864_Write16CnCHAR(0, 100, 2 * i, "kwh");
        }
        Lcd12864_Write16CnCHAR(0, 0, 2, "Fa:");
        Lcd12864_Write16CnCHAR(0, 0, 4, "Fb:");
        Lcd12864_Write16CnCHAR(0, 0, 6, "Fc:");
        xianshishuju2(HT7038_buf1[18]); // �����й�����

        display_ASCIIstring_8x16(1, 29, zifu_dian);     // 29
        display_graphic_8x16(1, 53, dian);              // 36
        display_ASCIIstring_8x16(1, 60, &zifu_dian[3]); // 44

        xianshishuju2(HT7038_buf1[15]); // A���й�����

        display_ASCIIstring_8x16(3, 29, zifu_dian);     // 29
        display_graphic_8x16(3, 53, dian);              // 36
        display_ASCIIstring_8x16(3, 60, &zifu_dian[3]); // 44

        xianshishuju2(HT7038_buf1[16]);
        display_ASCIIstring_8x16(5, 29, zifu_dian);
        display_graphic_8x16(5, 53, dian);
        display_ASCIIstring_8x16(5, 60, &zifu_dian[3]);

        xianshishuju2(HT7038_buf1[17]);
        display_ASCIIstring_8x16(7, 29, zifu_dian);
        display_graphic_8x16(7, 53, dian);
        display_ASCIIstring_8x16(7, 60, &zifu_dian[3]);
    }
}
void screenbase4() // ��ѯ4����    ����ϵ��
{

    //	Lcd12864_Write16CnCHAR(0,16,0,"����ϵ��/P_F");

    Lcd12864_Write16CnCHAR(0, 0, 0, "PFs:");
    Lcd12864_Write16CnCHAR(0, 0, 2, "PFa:");
    Lcd12864_Write16CnCHAR(0, 0, 4, "PFb:");
    Lcd12864_Write16CnCHAR(0, 0, 6, "PFc:");
    xianshishuju3(HT7038_buf1[14]); // ����ϵ������

    display_ASCIIstring_8x16(1, 56, zifu_dian);
    display_graphic_8x16(1, 63, dian);
    display_ASCIIstring_8x16(1, 71, &zifu_dian[1]);

    xianshishuju3(HT7038_buf1[11]); // ����ϵ������

    display_ASCIIstring_8x16(3, 56, zifu_dian);
    display_graphic_8x16(3, 63, dian);
    display_ASCIIstring_8x16(3, 71, &zifu_dian[1]);

    xianshishuju3(HT7038_buf1[12]);

    display_ASCIIstring_8x16(5, 56, zifu_dian);
    display_graphic_8x16(5, 63, dian);
    display_ASCIIstring_8x16(5, 71, &zifu_dian[1]);

    xianshishuju3(HT7038_buf1[13]);
    display_ASCIIstring_8x16(7, 56, zifu_dian);
    display_graphic_8x16(7, 63, dian);
    display_ASCIIstring_8x16(7, 71, &zifu_dian[1]);
}
void screenbase5() // ��ѯ5����    �й�����
{
    // if(F_Dataval==0)
    {

        // �й�������
        Lcd12864_Write16CnCHAR(0, 0, 0, "Ps:");
        Lcd12864_Write16CnCHAR(0, 0, 2, "Pa:");
        Lcd12864_Write16CnCHAR(0, 0, 4, "Pb:");
        Lcd12864_Write16CnCHAR(0, 0, 6, "Pc:");
        for (int i = 0; i < 4; i++)
        {
            Lcd12864_Write16CnCHAR(0, 100, 2 * i, "kw");
        }
        xianshishuju2(HT7038_buf1[10]);                 ////�й�������
        display_ASCIIstring_8x16(1, 45, zifu_dian);     // 29
        display_graphic_8x16(1, 69, dian);              // 36
        display_ASCIIstring_8x16(1, 76, &zifu_dian[3]); // 44
        xianshishuju2(HT7038_buf1[7]);                  // �й�������
        display_ASCIIstring_8x16(3, 45, zifu_dian);     // 29
        display_graphic_8x16(3, 69, dian);              // 36
        display_ASCIIstring_8x16(3, 76, &zifu_dian[3]); // 44
        xianshishuju2(HT7038_buf1[8]);
        display_ASCIIstring_8x16(5, 45, zifu_dian);
        display_graphic_8x16(5, 69, dian);
        display_ASCIIstring_8x16(5, 76, &zifu_dian[3]);
        xianshishuju2(HT7038_buf1[9]);
        display_ASCIIstring_8x16(7, 45, zifu_dian);
        display_graphic_8x16(7, 69, dian);
        display_ASCIIstring_8x16(7, 76, &zifu_dian[3]);
    }
}
void screenbase6() // ��ѯ6����
{

    Lcd12864_Write16CnCHAR(0, 0, 0, "I��:");
    Lcd12864_Write16CnCHAR(0, 0, 2, "Ua:");
    Lcd12864_Write16CnCHAR(0, 0, 4, "Ub:");
    Lcd12864_Write16CnCHAR(0, 0, 6, "Uc:");
    Lcd12864_Write16CnCHAR(0, 75, 0, "L:");
    Lcd12864_Write16CnCHAR(0, 64, 2, "Ia:");
    Lcd12864_Write16CnCHAR(0, 64, 4, "Ib:");
    Lcd12864_Write16CnCHAR(0, 64, 6, "Ic:");
    for (int a = 0; a < 3; a++)
    {
        Lcd12864_Write16CnCHAR(0, 52, 2 + 2 * a, "V");
        Lcd12864_Write16CnCHAR(0, 115, 2 + 2 * a, "A");
    }
    xianshishuju(Leak_Cur_disp);
    display_ASCIIstring_8x16(1, 96, zifu_dian);
    if (D_LCur == 0)
    {
        display_ASCIIstring_8x16(1, 35, "0.03A");
    }
    else if (D_LCur == 1)
    {
        display_ASCIIstring_8x16(1, 35, "0.05A");
    }
    else if (D_LCur == 2)
    {
        display_ASCIIstring_8x16(1, 35, "0.1A");
    }
    else if (D_LCur == 3)
    {
        display_ASCIIstring_8x16(1, 35, "0.2A");
    }
    else if (D_LCur == 4)
    {
        display_ASCIIstring_8x16(1, 35, "0.3A");
    }
    else if (D_LCur == 5)
    {
        display_ASCIIstring_8x16(1, 35, "0.5A");
    }
    else if (D_LCur == 6)
    {
        display_ASCIIstring_8x16(1, 35, "0.8A");
    }
    else if (D_LCur == 7)
    {
        display_ASCIIstring_8x16(1, 35, "1A");
    }
    else if (D_LCur == 8)
    {
        display_ASCIIstring_8x16(1, 35, "Auto");
    }

    xianshishuju(HT7038_buf1[4]); // ��������
    display_ASCIIstring_8x16(3, 91, zifu_dian);
    xianshishuju(HT7038_buf1[5]);
    display_ASCIIstring_8x16(5, 91, zifu_dian);
    xianshishuju(HT7038_buf1[6]);
    display_ASCIIstring_8x16(7, 91, zifu_dian);
    xianshishuju(HT7038_buf1[1]); // ��ѹ����
    display_ASCIIstring_8x16(3, 27, zifu_dian);
    xianshishuju(HT7038_buf1[2]);
    display_ASCIIstring_8x16(5, 27, zifu_dian);
    xianshishuju(HT7038_buf1[3]);
    display_ASCIIstring_8x16(7, 27, zifu_dian);
}
/***************************����*********************************/
void screenbase7() // ��ѯ7����   �޹�����
{
    // if(F_Dataval==0)
    {
        Lcd12864_Write16CnCHAR(0, 0, 0, "Qs:"); // ��
        Lcd12864_Write16CnCHAR(0, 0, 2, "Qa:");
        Lcd12864_Write16CnCHAR(0, 0, 4, "Qb:");
        Lcd12864_Write16CnCHAR(0, 0, 6, "Qc:");
        for (int i = 0; i < 4; i++)
        {
            Lcd12864_Write16CnCHAR(0, 100, 2 * i, "var");
        }
        xianshishuju2(HT7038_buf1[19]);                 // �й�������
        display_ASCIIstring_8x16(1, 45, zifu_dian);     // 29    //����Ҫ��
        display_graphic_8x16(1, 69, dian);              // 36
        display_ASCIIstring_8x16(1, 76, &zifu_dian[3]); // 44
        xianshishuju2(HT7038_buf1[20]);                 // �й�������
        display_ASCIIstring_8x16(3, 45, zifu_dian);     // 29
        display_graphic_8x16(3, 69, dian);              // 36
        display_ASCIIstring_8x16(3, 76, &zifu_dian[3]); // 44
        xianshishuju2(HT7038_buf1[21]);
        display_ASCIIstring_8x16(5, 45, zifu_dian);
        display_graphic_8x16(5, 69, dian);
        display_ASCIIstring_8x16(5, 76, &zifu_dian[3]);
        xianshishuju2(HT7038_buf1[22]);
        display_ASCIIstring_8x16(7, 45, zifu_dian);
        display_graphic_8x16(7, 69, dian);
        display_ASCIIstring_8x16(7, 76, &zifu_dian[3]);
    }
}
void screenbase8() // ��ѯ8����   ���ڹ���
{
    // if(F_Dataval==0)
    {
        Lcd12864_Write16CnCHAR(0, 0, 0, "Ss:"); // ��
        Lcd12864_Write16CnCHAR(0, 0, 2, "Sa:");
        Lcd12864_Write16CnCHAR(0, 0, 4, "Sb:");
        Lcd12864_Write16CnCHAR(0, 0, 6, "Sc:");
        for (int i = 0; i < 4; i++)
        {
            Lcd12864_Write16CnCHAR(0, 100, 2 * i, "VA");
        }
        xianshishuju2(HT7038_buf1[23]);                 // �й�������
        display_ASCIIstring_8x16(1, 45, zifu_dian);     // 29    //����Ҫ��
        display_graphic_8x16(1, 69, dian);              // 36
        display_ASCIIstring_8x16(1, 76, &zifu_dian[3]); // 44
        xianshishuju2(HT7038_buf1[24]);                 // �й�������
        display_ASCIIstring_8x16(3, 45, zifu_dian);     // 29
        display_graphic_8x16(3, 69, dian);              // 36
        display_ASCIIstring_8x16(3, 76, &zifu_dian[3]); // 44
        xianshishuju2(HT7038_buf1[25]);
        display_ASCIIstring_8x16(5, 45, zifu_dian);
        display_graphic_8x16(5, 69, dian);
        display_ASCIIstring_8x16(5, 76, &zifu_dian[3]);
        xianshishuju2(HT7038_buf1[26]);
        display_ASCIIstring_8x16(7, 45, zifu_dian);
        display_graphic_8x16(7, 69, dian);
        display_ASCIIstring_8x16(7, 76, &zifu_dian[3]);
    }
}
void screenbase9() // ��ѯ9����   �޹�����
{
    // if(F_Dataval==0)
    {
        //		   		clear_screen();
        // �й�������
        Lcd12864_Write16CnCHAR(0, 0, 0, "Qs:"); // ��
        Lcd12864_Write16CnCHAR(0, 0, 2, "Qa:");
        Lcd12864_Write16CnCHAR(0, 0, 4, "Qb:");
        Lcd12864_Write16CnCHAR(0, 0, 6, "Qc:");
        for (int i = 0; i < 4; i++)
        {
            Lcd12864_Write16CnCHAR(0, 95, 2 * i, "VARh");
        }

        xianshishuju2(HT7038_buf1[27]);                 // �й�������
        display_ASCIIstring_8x16(1, 40, zifu_dian);     // 29    //����Ҫ��
        display_graphic_8x16(1, 64, dian);              // 36
        display_ASCIIstring_8x16(1, 71, &zifu_dian[3]); // 44
        xianshishuju2(HT7038_buf1[28]);                 // �й�������
        display_ASCIIstring_8x16(3, 40, zifu_dian);     // 29
        display_graphic_8x16(3, 64, dian);              // 36
        display_ASCIIstring_8x16(3, 71, &zifu_dian[3]); // 44
        xianshishuju2(HT7038_buf1[29]);
        display_ASCIIstring_8x16(5, 40, zifu_dian);
        display_graphic_8x16(5, 64, dian);
        display_ASCIIstring_8x16(5, 71, &zifu_dian[3]);
        xianshishuju2(HT7038_buf1[30]);
        display_ASCIIstring_8x16(7, 40, zifu_dian);
        display_graphic_8x16(7, 64, dian);
        display_ASCIIstring_8x16(7, 71, &zifu_dian[3]);
    }
}

void screenbase10() // ��ѯ10����   �й�����
{
    // if(F_Dataval==0)
    {
        Lcd12864_Write16CnCHAR(0, 0, 0, "Pds:");
        Lcd12864_Write16CnCHAR(0, 0, 2, "Qds:");
        Lcd12864_Write16CnCHAR(0, 0, 4, "Sds:");
        Lcd12864_Write16CnCHAR(0, 5, 6, "�Ƽ�:");
        Lcd12864_Write16CnCHAR(0, 100, 6, "Ԫ");
        //	 Lcd12864_Write16CnCHAR(0,0,2,"Pda:");
        //	 Lcd12864_Write16CnCHAR(0,0,4,"Pdb:");
        //	 Lcd12864_Write16CnCHAR(0,0,6,"Pdc:");
        Lcd12864_Write16CnCHAR(0, 100, 0, "Kw");
        Lcd12864_Write16CnCHAR(0, 100, 2, "Kw");
        Lcd12864_Write16CnCHAR(0, 100, 4, "Va");

        xianshishuju2(HT7038_buf1[31]);
        display_ASCIIstring_8x16(1, 45, zifu_dian);     // 29
        display_graphic_8x16(1, 69, dian);              // 36
        display_ASCIIstring_8x16(1, 76, &zifu_dian[3]); // 44
        xianshishuju2(HT7038_buf1[42]);
        display_ASCIIstring_8x16(5, 45, zifu_dian);
        display_graphic_8x16(5, 69, dian);
        display_ASCIIstring_8x16(5, 76, &zifu_dian[3]);
        //		 xianshishuju2(HT7038_buf1[32]);
        //	 display_ASCIIstring_8x16(3,45,zifu_dian);//29
        //   display_graphic_8x16(3,69,dian);//36
        //   display_ASCIIstring_8x16(3,76,&zifu_dian[3]);//44
        //		 xianshishuju2(HT7038_buf1[33]);
        //	 display_ASCIIstring_8x16(5,45,zifu_dian);
        //   display_graphic_8x16(5,69,dian);
        //   display_ASCIIstring_8x16(5,76,&zifu_dian[3]);
        //		 xianshishuju2(HT7038_buf1[34]);
        //	 display_ASCIIstring_8x16(7,45,zifu_dian);
        //   display_graphic_8x16(7,69,dian);
        //   display_ASCIIstring_8x16(7,76,&zifu_dian[3]);
        xianshishuju2(HT7038_buf1[36]);
        display_ASCIIstring_8x16(3, 45, zifu_dian);     // 29
        display_graphic_8x16(3, 69, dian);              // 36
        display_ASCIIstring_8x16(3, 76, &zifu_dian[3]); // 44
        xianshishuju2(HT7038_buf1[47]);
        display_ASCIIstring_8x16(7, 45, zifu_dian);     // 29
        display_graphic_8x16(7, 69, dian);              // 36
        display_ASCIIstring_8x16(7, 76, &zifu_dian[3]); // 44
    }
}
void screenbase11() // ��ѯ11����   �޹�����
{

    // if(F_Dataval==0)
    {
        Lcd12864_Write16CnCHAR(0, 0, 0, "Qds:");
        Lcd12864_Write16CnCHAR(0, 0, 2, "Qda:");
        Lcd12864_Write16CnCHAR(0, 0, 4, "Qdb:");
        Lcd12864_Write16CnCHAR(0, 0, 6, "Qdc:");
        Lcd12864_Write16CnCHAR(0, 100, 0, "kW");
        Lcd12864_Write16CnCHAR(0, 100, 2, "kW");
        Lcd12864_Write16CnCHAR(0, 100, 4, "kW");
        Lcd12864_Write16CnCHAR(0, 100, 6, "kW");
        xianshishuju2(HT7038_buf1[35]);
        display_ASCIIstring_8x16(1, 45, zifu_dian);     // 29
        display_graphic_8x16(1, 69, dian);              // 36
        display_ASCIIstring_8x16(1, 76, &zifu_dian[3]); // 44
        xianshishuju2(HT7038_buf1[36]);
        display_ASCIIstring_8x16(3, 45, zifu_dian);     // 29
        display_graphic_8x16(3, 69, dian);              // 36
        display_ASCIIstring_8x16(3, 76, &zifu_dian[3]); // 44
        xianshishuju2(HT7038_buf1[37]);
        display_ASCIIstring_8x16(5, 45, zifu_dian);
        display_graphic_8x16(5, 69, dian);
        display_ASCIIstring_8x16(5, 76, &zifu_dian[3]);
        xianshishuju2(HT7038_buf1[38]);
        display_ASCIIstring_8x16(7, 45, zifu_dian);
        display_graphic_8x16(7, 69, dian);
        display_ASCIIstring_8x16(7, 76, &zifu_dian[3]);
    }
}
void screenbase12() // ��ѯ12����   ��������
{
    // if(F_Dataval==0)
    {

        Lcd12864_Write16CnCHAR(0, 0, 0, "Sds:");
        Lcd12864_Write16CnCHAR(0, 0, 2, "Sda:");
        Lcd12864_Write16CnCHAR(0, 0, 4, "Sdb:");
        Lcd12864_Write16CnCHAR(0, 0, 6, "Sdc:");
        Lcd12864_Write16CnCHAR(0, 100, 0, "Va");
        Lcd12864_Write16CnCHAR(0, 100, 2, "Va");
        Lcd12864_Write16CnCHAR(0, 100, 4, "Va");
        Lcd12864_Write16CnCHAR(0, 100, 6, "Va");
        xianshishuju2(HT7038_buf1[39]);
        display_ASCIIstring_8x16(1, 45, zifu_dian);     // 29
        display_graphic_8x16(1, 69, dian);              // 36
        display_ASCIIstring_8x16(1, 76, &zifu_dian[3]); // 44
        xianshishuju2(HT7038_buf1[40]);
        display_ASCIIstring_8x16(3, 45, zifu_dian);     // 29
        display_graphic_8x16(3, 69, dian);              // 36
        display_ASCIIstring_8x16(3, 76, &zifu_dian[3]); // 44
        xianshishuju2(HT7038_buf1[41]);
        display_ASCIIstring_8x16(5, 45, zifu_dian);
        display_graphic_8x16(5, 69, dian);
        display_ASCIIstring_8x16(5, 76, &zifu_dian[3]);
        xianshishuju2(HT7038_buf1[42]);
        display_ASCIIstring_8x16(7, 45, zifu_dian);
        display_graphic_8x16(7, 69, dian);
        display_ASCIIstring_8x16(7, 76, &zifu_dian[3]);
    }
}
void screenbase13() // ��ѯ13����   ����������ָʾ��Ƶ�� ��ѹ���಻ƽ��ȣ��������಻ƽ���
{
}

// typedef struct meun{
//	char *NAME;
//	  unsigned char (*A)[6]; // ʹ��ָ�������ָ��
//	unsigned char *value;
//     unsigned char array_size;
//	void (*func)(void);
// } meuntype;
struct smainmenu
{
    char *NAME;
    void (*func)(void);
};
void mainmenu() // ���˵�
{
    //	struct smainmenu smenu[]={
    //	{"��������",},
    //			{"��������",},
    //
    //	};
    Lcd12864_Write16CnCHAR(0, 40, 0, "���˵�");
    //	Lcd12864_Write16CnCHAR(0,2,2,"��һ����");

    switch (a1)
    {
    case 0:
    {
        Lcd12864_Write16CnCHAR(1, 0, 2, "��������");
        Lcd12864_Write16CnCHAR(0, 0, 4, "��������");
        Lcd12864_Write16CnCHAR(0, 0, 6, "У׼����");
        Lcd12864_Write16CnCHAR(0, 64, 2, "����Ʒ��");
        Lcd12864_Write16CnCHAR(0, 64, 4, "Խ�ޱ���");
        Lcd12864_Write16CnCHAR(0, 64, 6, "�¼���¼");
    }
    break;
    case 1:
    {
        Lcd12864_Write16CnCHAR(0, 0, 2, "��������");
        Lcd12864_Write16CnCHAR(1, 0, 4, "��������");
        Lcd12864_Write16CnCHAR(0, 0, 6, "У׼����");
        Lcd12864_Write16CnCHAR(0, 64, 2, "����Ʒ��");
        Lcd12864_Write16CnCHAR(0, 64, 4, "Խ�ޱ���");
        Lcd12864_Write16CnCHAR(0, 64, 6, "�¼���¼");
    }
    break;
    case 2:
    {
        Lcd12864_Write16CnCHAR(0, 0, 2, "��������");
        Lcd12864_Write16CnCHAR(0, 0, 4, "��������");
        Lcd12864_Write16CnCHAR(1, 0, 6, "У׼����");
        Lcd12864_Write16CnCHAR(0, 64, 2, "����Ʒ��");
        Lcd12864_Write16CnCHAR(0, 64, 4, "Խ�ޱ���");
        Lcd12864_Write16CnCHAR(0, 64, 6, "�¼���¼");
    }
    break;
    case 3:
    {
        Lcd12864_Write16CnCHAR(0, 0, 2, "��������");
        Lcd12864_Write16CnCHAR(0, 0, 4, "��������");
        Lcd12864_Write16CnCHAR(0, 0, 6, "У׼����");
        Lcd12864_Write16CnCHAR(1, 64, 2, "����Ʒ��");
        Lcd12864_Write16CnCHAR(0, 64, 4, "Խ�ޱ���");
        Lcd12864_Write16CnCHAR(0, 64, 6, "�¼���¼");
    }
    break;
    case 4:
    {
        Lcd12864_Write16CnCHAR(0, 0, 2, "��������");
        Lcd12864_Write16CnCHAR(0, 0, 4, "��������");
        Lcd12864_Write16CnCHAR(0, 0, 6, "У׼����");
        Lcd12864_Write16CnCHAR(0, 64, 2, "����Ʒ��");
        Lcd12864_Write16CnCHAR(1, 64, 4, "Խ�ޱ���");
        Lcd12864_Write16CnCHAR(0, 64, 6, "�¼���¼");
    }
    break;
    case 5:
    {
        Lcd12864_Write16CnCHAR(0, 0, 2, "��������");
        Lcd12864_Write16CnCHAR(0, 0, 4, "��������");
        Lcd12864_Write16CnCHAR(0, 0, 6, "У׼����");
        Lcd12864_Write16CnCHAR(0, 64, 2, "����Ʒ��");
        Lcd12864_Write16CnCHAR(0, 64, 4, "Խ�ޱ���");
        Lcd12864_Write16CnCHAR(1, 64, 6, "�¼���¼");
    }
    break;
    }
    if (key == KEY_UP_PRES)
    {
        a1++;
        if (a1 > 5) //&&F_Y!=4
        {
            clear_screen();
            a1 = 0;
            clear_screen();
        }
    }
    else if (key == KEY_DOWN_PRES)
    {
        a1--;
        if (a1 < 0)
        {
            a1 = 0;
            clear_screen();
        }
    }

    if (key == KEY_AFFIRM_PRES) // ȷ��֮��Ҫ�����ݱȽϣ��б����������
    {
        clear_screen();
        switch (a1)
        {
        case 0:
            F_MAINormenu = 2;
            break;
        case 1:
            F_MAINormenu = 1;
            break;
        case 2:
            F_MAINormenu = 5; // ���ܲ���
            break;
        case 3:
        {
            USART_LCD_Transmit(1, 6);

            USART_LCD_Transmit(1, 6);
            F_MAINormenu = 8;
        } // ����Ʒ��
        break;
        case 4:
            F_MAINormenu = 9; // �����鿴
            break;
        case 5:
            USART_LCD_Transmit(1, 7);
            F_MAINormenu = 4; // �¼���¼

            break;
        default:
            break;
        }
        /* USER CODE END WHILE */

        /* USER CODE BEGIN 3 */
    }
}
void Power_parameters() // ���ܲ���
{
    Lcd12864_Write16CnCHAR(0, 40, 0, "���ܲ���");
    switch (a)
    {
    case 0:
    {
        Lcd12864_Write16CnCHAR(1, 0, 2, "�й�����");
        Lcd12864_Write16CnCHAR(0, 0, 4, "�޹�����");
        Lcd12864_Write16CnCHAR(0, 0, 6, "�ܵ���");
    }
    break;
    case 1:
    {
        Lcd12864_Write16CnCHAR(0, 0, 2, "�й�����");
        Lcd12864_Write16CnCHAR(1, 0, 4, "�޹�����");
        Lcd12864_Write16CnCHAR(0, 0, 6, "�ܵ���");
    }
    break;
    case 2:
    {
        Lcd12864_Write16CnCHAR(0, 0, 2, "�й�����");
        Lcd12864_Write16CnCHAR(0, 0, 4, "�޹�����");
        Lcd12864_Write16CnCHAR(1, 0, 6, "�ܵ���");
    }
    break;
    }
    if (key == KEY_UP_PRES)
    {
        a++;
        if (a > 2) //&&F_Y!=4
        {
            // clear_screen();
            a = 0;
            clear_screen();
            //		if(F_Y==4) F_Y=5;        //�����ṹ��˵�
            //		if(F_Y==3) F_Y=5;
            //		  if(F_Y==2) F_Y=3;
            //		  if(F_Y==1) F_Y=2;
            //		  if(F_Y==0) F_Y=1;
        }
        //	}else if(a>totalItems-1&&F_Y==4) a=totalItems-1;
    }
    else if (key == KEY_DOWN_PRES)
    {
        a--;
        if (a < 0)
        {
            a = 0;
            clear_screen();
        }
    }

    else if (key == KEY_AFFIRM_PRES) // ȷ��֮��Ҫ�����ݱȽϣ��б����������
    {
        clear_screen();
        switch (a)
        {
        case 0:
            F_AEorREorALLE = 1;
            break;
        case 1:
            F_AEorREorALLE = 2;
            break;
        case 2:
            F_AEorREorALLE = 3;
            break;
        }
    }
}

void power_quality() // ����Ʒ��
{

    if (current_page == 0 && F_Dataval == 0 && f_f != 0)
    {
        Lcd12864_Write14CnCHAR(0, 30, 2, "���ڼ���......");
        switch (f_f)
        {
        case 1:
            disp_data(40, 5, 14, 0);
            break;
        case 2:
            disp_data(40, 5, 14, 166);
            break;
        case 3:
            disp_data(40, 5, 14, 333);
            break;
        case 4:
            disp_data(40, 5, 14, 500);
            break;
        case 5:
            disp_data(40, 5, 14, 667);
            break;
        case 6:
            disp_data(40, 5, 14, 833);
            break;
        }
    }
    else if (current_page == 0 && F_Dataval == 0 && f_f == 0)
    {

        Lcd12864_Write14CnCHAR(0, 0, 0, "��ѹƽ����");
        Lcd12864_Write16CnCHAR(0, 0, 2, "VUB:"); // �����ѹ��ƽ����
        disp_data(40, 2, 16, HT7038_buf1[44]);
        Lcd12864_Write14CnCHAR(0, 0, 4, "����ƽ����");
        Lcd12864_Write16CnCHAR(0, 0, 6, "IUB:"); // �����ѹ��ƽ����
        disp_data(40, 6, 16, HT7038_buf1[45]);
        Lcd12864_Write16CnCHAR(0, 79, 2, " ");
    }
    else if (current_page == 1) // �����ѹг��
    {
        Lcd12864_Write14CnCHAR(0, 0, 0, "��ѹ��г��������");
        Lcd12864_Write16CnCHAR(0, 0, 2, "VaTHD:");
        Lcd12864_Write16CnCHAR(0, 0, 4, "VbTHD:");
        Lcd12864_Write16CnCHAR(0, 0, 6, "VcTHD:");
        for (int i = 0; i < 3; i++)
        {
            disp_data(50, 2 + 2 * i, 16, HT7038_buf1[280 + i]);
        }
    }

    else if (current_page == 2) // �����ѹг��
    {
        Lcd12864_Write14CnCHAR(0, 0, 0, "%vHR A   B   C");

        Lcd12864_Write14CnCHAR(0, 2, 2, "2");
        Lcd12864_Write14CnCHAR(0, 2, 4, "3");
        Lcd12864_Write14CnCHAR(0, 2, 6, "4");

        for (int i = 0; i < 3; i++)
        {
            disp_data(16, 2 + 2 * i, 14, HT7038_buf1[100 + (current_page - 2) + i]);
            disp_data(51, 2 + 2 * i, 14, HT7038_buf1[130 + (current_page - 2) + i]);
            disp_data(86, 2 + 2 * i, 14, HT7038_buf1[160 + (current_page - 2) + i]);
        }
    }
    else if (current_page == 3) // �����ѹг��
    {
        Lcd12864_Write14CnCHAR(0, 0, 0, "%vHR A   B   C");

        Lcd12864_Write14CnCHAR(0, 2, 2, "5");
        Lcd12864_Write14CnCHAR(0, 2, 4, "6");
        Lcd12864_Write14CnCHAR(0, 2, 6, "7");

        for (int i = 0; i < 3; i++)
        {
            disp_data(16, 2 + 2 * i, 14, HT7038_buf1[100 + 3 * (current_page - 2) + i]);
            disp_data(51, 2 + 2 * i, 14, HT7038_buf1[130 + 3 * (current_page - 2) + i]);
            disp_data(86, 2 + 2 * i, 14, HT7038_buf1[160 + 3 * (current_page - 2) + i]);
        }
    }
    else if (current_page == 4) // �����ѹг��
    {
        Lcd12864_Write14CnCHAR(0, 0, 0, "%vHR A   B   C");
        Lcd12864_Write14CnCHAR(0, 2, 2, "8");
        Lcd12864_Write14CnCHAR(0, 2, 4, "9");
        Lcd12864_Write14CnCHAR(0, 2, 6, "10");

        for (int i = 0; i < 3; i++)
        {
            disp_data(16, 2 + 2 * i, 14, HT7038_buf1[100 + 3 * (current_page - 2) + i]);
            disp_data(51, 2 + 2 * i, 14, HT7038_buf1[130 + 3 * (current_page - 2) + i]);
            disp_data(86, 2 + 2 * i, 14, HT7038_buf1[160 + 3 * (current_page - 2) + i]);
        }
    }
    else if (current_page == 5) // �����ѹг��
    {
        Lcd12864_Write14CnCHAR(0, 0, 0, "%vHR A   B   C");

        Lcd12864_Write14CnCHAR(0, 2, 2, "11");
        Lcd12864_Write14CnCHAR(0, 2, 4, "12");
        Lcd12864_Write14CnCHAR(0, 2, 6, "13");

        for (int i = 0; i < 3; i++)
        {
            disp_data(16, 2 + 2 * i, 14, HT7038_buf1[100 + 3 * (current_page - 2) + i]);
            disp_data(51, 2 + 2 * i, 14, HT7038_buf1[130 + 3 * (current_page - 2) + i]);
            disp_data(86, 2 + 2 * i, 14, HT7038_buf1[160 + 3 * (current_page - 2) + i]);
        }
    }
    else if (current_page == 6) // �����ѹг��
    {
        Lcd12864_Write14CnCHAR(0, 0, 0, "%vHR A   B   C");

        Lcd12864_Write14CnCHAR(0, 2, 2, "14");
        Lcd12864_Write14CnCHAR(0, 2, 4, "15");
        Lcd12864_Write14CnCHAR(0, 2, 6, "16");
        for (int i = 0; i < 3; i++)
        {
            disp_data(16, 2 + 2 * i, 14, HT7038_buf1[100 + 3 * (current_page - 2) + i]);
            disp_data(51, 2 + 2 * i, 14, HT7038_buf1[130 + 3 * (current_page - 2) + i]);
            disp_data(86, 2 + 2 * i, 14, HT7038_buf1[160 + 3 * (current_page - 2) + i]);
        }
    }
    else if (current_page == 7) // �����ѹг��
    {
        Lcd12864_Write14CnCHAR(0, 0, 0, "%vHR A   B   C");

        Lcd12864_Write14CnCHAR(0, 2, 2, "17");
        Lcd12864_Write14CnCHAR(0, 2, 4, "18");
        Lcd12864_Write14CnCHAR(0, 2, 6, "19");
        for (int i = 0; i < 3; i++)
        {
            disp_data(16, 2 + 2 * i, 14, HT7038_buf1[100 + 3 * (current_page - 2) + i]);
            disp_data(51, 2 + 2 * i, 14, HT7038_buf1[130 + 3 * (current_page - 2) + i]);
            disp_data(86, 2 + 2 * i, 14, HT7038_buf1[160 + 3 * (current_page - 2) + i]);
        }
    }
    else if (current_page == 8) // �����ѹг��
    {
        Lcd12864_Write14CnCHAR(0, 0, 0, "%vHR A   B   C");

        Lcd12864_Write14CnCHAR(0, 2, 2, "20");
        Lcd12864_Write14CnCHAR(0, 2, 4, "21");
        Lcd12864_Write14CnCHAR(0, 2, 6, "22");
        for (int i = 0; i < 3; i++)
        {
            disp_data(16, 2 + 2 * i, 14, HT7038_buf1[100 + 3 * (current_page - 2) + i]);
            disp_data(51, 2 + 2 * i, 14, HT7038_buf1[130 + 3 * (current_page - 2) + i]);
            disp_data(86, 2 + 2 * i, 14, HT7038_buf1[160 + 3 * (current_page - 2) + i]);
        }
    }
    else if (current_page == 9) // �����ѹг��
    {
        Lcd12864_Write14CnCHAR(0, 0, 0, "%vHR A   B   C");

        Lcd12864_Write14CnCHAR(0, 2, 2, "23");
        Lcd12864_Write14CnCHAR(0, 2, 4, "24");
        Lcd12864_Write14CnCHAR(0, 2, 6, "25");
        for (int i = 0; i < 3; i++)
        {
            disp_data(16, 2 + 2 * i, 14, HT7038_buf1[100 + 3 * (current_page - 2) + i]);
            disp_data(51, 2 + 2 * i, 14, HT7038_buf1[130 + 3 * (current_page - 2) + i]);
            disp_data(86, 2 + 2 * i, 14, HT7038_buf1[160 + 3 * (current_page - 2) + i]);
        }
    }
    else if (current_page == 10) // �����ѹг��
    {
        Lcd12864_Write14CnCHAR(0, 0, 0, "%vHR A   B   C");

        Lcd12864_Write14CnCHAR(0, 2, 2, "26");
        Lcd12864_Write14CnCHAR(0, 2, 4, "27");
        Lcd12864_Write14CnCHAR(0, 2, 6, "28");
        for (int i = 0; i < 3; i++)
        {
            disp_data(16, 2 + 2 * i, 14, HT7038_buf1[100 + 3 * (current_page - 2) + i]);
            disp_data(51, 2 + 2 * i, 14, HT7038_buf1[130 + 3 * (current_page - 2) + i]);
            disp_data(86, 2 + 2 * i, 14, HT7038_buf1[160 + 3 * (current_page - 2) + i]);
        }
    }
    else if (current_page == 11) // �����ѹг��
    {
        Lcd12864_Write14CnCHAR(0, 0, 0, "%vHR A   B   C");
        Lcd12864_Write14CnCHAR(0, 2, 2, "29");
        Lcd12864_Write14CnCHAR(0, 2, 4, "30");
        Lcd12864_Write14CnCHAR(0, 2, 6, "31");
        for (int i = 0; i < 3; i++)
        {
            disp_data(16, 2 + 2 * i, 14, HT7038_buf1[100 + 3 * (current_page - 2) + i]);
            disp_data(51, 2 + 2 * i, 14, HT7038_buf1[130 + 3 * (current_page - 2) + i]);
            disp_data(86, 2 + 2 * i, 14, HT7038_buf1[160 + 3 * (current_page - 2) + i]);
        }
    }

    else if (current_page == -1) // ����г��
    {
        Lcd12864_Write14CnCHAR(0, 0, 0, "������г��������");
        Lcd12864_Write16CnCHAR(0, 0, 2, "IaTHD:");
        Lcd12864_Write16CnCHAR(0, 0, 4, "IbTHD:");
        Lcd12864_Write16CnCHAR(0, 0, 6, "IcTHD:");
        for (int i = 0; i < 3; i++)
        {
            disp_data(50, 2 + 2 * i, 16, HT7038_buf1[283 + i]);
        }
    }
    else if (current_page == -2) // �����ѹг��
    {
        Lcd12864_Write14CnCHAR(0, 0, 0, "%iHR A   B   C");

        Lcd12864_Write14CnCHAR(0, 2, 2, "2");
        Lcd12864_Write14CnCHAR(0, 2, 4, "3");
        Lcd12864_Write14CnCHAR(0, 2, 6, "4");
        for (int i = 0; i < 3; i++)
        {
            disp_data(16, 2 + 2 * i, 14, HT7038_buf1[190 + (-current_page - 2) + i]);
            disp_data(51, 2 + 2 * i, 14, HT7038_buf1[220 + (-current_page - 2) + i]);
            disp_data(86, 2 + 2 * i, 14, HT7038_buf1[256 + (-current_page - 2) + i]);
        }
    }
    else if (current_page == -3) // �����ѹг��
    {
        Lcd12864_Write14CnCHAR(0, 0, 0, "%iHR A   B   C");

        Lcd12864_Write14CnCHAR(0, 2, 2, "5");
        Lcd12864_Write14CnCHAR(0, 2, 4, "6");
        Lcd12864_Write14CnCHAR(0, 2, 6, "7");
        for (int i = 0; i < 3; i++)
        {
            disp_data(16, 2 + 2 * i, 14, HT7038_buf1[190 + 3 * (-current_page - 2) + i]);
            disp_data(51, 2 + 2 * i, 14, HT7038_buf1[220 + 3 * (-current_page - 2) + i]);
            disp_data(86, 2 + 2 * i, 14, HT7038_buf1[256 + 3 * (-current_page - 2) + i]);
        }
    }
    else if (current_page == -4) // �����ѹг��
    {
        Lcd12864_Write14CnCHAR(0, 0, 0, "%iHR A   B   C");

        Lcd12864_Write14CnCHAR(0, 2, 2, "8");
        Lcd12864_Write14CnCHAR(0, 2, 4, "9");
        Lcd12864_Write14CnCHAR(0, 2, 6, "10");
        for (int i = 0; i < 3; i++)
        {
            disp_data(16, 2 + 2 * i, 14, HT7038_buf1[190 + 3 * (-current_page - 2) + i]);
            disp_data(51, 2 + 2 * i, 14, HT7038_buf1[220 + 3 * (-current_page - 2) + i]);
            disp_data(86, 2 + 2 * i, 14, HT7038_buf1[256 + 3 * (-current_page - 2) + i]);
        }
    }
    else if (current_page == -5) // �����ѹг��
    {
        Lcd12864_Write14CnCHAR(0, 0, 0, "%iHR A   B   C");

        Lcd12864_Write14CnCHAR(0, 2, 2, "11");
        Lcd12864_Write14CnCHAR(0, 2, 4, "12");
        Lcd12864_Write14CnCHAR(0, 2, 6, "13");
        for (int i = 0; i < 3; i++)
        {
            disp_data(16, 2 + 2 * i, 14, HT7038_buf1[190 + 3 * (-current_page - 2) + i]);
            disp_data(51, 2 + 2 * i, 14, HT7038_buf1[220 + 3 * (-current_page - 2) + i]);
            disp_data(86, 2 + 2 * i, 14, HT7038_buf1[256 + 3 * (-current_page - 2) + i]);
        }
    }
    else if (current_page == -6) // �����ѹг��
    {
        Lcd12864_Write14CnCHAR(0, 0, 0, "%iHR A   B   C");

        Lcd12864_Write14CnCHAR(0, 2, 2, "14");
        Lcd12864_Write14CnCHAR(0, 2, 4, "15");
        Lcd12864_Write14CnCHAR(0, 2, 6, "16");
        for (int i = 0; i < 3; i++)
        {
            disp_data(16, 2 + 2 * i, 14, HT7038_buf1[190 + 3 * (-current_page - 2) + i]);
            disp_data(51, 2 + 2 * i, 14, HT7038_buf1[220 + 3 * (-current_page - 2) + i]);
            disp_data(86, 2 + 2 * i, 14, HT7038_buf1[256 + 3 * (-current_page - 2) + i]);
        }
    }
    else if (current_page == -7) // �����ѹг��
    {
        Lcd12864_Write14CnCHAR(0, 0, 0, "%iHR A   B   C");

        Lcd12864_Write14CnCHAR(0, 2, 2, "17");
        Lcd12864_Write14CnCHAR(0, 2, 4, "18");
        Lcd12864_Write14CnCHAR(0, 2, 6, "19");
        for (int i = 0; i < 3; i++)
        {
            disp_data(16, 2 + 2 * i, 14, HT7038_buf1[190 + 3 * (-current_page - 2) + i]);
            disp_data(51, 2 + 2 * i, 14, HT7038_buf1[220 + 3 * (-current_page - 2) + i]);
            disp_data(86, 2 + 2 * i, 14, HT7038_buf1[256 + 3 * (-current_page - 2) + i]);
        }
    }
    else if (current_page == -8) // �����ѹг��
    {
        Lcd12864_Write14CnCHAR(0, 0, 0, "%iHR A   B   C");

        Lcd12864_Write14CnCHAR(0, 2, 2, "20");
        Lcd12864_Write14CnCHAR(0, 2, 4, "21");
        Lcd12864_Write14CnCHAR(0, 2, 6, "22");
        for (int i = 0; i < 3; i++)
        {
            disp_data(16, 2 + 2 * i, 14, HT7038_buf1[190 + 3 * (-current_page - 2) + i]);
            disp_data(51, 2 + 2 * i, 14, HT7038_buf1[220 + 3 * (-current_page - 2) + i]);
            disp_data(86, 2 + 2 * i, 14, HT7038_buf1[256 + 3 * (-current_page - 2) + i]);
        }
    }
    else if (current_page == -9) // �����ѹг��
    {
        Lcd12864_Write14CnCHAR(0, 0, 0, "%iHR A   B   C");

        Lcd12864_Write14CnCHAR(0, 2, 2, "23");
        Lcd12864_Write14CnCHAR(0, 2, 4, "24");
        Lcd12864_Write14CnCHAR(0, 2, 6, "25");
        for (int i = 0; i < 3; i++)
        {
            disp_data(16, 2 + 2 * i, 14, HT7038_buf1[190 + 3 * (-current_page - 2) + i]);
            disp_data(51, 2 + 2 * i, 14, HT7038_buf1[220 + 3 * (-current_page - 2) + i]);
            disp_data(86, 2 + 2 * i, 14, HT7038_buf1[256 + 3 * (-current_page - 2) + i]);
        }
    }
    else if (current_page == -10) // �����ѹг��
    {
        Lcd12864_Write14CnCHAR(0, 0, 0, "%iHR A   B   C");

        Lcd12864_Write14CnCHAR(0, 2, 2, "26");
        Lcd12864_Write14CnCHAR(0, 2, 4, "27");
        Lcd12864_Write14CnCHAR(0, 2, 6, "28");
        for (int i = 0; i < 3; i++)
        {
            disp_data(16, 2 + 2 * i, 14, HT7038_buf1[190 + 3 * (-current_page - 2) + i]);
            disp_data(51, 2 + 2 * i, 14, HT7038_buf1[220 + 3 * (-current_page - 2) + i]);
            disp_data(86, 2 + 2 * i, 14, HT7038_buf1[256 + 3 * (-current_page - 2) + i]);
        }
    }
    else if (current_page == -11) // �����ѹг��
    {
        Lcd12864_Write14CnCHAR(0, 0, 0, "%iHR A   B   C");

        Lcd12864_Write14CnCHAR(0, 2, 2, "29");
        Lcd12864_Write14CnCHAR(0, 2, 4, "30");
        Lcd12864_Write14CnCHAR(0, 2, 6, "31");
        for (int i = 0; i < 3; i++)
        {
            disp_data(16, 2 + 2 * i, 14, HT7038_buf1[190 + 3 * (-current_page - 2) + i]);
            disp_data(51, 2 + 2 * i, 14, HT7038_buf1[220 + 3 * (-current_page - 2) + i]);
            disp_data(86, 2 + 2 * i, 14, HT7038_buf1[256 + 3 * (-current_page - 2) + i]);
        }
    }
    if (key == KEY_LEFT_PRES)
    {

        clear_screen();
        current_page--;
        if (current_page < -11)
        {
            current_page = -11;
        }
    }

    else if (key == KEY_RIGHRT_PRES) // ȷ��֮��Ҫ�����ݱȽϣ��б����������
    {

        clear_screen();
        current_page++;
        if (current_page > 11)
        {
            current_page = 11;
        }
    }
}
void demand()
{
    switch (current_page)
    {
    case 0:
        screenbase10();
        break;
    case 1:
        screenbase11();
        break;
    case 2:
        screenbase12();
        break;
    }
    if (key == KEY_LEFT_PRES)
    {
        clear_screen();
        current_page--;
    }

    else if (key == KEY_RIGHRT_PRES) // ȷ��֮��Ҫ�����ݱȽϣ��б����������
    {
        clear_screen();
        current_page++;
    }
}
/*************************************/
void Time1()
{

    HAL_RTC_GetTime(&hrtc, &stimestructure, RTC_FORMAT_BCD);
    HAL_RTC_GetDate(&hrtc, &sdatestructure, RTC_FORMAT_BCD);
    nian[0] = (sdatestructure.Year >> 4) + 0x30;
    nian[1] = (sdatestructure.Year & 0x0F) + 0x30;
    nian[2] = '\0';

    yue[0] = (sdatestructure.Month >> 4) + 0x30;
    yue[1] = (sdatestructure.Month & 0x0F) + 0x30;
    yue[2] = '\0';

    ri[0] = (sdatestructure.Date >> 4) + 0x30;
    ri[1] = (sdatestructure.Date & 0x0F) + 0x30;
    ri[2] = '\0';

    shi[0] = (stimestructure.Hours >> 4) + 0x30;
    shi[1] = (stimestructure.Hours & 0x0F) + 0x30;
    shi[2] = '\0';

    fen[0] = (stimestructure.Minutes >> 4) + 0x30;
    fen[1] = (stimestructure.Minutes & 0x0F) + 0x30;
    fen[2] = '\0';

    miao[0] = (stimestructure.Seconds >> 4) + 0x30;
    miao[1] = (stimestructure.Seconds & 0x0F) + 0x30;
    miao[2] = '\0';
    display_ASCIIstring_8x16(7, 8, nian);
    display_graphic_8x16(7, 24, qirigang);
    display_ASCIIstring_8x16(7, 29, yue);
    display_graphic_8x16(7, 45, qirigang);
    display_ASCIIstring_8x16(7, 50, ri);

    display_graphic_8x16(7, 65, xiaogang);
    display_ASCIIstring_8x16(7, 71, shi);
    display_graphic_8x16(7, 87, xiaomaohao);
    display_ASCIIstring_8x16(7, 92, fen);
    display_graphic_8x16(7, 108, xiaomaohao);
    display_ASCIIstring_8x16(7, 113, miao);
}
typedef struct meun1
{
    char *NAME;
    bool *openorclose;
} meunpro;
void displayMenupro(meunpro meunprotect[], int totalItems, int page)
{
    for (int i = 0; i < totalItems; i++)
    {
        int x;
        Lcd12864_Write16CnCHAR(0, 0, 2 * i, meunprotect[i].NAME);
        x = strlen(meunprotect[i].NAME);
        display_graphic_8x16(2 * i + 1, 8 * x + 5, maohao);
    }
    if (key == KEY_LEFT_PRES && (*(meunprotect[a].openorclose)) == 1)
    {
        (*(meunprotect[a].openorclose)) = 0;
    }
    else if (key == KEY_LEFT_PRES && (*(meunprotect[a].openorclose)) == 0)
    {
        (*(meunprotect[a].openorclose)) = 1;
    }
    else if (key == KEY_RIGHRT_PRES && (*(meunprotect[a].openorclose)) == 0)
    {
        (*(meunprotect[a].openorclose)) = 1;
    }
    else if (key == KEY_RIGHRT_PRES && (*(meunprotect[a].openorclose)) == 1)
    {
        (*(meunprotect[a].openorclose)) = 0;
    }

    switch (a) // a�ǰ��˼��� d���жϳ������м���    //���switch��ѡ������һ��
    {
    case 0:
        if (a < totalItems)
        {

            display_kaiguan_frame(1, 106, *(meunprotect[0].openorclose));
            if (totalItems > 1)
                display_kaiguan(3, 106, *(meunprotect[1].openorclose));
            if (totalItems > 2)
                display_kaiguan(5, 106, *(meunprotect[2].openorclose));
            if (totalItems > 3)
                display_kaiguan(7, 106, *(meunprotect[3].openorclose));
        }

        break;
    case 1:
        if (a < totalItems)
        {

            display_kaiguan(1, 106, *(meunprotect[0].openorclose));
            if (totalItems > 1)
                display_kaiguan_frame(3, 106, *(meunprotect[1].openorclose));
            if (totalItems > 2)
                display_kaiguan(5, 106, *(meunprotect[2].openorclose));
            if (totalItems > 3)
                display_kaiguan(7, 106, *(meunprotect[3].openorclose));
        }
        break;

    case 2:
        if (a < totalItems)
        {

            display_kaiguan(1, 106, *(meunprotect[0].openorclose));
            if (totalItems > 1)
                display_kaiguan(3, 106, *(meunprotect[1].openorclose));
            if (totalItems > 2)
                display_kaiguan_frame(5, 106, *(meunprotect[2].openorclose));
            if (totalItems > 3)
                display_kaiguan(7, 106, *(meunprotect[3].openorclose));
        }
        break;
    case 3:
        if (a < totalItems)
        {

            display_kaiguan(1, 106, *(meunprotect[0].openorclose));
            if (totalItems > 1)
                display_kaiguan(3, 106, *(meunprotect[1].openorclose));
            if (totalItems > 2)
                display_kaiguan(5, 106, *(meunprotect[2].openorclose));
            if (totalItems > 3)
                display_kaiguan_frame(7, 106, *(meunprotect[3].openorclose));
        }
        break;
    }
    if (key == KEY_UP_PRES)
    {
        a++;
        if (a > totalItems - 1)
        //	if(a>totalItems-1&&F_Ypro!=4)
        {
            clear_screen();
            a = 0;
            clear_screen();
            if (F_Ypro == 3)
                F_Ypro = 4;
            if (F_Ypro == 2)
                F_Ypro = 3;
            if (F_Ypro == 1)
                F_Ypro = 2;
            if (F_Ypro == 0)
                F_Ypro = 1;
        }
        //	}else if(a>totalItems-1&&F_Y==4) a=totalItems-1;
    }
    else if (key == KEY_DOWN_PRES)
    {
        a--;
        if (a < 0)
        {
            a = 0;
            clear_screen();
            if (F_Ypro == 1)
                F_Ypro = 0;
            if (F_Ypro == 2)
                F_Ypro = 1;
            if (F_Ypro == 3)
                F_Ypro = 2;
            if (F_Ypro == 4)
                F_Ypro = 3;
        }
    }
    else if (key == KEY_AFFIRM_PRES) // ȷ��֮��Ҫ�����ݱȽϣ��б����������
    {
        judge();
        a++;
        if (a > totalItems - 1)
        //	if(a>totalItems-1&&F_Ypro!=4)
        {
            clear_screen();
            a = 0;
            clear_screen();
            if (F_Ypro == 3)
                F_Ypro = 4;
            if (F_Ypro == 2)
                F_Ypro = 3;
            if (F_Ypro == 1)
                F_Ypro = 2;
            if (F_Ypro == 0)
                F_Ypro = 1;
        }
    }
}
void meun_protect1() // ��������1
{
    meunpro meunprotect[] = {
        {"1©��澯", &F_trip_ld},
        {"2�Զ�����", &F_auto_ld},
        {"3ͻ�䱣��", &F_TB_trip},
        {"4�ز�����", &F_Special_wave},
    };
    int totalItems = sizeof(meunprotect) / sizeof(meunprotect[0]);
    displayMenupro(meunprotect, totalItems, 0);

    if (F_trip_ld == 0)
        ctrlword[3] &= 0xFC; // �����ַ������ڷ���
    if (F_trip_ld == 1)
    {
        ctrlword[3] &= 0xFC;
        ctrlword[3] += 0x02;
    }
    ctrlword4_analyze();
}
void meun_protect2() // ��������2
{
    meunpro meunprotect[] = {
        {"5���㱣��", &F_trip_QL},
        {"6����ѹ����", &F_trip_gy},
        {"7Ƿ��ѹ����", &F_trip_qy},
        {"8���ౣ��", &F_trip_QX},
    };
    int totalItems = sizeof(meunprotect) / sizeof(meunprotect[0]);
    displayMenupro(meunprotect, totalItems, 0);

    if (F_trip_QL == 1)
        ctrlword[2] |= 0x01;
    if (F_trip_QL == 0)
        ctrlword[2] &= (~0x01);
    if (F_trip_gy == 1)
        ctrlword[1] |= 0x10;
    if (F_trip_gy == 0)
        ctrlword[1] &= (~0x10);
    if (F_trip_qy == 1)
        ctrlword[1] |= 0x40;
    if (F_trip_qy == 0)
        ctrlword[1] &= (~0x40);
    if (F_trip_QX == 1)
        ctrlword[1] |= 0x04;
    if (F_trip_QX == 0)
        ctrlword[1] &= (~0x04);
}
void meun_protect3() // ��������3
{

    meunpro meunprotect[] = {
        {"9ʧѹ����", &F_trip_sy},
        {"10��������", &F_trip_gl},
        {"11���ӱ���", &F_ip},
        {"12˲ʱ����", &F_ip_3},
    };
    int totalItems = sizeof(meunprotect) / sizeof(meunprotect[0]);
    displayMenupro(meunprotect, totalItems, 0);

    if (F_trip_gl == 1)
        ctrlword[1] |= 0x01;
    if (F_trip_gl == 0)
        ctrlword[1] &= (~0x01);
}
void meun_protect4() // ��������4
{

    meunpro meunprotect[] = {
        //		{"13У׼��λ",&jiaozhun},
        {"13�ϵ��բ", &shangdian},
        {"14©���բ", &LD_hezha},
        {"15��ѹ��բ", &DY_hezha},
        {"16������բ", &DL_hezha},
    };
    int totalItems = sizeof(meunprotect) / sizeof(meunprotect[0]);
    displayMenupro(meunprotect, totalItems, 0);
}
void meun_protect5() // ��������5
{

    meunpro meunprotect[] = {
        //		{"17������բ",&DL_hezha},
        {"17�¶ȱ���", &wendu},
        {"18ͨ�ŷ�ʽ", &F_TX},

    };
    int totalItems = sizeof(meunprotect) / sizeof(meunprotect[0]);
    displayMenupro(meunprotect, totalItems, 0);
}
typedef struct meun2
{
    char *NAME;
    unsigned int data;
} meund;

void displayMenudata(meund meundata[], int total_items)
{
    unsigned char array_temp[10];
    unsigned char lishijilu_1[5] = {0};

    int start_index = current_page * ITEMS_PER_PAGE;
    int end_index = start_index + ITEMS_PER_PAGE;
    if (end_index > total_items)
    {
        end_index = total_items;
    }
    Lcd12864_Write16CnCHAR(0, 0, 0, meundata[2 * current_page].NAME);
    Lcd12864_Write16CnCHAR(0, 100, 2, "��");
    Lcd12864_Write16CnCHAR(0, 0, 4, meundata[2 * current_page + 1].NAME);
    Lcd12864_Write16CnCHAR(0, 100, 6, "��");
    DectoBCD(array_temp, meundata[2 * current_page].data, 2);
    generate_chuan(lishijilu_1, array_temp[1] >> 4, array_temp[1] & 0x0F, array_temp[0] >> 4, array_temp[0] & 0x0F);
    display_ASCIIstring_8x16(3, 39, lishijilu_1);
    DectoBCD(array_temp, meundata[2 * current_page + 1].data, 2);
    generate_chuan(lishijilu_1, array_temp[1] >> 4, array_temp[1] & 0x0F, array_temp[0] >> 4, array_temp[0] & 0x0F);
    display_ASCIIstring_8x16(7, 39, lishijilu_1);

    if (key == KEY_DOWN_PRES)
    {
        if (current_page > 0)
        {
            clear_screen();
            current_page--;
        }
    }
    else if (key == KEY_UP_PRES)
    {
        if ((current_page + 1) * ITEMS_PER_PAGE < total_items)
        {
            clear_screen();
            current_page++;
        }
    }
}
void menu_fault()
{
    Lcd12864_Write16CnCHAR(0, 35, 0, "���ϼ�¼");
    switch (current_page)
    {
    case 0:
        Lcd12864_Write16CnCHAR(1, 5, 3, "��բ����"); // ��բ����
        Lcd12864_Write16CnCHAR(0, 5, 5, "������Ϣ"); // ������Ϣ
        break;
    case 1:
        Lcd12864_Write16CnCHAR(0, 5, 3, "��բ����"); // ��բ����
        Lcd12864_Write16CnCHAR(1, 5, 5, "������Ϣ"); // ������Ϣ
        break;
    }
    if (key == KEY_DOWN_PRES)
    {
        if (current_page > 0)
        {
            clear_screen();
            current_page--;
        }
    }
    else if (key == KEY_UP_PRES)
    {
        if (current_page < 1)
        {
            clear_screen();
            current_page++;
        }
    }
    else if (key == KEY_AFFIRM_PRES) // ȷ��֮��Ҫ�����ݱȽϣ��б����������
    {
        switch (current_page)
        {
        case 0:
            F_MAINormenu = 12;
            break;
        case 1:
            F_MAINormenu = 13;

            break;
        }
        clear_screen();
        current_page = 0;
    }
}

void meun_data() // ��բ��¼����
{
    Num_tripall = 1;
    Num_clearall = 2;
    meund meundata[] = {
        {"1 ����բ����", Num_tripall},
        {"2 �����������", Num_clearall},
        {"3 ������բ����", Num_triplock},
        {"4 ©����բ����", Num_tripleak},
        {"5������բ����", Num_tripcur},
        {"6 ��ѹ��բ����", Num_tripvol},
        {"7�ֶ�������բ����", Num_triphand},
        {"8 ������բ����", Num_triptest},
        {"9 ������բ����", Num_tripdelay},
        {"10 ��˲��բ���� ", Num_tripinstant},
        {"11 Ƿѹ��բ���� ", Num_leakover},
        {"12 ȱ����բ���� ", Num_leakprotect},
    };
    int total_items = sizeof(meundata) / sizeof(meundata[0]);
    displayMenudata(meundata, total_items);
}
typedef struct meun3
{
    char *NAME1;
    char *NAME2;
    char *NAME3;
    char *NAME4;
    unsigned int data;
} meunadj;
void displayMenuadj(meunadj meunadjust[], int total_items)
{
    if (current_page == 0)
    {

        Lcd12864_Write16CnCHAR(0, 32, 0, meunadjust[0].NAME1);
        if (F_adjustbegin == 0)
            Lcd12864_Write16CnCHAR(0, 32, 0, meunadjust[0].NAME2);
        else if (F_adjustbegin == 1)
            Lcd12864_Write16CnCHAR(0, 32, 0, meunadjust[0].NAME3);
        if (F_jiaozhuned == 1)
        {

            F_adjustbegin = 2;

            Lcd12864_Write16CnCHAR(0, 32, 0, meunadjust[0].NAME4);
        }
    }
    else if (current_page == 1)
    {

        Lcd12864_Write16CnCHAR(0, 32, 0, meunadjust[1].NAME1);
        if (F_adjustbegin == 0)
            Lcd12864_Write16CnCHAR(0, 32, 0, meunadjust[1].NAME2);
        else if (F_adjustbegin == 1)
            Lcd12864_Write16CnCHAR(0, 32, 0, meunadjust[1].NAME3);
        if (F_jiaozhuned == 1)
        {

            F_adjustbegin = 2;

            Lcd12864_Write16CnCHAR(0, 32, 0, meunadjust[1].NAME4);
        }
    }
    else if (current_page == 2)
    {
        if (Type_Cur == 0)
            Lcd12864_Write16CnCHAR(0, 24, 0, meunadjust[2].NAME1);
        if (Type_Cur == 1)
            Lcd12864_Write16CnCHAR(0, 24, 0, meunadjust[3].NAME1);
        if (Type_Cur == 2)
            Lcd12864_Write16CnCHAR(0, 24, 0, meunadjust[4].NAME1);
        if (Type_Cur == 3)
            Lcd12864_Write16CnCHAR(0, 24, 0, meunadjust[5].NAME1);
        if (Type_Cur == 4)
            Lcd12864_Write16CnCHAR(0, 24, 0, meunadjust[6].NAME1);

        if (F_adjustbegin == 0)
            Lcd12864_Write16CnCHAR(0, 32, 0, meunadjust[2].NAME2);
        else if (F_adjustbegin == 1)
            Lcd12864_Write16CnCHAR(0, 32, 0, meunadjust[2].NAME3);
        if (F_jiaozhuned == 1)
        {

            F_adjustbegin = 2;
            Lcd12864_Write16CnCHAR(0, 32, 0, meunadjust[2].NAME4);
        }
    }

    if (key == KEY_DOWN_PRES) // У׼�л�������д���ˣ�
    {
        F_jiaozhuned = 0;
        F_adjustbegin = 0;
        if (current_page > 0)
            current_page--;
        else
            current_page = 2;
        clear_screen();
    }
    else if (key == KEY_UP_PRES) // �����У׼���棨����д���ˣ�
    {
        F_jiaozhuned = 0;
        F_adjustbegin = 0;
        if (current_page < 2)
            current_page++;
        else
            current_page = 0;
        clear_screen();
    }
    else if (key == KEY_AFFIRM_PRES)
    {

        F_adjustbegin = 1;
        Cal_state = current_page;
        USART_LCD_Transmit(2, 3);

        clear_screen();
    }
}
void meun_adjust()
{ // У׼����

    meunadj meunadjust[] = {
        {"©��У׼", "\r\r  ��ʼ©��У׼", "\r\r ����©��У׼...", "\r\r ©��У׼���    "},
        {"��ѹУ׼", "\r\r  ��ʼ��ѹУ׼", "\r\r ���ڵ�ѹУ׼...", "\r\r ��ѹУ׼���    "},
        {"125A����У׼", "\r\r  ��ʼ����У׼", "\r\r ���ڵ���У׼...", "\r\r ����У׼���    "},
        {"250A����У׼", "\r\r  ��ʼ����У׼", "\r\r ���ڵ���У׼...", "\r\r ����У׼���    "},
        {"400A����У׼", "\r\r  ��ʼ����У׼", "\r\r ���ڵ���У׼...", "\r\r ����У׼���    "},
        {"630A����У׼", "\r\r  ��ʼ����У׼", "\r\r ���ڵ���У׼...", "\r\r ����У׼���    "},
        {"800A����У׼", "\r\r  ��ʼ����У׼", "\r\r ���ڵ���У׼...", "\r\r ����У׼���    "},

    };
    int total_items = sizeof(meunadjust) / sizeof(meunadjust[0]);
    displayMenuadj(meunadjust, total_items);
}
void fenzhaing() // ���ڷ�բ�н���
{
    Lcd12864_Write16CnCHAR(0, 32, 0, "\r  ���ڷ�բ...");
    if (isfenzha == 0)
    {
        F_MAINormenu = 0;
    }
}
void hezhaing() // ���ں�բ�н���
{
    Lcd12864_Write16CnCHAR(0, 32, 0, "\r  ���ں�բ...");
    if (isfenzha == 1)
    {
        F_MAINormenu = 0;
    }
}
void problemdisp() // ������ʾ
{
    if (F_gz_disp == A_qy || F_gz_disp == B_qy || F_gz_disp == C_qy) // Ƿѹ����
    {
        xianshishuju(gz_disp);

        Lcd12864_Write16CnCHAR(0, 32, 0, "Ƿѹ����\r ����ֵ");

        if (F_gz_disp == A_qy)
        {
            display_ASCIIstring_8x16(3, 75, "Ua:    V");
        }
        else if (F_gz_disp == B_qy)
        {
            display_ASCIIstring_8x16(3, 75, "Ub:    V");
        }
        else if (F_gz_disp == C_qy)
        {
            display_ASCIIstring_8x16(3, 75, "Uc:    V");
        }
        display_ASCIIstring_8x16(3, 100, zifu_dian);

        Lcd12864_Write16CnCHAR(0, 0, 4, " �غ�բ����:");
        xianshishuju(F_ch);
        display_ASCIIstring_8x16(5, 110, zifu_dian);

        Lcd12864_Write16CnCHAR(0, 0, 6, " Ƿѹ��λ:");
        display_ASCIIstring_8x16(7, 88, DIANYA_1[Vol_q]);
    }
    if (F_gz_disp == A_QX || F_gz_disp == B_QX || F_gz_disp == C_QX) // ȱ��
    {

        xianshishuju(gz_disp);
        Lcd12864_Write16CnCHAR(0, 32, 0, "ȱ�����\r ����ֵ");

        if (F_gz_disp == A_QX)
        {
            display_ASCIIstring_8x16(3, 75, "Ua:    V");
        }
        else if (F_gz_disp == B_QX)
        {
            display_ASCIIstring_8x16(3, 75, "Ub:    V");
        }
        else if (F_gz_disp == C_QX)
        {
            display_ASCIIstring_8x16(3, 75, "Uc:    V");
        }
        display_ASCIIstring_8x16(3, 100, zifu_dian);

        Lcd12864_Write16CnCHAR(0, 0, 4, " �غ�բ����:");
        xianshishuju(F_ch);
        display_ASCIIstring_8x16(5, 110, zifu_dian);
    }
    // ��ѹ��GY��
    if (F_gz_disp == A_gy || F_gz_disp == B_gy || F_gz_disp == C_gy)
    {

        xianshishuju(gz_disp);

        Lcd12864_Write16CnCHAR(0, 32, 0, "��ѹ����\r ����ֵ");

        if (F_gz_disp == A_gy)
        {
            display_ASCIIstring_8x16(3, 75, "Ua:    V");
        }
        else if (F_gz_disp == B_gy)
        {
            display_ASCIIstring_8x16(3, 75, "Ub:    V");
        }
        else if (F_gz_disp == C_gy)
        {
            display_ASCIIstring_8x16(3, 75, "Uc:    V");
        }
        display_ASCIIstring_8x16(3, 100, zifu_dian);

        Lcd12864_Write16CnCHAR(0, 0, 4, " �غ�բ����:");
        xianshishuju(F_ch);

        display_ASCIIstring_8x16(5, 110, zifu_dian);
        Lcd12864_Write16CnCHAR(0, 0, 6, " ��ѹ��λ:");
        display_ASCIIstring_8x16(7, 88, DIANYA[Vol_g]);
    }
    // ©�硰ld��
    if (F_gz_disp == L_hb)
    {

        xianshishuju(gz_disp);
        Lcd12864_Write16CnCHAR(0, 32, 0, "©�����\r ����ֵ      mA");
        display_ASCIIstring_8x16(3, 76, zifu_dian);
        Lcd12864_Write16CnCHAR(0, 0, 4, " �غ�բ����:");
        xianshishuju(F_ch);

        display_ASCIIstring_8x16(5, 110, zifu_dian);
        Lcd12864_Write16CnCHAR(0, 0, 6, " �©��:");
        display_ASCIIstring_8x16(7, 88, dianliu[D_LCur]);
    }
    // ������GL��
    if ((F_gz_disp > L_hb) && (F_gz_disp < Gz_TD))
    {

        SET_D_Cur = D_Cur;
        I_VAL_handle();
        //                gz_disp1=SET_I_VAL ;
        xianshishuju(gz_disp);

        Lcd12864_Write16CnCHAR(0, 32, 0, "��������\r ����ֵ");
        if (F_gz_disp == A_gl)
        {
            display_ASCIIstring_8x16(3, 75, "Ia:    A");
        }
        else if (F_gz_disp == B_gl)
        {
            display_ASCIIstring_8x16(3, 75, "Ib:    A");
        }
        else if (F_gz_disp == C_gl)
        {
            display_ASCIIstring_8x16(3, 75, "Ic:    A");
        }
        else if (F_gz_disp == N_gl)
        {
            display_ASCIIstring_8x16(3, 75, "In:    A");
        }
        display_ASCIIstring_8x16(3, 100, zifu_dian);

        Lcd12864_Write16CnCHAR(0, 0, 4, " �غ�բ����:");
        xianshishuju(F_ch);

        display_ASCIIstring_8x16(5, 110, zifu_dian);
        Lcd12864_Write16CnCHAR(0, 0, 6, " ������λ:    ");

        I_VAL_handle();

        xianshishuju_dianliu(SET_I_VAL);

        display_ASCIIstring_8x16(7, 92, zifu_dian); // ��������
    }
    // ͣ�硰tD��
    if (F_gz_disp == Gz_TD)
    {

        Lcd12864_Write16CnCHAR(0, 32, 0, "ͣ�����");
    }
    // �ֶ��Ͷ�·Ϊδ֪��UN��
    if (F_gz_disp == FZ_UK)
    {

        Lcd12864_Write16CnCHAR(0, 32, 0, "δ֪����");
    }
    // ������AJ��
    if (F_gz_disp == FZ_AJ)
    {

        Lcd12864_Write16CnCHAR(0, 32, 0, "������բ");
    }
    // Զ�̡�YC��
    if (F_gz_disp == FZ_YC)
    {

        Lcd12864_Write16CnCHAR(0, 32, 0, "Զ�̷�բ");
    }
    if (F_gz_disp == Gz_QL)
    {

        Lcd12864_Write16CnCHAR(0, 32, 0, "ȱ���բ");
    }
    if (F_gz_disp == Tem_IN_N)
    {
        Lcd12864_Write16CnCHAR(0, 32, 0, "N->���·�բ");
    }
    if (F_gz_disp == Tem_IN_A)
    {

        Lcd12864_Write16CnCHAR(0, 32, 0, "A->���·�բ");
    }
    if (F_gz_disp == Tem_IN_B)
    {

        Lcd12864_Write16CnCHAR(0, 32, 0, "B->���·�բ");
    }
    if (F_gz_disp == Tem_IN_C)
    {
        Lcd12864_Write16CnCHAR(0, 32, 0, "C->���·�բ");
    }
    if (F_gz_disp == Tem_OUT_N)
    {
        Lcd12864_Write16CnCHAR(0, 32, 0, "N<-���·�բ");
    }
    if (F_gz_disp == Tem_OUT_A)
    {

        Lcd12864_Write16CnCHAR(0, 32, 0, "A<-���·�բ");
    }
    if (F_gz_disp == Tem_OUT_B)
    {

        Lcd12864_Write16CnCHAR(0, 32, 0, "B<-���·�բ");
    }
    if (F_gz_disp == Tem_OUT_C)
    {
        Lcd12864_Write16CnCHAR(0, 32, 0, "C<-���·�բ");
    }
}

void timechange() // ���ں�ʱ�����
{
    // RTC_Set_Time(tim_h3,tim_f3,tim_s3);
    // RTC_Set_Date(tim_y3,tim_m3,tim_d3);
    Disp_date();
    Disp_time();

    switch (a)
    {
    case 0:
    {
        display_ASCIIstring_8x16(3, 35, nian_qian);
        display_ASCIIstring_8x16_fanxian(3, 51, nian);
        display_graphic_8x16(3, 67, qirigang);
        display_ASCIIstring_8x16(3, 72, yue);
        display_graphic_8x16(3, 88, qirigang);
        display_ASCIIstring_8x16(3, 93, ri);
        display_ASCIIstring_8x16(7, 51, shi);
        display_graphic_8x16(7, 67, xiaomaohao);
        display_ASCIIstring_8x16(7, 72, fen);
        display_graphic_8x16(7, 88, xiaomaohao);
        display_ASCIIstring_8x16(7, 93, miao);
    }
    break;
    case 1:
    {
        display_ASCIIstring_8x16(3, 35, nian_qian);
        display_ASCIIstring_8x16(3, 51, nian);
        display_graphic_8x16(3, 67, qirigang);
        display_ASCIIstring_8x16_fanxian(3, 72, yue);
        display_graphic_8x16(3, 88, qirigang);
        display_ASCIIstring_8x16(3, 93, ri);
        display_ASCIIstring_8x16(7, 51, shi);
        display_graphic_8x16(7, 67, xiaomaohao);
        display_ASCIIstring_8x16(7, 72, fen);
        display_graphic_8x16(7, 88, xiaomaohao);
        display_ASCIIstring_8x16(7, 93, miao);
    }
    break;
    case 2:
    {
        display_ASCIIstring_8x16(3, 35, nian_qian);
        display_ASCIIstring_8x16(3, 51, nian);
        display_graphic_8x16(3, 67, qirigang);
        display_ASCIIstring_8x16(3, 72, yue);
        display_graphic_8x16(3, 88, qirigang);
        display_ASCIIstring_8x16_fanxian(3, 93, ri);
        display_ASCIIstring_8x16(7, 51, shi);
        display_graphic_8x16(7, 67, xiaomaohao);
        display_ASCIIstring_8x16(7, 72, fen);
        display_graphic_8x16(7, 88, xiaomaohao);
        display_ASCIIstring_8x16(7, 93, miao);
    }
    break;
    case 3:
    {
        display_ASCIIstring_8x16(3, 35, nian_qian);
        display_ASCIIstring_8x16(3, 51, nian);
        display_graphic_8x16(3, 67, qirigang);
        display_ASCIIstring_8x16(3, 72, yue);
        display_graphic_8x16(3, 88, qirigang);
        display_ASCIIstring_8x16(3, 93, ri);
        display_ASCIIstring_8x16_fanxian(7, 51, shi);
        display_graphic_8x16(7, 67, xiaomaohao);
        display_ASCIIstring_8x16(7, 72, fen);
        display_graphic_8x16(7, 88, xiaomaohao);
        display_ASCIIstring_8x16(7, 93, miao);
    }
    break;
    case 4:
    {
        display_ASCIIstring_8x16(3, 35, nian_qian);
        display_ASCIIstring_8x16(3, 51, nian);
        display_graphic_8x16(3, 67, qirigang);
        display_ASCIIstring_8x16(3, 72, yue);
        display_graphic_8x16(3, 88, qirigang);
        display_ASCIIstring_8x16(3, 93, ri);
        display_ASCIIstring_8x16(7, 51, shi);
        display_graphic_8x16(7, 67, xiaomaohao);
        display_ASCIIstring_8x16_fanxian(7, 72, fen);
        display_graphic_8x16(7, 88, xiaomaohao);
        display_ASCIIstring_8x16(7, 93, miao);
    }
    break;
    case 5:
    {
        display_ASCIIstring_8x16(3, 35, nian_qian);
        display_ASCIIstring_8x16(3, 51, nian);
        display_graphic_8x16(3, 67, qirigang);
        display_ASCIIstring_8x16(3, 72, yue);
        display_graphic_8x16(3, 88, qirigang);
        display_ASCIIstring_8x16(3, 93, ri);
        display_ASCIIstring_8x16(7, 51, shi);
        display_graphic_8x16(7, 67, xiaomaohao);
        display_ASCIIstring_8x16(7, 72, fen);
        display_graphic_8x16(7, 88, xiaomaohao);
        display_ASCIIstring_8x16_fanxian(7, 93, miao);
    }
    break;
    }
    if (key == KEY_UP_PRES)
    {

        a++;
        if (a > 5)
        {
            F_Y = 6;
            a = 0;
            clear_screen();
        }
    }
    else if (key == KEY_DOWN_PRES)
    {

        a--;
        if (a < 0)
        {

            F_Y = 3;
            a = 0;
            clear_screen();
        }
    }
    else if (key == KEY_AFFIRM_PRES)
    {
        RTC_Set_Time(tim_h3, tim_f3, tim_s3);
        RTC_Set_Date(tim_y3, tim_m3, tim_d3);
        a++;
        USART_LCD_Transmit(57, 1); // ��������
        if (a > 5)
        {
            F_Y = 6;
            a = 0;
            clear_screen();
        }
    }
    else if (key == KEY_LEFT_PRES)
    {
        clear_screen();
        switch (a)
        {
        case 0:
        {
            tim_y3++;
            if ((tim_y3 & 0x0F) > 9)
                tim_y3 += 6;
        }
        break;
        case 1:
        {
            if (tim_m3 < 18)
            {
                tim_m3++;
                if ((tim_m3 & 0x0F) > 9)
                    tim_m3 += 6;
            }
        }
        break;
        case 2:
        {
            if (tim_d3 < 49)
            {
                tim_d3++;
                if ((tim_d3 & 0x0F) > 9)
                    tim_d3 += 6;
            }
        }
        break;
        case 3:
        {
            if (tim_h3 < 36)
            {
                tim_h3++;
                if ((tim_h3 & 0x0F) > 9)
                    tim_h3 += 6;
            }
        }
        break;
        case 4:
        {
            if (tim_f3 < 96)
            {
                tim_f3++;
                if ((tim_f3 & 0x0F) > 9)
                    tim_f3 += 6;
            }
        }
        break;
        case 5:
        {
            if (tim_s3 < 96)
            {
                tim_s3++;
                if ((tim_s3 & 0x0F) > 9)
                    tim_s3 += 6;
            }
        }
        break;
        }
    }
    else if (key == KEY_RIGHRT_PRES)
    {
        clear_screen();
        switch (a)
        {
        case 0:
        {
            if (tim_y3 > 0)
            {
                tim_y3--;
                if ((tim_y3 & 0x0F) == 15)
                    tim_y3 -= 6;
            }
        }
        break;
        case 1:
        {
            if (tim_m3 > 0)
            {
                tim_m3--;
                if ((tim_m3 & 0x0F) == 15)
                    tim_m3 -= 6;
            }
        }
        break;
        case 2:
        {
            if (tim_d3 > 0)
            {
                tim_d3--;
                if ((tim_d3 & 0x0F) == 15)
                    tim_d3 -= 6;
            }
        }
        break;
        case 3:
        {
            if (tim_h3 > 0)
            {
                tim_h3--;
                if ((tim_h3 & 0x0F) == 15)
                    tim_h3 -= 6;
            }
        }
        break;
        case 4:
        {
            if (tim_f3 > 0)
            {
                tim_f3--;
                if ((tim_f3 & 0x0F) == 15)
                    tim_f3 -= 6;
            }
        }
        break;
        case 5:
        {
            if (tim_s3 > 0)
            {
                tim_s3--;
                if ((tim_s3 & 0x0F) == 15)
                    tim_s3 -= 6;
            }
        }
        break;
        }
    }
    Disp_Write_time();
}
int mimaset() // �������
{

    if (qiehuan == 0)
    {
        Lcd12864_Write16CnCHAR(0, 33, 0, "��������");
        if (current_page == 0)
        {
            if (key == KEY_UP_PRES)
            {
                clear_screen();
                if (mima[0] < 9)
                    mima[0]++;
            }
            else if (key == KEY_DOWN_PRES)
            {
                clear_screen();
                if (mima[0] > 0)
                    mima[0]--;
            }
            Lcd12864_Write16CnCHAR(0, 32, 4, "��");
        }

        else if (current_page == 1)
        {
            if (key == KEY_UP_PRES)
            {
                clear_screen();
                if (mima[1] < 9)
                    mima[1]++;
            }
            else if (key == KEY_DOWN_PRES)
            {
                clear_screen();
                if (mima[1] > 0)
                    mima[1]--;
            }
            Lcd12864_Write16CnCHAR(0, 49, 4, "��"); // ��ʾѡ�е���
        }
        else if (current_page == 2)
        {
            if (key == KEY_UP_PRES)
            {
                clear_screen();
                if (mima[2] < 9)
                    mima[2]++;
            }
            else if (key == KEY_DOWN_PRES)
            {
                clear_screen();
                if (mima[2] > 0)
                    mima[2]--;
            }
            Lcd12864_Write16CnCHAR(0, 66, 4, "��");
        }
        else if (current_page == 3)
        {
            if (key == KEY_UP_PRES)
            {
                clear_screen();
                if (mima[3] < 9)
                    mima[3]++;
            }
            else if (key == KEY_DOWN_PRES)
            {
                clear_screen();
                if (mima[3] > 0)
                    mima[3]--;
            }
            if (key == KEY_AFFIRM_PRES)
            {
                if (mima[0] == mima_set[0] && mima[1] == mima_set[1] && mima[2] == mima_set[2] && mima[3] == mima_set[3])
                {
                    clear_screen();
                    current_page = 0;
                    F_MAINormenu = 10; // �������޸�����֮��ȥʲô����
                    clear_screen();
                    return 0;
                }
                else
                    qiehuan = 1;
                clear_screen();
                return 0;
            }

            Lcd12864_Write16CnCHAR(0, 83, 4, "��");
        }
        xianshishuju(mima[0]);
        Lcd12864_Write16CnCHAR(0, 32, 2, zifu_dian);
        xianshishuju(mima[1]);
        Lcd12864_Write16CnCHAR(0, 49, 2, zifu_dian);
        xianshishuju(mima[2]);
        Lcd12864_Write16CnCHAR(0, 66, 2, zifu_dian);
        xianshishuju(mima[3]);
        Lcd12864_Write16CnCHAR(0, 83, 2, zifu_dian);
        if (key == KEY_AFFIRM_PRES)
        {
            if (current_page < 3)
            {
                clear_screen();
                current_page++;
            }
        }
        else if (key == KEY_RIGHRT_PRES)
        {
            if (current_page > 0)
            {
                clear_screen();
                current_page--;
            }
        }
        else if (key == KEY_LEFT_PRES)
        {
            if (current_page < 3)
            {
                clear_screen();
                current_page++;
            }
        }
    }
    else if (qiehuan == 1)
    {
        Lcd12864_Write16CnCHAR(0, 33, 3, "�������");
        if (key == KEY_AFFIRM_PRES)
        {
            clear_screen();
            current_page = 0;
            qiehuan = 0;
        }
    }
}
void menu_mimaset() // �޸���������ͨ�ŵ�ַ
{
    unsigned char mima0[2], mima1[2], mima2[2], mima3[2];
    Lcd12864_Write16CnCHAR(0, 0, 0, "19�޸�����\r");
    display_graphic_8x16(1, 86, maohao);
    mima0[0] = mima_set_compare[0] + 0x30;
    mima0[1] = '\0';
    mima1[0] = mima_set_compare[1] + 0x30;
    mima1[1] = '\0';
    mima2[0] = mima_set_compare[2] + 0x30;
    mima2[1] = '\0';
    mima3[0] = mima_set_compare[3] + 0x30;
    mima3[1] = '\0';
    Lcd12864_Write16CnCHAR(0, 0, 3, "20ͨ�ŵ�ַ\r");
    display_graphic_8x16(1, 86, maohao);
    add_1_2[0] = (self_addr_code[0] & 0x0F) + 0x30;
    add_1_2[1] = '\0';

    add_1_1[0] = (self_addr_code[0] >> 4) + 0x30;
    add_1_1[1] = '\0';

    add_2_2[0] = (self_addr_code[1] & 0x0F) + 0x30;
    add_2_2[1] = '\0';

    add_2_1[0] = (self_addr_code[1] >> 4) + 0x30;
    add_2_1[1] = '\0';

    add_3_2[0] = (self_addr_code[2] & 0x0F) + 0x30;
    add_3_2[1] = '\0';

    add_3_1[0] = (self_addr_code[2] >> 4) + 0x30;
    add_3_1[1] = '\0';

    add_4_2[0] = (self_addr_code[3] & 0x0F) + 0x30;
    add_4_2[1] = '\0';

    add_4_1[0] = (self_addr_code[3] >> 4) + 0x30;
    add_4_1[1] = '\0';

    add_5_2[0] = (self_addr_code[4] & 0x0F) + 0x30;
    add_5_2[1] = '\0';

    add_5_1[0] = (self_addr_code[4] >> 4) + 0x30;
    add_5_1[1] = '\0';

    add_6_2[0] = (self_addr_code[5] & 0x0F) + 0x30;
    add_6_2[1] = '\0';

    add_6_1[0] = (self_addr_code[5] >> 4) + 0x30;
    add_6_1[1] = '\0';

    switch (a)
    {
    case 0:
    {
        display_ASCIIstring_8x16_fanxian(1, 96, mima0);
        display_ASCIIstring_8x16(1, 104, mima1);
        display_ASCIIstring_8x16(1, 112, mima2);
        display_ASCIIstring_8x16(1, 120, mima3);
        display_ASCIIstring_8x16(6, 8, add_6_1);
        display_ASCIIstring_8x16(6, 18, add_6_2);
        display_ASCIIstring_8x16(6, 28, add_5_1);
        display_ASCIIstring_8x16(6, 38, add_5_2);
        display_ASCIIstring_8x16(6, 48, add_4_1);
        display_ASCIIstring_8x16(6, 58, add_4_2);
        display_ASCIIstring_8x16(6, 68, add_3_1);
        display_ASCIIstring_8x16(6, 78, add_3_2);
        display_ASCIIstring_8x16(6, 88, add_2_1);
        display_ASCIIstring_8x16(6, 98, add_2_2);
        display_ASCIIstring_8x16(6, 108, add_1_1);
        display_ASCIIstring_8x16(6, 118, add_1_2);
    }
    break;
    case 1:
    {
        display_ASCIIstring_8x16(1, 96, mima0);
        display_ASCIIstring_8x16_fanxian(1, 104, mima1);
        display_ASCIIstring_8x16(1, 112, mima2);
        display_ASCIIstring_8x16(1, 120, mima3);
        display_ASCIIstring_8x16(6, 8, add_6_1);
        display_ASCIIstring_8x16(6, 18, add_6_2);
        display_ASCIIstring_8x16(6, 28, add_5_1);
        display_ASCIIstring_8x16(6, 38, add_5_2);
        display_ASCIIstring_8x16(6, 48, add_4_1);
        display_ASCIIstring_8x16(6, 58, add_4_2);
        display_ASCIIstring_8x16(6, 68, add_3_1);
        display_ASCIIstring_8x16(6, 78, add_3_2);
        display_ASCIIstring_8x16(6, 88, add_2_1);
        display_ASCIIstring_8x16(6, 98, add_2_2);
        display_ASCIIstring_8x16(6, 108, add_1_1);
        display_ASCIIstring_8x16(6, 118, add_1_2);
    }
    break;
    case 2:
    {
        display_ASCIIstring_8x16(1, 96, mima0);
        display_ASCIIstring_8x16(1, 104, mima1);
        display_ASCIIstring_8x16_fanxian(1, 112, mima2);
        display_ASCIIstring_8x16(1, 120, mima3);
        display_ASCIIstring_8x16(6, 8, add_6_1);
        display_ASCIIstring_8x16(6, 18, add_6_2);
        display_ASCIIstring_8x16(6, 28, add_5_1);
        display_ASCIIstring_8x16(6, 38, add_5_2);
        display_ASCIIstring_8x16(6, 48, add_4_1);
        display_ASCIIstring_8x16(6, 58, add_4_2);
        display_ASCIIstring_8x16(6, 68, add_3_1);
        display_ASCIIstring_8x16(6, 78, add_3_2);
        display_ASCIIstring_8x16(6, 88, add_2_1);
        display_ASCIIstring_8x16(6, 98, add_2_2);
        display_ASCIIstring_8x16(6, 108, add_1_1);
        display_ASCIIstring_8x16(6, 118, add_1_2);
    }
    break;
    case 3:
    {
        display_ASCIIstring_8x16(1, 96, mima0);
        display_ASCIIstring_8x16(1, 104, mima1);
        display_ASCIIstring_8x16(1, 112, mima2);
        display_ASCIIstring_8x16_fanxian(1, 120, mima3);
        display_ASCIIstring_8x16(6, 8, add_6_1);
        display_ASCIIstring_8x16(6, 18, add_6_2);
        display_ASCIIstring_8x16(6, 28, add_5_1);
        display_ASCIIstring_8x16(6, 38, add_5_2);
        display_ASCIIstring_8x16(6, 48, add_4_1);
        display_ASCIIstring_8x16(6, 58, add_4_2);
        display_ASCIIstring_8x16(6, 68, add_3_1);
        display_ASCIIstring_8x16(6, 78, add_3_2);
        display_ASCIIstring_8x16(6, 88, add_2_1);
        display_ASCIIstring_8x16(6, 98, add_2_2);
        display_ASCIIstring_8x16(6, 108, add_1_1);
        display_ASCIIstring_8x16(6, 118, add_1_2);
    }
    break;
    case 4:
    {
        display_ASCIIstring_8x16(1, 96, mima0);
        display_ASCIIstring_8x16(1, 104, mima1);
        display_ASCIIstring_8x16(1, 112, mima2);
        display_ASCIIstring_8x16(1, 120, mima3);
        display_ASCIIstring_8x16_fanxian(6, 8, add_6_1);
        display_ASCIIstring_8x16(6, 18, add_6_2);
        display_ASCIIstring_8x16(6, 28, add_5_1);
        display_ASCIIstring_8x16(6, 38, add_5_2);
        display_ASCIIstring_8x16(6, 48, add_4_1);
        display_ASCIIstring_8x16(6, 58, add_4_2);
        display_ASCIIstring_8x16(6, 68, add_3_1);
        display_ASCIIstring_8x16(6, 78, add_3_2);
        display_ASCIIstring_8x16(6, 88, add_2_1);
        display_ASCIIstring_8x16(6, 98, add_2_2);
        display_ASCIIstring_8x16(6, 108, add_1_1);
        display_ASCIIstring_8x16(6, 118, add_1_2);
    }
    break;
    case 5:
    {
        display_ASCIIstring_8x16(1, 96, mima0);
        display_ASCIIstring_8x16(1, 104, mima1);
        display_ASCIIstring_8x16(1, 112, mima2);
        display_ASCIIstring_8x16(1, 120, mima3);
        display_ASCIIstring_8x16(6, 8, add_6_1);
        display_ASCIIstring_8x16_fanxian(6, 18, add_6_2);
        display_ASCIIstring_8x16(6, 28, add_5_1);
        display_ASCIIstring_8x16(6, 38, add_5_2);
        display_ASCIIstring_8x16(6, 48, add_4_1);
        display_ASCIIstring_8x16(6, 58, add_4_2);
        display_ASCIIstring_8x16(6, 68, add_3_1);
        display_ASCIIstring_8x16(6, 78, add_3_2);
        display_ASCIIstring_8x16(6, 88, add_2_1);
        display_ASCIIstring_8x16(6, 98, add_2_2);
        display_ASCIIstring_8x16(6, 108, add_1_1);
        display_ASCIIstring_8x16(6, 118, add_1_2);
    }
    break;
    case 6:
    {
        display_ASCIIstring_8x16(1, 96, mima0);
        display_ASCIIstring_8x16(1, 104, mima1);
        display_ASCIIstring_8x16(1, 112, mima2);
        display_ASCIIstring_8x16(1, 120, mima3);
        display_ASCIIstring_8x16(6, 8, add_6_1);
        display_ASCIIstring_8x16(6, 18, add_6_2);
        display_ASCIIstring_8x16_fanxian(6, 28, add_5_1);
        display_ASCIIstring_8x16(6, 38, add_5_2);
        display_ASCIIstring_8x16(6, 48, add_4_1);
        display_ASCIIstring_8x16(6, 58, add_4_2);
        display_ASCIIstring_8x16(6, 68, add_3_1);
        display_ASCIIstring_8x16(6, 78, add_3_2);
        display_ASCIIstring_8x16(6, 88, add_2_1);
        display_ASCIIstring_8x16(6, 98, add_2_2);
        display_ASCIIstring_8x16(6, 108, add_1_1);
        display_ASCIIstring_8x16(6, 118, add_1_2);
    }
    break;
    case 7:
    {
        display_ASCIIstring_8x16(1, 96, mima0);
        display_ASCIIstring_8x16(1, 104, mima1);
        display_ASCIIstring_8x16(1, 112, mima2);
        display_ASCIIstring_8x16(1, 120, mima3);
        display_ASCIIstring_8x16(6, 8, add_6_1);
        display_ASCIIstring_8x16(6, 18, add_6_2);
        display_ASCIIstring_8x16(6, 28, add_5_1);
        display_ASCIIstring_8x16_fanxian(6, 38, add_5_2);
        display_ASCIIstring_8x16(6, 48, add_4_1);
        display_ASCIIstring_8x16(6, 58, add_4_2);
        display_ASCIIstring_8x16(6, 68, add_3_1);
        display_ASCIIstring_8x16(6, 78, add_3_2);
        display_ASCIIstring_8x16(6, 88, add_2_1);
        display_ASCIIstring_8x16(6, 98, add_2_2);
        display_ASCIIstring_8x16(6, 108, add_1_1);
        display_ASCIIstring_8x16(6, 118, add_1_2);
    }
    break;
    case 8:
    {
        display_ASCIIstring_8x16(1, 96, mima0);
        display_ASCIIstring_8x16(1, 104, mima1);
        display_ASCIIstring_8x16(1, 112, mima2);
        display_ASCIIstring_8x16(1, 120, mima3);
        display_ASCIIstring_8x16(6, 8, add_6_1);
        display_ASCIIstring_8x16(6, 18, add_6_2);
        display_ASCIIstring_8x16(6, 28, add_5_1);
        display_ASCIIstring_8x16(6, 38, add_5_2);
        display_ASCIIstring_8x16_fanxian(6, 48, add_4_1);
        display_ASCIIstring_8x16(6, 58, add_4_2);
        display_ASCIIstring_8x16(6, 68, add_3_1);
        display_ASCIIstring_8x16(6, 78, add_3_2);
        display_ASCIIstring_8x16(6, 88, add_2_1);
        display_ASCIIstring_8x16(6, 98, add_2_2);
        display_ASCIIstring_8x16(6, 108, add_1_1);
        display_ASCIIstring_8x16(6, 118, add_1_2);
    }
    break;
    case 9:
    {
        display_ASCIIstring_8x16(1, 96, mima0);
        display_ASCIIstring_8x16(1, 104, mima1);
        display_ASCIIstring_8x16(1, 112, mima2);
        display_ASCIIstring_8x16(1, 120, mima3);
        display_ASCIIstring_8x16(6, 8, add_6_1);
        display_ASCIIstring_8x16(6, 18, add_6_2);
        display_ASCIIstring_8x16(6, 28, add_5_1);
        display_ASCIIstring_8x16(6, 38, add_5_2);
        display_ASCIIstring_8x16(6, 48, add_4_1);
        display_ASCIIstring_8x16_fanxian(6, 58, add_4_2);
        display_ASCIIstring_8x16(6, 68, add_3_1);
        display_ASCIIstring_8x16(6, 78, add_3_2);
        display_ASCIIstring_8x16(6, 88, add_2_1);
        display_ASCIIstring_8x16(6, 98, add_2_2);
        display_ASCIIstring_8x16(6, 108, add_1_1);
        display_ASCIIstring_8x16(6, 118, add_1_2);
    }
    break;
    case 10:
    {
        display_ASCIIstring_8x16(1, 96, mima0);
        display_ASCIIstring_8x16(1, 104, mima1);
        display_ASCIIstring_8x16(1, 112, mima2);
        display_ASCIIstring_8x16(1, 120, mima3);
        display_ASCIIstring_8x16(6, 8, add_6_1);
        display_ASCIIstring_8x16(6, 18, add_6_2);
        display_ASCIIstring_8x16(6, 28, add_5_1);
        display_ASCIIstring_8x16(6, 38, add_5_2);
        display_ASCIIstring_8x16(6, 48, add_4_1);
        display_ASCIIstring_8x16(6, 58, add_4_2);
        display_ASCIIstring_8x16_fanxian(6, 68, add_3_1);
        display_ASCIIstring_8x16(6, 78, add_3_2);
        display_ASCIIstring_8x16(6, 88, add_2_1);
        display_ASCIIstring_8x16(6, 98, add_2_2);
        display_ASCIIstring_8x16(6, 108, add_1_1);
        display_ASCIIstring_8x16(6, 118, add_1_2);
    }
    break;
    case 11:
    {
        display_ASCIIstring_8x16(1, 96, mima0);
        display_ASCIIstring_8x16(1, 104, mima1);
        display_ASCIIstring_8x16(1, 112, mima2);
        display_ASCIIstring_8x16(1, 120, mima3);
        display_ASCIIstring_8x16(6, 8, add_6_1);
        display_ASCIIstring_8x16(6, 18, add_6_2);
        display_ASCIIstring_8x16(6, 28, add_5_1);
        display_ASCIIstring_8x16(6, 38, add_5_2);
        display_ASCIIstring_8x16(6, 48, add_4_1);
        display_ASCIIstring_8x16(6, 58, add_4_2);
        display_ASCIIstring_8x16(6, 68, add_3_1);
        display_ASCIIstring_8x16_fanxian(6, 78, add_3_2);
        display_ASCIIstring_8x16(6, 88, add_2_1);
        display_ASCIIstring_8x16(6, 98, add_2_2);
        display_ASCIIstring_8x16(6, 108, add_1_1);
        display_ASCIIstring_8x16(6, 118, add_1_2);
    }
    break;
    case 12:
    {
        display_ASCIIstring_8x16(1, 96, mima0);
        display_ASCIIstring_8x16(1, 104, mima1);
        display_ASCIIstring_8x16(1, 112, mima2);
        display_ASCIIstring_8x16(1, 120, mima3);
        display_ASCIIstring_8x16(6, 8, add_6_1);
        display_ASCIIstring_8x16(6, 18, add_6_2);
        display_ASCIIstring_8x16(6, 28, add_5_1);
        display_ASCIIstring_8x16(6, 38, add_5_2);
        display_ASCIIstring_8x16(6, 48, add_4_1);
        display_ASCIIstring_8x16(6, 58, add_4_2);
        display_ASCIIstring_8x16(6, 68, add_3_1);
        display_ASCIIstring_8x16(6, 78, add_3_2);
        display_ASCIIstring_8x16_fanxian(6, 88, add_2_1);
        display_ASCIIstring_8x16(6, 98, add_2_2);
        display_ASCIIstring_8x16(6, 108, add_1_1);
        display_ASCIIstring_8x16(6, 118, add_1_2);
    }
    break;
    case 13:
    {
        display_ASCIIstring_8x16(1, 96, mima0);
        display_ASCIIstring_8x16(1, 104, mima1);
        display_ASCIIstring_8x16(1, 112, mima2);
        display_ASCIIstring_8x16(1, 120, mima3);
        display_ASCIIstring_8x16(6, 8, add_6_1);
        display_ASCIIstring_8x16(6, 18, add_6_2);
        display_ASCIIstring_8x16(6, 28, add_5_1);
        display_ASCIIstring_8x16(6, 38, add_5_2);
        display_ASCIIstring_8x16(6, 48, add_4_1);
        display_ASCIIstring_8x16(6, 58, add_4_2);
        display_ASCIIstring_8x16(6, 68, add_3_1);
        display_ASCIIstring_8x16(6, 78, add_3_2);
        display_ASCIIstring_8x16(6, 88, add_2_1);
        display_ASCIIstring_8x16_fanxian(6, 98, add_2_2);
        display_ASCIIstring_8x16(6, 108, add_1_1);
        display_ASCIIstring_8x16(6, 118, add_1_2);
    }
    break;
    case 14:
    {
        display_ASCIIstring_8x16(1, 96, mima0);
        display_ASCIIstring_8x16(1, 104, mima1);
        display_ASCIIstring_8x16(1, 112, mima2);
        display_ASCIIstring_8x16(1, 120, mima3);
        display_ASCIIstring_8x16(6, 8, add_6_1);
        display_ASCIIstring_8x16(6, 18, add_6_2);
        display_ASCIIstring_8x16(6, 28, add_5_1);
        display_ASCIIstring_8x16(6, 38, add_5_2);
        display_ASCIIstring_8x16(6, 48, add_4_1);
        display_ASCIIstring_8x16(6, 58, add_4_2);
        display_ASCIIstring_8x16(6, 68, add_3_1);
        display_ASCIIstring_8x16(6, 78, add_3_2);
        display_ASCIIstring_8x16(6, 88, add_2_1);
        display_ASCIIstring_8x16(6, 98, add_2_2);
        display_ASCIIstring_8x16_fanxian(6, 108, add_1_1);
        display_ASCIIstring_8x16(6, 118, add_1_2);
    }
    break;
    case 15:
    {
        display_ASCIIstring_8x16(1, 96, mima0);
        display_ASCIIstring_8x16(1, 104, mima1);
        display_ASCIIstring_8x16(1, 112, mima2);
        display_ASCIIstring_8x16(1, 120, mima3);
        display_ASCIIstring_8x16(6, 8, add_6_1);
        display_ASCIIstring_8x16(6, 18, add_6_2);
        display_ASCIIstring_8x16(6, 28, add_5_1);
        display_ASCIIstring_8x16(6, 38, add_5_2);
        display_ASCIIstring_8x16(6, 48, add_4_1);
        display_ASCIIstring_8x16(6, 58, add_4_2);
        display_ASCIIstring_8x16(6, 68, add_3_1);
        display_ASCIIstring_8x16(6, 78, add_3_2);
        display_ASCIIstring_8x16(6, 88, add_2_1);
        display_ASCIIstring_8x16(6, 98, add_2_2);
        display_ASCIIstring_8x16(6, 108, add_1_1);
        display_ASCIIstring_8x16_fanxian(6, 118, add_1_2);
    }
    break;
    }

    if (key == KEY_UP_PRES)
    {
        if (a < 15)
            a++;
    }
    else if (key == KEY_DOWN_PRES)
    {

        a--;
        if (a < 0)
        {
            F_Y = 5;
            a = 0;
            clear_screen();
        }
    }
    else if (key == KEY_AFFIRM_PRES)
    {
        if (a < 15)
            a++;
        if (a == 4)
        {
            for (int i = 0; i < 4; i++) // �������趨��ɲ�ȷ���趨�������ֹϹ����
            {
                mima_set[i] = mima_set_compare[i];
            }
        }
        if (a > 3)
        {
            judge();
        }
    }
    else if (key == KEY_LEFT_PRES)
    {
        clear_screen();
        switch (a)
        {
        case 0:
        {
            if (mima_set_compare[0] < 9)
                mima_set_compare[0]++;
        }
        break;
        case 1:
        {
            if (mima_set_compare[1] < 9)
                mima_set_compare[1]++;
        }
        break;
        case 2:
        {
            if (mima_set_compare[2] < 9)
                mima_set_compare[2]++;
        }
        break;
        case 3:
        {
            if (mima_set_compare[3] < 9)
                mima_set_compare[3]++;
        }
        break;
        case 4:
        {
            if (self_addr_code[5] >> 4 < 9)
                self_addr_code[5] = self_addr_code[5] + 16;
        }
        break;
        case 5:
        {
            if ((self_addr_code[5] & 0x0F) < 9)
                self_addr_code[5] = self_addr_code[5] + 1;
        }
        break;
        case 6:
        {
            if (self_addr_code[4] >> 4 < 9)
                self_addr_code[4] = self_addr_code[4] + 16;
        }
        break;
        case 7:
        {
            if ((self_addr_code[4] & 0x0F) < 9)
                self_addr_code[4] = self_addr_code[4] + 1;
        }
        break;
        case 8:
        {
            if (self_addr_code[3] >> 4 < 9)
                self_addr_code[3] = self_addr_code[3] + 16;
        }
        break;
        case 9:
        {
            if ((self_addr_code[3] & 0x0F) < 9)
                self_addr_code[3] = self_addr_code[3] + 1;
        }
        break;
        case 10:
        {
            if (self_addr_code[2] >> 4 < 9)
                self_addr_code[2] = self_addr_code[2] + 16;
        }
        break;
        case 11:
        {
            if ((self_addr_code[2] & 0x0F) < 9)
                self_addr_code[2] = self_addr_code[2] + 1;
        }
        break;
        case 12:
        {
            if (self_addr_code[1] >> 4 < 9)
                self_addr_code[1] = self_addr_code[1] + 16;
        }
        break;
        case 13:
        {
            if ((self_addr_code[1] & 0x0F) < 9)
                self_addr_code[1] = self_addr_code[1] + 1;
        }
        break;
        case 14:
        {
            if (self_addr_code[0] >> 4 < 9)
                self_addr_code[0] = self_addr_code[0] + 16;
        }
        break;
        case 15:
        {
            if ((self_addr_code[0] & 0x0F) < 9)
                self_addr_code[0] = self_addr_code[0] + 1;
        }
        break;
        }
    }
    else if (key == KEY_RIGHRT_PRES)
    {
        clear_screen();
        switch (a)
        {
        case 0:
        {
            if (mima_set_compare[0] > 0)
                mima_set_compare[0]--;
        }
        break;
        case 1:
        {
            if (mima_set_compare[1] > 0)
                mima_set_compare[1]--;
        }
        break;
        case 2:
        {
            if (mima_set_compare[2] > 0)
                mima_set_compare[2]--;
        }
        break;
        case 3:
        {
            if (mima_set_compare[3] > 0)
                mima_set_compare[3]--;
        }
        break;
        case 4:
        {
            if (self_addr_code[5] >> 4 > 0)
                self_addr_code[5] = self_addr_code[5] - 16;
        }
        break;
        case 5:
        {
            if ((self_addr_code[5] & 0x0F) > 0)
                self_addr_code[5] = self_addr_code[5] - 1;
        }
        break;
        case 6:
        {
            if (self_addr_code[4] >> 4 > 0)
                self_addr_code[4] = self_addr_code[4] - 16;
        }
        break;
        case 7:
        {
            if ((self_addr_code[4] & 0x0F) > 0)
                self_addr_code[4] = self_addr_code[4] - 1;
        }
        break;
        case 8:
        {
            if (self_addr_code[3] >> 4 > 0)
                self_addr_code[3] = self_addr_code[3] - 16;
        }
        break;
        case 9:
        {
            if ((self_addr_code[3] & 0x0F) > 0)
                self_addr_code[3] = self_addr_code[3] - 1;
        }
        break;
        case 10:
        {
            if (self_addr_code[2] >> 4 > 0)
                self_addr_code[2] = self_addr_code[2] - 16;
        }
        break;
        case 11:
        {
            if ((self_addr_code[2] & 0x0F) > 0)
                self_addr_code[2] = self_addr_code[2] - 1;
        }
        break;
        case 12:
        {
            if (self_addr_code[1] >> 4 > 0)
                self_addr_code[1] = self_addr_code[1] - 16;
        }
        break;
        case 13:
        {
            if ((self_addr_code[1] & 0x0F) > 0)
                self_addr_code[1] = self_addr_code[1] - 1;
        }
        break;
        case 14:
        {
            if (self_addr_code[0] >> 4 > 0)
                self_addr_code[0] = self_addr_code[0] - 16;
        }
        break;
        case 15:
        {
            if ((self_addr_code[0] & 0x0F) > 0)
                self_addr_code[0] = self_addr_code[0] - 1;
        }
        break;
        }
    }
}
void judge() // ��λ�Ķ��ж�
{
    if (TH_LCurtemp != TH_LCur ||
        ctrlwordtemp[3] != ctrlword[3] ||
        Vol_gtemp != Vol_g ||
        Vol_qtemp != Vol_q ||
        D_SY_yanshitemp != D_SY_yanshi ||
        D_GY_yanshitemp != D_GY_yanshi ||
        D_QY_yanshitemp != D_QY_yanshi ||
        D3_Curtemp != D3_Cur ||
        D_Curtemp != D_Cur ||
        TH_Long_Curtemp != TH_Long_Cur ||
        D2_Curtemp != D2_Cur ||
        TH_DLtemp != TH_DL ||
        baudtemp != baud ||
        Type_Curtemp != Type_Cur ||
        tim_y3temp != tim_y3 ||
        tim_m3temp != tim_m3 ||
        tim_d3temp != tim_d3 ||
        tim_h3temp != tim_h3 ||
        tim_f3temp != tim_f3 ||
        tim_s3temp != tim_s3 ||
        TH_TEM_UPtemp != TH_TEM_UP ||
        TH_TEM_DOWNtemp != TH_TEM_DOWN ||
        mima_settemp[0] != mima_set[0] ||
        mima_settemp[1] != mima_set[1] ||
        mima_settemp[2] != mima_set[2] ||
        mima_settemp[3] != mima_set[3] ||
        self_addr_codetemp[0] != self_addr_code[0] ||
        self_addr_codetemp[1] != self_addr_code[1] ||
        self_addr_codetemp[2] != self_addr_code[2] ||
        self_addr_codetemp[3] != self_addr_code[3] ||
        self_addr_codetemp[4] != self_addr_code[4] ||
        self_addr_codetemp[5] != self_addr_code[5] ||
        ctrlwordtemp[0] != ctrlword[0] ||
        ctrlwordtemp[1] != ctrlword[1] ||
        ctrlwordtemp[2] != ctrlword[2] ||
        F_TB_triptemp != F_TB_trip ||
        F_Special_wavetemp != F_Special_wave ||
        F_iptemp != F_ip ||
        F_ip_3temp != F_ip_3 ||
        jiaozhuntemp != jiaozhun ||
        shangdiantemp != shangdian ||
        LD_hezhatemp != LD_hezha ||
        DY_hezhatemp != DY_hezha ||
        DL_hezhatemp != DL_hezha ||
        wendutemp != wendu ||
        F_TXtemp != F_TX ||
        F_trip_sytemp != F_trip_sy)
    {

        updata_c();
        USART_LCD_Transmit(57, 1); // ��������

        // ��������
    }
}
void updata_c() // ���иĶ����µ�λ����
{
    TH_LCurtemp = TH_LCur;
    ctrlwordtemp[3] = ctrlword[3];             // ������4
    Vol_gtemp = Vol_g;                         // ��ѹ��λ
    Vol_qtemp = Vol_q;                         // Ƿѹ��λ
    D_SY_yanshitemp = D_SY_yanshi;             // ʧѹ��ʱ
    D_GY_yanshitemp = D_GY_yanshi;             // ��ѹ��ʱ
    D_QY_yanshitemp = D_QY_yanshi;             // Ƿѹ��ʱ
    D3_Curtemp = D3_Cur;                       // ˲ʱ��λ
    D_Curtemp = D_Cur;                         // ������λ
    TH_Long_Curtemp = TH_Long_Cur;             // ����ʱ��
    D2_Curtemp = D2_Cur;                       // ���ӵ�λ
    TH_DLtemp = TH_DL;                         // ����ʱ��
    baudtemp = baud;                           // ͨ������
    Type_Curtemp = Type_Cur;                   // �Ǽ�����
    tim_y3temp = tim_y3;                       // ���� ��
    tim_m3temp = tim_m3;                       // ���� ��
    tim_d3temp = tim_d3;                       // ���� ��
    tim_h3temp = tim_h3;                       // ʱ�� ʱ
    tim_f3temp = tim_f3;                       // ʱ�� ��
    tim_s3temp = tim_s3;                       // ʱ�� ��
    TH_TEM_UPtemp = TH_TEM_UP;                 // ���·�բ
    TH_TEM_DOWNtemp = TH_TEM_DOWN;             // ���º�բ
    mima_settemp[0] = mima_set[0];             // ����
    mima_settemp[1] = mima_set[1];             // ����
    mima_settemp[2] = mima_set[2];             // ����
    mima_settemp[3] = mima_set[3];             // ����
    self_addr_codetemp[0] = self_addr_code[0]; // ͨ�ŵ�ַ�ֽ�0
    self_addr_codetemp[1] = self_addr_code[1]; // ͨ�ŵ�ַ�ֽ�1
    self_addr_codetemp[2] = self_addr_code[2]; // ͨ�ŵ�ַ�ֽ�2
    self_addr_codetemp[3] = self_addr_code[3]; // ͨ�ŵ�ַ�ֽ�3
    self_addr_codetemp[4] = self_addr_code[4]; // ͨ�ŵ�ַ�ֽ�4
    self_addr_codetemp[5] = self_addr_code[5]; // ͨ�ŵ�ַ�ֽ�5
    ctrlwordtemp[0] = ctrlword[0];
    ctrlwordtemp[1] = ctrlword[1];
    ctrlwordtemp[2] = ctrlword[2];
    F_TB_triptemp = F_TB_trip;
    F_Special_wavetemp = F_Special_wave;
    F_iptemp = F_ip;
    F_ip_3temp = F_ip_3;
    jiaozhuntemp = jiaozhun;
    shangdiantemp = shangdian;
    LD_hezhatemp = LD_hezha;
    DY_hezhatemp = DY_hezha;
    DL_hezhatemp = DL_hezha;
    wendutemp = wendu;
    F_TXtemp = F_TX;
    F_trip_sytemp = F_trip_sy;
}
void USART_LCD_Transmit(unsigned char len, unsigned char ch) // ���ͺ��� ����ͨ���� �ֱ�Ϊʵʱ��ʾ���ݺ͵�λ��0Ϊʵʱ��ʾ���ݣ�1Ϊ��λ��2©�磬3У׼���
{
    unsigned char i, cs_temp, array_tmp[len];
    switch (ch)
    {

    case 1:
        DI3 = 0x90;
        DI2 = 0x01;
        DI0 = 0x41;
        array_tmp[0] = ctrlword[3];
        array_tmp[1] = Vol_g;
        array_tmp[2] = Vol_q;
        array_tmp[3] = D_SY_yanshi;
        array_tmp[4] = D_GY_yanshi;
        array_tmp[5] = D_QY_yanshi;
        array_tmp[6] = D3_Cur;
        array_tmp[7] = D_Cur;
        array_tmp[8] = TH_Long_Cur;
        array_tmp[9] = D2_Cur;
        array_tmp[10] = TH_DL;
        array_tmp[11] = (baud >> 8) & 0xFF;
        array_tmp[12] = baud & 0xFF;
        array_tmp[13] = (Type_Cur >> 8) & 0xFF;
        array_tmp[14] = Type_Cur & 0xFF;
        array_tmp[15] = (tim_y3 >> 8) & 0xFF;
        array_tmp[16] = tim_y3 & 0xFF;
        array_tmp[17] = (tim_m3 >> 8) & 0xFF;
        array_tmp[18] = tim_m3 & 0xFF;
        array_tmp[19] = (tim_d3 >> 8) & 0xFF;
        array_tmp[20] = tim_d3 & 0xFF;
        array_tmp[21] = (tim_h3 >> 8) & 0xFF;
        array_tmp[22] = tim_h3 & 0xFF;
        array_tmp[23] = (tim_f3 >> 8) & 0xFF;
        array_tmp[24] = tim_f3 & 0xFF;
        array_tmp[25] = (tim_s3 >> 8) & 0xFF;
        array_tmp[26] = tim_s3 & 0xFF;

        array_tmp[27] = (TH_TEM_UP >> 8) & 0xFF;
        array_tmp[28] = TH_TEM_UP & 0xFF;
        array_tmp[29] = (TH_TEM_DOWN >> 8) & 0xFF;
        array_tmp[30] = TH_TEM_DOWN & 0xFF;
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
        array_tmp[42] = ctrlword[1];
        array_tmp[43] = ctrlword[2];
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

        Write_or_Readresponse(0x10, len, array_tmp);
        break;

    case 2: // ©���բ��բ
        DI3 = 0x32;
        DI2 = 0x01;
        DI0 = 0x03;
        switch (F_LEAK_OPEN_CLOSE) // F_LEAK_OPEN_CLOSE  1��©��2�Ƿ�բ3�Ǻ�բ          F_open==1�Ǹ��·�բ,F_open==0���ֶ���բ
        {
        case 1:
            array_tmp[0] = 1;
            array_tmp[1] = 0;
            array_tmp[2] = 0;
            array_tmp[3] = 0;
            array_tmp[4] = 0;
            array_tmp[5] = 0;
            array_tmp[6] = 0;
            break;
        case 2:
            if (F_open == 1)
            {
                array_tmp[0] = 0;
                array_tmp[1] = 0;
                array_tmp[2] = 0;
                array_tmp[3] = 1;
                array_tmp[4] = tem;
                array_tmp[5] = max_value;
                array_tmp[6] = 0;
            } // ��û�ģ��¶ȴ����ǣ�����д����warray_tmp[4]=2;array_tmp[5]=122
            else if (F_open == 0)
            {
                array_tmp[0] = 0;
                array_tmp[1] = 1;
                array_tmp[2] = 0;
                array_tmp[3] = 0;
                array_tmp[4] = 0;
                array_tmp[5] = 0;
                array_tmp[6] = 0;
            }
            break; // �ֶ���բ
        case 3:
            array_tmp[0] = 0;
            array_tmp[1] = 0;
            array_tmp[2] = 1;
            array_tmp[3] = 0;
            array_tmp[4] = 1;
            array_tmp[5] = 0;
            array_tmp[6] = 0;
            break; // �ֶ���բ
        case 4:
            array_tmp[0] = 0;
            array_tmp[1] = 0;
            array_tmp[2] = 1;
            array_tmp[3] = 0;
            array_tmp[4] = 0;
            array_tmp[5] = 0;
            array_tmp[6] = 1;
            break; // ���º�բ
        }
        Write_or_Readresponse(0x10, len, array_tmp);
        break;
    case 3: // У׼���
        DI3 = 0x04;
        DI2 = 0x10;
        DI0 = 0x10;
        array_tmp[0] = Cal_state;
        array_tmp[1] = 1;
        Write_or_Readresponse(0x10, len, array_tmp);
        break;
    case 4: // ����ȷ��
        DI3 = 0x05;
        DI2 = 0x10;
        DI0 = 0x01;
        array_tmp[0] = 1;
        F_GUZHANG = 1; // ʵ���˳�����
        Write_or_Readresponse(0x10, len, array_tmp);
        break;

    case 5: // ��ʼ������
        DI3 = 0x06;
        DI2 = 0x10;
        DI0 = 0x01;
        array_tmp[0] = 1;

        Write_or_Readresponse(0x10, len, array_tmp);
        break;

    case 6: // ����г��
        DI3 = 0x08;
        DI2 = 0x10;
        DI0 = 0x01;
        array_tmp[0] = 1;

        Write_or_Readresponse(0x10, len, array_tmp);
        break;

    case 7: // ������ϼ�¼
        DI3 = 0x09;
        DI2 = 0x10;
        DI0 = 0xF01;
        array_tmp[0] = 1;

        Write_or_Readresponse(0x10, len, array_tmp);
        break;

    default:
        break;
    }
}
void UART_LCD_process(void) // ���ڽ��պ�������λ��Ϣ��ʵʱ����
{

    // data_array0��1��2��3Ԫ��Ϊʶ���룬��4��ʼ������
    if (Lcd_data_array[read_ptr][0] == 0X90)
    {
        ctrlword[3] = Lcd_data_array[read_ptr][4];                                          // ������4
        Vol_g = Lcd_data_array[read_ptr][5];                                                // ��ѹ��λ
        Vol_q = Lcd_data_array[read_ptr][6];                                                // Ƿѹ��λ
        D_SY_yanshi = Lcd_data_array[read_ptr][7];                                          // ʧѹ��ʱ
        D_GY_yanshi = Lcd_data_array[read_ptr][8];                                          // ��ѹ��ʱ
        D_QY_yanshi = Lcd_data_array[read_ptr][9];                                          // Ƿѹ��ʱ
        D3_Cur = Lcd_data_array[read_ptr][10];                                              // ˲ʱ��λ
        D_Cur = Lcd_data_array[read_ptr][11];                                               // ������λ
        TH_Long_Cur = Lcd_data_array[read_ptr][12];                                         // ����ʱ��
        D2_Cur = Lcd_data_array[read_ptr][13];                                              // ���ӵ�λ
        TH_DL = Lcd_data_array[read_ptr][14];                                               // ����ʱ��
        baud = (Lcd_data_array[read_ptr][15] << 8) + (Lcd_data_array[read_ptr][16]);        // ͨ������
        Type_Cur = (Lcd_data_array[read_ptr][17] << 8) + (Lcd_data_array[read_ptr][18]);    // �Ǽ�����
        tim_y3 = (Lcd_data_array[read_ptr][19] << 8) + (Lcd_data_array[read_ptr][20]);      // ���� ��
        tim_m3 = (Lcd_data_array[read_ptr][21] << 8) + (Lcd_data_array[read_ptr][22]);      // ���� ��
        tim_d3 = (Lcd_data_array[read_ptr][23] << 8) + (Lcd_data_array[read_ptr][24]);      // ���� ��
        tim_h3 = (Lcd_data_array[read_ptr][25] << 8) + (Lcd_data_array[read_ptr][26]);      // ʱ�� ʱ
        tim_f3 = (Lcd_data_array[read_ptr][27] << 8) + (Lcd_data_array[read_ptr][28]);      // ʱ�� ��
        tim_s3 = (Lcd_data_array[read_ptr][29] << 8) + (Lcd_data_array[read_ptr][30]);      // ʱ�� ��
        TH_TEM_UP = (Lcd_data_array[read_ptr][31] << 8) + (Lcd_data_array[read_ptr][32]);   // ���·�բ
        TH_TEM_DOWN = (Lcd_data_array[read_ptr][33] << 8) + (Lcd_data_array[read_ptr][34]); // ���º�բ
        mima_set[0] = Lcd_data_array[read_ptr][35];                                         // ����
        mima_set[1] = Lcd_data_array[read_ptr][36];                                         // ����
        mima_set[2] = Lcd_data_array[read_ptr][37];                                         // ����
        mima_set[3] = Lcd_data_array[read_ptr][38];                                         // ����
        self_addr_code[0] = Lcd_data_array[read_ptr][39];                                   // ͨ�ŵ�ַ�ֽ�0
        self_addr_code[1] = Lcd_data_array[read_ptr][40];                                   // ͨ�ŵ�ַ�ֽ�1
        self_addr_code[2] = Lcd_data_array[read_ptr][41];                                   // ͨ�ŵ�ַ�ֽ�2
        self_addr_code[3] = Lcd_data_array[read_ptr][42];                                   // ͨ�ŵ�ַ�ֽ�3
        self_addr_code[4] = Lcd_data_array[read_ptr][43];                                   // ͨ�ŵ�ַ�ֽ�4
        self_addr_code[5] = Lcd_data_array[read_ptr][44];                                   // ͨ�ŵ�ַ�ֽ�5
        ctrlword[0] = Lcd_data_array[read_ptr][45];
        ctrlword[1] = Lcd_data_array[read_ptr][46];
        ctrlword[2] = Lcd_data_array[read_ptr][47];
        F_TB_trip = Lcd_data_array[read_ptr][48];
        F_Special_wave = Lcd_data_array[read_ptr][49];
        F_ip = Lcd_data_array[read_ptr][50];
        F_ip_3 = Lcd_data_array[read_ptr][51];
        jiaozhun = Lcd_data_array[read_ptr][52];
        shangdian = Lcd_data_array[read_ptr][53];
        LD_hezha = Lcd_data_array[read_ptr][54];
        DY_hezha = Lcd_data_array[read_ptr][55];
        DL_hezha = Lcd_data_array[read_ptr][56];
        wendu = Lcd_data_array[read_ptr][57];
        F_TX = Lcd_data_array[read_ptr][58];
        TH_LCur = Lcd_data_array[read_ptr][59];
        F_trip_sy = Lcd_data_array[read_ptr][60];
        // ctrlword1_analyze();
        ctrlword2_analyze();
        ctrlword3_analyze();
        ctrlword4_analyze();
        RTC_Set_Time(tim_h3, tim_f3, tim_s3);
        RTC_Set_Date(tim_y3, tim_m3, tim_d3);
        updata_c();
    }
    else if (Lcd_data_array[read_ptr][0] == 0X02)
    {
        HT7038_buf11[1] = ((Lcd_data_array[read_ptr][4] << 8) & 0xFF00) | Lcd_data_array[read_ptr][5];                                                        // av
        HT7038_buf11[2] = ((Lcd_data_array[read_ptr][6] << 8) & 0xFF00) | Lcd_data_array[read_ptr][7];                                                        // bv
        HT7038_buf11[3] = ((Lcd_data_array[read_ptr][8] << 8) & 0xFF00) | Lcd_data_array[read_ptr][9];                                                        // cv
        HT7038_buf11[4] = ((Lcd_data_array[read_ptr][10] << 8) & 0xFF00) | Lcd_data_array[read_ptr][11];                                                      // ai
        HT7038_buf11[5] = ((Lcd_data_array[read_ptr][12] << 8) & 0xFF00) | Lcd_data_array[read_ptr][13];                                                      // bi
        HT7038_buf11[6] = ((Lcd_data_array[read_ptr][14] << 8) & 0xFF00) | Lcd_data_array[read_ptr][15];                                                      // ci
        Leak_Cur_disp = ((Lcd_data_array[read_ptr][16] << 8) & 0xFF00) | Lcd_data_array[read_ptr][17];                                                        // leakcur
        HT7038_buf11[15] = ((Lcd_data_array[read_ptr][18] << 16) & 0xFF0000) | ((Lcd_data_array[read_ptr][19] << 8) & 0xFF00) | Lcd_data_array[read_ptr][20]; // an;�й�����
        HT7038_buf11[16] = ((Lcd_data_array[read_ptr][21] << 16) & 0xFF0000) | ((Lcd_data_array[read_ptr][22] << 8) & 0xFF00) | Lcd_data_array[read_ptr][23]; // bn;
        HT7038_buf11[17] = ((Lcd_data_array[read_ptr][24] << 16) & 0xFF0000) | ((Lcd_data_array[read_ptr][25] << 8) & 0xFF00) | Lcd_data_array[read_ptr][26]; // cn;
        HT7038_buf11[18] = ((Lcd_data_array[read_ptr][27] << 16) & 0xFF0000) | ((Lcd_data_array[read_ptr][28] << 8) & 0xFF00) | Lcd_data_array[read_ptr][29]; // alln;
        HT7038_buf11[7] = ((Lcd_data_array[read_ptr][30] << 8) & 0xFF00) | Lcd_data_array[read_ptr][31];                                                      // a�й�;
        HT7038_buf11[8] = ((Lcd_data_array[read_ptr][32] << 8) & 0xFF00) | Lcd_data_array[read_ptr][33];                                                      // b�й�;
        HT7038_buf11[9] = ((Lcd_data_array[read_ptr][34] << 8) & 0xFF00) | Lcd_data_array[read_ptr][35];                                                      // c�й�;
        HT7038_buf11[10] = ((Lcd_data_array[read_ptr][36] << 8) & 0xFF00) | Lcd_data_array[read_ptr][37];                                                     // all�й�����
        HT7038_buf11[11] = ((Lcd_data_array[read_ptr][38] << 8) & 0xFF00) | Lcd_data_array[read_ptr][39];                                                     // a��������;
        HT7038_buf11[12] = ((Lcd_data_array[read_ptr][40] << 8) & 0xFF00) | Lcd_data_array[read_ptr][41];                                                     // b��������;
        HT7038_buf11[13] = ((Lcd_data_array[read_ptr][42] << 8) & 0xFF00) | Lcd_data_array[read_ptr][43];                                                     // c��������;
        HT7038_buf11[14] = ((Lcd_data_array[read_ptr][44] << 8) & 0xFF00) | Lcd_data_array[read_ptr][45];                                                     // all��������;
        Num_tripall = ((Lcd_data_array[read_ptr][62] << 8) & 0xFF00) | Lcd_data_array[read_ptr][63];
        Num_clearall = ((Lcd_data_array[read_ptr][64] << 8) & 0xFF00) | Lcd_data_array[read_ptr][65];
        Num_triplock = ((Lcd_data_array[read_ptr][66] << 8) & 0xFF00) | Lcd_data_array[read_ptr][67];
        Num_tripleak = ((Lcd_data_array[read_ptr][68] << 8) & 0xFF00) | Lcd_data_array[read_ptr][69];
        Num_tripcur = ((Lcd_data_array[read_ptr][70] << 8) & 0xFF00) | Lcd_data_array[read_ptr][71];
        Num_tripvol = ((Lcd_data_array[read_ptr][72] << 8) & 0xFF00) | Lcd_data_array[read_ptr][73];
        Num_triphand = ((Lcd_data_array[read_ptr][74] << 8) & 0xFF00) | Lcd_data_array[read_ptr][75];
        Num_triptest = ((Lcd_data_array[read_ptr][76] << 8) & 0xFF00) | Lcd_data_array[read_ptr][77];
        Num_tripdelay = ((Lcd_data_array[read_ptr][78] << 8) & 0xFF00) | Lcd_data_array[read_ptr][79];
        Num_tripinstant = ((Lcd_data_array[read_ptr][80] << 8) & 0xFF00) | Lcd_data_array[read_ptr][81];
        Num_leakover = ((Lcd_data_array[read_ptr][82] << 8) & 0xFF00) | Lcd_data_array[read_ptr][83];
        Num_leakprotect = ((Lcd_data_array[read_ptr][84] << 8) & 0xFF00) | Lcd_data_array[read_ptr][85];
    }
    else if (Lcd_data_array[read_ptr][0] == 0x03) // �ֺ�բ״̬�͹�����ʾ���
    {
        isfenzha = Lcd_data_array[read_ptr][4];
        F_disp_jg = Lcd_data_array[read_ptr][5];
        F_disp_tr = Lcd_data_array[read_ptr][6];
        F_hezha_state = Lcd_data_array[read_ptr][7];
        F_fenzha_state = Lcd_data_array[read_ptr][8];
        F_gz_disp = Lcd_data_array[read_ptr][9];
        gz_disp = ((Lcd_data_array[read_ptr][10] << 8) & 0xFF00) | Lcd_data_array[read_ptr][11];
        F_ch = ((Lcd_data_array[read_ptr][12] << 8) & 0xFF00) | Lcd_data_array[read_ptr][13];
        if (F_gz_disp != 0x0F || F_hezha_state == 1 || F_fenzha_state == 1)
            clear_screen();
        if (F_gz_disp == 0x0F || F_GUZHANG == 1)
        {
            clear_screen();
            F_GUZHANG = 0;
        }
    }
    else if (Lcd_data_array[read_ptr][0] == 0x04) // У׼���
        F_jiaozhuned = Lcd_data_array[read_ptr][4];
    else if (Lcd_data_array[read_ptr][0] == 0x06) // ��ʼ�����
        F_initialization = Lcd_data_array[read_ptr][4];
    else if (Lcd_data_array[read_ptr][0] == 0x07) // ������ѯ
    {
        for (int i = 0; i < 24; i++)
        {
            HT7038_buf11[19 + i] = ((Lcd_data_array[read_ptr][4 + 2 * i] << 8) & 0xFF00) | Lcd_data_array[read_ptr][5 + 2 * i];
        }

        HT7038_buf11[43] = Lcd_data_array[read_ptr][52];                                                                                                      // Ƶ��;
        HT7038_buf11[44] = ((Lcd_data_array[read_ptr][53] << 8) & 0xFF00) | Lcd_data_array[read_ptr][54];                                                     // ��ѹ���಻ƽ��;
        HT7038_buf11[45] = ((Lcd_data_array[read_ptr][55] << 8) & 0xFF00) | Lcd_data_array[read_ptr][56];                                                     // �������಻ƽ��;
        HT7038_buf11[46] = Lcd_data_array[read_ptr][57];                                                                                                      // ����������ָʾ;
        HT7038_buf11[47] = ((Lcd_data_array[read_ptr][58] << 16) & 0xFF0000) | ((Lcd_data_array[read_ptr][59] << 8) & 0xFF00) | Lcd_data_array[read_ptr][60]; // ��ʱ����
    }

    else if (Lcd_data_array[read_ptr][0] == 0x08) // г��ua����
    {
        for (int i = 0; i < 30; i++) // 100��ѹ��г��
        {
            HT7038_buf11[100 + i] = ((Lcd_data_array[read_ptr][4 + 2 * i] << 8) & 0xFF00) | Lcd_data_array[read_ptr][5 + 2 * i]; // all�޹�����;
        }
        f_f = 2;
    }
    else if (Lcd_data_array[read_ptr][0] == 0x09) // г��ub����
    {
        for (int i = 0; i < 30; i++) // 100��ѹ��г��
        {
            HT7038_buf11[130 + i] = ((Lcd_data_array[read_ptr][4 + 2 * i] << 8) & 0xFF00) | Lcd_data_array[read_ptr][5 + 2 * i]; // all�޹�����;
        }
        f_f = 3;
    }
    else if (Lcd_data_array[read_ptr][0] == 0x0A) // г��uC����
    {
        for (int i = 0; i < 30; i++) // 100��ѹ��г��
        {
            HT7038_buf11[160 + i] = ((Lcd_data_array[read_ptr][4 + 2 * i] << 8) & 0xFF00) | Lcd_data_array[read_ptr][5 + 2 * i]; // all�޹�����;
        }
        f_f = 4;
    }
    else if (Lcd_data_array[read_ptr][0] == 0x0B) // г��IA����
    {
        for (int i = 0; i < 30; i++) // 100��ѹ��г��
        {
            HT7038_buf11[190 + i] = ((Lcd_data_array[read_ptr][4 + 2 * i] << 8) & 0xFF00) | Lcd_data_array[read_ptr][5 + 2 * i]; // all�޹�����;
        }
        f_f = 5;
    }

    else if (Lcd_data_array[read_ptr][0] == 0x0C) // г��IB����
    {
        for (int i = 0; i < 30; i++) // 100��ѹ��г��
        {
            HT7038_buf11[220 + i] = ((Lcd_data_array[read_ptr][4 + 2 * i] << 8) & 0xFF00) | Lcd_data_array[read_ptr][5 + 2 * i]; // all�޹�����;
        }
        f_f = 6;
    }
    else if (Lcd_data_array[read_ptr][0] == 0x0D) // г��IC����
    {
        for (int i = 0; i < 36; i++) // 100��ѹ��г��
        {
            HT7038_buf11[250 + i] = ((Lcd_data_array[read_ptr][4 + 2 * i] << 8) & 0xFF00) | Lcd_data_array[read_ptr][5 + 2 * i]; // all�޹�����;
        }
        f_f = 0;
        clear_screen();
    }
    else if (Lcd_data_array[read_ptr][0] == 0x0E) // ����ǰʮ��
    {
        for (int i = 0; i < 10; ++i)
        {
            int base_index = 4 + (i * 9); // ����ÿ�����ϼ�¼����ʼλ��
            fault_buffer[i].fault_type = Lcd_data_array[read_ptr][base_index];
            fault_buffer[i].fault_sec = Lcd_data_array[read_ptr][base_index + 1];
            fault_buffer[i].fault_min = Lcd_data_array[read_ptr][base_index + 2];
            fault_buffer[i].fault_hour = Lcd_data_array[read_ptr][base_index + 3];
            fault_buffer[i].fault_data = Lcd_data_array[read_ptr][base_index + 4];
            fault_buffer[i].fault_month = Lcd_data_array[read_ptr][base_index + 5];
            fault_buffer[i].fault_year = Lcd_data_array[read_ptr][base_index + 6];
            fault_buffer[i].fault_value = (Lcd_data_array[read_ptr][base_index + 7] << 8) | Lcd_data_array[read_ptr][base_index + 8];
        }
    }

    else if (Lcd_data_array[read_ptr][0] == 0x0F) // ���Ϻ�ʮ��
    {
        for (int i = 0; i < 10; ++i)
        {
            int base_index = 4 + (i * 9); // ����ÿ�����ϼ�¼����ʼλ��
            fault_buffer[10 + i].fault_type = Lcd_data_array[read_ptr][base_index];
            fault_buffer[10 + i].fault_sec = Lcd_data_array[read_ptr][base_index + 1];
            fault_buffer[10 + i].fault_min = Lcd_data_array[read_ptr][base_index + 2];
            fault_buffer[10 + i].fault_hour = Lcd_data_array[read_ptr][base_index + 3];
            fault_buffer[10 + i].fault_data = Lcd_data_array[read_ptr][base_index + 4];
            fault_buffer[10 + i].fault_month = Lcd_data_array[read_ptr][base_index + 5];
            fault_buffer[10 + i].fault_year = Lcd_data_array[read_ptr][base_index + 6];
            fault_buffer[10 + i].fault_value = (Lcd_data_array[read_ptr][base_index + 7] << 8) | Lcd_data_array[read_ptr][base_index + 8];
        }
    }
    read_ptr = (read_ptr + 1) % BUFFER_SIZE;
}
void ctrlword2_analyze(void)
{
    // F_dataalarm_qy=(ctrlword[1]&0x80)>>7 ;//Ƿѹ��������բ����
    F_trip_qy = (ctrlword[1] & 0x40) >> 6;
    // F_dataalarm_gy=(ctrlword[1]&0x20)>>5 ;
    F_trip_gy = (ctrlword[1] & 0x10) >> 4;
    // F_dataalarm_xq=(ctrlword[1]&0x08)>>3;
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
    D_LCur = (ctrlword[3] >> 4); // ʣ�������λ��ȡ������λ
    //	TH_LCur=((ctrlword[3]&0x0C)>>2);//ȡ������λ  ����޲�����ʱ��
    F_GJ_FUNC_tmp = (ctrlword[3] & 0x03); // ʣ���������ʱ��

    if (D_LCur > 7)
    {
        D_LCur = 0x07;
        ctrlword[3] &= 0x0F;
        ctrlword[3] += (D_LCur << 4);
    }
}
/***��������ֵ����***/

void I_VAL_handle()
{
    // if(!disp_num)
    SET_D_Cur = D_Cur;
    // ������ܵȼ�Ϊ20~100A
    // ������ܵȼ�Ϊ60~250A

    if (Type_Cur == 0)
    {
        if (SET_D_Cur >= 9)
            SET_D_Cur = 8;
        SET_I_VAL = SET_D_Cur * 10 + 50;

        if (SET_I_VAL == 60)
            SET_I_VAL = 63;
        if (SET_I_VAL == 130)
            SET_I_VAL = 125;
    }
    if (Type_Cur == 1)
    {
        // if(SET_D_Cur==20)
        // SET_D_Cur=0 ;
        SET_I_VAL = SET_D_Cur * 10 + 60;

        if (SET_I_VAL == 60)
            SET_I_VAL = 63;
    }
    // ������ܵȼ�Ϊ200~400A
    if (Type_Cur == 2)
    {
        if (SET_D_Cur >= 12)
            SET_D_Cur = 12;
        SET_I_VAL = SET_D_Cur * 20 + 160;
    }

    if (Type_Cur == 3)
    {
        if (SET_D_Cur >= 15)
        {
            SET_D_Cur = 14;
        }
        SET_I_VAL = SET_D_Cur * 30 + 250;

        if (SET_I_VAL == 250)
            SET_I_VAL = 252;
        if (SET_I_VAL == 640)
            SET_I_VAL = 630;
    }
    if (Type_Cur == 4)
    {
        if (SET_D_Cur >= 7)
            SET_D_Cur = 6;
        SET_I_VAL = SET_D_Cur * 80 + 320;
        if (SET_I_VAL == 640)
            SET_I_VAL = 630;
    }
}
void Disp_date(void)
{
    Lcd12864_Write16CnCHAR(0, 0, 0, "15�����޸�\r");

    tim_y3 = sdatestructure.Year; // tim_yΪʮ���ƣ�Ҫת��������
    tim_m3 = sdatestructure.Month;
    tim_d3 = sdatestructure.Date;
    tim_h3 = stimestructure.Hours;
    tim_f3 = stimestructure.Minutes;
    tim_s3 = stimestructure.Seconds;
    HAL_RTC_GetTime(&hrtc, &stimestructure, RTC_FORMAT_BCD);
    HAL_RTC_GetDate(&hrtc, &sdatestructure, RTC_FORMAT_BCD);
    nian[0] = (tim_y3 >> 4) + 0x30;
    nian[1] = (tim_y3 & 0x0F) + 0x30;
    nian[2] = '\0';

    yue[0] = (tim_m3 >> 4) + 0x30;
    yue[1] = (tim_m3 & 0x0F) + 0x30;
    yue[2] = '\0';

    ri[0] = (tim_d3 >> 4) + 0x30;
    ri[1] = (tim_d3 & 0x0F) + 0x30;
    ri[2] = '\0';

    shi[0] = (tim_h3 >> 4) + 0x30;
    shi[1] = (tim_h3 & 0x0F) + 0x30;
    shi[2] = '\0';

    fen[0] = (tim_f3 >> 4) + 0x30;
    fen[1] = (tim_f3 & 0x0F) + 0x30;
    fen[2] = '\0';

    miao[0] = (tim_s3 >> 4) + 0x30;
    miao[1] = (tim_s3 & 0x0F) + 0x30;
    miao[2] = '\0';

    nian_qian[0] = 0x02 + 0x30;
    nian_qian[1] = 0x00 + 0x30;
    nian_qian[2] = '\0';
}
void Disp_time(void)
{
    Lcd12864_Write16CnCHAR(0, 0, 4, "16ʱ���޸�\r");
}
void Disp_Write_time(void)
{
    sdatestructure.Year = tim_y3;
    sdatestructure.Month = tim_m3;
    sdatestructure.Date = tim_d3;
    stimestructure.Hours = tim_h3;
    stimestructure.Minutes = tim_f3;
    stimestructure.Seconds = tim_s3;
}
// �������������� field1 ������ 15 ��Ԫ������
int countNotEqual15(fault arr[], int size, int *min_index)
{
    int count = 0;
    *min_index = -1; // ��ʼֵ��Ϊ -1 ��ʾδ�ҵ�
    for (int i = 0; i < size; i++)
    {
        if (arr[i].fault_type != 0XFF)
        {

            count++;
            if (*min_index == -1)
            {
                *min_index = i;
            }
        }
    }
    return count;
}
void faultdisp()
{
    char zifu_dian1[12] = {1, 1, 1, 1};
    int min_index;
    int count = countNotEqual15(fault_buffer, 20, &min_index); // ���ú�����������

    if (count != 0)
    {
        Lcd12864_Write16CnCHAR(0, 0, 0, "��   ����բ��Ϣ\r");
        value_to_ascii1(current_page + 1, zifu_dian);
        display_ASCIIstring_8x16(1, 25, zifu_dian);
        Lcd12864_Write16CnCHAR(0, 0, 2, "����:");

        Lcd12864_Write16CnCHAR(0, 40, 2, guzhang_yuanyin[fault_buffer[min_index + current_page].fault_type]);
        switch (fault_buffer[min_index + current_page].fault_type)
        {
        case 0:
            Lcd12864_Write16CnCHAR(0, 110, 4, "V");
            break;
        case 1:
            Lcd12864_Write16CnCHAR(0, 110, 4, "V");
            break;
        case 2:
            Lcd12864_Write16CnCHAR(0, 110, 4, "mA");
            break;
        case 3:
            Lcd12864_Write16CnCHAR(0, 110, 4, "A");
            break;
        case 4:
            Lcd12864_Write16CnCHAR(0, 110, 4, " ");
            break;
        case 5:
            Lcd12864_Write16CnCHAR(0, 110, 4, " ");
            break;
        case 6:
            Lcd12864_Write16CnCHAR(0, 110, 4, " ");
            break;
        case 7:
            Lcd12864_Write16CnCHAR(0, 110, 4, " ");
            break;
        case 8:
            Lcd12864_Write16CnCHAR(0, 110, 4, " ");
            break;
        case 9:
            Lcd12864_Write16CnCHAR(0, 110, 4, "V");
            break;
        case 10:
            Lcd12864_Write16CnCHAR(0, 110, 4, "V");
            break;
        case 11:
            Lcd12864_Write16CnCHAR(0, 110, 4, "A");
            break;
        case 12:
            Lcd12864_Write16CnCHAR(0, 110, 4, "A");
            break;
        }
        value_to_ascii1(fault_buffer[min_index + current_page].fault_value, zifu_dian);
        Lcd12864_Write16CnCHAR(0, 0, 4, "����ֵ:");
        display_ASCIIstring_8x16(5, 77, zifu_dian);
        value_to_ascii1(fault_buffer[min_index + current_page].fault_year, zifu_dian);

        display_ASCIIstring_8x16(7, 8, zifu_dian);
        display_graphic_8x16(7, 24, qirigang);
        value_to_ascii1(fault_buffer[min_index + current_page].fault_month, zifu_dian);
        display_ASCIIstring_8x16(7, 29, zifu_dian);
        display_graphic_8x16(7, 45, qirigang);
        value_to_ascii1(fault_buffer[min_index + current_page].fault_data, zifu_dian);
        display_ASCIIstring_8x16(7, 50, zifu_dian);
        display_graphic_8x16(7, 65, xiaogang);
        value_to_ascii1(fault_buffer[min_index + current_page].fault_hour, zifu_dian);
        display_ASCIIstring_8x16(7, 71, zifu_dian);
        display_graphic_8x16(7, 87, xiaomaohao);
        value_to_ascii1(fault_buffer[min_index + current_page].fault_min, zifu_dian);
        display_ASCIIstring_8x16(7, 92, zifu_dian);
        display_graphic_8x16(7, 108, xiaomaohao);
        value_to_ascii1(fault_buffer[min_index + current_page].fault_sec, zifu_dian);
        display_ASCIIstring_8x16(7, 113, zifu_dian);
    }
    else
        Lcd12864_Write16CnCHAR(0, 20, 3, "�޹�����Ϣ");
    if (key == KEY_DOWN_PRES)
    {
        if (current_page > 0)
        {
            clear_screen();
            current_page--;
        }
    }
    else if (key == KEY_UP_PRES)
    {
        if (current_page < count - 1)
        {
            clear_screen();
            current_page++;
        }
    }
}

typedef struct
{
    char *NAME;            // ����
    unsigned char (*A)[8]; // ʹ��ָ�������ָ��
    unsigned char *value;
    unsigned char array_size;
    //	int setting_up;   //����ֵ
    //	int setting_down;  //����ֵ
    //	int *setting_value;  //�趨ֵָ��
    //	enum type_unit type;      //��λ����
    //	bool   arrayORaccumulate;   //���黹���ۼ� 0���ۼӣ�1������
    //	int array[4];
    //	  unsigned char (*A)[6]; // ʹ��ָ�������ָ��
    //	unsigned char *value;
    //    unsigned char array_size;
    //	void (*func)(void);
} warningtype;

void disp_list(warningtype warning_set[], int total_items);
int power_consumption[4] = {1000, 2000, 3000, 4000};
unsigned char frequency_up_warning = 5, frequency_down_warning = 5, avu_warning = 4, bvu_warning = 3, cvu_warning = 3;
unsigned char avd_warning = 2, bvd_warning = 2, cvd_warning = 2;
unsigned char aiu_warning = 2, biu_warning = 2, ciu_warning = 2;
unsigned char aid_warning = 2, bid_warning = 2, cid_warning = 2;
unsigned char power_warning = 2, powerconsumption_warning = 3;
unsigned char temperature_out_warning = 2, temperature_in_warning = 2;
unsigned char P_warning = 2, Q_warning = 2, S_warning = 2;
unsigned char cos_warning = 2;
unsigned char U_UB_waring = 2, I_UB_waring = 2;
// ���ַ����еĵ�ѹֵת��Ϊ����
int parse_voltage(const unsigned char *voltage_str, char a)
{
    char buffer[8];
    snprintf(buffer, sizeof(buffer), "%s", voltage_str);
    switch (a)
    {
    case 0:
        buffer[strlen(buffer) - 0] = '\0';
        break;
    case 1:
        buffer[strlen(buffer) - 1] = '\0';
        break;
    case 2:
        buffer[strlen(buffer) - 2] = '\0';
        break;
    case 3:
        buffer[strlen(buffer) - 3] = '\0';
        break;
    case 4:
        buffer[strlen(buffer) - 4] = '\0';
        break;
    }

    return atoi(buffer);
}
double parse_voltage1(const unsigned char *voltage_str)
{
    return atof((const char *)voltage_str);
}
bool exceeded[15] = {false};
bool waring;
int upper_hz;
int upper_q;
double Cos;
int upper_TEM;
int waring_num;
int lower_voltage;
 int U_UB;
 int I_UB;
void waring_compare()
{

    waring_num = 0;
    bool anyExceeded = false;
    int upper_voltage = parse_voltage(DIANYA1[avu_warning], 1);
    lower_voltage = parse_voltage(DIANYA_11[avd_warning], 1);
    int upper_current = parse_voltage(guoliu_type21[aiu_warning], 1);
    int lower_current = parse_voltage(guoliu_type21[aid_warning], 1);
    upper_hz = parse_voltage(hz_up[frequency_up_warning], 2);
    int lower_hz = parse_voltage(hz_down[frequency_down_warning], 2);
    int upper_power = parse_voltage(power_waring[power_warning], 2);
    upper_TEM = parse_voltage(TEM_UP_show1[temperature_in_warning], 0);
    int lower_TEM = parse_voltage(TEM_UP_show1[temperature_out_warning], 0);
    int upper_p = parse_voltage(p_waring[P_warning], 2);
    upper_q = parse_voltage(q_waring[Q_warning], 4);
    int upper_s = parse_voltage(s_warning[S_warning], 4);
    Cos = parse_voltage1(Cos_warning[cos_warning]);
   U_UB = parse_voltage(u_UB_waring[U_UB_waring], 1);
   I_UB = parse_voltage(i_UB_waring[I_UB_waring], 1);
    int Power_c = parse_voltage(Powerconsumption_warning[powerconsumption_warning], 3);

    if (HT7038_buf11[1] > upper_voltage || HT7038_buf11[2] > upper_voltage || HT7038_buf11[3] > upper_voltage)
    {
        exceeded[1] = true; // ��ѹ������
        anyExceeded = true;
        waring_num++;
    }
    else
        exceeded[1] = false;
    if (HT7038_buf11[1] < lower_voltage || HT7038_buf11[2] < lower_voltage || HT7038_buf11[3] < lower_voltage)
    {
        exceeded[2] = true; // ��ѹ������
        anyExceeded = true;
        waring_num++;
    }
    else
        exceeded[2] = false;
    if (HT7038_buf11[4] > upper_current || HT7038_buf11[5] > upper_current || HT7038_buf11[6] > upper_current)
    {
        exceeded[3] = true; // ����������
        anyExceeded = true;
        waring_num++;
    }
    else
        exceeded[3] = false;
    if (HT7038_buf11[43] > upper_hz)
    {
        exceeded[4] = true; // Ƶ�ʳ�����
        anyExceeded = true;
        waring_num++;
    }
    else
        exceeded[4] = false;
    if (HT7038_buf11[43] < lower_hz)
    {
        exceeded[5] = true; // Ƶ�ʳ�����
        anyExceeded = true;
        waring_num++;
    }
    else
        exceeded[5] = false;
    if (HT7038_buf11[10] > upper_power)
    {
        exceeded[6] = true; // ���ʳ�����
        anyExceeded = true;
        waring_num++;
    }
    else
        exceeded[6] = false;
    if (max_value > upper_TEM)
    {
        exceeded[7] = true; // ���߳�����
        anyExceeded = true;
        waring_num++;
    }
    else
        exceeded[7] = false;
    if (max_value > lower_TEM)
    {
        exceeded[8] = true; // ���߳�����
        anyExceeded = true;
        waring_num++;
    }
    else
        exceeded[8] = false;
    if (HT7038_buf11[10] > upper_p)
    {
        exceeded[9] = true; // �й����ʳ�����
        anyExceeded = true;
        waring_num++;
    }
    else
        exceeded[9] = false;
    if (HT7038_buf11[19] > upper_q)
    {
        exceeded[10] = true; // �޹����ʳ�����
        anyExceeded = true;
        waring_num++;
    }
    else
        exceeded[10] = false;
    if (HT7038_buf11[23] > upper_s)
    {
        exceeded[11] = true; // ���ڹ��ʳ�����
        anyExceeded = true;
        waring_num++;
    }
    else
        exceeded[11] = false;
    if (HT7038_buf11[14] < Cos)
    {
        exceeded[12] = true; // ��������������
        anyExceeded = true;
        waring_num++;
    }
    else
        exceeded[12] = false;
    if (HT7038_buf11[44] > U_UB)
    {
        exceeded[13] = true; // ��ѹ��ƽ�ⳬ����
        anyExceeded = true;
        waring_num++;
    }
    else
        exceeded[13] = false;
    if (HT7038_buf11[45] > I_UB)
    {
        exceeded[14] = true; // ������ƽ�ⳬ����
        anyExceeded = true;
        waring_num++;
    }
    else
        exceeded[14] = false;
    if (p_c_day > Power_c)
    {
        exceeded[15] = true; // ��������������
        anyExceeded = true;
        waring_num++;
    }
    else
        exceeded[15] = false;
    if (anyExceeded)
    {
        LED_waring_ON
            waring = true;
    }
    else
        LED_waring_OFF
}
void warning_setting()
{
    warningtype warning_set[] = {

        {"��ѹ����", DIANYA1, &avu_warning, 5},
        {"��ѹ����", DIANYA_11, &avd_warning, 5},
        {"��������", guoliu_type21, &aiu_warning, 19},
        {"��������", guoliu_type21, &aid_warning, 19},
        {"Ƶ������", hz_up, &frequency_up_warning, 5},
        {"Ƶ������", hz_down, &frequency_down_warning, 5},
        {"��������", power_waring, &power_warning, 12},
        {"�����¶�", TEM_UP_show1, &temperature_in_warning, 5},
        {"�����¶�", TEM_UP_show1, &temperature_out_warning, 5},
        {"�й�����", p_waring, &P_warning, 9},
        {"�޹�����", q_waring, &Q_warning, 9},
        {"���ڹ���", s_warning, &S_warning, 9},
        {"��������", Cos_warning, &cos_warning, 4},
        {"UUB", u_UB_waring, &U_UB_waring, 5},
        {"IUB", i_UB_waring, &I_UB_waring, 5},
        {"������Χ", Powerconsumption_warning, &powerconsumption_warning, 3},
        //		{"������Χ",NULL,NULL,&powerconsumption_warning,kWh,1,{1000, 2000, 3000, 4000}},
        ////		{"a���ѹ����",250,300,&avu_warning,V,0},
        ////		{"a���ѹ����",140,190,&avd_warning,V,0},
        ////		{"b���ѹ����",250,300,&bvu_warning,V,0},
        ////		{"b���ѹ����",140,190,&bvd_warning,V,0},
        ////		{"c���ѹ����",250,300,&cvu_warning,V,0},
        ////		{"c���ѹ����",140,190,&cvd_warning,V,0},
        ////		{"a���������",63,250, &aiu_warning,A,0},
        ////		{"a���������",63,250, &aid_warning,A,0},
        ////		{"b���������",63,250, &biu_warning,A,0},
        ////		{"b���������",63,250, &bid_warning,A,0},
        ////		{"c���������",63,250, &ciu_warning,A,0},
        ////		{"c���������",63,250, &cid_warning,A,0},
        //		{"Ƶ��",40,60,&frequency_warning,HZ,0},
        //		{"����",50,150,&power_warning,kW,0},
        //		{"�����¶�",50,100,&temperature_in_warning,C},
        //		{"�����¶�",50,100,&temperature_out_warning,C},
        //		{"�й�����",60,150,&P_warning,kW,0},
        //		{"�޹�����",60,150,&Q_warning,kvar,0},
        //		{"���ڹ���",60,150,&S_warning,kVA,0},
        //		{"��������",60,100,&cos_warning,NULL,0},
        //		{"UUB",0,30,&U_UB_waring,percent,0},
        //		{"IUB",0,30,&I_UB_waring,percent,0},
        //		{"������Χ",NULL,NULL,&powerconsumption_warning,kWh,1,{1000, 2000, 3000, 4000}},
        //		{"������Χ",NULL,NULL,&powerconsumption_warning,kWh,1,{1000, 2000, 3000, 4000}},
        ////		{"a���ѹ",40,60,&frequency_warning},
        ////		{"a���ѹ",40,60,&frequency_warning},
        ////		{"a���ѹ",40,60,&frequency_warning},
        ////		{"a���ѹ",40,60,&frequency_warning}
        //
    };
    int totallist = sizeof(warning_set) / sizeof(warning_set[0]);
    disp_list(warning_set, totallist);
}
#define list_PER_PAGE 4

void disp_list(warningtype warning_set[], int total_items)
{
    //	int totalItems=4;
    //	 int start_index = current_page * list_PER_PAGE;
    //    int end_index = start_index + list_PER_PAGE;
    //	 if (end_index > total_items) {
    //        end_index = total_items;
    //    }

    for (int i = 0; i < 4; i++)
    {
        int x;
        x = strlen(warning_set[current_page + i].NAME);
        display_graphic_8x16(2 * i + 1, 8 * x - 2, maohao);
        Lcd12864_Write14CnCHAR(0, 0, 2 * i, warning_set[current_page + i].NAME);
    }

    //

    for (int i = 0; i < 4; i++)
    {

        if (i == a)
        {
            display_ASCIIstring_8x16_fanxian(2 * i + 1, 72, warning_set[current_page + i].A[*(warning_set[current_page + i].value)]);
        }
        else
        {
            display_ASCIIstring_8x16(2 * i + 1, 72, warning_set[current_page + i].A[*(warning_set[current_page + i].value)]);
        }
    }

    if (key == KEY_DOWN_PRES)
    {
        a--;
        if (a < 0)
        {
            current_page -= 4;
            a = 3;
            clear_screen();
        }
    }
    else if (key == KEY_UP_PRES)
    {
        a++;
        if (a > 3)
        {
            current_page += 4;
            a = 0;
            clear_screen();
        }
    }
    else if (key == KEY_RIGHRT_PRES && (*(warning_set[current_page + a].value)) > 0)
    {
        clear_screen();
        (*(warning_set[current_page + a].value))--;
    }

    else if (key == KEY_LEFT_PRES && (*(warning_set[current_page + a].value) < warning_set[current_page + a].array_size))
    {
        clear_screen();
        (*(warning_set[current_page + a].value))++;
    }
}
void displayExceedMessage(int line, const char *message)
{
    switch (line)
    {
    case 1:
        Lcd12864_Write14CnCHAR(0, 0, 2, message);
        break;
    case 2:
        Lcd12864_Write14CnCHAR(0, 0, 4, message);
        break;
    case 3:
        Lcd12864_Write14CnCHAR(0, 0, 6, message);
        break;
    case 4:
        Lcd12864_Write14CnCHAR(0, 60, 2, message);
        break;
    case 5:
        Lcd12864_Write14CnCHAR(0, 60, 4, message);
        break;
    case 6:
        Lcd12864_Write14CnCHAR(0, 60, 6, message);
        break;
    default:
        // �����Ҫ������6�е������������������Ӵ���
        break;
    }
}

void displayExceededVoltages()
{

    int line = 0;

    for (int i = 0; i < 15; i++)
    {
        if (exceeded[i] && (i == 1 || i == 2))
        {
            line++;
            displayExceedMessage(line, "��ѹ����");
        }

        if (exceeded[i] && (i == 3))
        {
            line++;
            displayExceedMessage(line, "��������");
        }
        if (exceeded[i] && (i == 4 || i == 5))
        {
            line++;
            displayExceedMessage(line, "Ƶ�ʳ���");
        }

        if (exceeded[i] && (i == 6))
        {
            line++;
            displayExceedMessage(line, "���ʳ���");
        }
        if (exceeded[i] && (i == 7 || i == 8))
        {
            line++;
            displayExceedMessage(line, "�¶ȳ���");
        }
        if (exceeded[i] && (i == 9 || i == 10 || i == 11))
        {
            line++;
            displayExceedMessage(line, "����");
        }
        if (exceeded[i] && (i == 12))
        {
            line++;
            displayExceedMessage(line, "��������");
        }
        if (exceeded[i] && (i == 13))
        {
            line++;
            displayExceedMessage(line, "��ѹƽ��");
        }
        if (exceeded[i] && (i == 14))
        {
            line++;
            displayExceedMessage(line, "����ƽ��");
        }
        if (exceeded[i] && (i == 15))
        {
            line++;
            displayExceedMessage(line, "���ܳ���");
        }
    }
    switch (line)
    {
    case 0:
        displayExceedMessage(line + 1, "        ");
        displayExceedMessage(line + 2, "        ");
        displayExceedMessage(line + 3, "        ");
        displayExceedMessage(line + 4, "        ");
        displayExceedMessage(line + 5, "        ");
        displayExceedMessage(line + 6, "        ");
        break;

    case 1:
        displayExceedMessage(line + 1, "        ");
        displayExceedMessage(line + 2, "        ");
        displayExceedMessage(line + 3, "        ");
        displayExceedMessage(line + 4, "        ");
        displayExceedMessage(line + 5, "        ");
        break;
    case 2:
        displayExceedMessage(line + 1, "        ");
        displayExceedMessage(line + 2, "        ");
        displayExceedMessage(line + 3, "        ");
        displayExceedMessage(line + 4, "        ");
        break;
    case 3:
        displayExceedMessage(line + 1, "        ");
        displayExceedMessage(line + 2, "        ");
        displayExceedMessage(line + 3, "        ");
        break;
    case 4:
        displayExceedMessage(line + 1, "        ");
        displayExceedMessage(line + 2, "        ");
        break;
    case 5:
        displayExceedMessage(line + 1, "        ");
        break;
    }
    if (line != 0)
    {
        Lcd12864_Write16CnCHAR(0, 30, 0, " ������Ϣ ");
    }
    else
        Lcd12864_Write16CnCHAR(0, 18, 0, " �ޱ�����Ϣ ");
}
