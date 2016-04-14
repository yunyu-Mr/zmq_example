#include <zmq.h>
#include <stdlib.h>

#include "../zhelpers.h"

int main(int argc, char const *argv[])
{
	printf("I'm a worker.\n");

	void *context = zmq_ctx_new();

	void *responder = zmq_socket (context, ZMQ_REP);
	zmq_connect(responder, "tcp://localhost:5560");

	while (1) {
		char *str = s_recv(responder);
		printf("Receive request: %s\n", str);
		free(str);

		sleep(1);

		s_send(responder, "World");
	}
	zmq_close(responder);
	zmq_ctx_destroy(context);
	return 0;
}