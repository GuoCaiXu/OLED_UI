# ifndef _TOOLS_H
# define _TOOLS_H

# include "stdio.h"

# include "stm32f10x.h"
# include "./key/bsp_key.h"
# include "./menu/menu.h"
# include "./uart/bsp_uart.h"

void Tools_PWM_Init(void);
void Tools_PWMInput_Init(void);

void Tools_OptionPWMOut_MENU(void);
void Tools_PWM_Switch(void);
void Tools_PWM_SetOutputPSCuency(void);
void Tools_PWM_SetOutputARRuency(void);
void Tools_PWM_SetOutputDutyuency(void);
void Tools_PWM_SetOutputPolarity(void);
void Tools_PWM_View(void);

void Tools_OptionPWMInput_MENU(void);
void Tools_PWMInput_Switch(void);
void Tools_PWM_SetOutputInDutyuency(void);
void Tools_EnterCapture(void);

void Tools_OptionUSART_MENU(void);

void Tools_Porc(void);

# endif
