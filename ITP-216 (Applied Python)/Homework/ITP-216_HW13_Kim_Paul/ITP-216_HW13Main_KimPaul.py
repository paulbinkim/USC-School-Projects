# Paul Kim, pbkim@usc.edu, 1723717002, Spring 2022 (Tuesday 7PM)
# HW 13 (Climate Visualization)

# Purpose:
# Visualize Weather Data (Using Datasets from NOAA)
# Using Data from Honolulu, Hawaii (Hometown)

# Grading:
# Data is split into subsets by year. (Completed)
# The average of daily temperatures across all years are calculated. (Completed using sum function)
# Contains header with student name, semester, section, and assignment. (Completed)
# Comments and Readable. (Completed)
# Figure includes two subplots: (Completed)
# A line plot with every year (of the last 8 years) plotted by days (labeled months). (Piazza said 8 years is OK)
# A bar plot with 2019's daily temperatures and the average of daily temperatures across all years. (Completed)
# Each figure's axes labelled appropriately. (Completed)
# Legend on each subplot. (Completed)
# Removes all rows with a Nan in the temperature column. (Completed)

# Importing Libraries
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import datetime as dt

# For FixedFormatter Warning
# https://stackoverflow.com/questions/63723514/userwarning-fixedformatter-should-only-be-used-together-with-fixedlocator
import warnings
warnings.filterwarnings("ignore")


# Main Function that creates the two Sub Plots
def main():
    # Reading CSV Data File
    df = pd.read_csv("data.csv")

    # Plotting Two Graphs and Giving a Size
    fig, ax = plt.subplots(2, 1, figsize=(20, 10))

    # Cleaning Data (Preparing)
    # *Note, I couldn't do dropna() generically because it was true that most columns had some NaN value
    # Therefore, I had to be specific and only drop rows that did not have values for TAVG

    # Removing all rows with Nan in the 'TAVG' Column
    df3 = df[pd.notnull(df['TAVG'])]

    # Methods to access specific Temp Values (Focused on TAVG)
    # df = df[pd.notnull(df['TMAX'])]
    # df2 = df[pd.notnull(df['TMIN'])]

    # https://stackoverflow.com/questions/46878156/pandas-filter-dataframe-rows-with-a-specific-year
    # Reference ^^ that helped me parse the Dataframe of 'TAVG' into separate years (Citation)
    df3["DATE"] = pd.to_datetime(df3["DATE"])  # Convert into a Datetime

    # Access all data for Specific Year (Seperated into its own Data Variable)
    # Data Split into Subsets by Year.
    data2014 = df3[df3["DATE"].dt.year == 2014]
    data2015 = df3[df3["DATE"].dt.year == 2015]
    data2016 = df3[df3["DATE"].dt.year == 2016]
    data2017 = df3[df3["DATE"].dt.year == 2017]
    data2018 = df3[df3["DATE"].dt.year == 2018]
    data2019 = df3[df3["DATE"].dt.year == 2019]
    data2020 = df3[df3["DATE"].dt.year == 2020]
    data2021 = df3[df3["DATE"].dt.year == 2021]
    data2022 = df3[df3["DATE"].dt.year == 2022]

    # Months Container
    months = [' ', 'January', 'February', 'March', 'April', 'May', 'June', 'July',
              'August', 'September', 'October', 'November', 'December', ' ']

    # Days for X axis (I create multiple for different sizes)
    days = np.arange(0, 365)
    days2 = np.arange(0, 366)
    days3 = np.arange(0, 103)

    # Plotting First Subplot as Line Graph
    ax[0].plot(days, data2014["TAVG"], color="blue", label=2014, linewidth=0.7)
    ax[0].plot(days, data2015["TAVG"], color="red", label=2015, linewidth=0.7)
    ax[0].plot(days2, data2016["TAVG"], color="green", label=2016, linewidth=0.7)
    ax[0].plot(days, data2017["TAVG"], color="purple", label=2017, linewidth=0.7)
    ax[0].plot(days, data2018["TAVG"], color="yellow", label=2018, linewidth=0.7)
    ax[0].plot(days, data2019["TAVG"], color="orange", label=2019, linewidth=0.7)
    ax[0].plot(days2, data2020["TAVG"], color="brown", label=2020, linewidth=0.7)
    ax[0].plot(days, data2021["TAVG"], color="magenta", label=2021, linewidth=0.7)
    ax[0].plot(days3, data2022["TAVG"], color="black", label=2022, linewidth=0.7)

    # Formatting for X-Axis Ticks (this took me 2 hours to figure out :|)
    ax[0].xaxis.set_major_locator(plt.MultipleLocator(33))
    ax[0].set_xticklabels(months, fontsize=10, rotation=90)
    ax[0].set(title="Average Temperature in Honolulu from 2014-Early 2022", xlabel="Month", ylabel="Temp(F)")
    ax[0].legend(fontsize=8)

    # Resetting Indexes for Data from 2014-2021 (so that I can sum afterward)
    data2014 = data2014.reset_index(drop=True)
    data2015 = data2015.reset_index(drop=True)
    data2016 = data2016.reset_index(drop=True)
    data2017 = data2017.reset_index(drop=True)
    data2018 = data2018.reset_index(drop=True)
    data2019 = data2019.reset_index(drop=True)
    data2020 = data2020.reset_index(drop=True)
    data2021 = data2021.reset_index(drop=True)
    # data2022 = data2022.reset_index(drop=True) # Removing 2022 because not a full year (not full dataset)

    # Sums all TAVG values for each column in each year
    DataTotal = sum(
        [data2014["TAVG"], data2015["TAVG"], data2016["TAVG"], data2017["TAVG"], data2018["TAVG"], data2019["TAVG"],
         data2020["TAVG"], data2021["TAVG"]])

    # Arithmetic
    # Average Daily Temperatures across all years are calculated.
    NewList = []
    for item in DataTotal:
        NewList.append(item / 8)

    # Plotting Subgraph 2 as a Bar Graph
    ax[1].bar(days2, NewList, color="blue", label="historical average", alpha=0.5)
    ax[1].bar(days, data2019["TAVG"], color="orange", label=2019, alpha=0.5)

    # Formatting for X-Axis Ticks
    ax[1].xaxis.set_major_locator(plt.MultipleLocator(33))
    ax[1].set_xticklabels(months, fontsize=10, rotation=90)
    ax[1].set(title="Comparing 2019 to 7 Year Average (2014 to 2021)", xlabel="Month", ylabel="Temp(F)")
    ax[1].legend(fontsize=8)

    # Giving Large Title and Printing Graph
    plt.suptitle("Yearly Climatological Data for Honolulu, Hawaii from 2014-2022", fontsize=20)
    plt.tight_layout()
    plt.show()


# Call to Main
if __name__ == "__main__":
    main()
