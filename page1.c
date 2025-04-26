#include "common.h"
#include "page1.h"

//因为需要返回page值，所以页面的函数需是int型
int p1(void)
{
	int page = 0,idk=0,passwordk=0,show=0;
	char temp;
	ACCOUNT input={0};
	
	//防止鼠标在跳转页面时留痕
	clrmous(MouseX,MouseY);
	delay(100);
	page1_screen(input,show);
	/*循环，不停地监测异动，当异动导致page值改变，跳转页面*/
	while(page == 0)
	{
		//获取鼠标的位置和状态
		mou_pos(&MouseX,&MouseY,&press);
		
		//登录按钮
		if(mouse_press(150, 380, 150+140, 380+30) == 1)
		{
			if(checkaccount(input))//检测密码是否正确
				page = 9;//登入主界面
			else
			{
				setfillstyle(SOLID_FILL, WHITE);
				bar(0, 435, 640, 480);
				puthz(5,440,"用户不存在或密码不正确！",32,34,RED);
			}
			delay(100);
		}
		//退出按钮
		else if(mouse_press(300, 380, 300+140, 380+30) == 1)
		{
			page = -1;//退出程序
		}
		else if(mouse_press(200+165,225+60+35, 200+170+100, 225+60+60) == 1)
		{
			page = 5;//返回-1到主函数的页面跳转循环
		}
		else if(mouse_press(160, 200, 160+300, 200+30) == 1)//用户名输入框被按下
		{	
			clrmous(MouseX,MouseY);
			setfillstyle(SOLID_FILL, WHITE);
			bar(0, 435, 640, 480);
			puthz(5,440,"按回车确定！",32,34,RED);
			delay(500);
			while(1)
			{
				if(bioskey(1))
				{
					
					temp=bioskey(0)&0x00ff;//获取输入的字符
					if(temp!='\b'&&temp!='\n'&&temp!='\r')	//检测输入不为回车键或退格键，则继续，否则输入结束
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
								puthz(5,440,"请输入大小写字母或数字！",32,34,RED);
							}
						}
						else
						{
							setfillstyle(SOLID_FILL, WHITE);
							bar(0, 435, 640, 480);
							puthz(5,440,"仅可输入15位！",32,34,RED);
						}
					}
					else if(temp=='\b'&&idk>=0)		//检测是否为退格键，是则消除前一个字符
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
			puthz(5,440,"按回车确定！",32,34,RED);
			while(1)
			{
				if(bioskey(1))
				{
					
					temp=bioskey(0)&0x00ff;//获取输入的字符
					if(temp!='\b'&&temp!='\n'&&temp!='\r')	//检测输入不为回车键或退格键，则继续，否则输入结束
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
								puthz(5,440,"请输入大小写字母或数字！",32,34,RED);
							}
						}
						else
						{
							setfillstyle(SOLID_FILL, WHITE);
							bar(0, 435, 640, 480);
							puthz(5,440,"仅可输入十五位！",32,34,RED);
						}
						
						
					}
					else if(temp=='\b'&&passwordk>=0)		//检测是否为退格键，是则消除前一个字符
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
		else if(mouse_press(160+312, 192+60+40, 160+338, 190+60+40+28) == 1)//点击到复选框白色部分
		{
			show=!show;
			clrmous(MouseX,MouseY);
			page1_screen(input,show);
			
			delay(100);
		}
	}
	return page;
}

//绘制页面1界面
void page1_screen(ACCOUNT input,int show)
{
	int i;
	cleardevice();//把以前的页面清屏
	
	setbkcolor(WHITE);//背景色设置
	puthz(150,170-80,"无人机农药喷洒系统",32,35,BLUE);
	setfillstyle(SOLID_FILL, BLUE);//用户名框
	bar(160, 200, 160+300, 200+30);
	setfillstyle(SOLID_FILL, WHITE);
	bar(162, 202, 160+298, 200+28);
	puthz(90,210,"用户名：",16,18,BLUE);
	
	settextstyle(0,0,2);
	setcolor(BLUE);
	outtextxy(165,210, input.id);
	
	
	
	
	setfillstyle(SOLID_FILL, BLUE);//密码框
	bar(160, 190+60+40, 160+300, 190+60+40+30);
	setfillstyle(SOLID_FILL, WHITE);
	bar(162, 192+60+40, 160+298, 190+60+40+28);
	puthz(90,200+60+40,"密码：",16,18,BLUE);
	
	setfillstyle(SOLID_FILL, BLUE);
	bar(160+310, 190+60+40, 160+340, 190+60+40+30); //显示密码复选框
	setfillstyle(SOLID_FILL, WHITE);
	bar(160+312, 192+60+40, 160+338, 190+60+40+28);
	puthz(160+350,200+60+40,"显示密码",16,18,BLUE);
	
	if(!show)
	{
		for(i=0;input.password[i]!='\0';i++)//若不显示密码则将字符全部替换为*
			input.password[i]='*';
	}
	else
	{
		setfillstyle(SOLID_FILL, BLUE);//若显示密码则将复选框显示为选中状态
		bar(160+314, 194+60+40, 160+336, 190+60+40+26);
	}
	settextstyle(0,0,2);
	setcolor(BLUE);
	outtextxy(165,200+60+40,input.password);

	
	puthz(200+170,225+60+40,"点击注册！",16,18,0xFFF0F5);
	
	setfillstyle(SOLID_FILL, BLUE);//设定登录按钮
	bar(150, 380, 150+140, 380+30);
	puthz(202,385,"登录",16,18,WHITE);
	
	setfillstyle(SOLID_FILL, RED);//设定退出按钮
	bar(300, 380, 300+140, 380+30);
	puthz(352,385,"退出",16,18,WHITE);
	
	
}

int checkaccount(ACCOUNT input)//检测用户是否存在，密码是否正确
{
	int i=0;
	ACCOUNT temp[10];
	FILE*fp = NULL;
	fp = fopen("acc.bin", "rb");
	rewind(fp);
	fread(temp, sizeof(ACCOUNT), 10, fp);
	for(i=0;i<10;i++)
	{
		if(temp[i].id[0]=='\0')//当前位置是否为空,为空则说明无该用户
		{
			break;
		}
		else if(strcmp(temp[i].id,input.id)==0)//比对是否存在同名已注册用户
		{
			if(strcmp(temp[i].password,input.password)==0)//比对密码是否正确
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