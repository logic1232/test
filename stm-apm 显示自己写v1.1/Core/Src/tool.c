#include "tool.h"


void value_to_ascii(int value, char *ascii_array) {
    char percentage_str[10]; // 临时存放百分比字符串
    if (value == 0) {
        sprintf(percentage_str, "0.00%%");
    } else {
        sprintf(percentage_str, "%.1f%%", value / 10.0);
    }
    
    // 将字符串中的每个字符转换为 ASCII 值并存放到数组中
    for (int i = 0; i < strlen(percentage_str); ++i) {
        ascii_array[i] = percentage_str[i];
    }
    ascii_array[strlen(percentage_str)] = '\0'; // 添加字符串结束符
}
/*----------------------------
10进制数转压缩BCD
----------------------------*/
	unsigned char zifu_dian[5]={0};
	int DectoBCD(unsigned char *Bcd,unsigned int Dec, unsigned int length) 
	{
		//unsigned char convert_tmp[10];
		unsigned char ge,shi,bai,qian,wan,shiwan,baiwan,qianwan;
		if(length==2)
		{
			qian = Dec/1000;
			bai  = Dec%1000/100;
			shi  = Dec%100/10;
			ge   = (unsigned char) ((Dec) % 10);
			Bcd[0] = (shi<<4)+ge;
			Bcd[1] = (qian<<4)+bai;
		
		}
		if(length==3)
		{
			shiwan = Dec/100000;
			wan = Dec%100000/10000;
			qian = Dec%10000/1000;
			bai  = Dec%1000/100;
			shi  = Dec%100/10;
			ge   = (unsigned char) ((Dec) % 10);
			Bcd[0] = (shi<<4)+ge;
			Bcd[1] = (qian<<4)+bai;
			Bcd[2] = (shiwan<<4)+wan;
		}
		if(length==4)
		{
			qianwan = Dec/10000000;
			baiwan = Dec%10000000/1000000;
			shiwan = Dec%1000000/100000;
			wan = Dec%100000/10000;
			qian = Dec%10000/1000;
			bai  = Dec%1000/100;
			shi  = Dec%100/10;
			ge   = (unsigned char) ((Dec) % 10);
			Bcd[0] = (shi<<4)+ge;
			Bcd[1] = (qian<<4)+bai;
			Bcd[2] = (shiwan<<4)+wan;
			Bcd[3] = (baiwan<<4)+qianwan;
			
		}

		//    for(i=0; i<=length-1; i++)
//	
//		{  
//				BCD_V_temp = Dec % 100;
//        //Bcd[i] = (((BCD_V_temp/10)<<4)&0xF0);
//				Bcd[i] = BCD_V_temp % 10;
//				Dec /= 100;
//		}
		/*for(i=0; i<length; i++)
		{
			Bcd[i] = convert_tmp[lengh-i]
		}*/
		
		return 0;		
	}
	
	/*----------------------------
压缩BCD转10进制数
----------------------------*/

unsigned long int  BCDtoDec( unsigned char *bcd, int length)
	{
		//int  tmp;
		unsigned long dec = 0,dec1 = 0,dec2 = 0,dec3 =0,dec4 =0;
		if(length==1)
		{
			dec1 = ((bcd[0]>>4)&0x0F)*10 + (bcd[0]&0x0F);  
			dec = dec1;
		}
		if(length==2)
		{
			dec1 = ((bcd[0]>>4)&0x0F)*10 + (bcd[0]&0x0F);
			dec2 = ((bcd[1]>>4)&0x0F)*10 + (bcd[1]&0x0F);
			dec = dec1  + dec2*100;
		}
		if(length==3)
		{
			dec1 = ((bcd[0]>>4)&0x0F)*10 + (bcd[0]&0x0F);
			dec2 = ((bcd[1]>>4)&0x0F)*10 + (bcd[1]&0x0F);
			dec3 = ((bcd[2]>>4)&0x0F)*10 + (bcd[2]&0x0F);
			dec =  dec1  + dec2*100 + dec3*10000;
		}
		if(length==4)
		{
			dec1 = ((bcd[0]>>4)&0x0F)*10 + (bcd[0]&0x0F);
			dec2 = ((bcd[1]>>4)&0x0F)*10 + (bcd[1]&0x0F);
			dec3 = ((bcd[2]>>4)&0x0F)*10 + (bcd[2]&0x0F);
			dec4 = ((bcd[3]>>4)&0x0F)*10 + (bcd[3]&0x0F);
			dec =  dec1  + dec2*100 + dec3*10000 + dec4*100000;
		}
		
		return dec;
}
	

	void copy_array(unsigned char *obj_tmp,unsigned char *sours_tmp,unsigned char lenth_tmp)
{
	unsigned char i;
	for(i=0;i<lenth_tmp;i++)
	{
		obj_tmp[i] = sours_tmp[i];
	}
}

void delay_uart(void)
{
    volatile unsigned int ii,jj ;
    //asm("wdr");("wdr");
	for(ii=0;ii<400;ii++)
    {
        for(jj=0;jj<110;jj++);
    }
}
int HexToChar(unsigned char *Bcd,unsigned int Dec,unsigned int length)
{
	if(length==2)
	{
		Bcd[0] =  Dec&0xff;
		Bcd[1] = (Dec&0xff00)>>8;
	}
	if(length==3)
	{
		Bcd[0] =  Dec&0xff;
		Bcd[1] = (Dec&0xff00)>>8;
		Bcd[2] = (Dec&0xff0000)>>16;
	}
	return 0;
}
unsigned  int  ChartoHex( unsigned char *bcd,unsigned int length)
{
	//int  tmp;
	unsigned int dec = 0;
  if(length==2)
	{
  dec=(bcd[1]<<8)+bcd[0];
	}
   if(length==3)
	{
  dec=(bcd[2]<<16)+(bcd[1]<<8)+bcd[0];
	}
	return dec;
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
float my_exp(float x) 
{
    float result = 1.0f;
    float term = 1.0f;
    int i;
    for (i = 1; i <= 10; ++i) { // 假设10次幂级数足够近似exp函数
        term *= x / i;
        result += term;
    }
    return result;
}
float myln(float x)    
	{
    if (x <= 0) {
        // ln(x) 对于 x <= 0 是未定义的
        return 0;
    }

    float low = 0.0, high = x, guess = (low + high) / 2.0;

    // 使用二分法进行逼近
    for (int i = 0; i < 20; i++)/*i的范围是Ln计算结果的最大值，目前设为20*/
		{
        guess = (low + high) / 2.0;

        if ((high - low) < 0.000001) {/*0.01为精度*/
            // 达到所需的精度
            break;
        }

        float value = my_exp(guess);

        if (value < x) {
            low = guess;
        } else if (value > x) {
            high = guess;
        } else {
            // 找到了精确的解
            break;
        }
    }

    return guess;
}
	unsigned int ADtoTemp(unsigned int AD)
{
	
	 unsigned int T1;
	
	
		T1=344-41*myln(AD);
	
	return T1;
}
/***************************************数字生成字符串**********************************************/
void generate_chuan(unsigned char p[5],unsigned char a,unsigned char b,unsigned char c,unsigned char d)
	{
		p[0]=a+0x30;

		p[1]=b+0x30;

		p[2]=c+0x30;

		p[3]=d+0x30;

		p[4]='\0';	
	}
