#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>

int solve(FILE *fp, int part);
int get_round_score_1(char other_move, char my_move);
int get_round_score_2(char other_move, char round_outcome);

int main()
{
    clock_t t;
    int result;

    FILE* fp = fopen("input_02_test.txt", "r");
    if (fp == NULL) exit(1);

    assert(solve(fp, 1) == 15);
    rewind(fp);
    assert(solve(fp, 2) == 12);
    fclose (fp);
    
    fp = fopen("input_02.txt", "r");
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
    int total_score = 0;
    char other_move, my_move; 

    while(!feof(fp))
    {
        fscanf(fp, "%c %c\n", &other_move, &my_move);
        if (part == 1) total_score += get_round_score_1(other_move, my_move);
        else           total_score += get_round_score_2(other_move, my_move);
    }

    return total_score;
}

int get_round_score_1(char other_move, char my_move)
{
    int score = my_move - 'X' + 1;

    if (my_move == (other_move + 23))
        score += 3;
    else if ((other_move == 'A' && my_move == 'Y') || 
             (other_move == 'B' && my_move == 'Z') || 
             (other_move == 'C' && my_move == 'X'))
        score += 6;
    
    return score;
}

int get_round_score_2(char other_move, char round_outcome)
{
    int score = 0;

    if (round_outcome == 'Y') // draw case
    {
        score += 3;
        score += (other_move - 'A' + 1);
    }
    else if (round_outcome == 'Z') // win case
    {
        score += 6;
        if (other_move == 'A')      score += 2;
        else if (other_move == 'B') score += 3;
        else                        score += 1;
    }
    else // lost case
    {
        if (other_move == 'A')      score += 3;
        else if (other_move == 'B') score += 1;
        else                        score += 2;
    }

    return score;
}
