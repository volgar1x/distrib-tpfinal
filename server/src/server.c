#include <stdio.h>

#include "server.h"

error_t server_handle(char *data) {
	printf("RECV %s\n", data);

	return 0;
}
