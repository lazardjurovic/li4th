#include <string>
#include <iostream>
#include <cstdio>
#include <stack>
#include <vector>
#include <cmath>

#include "variable.hpp"

using namespace std;

vector<string> base_words = {"!",".", "+", "-", "*","/", "*/", "*/MOD","0<", "0=", "0>", "1+", "1-", "2+", "2-",
"<", "=", ">", "?DUP", "DUP","ABS","AND","XOR","OR", "MAX", "MIN", "MOD", "OVER", "SWAP", "DROP", "MOVE",
"NEGATE","PICK", "@", "DEPTH", "FILL", "VARIABLE"};

vector<Variable> variables;

int creating_var = 0;

int findNthFromTop(std::stack<int> st, int n) { // AI generated
    if ( n > st.size() || n<1) {
        std::cerr << "Invalid value of n or stack size." << std::endl;
        return -1; // Return an error value
    }

    std::vector<int> tempVec;

    // Pop elements from the stack and store them in a temporary vector
    while (!st.empty()) {
        tempVec.push_back(st.top());
        st.pop();
    }

    // Get the n-th element from the top
    int nthElement = tempVec[n];

    // Restore the original stack
    for (int i = tempVec.size() - 1; i >= 0; i--) {
        st.push(tempVec[i]);
    }

    return nthElement;
}

int find_word(string w){
    for(int i=0; i<base_words.size();i++){
        if(base_words[i].compare(w) == 0){
            return 1;
        }
    }
    return 0;
}

void execute_word(string w, vector<string> tokens,stack<int> &s, stack<int> &rs,int* mem, int &mem_end){

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
    else if(w.compare("/")==0){
        int res = s.top();
        s.pop();
        res/= s.top();
        s.pop();
        s.push(res);
    }else if(w.compare("*/")==0){
        int res = s.top();
        s.pop();
        res *= s.top();
        s.pop();
        res/= s.top();
        s.pop();
        s.push(res);
    }else if(w.compare("!")==0){
        int addr = s.top();
        s.pop();
        mem[addr] = s.top();
        s.pop();
        
    }else if(w.compare("*/MOD")==0){
        int n3 = s.top();
        s.pop();
        int n2 = s.top();
        s.pop();
        int n1 = s.top();
        s.pop();
        s.push((n1*n2)%n3);
        s.push(n1*n2/n3);
        
    }else if(w.compare("+!")==0){
        int addr = s.top();
        s.pop();
        int n = s.top();
        s.pop();
        mem[addr] += n;
    }else if(w.compare("0<")==0){
        if(s.top()<0){
            s.pop();
            s.push(1);
        }else{
            s.pop();
            s.push(1);
        }
 
    }
    else if(w.compare("0=")==0){
        if(s.top()<0){
            s.pop();
            s.push(1);
        }else{
            s.pop();
            s.push(1);
        }
    }
    else if(w.compare("0>")==0){
        if(s.top()<0){
            s.pop();
            s.push(1);
        }else{
            s.pop();
            s.push(1);
        }
    }else if(w.compare("1+")==0){
        int res = ++s.top();
        s.pop();
        s.push(res);
    }
    else if(w.compare("1-")==0){
        int res = --s.top();
        s.pop();
        s.push(res);
    }else if(w.compare("2+")==0){
        int res = s.top()+2;
        s.pop();
        s.push(res);
    }
    else if(w.compare("2-")==0){
        int res = s.top()-2;
        s.pop();
        s.push(res);
    }else if(w.compare("<")==0){
        int a = s.top();
        s.pop();
        int b = s.top();
        s.pop();
        if(a < b){
            s.push(1);
        }else{
            s.push(-1);
        }
    }
    else if(w.compare(">")==0){
        int a = s.top();
        s.pop();
        int b = s.top();
        s.pop();
        if(a > b){
            s.push(1);
        }else{
            s.push(-1);
        }
    }
    else if(w.compare("=")==0){
        int a = s.top();
        s.pop();
        int b = s.top();
        s.pop();
        if(a == b){
            s.push(1);
        }else{
            s.push(-1);
        }
    }else if(w.compare("DUP")==0){
        s.push(s.top());
    }
    else if(w.compare("?DUP")==0){
        if(s.top()!=0){
            s.push(s.top());
        }
    }else if(w.compare("ABS")==0){
        int res = abs(s.top());
        s.pop();
        s.push(res);
    }else if(w.compare("AND")==0){
        int res = s.top();
        s.pop();
        res&= s.top();
        s.pop();
        s.push(res);
    }else if(w.compare("XOR")==0){
        int res = s.top();
        s.pop();
        res^= s.top();
        s.pop();
        s.push(res);
    }
    else if(w.compare("OR")==0){
        int res = s.top();
        s.pop();
        res|= s.top();
        s.pop();
        s.push(res);
    }
     else if(w.compare("MAX")==0){
        int a = s.top();
        s.pop();
        int b = s.top();
        s.pop();
        if(a>=b){
            s.push(a);
        }else{
            s.push(b);
        }
    }
    else if(w.compare("MIN")==0){
        int a = s.top();
        s.pop();
        int b = s.top();
        s.pop();
        if(a<=b){
            s.push(a);
        }else{
            s.push(b);
        }
    }else if(w.compare("MOD")==0){
        int a = s.top();
        s.pop();
        int res = s.top()%a;
        s.pop();
        s.push(res);        
    }
    else if(w.compare("OVER")==0){
        int a = s.top();
        s.pop();
        int b = s.top();
        s.push(a);
        s.push(b);
    }
    else if(w.compare("SWAP")==0){
       int a = s.top();
       s.pop();
       int b = s.top();
       s.pop();
       s.push(a);
       s.push(b);
    }else if(w.compare("DROP")==0){
        s.pop();
    }else if(w.compare("MOVE")==0){
        int addr1 = s.top();
        s.pop();
        int addr2 = s.top();
        s.pop();
        int n = s.top();
        s.pop();

        for(int i = 0; i<n;i++){
            mem[addr2+i] = mem[addr1+i];
        }

    }else if(w.compare("NEGATE")==0){
        int n = s.top();
        s.pop();
        s.push(-n);

    }else if(w.compare("PICK")==0){
        int n = s.top();
        s.pop();
        s.push(findNthFromTop(s,n));
    }else if(w.compare("@")==0){
        int addr = s.top();
        s.pop();
        s.push(mem[addr]);
    }else if(w.compare("DEPTH")==0){
        s.push(s.size());
    }else if(w.compare("FILL")==0){
        int byte = s.top();
        s.pop();
        int n = s.top();
        s.pop();
        int addr = s.top();
        s.pop();
        if(n>0){
            for(int i=0;i<n;i++){
                mem[addr+i] = byte;
            }
        }
    }else if(w.compare("VARIABLE")==0){
        // first find where "VARIABLE" is in input line
        creating_var = 1;
        Variable var(tokens[1],mem_end,0);
        variables.push_back(var);
        mem_end--;
        
    }

}