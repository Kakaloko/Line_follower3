#ifndef ENGINE_H
#define ENGINE_H

typedef struct {
	unsigned int dir1;
	unsigned int dir2;
	unsigned int pwm;
} Engine;

Engine engine_init(unsigned int dir1, unsigned int dir2, unsigned int pwm);
void engine_set_speed(Engine engine, float speed);

#endif
