#include "bank.h"

#include <stdlib.h>

bank* bank_new() {
	bank* bank;

	bank = (bank*) malloc(sizeof(bank));
	bank->hd = bank->tl = NULL;

	return bank
}

void bank_free(bank* bank) {
	bank_account *it = bank->hd, *cur;
	while (it != NULL) {
		cur = it;
		it = it->next;
		free(cur);
  }

	free(bank);
}

bank_account* bank_create_account(bank* bank) {
	int          id;
	bank_account *acc;

	acc = (bank_account*) malloc(sizeof(bank_account));
	acc->amount = 0;
	acc->next   = NULL;

	if (bank->tl != NULL) {
		acc->id        = bank->tl->id + 1;
		bank->tl->next = acc;
		bank->tl       = acc;
  } else {
		acc->id  = 1;
		bank->hd = bank->tl = acc;
  }

	return acc;
}

bank_account* bank_get_account(bank* bank, int id) {
	bank_account *it;

	for (it = bank->hd; it != NULL; it = it->next) {
		if (it->id == id) {
    	return it;
		}
  }

	return NULL;
}
