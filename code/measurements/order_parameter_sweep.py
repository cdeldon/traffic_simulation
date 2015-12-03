from subprocess import check_call
import numpy as np
from matplotlib import pyplot as plt
import matplotlib

from paths import SETTINGS_PATH, OUTPUT_PATH, SIM_PATH, SIM_WD
from common import parse_output
from order_parameter import compute_variances

SETTINGS_TEMPLATE = """
VMAX      = 15
MIN_DIST  = 2
TIME_HEAD = 1.5
AMAX      = 0.6
DMAX      = 1.5
CAR_SIZE  = 5
DT        = 0.250
END_TIME  = 30000


# Output format
POSITIONS = 1
VELOCITIES = 1
OUT_FREQ = 1000
THROUGHPUT = 1
"""

exec SETTINGS_TEMPLATE

N_gammas = 51
Fixed_density = 0.05 # 50 cars per km

road_lengths = np.array([1000, 2000, 5000, 10000])
N_road_length = len(road_lengths)

N_cars = (Fixed_density * road_lengths).astype(int)

def run_sim():
    sims = np.zeros((N_road_length,2, N_gammas))   
    for i,l in enumerate(road_lengths):
        settings = SETTINGS_TEMPLATE + "N_CARS = {0}\nROAD_LENGTH = {1}\n".format(N_cars[i], l)
        gammas, variances = compute_variances(N_gammas, save = False, settings= settings)
        sims[i] = gammas, variances
        
    np.save("sims", sims)

def make_plot():
    sims = np.load("sims.npy")
    plt.figure(figsize=(4,3))
    matplotlib.rcParams.update({'font.size': 11})
    for i,l in enumerate(road_lengths):
        gammas, variances = sims[i]
        plt.plot(gammas, np.sqrt(variances), label="{} km".format(int(l/1000)))
        
    plt.xlabel(r"gap potential exponent $\gamma$")
    plt.ylabel(r"deviation of velocities $\sqrt{\langle v^2 \rangle}$ (m/s)")
    plt.ylim((-1, np.sqrt(np.max(variances))+1))
    
    plt.grid(True)
    plt.legend(loc="lower left", prop={'size':11})
    plt.tight_layout()
    plt.savefig("order_parameter_sweep.png")
    plt.savefig("order_parameter_sweep.pdf")
    plt.show()
    
    
if __name__ == "__main__":
    run_sim()
    make_plot()

