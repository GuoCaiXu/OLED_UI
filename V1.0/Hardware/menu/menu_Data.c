# include "./menu/menu.h"

void MENU_OptionStartMenu(void){

    static Option_Class Option_StartMenu[] = {
		{"<<<", NULL},
		{"Tools",MENU_OptionToolsMenu},
		{"Setting", MENU_OptionSettingMenu},
		{"Information", MENU_OptionInformationMenu},
		{"..", NULL, 0},
		{"\0"}
	};

	MENU_RunMain(Option_StartMenu);
}

void MENU_OptionToolsMenu(void){

	static Option_Class Option_ToolsMenu[] = {
		{"<<<"},
		{"PWM"},
		{"ADC检测电压"},
		{".."},
		{"\0"}
	};

	MENU_RunMain(Option_ToolsMenu);
}

void MENU_OptionInformationMenu(void){

	static Option_Class Option_InformationMenu[] = {
		{"Menu V1.0"},
		{"up:讨厌下雨天"},
		{"\0"}
	};

	MENU_RunMain(Option_InformationMenu);
}
