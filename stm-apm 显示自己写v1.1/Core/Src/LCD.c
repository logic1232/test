#include "lcd.h"
// #include "sys.h"
 #include "gpio.h"
//#include "delay.h"

void transfer_command(u8 data1)
{
	char i;
	CS_LOW;
	AO_LOW;
	for (i = 0; i < 8; i++)
	{
		SCLK_LOW;
		
		if (data1 & 0x80)
			SDA_HIGH;
		else
			SDA_LOW;
		SCLK_HIGH;
		data1 = data1 << 1;
	}
   CS_HIGH;

}

void transfer_data(unsigned char data1)
{

	char i;
	CS_LOW;
	AO_HIGH;
	for (i = 0; i < 8; i++)
	{
		SCLK_LOW;
		if (data1 & 0x80)
			SDA_HIGH;
		else
 			SDA_LOW;
		SCLK_HIGH;
		data1 = data1 << 1;
	}
	CS_HIGH;
}
/**
 *
 *
 *
 *
 **/
void initial_lcd()
{

	//CS_LOW;
	RESET_LOW; /*硬复位*/
	HAL_Delay (100);
	RESET_HIGH; /*硬复位*/
	HAL_Delay (100);

	transfer_command(0xe2); /*软复位 */
	HAL_Delay (5);
//	transfer_command(0x2c); /*升压步骤 1*/
//	HAL_Delay (5);
//	transfer_command(0x2e); /*升压步骤 2*/
//	HAL_Delay (5);
	transfer_command(0x2f); /*升压步骤 3*/
	HAL_Delay (5);

	//transfer_command(
	transfer_command(0x21); /*调整对比度，设置范围0x20～0x27*/
	transfer_command(0x81); /*微调对比度*/
	transfer_command(0x3F); /*微调对比度的值*/
//	transfer_command(0xa7);
//transfer_command(0xa4);
	transfer_command(0xa2); /*偏压比（bias）,0xA2:1/9   0xA3:1=1/7*/

// 	transfer_command(0xA6);  /* 正常显示 */
//	transfer_command(0xA4);  /* 全部点阵打开	*/

	transfer_command(0xc8); /*行扫描顺序：从上到下*/
	transfer_command(0xa0); //*列扫描顺序：从左到右*//
	transfer_command(0x40); //*起始行：第一行开始 */

	//transfer_command(0xa4); //*???????*/
	transfer_command(0xaf); //*开显示*/
	//*???*/
	//CS_HIGH;
	//	RESET_HIGH;
	//	HAL_Delay (2);
	//	RESET_LOW;
	//	HAL_Delay (10);
	//	RESET_HIGH;
	//	HAL_Delay (20);

	//	transfer_command(0xa2);		//1/9 Bias
	//	transfer_command(0xa6);		//Set Inverse display
	//	transfer_command(0xa0);		//ADC set (SEG)
	//	transfer_command(0xc8);		//COM reves

	//	transfer_command(0x24);		//??Ч???Χ??0X20-0X27??? ???????????????????
	//	transfer_command(0x81);		//Electronic Volume Mode Set
	//	transfer_command(0x1f);		//??Ч???Χ??0X00-0X3F??? ?????????????????????
	//	transfer_command(0x2c);
	//	HAL_Delay (200);                      //???200mS
	//	transfer_command(0x2f);		//The Power Control Set
	//	HAL_Delay (200);                     //???200mS
	//	transfer_command(0xaf);		//Lcd Disply ON
}
void lcd_address(unsigned char page, unsigned char column)
{
	// cs1=0;
	column = column - 1;
	page = page - 1;
	transfer_command(0xb0 + page); // B0?????

	transfer_command(((column >> 4) & 0x0f) + 0x10); // 0000 1111  ??4λ   ????????????
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
/******************************????????***********************************/
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

void display_graphic_32x32(uchar page,uchar column,uchar *dp)
{
uchar i,j;
for(j=0;j<4;j++)
{
lcd_address(page+j,column);
for (i=0;i<31;i++)
{
transfer_data(*dp); /*写数据到 LCD,每写完一个 8 位的数据后列地址自动加 1*/
dp++;
}
}
}
unsigned char read_data_from_lcd(unsigned char page, unsigned char column)
{
    // 读取LCD当前列数据的函数需要实现
    // 通常可以通过SPI或其他接口从LCD读取数据
    // 这里假设有一个函数可以实现此功能，具体实现取决于硬件接口
    unsigned char data;

    // 设置LCD地址
    lcd_address(page + 1, column + 1);

    // 读取数据过程
    // 注意：假设读数据的函数已经实现
    // data = spi_read_byte();

    return data;
}
void draw_point(unsigned char x, unsigned char y, unsigned char state)
{
    unsigned char page = y / 8; // 计算页地址
    unsigned char bit_position = y % 8; // 计算位位置
    unsigned char column = x; // 列地址

    // 设置LCD地址
    lcd_address(page + 1, column + 1);

    // 读取当前列的数据
    unsigned char current_data = read_data_from_lcd(page, column);

    if (state)
    {
        // 设置对应位
        current_data |= (1 << bit_position);
    }
    else
    {
        // 清除对应位
        current_data &= ~(1 << bit_position);
    }

    // 写回修改后的数据
    lcd_address(page + 1, column + 1);
    transfer_data(current_data);
}




void LCD_Fill(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2)
{
    unsigned char start_page = y1 / 8;
    unsigned char end_page = y2 / 8;
    unsigned char start_bit = y1 % 8;
    unsigned char end_bit = y2 % 8;

    for (unsigned char page = start_page; page <= end_page; page++)
    {
        for (unsigned char x = x1; x <= x2; x++)
        {
            unsigned char current_data = read_data_from_lcd(page, x);
            if (page == start_page && page == end_page)
            {
                // 同一页内
                for (unsigned char bit = start_bit; bit <= end_bit; bit++)
                {
                    current_data |= (1 << bit);
                }
            }
            else if (page == start_page)
            {
                // 第一个页
                for (unsigned char bit = start_bit; bit < 8; bit++)
                {
                    current_data |= (1 << bit);
                }
            }
            else if (page == end_page)
            {
                // 最后一个页
                for (unsigned char bit = 0; bit <= end_bit; bit++)
                {
                    current_data |= (1 << bit);
                }
            }
            else
            {
                // 中间页
                current_data = 0xFF;
            }

            // 写回数据
            lcd_address(page + 1, x + 1);
            transfer_data(current_data);
        }
    }
}


//void LCD_Fill(uint16_t xsta,uint16_t ysta,uint16_t xend,uint16_t yend,uint16_t* color)
//{        


//	uint16_t height,width;
//	uint16_t i,j;
//	width=xend-xsta+1; 			//得到填充的宽度
//	height=yend-ysta+1;			//高度
//	LCD_Address_Set(xsta,ysta,xend,yend);//设置显示范围
// 	for(i=0;i<height;i++)
//	{
//		for(j=0;j<width;j++)
//		LCD_WR_DATA(color[i*width+j]);//写入数据 
//	}	
//}
//void lcd_fill(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey, uint32_t color)
//{
//    uint16_t i, j;
//    uint16_t xlen = 0;
//    xlen = ex - sx + 1;

//    for (i = sy; i <= ey; i++)
//    {
//        lcd_set_cursor(sx, i);      /* 设置光标位置 */
//        lcd_write_ram_prepare();    /* 开始写入GRAM */

//        for (j = 0; j < xlen; j++)
//        {
//            lcd_wr_data(color);     /* 写入数据 */
//        }
//    }
//}
//void lcd_fill(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey, uint32_t color)
//{
//    uint16_t i, j;
//    uint16_t xlen = 0;
//    xlen = ex - sx + 1;

//    for (i = sy; i <= ey; i++)
//    {
//		lcd_address(sx,ex)
//        lcd_set_cursor(sx, i);      /* 设置光标位置 */
//        lcd_write_ram_prepare();    /* 开始写入GRAM */

//        for (j = 0; j < xlen; j++)
//        {
//            lcd_wr_data(color);     /* 写入数据 */
//        }
//    }
//}