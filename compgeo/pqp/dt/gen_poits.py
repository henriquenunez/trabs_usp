#!/usr/bin/python3

#import math
import random

num = int(input("type number of points to generate"))

output = open("in." + str(num), "w")

output.write(str(num)+"\n")

for i in range (0, num):
    X = random.randint(-100, 100)
    Y = random.randint(-100, 100)
    output.write(str(X) + " " + str(Y) + "\n")

output.close()
#end

