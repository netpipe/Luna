from time import time
import pyfiglet
import socket
import threading



def port_scanner_thread(ip, ports_batches, open_ports, lock):
    ascii_banner = pyfiglet.figlet_format("PORT SCANNER")

    while len(ports_batches) != 0:

        lock.acquire()
        selected_ports = ports_batches.pop()
        lock.release()

        for port in selected_ports:
            try:  
                s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
                socket.setdefaulttimeout(1)
                
                result = s.connect_ex((ip,port))
                if result == 0:
                    lock.acquire()
                    open_ports.append(port)
                    lock.release()
                s.close()
                
            except:
                pass


def scan_ports(ip, log=False):
    ports_batches = [range(i, min(i+100, 65535)) for i in range(1, 65535, 500)]
    open_ports = []
    lock = threading.Lock()
    threads = [threading.Thread(target=port_scanner_thread, args=(ip, ports_batches, open_ports, lock)) for t in range(100)]
    for t in threads:
        t.start()
    for t in threads:
        t.join()

    if log:
        print(f"{ip}\t=> {','.join([str(p) for p in open_ports])}")

    return open_ports


