# ifndef _BSP_TIM_H
# define _BSP_TIM_H

# include "stm32f10x.h"

void TIM3_Init(int psc, int per);
uint8_t Get_FPS(void);

# endif
