// created by Josh Bottelberghe 12/11/19
// driver for the game of snake

#include <iostream>
#include <unistd.h>
#include <string>
#include "gfx2.h"
#include "snake.h"

void drawMenu(int, int);
void drawLosingScreen(int, int, Snake);
void drawSnakeBoard(Snake, int, int);			// takes the snake board and draws it

int main()
{
	int height = 650, width = 650, pause = 50000;	// edit pause for game speed
	Snake snake;
	char c = 'n';	// temp value

	gfx_open(width, height, "Snake");
	gfx_color(0, 255, 0);

	drawMenu(width, height);	// will wait for someting to be pressed

	// wait for game start, then draw the initial board
	snake.startGame();
	drawSnakeBoard(snake, height, width);
	
	while (c != 'q')
	{
		gfx_flush();	// assue all shapes drawn

		if (gfx_event_waiting())	// check if new input
			c = gfx_wait();

		if (c=='w'||c=='a'||c=='s'||c=='d')	// all accepted movement keys
			snake.update(c);
		else 
			snake.update('c'); 		// c for continue, value unused

		drawSnakeBoard(snake, width, height);
		gfx_flush();

		if (snake.gameOver())
		{
			drawLosingScreen(width, height, snake);
			c = gfx_wait();
			if (c != 'q')
			{
				snake.startGame();
				drawSnakeBoard(snake, width, height);
			} // start a new game or exit
		} // end if game over

		usleep(pause);
	}// end while

	return 0;
}

void drawSnakeBoard(Snake board, int height, int width)
{
	// draw every block
	double SIZE = board.getSize();	
	gfx_clear();	// clean screen

	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (board.at(j, i) > 0){
				gfx_color(0,255,0);
				gfx_rectangle(1+j/SIZE*width, 1+i/SIZE*height, width /SIZE - 3, height/SIZE -3);
			}
			else if (board.at(j, i) == -1)
			{
				gfx_color(255, 0, 0);
				gfx_rectangle(1+j/SIZE*width, 1+i/SIZE*height, width /SIZE - 3, height/SIZE -3);
			}		
		}// end x level
	}// end y level
}// end function

void drawMenu(int width, int height)
{
	// draw welcome and promt start
	
	gfx_clear();
	gfx_color(255,255,255);
	
	gfx_text(width / 2 - 125, height/2 - 50, "Welcome to snake! Press anything to start");
	gfx_flush();
	char c = gfx_wait();
}

void drawLosingScreen(int w, int h, Snake snake)
{
	// announce loss
	gfx_clear();

	gfx_color(255,255,255);

	gfx_text(w / 2 - 30, h/2 - 50, "You Died!");
	gfx_text(w / 2 - 120, h/2 - 35, "Press any key to play again, or q to quit");
}

