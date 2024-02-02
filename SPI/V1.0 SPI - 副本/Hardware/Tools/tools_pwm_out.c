# include "./Tools/tools.h"

Option_Class Option_ToolsPWMOUTMenu[] = {
    {"<<<", NULL},
    {"PWM输出[关]", Tools_PWM_Switch},
    {"..", NULL},
    {"\0"},
    {"\0"},
    {"\0"},
    {"\0"},
    {"..", NULL},
    {"\0"}
};

bool pwm_switch = 0;
int32_t pwm_out_PSC = 72;
int32_t pwm_out_ARR = 1000;
int32_t pwm_out_duty = 10;

void Tools_OptionPWMOut_MENU(void){

    MENU_RunMain(Option_ToolsPWMOUTMenu);
}

void Tools_PWM_Switch(void){

    pwm_switch ^= 1;

    if (pwm_switch == 0){
        Option_ToolsPWMOUTMenu[1].str = "PWM输出[关]";
        Option_ToolsPWMOUTMenu[2].str = "..";
        Option_ToolsPWMOUTMenu[2].Variables = NULL;
        Option_ToolsPWMOUTMenu[2].func = NULL;
        for (uint8_t i = 3; i < 7; i ++){
            Option_ToolsPWMOUTMenu[i].str = "\0";
            Option_ToolsPWMOUTMenu[i].Variables = NULL;
            Option_ToolsPWMOUTMenu[i].func = NULL;
        }
        TIM_Cmd(TIM1, DISABLE);
    }
    else if (pwm_switch == 1){
        Option_ToolsPWMOUTMenu[1].str = "PWM输出[开]";
        Option_ToolsPWMOUTMenu[2].str = "频率: %d hz";
        Option_ToolsPWMOUTMenu[2].Variables = 72000000/pwm_out_PSC/pwm_out_ARR;
        Option_ToolsPWMOUTMenu[3].str = "PSC: %d";
        Option_ToolsPWMOUTMenu[3].Variables = pwm_out_PSC;
        Option_ToolsPWMOUTMenu[3].func = Tools_PWM_SetOutputPSCuency;
        Option_ToolsPWMOUTMenu[4].str = "ARR: %d";
        Option_ToolsPWMOUTMenu[4].Variables = pwm_out_ARR;
        Option_ToolsPWMOUTMenu[4].func = Tools_PWM_SetOutputARRuency;
        Option_ToolsPWMOUTMenu[5].str = "占空比: %d";
        Option_ToolsPWMOUTMenu[5].Variables = pwm_out_duty;
        Option_ToolsPWMOUTMenu[5].func = Tools_PWM_SetOutputDutyuency;
        Option_ToolsPWMOUTMenu[6].str = "输出电平:高电平";
        Option_ToolsPWMOUTMenu[6].func = Tools_PWM_SetOutputPolarity;
        TIM_PrescalerConfig(TIM1, pwm_out_PSC-1, TIM_PSCReloadMode_Update);
        TIM_SetAutoreload(TIM1, pwm_out_ARR-1);
        TIM_SetCompare1(TIM1, ((pwm_out_duty-1) < 0)?0:pwm_out_duty-1);
        TIM_Cmd(TIM1, ENABLE);
    }
}

void Tools_PWM_View(void){

    if (pwm_switch == 1){
        Option_ToolsPWMOUTMenu[2].Variables = 72000000/pwm_out_PSC/pwm_out_ARR;
        Option_ToolsPWMOUTMenu[3].Variables = pwm_out_PSC;
        Option_ToolsPWMOUTMenu[4].Variables = pwm_out_ARR;
        Option_ToolsPWMOUTMenu[5].Variables = pwm_out_duty;
    }
}

// 修改PSC
void Tools_PWM_SetOutputPSCuency(void){

    uint16_t tolerance = 1;
    int8_t encoder_value = 0;

    while(1){
        if (Key2_signal_func()){
            return;
        }
        if (Key1_signal_func()){
            tolerance *= 10;
            if (tolerance > 100) tolerance = 1;
        }
        encoder_value = Key_EncoderGetValue();
        pwm_out_PSC += (encoder_value*tolerance);
        if (pwm_out_PSC >= 7200) pwm_out_PSC = 7200;
        else if (pwm_out_PSC <= 0) pwm_out_PSC = 0; 

        TIM_PrescalerConfig(TIM1, pwm_out_PSC-1, TIM_PSCReloadMode_Update);
        OLED_Clear();
        OLED_Printf(1, 0, OLED_8X16, "频率: %d hz", 72000000/pwm_out_PSC/pwm_out_ARR);
        OLED_Printf(1, 25, OLED_6X8, "PSC: %d/7200", pwm_out_PSC);
        OLED_DrawRectangle(2, 35, 123, 14, OLED_UNFILLED);
        OLED_DrawRectangle(2, 35, ((pwm_out_PSC/59)>123)?123:pwm_out_PSC/59, 14, OLED_FILLED );
        OLED_Printf(1, 55, OLED_6X8, "tolerance: %d", tolerance);
        OLED_Update();
    }
}

// 修改ARR
void Tools_PWM_SetOutputARRuency(void){

    uint16_t tolerance = 1;
    int8_t encoder_value = 0;

    while(1){
        if (Key2_signal_func()){
            return;
        }
        if (Key1_signal_func()){
            tolerance *= 10;
            if (tolerance > 1000) tolerance = 1;
        }
        encoder_value = Key_EncoderGetValue();
        pwm_out_ARR += (encoder_value*tolerance);
        if (pwm_out_ARR >= 100000) pwm_out_ARR = 100000;
        else if (pwm_out_ARR <= 0) pwm_out_ARR = 0; 

        TIM_SetAutoreload(TIM1, pwm_out_ARR-1);
        OLED_Clear();
        OLED_Printf(1, 0, OLED_8X16, "频率: %d hz", 72000000/pwm_out_PSC/pwm_out_ARR);
        OLED_Printf(1, 25, OLED_6X8, "ARR: %d/100000", pwm_out_ARR);
        OLED_DrawRectangle(2, 35, 123, 14, OLED_UNFILLED);
        OLED_DrawRectangle(2, 35, ((pwm_out_ARR/814)>123)?123:pwm_out_ARR/814, 14, OLED_FILLED );
        OLED_Printf(1, 55, OLED_6X8, "tolerance: %d", tolerance);
        OLED_Update();

    }
}

// 修改占空比
void Tools_PWM_SetOutputDutyuency(void){
    uint16_t tolerance = 1;
    int8_t encoder_value = 0;

    while(1){
        if (Key2_signal_func()){
            return;
        }
        if (Key1_signal_func()){
            tolerance *= 10;
            if (tolerance > 1000) tolerance = 1;
        }
        encoder_value = Key_EncoderGetValue();
        pwm_out_duty += (encoder_value*tolerance);
        if (pwm_out_duty >= pwm_out_ARR) pwm_out_duty = pwm_out_ARR;
        else if (pwm_out_duty <= 0) pwm_out_duty = 0; 

        TIM_SetCompare1(TIM1, ((pwm_out_duty-1) < 0)?0:pwm_out_duty-1);
        OLED_Clear();
        OLED_Printf(1, 0, OLED_8X16, "频率: %d hz", 72000000/pwm_out_PSC/pwm_out_ARR);
        OLED_Printf(1, 25, OLED_6X8, "duty: %d/%d", pwm_out_duty, pwm_out_ARR);
        OLED_DrawRectangle(2, 35, 123, 14, OLED_UNFILLED);
        OLED_DrawRectangle(2, 35, ((pwm_out_duty/(pwm_out_ARR/124)) > 123)?123:pwm_out_duty/(pwm_out_ARR/124), 14, OLED_FILLED );
        OLED_Printf(1, 55, OLED_6X8, "tolerance: %d", tolerance);
        OLED_Update();

    }
}

void Tools_PWM_SetOutputPolarity(void){

    static bool polarity_stat = 1;

    polarity_stat ^= 1;

    if (polarity_stat == 0){
        Option_ToolsPWMOUTMenu[6].str = "输出电平:低电平";
        TIM_OC1PolarityConfig(TIM1, TIM_OCPolarity_Low);
    }
    else if (polarity_stat == 1){
        Option_ToolsPWMOUTMenu[6].str = "输出电平:高电平";
        TIM_OC1PolarityConfig(TIM1, TIM_OCPolarity_High);
    }
}

void Tools_PWM_Init(void){

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_TIM1, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
    TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStruct.TIM_Period = 20000-1;
    TIM_TimeBaseInitStruct.TIM_Prescaler = 72-1;
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseInitStruct);

    TIM_OCInitTypeDef TIM_OCInitStructure;
    TIM_OCStructInit(&TIM_OCInitStructure);
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 0;
    TIM_OC1Init(TIM1, &TIM_OCInitStructure);

    TIM_CtrlPWMOutputs(TIM1, ENABLE);

    TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);

    TIM_ARRPreloadConfig(TIM1, ENABLE);

    TIM_Cmd(TIM1, DISABLE);
}
