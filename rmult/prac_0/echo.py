# Echo end to end application
# Command line arguments: p1 p2
# p1 is the port where the application will listen
# p2 is the port where the application will send messages to

import socket
import argparse
import sys
import threading

IP_ADDRESS = '127.0.0.1'
PORT = '42069'

address = ''

def receive_message():

    while True:
        # TODO error checking
        data, addr = r_sck.recvfrom(2048)
        print('Received: ' + data.decode('utf-8'))
        #print('Insert message: ')

def send_message():
    
    while True:
        # TODO error checking
        text = input('Insert message: ')

        # Send message here
        s_sck.sendto(text.encode('utf-8'), (IP_ADDRESS, s_port))

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

