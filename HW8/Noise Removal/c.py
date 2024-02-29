from PIL import Image
import random
import numpy as np
from SNR import signal_to_noise


def boxfilter3by3(img):
    row,col=img.shape
    img=np.pad(img,(1,1),'edge')
    filter=np.array([[1,1,1],
                     [1,1,1],
                     [1,1,1]])
    coef=1.0/filter.sum()
    result=np.zeros((row,col),dtype=int)

    for i in range(1,row+1):
        for j in range(1,col+1):
            temp = 0.0
            for x in range(3):
                for y in range(3):
                    temp += img[i-1+x][j-1+y]*filter[x][y]
            result[i-1][j-1] = temp * coef
    return result

def boxfilter5by5(img):
    row,col=img.shape
    img=np.pad(img,(2,2),'edge')
    filter=np.array([[1,1,1,1,1],
                    [1,1,1,1,1],
                    [1,1,1,1,1],
                    [1,1,1,1,1],
                    [1,1,1,1,1]])
    coef=1.0/filter.sum()
    result=np.zeros((row,col),dtype=int)

    for i in range(2,row+2):
        for j in range(2,col+2):
            temp = 0.0
            for x in range(5):
                for y in range(5):
                    temp += img[i-2+x][j-2+y]*filter[x][y]
            result[i-2][j-2] = temp * coef
    return result


img=Image.open('lena.bmp')
original = np.asarray(img)

g10_3 = np.asarray(Image.open('lena_Gaussian10.jpg'))
g30_3 = np.asarray(Image.open('lena_Gaussian30.jpg'))
sap_053 = np.asarray(Image.open('lena_sap05.jpg'))
sap_103 = np.asarray(Image.open('lena_sap10.jpg'))

temp1 = boxfilter3by3(g10_3)
temp2 = boxfilter3by3(g30_3)
temp3 = boxfilter3by3(sap_053)
temp4 = boxfilter3by3(sap_103)

snr=signal_to_noise(temp1,original)
print(snr)
snr=signal_to_noise(temp2,original)
print(snr)
snr=signal_to_noise(temp3,original)
print(snr)
snr=signal_to_noise(temp4,original)
print(snr)

img1=Image.fromarray(temp1)
img1.show(title='lena_Gaussian10_box3by3')
img1=img1.convert("L")
img1.save('lena_Gaussian10_box3by3.jpg',format='JPEG')

img1=Image.fromarray(temp2)
img1.show(title='lena_Gaussian30_box3by3')
img1=img1.convert("L")
img1.save('lena_Gaussian30_box3by3.jpg',format='JPEG')

img1=Image.fromarray(temp3)
img1.show(title='lena_sap05_box3by3')
img1=img1.convert("L")
img1.save('lena_sap05_box3by3.jpg',format='JPEG')

img1=Image.fromarray(temp4)
img1.show(title='lena_sap10_box3by3')
img1=img1.convert("L")
img1.save('lena_sap10_box3by3.jpg',format='JPEG')


temp1 = boxfilter5by5(g10_3)
temp2 = boxfilter5by5(g30_3)
temp3 = boxfilter5by5(sap_053)
temp4 = boxfilter5by5(sap_103)

snr=signal_to_noise(temp1,original)
print(snr)
snr=signal_to_noise(temp2,original)
print(snr)
snr=signal_to_noise(temp3,original)
print(snr)
snr=signal_to_noise(temp4,original)
print(snr)

img1=Image.fromarray(temp1)
img1.show(title='lena_Gaussian10_box5by5')
img1=img1.convert("L")
img1.save('lena_Gaussian10_box5by5.jpg',format='JPEG')

img1=Image.fromarray(temp2)
img1.show(title='lena_Gaussian30_box5by5')
img1=img1.convert("L")
img1.save('lena_Gaussian30_box5by5.jpg',format='JPEG')

img1=Image.fromarray(temp3)
img1.show(title='lena_sap05_box5by5')
img1=img1.convert("L")
img1.save('lena_sap05_box5by5.jpg',format='JPEG')

img1=Image.fromarray(temp4)
img1.show(title='lena_sap10_box5by5')
img1=img1.convert("L")
img1.save('lena_sap10_box5by5.jpg',format='JPEG')