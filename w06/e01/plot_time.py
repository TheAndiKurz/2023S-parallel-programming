# reads data from the csv file times_number_tasks.csv (with header) and plots the values as a line graph
# on the x axis is the number of tasks on a logarithmical scale, on the y-axis the time in seconds. 
# the data is grouped by the name collumn, there are multiple messurements for each name and number of tasks, mean is computed and plotted

import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import math
import sys

file = sys.argv[1]
png_name = f"performance.pdf"
x_label='n'
y_label='Time in seconds'
title=f"time for number threads"


# create figure
fig = plt.figure(figsize=(10,8))

# read data from csv file with header
df = pd.read_csv(file, sep=',', header=0).sort_values(by=['time'])
#df = df[df['threads'] == df['threads'].max()]

# Group the data by 'threads' and 'name' columns and calculate the mean and standard deviation
grouped = (
    df.groupby(["threads", "name"])["time"].agg(["mean", "std"]).unstack().reset_index()
)

# Create a grouped bar chart with error bars showing the standard deviation
ax = grouped["mean"].plot(
    kind="bar",
    yerr=grouped["std"],
    capsize=2,
    ecolor="black",
    rot=0,
)

# Set the x-axis tick labels to the 'threads' column values
ax.set_xticklabels(grouped["threads"])

# Set the title and axis labels
ax.set_title(title)
ax.set_xlabel("Threads")
ax.set_ylabel("Time (seconds)")

# Add legend
ax.legend(title="Name", bbox_to_anchor=(0.98, 0.98), loc="upper right", borderaxespad=0)



# it should be big enough such that the legend isn't overlapping with the plot
plt.savefig(png_name,format='pdf')


# show plot
# plt.show()
