#include<stdint.h>
#include "led.h"

void delay(uint32_t count)
{
  for(uint32_t i = 0 ; i < count ; i++);
}

//void led_init (void)
//{
////
////	uint32_t *pRccAhb1enr = (uint32_t*)0x40023830;
////	uint32_t *pGpiodModeReg = (uint32_t*)0x40020C00;
////
////
////	*pRccAhb1enr |= ( 1 << 3);
////	//configure LED_GREEN
////	*pGpiodModeReg |= ( 1 << (2 * LED_GREEN));
////	*pGpiodModeReg |= ( 1 << (2 * LED_ORANGE));
////	*pGpiodModeReg |= ( 1 << (2 * LED_RED));
////	*pGpiodModeReg |= ( 1 << (2 * LED_BLUE));
////
////#if 0
////	//configure the outputtype
////	*pGpioOpTypeReg |= ( 1 << (2 * LED_GREEN));
////	*pGpioOpTypeReg |= ( 1 << (2 * LED_ORANGE));
////	*pGpioOpTypeReg |= ( 1 << (2 * LED_RED));
////	*pGpioOpTypeReg |= ( 1 << (2 * LED_BLUE));
////#endif
////
////    led_off(LED_GREEN);
////    led_off(LED_ORANGE);
////    led_off(LED_RED);
////    led_off(LED_BLUE);
//
//
//
//}

void led_init(){ // we have only one led on board which we can manipulate i guess
    uint32_t *pClkCtrlReg = (uint32_t*)0x40021014;
    uint32_t *pPortAModeReg = (uint32_t*)0x48000000;
    uint32_t *pPortABsrReg = (uint32_t*)0x48000018;

    //1. enable the clock for GPIOA peripheral in the AHBENR
    *pClkCtrlReg |= (1<<17);

    //2. configure the mode of the IO pin as output
    uint32_t modereg = *pPortAModeReg & ~(3<<(2*5));
    modereg |= (1<<(2*5));
    *pPortAModeReg = modereg;
}

void led_on()
{
	uint32_t *pPortABsrReg = (uint32_t*)0x48000018;
  *pPortABsrReg = (1<<5);
}

void led_off()
{
	uint32_t *pPortABsrReg = (uint32_t*)0x48000018;
	*pPortABsrReg = (1<<(5+16));
}