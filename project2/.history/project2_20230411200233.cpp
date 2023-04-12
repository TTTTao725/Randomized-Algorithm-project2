#include <iostream>
#include <vector>
using namespace std;

const int TABLE_SIZE = 10;
//* key value pair structure
struct key_value_pair
{
    int key;
    int value;
};

class HashTable {
private:
    vector<key_value_pair> table[TABLE_SIZE]; //* array of linked lists
    int hash(int key); //* hash function
public:
    HashTable();
    void update(key_value_pair key); //* insert a new key
    int search(int key); //* search for a key
    void display(); //* display the hash table
    long int query();
};

HashTable::HashTable() {
    // initialize the linked lists in the table
    for (int i = 0; i < TABLE_SIZE; i++) {
        table[i] = vector<key_value_pair>();
    }
}

int HashTable::hash(int key) {
    return key % TABLE_SIZE;
}

void HashTable::update(key_value_pair pair) {
    int index = hash(pair.key);
    //* if this key is not in the list, add the pair
    if (search(pair.key) == -1){
        table[index].push_back(pair);
    }
    //* else add the new value to the value of the pair
    else{
        table[index]
    }
}

int HashTable::search(int key) {
    int index = hash(key);
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
    key_value_pair c = {0, 3};
    ht.update(a);
    ht.update(b);
    // ht.insert(10);
    // ht.insert(20);
    // ht.insert(30);
    // ht.insert(40);
    // ht.insert(50);

    cout << "Search for key 0: " << ht.search(0) << endl;
    cout << "Search for key 1: " << ht.search(1) << endl;
    cout << "Search for key 2: " << ht.search(2) << endl;
    cout << ht.query() << endl;
    ht.update(c);
    cout << "Search for key 0: " << ht.search(0) << endl;
    cout << ht.query() << endl;
    return 0;
}
