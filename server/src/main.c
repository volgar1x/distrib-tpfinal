#include <stdio.h>

#include "config.h"
#include "sockets.h"

int main(int argc, char **argv) {
  struct sockaddr_in csin;
  int                sock, csock;
	socklen_t          csinlen = sizeof(csin);

  sock = tcp_listen(PORT, BACKLOG);
  if (-1 == sock) {
    perror("couldnt listen on port");
    return 1;
  }

  for (;;) {
    bzero(&csin, sizeof(csin));
    csock = accept(sock, (struct sockaddr*)&csin, &csinlen);
    if (-1 == csock) {
      perror("failed to accept a connection");
      break;
    }

    printf("accepted a connection YAY!\n");
    close(csock);
  }

  close(sock);
  return 0;
}
