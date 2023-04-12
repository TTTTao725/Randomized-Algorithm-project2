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

//* Sketching the norm
class Sketching {
private:
    int LIST_SIZE = pow(2,10);
    int *skech_list;
    void random_int(); //* random integer generator
    //* store the hash function
    int hash_a;
    int hash_b;
    int hash_c;
    int hash_d;
    
public:
    Sketching(int n = pow(2,10));
    void update(key_value_pair pair);
    long int query();
};

Sketching::Sketching(int n): LIST_SIZE(n), skech_list(new int[n]){

};
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
}

int main() {
    HashTable ht(pow(2,10));
    key_value_pair a = {0, 1};
    key_value_pair b = {1, 2};
    key_value_pair c = {2, 3};
    ht.update(a);
    ht.update(b);
    ht.update(c);
    // ht.search(0);
    // ht.search(1);
    // ht.search(2);
    // cout << "Search for key 0: " << ht.search(0) << endl;
    // cout << "Search for key 1: " << ht.search(1) << endl;
    // cout << "Search for key 2: " << ht.search(2) << endl;
    cout << ht.query() << endl;
    // ht.update(c);
    // cout << "Search for key 0: " << ht.search(0) << endl;
    // cout << ht.query() << endl;
    key_value_pair d = {4,1};
    key_value_pair e = {4,1};
    ht.update(d);
    ht.update(e);
    // cout << "Search for key 4: " << ht.search(4) << endl;
    cout << ht.query() << endl;
    cout << UINT32_MAX << endl;
    // cout << ht.query() << endl;
    return 0;
}
