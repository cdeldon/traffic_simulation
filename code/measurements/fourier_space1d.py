from subprocess import check_call
import numpy as np
from scipy.interpolate import griddata
from scipy.fftpack import fft2
from numpy.fft import fftshift, fftfreq, fft
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
    return parse_output(OUTPUT_PATH + "/cars_fourier_space.dat")

    
def create_grid():
    n, tt, xx, vv, throughput = run_sim()
    tt_2d = np.tile(tt, (n,1)).T
    grid_t, grid_x = np.mgrid[500.:END_TIME:1024j, 0.:ROAD_LENGTH:3j]    
    grid_v = np.nan_to_num(griddata((tt_2d.flatten(), xx.flatten()), vv.flatten(), (grid_t, grid_x), rescale = True))
    sample_spacing_t = grid_t[2,0]-grid_t[1,0]
    sample_spacing_x = grid_x[0,2]-grid_x[0,1]
    
    np.savez("fourier_data", tt_2d=tt_2d, grid_t=grid_t, grid_v=grid_v, grid_x=grid_x,
                              sample_spacing_t=sample_spacing_t, 
                              sample_spacing_x=sample_spacing_x)



def make_fft_plot():
    data_file = np.load("fourier_data.npz")
    grid_v = data_file["grid_v"]
    sample_spacing_t = data_file["sample_spacing_t"]
    row_fft = np.log(np.abs(fftshift(fft(grid_v[:,grid_v.shape[1]/2]))))
    freq_t = fftshift(fftfreq(row_fft.shape[0], sample_spacing_t))
    idx = freq_t>0
    row_fft = row_fft[idx]
    freq_t = freq_t[idx]
    plt.xlim((20, 1000))
    plt.semilogx(1./freq_t, row_fft)
    plt.xlabel("period (s)")
    plt.ylabel("magnitude (a.u.)")
    print "peak at index", np.argmax(row_fft), "i.e. at period", 1/freq_t[np.argmax(row_fft)]
    plt.vlines(1/freq_t[np.argmax(row_fft)], 0,10, linestyles = "dotted")
    plt.show()



if __name__ == "__main__":
    #create_grid()
    make_fft_plot()
