from subprocess import check_call
import numpy as np
from matplotlib import pyplot as plt

from paths import SETTINGS_PATH, OUTPUT_PATH, SIM_PATH, SIM_WD
from common import parse_output
import matplotlib

SETTINGS_TEMPLATE = """
ROAD_LENGTH = 1000
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
OUT_FREQ = 80
THROUGHPUT = 1
"""

exec SETTINGS_TEMPLATE
  
    
def compute_critical_gamma(n_cars = 50, max_iter = 10):
    left = 1.4
    right = 3.5
    for i in range(max_iter):
        gamma = (left+right)/2.
        print "\n\nRunning sim for gamma = {0}".format(gamma)
        settings_file = open(SETTINGS_PATH + "/phasediagram.txt", "w")
        settings_file.write(SETTINGS_TEMPLATE)
        settings_file.write("ID = phasediagram{0}\nGAMMA = {0}\n".format(gamma))
        settings_file.write("N_CARS = {}\n".format(n_cars))
        settings_file.close()
    
        check_call([SIM_PATH, SETTINGS_PATH+"/phasediagram.txt"], cwd = SIM_WD)
        
        # read output
        n, tt, xx, vv, throughput = parse_output(OUTPUT_PATH+"/cars_phasediagram{}.dat".format(gamma))      
        
        variance = np.var(vv[-1])
        
        if variance > 0.04:
            left = gamma
        elif variance < 0.01:
            right = gamma
        else:
            return gamma
    return gamma
    
def run_sim():
    N_densities = 20
    densities = np.linspace(10, 150., N_densities)
    gamma_c = np.zeros_like(densities)
    for i,d in enumerate(densities):
        print "============================================="
        print d
        print "============================================="
                
        n_cars = ROAD_LENGTH * d * 0.001
        gamma_c[i] = compute_critical_gamma(n_cars)
    np.savez("phase_diagram", densities=densities, gamma_c=gamma_c)

def make_plot():
    
    with np.load("phase_diagram.npz") as f:
        densities = f["densities"]
        gamma_c = f["gamma_c"]

    matplotlib.rcParams.update({'font.size': 11})
    plt.figure(figsize = (4,3), dpi = 200)
    plt.plot(densities, gamma_c, linewidth = 3)
    plt.xlabel(r"vehicle density [km$^{-1}]$")
    plt.ylabel(r"interaction exponent $\gamma$")
    plt.ylim((1.5, 3.5))
    plt.xlim((min(densities), max(densities)))
    plt.fill_between(densities, gamma_c, interpolate = True, alpha = 0.3)
    plt.grid(True)
    plt.text(70, 2.2, "Unstable")
    plt.text(22, 3.2, "Homogeneous")
    plt.tight_layout()
    plt.savefig("phase_diagram.png")
    plt.savefig("phase_diagram.pdf")

    plt.show()
    
    
if __name__ == "__main__":
    #run_sim()    
    make_plot()

