#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>
#include "int_deque.h"

#define BUFFER_SIZE 64
#define DEQUE_SIZE 60 // easily tunable wrt to any input file

enum Part {ONE, TWO};

char* solve(FILE *fp, enum Part part);

int main()
{
    clock_t t;
    char* result;

    FILE* fp = fopen("input_05_test.txt", "r");
    if (fp == NULL) exit(1);

    assert(strcmp(solve(fp, ONE), "CMZ") == 0);
    rewind(fp);
    assert(strcmp(solve(fp, TWO), "MCD") == 0);
    fclose (fp);
    
    fp = fopen("input_05.txt", "r");
    if (fp == NULL) exit(1);
    
    t = clock();
    result = solve(fp, ONE);
    t = clock() - t;
    printf("part1: %s , %f ms\n", result, ((double)t * 1000.0)/CLOCKS_PER_SEC);
    
    rewind(fp);

    t = clock();
    result = solve(fp, TWO);
    t = clock() - t;
    printf("part2: %s , %f ms\n", result, ((double)t * 1000.0)/CLOCKS_PER_SEC);
    
    fclose (fp);
    return 0;
}

char* solve(FILE *fp, enum Part part)
{
    char line[BUFFER_SIZE];
    int number_of_stacks;
    IntDeque* stacks;
    IntDeque buffer;
    int i, c;
    int number_of_moves, src, dest;
    char* top_of_stacks;

    fgets(line, BUFFER_SIZE, fp); 
    rewind(fp);
    number_of_stacks = strlen(line) / 4;

    // allocating an array of deques that represent the stacks
    stacks = malloc(number_of_stacks * sizeof(*stacks));
    for (i = 0; i < number_of_stacks; i++)
        create_deque(&stacks[i], DEQUE_SIZE);

    // initializing stacks
    while (fgets(line, 64, fp) != NULL) 
    {
        if (line[1] == '1')
        {
            fgets(line, 64, fp);
            break;
        }
        for (i = 0; i < number_of_stacks; i++)
        {
            c = line[i * 4 + 1];
            if (c != ' ') insert_front(&stacks[i], c);
        }
    }

    // for (i = 0; i < number_of_stacks; i++) print_queue(&stacks[i]);

    if (part == TWO) create_deque(&buffer, BUFFER_SIZE);

    // simulating moves
    while(!feof(fp))
    {
        fscanf(fp, "move %d from %d to %d\n", &number_of_moves, &src, &dest);
        src--; dest--;
        if (part == ONE)
        {
            for (i = 0; i < number_of_moves; i++)
            {
                insert_rear(&stacks[dest], get_rear(&stacks[src]));
                delete_rear(&stacks[src]);
            }
        }
        else
        {
            for (i = 0; i < number_of_moves; i++)
            {
                insert_rear(&buffer, get_rear(&stacks[src]));
                delete_rear(&stacks[src]);
            }
            for (i = 0; i < number_of_moves; i++)
            {
                insert_rear(&stacks[dest], get_rear(&buffer));
                delete_rear(&buffer);
            }
        }
    }

    // for (i = 0; i < number_of_stacks; i++) print_queue(&stacks[i]);

    top_of_stacks = (char *) calloc(number_of_stacks + 1, sizeof(char));
    if (top_of_stacks == NULL)
    {
        printf("An error has occurred in memory allocation!");
        exit(EXIT_FAILURE);
    }
    for (i = 0; i < number_of_stacks; i++)
        top_of_stacks[i] = get_rear(&stacks[i]);
    top_of_stacks[number_of_stacks] = '\0';
    return top_of_stacks;
}