# ifndef _SETTING_H
# define _SETTING_H

# include "stm32f10x.h"
# include "stdbool.h"

uint8_t Read_InvertedFlag(void);
bool Read_NightMode(void);

void MENU_OptionSettingMenu(void);
void Setting_AnimationSpeed(void);
void Setting_Inverted(void);
void Setting_NightMode(void);

# endif
