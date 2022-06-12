from scapy.config import conf
from scapy.layers.l2 import ARP, Ether, srp, get_if_addr


def scan(ip):
    arp = Ether(dst="ff:ff:ff:ff:ff:ff") / ARP(pdst=ip)
    asw = srp(arp, timeout=2, verbose=False)[0]
    ip_mac_list = []
    for i in asw:
        ip_mac_list.append({'ip': i[1].psrc, 'mac': i[1].hwsrc})
    return ip_mac_list


def print_r(r):
    print('-------------------------------------------\nIP\t\t\tMAC\n-------------------------------------------')
    for a in r:
        print(a['ip'] + '\t\t' + a['mac'])


class NetDiscover:
    def __init__(self, output: bool = True):
        self.ipg = '.'.join((get_if_addr(conf.iface).split('.')[:3])) + '.1/24'
        print('Net Discovering on:', self.ipg)
        self.result = scan(self.ipg)
        if output:
            print_r(self.result)


if __name__ == '__main__':
    NetDiscover(output=True)
