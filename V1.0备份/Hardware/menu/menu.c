# include "./menu/menu.h"

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

void MENU_RunMain(Option_Class *Option_List){

	int8_t list_len = 0;
	int8_t list_select = 1;							// 菜单选择下标
	// 字符
    int8_t x = 0;			                    	// x当前位置数值	
    int8_t y_trg = 0;                   	// y当前位置数值
	// 框框
    int8_t frame_len_trg = 0;		// 框框的宽度
    int8_t frame_y_trg = 16;			// 框框的高

	if (Option_List[list_select].Init_func){
		Option_List[list_select].Init_func();
	}

	while(1){

		if (Option_List[list_select].porc_func){
			Option_List[list_select].porc_func();
		}

		if (Key1_signal_func()){
			if (Option_List[list_select].func){
				Option_List[list_select].func();
				if ((Menu_Global.y == y_trg) && (Menu_Global.frame_y == frame_y_trg)){
					Menu_Global.frame_y = 0;
				}
			}
		}
		if (Key2_signal_func()){
			return;
		}

		list_len = Menu_stuctlen(Option_List);
		if (Key1_long_func()){
			list_select ++;
			frame_y_trg += Menu_Global.font_Hight;
			if (list_select >= list_len) {
				list_select = list_len-1;
				frame_y_trg -= (Menu_Global.font_Hight);
			}
			if (frame_y_trg > (Menu_Global.font_Hight*3)){
				y_trg -= (Menu_Global.font_Hight);
				frame_y_trg -= (Menu_Global.font_Hight);
			}
		}
		if (Key2_long_func()){
			list_select --;
			frame_y_trg -= Menu_Global.font_Hight;
			if (list_select < 0) {
				list_select = 0;
				frame_y_trg += Menu_Global.font_Hight;
			}
			if (frame_y_trg < 0) {
				y_trg += Menu_Global.font_Hight;
				frame_y_trg += Menu_Global.font_Hight;
			}
		}
		frame_len_trg = Menu_strlen(Option_List[list_select].str)*Menu_Global.font_Width+2;
		OLED_Clear();
		for (uint8_t i = 0; i < list_len; i ++){						// 显示list结构体的所以字符
			Menu_ShowString(x+1, Menu_Global.y+i*(Menu_Global.font_Hight), Option_List[i].str, OLED_8X16);
		}
		OLED_ReverseArea(x, Menu_Global.frame_y, Menu_Global.frame_len, Menu_Global.font_Hight+1);
		ui_run(&Menu_Global.y, &y_trg, Menu_Global.step, Menu_Global.slow_cnt);
		ui_run(&Menu_Global.frame_y, &frame_y_trg, Menu_Global.step, Menu_Global.slow_cnt);							// 框框的y值的ui
		ui_run(&Menu_Global.frame_len, &frame_len_trg, Menu_Global.step*3, Menu_Global.slow_cnt);
		OLED_Update();
	}
}

