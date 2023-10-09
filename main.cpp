#include <iostream>
#include <cstdio>
#include <stack>
#include <algorithm>
#include <array>

#include "utils.hpp"
#include "words.hpp"
#include "new_word.hpp"

using namespace std;

#define DATA_STACK_SIZE 256
#define MEMORY_SIZE 65536

stack<int> data_stack;
stack<int> return_stack;

extern int compile_mode;

int main()
{

    int sp = 0;
    int rsp = DATA_STACK_SIZE;
    int *memory = new int[MEMORY_SIZE];
    int mem_end = MEMORY_SIZE - 1;

    string input;
    vector<string> tokens;

    while (1)
    {
        getline(cin, input);

        if (input.compare("exit") == 0)
        {
            break;
        }
        else
        {

            tokens = tokenize(input);

            for (string &t : tokens)
            {
                if (compile_mode)
                {
                    if(t.compare(";")==0){
                        execute_word(base_words[indexOf(";",base_words)],tokens,data_stack,return_stack,memory,mem_end);
                    }
                    else{
                        word_def.push_back(t);
                    }
                
                }else if(check_number(t)){
                    if(executing)
                        data_stack.push(stoi(t));
                }
                else if(isUserWord(t)){

                    // TODO: support multiple levels of definitions
                    // TODO: fix if to work with user words

                    string words = userWord(user_words,t);

                    vector<string> toks = tokenize(words);
                    for(string &tok : toks){
                        execute_word(tok, tokens, data_stack, return_stack, memory, mem_end);
                    }

                }else if(isWord(t) && t.compare("THEN")==0){
                    executing = 1;
                }
                else if (isWord(t))
                {   
                    if(executing)
                        return_stack.push(indexOf(t, base_words));
                }
                else
                {
                    cout << "Not recognised literal."<<endl;
                }

                // this block is placed here because executing some words can change return stack
                
                return_stack = reverseStack(return_stack);
                while (return_stack.size() > 0)
                {
                    if (!compile_mode)
                    {
                        if(executing){
                            execute_word(base_words[return_stack.top()], tokens, data_stack, return_stack, memory, mem_end);
                            return_stack.pop();
                        }
                    }
                    else
                    { // handle compile mode
                        //word_def.push_back(base_words[return_stack.top()]);
                        return_stack.pop();
                    }
                }
            }
        }
    }

    delete memory;

    return 0;
}