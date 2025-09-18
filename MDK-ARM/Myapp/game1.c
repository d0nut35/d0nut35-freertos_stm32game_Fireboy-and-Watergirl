#include "game1.h"
#include "pic.h"

#define floor 200
#define left_wall 70
#define right_wall 390
#define Point_Position 175
#define Character_RIGHT 3
#define Character_LEFT -3
#define Character_NONE 0
#define ice_door 295
#define fire_door 255
#define Point_Position_low 200


uint8_t duilie_flag=0;
uint8_t g_level=0;//关卡难度选择
uint8_t debug11=0;
struct game_point g_point;/*分数*/


/*不同难度关卡所得的分数，和时间，捡宝石有关*/
struct game_point{
	
	uint8_t gp1;
	uint8_t gp2;
	uint8_t gp3;
	uint8_t gp4;
	uint8_t gp5;
};

struct point_flag{
	
	uint8_t f1;
	uint8_t f2;
	uint8_t i1;
	uint8_t i2;
};


/*x:70->390,y:200->170*/
/*角色移动位置结构体*/
struct Character_coordinates{
	
	/*fire*/
	int16_t X1_Position;
	int16_t Y1_Position;
	/*ice*/
	int16_t X2_Position;
	int16_t Y2_Position;
};

/*人物实际坐标，左上角*/
typedef	struct Character_actcoordinates{
	
	/*fire*/
	int16_t X1_ACTPosition;
	int16_t Y1_ACTPosition;
	/*ice*/
	int16_t X2_ACTPosition;
	int16_t Y2_ACTPosition;
}Character_actcoordinates;

/*钻石的横坐标*/
typedef	struct {
	
	/*fire*/
	int16_t fire_diamond;
	int16_t fire_diamond_low;
	/*ice*/
	int16_t ice_diamond;
	int16_t ice_diamond_low;
}diamond_position;



/*队列句柄*/
static QueueSetHandle_t g_xQueueSetInput; /* 输入设备的队列集 */
static QueueHandle_t g_xQueueCharacter; /* 角色队列 */
static QueueHandle_t g_xQueneJoystick; /*摇杆队列*/ 
//static QueueHandle_t g_xQueneKEY; /*按钮队列，待补充*/ 
//static QueueHandle_t g_xQueueMPU6050; /* MPU6050队列 */

/*函数声明*/
static void InputTask(void *params);


/**********************************************************************
 * 函数名称： Map_Init
 * 功能描述： 地图初始化,初始化角色位置，地图分数位置
 * 输入参数： level - 关卡(1-5),钻石位置
 * 输出参数： 无
 * 返 回 值： 无
 ***********************************************************************/
void Map_Init(uint8_t level, diamond_position *dia_data)
{
	char text[]="POINT:";
	
	switch(level)
	{
		case 1:
		{
			/*level 1绘制*/
			Gui_Drawbmp16(0,0,gImage_map1,480,320);
			LCD_ShowString(0,0,20,(uint8_t*)text,1);
			
			break;
        }
		
        case 2:
		{
			/*level 2绘制*/
			Gui_Drawbmp16(0,0,gImage_map1,480,320);
			LCD_ShowString(0,0,20,(uint8_t*)text,1);
			
			/*记录钻石位置*/
			dia_data->ice_diamond=110;
			dia_data->fire_diamond=350;
			
			break;
        }
		
		case 3:
		{

			
			/*level 3绘制*/
			Gui_Drawbmp16(0,0,gImage_map1,480,320);
			LCD_ShowString(0,0,20,(uint8_t*)text,1);
			
			/*记录钻石位置*/
			dia_data->ice_diamond = 110;
			dia_data->fire_diamond = 370;
			dia_data->fire_diamond_low = 325;
			dia_data->ice_diamond_low = 200;
			
			break;
        }
		
        case 4:
		{
			/*level 4绘制*/
			Gui_Drawbmp16(0,0,gImage_map1,480,320);
			Gui_Drawbmp16(170,230,gImage_hurt,50,10);
			LCD_ShowString(0,0,20,(uint8_t*)text,1);
			
			/*记录钻石位置*/
			dia_data->ice_diamond = 110;
			dia_data->fire_diamond = 370;
			dia_data->fire_diamond_low = 325;
			dia_data->ice_diamond_low = 235;
			
			
			break;
        }
		
		case 5:
		{
			/*level 5绘制*/
			Gui_Drawbmp16(0,0,gImage_map1,480,320);
			Gui_Drawbmp16(170,230,gImage_icepoor,50,10);
		    Gui_Drawbmp16(330,230,gImage_firepoor,50,10);
			LCD_ShowString(0,0,20,(uint8_t*)text,1);
			
			/*记录钻石位置*/
			dia_data->ice_diamond = 110;
			dia_data->fire_diamond = 370;
			dia_data->fire_diamond_low = 325;
			dia_data->ice_diamond_low = 200;
			
			break;
        }
		
		default:
        {
            break;
        }
	
	
	}
	
}

/**********************************************************************
 * 函数名称： point_Calculate
 * 功能描述： 分数计算
 * 输入参数： 关卡难度（全局变量g_level），人物实际位置，钻石位置，时间(在game_draw中定义秒数)，得分（全局变量）
 * 输出参数： 无
 * 返 回 值： 无
 ***********************************************************************/
void Point_Calculate(uint8_t level, Character_actcoordinates *person, diamond_position *dia_data, uint64_t time,struct point_flag *pf)
{
	switch(level)
	{
		case 1:
		{
			/*计算分数*/
			uint8_t p_time = (time >= 100) ? 0 : (100 - time);
			g_point.gp1 = p_time;
			
			break;
        }
		
        case 2:
		{
			/*计算时间得分*/
			uint8_t p_time = (time >= 100) ? 0 : (100 - time);
			
			
			/*绘制钻石*/
			if((person->X2_ACTPosition >= (dia_data->ice_diamond-10))&& (person->Y2_ACTPosition == (floor - 25)) && (person->X2_ACTPosition <= (dia_data->ice_diamond + 10) ) && (pf->i1 == 0))
			{
				LCD_DrawFillRectangle(dia_data->ice_diamond, Point_Position, dia_data->ice_diamond+20, Point_Position+30);
				pf->i1 = 50;
				
			}
			else
			{
				if(!(pf->i1))
				Gui_Drawbmp16(110,Point_Position,gImage_ice_point,15,15);
			}
			
			if( (person->X1_ACTPosition >= (dia_data->fire_diamond - 10))&& (person->Y1_ACTPosition == (floor - 25)) && (person->X1_ACTPosition <= (dia_data->fire_diamond + 10) ) && (pf->f1 == 0))
			{
				LCD_DrawFillRectangle(dia_data->fire_diamond, Point_Position, dia_data->fire_diamond+20, Point_Position+30);
				pf->f1 = 50;
				
			}
			else 
			{
				if(!(pf->f1))
				Gui_Drawbmp16(350,Point_Position,gImage_fire_point,15,15);
			}
			
			/*总得分*/
			g_point.gp2 = p_time + pf->f1 + pf->i1;
			
			break;
        }
		
		case 3:
		{
						/*计算时间得分*/
			uint8_t p_time = (time >= 100) ? 0 : (100 - time);
			
			
			/*绘制钻石*/
			if((person->X2_ACTPosition >= (dia_data->ice_diamond-10))&& (person->Y2_ACTPosition == (floor - 25)) && (person->X2_ACTPosition <= (dia_data->ice_diamond + 10) ) && (pf->i1 == 0))
			{
				LCD_DrawFillRectangle(dia_data->ice_diamond, Point_Position, dia_data->ice_diamond+20, Point_Position+30);
				pf->i1 = 25;
				
			}
			else
			{
				if(!(pf->i1))
				Gui_Drawbmp16(dia_data->ice_diamond,Point_Position,gImage_ice_point,15,15);
			}
			
			if((person->X2_ACTPosition >= (dia_data->ice_diamond_low-10))&& (person->Y2_ACTPosition == (floor)) && (person->X2_ACTPosition <= (dia_data->ice_diamond_low + 10) ) && (pf->i2 == 0))
			{
				LCD_DrawFillRectangle(dia_data->ice_diamond_low, Point_Position_low, dia_data->ice_diamond+20, Point_Position+30);
				pf->i2 = 25;
				
			}
			else
			{
				if(!(pf->i2))
				Gui_Drawbmp16(dia_data->ice_diamond_low,Point_Position_low,gImage_ice_point,15,15);
			}
			
			
			
			if( (person->X1_ACTPosition >= (dia_data->fire_diamond-10))&& (person->Y1_ACTPosition == (floor - 25)) && (person->X1_ACTPosition <= (dia_data->fire_diamond + 10) ) && (pf->f1 == 0))
			{
				LCD_DrawFillRectangle(dia_data->fire_diamond, Point_Position, dia_data->fire_diamond+20, Point_Position+30);
				pf->f1 = 25;
				
			}
			else 
			{
				if(!(pf->f1))
				Gui_Drawbmp16(dia_data->fire_diamond,Point_Position,gImage_fire_point,15,15);
			}
			
			if((person->X1_ACTPosition >= (dia_data->fire_diamond_low-10))&& (person->Y1_ACTPosition == (floor)) && (person->X1_ACTPosition <= (dia_data->fire_diamond_low + 10) ) && (pf->f2 == 0))
			{
				LCD_DrawFillRectangle(dia_data->fire_diamond_low, Point_Position_low, dia_data->fire_diamond_low+20, Point_Position+30);
				pf->f2 = 25;
				
			}
			else
			{
				if(!(pf->f2))
				Gui_Drawbmp16(dia_data->fire_diamond_low,Point_Position_low,gImage_fire_point,15,15);
			}
			
			/*总得分*/
			g_point.gp3 = p_time + pf->f1 + pf->i1 + pf->f2 + pf->i2;
			
			
			
			break;
        }
		
        case 4:
		{
									/*计算时间得分*/
			uint8_t p_time = (time >= 100) ? 0 : (100 - time);
			
			
			/*绘制钻石*/
			if((person->X2_ACTPosition >= (dia_data->ice_diamond-10))&& (person->Y2_ACTPosition == (floor - 25)) && (person->X2_ACTPosition <= (dia_data->ice_diamond + 10) ) && (pf->i1 == 0))
			{
				LCD_DrawFillRectangle(dia_data->ice_diamond, Point_Position, dia_data->ice_diamond+20, Point_Position+30);
				pf->i1 = 25;
				
			}
			else
			{
				if(!(pf->i1))
				Gui_Drawbmp16(dia_data->ice_diamond,Point_Position,gImage_ice_point,15,15);
			}
			
			if((person->X2_ACTPosition >= (dia_data->ice_diamond_low-10))&& (person->Y2_ACTPosition == (floor)) && (person->X2_ACTPosition <= (dia_data->ice_diamond_low + 10) ) && (pf->i2 == 0))
			{
				LCD_DrawFillRectangle(dia_data->ice_diamond_low, Point_Position_low, dia_data->ice_diamond+20, Point_Position+30);
				pf->i2 = 25;
				
			}
			else
			{
				if(!(pf->i2))
				Gui_Drawbmp16(dia_data->ice_diamond_low,Point_Position_low,gImage_ice_point,15,15);
			}
			
			
			
			if( (person->X1_ACTPosition >= (dia_data->fire_diamond-10))&& (person->Y1_ACTPosition == (floor - 25)) && (person->X1_ACTPosition <= (dia_data->fire_diamond + 10) ) && (pf->f1 == 0))
			{
				LCD_DrawFillRectangle(dia_data->fire_diamond, Point_Position, dia_data->fire_diamond+20, Point_Position+30);
				pf->f1 = 25;
				
			}
			else 
			{
				if(!(pf->f1))
				Gui_Drawbmp16(dia_data->fire_diamond,Point_Position,gImage_fire_point,15,15);
			}
			
			if((person->X1_ACTPosition >= (dia_data->fire_diamond_low-10))&& (person->Y1_ACTPosition == (floor)) && (person->X1_ACTPosition <= (dia_data->fire_diamond_low + 10) ) && (pf->f2 == 0))
			{
				LCD_DrawFillRectangle(dia_data->fire_diamond_low, Point_Position_low, dia_data->fire_diamond_low+20, Point_Position+30);
				pf->f2 = 25;
				
			}
			else
			{
				if(!(pf->f2))
				Gui_Drawbmp16(dia_data->fire_diamond_low,Point_Position_low,gImage_fire_point,15,15);
			}
			
			/*总得分*/
			g_point.gp4 = p_time + pf->f1 + pf->i1 + pf->f2 + pf->i2;
			break;
        }
		
		case 5:
		{
												/*计算时间得分*/
			uint8_t p_time = (time >= 100) ? 0 : (100 - time);
			
			
			/*绘制钻石*/
			if((person->X2_ACTPosition >= (dia_data->ice_diamond-10))&& (person->Y2_ACTPosition == (floor - 25)) && (person->X2_ACTPosition <= (dia_data->ice_diamond + 10) ) && (pf->i1 == 0))
			{
				LCD_DrawFillRectangle(dia_data->ice_diamond, Point_Position, dia_data->ice_diamond+20, Point_Position+30);
				pf->i1 = 25;
				
			}
			else
			{
				if(!(pf->i1))
				Gui_Drawbmp16(dia_data->ice_diamond,Point_Position,gImage_ice_point,15,15);
			}
			
			if((person->X2_ACTPosition >= (dia_data->ice_diamond_low-10))&& (person->Y2_ACTPosition == (floor)) && (person->X2_ACTPosition <= (dia_data->ice_diamond_low + 10) ) && (pf->i2 == 0))
			{
				LCD_DrawFillRectangle(dia_data->ice_diamond_low, Point_Position_low, dia_data->ice_diamond+20, Point_Position+30);
				pf->i2 = 25;
				
			}
			else
			{
				if(!(pf->i2))
				Gui_Drawbmp16(dia_data->ice_diamond_low,Point_Position_low,gImage_ice_point,15,15);
			}
			
			
			
			if( (person->X1_ACTPosition >= (dia_data->fire_diamond-10))&& (person->Y1_ACTPosition == (floor - 25)) && (person->X1_ACTPosition <= (dia_data->fire_diamond + 10) ) && (pf->f1 == 0))
			{
				LCD_DrawFillRectangle(dia_data->fire_diamond, Point_Position, dia_data->fire_diamond+20, Point_Position+30);
				pf->f1 = 25;
				
			}
			else 
			{
				if(!(pf->f1))
				Gui_Drawbmp16(dia_data->fire_diamond,Point_Position,gImage_fire_point,15,15);
			}
			
			if((person->X1_ACTPosition >= (dia_data->fire_diamond_low-10))&& (person->Y1_ACTPosition == (floor)) && (person->X1_ACTPosition <= (dia_data->fire_diamond_low + 10) ) && (pf->f2 == 0))
			{
				LCD_DrawFillRectangle(dia_data->fire_diamond_low, Point_Position_low, dia_data->fire_diamond_low+20, Point_Position+30);
				pf->f2 = 25;
				
			}
			else
			{
				if(!(pf->f2))
				Gui_Drawbmp16(dia_data->fire_diamond_low,Point_Position_low,gImage_fire_point,15,15);
			}
			
			/*总得分*/
			g_point.gp5 = p_time + pf->f1 + pf->i1 + pf->f2 + pf->i2;
			break;
			
        }
		
		default:
        {
            break;
        }
	
	
	}
	

}






/**********************************************************************
 * 函数名称： game1_draw
 * 功能描述： 游戏绘制
 * 输入参数： 变化位置量，实际位置，上一次的位置，关卡难度,关卡，钻石位置,分数标志位
 * 输出参数： 无
 * 返 回 值： 无
 ***********************************************************************/

void game1_draw(struct Character_coordinates *cdata, Character_actcoordinates *person, Character_actcoordinates *last_person, uint8_t level, diamond_position *dia_data, struct point_flag *pf,uint64_t time,uint64_t last_time,QueueHandle_t *g_xQueueCharacter)
{
	uint64_t dtime=0;
	
	while(1)
	{
		/*用于接收坐标变化量数据*/
		xQueueReceive(*g_xQueueCharacter,cdata,0);
		/*时间计算*/
		time = system_get_s();
		
		dtime += (time-last_time);
		last_time = time;
	
		LCD_ShowNum(60,0,g_point.gp5,3,20);
		
		/*两人走到门获胜*/
		if((person->X1_ACTPosition>=(fire_door-10))&&(person->X1_ACTPosition<=(fire_door+10))&&(person->X2_ACTPosition>=(ice_door-10))&&(person->X2_ACTPosition<=(ice_door+10)))
		{
		
			
		
			/*弹到菜单展示分数（返回or重新开始）*/	 
			break;
		
		}
	
		/*计算分数*/
		Point_Calculate(level, person, dia_data,dtime,pf);
	
		/*陷阱判断函数*/
		if(level==4)
		{
			if(((person->X1_ACTPosition >= 175)&&(person->X1_ACTPosition <= 215)&&(person->Y1_ACTPosition ==floor))||((person->X2_ACTPosition >= 175)&&(person->X2_ACTPosition <= 215)&&(person->Y2_ACTPosition ==floor)))
			{
				/*弹到菜单展示分数（返回or重新开始）*/	
				LCD_ShowNum(60,0,0,3,20);
				g_point.gp5=0;
				break;
			}
	
		}
		else if(level==5)
		{
			if(((person->X1_ACTPosition >= 175)&&(person->X1_ACTPosition <= 215)&&(person->Y1_ACTPosition ==floor))||((person->X2_ACTPosition >= 335)&&(person->X2_ACTPosition <= 375)&&(person->Y2_ACTPosition ==floor)))
			{
				/*弹到菜单展示分数（返回or重新开始）*/	
				LCD_ShowNum(60,0,0,3,20);
				g_point.gp5=0;
				break;
			}
	
		}
	
	
		/*fire*/
		uint16_t last_p1 = person->X1_ACTPosition + cdata->X1_Position;
		uint16_t fly_p1 = 0;
		/*ice*/
		uint16_t last_p2 = person->X2_ACTPosition + cdata->X2_Position;
		uint16_t fly_p2 = 0;
	
		/*数据处理计算*/
		if(cdata->Y1_Position == 3){ fly_p1 = floor - 25;}
		else{ fly_p1 = floor ;}
	
		if(cdata->Y2_Position == 3){ fly_p2 = floor - 25;}
		else{ fly_p2 = floor ;}
	
		if(last_p1 >= right_wall){last_p1 = 390;}
		else if(last_p1 <= left_wall){last_p1 = 70;}
		else{last_p1=last_p1;}
	
		if(last_p2 >= right_wall){last_p2 = 390;}
		else if(last_p2 <= left_wall){last_p2 = 70;}
		else{last_p2=last_p2;}
	
		if(fly_p1 <=175){fly_p1 = 175;}
		else{ fly_p1 =fly_p1;}
	
		if(fly_p2 <=175){fly_p2 = 175;}
		else{ fly_p2 =fly_p2;}
	
		person->X1_ACTPosition = last_p1;
		person->Y1_ACTPosition = fly_p1;
	
		person->X2_ACTPosition = last_p2;
		person->Y2_ACTPosition = fly_p2;
	
		/*绘制人物*/
		if((last_person->X1_ACTPosition != person->X1_ACTPosition )||(last_person->Y1_ACTPosition != person->Y1_ACTPosition))
		{LCD_DrawFillRectangle(last_person->X1_ACTPosition, last_person->Y1_ACTPosition, last_person->X1_ACTPosition+20, last_person->Y1_ACTPosition+30);}
	
		if((last_person->X2_ACTPosition != person->X2_ACTPosition )||(last_person->Y2_ACTPosition != person->Y2_ACTPosition))
		{LCD_DrawFillRectangle(last_person->X2_ACTPosition, last_person->Y2_ACTPosition, last_person->X2_ACTPosition+20, last_person->Y2_ACTPosition+30);}
	
		Gui_Drawbmp16(last_p1,fly_p1,gImage_fire1,20,30);/*draw fire*/
		Gui_Drawbmp16(last_p2,fly_p2,gImage_ice1,20,30);/*draw fire*/
	
		/*记录上次位置*/
		last_person->X1_ACTPosition = person->X1_ACTPosition;
		last_person->Y1_ACTPosition = person->Y1_ACTPosition;
		last_person->X2_ACTPosition = person->X2_ACTPosition;
		last_person->Y2_ACTPosition = person->Y2_ACTPosition;
	
	}
		
}




void game1_task(void *params)
{
	/* 创建队列,队列集,创建输入任务InputTask */
	g_xQueueCharacter = xQueueCreate(10, sizeof(struct Character_coordinates));
	g_xQueueSetInput =xQueueCreateSet(JOYSTICK_QUEUE_LEN + MPU6050_QUEUE_LEN);
	
	g_xQueneJoystick = GetQueueJoystick();
	//g_xQueueMPU6050 = GetQueueMPU6050();
	
	xQueueAddToSet(g_xQueneJoystick, g_xQueueSetInput);
	
	//xQueueAddToSet(g_xQueueMPU6050, g_xQueueSetInput);	
	
	/*防止未加入队列集就开始写入数据*/
	duilie_flag=1;
	
	/*创建任务*/
	//xTaskCreate(MPU6050_Task, "MPU6050Task", 128, NULL, osPriorityNormal, NULL);
	xTaskCreate(InputTask, "InputTask", 128, NULL, osPriorityNormal, NULL);
	
	
	/*钻石位置初始化*/
	diamond_position dia_data={0,0,0,0};
	
	/*地图初始化*/
	g_level=5;
	Map_Init(g_level,&dia_data);
	
	/*位置变量初始化*/
	Character_actcoordinates person={0,0,0,0};/*fire x,y ice x,y*/
	Character_actcoordinates last_person={0,0,0,0};/*用于记录上一次位置*/
	
	/*冰火人位置初始化*/
	person.X1_ACTPosition=70;
	person.X2_ACTPosition=390;
	last_person.X1_ACTPosition =70;
	last_person.X2_ACTPosition =390;
	
	/*用于存坐标变化量*/
	struct Character_coordinates cdata={0,0,0,0};
	
	/*得分标志位*/
	struct point_flag pf={0,0,0,0};
	
	uint64_t time=0;
	uint64_t last_time=0;


	/*游戏绘制*/
	game1_draw(&cdata,&person,&last_person,g_level,&dia_data,&pf,time,last_time,&g_xQueueCharacter);
		

	

}

/**********************************************************************
 * 函数名称： ProcessMPU6050Data
 * 功能描述： 读取MPU6050数据并转换为游戏控制键,写入角色队列
 * 输入参数： 无
 * 输出参数： 无
 * 返 回 值： 无
 ***********************************************************************/
//static void ProcessMPU6050Data(void)
//{
//	struct mpu6050_data mdata;
//	struct Character_coordinates idata;
//	
//	/* 读MPU6050队列 */
//	xQueueReceive(g_xQueueMPU6050, &mdata, 0);
//				
//	if(mdata.angle_x>90)
//	{
//		idata.X1_Position = Character_RIGHT;
//	}
//	
//	else if(mdata.angle_x<90)
//	{
//		idata.X1_Position = Character_LEFT;
//	
//	}
//	else
//	{
//		
//		idata.X1_Position = Character_NONE;
//	}
//	
//	if(mdata.angle_y<90)
//	{
//		idata.Y1_Position = Character_RIGHT;
//	}
//	else
//	{
//		idata.Y1_Position = 0;
//	}

//	xQueueSend(g_xQueueCharacter, &idata, 0);
//	
//}

/**********************************************************************
 * 函数名称： ProcessJoystickData
 * 功能描述： 读取摇杆数据并转换为游戏控制键,写入角色队列
 * 输入参数： 无
 * 输出参数： 无
 * 返 回 值： 无
 ***********************************************************************/
static void ProcessJoystickData(void)
{
	Joystick_Data jdata;
	struct Character_coordinates idata;
	
	/*读队列*/
	xQueueReceive(g_xQueneJoystick,&jdata,0);
	
	/*处理数据*/
	/*FIRE*/
	if(jdata.js1_x==3)
	{
		idata.X1_Position = Character_RIGHT;
	
	}
	else if(jdata.js1_x == -3)
	{
		idata.X1_Position = Character_LEFT;
	}
	else 
	{
		idata.X1_Position = Character_NONE;
	}
	
	if(jdata.js1_y==3)
	{
		idata.Y1_Position = Character_RIGHT;
	
	}
	else 
	{
		idata.Y1_Position = Character_NONE;
	}
	
	/*ICE*/
	if(jdata.js2_x==3)
	{
		idata.X2_Position = Character_RIGHT;
	
	}
	else if(jdata.js2_x == -3)
	{
		idata.X2_Position = Character_LEFT;
	}
	else 
	{
		idata.X2_Position = Character_NONE;
	}
	
	if(jdata.js2_y==3)
	{
		idata.Y2_Position = Character_RIGHT;
	
	}
	else 
	{
		idata.Y2_Position = Character_NONE;
	}
	
	/*写入队列*/
	xQueueSend(g_xQueueCharacter,&idata,0);
	//LCD_Show2Num(30,30,idata.Y1_Position,10,20);
	
}

static void InputTask(void *params)
{
	QueueSetMemberHandle_t xQueueHandle;
	
	while (1)
	{
		/* 读队列集, 得到有数据的队列句柄 */
		xQueueHandle = xQueueSelectFromSet(g_xQueueSetInput, portMAX_DELAY);
		
		if (xQueueHandle)
		{

			if (xQueueHandle == g_xQueneJoystick)
			{
				//LCD_Show2Num(100,50,Js_data.js1_x,10,20);
				ProcessJoystickData();
			}			
//			else if (xQueueHandle == g_xQueueMPU6050)
//			{
//				//LCD_Show2Num(200,200,Js_data.js1_x,10,20);
//				ProcessMPU6050Data();
//			}			
		}
		
	}
}



//static void test(void)
//{
////	  uint16_t a=0;
////	  MPU6050_Task(&a);
////	  RotaryEncoder_Test();  
////	  struct rotary_data buffer;
////	  QueueHandle_t g_xQueueRotary;
////	  g_xQueueRotary=GetQueueRotary();
//	  //????????
////	  while(1)
////	  {
////		  
////		LCD_Clear(BLACK);
////		LCD_Clear(BLUE);  
//////		LCD_Fill(10,10,30,30,BLACK);
//////		LCD_Fill(10,10,30,30,BLUE);
//////		  
//////		xQueueReceive(g_xQueueRotary,&buffer,0);
//////		LCD_ShowNum(30,70,buffer.cnt,10,20);
//////		LCD_ShowNum(30,110,buffer.speed,10,20);
//////		  LCD_ShowNum(30,110,ADC1_sampling.adc1_average_A2,10,20);
//////		  LCD_ShowNum(30,150,ADC1_sampling.adc1_average_A1,10,20);
////	  }
//	  
//	  
//	  Joystick_Data buffer;
//	  QueueHandle_t g_xQueneJoystick;
//	  g_xQueneJoystick =GetQueueJoystick();
//	  while(1)
//	  {
//		  xQueueReceive(g_xQueneJoystick,&buffer,0);
////		  sprintf(test,"-");
//		  LCD_Show2Num(30,30,Js_data.js1_x,10,20);
////		  LCD_ShowString(30,30,20,(uint8_t*)test,1);
////		  LCD_ShowNum(30,30,buffer.js1_x,10,20);
////		  LCD_ShowNum(30,70,Js_data.js1_y,10,20);
////		  LCD_ShowNum(30,110,ADC1_sampling.adc1_average_A2,10,20);
////		  LCD_ShowNum(30,150,ADC1_sampling.adc1_average_A1,10,20);
//	  }
//    //osDelay(1);
//  }
//}


