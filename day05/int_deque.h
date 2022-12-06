#ifndef __DEQUE_H
#define __DEQUE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct IntDeque
{
  int max_size;
  int *arr;
  int front;
  int rear;     
} IntDeque;

void create_deque (IntDeque *deque, int max_size);

void destroy_deque (IntDeque *deque);

bool is_empty (IntDeque *deque);

bool is_full (IntDeque *deque);

void insert_front (IntDeque *deque, int x);

void insert_rear (IntDeque *deque, int x);

void delete_front (IntDeque *deque);

void delete_rear (IntDeque *deque);

int get_front (IntDeque *deque);

int get_rear (IntDeque *deque);

void print_queue (IntDeque *deque);

#endif /* __DEQUE_H */