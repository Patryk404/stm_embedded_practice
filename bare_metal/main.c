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
#include "led.h"

void init_systick_timer(uint32_t tick_hz);
__attribute__((naked)) void init_scheduler_stack(uint32_t start_address);
void init_tasks_stack(void);
__attribute__((naked)) void switch_sp_to_psp(void);
void enable_all_faults(void){
	uint32_t *shcrs = (uint32_t*)0xE000ED24;
	*shcrs = (1<<18) | (1<<17) | (1<<16); // enabling usgfault busfault and memfault
}
void task_delay(uint32_t tick_count);

void task1_handler(void);
void task2_handler(void);
void task3_handler(void);
void task4_handler(void);

uint8_t current_task = 1; //task1 is running
uint32_t g_tick_count = 0;

const uint32_t constv1_elo = 100; 
const uint32_t constv2_elo = 200;
const uint8_t constv3_elo = 100;

typedef struct
{
	uint32_t psp_value;
	uint32_t block_count;
	uint8_t current_state;
	void (*task_handler)(void);
}TCB_t;

TCB_t user_tasks[MAX_TASKS];

int main(void){
	enable_all_faults();

	init_scheduler_stack(STACK_SCHEDULER_START);

	init_tasks_stack();

	init_systick_timer(TICK_HZ);

	switch_sp_to_psp();

	led_init();

	task1_handler();

	for(;;);
}

void idle_task(void){
	while(1);
}

void task1_handler(void){
	while(1){
		led_on();
		task_delay(1000);
		led_off();
		task_delay(1000);
	}
}

void task2_handler(void){
	while(1){
		led_on();
		task_delay(500);
		led_off();
		task_delay(500);
	}
}

void task3_handler(void){
	while(1){
		led_on();
		task_delay(250);
		led_off();
		task_delay(250);
	}
}

void task4_handler(void){
	while(1){
		led_on();
		task_delay(125);
		led_off();
		task_delay(125);
	}
}

uint32_t get_psp_value(void){
	return user_tasks[current_task].psp_value;
}

void update_next_task(void){
	int state = TASK_BLOCKING_STATE; // algorithm to switch to next task

	for(int i=0; i<MAX_TASKS; i++){
		current_task++;
		current_task %= MAX_TASKS;
		state = user_tasks[current_task].current_state;
		if((state == TASK_READY_STATE) && (current_task!=0)){
			break;
		}
	}
	if(state != TASK_READY_STATE){ // if all tasks are in blocked state go to idle function
		current_task = 0; //idle function
	}
}

void save_psp_value(uint32_t current_stack_addr){
		user_tasks[current_task].psp_value = current_stack_addr;
//		psp_of_tasks[current_task] = current_stack_addr;
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


__attribute__((naked))void PendSV_Handler(void){ // switch to next task
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
}

void unblock_tasks(void){
	for(int i=1; i< MAX_TASKS;i++){ // we dont need to check idle task
		if(user_tasks[i].current_state != TASK_READY_STATE){
			if(user_tasks[i].block_count == g_tick_count){
				user_tasks[i].current_state = TASK_READY_STATE; // change if task are ready to fire
			}
		}
	}
}

void update_global_tick_count(void){
	g_tick_count++;
}


__attribute__((naked)) void SysTick_Handler(void){
	__asm volatile("PUSH {LR}");
	uint32_t* pICSR = (uint32_t*)0xE000ED04;
	update_global_tick_count();
	unblock_tasks();
	*pICSR |= (1<<28); // PEND PENDSV_EXCEPTION
	__asm volatile("POP {LR}");
	__asm volatile("BX LR");
}

void init_tasks_stack(void){
	user_tasks[0].current_state = TASK_READY_STATE;
	user_tasks[1].current_state = TASK_READY_STATE;
	user_tasks[2].current_state = TASK_READY_STATE;
	user_tasks[3].current_state = TASK_READY_STATE;
	user_tasks[4].current_state = TASK_READY_STATE;


	user_tasks[0].psp_value = IDLE_STACK_START;
	user_tasks[1].psp_value = STACK_TASK1_START;
	user_tasks[2].psp_value = STACK_TASK2_START;
	user_tasks[3].psp_value = STACK_TASK3_START;
	user_tasks[4].psp_value = STACK_TASK4_START;

	user_tasks[0].task_handler = idle_task;
	user_tasks[1].task_handler = task1_handler;
	user_tasks[2].task_handler = task2_handler;
	user_tasks[3].task_handler = task3_handler;
	user_tasks[4].task_handler = task4_handler;


	uint32_t*pPSP;
	for(int i=0;i<MAX_TASKS; i++){
		pPSP=(uint32_t*)user_tasks[i].psp_value;

		pPSP--;
		*pPSP = DUMMY_XPSR;

		pPSP--;
		*pPSP =(uint32_t) user_tasks[i].task_handler;

		pPSP--;
		*pPSP = LR_EXC_RET;

		for(int j=0; j<13; j++){
			pPSP--;
			*pPSP = 0;
		}

		user_tasks[i].psp_value = (uint32_t)pPSP;
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

void schedule(void){
	uint32_t* pICSR = (uint32_t*)0xE000ED04;
	*pICSR |= (1<<28); // PEND PENDSV_EXCEPTION
}

#define INTERRUPT_DISABLE() do{ __asm volatile("MOV R0,#0x1"); __asm volatile("MSR PRIMASK,R0");} while(0);

#define INTERRUPT_ENABLE()  do{ __asm volatile("MOV R0,#0x0"); __asm volatile("MSR PRIMASK,R0");} while(0);

void task_delay(uint32_t tick_count){
	INTERRUPT_DISABLE(); //  it is secure
	if(current_task){
		user_tasks[current_task].block_count = g_tick_count + tick_count;
		user_tasks[current_task].current_state = TASK_BLOCKING_STATE;
		schedule();
	}
	INTERRUPT_ENABLE();
}

void HardFault_Handler(void){
	// printf("Exception: Hardfault \n");
	while(1);
}

void MemManage_Handler(void){
	// printf("Exception: MemManage \n");
	while(1);
}

void BusFault_Handler(void){
	// printf("Exception: BusFault \n");
	while(1);
}
