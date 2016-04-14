//
// Created by 骚铭科技 on 16/4/14.
//

#include "../zhelpers.h"

int main() {
    void *context = zmq_ctx_new();
    assert(context);

    // Control socket
    void *control = zmq_socket(context, ZMQ_PUB);
    assert(control);
    zmq_bind(control, "tcp://*:5559");

    // Sink receiver soket
    void *receiver = zmq_socket(context, ZMQ_PULL);
    assert(receiver);
    int rc = zmq_bind(receiver, "tcp://*:5558");
    if (rc != 0) {
        printf("E: Bind failed: %s!\n", zmq_strerror(zmq_errno()));
        return -1;
    }

    // Waiting for START signal to start batch
    char *str = s_recv (receiver);
    printf("Start batch ...\n");
    free(str);

    // Record start time
    int64_t start_time = s_clock();

    int task_nbr;
    for (task_nbr = 0; task_nbr < 100; task_nbr++) {
        char *str = s_recv(receiver);
        printf(".");
        fflush(stdout);
        free(str);
    }

    printf("Total using time: %d msec\n", (int)(s_clock() - start_time));

    s_send(control, "KILL");

    zmq_close(receiver);
    zmq_ctx_destroy(context);
    return 0;
}