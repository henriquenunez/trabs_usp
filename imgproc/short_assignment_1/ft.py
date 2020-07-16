"""
Henrique Hiram Libutti Núñez - 11275300

This code implements 2D Discrete Fourier Transform
"""

import numpy as np
import imageio

#Computes 2D DFT
def dft2d(matrix):
    n = matrix.shape[0]
    m = matrix.shape[1]

    #New matrix of the same dimensions as the original image.
    mat_dft = np.zeros(matrix.shape, dtype=np.complex64)

    """
    Assuming periodicity, we can compute for frequencies in the range of the
    measurement indexes.
    """
    x_vec = np.arange(n)

    for u in range(n):
        for v in range(m):
            for y in range(m):
                mat_dft[u, v] += np.sum(matrix[:, y]*\
                                    np.exp(-1j*(2*np.pi)*(u*x_vec/n + v*y/m)))

    return mat_dft/np.sqrt(n*m)

#Computes inverse 2D DFT (image)
def dft2d_inv(matrix):
    n = matrix.shape[0]
    m = matrix.shape[1]

    #New matrix of the same dimensions as the original image.
    inv_mat_dft = np.zeros(matrix.shape, dtype=np.complex64)

    u_vec = np.arange(n)

    for x in range(n):
        for y in range(m):
            for v in range(m):
                inv_mat_dft[x, y] += np.sum(matrix[:, v]*\
                                    np.exp(1j*(2*np.pi)*(x*u_vec/n + y*v/m)))
                                    #complex signal is changed
    return inv_mat_dft/np.sqrt(n*m)

def zero_if_less_than(mat, t):
    n = mat.shape[0]
    m = mat.shape[1]

    ret_mat = np.zeros(mat.shape, dtype=np.complex64)
    counter = 0

    for x in np.arange(n):
        for y in np.arange(m):
            if np.abs(mat[x, y]) < t:
                counter += 1
            else:
                ret_mat[x, y] += mat[x, y]

    return (ret_mat, counter)

if __name__ == "__main__":
    filename = input().rstrip()      #Image filename
    thresh = float(input().rstrip()) #Threshold
    output_format = "Threshold=%.4f\nFiltered Coefficients=%d\nOriginal Mean=%.2f\nNew Mean=%.2f"

    image = imageio.imread(filename)

    #Find fourier transformed version of image
    dft_image = dft2d(image)

    #Getting second largest
    sorted_values = np.sort(np.abs(dft_image.flat))
    scnd_larg = sorted_values[sorted_values.shape[0] - 2]

    #print(dft_image.shape)
    comp_thresh = scnd_larg*thresh

    filt_image, filt_coef = zero_if_less_than(dft_image, comp_thresh)

    orig_mean = np.abs(image).mean()
    new_mean = np.abs(dft2d_inv(filt_image)).mean()

    print(output_format % (comp_thresh, filt_coef, orig_mean, new_mean))

