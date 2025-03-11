#include "robot.h"
#include "engine.h"
#include "common.h"

static void _robot_apply_speed(Robot *robot);

void robot_init_engines(Robot *robot, uint dir1_l, uint dir2_l, uint pwm_l, uint dir1_r, uint dir2_r, uint pwm_r)
{
	robot->engine_l = engine_init(dir1_l, dir2_l, pwm_l);
	robot->engine_r = engine_init(dir1_r, dir2_r, pwm_r);
	
	robot->speed = 0.0f;
	robot->turn = 0.0f;
}

void robot_set_speed(Robot *robot, float speed)
{
	robot->speed = speed;
	_robot_apply_speed(robot);
}

void robot_set_turn(Robot *robot, float turn)
{
	robot->turn = turn;
	_robot_apply_speed(robot);
}

static void _robot_apply_speed(Robot *robot)
{
	float turn = robot->turn;
	float l_speed = robot->speed;
	float r_speed = robot->speed;
	if (turn < 0) 
	{
		r_speed = 1.0;
		l_speed = 1.0 - 2*turn;
	
	} 
	else if (turn > 0) 
	{
		r_speed = 1.0 - 2*turn;
		l_speed = 1.0;
	
	} 
	else
	{
		
		r_speed = 1.0;
		l_speed = 1.0;
	}
	r_speed *= robot->speed;
	l_speed *= robot->speed;

	//jeśli turn= 0 to na śilnikach bedzie taki sama prędkość
	engine_set_speed(robot->engine_l, l_speed);
	engine_set_speed(robot->engine_r, r_speed);
}

