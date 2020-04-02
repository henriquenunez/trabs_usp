"""
Name:       Henrique Hiram Libutti Núñez
Course :    SCC0251
NUSP:       11275300
Semester:   2020.1
Title:      Assignment1: Image Intensity Transformation
"""

##CODE BY HIRAM 31/03/2020

import numpy as npy
import imageio as iio
import math

#Just a class for unmatching matrices
class ImageSizeError(Exception):
    pass

#Computes root squared error
def rs_error(mod_image, ori_image):
    #error checking
    if mod_image.shape[0] != ori_image.shape[0] and\
       mod_image.shape[1] != ori_image.shape[1]:
        raise ImageSizeError

    iter_mod = npy.nditer(mod_image, flags=['multi_index'])
    iter_ori = npy.nditer(ori_image, flags=['multi_index'])
    """
    i did not know how to apply functional programming here, so im using
    imperative style
    """
    s = 0 #accumulator

    #checks wheter we have reached end of the matrixes
    while not iter_mod.finished and not iter_ori.finished:
        m = iter_mod[0] #access element 0 (the only one) pointed by iterator
        r = iter_ori[0] #access element 0 (the only one) pointed by iterator
        s += math.pow(float(m) - float(r), 2) #error squared
        iter_mod.iternext()
        iter_ori.iternext()

    return math.sqrt(s) #square root of the error sum

"""
Image enhancement functions
functional-style programming was chosen here since we need to apply the same
function to an iterable object (mapping)
"""

def invert_image(image):
    #applies image inversion
    func = npy.vectorize(lambda i : 255 - i)
    return func(image)

def constrast_modulation(image, c, d):
    a = float(npy.amin(image))  #minimum from image
    b = float(npy.amax(image))  #maximum from image
    func = npy.vectorize(lambda i : (i - a) * (d - c)/(b - a) + c)
    return func(image)

def logarithmic_function(image):
    r = int(npy.amax(image))    #maximum from image
    func = npy.vectorize(lambda i : 255 * math.log2(1 + i)/math.log2(1 + r))
    return func(image)

def gamma_adjustment(image, w, lamb):
    func = npy.vectorize(lambda i : w * math.pow(i, lamb))
    return func(image)

if __name__ == '__main__':

    fname = input().rstrip()    #filename input
    ttran = int(input())        #transformation type
    osave = int(input())        #save option

    image = iio.imread(fname)

    if ttran == 1:
        #Inversion
        ret_image = invert_image(image)
    elif ttran == 2:
        #Constrast modulation
        cpara = int(input()) #c parmeter
        dpara = int(input()) #lambda parameter
        ret_image = constrast_modulation(image, cpara, dpara)
    elif ttran == 3:
        #Logarithmic funcion
        ret_image = logarithmic_function(image)
    elif ttran == 4:
        #Gamma adjustment
        wpara = int(input())   #w parameter
        lpara = float(input()) #lambda parameter
        ret_image = gamma_adjustment(image, wpara, lpara)
    if osave is not 0:
        #iio.imwrite("proc-" + fname, ret_image)
        iio.imwrite("output_img.png", ret_image)

    #Output RSE
    comp_err = rs_error(image, ret_image)
    print("{:.4f}".format(comp_err))

