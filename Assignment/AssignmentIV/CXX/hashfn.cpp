#include "hash_fn.hpp"
#include <iostream>
#include <string>
#include <cmath>

/*
 * Hash function for Integer Keys
 */
int hashInt(int key, int m) {
    if (m <= 0) return 0;
    
    int index = key % m;
    if (index < 0) index += m;
    
    return index;
}

/*
 * Hash function for String Keys
 */
int hashStr(std::string str, int m) {
    if (m <= 0) return 0;

    unsigned long hash = 0;
    int p = 31;

    for (char c : str) {
        hash = (hash * p + c) % m;
    }

    return (int)hash;
}