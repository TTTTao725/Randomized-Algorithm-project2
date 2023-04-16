'''
Author: Tao
Date: 2023-04-12 15:34:45
LastEditors: Tao
LastEditTime: 2023-04-15 19:04:47
Description: 
Email: 202203580@post.au.dk
Copyright (c) 2023 by Tao Tang, All Rights Reserved. 
'''
import matplotlib.pyplot as plt

average_update_hwc = []
average_update_sc7 = []
average_update_sc10 = []
average_update_sc20 = []


largest_size = []

x = []

with open('construction_time_hwc.txt', 'r') as f:
    for line in f:
        construction_time_hwc.append(float(line.strip('\n')))

with open('construction_time_ph.txt', 'r') as f:
    for line in f:
        construction_time_ph.append(float(line.strip('\n')))

with open('construction_time_rb.txt', 'r') as f:
    for line in f:
        construction_time_rb.append(float(line.strip('\n')))

with open('query_time_hwc.txt', 'r') as f:
    for line in f:
        query_time_hwc.append(float(line.strip('\n')))

with open('query_time_ph.txt', 'r') as f:
    for line in f:
        query_time_ph.append(float(line.strip('\n')))

with open('query_time_rb.txt', 'r') as f:
    for line in f:
        query_time_rb.append(float(line.strip('\n')))

with open('total_time_hwc.txt', 'r') as f:
    for line in f:
        total_time_hwc.append(float(line.strip('\n')))

with open('total_time_ph.txt', 'r') as f:
    for line in f:
        total_time_ph.append(float(line.strip('\n')))

with open('total_time_rb.txt', 'r') as f:
    for line in f:
        total_time_rb.append(float(line.strip('\n')))

with open('largest_size.txt', 'r') as f:
    for line in f:
        largest_size.append(float(line.strip('\n')))

for i in range(5,25):
    x.append(i)

plt.subplot(2,2,1)
plt.plot(x, construction_time_hwc, c='r', label='hwc')
plt.plot(x, construction_time_ph, c='g', label='ph')
plt.plot(x, construction_time_rb, c='b', label='rb')
plt.legend(loc="upper left")
plt.xlabel('logn')
plt.ylabel('average construction time')
plt.title('average construction time VS logn')

plt.subplot(2,2,2)
plt.plot(x, query_time_hwc, c='r', label='hwc')
plt.plot(x, query_time_ph, c='g', label='ph')
plt.plot(x, query_time_rb, c='b', label='rb')
plt.legend(loc="upper left")
plt.xlabel('logn')
plt.ylabel('average query time')
plt.title('average query time VS logn')

plt.subplot(2,2,3)
plt.plot(x, total_time_hwc, c='r', label='hwc')
plt.plot(x, total_time_ph, c='g', label='ph')
plt.plot(x, total_time_rb, c='b', label='rb')
plt.legend(loc="upper left")
plt.xlabel('logn')
plt.ylabel('average total execution time')
plt.title('average total execution time VS logn')

plt.subplot(2,2,4)
plt.plot(x, largest_size)
plt.xlabel('logn')
plt.ylabel('length')
plt.title('largest linked-list size for hashing with chaining')

plt.show()
