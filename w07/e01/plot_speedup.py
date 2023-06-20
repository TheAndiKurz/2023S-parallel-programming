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


df = pd.read_csv(file, sep=',')
df = df.groupby(['n','name']).mean().reset_index()

df2 = df[df['name']=='vectorized']

df2['speedup'] = (df[df['name']=='reference']['time'].values/df[df['name']=='vectorized']['time'].values)
# plot the speedup between the two groups




# save plot as png file with 300 dpi and the name specified above
# it should be big enough such that the legend isn't overlapping with the plot
#plt.savefig(png_name,format='pdf')
