# include "./menu/menu.h"
# include "./encoder/Encoder.h"

MenuProperty	Menu_Global = {
	// 字体高宽
	.font_Hight = 16,
	.font_Width = 8,
	// 动画速度系数
	.step = 2,
	.slow_cnt = 5,

	.y = 16,
	.frame_y = 16,
	.frame_len = 0
};

int8_t Key_EncoderGetValue(void){

	if (Key1_long_func()){
		return 1;
	}
	else if (Key2_long_func()){
		return -1;
	}

	return Encoder_Get();
}

void MENU_RunMain(Option_Class *Option_List, void (*func_porc)(void)){

	int8_t list_len = 0;
	int8_t list_select = 1;							// 菜单选择下标
	// 字符
    int8_t x = 0;			                    	// x当前位置数值	
    int8_t y_trg = 0;                   	// y当前位置数值
	// 框框
    int8_t frame_len_trg = 0;		// 框框的宽度
    int8_t frame_y_trg = 16;			// 框框的高

	while(1){

		int8_t key_encoder = 0;
		
		if (func_porc){
			func_porc();
		}
		// 界面函数执行
		if (Key1_signal_func()){
			if (Option_List[list_select].func){
				Option_List[list_select].func();
			}
		}
		if (Key2_signal_func()){
			return;
		}
		list_len = Menu_stuctlen(Option_List);

		// 编码器+按键判断
		key_encoder = Key_EncoderGetValue();
		while(key_encoder != 0){
			if (key_encoder > 0){
				list_select ++;
				frame_y_trg += Menu_Global.font_Hight;
				key_encoder --;
			}
			else if (key_encoder < 0){

				list_select --;
				frame_y_trg -= Menu_Global.font_Hight;
				key_encoder ++;
			}
			if (list_select >= list_len) {
				list_select = list_len-1;
				frame_y_trg -= (Menu_Global.font_Hight);
			}
			else if (list_select < 0) {
				list_select = 0;
				frame_y_trg += Menu_Global.font_Hight;
			}
			if (frame_y_trg > (Menu_Global.font_Hight*3)){
				y_trg -= (Menu_Global.font_Hight);
				frame_y_trg -= (Menu_Global.font_Hight);
			}
			else if (frame_y_trg < 0) {
				y_trg += Menu_Global.font_Hight;
				frame_y_trg += Menu_Global.font_Hight;
			}
		}
		frame_len_trg = Menu_strlen(Option_List[list_select].str, Option_List[list_select].Variables)*Menu_Global.font_Width+2;
		OLED_Clear();
		if (Read_InvertedFlag() == 2) Menu_ShowString(Menu_Global.frame_len+4, Menu_Global.frame_y, "<-", OLED_8X16);
		for (uint8_t i = 0; i < list_len; i ++){						// 显示list结构体的所以字符
			OLED_Printf(x+1, Menu_Global.y+i*(Menu_Global.font_Hight), OLED_8X16, Option_List[i].str, Option_List[i].Variables);
		}
		
		if (Read_InvertedFlag() == 0) OLED_ReverseArea(x, Menu_Global.frame_y, Menu_Global.frame_len, Menu_Global.font_Hight);
		else if (Read_InvertedFlag() == 1) OLED_DrawRectangle(x, Menu_Global.frame_y, Menu_Global.frame_len, Menu_Global.font_Hight, OLED_UNFILLED);
		ui_run(&Menu_Global.y, &y_trg, Menu_Global.step, Menu_Global.slow_cnt);
		ui_run(&Menu_Global.frame_y, &frame_y_trg, Menu_Global.step, Menu_Global.slow_cnt);							// 框框的y值的ui
		ui_run(&Menu_Global.frame_len, &frame_len_trg, Menu_Global.step*3, Menu_Global.slow_cnt);
		if (Read_NightMode()) OLED_Reverse();
		OLED_Update();
	}
}

