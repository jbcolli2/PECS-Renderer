//
// Created by Jeb Collins on 3/7/22.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <bitset>

int main()
{
    std::set<std::bitset<8>> s{};

    std::bitset<8> bits{0b0000100};
    s.insert(bits);

//    std::cout << *s.begin() << std::endl;
}