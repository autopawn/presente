#ifndef LEVEL_H
#define LEVEL_H

#define TILE_SIZE 48

typedef struct {
    int size_x, size_y;
    char **cells;
} level;

level *level_new(int size_x, int size_y);

int level_get(const level *lvl, int x, int y);

void level_fill_random(level *lvl, int wall_size);

void level_free(level *lvl);


#endif
