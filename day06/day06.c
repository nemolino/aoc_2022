#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include "alphabet_counter.h"

#define WINDOW_SIZE_1 4
#define WINDOW_SIZE_2 14

enum Part {ONE, TWO};

void test_file_check(char* filename, int part_1_result, int part_2_result);
int solve(FILE *fp, enum Part part);

int main()
{
    clock_t t;
    int result;
    
    test_file_check("input_06_test_01.txt",  7, 19);
    test_file_check("input_06_test_02.txt",  5, 23);
    test_file_check("input_06_test_03.txt",  6, 23);
    test_file_check("input_06_test_04.txt", 10, 29);
    test_file_check("input_06_test_05.txt", 11, 26);
    
    FILE* fp = fopen("input_06.txt", "r");
    if (fp == NULL) exit(1);
    
    t = clock();
    result = solve(fp, ONE);
    t = clock() - t;
    printf("part1: %d , %f ms\n", result, ((double)t * 1000.0)/CLOCKS_PER_SEC);

    rewind(fp);

    t = clock();
    result = solve(fp, TWO);
    t = clock() - t;
    printf("part2: %d , %f ms\n", result, ((double)t * 1000.0)/CLOCKS_PER_SEC);

    fclose (fp);
    return 0;
}

void test_file_check(char* filename, int part_1_result, int part_2_result)
{
    FILE* fp = fopen(filename, "r");
    if (fp == NULL) exit(1);
    assert(solve(fp, ONE) == part_1_result);    
    rewind(fp);
    assert(solve(fp, TWO) == part_2_result);   
    fclose (fp);
}

int solve(FILE *fp, enum Part part)
{
    char c;
    int i, index;
    int w_size = (part == ONE) ? WINDOW_SIZE_1 : WINDOW_SIZE_2;
    char* w;
    AlphabetCounter counter;

    create_alphabet_counter(&counter);

    w = (char *) calloc(w_size, sizeof(char));
    if (w == NULL)
    {
        printf("An error has occurred in memory allocation!");
        exit(EXIT_FAILURE);
    }

    for (i = 0; i < w_size; i++)
    {
        c = getc(fp);
        w[i] = c;
        add_occurrence(&counter, c);
    }

    if (len(&counter) == w_size) return i;
    else
    {
        while ((c = getc(fp)) != EOF)
        {
            index = i % w_size;
            remove_occurrence(&counter, w[index]);
            add_occurrence(&counter, c);
            w[index] = c;
            i++;
            if (len(&counter) == w_size) return i;
        }
    }
    exit(EXIT_FAILURE);
}