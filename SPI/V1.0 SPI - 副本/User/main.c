# include "stm32f10x.h"
# include "./key/bsp_key.h"
# include "./oled/OLED.h"
# include "./tim/bsp_tim.h"
# include "./uart/bsp_uart.h"
# include "./menu/menu.h"
# include "./encoder/Encoder.h"

int main(void){

	Key_Init();
	OLED_Init();
	Encoder_Init();
	Tools_PWMInput_Init();
	Tools_PWM_Init();
	TIM3_Init(720-1, 1000-1);
	My_UART_Init();
	while(1){

		MENU_OptionStartMenu();
	}
}
