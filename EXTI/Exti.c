/*
    manar ashraf sec 2
    salema abdeltwab  sec 1
    ExtI.c
*/


#include "Nvic.h"

#include "Bit_Operations.h"
#include "Rcc_Private.h"
#include "Rcc.h"
#include "Std_Types.h"
#include "Gpio.h"

#define NVIC_ISER0 (*(uint32 *)(0xE000E100 + (0x04 * 0)))
#define NVIC_ISER1 (*(uint32 *)(0xE000E100 + (0x04 * 1)))
#define NVIC_ISER2 (*(uint32 *)(0xE000E100 + (0x04 * 2)))

#define NVIC_ICER0 (*(uint32 *)0xE000E180)
#define NVIC_ICER1 (*(uint32 *)0xE000E184)
#define NVIC_ICER2 (*(uint32 *)0xE000E188)

// SYSCFG base address
#define SYSCFG_BASE_ADDR 0x40013800

// SYSCFG register offsets
#define SYSCFG_EXTICR1 (*(uint32 *)(SYSCFG_BASE_ADDR + 0x08))
#define SYSCFG_EXTICR2 (*(uint32 *)(SYSCFG_BASE_ADDR + 0x0C))
#define SYSCFG_EXTICR3 (*(uint32 *)(SYSCFG_BASE_ADDR + 0x10))
#define SYSCFG_EXTICR4 (*(uint32 *)(SYSCFG_BASE_ADDR + 0x14))

// EXTI base address
#define EXTI_BASE_ADDR 0x40013C00



void Exti_Init( uint8 GPIO_PORT,uint32 pinNumber, uint32 trigger_edgeDetection){
    Gpio_ConfigPin(GPIO_PORT , pinNumber ,  GPIO_INPUT, GPIO_PULL_UP); // sit pin  as input 

// type of triger 

    // falling edge dectection
    if(trigger_edgeDetection==EXTI_Trigger_Falling){

            EXTI->FTSR &= ~(1 << (pinNumber));
            EXTI->FTSR |=  (1 << (pinNumber));
     
    }
    // Rissing adge detection
    else if (trigger_edgeDetection==EXTI_Trigger_Rising){
        EXTI->RTSR &= ~(1 << (pinNumber));
        EXTI->RTSR |=  (1 << (pinNumber));
        
    }
    // Rissing and falling adge detection
    else if(trigger_edgeDetection==EXTI_Trigger_Rising_And_Falling){   
        EXTI->FTSR &= ~(1 << (pinNumber));
        EXTI->FTSR |=  (1 << (pinNumber));
        EXTI->RTSR &= ~(1 << (pinNumber));
        EXTI->RTSR |=  (1 << (pinNumber));

    }



/*  line of nivc 
    NVIC_EXTI_Line_9_5 = 23,
	NVIC_EXTI_Line_15_10 = 40,
*/
    // this nvic for exti's pins from 0-4

    if(pinNumber<5 ){

            NVIC_ISER0 &= ~(1 << (6+pinNumber));  // clear  NVIC_ISER0
            NVIC_ISER0 |=  (1 << (6+pinNumber)); // set NVIC_ISER0 
    }


// this nvic for exti's pins from 5-9
    else if(pinNumber>4 && pinNumber <10){
     //STM32F4, EXTI9_5_IRQn is IRQ number 23.
            NVIC_ISER0 &= ~(1 << (23));  // clear  NVIC_ISER0
            NVIC_ISER0 |=  (1 << (23)); // set NVIC_ISER0 

    }

// this nvic for exti's pins
    else if(pinNumber>9 && pinNumber <16){
            NVIC_ISER0 &= ~(1 << (40));  // clear  NVIC_ISER0
            NVIC_ISER0 |=  (1 << (40)); // set NVIC_ISER0 
    }






/*SYSCOFG  */
    // 1-3 pin number -->  4-7  --> 8-11 --> 12-15
    // Configure EXTI line
    uint32 extiPinSource = pinNumber % 4;
    uint8 extiPortSource = pinNumber / 4;
    uint8 port_num = GPIO_PORT-GPIO_A;

    switch (extiPortSource) {
           case 0:
        	   SYSCFG_EXTICR1 &=~(0x0f<<(extiPinSource *4));
        	   SYSCFG_EXTICR1 |=(port_num<<(extiPinSource *4));
               break;
           case 1:
        	   SYSCFG_EXTICR2 &=~(0x0f<<(extiPinSource *4));
        	   SYSCFG_EXTICR2 |=(port_num<<(extiPinSource *4));
               break;
           case 2:
        	   SYSCFG_EXTICR3 &=~(0x0f<<(extiPinSource *4));
        	   SYSCFG_EXTICR3 |=(port_num<<(extiPinSource *4));

               break;
           case 3:
        	   SYSCFG_EXTICR4 &=~(0x0f<<(extiPinSource *4));
        	   SYSCFG_EXTICR4 |=(port_num<<(extiPinSource *4));
               break;
    }

}

// enable specific EXTI line 
void Exti_Enable(uint32 Exti_line){
    EXTI->IMR &= ~(1 << (Exti_line));
    EXTI->IMR|=  (1 << (Exti_line));

}

// disable specific EXTI line
void Exti_Disable(uint32 Exti_line) {
    EXTI->IMR &= ~(1 << (Exti_line));
}







