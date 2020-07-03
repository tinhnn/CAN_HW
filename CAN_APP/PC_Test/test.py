import socket

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
host ="192.168.10.116"
port =8000
s.connect((host,port))

def ts(str):
   data = ''
   data = s.recv(128)
   print (data)

while 2:
   ts(s)

s.close ()