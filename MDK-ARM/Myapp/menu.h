#ifndef __MENU_H
#define __MENU_H

#include "bsp_system.h"

struct option_class{
	char Name[16];	//��ʾ�ַ���
	void(*func)(void); //����ָ��
	
};

void main_menu(void);

void game_menu(void);

void data_menu(void);

void menu_task(void *params);

void level_menu(void);
	
#endif
