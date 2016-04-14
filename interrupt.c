// Signal handling

#include <signal.h>
#include <stdio.h>
#include <zmq.h>


static int s_interrupted;

static void s_signal_handler() {
    s_interrupted = 1;
}

static void s_catch_signal(void) {
    struct sigaction action;
    action.sa_handler = s_signal_handler;
    action.sa_flags = 0;
    sigemptyset(&action.sa_mask);
    sigaction (SIGINT, &action, NULL);
    sigaction (SIGTERM, &action, NULL);
}


int main() {
    void *context = zmq_ctx_new();
    void *socket = zmq_socket(context, ZMQ_REP);
    zmq_bind(socket, "tcp://*:5555");

    s_catch_signal();
    while (1) {
        zmq_msg_t msg;
        zmq_msg_init(&msg);
        zmq_msg_recv(&msg, socket, 0);

        if (s_interrupted){
            printf("\nShutting down ...\n");
            break;
        }
    }
    zmq_close(socket);
    zmq_ctx_destroy(context);
    return 0;
}