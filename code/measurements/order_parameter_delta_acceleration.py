from subprocess import check_call
import numpy as np
from matplotlib import pyplot as plt
import matplotlib

from paths import SETTINGS_PATH, OUTPUT_PATH, SIM_PATH, SIM_WD
from common import parse_output

SETTINGS_TEMPLATE = """
N_CARS    = 100
ROAD_LENGTH = 2000
VMAX      = 15
MIN_DIST  = 2
TIME_HEAD = 1.5
CAR_SIZE  = 5
DT        = 0.250
END_TIME  = 4000


# Output format
POSITIONS = 1
VELOCITIES = 1
OUT_FREQ = 80
THROUGHPUT = 1
"""

AMAX = 0.6
DMAX = np.linspace(0.5, 2.0, 61)
GAMMA = 2


def compute_variances(settings = SETTINGS_TEMPLATE, gammas = GAMMA):
    
    variances = 0*DMAX
    
    for i, decel in enumerate(DMAX):
        print "\n\nRunning sim for DMAX = {0}".format(decel)
        settings_file = open(SETTINGS_PATH + "/order_parameter.txt", "w")
        settings_file.write(settings)
        settings_file.write("ID = order_parameter{1}\nAMAX = {0}\nDMAX = {1}".format(AMAX, decel))
        settings_file.close()
    
        check_call([SIM_PATH, SETTINGS_PATH+"/order_parameter.txt"], cwd = SIM_WD)
        
        # read output
        n, tt, xx, vv, throughput = parse_output(OUTPUT_PATH+"/cars_order_parameter{}.dat".format(decel))      
        
        variances[i] = np.var(vv[-1])
          
    np.save("variances_delta_acceleration", variances)
    np.save("deceleration_delta_acceleration", DMAX)
        
    return DMAX, variances


def make_plot():
    plt.figure(figsize=(3,2.25))
    variances = np.load("variances_delta_acceleration.npy")
    DMAX = np.load("deceleration_delta_acceleration.npy")

    matplotlib.rcParams.update({'font.size': 11})
    matplotlib.rcParams['mathtext.fontset'] = 'custom'
    matplotlib.rcParams['mathtext.rm'] = 'Bitstream Vera Sans'
    matplotlib.rcParams['mathtext.it'] = 'Bitstream Vera Sans:italic'
    matplotlib.rcParams['mathtext.bf'] = 'Bitstream Vera Sans:bold'

    
    plt.figure(figsize=(4,3), dpi = 200)
    plt.plot(DMAX-AMAX, np.sqrt(variances))
    plt.xlabel(r"de- & acceleration difference $b-a$ [m/s$^2$]")
    plt.ylabel("std. dev. of velocities\n"+r"$\sqrt{\langle v^2 \rangle}$ [m/s]")
    plt.ylim((-1, np.sqrt(np.max(variances))+1))
    
    
  
    plt.grid(True)
    plt.tight_layout()
    plt.savefig("order_parameter_delta_acceleration.png", dpi = 300)
    plt.savefig("order_parameter_delta_acceleration.pdf")
    plt.show()
    
    
if __name__ == "__main__":
    #compute_variances()
    make_plot()

