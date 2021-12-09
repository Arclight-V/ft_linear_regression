import sys
import pandas as pd
import matplotlib.pyplot as plt


def main():
    df = pd.read_csv("../resources/data.csv")

    X = df.km.values
    y = df.price.values

    X_norm = (X - X.min()) / (X.max() - X.min())

    plt.ion()

    iterations = 100000
    learning_ratio = 0.001

    slope_normalize = 0.0
    intercept = 0.0

    for i in range(iterations):

        sum_slope = sum(
            (estimate_prace - prace) * millage
            for (estimate_prace,
                 prace,
                 millage) in zip(intercept + slope_normalize * X_norm,
                                 y,
                                 X_norm)
        )

        sum_intercept = sum(
            (estimate_prace - prace)
            for (estimate_prace, prace) in zip(intercept + slope_normalize * X_norm,
                                               y)
        )

        slope_normalize -= learning_ratio * sum_slope / len(X_norm)
        intercept -= learning_ratio * sum_intercept / len(X_norm)

        if (i % 1000 == 0):

            slope = slope_normalize / df.km.max()

            estimates = [estimate_price for estimate_price in intercept + slope * X]

            plt.scatter(X, y, color='black', alpha=0.7, label='fact price')
            plt.plot(X, estimates, color='red', label='regression line')
            plt.xlabel("millage")
            plt.ylabel("price")
            plt.legend(loc='upper right')
            plt.draw()
            plt.pause(0.0000001)
            plt.clf()


if __name__ == '__main__':
    main()
