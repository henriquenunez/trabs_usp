# Echo end to end application
# Command line arguments: p1 p2
# p1 is the port where the application will listen
# p2 is the port where the application will send messages to

import socket
import argparse
import sys
import threading
import time
import struct
import random

IP_ADDRESS = '127.0.0.1'
PORT = '42069'

address = ''

seq_number = 0

"""
    0                   1                   2                   3
    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |V=2|P|X|  CC   |M|     PT      |       sequence number         |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |                           timestamp                           |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |           synchronization source (SSRC) identifier            |
   +=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
   |            contributing source (CSRC) identifiers             |
   |                             ....                              |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
"""

my_time = 0
ssrc = 0

def make_rtp_packet(text):
    global my_time
    global seq_number 

    b = []
    #timestamp = int(time.time() * 10)
    timestamp = my_time
    my_time += random.randint(0, 9) 

    first_octet = 0b1000000000000000
    b[0:2] = struct.pack('!H', first_octet)
    b[2:4] = struct.pack('!H', seq_number)
    b[4:8] = struct.pack('!I', timestamp)
    b[8:12] = struct.pack('!I', ssrc)

    seq_number += 1

    return bytearray(b) + text.encode('utf-8')

# Extract RTP info
def unpack_rtp(data):
    rec_seq_number = struct.unpack('!H', data[2:4])[0]
    rec_timestamp = struct.unpack('!I', data[4:8])[0]
    text = str(data[12:])

    return (rec_seq_number, rec_timestamp, text)

def receive_message():

    while True:
        # TODO error checking
        data, addr = r_sck.recvfrom(2048)
        #print(data)
        rtp = unpack_rtp(data)
        #print(rtp)
        print('Sequence number: {} Timestamp: {} Message: {}.'.format(rtp[0], rtp[1], rtp[2]))

        r_sck.sendto(b"OK", addr)
        #print('Insert message: ')

def send_message():

    while True:
        # TODO error checking
        text = input("Insert message: ")

        tsend = time.time()

        data = make_rtp_packet(text)
        s_sck.sendto(data, (IP_ADDRESS, s_port))

        # Confirm arrival
        data, addr = s_sck.recvfrom(2048)
        treceive = time.time() - tsend

        print('RTT: %f      ' % treceive, end = '')
        if data == b"OK":
            print('Se ha recibido')

        #time.sleep(2)

def connect(send_port, rec_port):
    global r_sck
    global s_sck

    r_sck = socket.socket(socket.AF_INET,
                          socket.SOCK_DGRAM)
    r_sck.bind((IP_ADDRESS, rec_port))

    s_sck = socket.socket(socket.AF_INET,
                          socket.SOCK_DGRAM)
    #s_sck.bind((IP_ADDRESS, send_port))

def main():
    global s_port
    global r_port

    if len(sys.argv) < 3:
        print('Not enough args!')
        return

    r_port = int(sys.argv[1])
    s_port = int(sys.argv[2])

    print('Connecting to port ' + sys.argv[2])
    connect(s_port, r_port)
    threading.Thread(target=send_message).start()
    threading.Thread(target=receive_message).start()


if __name__ == '__main__':
    main()

