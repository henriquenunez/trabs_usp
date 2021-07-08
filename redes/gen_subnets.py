# 4

counter = 0
subnet_size = 4
net_start = '193.100.50.'

for i in range(64):

    # Address range:
    print(net_start + '%-3d' % (counter) + ' ' + \
            net_start + '%-3d' % (counter+1) + ' a ' + \
            net_start + '%-3d' % (counter+subnet_size-2) + ' ' +\
            net_start + '%-3d' % (counter+subnet_size-1) + ' ' +\
            net_start + '%-3d' % (counter+1) + ' ' + \
            net_start + '%-3d' % (counter+1))

    counter += subnet_size

# 5

counter = 0
subnet_size = 16
net_start = '19.20.30.'

for i in range(16):

    # Address range:
    print(net_start + '%-3d' % (counter) + ' ' + \
            net_start + '%-3d' % (counter+1) + ' a ' + \
            net_start + '%-3d' % (counter+subnet_size-2) + ' ' +\
            net_start + '%-3d' % (counter+subnet_size-1) + ' ' +\
            net_start + '%-3d' % (counter+1) + ' ' + \
            net_start + '%-3d' % (counter+1))

    counter += subnet_size

## 6
#
#counter = 0
#subnet_size = 2048
#net_start = '129.12.'
#
## the subnet mast is 240 = 0b11111000
#
#for i in range(32):
#
#    # Address range:
#    line = ''
#
#    val = counter
#    upper = val >> 8
#    lower = val & 255
#
#    line += net_start + '%d.' % (upper) + '%-3d' % (lower) + ' '
# 
#    val = counter + 1
#    upper = val >> 8
#    lower = val & 255
#   
#    line += net_start + '%d.' % (upper) + '%-3d' % (lower) + ' a '
#
#    val = counter + subnet_size - 2
#    upper = val >> 8
#    lower = val & 255
#
#    line += net_start + '%d.' % (upper) + '%-3d' % (lower) + ' '
#
#    val = counter + subnet_size - 1
#    upper = val >> 8
#    lower = val & 255
#
#    line += net_start + '%d.' % (upper) + '%-3d' % (lower) + ' '
#
#    val = counter + 1
#    upper = val >> 8
#    lower = val & 255
#
#    line += net_start + '%d.' % (upper) + '%-3d' % (lower) + ' '
#
#    val = counter + 2
#    upper = val >> 8
#    lower = val & 255
#
#    line += net_start + '%d.' % (upper) + '%-3d' % (lower) + ' '
#
#    val = counter + 3
#    upper = val >> 8
#    lower = val & 255
#
#    line += net_start + '%d.' % (upper) + '%-3d' % (lower) + ' '
#
#    print(line)
#
#    counter += subnet_size
