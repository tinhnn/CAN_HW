
# install "python-can" package
# sudo pip3 install python-can
import os
import socket
from threading import *
import can
import time
import struct

# Init CAN1
os.system("sudo ip link set can1 up type can bitrate 1000000")

serversocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
host = "192.168.10.116"
port = 8000
serversocket.bind((host, port))

bustype = 'socketcan_native'
channel = 'can1'
bus = can.interface.Bus(channel=channel, bustype=bustype)
serversocket.listen(5)


class client(Thread):
    def __init__(self, socket, address):
        Thread.__init__(self)
        self.sock = socket
        self.addr = address
        self.start()

    def run(self):
        while 1:
            msg = bus.recv(0.5)
            self.sock.send(struct.pack('!d', msg.timestamp))
            self.sock.send(struct.pack('!i', msg.arbitration_id))
            self.sock.send(struct.pack('!i', msg.dlc))
            self.sock.send(msg.data)
            #self.sock.send(b'aasdsdsad')


while True:
    clientsocket, address = serversocket.accept()
    client(clientsocket, address)
