import socket
import select
import errno
import sys
import threading
import time

client_socket = None
HEADER_LENGTH = 10


def background():
    while True:
        time.sleep(3)
        try:
            username_header = client_socket.recv(HEADER_LENGTH)
            if not len(username_header):
                print('Connection closed by the server')
                sys.exit()
            username_length = int(username_header.decode('utf-8').strip())
            username = client_socket.recv(username_length).decode('utf-8')
            message_header = client_socket.recv(HEADER_LENGTH)
            message_length = int(message_header.decode('utf-8').strip())
            message = client_socket.recv(message_length).decode('utf-8')
            print('\n')
            print(f'{username} > {message}')
        except IOError as e:
            if e.errno != errno.EAGAIN and e.errno != errno.EWOULDBLOCK:
                print('Reading error: {}'.format(str(e)))
                sys.exit()
            continue
        except Exception as e:
            print('Reading error: '.format(str(e)))
            sys.exit()


def client_start(room_ip_port, user):
    threading1 = threading.Thread(target=background)
    threading1.daemon = True
    threading1.start()
    HEADER_LENGTH = 10
    server_details = room_ip_port.split('/')
    IP = server_details[0]
    PORT = int(server_details[1])
    my_username = user
    global client_socket
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client_socket.connect((IP, PORT))
    client_socket.setblocking(False)
    username = my_username.encode('utf-8')
    username_header = f"{len(username):<{HEADER_LENGTH}}".encode('utf-8')
    client_socket.send(username_header + username)
    while True:
        message = input(f'{my_username} > ')
        if message:
            message = message.encode('utf-8')
            message_header = f"{len(message):<{HEADER_LENGTH}}".encode('utf-8')
            client_socket.send(message_header + message)
