#ifndef UTILS_HPP
#define UTILS_HPP

#include <vector>
#include <string>
#include <sstream>
#include "variable.hpp"
#include <stack>
#include <queue>


string queueNth(const std::queue<string>& originalQueue, int n) { 
    if (n < 1 || n > originalQueue.size()) {
        std::cerr << "Invalid value of n." << std::endl;
        return "Not found"; // Return an error value
    }

    std::queue<string> copyQueue = originalQueue;

    // Dequeue elements from the copy queue until the nth element is found
    for (int i = 1; i < n; i++) {
        copyQueue.pop();
    }

    // The nth element is now at the front of the copy queue
    return copyQueue.front();
}

void insertAtIndex(std::queue<std::string>& q, int index, const std::string& element) {
    std::queue<std::string> tempQueue;

    // Pop elements from the original queue and push them into the temporary queue
    while (index > 0 && !q.empty()) {
        tempQueue.push(q.front());
        q.pop();
        index--;
    }

    // Insert the new element at the specified index
    tempQueue.push(element);

    // Push the remaining elements from the temporary queue back into the original queue
    while (!tempQueue.empty()) {
        q.push(tempQueue.front());
        tempQueue.pop();
    }
}

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

void removeAtIndex(std::queue<std::string>& q, int index) {
    if (index < 0 || index >= q.size()) {
        // Invalid index, nothing to remove
        return;
    }

    std::queue<std::string> tempQueue;

    // Pop elements from the original queue and push them into the temporary queue, skipping the element at the specified index
    for (int i = 0; i < q.size(); i++) {
        if (i != index) {
            tempQueue.push(q.front());
        }
        q.pop();
    }

    // Copy elements back from the temporary queue to the original queue
    while (!tempQueue.empty()) {
        q.push(tempQueue.front());
        tempQueue.pop();
    }
}

void deleteLast(std::queue<std::string>& strQueue) {
    if (!strQueue.empty()) {
        int size = strQueue.size();
        for (int i = 0; i < size - 1; i++) {
            std::string frontElement = strQueue.front();
            strQueue.pop();
            strQueue.push(frontElement);
        }
        strQueue.pop(); // Remove the last element (newest)
    }
}

#endif