'''
Author: Tao
Date: 2023-04-16 19:27:24
LastEditors: Tao
LastEditTime: 2023-04-16 19:32:16
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

with open('experiment_result/average_error_2wise.txt', 'r') as f:
    for line in f:
        average_error_2wise.append(float(line.strip('\n')))

with open('experiment_result/max_error_2wise.txt', 'r') as f:
    for line in f:
        max_error_2wise.append(float(line.strip('\n')))