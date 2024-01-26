# ifndef _BSP_KEY_H
# define _BSP_KEY_H

# include "stm32f10x.h"
# include "stdbool.h"

typedef struct{
    uint8_t     key_judge;
    bool        key_sta;
    bool        single_flag;
    bool        long_flag;
    bool        long_sta;
    uint32_t    time;
}Keys;

extern Keys key[2];

void Key_Init(void);
void Key_Scan(void);

uint8_t Key1_signal_func(void);
uint8_t Key1_long_func(void);
uint8_t Key2_signal_func(void);
uint8_t Key2_long_func(void);

# endif
