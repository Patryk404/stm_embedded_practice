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
// TIM2
// I2C1 event


#define TIM2 28
#define I2C1_EV 31

uint32_t *pNVIC_IPRBase = (uint32_t*)0xE000E400;
uint32_t *pNVIC_ISERBase = (uint32_t*)0xE000E100;
uint32_t *pNVIC_ISPRBase = (uint32_t*)0xE000E200;

void configure_priority_for_irqs(uint8_t irq_no, uint8_t priority_value)
{
	uint8_t iprx = irq_no/4;
	uint32_t *ipr = pNVIC_IPRBase+iprx;
	uint8_t pos = (irq_no % 4) * 8; // offset calculation

	*ipr &= ~(0xFF << pos); // clear
	*ipr |= (priority_value << pos);
}

void set_pending_irq(uint8_t irq_no);

void set_enable_irq(uint8_t irq_no);

int main(void)
{
	configure_priority_for_irqs(TIM2,0x80);
 	configure_priority_for_irqs(I2C1_EV,0x70);

	// setting pending registers

	set_pending_irq(TIM2);
	set_pending_irq(I2C1_EV);

	// setting enable registers

	set_enable_irq(TIM2);


    /* Loop forever */
	for(;;);
}

void TIM2_IRQHandler(){
	printf("TIM2 HANDLING LOL");
	set_enable_irq(I2C1_EV); // priority higher so it will invoke
	// if priority the same it won't fire
	while(1);
}

void I2C1_EV_EXTI23_IRQHandler(){
	printf("I2C1_EV");
}

void set_pending_irq(uint8_t irq_no){
	uint8_t bytes_offset = irq_no/32;

	uint32_t *pNVIC_ISPR = pNVIC_ISPRBase + bytes_offset;
	*pNVIC_ISPR = (uint32_t*)(1<<(irq_no%32));
}

void set_enable_irq(uint8_t irq_no){
	uint8_t bytes_offset = irq_no/32;
	uint32_t *pNVIC_ISER = pNVIC_ISERBase + bytes_offset;

	*pNVIC_ISER = (uint32_t*)(1<<(irq_no%32));
}
