
#ifndef __TOOL_H
#define __TOOL_H
void value_to_ascii(int value, char *ascii_array);
int HexToChar(unsigned char *Bcd,unsigned int Dec,unsigned int length);
void xianshishuju(unsigned int dat);
void xianshishuju2(unsigned int dat);
void xianshishuju3(unsigned int dat);
void xianshishuju_dianliu(unsigned int dat);
	unsigned int ADtoTemp(unsigned int AD);
	int DectoBCD(unsigned char *Bcd,unsigned int Dec, unsigned int length) ;
	void generate_chuan(unsigned char p[5],unsigned char a,unsigned char b,unsigned char c,unsigned char d);
#endif