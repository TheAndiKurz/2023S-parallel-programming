import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import math
import sys

file = sys.argv[1]
x_col = 'n' 
png_name = f"performance.pdf"
x_label='n'
y_label='Time in seconds'
title=f"time for incrasing n"

# read data from the csv file into a pandas dataframe
# then plot it as a line graph, the x axis displays n, the y axis time.
# the data is grouped by name 

df = pd.read_csv(file, sep=',')
df = df.groupby(['n','name']).mean().reset_index()
df = df.pivot(index='n', columns='name', values='time')
df.plot()
plt.xscale('log') 
plt.yscale('log')
plt.xlabel(x_label)
plt.ylabel(y_label)
plt.title(title)



# save plot as png file with 300 dpi and the name specified above
# it should be big enough such that the legend isn't overlapping with the plot
plt.savefig(png_name,format='pdf')
