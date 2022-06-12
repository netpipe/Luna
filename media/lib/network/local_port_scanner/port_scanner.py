import socket
import sys
from optparse import OptionParser
from queue import Queue
from threading import Lock, Thread
from time import sleep, time

from .netdiscover import NetDiscover

banner = r"""
    ____             __     _____                                 
   / __ \____  _____/ /_   / ___/_________ _____  ____  ___  _____
  / /_/ / __ \/ ___/ __/   \__ \/ ___/ __ `/ __ \/ __ \/ _ \/ ___/
 / ____/ /_/ / /  / /_    ___/ / /__/ /_/ / / / / / / /  __/ /    
/_/    \____/_/   \__/   /____/\___/\__,_/_/ /_/_/ /_/\___/_/     

"""


def getparser():
    parser = OptionParser()
    parser.add_option("-H", "--host", dest="host", help="host address")
    parser.add_option("-a", "--auto", dest="auto", help="Auto discover addresses", default=False, action="store_true")
    return parser.parse_args()


class Scan:
    def __init__(self, target: str):
        socket.setdefaulttimeout(0.25)
        self.print_lock = Lock()
        self.q = Queue()
        try:
            self.t_IP = socket.gethostbyname(target)
        except socket.gaierror:
            print("\nHostname could not be resolved")
            sleep(3)
            sys.exit()

        except socket.error:
            print("\nCouldn't connect to server")
            sleep(3)
            sys.exit()

        print(f'\n\n___________________________________________\nStarting scan on host: {self.t_IP}\n'
              '___________________________________________\nPort\t\tStatus\n'
              '-------------------------------------------')
        self.startTime = time()

        for _ in range(100):
            t = Thread(target=self.threader, daemon=True)
            t.start()

        for port_p in range(1, 1024):
            self.q.put(port_p)

        self.q.join()
        print('\nTime taken:', str(int(time() - self.startTime)) + 's')

    def port_scan(self, port):
        s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        try:
            s.connect((self.t_IP, port))
            with self.print_lock:
                print(f'{port}\t\t open')
            s.close()
        except:
            pass

    def threader(self):
        while True:
            port_g = self.q.get()
            self.port_scan(port_g)
            self.q.task_done()


if __name__ == '__main__':
    (options, arguments) = getparser()
    print(banner)
    auto = options.auto
    if auto:
        print('Using Auto Discover mode\n')
        n = NetDiscover().result
        for i in n:
            target_ = i['ip']
            Scan(target=target_)

    else:
        target_ = options.host
        if not target_:
            target_ = input('Enter the host to be scanned: ')
        Scan(target=target_)
