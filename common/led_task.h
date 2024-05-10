#ifndef COMMONLED
#define COMMONLED
#include"../msgqueue/msgqueue.h"
struct led_task_arg {
    int gpio;
    int delay;
    Queue * redq;
    Queue * yellowq;
    Queue * greenq;
};

void led_task(void *p);
#endif

