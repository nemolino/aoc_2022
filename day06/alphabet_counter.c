#include "alphabet_counter.h"

int char_to_index (char ch)
{
    /*
    if (!(islower(ch) && isalpha(ch)))
    {
        printf("Error, you passed a non-lower or non-alpha characther!\n");
        exit(EXIT_FAILURE);
    }*/
    return ch - 'a';
}

char index_to_char (int i)
{
    /*if (i < 0 || i >= NUMBER_OF_LETTERS)
    {
        printf("Error, you passed an invalid index!\n");
        exit(EXIT_FAILURE);
    }*/
    return i + 'a';
}

void create_alphabet_counter (AlphabetCounter *c)
{
    int i;
    for (i = 0; i < NUMBER_OF_LETTERS; i++)
        c->arr[i] = 0;
    c->len = 0;
}

bool contains (AlphabetCounter *c, char ch)
{
    return c->arr[char_to_index(ch)] > 0;
}

void add_occurrence (AlphabetCounter *c, char ch)
{
    int i = char_to_index(ch);
    if (c->arr[i] == 0) c->len++;
    c->arr[i]++;
}

void remove_occurrence (AlphabetCounter *c, char ch)
{
    int i = char_to_index(ch);
    if (c->arr[i] == 1) c->len--;
    c->arr[i]--;
}

int len (AlphabetCounter *c)
{
    return c->len;
}

void print_alphabet_counter (AlphabetCounter *c)
{
    int len = c->len, i, number_of_occurrences;

    printf("AlphabetCounter (%d letters) = { ", len);
    if (len > 0)
    {
        for (i = 0; i < NUMBER_OF_LETTERS; i++)
        {
            number_of_occurrences = c->arr[i];
            if (number_of_occurrences > 0) 
                printf("%c:%d ", index_to_char(i), number_of_occurrences);
        }
    }
    printf("}\n");
}