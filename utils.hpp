#ifndef UTILS_HPP
#define UTILS_HPP

#include <vector>
#include <string>
#include <sstream>
#include "variable.hpp"
#include <stack>

std::vector<std::string> tokenize(std::string input){
        
        std::istringstream iss(input);
        
        std::vector<std::string> tokens;
        std::string token;

        while (iss >> token) {
            tokens.push_back(token);
        }   

        return tokens;
}

bool check_number(std::string str) {

   for (int i = 0; i < str.length(); i++)
   if (isdigit(str[i]) == false)
      return false;
      return true;

}

int isVariable(string name, vector<Variable> vars){
    
    for(Variable &v : vars){
        if(v.getName().compare(name)==0){
            return 1;
        }
    }

    return 0;

}

Variable *findVariable(string name, vector<Variable> vars){
    
    for(Variable &v : vars){
        if(v.getName().compare(name)==0){
            return &v;
        }
    }

    return NULL;

}

int indexOf(string w, vector<string> words){
    for(int i = 0; i< words.size(); i++){
        if(words[i].compare(w)==0){
            return i;
        }
    }
    return -1;
}

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

stack<int> reverseStack(stack<int> s) { 
    stack<int> reversed;
    
    while (!s.empty()) {
        int element = s.top();
        s.pop();
        reversed.push(element);
    }

    return reversed;
}

#endif