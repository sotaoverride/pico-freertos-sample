/*
 * UART Transport Layer Task FreeRTOS
 */

#include "uarttransportlayer.h"
#include <string.h>
volatile TaskHandle_t xTaskToNotify_UART = NULL;

uint8_t rxChar = 'b';
CIRCBUF_DEF(UartMsg, uart_tx_buff, 10);

CIRCBUF_DEF_FUNCS(UartMsg, uart_tx_buff, 10);


void initUART() {
	// Set up our UART
	uart_init(UART_ID, BAUD_RATE);
	// Set the TX and RX pins by using the function select on the GPIO
	// Set datasheet for more information on function select
	gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
	gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);
	// Set data format
	uart_set_format(UART_ID, DATA_BITS, STOP_BITS, PARITY);        
	// Turn off FIFO's - we want to do this character by character
	uart_set_fifo_enabled(UART_ID, false);
	// Set up a RX interrupt
	// We need to set up the handler first
	// Select correct interrupt for the UART we are using
	int UART_IRQ = UART_ID == uart0 ? UART0_IRQ : UART1_IRQ;
	// And set up and enable the interrupt handlers
	irq_set_exclusive_handler(UART_IRQ, UART_Isr);
	irq_set_enabled(UART_IRQ, true);
}

void uart_task(void *pvParameters) {

	/* To avoid compiler warnings */
	(UartMsg*) pvParameters;
	uint32_t ulNotificationValue;
	xTaskToNotify_UART = NULL;
	int counter = 0;
	UartMsg tmp;
	memset(&tmp, 0, sizeof(UartMsg));
        CIRCBUF_POP(uart_tx_buff, &tmp);
	//int size = sizeof(uart_msg);

	// TODO semaphore

	while (true) {
		/* Start the receiving from UART. */
		UART_receive();
		//This write is for testing - in real word other HW would be doing the writes...
		CIRCBUF_POP(uart_tx_buff, &tmp);

		//if uart_tx bffer !- emputy and msg_writtern=false and counter != size-1
		if (uart_is_writable(UART_ID) && counter<sizeof(UartMsg) && tmp.len != 0) {
			uart_putc(UART_ID, *((char*)(&tmp+counter)));
		       counter++;	// echo incoming char
					// 
		}
		if (counter == sizeof(UartMsg)-1){
		      counter =0;
	              memset(&tmp, 0, sizeof(UartMsg));
		      CIRCBUF_POP(uart_tx_buff, &tmp);
		}
		/* Wait to be notified that the receive is complete.  Note
		   the first parameter is pdTRUE, which has the effect of clearing
		   the task's notification value back to 0, making the notification
		   value act like a binary (rather than a counting) semaphore.  */
		ulNotificationValue = ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

		if (ulNotificationValue == 1) {
			/* Handle received data */
			if (uart_is_readable(UART_ID)) {
				rxChar = uart_getc(UART_ID);
			}
			if (rxChar == 'h') {
				gpio_xor_mask(1u << PICO_DEFAULT_LED_PIN); // toggle led
			}
		}
	}
}
// UART activate a receive with interrupt. Wait for ever for UART_BUFFER_SIZE bytes
void UART_receive() {
	/* At this point xTaskToNotify should be NULL as no receive
	   is in progress.  A mutex can be used to guard access to the
	   peripheral if necessary. */
	configASSERT(xTaskToNotify_UART == NULL);

	/* Store the handle of the calling task. */
	xTaskToNotify_UART = xTaskGetCurrentTaskHandle();
	// Now enable the UART to send interrupts - RX only
	uart_set_irq_enables(UART_ID, true, false);
}
void UART_Isr() {
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;
	// Now disable the UART to send interrupts
	uart_set_irq_enables(UART_ID, false, false);

	if (xTaskToNotify_UART != NULL) {

		/* Notify the task that the receive is complete. */
		vTaskNotifyGiveFromISR(xTaskToNotify_UART, &xHigherPriorityTaskWoken);
		/* There are no receive in progress, so no tasks to notify. */
		xTaskToNotify_UART = NULL;

		/* If xHigherPriorityTaskWoken is now set to pdTRUE then a
		   context switch should be performed to ensure the interrupt
		   returns directly to the highest priority task.  The macro used
		   for this purpose is dependent on the port in use and may be
		   called portEND_SWITCHING_ISR(). */
		portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
	}
}
