#include "support.h"
#include "LPC17xx.h"
#include "../GLCD/GLCD.h"


int current_satiety = 0;
int current_happiness = 0;
int end = 0;

void battery_management(int bar, int pos, int action){
	
	int lenght=16;
	int height=26;
	
	if(bar == 0){
	//Happiness
		switch(pos){
			case 1:
				if(action == 1){
					draw_rectangle_full(21, 57, height, lenght, Black);
					if(current_happiness < 5){
					current_happiness++;
					}
					}
				else{
					draw_rectangle_full(21, 57, height, lenght, White);
					current_happiness--;}
					break;
			case 2:
				if(action == 1){
					draw_rectangle_full(41, 57, height, lenght, Black);
										if(current_happiness < 5){
					current_happiness++;
					}}
				else{
					draw_rectangle_full(41, 57, height, lenght, White);
					current_happiness--;}
					break;
			case 3:
				if(action == 1){
					draw_rectangle_full(61, 57, height, lenght, Black);
										if(current_happiness < 5){
					current_happiness++;
					}}
				else{
					draw_rectangle_full(61, 57, height, lenght, White);
					current_happiness--;}
					break;
			case 4:
				if(action == 1){
					draw_rectangle_full(81, 57, height, lenght, Black);
										if(current_happiness < 5){
					current_happiness++;
					}}
				else{
					draw_rectangle_full(81, 57, height, lenght, White);
					current_happiness--;}
					break;
			case 5:
				if(action == 1){
					draw_rectangle_full(101, 57, height, lenght, Black);
										if(current_happiness < 5){
					current_happiness++;
					}}
				else{
					draw_rectangle_full(101, 57, height, lenght, White);
					current_happiness--;}
					break;
			default:
				break;
		}
		//draw_rectangle(61,57,30,100,Black);
	}
	
	if(bar == 1){
	//Satiety
				switch(pos){
			case 1:
				if(action == 1){
					draw_rectangle_full(142, 57, height, lenght, Black);
										if(current_satiety < 5){
					current_satiety++;
					}
				}
				else{
					draw_rectangle_full(142, 57, height, lenght, White);
					current_satiety--;
				}
					break;
			case 2:
				if(action == 1){
					draw_rectangle_full(162, 57, height, lenght, Black);
															if(current_satiety < 5){
					current_satiety++;
					}
				}
				else{
					draw_rectangle_full(162, 57, height, lenght, White);
					current_satiety--;
				}
					break;
			case 3:
				if(action == 1){
					draw_rectangle_full(182, 57, height, lenght, Black);
															if(current_satiety < 5){
					current_satiety++;
					}
				}
				else{
					draw_rectangle_full(182, 57, height, lenght, White);
					current_satiety--;
				}
					break;
			case 4:
				if(action == 1){
					draw_rectangle_full(202, 57, height, lenght, Black);
															if(current_satiety < 5){
					current_satiety++;
					}
				}
				else{
					draw_rectangle_full(202, 57, height, lenght, White);
					current_satiety--;
				}
					break;
			case 5:
				if(action == 1){
					draw_rectangle_full(222, 57, height, lenght, Black);
															if(current_satiety < 5){
					current_satiety++;
					}
				}
				else{
					draw_rectangle_full(222, 57, height, lenght, White);
					current_satiety--;
				}
					break;
			default:
				break;
		}
		//draw_rectangle(182,57,30,100,Black);
	}
	if(bar == 2){
		if(action == 1){
			draw_rectangle_full(21, 57, height, lenght, Black);
			current_happiness++;
			draw_rectangle_full(41, 57, height, lenght, Black);
			current_happiness++;
			draw_rectangle_full(61, 57, height, lenght, Black);
			current_happiness++;
			draw_rectangle_full(81, 57, height, lenght, Black);
			current_happiness++;
			draw_rectangle_full(101, 57, height, lenght, Black);
			current_happiness++;
		
			draw_rectangle_full(142, 57, height, lenght, Black);
			current_satiety++;
			draw_rectangle_full(162, 57, height, lenght, Black);
			current_satiety++;
			draw_rectangle_full(182, 57, height, lenght, Black);
			current_satiety++;
			draw_rectangle_full(202, 57, height, lenght, Black);
			current_satiety++;
			draw_rectangle_full(222, 57, height, lenght, Black);
			current_satiety++;
		}
		else{
			draw_rectangle_full(21, 57, height, lenght, White);
			draw_rectangle_full(41, 57, height, lenght, White);
			draw_rectangle_full(61, 57, height, lenght, White);
			draw_rectangle_full(81, 57, height, lenght, White);
			draw_rectangle_full(101, 57, height, lenght, White);
		
			draw_rectangle_full(142, 57, height, lenght, White);
			draw_rectangle_full(162, 57, height, lenght, White);
			draw_rectangle_full(182, 57, height, lenght, White);
			draw_rectangle_full(202, 57, height, lenght, White);
			draw_rectangle_full(222, 57, height, lenght, White);
		}

	}
	
	if(current_happiness == 0 || current_satiety == 0){
		end = 1;
	}	
}


