#ifndef _PAGE8_H_
#define _PAGE8_H_

int p8();
/*�������ܣ�ҳ��8*/

void page8_screen(plantstatus (*read)[20],int pagenumber,illtype *ill);//����ҳ��8

void num_to_str8(int i,char *numstr);//����ת���ַ���
void reverseString8(char *str,int length); //�ߵ��ַ���
void readplantinfo(plantstatus (*read)[20]);//��ȡ������Ϣ
void readillinfo(illtype *read);//��ȡ����


#endif
