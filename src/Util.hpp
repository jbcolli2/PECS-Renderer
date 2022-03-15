//
// Created by Jeb Collins on 3/3/22.
//

#ifndef PECS_RENDERER_UTIL_HPP
#define PECS_RENDERER_UTIL_HPP


#include <cstdint>
#include <bitset>
#include <typeinfo>
#include <algorithm>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>


namespace pecs
{
constexpr int MAX_COMPONENTS = 32;
using Signature = std::bitset<MAX_COMPONENTS>;








/***************** FindIndex  ******************
 * @brief Returns the index of an element found in a vector.  If element is
 *      not found in the vector, returns -1.  If the element is in the vector
 *      twice, it returns the index of the first occurence of the element.
 *
 * @param vector The vector we are searching for the element in.
 * @param element The element we are searching for
 *
 * @returns The index of the element if found.  Returns -1 if element is not found.
***************************************///
template<typename T>
int FindIndex(const std::vector<T> &vector, T element)
{
    auto iterator = std::find(vector.begin(), vector.end(), element);

    int index = std::distance(vector.begin(), iterator);
    if (index == vector.size())
        return -1;

    return index;
}


/***************** loadFile2String  ******************
 * @brief Opens the file at @path and loads returns the contents as a string.
 *
 * @param path The full path of the file to be opened.
 *
 * @returns The contents of the file at path.
******************************************************************/
std::string loadFile2String(const char *path);


} // end namespace pecs
#endif //PECS_RENDERER_UTIL_HPP
