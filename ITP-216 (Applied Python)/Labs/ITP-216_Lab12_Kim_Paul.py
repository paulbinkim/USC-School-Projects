# Paul Kim, pbkim@usc.edu, Spring 2022
# Lab 12 -- Maths, Visualized
# Program which visualized three trig functions in two different ways each.

# Duplicate the output figures.

# 6 Plots, Each Trig Function, Labelled Axes, Title

import matplotlib.pyplot as plt
import numpy as np


def main():
    x = np.arange(0, 2 * np.pi, 0.1)
    x = np.linspace(-np.pi, np.pi)

    # Trig Functions
    y = np.sin(x)
    y2 = np.cos(x)
    y3 = np.tan(x)
    y4 = np.sinh(x)
    y5 = np.cosh(x)
    y6 = np.tanh(x)

    fig, ax = plt.subplots(2, 3) # 2 Rows, 3 Columns
    fig.suptitle("Trig!")

    ax[0, 0].plot(x, y)
    ax[0, 0].set(title='sin(x)')
    ax[0, 0].set(xlabel='x')
    ax[0, 0].set(ylabel='y')

    ax[0, 1].plot(x, y2)
    ax[0, 1].set(title='cos(x)')
    ax[0, 1].set(xlabel='x')
    ax[0, 1].set(ylabel='y')

    ax[0, 2].plot(x, y3)
    ax[0, 2].set(title='tan(x)')
    ax[0, 2].set(xlabel='x')
    ax[0, 2].set(ylabel='y')

    ax[1, 0].plot(x, y4)
    ax[1, 0].set(title='sinh(x)')
    ax[1, 0].set(xlabel='x')
    ax[1, 0].set(ylabel='y')

    ax[1, 1].plot(x, y5)
    ax[1, 1].set(title='cosh(x)')
    ax[1, 1].set(xlabel='x')
    ax[1, 1].set(ylabel='y')

    ax[1, 2].plot(x, y6)
    ax[1, 2].set(title='tanh(x)')
    ax[1, 2].set(xlabel='x')
    ax[1, 2].set(ylabel='y')

    fig.tight_layout()
    plt.show()


if __name__ == "__main__":
    main()