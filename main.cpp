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
vector<NewWord> user_words;

int main()
{

    int sp = 0;
    int rsp = DATA_STACK_SIZE;
    int *memory = new int[MEMORY_SIZE];
    int mem_end = MEMORY_SIZE -1;

    string input;
    vector<string> tokens;
    string new_def = ""; // definition of new word in regards of existing words

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

            if (tokens[0].compare(":") == 0)
            {

                for (int j = 2; j < tokens.size(); j++)
                    new_def += tokens[j] + " ";

                NewWord nw(tokens[1], new_def);
                user_words.push_back(nw);

                new_def = "";
            }
            else
            {

                for (const std::string &t : tokens)
                {

                    if (check_number(t))
                    {

                        // if number push to stack

                        if (data_stack.size() < DATA_STACK_SIZE)
                        {
                            data_stack.push(stoi(t));
                        }
                        else
                        {
                            cout << "Data stack out of space!" << endl;
                        }
                    } else if(isVariable(t,variables)){
                        
                        // process variables
                        if(!creating_var)
                            data_stack.push(findVariable(t,variables)->getAddress());
                        else   
                            creating_var = 0;

                    }
                    else
                    {
                        // check if user defined word

                        string to_execute = userWord(user_words, t);

                        if (to_execute.compare("Not found") != 0)
                        { // if found
                            
                            vector<string> primitives = tokenize(to_execute);

                            for(string &prim : primitives){
                                execute_word(prim,tokens,data_stack,return_stack,memory,mem_end);
                            }

                        }
                        else // look up in predefined words
                        {

                            if (find_word(t))
                            {
                                execute_word(t, tokens ,data_stack, return_stack, memory,mem_end);
                            }
                            else
                            {
                                cout << "Invalid word!" << endl;
                            }
                        }
                    }
                }
            }
        }
    }

    delete memory;

    return 0;
}