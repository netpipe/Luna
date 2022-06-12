import socket
import threading


class Kangaroo:
    def __init__(self):
        self.__localhost = "127.0.0.1"
        self.__message = ""
        self.__has_new_message = False

    def send(self, port: int, message: str) -> None:
        """
        Send message to given port
        :param port: Port to send the message
        :param message: Message to be sent
        :return: None
        """
        socket_conn = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        socket_conn.connect((self.__localhost, port))
        socket_conn.sendall(bytes(message, "utf-8"))
        socket_conn.close()

    def listen(self, port: int):
        """
        Listen to a given port
        :param port: Port to send the message
        :return: Kangaroo object
        """
        socket_conn = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        socket_conn.bind((self.__localhost, port))
        socket_conn.listen(1)

        self.__listening_thread = threading.Thread(
            target=self.__listening, args=(socket_conn,)
        )
        self.__listening_thread.setDaemon(True)
        self.__listening_thread.start()

        return self

    def __listening(self, socket_conn: socket.socket) -> None:
        """
        Infinite loop to listen to a port
        :param socket_conn: Socket to be listen
        :return: None
        """
        while True:
            conn, _ = socket_conn.accept()
            self.__message = conn.recv(1024).decode("UTF-8")
            self.__has_new_message = True

    def has_new_message(self) -> bool:
        """
        Returns if there's a new message
        :return: True if there's a new message
        """
        return self.__has_new_message

    def get_message(self) -> str:
        """
        Returns the last message receive
        :return: Last message
        """
        if self.__has_new_message:
            self.__has_new_message = False
            return self.__message
        else:
            return ""
