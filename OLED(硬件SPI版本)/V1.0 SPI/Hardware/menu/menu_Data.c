# include "./menu/menu.h"

void MENU_OptionStartMenu(void){

    static Option_Class Option_StartMenu[] = {
		{"<<<", NULL},
		{"Tools",MENU_OptionToolsMenu},
		{"Setting", MENU_OptionSettingMenu},
		{"Information", MENU_OptionInformationMenu},
		{"..", NULL},
		{"\0"}
	};

	MENU_RunMain(Option_StartMenu, NULL);
}

void MENU_OptionInformationMenu(void){

	OLED_Clear();
	OLED_ShowImage(70, 5, 40, 40, Diode);
	Menu_ShowString(0, 0, "Menu:V1.0", OLED_6X8);
	Menu_ShowString(0, 48, "up:讨厌下雨天", OLED_8X16);
	if (Read_NightMode()) OLED_Reverse();
	OLED_Update();

	while(1){
		if (Key2_signal_func() || Key1_signal_func()){
			return;
		}
	}
}
