#ifndef _PAGE2_H_
#define _PAGE2_H_

#include "page7.h"

int p2(int mapx,int mapy,plantstatus (*plantmap)[20],int *plantx,int *planty);
/*函数功能：页面2*/

void page2_screen(int mapx,int mapy,plantstatus (*plantmap)[20],uavstatus st,int noflash,int move);//绘制页面二

void writedata2(plantstatus (*write)[20]);

coordinate nextxy(int mapx, int mapy, plantstatus (*plantmap)[20], int x, int y);

void readdata2(plantstatus (*read)[20]);

void uav_step(int ix,int iy,int ox,int oy,int speed,int mapx,int mapy, plantstatus (*plantmap)[20]);//无人机移动动画speed一秒几个像素

drawuav(int x,int y);


drawuavreal(int x,int y);


#endif