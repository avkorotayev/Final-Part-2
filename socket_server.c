#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "mqtt_utils.h"
#include "room_map.h"

#define PORT 12345
#define BUF_SIZE 64

typedef struct {
    char id[16];
    int current_room;
} Player;

Player players[10];

int find_or_create_player(const char* id) {
    for (int i = 0; i < 10; i++) {
        if (strcmp(players[i].id, id) == 0)
            return i;
        if (players[i].id[0] == '\0') {
            strcpy(players[i].id, id);
            players[i].current_room = rand() % 2;
            return i;
        }
    }
    return -1;
}

void start_socket_server() {
    int sockfd;
    struct sockaddr_in servaddr, cliaddr;
    char buffer[BUF_SIZE];

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));

    while (1) {
        socklen_t len = sizeof(cliaddr);
        memset(buffer, 0, BUF_SIZE);
        recvfrom(sockfd, buffer, BUF_SIZE, 0, (struct sockaddr*)&cliaddr, &len);

        char id[16], dir;
        sscanf(buffer, "%[^:]:%c", id, &dir);

        int idx = find_or_create_player(id);
        Room* next = move(players[idx].current_room, dir);
        if (next) players[idx].current_room = next->id;

        Room* cur = get_room(players[idx].current_room);
        mqtt_send(cur->description);
    }
}
