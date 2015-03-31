#ifndef BANK_H
#define BANK_H

typedef struct {
  char name[255], firstname[255];
} bank_account_infos;

/**
 * `bank_account' is a struct representing an account.
 */
typedef struct __bank_account {
  int                id, amount;
  bank_account_infos infos;
  struct __bank_account *next;
} bank_account;

/**
 * `bank' is a struct representing a whole bank.
 */
typedef struct {
  bank_account *hd, *tl;
} bank;

/**
 * Create a new `bank'.
 */
bank* bank_new();

/**
 * Free the memory taken by a `bank'.
 */
void bank_free(bank* bank);

/**
 * Create an account and add it to the bank.
 */
bank_account* bank_create_account(bank* bank);

/**
 * Retrieve or create an account from the bank using its ID. Return NULL if not found.
 */
bank_account* bank_get_account(bank* bank, int id);

#endif//BANK_H
