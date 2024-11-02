/*
 * RP2040 divider check program
 */

#include <FreeRTOS.h>
#include <task.h>
#include <timers.h>
#include <stdio.h>
#include "pico/stdlib.h"
#include "../redled/redled.h"
#include "../yellowled/yellowled.h"
#include "../greenled/greenled.h"
#include "../common/led_task.h"
#include "../msgqueue/msgqueue.h"
/*
void main()
{
    stdio_init_all();
    printf("Product test\n");

    int i;
    Queue *greenledQ    = ConstructQueue(21);
    Queue *redledQ      = ConstructQueue(21);
    Queue *yellowledQ   = ConstructQueue(21);
    NODE *pN;           

    //enqueue red with msgs for two other leds
    pN = (NODE*) malloc(sizeof (NODE));
    pN->data.msgdest_t = redledtaskdest;
    pN->data.msgorigin_t = yellowledtaskorigin;
    pN->data.msg_t = ledMsg;
    Enqueue(redledQ, pN);
    pN = (NODE*) malloc(sizeof (NODE));
    pN->data.msgdest_t = redledtaskorigin;
    pN->data.msgorigin_t = greenledtaskdest;
    pN->data.msg_t = ledMsg;
    Enqueue(redledQ, pN);
    pN = (NODE*) malloc(sizeof (NODE));
    pN->data.msgdest_t = redledtaskdest;
    pN->data.msgorigin_t = yellowledtaskorigin;
    pN->data.msg_t = ledMsg;
    Enqueue(redledQ, pN);
    pN = (NODE*) malloc(sizeof (NODE));
    pN->data.msgdest_t = redledtaskorigin;
    pN->data.msgorigin_t = greenledtaskdest;
    pN->data.msg_t = ledMsg;
    Enqueue(redledQ, pN);

    //enqueue yellow with msgs for two other leds
    pN = (NODE*) malloc(sizeof (NODE));
    pN->data.msgdest_t = yellowledtaskdest;
    pN->data.msgorigin_t = redledtaskorigin;
    pN->data.msg_t = ledMsg;
    Enqueue(yellowledQ, pN);
    pN = (NODE*) malloc(sizeof (NODE));
    pN->data.msgdest_t = yellowledtaskdest;
    pN->data.msgorigin_t = greenledtaskorigin;
    pN->data.msg_t = ledMsg;
    Enqueue(yellowledQ, pN);

    //enqueue green with msgs for two other leds
    pN = (NODE*) malloc(sizeof (NODE));
    pN->data.msgdest_t = greenledtaskdest;
    pN->data.msgorigin_t = redledtaskorigin;
    pN->data.msg_t = ledMsg;
    Enqueue(greenledQ, pN);
    pN = (NODE*) malloc(sizeof (NODE));
    pN->data.msgdest_t = greenledtaskdest;
    pN->data.msgorigin_t = yellowledtaskorigin;
    pN->data.msg_t = ledMsg;
    Enqueue(greenledQ, pN);



    struct led_task_arg arg2 = { 14, 300, redledQ, yellowledQ, greenledQ };
    xTaskCreate(yellow_led_task, "YELLOW_LED_Task", 128, &arg2, 1, NULL);

    struct led_task_arg arg3 = { 13, 500, redledQ, yellowledQ, greenledQ };
    xTaskCreate(green_led_task, "GREEN_LED_Task", 128, &arg3, 1, NULL);

    struct led_task_arg arg1 = { 15, 440, redledQ, yellowledQ, greenledQ };
    xTaskCreate(red_led_task, "RED_LED_Task", 128, &arg1, 1, NULL);

    vTaskStartScheduler();

    while (true)
        ;
}
*/
/* Scheduler include files. */
#include "FreeRTOS.h"
#include "task.h"

/* Library includes. */
#include <stdio.h>
#include "pico/stdlib.h"
#include "../uarttransportlayer/uarttransportlayer.h"

/*
 * Configure the hardware as necessary
 */
static void prvSetupHardware();

int main() {
    /* Configure the hardware */
    prvSetupHardware();

    /* Create the UART task. */
    xTaskCreate(uart_task, "UART task", UART_TASK_STACK_SIZE,
        NULL, UART_TASK_PRIORITY, NULL);

    /* Start the tasks and timer running. */
    vTaskStartScheduler();

    for (;;) {}
    return 0;
}

static void prvSetupHardware() {
    stdio_init_all();
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, 1);
    gpio_put(PICO_DEFAULT_LED_PIN, 0);
    initUART();
}
void vApplicationMallocFailedHook() {
    /* Called if a call to pvPortMalloc() fails because there is insufficient
    free memory available in the FreeRTOS heap.  pvPortMalloc() is called
    internally by FreeRTOS API functions that create tasks, queues, software
    timers, and semaphores.  The size of the FreeRTOS heap is set by the
    configTOTAL_HEAP_SIZE configuration constant in FreeRTOSConfig.h. */

    /* Force an assert. */
    configASSERT((volatile void *)NULL);
}

void vApplicationStackOverflowHook(TaskHandle_t pxTask, char *pcTaskName) {
    (void)pcTaskName;
    (void)pxTask;

    /* Run time stack overflow checking is performed if
    configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2.  This hook
    function is called if a stack overflow is detected. */

    /* Force an assert. */
    configASSERT((volatile void *)NULL);
}
/*-----------------------------------------------------------*/

void vApplicationIdleHook() {
    volatile size_t xFreeHeapSpace;

    /* This is just a trivial example of an idle hook.  It is called on each
    cycle of the idle task.  It must *NOT* attempt to block.  In this case the
    idle task just queries the amount of FreeRTOS heap that remains.  See the
    memory management section on the http://www.FreeRTOS.org web site for memory
    management options.  If there is a lot of heap memory free then the
    configTOTAL_HEAP_SIZE value in FreeRTOSConfig.h can be reduced to free up
    RAM. */
    xFreeHeapSpace = xPortGetFreeHeapSize();

    /* Remove compiler warning about xFreeHeapSpace being set but never used. */
    ( void ) xFreeHeapSpace;
}
