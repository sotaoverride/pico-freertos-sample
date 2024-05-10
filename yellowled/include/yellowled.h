#include"../msgqueue/msgqueue.h"
struct led_task_arg {
    int red_led_gpio;
    int yellow_led_gpio;
    int green_led_gpio;
    int delay;
    Queue * pq;
};

void led_task(void *p);
