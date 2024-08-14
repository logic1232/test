#include "menu.h"
#include "lcd.h"
#include "display_ziku.h"
#include "gpio.h"
#include "rtc.h"
#include "tool.h"
#include <stdbool.h>
#include <stdlib.h>
#define TOTAL_SCREENS 13 // 轮询显现界面页数
#define ITEMS_PER_PAGE 2

#define A_qy 0
// A相欠压故障
#define B_qy 2
// B相欠压故障
#define C_qy 4
// C相欠压故障
#define A_gy 1
// A相过压故障
#define B_gy 3
// B相过压故障
#define C_gy 5
// C相过压故障
#define L_hb 6
// 漏电故障
#define A_gl 7
// A相过流故障
#define B_gl 8
// B相过流故障
#define C_gl 9
// C相过流故障
#define N_gl 0x0A
// D相过流故障
#define Gz_TD 0x0B
// 停电故障
// #define FZ_SD 0x0C //手动分闸（未知）
#define FZ_UK 0x0c
// 未知分闸
#define FZ_AJ 0x0d
// 按键分闸
#define FZ_YC 0x0e
// 远程分闸
#define A_QX 0x10 // 缺相
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
extern int write_ptr; // 写入指针，初始位置为0
extern int read_ptr;  // 读取指针，初始位置为0
char F_GUZHANG = 0;   // 实现退出清屏
extern volatile unsigned char F_Dataval;
RTC_DateTypeDef sdatestructure;
RTC_TimeTypeDef stimestructure;
char F_AEorREorALLE; // 有功电能1or无功电能2or总电能3标志位
char f_f = 1;
int a1; // 菜单界面指针
extern bool F_initialization;
char qiehuan = 0; // 密码正确or错误
int one = 1;
volatile unsigned char tim_m3, tim_d3, tim_h3, tim_f3, tim_s3, tim_m3temp, tim_d3temp, tim_h3temp, tim_f3temp, tim_s3temp, tim_y3, tim_y3temp; // 时间相关
unsigned char nian_qian[3] = {0};                                                                                                              // 时间相关
volatile unsigned char SET_D_Cur = 0;                                                                                                          // 过流档位？
unsigned char mima[4];                                                                                                                         // 输入的密码
unsigned char mima_set[4], mima_settemp[4];                                                                                                    // 设定的密码
unsigned char mima_set_compare[4];                                                                                                             // 用于密码临时设置最后再和
char F_jiaozhuned;                                                                                                                             // 校准完成标志位
volatile unsigned char Cal_state = 0;                                                                                                          // 表示校准类型
char F_adjustbegin;                                                                                                                            // 开始校准标志位
uint8_t F_adjustswitch;                                                                                                                        // 校准界面切换标志位
volatile unsigned int SET_I_VAL;                                                                                                               // 不明白是啥
char isfenzha = 1;                                                                                                                             // 分闸指示
extern int F_Y, F_Ypro;                                                                                                                        // 菜单第几页标志位
int array_size;
extern int a;             // 菜单位置指针
extern int b;             // 菜单数组数据指针
char F_Ftoer;             // 轮询界面和菜单界面区分标志位
extern char F_MAINormenu; // 判断封面还是菜单标志还是保护界面 0封面 1参数设置 2保护设置
extern unsigned char maohao[16];
extern int key;
static int current_screen = 0;
extern int F_mainchange;
volatile unsigned char D_LCur = 4, D_A_LCur = 0, LC_N = 0, TH_LCur, Vol_g, Vol_q, TH_LCurtemp, Vol_gtemp, Vol_qtemp, D3_Curtemp;                              // 漏电电流档位指针
unsigned char N_GY_yanshi = 0, N_QY_yanshi = 0, D_GY_yanshi = 0, D3_Cur = 0, D_QY_yanshi = 0, D_SY_yanshi, D_SY_yanshitemp, D_GY_yanshitemp, D_QY_yanshitemp; // 第二页挡位指针
unsigned char D2_Cur = 0, TH_DL = 0, TH_Long_Cur = 0, D_Cur, D_Curtemp, TH_Long_Curtemp, D2_Curtemp, TH_DLtemp, Type_Cur, Type_Curtemp;                       //     第三页挡位指针
unsigned char baud, TH_TEM_UP, TH_TEM_DOWN, TH_TEM_UPtemp, TH_TEM_DOWNtemp, baudtemp;                                                                         // 第四页挡位指针
bool F_Special_wave, F_trip_ld, F_auto_ld, F_TB_trip, F_TB_triptemp, F_Special_wavetemp;                                                                      // 保护第一页指针
bool F_trip_QX, F_trip_qy, F_trip_gy, F_trip_QL;                                                                                                              // 保护第二页指针
bool F_ip_3, F_ip, F_trip_gl, F_trip_sy, F_iptemp, F_ip_3temp, F_trip_sytemp;                                                                                 // 保护第三页指针
bool DY_hezha, LD_hezha, shangdian, jiaozhun, jiaozhuntemp, shangdiantemp, LD_hezhatemp, DY_hezhatemp;                                                        // 保护第四页指针
bool F_TX, wendu, DL_hezha, DL_hezhatemp, wendutemp, F_TXtemp;                                                                                                // 保护第五页指针
volatile unsigned int Num_tripall, Num_clearall, Num_triplock, Num_tripleak, Num_tripcur, Num_tripvol, Num_triphand, Num_triptest, Num_tripdelay, Num_tripinstant, Num_leakover, Num_leakprotect;
extern unsigned char F_LEAK_OPEN_CLOSE, F_open;                                                     // 串口发送相关区分不同类型分合闸
int current_page = 0;                                                                               // 数据界面页数
volatile unsigned char F_disp_jg, F_disp_tr, F_hezha_state, F_fenzha_state, F_gz_disp = 0x0F, F_ch; // 故障和分合闸状态相关标志位
volatile unsigned int gz_disp;
extern char F_FENHEZHA;
extern uint8_t max_value; // ad口最大温度
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
        "欠压", "过压", "漏电", "过流", "停电", "手动", "按键", "远程", "其他", "缺相", "缺零", "短延", "短瞬"};

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
void mainmenu();    // 主菜单
void meun1();       // 菜单1界面
void meun2();       // 菜单2界面
void meun3();       // 菜单3界面
void meun4();       // 菜单4界面
void meun5();       // 菜单5界面
void meun();        // 轮询主函数
void screenbase1(); // 轮询1界面
void screenbase2(); // 轮询2界面
void screenbase3(); // 轮询3界面
void screenbase4(); // 轮询4界面
void screenbase5(); // 轮询5界面
void screenbase6(); // 轮询6界面
void screenbase7(); // 轮询7界面
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
void meun_data();   // 跳闸次数查询界面
void meun_adjust(); // 校准界面
void meun_protect1();
void meun_protect2();
void meun_protect3();
void meun_protect4();
void meun_protect5();
void Power_parameters(); // 电能参数
void Disp_Write_time(void);
void menu_mimaset(); // 修改密码
int mimaset();
void timechange();
void warning_setting();
void Disp_date(void);
void Disp_time(void);
void fenzhaing();   // 正在分闸...
void hezhaing();    // 正在合闸...
void problemdisp(); // 故障显示相关
void updata_c();    // 更新更改档位
void judge();       // 判断档位是否更改
void ctrlword4_analyze(void);
void ctrlword2_analyze(void);
void ctrlword3_analyze(void);
void I_VAL_handle();
void faultdisp();
void USART_LCD_Transmit(unsigned char len, unsigned char ch);
void value_to_ascii1(int value, char *ascii_array)
{
    char temp_str[12]; // 临时存放整数字符串，长度要足够大以容纳整数及结束符

    // 将整数转换为字符串
    sprintf(temp_str, "%02d", value);

    // 将字符串中的每个字符转换为 ASCII 值并存放到数组中
    for (int i = 0; i < strlen(temp_str); ++i)
    {
        ascii_array[i] = temp_str[i];
    }
    ascii_array[strlen(temp_str)] = '\0'; // 添加字符串结束符
}
void int_to_ascii(int num, char *str)
{
    sprintf(str, "%d", num); // 使用 sprintf 将整数格式化到字符串中
}
void disp_data(int x, int y, char i, int value) // 显示数据
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
    unsigned char (*A)[6]; // 使用指向数组的指针
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

    switch (a) // a是按了几次 d是判断出来的有几行    //这个switch是选择是哪一行
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
            //		if(F_Y==4) F_Y=5;        //跳出结构体菜单
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

    else if (key == KEY_AFFIRM_PRES) // 确认之后要加数据比较，有变更发送数据
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
void MEUN() // 判断不同菜单的标志位确定展示什么
{
    for (int i = 0; i < 300; i++)
    {
        HT7038_buf1[i] = HT7038_buf11[i];
    }
    if (F_initialization == 0)

    {
        Lcd12864_Write16CnCHAR(0, 0, 3, " 正在初始化...");
    }

    else
    {
        if (((F_hezha_state != 0) || (F_fenzha_state != 0)) && (F_gz_disp == 0x0F))
        {
            if (F_hezha_state == 1)
            {
                hezhaing(); // 正在合闸
            }
            else if (F_fenzha_state == 1)
            {
                fenzhaing(); // 正在分闸
            }
        }
        else if (F_gz_disp == 0x0F) // 未发生故障
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
            else if (F_MAINormenu == 1 && F_Y == 5) // 修改时间设置
            {
                timechange();
            }
            else if (F_MAINormenu == 1 && F_Y == 6) // 修改密码和挡位设置
            {
                menu_mimaset();
            }
            else if (F_MAINormenu == 2 && F_Ypro == 0) // 保护界面
            {
                meun_protect1();
            }
            else if (F_MAINormenu == 2 && F_Ypro == 1) // 保护界面
            {
                meun_protect2();
            }
            else if (F_MAINormenu == 2 && F_Ypro == 2) // 保护界面
            {
                meun_protect3();
            }
            else if (F_MAINormenu == 2 && F_Ypro == 3) // 保护界面
            {
                meun_protect4();
            }
            else if (F_MAINormenu == 2 && F_Ypro == 4) // 保护界面
            {
                meun_protect5();
            }
            else if (F_MAINormenu == 4) // F_MAINormenu==4跳闸次数界面
            {
                menu_fault(); // 跳闸次数界面
            }
            else if (F_MAINormenu == 5)
            {
                meun_adjust(); // 校准界面
            }
            else if (F_FENHEZHA == 1 && F_MAINormenu == 3)
            {
                fenzhaing(); // 正在分闸
            }
            else if (F_FENHEZHA == 2 && F_MAINormenu == 3)
            {
                hezhaing(); // 正在合闸
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
                power_quality(); // 电力品质se9();
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
        else if (F_gz_disp != 0x0F) // 有故障,显示故障相关界面
        {
            problemdisp();
            if (key == KEY_AFFIRM_PRES) // 故障状态按下确定键，实现故障显示退出
            {

                USART_LCD_Transmit(1, 4);
            }
        }
    }
}
void meun1() // 菜单1
{

    meuntype menu[] = {
        {"1漏电阀值", dianliu, &D_LCur, 7},
        {"2漏电延时", shijian, &TH_LCur, 4},
        {"3过压档位", DIANYA, &Vol_g, 5},
        {"4欠压档位", DIANYA_1, &Vol_q, 5},

    };
    int totalItems = sizeof(menu) / sizeof(menu[0]);
    displayMenu(menu, totalItems, 0);
    ctrlword[3] &= 0x0F;
    ctrlword[3] += (D_LCur << 4);
    ctrlword4_analyze();
}
void meun2() // 菜单2
{

    meuntype menu[] = {
        {"5失压延时", SY_yanshi, &D_SY_yanshi, 9},
        {"6过压延时", GY_yanshi, &D_GY_yanshi, 9},
        {"7欠压延时", QY_yanshi, &D_QY_yanshi, 9},
        {"8瞬时档位", D3_DW, &D3_Cur, 5},

    };
    int totalItems = sizeof(menu) / sizeof(menu[0]);
    displayMenu(menu, totalItems, 0);
}
void meun3() // 菜单3
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
        {"9过流档位", guoliu_show, &D_Cur, D_Cur_P},
        {"10过流时间", GUOLIU_T, &TH_Long_Cur, 7},
        {"11短延档位", D2_DW, &D2_Cur, 5},
        {"12短延时间", D2_T, &TH_DL, 5},

    };
    int totalItems = sizeof(menu) / sizeof(menu[0]);
    displayMenu(menu, totalItems, 0);
}
void meun4() // 菜单3
{
    meuntype menu[] = {
        {"13高温分闸", TEM_UP_show, &TH_TEM_UP, 5},
        {"14低温合闸", TEM_DOWN_show, &TH_TEM_DOWN, 4},
        {"15通信速率", botelv, &baud, 3},
        {"16壳架设置", Type_cur_show, &Type_Cur, 4}, // 这个没搞明白有问题

    };
    int totalItems = sizeof(menu) / sizeof(menu[0]);
    displayMenu(menu, totalItems, 0);
}
void meun5() // 菜单4
{
    meuntype menu[] = {
        {"17日期", TEM_UP_show, &TH_TEM_UP, 5},
        {"18时间", TEM_DOWN_show, &TH_TEM_DOWN, 4},
        //        {"15通信速率", botelv,&baud,5},
        //        {"16壳架设置", D2_T,&TH_DL,5},            //这个没搞明白有问题

    };
    int totalItems = sizeof(menu) / sizeof(menu[0]);
    displayMenu(menu, totalItems, 1);
}
void (*screenbase_funcs[13])() = {
    screenbase1, screenbase2, screenbase3, screenbase4, screenbase5, screenbase6, screenbase7, screenbase8, screenbase9, screenbase10};
void meun() // 封面
{
    screenbase_funcs[F_mainchange]();
    //	 if(F_mainchange==1)
    //	 {
    //		  showScreen(current_screen);

    //    // 更新标志位以展示下一个界面
    //    current_screen = (current_screen + 1) % TOTAL_SCREENS;
    ////		 Lcd12864_Write16CnCHAR(0,32,0,"分闸运行\r");
    //		 F_mainchange=0;
    //
    //	 }
    //	 if(F_mainchange==2)
    //	 {
    //		  showScreen(current_screen);

    //    // 更新标志位以展示下一个界面
    //    current_screen = (current_screen -1) % TOTAL_SCREENS;
    ////		 Lcd12864_Write16CnCHAR(0,32,0,"分闸运行\r");
    //		 F_mainchange=0;
    //
    //	 }
}
void showScreen(int screenIndex)
{ // 轮询的展示实现
    // 根据传入的 screenIndex 展示相应的界面
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

void screenbase1() // 轮询1界面
{
    switch (HT7038_buf1[46])
    {
    case 0:
        Lcd12864_Write16CnCHAR(0, 5, 0, "↗");
        break;
    case 1:
        Lcd12864_Write16CnCHAR(0, 5, 0, "↗");
        break;
    case 2:
        Lcd12864_Write16CnCHAR(0, 5, 0, "↖");
        break;
    case 3:
        Lcd12864_Write16CnCHAR(0, 5, 0, "↙");
        break;
    case 4:
        Lcd12864_Write16CnCHAR(0, 5, 0, "↘");
        break;
    }
    int_to_ascii(HT7038_buf1[43], zifu_dian);
    Lcd12864_Write14CnCHAR(0, 95, 0, zifu_dian);
    Lcd12864_Write14CnCHAR(0, 111, 0, "hz");
    if (isfenzha == 0)
    {
        Lcd12864_Write16CnCHAR(0, 32, 0, "分闸运行");
    }

    else if ((F_trip_ld == 1) && Leak_Cur_disp > 15)
    {
        Lcd12864_Write16CnCHAR(0, 0, 0, "漏电告警");
        xianshishuju(Leak_Cur_disp);
        display_ASCIIstring_8x16(1, 73, (unsigned char *)zifu_dian);
        Lcd12864_Write16CnCHAR(0, 105, 0, "mA");
    }

    else if ((isfenzha != 0) || (F_trip_ld == 0))
    {
        Lcd12864_Write14CnCHAR(0, 32, 0, "合闸运行\r");
    }

    Lcd12864_Write16CnCHAR(0, 0, 0, "\r漏电档位:\r额定电流:\r");
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

void screenbase2() // 轮询2界面
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
void screenbase3() // 轮询3界面      有功电能
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
        xianshishuju2(HT7038_buf1[18]); // 合相有功电能

        display_ASCIIstring_8x16(1, 29, zifu_dian);     // 29
        display_graphic_8x16(1, 53, dian);              // 36
        display_ASCIIstring_8x16(1, 60, &zifu_dian[3]); // 44

        xianshishuju2(HT7038_buf1[15]); // A相有功电能

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
void screenbase4() // 轮询4界面    功率系数
{

    //	Lcd12864_Write16CnCHAR(0,16,0,"功率系数/P_F");

    Lcd12864_Write16CnCHAR(0, 0, 0, "PFs:");
    Lcd12864_Write16CnCHAR(0, 0, 2, "PFa:");
    Lcd12864_Write16CnCHAR(0, 0, 4, "PFb:");
    Lcd12864_Write16CnCHAR(0, 0, 6, "PFc:");
    xianshishuju3(HT7038_buf1[14]); // 功率系数数据

    display_ASCIIstring_8x16(1, 56, zifu_dian);
    display_graphic_8x16(1, 63, dian);
    display_ASCIIstring_8x16(1, 71, &zifu_dian[1]);

    xianshishuju3(HT7038_buf1[11]); // 功率系数数据

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
void screenbase5() // 轮询5界面    有功功率
{
    // if(F_Dataval==0)
    {

        // 有功率数据
        Lcd12864_Write16CnCHAR(0, 0, 0, "Ps:");
        Lcd12864_Write16CnCHAR(0, 0, 2, "Pa:");
        Lcd12864_Write16CnCHAR(0, 0, 4, "Pb:");
        Lcd12864_Write16CnCHAR(0, 0, 6, "Pc:");
        for (int i = 0; i < 4; i++)
        {
            Lcd12864_Write16CnCHAR(0, 100, 2 * i, "kw");
        }
        xianshishuju2(HT7038_buf1[10]);                 ////有功率数据
        display_ASCIIstring_8x16(1, 45, zifu_dian);     // 29
        display_graphic_8x16(1, 69, dian);              // 36
        display_ASCIIstring_8x16(1, 76, &zifu_dian[3]); // 44
        xianshishuju2(HT7038_buf1[7]);                  // 有功率数据
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
void screenbase6() // 轮询6界面
{

    Lcd12864_Write16CnCHAR(0, 0, 0, "I△:");
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

    xianshishuju(HT7038_buf1[4]); // 电流数据
    display_ASCIIstring_8x16(3, 91, zifu_dian);
    xianshishuju(HT7038_buf1[5]);
    display_ASCIIstring_8x16(5, 91, zifu_dian);
    xianshishuju(HT7038_buf1[6]);
    display_ASCIIstring_8x16(7, 91, zifu_dian);
    xianshishuju(HT7038_buf1[1]); // 电压数据
    display_ASCIIstring_8x16(3, 27, zifu_dian);
    xianshishuju(HT7038_buf1[2]);
    display_ASCIIstring_8x16(5, 27, zifu_dian);
    xianshishuju(HT7038_buf1[3]);
    display_ASCIIstring_8x16(7, 27, zifu_dian);
}
/***************************新增*********************************/
void screenbase7() // 轮询7界面   无功功率
{
    // if(F_Dataval==0)
    {
        Lcd12864_Write16CnCHAR(0, 0, 0, "Qs:"); // 总
        Lcd12864_Write16CnCHAR(0, 0, 2, "Qa:");
        Lcd12864_Write16CnCHAR(0, 0, 4, "Qb:");
        Lcd12864_Write16CnCHAR(0, 0, 6, "Qc:");
        for (int i = 0; i < 4; i++)
        {
            Lcd12864_Write16CnCHAR(0, 100, 2 * i, "var");
        }
        xianshishuju2(HT7038_buf1[19]);                 // 有功率数据
        display_ASCIIstring_8x16(1, 45, zifu_dian);     // 29    //新增要改
        display_graphic_8x16(1, 69, dian);              // 36
        display_ASCIIstring_8x16(1, 76, &zifu_dian[3]); // 44
        xianshishuju2(HT7038_buf1[20]);                 // 有功率数据
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
void screenbase8() // 轮询8界面   视在功率
{
    // if(F_Dataval==0)
    {
        Lcd12864_Write16CnCHAR(0, 0, 0, "Ss:"); // 总
        Lcd12864_Write16CnCHAR(0, 0, 2, "Sa:");
        Lcd12864_Write16CnCHAR(0, 0, 4, "Sb:");
        Lcd12864_Write16CnCHAR(0, 0, 6, "Sc:");
        for (int i = 0; i < 4; i++)
        {
            Lcd12864_Write16CnCHAR(0, 100, 2 * i, "VA");
        }
        xianshishuju2(HT7038_buf1[23]);                 // 有功率数据
        display_ASCIIstring_8x16(1, 45, zifu_dian);     // 29    //新增要改
        display_graphic_8x16(1, 69, dian);              // 36
        display_ASCIIstring_8x16(1, 76, &zifu_dian[3]); // 44
        xianshishuju2(HT7038_buf1[24]);                 // 有功率数据
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
void screenbase9() // 轮询9界面   无功电能
{
    // if(F_Dataval==0)
    {
        //		   		clear_screen();
        // 有功率数据
        Lcd12864_Write16CnCHAR(0, 0, 0, "Qs:"); // 总
        Lcd12864_Write16CnCHAR(0, 0, 2, "Qa:");
        Lcd12864_Write16CnCHAR(0, 0, 4, "Qb:");
        Lcd12864_Write16CnCHAR(0, 0, 6, "Qc:");
        for (int i = 0; i < 4; i++)
        {
            Lcd12864_Write16CnCHAR(0, 95, 2 * i, "VARh");
        }

        xianshishuju2(HT7038_buf1[27]);                 // 有功率数据
        display_ASCIIstring_8x16(1, 40, zifu_dian);     // 29    //新增要改
        display_graphic_8x16(1, 64, dian);              // 36
        display_ASCIIstring_8x16(1, 71, &zifu_dian[3]); // 44
        xianshishuju2(HT7038_buf1[28]);                 // 有功率数据
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

void screenbase10() // 轮询10界面   有功需量
{
    // if(F_Dataval==0)
    {
        Lcd12864_Write16CnCHAR(0, 0, 0, "Pds:");
        Lcd12864_Write16CnCHAR(0, 0, 2, "Qds:");
        Lcd12864_Write16CnCHAR(0, 0, 4, "Sds:");
        Lcd12864_Write16CnCHAR(0, 5, 6, "计价:");
        Lcd12864_Write16CnCHAR(0, 100, 6, "元");
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
void screenbase11() // 轮询11界面   无功需量
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
void screenbase12() // 轮询12界面   视在需量
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
void screenbase13() // 轮询13界面   功率四象限指示，频率 电压三相不平衡度，电流三相不平衡度
{
}

// typedef struct meun{
//	char *NAME;
//	  unsigned char (*A)[6]; // 使用指向数组的指针
//	unsigned char *value;
//     unsigned char array_size;
//	void (*func)(void);
// } meuntype;
struct smainmenu
{
    char *NAME;
    void (*func)(void);
};
void mainmenu() // 主菜单
{
    //	struct smainmenu smenu[]={
    //	{"保护设置",},
    //			{"保护设置",},
    //
    //	};
    Lcd12864_Write16CnCHAR(0, 40, 0, "主菜单");
    //	Lcd12864_Write16CnCHAR(0,2,2,"第一象限");

    switch (a1)
    {
    case 0:
    {
        Lcd12864_Write16CnCHAR(1, 0, 2, "保护设置");
        Lcd12864_Write16CnCHAR(0, 0, 4, "参数设置");
        Lcd12864_Write16CnCHAR(0, 0, 6, "校准设置");
        Lcd12864_Write16CnCHAR(0, 64, 2, "电力品质");
        Lcd12864_Write16CnCHAR(0, 64, 4, "越限报警");
        Lcd12864_Write16CnCHAR(0, 64, 6, "事件记录");
    }
    break;
    case 1:
    {
        Lcd12864_Write16CnCHAR(0, 0, 2, "保护设置");
        Lcd12864_Write16CnCHAR(1, 0, 4, "参数设置");
        Lcd12864_Write16CnCHAR(0, 0, 6, "校准设置");
        Lcd12864_Write16CnCHAR(0, 64, 2, "电力品质");
        Lcd12864_Write16CnCHAR(0, 64, 4, "越限报警");
        Lcd12864_Write16CnCHAR(0, 64, 6, "事件记录");
    }
    break;
    case 2:
    {
        Lcd12864_Write16CnCHAR(0, 0, 2, "保护设置");
        Lcd12864_Write16CnCHAR(0, 0, 4, "参数设置");
        Lcd12864_Write16CnCHAR(1, 0, 6, "校准设置");
        Lcd12864_Write16CnCHAR(0, 64, 2, "电力品质");
        Lcd12864_Write16CnCHAR(0, 64, 4, "越限报警");
        Lcd12864_Write16CnCHAR(0, 64, 6, "事件记录");
    }
    break;
    case 3:
    {
        Lcd12864_Write16CnCHAR(0, 0, 2, "保护设置");
        Lcd12864_Write16CnCHAR(0, 0, 4, "参数设置");
        Lcd12864_Write16CnCHAR(0, 0, 6, "校准设置");
        Lcd12864_Write16CnCHAR(1, 64, 2, "电力品质");
        Lcd12864_Write16CnCHAR(0, 64, 4, "越限报警");
        Lcd12864_Write16CnCHAR(0, 64, 6, "事件记录");
    }
    break;
    case 4:
    {
        Lcd12864_Write16CnCHAR(0, 0, 2, "保护设置");
        Lcd12864_Write16CnCHAR(0, 0, 4, "参数设置");
        Lcd12864_Write16CnCHAR(0, 0, 6, "校准设置");
        Lcd12864_Write16CnCHAR(0, 64, 2, "电力品质");
        Lcd12864_Write16CnCHAR(1, 64, 4, "越限报警");
        Lcd12864_Write16CnCHAR(0, 64, 6, "事件记录");
    }
    break;
    case 5:
    {
        Lcd12864_Write16CnCHAR(0, 0, 2, "保护设置");
        Lcd12864_Write16CnCHAR(0, 0, 4, "参数设置");
        Lcd12864_Write16CnCHAR(0, 0, 6, "校准设置");
        Lcd12864_Write16CnCHAR(0, 64, 2, "电力品质");
        Lcd12864_Write16CnCHAR(0, 64, 4, "越限报警");
        Lcd12864_Write16CnCHAR(1, 64, 6, "事件记录");
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

    if (key == KEY_AFFIRM_PRES) // 确认之后要加数据比较，有变更发送数据
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
            F_MAINormenu = 5; // 电能参数
            break;
        case 3:
        {
            USART_LCD_Transmit(1, 6);

            USART_LCD_Transmit(1, 6);
            F_MAINormenu = 8;
        } // 电力品质
        break;
        case 4:
            F_MAINormenu = 9; // 需量查看
            break;
        case 5:
            USART_LCD_Transmit(1, 7);
            F_MAINormenu = 4; // 事件记录

            break;
        default:
            break;
        }
        /* USER CODE END WHILE */

        /* USER CODE BEGIN 3 */
    }
}
void Power_parameters() // 电能参数
{
    Lcd12864_Write16CnCHAR(0, 40, 0, "电能参数");
    switch (a)
    {
    case 0:
    {
        Lcd12864_Write16CnCHAR(1, 0, 2, "有功电能");
        Lcd12864_Write16CnCHAR(0, 0, 4, "无功电能");
        Lcd12864_Write16CnCHAR(0, 0, 6, "总电能");
    }
    break;
    case 1:
    {
        Lcd12864_Write16CnCHAR(0, 0, 2, "有功电能");
        Lcd12864_Write16CnCHAR(1, 0, 4, "无功电能");
        Lcd12864_Write16CnCHAR(0, 0, 6, "总电能");
    }
    break;
    case 2:
    {
        Lcd12864_Write16CnCHAR(0, 0, 2, "有功电能");
        Lcd12864_Write16CnCHAR(0, 0, 4, "无功电能");
        Lcd12864_Write16CnCHAR(1, 0, 6, "总电能");
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
            //		if(F_Y==4) F_Y=5;        //跳出结构体菜单
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

    else if (key == KEY_AFFIRM_PRES) // 确认之后要加数据比较，有变更发送数据
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

void power_quality() // 电力品质
{

    if (current_page == 0 && F_Dataval == 0 && f_f != 0)
    {
        Lcd12864_Write14CnCHAR(0, 30, 2, "正在计算......");
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

        Lcd12864_Write14CnCHAR(0, 0, 0, "电压平衡率");
        Lcd12864_Write16CnCHAR(0, 0, 2, "VUB:"); // 三项电压不平整度
        disp_data(40, 2, 16, HT7038_buf1[44]);
        Lcd12864_Write14CnCHAR(0, 0, 4, "电流平衡率");
        Lcd12864_Write16CnCHAR(0, 0, 6, "IUB:"); // 三项电压不平整度
        disp_data(40, 6, 16, HT7038_buf1[45]);
        Lcd12864_Write16CnCHAR(0, 79, 2, " ");
    }
    else if (current_page == 1) // 各相电压谐波
    {
        Lcd12864_Write14CnCHAR(0, 0, 0, "电压总谐波含有率");
        Lcd12864_Write16CnCHAR(0, 0, 2, "VaTHD:");
        Lcd12864_Write16CnCHAR(0, 0, 4, "VbTHD:");
        Lcd12864_Write16CnCHAR(0, 0, 6, "VcTHD:");
        for (int i = 0; i < 3; i++)
        {
            disp_data(50, 2 + 2 * i, 16, HT7038_buf1[280 + i]);
        }
    }

    else if (current_page == 2) // 各相电压谐波
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
    else if (current_page == 3) // 各相电压谐波
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
    else if (current_page == 4) // 各相电压谐波
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
    else if (current_page == 5) // 各相电压谐波
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
    else if (current_page == 6) // 各相电压谐波
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
    else if (current_page == 7) // 各相电压谐波
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
    else if (current_page == 8) // 各相电压谐波
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
    else if (current_page == 9) // 各相电压谐波
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
    else if (current_page == 10) // 各相电压谐波
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
    else if (current_page == 11) // 各相电压谐波
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

    else if (current_page == -1) // 电流谐波
    {
        Lcd12864_Write14CnCHAR(0, 0, 0, "电流总谐波含有率");
        Lcd12864_Write16CnCHAR(0, 0, 2, "IaTHD:");
        Lcd12864_Write16CnCHAR(0, 0, 4, "IbTHD:");
        Lcd12864_Write16CnCHAR(0, 0, 6, "IcTHD:");
        for (int i = 0; i < 3; i++)
        {
            disp_data(50, 2 + 2 * i, 16, HT7038_buf1[283 + i]);
        }
    }
    else if (current_page == -2) // 各相电压谐波
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
    else if (current_page == -3) // 各相电压谐波
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
    else if (current_page == -4) // 各相电压谐波
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
    else if (current_page == -5) // 各相电压谐波
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
    else if (current_page == -6) // 各相电压谐波
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
    else if (current_page == -7) // 各相电压谐波
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
    else if (current_page == -8) // 各相电压谐波
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
    else if (current_page == -9) // 各相电压谐波
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
    else if (current_page == -10) // 各相电压谐波
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
    else if (current_page == -11) // 各相电压谐波
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

    else if (key == KEY_RIGHRT_PRES) // 确认之后要加数据比较，有变更发送数据
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

    else if (key == KEY_RIGHRT_PRES) // 确认之后要加数据比较，有变更发送数据
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

    switch (a) // a是按了几次 d是判断出来的有几行    //这个switch是选择是哪一行
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
    else if (key == KEY_AFFIRM_PRES) // 确认之后要加数据比较，有变更发送数据
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
void meun_protect1() // 保护界面1
{
    meunpro meunprotect[] = {
        {"1漏电告警", &F_trip_ld},
        {"2自动定档", &F_auto_ld},
        {"3突变保护", &F_TB_trip},
        {"4特波保护", &F_Special_wave},
    };
    int totalItems = sizeof(meunprotect) / sizeof(meunprotect[0]);
    displayMenupro(meunprotect, totalItems, 0);

    if (F_trip_ld == 0)
        ctrlword[3] &= 0xFC; // 控制字分析用于发送
    if (F_trip_ld == 1)
    {
        ctrlword[3] &= 0xFC;
        ctrlword[3] += 0x02;
    }
    ctrlword4_analyze();
}
void meun_protect2() // 保护界面2
{
    meunpro meunprotect[] = {
        {"5断零保护", &F_trip_QL},
        {"6过电压保护", &F_trip_gy},
        {"7欠电压保护", &F_trip_qy},
        {"8断相保护", &F_trip_QX},
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
void meun_protect3() // 保护界面3
{

    meunpro meunprotect[] = {
        {"9失压保护", &F_trip_sy},
        {"10过流保护", &F_trip_gl},
        {"11短延保护", &F_ip},
        {"12瞬时保护", &F_ip_3},
    };
    int totalItems = sizeof(meunprotect) / sizeof(meunprotect[0]);
    displayMenupro(meunprotect, totalItems, 0);

    if (F_trip_gl == 1)
        ctrlword[1] |= 0x01;
    if (F_trip_gl == 0)
        ctrlword[1] &= (~0x01);
}
void meun_protect4() // 保护界面4
{

    meunpro meunprotect[] = {
        //		{"13校准档位",&jiaozhun},
        {"13上电合闸", &shangdian},
        {"14漏电合闸", &LD_hezha},
        {"15电压合闸", &DY_hezha},
        {"16电流合闸", &DL_hezha},
    };
    int totalItems = sizeof(meunprotect) / sizeof(meunprotect[0]);
    displayMenupro(meunprotect, totalItems, 0);
}
void meun_protect5() // 保护界面5
{

    meunpro meunprotect[] = {
        //		{"17电流合闸",&DL_hezha},
        {"17温度保护", &wendu},
        {"18通信方式", &F_TX},

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
    Lcd12864_Write16CnCHAR(0, 100, 2, "次");
    Lcd12864_Write16CnCHAR(0, 0, 4, meundata[2 * current_page + 1].NAME);
    Lcd12864_Write16CnCHAR(0, 100, 6, "次");
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
    Lcd12864_Write16CnCHAR(0, 35, 0, "故障记录");
    switch (current_page)
    {
    case 0:
        Lcd12864_Write16CnCHAR(1, 5, 3, "跳闸次数"); // 跳闸次数
        Lcd12864_Write16CnCHAR(0, 5, 5, "故障信息"); // 故障信息
        break;
    case 1:
        Lcd12864_Write16CnCHAR(0, 5, 3, "跳闸次数"); // 跳闸次数
        Lcd12864_Write16CnCHAR(1, 5, 5, "故障信息"); // 故障信息
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
    else if (key == KEY_AFFIRM_PRES) // 确认之后要加数据比较，有变更发送数据
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

void meun_data() // 跳闸记录界面
{
    Num_tripall = 1;
    Num_clearall = 2;
    meund meundata[] = {
        {"1 总跳闸次数", Num_tripall},
        {"2 数据清零次数", Num_clearall},
        {"3 闭锁跳闸次数", Num_triplock},
        {"4 漏电跳闸次数", Num_tripleak},
        {"5电流跳闸次数", Num_tripcur},
        {"6 过压跳闸次数", Num_tripvol},
        {"7手动闭锁跳闸次数", Num_triphand},
        {"8 按键跳闸次数", Num_triptest},
        {"9 短延跳闸次数", Num_tripdelay},
        {"10 短瞬跳闸次数 ", Num_tripinstant},
        {"11 欠压跳闸次数 ", Num_leakover},
        {"12 缺相跳闸次数 ", Num_leakprotect},
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

    if (key == KEY_DOWN_PRES) // 校准切换（上下写反了）
    {
        F_jiaozhuned = 0;
        F_adjustbegin = 0;
        if (current_page > 0)
            current_page--;
        else
            current_page = 2;
        clear_screen();
    }
    else if (key == KEY_UP_PRES) // 封面进校准界面（左右写反了）
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
{ // 校准界面

    meunadj meunadjust[] = {
        {"漏电校准", "\r\r  开始漏电校准", "\r\r 正在漏电校准...", "\r\r 漏电校准完成    "},
        {"电压校准", "\r\r  开始电压校准", "\r\r 正在电压校准...", "\r\r 电压校准完成    "},
        {"125A电流校准", "\r\r  开始电流校准", "\r\r 正在电流校准...", "\r\r 电流校准完成    "},
        {"250A电流校准", "\r\r  开始电流校准", "\r\r 正在电流校准...", "\r\r 电流校准完成    "},
        {"400A电流校准", "\r\r  开始电流校准", "\r\r 正在电流校准...", "\r\r 电流校准完成    "},
        {"630A电流校准", "\r\r  开始电流校准", "\r\r 正在电流校准...", "\r\r 电流校准完成    "},
        {"800A电流校准", "\r\r  开始电流校准", "\r\r 正在电流校准...", "\r\r 电流校准完成    "},

    };
    int total_items = sizeof(meunadjust) / sizeof(meunadjust[0]);
    displayMenuadj(meunadjust, total_items);
}
void fenzhaing() // 正在分闸中界面
{
    Lcd12864_Write16CnCHAR(0, 32, 0, "\r  正在分闸...");
    if (isfenzha == 0)
    {
        F_MAINormenu = 0;
    }
}
void hezhaing() // 正在合闸中界面
{
    Lcd12864_Write16CnCHAR(0, 32, 0, "\r  正在合闸...");
    if (isfenzha == 1)
    {
        F_MAINormenu = 0;
    }
}
void problemdisp() // 故障显示
{
    if (F_gz_disp == A_qy || F_gz_disp == B_qy || F_gz_disp == C_qy) // 欠压故障
    {
        xianshishuju(gz_disp);

        Lcd12864_Write16CnCHAR(0, 32, 0, "欠压故障\r 故障值");

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

        Lcd12864_Write16CnCHAR(0, 0, 4, " 重合闸次数:");
        xianshishuju(F_ch);
        display_ASCIIstring_8x16(5, 110, zifu_dian);

        Lcd12864_Write16CnCHAR(0, 0, 6, " 欠压档位:");
        display_ASCIIstring_8x16(7, 88, DIANYA_1[Vol_q]);
    }
    if (F_gz_disp == A_QX || F_gz_disp == B_QX || F_gz_disp == C_QX) // 缺相
    {

        xianshishuju(gz_disp);
        Lcd12864_Write16CnCHAR(0, 32, 0, "缺相故障\r 故障值");

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

        Lcd12864_Write16CnCHAR(0, 0, 4, " 重合闸次数:");
        xianshishuju(F_ch);
        display_ASCIIstring_8x16(5, 110, zifu_dian);
    }
    // 过压“GY”
    if (F_gz_disp == A_gy || F_gz_disp == B_gy || F_gz_disp == C_gy)
    {

        xianshishuju(gz_disp);

        Lcd12864_Write16CnCHAR(0, 32, 0, "过压故障\r 故障值");

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

        Lcd12864_Write16CnCHAR(0, 0, 4, " 重合闸次数:");
        xianshishuju(F_ch);

        display_ASCIIstring_8x16(5, 110, zifu_dian);
        Lcd12864_Write16CnCHAR(0, 0, 6, " 过压档位:");
        display_ASCIIstring_8x16(7, 88, DIANYA[Vol_g]);
    }
    // 漏电“ld”
    if (F_gz_disp == L_hb)
    {

        xianshishuju(gz_disp);
        Lcd12864_Write16CnCHAR(0, 32, 0, "漏电故障\r 故障值      mA");
        display_ASCIIstring_8x16(3, 76, zifu_dian);
        Lcd12864_Write16CnCHAR(0, 0, 4, " 重合闸次数:");
        xianshishuju(F_ch);

        display_ASCIIstring_8x16(5, 110, zifu_dian);
        Lcd12864_Write16CnCHAR(0, 0, 6, " 额定漏电:");
        display_ASCIIstring_8x16(7, 88, dianliu[D_LCur]);
    }
    // 过流“GL”
    if ((F_gz_disp > L_hb) && (F_gz_disp < Gz_TD))
    {

        SET_D_Cur = D_Cur;
        I_VAL_handle();
        //                gz_disp1=SET_I_VAL ;
        xianshishuju(gz_disp);

        Lcd12864_Write16CnCHAR(0, 32, 0, "过流故障\r 故障值");
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

        Lcd12864_Write16CnCHAR(0, 0, 4, " 重合闸次数:");
        xianshishuju(F_ch);

        display_ASCIIstring_8x16(5, 110, zifu_dian);
        Lcd12864_Write16CnCHAR(0, 0, 6, " 电流档位:    ");

        I_VAL_handle();

        xianshishuju_dianliu(SET_I_VAL);

        display_ASCIIstring_8x16(7, 92, zifu_dian); // 电流保存
    }
    // 停电“tD”
    if (F_gz_disp == Gz_TD)
    {

        Lcd12864_Write16CnCHAR(0, 32, 0, "停电故障");
    }
    // 手动和短路为未知“UN”
    if (F_gz_disp == FZ_UK)
    {

        Lcd12864_Write16CnCHAR(0, 32, 0, "未知故障");
    }
    // 按键“AJ”
    if (F_gz_disp == FZ_AJ)
    {

        Lcd12864_Write16CnCHAR(0, 32, 0, "按键分闸");
    }
    // 远程“YC”
    if (F_gz_disp == FZ_YC)
    {

        Lcd12864_Write16CnCHAR(0, 32, 0, "远程分闸");
    }
    if (F_gz_disp == Gz_QL)
    {

        Lcd12864_Write16CnCHAR(0, 32, 0, "缺零分闸");
    }
    if (F_gz_disp == Tem_IN_N)
    {
        Lcd12864_Write16CnCHAR(0, 32, 0, "N->过温分闸");
    }
    if (F_gz_disp == Tem_IN_A)
    {

        Lcd12864_Write16CnCHAR(0, 32, 0, "A->过温分闸");
    }
    if (F_gz_disp == Tem_IN_B)
    {

        Lcd12864_Write16CnCHAR(0, 32, 0, "B->过温分闸");
    }
    if (F_gz_disp == Tem_IN_C)
    {
        Lcd12864_Write16CnCHAR(0, 32, 0, "C->过温分闸");
    }
    if (F_gz_disp == Tem_OUT_N)
    {
        Lcd12864_Write16CnCHAR(0, 32, 0, "N<-过温分闸");
    }
    if (F_gz_disp == Tem_OUT_A)
    {

        Lcd12864_Write16CnCHAR(0, 32, 0, "A<-过温分闸");
    }
    if (F_gz_disp == Tem_OUT_B)
    {

        Lcd12864_Write16CnCHAR(0, 32, 0, "B<-过温分闸");
    }
    if (F_gz_disp == Tem_OUT_C)
    {
        Lcd12864_Write16CnCHAR(0, 32, 0, "C<-过温分闸");
    }
}

void timechange() // 日期和时间界面
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
        USART_LCD_Transmit(57, 1); // 发送数据
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
int mimaset() // 密码界面
{

    if (qiehuan == 0)
    {
        Lcd12864_Write16CnCHAR(0, 33, 0, "输入密码");
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
            Lcd12864_Write16CnCHAR(0, 32, 4, "杠");
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
            Lcd12864_Write16CnCHAR(0, 49, 4, "杠"); // 显示选中的线
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
            Lcd12864_Write16CnCHAR(0, 66, 4, "杠");
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
                    F_MAINormenu = 10; // 从这里修改密码之后去什么界面
                    clear_screen();
                    return 0;
                }
                else
                    qiehuan = 1;
                clear_screen();
                return 0;
            }

            Lcd12864_Write16CnCHAR(0, 83, 4, "杠");
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
        Lcd12864_Write16CnCHAR(0, 33, 3, "密码错误");
        if (key == KEY_AFFIRM_PRES)
        {
            clear_screen();
            current_page = 0;
            qiehuan = 0;
        }
    }
}
void menu_mimaset() // 修改密码界面和通信地址
{
    unsigned char mima0[2], mima1[2], mima2[2], mima3[2];
    Lcd12864_Write16CnCHAR(0, 0, 0, "19修改密码\r");
    display_graphic_8x16(1, 86, maohao);
    mima0[0] = mima_set_compare[0] + 0x30;
    mima0[1] = '\0';
    mima1[0] = mima_set_compare[1] + 0x30;
    mima1[1] = '\0';
    mima2[0] = mima_set_compare[2] + 0x30;
    mima2[1] = '\0';
    mima3[0] = mima_set_compare[3] + 0x30;
    mima3[1] = '\0';
    Lcd12864_Write16CnCHAR(0, 0, 3, "20通信地址\r");
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
            for (int i = 0; i < 4; i++) // 当密码设定完成才确认设定的密码防止瞎设置
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
void judge() // 挡位改动判断
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
        USART_LCD_Transmit(57, 1); // 发送数据

        // 发送数据
    }
}
void updata_c() // 如有改动更新档位函数
{
    TH_LCurtemp = TH_LCur;
    ctrlwordtemp[3] = ctrlword[3];             // 控制字4
    Vol_gtemp = Vol_g;                         // 过压挡位
    Vol_qtemp = Vol_q;                         // 欠压挡位
    D_SY_yanshitemp = D_SY_yanshi;             // 失压延时
    D_GY_yanshitemp = D_GY_yanshi;             // 过压延时
    D_QY_yanshitemp = D_QY_yanshi;             // 欠压延时
    D3_Curtemp = D3_Cur;                       // 瞬时挡位
    D_Curtemp = D_Cur;                         // 过流挡位
    TH_Long_Curtemp = TH_Long_Cur;             // 过流时间
    D2_Curtemp = D2_Cur;                       // 短延挡位
    TH_DLtemp = TH_DL;                         // 短延时间
    baudtemp = baud;                           // 通信速率
    Type_Curtemp = Type_Cur;                   // 壳架设置
    tim_y3temp = tim_y3;                       // 日期 年
    tim_m3temp = tim_m3;                       // 日期 月
    tim_d3temp = tim_d3;                       // 日期 日
    tim_h3temp = tim_h3;                       // 时间 时
    tim_f3temp = tim_f3;                       // 时间 分
    tim_s3temp = tim_s3;                       // 时间 秒
    TH_TEM_UPtemp = TH_TEM_UP;                 // 高温分闸
    TH_TEM_DOWNtemp = TH_TEM_DOWN;             // 低温合闸
    mima_settemp[0] = mima_set[0];             // 密码
    mima_settemp[1] = mima_set[1];             // 密码
    mima_settemp[2] = mima_set[2];             // 密码
    mima_settemp[3] = mima_set[3];             // 密码
    self_addr_codetemp[0] = self_addr_code[0]; // 通信地址字节0
    self_addr_codetemp[1] = self_addr_code[1]; // 通信地址字节1
    self_addr_codetemp[2] = self_addr_code[2]; // 通信地址字节2
    self_addr_codetemp[3] = self_addr_code[3]; // 通信地址字节3
    self_addr_codetemp[4] = self_addr_code[4]; // 通信地址字节4
    self_addr_codetemp[5] = self_addr_code[5]; // 通信地址字节5
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
void USART_LCD_Transmit(unsigned char len, unsigned char ch) // 发送函数 三个通道， 分别为实时显示数据和挡位，0为实时显示数据，1为挡位，2漏电，3校准相关
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

    case 2: // 漏电分闸合闸
        DI3 = 0x32;
        DI2 = 0x01;
        DI0 = 0x03;
        switch (F_LEAK_OPEN_CLOSE) // F_LEAK_OPEN_CLOSE  1是漏电2是分闸3是合闸          F_open==1是高温分闸,F_open==0是手动分闸
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
            } // 还没改，温度处理那，现在写死的warray_tmp[4]=2;array_tmp[5]=122
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
            break; // 手动分闸
        case 3:
            array_tmp[0] = 0;
            array_tmp[1] = 0;
            array_tmp[2] = 1;
            array_tmp[3] = 0;
            array_tmp[4] = 1;
            array_tmp[5] = 0;
            array_tmp[6] = 0;
            break; // 手动合闸
        case 4:
            array_tmp[0] = 0;
            array_tmp[1] = 0;
            array_tmp[2] = 1;
            array_tmp[3] = 0;
            array_tmp[4] = 0;
            array_tmp[5] = 0;
            array_tmp[6] = 1;
            break; // 低温合闸
        }
        Write_or_Readresponse(0x10, len, array_tmp);
        break;
    case 3: // 校准相关
        DI3 = 0x04;
        DI2 = 0x10;
        DI0 = 0x10;
        array_tmp[0] = Cal_state;
        array_tmp[1] = 1;
        Write_or_Readresponse(0x10, len, array_tmp);
        break;
    case 4: // 故障确认
        DI3 = 0x05;
        DI2 = 0x10;
        DI0 = 0x01;
        array_tmp[0] = 1;
        F_GUZHANG = 1; // 实现退出清屏
        Write_or_Readresponse(0x10, len, array_tmp);
        break;

    case 5: // 初始化发送
        DI3 = 0x06;
        DI2 = 0x10;
        DI0 = 0x01;
        array_tmp[0] = 1;

        Write_or_Readresponse(0x10, len, array_tmp);
        break;

    case 6: // 请求谐波
        DI3 = 0x08;
        DI2 = 0x10;
        DI0 = 0x01;
        array_tmp[0] = 1;

        Write_or_Readresponse(0x10, len, array_tmp);
        break;

    case 7: // 请求故障记录
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
void UART_LCD_process(void) // 串口接收函数，档位信息和实时数据
{

    // data_array0，1，2，3元素为识别码，从4开始是数据
    if (Lcd_data_array[read_ptr][0] == 0X90)
    {
        ctrlword[3] = Lcd_data_array[read_ptr][4];                                          // 控制字4
        Vol_g = Lcd_data_array[read_ptr][5];                                                // 过压挡位
        Vol_q = Lcd_data_array[read_ptr][6];                                                // 欠压挡位
        D_SY_yanshi = Lcd_data_array[read_ptr][7];                                          // 失压延时
        D_GY_yanshi = Lcd_data_array[read_ptr][8];                                          // 过压延时
        D_QY_yanshi = Lcd_data_array[read_ptr][9];                                          // 欠压延时
        D3_Cur = Lcd_data_array[read_ptr][10];                                              // 瞬时挡位
        D_Cur = Lcd_data_array[read_ptr][11];                                               // 过流挡位
        TH_Long_Cur = Lcd_data_array[read_ptr][12];                                         // 过流时间
        D2_Cur = Lcd_data_array[read_ptr][13];                                              // 短延挡位
        TH_DL = Lcd_data_array[read_ptr][14];                                               // 短延时间
        baud = (Lcd_data_array[read_ptr][15] << 8) + (Lcd_data_array[read_ptr][16]);        // 通信速率
        Type_Cur = (Lcd_data_array[read_ptr][17] << 8) + (Lcd_data_array[read_ptr][18]);    // 壳架设置
        tim_y3 = (Lcd_data_array[read_ptr][19] << 8) + (Lcd_data_array[read_ptr][20]);      // 日期 年
        tim_m3 = (Lcd_data_array[read_ptr][21] << 8) + (Lcd_data_array[read_ptr][22]);      // 日期 月
        tim_d3 = (Lcd_data_array[read_ptr][23] << 8) + (Lcd_data_array[read_ptr][24]);      // 日期 日
        tim_h3 = (Lcd_data_array[read_ptr][25] << 8) + (Lcd_data_array[read_ptr][26]);      // 时间 时
        tim_f3 = (Lcd_data_array[read_ptr][27] << 8) + (Lcd_data_array[read_ptr][28]);      // 时间 分
        tim_s3 = (Lcd_data_array[read_ptr][29] << 8) + (Lcd_data_array[read_ptr][30]);      // 时间 秒
        TH_TEM_UP = (Lcd_data_array[read_ptr][31] << 8) + (Lcd_data_array[read_ptr][32]);   // 高温分闸
        TH_TEM_DOWN = (Lcd_data_array[read_ptr][33] << 8) + (Lcd_data_array[read_ptr][34]); // 低温合闸
        mima_set[0] = Lcd_data_array[read_ptr][35];                                         // 密码
        mima_set[1] = Lcd_data_array[read_ptr][36];                                         // 密码
        mima_set[2] = Lcd_data_array[read_ptr][37];                                         // 密码
        mima_set[3] = Lcd_data_array[read_ptr][38];                                         // 密码
        self_addr_code[0] = Lcd_data_array[read_ptr][39];                                   // 通信地址字节0
        self_addr_code[1] = Lcd_data_array[read_ptr][40];                                   // 通信地址字节1
        self_addr_code[2] = Lcd_data_array[read_ptr][41];                                   // 通信地址字节2
        self_addr_code[3] = Lcd_data_array[read_ptr][42];                                   // 通信地址字节3
        self_addr_code[4] = Lcd_data_array[read_ptr][43];                                   // 通信地址字节4
        self_addr_code[5] = Lcd_data_array[read_ptr][44];                                   // 通信地址字节5
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
        HT7038_buf11[15] = ((Lcd_data_array[read_ptr][18] << 16) & 0xFF0000) | ((Lcd_data_array[read_ptr][19] << 8) & 0xFF00) | Lcd_data_array[read_ptr][20]; // an;有功电能
        HT7038_buf11[16] = ((Lcd_data_array[read_ptr][21] << 16) & 0xFF0000) | ((Lcd_data_array[read_ptr][22] << 8) & 0xFF00) | Lcd_data_array[read_ptr][23]; // bn;
        HT7038_buf11[17] = ((Lcd_data_array[read_ptr][24] << 16) & 0xFF0000) | ((Lcd_data_array[read_ptr][25] << 8) & 0xFF00) | Lcd_data_array[read_ptr][26]; // cn;
        HT7038_buf11[18] = ((Lcd_data_array[read_ptr][27] << 16) & 0xFF0000) | ((Lcd_data_array[read_ptr][28] << 8) & 0xFF00) | Lcd_data_array[read_ptr][29]; // alln;
        HT7038_buf11[7] = ((Lcd_data_array[read_ptr][30] << 8) & 0xFF00) | Lcd_data_array[read_ptr][31];                                                      // a有功;
        HT7038_buf11[8] = ((Lcd_data_array[read_ptr][32] << 8) & 0xFF00) | Lcd_data_array[read_ptr][33];                                                      // b有功;
        HT7038_buf11[9] = ((Lcd_data_array[read_ptr][34] << 8) & 0xFF00) | Lcd_data_array[read_ptr][35];                                                      // c有功;
        HT7038_buf11[10] = ((Lcd_data_array[read_ptr][36] << 8) & 0xFF00) | Lcd_data_array[read_ptr][37];                                                     // all有功功率
        HT7038_buf11[11] = ((Lcd_data_array[read_ptr][38] << 8) & 0xFF00) | Lcd_data_array[read_ptr][39];                                                     // a功率因数;
        HT7038_buf11[12] = ((Lcd_data_array[read_ptr][40] << 8) & 0xFF00) | Lcd_data_array[read_ptr][41];                                                     // b功率因数;
        HT7038_buf11[13] = ((Lcd_data_array[read_ptr][42] << 8) & 0xFF00) | Lcd_data_array[read_ptr][43];                                                     // c功率因数;
        HT7038_buf11[14] = ((Lcd_data_array[read_ptr][44] << 8) & 0xFF00) | Lcd_data_array[read_ptr][45];                                                     // all功率因数;
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
    else if (Lcd_data_array[read_ptr][0] == 0x03) // 分合闸状态和故障显示相关
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
    else if (Lcd_data_array[read_ptr][0] == 0x04) // 校准相关
        F_jiaozhuned = Lcd_data_array[read_ptr][4];
    else if (Lcd_data_array[read_ptr][0] == 0x06) // 初始化相关
        F_initialization = Lcd_data_array[read_ptr][4];
    else if (Lcd_data_array[read_ptr][0] == 0x07) // 新增轮询
    {
        for (int i = 0; i < 24; i++)
        {
            HT7038_buf11[19 + i] = ((Lcd_data_array[read_ptr][4 + 2 * i] << 8) & 0xFF00) | Lcd_data_array[read_ptr][5 + 2 * i];
        }

        HT7038_buf11[43] = Lcd_data_array[read_ptr][52];                                                                                                      // 频率;
        HT7038_buf11[44] = ((Lcd_data_array[read_ptr][53] << 8) & 0xFF00) | Lcd_data_array[read_ptr][54];                                                     // 电压三相不平衡;
        HT7038_buf11[45] = ((Lcd_data_array[read_ptr][55] << 8) & 0xFF00) | Lcd_data_array[read_ptr][56];                                                     // 电流三相不平衡;
        HT7038_buf11[46] = Lcd_data_array[read_ptr][57];                                                                                                      // 功率四象限指示;
        HT7038_buf11[47] = ((Lcd_data_array[read_ptr][58] << 16) & 0xFF0000) | ((Lcd_data_array[read_ptr][59] << 8) & 0xFF00) | Lcd_data_array[read_ptr][60]; // 分时计量
    }

    else if (Lcd_data_array[read_ptr][0] == 0x08) // 谐波ua部分
    {
        for (int i = 0; i < 30; i++) // 100电压总谐波
        {
            HT7038_buf11[100 + i] = ((Lcd_data_array[read_ptr][4 + 2 * i] << 8) & 0xFF00) | Lcd_data_array[read_ptr][5 + 2 * i]; // all无功功率;
        }
        f_f = 2;
    }
    else if (Lcd_data_array[read_ptr][0] == 0x09) // 谐波ub部分
    {
        for (int i = 0; i < 30; i++) // 100电压总谐波
        {
            HT7038_buf11[130 + i] = ((Lcd_data_array[read_ptr][4 + 2 * i] << 8) & 0xFF00) | Lcd_data_array[read_ptr][5 + 2 * i]; // all无功功率;
        }
        f_f = 3;
    }
    else if (Lcd_data_array[read_ptr][0] == 0x0A) // 谐波uC部分
    {
        for (int i = 0; i < 30; i++) // 100电压总谐波
        {
            HT7038_buf11[160 + i] = ((Lcd_data_array[read_ptr][4 + 2 * i] << 8) & 0xFF00) | Lcd_data_array[read_ptr][5 + 2 * i]; // all无功功率;
        }
        f_f = 4;
    }
    else if (Lcd_data_array[read_ptr][0] == 0x0B) // 谐波IA部分
    {
        for (int i = 0; i < 30; i++) // 100电压总谐波
        {
            HT7038_buf11[190 + i] = ((Lcd_data_array[read_ptr][4 + 2 * i] << 8) & 0xFF00) | Lcd_data_array[read_ptr][5 + 2 * i]; // all无功功率;
        }
        f_f = 5;
    }

    else if (Lcd_data_array[read_ptr][0] == 0x0C) // 谐波IB部分
    {
        for (int i = 0; i < 30; i++) // 100电压总谐波
        {
            HT7038_buf11[220 + i] = ((Lcd_data_array[read_ptr][4 + 2 * i] << 8) & 0xFF00) | Lcd_data_array[read_ptr][5 + 2 * i]; // all无功功率;
        }
        f_f = 6;
    }
    else if (Lcd_data_array[read_ptr][0] == 0x0D) // 谐波IC部分
    {
        for (int i = 0; i < 36; i++) // 100电压总谐波
        {
            HT7038_buf11[250 + i] = ((Lcd_data_array[read_ptr][4 + 2 * i] << 8) & 0xFF00) | Lcd_data_array[read_ptr][5 + 2 * i]; // all无功功率;
        }
        f_f = 0;
        clear_screen();
    }
    else if (Lcd_data_array[read_ptr][0] == 0x0E) // 故障前十次
    {
        for (int i = 0; i < 10; ++i)
        {
            int base_index = 4 + (i * 9); // 计算每个故障记录的起始位置
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

    else if (Lcd_data_array[read_ptr][0] == 0x0F) // 故障后十次
    {
        for (int i = 0; i < 10; ++i)
        {
            int base_index = 4 + (i * 9); // 计算每个故障记录的起始位置
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
    // F_dataalarm_qy=(ctrlword[1]&0x80)>>7 ;//欠压保护及跳闸控制
    F_trip_qy = (ctrlword[1] & 0x40) >> 6;
    // F_dataalarm_gy=(ctrlword[1]&0x20)>>5 ;
    F_trip_gy = (ctrlword[1] & 0x10) >> 4;
    // F_dataalarm_xq=(ctrlword[1]&0x08)>>3;
    F_trip_QX = (ctrlword[1] & 0x04) >> 2;
    F_trip_gl = (ctrlword[1] & 0x01) >> 0;
}
void ctrlword3_analyze(void)
{
    F_trip_QL = (ctrlword[2] & 0x01) >> 0; // 缺零保护及跳闸控制
}
void ctrlword4_analyze(void)
{
    unsigned char F_GJ_FUNC_tmp, E2_arraymrnow_tmp[5];
    D_LCur = (ctrlword[3] >> 4); // 剩余电流档位，取出高四位
    //	TH_LCur=((ctrlword[3]&0x0C)>>2);//取出低两位  额定极限不驱动时间
    F_GJ_FUNC_tmp = (ctrlword[3] & 0x03); // 剩余电流报警时间

    if (D_LCur > 7)
    {
        D_LCur = 0x07;
        ctrlword[3] &= 0x0F;
        ctrlword[3] += (D_LCur << 4);
    }
}
/***电流过载值处理***/

void I_VAL_handle()
{
    // if(!disp_num)
    SET_D_Cur = D_Cur;
    // 电流框架等级为20~100A
    // 电流框架等级为60~250A

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
    // 电流框架等级为200~400A
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
    Lcd12864_Write16CnCHAR(0, 0, 0, "15日期修改\r");

    tim_y3 = sdatestructure.Year; // tim_y为十进制，要转换二进制
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
    Lcd12864_Write16CnCHAR(0, 0, 4, "16时间修改\r");
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
// 函数计算数组中 field1 不等于 15 的元素数量
int countNotEqual15(fault arr[], int size, int *min_index)
{
    int count = 0;
    *min_index = -1; // 初始值设为 -1 表示未找到
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
    int count = countNotEqual15(fault_buffer, 20, &min_index); // 调用函数计算数量

    if (count != 0)
    {
        Lcd12864_Write16CnCHAR(0, 0, 0, "近   次跳闸信息\r");
        value_to_ascii1(current_page + 1, zifu_dian);
        display_ASCIIstring_8x16(1, 25, zifu_dian);
        Lcd12864_Write16CnCHAR(0, 0, 2, "类型:");

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
        Lcd12864_Write16CnCHAR(0, 0, 4, "故障值:");
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
        Lcd12864_Write16CnCHAR(0, 20, 3, "无故障信息");
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
    char *NAME;            // 名字
    unsigned char (*A)[8]; // 使用指向数组的指针
    unsigned char *value;
    unsigned char array_size;
    //	int setting_up;   //上限值
    //	int setting_down;  //下限值
    //	int *setting_value;  //设定值指针
    //	enum type_unit type;      //单位符号
    //	bool   arrayORaccumulate;   //数组还是累加 0是累加，1是数组
    //	int array[4];
    //	  unsigned char (*A)[6]; // 使用指向数组的指针
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
// 将字符串中的电压值转换为整数
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
        exceeded[1] = true; // 电压超上限
        anyExceeded = true;
        waring_num++;
    }
    else
        exceeded[1] = false;
    if (HT7038_buf11[1] < lower_voltage || HT7038_buf11[2] < lower_voltage || HT7038_buf11[3] < lower_voltage)
    {
        exceeded[2] = true; // 电压超下限
        anyExceeded = true;
        waring_num++;
    }
    else
        exceeded[2] = false;
    if (HT7038_buf11[4] > upper_current || HT7038_buf11[5] > upper_current || HT7038_buf11[6] > upper_current)
    {
        exceeded[3] = true; // 电流超上限
        anyExceeded = true;
        waring_num++;
    }
    else
        exceeded[3] = false;
    if (HT7038_buf11[43] > upper_hz)
    {
        exceeded[4] = true; // 频率超上限
        anyExceeded = true;
        waring_num++;
    }
    else
        exceeded[4] = false;
    if (HT7038_buf11[43] < lower_hz)
    {
        exceeded[5] = true; // 频率超下限
        anyExceeded = true;
        waring_num++;
    }
    else
        exceeded[5] = false;
    if (HT7038_buf11[10] > upper_power)
    {
        exceeded[6] = true; // 功率超上限
        anyExceeded = true;
        waring_num++;
    }
    else
        exceeded[6] = false;
    if (max_value > upper_TEM)
    {
        exceeded[7] = true; // 进线超上限
        anyExceeded = true;
        waring_num++;
    }
    else
        exceeded[7] = false;
    if (max_value > lower_TEM)
    {
        exceeded[8] = true; // 出线超上限
        anyExceeded = true;
        waring_num++;
    }
    else
        exceeded[8] = false;
    if (HT7038_buf11[10] > upper_p)
    {
        exceeded[9] = true; // 有功功率超上限
        anyExceeded = true;
        waring_num++;
    }
    else
        exceeded[9] = false;
    if (HT7038_buf11[19] > upper_q)
    {
        exceeded[10] = true; // 无功功率超上限
        anyExceeded = true;
        waring_num++;
    }
    else
        exceeded[10] = false;
    if (HT7038_buf11[23] > upper_s)
    {
        exceeded[11] = true; // 视在功率超上限
        anyExceeded = true;
        waring_num++;
    }
    else
        exceeded[11] = false;
    if (HT7038_buf11[14] < Cos)
    {
        exceeded[12] = true; // 功率因数超下限
        anyExceeded = true;
        waring_num++;
    }
    else
        exceeded[12] = false;
    if (HT7038_buf11[44] > U_UB)
    {
        exceeded[13] = true; // 电压不平衡超上限
        anyExceeded = true;
        waring_num++;
    }
    else
        exceeded[13] = false;
    if (HT7038_buf11[45] > I_UB)
    {
        exceeded[14] = true; // 电流不平衡超上限
        anyExceeded = true;
        waring_num++;
    }
    else
        exceeded[14] = false;
    if (p_c_day > Power_c)
    {
        exceeded[15] = true; // 功率因数超下限
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

        {"电压上限", DIANYA1, &avu_warning, 5},
        {"电压下限", DIANYA_11, &avd_warning, 5},
        {"电流上限", guoliu_type21, &aiu_warning, 19},
        {"电流下限", guoliu_type21, &aid_warning, 19},
        {"频率上限", hz_up, &frequency_up_warning, 5},
        {"频率下限", hz_down, &frequency_down_warning, 5},
        {"功率上限", power_waring, &power_warning, 12},
        {"进线温度", TEM_UP_show1, &temperature_in_warning, 5},
        {"出线温度", TEM_UP_show1, &temperature_out_warning, 5},
        {"有功功率", p_waring, &P_warning, 9},
        {"无功功率", q_waring, &Q_warning, 9},
        {"视在功率", s_warning, &S_warning, 9},
        {"功率因数", Cos_warning, &cos_warning, 4},
        {"UUB", u_UB_waring, &U_UB_waring, 5},
        {"IUB", i_UB_waring, &I_UB_waring, 5},
        {"电量范围", Powerconsumption_warning, &powerconsumption_warning, 3},
        //		{"电量范围",NULL,NULL,&powerconsumption_warning,kWh,1,{1000, 2000, 3000, 4000}},
        ////		{"a相电压上限",250,300,&avu_warning,V,0},
        ////		{"a相电压下限",140,190,&avd_warning,V,0},
        ////		{"b相电压上限",250,300,&bvu_warning,V,0},
        ////		{"b相电压下限",140,190,&bvd_warning,V,0},
        ////		{"c相电压上限",250,300,&cvu_warning,V,0},
        ////		{"c相电压下限",140,190,&cvd_warning,V,0},
        ////		{"a相电流上限",63,250, &aiu_warning,A,0},
        ////		{"a相电流下限",63,250, &aid_warning,A,0},
        ////		{"b相电流上限",63,250, &biu_warning,A,0},
        ////		{"b相电流下限",63,250, &bid_warning,A,0},
        ////		{"c相电流上限",63,250, &ciu_warning,A,0},
        ////		{"c相电流下限",63,250, &cid_warning,A,0},
        //		{"频率",40,60,&frequency_warning,HZ,0},
        //		{"功率",50,150,&power_warning,kW,0},
        //		{"进线温度",50,100,&temperature_in_warning,C},
        //		{"出线温度",50,100,&temperature_out_warning,C},
        //		{"有功功率",60,150,&P_warning,kW,0},
        //		{"无功功率",60,150,&Q_warning,kvar,0},
        //		{"视在功率",60,150,&S_warning,kVA,0},
        //		{"功率因数",60,100,&cos_warning,NULL,0},
        //		{"UUB",0,30,&U_UB_waring,percent,0},
        //		{"IUB",0,30,&I_UB_waring,percent,0},
        //		{"电量范围",NULL,NULL,&powerconsumption_warning,kWh,1,{1000, 2000, 3000, 4000}},
        //		{"电量范围",NULL,NULL,&powerconsumption_warning,kWh,1,{1000, 2000, 3000, 4000}},
        ////		{"a相电压",40,60,&frequency_warning},
        ////		{"a相电压",40,60,&frequency_warning},
        ////		{"a相电压",40,60,&frequency_warning},
        ////		{"a相电压",40,60,&frequency_warning}
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
        // 如果需要处理超过6行的情况，可以在这里添加代码
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
            displayExceedMessage(line, "电压超限");
        }

        if (exceeded[i] && (i == 3))
        {
            line++;
            displayExceedMessage(line, "电流超限");
        }
        if (exceeded[i] && (i == 4 || i == 5))
        {
            line++;
            displayExceedMessage(line, "频率超限");
        }

        if (exceeded[i] && (i == 6))
        {
            line++;
            displayExceedMessage(line, "功率超限");
        }
        if (exceeded[i] && (i == 7 || i == 8))
        {
            line++;
            displayExceedMessage(line, "温度超限");
        }
        if (exceeded[i] && (i == 9 || i == 10 || i == 11))
        {
            line++;
            displayExceedMessage(line, "功率");
        }
        if (exceeded[i] && (i == 12))
        {
            line++;
            displayExceedMessage(line, "功率因数");
        }
        if (exceeded[i] && (i == 13))
        {
            line++;
            displayExceedMessage(line, "电压平衡");
        }
        if (exceeded[i] && (i == 14))
        {
            line++;
            displayExceedMessage(line, "电流平衡");
        }
        if (exceeded[i] && (i == 15))
        {
            line++;
            displayExceedMessage(line, "电能超限");
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
        Lcd12864_Write16CnCHAR(0, 30, 0, " 报警信息 ");
    }
    else
        Lcd12864_Write16CnCHAR(0, 18, 0, " 无报警信息 ");
}
