#include "common.h"
#include "page7.h"

//因为需要返回page值，所以页面的函数需是int型
int p7(plantstatus *plantinfo,int x,int y)
{
	illtype ill[20];
	int page=0;
	FILE *fp=NULL;
	//防止鼠标在跳转页面时留痕
	clrmous(MouseX,MouseY);
	if ((fp = fopen("ill.bin", "rb")) == NULL) 
	{
		setfillstyle(SOLID_FILL, WHITE);
		bar(0, 435, 640, 480);
		puthz(5,440,"疫病未配置，请返回配置疫病",32,34,RED);
		while(mouse_press(535, 445, 535+100, 445+25) != 1)
			return 0;
	}
	fclose(fp);
	readdata7(ill);
	page7_screen(*plantinfo,x,y,ill);
	
	
	
	while(page==0)
	{
		//获取鼠标的位置和状态
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

//绘制页面7界面
void page7_screen(plantstatus plantinfo,int x,int y,illtype *ill)
{
	int i;
	char numstr[30]="\0";
	char temp[30]="\0";
	cleardevice();//把以前的页面清屏
	setbkcolor(WHITE);//背景色设置
	puthz(10,10,"田地坐标：",16,18,BLUE);//显示
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
	outtextxy(95,15, numstr);//显示坐标
	
	
	
	if(plantinfo.plantcode==0)
	{
		puthz(10,30,"健康，未患病",16,18,GREEN);//显示
		
		setfillstyle(SOLID_FILL, RED);
		bar(210, 30, 350, 60);
		puthz(220, 35,"设为患病",16,18,GREEN);
	}
	else
	{
		setfillstyle(SOLID_FILL, BLUE);//设定框
		bar(95, 30, 200, 50);//编号输入框
		setfillstyle(SOLID_FILL, WHITE);//设定框
		bar(97, 32, 198, 48);//编号输入框
		
		
		setfillstyle(SOLID_FILL, RED);
		bar(210, 30, 350, 60);
		puthz(220, 35,"设为健康",16,18,BLUE);
		
		num_to_str7(plantinfo.illnumber,temp);
		puthz(10,30,"疫病编号：",16,18,BLUE);//显示
		settextstyle(0,0,2);
		setcolor(BLUE);
		outtextxy(100,32, temp);//显示疫病编号（可更改）
		
		
		
		puthz(10,60,"疫病名称：",16,18,BLUE);//显示
		settextstyle(0,0,2);
		setcolor(BLUE);
		outtextxy(100,62, ill[(plantinfo.illnumber)-1].illname);//显示疫病名称
		
		puthz(10,90,"疫病所需农药量（一、二、三、四）单位：升",16,18,BLUE);//显示疫病所需农药量
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
	
	
	
	setfillstyle(SOLID_FILL, RED);//设定红色框
	bar(535, 445, 535+100, 445+25);//返回主页
	puthz(550, 450,"返回",16,18,BLUE);
}

void num_to_str7(int i,char *numstr)//数字转换字符串
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

void reverseString7(char *str,int length) //颠倒字符串
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


void inputnum7(plantstatus *plantinfo)//输入数字
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
			setfillstyle(SOLID_FILL, WHITE);//设定框
			bar(97, 32, 198, 48);//编号输入框
			outtextxy(100,34, instr);//擦除原数据并显示新数据
			
			temp=bioskey(0)&0x00ff;//获取输入的字符
			if(temp!='\b'&&temp!='\n'&&temp!='\r')	//检测输入不为回车键或退格键，则继续，否则输入结束
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
						setfillstyle(SOLID_FILL, WHITE);//设定框
						bar(97, 32, 198, 48);//编号输入框
						outtextxy(100,32, instr);//显示疫病编号（可更改）
					}
					else
					{
						settextstyle(0,0,2);
						setcolor(BLUE);
						setfillstyle(SOLID_FILL, WHITE);
						bar(0, 435, 640, 480);
						puthz(5,440,"请输入数字！",32,34,RED);
					}
				}
				else
				{
					settextstyle(0,0,2);
					setcolor(BLUE);
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
				plantinfo->illnumber=str_to_int7(instr);
				
				settextstyle(0,0,2);
				setcolor(BLUE);
				setfillstyle(SOLID_FILL, WHITE);//设定框
				bar(97, 32, 198, 48);//编号输入框
				outtextxy(100,32, instr);//擦除原数据并显示新数据
			}
			else
			{
				settextstyle(0,0,2);
				setcolor(BLUE);
				setfillstyle(SOLID_FILL, WHITE);//设定框
				bar(97, 32, 198, 48);//编号输入框
				outtextxy(100,32, instr);//擦除原数据并显示新数据
				break;
			}
			clrmous(MouseX,MouseY);
			delay(100);
		}
	}
}



int str_to_int7(char *str) //字符串转换整数
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

void writedata7(illtype *write)//全覆盖写入
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

void readdata7(illtype *read)//读取数据
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