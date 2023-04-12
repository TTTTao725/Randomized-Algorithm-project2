/*
 * @Author: Tao
 * @Date: 2023-04-11 23:29:20
 * @LastEditors: Tao
 * @LastEditTime: 2023-04-12 12:55:09
 * @Description: 
 * Email: 202203580@post.au.dk
 * Copyright (c) 2023 by Tao Tang, All Rights Reserved. 
 */

#include "project2.h"
using namespace std;

void random_int(){
    //* hash_a
    const uint32_t seed_value = 123456789;
    std::mt19937 gen(seed_value);
    //* Mersenne prime p = 2^31 -1
    std::uniform_int_distribution<uint32_t> dis(0, pow(2,31) - 1);  // Range is [0, p - 1]
    uint32_t rand_int1 = dis(gen);  // Generate a random 32-bit integer in the range [0, p - 1]
    unsigned int hash_a = rand_int1;

    //* hash_b
    //* Mersenne prime p = 2^31 -1
    uint32_t rand_int2 = dis(gen);  // Generate a random 32-bit integer in the range [0, p - 1]
    unsigned int hash_b = rand_int2;

    //* hash_c
    //* Mersenne prime p = 2^31 -1
    uint32_t rand_int3 = dis(gen);  // Generate a random 32-bit integer in the range [0, p - 1]
    unsigned int hash_c = rand_int3;

    //* hash_d
    //* Mersenne prime p = 2^31 -1
    uint32_t rand_int4 = dis(gen);  // Generate a random 32-bit integer in the range [0, p - 1]
    unsigned int hash_d = rand_int4;
}

int main(){
    const int SIZE = pow(2, 10);
    HashTable ht(SIZE);
    Sketching sc(SIZE);
    //* test...
    for (int i = 0; i < int(pow(10, 6)); i++){
        ht.hash(i);
        sc.hash_h(i);
        sc.hash_g(i);
    }
    return 0;
}
