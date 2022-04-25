# Paul Kim, pbkim@usc.edu, 1723717002
# Lab 13 - Pandas and Penguins

# Program which visualizes the Palmer Penguin Dataset:
# Frequency of Flipper Length
# Use a histogram or a bar plot.

# Contain the following:
# A figure containing 1 plot. (Good)
# Appropriately labeled axes. (Good)
# Gridlines (Good)
# Key with each species labelled. (good)
# Different color for species. (Good)
# Title (Good)


import matplotlib.pyplot as plt
import pandas as pd


def main():
    # Read File (CSV)
    df = pd.read_csv("penguins.csv")
    # Plot 1 Graph
    fig, ax = plt.subplots(1, 1)

    # Clean Data
    df = df.dropna()
    species_list = df["species"].unique()
    df_group = df.groupby("species")
    colors = ["blue", "red", "green"]

    # Construct Bar Plot
    df.round({"flippers_length_mm": 0})
    count = []
    for item in species_list:
        count.append(df_group.get_group(item)["flipper_length_mm"].value_counts())
    for i, species in enumerate(species_list):
        ax.bar(count[i].index, count[i].values, width=1, label=species, alpha=0.5, color=colors[i])

    # Set Title, Axes, and Legend
    ax.set(title="Penguin Flippers Length (Bar Graph)", xlabel="Flipper Length in (mm)", ylabel="Frequency")
    ax.grid(which='major', color='#999999', alpha=0.5)
    ax.legend()

    # format and show
    plt.tight_layout()
    plt.show()


if __name__ == "__main__":
    main()

# Referenced L13 Solution given on Blackboard.