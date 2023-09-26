#include <iostream>
#include <cstdio>
#include <stack>
#include <algorithm>
#include <array>

#include "utils.hpp"
#include "words.hpp"

using namespace std;

#define DATA_STACK_SIZE 256

stack<int> data_stack;
stack<string> return_stack;

int main(){
    
    int sp = 0;
    int rsp = DATA_STACK_SIZE;

    string input;
    vector<string> tokens;

    while(1){

        cin >> input;

        if(input.compare("exit") == 0){
            break;
        }else{

            tokens = tokenize(input);

            for (const std::string& t : tokens) {
                
                if(check_number(t)){

                    // if number push to stack    

                    if(data_stack.size() < DATA_STACK_SIZE){
                        data_stack.push(stoi(t));
                    }else{
                        cout << "Data stack out of space!" <<endl;
                    }

                }else{
                    // check if word

                    if(find_word(t)){
                        execute_word(t,data_stack);
                    }else{
                        cout << "Invalid word!" <<endl;
                    }

                }

            }

        }

    }

    return 0;
}