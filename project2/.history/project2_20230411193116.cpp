#include <iostream>
#include <list>
using namespace std;

const int TABLE_SIZE = 10;
// key value pair structure
struct key_value_pair
{
    int key;
    int value;
};

class HashTable {
private:
    list<key_value_pair> table[TABLE_SIZE]; // array of linked lists
    int hash(int key); // hash function
public:
    HashTable(); // constructor
    void insert(key_value_pair key); // insert a new key
    bool search(int key); // search for a key
    void display(); // display the hash table
};

HashTable::HashTable() {
    // initialize the linked lists in the table
    for (int i = 0; i < TABLE_SIZE; i++) {
        table[i] = list<key_value_pair>();
    }
}

int HashTable::hash(int key) {
    return key % TABLE_SIZE;
}

void HashTable::insert(key_value_pair pair) {
    int index = hash(pair.key);
    table[index].push_back(pair);
}

bool HashTable::search(int key) {
    int index = hash(key);
    int len = table[index].size();
    if (len == 0){
        return false;
    }
    for (int i = 0; i < len; i++) {
        if (*i->key == key) {
            return true;
        }
    }
    return false;
}

int main() {
    HashTable ht;
    // ht.insert(10);
    // ht.insert(20);
    // ht.insert(30);
    // ht.insert(40);
    // ht.insert(50);

    cout << "Search for key 20: " << ht.search(20) << endl;
    cout << "Search for key 60: " << ht.search(60) << endl;

    cout << sizeof(unsigned long int)*8 << endl;
    return 0;
}
