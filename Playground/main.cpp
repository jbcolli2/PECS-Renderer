//
// Created by Jeb Collins on 3/7/22.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <bitset>

class A
{
private:
    int val;

public:
    A(int val) : val(val) {};
    friend int getVal(const A& a);
};

int getVal(const A& a) { return a.val;};



int main()
{

    A a{5};
    std::cout << getVal(a) << std::endl;

    return 0;

}