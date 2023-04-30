# reads data from the csv file times_number_tasks.csv (with header) and plots the values as a line graph
# on the x axis is the number of tasks on a logarithmical scale, on the y-axis the time in seconds. 
# the data is grouped by the name collumn, there are multiple messurements for each name and number of tasks, mean is computed and plotted

import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import math

file = 'times.csv'
x_col = 'threads' 

# read csv file
df = pd.read_csv(file)

# group by name
grouped = df.groupby('name')

# create figure
fig = plt.figure()

# create subplot
ax = fig.add_subplot(111)

# iterate over groups
for name, group in grouped:
    # compute mean
    mean = group.groupby(x_col).mean()
    # get x and y values
    x = mean.index
    y = mean['time']
    # plot
    ax.plot(x,y, label=name)

# set labels and title
ax.set_xlabel('Number of tasks')
ax.set_ylabel('Time in seconds')
ax.set_title('Time per number of tasks')
# set x axis to logarithmic scale
ax.set_xscale('log')
# set y axis to logarithmic scale
ax.set_yscale('log')
# set legend
ax.legend()

# show plot
plt.show()
