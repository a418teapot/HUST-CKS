#include "common.h"
#include "page8.h"

//因为需要返回page值，所以页面的函数需是int型
int p8()
{
	int page=0,pagenumber=1;
	plantstatus plantmap[30][20];
	illtype ill[20];
	readplantinfo(plantmap);
	readillinfo(ill);
	//防止鼠标在跳转页面时留痕
	clrmous(MouseX,MouseY);
	delay(200);
	page8_screen(plantmap,pagenumber,ill);
	while(page==0)
	{
		//获取鼠标的位置和状态
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

//绘制页面8界面
void page8_screen(plantstatus (*plantmap)[20],int pagenumber,illtype *ill)
{
	int pesti[4]={0},i=0,j=0,temp=0,illcount[11]={0},max=-1;
	float k=0;
	char num[30];
	setbkcolor(WHITE);//背景色设置
	cleardevice();//把以前的页面清屏
	puthz(120, 10,"统计信息",32,34,BLUE);
	if(pagenumber==1)
	{
		puthz(270, 20,"农药需求量统计",16,18,BLUE);
		
		setfillstyle(SOLID_FILL, BLUE);
		bar(30, 30,32, 500);
		
		puthz(10, 70,"一",16,18,BLUE);
		puthz(10, 170,"二",16,18,BLUE);
		puthz(10, 270,"三",16,18,BLUE);
		puthz(10, 370,"四",16,18,BLUE);
		
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
		for(i=0;i<4;i++)//找出最大的农药作为基准
		{
			
			
			if(pesti[i]>temp)
			{
				j=i;
				temp=pesti[i];
			}
		}
		setfillstyle(SOLID_FILL, YELLOW);
		for(i=0;i<4;i++)//找出最大的农药作为基准
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
		for(i=0;i<4;i++)//找出最大的农药作为基准
		{
			num_to_str8(pesti[i],num);
			settextstyle(0,0,2);
			setcolor(BLUE);
			outtextxy(50,65+i*100, num);//显示坐标
		}
		
		
	}
	if(pagenumber==2)
	{
		puthz(270, 20,"疫病统计",16,18,BLUE);
		
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
				outtextxy(35+400*k,50+20*j, num);//显示坐标
				settextstyle(0,0,2);
				setcolor(BLUE);
				outtextxy(35,50+20*j, ill[i].illname);//显示坐标
				j++;
			}
		}
		
	}
	setfillstyle(SOLID_FILL, RED);//设定红色框
	bar(535, 445, 535+100, 445+25);//返回主页
	puthz(550, 450,"返回",16,18,BLUE);
	
	if(pagenumber<2)
	{
		setfillstyle(SOLID_FILL, RED);//设定红色框
		bar(375, 445, 375+100, 445+25);//
		puthz(390, 450,"下一页",16,18,BLUE);
	}
	
	if(pagenumber>1)
	{
		setfillstyle(SOLID_FILL, RED);//设定红色框
		bar(215, 445, 215+100, 445+25);//返回
		puthz(230, 450,"上一页",16,18,BLUE);
	}
}

void num_to_str8(int i,char *numstr)//数字转换字符串
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

void reverseString8(char *str,int length) //颠倒字符串
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

void readplantinfo(plantstatus (*read)[20])//读取作物信息
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

void readillinfo(illtype *read)//读取数据
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
