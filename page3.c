#include "common.h"
#include "page3.h"

//因为需要返回page值，所以页面的函数需是int型
int p3(int*mapxx,int*mapyy,int*size)
{
	int page = 0,mapx=*mapxx,mapy=*mapyy,map[2];//地图大小
	char temp;
	//防止鼠标在跳转页面时留痕
	clrmous(MouseX,MouseY);
	map[0]=mapx;map[1]=mapy;
	
	page3_screen(mapx,mapy,size,0);
	delay(100);
	
	
	/*循环，不停地监测异动，当异动导致page值改变，跳转页面*/
	while(page == 0)
	{
		//获取鼠标的位置和状态
		mou_pos(&MouseX,&MouseY,&press);
		
		//点击跳转页面框，跳转到页面2界面
		if(mouse_press(5, 420, 5+100, 420+25) == 1)
		{
			page = 2;//页面2
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
					temp=bioskey(0)&0x00ff;//获取输入的字符
					if(temp!='\b'&&temp!='\n'&&temp!='\r')	//检测输入不为回车键，则继续，否则输入结束
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
					else if(temp=='\b'&&(*size)>0)		//检测是否为退格键，是则消除前一个字符
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

//绘制页面3界面
void page3_screen(int mapxx,int mapyy,int*size,int inputing)
{
	char mapx[3],mapy[3],siz[20];
	cleardevice();//把以前的页面清屏
	sprintf(mapx,"%d",mapxx);
	sprintf(mapy,"%d",mapyy);
	setbkcolor(WHITE);//背景色设置
	puthz(10,34,"地图大小",32,34,BLUE);
	settextstyle(0,0,3);
	setcolor(BLUE);
	outtextxy(150, 36, mapx);
	setfillstyle(SOLID_FILL, RED);//设定红色框
	bar(148, 6, 148+22, 6+20);//+
	outtextxy(150, 6, "+");
	setfillstyle(SOLID_FILL, RED);//设定红色框
	bar(148, 66, 148+22, 66+20);//-
	outtextxy(150, 66, "-");
	
	outtextxy(200, 36, "X");
	
	setfillstyle(SOLID_FILL, RED);//设定红色框
	bar(228, 6, 228+22, 6+20);//+
	outtextxy(230, 6, "+");
	setfillstyle(SOLID_FILL, RED);//设定红色框
	bar(228, 66, 228+22, 66+20);//-
	outtextxy(230, 66, "-");
	outtextxy(230, 36, mapy);
	
	setfillstyle(SOLID_FILL, RED);//设定红色框
	bar(5, 420, 5+100, 420+25);//page3
	puthz(22, 425,"返回",16,18,BLUE);
	sprintf(siz,"%d",*size);
	setbkcolor(WHITE);//背景色设置
	settextstyle(0,0,3);
	setcolor(BLUE);
	puthz(10,100,"田地面积",32,34,BLUE);
	outtextxy(150, 105, "/");
	puthz(180,100,"亩",32,34,BLUE);
	
	
	if(!inputing)
	{
		setfillstyle(SOLID_FILL, RED);
		bar(498,98,570,132);
		puthz(500,100,"更改",32,34,BLUE);
	}
	else
		puthz(466,100,"按回车确定",32,34,BLUE);
	
	outtextxy(214, 104, ":");
	setcolor(RED);
	outtextxy(240, 102, siz);
}
	