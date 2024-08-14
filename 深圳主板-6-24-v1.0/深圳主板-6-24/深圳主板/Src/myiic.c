#include "myiic.h"
#include "delay.h"

 
void SDA_IN(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
  GPIO_InitStruct.Pin = AT24C512_I2C_SDA_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
//  switch(AT24C512_I2C_SDA_Pin)
//	{
//		case GPIO_PIN_0:{ AT24C512_I2C_SDA_GPIO_Port->MODER&=0XFFFFFFFC; break;}
//		case GPIO_PIN_1:{ AT24C512_I2C_SDA_GPIO_Port->MODER&=0XFFFFFFF3; break;}
//		case GPIO_PIN_2:{ AT24C512_I2C_SDA_GPIO_Port->MODER&=0XFFFFFFCF; break;}
//		case GPIO_PIN_3:{ AT24C512_I2C_SDA_GPIO_Port->MODER&=0XFFFFFF3F; break;}
//		case GPIO_PIN_4:{ AT24C512_I2C_SDA_GPIO_Port->MODER&=0XFFFFFCFF; break;}
//		case GPIO_PIN_5:{ AT24C512_I2C_SDA_GPIO_Port->MODER&=0XFFFFF3FF; break;}
//		case GPIO_PIN_6:{ AT24C512_I2C_SDA_GPIO_Port->MODER&=0XFFFFCFFF; break;}
//		case GPIO_PIN_7:{ AT24C512_I2C_SDA_GPIO_Port->MODER&=0XFFFF3FFF; break;}
//		case GPIO_PIN_8:{ AT24C512_I2C_SDA_GPIO_Port->MODER&=0XFFFCFFFF; break;}
//		case GPIO_PIN_9:{ AT24C512_I2C_SDA_GPIO_Port->MODER&=0XFFF3FFFF; break;}
//		case GPIO_PIN_10:{ AT24C512_I2C_SDA_GPIO_Port->MODER&=0XFFCFFFFF; break;}
//		case GPIO_PIN_11:{ AT24C512_I2C_SDA_GPIO_Port->MODER&=0XFF3FFFFF; break;}
//		case GPIO_PIN_12:{ AT24C512_I2C_SDA_GPIO_Port->MODER&=0XFCFFFFFF; break;}
//		case GPIO_PIN_13:{ AT24C512_I2C_SDA_GPIO_Port->MODER&=0XF3FFFFFF; break;}
//		case GPIO_PIN_14:{ AT24C512_I2C_SDA_GPIO_Port->MODER&=0XCFFFFFFF; break;}
//		case GPIO_PIN_15:{ AT24C512_I2C_SDA_GPIO_Port->MODER&=0X3FFFFFFF; break;}
//	}
}

void SDA_OUT(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
  GPIO_InitStruct.Pin = AT24C512_I2C_SDA_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
	
//  switch(AT24C512_I2C_SDA_Pin)
//	{
//		case GPIO_PIN_0:{ AT24C512_I2C_SDA_GPIO_Port->MODER&=0XFFFFFFFC;AT24C512_I2C_SDA_GPIO_Port->MODER|=(u32)1<<0; break;}
//		case GPIO_PIN_1:{ AT24C512_I2C_SDA_GPIO_Port->MODER&=0XFFFFFFF3;AT24C512_I2C_SDA_GPIO_Port->MODER|=(u32)1<<2; break;}
//		case GPIO_PIN_2:{ AT24C512_I2C_SDA_GPIO_Port->MODER&=0XFFFFFFCF;AT24C512_I2C_SDA_GPIO_Port->MODER|=(u32)1<<4; break;}
//		case GPIO_PIN_3:{ AT24C512_I2C_SDA_GPIO_Port->MODER&=0XFFFFFF3F;AT24C512_I2C_SDA_GPIO_Port->MODER|=(u32)1<<6; break;}
//		case GPIO_PIN_4:{ AT24C512_I2C_SDA_GPIO_Port->MODER&=0XFFFFFCFF;AT24C512_I2C_SDA_GPIO_Port->MODER|=(u32)1<<8; break;}
//		case GPIO_PIN_5:{ AT24C512_I2C_SDA_GPIO_Port->MODER&=0XFFFFF3FF;AT24C512_I2C_SDA_GPIO_Port->MODER|=(u32)1<<10; break;}
//		case GPIO_PIN_6:{ AT24C512_I2C_SDA_GPIO_Port->MODER&=0XFFFFCFFF;AT24C512_I2C_SDA_GPIO_Port->MODER|=(u32)1<<12; break;}
//		case GPIO_PIN_7:{ AT24C512_I2C_SDA_GPIO_Port->MODER&=0XFFFF3FFF;AT24C512_I2C_SDA_GPIO_Port->MODER|=(u32)1<<14; break;}
//		case GPIO_PIN_8:{ AT24C512_I2C_SDA_GPIO_Port->MODER&=0XFFFCFFFF;AT24C512_I2C_SDA_GPIO_Port->MODER|=(u32)1<<16; break;}
//		case GPIO_PIN_9:{ AT24C512_I2C_SDA_GPIO_Port->MODER&=0XFFF3FFFF;AT24C512_I2C_SDA_GPIO_Port->MODER|=(u32)1<<18; break;}
//		case GPIO_PIN_10:{ AT24C512_I2C_SDA_GPIO_Port->MODER&=0XFFCFFFFF;AT24C512_I2C_SDA_GPIO_Port->MODER|=(u32)1<<20; break;}
//		case GPIO_PIN_11:{ AT24C512_I2C_SDA_GPIO_Port->MODER&=0XFF3FFFFF;AT24C512_I2C_SDA_GPIO_Port->MODER|=(u32)1<<22; break;}
//		case GPIO_PIN_12:{ AT24C512_I2C_SDA_GPIO_Port->MODER&=0XFCFFFFFF;AT24C512_I2C_SDA_GPIO_Port->MODER|=(u32)1<<24; break;}
//		case GPIO_PIN_13:{ AT24C512_I2C_SDA_GPIO_Port->MODER&=0XF3FFFFFF;AT24C512_I2C_SDA_GPIO_Port->MODER|=(u32)1<<26; break;}
//		case GPIO_PIN_14:{ AT24C512_I2C_SDA_GPIO_Port->MODER&=0XCFFFFFFF;AT24C512_I2C_SDA_GPIO_Port->MODER|=(u32)1<<28; break;}
//		case GPIO_PIN_15:{ AT24C512_I2C_SDA_GPIO_Port->MODER&=0X3FFFFFFF;AT24C512_I2C_SDA_GPIO_Port->MODER|=(u32)1<<30; break;}
//	}
}
 
//����IIC��ʼ�ź�
void IIC_Start(void)
{
	SDA_OUT();     //sda�����
  IIC_SDA_HIGH;	  	  
	IIC_SCL_HIGH;
	delay_us(1);
	IIC_SDA_LOW;//START:when CLK is high,DATA change form high to low 
	delay_us(1);
	IIC_SCL_LOW;//ǯסI2C���ߣ�׼�����ͻ�������� 
}	  
//����IICֹͣ�ź�
void IIC_Stop(void)
{
	SDA_OUT();//sda�����
	IIC_SCL_LOW;
	IIC_SDA_LOW;//STOP:when CLK is high DATA change form low to high
 	delay_us(1);
	IIC_SCL_HIGH; 
	IIC_SDA_HIGH;//����I2C���߽����ź�
	delay_us(1);							   	
}
//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
u8 IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	SDA_IN();      //SDA����Ϊ����  
	IIC_SDA_HIGH;
	delay_us(1);	   
	IIC_SCL_HIGH;
	delay_us(1);	 
	while(READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC_Stop();
			return 1;
		}
	}
	IIC_SCL_LOW;//ʱ�����0 	   
	return 0;  
} 
//����ACKӦ��
void IIC_Ack(void)
{
	IIC_SCL_LOW;
	SDA_OUT();
	IIC_SDA_LOW;
	delay_us(1);
	IIC_SCL_HIGH;
	delay_us(1);
	IIC_SCL_LOW;
}
//������ACKӦ��		    
void IIC_NAck(void)
{
	IIC_SCL_LOW;
	SDA_OUT();
	IIC_SDA_HIGH;
	delay_us(1);
	IIC_SCL_HIGH;
	delay_us(1);
	IIC_SCL_LOW;
}					 				     
//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��			  
void IIC_Send_Byte(u8 txd)
{                        
   u8 t;   
	 SDA_OUT(); 	    
   IIC_SCL_LOW;//����ʱ�ӿ�ʼ���ݴ���
    for(t=0;t<8;t++)
    {              
        //IIC_SDA=(txd&0x80)>>7;
		if((txd&0x80)>>7)
			IIC_SDA_HIGH;
		else
			IIC_SDA_LOW;
		txd<<=1; 	  
		delay_us(1);   //��TEA5767��������ʱ���Ǳ����
		IIC_SCL_HIGH;
		delay_us(1); 
		IIC_SCL_LOW;	
		delay_us(1);
    }	 
} 	    
//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
u8 IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_IN();//SDA����Ϊ����
    for(i=0;i<8;i++ )
	{
        IIC_SCL_LOW;  
        delay_us(1);
		IIC_SCL_HIGH;
        receive<<=1;
        if(READ_SDA)receive++;   
		delay_us(1); 
    }					 
    if (!ack)
        IIC_NAck();//����nACK
    else
        IIC_Ack(); //����ACK   
    return receive;
}


