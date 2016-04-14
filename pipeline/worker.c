//
// Created by 骚铭科技 on 16/4/14.
//

#include "../zhelpers.h"

int main() {
    void *context = zmq_ctx_new();

    void *receiver = zmq_socket(context, ZMQ_PULL);
    zmq_connect(receiver, "tcp://localhost:5557");

    void *sender = zmq_socket(context, ZMQ_PUSH);
    zmq_connect(sender, "tcp://localhost:5558");

    void *controller = zmq_socket(context, ZMQ_SUB);
    zmq_connect(controller, "tcp://localhost:5559");
    zmq_setsockopt(controller, ZMQ_SUBSCRIBE, "", 0);

    zmq_pollitem_t item[] = {
            {receiver, 0, ZMQ_POLLIN, 0},
            {controller, 0, ZMQ_POLLIN, 0}
    };

    while (1) {
        zmq_poll(item, 2, -1);
        if (item[0].revents & ZMQ_POLLIN) {
            char *str = s_recv(receiver);
            fflush(stdout);
            printf("%s.", str);

            s_sleep(atoi(str));
            free(str);

            s_send(sender, "");
        }

        if (item[1].revents & ZMQ_POLLIN) {
            printf("KILL Worker!\n");
            break;
        }
    }

    zmq_close(receiver);
    zmq_close(sender);
    zmq_close(controller);
    zmq_ctx_destroy(context);
    return 0;
}