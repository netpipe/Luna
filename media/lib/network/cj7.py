import socket

def sendPacketUDP(ip, port, data, showSent):
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    sock.sendto(data, (ip, port))
    if (showSent == True):
	print('Packet sent')
    return True

def sendPacketTCP(ip, port, data, showSent):
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect((ip, port))
    s.sendall(data)
    data = s.recv(1024)
    s.close()
    if (showSent == True):
        print('Packet sent')
    return data
