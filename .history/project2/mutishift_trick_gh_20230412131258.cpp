/*
 * @Author: Tao
 * @Date: 2023-04-11 23:29:20
 * @LastEditors: Tao
 * @LastEditTime: 2023-04-12 13:12:58
 * @Description: 
 * Email: 202203580@post.au.dk
 * Copyright (c) 2023 by Tao Tang, All Rights Reserved. 
 */

#include "project2.h"
#include <chrono>
using namespace std;
using namespace std::chrono;

int main(){
    const int SIZE = pow(2, 10);
    HashTable ht(SIZE);
    Sketching sc(SIZE);
    //* test...
    auto time_stamp1 = high_resolution_clock::now();
    for (int i = 0; i < int(pow(10, 6)); i++){
        //* multiply-shift hash function
        ht.hash(i);
    }
        auto time_stamp2 = high_resolution_clock::now();
        //* mersenne modulo
        sc.hash_h(i);
        auto time_stamp3 = high_resolution_clock::now();
        sc.hash_g(i);
        auto time_stamp4 = high_resolution_clock::now();
        //* regular modulo
        sc.hash_h_modulo(i);
        auto time_stamp5 = high_resolution_clock::now();
        sc.hash_g_modulo(i);

    }
    return 0;
}
