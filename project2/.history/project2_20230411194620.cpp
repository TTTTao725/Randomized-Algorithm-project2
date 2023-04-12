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
    long int summingup();
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
    for (const auto& element : table[index]) {
        if (element.key == key) {
            return true;
        }
    }
    return false;
}

long int HashTable::summingup(){
    long int tmp = 0;
    //* run through all the lists in the table
    for(int i = 0; i < TABLE_SIZE; i++){
        //* if the current list is empty, pass thin iteration
        if(table[i].size() == 0){
            continue;
        }
        //* summing up the square values in this list
        for (const auto& element : table[i]){
            tmp += element.value * element.value;
        }
    }
    return tmp;
}

int main() {
    HashTable ht;
    key_value_pair a = {0, 1};
    key_value_pair b = {1, 2};
    ht.insert(a);
    ht.insert(b);
    // ht.insert(10);
    // ht.insert(20);
    // ht.insert(30);
    // ht.insert(40);
    // ht.insert(50);

    cout << "Search for key 0: " << ht.search(0) << endl;
    cout << "Search for key 1: " << ht.search(1) << endl;
    cout << "Search for key 2: " << ht.search(2) << endl;
    cout << ht.summingup() << endl;
    return 0;
}
