#include "int_deque.h"

void create_deque (IntDeque *deque, int max_size)
{
    deque->arr = (int *) calloc(max_size, sizeof(int));
    if (deque->arr == NULL)
    {
        printf("An error has occurred in memory allocation!");
        exit(EXIT_FAILURE);
    }
    deque->max_size = max_size;
    deque->front = -1;
    deque->rear = 0;
}

void destroy_deque (IntDeque *deque)
{
    free(deque->arr);
    deque->arr = NULL;
    deque->max_size = -1;
    deque->front = -1;
    deque->rear = -1;
}

bool is_empty (IntDeque *deque)
{
    return deque->front == -1;
}

bool is_full (IntDeque *deque)
{
    return ((deque->front == 0 && deque->rear == deque->max_size - 1) || deque->front == deque->rear + 1);
}

void insert_rear (IntDeque *deque, int x)
{
    if (is_full(deque))
    {
        printf("IntDeque overflow");
        exit(EXIT_FAILURE);
    }
    if (deque->front == -1)
    {
        deque->front = 0;
        deque->rear = 0;
    }
    else if (deque->rear == deque->max_size - 1)
        deque->rear = 0;
    else
        deque->rear++;
    deque->arr[deque->rear] = x;    
}

void insert_front (IntDeque *deque, int x)
{
    if (is_full(deque))
    {
        printf("IntDeque overflow");
        exit(EXIT_FAILURE);
    }
    if (deque->front == -1)
    {
        deque->front = 0;
        deque->rear = 0;
    }
    else if (deque->front == 0)
        deque->front = deque->max_size - 1;
    else
        deque->front--;
    deque->arr[deque->front] = x;    
}

void delete_rear (IntDeque *deque)
{
    if (is_empty(deque))
    {
        printf("IntDeque underflow");
        exit(EXIT_FAILURE);
    }
    if (deque->front == deque->rear)
    {
        deque->front = -1;
        deque->rear = -1;
    }
    else if (deque->rear == 0)
        deque->rear = deque->max_size - 1;
    else
        deque->rear--;
}

void delete_front (IntDeque *deque)
{
    if (is_empty(deque))
    {
        printf("IntDeque underflow");
        exit(EXIT_FAILURE);
    }
    if (deque->front == deque->rear)
    {
        deque->front = -1;
        deque->rear = -1;
    }
    else if (deque->front == deque->max_size - 1)
        deque->front = 0;
    else
        deque->front++;
}

int get_rear (IntDeque *deque)
{
    if (is_empty(deque) || deque->rear < 0)
    {
        printf("IntDeque underflow");
        exit(EXIT_FAILURE);
    }
    return deque->arr[deque->rear];
}

int get_front (IntDeque *deque)
{
    if (is_empty(deque))
    {
        printf("IntDeque underflow");
        exit(EXIT_FAILURE);
    }
    return deque->arr[deque->front];
}

void print_queue (IntDeque *deque)
{
    int i;
    if (is_empty(deque))
    {
        printf("IntDeque : []\n");
    }
    else 
    {
        printf("IntDeque : [");
        for (i = deque->front; i != deque->rear + 1; i = (i+1) % deque->max_size)
            printf(" %c ", deque->arr[i]);
        printf("]\n");
    }
}