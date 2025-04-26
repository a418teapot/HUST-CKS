#ifndef _COMMON_H_
#define _COMMON_H_

#include<graphics.h>
#include<stdio.h>
#include<stdlib.h>
#include<bios.h>
#include<dos.h>
#include<string.h>
#include<conio.h>
#include<time.h>
#include<math.h>
#include"mouse.h"
#include"hz.h"

typedef struct ACCOUNT
{
	char id[15];
	char password[15];
	
}ACCOUNT;




typedef struct uavstatus//无人机状态包
{
	int statuscode;//状态码，0空闲，1监测，2喷洒,3暂停
	int uavx,uavy;//无人机位置
	int uavp[4];//无人农药仓储量
}uavstatus;

typedef struct illtype
{
	char illname[20];
	int pesti[4];//记录四种农药所需量
	
}illtype;


typedef struct plantstatus//田地状态包
{
	int plantcode;//状态码，0正常，1患病
	int illnumber;//患病种类
	
}plantstatus;



typedef struct coordinate{ // 定义坐标结构体
    int x;
    int y;
} coordinate;



#endif