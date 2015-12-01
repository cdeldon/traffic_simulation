from subprocess import check_call
import numpy as np
from matplotlib import pyplot as plt
import matplotlib

from paths import SETTINGS_PATH, OUTPUT_PATH, SIM_PATH, SIM_WD
from common import parse_output
from order_parameter import compute_variances

SETTINGS_TEMPLATE = """
ROAD_LENGTH = 1000
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

exec SETTINGS_TEMPLATE

N_densities = 5
N_gammas = 51
densities = np.linspace(10, 100., N_densities)

def run_sim():

    sims = np.zeros((N_densities,2, N_gammas))   
    for i,d in enumerate(densities):
        n_cars = ROAD_LENGTH * d * 0.001
        settings = SETTINGS_TEMPLATE + "N_CARS = {}\n".format(n_cars)
        gammas, variances = compute_variances(N_gammas, save = False, settings= settings)
        sims[i] = gammas, variances
        
    np.save("sims", sims)

def make_plot():
    sims = np.load("sims.npy")
    matplotlib.rcParams.update({'font.size': 16})
    for i,d in enumerate(densities):
        gammas, variances = sims[i]
        plt.plot(gammas, np.sqrt(variances), label="{} 1/km".format(d))
    plt.xlabel(r"gap potential exponent $\gamma$")
    plt.ylabel(r"deviation of velocities $\sqrt{\langle v^2 \rangle}$ (m/s)")
    #plt.ylim((-1, np.sqrt(np.max(variances))+1))
    
    plt.grid(True)
    plt.legend(loc="best")
    plt.savefig("order_parameter_sweep.png")
    plt.savefig("order_parameter_sweep.pdf")
    #plt.show()
    
    
if __name__ == "__main__":
    #run_sim()
    make_plot()

