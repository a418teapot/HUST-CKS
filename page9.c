#include "common.h"
#include "page9.h"

//因为需要返回page值，所以页面的函数需是int型
int p9()
{
	int page=0,humidity;
	float wind_speed,temperature;
	
	//防止鼠标在跳转页面时留痕
	clrmous(MouseX,MouseY);
	delay(200);
	srand((unsigned)time(NULL));//随机数种子
	
	// 风速：0-30 m/s
	wind_speed = (float)(rand() % 3001) / 100.0f; 
	 
	// 温度：-20-60℃
	temperature = (float)(rand() % 8001) / 100.0f - 20.0f;
	 
	// 湿度：0-100%
	humidity = rand() % 101;

	page9_screen(wind_speed,temperature,humidity);
	while(page==0)
	{
		//获取鼠标的位置和状态
		mou_pos(&MouseX,&MouseY,&press);
		if(mouse_press(300, 350, 400, 400)==1)
		{
			page=2;
		}
	}
	return page;
	
}

//绘制页面9界面
void page9_screen(float wind_speed,float temperature,int humidity)
{
	char temp[10];
	cleardevice();//把以前的页面清屏
	setbkcolor(LIGHTCYAN);//背景色设置
	puthz(120, 10,"欢迎登陆系统！下面是天气情况",32,34,BLUE);
	
	num_to_str9((int)wind_speed,temp);
	if (wind_speed > 15.0f) 
	{
		puthz(10, 50,"风速（米每秒）：",16,18,RED);
		settextstyle(0,0,2);
		setcolor(RED);
		outtextxy(156,55, temp);
		puthz(10, 80,"严重警告：风速超过十五米每秒！不建议起飞！",16,18,RED);
		
	} 
	else if (wind_speed > 10.0f) 
	{
		puthz(10, 50,"风速（米每秒）：",16,18,LIGHTRED);
		settextstyle(0,0,2);
		setcolor(LIGHTRED);
		outtextxy(156,55, temp);
		puthz(10, 80,"警告：风速超过十米每秒，请谨慎操作！",16,18,LIGHTRED);
	}
	else
	{
		puthz(10, 50,"风速（米每秒）：",16,18,GREEN);
		settextstyle(0,0,2);
		setcolor(GREEN);
		outtextxy(156,55, temp);
		puthz(10, 80,"正常",16,18,GREEN);
	}
	
	num_to_str9((int)temperature,temp);
	if (temperature < 0.0f || temperature > 40.0f) 
	{
		
		puthz(10, 150,"温度（摄氏度）：",16,18,RED);
		settextstyle(0,0,2);
		setcolor(RED);
		outtextxy(156,155, temp);
		puthz(10, 180,"警告：当前温度可能影响设备性能！",16,18,RED);
	}
	else
	{
		puthz(10, 150,"温度（摄氏度）：",16,18,GREEN);
		settextstyle(0,0,2);
		setcolor(GREEN);
		outtextxy(156,155, temp);
		puthz(10, 180,"温度正常",16,18,GREEN);
	}
	
	num_to_str9((int)humidity,temp);
	if (humidity > 95) 
	{
		puthz(10, 250,"湿度（百分之）：",16,18,RED);
		settextstyle(0,0,2);
		setcolor(RED);
		outtextxy(156,255, temp);
		puthz(10, 280,"严重警告：湿度过高，存在短路风险！不建议起飞",16,18,RED);
	} 
	else if (humidity > 80)
	{
		puthz(10, 250,"湿度（百分之）：",16,18,LIGHTRED);
		settextstyle(0,0,2);
		setcolor(LIGHTRED);
		outtextxy(156,255, temp);
		puthz(10, 280,"警告：请尽量避免在雨中飞行！",16,18,LIGHTRED);
	}
	else
	{
		puthz(10, 250,"湿度（百分之）：",16,18,GREEN);
		settextstyle(0,0,2);
		setcolor(GREEN);
		outtextxy(156,255, temp);
		puthz(10, 280,"湿度正常",16,18,GREEN);
	}
	
	
	setfillstyle(SOLID_FILL, RED);//设定红色框
	bar(300, 350, 400, 400);//
	puthz(340, 370,"确定",16,18,BLUE);
	
}


void num_to_str9(int i,char *numstr)//数字转换字符串
{
	int x=0;
	if (i == 0) {
        numstr[0] = '0';
        numstr[1] = '\0';
        return;
    }
	else if(i<0)
	{
		i*=-1;
		for(x=0;i!=0;x++)
		{
			
			numstr[x]=(i%10)+'0';
			i=i/10;
		}
		numstr[x]='\0';
		reverseString7(numstr,x);
		addnegative(numstr);
	}
	else
	{
		for(x=0;i!=0;x++)
		{
			
			numstr[x]=(i%10)+'0';
			i=i/10;
		}
		numstr[x]='\0';
		reverseString7(numstr,x);
	}

}

void reverseString9(char *str,int length) //颠倒字符串
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


void addnegative(char *str) 
{
	size_t i;
	
	
    if (str == NULL || *str == '-') 
	{
        return; // 空指针或已经是负数，直接返回
    }
	str[strlen(str)+1]='\0';
    // 移动字符，为负号腾出空间
    for (i = strlen(str); i > 0; --i) 
	{
        str[i] = str[i - 1];
    }
	
    // 添加负号
    str[0] = '-';
}