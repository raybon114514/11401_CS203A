/* C/hash_fn.c */
#include "hash_fn.h"
#include <stdint.h>
#include <stdlib.h>

/*
 * 【獨家設計】Gemini Chaos-Mix Integer Hash
 * 設計思路：結合 Xorshift (隨機數生成器的概念) 與 
 * 黃金比例常數 (Golden Ratio) 的乘法攪拌。
 */
int myHashInt(int key, int m) {
    if (m <= 0) return 0;

    /* 1. 轉成 unsigned 避免負數位移問題 */
    uint32_t h = (uint32_t)key;

    /* 2. 注入混亂因子 (Magic Constant: 0x9E3779B9 是黃金分割數的變體) */
    h *= 0x9E3779B9;

    /* 3. Xorshift 結構：讓位元發生雪崩效應 (Avalanche)
       這三步會讓原本的一個 bit 影響到其他所有 bit */
    h ^= (h << 13);
    h ^= (h >> 17);
    h ^= (h << 5);

    /* 4. 最後再乘一次另一個大質數，確保徹底打散 */
    h *= 0x85EBCA6B;

    /* 5. 映射回 Table Size */
    return (int)(h % m);
}

/*
 * 【獨家設計】Gemini Spiral-String Hash
 * 設計思路：除了字元本身，還把「位置索引(i)」也捲進去運算，
 * 並且引入類似密碼學的「循環位移 (Rotate)」。
 */
int myHashString(const char* str, int m) {
    if (m <= 0 || str == NULL) return 0;

    uint32_t h = 0x12345678; /* 自定義的初始種子 */
    
    for (int i = 0; str[i] != '\0'; i++) {
        unsigned char c = (unsigned char)str[i];

        /* 核心公式：
           1. (h << 5) | (h >> 27): 這是 Circular Rotate Left 5 bits
           2. ^ c: 混入當前字元
           3. ^ i: 混入當前字元的位置 (讓 "ab" 和 "ba" 產生劇烈差異)
           4. + 0xDEADBEEF: 加一點魔術常數調味
        */
        h = ((h << 5) | (h >> 27)); // 旋轉
        h = h ^ c ^ i ^ 0xDEADBEEF; // 混淆
    }

    /* 為了保險，最後再來一次 Xorshift */
    h ^= (h >> 16);

    return (int)(h % m);
}