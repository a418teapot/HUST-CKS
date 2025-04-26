#include "common.h"
#include "page9.h"

//��Ϊ��Ҫ����pageֵ������ҳ��ĺ�������int��
int p9()
{
	int page=0,humidity;
	float wind_speed,temperature;
	
	//��ֹ�������תҳ��ʱ����
	clrmous(MouseX,MouseY);
	delay(200);
	srand((unsigned)time(NULL));//���������
	
	// ���٣�0-30 m/s
	wind_speed = (float)(rand() % 3001) / 100.0f; 
	 
	// �¶ȣ�-20-60��
	temperature = (float)(rand() % 8001) / 100.0f - 20.0f;
	 
	// ʪ�ȣ�0-100%
	humidity = rand() % 101;

	page9_screen(wind_speed,temperature,humidity);
	while(page==0)
	{
		//��ȡ����λ�ú�״̬
		mou_pos(&MouseX,&MouseY,&press);
		if(mouse_press(300, 350, 400, 400)==1)
		{
			page=2;
		}
	}
	return page;
	
}

//����ҳ��9����
void page9_screen(float wind_speed,float temperature,int humidity)
{
	char temp[10];
	cleardevice();//����ǰ��ҳ������
	setbkcolor(LIGHTCYAN);//����ɫ����
	puthz(120, 10,"��ӭ��½ϵͳ���������������",32,34,BLUE);
	
	num_to_str9((int)wind_speed,temp);
	if (wind_speed > 15.0f) 
	{
		puthz(10, 50,"���٣���ÿ�룩��",16,18,RED);
		settextstyle(0,0,2);
		setcolor(RED);
		outtextxy(156,55, temp);
		puthz(10, 80,"���ؾ��棺���ٳ���ʮ����ÿ�룡��������ɣ�",16,18,RED);
		
	} 
	else if (wind_speed > 10.0f) 
	{
		puthz(10, 50,"���٣���ÿ�룩��",16,18,LIGHTRED);
		settextstyle(0,0,2);
		setcolor(LIGHTRED);
		outtextxy(156,55, temp);
		puthz(10, 80,"���棺���ٳ���ʮ��ÿ�룬�����������",16,18,LIGHTRED);
	}
	else
	{
		puthz(10, 50,"���٣���ÿ�룩��",16,18,GREEN);
		settextstyle(0,0,2);
		setcolor(GREEN);
		outtextxy(156,55, temp);
		puthz(10, 80,"����",16,18,GREEN);
	}
	
	num_to_str9((int)temperature,temp);
	if (temperature < 0.0f || temperature > 40.0f) 
	{
		
		puthz(10, 150,"�¶ȣ����϶ȣ���",16,18,RED);
		settextstyle(0,0,2);
		setcolor(RED);
		outtextxy(156,155, temp);
		puthz(10, 180,"���棺��ǰ�¶ȿ���Ӱ���豸���ܣ�",16,18,RED);
	}
	else
	{
		puthz(10, 150,"�¶ȣ����϶ȣ���",16,18,GREEN);
		settextstyle(0,0,2);
		setcolor(GREEN);
		outtextxy(156,155, temp);
		puthz(10, 180,"�¶�����",16,18,GREEN);
	}
	
	num_to_str9((int)humidity,temp);
	if (humidity > 95) 
	{
		puthz(10, 250,"ʪ�ȣ��ٷ�֮����",16,18,RED);
		settextstyle(0,0,2);
		setcolor(RED);
		outtextxy(156,255, temp);
		puthz(10, 280,"���ؾ��棺ʪ�ȹ��ߣ����ڶ�·���գ����������",16,18,RED);
	} 
	else if (humidity > 80)
	{
		puthz(10, 250,"ʪ�ȣ��ٷ�֮����",16,18,LIGHTRED);
		settextstyle(0,0,2);
		setcolor(LIGHTRED);
		outtextxy(156,255, temp);
		puthz(10, 280,"���棺�뾡�����������з��У�",16,18,LIGHTRED);
	}
	else
	{
		puthz(10, 250,"ʪ�ȣ��ٷ�֮����",16,18,GREEN);
		settextstyle(0,0,2);
		setcolor(GREEN);
		outtextxy(156,255, temp);
		puthz(10, 280,"ʪ������",16,18,GREEN);
	}
	
	
	setfillstyle(SOLID_FILL, RED);//�趨��ɫ��
	bar(300, 350, 400, 400);//
	puthz(340, 370,"ȷ��",16,18,BLUE);
	
}


void num_to_str9(int i,char *numstr)//����ת���ַ���
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

void reverseString9(char *str,int length) //�ߵ��ַ���
{
	int i = 0;
    char temp;
    
    // ʹ������ָ�룬һ�����ַ����Ŀ�ͷ����ƶ�����һ�����ַ�����ĩβ��ǰ�ƶ�����������ָ����ַ�
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
        return; // ��ָ����Ѿ��Ǹ�����ֱ�ӷ���
    }
	str[strlen(str)+1]='\0';
    // �ƶ��ַ���Ϊ�����ڳ��ռ�
    for (i = strlen(str); i > 0; --i) 
	{
        str[i] = str[i - 1];
    }
	
    // ��Ӹ���
    str[0] = '-';
}