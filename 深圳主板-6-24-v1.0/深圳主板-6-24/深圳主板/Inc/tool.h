#ifndef __tool_H
#define __tool_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"
int DectoBCD(unsigned char *Bcd,unsigned int Dec, unsigned int length);
unsigned long int  BCDtoDec( unsigned char *bcd, int length);
void copy_array(unsigned char *obj_tmp,unsigned char *sours_tmp,unsigned char lenth_tmp);
int DectoBCD_NUM(unsigned char *Bcd,unsigned int Dec, unsigned int length);
void delay_uart(void);
int HexToChar(unsigned char *Bcd,unsigned int Dec,unsigned int length);
unsigned  int  ChartoHex( unsigned char *bcd,unsigned int length);
//int max_of_three(int a, int b, int c);
#ifdef __cplusplus
}
#endif
#endif /*__ pinoutConfig_H */

