#ifndef __DRIVER_KEY_H
#define __DRIVER_KEY_H

#include "bsp_system.h"




#define Filter_width	10		// 滤波宽度
#define Channel_num		4		// 通道数
#define JOYSTICK_QUEUE_LEN 10

// 定义阈值范围
#define THRESHOLD_DEADZONE  1000  //低于1000则为-3
#define THRESHOLD_MAX       3000 // 超过3000则为3

#define p_move 3  //正向移动的值
#define n_move -3 //负向移动的值	
#define s_move 0  //静止	

typedef struct{
	uint8_t adc_count;
	uint16_t adc1_dma_storage[4 * Filter_width];
	uint32_t adc1_sum_A1, adc1_sum_A2, adc1_sum_A3,adc1_sum_A4;
	uint16_t adc1_average_A1, adc1_average_A2, adc1_average_A3,adc1_average_A4;
	uint32_t time;
}ADC1_SAMPLING;

/*摇杆 1-FIRE 2-ICE*/
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
