// board.h declares functions to handle a crossword pussle
// Created by Josh Bottelberghe 11/19/19

const int SIZE = 15;
const int EMPTY = '.';
const bool VER = 1;
const bool HOR = 0;   // for vertical or horzontal
#include <cstring>
#include <string>
#include <fstream>
#include <vector>
#include <iostream>
using namespace std;

class Board{
	public:
		Board();
		~Board();

		void displaySolution();
		void displayPuzzle();
		void displayLegend();
		void add(int, int, char);
		char get(int, int); 
		void addWord(int, int, string, bool); // bool represesnts direction
		void remove(int, int);
		void clear();
		void writeLegend(ofstream&);
		void writeSolution(ofstream&);
		void writePuzzle(ofstream&);
		void clearLists();

		int addList(vector<string>);
		bool populate(vector<string>);

		bool isEmpty(int, int);
		bool inBounds(int, int);
		bool hasIntersection(int, int, string, bool); // (x, y, word, direction)
		bool wordFits(int, int, string, bool);        //      ^ same ^

		string toAnagram(string);

	private:
		char board[SIZE][SIZE];
		vector<string> acrossX;
		vector<string> acrossY;
		vector<string> acrossWord;
		vector<string> downX;
		vector<string> downY;
		vector<string> downWord; 
};
