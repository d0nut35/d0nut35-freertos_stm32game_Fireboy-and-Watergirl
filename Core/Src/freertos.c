/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "bsp_system.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
static SemaphoreHandle_t g_xI2CMutex; 
TaskHandle_t game1TaskHandle = NULL;
TaskHandle_t menuTaskHandle = NULL;
uint8_t light=1;
uint8_t led111=1;

/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
void GetI2C(void)
{
	xSemaphoreTake(g_xI2CMutex,portMAX_DELAY);

}

void PutI2C(void)
{
	xSemaphoreGive(g_xI2CMutex);

}




/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
	HAL_TIM_PWM_Start(&htim12,TIM_CHANNEL_1);//启用定时器通道
	//HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_1);//启用定时器通道
	g_xI2CMutex = xSemaphoreCreateMutex();//i2c����������
	
	LCD_Init();
	extern void LCD_LIGHT(uint16_t num);
	LCD_LIGHT(400);
	ADC_Start();//��ʼ����ҡ������
	//RotaryEncoder_Init();//��ת��������ʼ��
	MPU6050_Init();
	
	
  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
	
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
   xTaskCreate(menu_task, "MenuTask", 128, NULL, osPriorityNormal, &menuTaskHandle);
  //xTaskCreate(game1_task, "GameTask", 128, NULL, osPriorityNormal, NULL);
  //xTaskCreate(MPU6050_Task, "GameTask", 128, NULL, osPriorityNormal, NULL);
  
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
	  while(1)
	  {	 
		KEY_Data k_data1;
		key_read(&k_data1);
		if(k_data1.D_KEY==0)
		{
			vTaskDelay(50);
			if(k_data1.D_KEY==0)
			{
				while(!k_data1.D_KEY){key_read(&k_data1); };
				led111^=1;
			}
		
		}
		  
		light=HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_5);

		
		
		if(!led111)
		{
			LCD_LED_CLR;
		
		}
		
		else if(led111)
		{
		if(light)
		{
			LCD_LIGHT(400);
		}
		else
		{
			LCD_LIGHT(150);
		}
	}
	  }
	  //music1();
	  //W25Q64_Erase(4096,4096);
	  //W25Q64_Test();
	  /*播放音乐，调节声音*/
	  
  }
  /* USER CODE END StartDefaultTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

