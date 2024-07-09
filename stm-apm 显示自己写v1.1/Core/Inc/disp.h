#ifndef __DISP_H
#define __DISP_H	 
#include "main.h"




//#define WF    HAL_GPIO_ReadPin(OUT_OPEN_GPIO_Port,OUT_OPEN_Pin)
//#define WH    HAL_GPIO_ReadPin(OUT_CLOSE_GPIO_Port,OUT_CLOSE_Pin)
	
#define KEY1 HAL_GPIO_ReadPin(UP__BUTTON_GPIO_Port,UP__BUTTON_Pin)   //上键
#define KEY3 HAL_GPIO_ReadPin(CLOSE__BUTTON_GPIO_Port,CLOSE__BUTTON_Pin)
//#define KEY3 HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_2)   //合闸
//#define KEY2 HAL_GPIO_ReadPin(LEAK_TEST_BUTTON_GPIO_Port,LEAK_TEST_BUTTON_Pin)
#define KEY4 HAL_GPIO_ReadPin(OPEN__BUTTON_GPIO_Port,OPEN__BUTTON_Pin)  //分闸
#define KEY5 HAL_GPIO_ReadPin(SET__BUTTON_GPIO_Port,SET__BUTTON_Pin)   //设置键
#define KEY6 HAL_GPIO_ReadPin(CENTER__BUTTON_GPIO_Port,CENTER__BUTTON_Pin)   //确定键
#define KEY7 HAL_GPIO_ReadPin(BACK__BUTTON_GPIO_Port,BACK__BUTTON_Pin)   //返回键
#define KEY8 HAL_GPIO_ReadPin(DOWN__BUTTON_GPIO_Port,DOWN__BUTTON_Pin)   //向下键
//#define KEY0  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)//读取按键0
//#define KEY1  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)//读取按键1
//#define KEY2  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)//读取按键2 
//#define WK_UP   GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)//读取按键3(WK_UP) 

 

#define KEY0_PRES 	1	//KEY0按下
#define KEY1_PRES	2	//KEY1按下
#define KEY2_PRES	3	//KEY2按下
//#define WKUP_PRES   4	//KEY_UP按下(即WK_UP/KEY_UP)


unsigned int vol_handle_A(unsigned int value);
unsigned int vol_handle_B(unsigned int value);
unsigned int vol_handle_C(unsigned int value);
//unsigned int cur_handle_A(unsigned int x);
//unsigned int cur_handle_B(unsigned int x);
//unsigned int cur_handle_C(unsigned int x);
void KEY_Init(void);//IO初始化
void long_key_process(unsigned char key_tmp);
void display(void);
void Just_key_state(void);
void Sj_function_process(void);
void Ld_function_process(void);
void Dy_function_process(void);
void Gl_function_process(void);
void Ls_function_process(void);
void Sf_function_process(void);
void Else_function_process(void);
void Dy_disp(unsigned int tmp);
void Dl_disp(unsigned int tmp);
void Ls_disp(unsigned int tmp);
void Sj_disp(unsigned char tmp);
unsigned int vol_handle(unsigned int value);
unsigned int cur_handle(unsigned int x);
unsigned char nomal_disp(void);
void back_button(void);
//#define Cceshi    PCout(7) //SCL
#define SMG_CLK    z  //SCL
#define SMG_SDA    x //SDA	 
#define SMG_STB    y //SDA	
#define sclk    PCout(6)  //SCL
#define sid    PCout(7) //SDA	 
//#define cs1    PCout(8) //SDA
unsigned int cur_cal_handle(unsigned int x);

u8 KEY_Scan(u8);  	//按键扫描函数	
extern unsigned char disp_status,long_key_temp;
extern unsigned char F_cal;
extern signed char N_key_temp;
extern unsigned char dispbit[8];
unsigned char key_process(unsigned char key);
//extern unsigned char self_addr_code[6],EEPROM_array_tmp[150],F_gz_disp,F_ch;
//extern unsigned char self_addr_code_temp[6];
unsigned char get_key(void);
unsigned char Read_key(void);


void mima_input();
void mima_check();
void mima_change();

#endif


