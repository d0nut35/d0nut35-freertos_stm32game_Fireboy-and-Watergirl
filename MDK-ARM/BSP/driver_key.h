#ifndef __DRIVER_KEY_H
#define __DRIVER_KEY_H

#include "bsp_system.h"




#define Filter_width	10		// �˲����
#define Channel_num		4		// ͨ����
#define JOYSTICK_QUEUE_LEN 10

// ������ֵ��Χ
#define THRESHOLD_DEADZONE  1000  //����1000��Ϊ-3
#define THRESHOLD_MAX       3000 // ����3000��Ϊ3

#define p_move 3  //�����ƶ���ֵ
#define n_move -3 //�����ƶ���ֵ	
#define s_move 0  //��ֹ	

typedef struct{
	uint8_t adc_count;
	uint16_t adc1_dma_storage[4 * Filter_width];
	uint32_t adc1_sum_A1, adc1_sum_A2, adc1_sum_A3,adc1_sum_A4;
	uint16_t adc1_average_A1, adc1_average_A2, adc1_average_A3,adc1_average_A4;
	uint32_t time;
}ADC1_SAMPLING;

/*ҡ�� 1-FIRE 2-ICE*/
typedef struct{
	int8_t js1_x;
	int8_t js1_y;
	int8_t js2_x;
	int8_t js2_y;

}Joystick_Data;



extern ADC1_SAMPLING ADC1_sampling;
extern Joystick_Data Js_data;

void ADC_Start(void);
QueueHandle_t GetQueueJoystick(void);

#endif
