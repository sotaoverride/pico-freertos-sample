/*
 * RP2040 divider check program
 */

#include <FreeRTOS.h>
#include <task.h>
#include <timers.h>
#include <stdio.h>
#include "pico/stdlib.h"
#include "../blink/include/blink.h"

void main()
{
    stdio_init_all();
    printf("Product test\n");

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

