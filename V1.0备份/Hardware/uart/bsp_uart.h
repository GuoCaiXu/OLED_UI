# ifndef _BSP_UART_H
# define _BSP_UART_H

# include "stm32f10x.h"
# include "stdio.h"

/*调试串口配置*/
void My_UART_Init(void);

/*调试串口函数*/
int fputc(int ch, FILE *f);

# endif
