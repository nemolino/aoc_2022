#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <stdbool.h>

int solve(FILE *fp, int part);
bool is_fully_overlapped(int8_t p1_lower, int8_t p1_upper,  int8_t p2_lower, int8_t p2_upper);
bool is_overlapped(int8_t p1_lower, int8_t p1_upper,  int8_t p2_lower, int8_t p2_upper);

int main()
{
    clock_t t;
    int result;

    FILE* fp = fopen("input_04_test.txt", "r");
    if (fp == NULL) exit(1);

    assert(solve(fp, 1) == 2);
    rewind(fp);
    assert(solve(fp, 2) == 4);
    fclose (fp);
    
    fp = fopen("input_04.txt", "r");
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
    int8_t p1_lower, p1_upper, p2_lower, p2_upper;
    int count_fully_overlapped_pairs = 0;
    int count_overlapped_pairs = 0;

    while(!feof(fp))
    {
        fscanf(fp, "%hhd-%hhd,%hhd-%hhd\n", &p1_lower, &p1_upper, &p2_lower, &p2_upper);

        if (part == 1 && is_fully_overlapped(p1_lower, p1_upper, p2_lower, p2_upper))
        {
            count_fully_overlapped_pairs++;
        }   
        else if (is_overlapped(p1_lower, p1_upper, p2_lower, p2_upper))
        {
            count_overlapped_pairs++;
        }  
    }

    return (part == 1) ? count_fully_overlapped_pairs : count_overlapped_pairs;
}

bool is_fully_overlapped(int8_t p1_lower, int8_t p1_upper,  int8_t p2_lower, int8_t p2_upper)
{
    return (p2_lower >= p1_lower && p2_upper <= p1_upper) || 
            (p1_lower >= p2_lower && p1_upper <= p2_upper);
}

bool is_overlapped(int8_t p1_lower, int8_t p1_upper,  int8_t p2_lower, int8_t p2_upper)
{
    return (p2_lower >= p1_lower && p2_lower <= p1_upper) || 
            (p1_lower >= p2_lower && p1_lower <= p2_upper);
}