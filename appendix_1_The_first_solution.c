/**
 * @defgroup snowflake1.c Solution to the snowflake problem
 *
 * @brief A solution to the snowflake problem, defined at https://dmoj.ca/problem/cco07p2.
 * By comparing every arm of every snowflake to every other arm of every snowflake, we can check for duplicates.
 * This is slow, but works.
 *
 * @author Alfred Waleij <dv20abj@cs.umu.se> 
 * @author Liam Asplund  <et19lad@cs.umu.se> 
 * @author Sunny Zhang   <dv21szg@cs.umu.se> 
 *
 */
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int insert(int *snowflakes, int Max)
{
    for (int j = 0; j < 6; j++)
    {
        scanf("%d", &snowflakes[j]);
        if (snowflakes[j] >= Max || snowflakes[j] < 0)
        {
            return 1;
        }
    }
    return 0;
}

bool compare(int *snowflakebig, int *snowflakesmall, int big)
{
    int j = 0;
    for (int i = 0; (i < big) && (j != 6) ; i++)
    {
        if (snowflakebig[i] == snowflakesmall[j])
        {
            j++;
            if (j == 6)
            {
                break;
            } 
        }
        else
        {
            j = 0;
            if (i > big - 6)
            {
                break;
            }
        }
    }
    return (j == 6);
}

int main()
{
    int N;
    int capacity = 13;
    int Max = 10000000;
    int index = 0;
    
    scanf("%d", &N);
    if (N <= 0 || N > 100000)
    {
        return 0;
    }

    bool *arr1 = calloc(N, sizeof(char));
    int *snowflake1 = calloc(6, sizeof(int));
    int *snowflakeconcat = calloc(capacity, sizeof(int));
    int *snowflakerev = calloc(capacity, sizeof(int)); 

    for (int i = 0; i < N; i++)
    {
        int check1 = insert(snowflake1, Max);
        if (check1 == 1)
        {
            break;
        }
        int weight = 0;
        for (int b = 0; b < 6; b++)
        {
            weight += snowflake1[b];
        }
        
        if ((i != 0) && (arr1[weight%N] == 1))
        {
            if (compare(snowflakeconcat, snowflake1, index))
            {
                printf("Twin snowflakes found.\n");
                free(arr1);
                free(snowflake1);
                free(snowflakeconcat);
                free(snowflakerev);  
                return 0;
            }
            else
            {
                if (compare(snowflakerev, snowflake1, index))
                {
                    printf("Twin snowflakes found.\n");
                    free(arr1);
                    free(snowflake1);
                    free(snowflakeconcat);
                    free(snowflakerev);  
                    return 0;                
                }   
            }
        }
    
        arr1[weight%N] = 1;

        if (index >= capacity) 
        {
            capacity += 13;
            snowflakeconcat = realloc(snowflakeconcat,capacity*sizeof(int));
            snowflakerev = realloc(snowflakerev, capacity*sizeof(int));
        }
        for (int k = 0; k < 6; k++)
        {
            snowflakerev[index] = snowflake1[6 - 1 - k]; 
            snowflakeconcat[index++] = snowflake1[k];
        }
        for (int l = 0; l < 6; l++)
        {
            snowflakerev[index] = snowflake1[6 - 1 - l]; 
            snowflakeconcat[index++] = snowflake1[l];
        }
        snowflakerev[index] = -1;
        snowflakeconcat[index++] = -1;
    }

    printf("No two snowflakes are alike.\n");

    free(arr1);
    free(snowflake1);
    free(snowflakeconcat);
    free(snowflakerev);  

    return 0;
}