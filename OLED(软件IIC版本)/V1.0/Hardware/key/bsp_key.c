# include "./key/bsp_key.h"

Keys key[2] = {0, 0, 0, 0, 0, 0};

void Key_Init(void){

    RCC_APB2PeriphClockCmd(KEY_CLK, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Pin = KEY1_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(KEY1_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = KEY2_PIN;
    GPIO_Init(KEY2_PORT, &GPIO_InitStructure);
}

void Key_Scan(void){

    key[0].key_sta = GPIO_ReadInputDataBit(KEY1_PORT, KEY1_PIN);
    key[1].key_sta = GPIO_ReadInputDataBit(KEY2_PORT, KEY2_PIN);

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
                else key[i].key_judge = 0;
                break;
            }
            case 2:{
                if (key[i].key_sta == 1){

                    key[i].key_judge = 0;
                    if (key[i].time < 30)   
                        key[i].single_flag = 1;
                    key[i].long_sta = 0;
                }
                else {
                    key[i].time ++;
                    if (key[i].time >= 30) {
                        if (key[i].time % 30 == 0){
                            key[i].long_sta = 0;
                        }
                        if (key[i].long_sta == 0){
                            key[i].long_flag = 1;
                            key[i].long_sta = 1;
                        }
                    }
                }
                break;
            }
        }
    }
}

uint8_t Key1_signal_func(void){
    if (key[0].single_flag == 1){
        key[0].single_flag = 0;
        return 1;
    }
    return 0;
}

uint8_t Key1_long_func(void){
    if (key[0].long_flag == 1){
        key[0].long_flag = 0;
        return 1;
    }
    return 0;
}

uint8_t Key2_signal_func(void){
    if (key[1].single_flag == 1){
        key[1].single_flag = 0;
        return 1;
    }
    return 0;
}

uint8_t Key2_long_func(void){
    if (key[1].long_flag == 1){
        key[1].long_flag = 0;
        return 1;
    }
    return 0;
}
