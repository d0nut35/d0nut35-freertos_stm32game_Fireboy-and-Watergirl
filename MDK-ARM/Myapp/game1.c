#include "game1.h"
#include "pic.h"

#define floor 200
#define left_wall 70
#define right_wall 390
#define Point_Position 175

/*x:70->390,y:200->170，角色位置结构体*/
struct Character_coordinates{
	
	/*fire*/
	uint16_t X1_Position;
	uint16_t Y1_Position;
	/*ice*/
	uint16_t X2_Position;
	uint16_t Y2_Position;
};

/*队列句柄*/
static QueueSetHandle_t g_xQueueSetInput; /* 输入设备的队列集 */
static QueueHandle_t g_xQueueCharacter; /* 角色队列 */
static QueueHandle_t g_xQueneJoystick; /*摇杆队列*/ 
//static QueueHandle_t g_xQueneKEY; /*按钮队列，待补充*/ 
static QueueHandle_t g_xQueueMPU6050; /* MPU6050队列 */

/*函数声明*/
static void InputTask(void *params);


/**********************************************************************
 * 函数名称： Map_Init
 * 功能描述： 地图初始化
 * 输入参数： num - 关卡(1-5)
 * 输出参数： 无
 * 返 回 值： 无
 ***********************************************************************/
void Map_Init(uint8_t num)
{
	switch(num)
	{
		
	
	
	}
	
}






void game1_task(void *params)
{
	/* 创建队列,队列集,创建输入任务InputTask */
	g_xQueueCharacter = xQueueCreate(10, sizeof(struct Character_coordinates));
	g_xQueueSetInput =xQueueCreateSet(JOYSTICK_QUEUE_LEN + MPU6050_QUEUE_LEN);
	
	g_xQueneJoystick = GetQueueRotary();
	g_xQueueMPU6050 = GetQueueMPU6050();
	
	xQueueAddToSet(g_xQueneJoystick, g_xQueueSetInput);
	xQueueAddToSet(g_xQueueMPU6050, g_xQueueSetInput);	
	
	 xTaskCreate(MPU6050_Task, "MPU6050Task", 128, NULL, osPriorityNormal, NULL);
	 xTaskCreate(InputTask, "InputTask", 128, NULL, osPriorityNormal, NULL);
//	Gui_Drawbmp16(0,0,gImage_map1,480,320);
//	Gui_Drawbmp16(70,floor-30,gImage_fire1,20,30);
//	Gui_Drawbmp16(390,floor,gImage_ice1,20,30);
//	Gui_Drawbmp16(110,Point_Position,gImage_ice_point,15,15);
//	Gui_Drawbmp16(390,Point_Position,gImage_fire_point,15,15);
	
	while(1)
	{
	
	
	}
	
	
	


}

/**********************************************************************
 * 函数名称： ProcessMPU6050Data
 * 功能描述： 读取MPU6050数据并转换为游戏控制键,写入角色队列
 * 输入参数： 无
 * 输出参数： 无
 * 返 回 值： 无
 * 修改日期：      版本号     修改人	      修改内容
 * -----------------------------------------------
 * 2023/09/02	     V1.0	  韦东山	      创建
 ***********************************************************************/
static void ProcessMPU6050Data(void)
{
	


}
/**********************************************************************
 * 函数名称： ProcessJoystickData
 * 功能描述： 读取摇杆数据并转换为游戏控制键,写入角色队列
 * 输入参数： 无
 * 输出参数： 无
 * 返 回 值： 无
 * 修改日期：      版本号     修改人	      修改内容
 * -----------------------------------------------
 * 2023/09/02	     V1.0	  韦东山	      创建
 ***********************************************************************/
static void ProcessJoystickData(void)
{
	

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
				ProcessJoystickData();
			}			
			else if (xQueueHandle == g_xQueueMPU6050)
			{
				ProcessMPU6050Data();
			}			
		}
	}
}



static void test(void)
{
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
}


