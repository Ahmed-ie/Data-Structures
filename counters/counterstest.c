/* 
 * counterstest.c - CS50 'counterstest' module
 *
 * see counterstest.h for more information.
 *
 * David Kotz, April 2016, 2017, 2019, 2021
 * Ahmed Elmi, April 2024
 */

#include <stdio.h>
#include <stdlib.h>
#include "counters.h"

static void report_count(void* arg, const int key, const int count);

int main() {
    printf("Initializing new counters structure...\n");
    counters_t* counters = counters_new();
    if (counters == NULL) {
        fprintf(stderr, "Failed to initialize counters.\n");
        return 1;
    }
    printf("Counters initialized successfully.\n");

    // Adding different keys
    counters_add(counters, 10);
    counters_add(counters, 20);
    counters_add(counters, 10);  // Incrementing existing key
    printf("Added keys and incremented an existing key.\n");

    // Testing retrieval and setting new counts
    printf("Current count for key 10: %d\n", counters_get(counters, 10));
    counters_set(counters, 30, 1);  // Setting a new key
    counters_set(counters, 10, 5);  // Updating existing key
    printf("Updated counts and set a new key.\n");

    // Printing current state of counters
    printf("Current counters state:\n");
    counters_print(counters, stdout);

    // Using counters_iterate to sum counts
    int total = 0;
    counters_iterate(counters, &total, report_count);
    printf("Total count across all keys: %d\n", total);

    // Cleaning up
    counters_delete(counters);
    printf("Counters cleaned up and memory freed.\n");

    return 0;
}

static void report_count(void* arg, const int key, const int count) {
    int* total = (int*) arg;
    *total += count;
    printf("Key %d has count %d.\n", key, count);
}

