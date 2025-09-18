#ifndef __GAME1_H
#define __GAME1_H

#include "bsp_system.h"
#include "cmsis_os.h"
#include "FreeRTOS.h"                   // ARM.FreeRTOS::RTOS:Core
#include "task.h"                       // ARM.FreeRTOS::RTOS:Core
#include "event_groups.h"               // ARM.FreeRTOS::RTOS:Event Groups
#include "semphr.h"                     // ARM.FreeRTOS::RTOS:Core
#include "queue.h"

extern uint8_t duilie_flag;
extern uint8_t g_level;
extern uint8_t debug11;
extern struct game_point g_point;

void game1_task(void *params);


#endif
