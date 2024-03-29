# ifndef _MENU_H
# define _MENU_H

# include "stm32f10x.h"
# include "stdbool.h"
# include "string.h"
# include "stdlib.h"
#include "stdarg.h"

# include "./key/bsp_key.h"
# include "./uart/bsp_uart.h"
# include "./oled/OLED.h"
# include "./setting/setting.h"
# include "./Tools/tools.h"

typedef struct{
    // 字体高度
    int8_t font_Hight;                      // 高度
    int8_t font_Width;                      // 宽度

    // 动画过渡
    int8_t step;
    int8_t slow_cnt;

    int8_t y;
	int8_t frame_y;
	int8_t frame_len;
}MenuProperty;

typedef struct{
	char    *str;
    void    (*func)(void);
    int32_t Variables;
}Option_Class;

extern MenuProperty	Menu_Global;

/*补丁*/
uint8_t ui_run(int8_t *a, int8_t *a_trg, int8_t step, int8_t slow_cnt);
int8_t Menu_stuctlen(Option_Class *Option_List);
int8_t Menu_strlen(char *format, ...);
void Menu_ShowString(uint8_t X, uint8_t Y, char *str, uint8_t FontSize);
int8_t Key_EncoderGetValue(void);

void MENU_RunMain(Option_Class *Option_List);

void MENU_OptionStartMenu(void);
void MENU_OptionToolsMenu(void);
void MENU_OptionInformationMenu(void);

# endif
