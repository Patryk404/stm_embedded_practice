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
#include <stdio.h>

int32_t add_numbers(int32_t x,int32_t y){
	int32_t res;
	__asm("SVC #36");
	__asm("MOV %0,R0": "=r"(res));
	return res;
}

int32_t sub_numbers(int32_t x,int32_t y){
	int32_t res;
	__asm("SVC #37");
	__asm("MOV %0,R0": "=r"(res));
	return res;
}

int32_t mul_numbers(int32_t x,int32_t y){
	int32_t res;
	__asm("SVC #38");
	__asm("MOV %0,R0": "=r"(res));
	return res;
}

int32_t div_numbers(int32_t x,int32_t y){
	int32_t res;
	__asm("SVC #39");
	__asm("MOV %0,R0": "=r"(res));
	return res;
}

int main(void)
{
	int32_t result = add_numbers(10,20);
	printf("Addition: %ld \n",result);
	result = sub_numbers(10,20);
	printf("Subtraction: %ld \n",result);
	result = mul_numbers(10,3);
	printf("Multiplicaton: %ld \n",result);
	result = div_numbers(20,5);
	printf("Division: %ld \n",result);
    /* Loop forever */
	for(;;);
}

__attribute__ ((naked)) SVC_Handler(void) {
	__asm("MRS R0,MSP");
	__asm("B SVC_Handler_c");
}

void SVC_Handler_c(uint32_t* pBaseOfStackFrame){
	uint32_t arg1 = pBaseOfStackFrame[0];
	uint32_t arg2 = pBaseOfStackFrame[1];
	uint8_t* pReturn_addr = (uint8_t*)pBaseOfStackFrame[6];
	pReturn_addr -=2;
	uint8_t svc_number = *pReturn_addr;
	switch(svc_number){
		case 36:{ // Addition
			pBaseOfStackFrame[0] = arg1+arg2;
			break;
		}
		case 37:{ // Subtraction
			pBaseOfStackFrame[0] = arg1-arg2;
			break;
		}
		case 38:{ // Multiplication
			pBaseOfStackFrame[0] = arg1*arg2;
			break;
		}
		case 39: { // Division
			pBaseOfStackFrame[0]= arg1/arg2;
			break;
		}
	}
	return;
}