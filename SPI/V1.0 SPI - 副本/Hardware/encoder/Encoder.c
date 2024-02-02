#include "stm32f10x.h"                  // Device header

void Encoder_Init(void)
{
	GPIO_InitTypeDef            GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef     TIM_TimeBaseInitStructure;
    TIM_ICInitTypeDef           TIM_ICInitStructure;

    /*1.时钟配置*/
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    /*2.GPIO 配置*/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;           // 浮空输入
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /*3.定时器配置*/
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStructure.TIM_Period = 65535;
    TIM_TimeBaseInitStructure.TIM_Prescaler = 0;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);

    /*4.输入捕获配置*/
    TIM_ICStructInit(&TIM_ICInitStructure);
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
    TIM_ICInitStructure.TIM_ICFilter = 10;          // 滤波器设置为10
    TIM_ICInit(TIM2, &TIM_ICInitStructure);
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
    TIM_ICInit(TIM2, &TIM_ICInitStructure);

    /*5.编码器配置: 定时器2，模式3，上上升沿*/
    TIM_EncoderInterfaceConfig(TIM2, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);

    /*6.清除定时器溢出更新标志位(清除计数值)*/
    TIM_ClearFlag(TIM2, TIM_FLAG_Update);

    /*7.定时器2，溢出更新，使能*/
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

    /*8.定时器数据清0(输入捕获从0开始计数)*/
    TIM_SetCounter(TIM2, 0);

    /*9.定时器2使能*/
    TIM_Cmd(TIM2, ENABLE);
}

int16_t Encoder_Get(void)
{	
	static int8_t d0;
	int16_t temp;
	/*除以4输出*/	
	if(TIM_GetCounter(TIM2)/4 - d0)
	{
		temp = (short)(TIM_GetCounter(TIM2)/4 - d0);
		
		d0 = TIM_GetCounter(TIM2)/4;
		return temp;
	}
	return 0;
}
