import matplotlib.pyplot as plt
import matplotlib.animation as animation
import numpy as np

prices = []
volumes = []
signals = []  

with open("output.txt", "r") as f:
    for line in f:
        line = line.strip()
        if not line:
            continue
        if line == "Buy":
            signals.append("Buy")
            continue
        elif line == "Sell":
            signals.append("Sell")
            continue
        try:
            price, volume = map(float, line.split(","))
            prices.append(price)
            volumes.append(volume)
            signals.append(None)
        except ValueError:
            continue

fig, ax1 = plt.subplots(figsize=(12, 6))
ax2 = ax1.twinx()
ax1.set_xlabel("Time")
ax1.set_ylabel("Price")
ax2.set_ylabel("Volume")
ax1.grid(True, alpha=0.3)

price_line, = ax1.plot([], [], color='blue', linewidth=2)

# volume bars
x = np.arange(len(prices))
volume_bars = ax2.bar(x, np.zeros_like(volumes), alpha=0.2, color='gray', width=0.8)
ax2.set_ylim(0, max(volumes)*1.2)


buy_scatter = ax1.scatter([], [], marker='^', color='green', s=150, zorder=5)
sell_scatter = ax1.scatter([], [], marker='v', color='red', s=150, zorder=5)

def update(frame):
    xdata = x[:frame+1]
    ydata = prices[:frame+1]
    price_line.set_data(xdata, ydata)

    #zoom out
    margin = 0.5
    visible_points = max(5, frame+1)
    ax1.set_xlim(0, visible_points)
    ax1.set_ylim(min(prices[:frame+1]) - margin, max(prices[:frame+1]) + margin)

    #volume bars
    for bar, vol in zip(volume_bars[:frame+1], volumes[:frame+1]):
        bar.set_height(vol)

    #buy/sell scatter points
    buy_x = [i for i in range(frame+1) if signals[i] == "Buy"]
    buy_y = [prices[i] for i in buy_x]
    sell_x = [i for i in range(frame+1) if signals[i] == "Sell"]
    sell_y = [prices[i] for i in sell_x]

    buy_scatter.set_offsets(np.c_[buy_x, buy_y])
    sell_scatter.set_offsets(np.c_[sell_x, sell_y])

    return price_line, buy_scatter, sell_scatter

ani = animation.FuncAnimation(
    fig, update, frames=len(prices), interval=200, blit=False
)

plt.title("Live Trading Simulation")
plt.show()
