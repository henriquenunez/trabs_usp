# Proxy application 

import socket
import argparse
import sys
import threading
import time
import struct
import random



def receive_messages(send_message):
    while True:
        data, addr = r_sck.recvfrom(4096)
        print('Received messages from {}'.format(addr))

        send_message(data, (ipdst, portdst))


def message_sender_factory(should_thread, normal_dist):
    print('Message sender factory')

    def message_sender(data, addr):

        def send_message():

            if random.random() < loss_ratio:
                print('Packet lost!')
                return

            if normal_dist:
                mu = (min_delay + max_delay) / 2
                sigma = (mu - min_delay) / 3

                sleep_time = random.normalvariate(mu, sigma) / 1000
                while sleep_time < 0.0:
                    sleep_time = random.normalvariate(mu, sigma) / 1000
            else:
                sleep_time = random.uniform(min_delay / 1000, max_delay / 1000)
            print('Sleeping for {}s'.format(sleep_time))
            time.sleep(sleep_time)
            print('Sending message to {}'.format(addr))
            s_sck.sendto(data, addr)

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
    r_sck.setsockopt(socket.SOL_SOCKET, socket.SO_RCVBUF, 4096)
    r_sck.bind((iprcv, rec_port))

    print('Creating send socket')
    s_sck = socket.socket(socket.AF_INET,
                          socket.SOCK_DGRAM)


def main():
    global ipdst
    global portdst
    global iprcv
    global portrcv
    global loss_ratio
    global max_delay
    global min_delay

    parser = argparse.ArgumentParser(description='Proxy that slows down your network.')
    parser.add_argument('--thread', action='store_true',
                        help='Whether to use threading or not')
    parser.add_argument('--normal', action='store_true',
                        help='Whether to use uniform or gaussian packet delay.')
    parser.add_argument('ipdst', metavar='IP_dst',
                        help='IP Address the program will proxy to')
    parser.add_argument('portdst', type=int,
                        help='Port to which the program will proxy to')
    parser.add_argument('iprcv', metavar='IP_rcv',
                        help='IP Address the program will listen')
    parser.add_argument('portrcv', type=int,
                        help='Port in which the program will listen')
    parser.add_argument('loss_ratio', type=float,
                        help='Ratio of packet loss between 0 and 1')
    parser.add_argument('min_delay', type=int,
                        help='Minimum delay imposed by proxy (ms).')
    parser.add_argument('max_delay', type=int,
                        help='Maximum delay imposed by proxy (ms)')

    args = parser.parse_args()

    ipdst = args.ipdst
    portdst = args.portdst
    iprcv = args.iprcv
    max_delay = args.max_delay
    min_delay = args.min_delay
    loss_ratio = args.loss_ratio

    connect(args.portrcv)
    receive_messages(message_sender_factory(args.thread, args.normal))


if __name__ == '__main__':
    main()
