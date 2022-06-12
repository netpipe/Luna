import socket
import argparse
import ssl
import sys

# define configs
DEFAULT_HOST = "localhost"
DEFAULT_PORT = 80
DEFAULT_MODE = "c"
DEFAULT_BUFFERSIZE = 4092
DEFAULT_VERBOSITY = False

# define reusable methods
def communicate(sock, bufferSize, verbose):
    action = str(input("ACTION: (s)end or (r)eceive message or (e)xit program? (s/r/e): "))
    if(action == "s"):
        message = str(input("MESSAGE (default = newline): "))
        if(message == ""):
            if(verbose):
                print("SENDING NEWLINE")
            sock.sendall("\r\n".encode())
        else:
            if(verbose):
                print("SENDING MESSAGE: " + message)
            sock.sendall(message.encode())
        if(verbose):
            print("MESSAGE SENT")
    elif(action == "r"):
        if(verbose):
            print("WAITING FOR MESSAGE...")
        message = sock.recv(bufferSize).decode()
        if(verbose):
            print("RECEIVED MESSAGE START")
        print(message)
        if(verbose):
            print("RECEIVED MESSAGE END")
    elif(action == "e"):
        if(verbose):
            print("CLOSING SOCKET...")
        sock.close()
        if(verbose):
            print("SOCKET CLOSED")
        exit()

# ambil dari command line arguments
argParser = argparse.ArgumentParser()
argParser.add_argument("-a", "--host", help="Hostname (default: "+str(DEFAULT_HOST)+")")
argParser.add_argument("-p", "--port", help="Port number (default: "+str(DEFAULT_PORT)+")", type=int)
argParser.add_argument("-b", "--buffer", help="Buffer size (default: "+str(DEFAULT_BUFFERSIZE)+")", type=int) # untuk argument yang harus int
argParser.add_argument("-s", "--server", help="Server mode", action="store_true")
argParser.add_argument("-c", "--client", help="Client mode (default)", action="store_true")
argParser.add_argument("-i", "--interactive", help="Interactive argument input mode. If this flag is specified, then program will ask for missing arguments, otherwise it will just assume missing arguments with default values. If no argument provided, then program will assume interactive mode.", action="store_true") # untuk flag saja
argParser.add_argument("--verbose", help="Verbose output mode. Use this option for debugging", action="store_true") # untuk flag saja

# command line arguments khusus SSL
argParser.add_argument("--ssl", help="Use SSL/TLS", action="store_true") # untuk flag saja
argParser.add_argument("--ssl_server_certificate", help="path to SSL/TLS certificate file (only needed when using SSL/TLS, mode server)")
argParser.add_argument("--ssl_server_privatekey", help="path to SSL/TLS private key file (only needed when using SSL/TLS, mode server)")
argParser.add_argument("--ssl_client_ca", help="path to CA certificate file (only needed when using SSL/TLS, mode client)")

args = argParser.parse_args()

if len(sys.argv) <= 1:
    print("No flags passed, assumed interactive mode")
    argParser.print_help()
    args.interactive = True

sslFlag = False
if(args.interactive):
    host = None
    port = None
    bufferSize = None
    mode = None
    verbose = None
    ssl_server_certificate = None
    ssl_server_privatekey = None
    ssl_client_ca = None
else:
    host = DEFAULT_HOST
    port = DEFAULT_PORT
    bufferSize = DEFAULT_BUFFERSIZE
    mode = DEFAULT_MODE
    verbose = DEFAULT_VERBOSITY
if(args.host):
    host = args.host
if(args.port):
    port = args.port
if(args.buffer):
    bufferSize = args.buffer
if(args.server and args.client):
    print("Mode cannot be both client and server!")
    exit()
elif(args.server):
    mode = "s"
elif(args.client):
    mode = "c"
if(args.verbose):
    verbose = True
    print("RUNNING IN VERBOSE MODE")
if(args.ssl):
    sslFlag = True
    if(mode == "s"):
        ssl_server_certificate = args.ssl_server_certificate
        ssl_server_privatekey = args.ssl_server_privatekey
    elif(mode == "c"):
        ssl_client_ca = args.ssl_client_ca


try:

    # terima input
    if(host == None):
        host = str(input("HOST (default = "+DEFAULT_HOST+"): "))
        if(host == ""):
            host = DEFAULT_HOST
    if(port == None):
        port = str(input("PORT (default = "+str(DEFAULT_PORT)+"): "))
        if(port == ""):
            port = DEFAULT_PORT
        port = int(port)
    if(bufferSize == None):
        bufferSize = str(input("BUFFER SIZE (default = "+str(DEFAULT_BUFFERSIZE)+"): "))
        if(bufferSize == ""):
            bufferSize = DEFAULT_BUFFERSIZE
        bufferSize = int(bufferSize)
    if(mode == None):
        mode = str(input("MODE (c)lient or (s)erver (default = "+DEFAULT_MODE+"): "))
        if(mode == ""):
            mode = DEFAULT_MODE




    # mulai jalankan
    ctx = None
    if(sslFlag and mode == "s"):
        if(verbose):
            print("SETTING UP SSL CONTEXT TLS SERVER...")
        ctx = ssl.SSLContext(ssl.PROTOCOL_TLS_SERVER)
        if(verbose):
            print("FINISHED SETTING SSL CONTEXT")
        if(verbose):
            print("SETTING UP SSL CONTEXT CERTIFICATE CHAIN...")
        ctx.load_cert_chain(ssl_server_certificate, ssl_server_privatekey)
        if(verbose):
            print("FINISHED SETTING SSL CONTEXT CERTIFICATE CHAIN")
    elif(sslFlag and mode == "c"):
        if(verbose):
            print("SETTING UP SSL CONTEXT TLS CLIENT...")
        ctx = ssl.SSLContext(ssl.PROTOCOL_TLS_CLIENT)
        if(verbose):
            print("FINISHED SETTING SSL CONTEXT")
        if(verbose):
            print("SETTING UP SSL CONTEXT LOAD CA CERTIFICATE...")
        ctx.load_verify_locations(ssl_client_ca)
        if(verbose):
            print("FINISHED SETTING SSL CONTEXT LOAD CA CERTIFICATE")

    if(verbose):
        print("SETTING UP SOCKET...")
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    if(verbose):
        print("FINISHED SETTING SOCKET")


    if(sslFlag and mode == "c"):
        if(verbose):
            print("WRAPPING CLIENT SOCKET WITH SSL...")
        sock = ctx.wrap_socket(sock, server_hostname=host)
        if(verbose):
            print("FINISHED WRAPPING CLIENT SOCKET WITH SSL")

    if(mode == "c"):
        if(verbose):
            print("CONNECTING...")
        sock.connect((host, port))
        if(verbose):
            print("CONNECTED!")

        while True:
            communicate(sock, bufferSize, verbose)
    elif(mode == "s"):
        if(verbose):
            print("BINDING SOCKET...")
        sock.bind((host, port))
        if(verbose):
            print("SOCKET BINDED")
            print("SETTING UP LISTENER...")
        sock.listen(1)
        if(verbose):
            print("FINISHED SETTING LISTENER")
            print("WATING FOR CLIENT TO CONNECT...")
        sockClient, addr = sock.accept()
        if(verbose):
            print("CLIENT CONNECTED! ADDRESS: ", addr)

        if(sslFlag):
            if(verbose):
                print("WRAPPING CLIENT SOCKET WITH SSL...")
            sockClient = ctx.wrap_socket(sockClient, server_side=True)
            if(verbose):
                print("FINISHED WRAPPING CLIENT SOCKET WITH SSL")

        while True:
            communicate(sockClient, bufferSize, verbose)
    else:
        print("invalid mode, exiting...")

except KeyboardInterrupt as e:
    print("")
    print("user close program, exiting...")
except Exception as e:
    print("")
    print("ERROR:", e.strerror)
