#ifndef ENTITY_H
#define ENTITY_H

#include "level.h"

typedef struct {
    float x,y;
    float vx,vy;
    int rad;
    int hp;
    int dead;
} entity;

int entity_physics(const level *lvl, entity *ent);

int entity_collision(const entity *ent1, const entity *ent2);

#endif
