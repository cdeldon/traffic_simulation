import numpy as np

def parse_output(path) :
    # read output
    data = np.loadtxt(path)
    n = (len(data[0])-1)//2
    tt = data[:,0]
    xx = data[:, 1:n+1]
    vv = data[:, n+1:-1]
    throughput = data[:,-1]
    
    return n, tt, xx, vv, throughput