#include "common.h"
#include "page2.h"

//因为需要返回page值，所以页面的函数需是int型
int p2(int mapx,int mapy,plantstatus (*plantmap)[20],int *plantx,int *planty)
{
	
	int page = 0,i=0,j=0,ran=0,illtotal=0,tempdrop[4]={0};
	illtype read[20];
	char outputx[4]={0},outputy[4]={0};
	FILE*fp = NULL;
	uavstatus uav;
	coordinate next;
	next.x=0;
	next.y=0;
	uav.uavx=0;
	uav.uavy=0;
	uav.statuscode=0;
	uav.uavp[0]=0;
	uav.uavp[1]=0;
	uav.uavp[2]=0;
	uav.uavp[3]=0;
	readdata2(plantmap);
	
	//防止鼠标在跳转页面时留痕
	clrmous(MouseX,MouseY);
	delay(200);
	page2_screen(mapx,mapy,plantmap,uav,0,0);
	srand((unsigned)time(NULL));//随机数种子
	
	
	//检测已知疫病种类
	fp = fopen("ill.bin", "rb");
	rewind(fp);
	fread(read, sizeof(illtype), 20, fp);
	fclose(fp);
	for(i=0;i<=19;i++)
	{
		if(read[i].illname[0]!='\0')
			illtotal++;
	}
	if(illtotal==0)
	{
		illtotal=1;
	}
	
	/*循环，不停地监测异动，当异动导致page值改变，跳转页面*/
	while(page == 0)
	{
		//获取鼠标的位置和状态
		mou_pos(&MouseX,&MouseY,&press);
		
		//点击退出程序框
		if(mouse_press(5, 445, 5+100, 445+25) == 1)//基础配置
		{
			for(i=0;i<30;i++)//田地数据初始化
			{
				for(j=0;j<20;j++)
				{
					plantmap[i][j].plantcode=0;
					plantmap[i][j].illnumber=0;
				}
			}
			writedata2(plantmap);
			page = 3;
		}
		else if(mouse_press(335, 445, 335+100, 445+25) == 1)
		{
			page= 1;
		}
		else if(mouse_press(115, 445, 115+100, 445+25) == 1)//监测
		{
			uav.statuscode=1;
			clrmous(MouseX,MouseY);
			delay(100);
			page2_screen(mapx,mapy,plantmap,uav,0,0);
			for(uav.uavx=0;uav.uavx<mapy;uav.uavx++)
			{
				while(uav.uavy<mapy&&uav.uavy>=0)
				{
					
					//生成一百以内随机数模拟植物监测情况，实际可接入传感器接口
					ran=(rand()%100)+1;
					if(ran<95)
					{
						plantmap[uav.uavx][uav.uavy].plantcode=0;
						plantmap[uav.uavx][uav.uavy].illnumber=0;
					}
					else
					{
						ran=(rand()%illtotal)+1;
						plantmap[uav.uavx][uav.uavy].plantcode=1;
						plantmap[uav.uavx][uav.uavy].illnumber=ran;
					}
					page2_screen(mapx,mapy,plantmap,uav,1,1);
					mou_pos(&MouseX,&MouseY,&press);

					if(uav.uavx%2==0)
						uav.uavy++;
					else
						uav.uavy--;
				}
				if(uav.uavx%2==0)
						uav.uavy--;
					else
						uav.uavy++;
			}
			uav.uavx=0;
			uav.uavy=0;
			uav.statuscode=0;
			clrmous(MouseX,MouseY);delay(100);
			page2_screen(mapx,mapy,plantmap,uav,0,0);
			writedata2(plantmap);
		}
		else if(mouse_press(225, 445, 225+100, 445+25) == 1)//喷洒
		{
			uav.statuscode=2;
			clrmous(MouseX,MouseY);
			delay(100);
			while(1)
			{
				//获取鼠标的位置和状态
				mou_pos(&MouseX,&MouseY,&press);
				setfillstyle(SOLID_FILL, WHITE);
				bar(0, 435, 640, 480);
				puthz(5,440,"计算路径中",32,34,BLUE);
				next=nextxy(mapx,mapy,plantmap,uav.uavx,uav.uavy);
				if(next.x==-1||next.y==-1)
				{
					break;
				}
				
				
				
				
				/*********************************************************************************************************/
				//settextstyle(0,0,2);
				//setcolor(BLUE);
				//num_to_str7(plantmap[next.x][next.y].illnumber-1,outputy);
				//setfillstyle(SOLID_FILL, WHITE);//正常位置显示为绿色
				//bar(600, 200, 610, 210);
				//outtextxy(600, 200, outputy);
				if(plantmap[next.x][next.y].illnumber-1<=-1||plantmap[next.x][next.y].illnumber-1>19)

				{
					outtextxy(600, 300, "WRONG!");
					while(1);
				}
				/*********************************************************************************************************/
				if(
				uav.uavp[0]<read[plantmap[next.x][next.y].illnumber-1].pesti[0]||
				uav.uavp[1]<read[plantmap[next.x][next.y].illnumber-1].pesti[1]||
				uav.uavp[2]<read[plantmap[next.x][next.y].illnumber-1].pesti[2]||
				uav.uavp[3]<read[plantmap[next.x][next.y].illnumber-1].pesti[3])//返回补充农药
				{
					
					setfillstyle(SOLID_FILL, WHITE);
					bar(0, 435, 640, 480);
					puthz(5,440,"药量不足，返回补充。",32,34,RED);
					uav_step(uav.uavx,uav.uavy,0,0,10,mapx,mapy,plantmap);
					uav.uavx=0;
					uav.uavy=0;
					while(1)
					{
						
						for(i=0;i<=3;i++)
						{
							if(uav.uavp[i]<=90)
							{
								uav.uavp[i]+=10;
								
							}
							else
							{
								uav.uavp[i]=100;
							}
							
							
						}
						page2_screen(mapx,mapy,plantmap,uav,1,0);
						if(uav.uavp[0]==100&&
							uav.uavp[1]==100&&
							uav.uavp[2]==100&&
							uav.uavp[3]==100
							)
						{
							setfillstyle(SOLID_FILL, WHITE);
							bar(0, 435, 640, 480);
							puthz(5,440,"补充完毕",32,34,BLUE);
								
							break;
						}
						
							//获取鼠标的位置和状态
							mou_pos(&MouseX,&MouseY,&press);
							delay(100);
						
						
					}
					
				}
				else//开始前往喷洒
				{
					
					setfillstyle(SOLID_FILL, WHITE);
					bar(0, 435, 640, 480);
					puthz(5,440,"运行中",32,34,BLUE);
					uav_step(uav.uavx,uav.uavy,next.x,next.y,10,mapx,mapy,plantmap);
					uav.uavx=next.x;
					uav.uavy=next.y;
					setfillstyle(SOLID_FILL, WHITE);
					bar(0, 435, 640, 480);
					puthz(5,440,"喷洒中",32,34,BLUE);
					/*********************************************************************************************************/
					//settextstyle(0,0,2);
					//setcolor(BLUE);
					//num_to_str7(plantmap[next.x][next.y].illnumber-1,outputy);
					//setfillstyle(SOLID_FILL, WHITE);//正常位置显示为绿色
					//bar(600, 200, 610, 210);
					//outtextxy(600, 200, outputy);
					if(plantmap[next.x][next.y].illnumber-1<=-1||plantmap[next.x][next.y].illnumber-1>19)
					{
						outtextxy(600, 300, "WRONG!");
						while(1);
					}
					/**********************************************************************************************************/
					tempdrop[0]=read[plantmap[next.x][next.y].illnumber-1].pesti[0];
					tempdrop[1]=read[plantmap[next.x][next.y].illnumber-1].pesti[1];
					tempdrop[2]=read[plantmap[next.x][next.y].illnumber-1].pesti[2];
					tempdrop[3]=read[plantmap[next.x][next.y].illnumber-1].pesti[3];
					j=0;
					while(1)
					{
						//获取鼠标的位置和状态
						mou_pos(&MouseX,&MouseY,&press);
						
						
							for(i=0;i<=3;i++)
							{
								if(tempdrop[i]>0)
								{
									tempdrop[i]--;
									uav.uavp[i]--;
								}
							}
							
							if(tempdrop[0]==0&&
								tempdrop[1]==0&&
								tempdrop[2]==0&&
								tempdrop[3]==0)
							{
								plantmap[uav.uavx][uav.uavy].plantcode=0;
								writedata2(plantmap);
								break;//地图块喷洒完毕
							}
							
						delay(100);
						
					}
				}
				
				page2_screen(mapx,mapy,plantmap,uav,1,0);
			}
			setfillstyle(SOLID_FILL, WHITE);
			bar(0, 435, 640, 480);
			puthz(5,440,"喷洒完毕，正在返回",32,34,RED);
			uav_step(uav.uavx,uav.uavy,0,0,10,mapx,mapy,plantmap);
			uav.uavx=0;
			uav.uavy=0;
			setfillstyle(SOLID_FILL, WHITE);
			bar(0, 435, 640, 480);
			uav.statuscode=0;
			page2_screen(mapx,mapy,plantmap,uav,0,0);
		}
		else if(mouse_press(335, 445, 335+100, 445+25) == 1)//回到主界面
		{
			page=1;
		}
		else if(mouse_press(445, 445, 445+100, 445+25) == 1)//配置疫病
		{
			page=6;
		}
		else if(mouse_press(445, 405, 445+100, 405+25) == 1)//统计
		{
			page=8;
		}
		else if(mouse_press(445, 365, 445+100, 365+25) == 1)//手动导航
		{
			uav.statuscode=1;
			clrmous(MouseX,MouseY);
			delay(100);
			page2_screen(mapx,mapy,plantmap,uav,0,0);
			setfillstyle(SOLID_FILL, RED);//设定红色框
			bar(545, 385, 545+100, 385+25);//
			puthz(550, 390,"退出",16,18,BLUE);
			while(1)
			{
				mou_pos(&MouseX,&MouseY,&press);
				
				for(i=0;i<mapy;i++)
				{
					for(j=0;j<mapx;j++)
					{
						
						if(mouse_press(23+20*j, 43+20*i, 23+17+20*j, 43+17+20*i)==1)//点击某一个田地
						{
							next.x=j;
							next.y=i;
							uav_step(uav.uavx,uav.uavy,next.x,next.y,10,mapx,mapy,plantmap);
							uav.uavx=next.x;
							uav.uavy=next.y;
						}
					}
				}
				
				if(mouse_press(545, 385, 545+100, 385+25)==1)//点击退出
				{
					uav.statuscode=0;
					break;
				}
			}
			page2_screen(mapx,mapy,plantmap,uav,0,0);
			clrmous(MouseX,MouseY);delay(100);
			
		}
		else 
		{
			for(i=0;i<mapy;i++)
			{
				for(j=0;j<mapx;j++)
				{
					
					if(mouse_press(23+20*j, 43+20*i, 23+17+20*j, 43+17+20*i)==1)//点击配置某一个田地的信息
					{
						p7(&plantmap[j][i],j,i);
						writedata2(plantmap);
						//防止鼠标在跳转页面时留痕
						clrmous(MouseX,MouseY);
						delay(200);
						page2_screen(mapx,mapy,plantmap,uav,0,0);
					}
				}
			}
		}
	}
	return page;//返回2到主函数的页面跳转循环
}

//绘制页面2界面
void page2_screen(int mapx,int mapy,plantstatus (*plantmap)[20],uavstatus st,int noflash,int move)
{
	int i=0,j=0;
	char status[30],position[20];
	if(noflash==0)
	{
		cleardevice();//把以前的页面清屏
		setbkcolor(WHITE);//背景色设置
	}
	
	
	//检测无人机状态信息
	
	
	sprintf(position,"%s%d%s%d%s",":(",st.uavx,",",st.uavy,")");
	
	
	
	switch(st.statuscode)
	{
		case 0:
			sprintf(status,"%s","无人机状态：空闲");
			break;
		case 1:
			sprintf(status,"%s","无人机状态：监测");
			break;
		case 2:
			sprintf(status,"%s","无人机状态：喷洒");
			break;
		case 3:
			sprintf(status,"%s","无人机状态：暂停");
			break;
	}
	
	setfillstyle(SOLID_FILL, WHITE);//设定红色框
	bar(0, 0, 600, 20);//阻挡标题
	
	puthz(2,2,status,16,18,BLUE);//显示无人机状态信息
	puthz(182,2,"无人机位置",16,18,BLUE);//显示无人机状态信息
	settextstyle(0,0,2);
	setcolor(BLUE);
	outtextxy(272, 4, position);
	

	if(st.statuscode==3)
	{
		setfillstyle(SOLID_FILL, RED);//设定绿色框
		bar(445, 445, 445+100, 445+25);//终止
		puthz(465, 450,"已暂停",16,18,BLUE);
		
		setfillstyle(SOLID_FILL, RED);//设定红色框
		bar(115, 445, 115+100, 445+25);//page3
		puthz(123, 450,"继续",16,18,BLUE);
	}
	else if(st.statuscode!=0)//如果无人机正在工作则显示终止按钮
	{
		//setfillstyle(SOLID_FILL, WHITE);//遮挡继续框
		//bar(115, 445, 115+100, 445+25);//page3
		setfillstyle(SOLID_FILL, WHITE);//设定红色框
		bar(444, 404, 446+100, 406+25);
		bar(444, 384, 446+100, 386+25);
		bar(444, 364, 446+100, 366+25);
		
		
	}
	else
	{
		setfillstyle(SOLID_FILL, RED);//设定红色框
		bar(115, 445, 115+100, 445+25);//page3
		puthz(123, 450,"一键配置",16,18,BLUE);
	
		setfillstyle(SOLID_FILL, RED);//设定红色框
		bar(5, 445, 5+100, 445+25);//page3
		puthz(13, 450,"基础配置",16,18,BLUE);
	
	
		setfillstyle(SOLID_FILL, RED);//设定红色框
		bar(225, 445, 225+100, 445+25);//page3
		puthz(233, 450,"开始喷洒",16,18,BLUE);
	
		setfillstyle(SOLID_FILL, RED);//设定红色框
		bar(335, 445, 335+100, 445+25);//返回主页
		puthz(343, 450,"返回主页",16,18,BLUE);
		
		setfillstyle(SOLID_FILL, RED);//设定红色框
		bar(445, 445, 445+100, 445+25);//
		puthz(450, 450,"疫病配置",16,18,BLUE);
		
		
		setfillstyle(SOLID_FILL, RED);//设定红色框
		bar(445, 405, 445+100, 405+25);//
		puthz(450, 410,"信息统计",16,18,BLUE);
		
		setfillstyle(SOLID_FILL, RED);//设定红色框
		bar(445, 365, 445+100, 365+25);//
		puthz(450, 370,"手动导航",16,18,BLUE);
		
		
		
	}
	
		
	
	
	for(i=0;i<mapy;i++)
	{
		for(j=0;j<mapx;j++)
		{
			
			if(plantmap[j][i].plantcode==1)
				setfillstyle(SOLID_FILL, RED);//患病位置显示为红色
			else
				setfillstyle(SOLID_FILL, GREEN);//正常位置显示为绿色
			bar(23+20*j, 43+20*i, 23+17+20*j, 43+17+20*i);
		}
	}
	setfillstyle(SOLID_FILL, BLUE);//设定红色框
	if(move==0)
	{
		setfillstyle(SOLID_FILL, BLUE);//无人机显示为蓝色
		bar(25+20*st.uavx, 45+20*st.uavy, 20+17+20*st.uavx, 40+17+20*st.uavy);
	}
	
	puthz(427, 27,"农药一",16,18,BLUE);
	setfillstyle(SOLID_FILL, BLUE);//农药1框
	bar(427, 47, 483, 153);
	setfillstyle(SOLID_FILL, WHITE);
	bar(430, 50, 480, 150);
	setfillstyle(SOLID_FILL, YELLOW);
	bar(430, 150-st.uavp[0], 480,150);
	
	puthz(527, 27,"农药二",16,18,BLUE);
	setfillstyle(SOLID_FILL, BLUE);//农药2框
	bar(527, 47, 583, 153);
	setfillstyle(SOLID_FILL, WHITE);
	bar(530, 50, 580, 150);
	setfillstyle(SOLID_FILL, YELLOW);
	bar(530, 150-st.uavp[1], 580, 150);
	
	puthz(427, 227,"农药三",16,18,BLUE);
	setfillstyle(SOLID_FILL, BLUE);//农药3框
	bar(427, 247, 483, 353);
	setfillstyle(SOLID_FILL, WHITE);
	bar(430, 250, 480, 350);
	setfillstyle(SOLID_FILL, YELLOW);
	bar(430, 350-st.uavp[2], 480, 350);
	
	puthz(527, 227,"农药四",16,18,BLUE);
	setfillstyle(SOLID_FILL, BLUE);//农药4框
	bar(527, 247, 583, 353);
	setfillstyle(SOLID_FILL, WHITE);
	bar(530, 250, 580, 350);
	setfillstyle(SOLID_FILL, YELLOW);
	bar(530, 350-st.uavp[3], 580, 350);
	
	
	
}


void writedata2(plantstatus (*write)[20])//写入作物信息
{
	FILE* fp=NULL;
	fp = fopen("plant.bin", "wb");
	if (fp == NULL) {
        printf("Failed to open file");
        return;
    }
	rewind(fp);
	// 一次性写入整个数组
    fwrite(write, sizeof(plantstatus), 30*20, fp);
	fclose(fp);
}

void readdata2(plantstatus (*read)[20])//读取作物信息
{
	FILE* fp=NULL;
	fp = fopen("plant.bin", "rb");
	if (fp == NULL) {
        printf("Failed to open file");
        return;
    }
	rewind(fp);
    fread(read, sizeof(plantstatus), 30*20, fp);
	fclose(fp);
}



void uav_step(int ix,int iy,int ox,int oy,int speed,int mapx,int mapy,plantstatus (*plantmap)[20])//无人机移动动画speed一秒几个像素
{
	
	int i=0,j=0,x,y;
	//float time;//k为移动一个像素x需要移动多少y
	
	ix=23+20*ix+8;//将坐标换算为像素点坐标
	iy=43+20*iy+8;
	ox=23+20*ox+8;//将坐标换算为像素点坐标
	oy=43+20*oy+8;
	//获取鼠标的位置和状态
	mou_pos(&MouseX,&MouseY,&press);
	//if (speed == 0) return;
	if (ix == ox && iy == oy) return;
	//time=(sqrt((oy-iy)*(oy-iy)+(ox-ix)*(ox-ix)))/speed;
	//x=(ox-ix)/time;
	//y=(oy-iy)/time;
	while(1)
	{
		//page2_screen(mapx,mapy,plantmap,tem,water,st,0,1);
		//获取鼠标的位置和状态
		mou_pos(&MouseX,&MouseY,&press);
		
		setfillstyle(SOLID_FILL, WHITE);//清除无人机
		bar(ix-6,iy-6,ix+5,iy+6);
		
		for(i=0;i<mapy;i++)
		{
			for(j=0;j<mapx;j++)
			{
				
				if(plantmap[j][i].plantcode==1)
					setfillstyle(SOLID_FILL, RED);//患病位置显示为红色
				else
					setfillstyle(SOLID_FILL, GREEN);//正常位置显示为绿色
					bar(23+20*j, 43+20*i, 23+17+20*j, 43+17+20*i);
			}
		}
		
		
		if(ix<ox)
		{		
			ix=ix+2;
		}
		if(iy<oy)
		{
			iy=iy+2;
			
		}
		if(ix>ox)
		{		
			ix=ix-2;
		}
		if(iy>oy)
		{
			iy=iy-2;
			
		}
		if(abs(ix-ox)<=2&&abs(iy-oy)<=2)
		{
			drawuavreal(ox,oy);//画出无人机
			delay(10);
			return;
		}
		
		drawuavreal(ix,iy);//画出无人机
		delay(1);
	}
}
	
coordinate nextxy(int mapx, int mapy, plantstatus (*plantmap)[20], int x, int y) 
{
    //coordinate result; // 初始化为当前坐标
	
    //int min_dist = 1000;     // 足够大的初始距离值
    //int current_dist;
    //int i, j;
	
	coordinate result = {-1, -1};
    int max_distance = mapx + mapy; // 最大可能距离作为上限
    int d, dx, abs_dx, dy_abs, dy_sign, dy, nx, ny; // 所有中间变量提前声明
	
 
    // 先检查当前坐标是否有效且患病
    if (x >= 0 && x < mapx && y >= 0 && y < mapy && plantmap[x][y].plantcode == 1) 
	{
		result.x=x;
		result.y=y;
        return result;
    }
	/*
    // 遍历整个地图寻找最近患病点
    for (i = 0; i < mapy; i++) 
	{
        for (j = 0; j < mapx; j++) 
		{
            if (plantmap[i][j].plantcode == 1) 
			{
                // 计算距离
                current_dist = abs(i - x) + abs(j - y);
                
                // 更新最小距离和坐标
                if (current_dist < min_dist) 
				{
                    min_dist = current_dist;
                    result.x = i;
                    result.y = j;
                } 
            }
        }
    }
	
    return result;
	*/
	
	   
 
    for (d = 0; d <= max_distance; d++) {
        for (dx = -d; dx <= d; dx++) {
            abs_dx = abs(dx);
            dy_abs = d - abs_dx;
            if (dy_abs < 0) continue;
 
            // 遍历dy的可能值（先负后正，确保列号优先）
            for (dy_sign = -1; dy_sign <= 1; dy_sign += 2) {
                dy = dy_sign * dy_abs;
                nx = x + dx;
                ny = y + dy;
 
                // 检查坐标是否在地图范围内
                if (nx >= 0 && nx < mapx && ny >= 0 && ny < mapy) {
                    if (plantmap[nx][ny].plantcode == 1) {
                        // 找到最近的患病点，直接返回
                        result.x = nx;
                        result.y = ny;
                        return result;
                    }
                }
            }
        }
    }
 
    return result; // 未找到患病点

}

drawuav(int x,int y)
{
	setfillstyle(SOLID_FILL, BLUE);
	bar(25+20*x, 45+20*y, 20+17+20*x, 40+17+20*y);
}

drawuavreal(int x,int y)
{
	setfillstyle(SOLID_FILL, BLUE);
	bar(x-6,y-6,x+5,y+6);
}

