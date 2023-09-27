#include <string>
#include <iostream>
#include <cstdio>
#include <stack>
#include <vector>
#include <cmath>

using namespace std;

vector<string> base_words = {"!",".", "+", "-", "*","/", "*/", "0<", "0=", "0>", "1+", "1-", "2+", "2-",
"<", "=", ">", "?DUP", "DUP","ABS","AND","XOR","OR", "MAX", "MIN", "MOD", "OVER"};

int find_word(string w){
    for(int i=0; i<base_words.size();i++){
        if(base_words[i].compare(w) == 0){
            return 1;
        }
    }
    return 0;
}

void execute_word(string w, stack<int> &s,int* mem){

    if(w.compare(".")==0){
        if(s.size() != 0){
            printf("%d\n", s.top());
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

}