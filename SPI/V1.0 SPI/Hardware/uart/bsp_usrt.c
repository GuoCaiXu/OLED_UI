# include "./uart/bsp_uart.h"

/**
 *  @brief  调试串口 GPIO 初始化
 *  @param  无
 *  @retval 无
 */
void My_UART_Init(void){

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitTypeDef    GPIO_InitStructure;

    /*调试串口GPIO初始化*/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
    
    USART_InitTypeDef   USART_InitStructure;
    USART_InitStructure.USART_BaudRate = 921600;                                        //配置波特率
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;     //硬件流控制选择
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;                     //串口模式
    USART_InitStructure.USART_Parity = USART_Parity_No;                                 //选择是否使用奇偶校验位
    USART_InitStructure.USART_StopBits = USART_StopBits_1;                              //停止位长度
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;                         //配置字长
    USART_Init(USART1, &USART_InitStructure);

    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);

    /*使能串口*/
    USART_Cmd(USART1, DISABLE);
}

/*重定向c 库函数printf 到串口，重定向后可使用printf*/
int fputc(int ch, FILE *f){

    /*发送一个字节数据到串口*/
    USART_SendData(USART1, (uint8_t) ch);

    /*等待发送完毕*/
    while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);

    return (ch);
}


void USART1_IRQHandler(void)
{
	static uint8_t p0 = 0, p1 = 0;
	if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET)
	{
		/*接收一个字节数据*/
		uint8_t RxData = USART_ReceiveData(USART1);
		
		/*将一个字节放到OLED显存数组的指定位置*/
		OLED_DisplayBuf[p0][p1] = RxData;
		
		/*位置自增*/
		p1 ++;
		if (p1 >= 128)
		{
			p1 = 0;
			p0 ++;
			if (p0 >= 8)
			{
				p0 = 0;
			}
		}
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
	}
}
