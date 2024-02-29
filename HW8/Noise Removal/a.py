from PIL import Image
import random
import numpy as np
from SNR import signal_to_noise


def GetGaussianNoise_Image_10(img):
    gaussianNoise_Image_10 = img.copy()
    for c in range(img.size[0]):
        for r in range(img.size[1]):
            noisePixel = int(img.getpixel((c,r)) + 10 * random.gauss(0,1))
            if noisePixel > 255:
                noisePixel = 255
            gaussianNoise_Image_10.putpixel((c,r), noisePixel)
    return gaussianNoise_Image_10

def GetGaussianNoise_Image_30(img):
    gaussianNoise_Image_30 = img.copy()
    for c in range(img.size[0]):
        for r in range(img.size[1]):
            noisePixel = int(img.getpixel((c,r)) + 30 * random.gauss(0,1))
            if noisePixel > 255:
                noisePixel = 255
            gaussianNoise_Image_30.putpixel((c,r), noisePixel)
    return gaussianNoise_Image_30


img=Image.open('lena.bmp')
original = np.asarray(img)

GGN10 = GetGaussianNoise_Image_10(img)
GGN30 = GetGaussianNoise_Image_30(img)

GGN10.show()
GGN10=GGN10.convert("L")
GGN10.save('lena_Gaussian10.jpg',format='JPEG')

GGN30.show()
GGN30=GGN30.convert("L")
GGN30.save('lena_Gaussian30.jpg',format='JPEG')

N10 = np.asarray(GGN10)
N30 = np.asarray(GGN30)


snr=signal_to_noise(N10,original)
print(snr)
snr=signal_to_noise(N30,original)
print(snr)


