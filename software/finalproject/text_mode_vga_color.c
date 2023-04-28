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

void textVGAColorHexQuiz()
{

	volatile unsigned int *SW_PIO = (unsigned int*)0x180;
	volatile unsigned int *SUBMIT_PIO = (unsigned int*)0x80;
	volatile unsigned int *reset_PIO = (unsigned int*)0x70;
	int button_press;
	//This is the modified function for a random hexadecimal addition and subtraction quiz
	char question_string[80], answer_string[80], timer_string[80];
    int fg, bg, x, y, remaining_time = 300;
    time_t start_time, current_time, elapsed_time;

	textVGAColorClr();
	//initialize palette
//	while(*reset_PIO != 0){
	for (int i = 0; i < 16; i++)
	{
		setColorPalette (i, colors[i].red, colors[i].green, colors[i].blue);
	}

		int hex1 = rand() % 256; //generate random hex value between 0-255
		int hex2 = rand() % 256; //generate random hex value between 0-255
		int operation = rand() % 2; //generate random operation: 0 for addition, 1 for subtraction
		int correct_answer;
		while (hex1 <= hex2)
		{
			hex1 = rand() % 256;
			hex2 = rand() % 256;
		}
		if (operation == 0)
		{
			correct_answer = hex1 + hex2;
			sprintf(question_string, "What is %02X + %02X?", hex1, hex2);
		}
		else
		{
			correct_answer = hex1 - hex2;
			sprintf(question_string, "What is %02X - %02X?", hex1, hex2);
		}
       // remaining_time = 300 - difftime(time(NULL), start_time); //subtract the elapsed time from 5 minutes
        sprintf(timer_string, "Time: %02d:%02d", remaining_time / 60, remaining_time % 60);


		x = rand() % (80-strlen(question_string));
		y = rand() % 30;
        textVGADrawColorText(timer_string, 0, 0, 15, 0); // display timer in white text with black background
		textVGADrawColorText (question_string, 31, 14, 0, 15); //display the question with black background and white text
		fg = rand() % 16;
		bg = rand() % 16;
		while (fg == bg)
		{
			fg = rand() % 16;
			bg = rand() % 16;
		}
		sprintf(answer_string, "Enter answer using switches.");
		textVGADrawColorText (answer_string, 26, 15, bg, fg); //display the answer with random background and foreground colors
//
		if(*(SUBMIT_PIO)==0){
//
		if (*(SW_PIO) == correct_answer)
//	    if(operation == 0)
		{
			sprintf(answer_string, "Correct! %02X is the answer", hex1+hex2);
			textVGADrawColorText (answer_string, 27, 16, 2, 15); //display the correct answer with random background and foreground colors
			usleep(2000000); //pause for 2 seconds before clearing the screen
		}
		else
		{
			sprintf(answer_string, "Wrong! %02X is the correct answer, your answer is %02X", correct_answer,*(SW_PIO));
			textVGADrawColorText (answer_string, 16, 16, 4, 15); //display the correct answer with random background and foreground colors
			usleep(2000000); //pause for 2 seconds before clearing the screen
		}
		textVGAColorClr(); //clear the screen for the next question
	}}


