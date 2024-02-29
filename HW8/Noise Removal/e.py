from PIL import Image
import random
import numpy as np
from SNR import signal_to_noise


def dilation(img):
    row,col=img.shape
    kernel=[[0,1,1,1,0],
			[1,1,1,1,1],
			[1,1,1,1,1],
			[1,1,1,1,1],
			[0,1,1,1,0]]
    result=np.zeros((row,col),dtype=int)
    for i in range(row):
        for j in range(col):
            temp = img[i][j]
            for k in range(-2,3):
                if k+i >= 512: break
                for l in range(-2,3):
                    if j+l >= 512 : break
                    if kernel[k+2][l+2] == 1 and img[k+i][l+j] > temp : temp = img[i+k][j+l]
            result[i][j] = temp

    return result


def erosion(img):
    row,col=img.shape
    kernel=[[0,1,1,1,0],
			[1,1,1,1,1],
			[1,1,1,1,1],
			[1,1,1,1,1],
			[0,1,1,1,0]]
    result=np.zeros((row,col),dtype=int)
    for i in range(row):
        for j in range(col):
            temp = img[i][j]
            for k in range(-2,3):
                if k+i >= 512: break
                for l in range(-2,3):
                    if j+l >= 512 : break
                    if kernel[k+2][l+2] == 1 and img[k+i][l+j] < temp : temp = img[i+k][j+l]
            result[i][j] = temp

    return result

def opening(img):
    return dilation(erosion(img))

def closing(img):
    return erosion(dilation(img))



img=Image.open('lena.bmp')
original = np.asarray(img)

g10_3 = np.asarray(Image.open('lena_Gaussian10.jpg'))
g30_3 = np.asarray(Image.open('lena_Gaussian30.jpg'))
sap_053 = np.asarray(Image.open('lena_sap05.jpg'))
sap_103 = np.asarray(Image.open('lena_sap10.jpg'))

temp = opening(g10_3)
temp1= closing(temp)
temp = opening(g30_3)
temp2= closing(temp)
temp = opening(sap_053)
temp3= closing(temp)
temp = opening(sap_103)
temp4= closing(temp)

snr=signal_to_noise(temp1,original)
print(snr)
snr=signal_to_noise(temp2,original)
print(snr)
snr=signal_to_noise(temp3,original)
print(snr)
snr=signal_to_noise(temp4,original)
print(snr)

img1=Image.fromarray(temp1)
img1.show(title='lena_Gaussian10_opening_then_closing')
img1=img1.convert("L")
img1.save('lena_Gaussian10_opening_then_closing.jpg',format='JPEG')

img1=Image.fromarray(temp2)
img1.show(title='lena_Gaussian30_opening_then_closing')
img1=img1.convert("L")
img1.save('lena_Gaussian30_opening_then_closing.jpg',format='JPEG')

img1=Image.fromarray(temp3)
img1.show(title='lena_sap05_opening_then_closing')
img1=img1.convert("L")
img1.save('lena_sap05_opening_then_closing.jpg',format='JPEG')

img1=Image.fromarray(temp4)
img1.show(title='lena_sap10_opening_then_closing')
img1=img1.convert("L")
img1.save('lena_sap10_opening_then_closing.jpg',format='JPEG')


temp = closing(g10_3)
temp1= opening(temp)
temp = closing(g30_3)
temp2= opening(temp)
temp = closing(sap_053)
temp3= opening(temp)
temp = closing(sap_103)
temp4= opening(temp)

snr=signal_to_noise(temp1,original)
print(snr)
snr=signal_to_noise(temp2,original)
print(snr)
snr=signal_to_noise(temp3,original)
print(snr)
snr=signal_to_noise(temp4,original)
print(snr)

img1=Image.fromarray(temp1)
img1.show(title='lena_Gaussian10_closing_then_opening')
img1=img1.convert("L")
img1.save('lena_Gaussian10_closing_then_opening.jpg',format='JPEG')

img1=Image.fromarray(temp2)
img1.show(title='lena_Gaussian30_closing_then_opening')
img1=img1.convert("L")
img1.save('lena_Gaussian30_closing_then_opening.jpg',format='JPEG')

img1=Image.fromarray(temp3)
img1.show(title='lena_sap05_closing_then_opening')
img1=img1.convert("L")
img1.save('lena_sap05_closing_then_opening.jpg',format='JPEG')

img1=Image.fromarray(temp4)
img1.show(title='lena_sap10_closing_then_opening')
img1=img1.convert("L")
img1.save('lena_sap10_closing_then_opening.jpg',format='JPEG')