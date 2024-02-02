# include "./Tools/tools.h"

Option_Class Option_ToolsOutputCapturetMenu[] = {
    {"<<<"},
    {"输入捕获[关]", Tools_PWMInput_Switch},
    {".."},
    {"\0"},
    {"\0"},
    {".."},
    {"\0"}
};

bool pwm_input_switch = 0;
int32_t Enter_duty = 1000;
int16_t frequency = 0;
int32_t duty_cycle = 0;

void Tools_OptionPWMInput_MENU(void){

   MENU_RunMain(Option_ToolsOutputCapturetMenu);
}

void Tools_PWMInput_Switch(void){

    pwm_input_switch ^= 1;

    if (pwm_input_switch == 0){
        TIM_Cmd(TIM4, DISABLE);
        Option_ToolsOutputCapturetMenu[1].str = "输入捕获[关]";
        Option_ToolsOutputCapturetMenu[2].str = "..";
        Option_ToolsOutputCapturetMenu[2].Variables = NULL;
        Option_ToolsOutputCapturetMenu[2].func = NULL;
        Option_ToolsOutputCapturetMenu[3].str = "\0";
        Option_ToolsOutputCapturetMenu[3].Variables = NULL;
        Option_ToolsOutputCapturetMenu[4].str = "\0";
        Option_ToolsOutputCapturetMenu[4].Variables = NULL;
    }
    else if (pwm_input_switch == 1){
        TIM_Cmd(TIM4, ENABLE);

        Option_ToolsOutputCapturetMenu[1].str = "输入捕获[开]";
        Option_ToolsOutputCapturetMenu[2].str = "InDuty: %d";
        Option_ToolsOutputCapturetMenu[2].Variables = Enter_duty;
        Option_ToolsOutputCapturetMenu[2].func = Tools_PWM_SetOutputInDutyuency;
        Option_ToolsOutputCapturetMenu[3].str = "频率: %d hz";
        Option_ToolsOutputCapturetMenu[3].Variables = frequency;
        Option_ToolsOutputCapturetMenu[4].str = "占空比: %d";
        Option_ToolsOutputCapturetMenu[4].Variables = duty_cycle;
    }
}

void Tools_PWM_SetOutputInDutyuency(void){

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
        Enter_duty += (encoder_value*tolerance);
        if (Enter_duty >= 100000) Enter_duty = 100000;
        else if (Enter_duty <= 0) Enter_duty = 0; 
        OLED_Clear();
        OLED_Printf(1, 0, OLED_8X16, "占空比: %d", duty_cycle);
        OLED_Printf(1, 25, OLED_6X8, "InDuty: %d/100000", Enter_duty);
        OLED_DrawRectangle(2, 35, 123, 14, OLED_UNFILLED);
        OLED_DrawRectangle(2, 35, ((Enter_duty/814)>123)?123:Enter_duty/814, 14, OLED_FILLED );
        OLED_Printf(1, 55, OLED_6X8, "tolerance: %d", tolerance);
        OLED_Update();
    }
}

void Tools_PWMInput_Init(void){

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    TIM_InternalClockConfig(TIM4);

    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_Period = 65536-1;
    TIM_TimeBaseInitStructure.TIM_Prescaler = 72-1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseInitStructure);

    TIM_ICInitTypeDef TIM_ICInitStructure;
    TIM_ICStructInit(&TIM_ICInitStructure);
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
    TIM_ICInitStructure.TIM_ICFilter = 0xF;
    TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
    TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
    TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
    TIM_PWMIConfig(TIM4, &TIM_ICInitStructure);

    TIM_SelectInputTrigger(TIM4, TIM_TS_TI1FP1);   //配置TRGI的触发源为TI1FP1
    TIM_SelectSlaveMode(TIM4, TIM_SlaveMode_Reset);      //配置从模式

    TIM_Cmd(TIM4, DISABLE);
}

void Tools_EnterCapture(void){

    if (pwm_input_switch == 1){

        Option_ToolsOutputCapturetMenu[2].Variables = Enter_duty;
        Option_ToolsOutputCapturetMenu[3].Variables = ((1000000 / (TIM_GetCapture1(TIM4)+1)) == 1000000)?0:1000000 / (TIM_GetCapture1(TIM4)+1);
        Option_ToolsOutputCapturetMenu[4].Variables = (((TIM_GetCapture2(TIM4)+1) * Enter_duty / (TIM_GetCapture1(TIM4)+1)) == Enter_duty)?0:(TIM_GetCapture2(TIM4)+1) * Enter_duty / (TIM_GetCapture1(TIM4)+1);
        TIM4->CCR1 = 0;
        TIM4->CCR2 = 0;
    }
}
