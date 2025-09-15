#include "driver_key.h"


ADC1_SAMPLING ADC1_sampling;
Joystick_Data Js_data;

static QueueHandle_t g_xQueneJoystick;/*摇杆数据队列的句柄*/


QueueHandle_t GetQueueJoystick(void)
{
	return g_xQueneJoystick;
}


/*开启ADC通道，放在初始化后*/
void ADC_Start(void)
{
	/*开启接收数据的通道,后面4代表4个通道*/
	HAL_ADC_Start_DMA(&hadc1,(uint32_t*)ADC1_sampling.adc1_dma_storage,4*Filter_width);
	/*创建队列*/
	g_xQueneJoystick= xQueueCreate(JOYSTICK_QUEUE_LEN,sizeof(Joystick_Data));
}




void Joystick_Analysis(void)
{
		/*解析数据*/
		for(uint8_t i = 0; i < Filter_width; i++)
		{
		// 计算累计值
		ADC1_sampling.adc1_sum_A4 += ADC1_sampling.adc1_dma_storage[4*i];
		ADC1_sampling.adc1_sum_A3 += ADC1_sampling.adc1_dma_storage[4*i+1];
		ADC1_sampling.adc1_sum_A2 += ADC1_sampling.adc1_dma_storage[4*i+2];
		ADC1_sampling.adc1_sum_A1 += ADC1_sampling.adc1_dma_storage[4*i+3];
		}
	
		// 平均滤波
		ADC1_sampling.adc1_average_A4 = ADC1_sampling.adc1_sum_A4 / Filter_width; //* 3300.0 / 4096.0;	// mV
		ADC1_sampling.adc1_average_A3 = ADC1_sampling.adc1_sum_A3 / Filter_width; //* 3300.0 / 4096.0;	// mV
		ADC1_sampling.adc1_average_A2 = ADC1_sampling.adc1_sum_A2 / Filter_width; //* 3300.0 / 4096.0;
		ADC1_sampling.adc1_average_A1 = ADC1_sampling.adc1_sum_A1 / Filter_width; //* 3300.0 / 4096.0;
	
	
		// 累计值清零以待下次计算	
		ADC1_sampling.adc1_sum_A4 = 0;	
		ADC1_sampling.adc1_sum_A3 = 0;
		ADC1_sampling.adc1_sum_A2 = 0;
		ADC1_sampling.adc1_sum_A1 = 0;
		
		
		// 映射逻辑
		if (ADC1_sampling.adc1_average_A4 > THRESHOLD_MAX) {
			Js_data.js2_y = p_move;
		} else if (ADC1_sampling.adc1_average_A4 < THRESHOLD_DEADZONE) {
			Js_data.js2_y = n_move;
		} else {
			Js_data.js2_y = s_move;
		}

		if (ADC1_sampling.adc1_average_A3 > THRESHOLD_MAX) {
			Js_data.js2_x = p_move;
		} else if (ADC1_sampling.adc1_average_A3 < THRESHOLD_DEADZONE) {
			Js_data.js2_x = n_move;
		} else {
			Js_data.js2_x = s_move;
		}

		if (ADC1_sampling.adc1_average_A2 > THRESHOLD_MAX) {
			Js_data.js1_y = p_move;
		} else if (ADC1_sampling.adc1_average_A2 < THRESHOLD_DEADZONE) {
			Js_data.js1_y = n_move;
		} else {
			Js_data.js1_y = s_move;
		}

		if (ADC1_sampling.adc1_average_A1 > THRESHOLD_MAX) {
			Js_data.js1_x = p_move;
		} else if (ADC1_sampling.adc1_average_A1 < THRESHOLD_DEADZONE) {
			Js_data.js1_x = n_move;
		} else {
			Js_data.js1_x = s_move;
		}
		
		//写队列
		xQueueSendFromISR(g_xQueneJoystick,&Js_data,NULL);
		
		
}


void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
	if (hadc == &hadc1)
	{

		Joystick_Analysis();
		
		
    }
	
	
	
	
}


