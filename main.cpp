#include <iostream>
#include <cstdio>
#include <stack>
#include <algorithm>
#include <array>
#include <queue>

#include "utils.hpp"
#include "words.hpp"
#include "new_word.hpp"

using namespace std;

#define DATA_STACK_SIZE 256
#define MEMORY_SIZE 65536

extern int compile_mode;

int main()
{
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
                program.push(t);
            }

            while (program_counter <= program.size())
            {
                string word = queueNth(program, program_counter);

                if (check_number(word))
                {
                    if (executing){
                        program_counter++;
                        data_stack.push(stoi(word));
                    }
                }
                else if (isWord(word))
                {
                    if (executing)
                        execute_word(word,base_words,data_stack,return_stack,memory,mem_end);
                }else if(isVariable(word,variables)){
                    cout << "IS VARIABLE"<<endl;
                    data_stack.push(findVariable(word,variables)->getAddress());
                    program_counter++;

                }
                else
                {
                    cout << "Unknown word" << endl;
                }
            }

        }
    }

    delete memory;

    return 0;
}