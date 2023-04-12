/*
 * @Author: Tao
 * @Date: 2023-04-10 23:01:25
 * @LastEditors: Tao
 * @LastEditTime: 2023-04-12 12:41:32
 * @Description: 
 * Email: 202203580@post.au.dk
 * Copyright (c) 2023 by Tao Tang, All Rights Reserved. 
 */
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
    key_value_pair e = {7, -48};

    ht.update(a);
    ht.update(b);
    ht.update(c);
    ht.update(d);
    ht.update(e);
    cout << ht.query() << endl;

    sc.update(a);
    sc.update(b);
    sc.update(c);
    sc.update(d);
    sc.update(e);
    cout << sc.query() << endl;

    return 0;
}
