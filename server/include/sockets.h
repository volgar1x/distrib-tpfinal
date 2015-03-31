#ifndef SOCKETS_H
#define SOCKETS_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

typedef struct {
  int              sock;
  struct sockaddr* addr;
  socklen_t        addr_len;
} client_t;

int  client_recv(client_t c, void* buf, size_t len);
void client_send(client_t c, const void* buf, size_t len);

#endif//SOCKETS_H
