# include "./setting/setting.h"
# include "./menu/menu.h"

uint8_t inverted_flag = 0;
bool night_mode_flag = 0;

static Option_Class Option_SettingMenu[] = {
    {"<<<", NULL},
    {"动画速度[中]", Setting_AnimationSpeed},
    {"下标[反相]", Setting_Inverted},
    {"夜间模式[*]", Setting_NightMode},
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

uint8_t Read_InvertedFlag(void){

    return inverted_flag;
}

void Setting_Inverted(void){

    inverted_flag ++;
    inverted_flag %= 3;
    if (inverted_flag == 0){
        Option_SettingMenu[2].str = "下标[反相]";
    }
    else if (inverted_flag == 1){
        Option_SettingMenu[2].str = "下标[框框]";
    }
    else if (inverted_flag == 2){
        Option_SettingMenu[2].str = "下标[箭头]";
    }
}

bool Read_NightMode(void){

    return night_mode_flag;
}

void Setting_NightMode(void){

    night_mode_flag ^= 1;
    if (night_mode_flag == 0 ){
        Option_SettingMenu[3].str = "夜间模式[*]";
    }
    else if (night_mode_flag == 1 ){
        Option_SettingMenu[3].str = "夜间模式[ ]";
    }
}
