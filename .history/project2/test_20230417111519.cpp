/*
 * @Author: Tao
 * @Date: 2023-04-17 11:13:30
 * @LastEditors: Tao
 * @LastEditTime: 2023-04-17 11:15:19
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

Sketching sc(pow(2,7));
key_value_pair tmp1 = {1,1};
key_value_pair tmp2 = {2,4};
key_value_pair tmp3 = {3,9};
key_value_pair tmp4 = {4,16};
sc.update()