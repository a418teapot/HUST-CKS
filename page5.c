#include "common.h"
#include "page5.h"

//因为需要返回page值，所以页面的函数需是int型
int p5(void)
{
	int page = 0,idk=0,passwordk=0,passcheckk=0,show=0;
	char passcheck[15]={0};
	char temp;
	ACCOUNT write={0};
	//防止鼠标在跳转页面时留痕
	clrmous(MouseX,MouseY);
	delay(100);
	page5_screen(write.id,write.password,passcheck,show);
	/*循环，不停地监测异动，当异动导致page值改变，跳转页面*/
	while(page == 0)
	{
		//获取鼠标的位置和状态
		mou_pos(&MouseX,&MouseY,&press);
		//注册按钮
		if(mouse_press(150, 350, 150+140, 350+30) == 1)
		{
			if(write.id[0]=='\0')//是否填写了用户信息
			{
				setfillstyle(SOLID_FILL, WHITE);
				bar(0, 435, 640, 480);
				puthz(5,440,"请填写用户名！",32,34,RED);
			}
			else if(write.password[0]=='\0'||strcmp(write.password,passcheck)!=0)//输入的密码是否为空或者两次输入密码是否不相同
			{
				setfillstyle(SOLID_FILL, WHITE);
				bar(0, 435, 640, 480);
				puthz(5,440,"请确保密码不为空且两次输入密码相同！",32,34,RED);
			}
			else
			{
				creataccount(write);
			}
			delay(100);
		}
		//取消按钮
		else if(mouse_press(300, 350, 300+140, 350+30) == 1)
		{
			page = 1;//直接返回登录界面
			delay(100);
		}
		else if(mouse_press(160, 200, 160+300, 200+30) == 1)
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
					else if(temp=='\b'&&idk>=0)		//检测是否为退格键，是则消除前一个字符
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
								write.password[passwordk]=temp;
								passwordk++;
								page5_screen(write.id,write.password,passcheck,show);
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
			puthz(5,440,"按回车确定！",32,34,RED);
			
			while(1)
			{
				if(bioskey(1))
				{
					
					temp=bioskey(0)&0x00ff;//获取输入的字符
					if(temp!='\b'&&temp!='\n'&&temp!='\r')	//检测输入不为回车键或退格键，则继续，否则输入结束
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
					else if(temp=='\b'&&passcheckk>=0)		//检测是否为退格键，是则消除前一个字符
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
		else if(mouse_press(160+312, 192+60+40, 160+338, 190+60+40+28) == 1)//点击到复选框白色部分
		{
			show=!show;
			clrmous(MouseX,MouseY);
			page5_screen(write.id,write.password,passcheck,show);
			
			delay(100);
		}
	}
	return page;
}

//绘制注册界面
void page5_screen(char *idt,char *passwordt,char *passcheckt,int show)
{
	int i=0;
	char id[15]={0},password[15]={0},passcheck[15]={0};
	strcpy(id,idt);
	strcpy(password,passwordt);
	strcpy(passcheck,passcheckt);
	cleardevice();//把以前的页面清屏
	
	setbkcolor(WHITE);//背景色设置
	puthz(150,170-80,"无人机喷洒系统注册",32,35,0xFFF0F5);
	setfillstyle(SOLID_FILL, 0xFFF0F5);//设定用户名框
	bar(160, 200, 160+300, 200+30);
	setfillstyle(SOLID_FILL, WHITE);
	bar(162, 202, 160+298, 200+28);
	puthz(90,210,"用户名：",16,18,0xFFF0F5);
	
	
	settextstyle(0,0,2);
	setcolor(0xFFF0F5);
	outtextxy(165,210, id);
	
	
	setfillstyle(SOLID_FILL, 0xFFF0F5);
	bar(160+310, 190+60+40, 160+340, 190+60+40+30); //显示密码复选框
	setfillstyle(SOLID_FILL, WHITE);
	bar(160+312, 192+60+40, 160+338, 190+60+40+28);
	puthz(160+350,200+60+40,"显示密码",16,18,0xFFF0F5);
	
	if(!show)
	{
		for(i=0;password[i]!='\0';i++)//若不显示密码则将字符全部替换为*
			password[i]='*';
		for(i=0;passcheck[i]!='\0';i++)//若不显示密码则将字符全部替换为*
			passcheck[i]='*';
	}
	else
	{
		setfillstyle(SOLID_FILL, 0xFFF0F5);//若显示密码则将复选框显示为选中状态
		bar(160+314, 194+60+40, 160+336, 190+60+40+26);
	}
	
	
	
	
	setfillstyle(SOLID_FILL, 0xFFF0F5);//设定密码框
	bar(160, 245, 160+300, 245+30);
	setfillstyle(SOLID_FILL, WHITE);
	bar(162, 247, 160+298, 245+28);
	puthz(54,255,"输入密码：",16,18,0xFFF0F5);
	
	settextstyle(0,0,2);
	setcolor(0xFFF0F5);
	outtextxy(165,255, password);
	
	setfillstyle(SOLID_FILL, 0xFFF0F5);//设定确认密码框
	bar(160, 190+60+40, 160+300, 190+60+40+30);
	setfillstyle(SOLID_FILL, WHITE);
	bar(162, 192+60+40, 160+298, 190+60+40+28);
	puthz(18,200+60+40,"再次输入密码：",16,18,0xFFF0F5);
	
	settextstyle(0,0,2);
	setcolor(0xFFF0F5);
	outtextxy(165,200+60+40,passcheck);
	
	setfillstyle(SOLID_FILL, 0xFFF0F5);//设定注册按钮
	bar(150, 350, 150+140, 350+30);
	puthz(202,355,"注册",16,18,WHITE);
	
	setfillstyle(SOLID_FILL, RED);//设定取消按钮
	bar(300, 350, 300+140, 350+30);
	puthz(352,355,"返回",16,18,WHITE);
	
	
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
		if(temp[i].id[0]=='\0')//当前位置是否为空
		{
			break;//为空则直接开始写入
		}
		else if(strcmp(temp[i].id,write.id)==0)//比对是否存在同名已注册用户
		{
			setfillstyle(SOLID_FILL, WHITE);
			bar(0, 435, 640, 480);
			puthz(5,440,"该用户已被注册！",32,34,RED);
			return;
		}
	}
	if(i==10)
	{
		setfillstyle(SOLID_FILL, WHITE);
		bar(0, 435, 640, 480);
		puthz(5,440,"注册用户已满，请清理后再注册！",32,34,RED);
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
		puthz(5,440,"注册成功！",32,34,RED);
	}
	fclose(fp);
}

