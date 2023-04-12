/*
 * @Author: Tao
 * @Date: 2023-04-10 23:01:25
 * @LastEditors: Tao
 * @LastEditTime: 2023-04-10 23:11:00
 * @Description: 
 * Email: 202203580@post.au.dk
 * Copyright (c) 2023 by Tao Tang, All Rights Reserved. 
 */
#include <iostream>
#include <list>
using namespace std;

const int TABLE_SIZE = 10;

class HashTable {
private:
    list<int> table[TABLE_SIZE]; // array of linked lists
    int hash(int key); // hash function
public:
    HashTable(); // constructor
    void insert(int key); // insert a new key
    void remove(int key); // remove a key
    bool search(int key); // search for a key
    void display(); // display the hash table
};

HashTable::HashTable() {
    // initialize the linked lists in the table
    for (int i = 0; i < TABLE_SIZE; i++) {
        table[i] = list<int>();
    }
}

int HashTable::hash(int key) {
    unsigned long long int product = key * 2654435761;
    return product >> 32; // return the upper 32 bits of the product
}

void HashTable::insert(int key) {
    int index = hash(key);
    table[index].push_back(key);
}

void HashTable::remove(int key) {
    int index = hash(key);
    table[index].remove(key);
}

bool HashTable::search(int key) {
    int index = hash(key);
    for (auto i = table[index].begin(); i != table[index].end(); i++) {
        if (*i == key) {
            return true;
        }
    }
    return false;
}

void HashTable::display() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        cout << i;
        for (auto j = table[i].begin(); j != table[i].end(); j++) {
            cout << " --> " << *j;
        }
        cout << endl;
    }
}

int main() {
    HashTable ht;
    ht.insert(10);
    ht.insert(20);
    ht.insert(30);
    ht.insert(40);
    ht.insert(50);
    ht.display();
    cout << "Search for key 20: " << ht.search(20) << endl;
    cout << "Search for key 60: " << ht.search(60) << endl;
    ht.remove(30);
    ht.display();
    return 0;
}