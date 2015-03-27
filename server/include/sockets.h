#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#ifndef SOCKETS_H
#define SOCKETS_H

int tcp_listen(int port, int backlog);

#endif//SOCKETS_H
