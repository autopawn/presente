#include "level.h"

#include <stdlib.h>
#include <assert.h>

level *level_new(int size_x, int size_y){
    // Ask memory for the level struct
    level *lvl = malloc(sizeof(level));

    // Set the size
    lvl->size_x = size_x;
    lvl->size_y = size_y;

    // Ask memory for the cell* array
    lvl->cells  = malloc(lvl->size_y * sizeof(char *));

    // Ask memory for each column
    for(int y=0;y<lvl->size_y;y++){
        lvl->cells[y] = malloc(lvl->size_x * sizeof(char));
    }

    // Initialize level
    for(int y=0;y<lvl->size_y;y++){
        for(int x=0;x<lvl->size_x;x++){
            lvl->cells[y][x] = '.';
        }
    }

    return lvl;
}

int level_get(const level *lvl, int x, int y){
    if(x<0) return '#';
    if(y<0) return '#';
    if(x>=lvl->size_x) return '#';
    if(y>=lvl->size_y) return '#';
    return lvl->cells[y][x];
}

void level_fill_random(level *lvl, int wall_size){
    assert(wall_size<lvl->size_x);
    assert(wall_size<lvl->size_y);
    int n_walls = lvl->size_x*lvl->size_y/wall_size/10;
    for(int i=0;i<n_walls;i++){
        int vert = rand()%2;
        if(vert){
            int wx = rand()%(lvl->size_x);
            int wy = rand()%(lvl->size_y-wall_size);
            for(int k=0;k<wall_size;k++){
                lvl->cells[wy+k][wx] = '#';
            }
        }else{
            int wx = rand()%(lvl->size_x-wall_size);
            int wy = rand()%(lvl->size_y);
            for(int k=0;k<wall_size;k++){
                lvl->cells[wy][wx+k] = '#';
            }
        }
    }
}

// Free level memory
void level_free(level *lvl){
    for(int y=0;y<lvl->size_y;y++){
        free(lvl->cells[y]);
    }
    free(lvl->cells);
    free(lvl);
}
