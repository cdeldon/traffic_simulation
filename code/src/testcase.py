import numpy as np
from matplotlib import pyplot as plt
import matplotlib.animation as animation

# this script performs a simulation unsing the IDM  as implemented in the
# cpp files and visualized the trajectory of a breaking car with different
# interaction parameter gamma

# parameters of the simulation
gammas = np.linspace(2,10,2)
nGamma = len(gammas)

AMAX = 0.6
DMAX = 1.6
VMAX = 50.0

MIN_DIST  = 2.0
TIME_HEAD = 1.5
CAR_SIZE  = 5.0

DELTA = 4.0

# dynamics

v0 = 30.0
x0 = -100.0

dt = 0.01
T = 20.0
nSteps = int(T/dt)

x = np.zeros((nGamma, nSteps+1))
v = np.zeros((nGamma, nSteps+1))


def getAcceleration(x,v, gamma):
    
    # velocity difference
    deltaV = v - 0.0

    # desired gap to leading vehicle
    s_star = MIN_DIST + np.max([0.0 , v * TIME_HEAD + (v * deltaV)/(2.0*np.sqrt(AMAX*DMAX))])

    # current gap
    s_alpha = 0.0 - x
    s_alpha -= CAR_SIZE

    gap_term = (s_star / s_alpha)**gamma;

    # speed limit
    limit_term = (v / VMAX)**DELTA
    # acceleration computation
    a = AMAX * (1. - limit_term - gap_term)
    
    return a

#perform the simulation once per parameter gamma
for i, gamma in enumerate(gammas):
    v0 = 15.0
    x0 = -100.0
    t = 0.0
    
    x[i,0] = x0;
    v[i,0] = v0;
    
    # time loop
    for j in range(nSteps):
        a = getAcceleration(x[i,j],v[i,j],gamma)
        
        move = v[i,j] * dt + 0.5*a*dt*dt

        v[i,j+1] = v[i,j] + a * dt
        x[i,j+1] = x[i,j] + move
        
        
plt.figure(1)
plt.subplot(111)
for i,gamma in enumerate(gammas):
    plt.plot(x[i,:], v[i,:], label="Gamma = {}".format(gamma))
    
plt.legend()
plt.show()

fig = plt.figure(2)
ax = plt.subplot(111, autoscale_on=False, xlim=(x0-1, 1), ylim=(-1, nGamma))
yLoc = np.arange(-1, nGamma-1, 1) + 1


line, = ax.plot(x[:,0],yLoc, 'o', lw=2)
time_text = ax.text(0.02, 0.95, '', transform=ax.transAxes)
t = 0

def init():
    """initialize animation"""
    line.set_data([],[])
    time_text.set_text('')
    return line, time_text
    
def animate(i):
    """perform animation step"""
    global x, dt, t
    
    line.set_data(x[:,i],yLoc)
    time_text.set_text('time = %.1f' %t)
    t+=dt
    return line, time_text
    
ani = animation.FuncAnimation(fig, animate, frames=nSteps,
                              interval=0.1, blit=True, init_func=init)
    

plt.show()      
    





