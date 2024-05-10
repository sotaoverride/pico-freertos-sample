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

void main()
{
    stdio_init_all();
    printf("Product test\n");

    int i;
    Queue *redledQ      = ConstructQueue(7);
    Queue *yellowledQ   = ConstructQueue(7);               ;
    Queue *greenledQ    = ConstructQueue(7);               ;
    NODE *pN;           

    //enqueue red with msgs for two other leds
    pN = (NODE*) malloc(sizeof (NODE));
    pN->data.msgorigin_t = redledtaskorigin;
    pN->data.msgdest_t = yellowledtaskdest;
    pN->data.msg_t = ledMsg;
    Enqueue(redledQ, pN);
    pN = (NODE*) malloc(sizeof (NODE));
    pN->data.msgorigin_t = redledtaskorigin;
    pN->data.msgdest_t = greenledtaskdest;
    pN->data.msg_t = ledMsg;
    Enqueue(redledQ, pN);

    //enqueue yellow with msgs for two other leds
    pN = (NODE*) malloc(sizeof (NODE));
    pN->data.msgorigin_t = yellowledtaskorigin;
    pN->data.msgdest_t = redledtaskdest;
    pN->data.msg_t = ledMsg;
    Enqueue(yellowledQ, pN);
    pN = (NODE*) malloc(sizeof (NODE));
    pN->data.msgorigin_t = yellowledtaskorigin;
    pN->data.msgdest_t = greenledtaskdest;
    pN->data.msg_t = ledMsg;
    Enqueue(yellowledQ, pN);

    //enqueue green with msgs for two other leds
    pN = (NODE*) malloc(sizeof (NODE));
    pN->data.msgorigin_t = greenledtaskorigin;
    pN->data.msgdest_t = redledtaskdest;
    pN->data.msg_t = ledMsg;
    Enqueue(greenledQ, pN);
    pN = (NODE*) malloc(sizeof (NODE));
    pN->data.msgorigin_t = greenledtaskorigin;
    pN->data.msgdest_t = yellowledtaskdest;
    pN->data.msg_t = ledMsg;
    Enqueue(greenledQ, pN);


    struct led_task_arg arg1 = { 15, 100 , redledQ, yellowledQ, greenledQ};
    xTaskCreate(red_led_task, "RED_LED_Task", 256, &arg1, 1, NULL);

    struct led_task_arg arg2 = { 14, 200, redledQ, yellowledQ, greenledQ};
    xTaskCreate(yellow_led_task, "YELLOW_LED_Task", 256, &arg2, 1, NULL);

    struct led_task_arg arg3 = { 13, 300, redledQ, yellowledQ, greenledQ};
    xTaskCreate(green_led_task, "GREEN_LED_Task", 256, &arg3, 1, NULL);


    vTaskStartScheduler();

    while (true)
        ;
}

