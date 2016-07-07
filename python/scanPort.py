# coding: utf-8

import socket


ip = "127.0.0.1"
enablePort = []
print "start"
for port in range(65535):
    clinet = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    clinet.settimeout(3)
    try:
        clinet.connect((ip, port))
    except Exception, e:
        print "connect %d failed!" % (port)
    else:
        print "connect %d success!" % (port)
        clinet.close()
        enablePort.append(port)

print "end"
print enablePort
