/*
 * main.c
 */

#include <stdint.h>
#include <stdbool.h>
#include "tm4c123gh6pm.h"
#include "initPortF.h"
#include "initInterrupt.h"
#include "SysTickInterrupt.h"

//Push button defined on PF4
#define PUSH_BUTTON  (*((volatile uint32_t *)(0x42000000 + (0x400253FC-0x40000000)*32 + 4*4)))
//Red LED defined on PF1
#define RED_LED      (*((volatile uint32_t *)(0x42000000 + (0x400253FC-0x40000000)*32 + 1*4)))

volatile unsigned long Counts=0;

//Wait for input from user on PF4
void waitPbPress()
{
    while(PUSH_BUTTON);
}

void GPIOPortF_handler()
{

	if(GPIO_PORTF_RIS_R & 0x10)
	{
		GPIO_PORTF_ICR_R |= 0x10;// clear any priority interrupt
		//int i;
		//for(i=0;i<=3;i++)
		//{
		   RED_LED ^= 1;//Toggle RED LED
		//}
	}
	else
	{
		RED_LED = 1;//Glow RED LED
	}

}

void SysTick_Handler(void)
{
  GPIO_PORTF_DATA_R ^= 0x02;       // toggle PF1
  Counts = Counts + 1;
}

int main(void)
{
	
	// Configure HW to work with 16 MHz XTAL, PLL enabled, system clock of 40 MHz
	SYSCTL_RCC_R = SYSCTL_RCC_USESYSDIV|SYSCTL_RCC_XTAL_16MHZ|SYSCTL_RCC_OSCSRC_MAIN|(4 << SYSCTL_RCC_SYSDIV_S);

	// Set GPIO ports to use APB (not needed since default configuration -- for clarity)
	// Note UART on port A must use APB
    SYSCTL_GPIOHBCTL_R  = 0;//use of APB bus
    initPortF();//Initialize GPIO
    //initInterrupt();//Initialize Interrupt
    initSysTick(40000);//Initialize SysTick Interrupt
    //waitPbPress();
    while(1)
    {


    }

}
