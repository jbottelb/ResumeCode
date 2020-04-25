// all of the snake functions, all output creates an array that is the game
// Created by Josh Bottelberghe 12/6/19

const int SIZE = 20;
const int APPLE = -1;
const int EMPTY = 0;


class Snake {
	public:
		Snake();
		~Snake();
		int getSize();

		int at(int, int);	  // returns value at spot on graph
		void startGame();     // creates initial consdition
		void update(char);    // iterates game, needs what the user input

		void setLength(int);
		int getLength();

		void addApple();      // adds apple to free space

		bool inBounds(int, int);
		bool gameOver();


	private:
		int board[SIZE][SIZE];
		int length;              // how long the snake is
		int xVel, yVel;
		int x, y;
		int score;

		bool hasBounds;
		bool lost;
}; 
