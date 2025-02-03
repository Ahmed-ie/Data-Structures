/*
 * Author: Ahmed Elmi, Lab 
 * Date: 2024-04-11
 * Usage: This file cointains tests for set
 */
#include <stdio.h>
#include <stdlib.h>
#include "set.h"

// Function prototypes
static void display_item(FILE *fp, const char *key, void *item);
static void free_item(void *item);
static int *create_integer(int value);

int main() {
    printf("Initiating test of the set...\n");
    set_t *tech_set = set_new();
    if (tech_set == NULL) {
        fprintf(stderr, "Error: Could not initialize the set.\n");
        return 1;
    }

    printf("Testing empty set display:\n");
    set_print(tech_set, stdout, display_item);  // Expected to print (null)

    // Dynamically allocate integers with different test values
    int *speed = create_integer(500);
    int *capacity = create_integer(200);
    int *bandwidth = create_integer(150);

    printf("Adding items to the set...\n");
    set_insert(tech_set, "speed", speed);
    set_insert(tech_set, "capacity", capacity);
    set_insert(tech_set, "bandwidth", bandwidth);

    printf("Current set contents:\n");
    set_print(tech_set, stdout, display_item);  // Expected format: {[speed=500],[capacity=200],[bandwidth=150],}

    // Delete the set and free all resources
    printf("Deleting the set and freeing resources...\n");
    set_delete(tech_set, free_item);
    printf("Set has been cleared and resources freed.\n");

    return 0;
}

// Creates a new integer in the heap
static int *create_integer(int value) {
    int *new_int = malloc(sizeof(int));
    *new_int = value;
    return new_int;
}

// Displays an item in the set
static void display_item(FILE *fp, const char *key, void *item) {
    if (item != NULL) {
        fprintf(fp, "[%s=%d]", key, *(int *)item);
    } else {
        fprintf(fp, "(null)\n");
    }
}

// Frees an item from the set
static void free_item(void *item) {
    free(item);
}

