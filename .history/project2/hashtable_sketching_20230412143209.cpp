/*
 * @Author: Tao
 * @Date: 2023-04-10 23:01:25
 * @LastEditors: Tao
 * @LastEditTime: 2023-04-12 14:32:09
 * @Description: 
 * Email: 202203580@post.au.dk
 * Copyright (c) 2023 by Tao Tang, All Rights Reserved. 
 */
#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include "project2.h"
using namespace std;
using namespace std::chrono;


int main() {
    HashTable ht(pow(2,10));
    Sketching sc7(pow(2,7));
    Sketching sc10(pow(2,10));
    Sketching sc20(pow(2,20));
    //vector<vector<key_value_pair>> test;
    //* 23 experiments
    for (int i = 0; i < 23; i++){
        //* n = 2^N, N = 6,...,28
        int N = pow(2, i+6);
        //* hashing with chaining
        auto time_stamp1 = high_resolution_clock::now();
        for (int j = 0; j < N; j++){
            key_value_pair tmp = {j % N, 1};
            ht.update(tmp);
        }
        auto time_stamp2 = high_resolution_clock::now();
        //* sketching: r = 2^7
        for (int j = 0; j < N; j++){
            key_value_pair tmp = {j % N, 1};
            sc7.update(tmp);
        }
        auto time_stamp3 = high_resolution_clock::now();
        //* sketching: r = 2^10
        for (int j = 0; j < N; j++){
            key_value_pair tmp = {j % N, 1};
            sc10.update(tmp);
        }
        auto time_stamp4 = high_resolution_clock::now();
        //* sketching: r = 2^20
        for (int j = 0; j < N; j++){
            key_value_pair tmp = {j % N, 1};
            sc20.update(tmp);
        }
        auto time_stamp5 = high_resolution_clock::now();
    }
    return 0;
}
