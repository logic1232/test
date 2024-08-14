#include "usart.h"
//#include "stm32f0xx_hal_uart.h"
/* USER CODE END 0 */
const int BUFFER_SIZE = 4;
int write_ptr = 0;  // 写入指针，初始位置为0
int read_ptr = 0;   // 读取指针，初始位置为0
UART_HandleTypeDef huart1;
uint8_t Send[100];  //发送数据数组
/* USART1 init function */
volatile unsigned char	tmp_uart_rx[50];
volatile unsigned char F_re_sta,F_re_sta1,Addr_len,Addr_len1,F_guangbo,F_benji,F_addr;
volatile unsigned char ctrl_code,cs_data1,ctrl_code1,data_len_temp,cs_data,guozhitao,Addr_array[6],Addr_array1[6], Addr_len,data_len,data_len1,data_len_temp1;
unsigned char  Lcd_data_array[4][100];
uint8_t LCD_Receive_last[100]; //保存数据数组
volatile unsigned char F_Dataval=0;
extern  volatile unsigned char DI0,DI1,DI2,DI3;
void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 38400;
  huart1.Init.WordLength = UART_WORDLENGTH_9B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_EVEN;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */
HAL_UART_Receive_IT(&huart1,(uint8_t*)tmp_uart_rx,1);  
  /* USER CODE END USART1_Init 2 */

}

void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspInit 0 */

  /* USER CODE END USART1_MspInit 0 */
    /* USART1 clock enable */
    __HAL_RCC_USART1_CLK_ENABLE();

    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**USART1 GPIO Configuration
    PB6     ------> USART1_TX
    PB7     ------> USART1_RX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF0_USART1;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* USART1 interrupt Init */
    HAL_NVIC_SetPriority(USART1_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART1_IRQn);
  /* USER CODE BEGIN USART1_MspInit 1 */

  /* USER CODE END USART1_MspInit 1 */
  }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{

  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspDeInit 0 */

  /* USER CODE END USART1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART1_CLK_DISABLE();

    /**USART1 GPIO Configuration
    PB6     ------> USART1_TX
    PB7     ------> USART1_RX
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_6|GPIO_PIN_7);

    /* USART1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USART1_IRQn);
  /* USER CODE BEGIN USART1_MspDeInit 1 */

  /* USER CODE END USART1_MspDeInit 1 */
  }
}



void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    uint8_t tmp = tmp_uart_rx[0];			

    if(huart == &huart1) // 485-显示
    {
        if(F_re_sta == 0)  // 无开始标志，等待帧头
        {
            if(tmp != 0x68) 
            {
                HAL_UART_Receive_IT(&huart1, (uint8_t*)tmp_uart_rx, 1);  
                return; // 若非帧头且未置接收标志则不接收 
            }
            if(tmp == 0x68) // 帧头且无开始标志，则开始接收并置标志
            {
                data_len_temp = 0;
                F_re_sta = 2;
                HAL_UART_Receive_IT(&huart1, (uint8_t*)tmp_uart_rx, 1);  
                return;
            }
        }
        else if(F_re_sta == 2) // 开始接收地址数据
        {
            if(Addr_len == 1)
            {
                if(tmp == 0x68)
                {
                    Addr_len = 0;
                    F_re_sta = 3;
                    HAL_UART_Receive_IT(&huart1, (uint8_t*)tmp_uart_rx, 1);  
                    return;
                }
                else
                {
                    F_re_sta = 0;
                    Addr_len = 0;
                    HAL_UART_Receive_IT(&huart1, (uint8_t*)tmp_uart_rx, 1);  
                    return;
                }
            }
            else
            {
			
                Addr_array[Addr_len] = tmp;
                Addr_len++;
                HAL_UART_Receive_IT(&huart1, (uint8_t*)tmp_uart_rx, 1);  
                return;
            }
        }
        else if(F_re_sta == 3) // 接收控制码
        {
            ctrl_code = tmp;
            if(ctrl_code <= 0x80) // 主站发出的命令帧 80 为保留
            {
                F_re_sta = 4;
                HAL_UART_Receive_IT(&huart1, (uint8_t*)tmp_uart_rx, 1);  
                return;
            }
            else
            {
                F_re_sta = 0;
                HAL_UART_Receive_IT(&huart1, (uint8_t*)tmp_uart_rx, 1);  
                return;
            }
        }
        else if(F_re_sta == 4) // 接收数据长度
        {
            data_len = tmp;
            if(data_len <= 208)
            {
                if(data_len == 0)
                {
                    F_re_sta = 6;
                    HAL_UART_Receive_IT(&huart1, (uint8_t*)tmp_uart_rx, 1);  
                    return;
                }
                else
                {
                    F_re_sta = 5;
                    HAL_UART_Receive_IT(&huart1, (uint8_t*)tmp_uart_rx, 1);  
                    return;
                }
            }
            else
            {
                F_re_sta = 0;
                HAL_UART_Receive_IT(&huart1, (uint8_t*)tmp_uart_rx, 1);  
                return;
            }	
        }
        else if(F_re_sta == 5) // 开始接收数据
        {
            if(data_len > 0)
            {
					
                Lcd_data_array[write_ptr][data_len_temp] = tmp;
                data_len_temp++;
                HAL_UART_Receive_IT(&huart1, (uint8_t*)tmp_uart_rx, 1);  
                if(data_len_temp == data_len)
                {
                    F_re_sta = 6;
                }
                if(data_len_temp > data_len)
                {
                    F_re_sta = 0;
                    HAL_UART_Receive_IT(&huart1, (uint8_t*)tmp_uart_rx, 1);  
                    return;					
                }
                HAL_UART_Receive_IT(&huart1, (uint8_t*)tmp_uart_rx, 1);  
                return;
            }
        }
        else if(F_re_sta == 6) // 接收校验码
        {
			
            cs_data = tmp;
            F_re_sta = 7;
            HAL_UART_Receive_IT(&huart1, (uint8_t*)tmp_uart_rx, 1);  
            return;
        }
        else if(F_re_sta == 7) // 接收帧尾
        {
            if(tmp == 0x16)
            {
                F_re_sta = 0;
                F_Dataval=1;
				 write_ptr = (write_ptr + 1) % BUFFER_SIZE;  // 循环写入
				//HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_3);
                HAL_UART_Receive_IT(&huart1, (uint8_t*)tmp_uart_rx, 1);  
                return;
            }
            else
            {
                F_re_sta = 0;
                HAL_UART_Receive_IT(&huart1, (uint8_t*)tmp_uart_rx, 1); 
                return;
            }
        }
    }
}

void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
  /* Prevent unused argument(s) compilation warning */
 HAL_StatusTypeDef ERR;
	int i = 0;
  if(HAL_UART_GetError(huart) & HAL_UART_ERROR_ORE)
   {
     __HAL_UART_FLUSH_DRREGISTER(huart);  //读DR寄存器，就可以清除ORE错误标志位
   }
   
	if(huart->Instance == USART1){
		__HAL_UNLOCK(&huart1);
		HAL_UART_Receive_IT(&huart1,(uint8_t*)tmp_uart_rx,1);  
//		HAL_UART_Receive_IT(&huart1, (uint8_t *)&UART1_arr, 1);   //
			
	}
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_UART_ErrorCallback can be implemented in the user file.
   */
}

void Clear_Send_Data()  //清除发送数组和标志位
{
	for(uint8_t i=0;i<100;i++)
	{
		Send[i] = 0;    
	}

}
void LCD_Uart_prepare(uint8_t tmp)  //加帧头，地址，识别码  Send[9]开始为数据域
{
	unsigned char i;
	Clear_Send_Data();  //清除要发送的数据
	Send[0]=Send[2] = 0x68;//起始符 
	Send[1] =  0xA0;    //1为地址码
	
	if(tmp==0x00 || tmp==0x10)
	{
		if(tmp==0x00)
		{
		  Send[3]	= 0x51;   //控制码51 主站发出应答帧  
      for(i=0;i<4;i++)
			Send[5+i] = LCD_Receive_last[5+i]; //数据识别码			
		}
		else if(tmp==0x10)
		{
			Send[3]	= 0x14;   //控制码51 主站写数据
			Send[5] = DI3;
			Send[6] = DI2;
			Send[7] = DI1;
			Send[8] = DI0;    //数据识别码
		}
	}
	else if(tmp==0x01)
	{
		Send[3]	= 0x71;  //71从站异常应答帧
		Send[4] = 1 ;
//		Send[5] = Err_State; //异常类型
	}
}
void LCD_Send_Data(uint8_t *buf,uint8_t length)  //发送指定长度数据
{
	for(uint8_t i=0;i<length;i++)
	{
		HAL_UART_Transmit(&huart1,&buf[i],1,100);		///	
//		while(huart3.gState != HAL_UART_STATE_READY)
//		{}
	}	
}
void Write_or_Readresponse(uint8_t tmp,unsigned char len,unsigned char *array_temp)
{
	
	unsigned char i,cs_temp;
	cs_temp = 0;
	LCD_Uart_prepare(tmp);      //主站正常应答帧
	Send[4] = 4 + len;      //数据域总长度为数据加上四个标识位
	
	for(i=0;i<len;i++)
	{
		Send[9+i] = array_temp[i];   //数据部分
	}
	
	for(i=0;i<(9+len);i++)   //校验码处理
	{
		cs_temp =  Send[i] + cs_temp;
	}
	Send[9+len]  = cs_temp;   
	Send[10+len] = 0x16;
	//HAL_UART_Transmit(&huart1,&Send[i],11+len,0xffff);
  LCD_Send_Data(Send,11+len);  //发送读数据应答数据帧
}
/* USER CODE END 1 */