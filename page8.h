#ifndef _PAGE8_H_
#define _PAGE8_H_

int p8();
/*函数功能：页面8*/

void page8_screen(plantstatus (*read)[20],int pagenumber,illtype *ill);//绘制页面8

void num_to_str8(int i,char *numstr);//数字转换字符串
void reverseString8(char *str,int length); //颠倒字符串
void readplantinfo(plantstatus (*read)[20]);//读取作物信息
void readillinfo(illtype *read);//读取数据


#endif
