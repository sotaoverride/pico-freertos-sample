struct led_task_arg {
    int gpio;
    int delay;
};

void led_task(void *p);
