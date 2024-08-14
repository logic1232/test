#include "tool.h"
/*----------------------------
10进制数转压缩BCD
----------------------------*/

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
		Bcd[1] =  Dec&0xff;
		Bcd[0] = (Dec&0xff00)>>8;
	}
	if(length==3)
	{
		Bcd[2] =  Dec&0xff;
		Bcd[1] = (Dec&0xff00)>>8;
		Bcd[0] = (Dec&0xff0000)>>16;
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

