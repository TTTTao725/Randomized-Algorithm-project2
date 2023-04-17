'''
Author: Tao
Date: 2023-04-16 19:27:24
LastEditors: Tao
LastEditTime: 2023-04-16 19:33:22
Description: 
Email: 202203580@post.au.dk
Copyright (c) 2023 by Tao Tang, All Rights Reserved. 
'''
import matplotlib.pyplot as plt

average_error_2wise = []
max_error_2wise = []

logr = []

for i in range(3,21):
    logr.append(i)

with open('project2/experiment_result/average_error_2wise.txt', 'r') as f:
    for line in f:
        average_error_2wise.append(float(line.strip('\n')))

with open('project2/experiment_result/max_error_2wise.txt', 'r') as f:
    for line in f:
        max_error_2wise.append(float(line.strip('\n')))

tick = [3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20]
label = ['$2^3$','$2^4$','$2^5$','$2^6$','$2^7$','$2^8$','$2^9$','$2^{10}$',
            '$2^{11}$','$2^{12}$','$2^{13}$','$2^{14}$',
            '$2^{15}$','$2^{16}$','$2^{17}$','$2^{18}$',
            '$2^{19}$','$2^{20}$']
plt.xticks(tick, label)
plt.plot(logr, average_error_2wise, label="Average relative error")
plt.plot(logr, max_error_2wise, label="Max relative error")
plt.legend(loc="upper left")
plt.xlabel('Array size $r = 2^w$')
plt.ylabel('Relative error')
plt.savefig('ex9_pic.svg', format='svg')
# plt.show()