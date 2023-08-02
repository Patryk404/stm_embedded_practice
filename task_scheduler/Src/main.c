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
#include "main.h"

void init_systick_timer(uint32_t tick_hz);
__attribute__((naked)) void init_scheduler_stack(uint32_t start_address);
void init_tasks_stack(void);
__attribute__((naked)) void switch_sp_to_psp(void);
void enable_all_faults(void){
	uint32_t *shcrs = (uint32_t*)0xE000ED24;
	*shcrs = (1<<18) | (1<<17) | (1<<16); // enabling usgfault busfault and memfault
}

void task1_handler(void);
void task2_handler(void);
void task3_handler(void);
void task4_handler(void);

uint32_t psp_of_tasks[MAX_TASKS] = {STACK_TASK1_START,STACK_TASK2_START,STACK_TASK3_START,STACK_TASK4_START};
uint32_t task_handlers[MAX_TASKS];
uint8_t current_task = 0;

int main(void){
	enable_all_faults();
	init_scheduler_stack(STACK_SCHEDULER_START);

	task_handlers[0] = (uint32_t)task1_handler;
	task_handlers[1] = (uint32_t)task2_handler;
	task_handlers[2] = (uint32_t)task3_handler;
	task_handlers[3] = (uint32_t)task4_handler;

	init_tasks_stack();

	init_systick_timer(TICK_HZ);

	switch_sp_to_psp();

	task1_handler();

	for(;;);
}

void task1_handler(void){
	while(1){
		printf("TASK1 \n");
	}
}

void task2_handler(void){
	while(1){
		printf("TASK2 \n");
	}
}

void task3_handler(void){
	while(1){
		printf("TASK3 \n");
	}
}

void task4_handler(void){
	while(1){
		printf("TASK4 \n");
	}
}

uint32_t get_psp_value(void){
	return psp_of_tasks[current_task];
}

void update_next_task(void){
	current_task++;
	current_task %= MAX_TASKS;
}

void save_psp_value(uint32_t current_stack_addr){
		psp_of_tasks[current_task] = current_stack_addr;
}

__attribute__((naked)) void switch_sp_to_psp(void){
	__asm volatile("PUSH {LR}");
	__asm volatile("BL get_psp_value");
	__asm volatile("MSR PSP,R0");
	__asm volatile("POP {LR}");

	__asm volatile("MOV R0,#0x02");
	__asm volatile("MSR CONTROL,R0");
	__asm volatile("BX LR");
}




__attribute__((naked)) void SysTick_Handler(void){
	__asm volatile("PUSH {LR}"); // to return from that because when we bl lr is changing
	__asm volatile("MRS R0,PSP");
	__asm volatile("STMDB R0!,{R4-R11}");
	__asm volatile("BL save_psp_value");

	__asm volatile("BL update_next_task");
	__asm volatile("BL get_psp_value");
	__asm volatile("LDMIA R0!,{R4-R11}");
	__asm volatile("MSR PSP,R0");
	__asm volatile("POP {LR}");
	__asm volatile("BX LR");

 //write and debug here
}

void init_tasks_stack(void){
	uint32_t*pPSP;
	for(int i=0;i<MAX_TASKS; i++){
		pPSP=(uint32_t*)psp_of_tasks[i];

		pPSP--;
		*pPSP = DUMMY_XPSR;

		pPSP--;
		*pPSP = task_handlers[i];

		pPSP--;
		*pPSP = LR_EXC_RET;

		for(int j=0; j<13; j++){
			pPSP--;
			*pPSP = 0;
		}

		psp_of_tasks[i] = (uint32_t)pPSP;
	}
}
void init_systick_timer(uint32_t tick_hz){
	uint32_t *pSRVR = (uint32_t*)0xE000E014;
	uint32_t *pSCSR = (uint32_t*)0xE000E010;

	uint32_t count_value = PROCESSOR_CLOCK_FREQUENCY/tick_hz;

	*pSRVR &= ~(0x00FFFFFF);

	*pSRVR |= count_value;

	*pSCSR |= (1<<1);

	*pSCSR |= (1<<2);

	*pSCSR |= (1<<0);

}

__attribute__((naked)) void init_scheduler_stack(uint32_t start_address){
	__asm volatile("MSR MSP,%0"::"r"(start_address));
	__asm volatile("BX LR");
}

void HardFault_Handler(void){
	printf("Exception: Hardfault \n");
//	while(1);1
}

void MemManage_Handler(void){
	printf("Exception: MemManage \n");
//	while(1);
}

void BusFault_Handler(void){
	printf("Exception: BusFault \n");
//	while(1);
}
