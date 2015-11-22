from subprocess import check_call
import numpy as np
from scipy.interpolate import griddata
from scipy.fftpack import fft2
from numpy.fft import fftshift, fftfreq
from matplotlib import pyplot as plt

from paths import SETTINGS_PATH, OUTPUT_PATH, SIM_PATH, SIM_WD
from common import parse_output

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
END_TIME  = 4000
GAMMA = 2.05


# Output format
POSITIONS = 1
VELOCITIES = 1
OUT_FREQ = 4
THROUGHPUT = 1
"""

#Make the expressions above available in this script
exec SETTINGS_TEMPLATE

SETTINGS_TEMPLATE += "ID = fourier_space\n"


def run_sim():
    settings_file = open(SETTINGS_PATH + "/fourier_space.txt", "w")
    settings_file.write(SETTINGS_TEMPLATE)
    settings_file.close()
    
    check_call([SIM_PATH, SETTINGS_PATH+"/fourier_space.txt"], cwd = SIM_WD)
    
    # read output
    n, tt, xx, vv, throughput = parse_output(OUTPUT_PATH + "/cars_fourier_space.dat")
    
    # create grid
    tt_2d = np.tile(tt, (n,1)).T
    grid_t, grid_x = np.mgrid[500.:END_TIME:1024j, 0.:ROAD_LENGTH:1024j]
    grid_v = np.nan_to_num(griddata((tt_2d.flatten(), xx.flatten()), vv.flatten(), (grid_t, grid_x), rescale = True))
    sample_spacing_t = grid_t[2,0]-grid_t[1,0]
    sample_spacing_x = grid_x[0,2]-grid_x[0,1]
    
    grid_fft = np.log(np.abs(fftshift(fft2(grid_v))))
    freq_t = fftshift(fftfreq(grid_fft.shape[0], sample_spacing_t))
    freq_x = fftshift(fftfreq(grid_fft.shape[1], sample_spacing_x))
    print "computation of Fourier transform complete"
    
    plt.figure()    
    plt.subplot(1,2,1)
    plt.title("velocity field in real space (m/s)")
    plt.xlabel("time (s)")
    plt.ylabel("position (m)")
    plt.pcolormesh(grid_t, grid_x, grid_v)
    plt.colorbar()
    
    plt.subplot(1,2,2)
    plt.pcolormesh(freq_t, freq_x, grid_fft.T)
    plt.title("velocity field in frequency space\n(logarithmic magnitude)")
    plt.xlabel("frequency (1/s)")
    plt.ylabel("wave number (1/m)")
    plt.colorbar()
    plt.show()


if __name__ == "__main__":
    run_sim()
