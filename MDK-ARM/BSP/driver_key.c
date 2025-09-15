#include "driver_key.h"


ADC1_SAMPLING ADC1_sampling;
Joystick_Data Js_data;

static QueueHandle_t g_xQueneJoystick;/*ҡ�����ݶ��еľ��*/


QueueHandle_t GetQueueJoystick(void)
{
	return g_xQueneJoystick;
}


/*����ADCͨ�������ڳ�ʼ����*/
void ADC_Start(void)
{
	/*�����������ݵ�ͨ��,����4����4��ͨ��*/
	HAL_ADC_Start_DMA(&hadc1,(uint32_t*)ADC1_sampling.adc1_dma_storage,4*Filter_width);
	/*��������*/
	g_xQueneJoystick= xQueueCreate(JOYSTICK_QUEUE_LEN,sizeof(Joystick_Data));
}




void Joystick_Analysis(void)
{
		/*��������*/
		for(uint8_t i = 0; i < Filter_width; i++)
		{
		// �����ۼ�ֵ
		ADC1_sampling.adc1_sum_A4 += ADC1_sampling.adc1_dma_storage[4*i];
		ADC1_sampling.adc1_sum_A3 += ADC1_sampling.adc1_dma_storage[4*i+1];
		ADC1_sampling.adc1_sum_A2 += ADC1_sampling.adc1_dma_storage[4*i+2];
		ADC1_sampling.adc1_sum_A1 += ADC1_sampling.adc1_dma_storage[4*i+3];
		}
	
		// ƽ���˲�
		ADC1_sampling.adc1_average_A4 = ADC1_sampling.adc1_sum_A4 / Filter_width; //* 3300.0 / 4096.0;	// mV
		ADC1_sampling.adc1_average_A3 = ADC1_sampling.adc1_sum_A3 / Filter_width; //* 3300.0 / 4096.0;	// mV
		ADC1_sampling.adc1_average_A2 = ADC1_sampling.adc1_sum_A2 / Filter_width; //* 3300.0 / 4096.0;
		ADC1_sampling.adc1_average_A1 = ADC1_sampling.adc1_sum_A1 / Filter_width; //* 3300.0 / 4096.0;
	
	
		// �ۼ�ֵ�����Դ��´μ���	
		ADC1_sampling.adc1_sum_A4 = 0;	
		ADC1_sampling.adc1_sum_A3 = 0;
		ADC1_sampling.adc1_sum_A2 = 0;
		ADC1_sampling.adc1_sum_A1 = 0;
		
		
		// ӳ���߼�
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
		
		//д����
		xQueueSendFromISR(g_xQueneJoystick,&Js_data,NULL);
		
		
}


void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
	if (hadc == &hadc1)
	{

		Joystick_Analysis();
		
		
    }
	
	
	
	
}


