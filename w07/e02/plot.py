#!/usr/bin/python3

import pandas as pd
import matplotlib.pyplot as plt
from matplotlib.colors import ListedColormap
import cmasher as cmr

from argparse import ArgumentParser, BooleanOptionalAction

parser = ArgumentParser()

parser.add_argument(
    "-i",
    "--input",
    dest="csv_name",
    help="csv file name",
    default="times.csv",
    required=False,
)
parser.add_argument(
    "-o",
    "--output",
    dest="png_name",
    help="png file name",
    default="performance.png",
    required=False,
)
parser.add_argument(
    "-t",
    "--title",
    dest="title",
    help="Title of the plot",
    default="Execution Time by Number of Threads and Name",
    required=False,
)
parser.add_argument(
    "-l",
    "--log",
    dest="log",
    help="Logarithmic scale",
    action=BooleanOptionalAction,
    default=False,
    required=False,
)

# set the csv_name to the variable when argument is set
args = parser.parse_args()
csv_name = args.csv_name
png_name = args.png_name
title = args.title
log_scale = args.log

# Load the data from the CSV file
df = pd.read_csv(csv_name).sort_values(by=["name"], ascending=True)

# Group the data by 'threads' and 'name' columns and calculate the mean and standard deviation
grouped = (
    df.groupby(["vector_size", "name"])["time"].agg(
        ["mean", "std"]).unstack().reset_index()
)

# Dutch Field color palette
colors = [
    "#e60049",
    "#0bb4ff",
    "#50e991",
    "#e6d800",
    "#9b19f5",
    "#ffa300",
    "#dc0ab4",
    "#b3d4ff",
    "#00bfa0",
]
cmap = ListedColormap(colors, None, N=grouped["mean"].shape[1])
print(grouped["mean"])

# Create a grouped bar chart with error bars showing the standard deviation
ax = grouped["mean"].plot(
    kind="line",
    yerr=grouped["std"],
    capsize=2,
    ecolor="black",
    rot=0,
    cmap=cmap,
    logy=log_scale,
)

# Set the x-axis tick labels to the 'threads' column values
ax.set_xticklabels(grouped["vector_size"])

# Set the title and axis labels
ax.set_title(title)
ax.set_xlabel("Vector Size")
ax.set_ylabel("Time (seconds)")

# Add legend
ax.legend(title="Name", bbox_to_anchor=(1.02, 1),
          loc="upper left", borderaxespad=0)

plt.savefig(png_name, bbox_inches="tight")
