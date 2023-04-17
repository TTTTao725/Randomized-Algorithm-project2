/*
 * @Author: Tao
 * @Date: 2023-04-15 18:09:47
 * @LastEditors: Tao
 * @LastEditTime: 2023-04-17 12:53:04
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
#include "two_wise_sketching.h"
using namespace std;

vector<double> average_error_list_2wise;
vector<double> max_error_list_2wise;
int main(){
    int min_r=3;
    int max_r=20;
    for (unsigned int w = min_r; w<= max_r ;w++){
        double average_error_sum = 0;
        double max_error = 0;
        int n = 1 << w;
        Sketching_2wise sc(n);
        int update_times = pow(10, 3);
        int experiment_times = pow(10, 3);
        for (int i = 0; i < experiment_times; i++){
            long long int true_sum = 0;
            //* key also has to be uint64_t
            for (uint64_t key = 0; key < update_times; key++){
                // assert(key*key == static_cast<int>(key*key));
                key_value_pair_64bit tmp = {key, static_cast<uint64_t>(key*key)};
                // key_value_pair tmp = {key, key*key};
                sc.update(tmp,n);
                // true frequency is key^2
                auto freq = key*key;
                true_sum += freq*freq;
            }
            auto fre_estimate = sc.query();
            sc.clear();
            sc.reset_hash();
            // cout << "fre_estimate: " << fre_estimate << endl;
            // cout << "true_sum: " << true_sum << endl;

            //calculate the error of each experiment
            double error = static_cast<double>(fabs(fre_estimate - true_sum)/static_cast<double>(true_sum)); 
            cout << error << endl;
            average_error_sum += error;
            max_error = max(max_error, error);
        }
        double average_error_result = static_cast<double>(average_error_sum/static_cast<double>(experiment_times));
        average_error_list_2wise.push_back(average_error_result);
        max_error_list_2wise.push_back(max_error);
        sc.reset_hash();
        sc.clear();
    }
    fstream fout;
    fout.open("experiment_result/average_error_2wise.txt", ios::out);
    for (auto i : average_error_list_2wise){
        fout << i << endl;
    }
    fout.close();
    fout.open("experiment_result/max_error_2wise.txt", ios::out);
    for (auto i : max_error_list_2wise){
        fout << i << endl;
    }
    fout.close();
}
