#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>

int part1(FILE *fp);
int part2(FILE *fp);
void update_max_totals(int* max_totals, int cur_total);
int get_index_of_min(int* a);

int main()
{
    clock_t t;
    int result;

    FILE* fp = fopen("input_01_test.txt", "r");
    if (fp == NULL) exit(1);

    assert(part1(fp) == 24000);
    rewind(fp);
    assert(part2(fp) == 45000);
    fclose (fp);

    fp = fopen("input_01.txt", "r");
    if (fp == NULL) exit(1);

    t = clock();
    result = part1(fp);
    t = clock() - t;
    printf("part1: %d , %f ms\n", result, ((double)t * 1000.0)/CLOCKS_PER_SEC);

    rewind(fp);

    t = clock();
    result = part2(fp);
    t = clock() - t;
    printf("part2: %d , %f ms\n", result, ((double)t * 1000.0)/CLOCKS_PER_SEC);

    fclose (fp);
    return 0;
}

int part1(FILE *fp)
{
    int cur_total = 0;
    int max_total = 0;
    char line[8];

    while(fgets(line, sizeof(line), fp) != NULL)
    {
        if (strlen(line) == 1)
        {
            if (cur_total > max_total) max_total = cur_total;
            cur_total = 0;
        }
        else
            cur_total += atoi(line);
    }
    // per considerare anche l'ultimo cur_total
    if (cur_total > max_total) max_total = cur_total;
    return max_total;
}

int part2(FILE *fp)
{
    int cur_total = 0;
    int max_totals[] = {0, 0, 0};
    char line[8];

    while(fgets(line, sizeof(line), fp) != NULL)
    {
        if (strlen(line) == 1)
        {
            update_max_totals(max_totals, cur_total);
            cur_total = 0;
        }
        else
            cur_total += atoi(line);
    }
    // per considerare anche l'ultimo cur_total
    update_max_totals(max_totals, cur_total);
    return max_totals[0] + max_totals[1] + max_totals[2];
}

void update_max_totals(int* max_totals, int cur_total)
{
    int index_of_min = get_index_of_min(max_totals);
    if (cur_total > max_totals[index_of_min])
            max_totals[index_of_min] = cur_total;
}

int get_index_of_min(int* a)
{
    return (a[0] <= a[1]) ? ((a[0] <= a[2]) ? 0 : 2) : ((a[1] <= a[2]) ? 1 : 2);
}
