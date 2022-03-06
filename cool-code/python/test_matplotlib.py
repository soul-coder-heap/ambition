import matplotlib.pyplot as plt
import numpy as np
#import torch
x = np.arange(0, 10, 0.1)
y = np.random.randn(len(x))
y = np.sin(x)
print(x)
print(y)
plt.plot(x, y)
plt.title('random numbers')
plt.show()
print("show success")