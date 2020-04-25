// functions for snake class
// Created by Josh Bottelberghe 12/6/19

#include "snake.h"
#include <cstdlib>
#include <ctime>

Snake::Snake()
{
	hasBounds = true;

	length = 3;

	x = SIZE/2;
	y = SIZE/2;

	// add empty space
	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
			board[i][j] = EMPTY;
	
	// add snake start point
	board[x][y] = length;

	// add apple to start
	addApple();
}

Snake::~Snake() {}

int Snake::at(int x, int y) { return board[x][y]; }

void Snake::setLength(int l){  length = l;  }
int Snake::getLength(){ return length;}

void Snake::startGame()
{
	// add empty space
	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
			board[i][j] = EMPTY;

	x = SIZE/2;
	y = SIZE/2;
	length = 3;


	for (int i = 0; i < length; i++)
		board[x-i][y] = length - i;		// sets snake locations to length
	
	addApple();
	xVel = 1;
	yVel = 0;

	lost = false;
}

void Snake::update(char c)

{	
	switch (c){
		case 'w':
			if (yVel != 0) break; 	// cant turn into itself
			yVel = -1;
			xVel = 0;
			break;
		case 'a':
			if (xVel != 0) break;
			xVel = -1;
			yVel = 0;
			break;
		case 's':
			if (yVel != 0) break;
			yVel = 1;
			xVel = 0;
			break;
		case 'd':
			if (xVel != 0) break;
			xVel = 1;
			yVel = 0;
			break;
		default:

		break;
	}
	// check if it dies
	if (!inBounds(x + xVel, y + yVel) || board[x + xVel][y + yVel] > 0)
	{
		lost = true;
		return;
	}	
	
	// check if it's eating an apple, act accordingly
	if (board[x + xVel][y + yVel] == APPLE)
	{
		length++;
		addApple();
	}
	
	// move the snake forwards
	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
			if (board[i][j] > 0) board[i][j] --;
	
	board[x + xVel][y + yVel] = length;

	x = x + xVel;
	y = y + yVel;

}

void Snake::addApple()
{
	// find a spot to put an apple on and put it there
	int x, y;

	while (true){
		srand(time(0));
		x = rand() % SIZE;
		y = rand() % SIZE;

		if (board[x][y] == EMPTY){
			board[x][y] = -1;
			return;
		}// adds apple at random spot
	}
}

bool Snake::inBounds(int x, int y)
{
	return (x >= 0 && y >= 0 && x < SIZE && y < SIZE);
}

bool Snake::gameOver() {return lost;}

int Snake::getSize(){return SIZE;}

