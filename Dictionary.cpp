#include "Dictionary.h"

// Your code here

/*
 * Function:  default constructor
 *
 * Precondition:
 * Needs to initiate root node
 *
 * Postcondition:
 * sets numwords to 0 and all child nodes to nullptr
 */
Dictionary::Dictionary() {
    root = new Node();
    numWords = 0;
}

/*
 * Function:  destructor
 *
 * Precondition:
 * Needs destroyhelper to be functioning
 *
 * Postcondition:
 * destroys all existing node starting from the root;
 */
Dictionary::~Dictionary() {
    destroyHelper(root);
}

/*
 * Function:  copy constructor
 *
 * Precondition:
 * copyother and copyhelper need to be working properly
 * Needs a node to copy from the node thats been passed by the parameter;
 *
 * Postcondition:
 * copies all nodes from the parameter node into a new node;
 */
Dictionary::Dictionary(const Dictionary &otherDict) {
    root = new Node();
    numWords = 0;
    copyOther(otherDict);
}

/*
 * Function:  addWord function
 *
 * Precondition:
 * Needs a string word to be passed into the parameter
 *
 * Postcondition:
 * for every letter of the word the function creates a newNode and sets the last node
 * isWord boolean to true, numWords is incremented
 * copies class object into another class object.
 */
void Dictionary::AddWord(string word) {
    Node* curr  =  root;

    for(int i = 0; i<word.length(); i++){
        int index = word[i] - 'a';
        if(index<0 || index>26){
            throw DictionaryError("Invalid character");
        }
        if(curr->child[index] == nullptr){
            curr->child[index] = new Node();
        }
        curr = curr->child[index];
    }
    curr->isWord = true;
    numWords++;

}
/*
 * Function:  parameter constructor
 *
 * Precondition:
 * Needs a working file. Addword need to function properly
 *
 * Postcondition:
 * take all the words in the file and pass them inside the addword funtion.
 */
Dictionary::Dictionary(string filename) {
    root = new Node();
    numWords = 0;
    string line;
    ifstream infile(filename);

    if (infile.is_open())
    {
        while ( getline (infile,line) )
        {
            AddWord(line);
        }
        infile.close();
    }
}

/*
 * Function:  operator overload function
 *
 * Precondition:
 * Needs copyother to be functioning. The node being used to assign the parameter
 * cannot have the same name
 *
 * Postcondition:
 * Does a deep copy of the Node passed in the parameter.
 */
Dictionary &Dictionary::operator=(const Dictionary &otherDict) {
    if(this != &otherDict){
        copyOther(otherDict);
    }
    return *this;
}

/*
 * Function:  loaddictionary function
 *
 * Precondition:
 * Needs to a text file in side the parameter
 *
 * Postcondition:
 * File is read and each word passed in the addWord function
 */

void Dictionary::LoadDictionaryFile(string filename) {
    string line;
    ifstream infile(filename);

    if (infile.is_open())
    {
        while ( getline (infile,line) )
        {

            AddWord(line);
        }
        infile.close();
    }
}

/*
 * Function:  savedictionary function
 *
 * Precondition:
 * Needs a text file as a parameter to save all existing words.
 * savedictionary function needs to be functioning.
 *
 * Postcondition:
 * sets numwords to 0 and all child nodes to nullptr
 */
void Dictionary::SaveDictionaryFile(string filename) {
    ofstream dictFile;
    dictFile.open(filename);

    // Notice we start with the empty string as the prefix.
    SaveDictionaryHelper(root, "", dictFile);
}

/*
 * Function:  Makeempty function
 *
 * Precondition:
 * destroy helper needs to be working
 *
 * Postcondition:
 * empties the class object by deleting all the nodes starting from the root.
 * numwords is set to 0.
 */

void Dictionary::MakeEmpty() {
    destroyHelper(root);
    root = new Node;
    numWords = 0;
}

/*
 * Function:  isword function
 *
 * Precondition:
 * string word is passed in the parameter to check if the word exist.
 *
 * Postcondition:
 * traverse through the string and check if the letters are nodes.
 * at the very last letter it will check if isWord is true or false and return it.
 */

bool Dictionary::IsWord(string word) {
    Node * curr = root;
    for(int i =0; i< word.length();i++){
        int index  = word[i] - 'a';
        if(curr->child[index] == nullptr){
            return false;
        }
        curr = curr->child[index];
    }
    return curr->isWord;
}

/*
 * Function:  isprefix function
 *
 * Precondition:
 * string word is passed in the parameter to check if it is a prefix of an existing word
 *
 * Postcondition:
 * traverse through the string and check if the letters are nodes.
 * if all letters are nodes then it will return true otherwise it will return false
 */
bool Dictionary::IsPrefix(string word) {
    Node * curr = root;
    for(int i =0; i< word.length();i++){
        int index  = word[i] - 'a';
        if(index<0 || index>26){
            throw DictionaryError("Invalid character");
        }
        if(curr->child[index] == nullptr){
            return false;
        }
        curr = curr->child[index];
    }

    return true;
}

//return numWords
int Dictionary::WordCount() {
    return numWords;
}

/*
 * Function:  copyother function;
 *
 * Precondition:
 * needs an object passed in the parameter to be copied.
 * Makeempty and cophelper needs to be functioning
 *
 * Postcondition:
 * empties the current object then proceed to copy the class object pass by the
 * parameter. Uses copyhelper to copy the object by passing both roots.
 */
void Dictionary::copyOther(const Dictionary &otherDict) {
    MakeEmpty();
    copyHelper(root, otherDict.root);
    numWords = otherDict.numWords;


}

/*
 * Function:  destroyhelper function
 *
 * Precondition:
 * Needs a node to be passed inside the parameter
 *
 * Postcondition:
 * traverses through the tree starting with the node from the parameter
 * and deletes every node thats comes after the node from the parameter
 * using recursion.
 */
void Dictionary::destroyHelper(Dictionary::Node *thisTree) {
    if(thisTree == nullptr) {
        delete thisTree;
        return;
    }
    Node * curr = thisTree;
    for(int i = 0; i<NUM_CHARS;i++){
        if(curr->child[i]!= nullptr){
            destroyHelper(curr->child[i]);

        }
    }
    delete curr;
}

/*
 * Function:  copyhelper function
 *
 * Precondition:
 * using two nodes from two different class objects. Both
 * are passed by reference
 *
 * Postcondition:
 * traverses through both trees and thistree makes a deep copy of each nodes
 * that exist in othertree
 */
void Dictionary::copyHelper(Dictionary::Node *&thisTree, Dictionary::Node *otherTree) {
    if(otherTree == nullptr){
        thisTree = nullptr;
        return;
    }

    thisTree = new Node;
    thisTree->isWord = otherTree->isWord;
    for(int i = 0; i<NUM_CHARS;i++){
        copyHelper(thisTree->child[i], otherTree->child[i]);
    }


}

/*
 * Function:  savedictionaryhelper function
 *
 * Precondition:
 * empty string currprefix is passed in the parameter, along with the rootnode
 * ofstream outfile of a text file to save the words.
 *
 * Postcondition:
 * traverses through the string checking each letter and adding them to the empty string
 * the word is save as soon as curr->isWord ==  true.
 */

void Dictionary::SaveDictionaryHelper(Dictionary::Node *curr, string currPrefix, ofstream &outFile) {
//    ofstream out(outFile);
    if (curr == nullptr){
        return;
    }
    if (curr->isWord)
        outFile << currPrefix <<"\n";

    for (int i = 0; i < NUM_CHARS; ++i){
        if (curr->child[i]!= nullptr) {
            char letter = i + 'a';
            cout<<letter<<endl;
            SaveDictionaryHelper(curr->child[i], currPrefix + letter, outFile);



        }
    }
}
