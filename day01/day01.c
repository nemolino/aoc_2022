#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

int part1(FILE *fp);
int part2(FILE *fp);
void update_max_totals(int* max_totals, int cur_total);
int get_index_of_min(int* a);

int main()
{
    FILE* fp = fopen("input_01_test.txt", "r");
    if (fp == NULL) exit(1);

    assert(part1(fp) == 24000);
    rewind(fp);
    assert(part2(fp) == 45000);
    fclose (fp);

    fp = fopen("input_01.txt", "r");
    if (fp == NULL) exit(1);

    printf("part1: %d\n", part1(fp));
    rewind(fp);
    printf("part2: %d\n", part2(fp));
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
        if (line[0] == '\n')
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
        if (line[0] == '\n')
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
    if (a[0] <= a[1])
        return (a[0] <= a[2]) ? 0 : 2;
    else
        return (a[1] <= a[2]) ? 1 : 2;
}
