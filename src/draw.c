#include "draw.h"

#include <raylib.h>

void draw_level(const level *lvl){
    // Draw cells
    for(int y=-1;y<=lvl->size_y;y++){
        for(int x=-1;x<=lvl->size_x;x++){
            char cell = level_get(lvl,x,y);
            if(cell=='#'){
                DrawRectangle(TILE_SIZE*x,TILE_SIZE*y,TILE_SIZE,TILE_SIZE,BROWN);
            }
        }
    }
}

void draw_state(const level *lvl, const state *sta){

    Camera2D cam;
    cam.target.x = sta->pla.ent.x;
    cam.target.y = sta->pla.ent.y;
    cam.rotation = 0.0;
    cam.offset.x = GetScreenWidth()/2.0;
    cam.offset.y = GetScreenHeight()/2.0;
    cam.zoom = 1.0;

    BeginMode2D(cam);

    // Draw level
    draw_level(lvl);

    // Draw enemies
    for(int i=0;i<sta->n_enemies;i++){
        entity ent = sta->enemies[i].ent;
        Vector2 vec = {ent.x,ent.y};
        if(sta->enemies[i].kind == MINION){
            DrawCircleV(vec,ent.rad,YELLOW);
        }else{
            DrawCircleV(vec,ent.rad,RED);
        }
    }

    // Draw player
    {
        entity ent = sta->pla.ent;
        Vector2 vec = {ent.x,ent.y};
        DrawCircleV(vec,ent.rad,BLUE);
    }

    // Draw bullets
    for(int i=0;i<sta->n_bullets;i++){
        entity ent = sta->bullets[i].ent;
        Vector2 vec = {ent.x,ent.y};
        DrawCircleV(vec,ent.rad,PINK);
    }

    EndMode2D();
}
