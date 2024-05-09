/*
 * RP2040 divider check program
 */

#include <FreeRTOS.h>
#include <task.h>
#include <timers.h>
#include <stdio.h>
#include "pico/stdlib.h"
#include "../blink/include/blink.h"
#include "../msgqueue/msgqueue.h"

void main()
{
    stdio_init_all();
    printf("Product test\n");

    int i;
    Queue *pQ = ConstructQueue(7);
    NODE *pN;

    for (i = 0; i < 7; i++) {
        pN = (NODE*) malloc(sizeof (NODE));
        pN->data.msgdest_t = task2;
        pN->data.msgorigin_t = task1;
        pN->data.msg_t = ledMsg;
        Enqueue(pQ, pN);
    }

    while (!isEmpty(pQ)) {
        pN = Dequeue(pQ);
        printf("\nDequeued: %d", pN->data);
        free(pN);
    }
    DestructQueue(pQ);

    struct led_task_arg arg1 = { 15, 100 };
    xTaskCreate(led_task, "LED_Task 1", 256, &arg1, 1, NULL);

    struct led_task_arg arg2 = { 14, 200 };
    xTaskCreate(led_task, "LED_Task 2", 256, &arg2, 1, NULL);

    struct led_task_arg arg3 = { 13, 300 };
    xTaskCreate(led_task, "LED_Task 3", 256, &arg3, 1, NULL);


    vTaskStartScheduler();

    while (true)
        ;
}

