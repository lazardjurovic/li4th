#include <string>
#include <iostream>
#include <cstdio>
#include <stack>

using namespace std;

string base_words[] = {".", "+", "-", "*","/"};

int find_word(string w){
    for(int i=0; i<5;i++){
        if(base_words[i].compare(w) == 0){
            return 1;
        }
    }
    return 0;
}

void execute_word(string w, stack<int> &s){

    if(w.compare(".")==0){
        if(s.size() != 0){
            printf("%d", s.top());
            s.pop();
        }else{
            printf("Data stack is empty!\n");
        }
    }else if(w.compare("+")==0){
        int res = s.top();
        s.pop();
        res+= s.top();
        s.pop();
        s.push(res);
    }else if(w.compare("-")==0){
        int res = s.top();
        s.pop();
        res-= s.top();
        s.pop();
        s.push(res);
    }else if(w.compare("*")==0){
        int res = s.top();
        s.pop();
        res*= s.top();
        s.pop();
        s.push(res);
    }
    else if(w.compare("+")==0){
        int res = s.top();
        s.pop();
        res/= s.top();
        s.pop();
        s.push(res);
    }

}