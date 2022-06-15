//
// Created by mat on 6/12/2022.
//

#ifndef PONG_CLONE_MATH_H
#define PONG_CLONE_MATH_H

#define _USE_MATH_DEFINES

#include <math.h>

#define MIN(a, b) (((a)<(b))?(a):(b))
#define MAX(a, b) (((a)>(b))?(a):(b))

/**
 * Converts angle to radians
 *
 * @param ang angle that you want to convert
 * @return angle in radians
 */

float math_rad(float ang);

/**
 * Maps a value to a range
 *
 * @param value value that you want to map
 * @param from minimum of the value
 * @param to maximum of the value
 * @param min min of the range
 * @param max max of the range
 * @return value from min to max based on the value
 */

float math_map_float(float value, float from, float to, float min, float max);

#endif //PONG_CLONE_MATH_H
