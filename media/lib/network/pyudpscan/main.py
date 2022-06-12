import argparse
import time

from scanner import Scanner


def main():
    try:
        parser = argparse.ArgumentParser()
        parser.add_argument("-H", "--hosts", dest="hosts", type=str,
            nargs="+", default=["127.0.0.1"],
            help=("List of target hosts.\n"
                  "Example: 192.168.0-4.0/24 192.168.15-28.0/24"))
        parser.add_argument("-P", "--ports", dest="ports", type=str,
            nargs="+", default=[19],
            help=("List of target ports.\n"
                  "Example: 15 19 53-69"))
        parser.add_argument("-p", "--proxy", dest="proxies", type=str,
            nargs="+", default=None,
            help=("List of SOCKS5 proxies which will be taken at random.\n"
                  "Example: 98.98.98.98:1080 99.99.99.99:1080"))
        parser.add_argument("-t", "--timeout", dest="timeout",
            type=int, default=1,
            help="How long to wait for reply at UDP request from target host")
        parser.add_argument("-r", "--recheck", dest="recheck", type=int,
            default=0, help="Number of recheck for every port")
        parser.add_argument("-D", "--decoys", dest="decoys", type=str,
            nargs="+", default=None,
            help=("List of decoys to use.\n"
                  "Example: 91.91.91.91 19.19.19.19"))
        parser.add_argument("-i", "--interface", dest="interface",
            type=str, required=True,
            help=("Name of local source interface to listen on.\n"
                  "Example: eth0"))
        args = parser.parse_args()

        start = time.time()
        s = Scanner(args.proxies, args.decoys, args.hosts, args.ports,
            args.timeout, args.recheck, args.interface)
        result = s.scan()
        end = time.time()
        sorted_ips = sorted(result.keys())
        print("\n")

        min_len = 10
        for ip in sorted_ips:
            if args.proxies is None or \
                    ip not in [el.split(":")[0] for el in args.proxies]:
                sorted_ports = sorted(result[ip].keys())
                for port in sorted_ports:
                    address = "{}:{}".format(ip, port)
                    if len(address) / 8 <= 1:
                        tn = 2
                    else:
                        tn = 1
                    print(address + "\t" * tn + str(result[ip][port]))

        m, s = divmod(end - start, 60)
        h, m = divmod(m, 60)
        print("\nElapsed time: {} hours {} minutes {} seconds\n".format(
            h, m, s))

    except KeyboardInterrupt:
        print('\nThe process was interrupted by the user')
        raise SystemExit


if __name__ == "__main__":
    main()
