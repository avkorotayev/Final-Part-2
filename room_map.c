#include "room_map.h"
#include <string.h>

static Room rooms[MAX_ROOMS];

void init_rooms() {
    rooms[0].id = 0;
    strcpy(rooms[0].name, "Ancient Hall");
    strcpy(rooms[0].description, "You are in a dark hall with mossy walls.");
    rooms[0].north = 1; rooms[0].south = -1; rooms[0].east = -1; rooms[0].west = -1;

    rooms[1].id = 1;
    strcpy(rooms[1].name, "Crystal Cave");
    strcpy(rooms[1].description, "Crystals glow faintly from the cave walls.");
    rooms[1].south = 0;
}

Room* get_room(int id) {
    if (id >= 0 && id < MAX_ROOMS) return &rooms[id];
    return NULL;
}

Room* move(int current_id, char dir) {
    Room* r = get_room(current_id);
    if (!r) return NULL;
    int next = -1;
    switch (dir) {
        case 'N': next = r->north; break;
        case 'S': next = r->south; break;
        case 'E': next = r->east;  break;
        case 'W': next = r->west;  break;
    }
    return get_room(next);
}
