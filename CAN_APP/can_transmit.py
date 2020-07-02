
# install "python-can" package
# sudo pip3 install python-can
import can
import time

bustype = 'socketcan_native'
channel = 'can0'

bus = can.interface.Bus(channel=channel, bustype=bustype)
data = 0
while True:
    msg = can.Message(arbitration_id=0xA5A5A5A5, data=[0, 0, 0, 0, 0, 0, 0, data], extended_id=False)
    bus.send(msg, timeout=0.1)
    data = data+1
    if data == 256:
        data = 0
    time.sleep(0.1)