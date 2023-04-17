/*
 * @Author: Tao
 * @Date: 2023-04-17 11:13:30
 * @LastEditors: Tao
 * @LastEditTime: 2023-04-17 12:16:43
 * @Description: 
 * Email: 202203580@post.au.dk
 * Copyright (c) 2023 by Tao Tang, All Rights Reserved. 
 */
#include <iostream>
#include <vector>
#include <random>
#include <cassert>
#include <chrono>
#include <fstream>
#include "project2.h"
using namespace std;
using namespace std::chrono;

int main(){
    Sketching sc(pow(2,10));
    HashTable ht(10);
    vector <key_value_pair> mylist;
    long long int true_sum = 0;
    for (uint64_t i = 0; i < 1000; i++){
        key_value_pair tmp = {i,i*i};
        mylist.push_back(tmp);
        true_sum += i*i * i*i;
    }

    for (int i = 0; i < 1000; i++){
        ht.update(mylist[i], 9, 10);
        sc.update(mylist[i], pow(2,10));
    }
    long long int* sketch_list = sc.return_list();
    for (int i = 0; i < int(pow(2,10)); i++){
        cout << sketch_list[i] << endl;
    }
    cout << true_sum << endl;
    cout << ht.query() << endl;
    cout << sc.query() << endl;
    cout << fabs(sc.query() - true_sum) / true_sum << endl;
    ht.clear();
    sc.clear();
    return 0;
}