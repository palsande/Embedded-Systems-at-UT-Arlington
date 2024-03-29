/*
 * SysTickInterrupt.c
 *
 *  Created on: Jul 27, 2015
 *      Author: Sandeep
 */
#include <stdint.h>
#include <stdbool.h>
#include "tm4c123gh6pm.h"
#include "SysTickInterrupt.h"

void initSysTick(uint16_t period)
{
	  NVIC_ST_CTRL_R     = 0;         // disable SysTick during setup
	  NVIC_ST_RELOAD_R   = period-1;  // reload value
	  NVIC_ST_CURRENT_R  = 0;         // any write to current clears it
	  NVIC_SYS_PRI3_R    = (NVIC_SYS_PRI3_R&0x00FFFFFF)|0x40000000; // priority 2
	  NVIC_ST_CTRL_R     |= 0x07; // enable SysTick with core clock and interrupts
	  NVIC_EN0_R         |= 0x00008000;//Enable IRQ-15
}

