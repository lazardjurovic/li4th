#include <string>
#include <iostream>

using namespace std;

class NewWord{

    public:
        NewWord(string n, string w){
            name = n;
            words = w;
        };
        void print(){
            cout << "New word name: " << name << " and it's words are: " << words<<endl;
        };

    private:
        string name;
        string words;

};