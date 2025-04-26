#include "common.h"
#include "page7.h"

//��Ϊ��Ҫ����pageֵ������ҳ��ĺ�������int��
int p7(plantstatus *plantinfo,int x,int y)
{
	illtype ill[20];
	int page=0;
	FILE *fp=NULL;
	//��ֹ�������תҳ��ʱ����
	clrmous(MouseX,MouseY);
	if ((fp = fopen("ill.bin", "rb")) == NULL) 
	{
		setfillstyle(SOLID_FILL, WHITE);
		bar(0, 435, 640, 480);
		puthz(5,440,"�߲�δ���ã��뷵�������߲�",32,34,RED);
		while(mouse_press(535, 445, 535+100, 445+25) != 1)
			return 0;
	}
	fclose(fp);
	readdata7(ill);
	page7_screen(*plantinfo,x,y,ill);
	
	
	
	while(page==0)
	{
		//��ȡ����λ�ú�״̬
		mou_pos(&MouseX,&MouseY,&press);
		if(mouse_press(535, 445, 535+100, 445+25) == 1)
		{
			page=2;
		}
		else if(mouse_press(95, 30, 200, 50) == 1)
		{
			page7_screen(*plantinfo,x,y,ill);
			inputnum7(plantinfo);
			page7_screen(*plantinfo,x,y,ill);
		}
		else if(mouse_press(210, 30, 350, 60) == 1)
		{
			if(plantinfo->plantcode==0)
			{
				plantinfo->plantcode=1;
				plantinfo->illnumber=1;
			}
			else if(plantinfo->plantcode==1)
			{
				plantinfo->plantcode=0;
				plantinfo->illnumber=0;
			}
			page7_screen(*plantinfo,x,y,ill);
			clrmous(MouseX,MouseY);
			delay(500);
			page7_screen(*plantinfo,x,y,ill);
		}
	}
	return page;
}

//����ҳ��7����
void page7_screen(plantstatus plantinfo,int x,int y,illtype *ill)
{
	int i;
	char numstr[30]="\0";
	char temp[30]="\0";
	cleardevice();//����ǰ��ҳ������
	setbkcolor(WHITE);//����ɫ����
	puthz(10,10,"������꣺",16,18,BLUE);//��ʾ
	settextstyle(0,0,2);
	setcolor(BLUE);
	
	
	num_to_str7(x,temp);
	strcat(numstr, "(");
	strcat(numstr, temp);
	num_to_str7(y,temp);
	strcat(numstr, ",");
	strcat(numstr, temp);
	strcat(numstr, ")");
	settextstyle(0,0,2);
	setcolor(BLUE);
	outtextxy(95,15, numstr);//��ʾ����
	
	
	
	if(plantinfo.plantcode==0)
	{
		puthz(10,30,"������δ����",16,18,GREEN);//��ʾ
		
		setfillstyle(SOLID_FILL, RED);
		bar(210, 30, 350, 60);
		puthz(220, 35,"��Ϊ����",16,18,GREEN);
	}
	else
	{
		setfillstyle(SOLID_FILL, BLUE);//�趨��
		bar(95, 30, 200, 50);//��������
		setfillstyle(SOLID_FILL, WHITE);//�趨��
		bar(97, 32, 198, 48);//��������
		
		
		setfillstyle(SOLID_FILL, RED);
		bar(210, 30, 350, 60);
		puthz(220, 35,"��Ϊ����",16,18,BLUE);
		
		num_to_str7(plantinfo.illnumber,temp);
		puthz(10,30,"�߲���ţ�",16,18,BLUE);//��ʾ
		settextstyle(0,0,2);
		setcolor(BLUE);
		outtextxy(100,32, temp);//��ʾ�߲���ţ��ɸ��ģ�
		
		
		
		puthz(10,60,"�߲����ƣ�",16,18,BLUE);//��ʾ
		settextstyle(0,0,2);
		setcolor(BLUE);
		outtextxy(100,62, ill[(plantinfo.illnumber)-1].illname);//��ʾ�߲�����
		
		puthz(10,90,"�߲�����ũҩ����һ�����������ģ���λ����",16,18,BLUE);//��ʾ�߲�����ũҩ��
		numstr[0]='\0';
		num_to_str7(ill[plantinfo.illnumber-1].pesti[0],temp);
		strcat(numstr, temp);
		num_to_str7(ill[plantinfo.illnumber-1].pesti[1],temp);
		strcat(numstr, ",");
		strcat(numstr, temp);
		num_to_str7(ill[plantinfo.illnumber-1].pesti[2],temp);
		strcat(numstr, ",");
		strcat(numstr, temp);
		num_to_str7(ill[plantinfo.illnumber-1].pesti[3],temp);
		strcat(numstr, ",");
		strcat(numstr, temp);
		
		outtextxy(400,95, numstr);
	}
	
	
	
	setfillstyle(SOLID_FILL, RED);//�趨��ɫ��
	bar(535, 445, 535+100, 445+25);//������ҳ
	puthz(550, 450,"����",16,18,BLUE);
}

void num_to_str7(int i,char *numstr)//����ת���ַ���
{
	int x=0;
	if (i == 0) {
        numstr[0] = '0';
        numstr[1] = '\0';
        return;
    }
	
	
	for(x=0;i!=0;x++)
	{
		
		numstr[x]=(i%10)+'0';
		i=i/10;
	}
	numstr[x]='\0';
	reverseString7(numstr,x);
}

void reverseString7(char *str,int length) //�ߵ��ַ���
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


void inputnum7(plantstatus *plantinfo)//��������
{
	char temp;
	char instr[5]="\0";
	int numk=0;
	plantinfo->illnumber=0;
	while(1)
	{
		if(bioskey(1))
		{
			settextstyle(0,0,2);
			setcolor(BLUE);
			setfillstyle(SOLID_FILL, WHITE);//�趨��
			bar(97, 32, 198, 48);//��������
			outtextxy(100,34, instr);//����ԭ���ݲ���ʾ������
			
			temp=bioskey(0)&0x00ff;//��ȡ������ַ�
			if(temp!='\b'&&temp!='\n'&&temp!='\r')	//������벻Ϊ�س������˸����������������������
			{
				if(numk<=1)
				{
					if('0'<=temp&&temp<='9')
					{
						instr[numk]=temp;
						numk++;
						instr[numk]='\0';
						plantinfo->illnumber=str_to_int7(instr);
						
						settextstyle(0,0,2);
						setcolor(BLUE);
						setfillstyle(SOLID_FILL, WHITE);//�趨��
						bar(97, 32, 198, 48);//��������
						outtextxy(100,32, instr);//��ʾ�߲���ţ��ɸ��ģ�
					}
					else
					{
						settextstyle(0,0,2);
						setcolor(BLUE);
						setfillstyle(SOLID_FILL, WHITE);
						bar(0, 435, 640, 480);
						puthz(5,440,"���������֣�",32,34,RED);
					}
				}
				else
				{
					settextstyle(0,0,2);
					setcolor(BLUE);
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
				plantinfo->illnumber=str_to_int7(instr);
				
				settextstyle(0,0,2);
				setcolor(BLUE);
				setfillstyle(SOLID_FILL, WHITE);//�趨��
				bar(97, 32, 198, 48);//��������
				outtextxy(100,32, instr);//����ԭ���ݲ���ʾ������
			}
			else
			{
				settextstyle(0,0,2);
				setcolor(BLUE);
				setfillstyle(SOLID_FILL, WHITE);//�趨��
				bar(97, 32, 198, 48);//��������
				outtextxy(100,32, instr);//����ԭ���ݲ���ʾ������
				break;
			}
			clrmous(MouseX,MouseY);
			delay(100);
		}
	}
}



int str_to_int7(char *str) //�ַ���ת������
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

void writedata7(illtype *write)//ȫ����д��
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

void readdata7(illtype *read)//��ȡ����
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