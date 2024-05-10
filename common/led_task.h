#ifndef COMMONLED
#define COMMONLED
#include"../msgqueue/msgqueue.h"
#pragma pack(push, 1)
struct led_task_arg {
    int gpio;
    int delay;
    Queue * redq;
    Queue * yellowq;
    Queue * greenq;
};
#pragma pack(pop)

void led_task(void *p);
void ping_pong(struct led_task_arg *, enum MsgDest_T dest);
#endif

