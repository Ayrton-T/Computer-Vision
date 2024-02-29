from PIL import Image
import numpy as np
import math

def signal_to_noise(noise,original):
    row,col=original.shape

    noise=noise/255.0
    original=original/255.0 

    n=row*col
    u=np.mean(original)
    vs=0.0
    for i in range(row):
        for j in range(col):
            vs+=(math.pow(original[i][j]-u,2))/n
    
    un=0.0
    for i in range(row):
        for j in range(col):
            un+=(noise[i][j]-original[i][j])
    un/=n

    vn=0.0
    for i in range(row):
        for j in range(col):
            vn+=(math.pow(noise[i][j]-original[i][j]-un,2))
    vn/=n

    ans = 20*math.log10(math.sqrt(vs)/math.sqrt(vn))

    return ans