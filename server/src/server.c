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

void server_send(client_t c, char* msg) {
  client_send(c, msg, strlen(msg));
}

void server_send_account_status(client_t c, bank_account* account) {
  char msg[100];
  sprintf(msg, "success,%d,%s,%s,%d\n", account->id, account->infos.name,
                                        account->infos.firstname,
                                        account->amount);
  server_send(c, msg);
}

error_t server_handle(client_t c, char *data, int data_len) {
  int args_len;
  int id, from, to, amount;
  char **args;
  
  printf("RECV %s\n", data);

  args = str_split(data, 0, data_len - 1, ',', &args_len);

  if (args_len == 3 && strcmp(args[0], "create") == 0) {
    return server_handle_create(c, args[1], args[2]);
  } else if (args_len == 3 && strcmp(args[0], "deposit") == 0) {
    id     = atoi(args[1]);
    amount = atoi(args[2]);
    return server_handle_deposit(c, id, amount);
  } else if (args_len == 3 && strcmp(args[0], "withdraw") == 0) {
    id     = atoi(args[1]);
    amount = atoi(args[2]);
    return server_handle_withdraw(c, id, amount);
  } else if (args_len == 2 && strcmp(args[0], "query") == 0) {
    id = atoi(args[1]);
    return server_handle_query(c, id);
  } else if (args_len == 4 && strcmp(args[0], "transfer") == 0) {
    from   = atoi(args[1]);
    to     = atoi(args[2]);
    amount = atoi(args[3]);
    return server_handle_transfer(c, from, to, amount);
  } else if (args_len == 4 && strcmp(args[0], "infos") == 0) {
    id = atoi(args[1]);
    return server_handle_infos(c, id, args[2], args[3]);
  }

  if (args_len >= 1) {
    printf("Unknown action `%s'.\n", args[0]);
  } else {
    printf("Unknown action `%s'.\n", data);
  }
  return 0;
}

error_t server_handle_create(client_t c, char* name, char* firstname) {
  bank_account* acc = bank_create_account(the_bank);
  strcpy(acc->infos.name, name);
  strcpy(acc->infos.firstname, firstname);
  server_send_account_status(c, acc);
  return 0;
}

error_t server_handle_deposit(client_t c, int id, int amount) {
  if (amount < 0) {
    server_send(c, "error,amount_negative\n");
    return 0;
  }

  bank_account* acc = bank_get_account(the_bank, id);

  if (acc == NULL) {
    server_send(c, "error,not_found\n");
    return 0;
  }

  acc->amount += amount;
  server_send_account_status(c, acc);

  return 0;
}

error_t server_handle_withdraw(client_t c, int id, int amount) {
  if (amount < 0) {
    server_send(c, "error,amount_negative\n");
    return 0;
  }

  bank_account* acc = bank_get_account(the_bank, id);

  if (acc == NULL) {
    server_send(c, "error,not_found\n");
    return 0;
  }

  if (amount > acc->amount) {
    server_send(c, "error,amount_too_high\n");
    return 0;
  }

  acc->amount -= amount;
  server_send_account_status(c, acc);

  return 0;
}

error_t server_handle_query(client_t c, int id) {
  bank_account* acc = bank_get_account(the_bank, id);
  if (acc == NULL) {
    server_send(c, "error,not_found,from\n");
    return 0;
  }
  server_send_account_status(c, acc);
  return 0;
}

error_t server_handle_transfer(client_t c, int a, int b, int amount) {
  if (amount < 0) {
    server_send(c, "error,amount_negative\n");
    return 0;
  }

  bank_account *from = bank_get_account(the_bank, a),
               *to   = bank_get_account(the_bank, b);

  if (from == NULL) {
    server_send(c, "error,not_found,from\n");
    return 0;
  }
  if (to == NULL) {
    server_send(c, "error,not_found,to\n");
    return 0;
  }

  if (amount > from->amount) {
    server_send(c, "error,amount_too_high\n");
    return 0;
  }

  from->amount -= amount;
  to->amount   += amount;

  server_send_account_status(c, from);

  return 0;
}

error_t server_handle_infos(client_t c, int id, char* name, char* firstname) {
  bank_account* acc = bank_get_account(the_bank, id);
  if (acc == NULL) {
    server_send(c, "error,not_found\n");
    return 0;
  }

  bank_account_infos infos;
  strcpy(infos.name, name);
  strcpy(infos.firstname, firstname);

  acc->infos = infos;
  server_send_account_status(c, acc);

  return 0;
}
