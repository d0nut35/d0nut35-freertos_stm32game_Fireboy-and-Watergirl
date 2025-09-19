#include "menu.h"

static char text[]="P L A Y";
static char text10[]="P O I N T";
static char text3[]="F I R E && I C E";
static char text30[]="S E L E C T  L E V E L";
static char text4[]="> >";


/*控制灯的亮度, 0-1000*/
void LCD_LIGHT(uint16_t num)
{
	__HAL_TIM_SET_COMPARE(&htim12, TIM_CHANNEL_1, num);

}




void LCD_ShowString222(uint16_t x,uint16_t y,uint8_t size,uint8_t *p,uint8_t mode,uint16_t BACK,uint16_t point)
{         
    while((*p<='~')&&(*p>=' '))//判断是不是非法字符!
    {   
		if(x>(lcddev.width-1)||y>(lcddev.height-1)) 
		return;     
        LCD_ShowChar(x,y,point,BACK,*p,size,mode);
        x+=size/2;
        p++;
    }  
} 

/*主菜单函数此后仿照该菜单书写次级菜单，嵌套再次*/
void main_menu(struct option_class *option1)
{
	/*打印菜单信息*/
	
	LCD_ShowString222(155,50,20,(uint8_t*)text3,1,WHITE,DARKBLUE );
	
	LCD_ShowString222(190,100,20,(uint8_t*)text,1,BLACK,DARKBLUE );
	
	LCD_ShowString222(190,150,20,(uint8_t*)text10,1,BLACK,DARKBLUE );
	
	LCD_ShowString222(140,100,20,(uint8_t*)text4,1,BLACK,DARKBLUE );
	
	/*用于存储菜单数目*/
	uint8_t menu_num=0;
	int8_t Cursor=1;
	
	while(option1[menu_num].Name[0] != '.') menu_num++;
	Cursor=1;
	
	while(1)
	{
		
		KEY_Data k_data;
		key_read(&k_data);
		
		if(!k_data.E_KEY)
		{
			if(Cursor==1)
			{
				level_menu();
			}
			
			if(Cursor==2)
			{
				data_menu();
			}
		}
		
		
		
		/*调节光标位置*/
		if(!k_data.A_KEY)
		{
			
			while(!k_data.A_KEY){ key_read(&k_data);};
			Cursor--;
		}
		if(!k_data.C_KEY)
		{
			
			while(!k_data.C_KEY){key_read(&k_data); };
			Cursor++;
		}
		
		if(Cursor>menu_num) Cursor=menu_num;
		else if(Cursor<1) Cursor=1;
		else Cursor=Cursor;
		
		if(Cursor==1)
		{
			LCD_Fill(140,150,180,170,LIGHTGRAY);
			LCD_ShowString222(140,100,20,(uint8_t*)text4,1,BLACK,DARKBLUE );
		}
		else
		{
			LCD_Fill(140,100,180,120,LIGHTGRAY);
			LCD_ShowString222(140,150,20,(uint8_t*)text4,1,BLACK,DARKBLUE );
		}
		LCD_ShowNum(0,0,Cursor,3,20);
		
		
		
	}
}

void level_menu(void)
{
	extern const unsigned char gImage_map1[307200];
	Gui_Drawbmp16(0,0,gImage_map1,480,320);
	
	LCD_ShowString222(130,10,20,(uint8_t*)text30,1,WHITE,DARKBLUE );
	char text1[]="L E V E L 1";
	LCD_ShowString222(190,50,20,(uint8_t*)text1,1,WHITE,DARKBLUE );
	strcpy(text1,"L E V E L 2");
	LCD_ShowString222(190,90,20,(uint8_t*)text1,1,WHITE,DARKBLUE );
	strcpy(text1,"L E V E L 3");
	LCD_ShowString222(190,130,20,(uint8_t*)text1,1,WHITE,DARKBLUE );
	strcpy(text1,"L E V E L 4");
	LCD_ShowString222(190,170,20,(uint8_t*)text1,1,WHITE,DARKBLUE );
	strcpy(text1,"L E V E L 5");
	LCD_ShowString222(190,210,20,(uint8_t*)text1,1,WHITE,DARKBLUE );
	
	int8_t Cursor=1;
	uint8_t max=5;
	while(1)
	{
		//LCD_ShowString222(140,50,20,(uint8_t*)text4,1,BLACK,DARKBLUE );
		KEY_Data k_data;
		key_read(&k_data);
	
		if(!k_data.E_KEY)
		{
			switch (Cursor)
			{
				case 1:
				{
					
					g_level=1;
					
					xTaskCreate(game1_task, "GameTask", 128, NULL, osPriorityNormal, NULL);
					vTaskDelete(NULL);  // 任务自身删除
					break;
				}
		
				case 2:
				{
					g_level=2;
					
					xTaskCreate(game1_task, "GameTask", 128, NULL, osPriorityNormal, NULL);
					vTaskDelete(NULL);  // 任务自身删除
					
					break;
				}
				
				case 3:
				{
					g_level=3;
					
					xTaskCreate(game1_task, "GameTask", 128, NULL, osPriorityNormal, NULL);
					vTaskDelete(NULL);  // 任务自身删除
					
					
					break;
				}
		
				case 4:
				{
					g_level=4;
					xTaskCreate(game1_task, "GameTask", 128, NULL, osPriorityNormal, NULL);
					
					vTaskDelete(NULL);  // 任务自身删除
					break;
				}
				
				case 5:
				{
					g_level=5;
					
					xTaskCreate(game1_task, "GameTask", 128, NULL, osPriorityNormal, NULL);
					vTaskDelete(NULL);  // 任务自身删除
					
					break;
				}
				
				default:
				{
					break;
				}
			}
			
		}
		
		
		/*调节光标位置*/
		if(!k_data.A_KEY)
		{
			
			while(!k_data.A_KEY){ key_read(&k_data);};
			Cursor--;
		}
		if(!k_data.C_KEY)
		{
			
			while(!k_data.C_KEY){key_read(&k_data); };
			Cursor++;
		}
		
		if(Cursor>max) Cursor=max;
		else if(Cursor<1) Cursor=1;
		else Cursor=Cursor;
		
		switch(Cursor)
		{
			case 1:
			{
				LCD_ShowString222(140,50,20,(uint8_t*)text4,1,BLACK,DARKBLUE );
				LCD_Fill(140,90,180,110,LIGHTGRAY);
				LCD_Fill(140,130,180,150,LIGHTGRAY);
				LCD_Fill(140,170,180,190,LIGHTGRAY);
				LCD_Fill(140,210,180,230,LIGHTGRAY);
				
				break;
			}
		
			case 2:
			{
				LCD_ShowString222(140,90,20,(uint8_t*)text4,1,BLACK,DARKBLUE );
				LCD_Fill(140,50,180,70,LIGHTGRAY);
				LCD_Fill(140,130,180,150,LIGHTGRAY);
				LCD_Fill(140,170,180,190,LIGHTGRAY);
				LCD_Fill(140,210,180,230,LIGHTGRAY);
				
				break;
			}
			
			case 3:
			{
				LCD_ShowString222(140,130,20,(uint8_t*)text4,1,BLACK,DARKBLUE );
				LCD_Fill(140,50,180,70,LIGHTGRAY);
				LCD_Fill(140,90,180,110,LIGHTGRAY);
				LCD_Fill(140,170,180,190,LIGHTGRAY);
				LCD_Fill(140,210,180,230,LIGHTGRAY);
				
				break;
			}	
			
			case 4:
			{
				LCD_ShowString222(140,170,20,(uint8_t*)text4,1,BLACK,DARKBLUE );
				LCD_Fill(140,50,180,70,LIGHTGRAY);
				LCD_Fill(140,90,180,110,LIGHTGRAY);
				LCD_Fill(140,130,180,150,LIGHTGRAY);
				LCD_Fill(140,210,180,230,LIGHTGRAY);
				
				break;
			}
			
			case 5:
			{
				LCD_ShowString222(140,210,20,(uint8_t*)text4,1,BLACK,DARKBLUE );
				LCD_Fill(140,50,180,70,LIGHTGRAY);
				LCD_Fill(140,90,180,110,LIGHTGRAY);
				LCD_Fill(140,130,180,150,LIGHTGRAY);
				LCD_Fill(140,170,180,190,LIGHTGRAY);
				
				break;
			}			
			default:
			{
				break;
			}
		
		}
		
		
		
		LCD_ShowNum(0,0,Cursor,3,20);
		
	}

}

void game_menu(void)
{

	
}

void data_menu(void)
{
//	extern const unsigned char gImage_map1[307200];
//	Gui_Drawbmp16(0,0,gImage_map1,480,320);
	LCD_Clear(WHITE);
	uint8_t BUF[5];
	
	while(1)
	{
	W25Q64_Read(4096,BUF,5);
	LCD_ShowNum(0,0,(uint32_t)BUF[0],3,20);
	LCD_ShowNum(0,40,(uint32_t)BUF[1],3,20);
	LCD_ShowNum(0,80,(uint32_t)BUF[2],3,20);
	LCD_ShowNum(0,120,(uint32_t)BUF[3],3,20);
	LCD_ShowNum(0,160,(uint32_t)BUF[4],3,20);
	}
}


void menu_task(void *params)
{
	
	extern const unsigned char gImage_map1[307200];
	Gui_Drawbmp16(0,0,gImage_map1,480,320);
	
	
	
	/*创建结构体数组存储菜单相关变量*/	
	struct option_class option1[]={
		
		{"P L A Y",level_menu},
		{"P O I N T",data_menu},
		{".."}	
	};	
	
	main_menu(option1);

}

