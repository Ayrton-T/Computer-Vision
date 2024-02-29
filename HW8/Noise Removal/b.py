from PIL import Image
import random
import numpy as np
from SNR import signal_to_noise



def GSAP_05(img):
    SAP_05 = img.copy()
    for c in range(img.size[0]):
        for r in range(img.size[1]):
            random_Value = random.uniform(0, 1)
            if (random_Value <= 0.05):
                SAP_05.putpixel((c,r), 0)
            elif (random_Value >= 1-0.05):
                SAP_05.putpixel((c, r), 255)
            else:
                SAP_05.putpixel((c, r), img.getpixel((c, r)))
    return SAP_05

def GSAP_10(img):
    SAP_10 = img.copy()
    for c in range(img.size[0]):
        for r in range(img.size[1]):
            random_Value = random.uniform(0, 1)
            if (random_Value <= 0.1):
                SAP_10.putpixel((c,r), 0)
            elif (random_Value >= 1-0.1):
                SAP_10.putpixel((c, r), 255)
            else:
                SAP_10.putpixel((c, r), img.getpixel((c, r)))
    return SAP_10

img=Image.open('lena.bmp')

SAP05 = GSAP_05(img)
SAP10 = GSAP_10(img)

SAP05.show()
SAP05=SAP05.convert("L")
SAP05.save('lena_sap05.jpg',format='JPEG')


SAP10.show()
SAP10=SAP10.convert("L")
SAP10.save('lena_sap10.jpg',format='JPEG')

original = np.asarray(img)
noise1 = np.asarray(SAP05)
noise2 = np.asarray(SAP10)

snr=signal_to_noise(noise1,original)
print(snr)
snr=signal_to_noise(noise2,original)
print(snr)