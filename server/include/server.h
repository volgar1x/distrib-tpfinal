#ifndef SERVER_H
#define SERVER_H

#include "sockets.h"
#include "bank.h"

typedef int error_t;

void server_init();
void server_clean();

error_t server_handle(client_t c, char *data, int data_len);
error_t server_handle_create(client_t c, char* name, char* firstname);
error_t server_handle_deposit(client_t c, int id, int amount);
error_t server_handle_withdraw(client_t c, int id, int amount);
error_t server_handle_query(client_t c, int id);
error_t server_handle_transfer(client_t c, int from, int to, int amount);
error_t server_handle_infos(client_t c, int id, char* name, char* firstname);

#endif//SERVER_H
