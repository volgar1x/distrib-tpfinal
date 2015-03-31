#ifndef SERVER_H
#define SERVER_H

#include "sockets.h"
#include "bank.h"

typedef int error_t;

void server_init();
void server_clean();

void server_send(int sock, struct sockaddr_in csin, char* msg);
void server_send_account_status(int sock, struct sockaddr_in csin, bank_account* account);

error_t server_handle(int sock, struct sockaddr_in csin, char *data, int data_len);
error_t server_handle_create(int sock, struct sockaddr_in csin);
error_t server_handle_deposit(int sock, struct sockaddr_in csin, int id, int amount);
error_t server_handle_withdraw(int sock, struct sockaddr_in csin, int id, int amount);
error_t server_handle_query(int sock, struct sockaddr_in csin, int id);
error_t server_handle_transfer(int sock, struct sockaddr_in csin, int from, int to, int amount);

#endif//SERVER_H
