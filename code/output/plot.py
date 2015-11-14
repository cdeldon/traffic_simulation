import numpy
import sys
from matplotlib import pyplot as plt

if len(sys.argv)<=1:
    data = numpy.loadtxt("cars_test.dat")
else :
    data = numpy.loadtxt(sys.argv[1])


n = (len(data[0])-1)//2
tt = data[:,0]
xx = data[:, 1:n+1]
vv = data[:, n+1:-2]
throughput = data[:,-1]

plt.title("Positions")
plt.xlabel("time")
plt.ylabel("position")
plt.plot(tt,xx, "rx")
plt.show()



plt.title("Velocity & trajectories")
for i in range(0,len(xx[0,:]), max(1, len(xx[0,:])/10)):
    t = tt[:]
    x = xx[:,i]
    # detect discontinuities
    pos = numpy.array(numpy.where(numpy.abs(numpy.diff(x)) >= numpy.diff(t)[0]*70))+1
    for p in pos:
        t = numpy.insert(t, p, numpy.nan)
        x = numpy.insert(x, p, numpy.nan)
    plt.plot(t, x, "k:")



# sort cars
for i in range(len(xx)):
    start = numpy.argmin(xx[i,:])
    xx[i,:] = numpy.hstack((xx[i,start:], xx[i,:start]))
    vv[i,:] = numpy.hstack((vv[i,start:], vv[i,:start]))

tt_2d = numpy.tile(tt, (n,1)).T
plt.xlabel("time")
plt.ylabel("position")
plt.pcolormesh(tt_2d,xx, vv)
plt.colorbar()
plt.show()


plt.title("throughput")
plt.xlabel("time")
plt.ylabel("# of cars")
plt.plot(tt,throughput)
plt.show()
