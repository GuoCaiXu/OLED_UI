# ifndef _SETTING_H
# define _SETTING_H

# include "stm32f10x.h"
# include "stdbool.h"

bool Read_InvertedFlag(void);

void MENU_OptionSettingMenu(void);
void Setting_AnimationSpeed(void);
void Setting_Inverted(void);

# endif
