// Main method for the crossword lab
// Creates a crossword and anagram hints for a given list of words
// Created by Josh Bottelberghe 11/19/19

#include <iostream>
#include <cstdlib> // for random
using namespace std;

#include <string>
#include <cctype>
#include <iomanip>
#include <algorithm>
#include "board.h"
#include <vector>
#include <fstream>

// methods
void upper (string&);
vector<string> reorder (vector<string>);
bool wordAlpha(string);

int main(int argc, char *argv[]){
	
	if (argc > 3){
		cout << "Too many command line arguments" << endl;
		return 1;
	}

	vector<string> words;
	string str = "nonono";
	fstream fs;

	if (argc == 1) cout << "Enter words, and a period to stop" << endl;
	if (argc > 1) {
		fs.open(argv[1]);
		if (!fs) {
			cout << "FILE NOT FOUND" << endl;
			return 2;
		}
	}

	while (str.compare(".") != 0 && words.size() <= 20){
		if (argc == 1){
			cin >> str;
		}
		else {
			getline(fs, str);
		 }
		 if (str.length() >= 15 || str.length() < 2 || !wordAlpha(str)){
			 if (str.compare(".") != 0) cout << "Cannot add that word" << endl;
		 }
		 else 
			 words.push_back(str);

	}

	if (words.size() == 0){
		cout << "List of words is empty" << endl;
		return 5;
	}

	// here we should have a list of words
	for (string &str: words)
		upper(str);	
	words = reorder(words);

	Board crossword;

	if (crossword.populate(words) != 1){
		cout << "A solution could not be formed" << endl;
		return 4;
	}

	if (argc == 3){
		ofstream file;
		file.open(argv[2]);
		crossword.writeSolution(file);
		crossword.writePuzzle(file);
		crossword.writeLegend(file);
	}
	else{
		crossword.displayPuzzle();
		crossword.displaySolution();
		crossword.displayLegend();
	}

	return 0;
}

void upper (string &str){
	for (auto &i: str)
		i = toupper(i);
}

vector<string> reorder (vector<string> list){
	int max = 0;
	int index = 0;
	string big = list[0];
	for (int i = 0; i < list.size(); i++){
		if (list[i].size() > max){
			max = list[i].size();
			big = list[i];
			index = i;
		}
	}
	
	list.erase(list.begin() + index);
	list.insert(list.begin(), big);

	return list;
}

bool wordAlpha(string str){
	for (char &c : str)
		if (!isalpha(c)) return false;
	return true;
}
