/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
// some of this code is in a header file. Check the attached zip to see what's where.
#ifndef UART_TRANS_LAYER
#define UART_TRANS_LAYER


#include <FreeRTOS.h>
#include <task.h>
#include <stdio.h>
#include "pico/stdlib.h"
#include "../common/led_task.h"
#include "../msgqueue/msgqueue.h"

/* Task parameters for UART Task. */
#define UART_TASK_PRIORITY       (2)
#define UART_TASK_STACK_SIZE     (1024 * 3)

/* application dependent UART settings */
#define UART_BUFFER_SIZE 26

// ... 

#define UART_ID uart0
#define BAUD_RATE 115200
#define DATA_BITS 8
#define STOP_BITS 1
#define PARITY    UART_PARITY_NONE
// Use pins 4 and 5 for UART1
// Pins can be changed, see the GPIO function select table in the datasheet for information on GPIO assignments
#define UART_TX_PIN 4
#define UART_RX_PIN 5
/* Stores the handle of the task that will be notified when the
 receive is complete. */
void initUART();
void uart_task(void *pvParameters);
void UART_receive();
void UART_Isr();
#endif

