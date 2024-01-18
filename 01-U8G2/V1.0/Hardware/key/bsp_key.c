# include "./key/bsp_key.h"

extern u8g2_t u8g2;

Keys key[2] = {0, 0, 0, 0, 0};

void Key_Init(void){

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
}

void Key_Scan(void){

    key[0].key_sta = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11);
    key[1].key_sta = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_10);

    for (uint8_t i = 0; i < 2; i ++){

        switch(key[i].key_judge){
            case 0:{
                if (key[i].key_sta == 0){
                    key[i].time = 0;
                    key[i].key_judge = 1;
                }
                break;
            }
            case 1:{
                if (key[i].key_sta == 0){
                    key[i].key_judge = 2;
                }
                break;
            }
            case 2:{
                if (key[i].key_sta == 1){

                    if (key[i].time < 30) 
                        key[i].single_flag = 1;
                    key[i].key_judge = 0;
                }
                else {
                    key[i].time ++;
                    if (key[i].time > 30) {
                        key[i].long_flag = 1;
                        key[i].key_judge = 0;
                    }
                }
                break;
            }
        }
    }
}

