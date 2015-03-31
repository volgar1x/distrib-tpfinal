#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sockets.h"
#include "config.h"
#include "server.h"

int main(int argc, char **argv) {
	int                sock, n;
	struct sockaddr_in sin, csin;
	socklen_t          csin_len;
	char               *buf, *data;
	error_t            err;

	sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (-1 == sock) {
		perror("couldnt create socket");
		return 1;
  }

	sin.sin_family      = AF_INET;
	sin.sin_port        = htons(PORT);
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	csin_len            = sizeof(csin);

	if (-1 == bind(sock, (struct sockaddr*)&sin, sizeof(sin))) {
		perror("couldnt bind socket");
		return 1;
  }

	buf = (char*) malloc(sizeof(char) * BUFLEN);
	// boucle infinie
	for (;;) {
		n = recvfrom(sock, buf, BUFLEN, 0, (struct sockaddr*)&csin, &csin_len);

		data = (char*) malloc(sizeof(char) * n);
		memcpy(data, buf, n);
		err = server_handle(data);
		free(data);
		if (err) {
			perror("server fault");
			break;
    }
  }

	free(buf);

	return 0;
}
