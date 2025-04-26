#include "common.h"
#include "page8.h"

//��Ϊ��Ҫ����pageֵ������ҳ��ĺ�������int��
int p8()
{
	int page=0,pagenumber=1;
	plantstatus plantmap[30][20];
	illtype ill[20];
	readplantinfo(plantmap);
	readillinfo(ill);
	//��ֹ�������תҳ��ʱ����
	clrmous(MouseX,MouseY);
	delay(200);
	page8_screen(plantmap,pagenumber,ill);
	while(page==0)
	{
		//��ȡ����λ�ú�״̬
		mou_pos(&MouseX,&MouseY,&press);
		if(mouse_press(535, 445, 535+100, 445+25)==1)
		{
			page=2;
		}
		else if(mouse_press(375, 445, 375+100, 445+25)==1&&pagenumber<2)
		{
			pagenumber++;
			page8_screen(plantmap,pagenumber,ill);
		}
		else if(mouse_press(215, 445, 215+100, 445+25)==1&&pagenumber>1)
		{
			pagenumber--;
			page8_screen(plantmap,pagenumber,ill);
		}
	}
	return page;
	
}

//����ҳ��8����
void page8_screen(plantstatus (*plantmap)[20],int pagenumber,illtype *ill)
{
	int pesti[4]={0},i=0,j=0,temp=0,illcount[11]={0},max=-1;
	float k=0;
	char num[30];
	setbkcolor(WHITE);//����ɫ����
	cleardevice();//����ǰ��ҳ������
	puthz(120, 10,"ͳ����Ϣ",32,34,BLUE);
	if(pagenumber==1)
	{
		puthz(270, 20,"ũҩ������ͳ��",16,18,BLUE);
		
		setfillstyle(SOLID_FILL, BLUE);
		bar(30, 30,32, 500);
		
		puthz(10, 70,"һ",16,18,BLUE);
		puthz(10, 170,"��",16,18,BLUE);
		puthz(10, 270,"��",16,18,BLUE);
		puthz(10, 370,"��",16,18,BLUE);
		
		for(i=0;i<30;i++)
		{
			for(j=0;j<20;j++)
			{
				if(plantmap[i][j].plantcode==1)
				{
					pesti[0]+=ill[plantmap[i][j].illnumber-1].pesti[0];
					pesti[1]+=ill[plantmap[i][j].illnumber-1].pesti[1];
					pesti[2]+=ill[plantmap[i][j].illnumber-1].pesti[2];
					pesti[3]+=ill[plantmap[i][j].illnumber-1].pesti[3];
				}
			}
		}
		temp=-1;
		j=0;
		for(i=0;i<4;i++)//�ҳ�����ũҩ��Ϊ��׼
		{
			
			
			if(pesti[i]>temp)
			{
				j=i;
				temp=pesti[i];
			}
		}
		setfillstyle(SOLID_FILL, YELLOW);
		for(i=0;i<4;i++)//�ҳ�����ũҩ��Ϊ��׼
		{
			if(pesti[j]==0)
			{
				break;
			}
			k=(float)pesti[i]/pesti[j];
			temp=35+500*k;
			if(i==j)
			{
				bar(33, 50+i*100,535, 110+i*100);
			}
			else
			{
				bar(33, 50+i*100,temp, 110+i*100);
			}
			
			
		}
		for(i=0;i<4;i++)//�ҳ�����ũҩ��Ϊ��׼
		{
			num_to_str8(pesti[i],num);
			settextstyle(0,0,2);
			setcolor(BLUE);
			outtextxy(50,65+i*100, num);//��ʾ����
		}
		
		
	}
	if(pagenumber==2)
	{
		puthz(270, 20,"�߲�ͳ��",16,18,BLUE);
		
		setfillstyle(SOLID_FILL, BLUE);
		bar(30, 30,32, 500);
		
		for(i=0;i<30;i++)
		{
			for(j=0;j<20;j++)
			{
				if(plantmap[i][j].plantcode==1)
				{
					illcount[plantmap[i][j].illnumber-1]++;
				}
			}
		}
		temp=-1;
		for(i=0;i<=10;i++)
		{
			if(illcount[i]>=temp)
			{
				max=i;
				temp=illcount[i];
			}
		}
		temp=0;
		j=0;
		for(i=0;i<=10;i++)
		{
			if(illcount[i]!=0)
			{
				k=(float)illcount[i]/illcount[max];
				switch(temp)
				{
					case 0:
						setfillstyle(SOLID_FILL, LIGHTRED);
						temp++;
						break;
					case 1:
						setfillstyle(SOLID_FILL, LIGHTCYAN);

						temp++;
						break;
						
					case 2:
						setfillstyle(SOLID_FILL, BROWN);
						temp=0;
						break;
				}
				bar(33,45+20*j,33+400*k,65+20*j);
				num_to_str8(illcount[i],num);
				settextstyle(0,0,2);
				setcolor(BLUE);
				outtextxy(35+400*k,50+20*j, num);//��ʾ����
				settextstyle(0,0,2);
				setcolor(BLUE);
				outtextxy(35,50+20*j, ill[i].illname);//��ʾ����
				j++;
			}
		}
		
	}
	setfillstyle(SOLID_FILL, RED);//�趨��ɫ��
	bar(535, 445, 535+100, 445+25);//������ҳ
	puthz(550, 450,"����",16,18,BLUE);
	
	if(pagenumber<2)
	{
		setfillstyle(SOLID_FILL, RED);//�趨��ɫ��
		bar(375, 445, 375+100, 445+25);//
		puthz(390, 450,"��һҳ",16,18,BLUE);
	}
	
	if(pagenumber>1)
	{
		setfillstyle(SOLID_FILL, RED);//�趨��ɫ��
		bar(215, 445, 215+100, 445+25);//����
		puthz(230, 450,"��һҳ",16,18,BLUE);
	}
}

void num_to_str8(int i,char *numstr)//����ת���ַ���
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

void reverseString8(char *str,int length) //�ߵ��ַ���
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

void readplantinfo(plantstatus (*read)[20])//��ȡ������Ϣ
{
	FILE* fp=NULL;
	fp = fopen("plant.bin", "rb");
	if (fp == NULL) {
        printf("Failed to open file");
        return;
    }
	rewind(fp);
    fread(read, sizeof(plantstatus), 20*30, fp);
	fclose(fp);
}

void readillinfo(illtype *read)//��ȡ����
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
