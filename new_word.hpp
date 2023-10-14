#ifndef NEW_WORD_HPP
#define NEW_WORD_HPP

#include <string>
#include <iostream>
#include <vector>

using namespace std;

//TODO: Implement body as string vector for easier manipulation

class NewWord{

    public:
        NewWord(string n, string w){
            name = n;
            words = w;
        };
        void print(){
            cout << name << " -> " << words << endl;
        };
        string getName(){ return name;};
        string getWords(){ return words;};


    private:
        string name;
        string words;

};

#endif