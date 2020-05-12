#ifndef DRAW_H
#define DRAW_H

#include "level.h"
#include "state.h"

// Draws the cells of the level in the screen
void draw_level(const level *lvl);

// Draws the whole state and the level in the screen
void draw_state(const level *lvl, const state *sta);

#endif
