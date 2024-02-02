# include "./Tools/tools.h"

void Tools_OptionUSART_MENU(void){

    uint16_t cnt = 0;

    USART_Cmd(USART1, ENABLE);
    OLED_Clear();
	OLED_Printf(32, 24, OLED_8X16, "等待数据");
	OLED_Update();

    while(1){

        if (Key2_signal_func()){
            
            USART_Cmd(USART1, DISABLE);
            return;
        }
        OLED_Update();
    }
}