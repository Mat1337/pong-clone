//
// Created by mat on 6/12/2022.
//

#ifndef PONG_CLONE_BALL_H
#define PONG_CLONE_BALL_H

#define BALL_RADIUS 10

#include <math.h>

#include "player.h"
#include "../util/rand.h"
#include "../util/box.h"
#include "../graphics/render.h"

typedef struct {
    BOX box;
    PLAYER *last_hit;

    float vel_x;
    float vel_y;
} BALL;

/**
 * Renders the ball onto the screen
 *
 * @param ball ball that you want to render
 * @param time_step time since last render call
 */

void ball_render(BALL *ball, float time_step);

/**
 * Resets the ball data
 *
 * @param ball ball that you want to reset
 * @param width width of the screen
 * @param height height of the screen
 */

void ball_reset(BALL *ball, float width, float height);

#endif //PONG_CLONE_BALL_H
