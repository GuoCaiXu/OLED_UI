# include "./setting/setting.h"
# include "./menu/menu.h"

static Option_Class Option_SettingMenu[] = {
    {"<<<", NULL},
    {"动画速度[中]", Setting_AnimationSpeed},
    {"..", NULL},
    {"\0"}
};

void MENU_OptionSettingMenu(void){

	MENU_RunMain(Option_SettingMenu);
}

void Setting_AnimationSpeed(void){

    static uint8_t speed_judge = 1;
    speed_judge ++;
    speed_judge %= 3;
    if (speed_judge == 0){

        Option_SettingMenu[1].str = "动画速度[慢]";
        Menu_Global.step = 1;
        Menu_Global.slow_cnt = 5;
    }
    else if (speed_judge == 1){

        Option_SettingMenu[1].str = "动画速度[中]";
        Menu_Global.step = 2;
        Menu_Global.slow_cnt = 5;
    }
    else if (speed_judge == 2){

        Option_SettingMenu[1].str = "动画速度[快]";
        Menu_Global.step = 3;
        Menu_Global.slow_cnt = 5;
    }
}
