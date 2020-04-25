// created by Josh Bottelberghe 12/11/19
// driver for the game of snake

#include <iostream>
#include <unistd.h>
#include "gfx2.h"
#include "snake.h"
using namespace std;

void drawMenu();
void drawLosingScreen();
void drawSnakeBoard(Snake, int, int);	// takes the snake board and draws it

void drawSquare(int x, int y, int size, int width, int height);


int main()
{
	int height = 800, width = 800, pause = 2500000;
	Snake snake;
	char c = 'n';

	gfx_open(width, height, "Snake");
	gfx_color(0, 255, 0);

	drawMenu();

	// wait for game start
	snake.startGame();

	drawSnakeBoard(snake, height, width);
	
	
	while (c != 'q')
	{
		gfx_flush();
		//if (gfx_event_waiting()) 
		//{
			c = gfx_wait();
			cout << c << endl;
		//}

		if (c=='w'||c=='a'||c=='s'||c=='d')
		{
			snake.update(c);
		}
		else 
		{
			snake.update('c'); 		// c for continue
		}

		drawSnakeBoard(snake, width, height);
		gfx_flush();

		if (snake.gameOver())
		{
			cout << "lost" << endl;
			drawLosingScreen();
			c = gfx_wait();
			if (c != 'q')
			{
				snake.startGame();
				drawSnakeBoard(snake, width, height);
			} // start a new game or exit
		} // end if game over

		//usleep(pause);
	}// end while

	return 0;
}

void drawSnakeBoard(Snake board, int height, int width)
{
	// draw every block and a score
	
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (board.at(j, i) > 0){
				gfx_color(0,255,0);
			}
			if (board.at(j, i) == -1)
			{
				gfx_color(255, 0, 0);
			}
			if (board.at(j, i) == 0)
			{
				gfx_color(0,0,0);
			}
			cout << j * SIZE / width << " " << i * SIZE / width << endl;
			gfx_fill_rectangle(j*SIZE/width, i*SIZE/height, width /SIZE, height/SIZE);
			
		}
	}
	
	
	
	
	for (int i = 0; i < 20; i ++){
		for (int j = 0; j < 20; j++)
			cout << board.at(j, i) << " ";
		cout << endl;
		}
	cout << endl;
	
		
}

void drawMenu()
{
	// draw welcome or whatever and promt start
	// draw high score
}

void drawLosingScreen()
{
	// announce loss
	// display score
	// display highscore and if broken
	// ask to play again
}

void drawSquare (int x, int y, int size, int width, int height)
{
	 
}
