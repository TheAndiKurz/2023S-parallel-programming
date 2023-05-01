# reads data from the csv file times_number_tasks.csv (with header) and plots the values as a line graph
# on the x axis is the number of tasks on a logarithmical scale, on the y-axis the time in seconds. 
# the data is grouped by the name collumn, there are multiple messurements for each name and number of tasks, mean is computed and plotted

import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import math

n=11
files = {f"./times_number_tasks-n{n}.csv"}
x_col = 'threads' 
png_name = f"performance_tasks_n{n}.pdf"
x_label='Number of tasks'
y_label='Time in seconds'
title=f"time for incrasing number of tasks (n={n})"


# create figure
fig = plt.figure(figsize=(10,8))

for f in files:
# read csv file
    df = pd.read_csv(f)

# group by name
    grouped = df.groupby('name')
# create subplot
    ax = fig.add_subplot(111)

# iterate over groups
    for name, group in grouped:
        # compute mean
        mean = group.groupby(x_col).mean(numeric_only=True)
        # get x and y values
        x = mean.index
        y = mean['time']
        # plot
        ax.plot(x,y, label=name)

# set labels and title
    ax.set_xlabel(x_label)
    ax.set_ylabel(y_label)
    ax.set_title(title)
# set x axis to logarithmic scale
    ax.set_xscale('log')
# set y axis to logarithmic scale
    ax.set_yscale('log')
# set legend
    ax.legend()

# save plot as png file with 300 dpi and the name specified above
# it should be big enough such that the legend isn't overlapping with the plot
plt.savefig(png_name,format='pdf')


# show plot
# plt.show()
