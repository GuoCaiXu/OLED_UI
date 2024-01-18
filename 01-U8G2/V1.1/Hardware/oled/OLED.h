#ifndef __OLED_H
#define __OLED_H

# include "main.h"
# include "u8g2.h"

# define OLED_W_SCL(x)      GPIO_WriteBit(GPIOB, GPIO_Pin_8, (BitAction)x)
# define OLED_W_SDA(x)      GPIO_WriteBit(GPIOB, GPIO_Pin_9, (BitAction)x)

extern u8g2_t u8g2;

void OLED_GPIO_Init(void);
uint8_t u8g2_gpio_and_delay_stm32(U8X8_UNUSED u8x8_t *u8x8, U8X8_UNUSED uint8_t msg, U8X8_UNUSED uint8_t arg_int, U8X8_UNUSED void *arg_ptr);

void ui_porc(void);
void ui_show(void);
#endif
