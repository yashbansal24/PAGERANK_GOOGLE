import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

data = pd.read_csv('errors.txt')
data = np.array(data)
x = np.arange(0,len(data))
plt.scatter(x,data)
plt.title("Error Vs Iteration")
plt.xlabel('Iteration')
plt.ylabel('Error')
plt.plot(data)
plt.savefig('output_error.png')
plt.show()
