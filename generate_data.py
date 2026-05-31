import numpy as np
import numpy.random as rng
import matplotlib.pyplot as plt

rng.seed(123)

# Sinusoid
#N = 1001
#err = 0.1*np.ones(N)
#t = np.linspace(0.0, 10.0, 1001)
#y = np.sin(t) + err*rng.randn(N)
#data = np.column_stack([t, y, err])
#np.savetxt("data.txt", data)

#plt.errorbar(t, y, yerr=err, fmt="o")
#plt.show()


# SDE
dt = 1E-3
skip = 100
y = 0.0
v = 0.0
t = 0.0
data = np.empty((10000, 3))
for i in range(skip*data.shape[0]):
    y = y + dt*v
    v = v - dt*y - 0.1*dt*v + np.sqrt(dt)*rng.randn()
    t += dt
    if i % skip == 0:
        data[i // skip, :] = [t, y + 0.5*rng.randn(), 0.5]
np.savetxt("data.txt", data)
plt.errorbar(data[:,0], data[:,1], yerr=data[:,2], fmt="o")
plt.show()

