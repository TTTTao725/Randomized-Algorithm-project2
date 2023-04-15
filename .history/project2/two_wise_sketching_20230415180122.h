/*
 * @Author: Tao
 * @Date: 2023-04-15 17:52:26
 * @LastEditors: Tao
 * @LastEditTime: 2023-04-15 18:00:40
 * @Description: 
 * Email: 202203580@post.au.dk
 * Copyright (c) 2023 by Tao Tang, All Rights Reserved. 
 */
#include <iostream>
#include <vector>
#include <random>
using namespace std;

//*64 bits

//* key value pair structure
struct key_value_pair
{
    unsigned int key;
    int value;
};

//* Sketching the norm
class Sketching {
private:
    int LIST_SIZE = pow(2,10);
    int *sketch_list;
    //* random integer generator
    void random_int();
    //* Mersenne mod
    unsigned int mersenne_mod(unsigned int x, unsigned int p = pow(2,31) - 1);
    //* store the hash function
    int hash_a;
    int hash_b;
public:
    Sketching(int n = pow(2,10));
    //* estimated hash functions h and g
    unsigned int hash_h(unsigned int x, unsigned int r);
    unsigned int hash_g(unsigned int x);
    unsigned int hash_h_modulo(unsigned int x, unsigned int r);
    unsigned int hash_g_modulo(unsigned int x);
    void update(key_value_pair pair, unsigned int r);
    long int query();
    void clear();
};

unsigned int Sketching::mersenne_mod(unsigned int x, unsigned int p){
    unsigned int y = (x & p) + (x >> 31);
    if (y >= p){
        y -= p;
    }
    return y;
}

void Sketching::random_int(){
    //* hash_a
    const unsigned int seed_value = 123456789;
    std::mt19937_64 gen(seed_value);
    std::uniform_int_distribution<uint64_t> dis(0, (uint16_t) - 1);  
    uint64_t rand_int1 = dis(gen);  // Generate a random 64-bit integer in the range [0, p - 1]
    hash_a = rand_int1;

    //* hash_b
    uint64_t rand_int2 = dis(gen);  // Generate a random 64-bit integer in the range [0, p - 1]
    hash_b = rand_int2;
}

//* h = (k >> 1) & (r - 1)
unsigned int Sketching::hash_h(unsigned int x, unsigned int r){
    unsigned int k = mersenne_mod(hash_a * x + hash_b);
    k = mersenne_mod(k * x + hash_c);
    k = mersenne_mod(k * x + hash_d);
    return (k >> 1) & (r - 1);
}

//* g = 2 * (k & 1) - 1
unsigned int Sketching::hash_g(unsigned int x){
    unsigned int k = mersenne_mod(hash_a * x + hash_b);
    k = mersenne_mod(k * x + hash_c);
    k = mersenne_mod(k * x + hash_d);
    return 2 * (k & 1) - 1;
}

unsigned int Sketching::hash_h_modulo(unsigned int x, unsigned int r){
    //* mersenne prime
    unsigned int p = (pow(2,31) - 1);
    unsigned int k = (hash_a * x + hash_b) % p;
    k = (k * x + hash_c) % p;
    k = (k * x + hash_d) % p;
    return (k >> 1) & (r - 1);
}

unsigned int Sketching::hash_g_modulo(unsigned int x){
    //* mersenne prime
    unsigned int p = (pow(2,31) - 1);
    unsigned int k = (hash_a * x + hash_b) % p;
    k = (k * x + hash_c) % p;
    k = (k * x + hash_d) % p;
    return 2 * (k & 1) - 1;
}

Sketching::Sketching(int n): LIST_SIZE(n), sketch_list(new int[n]()){
    random_int();
};

//* A[h(i)] = A[h(i)] + g(i) * value
void Sketching::update(key_value_pair pair, unsigned int r){
    sketch_list[hash_h(pair.key, r)] += hash_g(pair.key) * pair.value;
}

long int Sketching::query(){
    long int tmp = 0;
    for(int i = 0; i < LIST_SIZE; i++){
        tmp += sketch_list[i] * sketch_list[i];
    }
    return tmp;
}

void Sketching::clear(){
    //* free up the memory
    delete[] sketch_list;
    sketch_list = nullptr;
    //* reallocate list to a piece of memory
    sketch_list = new int[LIST_SIZE]();
}