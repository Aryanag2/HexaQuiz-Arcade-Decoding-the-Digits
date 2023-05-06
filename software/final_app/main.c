#include "text_mode_vga_color.h"
int main (void){
	volatile unsigned int *SW_PIO = (unsigned int*)0x180;
	volatile unsigned int *SUBMIT_PIO = (unsigned int*)0x80;
	volatile unsigned int *reset_PIO = (unsigned int*)0x70;
	volatile unsigned int *buttons = (unsigned int*)0x1d0;
	volatile unsigned int *state = (unsigned int*)0x00;
	int fsm = 0;
	int score;
	int leaderboardeasy[5] = {20, 18, 15, 13, 10};
	int leaderboardmed[5] = {15, 13, 11, 9, 8};
	int leaderboardhard[5] = {8, 7, 6, 4, 3};

	int* tempeasy;
	int* tempmed;
	int* temphard;
		for (int i = 0; i < 16; i++)
	{
		setColorPalette (i, colors[i].red, colors[i].green, colors[i].blue);
	}
	while (1==1){
		switch (*(state)){
			case 1:
				break;
			case 2:
				break;
			case 3:

				score = textVGAColorHexQuizEasy();
				fsm = 1;
				break;
			case 4:
				score = textVGAColorHexQuizMed();
				fsm = 2;
				break;
			case 5:
				score = textVGAColorHexQuizHard();
				fsm = 3;
				break;
			case 6:
				if (fsm = 1){
					tempeasy = leaderboard_easy(leaderboardeasy, score);
					for (int i = 0; i < 5; i++) 
					{
						leaderboardeasy[i] = tempeasy[i];
					}
				}
				else if (fsm = 2){
					tempmed = leaderboard_med(leaderboardmed, score);
					for (int i = 0; i < 5; i++) 
					{
						leaderboardmed[i] = tempmed[i];
					}
				}
				else {
					temphard = leaderboard_hard(leaderboardhard, score);
					for (int i = 0; i < 5; i++) 
					{
						leaderboardhard[i] = temphard[i];
					}
				}
				while(*(reset_PIO)==1){}
				break;
		}
	}
}
