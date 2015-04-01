#include "bank.h"
#include "util.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

bank* bank_new() {
  bank* the_bank;

  the_bank = (bank*) malloc(sizeof(bank));
  the_bank->hd = the_bank->tl = NULL;

  return the_bank;
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

int bank_size(bank* bank) {
	bank_account *it;
	int size = 0;
	for (it = bank->hd; it != NULL; it = it->next) {
		size++;
  }
	return size;
}

void bank_load(bank* bank, const char* filename) {
	FILE *file;
	char line[255], **args;
	int args_len;

	file = fopen(filename, "r");
	if (!file) {
		return;
  }

	while (fscanf(file, "%s", line) != EOF) {
		args = str_split(line, 0, strlen(line), ',', &args_len);

		bank_account* acc = (bank_account*) malloc(sizeof(bank_account));
		acc->id = atoi(args[0]);
		acc->amount = atoi(args[3]);
		strcpy(acc->infos.name, args[1]);
		strcpy(acc->infos.firstname, args[2]);

		printf("loaded %s's account\n", acc->infos.name);

		if (bank->tl == NULL) {
			bank->hd = bank->tl = acc;
    } else {
			bank->tl->next = acc;
			bank->tl = acc;
    }
  }

	fclose(file);

	printf("%d bank accounts\n", bank_size(bank));
}

void bank_save(bank* bank, const char* filename) {
	FILE *file;
	bank_account *it;

	file = fopen(filename, "w+");

	for (it = bank->hd; it != NULL; it = it->next) {
		fprintf(file, "%d,%s,%s,%d\n", it->id, it->infos.name, it->infos.firstname, it->amount);
  }

	fflush(file);
	fclose(file);
}

bank_account* bank_create_account(bank* bank) {
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
