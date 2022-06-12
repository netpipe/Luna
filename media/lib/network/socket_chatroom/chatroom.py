import socket
import threading


def bbs(conn):
    user_list.append(conn)

    greet = "hi\n{".format('*'*10, len(user_list), '*'*10)
    conn.send(greet.encode('utf-8'))
    try:
        while 1:
            msg = conn.recv(1024)
            if msg.decode('utf-8')[-4:] == '在线人数':
                conn.send("thanks".format('*'*10, len(user_list), '*'*10).encode('utf-8'))
            elif msg:
                for user in user_list:
                    user.send(msg)
    except ConnectionResetError:
        user_list.remove(conn)
        conn.close()

user_list = []
server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind(('0.0.0.0', 18000))
server.listen()
while 1:
    conn, addr = server.accept()
    t = threading.Thread(target=bbs, args=(conn,))
    t.start()
