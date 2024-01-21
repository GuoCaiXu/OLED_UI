/*
 * @Author: xgc030920@outlook.com
 * @Date: 2024-01-18 16:06:06
 * @LastEditors: xgc030920@outlook.com
 * @LastEditTime: 2024-01-19 20:22:38
 * @FilePath: \Project_EIDEc:\SyncFile\03-Project\05-OLED_UI\02-江科大\V1.1\Hardware\ui\ui.c
 * @Description: 
 * 
 * Copyright (c) 2024 by ${git_name_email}, All Rights Reserved. 
 */
# include "./ui/ui.h"
# include <stdlib.h>
# include <math.h>
# include "./key/bsp_key.h"

extern Keys key[2];

int list_len;

// 字符
short x;			// x当前位置数值	
short y = 0, y_trg = 0;

// 字体高度
uint8_t font_Hight = 16;
uint8_t font_Width = 8;

// 框框
short frame_len = 0, frame_len_trg = 0;			// 框框的宽度
short frame_y = 0, frame_y_trg = 0;				// 框框的高

int8_t ui_select = 0;

typedef struct{
	char *str;
    uint8_t len;
}SETTING_LIST;

SETTING_LIST list[] = 
{
	{"Type", 4},
	{"Value", 5},
	{"Yaw", 3},
	{"Time", 4},
	{"Reduct", 6},
	{"Set", 3},
	{"List_1", 6},
	{"List_2", 6},
	{"List_3", 6}
};

void UI_Init(void)
{
    OLED_Init();
}

/*
	函数作用: 使ui动起来
	变量:	a : 		变量的现坐标
			a_trg:		变量坐标的目标值
			step:		目标每次增加的值
			slow_cnt:	设置限制快到目标值就缓慢增加
*/
uint8_t ui_run(short *a, short *a_trg, uint8_t step, uint8_t slow_cnt){

	uint8_t temp;

	temp = (abs(*a_trg - *a ))> slow_cnt ? step : 1;

	if (*a < *a_trg){
		
		*a += temp;
	}
	else if (*a > *a_trg){

		*a -= temp;
	}
	else {

		return 0;
	}

	return 1;
}

void ui_show(void){

	list_len = sizeof(list)/sizeof(SETTING_LIST);

	OLED_Clear();
	for (uint8_t i = 0; i < list_len; i ++){						// 显示list结构体的所以字符

		OLED_ShowString(x+1, y+i*(font_Hight), list[i].str, OLED_8X16 );				// 显示字符	x表示字符从x+2开始， y表示从y+i*20开始
	}
    OLED_ReverseArea(x, frame_y, frame_len, font_Hight+1);
    ui_run(&y, &y_trg, 1, 5);
	ui_run(&frame_y, &frame_y_trg, 1, 5);							// 框框的y值的ui
	ui_run(&frame_len, &frame_len_trg, 1, 5);
	OLED_Update();
}

void ui_porc(void){

	if (key[0].single_flag == 1){

        
        key[0].single_flag = 0;
    }

    if (key[0].long_flag == 1){
        ui_select ++;
		frame_y_trg += (font_Hight);
		
		if (ui_select >= list_len){
			ui_select = list_len - 1;
			frame_y_trg -= (font_Hight);
		}
		if ((ui_select > 2) && (frame_y_trg > (font_Hight*3))){
			y_trg -= (font_Hight);
			frame_y_trg -= (font_Hight);
		}
        key[0].long_flag = 0;
    }

    if (key[1].single_flag == 1){
		
		
		key[1].single_flag = 0; 
    }

    if (key[1].long_flag == 1){
        ui_select --;
		frame_y_trg -= (font_Hight);
		if (ui_select < 0){
			ui_select = 0;
			frame_y_trg += (font_Hight);
		}
		if (frame_y_trg < 0){
			y_trg += (font_Hight);
			frame_y_trg += (font_Hight);
		}
		key[1].long_flag = 0;  
    }
	frame_len_trg = list[ui_select].len*font_Width+2;
	ui_show();
}
