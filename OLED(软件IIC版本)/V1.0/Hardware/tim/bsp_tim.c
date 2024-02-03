# include "./tim/bsp_tim.h"
# include "./key/bsp_key.h"

void TIM3_Init(int psc, int per){

    // 1.选择内部时钟
    TIM_InternalClockConfig(TIM3);

    // 2.开启TIM时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

    // 3.配置时基结构体
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;

    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_Prescaler = psc;
    TIM_TimeBaseInitStructure.TIM_Period = per;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);

    // 4.配置中断结构体
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_Init(&NVIC_InitStructure);

    // 5.清除中断标志位
    TIM_ClearFlag(TIM3, TIM_FLAG_Update);

    // 6.定时器中断初始化
    TIM_ITConfig(TIM3, TIM_FLAG_Update, ENABLE);

    // 7. 开启定时器
    TIM_Cmd(TIM3, ENABLE);
}

uint8_t FPS_Count = 0, FPS_Value = 0;
uint8_t Get_FPS(void){
    FPS_Count ++;

    return FPS_Value;
}

void TIM3_IRQHandler(void){

    static uint16_t FPS_i = 0;

    if (TIM_GetITStatus(TIM3, TIM_FLAG_Update) == SET){

        Key_Scan();

        if (++ FPS_i >= 100){
            
            FPS_Value = FPS_Count;
            FPS_Count = 0;
            FPS_i = 0;
        }
        TIM_ClearITPendingBit(TIM3, TIM_FLAG_Update);
    }
}
