import socket
import select
from collections import defaultdict
HEADER_LENGTH = 10
IP = "127.0.0.1"
PORT = 8081
server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
server_socket.bind((IP, PORT))
server_socket.listen()
sockets_list = [server_socket]
clients = {}
groups = defaultdict(list)
print(f'Listening for connections on {IP}:{PORT}...')


def get_server_messages(client_socket):
    try:
        message_header = client_socket.recv(HEADER_LENGTH)
        if not len(message_header):
            return False
        message_length = int(message_header.decode('utf-8').strip())
        return {'header': message_header, 'data': client_socket.recv(message_length)}
    except:
        return False


while True:
    read_sockets, _, exception_sockets = select.select(sockets_list, [], sockets_list)
    for notified_socket in read_sockets:
        if notified_socket == server_socket:
            client_socket, client_address = server_socket.accept()
            user = get_server_messages(client_socket)
            if user is False:
                continue
            data = user['data'].decode('UTF-8')
            list_of_split = data.split('#')
            group_name = list_of_split[1]
            data = list_of_split[0]
            sockets_list.append(client_socket)
            groups[group_name].append(client_socket)
            clients[client_socket] = user
            print('New connection from {}:{}, username: {}, for group: {}'.format(*client_address,
                                                                            data,group_name))
        else:
            message = get_server_messages(notified_socket)
            if message is False:
                sockets_list.remove(notified_socket)
                del clients[notified_socket]
                continue
            user = clients[notified_socket]
            data = user["data"].decode("utf-8")
            list_of_split = data.split('#')
            group_name = list_of_split[1]
            data = list_of_split[0]
            list_of_clients =groups[group_name]
            for client_socket in list_of_clients:
                if client_socket != notified_socket:
                    client_socket.send(user['header'] + user['data'] + message['header'] + message['data'])
    for notified_socket in exception_sockets:
        sockets_list.remove(notified_socket)
        del clients[notified_socket]
