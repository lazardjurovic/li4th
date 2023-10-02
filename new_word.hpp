#include <string>
#include <iostream>
#include <vector>

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
        string getName(){ return name;};
        string getWords(){ return words;};


    private:
        string name;
        string words;

};

string userWord(vector<NewWord> words, string n){
    for(NewWord &nw : words){
        if(nw.getName().compare(n)==0){
            return nw.getWords(); 
        }
    }
    return "Not found";
}