from PIL import Image
import random
import numpy as np
from SNR import signal_to_noise


img=Image.open('lena.bmp')
original = np.asarray(img)

test = np.asarray(Image.open('median_5x5.bmp'))
snr=signal_to_noise(test,original)
print(snr)