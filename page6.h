#ifndef _PAGE6_H_
#define _PAGE6_H_

int p6();
/*�������ܣ�ҳ��6*/

void page6_screen(int pagenumber,illtype ill[20]);//����ҳ��6

void num_to_str(int i,char *numstr);//����ת�ַ���

void reverseString(char *str,int length); //�ߵ��ַ���

void inputstr(int illnum,illtype *ill,int pagenumber);//������ĸ

void inputnum(int illnum,illtype *ill,int pagenumber,int pestinum);//��������

int str_to_int(char *str); //�ַ���ת������



void writedata(illtype *write);//ȫ����д��


void readdata(illtype *read);//��ȡ����

#endif