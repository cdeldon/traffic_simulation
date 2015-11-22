import sys
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import numpy as np

if len(sys.argv)<=1:
    data = np.loadtxt("cars_test.dat")
else :
    data = np.loadtxt(sys.argv[1])


n = (len(data[0])-1)//2
tt = data[:,0]
xx = data[:, 1:n+1]
vv = data[:, n+1:-1]
throughput = data[:,-1]


road_length = np.max(xx);


# First set up the figure, the axis, and the plot element we want to animate
fig = plt.figure()
ax = plt.axes()
plt.axis('equal')
scat = ax.scatter(xx[0,:], np.zeros_like(xx[0,:]))
ax.hold(False)
old_data = xx[0,:];

# initialization function: plot the background of each frame
def init():
    ax.hold(False)
    ax.set_xlim([-road_length/2,road_length/2])
    ax.set_ylim([-road_length/2,road_length/2])
    return ax,

# animation function.  This is called sequentially
def animate(i):
    print('frame: ', i)
    x = road_length/(2*np.pi)*np.cos(2*np.pi*xx[i,:]/road_length)
    y = road_length/(2*np.pi)*np.sin(2*np.pi*xx[i,:]/road_length)
    scat = ax.scatter(x,y)
    ax.hold(True)
    scat = ax.scatter(x[0],y[0], color='r',s=100, label="t={}".format(tt[i]))
    ax.hold(False)
    ax.set_xlim([-road_length/2,road_length/2])
    ax.set_ylim([-road_length/2,road_length/2])
    ax.legend(loc = "best")
    return scat,

# call the animator.  blit=True means only re-draw the parts that have changed.
anim = animation.FuncAnimation(fig, animate, init_func=init,
                               frames=len(tt), interval=1, blit=False)

# save the animation as an mp4.  This requires ffmpeg or mencoder to be
# installed.  The extra_args ensure that the x264 codec is used, so that
# the video can be embedded in html5.  You may need to adjust this for
# your system: for more information, see
# http://matplotlib.sourceforge.net/api/animation_api.html
#anim.save('basic_animation.mp4', fps=30, extra_args=['-vcodec', 'libx264'])

plt.show()
