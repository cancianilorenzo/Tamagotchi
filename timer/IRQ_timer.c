/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_timer.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    timer.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include <string.h>
#include "lpc17xx.h"
#include "timer.h"
#include "../GLCD/GLCD.h"
#include "../TouchPanel/TouchPanel.h"


/******************************************************************************
** Function name:		Timer0_IRQHandler
**
** Descriptions:		Timer/Counter 0 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
volatile int seconds = 0;
volatile int minutes = 0;
volatile int hours = 0;

volatile int snack = 0;

extern int update;
extern int removeBar;

volatile int cuddles = 0;


int clear = 0;

void TIMER0_IRQHandler(void)
{

	// Match register 0 interrupt service routine
	if (LPC_TIM0->IR & 01)
	{

		if (seconds == 59)
		{
			seconds = 0;

			if (minutes > 59)
			{
				minutes = 0;

				hours++;
			}
			minutes++;
		}
		if(((seconds+1) % 5) == 0){
			removeBar = 1;
		}
		if(snack == 3){
		snack = 0;
		}
		if(snack == 2){
		snack++;
		}
		if(snack == 1){
		snack++;
		}
		if(cuddles == 1 || cuddles == 2){
		cuddles++;
		}
		seconds++;
		update = 1;

		LPC_TIM0->IR = 1; /* clear interrupt flag */
	}

	return;
}

/******************************************************************************
** Function name:		Timer1_IRQHandler
**
** Descriptions:		Timer/Counter 1 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
void TIMER2_IRQHandler(void)
{
	
	//Match register 0
	if (LPC_TIM2->IR & 01){
	if(getDisplayPoint(&display, Read_Ads7846(), &matrix )){
		if((display.x < 170 && display.x > 70) && (display.y < 215 && display.y > 115)){
			cuddles = 1;
			//TP_DrawPoint(display.x,display.y);
			//draw_rectangle_full(100, 100, 100, 100, 100);
			}
		}
	}
	LPC_TIM2->IR = 1; /* clear interrupt flag */
	return;
}

/******************************************************************************
** Function name:		Timer2_IRQHandler
**
** Descriptions:		Timer/Counter 2 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
//void TIMER2_IRQHandler(void)
//{

	// matchreg0
	//if (LPC_TIM2->IR == 1)
	//{

		//LPC_TIM2->IR = 1; /* clear interrupt flag */
	//}
	/* Match register 1 interrupt service routine */
	//else if (LPC_TIM2->IR == 2)
	//{

		//LPC_TIM2->IR = 2; /* clear interrupt flag */
	//}

	//return;
//}

/******************************************************************************
**                            End Of File
******************************************************************************/
