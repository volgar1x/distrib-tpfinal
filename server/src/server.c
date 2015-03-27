/// @author Antoine CHAUVIN

#include <stdlib.h>

#include "server.h"
#include "config.h"
#include "util.h"

void server_handle(int sock, struct sockaddr* saddr) {
	server_handle_conn(sock, saddr);

	ssize_t n;

	void* buf     = malloc(BUF_LEN);
	void* tmp     = (void*)0;
	int   tmp_len = 0;
	
	for (;;) {
		n = recv(sock, buf, BUF_LEN, 0);

		if (n < 0) {
			/** We got an error. */
			perror("error receiving data from client");
			break;
    } else if (n == 0) {
			/** Client gracefully shut down its connection. */
			break;
    } else if (n < BUF_LEN) {
			/** We received all there is to receive. */

			void* data = malloc(tmp_len + n);

			/** Copy the tmp buffer back into the data */
			if (tmp != (void*)0) {
				util_memcpy(tmp, 0, data, 0, tmp_len);
      }
			/** Copy the actual buffer into the data */
			util_memcpy(buf, 0, data, tmp_len, n);

			/** Handle the data, at least. */
			server_handle_recv(sock, saddr, data);

			/** Clean up the memory. */
			if (tmp != (void*)0) {
				free(tmp);
				tmp = (void*)0;
				tmp_len = 0;
      }
			free(data);
    } else if (tmp != (void*)0) {
			/**
			 * We received more data than the buffer can remember
			 * Although we already have buffered data
			 * Merge the actual buffer and the tmp buffer into a new tmp buffer
			 */
			void* cpy = malloc(cpy_len);
			util_memcpy(tmp, 0, cpy, 0, tmp_len);
			util_memcpy(buf, 0, cpy, tmp_len, n);
			free(tmp); // free the old tmp buffer
			tmp = cpy;
			tmp_len += BUF_LEN;
		} else {
			/**
			 * We received more data than the buffer can remember
			 * Copy the buffer into a new temporary buffer
			 */
			tmp = malloc(BUF_LEN);
			util_memcpy(buf, 0, tmp, 0, BUF_LEN);
			tmp_len = BUF_LEN;
		}
  }
	
	server_handle_dcnn(sock, saddr, n);
	close(sock);

	if (tmp != (void*)0) {
		free(tmp);
  }
	free(buf);
}

void server_handle_recv(int sock, struct sockaddr* saddr, void* data) {
	// TODO: server_handle_recv
}

void server_handle_conn(int sock, struct sockaddr* saddr) {
	// TODO: server_handle_conn
}

void server_handle_dcnn(int sock, struct sockaddr* saddr, int last_payload) {
	// TODO: server_handle_dconn
}

