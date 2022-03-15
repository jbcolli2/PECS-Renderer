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

    std::bitset<8> bits{0b00001000};
    std::bitset<8> b2{0b00000110};

    b2 |= bits;

    std::cout << b2 << std::endl;

    return 0;

}