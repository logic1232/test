#ifndef __MENU_H
#define __MENU_H
#include <stdint.h>
	typedef struct {
	uint8_t fault_type ;
	int fault_value;
	char fault_year;
	char fault_month;
	char fault_data;
	char fault_hour;
	char fault_min;
	char fault_sec;		
		
} fault;
 void MEUN();
 void Time1();
void UART_LCD_process(void)    ;
#endif