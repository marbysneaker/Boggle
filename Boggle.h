#ifndef BOGGLE_BOGGLE_H
#define BOGGLE_BOGGLE_H

#include <string>
#include "Dictionary.h"

using namespace std;

const int BOARD_SIZE = 4;

class BoardNotInitialized {};

class Boggle {
public:
    Boggle();  // load "dictionary.txt" into dict
    explicit Boggle(string filename);  // load filename into dict

    void SetBoard(string board[BOARD_SIZE][BOARD_SIZE]);

    void SolveBoard(bool printBoard, ostream& output);

    void SaveSolve(string filename);   // Saves all the words from the last solve.

    Dictionary GetDictionary();
    Dictionary WordsFound();

private:
    Dictionary dict;
    Dictionary wordsFound;
    string board[BOARD_SIZE][BOARD_SIZE];
    int visited[BOARD_SIZE][BOARD_SIZE];

    void PrintBoard(ostream& output);
    void SolveBoardHelper(int r, int c, string s, int f, ostream & output, int & numWords, bool printBoard);
};

#endif //BOGGLE_BOGGLE_H
