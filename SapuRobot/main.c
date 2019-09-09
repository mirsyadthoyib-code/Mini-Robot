#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_syscfg.h"
#include "tm_stm32f4_delay.h"
#include "misc.h"
#include "motorDC.h"
#include "uart_node.h"
#include "sensor.h"

int flag = 0;
int prevFlag = 0;
extern int proxy13, proxy14;			//mengambil data variabel dari file lain dalam satu project
extern char data1,data2,data3,data4;
int proxy15 = 0;

/*
 * fungsi utama dari robot untuk melakukan tugas menyapu dengan gerakan awal maju
 * dan jika mengenai halangan maka akan berbelok kekiri kemudian jika menemui halangan lagi
 * maka akan berbelok kekanan agar semua wilayah tersapu
 */

void nyapu()
{
	if(flag == 0)
	{
		maju();
		if(proxy13 == 0 || proxy14 == 0)
		{
			if(prevFlag == 0 || prevFlag == 2)
			{
				flag = 1;
			}
			else if(prevFlag == 1)
			{
				flag = 2;
			}
		}
	}
	//kondisi untuk berbelok kekiri apabila proximity terkena halangan saat flag = 1
	else if(flag == 1)
	{
		kiri();
		Delayms(500);
		prevFlag = flag;
		flag = 0;
	}
	//kondisi untuk berbelok kekanan apabila proximity terkena halangan saat flag = 2
	else if(flag == 2)
	{
		kanan();
		Delayms(500);
		prevFlag = flag;
		flag = 0;
	}
}

/*
 * fungsi untuk dikendalikan secara manual melalui hp dengan protokol mqtt yang terhubung ke
 */

void manual()
{
	while(data1)
	{
		berhenti();
	}
	while(data2)
	{
		kiri();
	}
	while(data3)
	{
		kanan();
	}
	while(data4)
	{
		mundur();
	}
}

/*
 * fungsi utama yang akan dijalankan
 */

int main(void)
{
	SystemInit();
	TM_DELAY_Init();
	init_motor();
	init_node();
	init_proximity();

    while(1)
    {
    	dataProxy();
    	nyapu();
    	manual();
//    	tesMotor();
//    	mundur();
//    	Delayms(50);
//    	kiri();
    }
}
