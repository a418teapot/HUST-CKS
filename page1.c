#include "common.h"
#include "page1.h"

//��Ϊ��Ҫ����pageֵ������ҳ��ĺ�������int��
int p1(void)
{
	int page = 0,idk=0,passwordk=0,show=0;
	char temp;
	ACCOUNT input={0};
	
	//��ֹ�������תҳ��ʱ����
	clrmous(MouseX,MouseY);
	delay(100);
	page1_screen(input,show);
	/*ѭ������ͣ�ؼ���춯�����춯����pageֵ�ı䣬��תҳ��*/
	while(page == 0)
	{
		//��ȡ����λ�ú�״̬
		mou_pos(&MouseX,&MouseY,&press);
		
		//��¼��ť
		if(mouse_press(150, 380, 150+140, 380+30) == 1)
		{
			if(checkaccount(input))//��������Ƿ���ȷ
				page = 9;//����������
			else
			{
				setfillstyle(SOLID_FILL, WHITE);
				bar(0, 435, 640, 480);
				puthz(5,440,"�û������ڻ����벻��ȷ��",32,34,RED);
			}
			delay(100);
		}
		//�˳���ť
		else if(mouse_press(300, 380, 300+140, 380+30) == 1)
		{
			page = -1;//�˳�����
		}
		else if(mouse_press(200+165,225+60+35, 200+170+100, 225+60+60) == 1)
		{
			page = 5;//����-1����������ҳ����תѭ��
		}
		else if(mouse_press(160, 200, 160+300, 200+30) == 1)//�û�������򱻰���
		{	
			clrmous(MouseX,MouseY);
			setfillstyle(SOLID_FILL, WHITE);
			bar(0, 435, 640, 480);
			puthz(5,440,"���س�ȷ����",32,34,RED);
			delay(500);
			while(1)
			{
				if(bioskey(1))
				{
					
					temp=bioskey(0)&0x00ff;//��ȡ������ַ�
					if(temp!='\b'&&temp!='\n'&&temp!='\r')	//������벻Ϊ�س������˸����������������������
					{
						if(idk<=14)
						{
							if(('0'<=temp&&temp<='9')||('A'<=temp&&temp<='Z')||('a'<=temp&&temp<='z'))
							{
								input.id[idk]=temp;
								idk++;
								page1_screen(input,show);
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
							puthz(5,440,"��������15λ��",32,34,RED);
						}
					}
					else if(temp=='\b'&&idk>=0)		//����Ƿ�Ϊ�˸������������ǰһ���ַ�
					{
						if(idk>0)
							idk--;
						input.id[idk]='\0';
						
						page1_screen(input,show);
					}
					else
					{
						page1_screen(input,show);
						break;
					}
					clrmous(MouseX,MouseY);
					delay(100);
				}
			}
		}
		else if(mouse_press(160, 190+60+40, 160+300, 190+60+40+30) == 1)
		{	
			clrmous(MouseX,MouseY);
			setfillstyle(SOLID_FILL, WHITE);
			bar(0, 435, 640, 480);
			puthz(5,440,"���س�ȷ����",32,34,RED);
			while(1)
			{
				if(bioskey(1))
				{
					
					temp=bioskey(0)&0x00ff;//��ȡ������ַ�
					if(temp!='\b'&&temp!='\n'&&temp!='\r')	//������벻Ϊ�س������˸����������������������
					{
						if(passwordk<=14)
						{
							if(('0'<=temp&&temp<='9')||('A'<=temp&&temp<='Z')||('a'<=temp&&temp<='z'))
							{
								input.password[passwordk]=temp;
								passwordk++;
								page1_screen(input,show);
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
							puthz(5,440,"��������ʮ��λ��",32,34,RED);
						}
						
						
					}
					else if(temp=='\b'&&passwordk>=0)		//����Ƿ�Ϊ�˸������������ǰһ���ַ�
					{
						if(passwordk>0)
							passwordk--;
						input.password[passwordk]='\0';
						page1_screen(input,show);
					}
					else
					{
						page1_screen(input,show);
						break;
					}
					clrmous(MouseX,MouseY);
					delay(100);
				}
			}
		}
		else if(mouse_press(160+312, 192+60+40, 160+338, 190+60+40+28) == 1)//�������ѡ���ɫ����
		{
			show=!show;
			clrmous(MouseX,MouseY);
			page1_screen(input,show);
			
			delay(100);
		}
	}
	return page;
}

//����ҳ��1����
void page1_screen(ACCOUNT input,int show)
{
	int i;
	cleardevice();//����ǰ��ҳ������
	
	setbkcolor(WHITE);//����ɫ����
	puthz(150,170-80,"���˻�ũҩ����ϵͳ",32,35,BLUE);
	setfillstyle(SOLID_FILL, BLUE);//�û�����
	bar(160, 200, 160+300, 200+30);
	setfillstyle(SOLID_FILL, WHITE);
	bar(162, 202, 160+298, 200+28);
	puthz(90,210,"�û�����",16,18,BLUE);
	
	settextstyle(0,0,2);
	setcolor(BLUE);
	outtextxy(165,210, input.id);
	
	
	
	
	setfillstyle(SOLID_FILL, BLUE);//�����
	bar(160, 190+60+40, 160+300, 190+60+40+30);
	setfillstyle(SOLID_FILL, WHITE);
	bar(162, 192+60+40, 160+298, 190+60+40+28);
	puthz(90,200+60+40,"���룺",16,18,BLUE);
	
	setfillstyle(SOLID_FILL, BLUE);
	bar(160+310, 190+60+40, 160+340, 190+60+40+30); //��ʾ���븴ѡ��
	setfillstyle(SOLID_FILL, WHITE);
	bar(160+312, 192+60+40, 160+338, 190+60+40+28);
	puthz(160+350,200+60+40,"��ʾ����",16,18,BLUE);
	
	if(!show)
	{
		for(i=0;input.password[i]!='\0';i++)//������ʾ�������ַ�ȫ���滻Ϊ*
			input.password[i]='*';
	}
	else
	{
		setfillstyle(SOLID_FILL, BLUE);//����ʾ�����򽫸�ѡ����ʾΪѡ��״̬
		bar(160+314, 194+60+40, 160+336, 190+60+40+26);
	}
	settextstyle(0,0,2);
	setcolor(BLUE);
	outtextxy(165,200+60+40,input.password);

	
	puthz(200+170,225+60+40,"���ע�ᣡ",16,18,0xFFF0F5);
	
	setfillstyle(SOLID_FILL, BLUE);//�趨��¼��ť
	bar(150, 380, 150+140, 380+30);
	puthz(202,385,"��¼",16,18,WHITE);
	
	setfillstyle(SOLID_FILL, RED);//�趨�˳���ť
	bar(300, 380, 300+140, 380+30);
	puthz(352,385,"�˳�",16,18,WHITE);
	
	
}

int checkaccount(ACCOUNT input)//����û��Ƿ���ڣ������Ƿ���ȷ
{
	int i=0;
	ACCOUNT temp[10];
	FILE*fp = NULL;
	fp = fopen("acc.bin", "rb");
	rewind(fp);
	fread(temp, sizeof(ACCOUNT), 10, fp);
	for(i=0;i<10;i++)
	{
		if(temp[i].id[0]=='\0')//��ǰλ���Ƿ�Ϊ��,Ϊ����˵���޸��û�
		{
			break;
		}
		else if(strcmp(temp[i].id,input.id)==0)//�ȶ��Ƿ����ͬ����ע���û�
		{
			if(strcmp(temp[i].password,input.password)==0)//�ȶ������Ƿ���ȷ
			{
				fclose(fp);
				return 1;
			}
			else
			{
				fclose(fp);
				return 0;
			}
		}
	}
	fclose(fp);
	return 0;


	
}