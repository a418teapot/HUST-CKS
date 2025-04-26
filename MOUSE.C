#include<conio.h>
#include<graphics.h>
#include<dos.h>
#include<stdio.h>
#include<stdlib.h>
#include "mouse.h"

int MouseX;
int MouseY;
int press;
void *buffer;
union REGS regs;
int flag=0;

void mouseinit()//初始化
{
	int retcode;
	int xmin,xmax,ymin,ymax,x_max=625,y_max=480;
	int size;

	xmin=2;
	xmax=x_max-1;
	ymin=8;
	ymax=y_max-2;
	regs.x.ax=0;
	int86(51,&regs,&regs);
	retcode=regs.x.ax;
	if(retcode==0)
	{
		printf("Mouse or Mouse Driver Obsent,Please Install!");
		delay(5000);
	}
	else
	{
		regs.x.ax=7;
		regs.x.cx=xmin;
		regs.x.dx=xmax;
		int86(51,&regs,&regs);
		regs.x.ax=8;
		regs.x.cx=ymin;
		regs.x.dx=ymax;
		int86(51,&regs,&regs);
	}
	MouseX=320,MouseY=240;
	save_bk_mou(320,240);
	mouse(MouseX,MouseY);
	flag=1;
}

void mouse(int x,int y)
{
	setlinestyle(0,0,1);
	setcolor(WHITE);
	line(x,y,x,y+13);
	line(x+1,y+1,x+1,y+12);
	line(x+2,y+2,x+2,y+11);
	line(x+3,y+3,x+3,y+10);
	line(x+4,y+4,x+4,y+12);
	line(x+5,y+5,x+5,y+9);
	line(x+5,y+11,x+5,y+14);
	line(x+6,y+6,x+6,y+9);
	line(x+6,y+13,x+6,y+15);
	line(x+7,y+7,x+7,y+9);
	line(x+8,y+8,x+8,y+9);
	line(x+9,y+9,x+9,y+9);
	setcolor(DARKGRAY);
	line(x-1,y-1,x-1,y+14);
	line(x-1,y+14,x+3,y+11);
	line(x+3,y+11,x+3,y+12);
	line(x+3,y+12,x+4,y+13);
	line(x+4,y+13,x+4,y+14);
	line(x+4,y+14,x+7,y+17);
	line(x+7,y+17,x+7,y+13);
	line(x+7,y+13,x+6,y+12);
	line(x+6,y+12,x+6,y+11);
	line(x+6,y+11,x+5,y+10);
	line(x+5,y+10,x+11,y+10);
	line(x+11,y+10,x-1,y-2);
}

void mou_pos(int *nx,int *ny,int*nbuttons)//更改鼠标位置
{
	int x0=*nx,y0=*ny;

	mread(nx,ny,nbuttons);
	clrmous(x0,y0);
	save_bk_mou(*nx,*ny);
	drawmous(*nx,*ny);
}

void mread(int *nx,int *ny,int*nbuttons)//改坐标不画
{
	int x0=*nx,y0=*ny,buttons0=*nbuttons;
	int xnew,ynew,buttonsnew;

	//do{
	regs.x.ax=3;
	int86(51,&regs,&regs);
	buttonsnew=regs.x.bx;
	delay(10);
	regs.x.ax=3;
	int86(51,&regs,&regs);
	if(regs.x.bx==buttonsnew)
		*nbuttons=regs.x.bx;
	else
		*nbuttons=buttons0;
	xnew=regs.x.cx;
	ynew=regs.x.dx;
	//}while(xnew==x0&&ynew==y0&&*nbuttons==0);
	*nx=xnew;
	*ny=ynew;
}

void save_bk_mou(int nx,int ny)//存鼠标背景
{
	int size;

	size=imagesize(nx-1,ny-2,nx+11,ny+17);
	buffer=malloc(size);
	if(buffer!=NULL)
		getimage(nx-1,ny-2,nx+11,ny+17,buffer);
	else
		printf("Error");
}

void clrmous(int nx,int ny)//清除鼠标
{
	if(flag==1)
	{
		setwritemode(XOR_PUT);
		mouse(nx,ny);
		putimage(nx-1,ny-2,buffer,COPY_PUT);
		free(buffer);
		flag=0;
		setwritemode(COPY_PUT);
	}
}
void drawmous(int nx,int ny)
{
	if(flag==0)
	{
		setwritemode(COPY_PUT);
	    mouse(nx,ny);
		flag=1;
	}
}



//如果在框中点击，则返回1；在框中未点击，则返回2；不在框中则返回0
int mouse_press(int x1, int y1, int x2, int y2)
{
	//在框中点击，则返回1
	if(MouseX > x1 
	&&MouseX < x2
	&&MouseY > y1
	&&MouseY < y2
	&&press == 1)
	{
		return 1;
	}
	
	//在框中未点击，则返回2
	else if(MouseX > x1 
	&&MouseX < x2
	&&MouseY > y1
	&&MouseY < y2
	&&press == 0)
	{
		return 2;
	}
	
	//在框中点击右键，则返回3
	else if(MouseX > x1 
	&&MouseX < x2
	&&MouseY > y1
	&&MouseY < y2
	&&press == 2)
	{
		return 3;
	}
	
	else
	{
		return 0;
	}
}



