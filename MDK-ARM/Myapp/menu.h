#ifndef __MENU_H
#define __MENU_H

#include "bsp_system.h"

struct option_class{
	
	char Name[16];	//ÏÔÊ¾×Ö·û´®
	void(*func)(void); //º¯ÊýÖ¸Õë
	
};

void main_menu(struct option_class *option1);

void game_menu(void);

void data_menu(void);

void menu_task(void *params);

void level_menu(void);
	
void LCD_LIGHT(uint16_t num);

void LCD_ShowString222(uint16_t x,uint16_t y,uint8_t size,uint8_t *p,uint8_t mode,uint16_t BACK,uint16_t point);

#endif
