/**
 * @defgroup snowflake2.c Solution to the snowflake problem
 *
 * @brief A solution to the snowflake problem, defined at https://dmoj.ca/problem/cco07p2.
 * By creating a hash table and storing all snowflakes with the same hash value, we can check for duplicates
 * much faster since we only have to compare a few snowflakes to each other. Snowflakes with the same hash
 * are stored in a linked list.
 *
 * @author Alfred Waleij <dv20abj@cs.umu.se> 
 * @author Liam Asplund  <et19lad@cs.umu.se> 
 * @author Sunny Zhang   <dv21szg@cs.umu.se> 
 *
 */

#include <stdio.h>
#include <stdlib.h> /* calloc, free */
#include <string.h>

#define SNOWFLAKE_SIZE 6

typedef struct snowflake {
    int sum;
    int arms[SNOWFLAKE_SIZE];

    struct snowflake *next_snowflake;
} snowflake;

void treverse_snowflake_table(snowflake **snowflakes, int size);
int arrays_are_equal(int size, int a[], int b[]);
void reverse_array(int arr[], int n);
int compare_arms(snowflake original, int *cmpArray);

int main(void) {
    int amount_of_snowflakes = 0;
    fscanf(stdin, "%d", &amount_of_snowflakes);

    snowflake **snowflakes = calloc(amount_of_snowflakes, sizeof(snowflake *));

    for (int s = 0; s < amount_of_snowflakes; s++) {
        snowflake *current_snowflake = calloc(1, sizeof(snowflake));

        int arm_sum = 0;
        //calculate the sum of the arms
        for (int i = 0; i < SNOWFLAKE_SIZE; i++) {
            int arm_input = 0;
            fscanf(stdin, "%d", &arm_input);

            arm_sum = arm_sum + arm_input;
            current_snowflake->arms[i] = arm_input;
        }

        current_snowflake->sum = arm_sum;

        int current_snowflake_hash = current_snowflake->sum % amount_of_snowflakes;

        //all snowflakes with the same hash are stored in a linked list, we need to point to the next snowflake
        current_snowflake->next_snowflake = snowflakes[current_snowflake_hash];

        snowflakes[current_snowflake_hash] = current_snowflake;
    }

    treverse_snowflake_table(snowflakes, amount_of_snowflakes);

    //free all snowflakes within the snowflake table
    for (int i = 0; i < amount_of_snowflakes; i++) {
        snowflake *current_snowflake = snowflakes[i];
        while (current_snowflake != NULL) {
            snowflake *next_snowflake = current_snowflake->next_snowflake;
            free(current_snowflake);
            current_snowflake = next_snowflake;
        }
    }

    //lastly, free the snowflake table
    free(snowflakes);

    return 0;
}

void treverse_snowflake_table(snowflake **snowflakes, int size) {
    snowflake *comparator_flake_1, *comparator_flake_2;

    //since we are basically going through a linked list of snowflakes,
    //instead of a for loop, we will use a while loop because we don't know how many snowflakes there are

    for (int i = 0; i < size; i++) {
        comparator_flake_1 = snowflakes[i];

        while (comparator_flake_1 != NULL) {
            comparator_flake_2 = comparator_flake_1->next_snowflake;

            while (comparator_flake_2 != NULL) {
                int reversed_arms[SNOWFLAKE_SIZE];

                //copy the arms of the current snowflake into a new array
                memcpy(reversed_arms, (*comparator_flake_2).arms, sizeof(int) * SNOWFLAKE_SIZE);
                //we need to reverse the array of arms of the current snowflake, to compare both cases
                reverse_array(reversed_arms, SNOWFLAKE_SIZE);

                //compare the arms of flake1 with both the arms of flake2 and the reversed arms of flake2
                if (compare_arms(*comparator_flake_1, (*comparator_flake_2).arms) ||
                        compare_arms(*comparator_flake_1, reversed_arms)) {
                    printf("Twin snowflakes found.\n");
                    return;
                }

                comparator_flake_2 = comparator_flake_2->next_snowflake;
            }

            comparator_flake_1 = comparator_flake_1->next_snowflake;
        }
    }

    printf("No two snowflakes are alike.\n");
}

int arrays_are_equal(int size, int a[], int b[]) {
    for (int i = 0; i < size; i++) {
        if (a[i] != b[i]) {
            return 0;
        }
    }

    return 1;
}

void reverse_array(int arr[], int n) {
    int tmp[n];

    for (int i = 0; i < n; i++) {
        tmp[n - 1 - i] = arr[i];
    }

    for (int i = 0; i < n; i++) {
        arr[i] = tmp[i];
    }
}

int compare_arms(snowflake original, int *cmpArray) {
    // we make a temporary array that we will offset to try all combinations of the arms
    int offset_cmp_array[SNOWFLAKE_SIZE];

    //if we're lucky, the arrays are already equal
    if (arrays_are_equal(SNOWFLAKE_SIZE, original.arms, cmpArray))
        return 1;

    //copy the original array into the temporary array
    memcpy(offset_cmp_array, cmpArray, sizeof(int) * SNOWFLAKE_SIZE);

    //here we offset the temporary array by one each loop, 
    //and in every iteration check if its equal to the original array
    for (int i = 0; i < SNOWFLAKE_SIZE; i++) {
        for (int j = 0; j < SNOWFLAKE_SIZE; j++) {
            offset_cmp_array[(i + j + 1) % SNOWFLAKE_SIZE] = cmpArray[j];
        }

        if (arrays_are_equal(SNOWFLAKE_SIZE, original.arms, offset_cmp_array) == 1) {
            return 1;
        }
    }

    return 0;
}