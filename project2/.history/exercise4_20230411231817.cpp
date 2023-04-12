#include <iostream>
#include <vector>
#include <random>
using namespace std;

//* key value pair structure
struct key_value_pair
{
    unsigned int key;
    int value;
};

//* Hashing with chaining to maintain ||f||^2 exactly

class HashTable {
private:
    int TABLE_SIZE = pow(2,10); //* table size
    int hash_a; //* store the hash function
    vector<key_value_pair> *table; //* array of linked lists
    void random_odd(); //* random odd integer generator
    unsigned int hash(unsigned int key, int l); //* hash function
public:
    HashTable(int n = pow(2,10));
    void update(key_value_pair pair); //* insert a new key
    int search(unsigned int key); //* search for a key
    void display(); //* display the hash table
    long int query();
};

void HashTable::random_odd(){
    // std::random_device rd;  // Seed the random number generator
    const uint32_t seed_value = 123456789;
    std::mt19937 gen(seed_value);
    std::uniform_int_distribution<uint32_t> dis(1, UINT32_MAX);  // Range is [1, 2^32 - 1)

    uint32_t rand_int = dis(gen);  // Generate a random 32-bit integer in the range [1, 2^32 -1)
    uint32_t odd_int = rand_int | 0x1;  // Set the least significant bit to 1 to get an odd number
    hash_a = odd_int;
}

HashTable::HashTable(int n): TABLE_SIZE(n), table(new vector<key_value_pair>[n]) {
    // initialize the linked lists in the table
    for (int i = 0; i < n; i++) {
        table[i] = vector<key_value_pair>();
    }
    random_odd();
}


unsigned int HashTable::hash(unsigned int key, int l=10) {
    if(l == 0){
        return 0;
    }
    return hash_a*key >> (32 - l);
}

void HashTable::update(key_value_pair pair) {
    int index = hash(pair.key);
    //* if this key is not in the list, add the pair
    int searched_index = search(pair.key);
    if (searched_index == -1){
        table[index].push_back(pair);
    }
    //* else add the new value to the value of the pair
    else{
        table[index][searched_index].value += pair.value;
    }
}

int HashTable::search(unsigned int key) {
    int index = hash(key);
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
        cout << "index: " << i << endl;
        // cout << "length: " << table[i].size() << endl;
        //* summing up the square values in this list
        for (const auto& element : table[i]){
            // cout << element.value << endl;
            tmp += element.value * element.value;
        }
    }
    return tmp;
}

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

//* Sketching the norm
class Sketching {
private:
    int LIST_SIZE = pow(2,10);
    int *skech_list;
    //* random integer generator
    void random_int();
    //* Mersenne mod
    unsigned int mersenne_mod(unsigned int x, unsigned int p = pow(2,31) - 1);
    //* store the hash function
    int hash_a;
    int hash_b;
    int hash_c;
    int hash_d;
    //* estimated hash functions h and g
    unsigned int hash_h(unsigned int x);
    unsigned int hash_g(unsigned int x);
public:
    Sketching(int n = pow(2,10));
    void update(key_value_pair pair);
    long int query();
};

unsigned int Sketching::mersenne_mod(unsigned int x, unsigned int p = pow(2,31) - 1){
    unsigned int y = (x & p) + (x >> 31);
    if (y >= p){
        y -= p;
    }
    return y;
}

void Sketching::random_int(){
    //* hash_a
    const uint32_t seed_value1 = 123456789;
    std::mt19937 gen(seed_value1);
    //* Mersenne prime p = 2^31 -1
    std::uniform_int_distribution<uint32_t> dis(0, pow(2,31) - 1);  // Range is [0, p - 1]
    uint32_t rand_int1 = dis(gen);  // Generate a random 32-bit integer in the range [0, p - 1]
    hash_a = rand_int1;

    //* hash_b
    const uint32_t seed_value2 = 276391965;
    std::mt19937 gen(seed_value2);
    //* Mersenne prime p = 2^31 -1
    std::uniform_int_distribution<uint32_t> dis(0, pow(2,31) - 1);  // Range is [0, p - 1]
    uint32_t rand_int2 = dis(gen);  // Generate a random 32-bit integer in the range [0, p - 1]
    hash_b = rand_int2;

    //* hash_c
    const uint32_t seed_value3 = 987654321;
    std::mt19937 gen(seed_value3);
    //* Mersenne prime p = 2^31 -1
    std::uniform_int_distribution<uint32_t> dis(0, pow(2,31) - 1);  // Range is [0, p - 1]
    uint32_t rand_int3 = dis(gen);  // Generate a random 32-bit integer in the range [0, p - 1]
    hash_c = rand_int3;

    //* hash_d
    const uint32_t seed_value4 = 526481905;
    std::mt19937 gen(seed_value4);
    //* Mersenne prime p = 2^31 -1
    std::uniform_int_distribution<uint32_t> dis(0, pow(2,31) - 1);  // Range is [0, p - 1]
    uint32_t rand_int4 = dis(gen);  // Generate a random 32-bit integer in the range [0, p - 1]
    hash_d = rand_int4;
}

//* h = (k >> 1) & (r - 1)
unsigned int Sketching::hash_h(unsigned int x){
    unsigned int k = mersenne_mod(hash_a * x + hash_b);
    k = mersenne_mod(k * x + hash_c);
    k = mersenne_mod(k * x + hash_d);
    return (k >> 1) & (int(pow(2, 10)) - 1);
}

//* g = 2 * (k & 1) - 1
unsigned int Sketching::hash_g(unsigned int x){
    unsigned int k = mersenne_mod(hash_a * x + hash_b);
    k = mersenne_mod(k * x + hash_c);
    k = mersenne_mod(k * x + hash_d);
    return 2 * (k & 1) - 1;
}

Sketching::Sketching(int n): LIST_SIZE(n), skech_list(new int[n]){
    random_int();
};

//* A[h(i)] = A[h(i)] + g(i) * value
void Sketching::update(key_value_pair pair){
    skech_list[hash_h(pair.key)] += hash_g(pair.key) * pair.value;
}

long int Sketching::query(){
    long int tmp = 0;
    for(int i = 0; i < LIST_SIZE; i++){
        tmp += skech_list[i] * skech_list[i];
    }
    return tmp;
}

int main() {
    HashTable ht(pow(2,10));
    Sketching sc(pow(2,10));

    key_value_pair a = {0, 1};
    key_value_pair b = {1, 2};
    key_value_pair c = {2, 3};

    ht.update(a);
    ht.update(b);
    ht.update(c);
    cout << ht.query() << endl;

    sc.update(a);
    sc.update(b);
    sc.update(c);
    cout << sc.query() << endl;

    return 0;
}
