/// @author Antoine CHAUVIN

#include "sockets.h"

int tcp_listen(int port, int backlog) {
  struct sockaddr_in sin;
  int                sock;

	/** Create a socket. */
  sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock == -1) {
    return -1;
  }

	/** Bootstrap its address. */
  bzero(&sin, sizeof(sin));
  sin.sin_addr.s_addr = htonl(INADDR_ANY);
  sin.sin_port        = htons(port);
  sin.sin_family      = AF_INET;

	/** We want to reuse unused ports. */
  int yes=1;
  if (-1 == setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes))) {
    return -1;
  }

	/** Let's bind! */
  if (-1 == bind(sock, (struct sockaddr*)&sin, sizeof(sin))) {
    return -1;
  }

	/** And now, we listen. */
  if (-1 == listen(sock, backlog)) {
    return -1;
  }

  return sock;
}

