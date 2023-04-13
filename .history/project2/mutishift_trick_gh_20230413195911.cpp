/*
 * @Author: Tao
 * @Date: 2023-04-11 23:29:20
 * @LastEditors: Tao
 * @LastEditTime: 2023-04-13 19:58:17
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
    cout << 1 << endl;
    HashTable ht(SIZE);
    Sketching sc(SIZE);
    //* test...
    auto time_stamp1 = high_resolution_clock::now();
    cout << "mutiply-shift hash function" << endl;
    for (int i = 0; i < int(pow(10, 6)); i++){
        //* multiply-shift hash function
        ht.hash(i);
    }
    cout << "mersenne modulo h" << endl;
    auto time_stamp2 = high_resolution_clock::now();
    for (int i = 0; i < int(pow(10, 6)); i++){
        //* mersenne modulo h
        sc.hash_h(i, SIZE);
    }
    cout << "mersenne modulo g" << endl;
    auto time_stamp3 = high_resolution_clock::now();
    for (int i = 0; i < int(pow(10, 6)); i++){
        //* mersenne modulo g
        sc.hash_g(i);
    }
    cout << "regular modulo h" << endl;
    auto time_stamp4 = high_resolution_clock::now();
    for (int i = 0; i < int(pow(10, 6)); i++){
        //* regular modulo h
        sc.hash_h_modulo(i, SIZE);
    }
    cout << "regular modulo g" << endl;
    auto time_stamp5 = high_resolution_clock::now();
    for (int i = 0; i < int(pow(10, 6)); i++){
        //* regular modulo g
        sc.hash_g_modulo(i);
    }
    auto time_stamp6 = high_resolution_clock::now();

    auto average_mts = duration_cast<microseconds>(time_stamp2 - time_stamp1);
    cout << average_mts.count() / double(pow(10, 6)) << endl;
    auto average_mmh = duration_cast<microseconds>(time_stamp3 - time_stamp2);
    cout << average_mmh.count() / double(pow(10, 6)) << endl;
    auto average_mmg = duration_cast<microseconds>(time_stamp4 - time_stamp3);
    cout << average_mmg.count() / double(pow(10, 6)) << endl;
    auto average_rmh = duration_cast<microseconds>(time_stamp5 - time_stamp4);
    cout << average_rmh.count() / double(pow(10, 6)) << endl;
    auto average_rmg = duration_cast<microseconds>(time_stamp6 - time_stamp5);
    cout << average_rmg.count() / double(pow(10, 6)) << endl;
    return 0;
}
