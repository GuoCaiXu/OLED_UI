# include "./Tools/tools.h"

void MENU_OptionToolsMenu(void){

	static Option_Class Option_ToolsMenu[] = {
		{"<<<"},
		{"PWM输出比较", Tools_OptionPWMOut_MENU, NULL},
		{"PWM输入捕获", Tools_OptionPWMInput_MENU},
		{"检测电压(ADC)"},
		{"串口播放视频", Tools_OptionUSART_MENU},
		{".."},
		{"\0"}
	};

	MENU_RunMain(Option_ToolsMenu, NULL);
}

void Tools_Porc(void){

    // Tools_PWMOut_porc();
    // Tools_EnterCapture();
}
