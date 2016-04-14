#include <zmq.h>
#include <stdlib.h>

#include "../zhelpers.h"

int main(int argc, char const *argv[])
{
	printf("I'm a client.\n");

	void *context = zmq_ctx_new();
	void *requester = zmq_socket(context, ZMQ_REQ);
	zmq_connect(requester, "tcp://localhost:5559");

	for (int i = 0; i < 10; i++) {
		s_send(requester, "Hello");

		sleep(1);

		char *str = s_recv(requester);
		printf("Receive reply: %s\n", str);
		free(str);
	}

	zmq_close(requester);
	zmq_ctx_destroy(context);
	return 0;
}