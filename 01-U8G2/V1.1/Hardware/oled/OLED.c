#include "OLED.h"
# include <stdlib.h>
# include <math.h>

extern Keys key[2];
u8g2_t u8g2;

int list_len;

// 字符
short x;			// x当前位置数值	
short y = 14, y_trg = 14;

// 字体高度
uint8_t font_Hight;

// 框框
short frame_len, frame_len_trg;			// 框框的宽度
short frame_y, frame_y_trg;				// 框框的高

int8_t ui_select = 0;

uint8_t state;

typedef struct{
	char *str;
}SETTING_LIST;

SETTING_LIST list[] = 
{
	{"Type"},
	{"Value"},
	{"Yaw"},
	{"Time"},
	{"Reduct"},
	{"Set"}
};

SETTING_LIST list_buff[3];

uint8_t u8g2_gpio_and_delay_stm32(U8X8_UNUSED u8x8_t *u8x8, U8X8_UNUSED uint8_t msg, U8X8_UNUSED uint8_t arg_int, U8X8_UNUSED void *arg_ptr)
{
	switch(msg)
		{
			case U8X8_MSG_DELAY_MILLI://Function which implements a delay, arg_int contains the amount of ms
				delay_ms(arg_int);
			break;
		
			case U8X8_MSG_DELAY_10MICRO://Function which delays 10us
				delay_us(10);
			break;
		
			case U8X8_MSG_DELAY_100NANO://Function which delays 100ns
				__NOP();
			break;
			case U8X8_MSG_GPIO_I2C_CLOCK:
				if (arg_int) OLED_W_SCL(1);
				else OLED_W_SCL(0);
			break;
			case U8X8_MSG_GPIO_I2C_DATA:
				if (arg_int) OLED_W_SDA(1);
				else OLED_W_SDA(0);
			break;
			default:
				return 0; //A message was received which is not implemented, return 0 to indicate an error
	}
	return 1; // command processed successfully.
}

void OLED_GPIO_Init(void)
{
	
	/*将SCL和SDA引脚初始化为开漏模式*/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
 	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
 	GPIO_Init(GPIOB, &GPIO_InitStructure);

	u8g2_Setup_ssd1306_i2c_128x64_noname_f(&u8g2, U8G2_R0, u8x8_byte_sw_i2c, u8g2_gpio_and_delay_stm32);
	u8g2_InitDisplay(&u8g2);
	u8g2_SetPowerSave(&u8g2, 0);
	u8g2_ClearBuffer(&u8g2);
	u8g2_SetFont(&u8g2, u8g2_font_t0_18b_mf);
	font_Hight = u8g2_GetMaxCharHeight(&u8g2);
}

/*
	函数作用: 使ui动起来
	变量:	a : 		变量的现坐标
			a_trg:		变量坐标的目标值
			step:		目标每次增加的值
			slow_cnt:	设置限制快到目标值就缓慢增加
*/
uint8_t ui_run(short *a, short *a_trg, uint8_t step, uint8_t slow_cnt){

	uint8_t temp;

	temp = (abs(*a_trg - *a ))> slow_cnt ? step : 1;

	if (*a < *a_trg){
		
		*a += temp;
	}
	else if (*a > *a_trg){

		*a -= temp;
	}
	else {

		return 0;
	}

	return 1;
}

void ui_show(void){

	list_len = sizeof(list)/sizeof(SETTING_LIST);

	u8g2_ClearBuffer(&u8g2);
	for (uint8_t i = 0; i < list_len; i ++){						// 显示list结构体的所以字符

		u8g2_DrawStr(&u8g2, x, y+i*(font_Hight), list[i].str);				// 显示字符	x表示字符从x+2开始， y表示从y+i*20开始
	}
	u8g2_SetDrawColor(&u8g2, 2);
	u8g2_DrawRBox(&u8g2, x, frame_y, frame_len, font_Hight, 0);			// 画框框
	u8g2_SetDrawColor(&u8g2, 1);
	ui_run(&y, &y_trg, 1, 3);
	ui_run(&frame_y, &frame_y_trg, 1, 3);							// 框框的y值的ui
	ui_run(&frame_len, &frame_len_trg, 1, 7);
	u8g2_SendBuffer(&u8g2);
}

void ui_porc(void){

	if (key[0].single_flag == 1){

        
        key[0].single_flag = 0;
    }

    if (key[0].long_flag == 1){
        ui_select ++;
		frame_y_trg += (font_Hight-1);
		
		if (ui_select >= list_len){
			ui_select = list_len - 1;
			frame_y_trg = frame_y_trg - (font_Hight-1);
		}
		if ((ui_select > 2) && (frame_y_trg > (14+((font_Hight-1)*3)))){
			y_trg -= (font_Hight);
			frame_y_trg = frame_y_trg - (font_Hight-1);
		}
        key[0].long_flag = 0;
    }

    if (key[1].single_flag == 1){
		
		
		key[1].single_flag = 0; 
    }

    if (key[1].long_flag == 1){
        ui_select --;
		frame_y_trg -= (font_Hight-1);
		if (ui_select < 0){
			ui_select = 0;
			frame_y_trg = 0;
		}
		if (frame_y_trg < 0){
			y_trg += (font_Hight-1);
			frame_y_trg = 0;
		}
		key[1].long_flag = 0;  
    }
	frame_len_trg = u8g2_GetStrWidth(&u8g2, list[ui_select].str)+1;
	ui_show();
}
