#ifndef LEVEL_H
#define LEVEL_H

#define TILE_SIZE 48

/* A level is a matrix of cells, each cell is represented using chars.
'.' = free cells
'#' = walls
*/
typedef struct {
    int size_x, size_y;
    char **cells;
} level;

// Create a new level with the given size, allocates memory for it.
level *level_new(int size_x, int size_y);

// Retrieves the cell at a given position, can be used for cells outside the board.
int level_get(const level *lvl, int x, int y);

// Put randomly placed walls of the given size in the level.
void level_fill_random(level *lvl, int wall_size);

// Destroy a level, free its memory.
void level_free(level *lvl);


#endif
