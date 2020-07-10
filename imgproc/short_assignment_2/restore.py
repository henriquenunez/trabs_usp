"""
Henrique Hiram Libutti Núñez - 11275300
Image restoration
"""

import imageio
import numpy as np
from numpy.fft import *

#Gaussian filter
def gaussian_filter(k=3, sigma=1.0):
    arx = np.arange((-k // 2) + 1.0, (k // 2) + 1.0)
    x, y = np.meshgrid(arx, arx)
    filt = np.exp( -(1/2)*(np.square(x) + np.square(y))/np.square(sigma) )
    return filt/np.sum(filt)


def denoiser(image, conv_filter):
    #Compute FT of image.
    G = fft2(image)

    # Noise padding
    a = int(image.shape[0]//2 - conv_filter.shape[0]//2)
    padded_filter = np.pad(conv_filter, (a,a-1), 'constant', constant_values=(0))

    #Compute FT of filter.
    H = fftn(padded_filter)
    denoised = np.multiply(G, H)
    return ifft2(denoised).real


def _normalizer(val, max_val, min_val, new_max):
    return new_max*(val-min_val)/(max_val-min_val)


def normalizer(image, max_val):
    img_max = image.max()
    img_min = image.min()
    vector_normalizer = np.vectorize(_normalizer)
    norm_image = vector_normalizer(image, img_max, img_min, max_val)
    return norm_image


def cls_filter(image, deg_func, reg):
    #Image Ft
    G = fft2(image)

    #Zero pad degradation function
    a_deg = int(image.shape[0]//2 - deg_func.shape[0]//2)
    deg_paddded = np.pad(deg_func, (a_deg,a_deg-1), 'constant', constant_values=(0))

    #Degradation function Ft
    H = fft2(deg_paddded)
    H_star = np.conjugate(H)

    #Zero pad and Ft laplacian
    laplacian = np.array(  [[0, -1, 0],\
                            [-1, 4, -1],\
                            [0, -1, 0]])
    a_lap = int(image.shape[0]//2 - laplacian.shape[0]//2)
    lap_padded = np.pad(laplacian, (a_lap,a_lap-1), 'constant', constant_values=(0))
    P = fft2(lap_padded)

    return ifft2((H_star/(np.power(H, 2) + reg*np.power(P, 2)))*G).real

if __name__ == "__main__":
    filename = input().rstrip()
    k = int(input().rstrip())
    sigma = float(input().rstrip())
    gamma = float(input().rstrip())

    orig_image = imageio.imread(filename).astype("float64")
    maxg = orig_image.max()

    blur_filter = gaussian_filter(k, sigma)

    denoised_image = denoiser(orig_image, blur_filter)
    maxd = denoised_image.max()
    denoised_image = normalizer(denoised_image, maxg).astype("uint8")

    restored_img = cls_filter(denoised_image, blur_filter, gamma)
    restored_img = normalizer(restored_img, maxd)
    stddev = np.std(restored_img)
    print("%.1f" % stddev)
