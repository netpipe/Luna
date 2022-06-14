/*
  * client1.c
  *
  * Establish TCP client connection &
  * terminate connection using socket(),
  * connect() and close() functions.
  *
  *
  *
  */
#include  <stdio.h>
#include  <sys/types.h>
#include  <sys/socket.h>
#include  <netinet/in.h>
 #include <arpa/inet.h>
#include  <memory.h>
#include <stdlib.h>
#include <unistd.h>
int
main     (int argc, char *argv[])
{
    struct sockaddr_in sin;
    int sock = 0;
    int ret = 0;
    if (argc != 3)
    {
        printf("usage: %s: ip_address port\n", argv[0]);
        return(1);
    }
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        printf("TCP client socket() failed.\n");
        return(1);
    }
      // memset(&sin, 0x0, sizeof(struct sockaddr_in *)); the size of any pointer is 4 or 8,
                                            //depending on if it's a 32 bit or 64 bit pointer
        memset(&sin, 0x0, sizeof(struct sockaddr_in));
    sin.sin_family = AF_INET;
    sin.sin_port = htons(atoi(argv[2]));
    sin.sin_addr.s_addr = inet_addr(argv[1]);
    ret = connect(sock, (struct sockaddr *)&sin,
          sizeof(struct sockaddr));
    if (ret < 0)
    {
        printf("TCP client connect() failed.\n");
        close (sock);
        return(1);
    }
    printf("TCP client connected.\n");
    close(sock);
    printf("TCP client connection closed.\n");
    return(0);
}

