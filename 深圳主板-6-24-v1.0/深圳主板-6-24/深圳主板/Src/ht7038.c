/*
 * ht7038.c
 *
 *  Created on: Nov 6, 2021
 *      Author: zhang
  */
#include "ht7038.h" 
#include "delay.h"
#include "24cxx.h"
#include "disp.h"

#define DELAY 3

extern float Ugain_A,Ugain_B,Ugain_C,Igain_A,Igain_B,Igain_C,Pgain_AA,Pgain_BB,Pgain_CC;

extern unsigned int Uoffset_A,Uoffset_B,Uoffset_C,Ioffset_A,Ioffset_B,Ioffset_C,Ioffset_ABC;

unsigned int test_buf[20] = {0};//测试用


void delay(unsigned int cnt)
{
	unsigned int i,j;
	for(i=0;i<cnt;i++)
	{
		for(j=0;j<100;j++)
		{
			;
		}
	}
}


void HT7038ResetSet(unsigned char state)
{
    if( state == ENABLE )
    {
		HAL_GPIO_WritePin(SPI_RESET_GPIO_Port, SPI_RESET_Pin, GPIO_PIN_RESET);			//将复位引脚置低

    }
    else
    {
		HAL_GPIO_WritePin(SPI_RESET_GPIO_Port, SPI_RESET_Pin, GPIO_PIN_SET);			//将复位引脚置高

    }

}


/*************************************
	* 功能函数：	复位ht7038模块
	* 入口参数：	无
	* 返回值：		无
**************************************/
void HT7038Reset(void)
{
    HT7038ResetSet( ENABLE );
	delay_ms(1); 				//等待100us  
	
    HT7038ResetSet( DISABLE );
	delay_ms(1); 				//等待100us 	
	
	 HT7038_Write(0xD3,0X000000);//软件复位
}





void HT7038_Init(void)
{
	
	HT7038_Write(0xC9,0x5A); ////选择校表寄存器//校表数据写使能


	
	HT7038_Write(w_ModeCfg,0xB97E); //模式配置寄存器(0x01)写入：0xB97E 。开启 Vref Chopper 功能提升 Vref 性能；开启功率有效值慢速模式，减小跳动；配置 EMU 时钟 921.6kHz，降低功耗；开启 6 路 ADC，关闭 In 通道
	HT7038_Write(w_EMUCfg,0xFC04);// EMU 单元配置寄存器(0x03)写入：0xFC04。开启能量计量，使用功率作为潜动起动依据。开启基波波/谐波计量功能
	HT7038_Write(w_ModuleCFG,0x3427);// 模拟模块使能寄存器(0x31)写入：0x3427，开启高通滤波器；开启 BOR 电源监测电路。


	HT7038_Write(w_EMCfg,0x0130);//设置三相四线模式0x0110,基波无功，基波测量0110,谐波测量0130

	HT7038_Write(w_EMUIE,0xFFFF);

	HT7038_Write(w_Hfconst,0x0036);//高频脉冲常数
	
//T7038_Write(w_ModuleCFG,0x3404);

	
	HT7038_Write(w_PGACtrl,0x0100);	//ADC增益配置为三相电压通道ADC增益放大1倍 bit09和bit08为设置电压通道增益位0x03FC
	
//	//HT7038_Write(w_EMUCfg,0x0201);	//EMU模块配置寄存器0x0201
//	  HT7038_Write(w_PgainA,0XFF7A);
		HT7038_Write(w_PgainB,0XFF7A);
//		HT7038_Write(w_PgainC,0XFF7A);

//	HT7038_Write(w_UaRmsoffse,Uoffset_A);
//	HT7038_Write(w_UbRmsoffse,Uoffset_B);
//	HT7038_Write(w_UcRmsoffse,Uoffset_C);
	
//	HT7038_Write(w_IaRmsoffse,Ioffset_A);
//	HT7038_Write(w_IbRmsoffse,Ioffset_B);
//	HT7038_Write(w_IcRmsoffse,Ioffset_C);
//	HT7038_Write(w_ItRmsoffset,Ioffset_ABC);


	HT7038_Write(w_UgainA,0XF555);//Uab电压增益0x8684   0x83EE
	HT7038_Write(w_UgainB,0XF555);//Ubc电压增益0x8684   2023-12-9
	HT7038_Write(w_UgainC,0XF555);//Uac相电压增益需单独计算，不与A相C相相同


//	HT7038_Write(w_IgainA,Igain_A);//电流增益
//	HT7038_Write(w_IgainC,Igain_C);//
//	HT7038_Write(w_IgainB,Igain_B);//
//	
//	  HT7038_Write(w_PgainA,Pgain_AA);
//	  HT7038_Write(w_QgainA,Pgain_AA);
//	  HT7038_Write(w_SgainA,Pgain_AA);
//		
//		HT7038_Write(w_PgainB,Pgain_BB);
//   	HT7038_Write(w_QgainB,Pgain_BB);
//  	HT7038_Write(w_SgainB,Pgain_BB);
//		
//		HT7038_Write(w_PgainC,Pgain_CC);
//	  HT7038_Write(w_QgainC,Pgain_CC);
//  	HT7038_Write(w_SgainC,Pgain_CC);

	
////
	

	
	HT7038_Write(w_HFDouble,0x0000);//脉冲常数加倍选择
	
	HT7038_Write(0x31,0x3427);//设置高通滤波(关闭电压&&电流通道数字高通滤波器)  

	HT7038_Write(0xc9,0x5b); ////关闭SPI校表寄存器的写操作

	HT7038_Write(0xc6,0x5b); ////使能SPI计量寄存器读操作
  

}





void HT7038_GPIO_Init(void)
{
//	GPIO_InitTypeDef GPIO_InitStructure;
//
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);
//
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_5 | GPIO_Pin_4;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//	GPIO_Init(GPIOE, &GPIO_InitStructure);
//
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
//	GPIO_Init(GPIOE, &GPIO_InitStructure);
}

void HT7038_Write(unsigned char addr,unsigned int dat)
{
	unsigned char i;

	HT7038_CS_Low();
	HT7038_SCK_Low();

	addr |= 0x80;
	delay(10);
	for(i=0;i<8;i++)
	{
		HT7038_SCK_High();
		if(addr&0x80)
		{
			HT7038_MOSI_High();
		}
		else
		{
			HT7038_MOSI_Low();
		}

		addr = addr << 1;
		delay(DELAY);
		HT7038_SCK_Low();
		delay(DELAY);
	}
	for(i=0;i<24;i++)
	{
		HT7038_SCK_High();
		if(dat&0x800000)
		{
			HT7038_MOSI_High();
		}
		else
		{
			HT7038_MOSI_Low();
		}

		dat = dat << 1;
		delay(DELAY);
		HT7038_SCK_Low();
		delay(DELAY);
	}

	HT7038_CS_High();
	HT7038_SCK_Low();
	HT7038_MOSI_Low();
}

unsigned int HT7038_Read(unsigned char addr)
{
	unsigned char i;
	unsigned int dat=0;

	HT7038_CS_Low();
	HT7038_SCK_Low();
	delay(10);

	for(i=0;i<8;i++)
	{
		HT7038_SCK_High();
		if(addr&0x80)
		{
			HT7038_MOSI_High();
		}
		else
		{
			HT7038_MOSI_Low();
		}

		addr = addr << 1;
		delay(DELAY);
		HT7038_SCK_Low();
		delay(DELAY);
	}

	delay(10);

	for(i=0;i<24;i++)
	{
		HT7038_SCK_High();
		delay(DELAY);
		dat =dat << 1;
		if(HT7038_MISO_STA())
		{
			dat |= 1;
		}

		HT7038_SCK_Low();
		delay(DELAY);
	}

	HT7038_CS_High();
	HT7038_SCK_Low();
	HT7038_MOSI_Low();

	return dat;
}


void HT7038_EEP_Initial(void)
{
	unsigned char array_temp[2];
	EEPROM_R(Addr_Ugain_A, array_temp, 2, 0xA0);
	Ugain_A = (array_temp[1] << 8) + array_temp[0];
	EEPROM_R(Addr_Ugain_B, array_temp, 2, 0xA0);
	Ugain_B = (array_temp[1] << 8) + array_temp[0];
	EEPROM_R(Addr_Ugain_C, array_temp, 2, 0xA0);
	Ugain_C = (array_temp[1] << 8) + array_temp[0];

	EEPROM_R(Addr_Igain_A, array_temp, 2, 0xA0);
	Igain_A = (array_temp[1] << 8) + array_temp[0];
	EEPROM_R(Addr_Igain_B, array_temp, 2, 0xA0);
	Igain_B = (array_temp[1] << 8) + array_temp[0];
	EEPROM_R(Addr_Igain_C, array_temp, 2, 0xA0);
	Igain_C = (array_temp[1] << 8) + array_temp[0];

	EEPROM_R(Addr_Pgain_A, array_temp, 2, 0xA0);
	Pgain_AA = (array_temp[1] << 8) + array_temp[0];
	EEPROM_R(Addr_Pgain_B, array_temp, 2, 0xA0);
	Pgain_BB = (array_temp[1] << 8) + array_temp[0];
	EEPROM_R(Addr_Pgain_C, array_temp, 2, 0xA0);
	Pgain_CC = (array_temp[1] << 8) + array_temp[0];

	//	EEPROM_R(Addr_Uoffset_A,array_temp,2,0xA0);
	//	Uoffset_A=(array_temp[1]<<8)+array_temp[0];
	//	EEPROM_R(Addr_Uoffset_B,array_temp,2,0xA0);
	//	Uoffset_B=(array_temp[1]<<8)+array_temp[0];
	//	EEPROM_R(Addr_Uoffset_C,array_temp,2,0xA0);
	//	Uoffset_C=(array_temp[1]<<8)+array_temp[0];

	EEPROM_R(Addr_Ioffset_A, array_temp, 2, 0xA0);
	Ioffset_A = (array_temp[1] << 8) + array_temp[0];
	EEPROM_R(Addr_Ioffset_B, array_temp, 2, 0xA0);
	Ioffset_B = (array_temp[1] << 8) + array_temp[0];
	EEPROM_R(Addr_Ioffset_C, array_temp, 2, 0xA0);
	Ioffset_C = (array_temp[1] << 8) + array_temp[0];

	EEPROM_R(Addr_Ioffset_ABC, array_temp, 2, 0xA0);
	Ioffset_ABC = (array_temp[1] << 8) + array_temp[0];
	
	
}