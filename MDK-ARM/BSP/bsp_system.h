#ifndef __BSP_SYSTEM_H
#define __BSP_SYSTEM_H

#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "math.h"
#include "stdint.h"

#include "main.h"
#include "cmsis_os.h"
#include "spi.h"
#include "gpio.h"
#include "dma.h"
#include "adc.h"
#include "tim.h"
#include "i2c.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "task.h"                      
#include "event_groups.h"               
#include "semphr.h"

#include "driver_timer.h"
#include "gui.h" 
#include "lcd.h"
#include "driver_key.h"
#include "driver_mpu6050.h"
#include "driver_rotary_encoder.h"

#include "game1.h"
#include "menu.h"
#include "Music.h"

extern TaskHandle_t game1TaskHandle ;
extern TaskHandle_t menuTaskHandle ;


#endif

