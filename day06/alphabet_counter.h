#ifndef __ALPHABET_COUNTER_H
#define __ALPHABET_COUNTER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#define NUMBER_OF_LETTERS 26

typedef struct AlphabetCounter
{
    int len;
    int arr[NUMBER_OF_LETTERS];
} AlphabetCounter;

int char_to_index (char ch);

char index_to_char (int i);

void create_alphabet_counter (AlphabetCounter *c);

bool contains (AlphabetCounter *c, char ch);

void add_occurrence (AlphabetCounter *c, char ch);

void remove_occurrence (AlphabetCounter *c, char ch);

int len (AlphabetCounter *c);

void print_alphabet_counter (AlphabetCounter *c);

#endif /* __ALPHABET_COUNTER_H */