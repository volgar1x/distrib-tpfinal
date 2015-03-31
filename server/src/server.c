#include <stdio.h>
#include <stdlib.h>

#include "server.h"
#include "util.h"
#include "string.h"

static bank* the_bank = NULL;

void server_init() {
	the_bank = bank_new();
}

void server_clean() {
	bank_free(the_bank);
	the_bank = NULL;
}

void server_send(int sock, struct sockaddr_in csin, char* msg) {
	sendto(sock, msg, strlen(msg), 0, (struct sockaddr*)&csin, sizeof(csin));
}

void server_send_account_status(int sock, struct sockaddr_in csin, bank_account* account) {
	char msg[100];
	sprintf(msg, "success,%d,%d\n", account->id, account->amount);
	server_send(sock, csin, msg);
}

error_t server_handle(int sock, struct sockaddr_in csin, char *data, int data_len) {
	int args_len;
	int id, amount;
	char **args;
	
	printf("RECV %s\n", data);

	args = str_split(data, 0, data_len - 1, ',', &args_len);

	if (args_len == 1 && strcmp(args[0], "create") == 0) {
		return server_handle_create(sock, csin);
  } else if (args_len == 3 && strcmp(args[0], "deposit") == 0) {
		id = atoi(args[1]);
		amount = atoi(args[2]);
		return server_handle_deposit(sock, csin, id, amount);
  } else if (args_len == 3 && strcmp(args[0], "withdraw") == 0) {
		id = atoi(args[1]);
		amount = atoi(args[2]);
		return server_handle_withdraw(sock, csin, id, amount);
  } else if (args_len == 2 && strcmp(args[0], "query") == 0) {
		id = atoi(args[1]);
		return server_handle_query(sock, csin, id);
  }

	if (args_len >= 1) {
		printf("Unknown action `%s'.\n", args[0]);
  } else {
		printf("Unknown action `%s'.\n", data);
  }
	return 0;
}

error_t server_handle_create(int sock, struct sockaddr_in csin) {
	bank_account* acc = bank_create_account(the_bank);
	server_send_account_status(sock, csin, acc);
	return 0;
}

error_t server_handle_deposit(int sock, struct sockaddr_in csin, int id, int amount) {
	if (amount < 0) {
		server_send(sock, csin, "error,amount_negative\n");
		return 0;
	}

	bank_account* acc = bank_get_account(the_bank, id);

	if (acc == NULL) {
		server_send(sock, csin, "error,not_found\n");
		return 0;
  }

	acc->amount += amount;
	server_send_account_status(sock, csin, acc);

	return 0;
}

error_t server_handle_withdraw(int sock, struct sockaddr_in csin, int id, int amount) {
	if (amount < 0) {
		server_send(sock, csin, "error,amount_negative\n");
		return 0;
  }

	bank_account* acc = bank_get_account(the_bank, id);

	if (acc == NULL) {
		server_send(sock, csin, "error,not_found\n");
		return 0;
  }

	if (amount > acc->amount) {
		server_send(sock, csin, "error,amount_too_high\n");
		return 0;
	}

	acc->amount -= amount;
	server_send_account_status(sock, csin, acc);

	return 0;
}

error_t server_handle_query(int sock, struct sockaddr_in csin, int id) {
	bank_account* acc = bank_get_account(the_bank, id);
	server_send_account_status(sock, csin, acc);
	return 0;
}
