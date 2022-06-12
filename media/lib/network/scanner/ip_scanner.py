import os
from .utils import *
import threading



ping_cmd = get_ping_cmd()


def ip_scanner_thread(lock, ip_range, available_ips):
    # global available_ips

    while ip_range:
        lock.acquire()
        ip = ip_range.pop()
        lock.release()

        comm = ping_cmd + ip
        response = os.popen(comm)

        if 'ttl' in response.read():
                lock.acquire()
                available_ips.append(ip)
                lock.release()



def scan_ips(start, end):
    ip_range = find_ips(start, end)
    available_ips = []
    lock = threading.Lock()

    threads = [threading.Thread(target=ip_scanner_thread, args=(lock, ip_range, available_ips)) for t in range(200)]
    for t in threads:
        t.start()
    for t in threads:
        t.join()

    return available_ips
