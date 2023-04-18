#!/usr/bin/python3

import pandas as pd
import matplotlib.pyplot as plt
from matplotlib.colors import ListedColormap
import cmasher as cmr

# Load the data from the CSV file
df = pd.read_csv('times.csv').sort_values(by=['name'], ascending=True)

# Group the data by 'threads' and 'name' columns and calculate the mean and standard deviation
grouped = df.groupby(['threads', 'name'])['time'].agg(['mean', 'std']).unstack().reset_index()

# use the Safe color palette by Paul Tol
colors = ['#009E73', '#0072B2', '#D55E00', '#CC79A7', '#F0E442', '#56B4E9', '#bcbcbc']
cmap = ListedColormap(colors)

# Create a grouped bar chart with error bars showing the standard deviation
ax = grouped['mean'].plot(kind='bar', yerr=grouped['std'], rot=0, cmap=cmap)

# Set the x-axis tick labels to the 'threads' column values
ax.set_xticklabels(grouped['threads'])

# Set the title and axis labels
ax.set_title('Execution Time by Number of Threads and Name')
ax.set_xlabel('Threads')
ax.set_ylabel('Time (seconds)')

# Add legend
ax.legend(title='Name', bbox_to_anchor=(1.02, 1), loc='upper left', borderaxespad=0)

plt.savefig('performance.png', bbox_inches='tight')
