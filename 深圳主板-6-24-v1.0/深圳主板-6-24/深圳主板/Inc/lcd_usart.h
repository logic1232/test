#ifndef _LCD_UASRT_
#define _LCD_UASRT_

#include "main.h"
void UART_LCD_process(void);
void Write_Trip_Data2LCD(void);


//#define SLAVE_READ_NOL_RES   0x00  //从站读数据正常响应
//#define SLAVE_READ_ABNOL_RES 0x10  //从站读数据正常响应
//#define MASTER_WRITE         0x10  //主站写数据


//#define DATA_ADDR                 0xA0  //地址
//#define DATA_OVER                 0x16  //结束符
//#define MASTER_DATA_ADDR          0xA0  //主站地址
///******控制码******/
//#define Ctrl_READ_DATA            0x11  //读数据
//#define Ctrl_WRITE_DATA           0X14  //写数据
//#define Ctrl_WARN                 0x0C  //报警
//#define Ctrl_PRO                  0x12  //保护功能


//#define M2S_READ_DATA             0x11  //主站请求读数据
//#define S2M_READ_DATA_NOR_ACK     0xD1  //从站正常响应读数据
//#define S2M_READ_DATA_ABNOR_ACK   0xF1  //从站异常响应读数据
//#define M2S_WRITE_DATA            0x14  //主站请求写数据
//#define S2M_WRITE_DATA_NOR_ACK    0xD4  //从站正常响应写数据
//#define S2M_WRITE_DATA_ABNOR_ACK  0xF4  //从站异常响应写数据
//#define S2M_WRITE_DATA            0x94  //从站请求写数据
//#define M2S_WRITE_DATA_NOR_ACK    0x54  //主站正常响应写数据
//#define M2S_WRITE_DATA_ABNOR_ACK  0x74  //主站异常响应写数据
//#define M2S_WARN									0x1C  //主站发送报警信息
//#define S2M_WARN_NOR_ACK          0xDC  //从站正常应答报警
//#define S2M_WARN_ABNOR_ACK        0xFC  //从站异常应答报警
//#define M2S_PRO                   0x12  //主站请求查询保护功能
//#define S2M_PRO_NOR_ACK           0xD2  //从站正常应答保护功能
//#define S2M_PRO_ABNOR_ACK         0xF2  //从站异常应答保护功能
//#define S2M_PRO                   0x92  //从站请求更改保护功能
//#define M2S_PRO_NOR_ACK           0x52  //从站正常应答保护功能
//#define M2S_PRO_ABNOR_ACK         0x72  //从站异常应答保护功能


///*****数据识别码*****/
///**************当前数据*************/
//#define Data_Iden_Vol              0x01 
//#define Data_Iden_A_Phase_Vol      0x01   
//#define Data_Iden_B_Phase_Vol      0x02  
//#define Data_Iden_C_Phase_Vol      0x04 
//#define Data_Iden_ALL_Phase_Vol    0xFF

//#define Data_Iden_Cur              0x02 
//#define Data_Iden_A_Phase_Cur      0x01   
//#define Data_Iden_B_Phase_Cur      0x02  
//#define Data_Iden_C_Phase_Cur      0x04 
//#define Data_Iden_ALL_Phase_Cur    0xFF

//#define Data_Iden_Fre              0x0C
//#define Data_Iden_Leak             0x0D
//#define Data_Iden_Energy           0x0E

//#define Data_Iden_Power            0x0F
//#define Data_Iden_Act_Power        0x01
//#define Data_Iden_Rea_Power        0x02
//#define Data_Iden_App_Power        0x04
//#define Data_Iden_All_Power        0xFF

//#define Exhibition_Data            0x10
///*************基本保护数据********************/
//#define Data_Iden_Overload         0x01
//#define Data_Iden_Overload_Cur     0x01
//#define Data_Iden_Overload_Time    0x02
//#define Data_Iden_Overload_Pro     0x04
//#define Data_Iden_Overload_ALL     0xFF


//#define Data_Iden_Shortdelay        0x02
//#define Data_Iden_Shortdelay_Cur    0x01
//#define Data_Iden_Shortdelay_Time   0x02
//#define Data_Iden_Shortdelay_Pro    0x04
//#define Data_Iden_Shortdelay_ALL    0xFF

//#define Data_Iden_Shortinstant        0x03
//#define Data_Iden_Shortinstant_Cur    0x01
//#define Data_Iden_Shortinstant_Pro    0x02
//#define Data_Iden_Shortinstant_ALL    0xFF

//#define Data_Iden_Leakage          0x02
//#define Data_Iden_Leakage_Cur    	 0x01
//#define Data_Iden_Leakage_Time   	 0x02
//#define Data_Iden_Leakage_Notact 	 0x04 //额定剩余不动作电流
//#define Data_Iden_Leakage_Pro    	 0x08
//#define Data_Iden_Leakage_ALL    	 0xFF

///***************扩展保护数据****************/
//#define Data_Iden_OverVol        0x01
//#define Data_Iden_OverVol_Vol    0x01
//#define Data_Iden_OverVol_Reclose_Vol    0x02
//#define Data_Iden_OverVol_Time   0x04
//#define Data_Iden_OverVol_Pro    0x08
//#define Data_Iden_OverVol_ALL    0xFF

//#define Data_Iden_UnderVol        0x02
//#define Data_Iden_UnderVol_Vol    0x01
//#define Data_Iden_UnderVol_Reclose_Vol    0x02
//#define Data_Iden_UnderVol_Time   0x04
//#define Data_Iden_UnderVol_Pro    0x08
//#define Data_Iden_UnderVol_ALL    0xFF

//#define Data_Iden_Loss           0x03
//#define Data_Iden_Loss_Cur       0x01
//#define Data_Iden_Loss_Time      0x02
//#define Data_Iden_Loss_Pro       0x04
//#define Data_Iden_Loss_ALL       0xFF

//#define Data_Iden_Misphase       0x04
//#define Data_Iden_Misphase_Vol   0x01
//#define Data_Iden_Misphase_Time  0x02
//#define Data_Iden_Misphase_Pro   0x04
//#define Data_Iden_Misphase_ALL   0xFF

//#define Data_Iden_Unbalance       0x05
//#define Data_Iden_Unbalance_Vol   0x01
//#define Data_Iden_Unbalance_Time  0x02
//#define Data_Iden_Unbalance_Pro   0x04
//#define Data_Iden_Unbalance_ALL   0xFF

//void LCD_Data_process(void);   //主站接收数据处理函数
//uint8_t Response_By_LCD(uint8_t type);  //从机数据应答等待函数 
//void LCD_screen_display(void);     //主机发送LCD封面数据
//void Send_Data2LCD_process(uint8_t *ID_array, uint8_t *array_temp, uint8_t len); //给LCD发送数据
//void Read_NowTime(uint8_t type);//读当前时间或日期
//uint8_t Write_response_By_LCD(void);
//void Write_Trip_Data2LCD(uint8_t type);
//void Write_Now_time(uint8_t *array); //写当前时间
//void Write_Now_date(uint8_t *array); //写当前日期
#endif
