#include "common.h"
#include "main.h"

void main(void)
{
	int i=0,j=0,size=100;
	FILE *fp=NULL;
	ACCOUNT accountinfo[10]={0};
	uavstatus st;
	int map[2]={10,10},plantx=0,planty=0;//地图面积map[0]*map[1],plantxy用于传递鼠标所点击的地块参数
	plantstatus plantmap[30][20];
	/***********各种初始化*****************/
	/*设定初始页面
	调试的时候可以改变page的初始设定，直接跳转到需要调试的页面
	*/
	int page = 1;
	//VGA画图的初始化
    int graphdriver = VGA;
    int	graphmode = VGAHI;
    initgraph(&graphdriver, &graphmode, "BGI");
	//鼠标的初始化
	mouseinit();
	for(i=0;i<30;i++)//田地数据初始化
	{
		for(j=0;j<20;j++)
		{
			plantmap[i][j].plantcode=0;
			plantmap[i][j].illnumber=0;
		}
	}
	srand((unsigned)time(NULL));
	if ((fp = fopen("acc.bin", "rb")) == NULL) 
	{
		fclose(fp);
		fp = fopen("acc.bin", "wb");
		fwrite(accountinfo,sizeof(ACCOUNT),10,fp);
		
	}
	fclose(fp);
	if ((fp = fopen("plant.bin", "rb")) == NULL) 
	{
		fclose(fp);
		fp = fopen("plant.bin", "wb");
		rewind(fp);
		fwrite(plantmap, sizeof(plantstatus), 20*30, fp);
		
	}
	fclose(fp);
	
	/*
	*********页面跳转循环***********
	每一个页面对应一个page值，
	在各个页面的程序中，每一次有需要跳转页面的时候，就改变page值，且回到主程序
	在主程序的循环中，通过page值的改变，跳转到相应页面
	*/
	while(1)
	{
		switch(page)
		{
			case 1://页面1（初始页面）
			    page = p1();
				break;
				
			case 2://页面2
			    page = p2(map[0],map[1],plantmap,&plantx,&planty);
				break;
				
			case -1://退出程序
				closegraph();//关闭画图
			    exit(0);//退出程序
				
			case 3:
				page = p3(&map[0],&map[1],&size);//更改基础配置页面
				break;
				
			//case 4:
				//page = p4(&plantmap[plantx][planty]);//更改地块的面积页面
				//break;
				
			case 5:
				page = p5();
				break;
				
			case 6:
				page = p6();
				break;
				
			case 8:
				page = p8();
				break;
				
			case 9:
				page = p9();
				break;
		}
	}
}
		
				
