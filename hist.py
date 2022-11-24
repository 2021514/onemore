import matplotlib.pyplot as plt
  
time_fifo = []
priority_fifo = []
  
f = open('FIFO.txt','r')
for row in f:
    row = row.split(' ')
    time_fifo.append(row[0])
    priority_fifo.append(float(row[1]))
  
plt.bar(time_fifo, priority_fifo, color = 'b', label = 'File Data')
  
plt.xlabel('Priority', fontsize = 12)
plt.ylabel('time', fontsize = 12)
  
plt.title('Histogram for SCHED_FIFO', fontsize = 20)
plt.legend()
plt.show()

time_RR = []
priority_RR = []
  
f = open('RR.txt','r')
for row in f:
    row = row.split(' ')
    time_RR.append(row[0])
    priority_RR.append(float(row[1]))
  
plt.bar(time_RR, priority_RR, color = 'r', label = 'File Data')
  
plt.xlabel('Priority', fontsize = 12)
plt.ylabel('time', fontsize = 12)
  
plt.title('Histogram for SCHED_RR', fontsize = 20)
plt.legend()
plt.show()