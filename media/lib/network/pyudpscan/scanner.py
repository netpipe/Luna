import ctypes
import netifaces
import os
import random
import socket
import sys
import threading

from netaddr import IPNetwork
import socks
from scapy.all import IP, UDP, struct, sendp, srp


devnull = open(os.devnull, 'w')
stdout = sys.stdout
payload = {
    7: "\x0D\x0A\x0D\x0A",
    19: "\x63\x68\x61\x72\x67\x65\x6e",
    53: "\x00\x00\x10\x00\x00\x00\x00\x00\x00\x00\x00\x00",
    80: "\r12345678Q999\x00",
    111: ("\x72\xFE\x1D\x13\x00\x00\x00\x00\x00\x00\x00\x02\x00\x01\x86\xA0"
         "\x00\x01\x97\x7C\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
         "\x00\x00\x00\x00\x00\x00\x00\x00"),
    123: ("\xE3\x00\x04\xFA\x00\x01\x00\x00\x00\x01\x00\x00\x00\x00\x00\x00"
          "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
          "\x00\x00\x00\x00\x00\x00\x00\x00\xC5\x4F\x23\x4B\x71\xB1\x52\xF3"),
    137: ("\x80\xF0\x00\x10\x00\x01\x00\x00\x00\x00\x00\x00"
          "\x20CKAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\x00\x00\x21\x00\x01"),
    161: ("\x30\x3A\x02\x01\x03\x30\x0F\x02\x02\x4A\x69\x02\x03\x00\xFF\xE3"
          "\x04\x01\x04\x02\x01\x03\x04\x10\x30\x0E\x04\x00\x02\x01\x00\x02"
          "\x01\x00\x04\x00\x04\x00\x04\x00\x30\x12\x04\x00\x04\x00\xA0\x0C"
          "\x02\x02\x37\xF0\x02\x01\x00\x02\x01\x00\x30\x00"),
    177: "\x00\x01\x00\x02\x00\x01\x00",
    389: ("\x30\x84\x00\x00\x00\x2d\x02\x01\x07\x63\x84\x00\x00\x00\x24\x04"
          "\x00\x0a\x01\x00\x0a\x01\x00\x02\x01\x00\x02\x01\x64\x01\x01\x00"
          "\x87\x0b\x6f\x62\x6a\x65\x63\x74\x43\x6c\x61\x73\x73\x30\x84\x00"
          "\x00\x00\x00"),
    427: ("\x02\x01\x00\x006 \x00\x00\x00\x00\x00\x01\x00\x02en\x00\x00\x00"
          "\x15service:service-agent\x00\x07default\x00\x00\x00\x00"),
    520: ("\x01\x01\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
          "\x00\x00\x00\x00\x00\x00\x00\x10"),
    623: ("\x06\x00\xff\x07\x00\x00\x00\x00\x00\x00\x00\x00\x00\x09\x20\x18"
          "\xc8\x81\x00\x38\x8e\x04\xb5"),
    1194: "8d\xc1x\x01\xb8\x9b\xcb\x8f\0\0\0\0\0",
    1604: ("\x1e\x00\x01\x30\x02\xfd\xa8\xe3\x00\x00\x00\x00\x00\x00\x00\x00"
           "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"),
    1645: ("\x01\x00\x00\x14"
           "\x00\x00\x00\x00\x00\x00\x00\x00"
           "\x00\x00\x00\x00\x00\x00\x00\x00"),
    1812: ("\x01\x00\x00\x14"
           "\x00\x00\x00\x00\x00\x00\x00\x00"
           "\x00\x00\x00\x00\x00\x00\x00\x00"),
    2049: ("\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x02\x00\x01\x86\xA3"
           "\x00\x00\x00\x02\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
           "\x00\x00\x00\x00\x00\x00\x00\x00"),
    2302: ("\x00\x02\xf1\x26\x01\x26\xf0\x90\xa6\xf0\x26\x57\x4e"
           "\xac\xa0\xec\xf8\x68\xe4\x8d\x21"),
    3283: "\0\x14\0\x01\x03",
    5351: "\x00\x00",
    5353: ("\x00\x00\x00\x00\x00\x01\x00\x00\x00\x00\x00\x00"
           "\x09_services\x07_dns-sd\x04_udp\x05local\x00\x00\x0C\x00\x01"),
    17185: "\x00\x00\x00\x00",
    27910: "\xff\xff\xff\xffstatus",
    27911: "\xff\xff\xff\xffstatus",
    27912: "\xff\xff\xff\xffstatus",
    27913: "\xff\xff\xff\xffstatus",
    27914: "\xff\xff\xff\xffstatus",
    64738: "\x00\x00\x00\x00abcdefgh",
    3784: ("\x01\xe7\xe5\x75\x31\xa3\x17\x0b\x21\xcf\xbf\x2b\x99\x4e\xdd\x19"
           "\xac\xde\x08\x5f\x8b\x24\x0a\x11\x19\xb6\x73\x6f\xad\x28\x13\xd2"
           "\x0a\xb9\x12\x75"),
    8767: ("\xf4\xbe\x03\x00\x00\x00\x00\x00\x00\x00\x00\x00\x01\x00\x00"
           "\x002x\xba\x85\tTeamSpeak\x00\x00\x00\x00\x00\x00\x00\x00\x00"
           "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\nWindows XP\x00\x00"
           "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
           "\x00\x02\x00\x00\x00 \x00<\x00\x00\x01\x00\x00\x00\x00\x00\x00"
           "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
           "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
           "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
           "\x00\x00\x00\x00\x00\x00\x08nickname\x00\x00\x00\x00\x00\x00\x00"
           "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"),
    9987: ("\x05\xca\x7f\x16\x9c\x11\xf9\x89\x00\x00\x00\x00\x02\x9d\x74\x8b"
           "\x45\xaa\x7b\xef\xb9\x9e\xfe\xad\x08\x19\xba\xcf\x41\xe0\x16\xa2"
           "\x32\x6c\xf3\xcf\xf4\x8e\x3c\x44\x83\xc8\x8d\x51\x45\x6f\x90\x95"
           "\x23\x3e\x00\x97\x2b\x1c\x71\xb2\x4e\xc0\x61\xf1\xd7\x6f\xc5\x7e"
           "\xf6\x48\x52\xbf\x82\x6a\xa2\x3b\x65\xaa\x18\x7a\x17\x38\xc3\x81"
           "\x27\xc3\x47\xfc\xa7\x35\xba\xfc\x0f\x9d\x9d\x72\x24\x9d\xfc\x02"
           "\x17\x6d\x6b\xb1\x2d\x72\xc6\xe3\x17\x1c\x95\xd9\x69\x99\x57\xce"
           "\xdd\xdf\x05\xdc\x03\x94\x56\x04\x3a\x14\xe5\xad\x9a\x2b\x14\x30"
           "\x3a\x23\xa3\x25\xad\xe8\xe6\x39\x8a\x85\x2a\xc6\xdf\xe5\x5d\x2d"
           "\xa0\x2f\x5d\x9c\xd7\x2b\x24\xfb\xb0\x9c\xc2\xba\x89\xb4\x1b\x17"
           "\xa2\xb6")
}


class ICMP(ctypes.Structure):
    _fields_ = [
        ("type", ctypes.c_ubyte),
        ("code", ctypes.c_ubyte),
        ("checksum", ctypes.c_ushort),
        ("unused", ctypes.c_ushort),
        ("next_hop_mtu", ctypes.c_ushort)
    ]

    def __new__(self, socket_buffer):
        return self.from_buffer_copy(socket_buffer)

    def __init__(self, socket_buffer):
        pass


class Scanner(object):
    def __init__(self, proxies=None, decoys=None, hosts=["127.0.0.1"],
                 ports=[19], timeout=1, recheck=0, interface=None):
        self.proxies = proxies
        self.decoys = decoys
        self.hosts = hosts
        self.ports = ports
        self.timeout = timeout
        self.recheck = recheck
        self.interface = interface
        self.int_address = netifaces.ifaddresses(
            self.interface)[netifaces.AF_INET][0]["addr"]
        self.sockets = {}
        self._init_sockets()

    def _init_sockets(self):
        """Initiate sockets throgh proxies"""

        if self.proxies is not None:
            for proxy in self.proxies:
                self._init_socket(proxy)

    def _init_socket(self, proxy):
        """Initiate socket throgh proxy

        @param proxy: Proxy address in format ip:port
        @type proxy: `str`
        """

        sp = random.randint(1000, 65535)
        self.sockets[proxy] = socks.socksocket(
            socket.AF_INET, socket.SOCK_DGRAM)
        ip, port = proxy.split(":")
        port = int(port)
        self.sockets[proxy].set_proxy(socks.SOCKS5, ip, port)
        self.sockets[proxy].setblocking(0)
        self.sockets[proxy].settimeout(self.timeout)
        self.sockets[proxy].bind((self.int_address, sp))

    def segmentation(self, subnet):
        """Split IP into segments

        @param subnet: IP or subnet
        @type subnet: `str`
        """

        segments = subnet.split(".")
        if "/" in segments[-1]:
            segments.extend(segments[-1].split("/"))
            del segments[-3]

        return segments

    def break_up_ip_ranges(self, segments):
        """Breaks up IP ranges

        @param segments: List of IP segments
        @type segments: [`str`]

        Example:
        For ["192", "168", "0-1", "0"]
        would be ["192.168.0.0", "192.168.1.0"]
        """

        subnets = []
        tails = []
        head = ""
        idx = 0

        while "-" not in segments[idx]:
            if idx < len(segments) - 1:
                head += segments[idx] + "."
            else:
                head += segments[idx]
            if idx + 1 == len(segments):
                break
            idx += 1

        if "-" in segments[idx]:
            start, end = segments[idx].split("-")
            for el in xrange(int(start), int(end) + 1):
                tails.extend(self.break_up_ip_ranges(
                    [str(el)] + segments[idx+1:]))
            for el in tails:
                subnets.append(head + el)

        if not subnets:
            subnets.append(head)

        return subnets

    def parse_subnet(self, subnet):
        """Parse subnet into subnets

        @param subnet: Subnet
        @type subnet: `str`
        """

        segments = self.segmentation(subnet)
        if "/" in subnet:
            subnets = self.break_up_ip_ranges(segments[:-1])
            for idx in xrange(len(subnets)):
                subnets[idx] = subnets[idx] + "/" + segments[-1]
        else:
            subnets = self.break_up_ip_ranges(segments)

        return subnets

    def break_up_port_range(self, port_range):
        """Breaks up port ranges

        @param port_range: Port range to parse
        @type port_range: `str`
        """

        ports = []

        start, end = port_range.split("-")
        for idx in xrange(int(start), int(end) + 1):
            ports.append(idx)

        return ports

    def scan(self):
        """Scan hosts for ports status"""

        scan_data = {}
        threads = []

        def send_requests_proxy(ip, proxy, dproxies):
            """Send requests to hosts in subnet through proxy

            @param ip: Target IP address
            @type ip: `str`
            @param proxy: Proxy address in format ip:port
            @type proxy: `str`
            @param dproxies: Dictionary with proxies and their status
            @type dproxies: dict(`str`: `bool`)
            """

            proxy_ip, _ = proxy.split(":")
            scan_data.setdefault(proxy_ip, {})
            scan_data.setdefault(ip, {})
            for port in ports:
                pld = ""
                if port in payload:
                    pld = payload[port]
                for i in xrange(self.recheck + 1):
                    if port in scan_data[ip] and scan_data[ip][port] in \
                            ["Open", "Closed", "Filtered"]:
                        break
                    packet = IP(dst=ip.format())/UDP(dport=port)/(pld)

                    try:
                        self._init_socket(proxy)
                        s = self.sockets[proxy]
                        scan_data[proxy_ip]["current_ip"] = ip
                        scan_data[proxy_ip]["current_port"] = port

                        s.connect((ip.format(), port))
                        s.send(bytes(packet))
                        s.recv(65565)
                        scan_data[ip][port] = "Open"
                    except (socket.timeout, socket.error, Exception) as ex:
                        if ip not in scan_data or \
                                port not in scan_data[ip]:
                            scan_data[ip][port] = "Open|Filtered"

                    s.close()

            dproxies[proxy] = True

        def send_requests(ip):
            """Send requests to hosts in subnet directly

            @param ip: Target IP address
            @type ip: `str`
            """

            scan_data.setdefault(ip, {})
            for port in ports:
                pld = ""
                if port in payload:
                    pld = payload[port]
                for i in xrange(self.recheck + 1):
                    if port in scan_data[ip] and scan_data[ip][port] in \
                            ["Open", "Closed", "Filtered"]:
                        break

                    sport = random.randint(1000, 65535)
                    packet = IP(dst=ip.format())/UDP(
                        dport=port,sport=sport)/(pld)
                    decoys = []

                    # Decoys evaluating
                    if self.decoys is not None:
                        for decoy in self.decoys:
                            sport = random.randint(1000, 65535)
                            decoys.append(IP(dst=ip.format(),src=decoy)/
                                          UDP(dport=port,sport=sport)/
                                          (pld))

                    try:
                        sys.stdout = devnull

                        decoy_pause = random.randint(0, len(decoys))
                        random.shuffle(decoys)

                        for d in xrange(decoy_pause):
                            del decoys[d]["UDP"].chksum
                            pack = IP(str(decoys[d]))
                            sendp(pack, iface=self.interface, verbose=False)

                        del packet.chksum
                        pack = IP(str(packet))
                        rep, non_rep = srp(pack, timeout=self.timeout,
                            iface=self.interface, verbose=False)
                        if len(rep) == 0:
                                scan_data[ip][port] = "Open|Filtered"
                        elif rep[0][1].proto == 1:
                            if rep[0][1].code == 3:
                                scan_data[ip][port] = "Closed"
                            else:
                                scan_data[ip][port] = "Filtered"
                        elif rep[0][1].proto == 17:
                            scan_data[ip][port] = "Open"

                        for d in xrange(decoy_pause, len(decoys)):
                            del decoys[d]["UDP"].chksum
                            pack = IP(str(decoys[d]))
                            sendp(pack, iface=self.interface, verbose=False)

                        sys.stdout = stdout
                    except Exception as ex:
                        sys.stdout = stdout
                        print("{}:{} Something went wrong\n{}".format(
                            ip, port, ex))

        def sniff_icmp():
            """Sniff for ICMP responses"""

            sniffer = socket.socket(socket.AF_INET, socket.SOCK_RAW,
                socket.IPPROTO_ICMP)
            sniffer.bind((self.int_address, 0))
            sniffer.setsockopt(socket.IPPROTO_IP, socket.IP_HDRINCL, 1)

            while True:
                raw_buffer = sniffer.recvfrom(65565)[0]
                ip_header = raw_buffer[0:20]
                iph = struct.unpack('!BBHHHBBH4s4s', ip_header)

                # protocol = iph[6]
                version_ihl = iph[0]
                ihl = version_ihl & 0xF
                iph_length = ihl * 4
                src_addr = socket.inet_ntoa(iph[8])

                buf = raw_buffer[iph_length:iph_length + ctypes.sizeof(ICMP)]
                icmp_header = ICMP(buf)

                if self.proxies is not None and \
                        src_addr in [el.split(":")[0] for el in self.proxies]:
                    if icmp_header.code == 3 and icmp_header.type == 3:
                        scan_data[scan_data[src_addr]["current_ip"]][
                            scan_data[src_addr]["current_port"]] = "Closed"
                    else:
                        scan_data[scan_data[src_addr]["current_ip"]][
                            scan_data[src_addr]["current_port"]] = "Filtered"

        def get_proxy(dproxies):
            """Get random proxy

            @param dproxies: Dictionary with proxies and their status
            @type dproxies: dict(`str`: `bool`)
            """

            available_proxies = []
            while len(available_proxies) == 0:
                available_proxies = [k for k, v in dproxies.iteritems() if v]

            proxy = random.choice(available_proxies)
            s = self.sockets[proxy]
            dproxies[proxy] = False

            return (proxy, s)

        subnets = []
        for host in self.hosts:
            subnets.extend(self.parse_subnet(host))

        ports = []
        for port in self.ports:
            if "-" in port:
                ports.extend(self.break_up_port_range(port))
            else:
                ports.append(int(port))

        if self.proxies is not None:
            sniff_thread = threading.Thread(target=sniff_icmp)
            sniff_thread.daemon = True
            sniff_thread.start()

        dproxies = dict([(el, True) for el in self.sockets.keys()])

        for subnet in subnets:
            for net_ip in IPNetwork(subnet):
                if self.proxies is None:
                    t = threading.Thread(target=send_requests, args=(net_ip,))
                    t.start()
                    threads.append(t)
                else:
                    proxy, _ = get_proxy(dproxies)
                    t = threading.Thread(target=send_requests_proxy,
                        args=(net_ip, proxy, dproxies,))
                    t.start()
                    threads.append(t)

        for thread in threads:
            thread.join()

        return scan_data
