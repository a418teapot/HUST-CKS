#include "common.h"
#include "page2.h"

//��Ϊ��Ҫ����pageֵ������ҳ��ĺ�������int��
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
	
	//��ֹ�������תҳ��ʱ����
	clrmous(MouseX,MouseY);
	delay(200);
	page2_screen(mapx,mapy,plantmap,uav,0,0);
	srand((unsigned)time(NULL));//���������
	
	
	//�����֪�߲�����
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
	
	/*ѭ������ͣ�ؼ���춯�����춯����pageֵ�ı䣬��תҳ��*/
	while(page == 0)
	{
		//��ȡ����λ�ú�״̬
		mou_pos(&MouseX,&MouseY,&press);
		
		//����˳������
		if(mouse_press(5, 445, 5+100, 445+25) == 1)//��������
		{
			for(i=0;i<30;i++)//������ݳ�ʼ��
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
		else if(mouse_press(115, 445, 115+100, 445+25) == 1)//���
		{
			uav.statuscode=1;
			clrmous(MouseX,MouseY);
			delay(100);
			page2_screen(mapx,mapy,plantmap,uav,0,0);
			for(uav.uavx=0;uav.uavx<mapy;uav.uavx++)
			{
				while(uav.uavy<mapy&&uav.uavy>=0)
				{
					
					//����һ�����������ģ��ֲ���������ʵ�ʿɽ��봫�����ӿ�
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
		else if(mouse_press(225, 445, 225+100, 445+25) == 1)//����
		{
			uav.statuscode=2;
			clrmous(MouseX,MouseY);
			delay(100);
			while(1)
			{
				//��ȡ����λ�ú�״̬
				mou_pos(&MouseX,&MouseY,&press);
				setfillstyle(SOLID_FILL, WHITE);
				bar(0, 435, 640, 480);
				puthz(5,440,"����·����",32,34,BLUE);
				next=nextxy(mapx,mapy,plantmap,uav.uavx,uav.uavy);
				if(next.x==-1||next.y==-1)
				{
					break;
				}
				
				
				
				
				/*********************************************************************************************************/
				//settextstyle(0,0,2);
				//setcolor(BLUE);
				//num_to_str7(plantmap[next.x][next.y].illnumber-1,outputy);
				//setfillstyle(SOLID_FILL, WHITE);//����λ����ʾΪ��ɫ
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
				uav.uavp[3]<read[plantmap[next.x][next.y].illnumber-1].pesti[3])//���ز���ũҩ
				{
					
					setfillstyle(SOLID_FILL, WHITE);
					bar(0, 435, 640, 480);
					puthz(5,440,"ҩ�����㣬���ز��䡣",32,34,RED);
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
							puthz(5,440,"�������",32,34,BLUE);
								
							break;
						}
						
							//��ȡ����λ�ú�״̬
							mou_pos(&MouseX,&MouseY,&press);
							delay(100);
						
						
					}
					
				}
				else//��ʼǰ������
				{
					
					setfillstyle(SOLID_FILL, WHITE);
					bar(0, 435, 640, 480);
					puthz(5,440,"������",32,34,BLUE);
					uav_step(uav.uavx,uav.uavy,next.x,next.y,10,mapx,mapy,plantmap);
					uav.uavx=next.x;
					uav.uavy=next.y;
					setfillstyle(SOLID_FILL, WHITE);
					bar(0, 435, 640, 480);
					puthz(5,440,"������",32,34,BLUE);
					/*********************************************************************************************************/
					//settextstyle(0,0,2);
					//setcolor(BLUE);
					//num_to_str7(plantmap[next.x][next.y].illnumber-1,outputy);
					//setfillstyle(SOLID_FILL, WHITE);//����λ����ʾΪ��ɫ
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
						//��ȡ����λ�ú�״̬
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
								break;//��ͼ���������
							}
							
						delay(100);
						
					}
				}
				
				page2_screen(mapx,mapy,plantmap,uav,1,0);
			}
			setfillstyle(SOLID_FILL, WHITE);
			bar(0, 435, 640, 480);
			puthz(5,440,"������ϣ����ڷ���",32,34,RED);
			uav_step(uav.uavx,uav.uavy,0,0,10,mapx,mapy,plantmap);
			uav.uavx=0;
			uav.uavy=0;
			setfillstyle(SOLID_FILL, WHITE);
			bar(0, 435, 640, 480);
			uav.statuscode=0;
			page2_screen(mapx,mapy,plantmap,uav,0,0);
		}
		else if(mouse_press(335, 445, 335+100, 445+25) == 1)//�ص�������
		{
			page=1;
		}
		else if(mouse_press(445, 445, 445+100, 445+25) == 1)//�����߲�
		{
			page=6;
		}
		else if(mouse_press(445, 405, 445+100, 405+25) == 1)//ͳ��
		{
			page=8;
		}
		else if(mouse_press(445, 365, 445+100, 365+25) == 1)//�ֶ�����
		{
			uav.statuscode=1;
			clrmous(MouseX,MouseY);
			delay(100);
			page2_screen(mapx,mapy,plantmap,uav,0,0);
			setfillstyle(SOLID_FILL, RED);//�趨��ɫ��
			bar(545, 385, 545+100, 385+25);//
			puthz(550, 390,"�˳�",16,18,BLUE);
			while(1)
			{
				mou_pos(&MouseX,&MouseY,&press);
				
				for(i=0;i<mapy;i++)
				{
					for(j=0;j<mapx;j++)
					{
						
						if(mouse_press(23+20*j, 43+20*i, 23+17+20*j, 43+17+20*i)==1)//���ĳһ�����
						{
							next.x=j;
							next.y=i;
							uav_step(uav.uavx,uav.uavy,next.x,next.y,10,mapx,mapy,plantmap);
							uav.uavx=next.x;
							uav.uavy=next.y;
						}
					}
				}
				
				if(mouse_press(545, 385, 545+100, 385+25)==1)//����˳�
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
					
					if(mouse_press(23+20*j, 43+20*i, 23+17+20*j, 43+17+20*i)==1)//�������ĳһ����ص���Ϣ
					{
						p7(&plantmap[j][i],j,i);
						writedata2(plantmap);
						//��ֹ�������תҳ��ʱ����
						clrmous(MouseX,MouseY);
						delay(200);
						page2_screen(mapx,mapy,plantmap,uav,0,0);
					}
				}
			}
		}
	}
	return page;//����2����������ҳ����תѭ��
}

//����ҳ��2����
void page2_screen(int mapx,int mapy,plantstatus (*plantmap)[20],uavstatus st,int noflash,int move)
{
	int i=0,j=0;
	char status[30],position[20];
	if(noflash==0)
	{
		cleardevice();//����ǰ��ҳ������
		setbkcolor(WHITE);//����ɫ����
	}
	
	
	//������˻�״̬��Ϣ
	
	
	sprintf(position,"%s%d%s%d%s",":(",st.uavx,",",st.uavy,")");
	
	
	
	switch(st.statuscode)
	{
		case 0:
			sprintf(status,"%s","���˻�״̬������");
			break;
		case 1:
			sprintf(status,"%s","���˻�״̬�����");
			break;
		case 2:
			sprintf(status,"%s","���˻�״̬������");
			break;
		case 3:
			sprintf(status,"%s","���˻�״̬����ͣ");
			break;
	}
	
	setfillstyle(SOLID_FILL, WHITE);//�趨��ɫ��
	bar(0, 0, 600, 20);//�赲����
	
	puthz(2,2,status,16,18,BLUE);//��ʾ���˻�״̬��Ϣ
	puthz(182,2,"���˻�λ��",16,18,BLUE);//��ʾ���˻�״̬��Ϣ
	settextstyle(0,0,2);
	setcolor(BLUE);
	outtextxy(272, 4, position);
	

	if(st.statuscode==3)
	{
		setfillstyle(SOLID_FILL, RED);//�趨��ɫ��
		bar(445, 445, 445+100, 445+25);//��ֹ
		puthz(465, 450,"����ͣ",16,18,BLUE);
		
		setfillstyle(SOLID_FILL, RED);//�趨��ɫ��
		bar(115, 445, 115+100, 445+25);//page3
		puthz(123, 450,"����",16,18,BLUE);
	}
	else if(st.statuscode!=0)//������˻����ڹ�������ʾ��ֹ��ť
	{
		//setfillstyle(SOLID_FILL, WHITE);//�ڵ�������
		//bar(115, 445, 115+100, 445+25);//page3
		setfillstyle(SOLID_FILL, WHITE);//�趨��ɫ��
		bar(444, 404, 446+100, 406+25);
		bar(444, 384, 446+100, 386+25);
		bar(444, 364, 446+100, 366+25);
		
		
	}
	else
	{
		setfillstyle(SOLID_FILL, RED);//�趨��ɫ��
		bar(115, 445, 115+100, 445+25);//page3
		puthz(123, 450,"һ������",16,18,BLUE);
	
		setfillstyle(SOLID_FILL, RED);//�趨��ɫ��
		bar(5, 445, 5+100, 445+25);//page3
		puthz(13, 450,"��������",16,18,BLUE);
	
	
		setfillstyle(SOLID_FILL, RED);//�趨��ɫ��
		bar(225, 445, 225+100, 445+25);//page3
		puthz(233, 450,"��ʼ����",16,18,BLUE);
	
		setfillstyle(SOLID_FILL, RED);//�趨��ɫ��
		bar(335, 445, 335+100, 445+25);//������ҳ
		puthz(343, 450,"������ҳ",16,18,BLUE);
		
		setfillstyle(SOLID_FILL, RED);//�趨��ɫ��
		bar(445, 445, 445+100, 445+25);//
		puthz(450, 450,"�߲�����",16,18,BLUE);
		
		
		setfillstyle(SOLID_FILL, RED);//�趨��ɫ��
		bar(445, 405, 445+100, 405+25);//
		puthz(450, 410,"��Ϣͳ��",16,18,BLUE);
		
		setfillstyle(SOLID_FILL, RED);//�趨��ɫ��
		bar(445, 365, 445+100, 365+25);//
		puthz(450, 370,"�ֶ�����",16,18,BLUE);
		
		
		
	}
	
		
	
	
	for(i=0;i<mapy;i++)
	{
		for(j=0;j<mapx;j++)
		{
			
			if(plantmap[j][i].plantcode==1)
				setfillstyle(SOLID_FILL, RED);//����λ����ʾΪ��ɫ
			else
				setfillstyle(SOLID_FILL, GREEN);//����λ����ʾΪ��ɫ
			bar(23+20*j, 43+20*i, 23+17+20*j, 43+17+20*i);
		}
	}
	setfillstyle(SOLID_FILL, BLUE);//�趨��ɫ��
	if(move==0)
	{
		setfillstyle(SOLID_FILL, BLUE);//���˻���ʾΪ��ɫ
		bar(25+20*st.uavx, 45+20*st.uavy, 20+17+20*st.uavx, 40+17+20*st.uavy);
	}
	
	puthz(427, 27,"ũҩһ",16,18,BLUE);
	setfillstyle(SOLID_FILL, BLUE);//ũҩ1��
	bar(427, 47, 483, 153);
	setfillstyle(SOLID_FILL, WHITE);
	bar(430, 50, 480, 150);
	setfillstyle(SOLID_FILL, YELLOW);
	bar(430, 150-st.uavp[0], 480,150);
	
	puthz(527, 27,"ũҩ��",16,18,BLUE);
	setfillstyle(SOLID_FILL, BLUE);//ũҩ2��
	bar(527, 47, 583, 153);
	setfillstyle(SOLID_FILL, WHITE);
	bar(530, 50, 580, 150);
	setfillstyle(SOLID_FILL, YELLOW);
	bar(530, 150-st.uavp[1], 580, 150);
	
	puthz(427, 227,"ũҩ��",16,18,BLUE);
	setfillstyle(SOLID_FILL, BLUE);//ũҩ3��
	bar(427, 247, 483, 353);
	setfillstyle(SOLID_FILL, WHITE);
	bar(430, 250, 480, 350);
	setfillstyle(SOLID_FILL, YELLOW);
	bar(430, 350-st.uavp[2], 480, 350);
	
	puthz(527, 227,"ũҩ��",16,18,BLUE);
	setfillstyle(SOLID_FILL, BLUE);//ũҩ4��
	bar(527, 247, 583, 353);
	setfillstyle(SOLID_FILL, WHITE);
	bar(530, 250, 580, 350);
	setfillstyle(SOLID_FILL, YELLOW);
	bar(530, 350-st.uavp[3], 580, 350);
	
	
	
}


void writedata2(plantstatus (*write)[20])//д��������Ϣ
{
	FILE* fp=NULL;
	fp = fopen("plant.bin", "wb");
	if (fp == NULL) {
        printf("Failed to open file");
        return;
    }
	rewind(fp);
	// һ����д����������
    fwrite(write, sizeof(plantstatus), 30*20, fp);
	fclose(fp);
}

void readdata2(plantstatus (*read)[20])//��ȡ������Ϣ
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



void uav_step(int ix,int iy,int ox,int oy,int speed,int mapx,int mapy,plantstatus (*plantmap)[20])//���˻��ƶ�����speedһ�뼸������
{
	
	int i=0,j=0,x,y;
	//float time;//kΪ�ƶ�һ������x��Ҫ�ƶ�����y
	
	ix=23+20*ix+8;//�����껻��Ϊ���ص�����
	iy=43+20*iy+8;
	ox=23+20*ox+8;//�����껻��Ϊ���ص�����
	oy=43+20*oy+8;
	//��ȡ����λ�ú�״̬
	mou_pos(&MouseX,&MouseY,&press);
	//if (speed == 0) return;
	if (ix == ox && iy == oy) return;
	//time=(sqrt((oy-iy)*(oy-iy)+(ox-ix)*(ox-ix)))/speed;
	//x=(ox-ix)/time;
	//y=(oy-iy)/time;
	while(1)
	{
		//page2_screen(mapx,mapy,plantmap,tem,water,st,0,1);
		//��ȡ����λ�ú�״̬
		mou_pos(&MouseX,&MouseY,&press);
		
		setfillstyle(SOLID_FILL, WHITE);//������˻�
		bar(ix-6,iy-6,ix+5,iy+6);
		
		for(i=0;i<mapy;i++)
		{
			for(j=0;j<mapx;j++)
			{
				
				if(plantmap[j][i].plantcode==1)
					setfillstyle(SOLID_FILL, RED);//����λ����ʾΪ��ɫ
				else
					setfillstyle(SOLID_FILL, GREEN);//����λ����ʾΪ��ɫ
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
			drawuavreal(ox,oy);//�������˻�
			delay(10);
			return;
		}
		
		drawuavreal(ix,iy);//�������˻�
		delay(1);
	}
}
	
coordinate nextxy(int mapx, int mapy, plantstatus (*plantmap)[20], int x, int y) 
{
    //coordinate result; // ��ʼ��Ϊ��ǰ����
	
    //int min_dist = 1000;     // �㹻��ĳ�ʼ����ֵ
    //int current_dist;
    //int i, j;
	
	coordinate result = {-1, -1};
    int max_distance = mapx + mapy; // �����ܾ�����Ϊ����
    int d, dx, abs_dx, dy_abs, dy_sign, dy, nx, ny; // �����м������ǰ����
	
 
    // �ȼ�鵱ǰ�����Ƿ���Ч�һ���
    if (x >= 0 && x < mapx && y >= 0 && y < mapy && plantmap[x][y].plantcode == 1) 
	{
		result.x=x;
		result.y=y;
        return result;
    }
	/*
    // ����������ͼѰ�����������
    for (i = 0; i < mapy; i++) 
	{
        for (j = 0; j < mapx; j++) 
		{
            if (plantmap[i][j].plantcode == 1) 
			{
                // �������
                current_dist = abs(i - x) + abs(j - y);
                
                // ������С���������
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
 
            // ����dy�Ŀ���ֵ���ȸ�������ȷ���к����ȣ�
            for (dy_sign = -1; dy_sign <= 1; dy_sign += 2) {
                dy = dy_sign * dy_abs;
                nx = x + dx;
                ny = y + dy;
 
                // ��������Ƿ��ڵ�ͼ��Χ��
                if (nx >= 0 && nx < mapx && ny >= 0 && ny < mapy) {
                    if (plantmap[nx][ny].plantcode == 1) {
                        // �ҵ�����Ļ����㣬ֱ�ӷ���
                        result.x = nx;
                        result.y = ny;
                        return result;
                    }
                }
            }
        }
    }
 
    return result; // δ�ҵ�������

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

