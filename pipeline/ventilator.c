//
// Created by 骚铭科技 on 16/4/14.
//

#include "../zhelpers.h"

int main() {
    void *context = zmq_ctx_new();

    // PUSH port
    void *sender  = zmq_socket(context, ZMQ_PUSH);
    zmq_bind(sender, "tcp://*:5557");

    // Connect sink
    void *sink = zmq_socket(context, ZMQ_PUSH);
    zmq_connect(sink, "tcp://localhost:5558");

    printf("Press Enter when the workers are ready:");
    getchar();
    printf("Sending tasks to Workers ...\n");

    s_send(sink, "0");

    int task_nbr;
    int total_msec = 0;
    for (task_nbr = 0; task_nbr < 100; task_nbr++) {
        int workload = 50;
        total_msec += workload;
        char str[10];
        sprintf(str, "%d", workload);
        s_send(sender, str);
    }
    printf("Total expected cost: %d msec\n", total_msec);
    s_sleep(1);

    zmq_close(sink);
    zmq_close(sender);
    zmq_ctx_destroy(context);
    return 0;
}