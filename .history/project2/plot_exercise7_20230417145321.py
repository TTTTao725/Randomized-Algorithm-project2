'''
Author: Tao
Date: 2023-04-12 15:34:45
LastEditors: Tao
LastEditTime: 2023-04-17 14:53:19
Description: 
Email: 202203580@post.au.dk
Copyright (c) 2023 by Tao Tang, All Rights Reserved. 
'''
import matplotlib.pyplot as plt

average_update_hwc = []
average_update_sc7 = []
average_update_sc10 = []
average_update_sc20 = []

x = []

for i in range(6,29):
    x.append(i)

with open('experiment_result/average_update_hwc.txt', 'r') as f:
    for line in f:
        average_update_hwc.append(float(line.strip('\n')))

with open('experiment_result/average_update_sc7.txt', 'r') as f:
    for line in f:
        average_update_sc7.append(float(line.strip('\n')))

with open('experiment_result/average_update_sc10.txt', 'r') as f:
    for line in f:
        average_update_sc10.append(float(line.strip('\n')))

with open('experiment_result/average_update_sc20.txt', 'r') as f:
    for line in f:
        average_update_sc20.append(float(line.strip('\n')))

tick = [6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28]
label = ['$2^6$','$2^7$','$2^8$','$2^9$','$2^{10}$',
            '$2^{11}$','$2^{12}$','$2^{13}$','$2^{14}$',
            '$2^{15}$','$2^{16}$','$2^{17}$','$2^{18}$',
            '$2^{19}$','$2^{20}$','$2^{21}$','$2^{22}$',
            '$2^{23}$','$2^{24}$','$2^{25}$','$2^{26}$',
            '$2^{27}$','$2^{28}$']
plt.xticks(tick, label)

plt.plot(x, average_update_hwc, label="Hash with chaining")
plt.plot(x, average_update_sc7, label="Sketch with r = $2^7$")
plt.plot(x, average_update_sc10, label="Sketch with r = $2^{10}$")
plt.plot(x, average_update_sc20, label="Sketch with r = $2^{20}$")
plt.legend(loc="upper left")
plt.xlabel('n keys')
plt.ylabel('Average update time[microseconds]')

plt.savefig('ex7_pic.svg', format='svg')
# plt.show()
