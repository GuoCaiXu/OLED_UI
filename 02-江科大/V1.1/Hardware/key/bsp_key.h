/*
 * @Author: xgc030920@outlook.com
 * @Date: 2024-01-18 16:15:47
 * @LastEditors: xgc030920@outlook.com
 * @LastEditTime: 2024-01-18 16:16:50
 * @FilePath: \Project_EIDEc:\SyncFile\03-Project\05-OLED_UI\02-江科大\V1.0\Hardware\key\bsp_key.h
 * @Description: 
 * 
 * Copyright (c) 2024 by ${git_name_email}, All Rights Reserved. 
 */
# ifndef _BSP_KEY_H
# define _BSP_KEY_H

# include "main.h"
# include "stdbool.h"

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
