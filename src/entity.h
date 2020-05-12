#ifndef ENTITY_H
#define ENTITY_H

#include "level.h"

// An entity represents the common part of all objects in the game
typedef struct {
    // position
    float x,y;
    // velocity
    float vx,vy;
    // radious
    int rad;
    // hit points (or damage)
    int hp;
    // if it is dead or not
    int dead;
} entity;

/* Updates the entity position according to its velocity.
It also should perform collision checking with the level cells.
Retrieves 1 if there is a collision.
*/
int entity_physics(const level *lvl, entity *ent);

// Checks if two entities are colliding, retrieving 1 in that case.
int entity_collision(const entity *ent1, const entity *ent2);

#endif
