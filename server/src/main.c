#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sockets.h"
#include "config.h"
#include "server.h"

int main(int argc, char **argv) {
	int                sock;
	struct sockaddr_in sin, csin;
	client_t           client;

	int                n;
	char               *buf, *data;
	error_t            err;

	// Create a socket.
	sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (-1 == sock) {
		perror("couldnt create socket");
		return 1;
  }

	// Configure it.
	sin.sin_family      = AF_INET;
	sin.sin_port        = htons(PORT);
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	client.sock         = sock;
	client.addr         = (struct sockaddr*)&csin;
	client.addr_len     = sizeof(csin);

	// Bind it.
	if (-1 == bind(sock, (struct sockaddr*)&sin, sizeof(sin))) {
		perror("couldnt bind socket");
		return 1;
  }

	// Init the server.
	server_init();

	// Allocate a buffer.
	buf = (char*) malloc(sizeof(char) * BUFLEN);

	// Enter an infinite loop.
	for (;;) {
		// Receive from any client.
		n = client_recv(client, buf, BUFLEN);

		// Slice and copy buffer into a new memory space.
		data = (char*) malloc(sizeof(char) * n);
		data[n-1] = '\0';
		memcpy(data, buf, n-1);

		// Make the server handle the received data.
		err = server_handle(client, data, n-1);

		// Free the now useless memory.
		free(data);

		// Close the server if there was an error.
		if (err) {
			perror("server fault");
			break;
    }
  }

	// Free the memory taken by the buffer.
	free(buf);

	// Clean the server.
	server_clean();

	// Close the socket.
	close(sock);

	return 0;
}
