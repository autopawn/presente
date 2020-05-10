#include "state.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>

state *state_new(){
    // Ask for memory for the state
    state *sta = malloc(sizeof(state));

    // Fill every byte in the state with 0's so that effectivelly each field is set to 0.
    // (this is a trick from <string.h>)
    memset(sta,0,sizeof(state));

    // We put the player in the center of the top-left cell.
    sta->pla.ent.x = TILE_SIZE/2;
    sta->pla.ent.y = TILE_SIZE/2;
    sta->pla.ent.rad = PLAYER_RAD;
    sta->pla.ent.hp  = PLAYER_HP;

    // Retrieve pointer to the state
    return sta;
}

void state_update(level *lvl, state *sta){

    // == Update player speed according to buttons
    // (mov_x,mov_y) is a vector that represents the position of the analog control
    float mov_x = 0;
    float mov_y = 0;
    mov_x += sta->button_state[0];
    mov_x -= sta->button_state[2];
    mov_y -= sta->button_state[1];
    mov_y += sta->button_state[3];
    float mov_norm = sqrt(mov_x*mov_x+mov_y*mov_y);

    if(mov_norm==0 || sta->pla.ent.dead){
        // If nothing is being pressed, deacelerate the player
        sta->pla.ent.vx *= 0.6;
        sta->pla.ent.vy *= 0.6;
    }else{
        // If something is being pressed, normalize the mov vector and multiply by the PLAYER_SPEED
        sta->pla.ent.vx = mov_x/mov_norm * PLAYER_SPEED;
        sta->pla.ent.vy = mov_y/mov_norm * PLAYER_SPEED;
    }

    // == Make the player shoot
    // Lower the player's cooldown by 1
    sta->pla.cooldown -= 1;
    // If the shoot button is pressed and the player cooldown is smaller than 0, shoot a bullet
    if(sta->button_state[4] && sta->pla.cooldown<=0 && !sta->pla.ent.dead){
        // Reset the player cooldown to a positive value so that he can't shoot for that amount of frames
        sta->pla.cooldown = PLAYER_COOLDOWN;
        // Ensure that the new bullet won't be created if that would overflow the bullets array
        if(sta->n_bullets<MAX_BULLETS){
            // The new bullet will be in the next unused position of the bullets array
            bullet *new_bullet = &sta->bullets[sta->n_bullets];
            sta->n_bullets += 1;
            // Initialize all bullet fields to 0
            memset(new_bullet,0,sizeof(bullet));
            // Start the bullet on the player's position
            new_bullet->ent.x      = sta->pla.ent.x;
            new_bullet->ent.y      = sta->pla.ent.y;
            // Bullet speed is set to the aiming angle
            new_bullet->ent.vx     =  BULLET_SPEED*cos(sta->aim_angle);
            new_bullet->ent.vy     = -BULLET_SPEED*sin(sta->aim_angle);
            //
            new_bullet->ent.rad    = BULLET_RAD;
            new_bullet->ent.hp     = BULLET_DMG;
        }
    }

    // == Check bullet-enemy collisions
    for(int i=0;i<sta->n_bullets;i++){
        for(int k=0;k<sta->n_enemies;k++){
            // If a bullet is colliding with an enemy
            if(entity_collision(&sta->bullets[i].ent,&sta->enemies[k].ent)){
                // Reduce enemy's health by bullet's health and kill bullet
                sta->enemies[k].ent.hp -= sta->bullets[i].ent.hp;
                sta->bullets[i].ent.dead = 1;
            }
        }
    }

    // == Update entities
    // Update player
    entity_physics(lvl,&sta->pla.ent);
    if(sta->pla.ent.hp<=0) sta->pla.ent.dead=1;
    // Update enemies
    for(int i=0;i<sta->n_enemies;i++){
        entity_physics(lvl,&sta->enemies[i].ent);
        // Kill enemy if it has less than 0 HP
        if(sta->enemies[i].ent.hp<=0) sta->enemies[i].ent.dead = 1;
    }
    // Update bullets
    for(int i=0;i<sta->n_bullets;i++){
        int col = entity_physics(lvl,&sta->bullets[i].ent);
        // Kill bullet if it is colliding with a wall
        if(col) sta->bullets[i].ent.dead = 1;
    }


    // == Delete dead entities
    {
        // We filter the bullets array, moving each surviving bullet to the position it would have on a filtered array
        int new_n_bullets = 0;
        for(int i=0;i<sta->n_bullets;i++){
            if(!sta->bullets[i].ent.dead){
                sta->bullets[new_n_bullets] = sta->bullets[i];
                new_n_bullets += 1;
            }
        }
        // Update the number of bullets
        sta->n_bullets = new_n_bullets;
    }

    {
        // We filter the enemy array, moving each surviving enemy to the position it would have on a filtered array
        int new_n_enemies = 0;
        for(int i=0;i<sta->n_enemies;i++){
            if(!sta->enemies[i].ent.dead){
                sta->enemies[new_n_enemies] = sta->enemies[i];
                new_n_enemies += 1;
            }
        }
        // Update the number of enemies
        sta->n_enemies = new_n_enemies;
    }

}

void state_populate_random(level *lvl, state *sta, int n_enemies){
    assert(n_enemies<=MAX_ENEMIES);
    while(sta->n_enemies<n_enemies){
        // Until an empty cell is found, Las Vegas algorithm approach.
        while(1){
            int posx = rand()%lvl->size_x;
            int posy = rand()%lvl->size_y;
            // Check if the cell is empty
            if(level_get(lvl,posx,posy)=='.'){

                // The new enemy will be in the next unused position of the enemies array
                enemy *new_enemy = &sta->enemies[sta->n_enemies];
                sta->n_enemies++;

                // Initialize all new enemy fields to 0
                memset(new_enemy,0,sizeof(enemy));

                // Put the new enemy at the center of the chosen cell
                new_enemy->ent.x = (posx+0.5)*TILE_SIZE;
                new_enemy->ent.y = (posy+0.5)*TILE_SIZE;
                // Pick an enemy tipe and set variables accordingly
                int brute = rand()%4==0; // brute has 1/4 chance.
                if(brute){
                    new_enemy->kind   = BRUTE;
                    new_enemy->ent.hp = BRUTE_HP;
                    new_enemy->ent.rad = BRUTE_RAD;
                }else{
                    new_enemy->kind   = MINION;
                    new_enemy->ent.hp = MINION_HP;
                    new_enemy->ent.rad = MINION_RAD;
                }
                // Break while(1) as the operation was successful
                break;
            }
        }
    }
}

void state_free(state *sta){
    free(sta);
}
