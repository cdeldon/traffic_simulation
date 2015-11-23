from subprocess import check_call
import numpy as np
from matplotlib import pyplot as plt

from paths import SETTINGS_PATH, OUTPUT_PATH, SIM_PATH, SIM_WD
from common import parse_output

SETTINGS_TEMPLATE = """
N_CARS    = 500
ROAD_LENGTH = 10000
VMAX      = 15
MIN_DIST  = 2
TIME_HEAD = 1.5
AMAX      = 0.6
DMAX      = 2
CAR_SIZE  = 5
DT        = 0.250
END_TIME  = 30000


# Output format
POSITIONS = 1
VELOCITIES = 1
OUT_FREQ = 80
THROUGHPUT = 1
"""


def compute_variances():
    gammas = np.linspace(2.0, 3.5, 101)
    
    variances = 0*gammas
    
    for i, gamma in enumerate(gammas):
        print "\n\nRunning sim for gamma = {0}".format(gamma)
        settings_file = open(SETTINGS_PATH + "/order_parameter.txt", "w")
        settings_file.write(SETTINGS_TEMPLATE)
        settings_file.write("ID = order_parameter{0}\nGAMMA = {0}".format(gamma))
        settings_file.close()
    
        check_call([SIM_PATH, SETTINGS_PATH+"/order_parameter.txt"], cwd = SIM_WD)
        
        # read output
        n, tt, xx, vv, throughput = parse_output(OUTPUT_PATH+"/cars_order_parameter{}.dat".format(gamma))      
        
        variances[i] = np.var(vv[-1])
        
        
    np.save("variances", variances)
    np.save("gammas", gammas)
    return gammas, variances


def make_plot():
    variances = np.load("variances.npy")
    gammas = np.load("gammas.npy")
    
    
    plt.plot(gammas, np.sqrt(variances), label="data")
    plt.xlabel(r"gap potential exponent $\gamma$")
    plt.ylabel(r"deviation of velocities $\sqrt{\langle v^2 \rangle}$ (m/s)")
    plt.ylim((-1, np.sqrt(np.max(variances))+1))
    
    
    idx = np.where(np.logical_and(2.8 <= gammas, gammas <= 3) )
    a, b = np.polyfit(gammas[idx], np.sqrt(variances)[idx], 1)
    xx = np.linspace(2.,3.5, 2)
    #plt.plot(xx, a*xx+b, "g--", label="linear fit")
    plt.grid(True)
    plt.legend(loc="best")
    plt.savefig("order_parameter.png")
    plt.savefig("order_parameter.pdf")
    plt.show()
    
    
if __name__ == "__main__":
    #○compute_variances()
    make_plot()

