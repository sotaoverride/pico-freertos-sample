/*
 * UART Transport Layer Task FreeRTOS
 */

#include <FreeRTOS.h>
#include <task.h>
#include <stdio.h>
#include "pico/stdlib.h"
#include "../common/led_task.h"
#include "../msgqueue/msgqueue.h"

void uart_transport_layer_task(void *p)
{
	struct uart_transport_layer_task_arg *a = (struct uart_tranport_layer_task_arg *)p;

	//init UART..
	while (1) {
		//send rsv UART msg here..
	}
}






