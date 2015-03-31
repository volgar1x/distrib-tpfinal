#include "sockets.h"

int client_recv(client_t c, void* buf, size_t len) {
	return recvfrom(c.sock, buf, len, 0, c.addr, &c.addr_len);
}

void client_send(client_t c, const void* buf, size_t len) {
	sendto(c.sock, buf, len, 0, c.addr, c.addr_len);
}
