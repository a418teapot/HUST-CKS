#include "common.h"
#include "page6.h"

//��Ϊ��Ҫ����pageֵ������ҳ��ĺ�������int��
int p6()
{
	illtype ill[20];
	int page=0;
	int i,j;
	int pagenumber=1;
	FILE*fp=NULL;
	//��ֹ�������תҳ��ʱ����
	clrmous(MouseX,MouseY);
	for(i=0;i<=19;i++)
	{
		ill[i].pesti[0]=0;
		ill[i].pesti[1]=0;
		ill[i].pesti[2]=0;
		ill[i].pesti[3]=0;
		
		for(j=0;j<=19;j++)
		{
			ill[i].illname[j]='\0';
		}
	}
	if ((fp = fopen("ill.bin", "rb")) == NULL) 
	{
		fclose(fp);
		fp = fopen("ill.bin", "wb");
		fwrite(ill,sizeof(illtype),20,fp);
		fclose(fp);
	}
	readdata(ill);
	
	page6_screen(pagenumber,ill);
	delay(100);

	fclose(fp);
	
	/*ѭ������ͣ�ؼ���춯�����춯����pageֵ�ı䣬��תҳ��*/

	while(page == 0)
	{
		
		//��ȡ����λ�ú�״̬
		mou_pos(&MouseX,&MouseY,&press);
		for(i=10*(pagenumber-1);i<=10*(pagenumber)&&i<=19;i++)
		{
			if(mouse_press(50, 20+i*47, 200, 40+i*47) == 1)
			{
				page6_screen(pagenumber,ill);
				inputstr(i,ill,pagenumber);
			}
			else if(mouse_press(240, 20+i*47, 285, 40+i*47) == 1)
			{
				page6_screen(pagenumber,ill);
				inputnum(i,ill,pagenumber,0);
			}
			else if(mouse_press(290, 20+i*47, 290+45, 40+i*47) == 1)
			{
				page6_screen(pagenumber,ill);
				inputnum(i,ill,pagenumber,1);
			}
			else if(mouse_press(340, 20+i*47, 340+45, 40+i*47) == 1)
			{
				page6_screen(pagenumber,ill);
				inputnum(i,ill,pagenumber,2);
			}
			else if(mouse_press(390, 20+i*47, 390+45, 40+i*47) == 1)
			{
				page6_screen(pagenumber,ill);
				inputnum(i,ill,pagenumber,3);
			}
			else if(mouse_press(435, 445, 435+100, 445+25) == 1)
			{
				writedata(ill);//ȫ����д��
				page=2;
				
			}
		}
		
	}
	return page;
	
}

//����ҳ��6����
void page6_screen(int pagenumber,illtype *ill)
{
	int i;
	char numstr[20]="\0";
	cleardevice();//����ǰ��ҳ������
	setbkcolor(WHITE);//����ɫ����
	puthz(10,2,"���",16,18,BLUE);//��ʾ
	puthz(60,2,"�߲�����",16,18,BLUE);//��ʾ
	puthz(250,2,"�߲�����ũҩ����һ�����������ģ���λ����",16,18,BLUE);//��ʾ
	for(i=10*(pagenumber-1);i<=10*(pagenumber)&&i<=19;i++)
	{
		num_to_str(i+1,numstr);
		settextstyle(0,0,2);
		setcolor(BLUE);
		outtextxy(10,17+i*47, numstr);//��ʾ���
		
		setfillstyle(SOLID_FILL, BLUE);//�趨��
		bar(50, 20+i*47, 200, 40+i*47);//���������
		setfillstyle(SOLID_FILL, WHITE);//�趨��
		bar(52, 22+i*47, 198, 38+i*47);//���������
		outtextxy(54,24+i*47, ill[i].illname);//��ʾ
		
		setfillstyle(SOLID_FILL, BLUE);//�趨��
		bar(240, 20+i*47, 285, 40+i*47);//ҩ�������0
		setfillstyle(SOLID_FILL, WHITE);//�趨��
		bar(242, 22+i*47, 285-2, 38+i*47);//ҩ�������
		num_to_str(ill[i].pesti[0],numstr);
		outtextxy(244,24+i*47, numstr);//��ʾ����ҩ��
		
		setfillstyle(SOLID_FILL, BLUE);//�趨��
		bar(290, 20+i*47, 290+45, 40+i*47);//ҩ�������1
		setfillstyle(SOLID_FILL, WHITE);//�趨��
		bar(292, 22+i*47, 290+45-2, 38+i*47);//ҩ�������
		num_to_str(ill[i].pesti[1],numstr);
		outtextxy(294,24+i*47, numstr);//��ʾ����ҩ��
		
		setfillstyle(SOLID_FILL, BLUE);//�趨��
		bar(340, 20+i*47, 340+45, 40+i*47);//ҩ�������2
		setfillstyle(SOLID_FILL, WHITE);//�趨��
		bar(342, 22+i*47, 340+45-2, 38+i*47);//ҩ�������
		num_to_str(ill[i].pesti[2],numstr);
		outtextxy(344,24+i*47, numstr);//��ʾ����ҩ��
		
		setfillstyle(SOLID_FILL, BLUE);//�趨��
		bar(390, 20+i*47, 390+45, 40+i*47);//ҩ�������3
		setfillstyle(SOLID_FILL, WHITE);//�趨��
		bar(392, 22+i*47, 390+45-2, 38+i*47);//ҩ�������
		num_to_str(ill[i].pesti[3],numstr);
		outtextxy(394,24+i*47, numstr);//��ʾ����ҩ��
		
		
		
		
		
	}
	setfillstyle(SOLID_FILL, RED);//�趨��ɫ��
	bar(435, 445, 435+100, 445+25);//������ҳ
	puthz(461, 450,"����",16,18,BLUE);
}

void num_to_str(int i,char *numstr)//����ת���ַ���
{
	
	int x=0;
	for(x=0;i!=0;x++)
	{
		
		numstr[x]=(i%10)+'0';
		i=i/10;
	}
	numstr[x]='\0';
	reverseString(numstr,x);
}

void reverseString(char *str,int length) //�ߵ��ַ���
{
	int i = 0;
    char temp;
    
    // ʹ������ָ�룬һ�����ַ����Ŀ�ͷ����ƶ�����һ�����ַ�����ĩβ��ǰ�ƶ�����������ָ����ַ�
    for (i=0; i<length/2; i++) 
	{
        temp=str[i];
        str[i]=str[length-i-1];
        str[length-i-1]=temp;
    }
}

void inputstr(int illnum,illtype *ill,int pagenumber)//������ĸ
{
	char temp;
	int namek=0;
	int i=0;
	for(i=0;i<=19;i++)
		ill[illnum].illname[i]='\0';
	while(1)
	{
		if(bioskey(1))
		{
			page6_screen(pagenumber,ill);
			temp=bioskey(0)&0x00ff;//��ȡ������ַ�
			if(temp!='\b'&&temp!='\n'&&temp!='\r')	//������벻Ϊ�س������˸����������������������
			{
				if(namek<=8)
				{
					if(('0'<=temp&&temp<='9')||('A'<=temp&&temp<='Z')||('a'<=temp&&temp<='z'))
					{
						ill[illnum].illname[namek]=temp;
						namek++;
						page6_screen(pagenumber,ill);
					}
					else
					{
						setfillstyle(SOLID_FILL, WHITE);
						bar(0, 435, 640, 480);
						puthz(5,440,"�������Сд��ĸ�����֣�",32,34,RED);
					}
				}
				else
				{
					setfillstyle(SOLID_FILL, WHITE);
					bar(0, 435, 640, 480);
					puthz(5,440,"�����������ƣ�",32,34,RED);
				}
				
				
			}
			else if(temp=='\b'&&namek>=0)		//����Ƿ�Ϊ�˸������������ǰһ���ַ�
			{
				if(namek>0)
				{
					namek--;
				}
				ill[illnum].illname[namek]='\0';
				
				page6_screen(pagenumber,ill);
			}
			else
			{
				page6_screen(pagenumber,ill);
				break;
			}
			clrmous(MouseX,MouseY);
			delay(100);
		}
	}
}


void inputnum(int illnum,illtype *ill,int pagenumber,int pestinum)//��������
{
	char temp;
	char instr[10]={0};
	int numk=0;
	ill[illnum].pesti[pestinum]=0;
	while(1)
	{
		if(bioskey(1))
		{
			page6_screen(pagenumber,ill);
			temp=bioskey(0)&0x00ff;//��ȡ������ַ�
			if(temp!='\b'&&temp!='\n'&&temp!='\r')	//������벻Ϊ�س������˸����������������������
			{
				if(numk<=2)
				{
					if('0'<=temp&&temp<='9')
					{
						instr[numk]=temp;
						numk++;
						ill[illnum].pesti[pestinum]=str_to_int(instr);
						
						
						page6_screen(pagenumber,ill);
					}
					else
					{
						setfillstyle(SOLID_FILL, WHITE);
						bar(0, 435, 640, 480);
						puthz(5,440,"���������֣�",32,34,RED);
					}
				}
				else
				{
					setfillstyle(SOLID_FILL, WHITE);
					bar(0, 435, 640, 480);
					puthz(5,440,"�����������ƣ�",32,34,RED);
				}
				
				
			}
			else if(temp=='\b'&&numk>=0)		//����Ƿ�Ϊ�˸������������ǰһ���ַ�
			{
				if(numk>0)
				{
					numk--;
				}
				instr[numk]='\0';
				ill[illnum].pesti[pestinum]=str_to_int(instr);
				page6_screen(pagenumber,ill);
			}
			else
			{
				page6_screen(pagenumber,ill);
				break;
			}
			clrmous(MouseX,MouseY);
			delay(100);
		}
	}
}



int str_to_int(char *str) //�ַ���ת������
{
    int num = 0;
    int i = 0;
    
    // ��������ַ�
    while (str[i] >= '0' && str[i] <= '9') {
        // ��λ�ۼ�
        num = num * 10 + (str[i] - '0');
        i++;
    }
    
    return num;
}

void writedata(illtype *write)//ȫ����д��
{
	FILE* fp=NULL;
	fp = fopen("ill.bin", "wb");
	if (fp == NULL) {
        printf("Failed to open file");
        return;
    }
	rewind(fp);
	fwrite(write,sizeof(illtype),20,fp);
	fclose(fp);
}

void readdata(illtype *read)//��ȡ����
{
	FILE*fp = NULL;
	fp = fopen("ill.bin", "rb");
	if (fp == NULL) {
        printf("Failed to open file");
        return;
    }
	rewind(fp);
	fread(read, sizeof(illtype), 20, fp);
	fclose(fp);
}
