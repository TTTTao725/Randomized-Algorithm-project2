/*
 * @Author: Tao
 * @Date: 2023-04-17 11:13:30
 * @LastEditors: Tao
 * @LastEditTime: 2023-04-17 11:28:45
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
    Sketching sc(pow(2,7));
    HashTable ht(10);
    vector <key_value_pair> mylist;
    long long int true_sum = 0;
    for (int i = 0; i < 1000; i++){
        key_value_pair tmp = {i,i*i};
        mylist.push_back(tmp);
        true_sum += i*i * i*i;
    }

    for (int i = 0; i < 1000; i++){
        ht.update(mylist[i], 9, 10);
        sc.update(mylist[i], 7);
    }
    // key_value_pair tmp1 = {1,1};
    // key_value_pair tmp2 = {2,4};
    // key_value_pair tmp3 = {3,9};
    // key_value_pair tmp4 = {4,16};
    // sc.update(tmp1,7);
    // sc.update(tmp2,7);
    // sc.update(tmp3,7);
    // sc.update(tmp4,7);
    // cout << ht.query() << endl;
    cout << true_sum << endl;
    cout << fabs(sc.query() - ht.query()) / ht.query() << endl;
    return 0;
}