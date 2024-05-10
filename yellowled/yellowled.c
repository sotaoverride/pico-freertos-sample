/*
 * LED blink with FreeRTOS
 */

#include <FreeRTOS.h>
#include <task.h>
#include <stdio.h>
#include "pico/stdlib.h"
#include"../common/led_task.h"
#include "../msgqueue/msgqueue.h"

void yellow_led_task(void *p)
{
	struct led_task_arg *a = (struct led_task_arg *)p;

	gpio_init(a->gpio);
	gpio_set_dir(a->gpio, GPIO_OUT);
	NODE * tmp;
	while (1) {
		ping_pong(a, yellowledtaskdest);
	}
}




