#include "entity.h"

#include <math.h>

int entity_physics(const level *lvl, entity *ent){
    // Update position
    ent->x += ent->vx;
    ent->y += ent->vy;

    // Check if colliding
    int tile_x = (int) floor(ent->x/TILE_SIZE);
    int tile_y = (int) floor(ent->y/TILE_SIZE);
    char cell = level_get(lvl,tile_x,tile_y);

    if(cell=='#') return 1;
    return 0;
}

int entity_collision(const entity *ent1, const entity *ent2){
    if(ent1->dead || ent2->dead) return 0;

    float delta_x = ent1->x - ent2->x;
    float delta_y = ent1->y - ent2->y;

    float delta_mag = sqrt(delta_x*delta_x+delta_y*delta_y);

    return (delta_mag < ent1->rad + ent2->rad);
}
