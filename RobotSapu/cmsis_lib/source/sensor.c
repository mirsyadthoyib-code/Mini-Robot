#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "sensor.h"

int proxy13, proxy14;

/*
 * inisialisasi 2 sensor proximity sebagai input data untuk menghindari halangan
 */

void init_proximity()
{
	GPIO_InitTypeDef GPIO_InitStruct;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

	GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
}

/*
 * fungsi untuk membaca data dari sensor proximity
 */

void dataProxy()
{
	proxy13 = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_6);
    proxy14 = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_7);
}
