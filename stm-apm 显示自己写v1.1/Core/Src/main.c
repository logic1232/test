/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
�����ɴ޼�����������д���������ߵ�һ�θ��������ĳ����д�������������ĵط���������£������Ѿ�ȫ�����ñ�ע
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "rtc.h"
#include "tim.h"
#include "gpio.h"
#include "menu.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
 #include "lcd.h"
#include "display_ziku.h"
#include "menu.h"
#include "disp.h"
#include "usart.h"
#include "tool.h"
#include<stdbool.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
extern char f_f;
extern int write_ptr;  // д��ָ�룬��ʼλ��Ϊ0
extern int read_ptr;   // ��ȡָ�룬��ʼλ��Ϊ0
extern volatile unsigned char	tmp_uart_rx[50];
extern char F_AEorREorALLE; //�й�����0or�޹�����1or�ܵ���2��־λ
extern int a1; //�˵�����ָ��
bool F_initialization=1;
int F_Y,F_Ypro;
int i;
int key;
int F_mainchange;
char F_MAINormenu;   //�жϷ��滹�ǲ˵���־λ
char F_MAINorprotect;  //�жϷ��滹�Ǳ�����־λ
int a;    //�˵�λ��ָ��
int b;    //�˵���������ָ��
extern unsigned char   mima[4];        //���������
extern	char qiehuan; 
extern int current_page ;     //���ݽ���ҳ��
	extern UART_HandleTypeDef huart1;
	extern char F_adjustbegin; //��ʼУ׼��־λ
extern volatile unsigned char F_Dataval;
unsigned char F_LEAK_OPEN_CLOSE,F_open;   //���ڷ���������ֲ�ͬ���ͷֺ�բ
extern char F_jiaozhuned; 
char F_FENHEZHA;
uint8_t  max_value;  //ad����¶�
uint8_t  tem=0;      //�жϸ߷ַ�բ��һ��
extern char isfenzha;            //��բָʾ
uint16_t ADC_Convertedvalue[8];
volatile unsigned char TEM_UP_arry[6]={50,60,70,80,90,100},TEM_DOWN_arry[5]={10,20,30,40,50};;
uint8_t temperature[8];
extern unsigned char baud,TH_TEM_UP,TH_TEM_DOWN,TH_TEM_UPtemp,TH_TEM_DOWNtemp,baudtemp;   //����ҳ��λָ��
extern volatile unsigned char  F_disp_jg,F_disp_tr,F_hezha_state,F_fenzha_state,F_gz_disp,gz_disp,F_ch;      //���Ϻͷֺ�բ״̬��ر�־λ
uint8_t  count1 = 0;
char F_T;
int time_1,time_2,f_pc,p_c_old,p_c_day;
uint8_t previous_button_state = GPIO_PIN_SET;
extern fault fault_buffer[20]; // �����ⲿ����
extern volatile signed int HT7038_buf1[300],HT7038_buf11[300] ;
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void uart_com_process(void);
void OPEN_CLOSE(); 

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_TIM1_Init();
  MX_RTC_Init();
  MX_ADC_Init();
    MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
   initial_lcd();
//   clear_screen();




  	HAL_TIM_Base_Start_IT(&htim1);
HAL_ADC_Start_DMA(&hadc,(uint32_t*)ADC_Convertedvalue,8);
HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4,GPIO_PIN_RESET);
clear_screen();

//	display_graphic_32x32(1,32*0,cheng1);
 HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_SET);	
  /* USER CODE END 2 */
//unsigned char lishijilu_1[]="10";
//	  display_ASCIIstring_8x16(3,39,lishijilu_1);	
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */\
 
if(key==KEY_AFFIRM_PRES)     //�ϵ����Ƿ��ʼ��
{
	
	
F_initialization=0;
	USART_LCD_Transmit(1,5);
	


}
	


HAL_UART_Receive_IT(&huart1,(uint8_t*)tmp_uart_rx,1); 

  while (1)
  {

OPEN_CLOSE(); //Ӳ���ֺ�բ�ź�

	 key = key_scan(0);	 
//faultdisp();
	 // warning_setting();
	  MEUN();
	//  menu_fault();
//	timechange()  ;
	  uart_com_process();   //���ڽ��պ���

	  if(key==KEY_AFFIRM_PRES&&F_MAINormenu==0&&F_gz_disp==0x0F)    //F_MAINormenu==0�����棬F_MAINormenu==1�˵�����
{
	F_MAINormenu=7;
	clear_screen();
}


else if(key==KEY_GOBACK_PRES&&(F_MAINormenu==1||F_MAINormenu==2||F_MAINormenu==4||F_MAINormenu==5||(F_MAINormenu==6&&F_AEorREorALLE==0)||F_MAINormenu==8||F_MAINormenu==9)&&F_gz_disp==0x0F)    //��λ���������˵�
{
	clear_screen();
	f_f=1;
	F_Y=0;                                                //�ص����������еĵ�λλ��ָ��ɶ��ȫ������
	a=0;
	F_Ypro=0;
	F_AEorREorALLE=0;
	F_MAINormenu=10;
		F_adjustbegin=0;
	current_page=0;
	F_jiaozhuned=0;
	qiehuan=0;
mima[0]=0;
	mima[1]=0;
	mima[2]=0;
	mima[3]=0;
}
else if(key==KEY_GOBACK_PRES&&F_MAINormenu==6&&F_AEorREorALLE!=0&&F_gz_disp==0x0F)   //��λ������������
{
		clear_screen();
	F_AEorREorALLE=0;
	
}
		else  if(key==KEY_GOBACK_PRES&&(F_MAINormenu==12||F_MAINormenu==13))
{
	clear_screen ();
	current_page=0;
	 F_MAINormenu=4;
}
else if(key==KEY_GOBACK_PRES&&(F_MAINormenu==10||F_MAINormenu==7)&&F_AEorREorALLE==0&&F_gz_disp==0x0F)    //��λ������������
{
	a1=0;
	clear_screen();
	F_Y=0;                                                //�ص����������еĵ�λλ��ָ��ɶ��ȫ������
	a=0;
	F_Ypro=0;
	F_MAINormenu=0;
		F_adjustbegin=0;
	current_page=0;
	F_jiaozhuned=0;
	qiehuan=0;
mima[0]=0;
	mima[1]=0;
	mima[2]=0;
	mima[3]=0;
}
else if(key==KEY_UP_PRES&&F_MAINormenu==0&&F_gz_disp==0x0F)     //���������������д���ˣ�
{        
	
 F_MAINormenu=2;
clear_screen();
	
}else if(key==KEY_LEFT_PRES&&F_MAINormenu==0&&F_gz_disp==0x0F)     //�������բ��¼��ѯ������д���ˣ�
{        
	F_mainchange++;
	if(F_mainchange>9)
	{F_mainchange=0;}
// F_MAINormenu=4;
clear_screen();
	
}
else if(key==KEY_RIGHRT_PRES&&F_MAINormenu==0&&F_gz_disp==0x0F)     //�������բ��¼��ѯ������д���ˣ�
{        
	F_mainchange--;
	if(F_mainchange<0)
	{F_mainchange=9;
	}
// F_MAINormenu=4;
clear_screen();
	
}
else if(key==KEY_DOWN_PRES&&F_MAINormenu==0&&F_gz_disp==0x0F)     //�����У׼���棨����д���ˣ�
{        
	
 F_MAINormenu=15;
clear_screen();
	
}

else if(key==KEY_LEAK_PRES&&F_MAINormenu==0&&F_gz_disp==0x0F)    //©������
{
		if(isfenzha==1)                    //ֻ���ں�բ״̬����Ч
		{
			//F_MAINormenu=3;
			F_LEAK_OPEN_CLOSE=1;
			F_open=0;
			USART_LCD_Transmit(7,2) ;
			//F_FENHEZHA =1;
			clear_screen();
		   
	}
}else if(key==KEY_OPEN_PRES&&F_MAINormenu==0&&F_gz_disp==0x0F)    //��բ��ť
{
		if(isfenzha==1)                           //ֻ���ں�բ״̬����Ч
		{
			F_MAINormenu=3;                          //��ʾ���
			F_LEAK_OPEN_CLOSE=2;                 //���ڷ������
			F_open=0;							//���ڷ������
			USART_LCD_Transmit(7,2) ;
			F_FENHEZHA =1;                      //��ʾ���
		   clear_screen();
	}
}
		else if(key==KEY_GOBACK&&F_MAINormenu==0&&F_gz_disp==0x0F)    //��բ��ť
{
		if(isfenzha==0)                           //ֻ���ڷ�բ״̬����Ч
		{
			F_MAINormenu=3;
			F_LEAK_OPEN_CLOSE=3;
			USART_LCD_Transmit(7,2) ;
			F_FENHEZHA =2;
			clear_screen();
		}  
	}
	 
if(F_T==5)
{
	waring_compare();
}

  /* USER CODE END 3 */
}
}
void get_ADCtoT()                   //adת�¶�
{
	
	for(int i=0;i<8;i++)
	{
	temperature[i]=ADtoTemp((unsigned int)ADC_Convertedvalue[i]);
	}
	  max_value = temperature[0];
//	temperature[i]=ADC_Convertedvalue[i];
	 for (int i = 1; i < 8; i++) 
	{
        if (temperature[i] > max_value) 
		{
            max_value = temperature[i];
			tem=i;
        }
    }
	 if(max_value>TEM_UP_arry[TH_TEM_UP])//TEM_UP_arry[TH_TEM_UP]
	{
		 count1++;
		
	}
	else 
	{
		if(count1>1)
		count1--;
		//HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3,GPIO_PIN_SET);
	}
	
	 if(count1<0){count1=0;}
	 

		 
}
/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_HSI14
                              |RCC_OSCILLATORTYPE_LSE;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSI14State = RCC_HSI14_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.HSI14CalibrationValue = 16;
    RCC_OscInitStruct.LSEState = RCC_LSE_ON;
//  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL6;
  RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC|RCC_PERIPHCLK_USART1;
   PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK1;
  PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
  
}

/* USER CODE BEGIN 4 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)   //��ʱ���ص�  һ��Ķ�ʱ��
{
    if(htim==(&htim1))
    {
		 get_ADCtoT();
	// F_mainchange=1;
		time_1++;	
	F_T++;
		if(F_T>10)
		{
//			clear_screen ();
//			F_gz_disp=0;     //cjmtest
			 if(count1>5)
	{
			F_open=1;
		F_LEAK_OPEN_CLOSE=2;
		USART_LCD_Transmit(7,2);              //�����¶�
	}
			F_T=0;
}
		if(time_1>3600)
		{
			time_1=0;
			time_2++;
		}
		if(time_2>24)
		{
			time_2=0;
			f_pc=1;
		}
		if(f_pc==1)
		{f_pc=0;
		p_c_day=HT7038_buf11[18]-p_c_old;
		p_c_old=HT7038_buf11[18];
		
		}
		
		
    }
		
}
void uart_com_process(void)      //���ڴ�����
{
	
	  while (read_ptr != write_ptr)        //���ڳɹ����ձ�־λ
	{
		HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_15);
		UART_LCD_process();       //���ڽ��պ�����ֵ��ʵʱ���ݺ͵�λ��Ϣ
		    //����λ��Ϣ��ֵ����ʱ���������жϵ�λ�Ƿ�ı�
		F_Dataval = 0;
		
	}
}
void OPEN_CLOSE()  //Ӳ���ֺ�բ�ź�
{
	if(key==KEY_OPEN_hardware_PRES){     //��բ
		F_LEAK_OPEN_CLOSE=2;
		F_open=0;
		USART_LCD_Transmit(7,2); //��������
	}
	if(key==KEY_CLOSE_hardware_PRES){    //��բ
		F_LEAK_OPEN_CLOSE=3;
		USART_LCD_Transmit(7,2); //��������
	}
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
