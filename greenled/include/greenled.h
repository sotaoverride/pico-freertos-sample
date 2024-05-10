#include"../msgqueue/msgqueue.h"
struct led_task_arg {
    int gpio;
    int delay;
    Queue * pq;
};

void led_task(void *p);
