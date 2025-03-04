#include <stdio.h>
#include <pico/stdlib.h>

#include "engine.h"

int main(void)
{
	stdio_init_all();

	gpio_init(25);
	gpio_set_dir(25, true);

	Engine e = engine_init(17, 18, 16);

	while(1)
	{
		gpio_put(25, 1);
		engine_set_speed(e, 1.0);
		sleep_ms(1000);
		engine_set_speed(e, 0.5);
		sleep_ms(1000);
		engine_set_speed(e, 0);
		sleep_ms(1000);
		gpio_put(25, 1);
		engine_set_speed(e, -1.0);
		sleep_ms(1000);
		engine_set_speed(e, -0.5);
		sleep_ms(1000);
		engine_set_speed(e, 0);
		sleep_ms(1000);
	}
}


