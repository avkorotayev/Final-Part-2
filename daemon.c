#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "mqtt_utils.h"
#include "socket_server.h"
#include "room_map.h"

void* socket_thread(void* arg) {
    start_socket_server();
    return NULL;
}

int main() {
    daemon(1, 0);
    init_rooms();
    mqtt_setup();

    pthread_t t_socket;
    pthread_create(&t_socket, NULL, socket_thread, NULL);
    pthread_join(t_socket, NULL);
    return 0;
}
