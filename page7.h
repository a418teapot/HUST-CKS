#ifndef _PAGE7_H_
#define _PAGE7_H_

int p7(plantstatus *plantinfo,int x,int y);
/*�������ܣ�ҳ��7*/

void page7_screen(plantstatus plantinfo,int x,int y,illtype ill[20]);//����ҳ��6

void num_to_str7(int i,char *numstr);

void reverseString7(char *str,int length);

void inputnum7(plantstatus *plantinfo);//��������

int str_to_int7(char *str); //�ַ���ת������

void writedata7(illtype *write);//ȫ����д��

void readdata7(illtype *read);//��ȡ����


#endif