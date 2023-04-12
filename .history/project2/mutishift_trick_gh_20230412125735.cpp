/*
 * @Author: Tao
 * @Date: 2023-04-11 23:29:20
 * @LastEditors: Tao
 * @LastEditTime: 2023-04-12 12:57:35
 * @Description: 
 * Email: 202203580@post.au.dk
 * Copyright (c) 2023 by Tao Tang, All Rights Reserved. 
 */

#include "project2.h"
using namespace std;

int main(){
    const int SIZE = pow(2, 10);
    HashTable ht(SIZE);
    Sketching sc(SIZE);
    //* test...
    for (int i = 0; i < int(pow(10, 6)); i++){
        ht.hash(i);
        sc.hash_h(i);
        sc.hash_g(i);
    }
    return 0;
}
