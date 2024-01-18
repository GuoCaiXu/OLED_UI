# ifndef _BSP_KEY_H
# define _BSP_KEY_H

# include "main.h"

typedef struct{
    uint8_t     key_judge;
    bool        key_sta;
    bool        single_flag;
    bool        long_flag;
    uint32_t    time;
}Keys;

extern Keys key[2];

void Key_Init(void);
void Key_Scan(void);
void Key_porc(void);

# endif
