import numpy as np
import numpy.random as rng
import matplotlib.pyplot as plt

N = 1001
err = 0.1*np.ones(N)
t = np.linspace(0.0, 10.0, 1001)
y = np.sin(t) + err*rng.randn(N)
data = np.column_stack([t, y, err])
np.savetxt("data.txt", data)

plt.errorbar(t, y, yerr=err, fmt="o")
plt.show()
