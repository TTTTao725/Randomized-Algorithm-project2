/*
 * @Author: Tao
 * @Date: 2023-04-10 23:01:25
 * @LastEditors: Tao
 * @LastEditTime: 2023-04-12 14:27:38
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
    Sketching sc1(pow(2,7));
    Sketching sc2(pow(2,10));
    Sketching sc3(pow(2,20));
    //vector<vector<key_value_pair>> test;
    //* 23 experiments
    for (int i = 0; i < 23; i++){
        //* n = 2^N, N = 6,...,28
        int N = pow(2, i+6);
        for (int j = 0; j < N; j++){
            key_value_pair tmp = {j % N, 1};
        }
    }
    return 0;
}
