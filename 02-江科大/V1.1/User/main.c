/*
 * @Author: xgc030920@outlook.com
 * @Date: 2024-01-18 15:04:43
 * @LastEditors: xgc030920@outlook.com
 * @LastEditTime: 2024-01-18 17:00:03
 * @FilePath: \Project_EIDEc:\SyncFile\03-Project\05-OLED_UI\02-江科大\V1.0\User\main.c
 * @Description: 
 * 
 * Copyright (c) 2024 by ${git_name_email}, All Rights Reserved. 
 */
# include "main.h"


int main(void){

	Key_Init();
	UI_Init();
	TIM2_Init(720-1, 1000-1);
	while(1){
	
		ui_porc();
	}
}
