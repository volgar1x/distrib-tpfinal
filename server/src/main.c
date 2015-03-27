/// @author Antoine CHAUVIN

#include <stdio.h>

#include "config.h"
#include "sockets.h"

int main(int argc, char **argv) {
  struct sockaddr_in csin;
  int                sock, csock;
	socklen_t          csinlen = sizeof(csin);

	/** Create a TCP listening socket. */
  sock = tcp_listen(PORT, BACKLOG);
  if (-1 == sock) {
    perror("couldnt listen on port");
    return 1;
  }

	/** An infinite loop accepting all clients. */
  for (;;) {
		/** Accept one client. */
		bzero(&csin, sizeof(csin));
    csock = accept(sock, (struct sockaddr*)&csin, &csinlen);
    if (-1 == csock) {
      perror("failed to accept a connection");
      break;
    }

		/** Let the server handle the connection. */
		server_handle(csock, csin);
  }

	/** Clean things up. */
  close(sock);

  return 0;
}
