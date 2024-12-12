import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from matplotlib.animation import FuncAnimation

G = 6.67430e-11 

planet_mass = 5.972e24
planet_radius = 6371000
satellite_height = 100000

r = planet_radius + satellite_height
orbital_velocity = np.sqrt(G * planet_mass / r)

time = np.linspace(0, 2 * np.pi, 1000) 
x = r * np.cos(time)  
y = r * np.sin(time)  
z = np.zeros_like(time)

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
ax.plot(x, y, z, label='Orbit', color='b') 
ax.scatter(0, 0, 0, color='r', label='Planet')
ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')
ax.set_title('Planet and Satellite Orbit')
ax.legend()

top, = ax.plot([], [], [], 'go', markersize=10)

def update(frame):
    top.set_data([x[frame]], [y[frame]])
    top.set_3d_properties(z[frame])
    return top,

ani = FuncAnimation(fig, update, frames=len(time), interval=1, blit=True)

plt.show()