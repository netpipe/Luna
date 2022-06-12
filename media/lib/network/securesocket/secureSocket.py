import socket
import pyDH as dh
class secure_socket(socket.socket):
    """Secured socket object. Can auto-encrypt transfered data.
    """
    def __init__(s, family=-1, type=-1, proto=-1, fileno=None, privatekey:int=None):
       super().__init__(family, type, proto, fileno)
       s.keypair=dh.DiffieHellman()
       s.shared=s._tobytes(0)
       if privatekey!=None:
          s.keypair._DiffieHellman__a=privatekey
    @classmethod
    def _tobytes(t,a:int)->bytes:
        l=[]
        if a==0:return bytes([0])
        while a!=0:
            l+=[a%256]
            a=a//256
        return bytes(l)
    @classmethod
    def _frombytes(t,l:bytes)->int:
       a=0
       for i in range(len(l)):
          a+=l[i]*(256**i)
       return a
    @classmethod
    def _xor(t,a,b):
        a,b=bin(a)[2:].zfill(8),bin(b)[2:].zfill(8)
        return int("".join(["0" if a[i]==b[i] else "1" for i in range(8)]),2)
    @classmethod
    def _crypt(t,a,b):
        k=(b*(len(a)//len(b)+1))[:len(a)]
        return bytes([t._xor(a[i],k[i]) for i in range(len(a))])
    def accept(s) -> ("secured_socket", "address info"):
        """
        Wait for an incoming connection.  Return a new socket
        representing the connection, and the address of the client.
        For IP sockets, the address info is a pair (hostaddr, port).
        """
        c,a=s._accept()
        return secure_socket(s.family,s.type,s.proto,c,s.keypair.get_private_key()),a
    def recvall(s) -> bytes:
        """
        Recives all available data.
        """
        r=b""
        try:
            while True:
                r+=s.recv(1)
        except:pass
        return r
    def setup_encryption(s):
        """
        Setup asymmetric encryption. the other side should also run this to complete
        """
        s.setblocking(True)
        key=s._tobytes(s.keypair.gen_public_key())
        s.encrypted_send(key+b"0"*(256-len(key)))
        s.shared=s._tobytes(int(s.keypair.gen_shared_key(s._frombytes(s.encrypted_recv(256))),16))
        s.setblocking(False)
    def set_key(s,key:int):
        """
        Set a integer as encryption key. 
        """
        s.shared=s._tobytes(key)
        s.setblocking(False)
    def encrypted_send(s,data):
        """
        Encrypts data and sends it.
        """
        s.send(s._crypt(data,s.shared))
    def encrypted_recv(s,buff):
        """
        Recives data and decrypts it.
        """
        data=s.recv(buff)
        return s._crypt(data,s.shared)
    def encrypted_recvall(s):
        """
        Recives all available data and decrypts it.
        """
        return s._crypt(s.recvall(),s.shared)
