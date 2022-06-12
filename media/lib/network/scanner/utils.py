from ipaddress import ip_address
import platform
import socket
import netifaces as ni


def find_ips(start, end):
    start = ip_address(start)
    end = ip_address(end)
    result = []
    while start <= end:
        result.append(str(start))
        start += 1
    return result


def get_ping_cmd():
    oper = platform.system()
    if (oper == "Windows"):
        return "ping -n 1 "
    elif (oper == "Linux"):
        return "ping -c 1 "
    else:
        return "ping -c 1 "


def get_host_ip():
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    s.connect(("8.8.8.8", 80))
    return s.getsockname()[0]


def get_all_interfaces():
    interfaces = {}
    for intf in socket.if_nameindex():
        try:
            interfaces[intf[1]] = {
                'addr': ni.ifaddresses(intf[1])[ni.AF_INET][0]['addr'],
                'netmask': ni.ifaddresses(intf[1])[ni.AF_INET][0]['netmask']
            }
        except:
            pass
    return interfaces


def get_network_ips_range(ip, netmask):
    ip = bin(int(ip_address(ip)))[2:]
    ip = ip.rjust(32, '0')
    netmask = bin(int(ip_address(netmask)))[2:]
    netmask = netmask.rjust(32, '0')
    start = [ip[i] if netmask[i]=='1' else '0' for i in range(32)]
    end = [ip[i] if netmask[i]=='1' else '1' for i in range(32)]
    start = int(''.join(start), 2)
    end = int(''.join(end), 2)
    return (ip_address(start), ip_address(end))
