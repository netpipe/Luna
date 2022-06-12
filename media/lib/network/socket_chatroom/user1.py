import socket
import threading
import time


def send_msg():
    while 1:
        msg = input()
        client.send((name + '：' + msg).encode('utf-8'))


def recv_msg():
    while 1:
        msg = client.recv(1024)
        if msg:
            try:
                print(msg.decode('utf-8'))
                time.sleep(1)
            except UnicodeDecodeError:
                pass

name = input('test：')
client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client.connect(('13.4.47.1', 1443))
sendmsg_thread = threading.Thread(target=send_msg)
recvmsg_thread = threading.Thread(target=recv_msg)
sendmsg_thread.start()
recvmsg_thread.start()

