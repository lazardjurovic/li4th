#include <iostream>
#include "variable.hpp"

Variable::Variable(string nam, int addr, int val)
{
    name = nam;
    address = addr;
    value = val;
}

int Variable::getAddress()
{
    return address;
};
int Variable::getValue()
{
    return value;
};
string Variable::getName()
{
    return name;
};

void Variable::setValue(int val)
{
    value = val;
}

void Variable::print()
{
    std::cout << "Variable " << name << " with value " << value << " is at: " << address << endl;
}