#include "sockets.h"

#ifndef SERVERS_H
#define SERVERS_H

void server_handle(int sock, struct sockaddr* saddr);
void server_handle_recv(int sock, struct sockaddr* saddr, void* data);
void server_handle_conn(int sock, struct sockaddr* saddr);
void server_handle_dcnn(int sock, struct sockaddr* saddr, int last_payload);

#endif
