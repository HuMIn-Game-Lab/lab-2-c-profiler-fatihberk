import matplotlib.pyplot as plt
import pandas as pd

# Load profiler data
data = pd.read_csv('profiler_output.csv')

# Convert 'Total Time' to microseconds (µs) for readability
data['Total Time (µs)'] = data['Total Time'] * 1e6  # Convert from seconds to microseconds (µs)

# Create subplots: one for average execution time, another for the timeline
fig, axes = plt.subplots(nrows=2, ncols=1, figsize=(12, 10))

# 1. Average Execution Time by Section (Bar Chart)
def plot_average_times(ax):
    data_sorted = data.sort_values(by='Average Time', ascending=False)
    ax.barh(data_sorted['Section'], data_sorted['Average Time'], color='skyblue')
    ax.set_xlabel('Average Time (seconds)')
    ax.set_ylabel('Section')
    ax.set_title('Average Execution Time by Section')

# 2. Timeline of Section Calls (Horizontal Bar Chart)
def plot_timeline(ax):
    for i, section in enumerate(data['Section']):
        ax.barh(section, data['Total Time (µs)'][i], left=i, color='orange')
    ax.set_xlabel('Execution Time (µs)')  # Show time in microseconds for clarity
    ax.set_ylabel('Section')
    ax.set_title('Timeline of Section Calls')

# Plot both charts in subplots
plot_average_times(axes[0])  # Top plot: Average times
plot_timeline(axes[1])       # Bottom plot: Timeline of section calls

# Adjust layout for better spacing
plt.tight_layout()

# Save the figure as a single image file
plt.savefig('VisulizationAfterImprovements.png')

# Show the figure
plt.show()
