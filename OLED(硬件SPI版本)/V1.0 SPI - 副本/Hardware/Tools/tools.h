# ifndef _TOOLS_H
# define _TOOLS_H

# include "stdio.h"

# include "stm32f10x.h"
# include "./key/bsp_key.h"
# include "./menu/menu.h"
# include "./uart/bsp_uart.h"

// 界面函数
void MENU_OptionToolsMenu(void);

// PWM输出函数
void Tools_PWMOut_Init(void);                       // PWM输出初始化
void Tools_OptionPWMOut_MENU(void);

// PWM输入捕获
void Tools_PWMInput_Init(void);
void Tools_OptionPWMInput_MENU(void);

// 串口播放视频函数
void Tools_OptionUSART_MENU(void);

# endif
