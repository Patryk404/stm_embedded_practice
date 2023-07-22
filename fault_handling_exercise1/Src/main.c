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

void enable_all_faults(void){
	uint32_t *shcrs = (uint32_t*)0xE000ED24;
	*shcrs = (1<<18) | (1<<17) | (1<<16); // enabling usgfault busfault and memfault
}
int illegal_instruction_execution(void) { // processor attempted an instruction fetch from a location that does nor permit execution in case of 0xE0000000
  int (*bad_instruction)(void) = (void *)0x60000000;
  return bad_instruction();
}

void divide_by_0(void){
	uint8_t test = 12/0;
	return test;
}

int executing_instruction_from_peripherial_region(void){
	uint32_t (*region)(void) = (void*)0x40000000;
	return region();
}



int main(void)
{
	// enable all configurable exceptions like usage fault, mem manage fault and bus fault
	enable_all_faults();

	// implement the fault handlers
	// done below lol
	// lets force the processor to execute some undefined instruction
//	illegal_instruction_execution(); // usage fault
//	divide_by_0(); //
	executing_instruction_from_peripherial_region();
	// analyze the fault

    /* Loop forever */
	for(;;);
}

void HardFault_Handler(void){

}

void MemManage_Handler(void){
	uint8_t* MMSR = (uint8_t*)0xE000ED28;
	printf("status: %x",*MMSR);
}

void BusFault_Handler(void){

}

void UsageFault_Handler(void){
	uint16_t* UFSR = (uint16_t*)0xE000ED2A;
	printf("status: %x",*UFSR);
}

