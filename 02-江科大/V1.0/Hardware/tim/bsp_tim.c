# include "./tim/bsp_tim.h"

void TIM2_Init(int psc, int per){

    // 1.选择内部时钟
    TIM_InternalClockConfig(TIM2);

    // 2.开启TIM时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    // 3.配置时基结构体
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;

    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_Prescaler = psc;
    TIM_TimeBaseInitStructure.TIM_Period = per;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);

    // 4.配置中断结构体
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_Init(&NVIC_InitStructure);

    // 5.清除中断标志位
    TIM_ClearFlag(TIM2, TIM_FLAG_Update);

    // 6.定时器中断初始化
    TIM_ITConfig(TIM2, TIM_FLAG_Update, ENABLE);

    // 7. 开启定时器
    TIM_Cmd(TIM2, ENABLE);
}

void TIM2_IRQHandler(void){

    if (TIM_GetITStatus(TIM2, TIM_FLAG_Update) == SET){

        Key_Scan();
        TIM_ClearITPendingBit(TIM2, TIM_FLAG_Update);
    }
}
