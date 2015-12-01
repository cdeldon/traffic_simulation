import sys
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import numpy as np

saveAnim = False;

if len(sys.argv)<=1:
    data = np.loadtxt("cars_test.dat")
else :
    data = np.loadtxt(sys.argv[1])
    dataLight = np.loadtxt(sys.argv[1] + "_lights.dat")
    if len(sys.argv) ==3:
        saveAnim = (sys.argv[2] == "save")


n = (len(data[0])-1)//2
tt = data[:,0]
xx = data[:, 1:n+1]
vv = data[:, n+1:-1]
throughput = data[:,-1]

nLights = int(dataLight[0,0])
xxLights = dataLight[:,1::2]
onLights = dataLight[:,2::2]

# traveled distance of car0;
distanceX0 = 0
oldDistance = 0
loops = 0

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
    ax.set_xlim([-road_length/4,road_length/4])
    ax.set_ylim([-road_length/4,road_length/4])
    return ax,

# animation function.  This is called sequentially
def animate(i):
    print('frame: ', i)
    x = road_length/(2*np.pi)*np.cos(2*np.pi*xx[i,:]/road_length)
    y = road_length/(2*np.pi)*np.sin(2*np.pi*xx[i,:]/road_length)
    scat = ax.scatter(x,y)
    ax.hold(True)
    # calculate the time in minutes, hours and second
    
    scat = ax.scatter(x[0],y[0], color='r',s=100)
    # add the traffic lights
    if nLights>0:
        xl = 1.1*road_length/(2*np.pi)*np.cos(2*np.pi*xxLights[i,:]/road_length)
        yl = 1.1*road_length/(2*np.pi)*np.sin(2*np.pi*xxLights[i,:]/road_length)
        for l in range(nLights):
            if(onLights[i,l] == 1):
                scat = ax.scatter(xl[l],yl[l], marker="s" ,color='r', s=50)
            else:
                scat = ax.scatter(xl[l],yl[l], marker="^", color='g', s=50)
        
    ax.hold(False)
    ax.set_xlim([-road_length/4,road_length/4])
    ax.set_ylim([-road_length/4,road_length/4])
    m, s = divmod(tt[i], 60)
    h, m = divmod(m, 60)
    
    ## ADD text informations
    vskip = road_length/6 - road_length/7;
    # time informations
    ax.text(road_length/7,road_length/6, r"$Time:$ $%d:%02d:%02d$" % (h, m, s))
        
    # add velocity information of the red car
    ax.text(road_length/7,road_length/6 - vskip,    r"$v:$      $%d [km/h]$" % int(vv[i,0]*3.6))
    
    global oldDistance
    global distanceX0
    global loops
    
    distanceX0 = xx[i,0] + loops*road_length;
    if distanceX0 < oldDistance: #if the car completed a loop
        loops += 1
        distanceX0 += road_length
        
    oldDistance = distanceX0
        
    ax.text(road_length/7,road_length/6 - 1.7*vskip,    r"$d:$      $%d [m]$" % int(distanceX0))
    
    # add velocity information of the simulation
    ax.text(road_length/7,road_length/6 -2.7*vskip, r"$avg_v:$ $%d [km/h]$" % int(np.mean(vv[i,:])*3.6))
        
    return scat,

# call the animator.  blit=True means only re-draw the parts that have changed.
anim = animation.FuncAnimation(fig, animate, init_func=init,
                               frames=len(tt), interval=1, blit=False)
                
if saveAnim:               
    anim.save('basic_animation.mp4', fps=30, extra_args=['-vcodec', 'libx264'])
else:                              
    plt.show()
                            
# save the animation as an mp4.  This requires ffmpeg or mencoder to be
# installed.  The extra_args ensure that the x264 codec is used, so that
# the video can be embedded in html5.  You may need to adjust this for
# your system: for more information, see
# http://matplotlib.sourceforge.net/api/animation_api.html


