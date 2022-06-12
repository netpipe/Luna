from .ip_scanner import scan_ips
from .port_scanner import scan_ports
from .utils import get_all_interfaces, get_network_ips_range
from time import time
from multiprocessing.pool import ThreadPool


if __name__ == '__main__':
    # find host interfaces
    print('found interfaces:')
    intfs = get_all_interfaces()
    for i, intf in enumerate(intfs):
        print(f"{i}: {intf}  {intfs[intf]['addr']}")

    intf_i = input('select one of your interface to scan related network: ')
    intf_name = list(intfs.keys())[int(intf_i)]
    intf = intfs[intf_name]


    # find network ip range
    start, end = get_network_ips_range(intf['addr'], intf['netmask'])

    # find ips in local network
    print('--------------------------------------------')
    print('start scanning network...')
    start_t = time()
    ips = scan_ips(start, end)
    end_t = time()

    print(f'found {len(ips)} ips in {int(end_t-start_t)}s.')
    print('--------------------------------------------')


    # scan all ips
    print('scan ports for found IPs...')
    procs_num = min(len(ips), 10)
    pool = ThreadPool(processes=procs_num)
    start_t = time()
    procs = {ip: pool.apply_async(scan_ports, (ip, True)) for ip in ips}
    ip_ports = {ip:proc.get() for ip,proc in procs.items()}
    end_t = time()



    print(f'scanned in {int(end_t-start_t)}s')
