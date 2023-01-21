/****************************************Copyright (c)****************************************************
**
**                                 http://www.powermcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               main.c
** Descriptions:            The GLCD application function
**
**--------------------------------------------------------------------------------------------------------
** Created by:              AVRman
** Created date:            2010-11-7
** Version:                 v1.0
** Descriptions:            The original version
**
**--------------------------------------------------------------------------------------------------------
** Modified by:             Paolo Bernardi
** Modified date:           03/01/2020
** Version:                 v2.0
** Descriptions:            basic program for LCD and Touch Panel teaching
**
*********************************************************************************************************/

/* Includes ------------------------------------------------------------------*/

#include <stdio.h>
#include "LPC17xx.h"

#include "GLCD/GLCD.h"
#include "timer/timer.h"
#include "Support/support.h"

#include "joystick/joystick.h"
#include "RIT/RIT.h"

#include "TouchPanel/TouchPanel.h"

#define SIMULATOR 1

#ifdef SIMULATOR
extern uint8_t ScaleFlag; // <- ScaleFlag needs to visible in order for the emulator to find the symbol (can be placed also inside system_LPC17xx.h but since it is RO, it needs more work)
#endif


int disegno = 0;

volatile int update = 0;
volatile int removeBar = 0;
extern int current_happiness;
extern int current_satiety;
extern int end;



extern int hours, minutes, seconds;
int oldHours, oldMinutes;
extern int select, left, right;
extern int snack;
extern int cuddles;


void update_time(void);
void update_status_bar(void);
void startGame(void);
void moveSnack(void);

int main(void)
     {
	SystemInit();	 /* System Initialization (i.e., PLL)  */
	joystick_init(); /* Joystick Initialization            */
	LCD_Initialization();
	TP_Init();
	TouchPanel_Calibrate();
	startGame();

	while (1)
	{
		if(cuddles == 1){
			LCD_DrawCircle(70, 170, 3, Red);
			LCD_DrawCircle(115, 215, 3, Red);
			LCD_DrawCircle(80, 150, 3, Red);
			LCD_DrawCircle(30, 200, 3, Red);
			LCD_DrawCircle(200, 130, 3, Red);
			LCD_DrawCircle(170, 150, 3, Red);
			GUI_Text(100, 110, (uint8_t *) "Cuddles",Black, White);
		}
		if(cuddles == 3){
			GUI_Text(100, 110, (uint8_t *) "                    ",Black, White);
			LCD_DrawCircle(70, 170, 3, White);
			LCD_DrawCircle(115, 215, 3, White);
			LCD_DrawCircle(80, 150, 3, White);
			LCD_DrawCircle(30, 200, 3, White);
			LCD_DrawCircle(200, 130, 3, White);
			LCD_DrawCircle(170, 150, 3, White);
			battery_management(0,current_happiness+1,1);
			cuddles = 0;
		//Stop cuddles
		//Edit animation
		//Increment bar
		}
		if(update == 1 && end == 0 && snack == 0){
			update = ~update;
			update_time();
			if(disegno == 1){
				LCD_DrawLine(110, 190,110,195, White); //accorcio gamba
				LCD_DrawLine(130, 180,130,195, Black); //allungo gamba
				disegno = 0;
			}
			else{
				LCD_DrawLine(130, 190,130,195, White); //accorcio gamba
				LCD_DrawLine(110, 180,110,195, Black); //allungo gamba
				disegno = 1;
			}
		}
		if(removeBar == 1 && end == 0 && snack == 0){
		removeBar = ~removeBar;	
		update_time();
		battery_management(0, current_happiness, 0);
		battery_management(1, current_satiety, 0);
		}
		
		if(left == 1 && end == 0 && snack == 0){
		left = 2;
		update_time();
		draw_rectangle(180, 295, 50, 120, Black);
		draw_rectangle(60, 295, 50, 120, Red);
		}
		if(right == 1&& end == 0 && snack == 0){
		right = 2;
		update_time();
		draw_rectangle(60, 295, 50, 120, Black);
		draw_rectangle(180, 295, 50, 120, Red);
		}
		if(right == 2 && select == 1 && end == 0 && snack == 0){
			draw_rectangle(180, 295, 50, 120, Black);
			right = 0;
			select = 0;
			snack = 1;
			LCD_DrawCircle(220, 200, 10, Green);
			battery_management(0,current_happiness+1,1);
			moveSnack();
			//Meal
		}
		if(left == 2 && select == 1 && end == 0 && snack == 0){
			draw_rectangle(60, 295, 50, 120, Black);
			left = 0,
			select = 0;
			snack = 1;
			draw_rectangle_full(220, 200, 20, 20, Red);
			battery_management(1,current_satiety+1,1);
			moveSnack();
			//Snack
			
		}
		if(end == 0 && snack == 2){
		update_time();
		}
		if(end == 0 && snack == 3){
		snack = 0;
		update_time();
		draw_rectangle_full(220, 200, 20, 20, White);
		LCD_DrawCircle(220, 200, 10, White);
		draw_rectangle(20,200,20,20,White);
		LCD_DrawCircle(160, 170, 6, White);
		draw_rectangle(170,150,5,5,White); //occhio
		draw_rectangle(150,150,5,5,White); //occhio
		draw_rectangle(160,160,40,40,White);
		LCD_DrawLine(170, 180,170,190, White); //accorcio gamba	
		LCD_DrawLine(170, 190,170,195, White); //accorcio gamba
		LCD_DrawLine(150, 180,150,195, White); //allungo gamba

			
			
		draw_rectangle(130,150,5,5,Black); //occhio
		draw_rectangle(110,150,5,5,Black); //occhio
		draw_rectangle(120,160,40,40,Black);
		LCD_DrawLine(130, 180,130,190, Black); //accorcio gamba
		
		LCD_DrawLine(130, 190,130,195, White); //accorcio gamba
		LCD_DrawLine(110, 180,110,195, Black); //allungo gamba	
		}
 		if(end == 1 && snack == 0){
			end = 2;
			disable_timer(0);
			draw_rectangle(130,150,5,5,White); //occhio
			draw_rectangle(110,150,5,5,White); //occhio
			draw_rectangle(120,160,40,40,White);
			LCD_DrawLine(130, 180,130,195, White); //accorcio gamba
			LCD_DrawLine(110, 180,110,195, White); //allungo gamba
			
			draw_rectangle(100,150,5,5,Black); //occhio
			draw_rectangle(80,150,5,5,Black); //occhio
			draw_rectangle(90,160,40,40,Black);
			LCD_DrawLine(100, 180,100,195, Black); //accorcio gamba
			LCD_DrawLine(80, 180,80,190, Black); //allungo gamba
			
			draw_rectangle(100,150,5,5,White); //occhio
			draw_rectangle(80,150,5,5,White); //occhio
			draw_rectangle(90,160,40,40,White);
			LCD_DrawLine(100, 180,100,195, White); //accorcio gamba
			LCD_DrawLine(80, 180,80,190, White); //allungo gamba
			
			draw_rectangle(50,150,5,5,Black); //occhio
			draw_rectangle(30,150,5,5,Black); //occhio
			draw_rectangle(40,160,40,40,Black);
			LCD_DrawLine(50, 180,50,195, Black); //accorcio gamba
			LCD_DrawLine(30, 180,30,190, Black); //allungo gamba
			
			draw_rectangle(50,150,5,5,White); //occhio
			draw_rectangle(30,150,5,5,White); //occhio
			draw_rectangle(40,160,40,40,White);
			LCD_DrawLine(50, 180,50,195, White); //accorcio gamba
			LCD_DrawLine(30, 180,30,190, White); //allungo gamba
			
			
			draw_rectangle(60, 295, 50, 120, White);
			GUI_Text(60,295,(uint8_t *)"       ",Black,White);
			draw_rectangle(180, 295, 50, 120, White);
			GUI_Text(180,295,(uint8_t *)"      ",Black,White);
			
			GUI_Text(105, 160, (uint8_t *) "FAILED!!",Black, White);
			draw_rectangle(120, 295, 50, 320, Red);
			GUI_Text(110, 295, (uint8_t *) "Reset",Black, White);
		}
		if(end == 2 && select == 1 && snack == 0){
		select = ~select;
		end = 0;
		startGame();
		}
	}
}


void moveSnack(void){
		draw_rectangle(130,150,5,5,White); //occhio
		draw_rectangle(110,150,5,5,White); //occhio
		draw_rectangle(120,160,40,40,White);
		LCD_DrawLine(130, 180,130,195, White); //accorcio gamba
		LCD_DrawLine(110, 180,110,195, White); //allungo gamba
			
			
		draw_rectangle(170,150,5,5,Black); //occhio
		draw_rectangle(150,150,5,5,Black); //occhio
		draw_rectangle(160,160,40,40,Black);
		LCD_DrawLine(170, 180,170,190, Black); //accorcio gamba
		LCD_DrawLine(170, 190,170,195, White); //accorcio gamba
		LCD_DrawLine(150, 180,150,195, Black); //allungo gamba
		LCD_DrawCircle(160, 170, 6, Black);
}


void startGame(void){
	LCD_Clear(White);
	oldHours = oldMinutes = hours = minutes = seconds = current_happiness = current_satiety =0;
	draw_rectangle(130,150,5,5,Black); //occhio
	draw_rectangle(110,150,5,5,Black); //occhio
	draw_rectangle(120,160,40,40,Black);
	
	
	//draw_rectangle(120,165,100,100,Red);
	
	LCD_DrawLine(130, 180,130,190, Black); //accorcio gamba
	
	LCD_DrawLine(130, 190,130,195, White); //accorcio gamba
	LCD_DrawLine(110, 180,110,195, Black); //allungo gamba
	
	//Create playground
	//Time
	GUI_Text(60, 0, (uint8_t *)" Age:  :  :  ", Black, White);
	GUI_Text(100, 0, (uint8_t *)"00", Black, White);
	GUI_Text(125, 0, (uint8_t *)"00", Black, White);
	GUI_Text(150, 0, (uint8_t *)"00", Black, White);
	//Button
	draw_rectangle(60, 295, 50, 120, Black);
	GUI_Text(60,295,(uint8_t *)"Snack",Black,White);
	draw_rectangle(180, 295, 50, 120, Black);
	GUI_Text(180,295,(uint8_t *)"Meal",Black,White);
	//Batteries
	GUI_Text(143, 25, (uint8_t *) "Satiety",Black, White);
	draw_rectangle(61,57,30,100,Black);
	GUI_Text(23, 25, (uint8_t *) "Happiness",Black, White);
	draw_rectangle(182,57,30,100,Black);
	battery_management(2,0,1);
	
	init_RIT(0x004C4B40); /* RIT Initialization 50 msec       */

	enable_RIT(); /* enable RIT to count 50ms				 */

	init_timer(0, 0, 0, 3, 0x017D7840); // 1 secondo
	enable_timer(0);
	init_timer(2, 0, 0, 3, 0x1312D0); // 50 ms
	enable_timer(2);
}


void update_time(void)
{
	char a[200];
	if(oldHours != hours){
		sprintf(a, "%02d", hours);
		GUI_Text(100, 0, (uint8_t *)a, Black, White);
		oldHours = hours;
	}
	
	if(oldMinutes != minutes){
		sprintf(a, "%02d", minutes);
		GUI_Text(125, 0, (uint8_t *)a, Black, White);
		oldMinutes = minutes;
	}
	
	sprintf(a, "%02d", seconds);
	GUI_Text(150, 0, (uint8_t *)a, Black, White);
}
/*********************************************************************************************************
	  END FILE
*********************************************************************************************************/
