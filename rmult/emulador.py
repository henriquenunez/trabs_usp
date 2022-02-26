# Proxy application 

import socket
import argparse
import sys
import threading
import time
import struct
import random

address = ''

seq_number = 0

my_time = 0
ssrc = 0

def receive_messages(send_message):

    while True:
        data, addr = r_sck.recvfrom(2048)
        print('Received messages from {}'.format(addr))
        
        send_message(data, (ipdst, portdst))
        #threading.Thread(send_message, data).start()
        #rtp = unpack_rtp(data)
        #print('Sequence number: {} Timestamp: {} Message: {}.'.format(rtp[0], rtp[1], rtp[2]))

        #r_sck.sendto(b"OK", addr)
        #print(f"Puerto UDP de recepcion: {PORTRCV}")
        #print('Insert message: ')

def message_sender_factory(should_thread, normal_dist):

    print('Message sender factory')

    def message_sender(data, addr):

        #tsend = time.time()
        #data = make_rtp_packet(text)
     
        #if should_thread:
            #threading.Thread(s_sck.sendto, (data, addr)) 
        def send_message():

            if random.random() < loss_ratio:
                print('Packet lost!')
                return

            if normal_dist:
                mu = (min_delay + max_delay) / 2
                sigma = (mu - min_delay) / 3

                sleep_time = random.normalvariate(mu, sigma) / 1000
            else:
                sleep_time = random.uniform(min_delay / 1000, max_delay / 1000)
            print('Sleeping for {}s'.format(sleep_time))
            time.sleep(sleep_time)
            print('Sending message to {}'.format(addr)) 
            s_sck.sendto(data, addr)
    
            # Confirm arrival
            #data, addr = s_sck.recvfrom(2048)
            #treceive = time.time() - tsend
    
            #print('RTT: %f      ' % treceive, end = '')
            #if data == b"OK":
            #    print('Se ha recibido')
    
            #time.sleep(2)

        if should_thread:
            threading.Thread(target=send_message).start()
        else:
            send_message()

    return message_sender

def connect(rec_port):
    global r_sck
    global s_sck

    print('Creaing receive socket on port %d' % rec_port)
    r_sck = socket.socket(socket.AF_INET,
                          socket.SOCK_DGRAM)
    r_sck.bind(('127.0.0.1', rec_port))

    print('Creating send socket')
    s_sck = socket.socket(socket.AF_INET,
                          socket.SOCK_DGRAM)

def main():
    global ipdst 
    global portdst
    global portrcv
    global loss_ratio
    global max_delay
    global min_delay

    parser = argparse.ArgumentParser(description='Proxy that slows down your network.')
    parser.add_argument('--thread', action='store_true',
                        help='Whether to use threading or not')
    parser.add_argument('--normal', action='store_true',
                        help='Whether to use uniform or gaussian packet delay.')
    parser.add_argument('ipdst', metavar='IP',
                        help='IP Address the program will proxy to')
    parser.add_argument('portdst', type=int,
                        help='Port to which the program will proxy to')
    parser.add_argument('portrcv', type=int,
                        help='Port in which the program will listen')
    parser.add_argument('loss_ratio', type=float,
                        help='Ratio of packet loss between 0 and 1')
    parser.add_argument('min_delay', type=int,
                        help='Minimum delay imposed by proxy (ms).') # When --normal will be forced to 0.
    parser.add_argument('max_delay', type=int,
                        help='Maximum delay imposed by proxy (ms)')

    args = parser.parse_args()

    ipdst = args.ipdst
    portdst = args.portdst
    max_delay = args.max_delay
    min_delay = args.min_delay
    loss_ratio = args.loss_ratio

    connect(args.portrcv)
    receive_messages(message_sender_factory(args.thread, args.normal))

if __name__ == '__main__':
    main()

