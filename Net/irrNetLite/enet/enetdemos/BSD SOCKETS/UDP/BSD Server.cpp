/*
  * server1.c
  *
  * Create TCP server socket, accept
  * one TCP client connection using
  * socket(), bind(), listen() and
  * accept().
  *
  * foster <jamescfoster@gmail.com>
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
          struct sockaddr_in sin ;
          struct sockaddr_in csin;
          socklen_t           len   = sizeof(struct sockaddr);
short                port  =  0;
int                  csock =  0;
int                  sock   = 0;
int                  ret    = 0;
if(argc != 2)
{
         printf("usage: %s: port\n", argv[0]);
         return(1);
}
port = atoi(argv[1]);
sock = socket(AF_INET, SOCK_STREAM, 0);
if(sock < 0)
{
         printf("TCP server socket() failed.\n");
         return(1);
}
      // memset(&sin, 0x0, sizeof(struct sockaddr_in *)); the size of any pointer is 4 or 8,
                                            //depending on if it's a 32 bit or 64 bit pointer
        memset(&sin, 0x0, sizeof(struct sockaddr_in));
sin.sin_family       = AF_INET;
sin.sin_port         = htons(port);
sin.sin_addr.s_addr = INADDR_ANY;
ret = bind(sock, (struct sockaddr *)&sin,
                      (struct sockaddr));
if(ret < 0)
{
         printf("TCP server bind() failed.\n");
         close (sock);
         return(1   );
}
ret = listen(sock, 5);
if(ret < 0)
{
         printf("TCP server listen() failed.\n");
         close (sock);
         return(1   );
}
printf("TCP server listening.\n");
memset(&csin, 0x0, sizeof(struct sockaddr));
csock = accept(sock, (struct sockaddr *)&csin, &len);
if(csock < 0)
{
         printf("TCP server accept() failed.\n");
}
else
{
         printf("TCP server: TCP client connection " /
         "on port %d.\n", port);
         close(csock);
  }
  close(sock);
  return(0);
}

