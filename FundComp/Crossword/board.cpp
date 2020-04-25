// board.cpp defines board class
// Created by Josh Bottelberghe 11/19/19

#include <iostream>
#include <cstring>
#include <string>
#include <iomanip>
#include <vector>
#include <fstream>
#include "board.h"
#include <algorithm>
using namespace std;

Board::Board()
{
	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j ++)
			board[i][j] = EMPTY;

}

Board::~Board(){	}

void Board::displaySolution(){
	cout << "Solution to crossword: " << endl;
	cout << " ------------------------------" << endl;
	for (int i = 0; i < SIZE; i++){
		cout << "|";
		for (int j = 0; j < SIZE; j++)
			cout << board[j][i] << " ";
		cout << "|" << endl;
	}
	cout << " ------------------------------" << endl;
}

void Board::displayPuzzle(){
	cout << "Crossword: " << endl;
	cout << " ------------------------------" << endl;
	for (int i = 0; i < SIZE; i++){
		cout << "|";
		for (int j = 0; j < SIZE; j++)
			if (board[j][i] == EMPTY)
				cout << "# ";
			else
				cout << "  ";
		cout << "|" << endl;
	}
	cout << " ------------------------------" << endl;
}

void Board::displayLegend(){
	cout << "LEGEND  (Values index at 0)" << endl;
	cout << "ACROSS" << endl;
	for (int i = 0; i < acrossX.size(); i++){
		cout << setw(2) <<  acrossX.at(i) << ", " << setw(2) << acrossY.at(i) << " ";
		cout << toAnagram(acrossWord.at(i)) << endl;
	}

	cout << endl;
	
	cout << "DOWN" << endl;
	for (int i = 0; i < downX.size(); i++){
		cout << setw(2) << downX.at(i) << ", " <<  setw(2) << downY.at(i) << " ";
		cout << toAnagram(downWord.at(i)) << endl;
	}
}

void Board::add(int x, int y, char c)
{
	board[x][y] = c;
}

char Board::get(int x, int y) { return board[x][y]; }

string Board::toAnagram(string str){
	if (str.length() > 2)
		random_shuffle(str.begin(), str.end());
	else
		reverse(str.begin(), str.end());
	
	return str;
}

void Board::addWord(int x, int y, string str, bool ver)
{
	if (ver){
		for (int i = y; i < str.length() + y; i++){
			add(x, i, str[i - y]);
		}
	}

	else {
		for (int i = x; i < str.length() + x; i++){
			add(i, y, str[i - x]);
		}
	}

}// end addWords

void Board::remove(int x, int y)
{
	board[x][y] = EMPTY;
}

void Board::clear()
{
	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
			board[i][j] = EMPTY;
}

bool Board::isEmpty(int x, int y)
{
	return board[x][y] == EMPTY;
}

bool Board::inBounds(int x, int y)
{
	return x < SIZE && y < SIZE && x >= 0 && y >= 0;
}
bool Board::wordFits(int x, int y, string str, bool ver)
{
	// see if there is space to put the word
	if (ver){
		for (int i = 0; i < str.length(); i ++){

			// check if there are existing words
			if (board[x][y + i] != EMPTY || board[x + 1][y + i] != EMPTY || board[x - 1][y + i] != EMPTY){ // check spot and 2 adjacent

				if (board[x][y + i] != str[i]){ // catches exception of intersection
					return false;
				}
			}
		}
		// check top and bottom
		if (board[x][y - 1] != EMPTY)
			return false;
		if (board[x][y + str.length()] != EMPTY)
			return false;
	}
	else{ // horizontal
		for (int i = 0; i < str.length(); i ++){
			if (board[x + i][y] != EMPTY || board[x + i][y + 1] != EMPTY || board[x + i][y - 1] != EMPTY){
				if (board[x + i][y] != str[i]){
					return false;
				}
			}
		}
		// check left and right
		
		if (board[x - 1][y] != EMPTY)
			return false;
		if (board[x + str.length()][y] != EMPTY)
			return false;
	}

	return true;	// has found np issues with the words
}

bool Board::hasIntersection(int x, int y, string str, bool ver)
{
	// loop and check if a location, or more, has an intersection
	if (ver){
		for (int i = 0; i < str.length(); i ++){
			if (board[x][y + i] == str[i])
				return true;
		}
	}
	else{
		for (int j = 0; j < str.length(); j++){
			if (board[x + j][y] == str[j])
				return true;
		}
	}
	
	return false; 	// no intersection found
}// end hasIntersection

void Board::clearLists(){
	downX.clear();
	downY.clear();
	downWord.clear();
	acrossX.clear();
	acrossY.clear();
	acrossWord.clear();
}

bool Board::populate(vector<string> list)
{
	addWord(7 - (list[0].length() / 2), 7, list[0], 0);
	acrossX.push_back(to_string(7 - (list[0].length()/2)));
	acrossY.push_back(to_string(7));
	acrossWord.push_back(list[0]);


	int works = addList(list);
	return works;
}

int Board::addList(vector <string> list)
{
	list.erase(list.begin());
	if (list.size() == 0) return 1;

	//
	Board hold;
	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j ++)
			hold.add(i,j,board[i][j]);
	//

	bool ver = true;
	string str = *list.begin();

	for (int j = 0; j <= SIZE - str.length(); j ++){
		for (int i = 0; i < SIZE; i++){
			if (wordFits(i, j, str, ver) && hasIntersection(i, j, str, ver)){

				addWord(i, j, str, ver);

				if (addList(list) == 1){
					downX.push_back(to_string(i));
					downY.push_back(to_string(j));
					downWord.push_back(str);					
					return 1;
				}
				else {
					clearLists();
					for (int i = 0; i < SIZE; i ++)
						for (int j = 0; j < SIZE; j++)
							board[i][j] = hold.get(i, j);
				}
			}
		}
	}
	for (int i = 0; i <= SIZE; i ++){
		for (int j = 0; j < SIZE - str.length(); j++){
			if (wordFits(j, i, str, !ver) &&  hasIntersection(j, i, str, !ver)){
				addWord(j, i, str, !ver);

				if (addList(list) == 1) {
					acrossX.push_back(to_string(i));
					acrossY.push_back(to_string(j));
					acrossWord.push_back(str);	
					return 1;
				}
				else {
					clearLists();
					for (int i = 0; i < SIZE; i ++)
						for (int j = 0; j < SIZE; j++)
							board[i][j] = hold.get(i, j);
				}
			}
		}
	}

	return 0;
}
// these are for writng to a file

void Board::writeSolution(ofstream & file){
	file << "Solution to crossword: " << endl;
	file << " ------------------------------" << endl;
	for (int i = 0; i < SIZE; i++){
		file << "|";
		for (int j = 0; j < SIZE; j++)
			file << board[j][i] << " ";
		file << "|" << endl;
	}
	file << " ------------------------------" << endl;
}

void Board::writePuzzle(ofstream &file){
	file << "Crossword: " << endl;
	file << " ------------------------------" << endl;
	for (int i = 0; i < SIZE; i++){
		file << "|";
		for (int j = 0; j < SIZE; j++)
			if (board[j][i] == EMPTY)
				file << "# ";
			else
				file << "  ";
		file << "|" << endl;
	}
	file << " ------------------------------" << endl;
}

void Board::writeLegend(ofstream &file){
	file << "LEGEND (Values index at 0)" << endl;
	file << "ACROSS" << endl;
	for (int i = 0; i < acrossX.size(); i++){
		file << setw(2) << acrossX.at(i) << ", " << setw(2) << acrossY.at(i) << " ";
		file << toAnagram(acrossWord.at(i)) << endl;
	}

	file << endl;
	
	file << "DOWN" << endl;
	for (int i = 0; i < downX.size(); i++){
		file << setw(2) << downX.at(i) << ", " << setw(2) << downY.at(i) << " ";
		file << toAnagram(downWord.at(i)) << endl;
	}
}

