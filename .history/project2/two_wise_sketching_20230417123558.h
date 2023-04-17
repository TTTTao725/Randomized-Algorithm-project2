/*
 * @Author: Tao
 * @Date: 2023-04-15 17:52:26
 * @LastEditors: Tao
 * @LastEditTime: 2023-04-17 12:35:58
 * @Description: 
 * Email: 202203580@post.au.dk
 * Copyright (c) 2023 by Tao Tang, All Rights Reserved. 
 */
#include <iostream>
#include <vector>
#include <random>
#include "project2.h"
using namespace std;

//*64 bits
//* pair is defined as (i, i*i), so value also has to be uint64_t
struct key_value_pair_64bit
{
    uint64_t key;
    int value;
};

//* Sketching the norm
class Sketching_2wise {
private:
    int LIST_SIZE = pow(2,10);
    uint64_t *sketch_list;
    //* random integer generator
    void random_int();
    //* store the hash function
    int hash_a;
    int hash_b;
public:
    Sketching_2wise(int n = pow(2,10));
    //* estimated hash functions h and g
    unsigned int hash_h(uint64_t x, unsigned int r);
    int hash_g(uint64_t x);
    void update(key_value_pair_64bit pair, unsigned int r);
    uint64_t query();
    void clear();
    void reset_hash();
};


void Sketching_2wise::random_int(){
    //* hash_a 64-bit
    // const unsigned int seed_value = 123456789;
    // std::mt19937_64 gen(seed_value);
    std::random_device rd; // obtain a random seed from the system
    std::mt19937_64 gen(rd()); // 64-bit Mersenne Twister engine
    std::uniform_int_distribution<uint64_t> dis(0, (uint64_t) - 1);  
    uint64_t rand_int1 = dis(gen);  // Generate a random 64-bit integer in the range [0, p - 1]
    hash_a = rand_int1;

    //* hash_b 64-bit
    uint64_t rand_int2 = dis(gen);  // Generate a random 64-bit integer in the range [0, p - 1]
    hash_b = rand_int2;
}

//* h = (k >> 1) & (r - 1)
unsigned int Sketching_2wise::hash_h(uint64_t x, unsigned int r){
    unsigned int k = (hash_a * x + hash_b) >> 33;
    return (k >> 1) & (r - 1);
}

//* g = 2 * (k & 1) - 1
int Sketching_2wise::hash_g(uint64_t x){
    unsigned int k = (hash_a * x + hash_b) >> 33;
    return 2 * (k & 1) - 1;
}

Sketching_2wise::Sketching_2wise(int n): LIST_SIZE(n), sketch_list(new uint64_t[n]()){
    random_int();
};

//* A[h(i)] = A[h(i)] + g(i) * value
void Sketching_2wise::update(key_value_pair_64bit pair, unsigned int r){
    sketch_list[hash_h(pair.key, r)] += hash_g(pair.key) * pair.value;
}

uint64_t Sketching_2wise::query(){
    uint64_t tmp = 0;
    for(int i = 0; i < LIST_SIZE; i++){
        tmp += sketch_list[i] * sketch_list[i];
    }
    return tmp;
}

void Sketching_2wise::clear(){
    //* free up the memory
    delete[] sketch_list;
    sketch_list = nullptr;
    //* reallocate list to a piece of memory
    sketch_list = new uint64_t[LIST_SIZE]();
}

void Sketching_2wise::reset_hash(){
    random_int();
}