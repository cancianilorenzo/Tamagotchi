/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_RIT.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    RIT.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "lpc17xx.h"
#include "RIT.h"
#include "../GLCD/GLCD.h"

#include "../joystick/joystick.h"
#include "../timer/timer.h"

#include "../TouchPanel/TouchPanel.h"

/******************************************************************************
** Function name:		RIT_IRQHandler
**
** Descriptions:		REPETITIVE INTERRUPT TIMER handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/

extern int end;

extern int seconds, hours, minutes;

volatile int select, left, right;
volatile int left = 0;
volatile int right = 0;



void RIT_IRQHandler(void)
{

	if ((LPC_GPIO1->FIOPIN & (1 << 25)) == 0)
	{ // select
		select = 1;
	}

	if ((LPC_GPIO1->FIOPIN & (1 << 27)) == 0)
	{ // left

		left = 1;
		right = 0;
	}

	if ((LPC_GPIO1->FIOPIN & (1 << 28)) == 0)
	{ // right
		right = 1;
		left = 0;
	}
	
	/*if(getDisplayPoint(&display, Read_Ads7846(), &matrix )){
	if(display.y < 280){
		cuddles = 1;
		}
	}*/

	reset_RIT();
	LPC_RIT->RICTRL |= 0x1; /* clear interrupt flag */

	return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
