/*
    manar ashraf sec 2
    salema abdeltwab  sec 1
    EXTI.h
*/

#ifndef NVIC_H
#define NVIC_H

#include "Std_Types.h"
#include "Gpio.h"

#define EXTI_Trigger_Rising  'R'
#define EXTI_Trigger_Falling  'F'
#define EXTI_Trigger_Rising_And_Falling  'B'

#define EXTI 	((ExtiType *)0x40013C00)
#define SYSCOFG  ((SYSCFGType *)0x40013800)
#define NVIC_ISERx_BASE_ADDRESS 0xE000E100		//Base address for NVIC ISERx Registers
#define NVIC_ISER ((NVIC_ISER_Index *)NVIC_ISERx_BASE_ADDRESS)


typedef struct {
	uint32 IMR;  // Interrupt mask register  // register after pandding flage
	uint32 EMR ;  // Event mask register
	uint32  RTSR ;  // Rising trigger selection register
	uint32 FTSR;	// Falling trigger selection register
	uint32 SWIER;	// Software interrupt event register
	uint32 PR;		// Pending register
} ExtiType;

typedef struct {
	uint32 MEMRMP;
	uint32 PMC;
	uint32 EXTICR1;
	uint32 EXTICR2;
	uint32 EXTICR3 ;
	uint32 EXTICR4;
	uint32 CMPCR;

}SYSCFGType;

typedef struct{
	uint32 ISER0;
	uint32 ISER1;
	uint32 ISER2;
}NVIC_ISER_Index;





void Exti_Init(uint8 GPIO_PORT , uint32 pinNumber, uint32 trigger_edgeDetection);
void Exti_Disable(uint32 Exti_line) ;
void Exti_Enable(uint32 Exti_line);





#endif /* NVIC_H */
