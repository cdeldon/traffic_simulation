from subprocess import check_call
import numpy as np
from matplotlib import pyplot as plt
from scipy.interpolate import griddata
import matplotlib

from paths import SETTINGS_PATH, OUTPUT_PATH, SIM_PATH, SIM_WD
from common import parse_output

SETTINGS_TEMPLATE = """
N_CARS    = 50
ROAD_LENGTH = 1000
VMAX      = 15
MIN_DIST  = 2
TIME_HEAD = 1.5
AMAX      = 0.6
DMAX      = 1.5
CAR_SIZE  = 5
DT        = 0.125
END_TIME  = 2000


# Output format
POSITIONS = 1
VELOCITIES = 1
OUT_FREQ = 8
THROUGHPUT = 1
"""

exec SETTINGS_TEMPLATE

SETTINGS_TEMPLATE += "ID = free_road\n"


def make_plot():
    matplotlib.rcParams.update({'font.size': 11})
    plt.figure(figsize = (4,3), dpi = 200)
    settings_file = open(SETTINGS_PATH + "/free_road.txt", "w")
    settings_file.write(SETTINGS_TEMPLATE)
    settings_file.close()
    
    check_call([SIM_PATH, SETTINGS_PATH+"/free_road.txt"], cwd = SIM_WD)
    # read output
    n, tt, xx, vv, throughput = parse_output(OUTPUT_PATH+"/cars_free_road.dat")      

    matplotlib.rcParams.update({'font.size': 11})

    for i in range(0,len(xx[0,:]), max(1, len(xx[0,:])/10)):
        t = tt[:]
        x = xx[:,i]
        # detect discontinuities
        pos = np.array(np.where(np.abs(np.diff(x)) >= np.diff(t)[0]*70))+1
        for p in pos:
            t = np.insert(t, p, np.nan)
            x = np.insert(x, p, np.nan)
        if i%100==0:
           plt.plot(t, x, "w:")

    # sort cars
    for i in range(len(xx)):
        start = np.argmin(xx[i,:])
        xx[i,:] = np.hstack((xx[i,start:], xx[i,:start]))
        vv[i,:] = np.hstack((vv[i,start:], vv[i,:start]))

    tt_2d = np.tile(tt, (n,1)).T
    grid_t, grid_x = np.mgrid[0.:END_TIME:512j, 0.:ROAD_LENGTH:512j]
    grid_v = np.nan_to_num(griddata((tt_2d.flatten(), xx.flatten()), vv.flatten(), (grid_t, grid_x), rescale = True))
    
    plt.xlabel("time [s]")
    plt.ylabel("position [m]")
    plt.pcolormesh(grid_t, grid_x, grid_v)
    plt.colorbar()
    ax = plt.gca()
    ax.set_ylim([0,np.max(np.max(xx))])
    
    plt.tight_layout()
    plt.savefig("free_road.png",dpi=600)
    #plt.savefig("free_road.pdf")
    plt.show()
    
    
if __name__ == "__main__":
    make_plot()

