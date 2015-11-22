from subprocess import check_call
import numpy as np
from matplotlib import pyplot as plt

from paths import SETTINGS_PATH, OUTPUT_PATH, SIM_PATH, SIM_WD

SETTINGS_TEMPLATE = """
N_CARS    = 50
ROAD_LENGTH = 1000
VMAX      = 15
MIN_DIST  = 2
TIME_HEAD = 1.5
AMAX      = 0.6
DMAX      = 2
CAR_SIZE  = 5
DT        = 0.125
END_TIME  = 8000


# Output format
POSITIONS = 1
VELOCITIES = 1
OUT_FREQ = 8
THROUGHPUT = 1
"""


gammas = np.linspace(2.0, 3.0, 51)

variances = 0*gammas

for i, gamma in enumerate(gammas):
    print "\n\nRunning sim for gamma = {0}".format(gamma)
    settings_file = open(SETTINGS_PATH + "/order_parameter.txt", "w")
    settings_file.write(SETTINGS_TEMPLATE)
    settings_file.write("ID = order_parameter{0}\nGAMMA = {0}".format(gamma))
    settings_file.close()

    check_call([SIM_PATH, SETTINGS_PATH+"/order_parameter.txt"], cwd = SIM_WD)
    
    # read output
    data = np.loadtxt(OUTPUT_PATH+"/cars_order_parameter{}.dat".format(gamma))
    n = (len(data[0])-1)//2
    tt = data[:,0]
    xx = data[:, 1:n+1]
    vv = data[:, n+1:-2]
    throughput = data[:,-1]
    
    
    variances[i] = np.var(vv[-1])
    
plt.plot(gammas, variances)
plt.show()

