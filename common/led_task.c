#include <FreeRTOS.h>
#include <task.h>
#include <stdio.h>
#include "led_task.h"
#include "pico/stdlib.h"
#include "../msgqueue/msgqueue.h"
void ping_pong(struct led_task_arg * a, enum MsgDest_T dest){
	NODE * tmp;
	while (isEmpty(a->greenq)) {
		taskYIELD();
	}

		switch(dest) {
			case greenledtaskdest:
				tmp = Dequeue(a->greenq);
				if (tmp->data.msg_t == ledMsg){
			
					if (tmp->data.msgdest_t == greenledtaskdest)
			
					{
						gpio_put(a->gpio, 1);
						vTaskDelay(pdMS_TO_TICKS(a->delay));
						gpio_put(a->gpio, 0);
						vTaskDelay(pdMS_TO_TICKS(a->delay));
						if (tmp->data.msgorigin_t == redledtaskorigin) {
							tmp->data.msgdest_t = redledtaskdest;
							tmp->data.msgorigin_t = greenledtaskorigin;
							Enqueue(a->redq, tmp);
						}
						else if (tmp->data.msgorigin_t == yellowledtaskorigin) {
							tmp->data.msgdest_t = yellowledtaskdest;
							tmp->data.msgorigin_t = greenledtaskorigin;
							Enqueue(a->yellowq, tmp);
						}
			
			
					}
				}
				break;
			case redledtaskdest:
				tmp = Dequeue(a->redq);
				if (tmp->data.msg_t == ledMsg){
			
					if (tmp->data.msgdest_t == redledtaskdest)
			
					{
						gpio_put(a->gpio, 1);
						vTaskDelay(pdMS_TO_TICKS(a->delay));
						gpio_put(a->gpio, 0);
						vTaskDelay(pdMS_TO_TICKS(a->delay));
						if (tmp->data.msgorigin_t == greenledtaskorigin) {
							tmp->data.msgdest_t = greenledtaskdest;
							tmp->data.msgorigin_t = redledtaskorigin;
							Enqueue(a->greenq, tmp);
						}
						else if (tmp->data.msgorigin_t == yellowledtaskorigin) {
							tmp->data.msgdest_t = yellowledtaskdest;
							tmp->data.msgorigin_t = redledtaskorigin;
							Enqueue(a->yellowq, tmp);
						}
			
			
					}
				}
				break;
			case yellowledtaskdest:
				tmp = Dequeue(a->yellowq);
				if (tmp->data.msg_t == ledMsg){
			
					if (tmp->data.msgdest_t == yellowledtaskdest)
			
					{
						gpio_put(a->gpio, 1);
						vTaskDelay(pdMS_TO_TICKS(a->delay));
						gpio_put(a->gpio, 0);
						vTaskDelay(pdMS_TO_TICKS(a->delay));
						if (tmp->data.msgorigin_t == redledtaskorigin) {
							tmp->data.msgdest_t = redledtaskdest;
							tmp->data.msgorigin_t = yellowledtaskorigin;
							Enqueue(a->redq, tmp);
						}
						else if (tmp->data.msgorigin_t == greenledtaskorigin) {
							tmp->data.msgdest_t = greenledtaskdest;
							tmp->data.msgorigin_t = yellowledtaskorigin;
							Enqueue(a->greenq, tmp);
						}
			
			
					}
				}
				break;
		}
}
