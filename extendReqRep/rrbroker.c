#include <zmq.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
	printf("I'm a broker.\n");

	void *context = zmq_ctx_new();

	void *frontend = zmq_socket(context, ZMQ_ROUTER);
	void *backend  = zmq_socket(context, ZMQ_DEALER);
	zmq_bind(frontend, "tcp://*:5559");
	zmq_bind(backend,  "tcp://*:5560");

	zmq_proxy(frontend, backend, NULL);

	zmq_close(frontend);
	zmq_close(backend);
	zmq_ctx_destroy(context);
	return 0;
}