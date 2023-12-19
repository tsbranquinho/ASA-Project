import numpy as np
from scipy.optimize import curve_fit
import matplotlib.pyplot as plt

# Given data
sizes = np.array([200, 400, 600, 800, 1000, 1200, 1400, 1600, 1800, 2000, 2200, 2400, 2600, 2800, 3000])
times = np.array([1.3, 4.6, 13.9, 30.5, 66.5, 127.6, 214, 334.3, 478.4, 702.6, 914.4, 1246.2, 1662.6, 2083.2, 2646.1])

# Define the power-law function
def power_law(x, a, b):
    return a * np.power(x, b)

# Use curve fitting to find the coefficients
params, covariance = curve_fit(power_law, sizes, times)

# Extract the coefficients
a, b = params

# Generate fitted values for visualization
sizes_fit = np.linspace(min(sizes), max(sizes), 100)
times_fit = power_law(sizes_fit, a, b)

# Plot the original data and the fitted curve
plt.scatter(sizes, times, label='Original Data')
plt.plot(sizes_fit, times_fit, label=f'Fitted Curve: {a:.9f} * x^{b:.9f}', color='red')
plt.xlabel('Sizes (x)')
plt.ylabel('Times (y)')
plt.legend()
plt.show()
