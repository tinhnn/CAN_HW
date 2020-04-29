
# install "python-can" package
# sudo pip3 install python-can
import can

can_interface = 'can0'
#can_interface = 'can1'
bus = can.interface.Bus(can_interface, bustype='socketcan_native')
while True:
    message = bus.recv(1.0) # Timeout in seconds.
    if message is None:
            print('Timeout occurred, no message.')
    # send to PC via ethernet
    # TODO
    print(message)