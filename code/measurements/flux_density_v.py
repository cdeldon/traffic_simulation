from subprocess import check_call
import numpy as np
from matplotlib import pyplot as plt

from paths import SETTINGS_PATH, OUTPUT_PATH, SIM_PATH, SIM_WD
from common import parse_output

SETTINGS_TEMPLATE = """
ROAD_LENGTH = 1000

MIN_DIST  = 2
TIME_HEAD = 1.6
AMAX      = 1.5
DMAX      = 2.5
CAR_SIZE  = 5
DT        = 0.250
END_TIME  = 3000
GAMMA     = 2


# Output format
POSITIONS = 1
VELOCITIES = 1
OUT_FREQ = 100
THROUGHPUT = 1
OUT_LI = 0
OUT_OB = 0
"""


exec SETTINGS_TEMPLATE

def compute_flux():
    ncars = np.arange(2, 150, 2);
    # set the velocity of the cars manually (in km/h)
    vcars = np.array([30, 50, 80, 100, 120])/3.6
    
    flux = np.zeros((len(vcars), len(ncars)))
    density = ncars*(1000./ROAD_LENGTH)
    
    for j, vel in enumerate(vcars):
        for i, cars in enumerate(ncars):
            print "\n\nRunning sim for ncars = {0} and maxV = {1}".format(cars, vel)
            settings_file = open(SETTINGS_PATH + "/flux.txt", "w")
            settings_file.write(SETTINGS_TEMPLATE)
            settings_file.write("ID = flux{0}_{1}\nN_CARS= {0}\nVMAX= {1}".format(cars, vel))
            settings_file.close()
        
            check_call([SIM_PATH, SETTINGS_PATH+"/flux.txt"], cwd = SIM_WD)
            
            # read output
            n, tt, xx, vv, throughput = parse_output(OUTPUT_PATH+"/cars_flux{0}_{1}.dat".format(cars, vel))  
            
            # calculate the maximal throughput (cars per minute)
            
            # maxFlux = 0.
            # for t in np.arange(len(tt)-1):
            #    maxFlux = np.max([maxFlux, throughput[t+1]-throughput[t]])
            
            # calculates the average throughput
            flux[j,i] = throughput[-1]*1./tt[-1] 
        

    flux = flux*60*60;
    np.save("flux_density_v_density", density)
    np.save("flux_density_v_flux", flux)
    np.save("flux_density_v_maxV", vcars)
    return density, flux, vcars


def make_plot():

    density = np.load("flux_density_v_density.npy")
    flux = np.load("flux_density_v_flux.npy")
    velocity = np.load("flux_density_v_maxV.npy")
    velocity = velocity*3.6;
    
    for i, v in enumerate(velocity):
        plt.plot(density, flux[i,:], label=r"$v_{max}= "+str(int(velocity[i]))+"[km/h]$")
        
    plt.xlabel(r"car density (cars/km)")
    plt.ylabel(r"flux (cars/h)")
#    plt.title(r"Traffic Flux for different car densities and maximal velocities")
    plt.legend(loc="best")
    
    plt.grid(True)
    plt.savefig("flux_density_v.png")
    plt.savefig("flux_density_v.pdf")
    plt.show()
    
    
if __name__ == "__main__":
    compute_flux()
    make_plot()

