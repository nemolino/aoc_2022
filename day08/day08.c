#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>

#define BUFFER_SIZE 128

enum Part {ONE, TWO};

int solve(FILE *fp, enum Part part);
bool visible(int **mat, int n, int i, int j);
int get_scenic_score(int **mat, int n, int i, int j);

int main()
{
    FILE* fp;
    clock_t t;
    int result;
    
    fp = fopen("input_08_test.txt", "r");
    if (fp == NULL) exit(1);
    assert(solve(fp, ONE) == 21);    
    rewind(fp);
    assert(solve(fp, TWO) == 8);   
    fclose (fp);
    
    fp = fopen("input_08.txt", "r");
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

int solve(FILE *fp, enum Part part)
{
    char buffer[BUFFER_SIZE];
    int n, count_visible, scenic_score, max_scenic_score = 0;
    int **mat;

    fgets(buffer, BUFFER_SIZE, fp);
    n = strlen(buffer) - 1;
    rewind(fp);

    // matrix allocation
    mat = (int **)malloc(n * sizeof(int *));
    if (mat == NULL)
    {
        printf("An error has occurred in memory allocation!");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < n; i++)
    {
        mat[i] = (int *)malloc(n * sizeof(int));
        if (mat[i] == NULL)
        {
            printf("An error has occurred in memory allocation!");
            exit(EXIT_FAILURE);
        }
    }

    // matrix initialization
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            mat[i][j] = getc(fp) - 48;
        getc(fp);
    }

    if (part == ONE)
    {
        count_visible = 4 * n - 4;
        for (int i = 1; i < n - 1; i++)
        {
            for (int j = 1; j < n - 1; j++)
            {
                if (visible(mat, n, i, j))
                    count_visible++;
            }
        }
        return count_visible;
    }
    else
    {
        for (int i = 1; i < n - 1; i++)
        {
            for (int j = 1; j < n - 1; j++)
            {
                scenic_score = get_scenic_score(mat, n, i, j);
                if (scenic_score > max_scenic_score)
                    max_scenic_score = scenic_score;
            }
        }
        return max_scenic_score;
    }
}

bool visible(int **mat, int n, int i, int j)
{
    bool visible;

    // left columns
    visible = true;
    for (int k = j - 1; k >= 0; k--)
    {
        if (mat[i][k] >= mat[i][j])
        {
            visible = false;
            break;
        }
    }
    if (visible) return visible;

    // right columns
    visible = true;
    for (int k = j + 1; k < n; k++)
    {
        if (mat[i][k] >= mat[i][j])
        {
            visible = false;
            break;
        }
    }
    if (visible) return visible;

    // top rows
    visible = true;
    for (int k = i - 1; k >= 0; k--)
    {
        if (mat[k][j] >= mat[i][j])
        {
            visible = false;
            break;
        }
    }
    if (visible) return visible;

    // bottom rows
    visible = true;
    for (int k = i + 1; k < n; k++)
    {
        if (mat[k][j] >= mat[i][j])
        {
            visible = false;
            break;
        }
    }
    return visible;
}

int get_scenic_score(int **mat, int n, int i, int j)
{
    int scenic_score, score;

    // left columns
    score = 0;
    for (int k = j - 1; k >= 0; k--)
    {
        score++;
        if (mat[i][k] >= mat[i][j]) break;  
    }
    scenic_score = score;

    // right columns
    score = 0;
    for (int k = j + 1; k < n; k++)
    {
        score++;
        if (mat[i][k] >= mat[i][j]) break;
    }
    scenic_score *= score;

    // top rows
    score = 0;
    for (int k = i - 1; k >= 0; k--)
    {
        score++;
        if (mat[k][j] >= mat[i][j]) break;
    }
    scenic_score *= score;

    // bottom rows
    score = 0;
    for (int k = i + 1; k < n; k++)
    {
        score++;
        if (mat[k][j] >= mat[i][j]) break;
    }
    return scenic_score * score;
}