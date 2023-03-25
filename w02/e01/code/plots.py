import numpy as np
import pandas as pd
import matplotlib as mpl
import matplotlib.pyplot as plt

df = pd.read_csv('output.log', sep=',')
df.columns = ['op', 'time']

df_grouped = df.groupby(['op'], as_index=False).agg({'time':['mean', 'std']})
df_grouped.columns = ['optimization', 'time', 'std']

#df_grouped['std'] = df.groupby('optimization', as_index=False).std()

print(df_grouped)

x = df_grouped.loc[:,'optimization']
y = df_grouped.loc[:,'time']
err = df_grouped.loc[:,'std']

fig, ax = plt.subplots()
bar = ax.bar(x, y, yerr=err)
ax.set_ylabel('execution time in seconds')
ax.set_xlabel('optimization flag')

for rect in bar:
    height = rect.get_height()
    plt.text(rect.get_x() + rect.get_width()/2.0, height, f'{height:.2f}s', ha='center', va='bottom')


plt.show()




