import socket
import struct
import threading
import platform

msgDecoded = b""
filenameDecoded = ""

def send(filepath:str, socket:socket.socket):
    try:
        fObj = open(filepath, "rb")
    except Exception as err:
        print(err)
        return

    f = fObj.read()
    bLenFilecontents = struct.pack("!I", len(f))

    if platform.system() == "Windows":
        filename = filepath.split("\\")
    else:
        filename = filepath.split("/")

    bLenFilename = struct.pack("!I", len(filename[0]))

    bMessage = bLenFilename + filename[len(filename) - 1].encode("utf8") + bLenFilecontents + f
    socket.send(bMessage)

def receive(socket:socket.socket) -> tuple:
    def worker(socket):
        global msgDecoded
        global filenameDecoded

        bMessage = socket.recv(1024)

        filenameLen = struct.unpack("!I", bMessage[:4])[0]
        filenameDecoded = bMessage[4:4 + filenameLen]
        filenameDecoded = filenameDecoded.decode("utf8")
        msgLen = struct.unpack("!I", bMessage[4 + filenameLen:4 + filenameLen + 4])[0]
        msgDecoded = bMessage[4 + filenameLen + 4:4 + filenameLen + 4 + msgLen]

        while True:
            if len(msgDecoded) < msgLen:
                bMessage = socket.recv(1024)
                msgDecoded += bMessage
                print(str(len(msgDecoded)) + " / " + str(msgLen) + " kb")
            else:
                break

    WorkerThread = threading.Thread(target=worker, kwargs={"socket":socket})
    WorkerThread.start()
    return msgDecoded, filenameDecoded