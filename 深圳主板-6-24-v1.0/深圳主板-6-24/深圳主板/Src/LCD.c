#include "lcd.h"
// #include "sys.h"
// #include "gpio.h"
#include "delay.h"

void transfer_command(u8 data1)
{
//	char i;
//	CS_LOW;
//	AO_LOW;
//	for (i = 0; i < 8; i++)
//	{
//		SCLK_LOW;
//		if (data1 & 0x80)
//			SDA_HIGH;
//		else
//			SDA_LOW;
//		SCLK_HIGH;
//		data1 = data1 << 1;
//	}
//   CS_HIGH;

}

void transfer_data(unsigned char data1)
{

//	char i;
//	CS_LOW;
//	AO_HIGH;
//	for (i = 0; i < 8; i++)
//	{
//		SCLK_LOW;
//		if (data1 & 0x80)
//			SDA_HIGH;
//		else
//			SDA_LOW;
//		SCLK_HIGH;
//		data1 = data1 << 1;
//	}
//	CS_HIGH;
}
/**
 *
 *
 *
 *
 **/
void initial_lcd()
{

//	CS_LOW;
//	RESET_LOW; /*硬复位*/
//	delay_ms(2);
//	RESET_HIGH; /*硬复位*/
//	delay_ms(2);

//	transfer_command(0xe2); /*软复位 */
//	delay_ms(5);
//	transfer_command(0x2c); /*升压步骤 1*/
//	delay_ms(5);
//	transfer_command(0x2e); /*升压步骤 2*/
//	delay_ms(5);
//	transfer_command(0x2f); /*升压步骤 3*/
//	delay_ms(5);

//	transfer_command(0x24); /*调整对比度，设置范围0x20～0x27*/
//	transfer_command(0x81); /*微调对比度*/
//	transfer_command(0x1d); /*微调对比度的值*/

//	transfer_command(0xa2); /*偏压比（bias）,0xA2:1/9   0xA3:1=1/7*/

// 	transfer_command(0xA6);  /* 正常显示 */
//	transfer_command(0xA4);  /* 全部点阵打开	*/

//	transfer_command(0xc8); /*行扫描顺序：从上到下*/
//	transfer_command(0xa0); //*列扫描顺序：从左到右*//
//	transfer_command(0x40); //*起始行：第一行开始 */

//	transfer_command(0xa4); //*???????*/
//	transfer_command(0xaf); //*开显示*/
//	//*???*/
//	CS_HIGH;

}
void lcd_address(unsigned char page, unsigned char column)
{
	// cs1=0;
	column = column - 1;
	page = page - 1;
	transfer_command(0xb0 + page); // B0Ϊ��ʼҳ

	transfer_command(((column >> 4) & 0x0f) + 0x10); // 0000 1111  ��4λ   ������ַ�ĺ���
	transfer_command(column & 0x0f);
}

void clear_screen(void)
{

	int i, j;
	for (i = 0Xb0; i < 0Xb9; i++)
	{
		transfer_command(i);
		transfer_command(0x10);
		transfer_command(0x00);
		for (j = 0; j < 132; j++)
		{
			transfer_data(0x00);
		}
	}
}

void font1(void)
{
	int i, j;
	for (i = 0Xb0; i < 0Xb8; i++)
	{
		transfer_command(i);
		transfer_command(0x10);
		transfer_command(0x00);
		for (j = 0; j < 128; j++)
		{
			transfer_data(0XFF);
		}
	}
}
void font4(void)
{
	int i, j;
	for (i = 0Xb0; i < 0Xb1; i++)
	{
		transfer_command(i);
		transfer_command(0x10);
		transfer_command(0x00);
		for (j = 0; j < 32; j++)
		{
			transfer_data(0XFF);
			transfer_data(0X00);
			transfer_data(0X00);
			transfer_data(0XFF);
		}
	}
}
/******************************����ض���***********************************/
void clear_define_screen(unsigned char x0, u8 x1, unsigned char y0, unsigned char y1)
{
	unsigned char i, j;
	unsigned char x2, x3, y2, y3;
	x2 = x0;
	x3 = x1;
	y2 = y0;
	y3 = y1;

	// cs1=0;
	for (i = x2; i < x3; i++)
	{

		transfer_command(0xb0 + i); //

		transfer_command(((y2 >> 4) & 0x0f) + 0x10);
		transfer_command(y2 & 0x0f);
		for (j = y2; j < y3; j++)
		{
			transfer_data(0x00);
		}
	}
	// cs1=1;
}
void disp_grap(char *dp)
{
	int i, j;
	for (i = 0; i < 8; i++)
	{
		// cs1=0;
		transfer_command(0xb0 + i); // set page address,
		transfer_command(0x10);
		transfer_command(0x00);
		for (j = 0; j < 128; j++)
		{
			transfer_data(*dp);
			dp++;
		}
	}
}
