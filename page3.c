#include "common.h"
#include "page3.h"

//��Ϊ��Ҫ����pageֵ������ҳ��ĺ�������int��
int p3(int*mapxx,int*mapyy,int*size)
{
	int page = 0,mapx=*mapxx,mapy=*mapyy,map[2];//��ͼ��С
	char temp;
	//��ֹ�������תҳ��ʱ����
	clrmous(MouseX,MouseY);
	map[0]=mapx;map[1]=mapy;
	
	page3_screen(mapx,mapy,size,0);
	delay(100);
	
	
	/*ѭ������ͣ�ؼ���춯�����춯����pageֵ�ı䣬��תҳ��*/
	while(page == 0)
	{
		//��ȡ����λ�ú�״̬
		mou_pos(&MouseX,&MouseY,&press);
		
		//�����תҳ�����ת��ҳ��2����
		if(mouse_press(5, 420, 5+100, 420+25) == 1)
		{
			page = 2;//ҳ��2
		}
		else if(mouse_press(148, 6, 148+22, 6+20) == 1)
		{
			if(mapx<20)
			mapx++;
			page3_screen(mapx,mapy,size,0);
			delay(100);
		}
		else if(mouse_press(148, 66, 148+22, 66+20) == 1)
		{
			if(mapx>1)
			mapx--;
			page3_screen(mapx,mapy,size,0);
			delay(100);
		}
		else if(mouse_press(228, 6, 228+22, 6+20) == 1)
		{
			if(mapy<20)
			mapy++;
			page3_screen(mapx,mapy,size,0);
			delay(100);
		}
		else if(mouse_press(228, 66, 228+22, 66+20) == 1)
		{
			if(mapx>1)
			mapy--;
			page3_screen(mapx,mapy,size,0);
			delay(100);
		}
		else if(mouse_press(498,98,570,132) == 1)
		{
			*size=0;
			page3_screen(mapx,mapy,size,1);
			while(1)
			{
				if(bioskey(1))
				{
					temp=bioskey(0)&0x00ff;//��ȡ������ַ�
					if(temp!='\b'&&temp!='\n'&&temp!='\r')	//������벻Ϊ�س�����������������������
					{
						if('0'<=temp&&temp<='9')
						{
							if(*size<6552)
							{
								(*size)*=10;
								(*size)+=(temp-'0');
								page3_screen(mapx,mapy,size,1);
							}
						}
						
					}
					else if(temp=='\b'&&(*size)>0)		//����Ƿ�Ϊ�˸������������ǰһ���ַ�
					{
						(*size)/=10;
						page3_screen(mapx,mapy,size,1);
					}
					else
					{
						page3_screen(mapx,mapy,size,0);
						break;
					}
					delay(100);
				}
			}
		}
	}
	
	*mapxx=mapx;*mapyy=mapy;
	return page;
}

//����ҳ��3����
void page3_screen(int mapxx,int mapyy,int*size,int inputing)
{
	char mapx[3],mapy[3],siz[20];
	cleardevice();//����ǰ��ҳ������
	sprintf(mapx,"%d",mapxx);
	sprintf(mapy,"%d",mapyy);
	setbkcolor(WHITE);//����ɫ����
	puthz(10,34,"��ͼ��С",32,34,BLUE);
	settextstyle(0,0,3);
	setcolor(BLUE);
	outtextxy(150, 36, mapx);
	setfillstyle(SOLID_FILL, RED);//�趨��ɫ��
	bar(148, 6, 148+22, 6+20);//+
	outtextxy(150, 6, "+");
	setfillstyle(SOLID_FILL, RED);//�趨��ɫ��
	bar(148, 66, 148+22, 66+20);//-
	outtextxy(150, 66, "-");
	
	outtextxy(200, 36, "X");
	
	setfillstyle(SOLID_FILL, RED);//�趨��ɫ��
	bar(228, 6, 228+22, 6+20);//+
	outtextxy(230, 6, "+");
	setfillstyle(SOLID_FILL, RED);//�趨��ɫ��
	bar(228, 66, 228+22, 66+20);//-
	outtextxy(230, 66, "-");
	outtextxy(230, 36, mapy);
	
	setfillstyle(SOLID_FILL, RED);//�趨��ɫ��
	bar(5, 420, 5+100, 420+25);//page3
	puthz(22, 425,"����",16,18,BLUE);
	sprintf(siz,"%d",*size);
	setbkcolor(WHITE);//����ɫ����
	settextstyle(0,0,3);
	setcolor(BLUE);
	puthz(10,100,"������",32,34,BLUE);
	outtextxy(150, 105, "/");
	puthz(180,100,"Ķ",32,34,BLUE);
	
	
	if(!inputing)
	{
		setfillstyle(SOLID_FILL, RED);
		bar(498,98,570,132);
		puthz(500,100,"����",32,34,BLUE);
	}
	else
		puthz(466,100,"���س�ȷ��",32,34,BLUE);
	
	outtextxy(214, 104, ":");
	setcolor(RED);
	outtextxy(240, 102, siz);
}
	