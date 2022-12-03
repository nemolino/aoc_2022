#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <time.h>
#include <assert.h>

#define NUMBER_OF_LETTERS 52

int solve(FILE *fp, int part);
int char_to_set_index(char c);
int char_to_priority(char c);
int get_bag_priority(char* bag_content);
int get_badges_priority(char* bag_content_1, char* bag_content_2, char* bag_content_3);

int main()
{
    clock_t t;
    int result;

    FILE* fp = fopen("input_03_test.txt", "r");
    if (fp == NULL) exit(1);

    assert(solve(fp, 1) == 157);
    rewind(fp);
    assert(solve(fp, 2) == 70);
    fclose (fp);
    
    fp = fopen("input_03.txt", "r");
    if (fp == NULL) exit(1);

    t = clock();
    result = solve(fp, 1);
    t = clock() - t;
    printf("part1: %d , %f ms\n", result, ((double)t * 1000.0)/CLOCKS_PER_SEC);
    
    rewind(fp);

    t = clock();
    result = solve(fp, 2);
    t = clock() - t;
    printf("part2: %d , %f ms\n", result, ((double)t * 1000.0)/CLOCKS_PER_SEC);
    
    fclose (fp);
    return 0;
}

int solve(FILE *fp, int part)
{
    char bag1_content[64], bag2_content[64], bag3_content[64];
    int priorities_sum = 0;

    while(!feof(fp))
    {
        if (part == 1)
        {
            fscanf(fp, "%s\n", bag1_content);
            priorities_sum += get_bag_priority(bag1_content);
        }
        else 
        {
            fscanf(fp, "%s\n%s\n%s\n", bag1_content, bag2_content, bag3_content);
            priorities_sum += get_badges_priority(bag1_content, bag2_content, bag3_content);
        }
    }

    return priorities_sum;
}

int char_to_set_index(char c)
{
    return (isupper(c)) ? c - 'A' : c - 'a' + 26;
}

int char_to_priority(char c)
{
    return (isupper(c)) ? c - 'A' + 27 : c - 'a' + 1;
}

int get_bag_priority(char* bag_content)
{
    bool items_set[NUMBER_OF_LETTERS] = {false};
    int i;
    char c;

    for (i = 0; i < strlen(bag_content) / 2; i++)
    {
        c = bag_content[i];
        items_set[char_to_set_index(c)] = true;
    }

    for (i = strlen(bag_content) / 2; i < strlen(bag_content); i++)
    {
        c = bag_content[i];
        if (items_set[char_to_set_index(c)])
            return char_to_priority(c);
    }

    exit(1);
}

int get_badges_priority(char* bag1_content, char* bag2_content, char* bag3_content)
{
    int8_t items_set[NUMBER_OF_LETTERS] = {0};
    int i;
    char c;

    for (i = 0; i < strlen(bag1_content); i++)
    {
        c = bag1_content[i];
        items_set[char_to_set_index(c)] = 1;
    }

    for (i = 0; i < strlen(bag2_content); i++)
    {
        c = bag2_content[i];
        if (items_set[char_to_set_index(c)] == 1)
            items_set[char_to_set_index(c)] = 2;
    }

    for (i = 0; i < strlen(bag3_content); i++)
    {
        c = bag3_content[i];
        if (items_set[char_to_set_index(c)] == 2)
            return char_to_priority(c);
    }

    exit(1);
}