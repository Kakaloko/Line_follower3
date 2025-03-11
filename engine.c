#include <pico/stdlib.h>
#include <hardware/pwm.h>
#include <stdlib.h>
#include "engine.h"

Engine engine_init(unsigned int dir1, unsigned int dir2, unsigned int pwm)
{
	Engine e = {dir1, dir2, pwm};

	gpio_init(dir1);
	gpio_init(dir2);

	gpio_set_dir(dir1, true);
	gpio_set_dir(dir2, true);

	gpio_set_function(pwm, GPIO_FUNC_PWM);
	uint slice_num = pwm_gpio_to_slice_num(pwm);

	pwm_set_wrap(slice_num, 999);
	pwm_set_clkdiv(slice_num, 125);

	engine_set_speed(e, 0.0f);

	pwm_set_enabled(slice_num, true);

	return e;
}

void engine_set_speed(Engine engine, float speed)
{
	if (speed < 0)
	{
		gpio_put(engine.dir1, 1);
		gpio_put(engine.dir2, 0);
	}
	else if (speed > 0)
	{
		gpio_put(engine.dir1, 0);
		gpio_put(engine.dir2, 1);
	}
	else
	{
		gpio_put(engine.dir1, 0);
		gpio_put(engine.dir2, 0);
	}

	pwm_set_gpio_level(engine.pwm, abs((int)(10000*speed)));
}

