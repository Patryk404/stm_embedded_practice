#include <stdint.h>
#define SRAM_START 0x20000000U
#define SRAM_SIZE (64 * 1024)
#define SRAM_END ((SRAM_START) + (SRAM_SIZE))

#define STACK_START SRAM_END 

void Reset_handler                  (void);
void NMI_handler                    (void) __attribute__ ((weak,alias("Default_Handler"))); // by giving weak attribut we are allowing programmer to override this function with same function name in main application. There programmer can implement real implementation of handling that exception
void HardFault_Handler              (void) __attribute__ ((weak,alias("Default_Handler")));
void MemManage_Handler 				(void) __attribute__ ((weak, alias("Default_Handler")));
void BusFault_Handler 				(void) __attribute__ ((weak, alias("Default_Handler")));
void UsageFault_Handler 			(void) __attribute__ ((weak, alias("Default_Handler")));
void SVC_Handler 					(void) __attribute__ ((weak, alias("Default_Handler")));
void DebugMon_Handler               (void) __attribute__ ((weak, alias("Default_Handler")));
void PendSV_Handler   				(void) __attribute__ ((weak, alias("Default_Handler")));
void SysTick_Handler  				(void) __attribute__ ((weak, alias("Default_Handler")));
void WWDG_IRQHandler 				(void) __attribute__ ((weak, alias("Default_Handler")));
void PVD_IRQHandler 				(void) __attribute__ ((weak, alias("Default_Handler")));             
void TAMP_STAMP_IRQHandler 			(void) __attribute__ ((weak, alias("Default_Handler")));      
void RTC_WKUP_IRQHandler 			(void) __attribute__ ((weak, alias("Default_Handler")));    
void FLASH_IRQHandler               (void) __attribute__ ((weak, alias("Default_Handler")));  
void RCC_IRQHandler 				(void) __attribute__ ((weak, alias("Default_Handler")));             
void EXTI0_IRQHandler 				(void) __attribute__ ((weak, alias("Default_Handler")));           
void EXTI1_IRQHandler 				(void) __attribute__ ((weak, alias("Default_Handler")));           
void EXTI2_IRQHandler 				(void) __attribute__ ((weak, alias("Default_Handler")));           
void EXTI3_IRQHandler 				(void) __attribute__ ((weak, alias("Default_Handler")));           
void EXTI4_IRQHandler 				(void) __attribute__ ((weak, alias("Default_Handler"))); 
void DMA1_Channel0_IRQHandler 		(void) __attribute__ ((weak, alias("Default_Handler")));    
void DMA1_Channel1_IRQHandler 		(void) __attribute__ ((weak, alias("Default_Handler")));    
void DMA1_Channel2_IRQHandler 		(void) __attribute__ ((weak, alias("Default_Handler")));    
void DMA1_Channel3_IRQHandler 		(void) __attribute__ ((weak, alias("Default_Handler")));    
void DMA1_Channel4_IRQHandler 		(void) __attribute__ ((weak, alias("Default_Handler")));    
void DMA1_Channel5_IRQHandler 		(void) __attribute__ ((weak, alias("Default_Handler")));    
void DMA1_Channel6_IRQHandler 		(void) __attribute__ ((weak, alias("Default_Handler")));  
void DMA1_Channel7_IRQHandler 		(void) __attribute__ ((weak, alias("Default_Handler")));    
void ADC1_2_IRQHandler 				(void) __attribute__ ((weak, alias("Default_Handler")));             
void USB_HP_CAN_TX_IRQHandler       (void) __attribute__ ((weak, alias("Default_Handler")));             
void USB_LP_CAN_RX0_IRQHandler      (void) __attribute__ ((weak, alias("Default_Handler")));             
void CAN_RX1_IRQHandler 			(void) __attribute__ ((weak, alias("Default_Handler")));        
void CAN_SCE_IRQHandler 			(void) __attribute__ ((weak, alias("Default_Handler")));        
void EXTI9_5_IRQHandler 			(void) __attribute__ ((weak, alias("Default_Handler")));         
void TIM1_BRK_TIM15_IRQHandler 		(void) __attribute__ ((weak, alias("Default_Handler")));   
void TIM1_UP_TIM16_IRQHandler 		(void) __attribute__ ((weak, alias("Default_Handler")));   
void TIM1_TRG_COM_TIM17_IRQHandler 	(void) __attribute__ ((weak, alias("Default_Handler")));
void TIM1_CC_IRQHandler 			(void) __attribute__ ((weak, alias("Default_Handler")));         
void TIM2_IRQHandler 				(void) __attribute__ ((weak, alias("Default_Handler")));            
void TIM3_IRQHandler 				(void) __attribute__ ((weak, alias("Default_Handler")));            
void TIM4_IRQHandler 				(void) __attribute__ ((weak, alias("Default_Handler")));            
void I2C1_EV_IRQHandler 			(void) __attribute__ ((weak, alias("Default_Handler")));         
void I2C1_ER_IRQHandler 			(void) __attribute__ ((weak, alias("Default_Handler")));         
void I2C2_EV_IRQHandler 			(void) __attribute__ ((weak, alias("Default_Handler")));         
void I2C2_ER_IRQHandler 			(void) __attribute__ ((weak, alias("Default_Handler")));         
void SPI1_IRQHandler  				(void) __attribute__ ((weak, alias("Default_Handler")));           
void SPI2_IRQHandler 				(void) __attribute__ ((weak, alias("Default_Handler")));            
void USART1_IRQHandler  			(void) __attribute__ ((weak, alias("Default_Handler")));         
void USART2_IRQHandler  			(void) __attribute__ ((weak, alias("Default_Handler")));        
void USART3_IRQHandler   			(void) __attribute__ ((weak, alias("Default_Handler")));        
void EXTI15_10_IRQHandler   		(void) __attribute__ ((weak, alias("Default_Handler")));     
void RTC_Alarm_IRQHandler    		(void) __attribute__ ((weak, alias("Default_Handler")));
void USB_wakeupIRQHandler           (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM8_BRK_IRQHandler            (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM8_UP_IRQHandler             (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM8_TRG_COM_IRQHandler        (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM8_CC_IRQHandler             (void) __attribute__ ((weak, alias("Default_Handler")));
void ADC3_IRQHandler                (void) __attribute__ ((weak, alias("Default_Handler")));
void FMC_IRQHandler                 (void) __attribute__ ((weak, alias("Default_Handler")));
void SPI3_IRQHandler             	(void) __attribute__ ((weak, alias("Default_Handler")));
void UART4_IRQHandler            	(void) __attribute__ ((weak, alias("Default_Handler")));
void UART5_IRQHandler            	(void) __attribute__ ((weak, alias("Default_Handler")));
void TIM6_DAC_IRQHandler         	(void) __attribute__ ((weak, alias("Default_Handler")));
void TIM7_IRQHandler             	(void) __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Channel1_IRQHandler     	(void) __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Channel2_IRQHandler     	(void) __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Channel3_IRQHandler     	(void) __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Channel4_IRQHandler     	(void) __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Channel5_IRQHandler     	(void) __attribute__ ((weak, alias("Default_Handler")));
void ADC4_IRQHandler                (void) __attribute__ ((weak, alias("Default_Handler")));
void COMP123_IRQHandler             (void) __attribute__ ((weak, alias("Default_Handler")));
void COMP456_IRQHandler             (void) __attribute__ ((weak, alias("Default_Handler")));
void COMP7_IRQHandler               (void) __attribute__ ((weak, alias("Default_Handler")));
void I2C3_EV_IRQHandler             (void) __attribute__ ((weak, alias("Default_Handler")));
void I2C3_ER_IRQHandler             (void) __attribute__ ((weak, alias("Default_Handler")));
void USB_HP_IRQHandler              (void) __attribute__ ((weak, alias("Default_Handler")));
void USB_LP_IRQHandler              (void) __attribute__ ((weak, alias("Default_Handler")));
void USB_WKUP_EXTI_IRQHandler       (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM20_BRK_IRQHandler           (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM20_UP_IRQHandler            (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM20_TRG_COM_IRQHandler       (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM20_CC_IRQHandler            (void) __attribute__ ((weak, alias("Default_Handler")));
void SPI4_IRQHandler                (void) __attribute__ ((weak, alias("Default_Handler")));

uint32_t vectors[] __attribute__((section (".isr_vector"))) = {
    STACK_START, 
    (uint32_t)Reset_handler,
    (uint32_t)NMI_handler,
    (uint32_t)HardFault_Handler,
    (uint32_t)MemManage_Handler,
    (uint32_t)BusFault_Handler,
    (uint32_t)UsageFault_Handler,
    0,
    0,
    0,
    0,
    (uint32_t)SVC_Handler,
    (uint32_t)DebugMon_Handler,
    0,
    (uint32_t)PendSV_Handler,
    (uint32_t)SysTick_Handler,
    (uint32_t)WWDG_IRQHandler,
    (uint32_t)PVD_IRQHandler,
    (uint32_t)TAMP_STAMP_IRQHandler,
    (uint32_t)RTC_WKUP_IRQHandler,
    (uint32_t)FLASH_IRQHandler,
    (uint32_t)RCC_IRQHandler,
    (uint32_t)EXTI0_IRQHandler,
    (uint32_t)EXTI1_IRQHandler, 
    (uint32_t)EXTI2_IRQHandler,
    (uint32_t)EXTI3_IRQHandler, 
    (uint32_t)EXTI4_IRQHandler,
    (uint32_t)DMA1_Channel1_IRQHandler,
    (uint32_t)DMA1_Channel2_IRQHandler,
    (uint32_t)DMA1_Channel3_IRQHandler,
    (uint32_t)DMA1_Channel4_IRQHandler,
    (uint32_t)DMA1_Channel5_IRQHandler,
    (uint32_t)DMA1_Channel6_IRQHandler,
    (uint32_t)DMA1_Channel7_IRQHandler,
    (uint32_t)ADC1_2_IRQHandler,
    (uint32_t)USB_HP_CAN_TX_IRQHandler,
    (uint32_t)USB_LP_CAN_RX0_IRQHandler, 
    (uint32_t)CAN_RX1_IRQHandler,
    (uint32_t)CAN_SCE_IRQHandler,
    (uint32_t)EXTI9_5_IRQHandler,
    (uint32_t)TIM1_BRK_TIM15_IRQHandler,
    (uint32_t)TIM1_UP_TIM16_IRQHandler,
    (uint32_t)TIM1_TRG_COM_TIM17_IRQHandler,
    (uint32_t)TIM1_CC_IRQHandler,
    (uint32_t)TIM2_IRQHandler,
    (uint32_t)TIM3_IRQHandler,
    (uint32_t)TIM4_IRQHandler,
    (uint32_t)I2C1_EV_IRQHandler,
    (uint32_t)I2C1_ER_IRQHandler,
    (uint32_t)I2C2_EV_IRQHandler,
    (uint32_t)I2C2_ER_IRQHandler,
    (uint32_t)SPI1_IRQHandler,
    (uint32_t)SPI2_IRQHandler, 
    (uint32_t)USART1_IRQHandler,    
    (uint32_t)USART2_IRQHandler,
    (uint32_t)USART3_IRQHandler,
    (uint32_t)EXTI15_10_IRQHandler,
    (uint32_t)RTC_Alarm_IRQHandler,
    (uint32_t)USB_WKUP_EXTI_IRQHandler,
    (uint32_t)TIM8_BRK_IRQHandler,
    (uint32_t)TIM8_UP_IRQHandler,
    (uint32_t)TIM8_TRG_COM_IRQHandler,
    (uint32_t)TIM8_CC_IRQHandler,
    (uint32_t)ADC3_IRQHandler,
    (uint32_t)FMC_IRQHandler,
    0,
    0,
    (uint32_t)SPI3_IRQHandler, 
    (uint32_t)UART4_IRQHandler,
    (uint32_t)UART5_IRQHandler,
    (uint32_t)TIM6_DAC_IRQHandler,
    (uint32_t)TIM7_IRQHandler,
    (uint32_t)DMA2_Channel1_IRQHandler, 
    (uint32_t)DMA2_Channel2_IRQHandler,
    (uint32_t)DMA2_Channel3_IRQHandler,
    (uint32_t)DMA2_Channel4_IRQHandler,
    (uint32_t)DMA2_Channel5_IRQHandler,
    (uint32_t)ADC4_IRQHandler,
    0,
    0,
    (uint32_t)COMP123_IRQHandler,
    (uint32_t)COMP456_IRQHandler,
    (uint32_t)COMP7_IRQHandler,
    0,
    0,
    0,
    0,
    0,
    (uint32_t)I2C3_EV_IRQHandler,
    (uint32_t)I2C3_ER_IRQHandler,
    (uint32_t)USB_HP_IRQHandler,
    (uint32_t)USB_LP_IRQHandler,
    (uint32_t)USB_WKUP_EXTI_IRQHandler,
    (uint32_t)TIM20_BRK_IRQHandler,
    (uint32_t)TIM20_UP_IRQHandler, 
    (uint32_t)TIM20_TRG_COM_IRQHandler,
    (uint32_t)TIM20_CC_IRQHandler,
    0,
    0,
    0,
    (uint32_t)SPI4_IRQHandler
};

void Default_Handler(void){ 
    while(1);
}

void Reset_handler(void){
    
}