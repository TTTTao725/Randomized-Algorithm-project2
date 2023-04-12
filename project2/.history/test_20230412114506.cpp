/*
 * @Author: Tao
 * @Date: 2023-04-11 20:14:55
 * @LastEditors: Tao
 * @LastEditTime: 2023-04-12 11:45:06
 * @Description: 
 * Email: 202203580@post.au.dk
 * Copyright (c) 2023 by Tao Tang, All Rights Reserved. 
 */
/*
 * @Author: Tao
 * @Date: 2023-04-11 20:14:55
 * @LastEditors: Tao
 * @LastEditTime: 2023-04-11 20:17:07
 * @Description: 
 * Email: 202203580@post.au.dk
 * Copyright (c) 2023 by Tao Tang, All Rights Reserved. 
 */
#include <iostream>
#include <random>

int main() {
    std::random_device rd;  // Seed the random number generator
    std::mt19937 gen(rd());
    std::uniform_int_distribution<uint32_t> dis(1, UINT32_MAX / 2);  // Range is [1, 2^31)

    uint32_t rand_int = dis(gen);  // Generate a random 32-bit integer in the range [1, 2^31)
    uint32_t odd_int = rand_int | 0x1;  // Set the least significant bit to 1 to get an odd number

    std::cout << "Random odd integer: " << (odd_int * 100 >> 10) << std::endl;

    return 0;
}
