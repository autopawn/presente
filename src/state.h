#ifndef STATE_H
#define STATE_H

#include "entity.h"

#define PLAYER_HP  10
#define PLAYER_RAD 10
#define PLAYER_SPEED 4
#define PLAYER_COOLDOWN 8

#define MINION_HP   4
#define MINION_RAD 12
#define BRUTE_HP   12
#define BRUTE_RAD  16

#define BULLET_DMG 3
#define BULLET_SPEED 16
#define BULLET_RAD   5


// ==== PLAYER DEFINITION
typedef struct {
    entity ent;
    int cooldown;
} player;

// ==== ENEMY DEFINITION
typedef enum {MINION=0, BRUTE=1} enemykind;

typedef struct {
    entity ent;
    enemykind kind;
} enemy;

// ==== BULLET DEFINTION

typedef struct {
    entity ent;
    // more things?
} bullet;

// ==== STATE DEFINITION

#define MAX_ENEMIES 128
#define MAX_BULLETS 128

#define N_BUTTONS 5

typedef struct {
    player pla;

    int n_enemies;
    enemy enemies[MAX_ENEMIES];

    int n_bullets;
    bullet bullets[MAX_BULLETS];

    // Controls
    int button_state[N_BUTTONS];
    float aim_angle;

} state;

state *state_new();

void state_update(level *lvl, state *sta);

void state_populate_random(level *lvl, state *sta, int n_enemies);

void state_free(state *sta);



#endif
