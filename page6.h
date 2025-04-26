#ifndef _PAGE6_H_
#define _PAGE6_H_

int p6();
/*函数功能：页面6*/

void page6_screen(int pagenumber,illtype ill[20]);//绘制页面6

void num_to_str(int i,char *numstr);//数字转字符串

void reverseString(char *str,int length); //颠倒字符串

void inputstr(int illnum,illtype *ill,int pagenumber);//输入字母

void inputnum(int illnum,illtype *ill,int pagenumber,int pestinum);//输入数字

int str_to_int(char *str); //字符串转换整数



void writedata(illtype *write);//全覆盖写入


void readdata(illtype *read);//读取数据

#endif