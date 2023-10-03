#ifndef VARIABLE_HPP
#define VARIABLE_HPP

#include <string>

using namespace std;

class Variable{

    private:
        string name;
        int address;
        int value;
    public:
        Variable(string nam, int addr, int val);
        int getAddress();
        int getValue();
        string getName();
        void setValue(int val);
        void print();

};

#endif