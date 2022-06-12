//
// Created by mat on 6/11/2022.
//

#ifndef PONG_CLONE_GAME_H
#define PONG_CLONE_GAME_H

#include "player.h"
#include "ball.h"
#include "../util/list.h"

typedef struct {
    LIST *players;
    LIST *balls;
} GAME;

/**
 * Starts a game session
 *
 * @param game game that you want to start the session for
 * @param player_count amount of players that will play
 */

void game_start(GAME *game);

/**
 * Adds a player to the game
 *
 * @param game game that you want to add player to
 * @param padding horizontal padding
 * @param key_up key that when pressed will move the player up
 * @param key_down key that when pressed will move the player down
 */

void game_add_player(GAME *game, float padding, int key_up, int key_down);

/**
 * Renders the players in game to the screen
 *
 * @param game game that you want to render
 * @param time_step time since the last render call
 */

void game_render_players(GAME *game, float time_step);

/**
 * Adds a ball to the game
 *
 * @param game game that you want to add the ball to
 */

void game_add_ball(GAME *game);

/**
 * Renders the balls in the game screen
 *
 * @param game game that you want to render
 * @param time_step time since the last render call
 */

void game_render_balls(GAME *game, float time_step);

/**
 * Checks for any collision
 */

void game_check_collisions(GAME *game);

/**
 * Stops the game session
 *
 * @param game game that you want to stop the session for
 */

void game_stop(GAME *game);

#endif //PONG_CLONE_GAME_H
