#ifndef _PAGE7_H_
#define _PAGE7_H_

int p7(plantstatus *plantinfo,int x,int y);
/*函数功能：页面7*/

void page7_screen(plantstatus plantinfo,int x,int y,illtype ill[20]);//绘制页面6

void num_to_str7(int i,char *numstr);

void reverseString7(char *str,int length);

void inputnum7(plantstatus *plantinfo);//输入数字

int str_to_int7(char *str); //字符串转换整数

void writedata7(illtype *write);//全覆盖写入

void readdata7(illtype *read);//读取数据


#endif