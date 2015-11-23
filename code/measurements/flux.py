from subprocess import check_call
import numpy as np
from matplotlib import pyplot as plt

from paths import SETTINGS_PATH, OUTPUT_PATH, SIM_PATH, SIM_WD
from common import parse_output

SETTINGS_TEMPLATE = """
ROAD_LENGTH = 1000
VMAX      = 15
MIN_DIST  = 2
TIME_HEAD = 1.6
AMAX      = 0.73
DMAX      = 1.67
CAR_SIZE  = 5
DT        = 0.250
END_TIME  = 3000
GAMMA     = 3


# Output format
POSITIONS = 1
VELOCITIES = 1
OUT_FREQ = 100
THROUGHPUT = 1
"""


exec SETTINGS_TEMPLATE

def compute_flux():
    ncars = np.arange(5, 150, 5)
    flux = ncars*0.
    density = ncars*0.
    
    for i, cars in enumerate(ncars):
        print "\n\nRunning sim for ncars = {0}".format(cars)
        settings_file = open(SETTINGS_PATH + "/flux.txt", "w")
        settings_file.write(SETTINGS_TEMPLATE)
        settings_file.write("ID = flux{0}\nN_CARS= {0}".format(cars))
        settings_file.close()
    
        check_call([SIM_PATH, SETTINGS_PATH+"/flux.txt"], cwd = SIM_WD)
        
        # read output
        n, tt, xx, vv, throughput = parse_output(OUTPUT_PATH+"/cars_flux{}.dat".format(cars))  
        
        # calculate the maximal throughput (cars per minute)
        maxFlux = 0.
#        for t in np.arange(len(tt)-1):
#            maxFlux = np.max([maxFlux, throughput[t+1]-throughput[t]])
        
        flux[i] = throughput[-1]*1./tt[-1] 
        density[i] = cars*(1000./ROAD_LENGTH)
        

    flux = flux*60*60;
    np.save("density", density)
    np.save("flux", flux)
    return density, flux


def make_plot():
    density = np.load("density.npy")
    flux = np.load("flux.npy")
    
  
    plt.plot(density, flux, label="car flux")
    plt.xlabel(r"car density (cars/km)")
    plt.ylabel(r"flux (cars/h)")
    
    plt.grid(True)
    plt.savefig("flux.png")
    plt.legend(loc="best")
    plt.show()
    
    
if __name__ == "__main__":
    compute_flux()
    make_plot()

