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
		if (isEmpty(a->yellowq)) {
			taskYIELD();
		}
		tmp = Dequeue(a->yellowq);
		if (tmp->data.msg_t == ledMsg){

			if (tmp->data.msgdest_t == yellowledtaskdest)

			{
				gpio_put(a->gpio, 1);
				vTaskDelay(pdMS_TO_TICKS(a->delay));
				gpio_put(a->gpio, 0);
				vTaskDelay(pdMS_TO_TICKS(a->delay));
				if (tmp->data.msgorigin_t = redledtaskorigin) {
					tmp->data.msgdest_t = redledtaskdest;
					tmp->data.msgorigin_t = yellowledtaskorigin;
					Enqueue(a->redq, tmp);
				}
				else if (tmp->data.msgorigin_t = greenledtaskorigin) {
					tmp->data.msgdest_t = greenledtaskdest;
					tmp->data.msgorigin_t = redledtaskorigin;
					Enqueue(a->greenq, tmp);
				}


			}
		}
	}
}




