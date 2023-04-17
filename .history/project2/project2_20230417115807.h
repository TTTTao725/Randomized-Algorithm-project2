/*
 * @Author: Tao
 * @Date: 2023-04-12 12:37:50
 * @LastEditors: Tao
 * @LastEditTime: 2023-04-17 11:57:54
 * @Description: 
 * Email: 202203580@post.au.dk
 * Copyright (c) 2023 by Tao Tang, All Rights Reserved. 
 */

#include <iostream>
#include <vector>
#include <random>
using namespace std;

//* key value pair structure
struct key_value_pair
{
    uint64_t key;
    int value;
};

//* Hashing with chaining to maintain ||f||^2 exactly

class HashTable {
private:
    int TABLE_SIZE = pow(2,5); //* table size
    int hash_a; //* store the hash function
    vector<key_value_pair> *table; //* array of linked lists
    void random_odd(int w=32); //* random odd integer generator
public:
    HashTable(int w = 32);
    //* [2^w] -> [2^(w-1)]
    unsigned int hash(unsigned int key, int l=10, int w=32); //* hash function
    void update(key_value_pair pair, int l=10, int w=32); //* insert a new key
    int search(unsigned int key, int l=10, int w=32); //* search for a key
    void display(); //* display the hash table
    long int query();
    void clear();
    void update_hash_a(int w=32);
    //* initialise an existing hash table to be a new hash table with 2^(w-1) size
    void initialise(int w=32);
    int get_table_size();
    int get_hash_a();
};

void HashTable::random_odd(int w){
    // std::random_device rd;  // Seed the random number generator
    const uint32_t seed_value = 987654321;
    std::mt19937 gen(seed_value);
    std::uniform_int_distribution<uint32_t> dis(1, (1u << w) - 1);  // Range is [1, 2^w - 1]

    uint32_t rand_int = dis(gen);  // Generate a random 32-bit integer in the range [1, 2^32 -1]
    uint32_t odd_int = rand_int | 1u;  // Set the least significant bit to 1 to get an odd number
    hash_a = odd_int;
}

//* initialise the table size as the same to the number of update
//* make the size of hashtable to be a half of the size of universe
HashTable::HashTable(int w): TABLE_SIZE(int(pow(2, w-1))), table(new vector<key_value_pair>[int(pow(2, w-1))]) {
    //* initialize the linked lists in the table
    for (int i = 0; i < pow(2, w-1); i++) {
        table[i] = vector<key_value_pair>();
    }
    //* uniformly pick a w-bit random odd integer
    random_odd(w);
}


unsigned int HashTable::hash(unsigned int key, int l, int w) {
    return floor(((hash_a*key % int((pow(2, w)))) >> (w - l)));
}

void HashTable::update(key_value_pair pair, int l, int w) {
    int index = hash(pair.key, l, w);
    //* if this key is not in the list, add the pair
    int searched_index = search(pair.key, w);
    if (searched_index == -1){
        table[index].push_back(pair);
    }
    //* else add the new value to the value of the pair
    else{
        table[index][searched_index].value += pair.value;
    }
}

int HashTable::search(unsigned int key, int l, int w) {
    int index = hash(key, l, w);
    // cout << index << endl;
    int len = table[index].size();
    //* if the list is empty, then return -1
    if (len == 0){
        return -1;
    }
    for (int i = 0; i < len; i++) {
        //* find it, return the index of this element in this list
        if (table[index][i].key == key) {
            return i;
        }
    }
    //* couldn't find it, return -1
    return -1;
}

long int HashTable::query(){
    long int tmp = 0;
    //* run through all the lists in the table
    for(int i = 0; i < TABLE_SIZE; i++){
        //* if the current list is empty, pass this iteration
        if(table[i].size() == 0){
            continue;
        }
        //cout << "index: " << i << endl;
        // cout << "length: " << table[i].size() << endl;
        //* summing up the square values in this list
        for (const auto& element : table[i]){
            // cout << element.value << endl;
            tmp += element.value * element.value;
        }
    }
    return tmp;
}

void HashTable::clear(){
    //* First, clear the vector pointed to by table
    table->clear();
    //* Then, deallocate the memory pointed to by table
    delete[] table;
    table = nullptr;
}

void HashTable::update_hash_a(int w){
    random_odd(w);
}

void HashTable::initialise(int w){
    //* reset the table size
    TABLE_SIZE = pow(2, w-1);
    //* initialise the hash table
    table = new vector<key_value_pair>[TABLE_SIZE];
    for (int i = 0; i < TABLE_SIZE; i++) {
        table[i] = vector<key_value_pair>();
    }
    //* repick an random odd to update the hash function
    random_odd(w);
}

int HashTable::get_table_size(){
    return TABLE_SIZE;
}

int HashTable::get_hash_a(){
    return hash_a;
}

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

//* Sketching the norm
class Sketching {
private:
    int LIST_SIZE = pow(2,10);
    long long int *sketch_list;
    //* random integer generator
    void random_int();
    //* Mersenne mod
    uint64_t mersenne_mod(uint64_t x, uint64_t p = pow(2,31) - 1);
    //* store the hash function
    uint64_t hash_a;
    uint64_t hash_b;
    uint64_t hash_c;
    uint64_t hash_d;
public:
    Sketching(int n = pow(2,10));
    //* estimated hash functions h and g
    unsigned int hash_h(uint64_t x, unsigned int r);
    int hash_g(uint64_t x);
    unsigned int hash_h_modulo(uint64_t x, unsigned int r);
    int hash_g_modulo(uint64_t x);
    void update(key_value_pair pair, unsigned int r);
    long int query();
    void clear();
    void reset_hash();
    long long int* return_list();
};

uint64_t Sketching::mersenne_mod(uint64_t x, uint64_t p){
    uint64_t y = (x & p) + (x >> 31);
    if (y >= p){
        y -= p;
    }
    return y;
}

void Sketching::random_int(){
    //* hash_a
    const uint64_t seed_value = 123456789;
    std::mt19937 gen(seed_value);
    //* Mersenne prime p = 2^31 -1
    std::uniform_int_distribution<uint64_t> dis(0, pow(2,31) - 1);  // Range is [0, p - 1]
    uint64_t rand_int1 = dis(gen);  // Generate a random 32-bit integer in the range [0, p - 1]
    hash_a = rand_int1;

    //* hash_b
    //* Mersenne prime p = 2^31 -1
    uint64_t rand_int2 = dis(gen);  // Generate a random 32-bit integer in the range [0, p - 1]
    hash_b = rand_int2;

    //* hash_c
    //* Mersenne prime p = 2^31 -1
    uint64_t rand_int3 = dis(gen);  // Generate a random 32-bit integer in the range [0, p - 1]
    hash_c = rand_int3;

    //* hash_d
    //* Mersenne prime p = 2^31 -1
    uint64_t rand_int4 = dis(gen);  // Generate a random 32-bit integer in the range [0, p - 1]
    hash_d = rand_int4;
}

//* h = (k >> 1) & (r - 1)
unsigned int Sketching::hash_h(uint64_t x, unsigned int r){
    unsigned int k = mersenne_mod(hash_a * x + hash_b);
    k = mersenne_mod(k * x + hash_c);
    k = mersenne_mod(k * x + hash_d);
    return (k >> 1) & (r - 1);
}

//* g = 2 * (k & 1) - 1
int Sketching::hash_g(uint64_t x){
    unsigned int k = mersenne_mod(hash_a * x + hash_b);
    k = mersenne_mod(k * x + hash_c);
    k = mersenne_mod(k * x + hash_d);
    return 2 * (k & 1) - 1;
}

unsigned int Sketching::hash_h_modulo(uint64_t x, unsigned int r){
    //* mersenne prime
    unsigned int p = (pow(2,31) - 1);
    unsigned int k = (hash_a * x + hash_b) % p;
    k = (k * x + hash_c) % p;
    k = (k * x + hash_d) % p;
    return (k >> 1) & (r - 1);
}

int Sketching::hash_g_modulo(uint64_t x){
    //* mersenne prime
    unsigned int p = (pow(2,31) - 1);
    unsigned int k = (hash_a * x + hash_b) % p;
    k = (k * x + hash_c) % p;
    k = (k * x + hash_d) % p;
    return 2 * (k & 1) - 1;
}

Sketching::Sketching(int n): LIST_SIZE(n), sketch_list(new long long int[n]()){
    random_int();
};

//* A[h(i)] = A[h(i)] + g(i) * value
void Sketching::update(key_value_pair pair, unsigned int r){
    // cout << hash_h(pair.key, r) << endl;
    // cout << hash_g(pair.key) << endl;
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
    sketch_list = new long long int[LIST_SIZE]();
}

void Sketching::reset_hash(){
    random_int();
}
long long int* Sketching::return_list(){
    return sketch_list;
}