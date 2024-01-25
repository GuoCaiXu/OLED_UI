# include "stm32f10x.h"
# include "./key/bsp_key.h"
# include "./oled/OLED.h"
# include "./tim/bsp_tim.h"
# include "./uart/bsp_uart.h"
# include "./menu/menu.h"

int main(void){

	Key_Init();
	OLED_Init();
	TIM2_Init(720-1, 1000-1);
	My_UART_Init();
	while(1){

		MENU_OptionStartMenu();
	}
}
