# include "./menu/menu.h"

uint8_t ui_run(int8_t *a, int8_t *a_trg, int8_t step, int8_t slow_cnt){

	int8_t temp;

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

// 获取结构体长度
int8_t Menu_stuctlen(Option_Class *Option_List){

	int8_t list_len;
	for (list_len = 0; strcmp(Option_List[list_len].str, "\0") != 0; list_len ++);

	return list_len;
}

// 获取字符串长度
int8_t Menu_strlen(char *str){

	int8_t str_len = 0, i = 0;
	while(str[i] != '\0'){
		if (str[i] > '~'){
			str_len += 2;
			i += 3;
		}
		else {
			str_len += 1;
			i += 1;
		}
	}

	return str_len;
}

/**
 * 函    数：OLED显示汉字单字
 * 参    数：X 指定字符串左上角的横坐标，范围：0~127
 * 参    数：Y 指定字符串左上角的纵坐标，范围：0~63
 * 参    数：Hanzi 指定要显示的字符，范围：字库字符
 * 参    数：FontSize 指定字体大小
 *           范围：OLED_8X16		宽8像素，高16像素
 *                 OLED_6X8		宽6像素，高8像素
 * 返 回 值：无
 * 说    明：调用此函数后，要想真正地呈现在屏幕上，还需调用更新函数
 */
void Menu_ShowChinese(int8_t X, int8_t Y, char *Hanzi) // 汉字单字打印;
{
	uint8_t pIndex;
	for (pIndex = 0; strcmp(OLED_CF16x16[pIndex].Index, "") != 0; pIndex++)
	{
		/*找到匹配的汉字*/
		if (strcmp(OLED_CF16x16[pIndex].Index, Hanzi) == 0)
		{
			break; // 跳出循环，此时pIndex的值为指定汉字的索引
		}
	}
	/*将汉字字模库OLED_CF16x16的指定数据以16*16的图像格式显示*/
	OLED_ShowImage(X, Y, 16, 16, OLED_CF16x16[pIndex].Data);
}

void Menu_ShowString(uint8_t X, uint8_t Y, char *str, uint8_t FontSize){

    uint8_t i = 0;
	uint8_t pChinese = 0;
	char SingleChinese[OLED_CHN_CHAR_WIDTH + 1] = {0};
	while (str[i] != '\0') // 遍历字符串的每个字符
	{
		if (str[i] > '~'){
			SingleChinese[pChinese] = str[i];	//提取汉字串数据到单个汉字数组
			pChinese ++;
			i ++;
			
			if (pChinese >= OLED_CHN_CHAR_WIDTH){
				pChinese = 0;
				// /*遍历整个汉字字模库，寻找匹配的汉字*/
				// /*如果找到最后一个汉字（定义为空字符串），则表示汉字未在字模库定义，停止寻找*/
				// for (pIndex = 0; strcmp(OLED_CF16x16[pIndex].Index, "") != 0; pIndex ++)
				// {
				// 	/*找到匹配的汉字*/
				// 	if (strcmp(OLED_CF16x16[pIndex].Index, SingleChinese) == 0)
				// 	{
				// 		break;		//跳出循环，此时pIndex的值为指定汉字的索引
				// 	}
				// }
				
				// /*将汉字字模库OLED_CF16x16的指定数据以16*16的图像格式显示*/
				// OLED_ShowImage(X + ((i + 1) / OLED_CHN_CHAR_WIDTH - 1) * 16, Y, 16, 16, OLED_CF16x16[pIndex].Data);
				Menu_ShowChinese(X + ((i + 1) / OLED_CHN_CHAR_WIDTH - 1) * 16, Y, SingleChinese);
			}
		}
		else {
			OLED_ShowChar(X + i * FontSize, Y, str[i], FontSize);
			i ++;
		}
	}
}
