/* CXX/hash_fn.cpp */
#include "hash_fn.hpp"
#include <string>
#include <cstdint>

// Integer Hash: Chaos-Mix Implementation
int myHashInt(int key, int m) {
    if (m <= 0) return 0;

    uint32_t h = static_cast<uint32_t>(key);

    // Stage 1: Golden Ratio Multiplication
    h *= 0x9E3779B9;

    // Stage 2: Xorshift Avalanche
    h ^= (h << 13);
    h ^= (h >> 17);
    h ^= (h << 5);

    // Stage 3: Final Mix
    h *= 0x85EBCA6B;

    return (int)(h % m);
}

// String Hash: Spiral-String Implementation
int myHashString(const std::string& str, int m) {
    if (m <= 0) return 0;

    uint32_t h = 0x12345678; // Custom seed

    for (int i = 0; i < (int)str.length(); i++) {
        unsigned char c = (unsigned char)str[i];

        // Custom "Rotate-XOR-Index" logic
        // Rotate Left 5 bits manually
        uint32_t rotated = (h << 5) | (h >> 27);
        
        // Mix char, index, and magic constant
        h = rotated ^ c ^ i ^ 0xDEADBEEF;
    }

    // Finalizer
    h ^= (h >> 16);

    return (int)(h % m);
}