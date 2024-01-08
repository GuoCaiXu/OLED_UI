# include "main.h"

void SysConfiguration(void){

	OLED_GPIO_Init();
	Key_Init();
	TIM2_Init(720-1, 1000-1);
}

/**
 *  @brief  主函数
 *  @param  无
 *  @retval 无
 */
int main(void){

	SysConfiguration();
	
	while(1){
		ui_porc();
	}
}
