#include <string>
#include <iostream>
#include <cstdio>
#include <stack>
#include <vector>
#include <cmath>

#include "variable.hpp"
#include "utils.hpp"
#include "new_word.hpp"

using namespace std;

vector<string> base_words = {"WORDS", "!", ".", "+", "-", "*", "/", "*/", "*/MOD", "0<", "0=", "0>", "1+", "1-", "2+", "2-",
                             "<", "=", ">", ">R", "?DUP", "DUP", "ABS", "AND", "XOR", "OR", "MAX", "MIN", "MOD", "OVER", "SWAP", "DROP", "MOVE",
                             "NEGATE", "PICK", "@", "DEPTH", "FILL", "VARIABLE", ":", ";", "IF", "ELSE", "THEN", "R>", "R@", "DO", "LOOP", "I"};

vector<Variable> variables;
vector<string> word_def; // definition of new word in regards of existing words
vector<NewWord> user_words; // definitions of all user words

queue<string> program;

stack<int> data_stack;
stack<int> return_stack;

stack<int> flow_stack;
stack<int> control_stack;
int program_counter = 1;

int executing = 1;

int userWord(string n, vector<NewWord> words){
    for(NewWord &nw : words){
        if(nw.getName().compare(n)==0){
            return 1;
        }
    }
    return 0;
}

int isWord(string w)
{
    for (int i = 0; i < base_words.size(); i++)
    {
        if (base_words[i].compare(w) == 0)
        {
            return 1;
        }
    }
    return 0;
}

void execute_word(string w, stack<int> &s, stack<int> &rs, int *mem, int &mem_end)
{

    if (w.compare("WORDS") == 0)
    {
        for (NewWord &nw : user_words)
        {
            nw.print();
        }
        program_counter++;
    }
    else if (w.compare(".") == 0)
    {
        if (s.size() != 0)
        {
            printf("%d\n", s.top());
            s.pop();
        }
        else
        {
            printf("Data stack is empty!\n");
        }
        program_counter++;
    }
    else if (w.compare("+") == 0)
    {
        int res = s.top();
        s.pop();
        res += s.top();
        s.pop();
        s.push(res);
        program_counter++;
    }
    else if (w.compare("-") == 0)
    {
        int res = s.top();
        s.pop();
        res -= s.top();
        s.pop();
        s.push(res);
        program_counter++;
    }
    else if (w.compare("*") == 0)
    {
        int res = s.top();
        s.pop();
        res *= s.top();
        s.pop();
        s.push(res);
        program_counter++;
    }
    else if (w.compare("/") == 0)
    {
        int res = s.top();
        s.pop();
        res /= s.top();
        s.pop();
        s.push(res);
        program_counter++;
    }
    else if (w.compare("*/") == 0)
    {
        int res = s.top();
        s.pop();
        res *= s.top();
        s.pop();
        res /= s.top();
        s.pop();
        s.push(res);
        program_counter++;
    }
    else if (w.compare("!") == 0)
    {
        int addr = s.top();
        s.pop();
        mem[addr] = s.top();
        s.pop();
        program_counter++;
    }
    else if (w.compare("*/MOD") == 0)
    {
        int n3 = s.top();
        s.pop();
        int n2 = s.top();
        s.pop();
        int n1 = s.top();
        s.pop();
        s.push((n1 * n2) % n3);
        s.push(n1 * n2 / n3);
        program_counter++;
    }
    else if (w.compare("+!") == 0)
    {
        int addr = s.top();
        s.pop();
        int n = s.top();
        s.pop();
        mem[addr] += n;
        program_counter++;
    }
    else if (w.compare("0<") == 0)
    {
        if (s.top() < 0)
        {
            s.pop();
            s.push(1);
        }
        else
        {
            s.pop();
            s.push(-1);
        }
        program_counter++;
    }
    else if (w.compare("0=") == 0)
    {
        if (s.top() < 0)
        {
            s.pop();
            s.push(1);
        }
        else
        {
            s.pop();
            s.push(-1);
        }
        program_counter++;
    }
    else if (w.compare("0>") == 0)
    {
        if (s.top() > 0)
        {
            s.pop();
            s.push(1);
        }
        else
        {
            s.pop();
            s.push(-1);
        }
        program_counter++;
    }
    else if (w.compare("1+") == 0)
    {
        int res = ++s.top();
        s.pop();
        s.push(res);
        program_counter++;
    }
    else if (w.compare("1-") == 0)
    {
        int res = --s.top();
        s.pop();
        s.push(res);
        program_counter++;
    }
    else if (w.compare("2+") == 0)
    {
        int res = s.top() + 2;
        s.pop();
        s.push(res);
        program_counter++;
    }
    else if (w.compare("2-") == 0)
    {
        int res = s.top() - 2;
        s.pop();
        s.push(res);
        program_counter++;
    }
    else if (w.compare("<") == 0)
    {
        int a = s.top();
        s.pop();
        int b = s.top();
        s.pop();
        if (b < a)
        {
            s.push(1);
        }
        else
        {
            s.push(-1);
        }
        program_counter++;
    }
    else if (w.compare(">") == 0)
    {
        int a = s.top();
        s.pop();
        int b = s.top();
        s.pop();
        if (b > a)
        {
            s.push(1);
        }
        else
        {
            s.push(-1);
        }
        program_counter++;
    }
    else if (w.compare("=") == 0)
    {
        int a = s.top();
        s.pop();
        int b = s.top();
        s.pop();
        if (a == b)
        {
            s.push(1);
        }
        else
        {
            s.push(-1);
        }
        program_counter++;
    }
    else if (w.compare("DUP") == 0)
    {
        s.push(s.top());
        program_counter++;
    }
    else if (w.compare("?DUP") == 0)
    {
        if (s.top() != 0)
        {
            s.push(s.top());
        }
        program_counter++;
    }
    else if (w.compare("ABS") == 0)
    {
        int res = abs(s.top());
        s.pop();
        s.push(res);
        program_counter++;
    }
    else if (w.compare("AND") == 0)
    {
        int res = s.top();
        s.pop();
        res &= s.top();
        s.pop();
        s.push(res);
        program_counter++;
    }
    else if (w.compare("XOR") == 0)
    {
        int res = s.top();
        s.pop();
        res ^= s.top();
        s.pop();
        s.push(res);
        program_counter++;
    }
    else if (w.compare("OR") == 0)
    {
        int res = s.top();
        s.pop();
        res |= s.top();
        s.pop();
        s.push(res);
        program_counter++;
    }
    else if (w.compare(">R") == 0)
    {
        int n = s.top();
        s.pop();
        rs.push(n);
        program_counter++;
    }
    else if (w.compare("MAX") == 0)
    {
        int a = s.top();
        s.pop();
        int b = s.top();
        s.pop();
        if (a >= b)
        {
            s.push(a);
        }
        else
        {
            s.push(b);
        }
        program_counter++;
    }
    else if (w.compare("MIN") == 0)
    {
        int a = s.top();
        s.pop();
        int b = s.top();
        s.pop();
        if (a <= b)
        {
            s.push(a);
        }
        else
        {
            s.push(b);
        }
        program_counter++;
    }
    else if (w.compare("MOD") == 0)
    {
        int a = s.top();
        s.pop();
        int res = s.top() % a;
        s.pop();
        s.push(res);
        program_counter++;
    }
    else if (w.compare("OVER") == 0)
    {
        int a = s.top();
        s.pop();
        int b = s.top();
        s.push(a);
        s.push(b);
        program_counter++;
    }
    else if (w.compare("R>") == 0)
    {
        int n = rs.top();
        rs.pop();
        s.push(n);
        program_counter++;
    }
    else if (w.compare("R@") == 0)
    {
        int n = rs.top();
        s.push(n);
        program_counter++;
    }
    else if (w.compare("SWAP") == 0)
    {
        int a = s.top();
        s.pop();
        int b = s.top();
        s.pop();
        s.push(b);
        s.push(a);
        program_counter++;
    }
    else if (w.compare("DROP") == 0)
    {
        s.pop();
        program_counter++;
    }
    else if (w.compare("MOVE") == 0)
    {
        int addr1 = s.top();
        s.pop();
        int addr2 = s.top();
        s.pop();
        int n = s.top();
        s.pop();

        for (int i = 0; i < n; i++)
        {
            mem[addr2 + i] = mem[addr1 + i];
        }
        program_counter++;
    }
    else if (w.compare("NEGATE") == 0)
    {
        int n = s.top();
        s.pop();
        s.push(-n);
        program_counter++;
    }
    else if (w.compare("PICK") == 0)
    {
        int n = s.top();
        s.pop();
        s.push(findNthFromTop(s, n));
        program_counter++;
    }
    else if (w.compare("@") == 0)
    {
        int addr = s.top();
        s.pop();
        s.push(mem[addr]);
        program_counter++;
    }
    else if (w.compare("DEPTH") == 0)
    {
        s.push(s.size());
        program_counter++;
    }
    else if (w.compare("FILL") == 0)
    {
        int byte = s.top();
        s.pop();
        int n = s.top();
        s.pop();
        int addr = s.top();
        s.pop();
        if (n > 0)
        {
            for (int i = 0; i < n; i++)
            {
                mem[addr + i] = byte;
            }
        }

        program_counter++;
    }
    else if (w.compare("VARIABLE") == 0)
    {
        Variable var(queueNth(program,program_counter+1), mem_end, 0);
        variables.push_back(var);
        mem_end--;
        program_counter+=2;

        cout << "CREATED VAR: " << var.getName() << " PC: " << program_counter <<endl;
    }
    else if (w.compare("DO") == 0)
    {
        program_counter++;
        int start = s.top();
        s.pop();
        int limit = s.top();
        s.pop();
        control_stack.push(start);
        control_stack.push(limit);
        control_stack.push(program_counter);

        cout << "start: " << start << endl;
        cout << "limit: " << limit << endl;
        cout << "PC: " << program_counter << endl;
    }
    else if (w.compare("LOOP") == 0)
    {

        int pc = control_stack.top();
        control_stack.pop();
        int limit = control_stack.top();
        control_stack.pop();
        int i = control_stack.top();
        control_stack.pop();

        if (i == limit - 1)
        {
            program_counter++;
            // control_stack.pop();
            // control_stack.pop();
            // control_stack.pop();
        }
        else
        {
            program_counter = pc;
            i++;
        }

        control_stack.push(i);
        control_stack.push(limit);
        control_stack.push(pc);
    }
    else if (w.compare("I") == 0)
    {
        int pc = control_stack.top();
        control_stack.pop();
        int limit = control_stack.top();
        control_stack.pop();
        int i = control_stack.top();
        control_stack.pop();

        s.push(i);

        control_stack.push(i);
        control_stack.push(limit);
        control_stack.push(pc);
        program_counter++;
    }
    else if (w.compare(":") == 0)
    {
        executing = 0;
        program_counter++;

    }
    else if (w.compare(";") == 0)
    {

        executing=1;

        for(int i =program_counter-1; queueNth(program,i).compare(":")!=0;i--){
            word_def.push_back(queueNth(program,i));
        }
        reverse(word_def.begin(),word_def.end());

        // get first element for name
        string name = word_def.front();
        word_def.erase(word_def.begin());

        //add other elements into word body
        string def = "";

        for(string &s : word_def){
            def += s + " ";
        }

        NewWord nw(name,def);
        user_words.push_back(nw);

        program_counter++;

    }
    else if (w.compare("IF") == 0)
    {

        int n = s.top();
        s.pop();
        flow_stack.push(n);

        if (flow_stack.top() == 1)
        { // true
            executing = 1;
        }
        else
        { // false
            executing = 0;
        }
        program_counter++;

    }
    else if (w.compare("ELSE") == 0)
    {
        if (executing == 1)
        {
            executing = 0;
        }
        else
        {
            executing = 1;
        }
        program_counter++;


    }
    else if (w.compare("THEN") == 0)
    {
        if (!flow_stack.empty())
        {
            flow_stack.pop();
        }
        executing = 1;
        program_counter++;
    }
    else
    {
        cout << "Invalid word." << endl;
    }
}