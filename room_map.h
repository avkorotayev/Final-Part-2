#ifndef ROOM_MAP_H
#define ROOM_MAP_H
#define MAX_ROOMS 40
#define MAX_DESC  256

typedef struct {
    int id;
    char name[32];
    char description[MAX_DESC];
    int north, south, east, west;
} Room;

void init_rooms();
Room* get_room(int id);
Room* move(int current_id, char direction);

#endif
