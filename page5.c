#include "common.h"
#include "page5.h"

//��Ϊ��Ҫ����pageֵ������ҳ��ĺ�������int��
int p5(void)
{
	int page = 0,idk=0,passwordk=0,passcheckk=0,show=0;
	char passcheck[15]={0};
	char temp;
	ACCOUNT write={0};
	//��ֹ�������תҳ��ʱ����
	clrmous(MouseX,MouseY);
	delay(100);
	page5_screen(write.id,write.password,passcheck,show);
	/*ѭ������ͣ�ؼ���춯�����춯����pageֵ�ı䣬��תҳ��*/
	while(page == 0)
	{
		//��ȡ����λ�ú�״̬
		mou_pos(&MouseX,&MouseY,&press);
		//ע�ᰴť
		if(mouse_press(150, 350, 150+140, 350+30) == 1)
		{
			if(write.id[0]=='\0')//�Ƿ���д���û���Ϣ
			{
				setfillstyle(SOLID_FILL, WHITE);
				bar(0, 435, 640, 480);
				puthz(5,440,"����д�û�����",32,34,RED);
			}
			else if(write.password[0]=='\0'||strcmp(write.password,passcheck)!=0)//����������Ƿ�Ϊ�ջ����������������Ƿ���ͬ
			{
				setfillstyle(SOLID_FILL, WHITE);
				bar(0, 435, 640, 480);
				puthz(5,440,"��ȷ�����벻Ϊ������������������ͬ��",32,34,RED);
			}
			else
			{
				creataccount(write);
			}
			delay(100);
		}
		//ȡ����ť
		else if(mouse_press(300, 350, 300+140, 350+30) == 1)
		{
			page = 1;//ֱ�ӷ��ص�¼����
			delay(100);
		}
		else if(mouse_press(160, 200, 160+300, 200+30) == 1)
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
						if(idk<=14)
						{
							if(('0'<=temp&&temp<='9')||('A'<=temp&&temp<='Z')||('a'<=temp&&temp<='z'))
							{
								write.id[idk]=temp;
								idk++;
								page5_screen(write.id,write.password,passcheck,show);
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
					else if(temp=='\b'&&idk>=0)		//����Ƿ�Ϊ�˸������������ǰһ���ַ�
					{
						if(idk>0)
							idk--;
						write.id[idk]='\0';
						
						page5_screen(write.id,write.password,passcheck,show);
					}
					else
					{
						page5_screen(write.id,write.password,passcheck,show);
						break;
					}
					clrmous(MouseX,MouseY);
					delay(100);
				}
			}
		}
		else if(mouse_press(160, 245, 160+300, 245+30) == 1)
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
								write.password[passwordk]=temp;
								passwordk++;
								page5_screen(write.id,write.password,passcheck,show);
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
						write.password[passwordk]='\0';
						
						page5_screen(write.id,write.password,passcheck,show);
					}
					else
					{
						page5_screen(write.id,write.password,passcheck,show);
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
						if(passcheckk<=14)
						{
							if(('0'<=temp&&temp<='9')||('A'<=temp&&temp<='Z')||('a'<=temp&&temp<='z'))
							{
								passcheck[passcheckk]=temp;
								passcheckk++;
								page5_screen(write.id,write.password,passcheck,show);
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
					else if(temp=='\b'&&passcheckk>=0)		//����Ƿ�Ϊ�˸������������ǰһ���ַ�
					{
						if(passcheckk>0)
							passcheckk--;
						passcheck[passcheckk]='\0';
						
						page5_screen(write.id,write.password,passcheck,show);
					}
					else
					{
						page5_screen(write.id,write.password,passcheck,show);
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
			page5_screen(write.id,write.password,passcheck,show);
			
			delay(100);
		}
	}
	return page;
}

//����ע�����
void page5_screen(char *idt,char *passwordt,char *passcheckt,int show)
{
	int i=0;
	char id[15]={0},password[15]={0},passcheck[15]={0};
	strcpy(id,idt);
	strcpy(password,passwordt);
	strcpy(passcheck,passcheckt);
	cleardevice();//����ǰ��ҳ������
	
	setbkcolor(WHITE);//����ɫ����
	puthz(150,170-80,"���˻�����ϵͳע��",32,35,0xFFF0F5);
	setfillstyle(SOLID_FILL, 0xFFF0F5);//�趨�û�����
	bar(160, 200, 160+300, 200+30);
	setfillstyle(SOLID_FILL, WHITE);
	bar(162, 202, 160+298, 200+28);
	puthz(90,210,"�û�����",16,18,0xFFF0F5);
	
	
	settextstyle(0,0,2);
	setcolor(0xFFF0F5);
	outtextxy(165,210, id);
	
	
	setfillstyle(SOLID_FILL, 0xFFF0F5);
	bar(160+310, 190+60+40, 160+340, 190+60+40+30); //��ʾ���븴ѡ��
	setfillstyle(SOLID_FILL, WHITE);
	bar(160+312, 192+60+40, 160+338, 190+60+40+28);
	puthz(160+350,200+60+40,"��ʾ����",16,18,0xFFF0F5);
	
	if(!show)
	{
		for(i=0;password[i]!='\0';i++)//������ʾ�������ַ�ȫ���滻Ϊ*
			password[i]='*';
		for(i=0;passcheck[i]!='\0';i++)//������ʾ�������ַ�ȫ���滻Ϊ*
			passcheck[i]='*';
	}
	else
	{
		setfillstyle(SOLID_FILL, 0xFFF0F5);//����ʾ�����򽫸�ѡ����ʾΪѡ��״̬
		bar(160+314, 194+60+40, 160+336, 190+60+40+26);
	}
	
	
	
	
	setfillstyle(SOLID_FILL, 0xFFF0F5);//�趨�����
	bar(160, 245, 160+300, 245+30);
	setfillstyle(SOLID_FILL, WHITE);
	bar(162, 247, 160+298, 245+28);
	puthz(54,255,"�������룺",16,18,0xFFF0F5);
	
	settextstyle(0,0,2);
	setcolor(0xFFF0F5);
	outtextxy(165,255, password);
	
	setfillstyle(SOLID_FILL, 0xFFF0F5);//�趨ȷ�������
	bar(160, 190+60+40, 160+300, 190+60+40+30);
	setfillstyle(SOLID_FILL, WHITE);
	bar(162, 192+60+40, 160+298, 190+60+40+28);
	puthz(18,200+60+40,"�ٴ��������룺",16,18,0xFFF0F5);
	
	settextstyle(0,0,2);
	setcolor(0xFFF0F5);
	outtextxy(165,200+60+40,passcheck);
	
	setfillstyle(SOLID_FILL, 0xFFF0F5);//�趨ע�ᰴť
	bar(150, 350, 150+140, 350+30);
	puthz(202,355,"ע��",16,18,WHITE);
	
	setfillstyle(SOLID_FILL, RED);//�趨ȡ����ť
	bar(300, 350, 300+140, 350+30);
	puthz(352,355,"����",16,18,WHITE);
	
	
}

void creataccount(ACCOUNT write)
{
	int i=0;
	ACCOUNT temp[10];
	FILE*fp = NULL;
	fp = fopen("acc.bin", "rb");
	rewind(fp);
	fread(temp, sizeof(ACCOUNT), 10, fp);
	for(i=0;i<10;i++)
	{
		if(temp[i].id[0]=='\0')//��ǰλ���Ƿ�Ϊ��
		{
			break;//Ϊ����ֱ�ӿ�ʼд��
		}
		else if(strcmp(temp[i].id,write.id)==0)//�ȶ��Ƿ����ͬ����ע���û�
		{
			setfillstyle(SOLID_FILL, WHITE);
			bar(0, 435, 640, 480);
			puthz(5,440,"���û��ѱ�ע�ᣡ",32,34,RED);
			return;
		}
	}
	if(i==10)
	{
		setfillstyle(SOLID_FILL, WHITE);
		bar(0, 435, 640, 480);
		puthz(5,440,"ע���û����������������ע�ᣡ",32,34,RED);
	}
	else
	{
		fclose(fp);
		fp = fopen("acc.bin", "wb");
		rewind(fp);
		temp[i]=write;
		fwrite(temp,sizeof(ACCOUNT),10,fp);
		setfillstyle(SOLID_FILL, WHITE);
		bar(0, 435, 640, 480);
		puthz(5,440,"ע��ɹ���",32,34,RED);
	}
	fclose(fp);
}

