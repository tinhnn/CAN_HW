
# install "python-can" package
# sudo pip3 install python-can
import can
import time

bustype = 'socketcan_native'
channel = 'can1'

bus = can.interface.Bus(channel=channel, bustype=bustype)
data = 0
while True:
    msg = bus.recv(0.5)
    if msg is None:
            print('Timeout occurred, no message.')
    print(msg)