#include "common.h"
#include "page6.h"

//因为需要返回page值，所以页面的函数需是int型
int p6()
{
	illtype ill[20];
	int page=0;
	int i,j;
	int pagenumber=1;
	FILE*fp=NULL;
	//防止鼠标在跳转页面时留痕
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
	
	/*循环，不停地监测异动，当异动导致page值改变，跳转页面*/

	while(page == 0)
	{
		
		//获取鼠标的位置和状态
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
				writedata(ill);//全覆盖写入
				page=2;
				
			}
		}
		
	}
	return page;
	
}

//绘制页面6界面
void page6_screen(int pagenumber,illtype *ill)
{
	int i;
	char numstr[20]="\0";
	cleardevice();//把以前的页面清屏
	setbkcolor(WHITE);//背景色设置
	puthz(10,2,"编号",16,18,BLUE);//显示
	puthz(60,2,"疫病名称",16,18,BLUE);//显示
	puthz(250,2,"疫病所需农药量（一、二、三、四）单位：升",16,18,BLUE);//显示
	for(i=10*(pagenumber-1);i<=10*(pagenumber)&&i<=19;i++)
	{
		num_to_str(i+1,numstr);
		settextstyle(0,0,2);
		setcolor(BLUE);
		outtextxy(10,17+i*47, numstr);//显示编号
		
		setfillstyle(SOLID_FILL, BLUE);//设定框
		bar(50, 20+i*47, 200, 40+i*47);//名称输入框
		setfillstyle(SOLID_FILL, WHITE);//设定框
		bar(52, 22+i*47, 198, 38+i*47);//名称输入框
		outtextxy(54,24+i*47, ill[i].illname);//显示
		
		setfillstyle(SOLID_FILL, BLUE);//设定框
		bar(240, 20+i*47, 285, 40+i*47);//药量输入框0
		setfillstyle(SOLID_FILL, WHITE);//设定框
		bar(242, 22+i*47, 285-2, 38+i*47);//药量输入框
		num_to_str(ill[i].pesti[0],numstr);
		outtextxy(244,24+i*47, numstr);//显示所需药量
		
		setfillstyle(SOLID_FILL, BLUE);//设定框
		bar(290, 20+i*47, 290+45, 40+i*47);//药量输入框1
		setfillstyle(SOLID_FILL, WHITE);//设定框
		bar(292, 22+i*47, 290+45-2, 38+i*47);//药量输入框
		num_to_str(ill[i].pesti[1],numstr);
		outtextxy(294,24+i*47, numstr);//显示所需药量
		
		setfillstyle(SOLID_FILL, BLUE);//设定框
		bar(340, 20+i*47, 340+45, 40+i*47);//药量输入框2
		setfillstyle(SOLID_FILL, WHITE);//设定框
		bar(342, 22+i*47, 340+45-2, 38+i*47);//药量输入框
		num_to_str(ill[i].pesti[2],numstr);
		outtextxy(344,24+i*47, numstr);//显示所需药量
		
		setfillstyle(SOLID_FILL, BLUE);//设定框
		bar(390, 20+i*47, 390+45, 40+i*47);//药量输入框3
		setfillstyle(SOLID_FILL, WHITE);//设定框
		bar(392, 22+i*47, 390+45-2, 38+i*47);//药量输入框
		num_to_str(ill[i].pesti[3],numstr);
		outtextxy(394,24+i*47, numstr);//显示所需药量
		
		
		
		
		
	}
	setfillstyle(SOLID_FILL, RED);//设定红色框
	bar(435, 445, 435+100, 445+25);//返回主页
	puthz(461, 450,"返回",16,18,BLUE);
}

void num_to_str(int i,char *numstr)//数字转换字符串
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

void reverseString(char *str,int length) //颠倒字符串
{
	int i = 0;
    char temp;
    
    // 使用两个指针，一个从字符串的开头向后移动，另一个从字符串的末尾向前移动，交换它们指向的字符
    for (i=0; i<length/2; i++) 
	{
        temp=str[i];
        str[i]=str[length-i-1];
        str[length-i-1]=temp;
    }
}

void inputstr(int illnum,illtype *ill,int pagenumber)//输入字母
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
			temp=bioskey(0)&0x00ff;//获取输入的字符
			if(temp!='\b'&&temp!='\n'&&temp!='\r')	//检测输入不为回车键或退格键，则继续，否则输入结束
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
						puthz(5,440,"请输入大小写字母或数字！",32,34,RED);
					}
				}
				else
				{
					setfillstyle(SOLID_FILL, WHITE);
					bar(0, 435, 640, 480);
					puthz(5,440,"超出输入限制！",32,34,RED);
				}
				
				
			}
			else if(temp=='\b'&&namek>=0)		//检测是否为退格键，是则消除前一个字符
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


void inputnum(int illnum,illtype *ill,int pagenumber,int pestinum)//输入数字
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
			temp=bioskey(0)&0x00ff;//获取输入的字符
			if(temp!='\b'&&temp!='\n'&&temp!='\r')	//检测输入不为回车键或退格键，则继续，否则输入结束
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
						puthz(5,440,"请输入数字！",32,34,RED);
					}
				}
				else
				{
					setfillstyle(SOLID_FILL, WHITE);
					bar(0, 435, 640, 480);
					puthz(5,440,"超出输入限制！",32,34,RED);
				}
				
				
			}
			else if(temp=='\b'&&numk>=0)		//检测是否为退格键，是则消除前一个字符
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



int str_to_int(char *str) //字符串转换整数
{
    int num = 0;
    int i = 0;
    
    // 检查数字字符
    while (str[i] >= '0' && str[i] <= '9') {
        // 逐位累加
        num = num * 10 + (str[i] - '0');
        i++;
    }
    
    return num;
}

void writedata(illtype *write)//全覆盖写入
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

void readdata(illtype *read)//读取数据
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
