/**
 * Nvic.c
 *
 *  Created on: Mon May 13 2024
 *  Author    : Abdallah Darwish
 */

#include "Nvic.h"

#include "Bit_Operations.h"

#define NVIC_BASE (0xE000E100)

#define NVIC_ISER0 (*(uint32 *)(0xE000E100 + (0x04 * 0)))
#define NVIC_ISER1 (*(uint32 *)(0xE000E100 + (0x04 * 1)))
#define NVIC_ISER2 (*(uint32 *)(0xE000E100 + (0x04 * 2)))

#define NVIC_ICER0 (*(uint32 *)0xE000E180)
#define NVIC_ICER1 (*(uint32 *)0xE000E184)
#define NVIC_ICER2 (*(uint32 *)0xE000E188)

// Array of pointers to ISER registers
volatile uint32 *NVIC_ISER[] = {&NVIC_ISER0, &NVIC_ISER1, &NVIC_ISER2};

// Array of pointers to ICER registers
volatile uint32 *NVIC_ICER[] = {&NVIC_ICER0, &NVIC_ICER1, &NVIC_ICER2};

void Nvic_EnableInterrupt(uint8 IRQn) {
  // TODO: use arrays and pointers to remove this if else statement
  if (IRQn < 96) {

    uint8 register_index = IRQn / 32;
    uint8 bit_position = IRQn % 32;
    SET_BIT(*NVIC_ISER[register_index], bit_position);
    
    }
  // if (IRQn>=0 && IRQn < 32) {
  //   SET_BIT(NVIC_ISER0, IRQn);
  // } else if (IRQn >= 32 &&IRQn < 64) {
  //    SET_BIT(NVIC_ISER1, IRQn - 32);
  // } else if (IRQn >= 64 && IRQn < 96) {
  //   SET_BIT(NVIC_ISER2, IRQn - 64);
  // }
}

void Nvic_DisableInterrupt(uint8 IRQn) {
  // TODO: use arrays and pointers to remove this if else statement
  if (IRQn < 96) {
  
    uint8 register_index = IRQn / 32;
    uint8 bit_position = IRQn % 32;
    SET_BIT(*NVIC_ICER[register_index], bit_position);
  }
}
