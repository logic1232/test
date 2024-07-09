#ifndef __DISPLAY_ZIKU_H_
#define __DISPLAY_ZIKU_H_



//extern unsigned char  temp_frame[32];
extern unsigned char or_process(unsigned char *dp1,unsigned char *dp2);
extern unsigned char display_graphic_8x16(unsigned char page,unsigned char column,unsigned char  *dp);
extern  unsigned char display_graphic_8x16(unsigned char page,unsigned char column,unsigned char *dp);
//extern unsigned char Lcd12864_Write16_1CnCHAR(unsigned char F_rever,unsigned char  x, unsigned char y, unsigned char *cn);
extern 	unsigned char display_graphic_8x16_fanxian(unsigned char page,unsigned char column,unsigned char *dp);
extern unsigned char display_graphic_1x16(unsigned char page,unsigned char column,unsigned char *dp);
extern void display_kaiguan(unsigned char x0,unsigned char y0,unsigned char Flag);
extern unsigned char display_graphic_16x16(unsigned char page,unsigned char column,unsigned char *dp);
extern unsigned char display_graphic_quanping(unsigned char page,unsigned char column,unsigned char *dp);
extern void display_kaiguan_frame(unsigned char x0,unsigned char y0,unsigned char Flag);
extern void display_jiaozhun_frame(unsigned char x0,unsigned char y0,unsigned char Flag);
extern unsigned char Lcd12864_Write8CnCHAR(unsigned char F_rever,unsigned char  x, unsigned char y, unsigned char *cn);
extern void display_ASCIIstring_8x16_frame(unsigned char page,unsigned char column,unsigned char *text);
extern void display_kaiguan_fanxian(unsigned char x0,unsigned char y0,unsigned char Flag);
extern void display_jiaozhun_fanxian(unsigned char x0,unsigned char y0,unsigned char Flag);
extern void display_sanjiao(unsigned char x0,unsigned char y0,unsigned char black_up,unsigned char black_down);
extern void display_ASCIIstring_8x16(unsigned char page,unsigned char column,unsigned char *text);
extern void display_xianfangkuai(unsigned char x0,unsigned char y0,unsigned char daxiao,unsigned char yuan_fang);
extern unsigned char display_graphic_2x16(unsigned char page,unsigned char column,unsigned char *dp);
extern void display_biankuang(unsigned char  x0,unsigned char  x1,unsigned char  y0,unsigned char  y1);
extern void display_shouzhi(unsigned char x0,unsigned char y0);
extern void display_ASCIIstring_8x16_fanxian(unsigned char page,unsigned char column,unsigned char *text);
extern unsigned char Lcd12864_Write16CnCHAR(unsigned char F_rever,unsigned char x, unsigned char y, unsigned char *cn);

extern void display_ASCIIstring_8x16(unsigned char page,unsigned char column,unsigned char *text);

#endif

