#ifndef ROBOT_H
#define ROBOT_H

#include "common.h"
#include "engine.h"

typedef struct {
	Engine engine_l;
	Engine engine_r;

	float speed;
	float turn;
} Robot;

void robot_init_engines(Robot *robot, uint dir1_l, uint dir2_l, uint pwm_l, uint dir1_r, uint dir2_r, uint pwm_r);
void robot_set_speed(Robot *robot, float speed);
void robot_set_turn(Robot *robot, float turn);

#endif
