"""
Henrique Hiram Libutti Núñez - 11275300
color morphological operations
"""

import imageio
import numpy as np
import skimage.morphology as morphee
import matplotlib.colors as rainbow

#In practice this is the euclidean distance between the values
def rmse(a, b):
	n, m = a.shape[0:2]
	err = np.subtract(a.astype("float64"), b.astype("float64"))
	fact = np.divide(np.sum(np.square(err)), n*m)
	return np.sqrt(fact)


#Normalize image
def _normalizer(val, max_val, min_val, new_max):
    return new_max*(val-min_val)/(max_val-min_val)


def normalizer(image, max_val):
    img_max = image.max()
    img_min = image.min()
    vector_normalizer = np.vectorize(_normalizer)
    norm_image = vector_normalizer(image, img_max, img_min, max_val)
    return norm_image


def morph_opening(image, kernel_size):
	sweden = morphee.disk(kernel_size)
	eroded = morphee.erosion(image, sweden).astype("uint8")
	opened = morphee.dilation(eroded, sweden).astype("uint8")
	return opened

def morph_closing(image, kernel_size):
	sweden = morphee.disk(kernel_size)
	dilated = morphee.dilation(image, sweden).astype("uint8")
	closed = morphee.erosion(dilated, sweden).astype("uint8")
	return closed

def morph_gradient(image, kernel_size):
	sweden = morphee.disk(kernel_size) #a.k.a. structuring element, or .se
	eroded = morphee.erosion(image, sweden).astype("uint8")
	dilated = morphee.dilation(image, sweden).astype("uint8")
	gradient = dilated - eroded
	return gradient

#Perform morphological opening on each rgb channel
def option_one(image, kernel_size):
	ret_image = np.array(image, copy=True)
	ret_image[:,:,0] = morph_opening(ret_image[:,:,0], kernel_size) #R channel
	ret_image[:,:,1] = morph_opening(ret_image[:,:,1], kernel_size) #G channel
	ret_image[:,:,2] = morph_opening(ret_image[:,:,2], kernel_size) #B channel
	return ret_image


def option_two(image, kernel_size):
	ret_image = np.array(image, copy=True)
	hsv_image = rainbow.rgb_to_hsv(image)
	norm_hue = normalizer(hsv_image[:, :, 0], 255)
	hue_grad = morph_gradient(norm_hue, kernel_size)
	norm_hue_grad = normalizer(hue_grad, 255)

	ret_image[:,:,0] = norm_hue_grad
	ret_image[:,:,1] = morph_opening(norm_hue, kernel_size)
	ret_image[:,:,2] = morph_closing(norm_hue, kernel_size)

	return ret_image


def option_three(image, kernel_size):
	step_one = option_one(image, kernel_size*2)
	step_two = option_two(step_one, kernel_size)
	return step_two


if __name__ == '__main__':
	filename = input().rstrip()
	k = int(input().rstrip())
	option = int(input().rstrip())

	orig_image = imageio.imread(filename)

	menu = [option_one, option_two, option_three]
	mod_image = menu[option-1](orig_image, k)

	print("%.4f" % rmse(orig_image, mod_image))