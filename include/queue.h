/*
The include file for the queue data structure
*/
#ifndef QUEUE_H
#define QUEUE_H

/* Queue structure definition */
typedef struct node 
{
    int data;
    struct node * next;
} Queue;    // Queue is a typedef of struct node


int enqueue(Queue ** rear, Queue ** front, int data);
int dequeue(Queue ** front);
int getRear(Queue * rear);
int getFront(Queue * front);
int isEmpty();
int isFull();

#endif
