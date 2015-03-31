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
	client_t           client;
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
	client.sock         = sock;
	client.addr         = (struct sockaddr*)&csin;
	client.addr_len     = csin_len;

	if (-1 == bind(sock, (struct sockaddr*)&sin, sizeof(sin))) {
		perror("couldnt bind socket");
		return 1;
  }

	server_init();
	buf = (char*) malloc(sizeof(char) * BUFLEN);
	// boucle infinie
	for (;;) {
		n = client_recv(client, buf, BUFLEN);

		data = (char*) malloc(sizeof(char) * n);
		data[n-1] = '\0';
		memcpy(data, buf, n-1);
		err = server_handle(client, data, n-1);
		free(data);
		if (err) {
			perror("server fault");
			break;
    }
  }

	free(buf);
	server_clean();

	return 0;
}
