/*
 * ht7038.c
 *
 *  Created on: Nov 6, 2021
 *      Author: zhang
 */

#ifndef INC_HT7038_C_
#define INC_HT7038_C_

#include "main.h"
#include "gpio.h"  



#define HT7038_CS_Low()  		HAL_GPIO_WritePin(SPI_NSS_GPIO_Port,SPI_NSS_Pin,0)
#define HT7038_CS_High()  		HAL_GPIO_WritePin(SPI_NSS_GPIO_Port,SPI_NSS_Pin,1)
#define HT7038_SCK_Low()  		HAL_GPIO_WritePin(SPI_SCK_GPIO_Port,SPI_SCK_Pin,0)
#define HT7038_SCK_High()  	HAL_GPIO_WritePin(SPI_SCK_GPIO_Port,SPI_SCK_Pin,1)
#define HT7038_MOSI_Low()  	HAL_GPIO_WritePin(SPI_MOSI_GPIO_Port,SPI_MOSI_Pin,0)
#define HT7038_MOSI_High() 	HAL_GPIO_WritePin(SPI_MOSI_GPIO_Port,SPI_MOSI_Pin,1)
#define HT7038_MISO_STA() 		HAL_GPIO_ReadPin(SPI_MISO_GPIO_Port, SPI_MISO_Pin)



//===================================================
//      定义HT7038的数据寄存器 
//===================================================
#define rDeviceID 0x00  //7038 Device ID
#define rPa     0x01  //A相有功功率
#define rPb     0x02  //B相有功功率
#define rPc     0x03  //C相有功功率
#define rPt     0x04  //合相有功功率
 
#define rQa     0x05  //A相无功功率
#define rQb     0x06  //B相无功功率
#define rQc     0x07  //C相无功功率
#define rQt     0x08  //合相无功功率
 
#define rSa     0x09  //A相视在功率
#define rSb     0x0A  //B相视在功率
#define rSc     0x0B  //C相视在功率
#define rSt     0x0C  //合相视在功率
 
#define rUaRms      0x0D  //A相电压有效值
#define rUbRms      0x0E  //B相电压有效值
#define rUcRms      0x0F  //C相电压有效值
 
#define rIaRms      0x10  //A相电流有效值
#define rIbRms      0x11  //B相电流有效值
#define rIcRms      0x12  //C相电流有效值
#define rItRms      0x13  //ABC相电流矢量和的有效值
 
#define rPfa    0x14  //A相功率因数
#define rPfb    0x15  //B相功率因数
#define rPfc    0x16  //C相功率因数
#define rPft    0x17  //合相功率因数
 
#define rPga    0x18  //A相电流与电压相角
#define rPgb    0x19  //B相电流与电压相角功率因数
#define rPgc    0x1a  //C相电流与电压相角
 
#define rINTFlag  0x1b  //中断标志，读后清零 ☆
 
#define rFreq   0x1C  //线频率
#define rEFlag  0x1d  //电能寄存器的工作状态，读后清零☆
 
#define rEpa    0x1e  //A相有功电能
#define rEpb    0x1f  //B相有功电能
#define rEpc    0x20  //C相有功电能
#define rEpt    0x21  //合相有功电能
 
#define rEqa    0x22  //A相无功电能
#define rEqb    0x23  //B相无功电能
#define rEqc    0x24  //C相无功电能
#define rEqt    0x25  //合相无功电能
 
#define rYUaUb    0x26  //Ua与Ub的电压夹角            ☆
#define rYUaUc    0x27  //Ua与Uc的电压夹角            ☆
#define rYUbUc    0x28  //Ub与Uc的电压夹角            ☆
 
#define rTPSD   0x2a  //温度传感器的输出
#define rURmst    0x2b  //ABC电压矢量和的有效值
 
#define rS_Flag   0x2c  //存放断相、相序、SIG信号的有效值
 
#define rBackReg    0x2d  //通讯数据备份寄存器☆
#define rComChksum  0x2e  //通讯校验和寄存器☆
#define rSampleIA   0x2f  //A相电流通道ADC采样数据☆
#define rSampleIB   0x30  //B相电流通道ADC采样数据☆
#define rSampleIC   0x31  //C相电流通道ADC采样数据☆
 
#define rSampleUA   0x32  //A相电压通道ADC采样数据☆
#define rSampleUB   0x33  //B相电压通道ADC采样数据☆
#define rSampleUC   0x34  //C相电压通道ADC采样数据☆
 
#define rEsa  0x35  //A相视在电能☆
#define rEsb  0x36  //B相视在电能☆
#define rEsc  0x37  //C相视在电能☆
#define rEst  0x38  //合相视在电能☆
 
#define rFstCntA    0x39  //A相快速脉冲计数☆
#define rFstCntB    0x40  //B相快速脉冲计数☆
#define rFstCntC    0x40  //C相快速脉冲计数☆
#define rFstCntT    0x41  //合相快速脉冲计数☆
 
#define rPFlag    0x3d  //有功和无功功率方向，正向为0，负向为1
 
#define rChkSum 0x3e  //校表数据校验寄存器（三相四线模式下是0x01D4CD;三相三线模式下是0x01E0CD;）
 
 
#define rVrefgain   0x5c  //Vref自动补偿系数
#define rChipID     0x5d  //芯片版本指示器0X7026E0
#define rChkSum1    0x5e  //新增校表寄存器校验和





//==================================================================
//          HT7038校表寄存器定义
//==================================================================
#define w_ModeCfg       0X01  //模式相关控制 (缺省值为			--	0x89aa)
#define w_PGACtrl       0X02  //ADC增益选择 
#define w_EMUCfg        0X03  //EMU模块配置寄存器 
#define w_PgainA        0X04  //A相有功功率增益 
#define w_PgainB        0X05  //B相有功功率增益 
#define w_PgainC        0X06  //C相有功功率增益 
#define w_QgainA        0X07  //A相无功功率增益 
#define w_QgainB        0X08  //B相无功功率增益 
#define w_QgainC        0X09  //C相无功功率增益 
#define w_SgainA        0X0A  //A相视在功率增益 
#define w_SgainB        0X0B  //B相视在功率增益 
#define w_SgainC        0X0C  //C相视在功率增益 
#define w_PhSregApq0    0X0D  //A相相位校正0 
#define w_PhSregBpq0    0X0E  //B相相位校正0 
#define w_PhSregCpq0    0X0F  //C相相位校正0 
#define w_PhSregApq1    0X10  //A相相位校正1 
#define w_PhSregBpq1    0X11  //B相相位校正1 
#define w_PhSregCpq1    0X12  //C相相位校正1 
#define w_PoffsetA      0X13  //A相有功功率offset校正 
#define w_PoffsetB      0X14  //B相有功功率offset校正 
#define w_PoffsetC      0X15  //C相有功功率offset校正 
#define w_QPhscal       0X16  //无功相位校正 
#define w_UgainA        0X17  //A相电压增益 
#define w_UgainB        0X18  //B相电压增益 
#define w_UgainC        0X19  //C相电压增益 
#define w_IgainA        0X1A  //A相电流增益 
#define w_IgainB        0X1B  //B相电流增益 
#define w_IgainC        0X1C  //C相电流增益 
#define w_Istarup       0X1D  //起动电流阈值设置 
#define w_Hfconst       0X1E  //高频脉冲输出设置 
#define w_FailVoltage   0X1F  //失压阈值设置
 
#define w_QoffsetA      0X21  //A相无功功率offset校正 
#define w_QoffsetB      0X22  //B相无功功率offset校正 
#define w_QoffsetC      0X23  //C相无功功率offset校正 
#define w_UaRmsoffse    0X24  //A相电压有效值offset校正 
#define w_UbRmsoffse    0X25  //B相电压有效值offset校正 
#define w_UcRmsoffse    0X26  //C相电压有效值offset校正 
#define w_IaRmsoffse    0X27  //A相电流有效值offset校正 
#define w_IbRmsoffse    0X28  //B相电流有效值offset校正 
#define w_IcRmsoffse    0X29  //C相电流有效值offset校正 
#define w_UoffsetA      0X2A  //A相电压通道ADC offset校正 
#define w_UoffsetB      0X2B  //B相电压通道ADC offset校正 
#define w_UoffsetC      0X2C  //C相电压通道ADC offset校正 
#define w_IoffsetA      0X2D  //A相电流通道ADC offset校正 
#define w_IoffsetB      0X2E  //B相电流通道ADC offset校正 
#define w_IoffsetC      0X2F  //C相电流通道ADC offset校正 
#define w_EMUIE         0X30  //中断使能 
#define w_ModuleCFG     0X31  //电路模块配置寄存器 (缺省值为	--	0x0x3527)
#define w_AllGain       0X32  //全通道增益，用于校正ref自校正
#define w_HFDouble      0X33  //脉冲常数加倍选择 
#define w_LineGain      0X34  //基波增益校正 
#define w_PinCtrl       0X35  //数字pin上下拉电阻选择控制 
#define w_Pstartup      0X36  //起动功率阈值设置 
#define w_Iregion0      0X37  //相位补偿区域设置寄存器 
#define w_Iregion1      0X60  //相位补偿区域设置寄存器1 
#define w_PhSregApq2    0X61  //A相相位校正2 
#define w_PhSregBpq2    0X62  //B相相位校正2 
#define w_PhSregCpq2    0X63  //C相相位校正2 
#define w_PoffsetAL     0X64  //A相有功功率offset校正低字节 
#define w_PoffsetBL     0X65  //B相有功功率offset校正低字节 
#define w_PoffsetCL     0X66  //C相有功功率offset校正低字节 
#define w_QoffsetAL     0X67  //A相无功功率offset校正低字节 
#define w_QoffsetBL     0X68  //B相无功功率offset校正低字节 
#define w_QoffsetCL     0X69  //C相无功功率offset校正低字节 
#define w_ItRmsoffset   0X6A  //电流矢量和offset校正寄存器 
#define w_TPSoffset     0X6B  //TPS初值校正寄存器 
#define w_TPSgain       0X6C  //TPS斜率校正寄存器 
#define w_TCcoffA       0X6D  //Vrefgain的二次系数
#define w_TCcoffB       0X6E  //Vrefgain的一次系数
#define w_TCcoffC       0X6F  //Vrefgain的常数项 
#define w_EMCfg         0X70  //新增算法控制寄存器
#define w_PtrWavebuff   0X7E  //缓冲数据指针，
#define w_WaveBuff      0X7F  //缓冲数据指针，

//==================================================================
//          HT7038校表寄存器存储地址定义
//==================================================================
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


unsigned int HT7038_Read(unsigned char addr);
void HT7038_Write(unsigned char addr,unsigned int dat);
void HT7038_GPIO_Init(void);
void HT7038_Init(void);
void delay(unsigned int cnt);
void HT7038_EEP_Initial(void);

void HT7038Reset(void);
void HT7038ResetSet(unsigned char state);


#endif /* INC_HT7038_C_ */
