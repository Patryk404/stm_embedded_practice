/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include <stdint.h>

int main(void)
{
//	__asm volatile(
//			"LDR R0,[R1]\n\t"
//			"LDR R1,[R0]\n\t"
//			"ADD R1,R0\n\t"
//			"STR R1,[R0]"
//	);

#if
	__asm volatile("LDR R1,=#0x20001000");
	__asm volatile("LDR R2,=#0x20001004");
	__asm volatile("LDR R0,[R1]");
	__asm volatile("LDR R1,[R2]");
	__asm volatile("ADD R0,R0,R1");
	__asm volatile("STR R0,[R2]");
#endif

	int val=50;
	__asm volatile("MOV R0,%0": :"r"(val):); // r constraint says to use general registers while moving

	uint32_t control_reg=0;
	__asm volatile("MRS %0,CONTROL": "=r"(control_reg)::); // load value of control register to our control_reg variable

	int var1=10,var2=0;
	__asm volatile("MOV %0,%1":"=r"(var2):"r"(var1)); // copy values

	int p1, *p2;
	p2 = (int*)0x20001008;
	__asm volatile("LDR %0,[%1]":"=r"(p1):"r"(p2));

	for(;;);
}
