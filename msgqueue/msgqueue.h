#ifndef MSGQUEUE
#define MSGQUEUE
#include <stdlib.h>
#include <stdio.h>

#define TRUE  1
#define FALSE	0

enum Msg_T{
	ledMsg,
	divChkMsg
};

enum MsgOrigin_T{
	redledtaskorigin,
	yellowledtaskorigin,
	greenledtaskorigin
};

enum MsgDest_T{
	redledtaskdest,
	yellowledtaskdest,
	greenledtaskdest
};

typedef struct Msg{
	enum Msg_T msg_t;
	enum MsgOrigin_T  msgorigin_t;
	enum MsgDest_T msgdest_t;
} MSG_T;

typedef struct Node_t {
    MSG_T data;
    struct Node_t *prev;
} NODE;

/* the HEAD of the Queue, hold the amount of node's that are in the queue*/
typedef struct Queue {
    NODE *head;
    NODE *tail;
    int size;
    int limit;
} Queue;

Queue *ConstructQueue(int limit);
void DestructQueue(Queue *queue);
int Enqueue(Queue *pQueue, NODE *item);
NODE *Dequeue(Queue *pQueue);
int isEmpty(Queue* pQueue);
#endif
