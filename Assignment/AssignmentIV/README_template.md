# Homework Assignment IV: Hash Function Design & Observation (C/C++ Version)

This assignment focuses on the design and observation of hash functions using C/C++. 
Students are expected to implement and analyze the behavior of hash functions, 
evaluate their efficiency, and understand their applications in computer science.

Developer: 彭睿謙 
Email: raypong6@gmail.com

## My Hash Function
### Integer Keys 
- Formula / pseudocode:
  ```text
      h *= 0x9E3779B9; // Golden Ratio
      h ^= (h << 13); h ^= (h >> 17); h ^= (h << 5); // Xorshift
      h *= 0x85EBCA6B; // Final Mix
      index = h % m;
  ```
- Rationale:I designed a custom method combining Multiplicative Hashing with Xorshift. By multiplying with a Golden Ratio constant and applying bitwise shifts, I induce an "Avalanche Effect". This ensures that sequential keys (e.g., 21, 22) map to widely different indices, rather than sequential ones.

### Non-integer Keys
- Formula / pseudocode:
  ```text
  h = ((h << 5) | (h >> 27)) ^ char ^ index ^ 0xDEADBEEF;
  ```
- Rationale:I designed a "Spiral" loop that incorporates Circular Rotation and Index Mixing. Unlike standard hashing, this method XORs the position (i) of the character into the hash, ensuring that anagrams (like "cat" and "act") produce completely different results.

## Experimental Setup
- Table sizes tested (m): 10, 11, 37
- Test dataset:
  - Integers: 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60
  - Strings: "cat", "dog", "bat", "cow", "ant", "owl", "bee", "hen", "pig", "fox"
- Compiler: GCC and G++
- Standard: C23 and C++23

## Results
| Table Size (m) | Index Sequence         | Observation              |
|----------------|------------------------|--------------------------|
| 10             | 9, 8, 9, 0, 3...        | Best Distribution: For strings, there were Zero Collisions. For integers, collisions were significantly reduced compared to m=10. |
| 11             | 9, 0, 9, 4, 9...      | Clustered: Despite being prime, index 9 was still heavily targeted (keys 21, 23, 25, 27).  |
| 37             | 23, 30, 27, 2...    | Best Distribution: For strings, there were Zero Collisions. For integers, collisions were significantly reduced compared to m=10.             |

## Compilation, Build, Execution, and Output

### Compilation
- The project uses a comprehensive Makefile that builds both C and C++ versions with proper flags:
  ```bash
  # Build both C and C++ versions
  make all
  
  # Build only C version
  make c
  
  # Build only C++ version
  make cxx
  ```

### Manual Compilation (if needed)
- Command for C:
  ```bash
  gcc -std=c23 -Wall -Wextra -Wpedantic -g -o C/hash_function C/main.c C/hash_fn.c
  ```
- Command for C++:
  ```bash
  g++ -std=c++23 -Wall -Wextra -Wpedantic -g -o CXX/hash_function_cpp CXX/main.cpp CXX/hash_fn.cpp
  ```

### Clean Build Files
- Remove all compiled files:
  ```bash
  make clean
  ```

### Execution
- Run the compiled binary:
  ```bash
  ./hash_function
  ```
  or
  ```bash
  ./hash_function_cpp
  ```

### Result Snapshot
- Example output for integers:
  ```
  === Hash Function Observation (C Version) ===

  === Table Size m = 10 ===
  Key     Index
  -----------------
  21      9
  22      8
  23      9
  24      0
  25      3
  26      5
  27      9
  28      5
  29      2
  30      8
  51      4
  52      9
  53      5
  54      9
  55      7
  56      0
  57      7
  58      2
  59      9
  60      7
  ```
- Observation: Heavy clustering at index 9.
  ```
  === Table Size m = 11 ===
  Key     Index
  -----------------
  21      9
  22      0
  23      9
  24      4
  25      9
  26      2
  27      9
  28      1
  29      7
  30      1
  51      2
  52      3
  53      1
  54      6
  55      10
  56      2
  57      3
  58      8
  59      5
  60      7

  === Table Size m = 37 ===
  Key     Index
  -----------------
  21      23
  22      30
  23      27
  24      2
  25      8
  26      33
  27      1
  28      35
  29      2
  30      21
  51      20
  52      20
  53      10
  54      23
  55      14
  56      33
  57      31
  58      21
  59      8
  60      16
  ```
- Observation: Much better spread.  
- Example output for strings:
  ```
  === String Hash (m = 10) ===
  Key     Index
  -----------------
  cat     2
  dog     5
  bat     6
  cow     3
  ant     4
  owl     2
  bee     3
  hen     2
  pig     7
  fox     2

  === String Hash (m = 11) ===
  Key     Index
  -----------------
  cat     6
  dog     10
  bat     7
  cow     8
  ant     10
  owl     5
  bee     7
  hen     6
  pig     6
  fox     2

  === String Hash (m = 37) ===
  Key     Index
  -----------------
  cat     9
  dog     15
  bat     34
  cow     4
  ant     13
  owl     25
  bee     2
  hen     19
  pig     3
  fox     7
  ...
  ```

- Observation: PERFECT distribution. 10 keys mapped to 10 unique indices.

## Analysis
- Table Size Impact ($m$):
  -m=10: The results were poor. For integers, 21, 23, 27, 52... all mapped to 9. For strings, "cat", "owl", "hen", "fox" all mapped to 2. This proves that small, even table sizes exacerbate collisions.
  -m=37: This was the most effective size. Specifically for strings, I achieved a perfect hash with zero collisions, where every animal name got a unique index.
- Algorithm Performance:
  -My "Chaos-Mix" integer algorithm successfully broke the "last digit" pattern (e.g., 21 did not map to 1). However, it revealed that without a large enough table size ($m$), collisions are unavoidable due to the Pigeonhole Principle.
  -My "Spiral-String" algorithm worked exceptionally well with $m=37$, showing that mixing the index of characters into the calculation effectively separates similar words.
- Conclusion:
To minimize collisions, a sophisticated hash function (like the one implemented here using bitwise rotation and golden ratio mixing) is helpful, but it must be paired with a sufficiently large, prime number table size (like 37 or larger) to be truly effective.

## Reflection
1. **Complexity vs. Table Size**: I learned that even a very complex hash function (Chaos-Mix) will still fail if the table size ($m=10$) is too small and crowded.
2. **String Hashing Success**: The "Spiral" logic which includes the character's index i proved very powerful, as it successfully distinguished all 10 string keys when $m=37$.
3. **Data Observation**: Real data often looks messier than theory. Seeing 21 map to 9 instead of 1 confirmed my custom logic was working, but seeing collisions persist at $m=11$ taught me that hash collisions are hard to eliminate completely.
