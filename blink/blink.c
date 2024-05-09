/*
 * LED blink with FreeRTOS
 */

#include <FreeRTOS.h>
#include <task.h>
#include <stdio.h>
#include "pico/stdlib.h"
#include "include/blink.h"
#include "../msgqueue/msgqueue.h"

void led_task(void *p)
{
    struct led_task_arg *a = (struct led_task_arg *)p;

    gpio_init(a->gpio);
    gpio_set_dir(a->gpio, GPIO_OUT);
    NODE * tmp;
    while (!isEmpty(a->pq)) {
		    tmp = Dequeue(a->pq);
		    if (tmp->data.msg_t == ledMsg){
			    if (tmp->data.msgdest_t == task2)
			    {
				    gpio_put(a->gpio, 1);
				    vTaskDelay(pdMS_TO_TICKS(a->delay));
				    gpio_put(a->gpio, 0);
				    vTaskDelay(pdMS_TO_TICKS(a->delay));
			    }
		}
		Enqueue(a->pq, tmp);
    }
}

