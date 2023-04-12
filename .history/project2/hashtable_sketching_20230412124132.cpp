#include <iostream>
#include <vector>
#include <random>
#include "project2.h"
using namespace std;

int main() {
    HashTable ht(pow(2,10));
    Sketching sc(pow(2,10));

    key_value_pair a = {0, 1};
    key_value_pair b = {1, 2};
    key_value_pair c = {2, 3};
    key_value_pair d = {0, -3};
    key_value_pair e = {7, -48}

    ht.update(a);
    ht.update(b);
    ht.update(c);
    ht.update(d);
    cout << ht.query() << endl;

    sc.update(a);
    sc.update(b);
    sc.update(c);
    sc.update(d);
    cout << sc.query() << endl;

    return 0;
}
