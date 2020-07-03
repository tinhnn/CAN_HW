
# install "python-can" package
# sudo pip3 install python-can
import os
import socket
import can
import time

# Init CAN0
os.system("sudo ip link set can0 up type can bitrate 1000000   dbitrate 8000000 restart-ms 1000 berr-reporting on fd on")
os.system("sudo ifconfig can0 txqueuelen 65536")

bustype = 'socketcan_native'
channel = 'can0'

bus = can.interface.Bus(channel=channel, bustype=bustype)
cnt = 0
while True:
    msg = can.Message(arbitration_id=0xA5A5A5A5, data=[0, 0, 0, 0, 0, 0, 0, cnt], extended_id=False)
    bus.send(msg, timeout=0.1)
    cnt = cnt+1
    if cnt == 256:
        cnt = 0
    time.sleep(0.1)