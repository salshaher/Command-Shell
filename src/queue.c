/**
 * Queue implementation using linked list in C.
 * Source: https://codeforwin.org/2018/08/queue-implementation-using-linked-list-in-c.html
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "queue.h"


#define CAPACITY 100    // Queue max capacity


/* Queue size */
unsigned int size = 0;

/**
 * Enqueues/Insert an element at the rear of a queue.
 * Function returns 1 on success otherwise returns 0.
 */
int enqueue(Queue ** rear, Queue ** front, int data)
{
    Queue * newNode = NULL;

    // Check queue out of capacity error
    if (isFull())
    {
        return 0;
    }

    // Create a new node of queue type
    newNode = (Queue *) malloc (sizeof(Queue));

    // Assign data to new node
    newNode->data = data;

    // Initially new node does not point anything
    newNode->next = NULL;

    // Link new node with existing last node 
    if ( (*rear) )
    {
        (*rear)->next = newNode;
    }
    

    // Make sure newly created node is at rear
    *rear = newNode;

    // Link first node to front if its NULL
    if ( !( *front) )
    {
        *front = *rear;
    }

    // Increment quque size
    size++;

    return 1;
}


/**
 * Dequeues/Removes an element from front of the queue.
 * It returns the element on success otherwise returns 
 * INT_MIN as error code.
 */
int dequeue(Queue ** front)
{
    Queue *toDequque = NULL;
    int data = INT_MIN;

    // Queue empty error
    if (isEmpty())
    {
        return INT_MIN;
    }

    // Get element and data to dequeue
    toDequque = *front;
    data = toDequque->data;

    // Move front ahead
    *front = (*front)->next;

    // Decrement size
    size--;

    // Clear dequeued element from memory
    free(toDequque);

    return data;
}


/**
 * Gets, element at rear of the queue. It returns the element
 * at rear of the queue on success otherwise return INT_MIN as 
 * error code.
 */
int getRear(Queue * rear)
{
    // Return INT_MIN if queue is empty otherwise rear.
    return (isEmpty())
            ? INT_MIN
            : rear->data;
}


/**
 * Gets, element at front of the queue. It returns the element
 * at front of the queue on success otherwise return INT_MIN as 
 * error code.
 */
int getFront(Queue * front)
{
    // Return INT_MIN if queue is empty otherwise front.
    return (isEmpty())
            ? INT_MIN
            : front->data;
}


/**
 * Checks, if queue is empty or not.
 */
int isEmpty()
{
    return (size <= 0);
}


/**
 * Checks, if queue is within the maximum queue capacity.
 */
int isFull()
{
    return (size > CAPACITY);
}
