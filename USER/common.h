#ifndef __COMMON_H
#define __COMMON_H

#include "sys.h"
#include "string.h"
#include "stdlib.h"
#include "stdio.h"


extern u8 UUID[18];
extern u8 StrNull[18];
extern u8 UUIDGroup[10][18];


void ResetUUIDGroup(void);
u16 MyStrstr(u8 *str1, u8 *str2, u16 str1_len, u16 str2_len);
u8 GetDatBit(u32 dat);
u32 GetADV(u8 len);
void IntToString(u8 *DString,u32 Dint,u8 zero_num);
u32 StringToInt(u8 *String);
unsigned short find_str(unsigned char *s_str, unsigned char *p_str, unsigned short count, unsigned short *seek);
int search_str(unsigned char *source, unsigned char *target);
unsigned short get_str1(unsigned char *source, unsigned char *begin, unsigned short count1, unsigned char *end, unsigned short count2, unsigned char *out);
unsigned short get_str2(unsigned char *source, unsigned char *begin, unsigned short count, unsigned short length, unsigned char *out);
unsigned short get_str3(unsigned char *source, unsigned char *out, unsigned short length);


void ShowSerialNumber(void);





































#endif
