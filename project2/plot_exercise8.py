
import matplotlib.pyplot as plt

average_error = []
max_error = []

largest_size = []

x = []

with open('project2/experiment_result/average_error.txt', 'r') as f:
    for line in f:
        average_error.append(float(line.strip('\n')))

with open('project2/experiment_result/max_error.txt', 'r') as f:
    for line in f:
        max_error.append(float(line.strip('\n')))


for i in range(3,21):
    x.append(i)

tick = [3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20]
label = ['$2^3$','$2^4$','$2^5$','$2^6$',
         '$2^7$','$2^8$','$2^9$','$2^{10}$',
        '$2^{11}$','$2^{12}$','$2^{13}$',
        '$2^{14}$','$2^{15}$','$2^{16}$',
        '$2^{17}$','$2^{18}$','$2^{19}$',
        '$2^{20}$']
plt.xticks(tick, label)
plt.plot(x, average_error, label='Average relative error',marker='o', markersize=4.0)
plt.plot(x, max_error, label='Max relative error',marker='o', markersize=4.0)
plt.legend(loc="upper left")
plt.xlabel('Array r = $2^w$')
plt.ylabel('Relative error')
# plt.title(''))

plt.savefig('ex8_pic.svg', format='svg')
# plt.show()
