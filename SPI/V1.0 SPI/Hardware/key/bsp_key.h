# ifndef _BSP_KEY_H
# define _BSP_KEY_H

# include "stm32f10x.h"
# include "stdbool.h"

# define KEY_CLK            RCC_APB2Periph_GPIOB

# define KEY1_PIN           GPIO_Pin_11
# define KEY1_PORT          GPIOB

# define KEY2_PIN           GPIO_Pin_10
# define KEY2_PORT          GPIOB

typedef struct{
    uint8_t     key_judge;
    bool        key_sta;
    bool        single_flag;
    bool        long_flag;
    bool        long_sta;
    uint32_t    time;
}Keys;

void Key_Init(void);
void Key_Scan(void);

uint8_t Key1_signal_func(void);
uint8_t Key1_long_func(void);
uint8_t Key2_signal_func(void);
uint8_t Key2_long_func(void);

# endif
