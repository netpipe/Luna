import socket
import struct
import re
import ipaddress


class SocksException(Exception):
    pass


class AddrTypes():
    IPv4 = b'\x01'
    IPv6 = b'\x04'
    Domain = b'\x03'


class Socks5Address():
    def __init__(self, ip, type=AddrTypes.IPv4):
        self.ip = ip
        self.type = type

    def getByteIp(self):
        if self.type == AddrTypes.IPv4:
            return AddrTypes.IPv4 + ipaddress.IPv4Address(self.ip).packed
        elif self.type == AddrTypes.IPv6:
            return AddrTypes.IPv6 + ipaddress.IPv6Address(self.ip).packed
        elif self.type == AddrTypes.Domain:
            return AddrTypes.Domain + bytes([len(self.ip)]) + self.ip.encode()
        else:
            raise TypeError(f"Unknown Address Type: {self.type}")

    def getIp(self):
        return self.ip

    def getType(self):
        return self.type

    @staticmethod
    def readAddr(sock):
        type = sock.recv(1)
        if type == AddrTypes.IPv4:
            return Socks5Address(ipaddress.IPv4Address(sock.recv(4)).exploded,
                                 AddrTypes.IPv4)
        elif type == AddrTypes.IPv6:
            return Socks5Address(ipaddress.IPv6Address(sock.recv(16)).compressed,
                                 AddrTypes.IPv6)
        elif type == AddrTypes.Domain:
            drlen, = sock.recv(1)
            return Socks5Address(sock.recv(drlen).decode(), AddrTypes.Domain)
        else:
            raise SocksException(f"Unknown address type: {type}")

    def __repr__(self):
        return self.getIp()


class IpIdentify():
    @staticmethod
    def identify(ip):
        try:
            addr = ipaddress.ip_address(ip)
            if isinstance(addr, ipaddress.IPv4Address):
                return AddrTypes.IPv4
            else:
                return AddrTypes.IPv6
        except Exception:
            rident = r"^(?=.{1,255}$)(?!-)[A-Za-z0-9\-]{1,63}(\.[A-Za-z0-9\-]{1,63})*\.?(?<!-)$"
            match = re.match(rident, ip)

            if match:
                return AddrTypes.Domain
            return None


class SocksErrors():
    rqden = {
        0x00: "Granted",
        0x01: "General Faliure",
        0x02: "Connection not allowed by ruleset",
        0x03: "Network unreachable",
        0x04: "Host unreachable",
        0x05: "Connection refused by destination host",
        0x06: "TTL expired",
        0x07: "Command not supported / protocol error",
        0x08: "Address type not supported",
        0x5A: "Granted",
        0x5B: "Request rejected or failed",
        0x5C: "Request failed because client is not running identd (or not reachable from server)",
        0x5D: "Request failed because client's identd could not confirm the user ID in the request"
    }

    @staticmethod
    def request_denied(err):
        if err in SocksErrors.rqden:
            return f"({'0x%02x'%err}) {SocksErrors.rqden[err]}"
        else:
            return "Unknown Error"


class AuthenticationMethod():
    def getId(self) -> int:
        pass

    def forP(self) -> int:
        pass

    def authenticate(self, socket) -> bool:
        pass


class NoAuth(AuthenticationMethod):
    def getId(self):
        return 0x00

    def forP(self):
        return Socks.SOCKS5

    def authenticate(self, socket):
        return True


class Socks4Ident(AuthenticationMethod):
    def __init__(self, *args):
        if len(args) == 0:
            self.ident = ''
        else:
            self.ident = args[0]

    def forP(self):
        return Socks.SOCKS4

    def getId(self):
        return 0x00

    def authenticate(self, socket):
        return True


class Socks:
    SOCKS5 = 5
    SOCKS4 = 4


class ProxyHopper:
    def __init__(self, proxies, debug=False, stype=Socks.SOCKS5):
        self.proxies = proxies
        self.debug = debug
        self.stype = stype

    def connect(self, addr):
        self.hopper = None
        for proxy in self.proxies:
            self.hopper = SocksSocket(self.hopper, self.debug)
            self.hopper.set_proxy(proxy, self.stype)
        self.hopper.connect(addr)

    def sendall(self, data):
        self.hopper.sendall(data)

    def recv(self, numbytes=1):
        return self.hopper.recv(numbytes)

    def close(self):
        self.hopper.close()


class SocksSocket(socket.socket):
    def __init__(self, *args, **kwargs):
        global default_proxy, default_proxy_auth, default_proxy_type
        defaults = {
            "udp": False,
            "socketobject": None,
            "debug": False
        }
        kwargs = {**defaults, **kwargs}

        super().__init__(socket.AF_INET, socket.SOCK_STREAM)

        self.proxy = default_proxy
        self.udp = kwargs["udp"]
        self.auth = default_proxy_auth
        self.socktype = default_proxy_type
        self.socketobject = kwargs["socketobject"]
        self.debug = kwargs["debug"]
        self.udpbind = None
        self.udpsocket = None

    def set_proxy(self, proxy, socktype=Socks.SOCKS5, auth=[NoAuth()]):
        """
         Set the proxy to use
        """
        self.proxy = proxy
        self.auth = auth
        self.socktype = socktype

    def sendall(self, data):
        """
        -- TCP ONLY --
         Send data over TCP socket via proxy.
        """
        if self.udp and self.udpbind is not None:
            raise SocksException("Cannot use SENDALL on UDP type socket")

        if self.socketobject is not None:
            self.socketobject.sendall(data)
        else:
            super().sendall(data)

    def recv(self, numbytes=1):
        """
        -- TCP ONLY --
         Recieve data over TCP socket
        """
        if self.udp and self.udpbind is not None:
            raise SocksException("Cannot use RECV on UDP type socket")

        if self.socketobject is not None:
            return self.socketobject.recv(numbytes)
        else:
            return super().recv(numbytes)

    def sendto(self, data, address):
        """
        -- UDP ONLY --
         Send data over UDP socket via proxy.
        """
        if not self.udp:
            raise SocksException("Cannot use SENDTO on TCP type socket")
        if self.udpbind is None or self.udpsocket is None:
            raise SocksException("Proxy connection not initialized")

        ip, port = address

        addr_type = IpIdentify.identify(ip)
        if addr_type is None:
            raise SocksException(f"Invalid IP address or domain name: {ip}")

        # No Fragmentation
        packet = b"\x00\x00\x00"
        packet += Socks5Address(ip, addr_type).getByteIp()
        packet += struct.pack("!H", port)
        packet += data

        self.udpbind = (self.udpbind[0].getIp(), self.udpbind[1])

        if self.udpbind[0] == "0.0.0.0":
            self.udpbind = (self.proxy[0], self.udpbind[1])

        self.udpsocket.sendto(packet, self.udpbind)

    def recvfrom(self, bytes):
        """
        -- UDP ONLY --
         Recieve Data from UDP sock.
        """
        if not self.udp:
            raise SocksException("Cannot use SENDTO on TCP type socket")
        if self.udpbind is None or self.udpsocket is None:
            raise SocksException("Proxy connection not initialized")

        return self.udpsocket.recvfrom(bytes)

    def close(self):
        if self.socketobject is not None:
            return self.socketobject.close()
        else:
            return super().close()

    def __handshake_5(self, hp, auth=[NoAuth()]):
        if len(auth) < 1:
            self.close()
            raise SocksException("Must provide at least 1 authentication method. Leave the auth field blank for the default (No authentication)")

        if self.debug:
            print("[DEBUG/INFO] (SOCKS5) Sending authentication request...")

        authrequestpacket = b"\x05"
        authrequestpacket += struct.pack("B", len(auth))
        authrequestpacket += bytes([method.getId() for method in auth])
        self.sendall(authrequestpacket)
        ver, authc = self.recv(2)

        if hp is not None:
            ip, port = hp
        else:
            ip, port = ('0.0.0.0', 0)

        # Check if authentication method is correct
        if authc == 0xFF:
            self.close()
            raise SocksException("No usable authentication methods available")

        if self.debug:
            print(f"[DEBUG/INFO] (SOCKS5) Server chose authentication method: [{authc}]")

        for method in auth:
            if method.forP() != Socks.SOCKS5:
                pass
            if method.getId() == authc:
                if not method.authenticate(self):
                    self.close()
                    raise SocksException("Authentication Failed!")
                break

        # Send connect request packet
        addr_type = IpIdentify.identify(ip)
        if addr_type is None:
            self.close()
            raise SocksException(f"Invalid IP address or domain name: {ip}")

        if self.debug:
            print("[DEBUG/INFO] (SOCKS5) Sending connection request...")

        if self.udp:
            self.sendall(b'\x05\x03\x00\x01\x00\x00\x00\x00\x00\x00')
        else:
            self.sendall(b'\x05\x01\x00' + Socks5Address(ip, addr_type).getByteIp() + struct.pack("!H", port))

        ver, status, _ = self.recv(3)

        if status != 0x00:
            self.close()
            raise SocksException(f"Server denied connection request with response: {SocksErrors.request_denied(status)}")

        bndaddr = Socks5Address.readAddr(self)
        bndport, = struct.unpack("!H", self.recv(2))

        self.udpbind = (bndaddr, bndport)

        if self.udp:
            self.close()

        if self.debug:
            print(f"[DEBUG/INFO] (SOCKS5) [{'UDP' if self.udp else 'TCP'}] Server accepted connection. (*{bndaddr}:{bndport})")

    def __handshake_4(self, hp, auth=[Socks4Ident("")]):
        if self.udp:
            raise SocksException("Cannot use UDP port over SOCKS4")

        ip, port = hp
        ident = IpIdentify.identify(ip)

        if ident == AddrTypes.Domain:
            ip = socket.gethostbyname_ex(ip)[2][0]
        elif ident == AddrTypes.IPv6:
            self.close()
            raise SocksException("IPv6 is not supported for Socks4")
        elif ident == AddrTypes.IPv4:
            pass
        else:
            self.close()
            raise SocksException(f"Unknown IP type ({ip})")

        id = ""
        for method in auth:
            if isinstance(method, Socks4Ident):
                id = method.ident
                break

        if self.debug:
            print("[DEBUG/INFO] (SOCKS4) Sending authentication request...")

        authrequestpacket = b"\x04\x01"
        authrequestpacket += struct.pack("!H", port)
        authrequestpacket += ipaddress.IPv4Address(ip).packed
        authrequestpacket += id.encode() + b"\x00"
        self.sendall(authrequestpacket)

        _, rep = self.recv(2)

        if rep != 0x5A:
            self.close()
            raise SocksException(f"Server denied connection request with response: {SocksErrors.request_denied(rep)}")

        dstport, = struct.unpack("!H", self.recv(2))
        dstip = ipaddress.IPv4Address(self.recv(4)).exploded
        if self.debug:
            print(f"[DEBUG/INFO] (SOCKS4) Server accepted connection. (*{dstip}:{dstport})")

        self.udpbind = (dstip, dstport)

    def initudp(self):
        if not self.udp:
            raise SocksException("Cannot initialize UDP proxy connection on TCP socket. Please see docs for proper UDP socket use.")

        self.udpsocket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        # self.udpsocket.bind(('', ))
        self.connect(None)

    def connect(self, hp):
        if self.udp and hp is not None:
            raise SocksException("Cannot initialize TCP proxy connection on UDP socket. Please see docs for proper TCP socket use.")

        if self.proxy is None:
            raise SocksException("No proxy selected")

        if self.debug:
            print(f"[DEBUG/INFO] Connecting to proxy: {self.proxy}")

        if self.socketobject is not None:
            self.socketobject.connect(self.proxy)
        else:
            super().connect(self.proxy)

        if self.debug:
            print("[DEBUG/INFO] Connected, Handshaking...")

        if self.socktype == Socks.SOCKS5:
            self.__handshake_5(hp, self.auth)
        elif self.socktype == Socks.SOCKS4:
            self.__handshake_4(hp, self.auth)
        else:
            raise SocksException(f"Unknown proxy type {self.socktype}")


default_proxy = None
default_proxy_auth = [NoAuth()]
default_proxy_type = Socks.SOCKS5


def set_default_proxy(proxy, socktype=Socks.SOCKS5, auth=[NoAuth()]):
    """
    Set the proxy for all sockssockets to use by default
    """
    global default_proxy, default_proxy_auth, default_proxy_type
    default_proxy = proxy
    default_proxy_type = socktype
    default_proxy_auth = auth
