#!/usr/bin/python3

#!/usr/bin/python3

import pandas as pd
import matplotlib.pyplot as plt

# Load the data from the CSV file
df = pd.read_csv('times.csv')

# Group the data by 'threads' and 'name' columns and calculate the mean and standard deviation
grouped = df.groupby(['threads', 'name'])['time'].agg(['mean', 'std']).unstack().reset_index()

# Create a grouped bar chart with error bars showing the standard deviation
ax = grouped['mean'].plot(kind='bar', yerr=grouped['std'], rot=0,)

# Set the title and axis labels
ax.set_title('Execution Time by Number of Threads and Name')
ax.set_xlabel('Threads')
ax.set_ylabel('Time (seconds)')

# Add legend
ax.legend(title='Name')

plt.savefig('performance.png')
