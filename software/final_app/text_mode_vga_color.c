/*
 * text_mode_vga_color.c
 * Minimal driver for text mode VGA support
 * This is for Week 2, with color support
 *
 *  Created on: Oct 25, 2021
 *      Author: zuofu
 */

#include <system.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <alt_types.h>
#include "text_mode_vga_color.h"

void textVGAColorClr()
{
	for (int i = 0; i<(ROWS*COLUMNS) * 2; i++)
	{
		vga_ctrl->VRAM[i] = 0x00;
	}
}

void textVGADrawColorText(char* str, int x, int y, alt_u8 background, alt_u8 foreground)
{
	int i = 0;
	while (str[i]!=0)
	{
		vga_ctrl->VRAM[(y*COLUMNS + x + i) * 2] = foreground << 4 | background;
		vga_ctrl->VRAM[(y*COLUMNS + x + i) * 2 + 1] = str[i];
		i++;
	}
}

void setColorPalette (alt_u8 color, alt_u8 red, alt_u8 green, alt_u8 blue)
{
	//fill in this function to set the color palette starting at offset 0x0000 2000 (from base)


	alt_u32 palette = 0;
	alt_u32 r1 = red<<9;
	alt_u32  g1 = green<<5;
	alt_u32 b1 = blue <<1;

	alt_u32 r2 = red<<21;
	alt_u32 g2 = green<<17;
	alt_u32 b2 = blue <<13;
	switch (color){
	 case (0):
			 vga_ctrl->palette[0] &= ~(0xFFF << 1);
			 vga_ctrl->palette[0] |= r1;
			 vga_ctrl->palette[0] |= g1;
			 vga_ctrl->palette[0] |= b1;
			 break;
	 case (1):
		    vga_ctrl->palette[0] &= ~(0xFFF << 13);
			vga_ctrl->palette[0] |= r2;
			vga_ctrl->palette[0] |= g2;
			vga_ctrl->palette[0] |= b2;

			 break;
	 case (2):
			 vga_ctrl->palette[1] &= ~(0xFFF << 1);
			 vga_ctrl->palette[1] |= r1;
			 vga_ctrl->palette[1] |= g1;
			 vga_ctrl->palette[1] |= b1;
			 break;
	 case (3):
		    vga_ctrl->palette[1] &= ~(0xFFF << 13);
			vga_ctrl->palette[1] |= r2;
			vga_ctrl->palette[1] |= g2;
			vga_ctrl->palette[1] |= b2;
			 break;
     case 4:  // Green
    	 	 vga_ctrl->palette[2] &= ~(0xFFF << 1);
			 vga_ctrl->palette[2] |= r1;
			 vga_ctrl->palette[2] |= g1;
			 vga_ctrl->palette[2] |= b1;
			 break;

     case 5:  // Bright green
    	 vga_ctrl->palette[2] &= ~(0xFFF << 13);
         vga_ctrl->palette[2] |= r2;
         vga_ctrl->palette[2] |= g2;
         vga_ctrl->palette[2] |= b2;
         break;

     case 6:  // Yellow
    	 vga_ctrl->palette[3] &= ~(0xFFF << 1);
         vga_ctrl->palette[3] |= r1;
         vga_ctrl->palette[3] |= g1;
         vga_ctrl->palette[3] |= b1;
         break;

     case 7:  // Bright yellow
    	 vga_ctrl->palette[3] &= ~(0xFFF << 13);
         vga_ctrl->palette[3] |= r2;
         vga_ctrl->palette[3] |= g2;
         vga_ctrl->palette[3] |= b2;
         break;

     case 8:  // Blue
    	 vga_ctrl->palette[4] &= ~(0xFFF << 1);
         vga_ctrl->palette[4] |= r1;
         vga_ctrl->palette[4] |= g1;
         vga_ctrl->palette[4] |= b1;
         break;

     case 9:  // Light blue
    	 vga_ctrl->palette[4] &= ~(0xFFF << 13);
         vga_ctrl->palette[4] |= r2;
         vga_ctrl->palette[4] |= g2;
         vga_ctrl->palette[4] |= b2;
         break;

     case 10:  // Light green
    	 vga_ctrl->palette[5] &= ~(0xFFF << 1);
         vga_ctrl->palette[5] |= r1;
         vga_ctrl->palette[5] |= g1;
         vga_ctrl->palette[5] |= b1;
         break;
     case 11:
    	  vga_ctrl->palette[5] &= ~(0xFFF << 13);
    	  vga_ctrl->palette[5] |= r2;
    	  vga_ctrl->palette[5] |= g2;
	      vga_ctrl->palette[5] |= b2;
	      break;

	case (12): //("light red"):
		vga_ctrl->palette[6] &= ~(0xFFF << 1);
		vga_ctrl->palette[6] |= r1;
		vga_ctrl->palette[6] |= g1;
		vga_ctrl->palette[6] |= b1;
		break;
	case (13): //("light magenta"):
		vga_ctrl->palette[6] &= ~(0xFFF << 13);
		vga_ctrl->palette[6] |= r2;
		vga_ctrl->palette[6] |= g2;
		vga_ctrl->palette[6] |= b2;
		break;
	case (14): //("yellow"):
		vga_ctrl->palette[7] &= ~(0xFFF << 1);
		vga_ctrl->palette[7] |= r1;
		vga_ctrl->palette[7] |= g1;
		vga_ctrl->palette[7] |= b1;
		break;
	case (15): //("white"):
		vga_ctrl->palette[7] &= ~(0xFFF << 13);
		vga_ctrl->palette[7] |= r2;
		vga_ctrl->palette[7] |= g2;
		vga_ctrl->palette[7] |= b2;
	    break;
	}



}


void textVGAColorScreenSaver()
{
	//This is the function you call for your week 2 demo
	char color_string[80];
    int fg, bg, x, y;
	textVGAColorClr();
	//initialize palette
	for (int i = 0; i < 16; i++)
	{
		setColorPalette (i, colors[i].red, colors[i].green, colors[i].blue);
	}
	while (1)
	{
		fg = rand() % 16;
		bg = rand() % 16;
		while (fg == bg)
		{
			fg = rand() % 16;
			bg = rand() % 16;
		}
		sprintf(color_string, "Drawing %s text with %s background", colors[fg].name, colors[bg].name);
		x = rand() % (80-strlen(color_string));
		y = rand() % 30;
		textVGADrawColorText (color_string, x, y, bg, fg);
		usleep (100000);
	}
}

int textVGAColorHexQuizEasy()
{

	volatile unsigned int *SW_PIO = (unsigned int*)0x180;
	volatile unsigned int *SUBMIT_PIO = (unsigned int*)0x80;
	volatile unsigned int *reset_PIO = (unsigned int*)0x70;
	volatile unsigned int *buttons = (unsigned int*)0x1d0;
	volatile unsigned int *state = (unsigned int*)0x00;

	int button_press;
	//This is the modified function for a random hexadecimal addition and subtraction quiz
	char question_string[80], answer_string[80], timer_string[80], score_string[80];
    int fg, bg, x, y;
    int score = 0;

	textVGAColorClr();
	//initialize palette
	for (int i = 0; i < 16; i++)
	{
		setColorPalette (i, colors[i].red, colors[i].green, colors[i].blue);
	}

    while(*state ==3){

		int hex1 = rand() % 16; //generate random hex value between 0-255
		int hex2 = rand() % 16; //generate random hex value between 0-255
		int operation = rand() % 2; //generate random operation: 0 for addition, 1 for subtraction
		int correct_answer;

		while ( hex1<= hex2)
		{
			hex1 = rand() % 16;
			hex2 = rand() % 16;
		}
		if (operation == 0)
		{
			correct_answer = hex1 - hex2;
			sprintf(question_string, "What is %01X - %01X?", hex1, hex2);
		}
		else{
					correct_answer = hex1 - hex2;
			sprintf(question_string, "What is %01X - %01X?", hex1, hex2);
		}


        sprintf(timer_string, " Time: ");
		sprintf(score_string, "Score: %d", score);
        x = rand() % (80-strlen(question_string));
		y = rand() % 30;
        textVGADrawColorText(timer_string, 0, 0, 15, 0); // display timer in white text with black background
		textVGADrawColorText (question_string, 31, 14, 0, 15); //display the question with black background and white text
		textVGADrawColorText(score_string, 36, 10, 15, 0);
		fg = rand() % 16;
		bg = rand() % 16;
		while (fg == bg)
		{
			fg = rand() % 16;
			bg = rand() % 16;
		}
		sprintf(answer_string, "Enter answer using switches.");
		textVGADrawColorText (answer_string, 26, 15, bg, fg); //display the answer with random background and foreground colors

		while(*(SUBMIT_PIO)==0){
			if (*state != 3){
				textVGAColorClr();
				return score;
			}
		}

		while(*(SUBMIT_PIO)==1){
			if (*state != 3){
				textVGAColorClr();
				return score;
			}
		}

			if (*(SW_PIO) == correct_answer)
			{
                score++;
				sprintf(answer_string, "Correct! %01X is the answer.", correct_answer);
				textVGADrawColorText (answer_string, 27, 17, 2, 15); //display the correct answer with random background and foreground colors
				usleep(500000); //pause for 1 seconds before clearing the screen
			}
			else
			{
				sprintf(answer_string, "Wrong! %01X is the correct answer, your answer is %02X.", correct_answer,*(SW_PIO));
				textVGADrawColorText (answer_string, 16, 17, 4, 15); //display the correct answer with random background and foreground colors
				usleep(500000); //pause for 1 seconds before clearing the screen
			}
			textVGAColorClr();
		//clear the screen for the next question
		}
	return score;
	}

int textVGAColorHexQuizMed()
{

	volatile unsigned int *SW_PIO = (unsigned int*)0x180;
	volatile unsigned int *SUBMIT_PIO = (unsigned int*)0x80;
	volatile unsigned int *reset_PIO = (unsigned int*)0x70;
	volatile unsigned int *buttons = (unsigned int*)0x1d0;
	volatile unsigned int *state = (unsigned int*)0x00;

	int button_press;
	//This is the modified function for a random hexadecimal addition and subtraction quiz
	char question_string[80], answer_string[80], timer_string[80], score_string[80];
    int fg, bg, x, y;
    int score = 0;

	textVGAColorClr();
	//initialize palette
	for (int i = 0; i < 16; i++)
	{
		setColorPalette (i, colors[i].red, colors[i].green, colors[i].blue);
	}

    while(*state == 4){

		int hex1 = rand() % 256; //generate random hex value between 0-255
		int hex2 = rand() % 256; //generate random hex value between 0-255
		int operation = rand() % 2; //generate random operation: 0 for addition, 1 for subtraction
		int correct_answer;

		while ( hex1<= 2 ||  hex2<=2)
		{
			hex1 = rand() % 256;
			hex2 = rand() % 256;
		}

		if (operation == 0)
		{
			correct_answer = hex1 - hex2;
			sprintf(question_string, "What is %01X - %01X?", hex1, hex2);
		}
		else{
					correct_answer = hex1 - hex2;
			sprintf(question_string, "What is %01X - %01X?", hex1, hex2);
		}

        sprintf(timer_string, " Time: ");
		sprintf(score_string, "Score: %d", score);
        x = rand() % (80-strlen(question_string));
		y = rand() % 30;
        textVGADrawColorText(timer_string, 0, 0, 15, 0); // display timer in white text with black background
		textVGADrawColorText (question_string, 31, 14, 0, 15); //display the question with black background and white text
		textVGADrawColorText(score_string, 36, 10, 15, 0);
		fg = rand() % 16;
		bg = rand() % 16;
		while (fg == bg)
		{
			fg = rand() % 16;
			bg = rand() % 16;
		}
		sprintf(answer_string, "Enter answer using switches.");
		textVGADrawColorText (answer_string, 26, 15, bg, fg); //display the answer with random background and foreground colors

		while(*(SUBMIT_PIO)==0){
			if (*state != 4){
				textVGAColorClr();
				return score;
			}
		}
		while(*(SUBMIT_PIO)==1){
			if (*state != 4){
				textVGAColorClr();
				return score;
			}
		}

			if (*(SW_PIO) == correct_answer)
			{
                score++;
				sprintf(answer_string, "Correct! %01X is the answer.", correct_answer);
				textVGADrawColorText (answer_string, 27, 17, 2, 15); //display the correct answer with random background and foreground colors
				usleep(500000); //pause for 1 seconds before clearing the screen
			}
			else
			{
				sprintf(answer_string, "Wrong! %01X is the correct answer, your answer is %02X.", correct_answer,*(SW_PIO));
				textVGADrawColorText (answer_string, 16, 17, 4, 15); //display the correct answer with random background and foreground colors
				usleep(500000); //pause for 1 seconds before clearing the screen
			}
			textVGAColorClr();
		//clear the screen for the next question
		}
	return score;
	}

int textVGAColorHexQuizHard()
{

	volatile unsigned int *SW_PIO = (unsigned int*)0x180;
	volatile unsigned int *SUBMIT_PIO = (unsigned int*)0x80;
	volatile unsigned int *reset_PIO = (unsigned int*)0x70;
	volatile unsigned int *buttons = (unsigned int*)0x1d0;
	volatile unsigned int *state = (unsigned int*)0x00;

	int button_press;
	//This is the modified function for a random hexadecimal addition and subtraction quiz
	char question_string[80], answer_string[80], timer_string[80], score_string[80];
    int fg, bg, x, y;
    int score = 0;

	textVGAColorClr();
	//initialize palette
	for (int i = 0; i < 16; i++)
	{
		setColorPalette (i, colors[i].red, colors[i].green, colors[i].blue);
	}

    while(*state == 5){

		int hex1 = rand() % 16; //generate random hex value between 0-255
		int hex2 = rand() % 16; //generate random hex value between 0-255
//		int operation = rand() % 2; //generate random operation: 0 for addition, 1 for subtraction
		int correct_answer;

		while ( hex1<= 2 ||  hex2<=2)
		{
			hex1 = rand() % 16;
			hex2 = rand() % 16;
		}


			correct_answer = hex1 * hex2;
			sprintf(question_string, "What is %01X x %01X?", hex1, hex2);


        sprintf(timer_string, " Time: ");
		sprintf(score_string, "Score: %d", score);
        x = rand() % (80-strlen(question_string));
		y = rand() % 30;
        textVGADrawColorText(timer_string, 0, 0, 15, 0); // display timer in white text with black background
		textVGADrawColorText (question_string, 31, 14, 0, 15); //display the question with black background and white text
		textVGADrawColorText(score_string, 36, 10, 15, 0);
		fg = rand() % 16;
		bg = rand() % 16;
		while (fg == bg)
		{
			fg = rand() % 16;
			bg = rand() % 16;
		}
		sprintf(answer_string, "Enter answer using switches.");
		textVGADrawColorText (answer_string, 26, 15, bg, fg); //display the answer with random background and foreground colors
		
		while(*(SUBMIT_PIO)==0){
			if (*state != 5){
				textVGAColorClr();
				return score;
			}
		}

		while(*(SUBMIT_PIO)==1){
			if (*state != 5){
				textVGAColorClr();
				return score;
			}
		}

			if (*(SW_PIO) == correct_answer)
			{
                score++;
				sprintf(answer_string, "Correct! %01X is the answer.", correct_answer);
				textVGADrawColorText (answer_string, 27, 17, 2, 15); //display the correct answer with random background and foreground colors
				usleep(500000); //pause for 1 seconds before clearing the screen
			}
			else
			{
				sprintf(answer_string, "Wrong! %01X is the correct answer, your answer is %02X.", correct_answer,*(SW_PIO));
				textVGADrawColorText (answer_string, 16, 17, 4, 15); //display the correct answer with random background and foreground colors
				usleep(500000); //pause for 1 seconds before clearing the screen
			}
			textVGAColorClr();
		//clear the screen for the next question
		}
	return score;
	}

int* updateLeaderboard(int leaderboard[], int score) {
    int i, j;
    int position = -1;
	char header[80], pos0[80], top[80], reset[80], pos1[80], pos2[80], pos3[80], pos4[80];

    // Find the position where the input score should be inserted
    for (i = 0; i < 5; i++) {
        if (score > leaderboard[i]) {
            position = i;
            break;
        }
    }

    // If the position is found, shift the existing scores to make space for the new score
    if (position != -1) {
        for (j = 5 - 1; j > position; j--) {
            leaderboard[j] = leaderboard[j - 1];
        }
        leaderboard[position] = score;
    }

	sprintf(header,"Updated leaderboard");
	sprintf(pos0,"1: %d", leaderboard[0]);
	sprintf(pos1,"2: %d", leaderboard[1]);
	sprintf(pos2,"3: %d", leaderboard[2]);
	sprintf(pos3,"4: %d", leaderboard[3]);
	sprintf(pos4,"5: %d", leaderboard[4]);

	textVGADrawColorText (header, 45, 15, 2, 15); 
	textVGADrawColorText (pos0, 45, 16, 2, 15);
	textVGADrawColorText (pos1, 45, 17, 2, 15);
	textVGADrawColorText (pos2, 45, 18, 2, 15);
	textVGADrawColorText (pos3, 45, 19, 2, 15);
	textVGADrawColorText (pos4, 45, 20, 2, 15);

	return leaderboard;
}

int* leaderboard_hard(int leaderboard[], int score){
	int* temp;
	char header[80], pos0[80], top[80], reset[80], pos1[80], pos2[80], pos3[80], pos4[80];

	sprintf(header,"Initial leaderboard");
	sprintf(pos0,"1: %d", leaderboard[0]);
	sprintf(pos1,"2: %d", leaderboard[1]);
	sprintf(pos2,"3: %d", leaderboard[2]);
	sprintf(pos3,"4: %d", leaderboard[3]);
	sprintf(pos4,"5: %d", leaderboard[4]);
	textVGADrawColorText (header, 5, 15, 2, 15); 
	textVGADrawColorText (pos0, 5, 16, 2, 15);
	textVGADrawColorText (pos1, 5, 17, 2, 15);
	textVGADrawColorText (pos2, 5, 18, 2, 15);
	textVGADrawColorText (pos3, 5, 19, 2, 15);
	textVGADrawColorText (pos4, 5, 20, 2, 15);

	if (score > leaderboard[4]){
 		sprintf(top,"Updating Leaderboard with score %d", leaderboard[0]);
		textVGADrawColorText (top, 22, 11, 2, 15);
		temp = updateLeaderboard(leaderboard, score);
		sprintf(reset,"Push Reset to start new game");
		textVGADrawColorText (reset, 26, 22, 2, 15);
		return temp;
	}
	else{
		sprintf(top,"Try again to get on the leaderboard");
		textVGADrawColorText (top, 22, 11, 2, 15);
	}

	sprintf(reset,"Push Reset to start new game");
	textVGADrawColorText (reset, 26, 22, 2, 15);
	return leaderboard;

}
int* leaderboard_easy(int leaderboard[], int score){
	int* temp;
	char header[80], pos0[80], top[80], reset[80], pos1[80], pos2[80], pos3[80], pos4[80];

	sprintf(header,"Initial leaderboard");
	sprintf(pos0,"1: %d", leaderboard[0]);
	sprintf(pos1,"2: %d", leaderboard[1]);
	sprintf(pos2,"3: %d", leaderboard[2]);
	sprintf(pos3,"4: %d", leaderboard[3]);
	sprintf(pos4,"5: %d", leaderboard[4]);
	textVGADrawColorText (header, 5, 15, 2, 15); 
	textVGADrawColorText (pos0, 5, 16, 2, 15);
	textVGADrawColorText (pos1, 5, 17, 2, 15);
	textVGADrawColorText (pos2, 5, 18, 2, 15);
	textVGADrawColorText (pos3, 5, 19, 2, 15);
	textVGADrawColorText (pos4, 5, 20, 2, 15);

	if (score > leaderboard[4]){
 		sprintf(top,"Updating Leaderboard with score %d", leaderboard[0]);
		textVGADrawColorText (top, 22, 11, 2, 15);
		temp = updateLeaderboard(leaderboard, score);
		sprintf(reset,"Push Reset to start new game");
		textVGADrawColorText (reset, 26, 22, 2, 15);
		return temp;
	}
	else{
		sprintf(top,"Try again to get on the leaderboard");
		textVGADrawColorText (top, 22, 11, 2, 15);
	}

	sprintf(reset,"Push Reset to start new game");
	textVGADrawColorText (reset, 26, 22, 2, 15);
	return leaderboard;
}
int* leaderboard_med(int leaderboard[], int score){
	int* temp;
	char header[80], pos0[80], top[80], reset[80], pos1[80], pos2[80], pos3[80], pos4[80];

	sprintf(header,"Initial leaderboard");
	sprintf(pos0,"1: %d", leaderboard[0]);
	sprintf(pos1,"2: %d", leaderboard[1]);
	sprintf(pos2,"3: %d", leaderboard[2]);
	sprintf(pos3,"4: %d", leaderboard[3]);
	sprintf(pos4,"5: %d", leaderboard[4]);
	textVGADrawColorText (header, 5, 15, 2, 15); 
	textVGADrawColorText (pos0, 5, 16, 2, 15);
	textVGADrawColorText (pos1, 5, 17, 2, 15);
	textVGADrawColorText (pos2, 5, 18, 2, 15);
	textVGADrawColorText (pos3, 5, 19, 2, 15);
	textVGADrawColorText (pos4, 5, 20, 2, 15);

	if (score > leaderboard[4]){
 		sprintf(top,"Updating Leaderboard with score %d", leaderboard[0]);
		textVGADrawColorText (top, 22, 11, 2, 15);
		temp = updateLeaderboard(leaderboard, score);
		sprintf(reset,"Push Reset to start new game");
		textVGADrawColorText (reset, 26, 22, 2, 15);
		return temp;
	}
	else{
		sprintf(top,"Try again to get on the leaderboard");
		textVGADrawColorText (top, 22, 11, 2, 15);
	}

	sprintf(reset,"Push Reset to start new game");
	textVGADrawColorText (reset, 26, 22, 2, 15);
	return leaderboard;
}
