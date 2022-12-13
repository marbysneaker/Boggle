
#include "Dictionary.h"
#include "Boggle.h"

// Your code here


// This function is done.
Dictionary Boggle::GetDictionary() {


    return dict;

}

// This function is done.
Dictionary Boggle::WordsFound() {
    return wordsFound;
}

/*
 * Function:  default constructor
 *
 * Precondition:
 * loads words from a hardcoded text file.
 *
 * Postcondition:
 * sets board to all empty chars. Sets visited board all to zero
 */
Boggle::Boggle() {
    this->dict.LoadDictionaryFile("dictionary.txt");

    cout<<dict.WordCount()<<endl;
    for(int i =0; i<4; i++){
        for(int j =0; j<4; j++){
            board[i][j] = "";
            visited[i][j] = 0;
        }
    }
}

/*
 * Function:  default constructor
 *
 * Precondition:
 * loads words from a hardcoded text file.
 *
 * Postcondition:
 * sets board to all empty chars. Sets visited board all to zero
 */
Boggle::Boggle(string filename) {

    this->dict.LoadDictionaryFile(filename);
    for(int i =0; i<4; i++){
        for(int j =0; j<4; j++){
            board[i][j] = "";
            visited[i][j] = 0;
        }
    }

}

/*
 * Function:  setboard function
 *
 * Precondition:
 * 4x4 board passed in by the parameter
 *
 * Postcondition:
 * Copies the board into the class object by using this->board to copy all the letters
 * from the board passed by the parameter
 */
void Boggle::SetBoard(string (*board)[4]) {
    for(int i =0; i<BOARD_SIZE; i++){
        for(int j =0; j<BOARD_SIZE; j++){
            this->board[i][j] = board[i][j];
        }
    }
}

/*
 * Function:  solvedboard function
 *
 * Precondition:
 * takes a boolean printboard, and an output file as parameters.
 * Solveboardhelper needs to be functioning.
 *
 * Postcondition:
 * runs a nested for loop and pass the row and column into the solvedboardhelper
 * as the starting point and empty string to saved letters that are valid.
 */
void Boggle::SolveBoard(bool printBoard, ostream &output) {


    int numWords =0;
    for(int row = 0;  row<BOARD_SIZE; row++){
        for(int col = 0 ; col< BOARD_SIZE; col++ ){
            string word =  "";
            int found =0;
            SolveBoardHelper(row, col, word, found, output, numWords,printBoard);
        }
    }

}

/*
 * Function:  savesolve function
 *
 * Precondition:
 * needs a text file to be passed in the parameter.
 *
 * Postcondition:
 * saves all existing word into the text file
 */
void Boggle::SaveSolve(string filename) {
    ofstream savefile;
    savefile.open(filename);
    this->wordsFound.SaveDictionaryFile(filename);
}

/*
 * Function:  printboard funciton
 *
 * Precondition:
 * needs a text file to save all the outcome of found words
 *
 * Postcondition:
 * displays or writes in the board and the visited board into a file along
 * with the word that is found and the number of words found
 */
void Boggle::PrintBoard(ostream & output) {
    for(int r = 0; r< BOARD_SIZE; r++){
        for(int c = 0; c< BOARD_SIZE; c++){
            if(visited[r][c]>0){
                output<<" "<<"'"<<board[r][c]<<"'"<<" ";
                if(c == BOARD_SIZE-1){
                    output<<"\t";
                }
            }
            else{
                output<<"  "<<board[r][c]<<"  ";
                if(c == BOARD_SIZE -1){
                    output<<"\t";
                }
            }

        }

            for(int c = 0; c< BOARD_SIZE; c++){
                output<<"  "<<visited[r][c]<<"  ";
                if(c == BOARD_SIZE -1){
                    output<<"\n";
                if(r == BOARD_SIZE -1 && c == BOARD_SIZE -1){
                    output<<"\n";
                }
                }
            }

        }


}

/*
 * Function:  solvedboard function
 *
 * Precondition:
 * takes the board and and finds all possible words using the boggle rule.
 * edge cases:
 *  row and column both needs to be more than zero and less than 4
 *  ongoing word needs to be a prefix
 * printboard needs to be functioning.
 *
 * Postcondition:
 * traverses trough the board starting with the given coordinates from solvedboard
 * traverses through all possible paths to find an existing word from the dictionary dict
 * object and then saves them in the dictionary wordsfound object.
 */
void Boggle::SolveBoardHelper(int r, int c, string s, int f, ostream& output, int &numWords,bool printBoard) {



    if(r < 0 || c < 0 || r > BOARD_SIZE -1 || c > BOARD_SIZE -1){
        return;
    }
    s += board[r][c];
    cout<<s<<endl;
    if(!dict.IsPrefix(s)){

        return;
    }
//    if(wordsFound.IsWord(s)){
//
//            return;
//    }
    if(visited[r][c]>0 ){
//        cout<<s<<" "<<visited[r][c]<< "  visited "<<endl;
        return;
    }

    f++;

    visited[r][c] = f;

    if(dict.IsWord(s)){


        if(wordsFound.IsWord(s)){

        }

        else if(printBoard == true) {
            this->wordsFound.AddWord(s);
            numWords++;
            output << "Word: " << s << "\n" << "Number of Words: " << numWords << "\n";
            PrintBoard(output);
        }
        else {
            this->wordsFound.AddWord(s);
            numWords++;
            output << numWords << "\t" << s << "\n";
        }


    }





    SolveBoardHelper(r -1, c, s, f, output, numWords, printBoard);//north
    SolveBoardHelper(r -1, c+1, s , f, output, numWords, printBoard);//northeast
    SolveBoardHelper(r , c+1, s, f, output, numWords, printBoard);//east
    SolveBoardHelper(r +1, c+1, s, f, output, numWords, printBoard);//southeast
    SolveBoardHelper(r +1, c, s , f, output, numWords, printBoard);//south
    SolveBoardHelper(r +1, c-1, s , f, output, numWords, printBoard);//southwest
    SolveBoardHelper(r , c-1, s , f, output, numWords, printBoard);//west
    SolveBoardHelper(r -1, c-1, s, f, output, numWords, printBoard);//northwest


    visited[r][c] = 0;



}



