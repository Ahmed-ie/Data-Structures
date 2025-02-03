/* 
 * counters.c - CS50 'bag' module
 *
 * see counters.h for more information.
 *
 * David Kotz, April 2016, 2017, 2019, 2021
 * Ahmed Elmi, April 2024
 */

#include <stdio.h>
#include <stdlib.h>
#include "counters.h"
#include "mem.h"

/**************** Local types ****************/
typedef struct counternode {
    int key;                 // the key for this counter
    int count;               // the count associated with this key
    struct counternode *next; // pointer to the next counternode
} counternode_t;

// global type
typedef struct counters {
    counternode_t *head;     // head of the list of counternodes
} counters_t;

/**************** Local functions prototypes ****************/
static counternode_t *counternode_new(int key);

/**************** counters_new() ****************/
/* see counters.h for description */

counters_t *counters_new(void) {
    counters_t *ctrs = malloc(sizeof(counters_t));

    if (ctrs == NULL) {
        return NULL; // Memory allocation failed
    }
    ctrs->head = NULL;
    return ctrs;
}

/**************** counters_add() ****************/
/* see counters.h for description */
int counters_add(counters_t *ctrs, int key) {

    if (ctrs == NULL || key < 0) {
        return 0; // Invalid input
    }
 
    counternode_t *node = ctrs->head;
    counternode_t *prev = NULL;
 
    // Search for existing node with the same key
    while (node != NULL && node->key != key) {
        prev = node;
        node = node->next;
    }
 
    if (node != NULL) {
        node->count++; // Key found, increment count
    } else {
        node = counternode_new(key); // Key not found, create new node
        if (node == NULL) {
            return 0; // Failed to create new node
        }
        if (prev == NULL) {
            ctrs->head = node; // New node is new head of list
        } else {
            prev->next = node; // Append new node to end of list
        }
    }
    return node->count;
}

/**************** counters_get() ****************/
/* see counters.h for description */

int counters_get(counters_t *ctrs, int key) {
    if (ctrs == NULL || key < 0) {
        return 0; // Invalid input
    }
 
    counternode_t *node;
    for (node = ctrs->head; node != NULL; node = node->next) {
        if (node->key == key) {
            return node->count; // Key found, return count
        }
    }
    return 0; // Key not found
}

/**************** counters_set() ****************/
/* see counters.h for description */

bool counters_set(counters_t *ctrs, int key, int count) {
    if (ctrs == NULL || key < 0 || count < 0) {
        return false;
    }
 
    counternode_t *node = ctrs->head;
    counternode_t *prev = NULL;
 
    while (node != NULL && node->key != key) {
        prev = node;
        node = node->next;
    }
 
    if (node != NULL) {
        node->count = count; // Key found, set count
        return true;
    } else {
        node = counternode_new(key); // Key not found, create new node
        if (node == NULL) {
            return false; // Failed to create new node
        }
        node->count = count;
        if (prev == NULL) {
            ctrs->head = node; // List was empty, set as head
        } else {
            prev->next = node; // Append to end of list
        }
        return true;
    }
}

/**************** counters_print() ****************/
/* see counters.h for description */

void counters_print(counters_t *ctrs, FILE *fp) {
    if (fp == NULL || ctrs == NULL) {
        fprintf(fp, "(null)\n");
        return;
    }
 
    fprintf(fp, "{");
    for (counternode_t *node = ctrs->head; node != NULL; node = node->next) {
        fprintf(fp, "[%d:%d]", node->key, node->count);
        if (node->next != NULL) {
            fprintf(fp, ", ");
        }
    }
    fprintf(fp, "}\n");
}

/**************** counters_iterate() ****************/
/* see counters.h for description */

void counters_iterate(counters_t *ctrs, void *arg, void (*itemfunc)(void *arg, const int key, const int count)) {
    if (ctrs != NULL && itemfunc != NULL) {
        for (counternode_t *node = ctrs->head; node != NULL; node = node->next) {
            itemfunc(arg, node->key, node->count);
        }
    }
}

/**************** counters_delete() ****************/
/* see counters.h for description */

void counters_delete(counters_t *ctrs) {
    if (ctrs != NULL) {
        counternode_t *node = ctrs->head;  // Start at the head of the list
        while (node != NULL) {
            counternode_t *next = node->next;  // Save reference to next node
            free(node);                        // Free the current node
            node = next;                       // Move to the next node
        }
        free(ctrs);                           // Free the structure itself
    }
}

/**************** Helper function to create a new node ****************/

static counternode_t *counternode_new(int key) {
    counternode_t *node = malloc(sizeof(counternode_t));
    if (node == NULL) {
        fprintf(stderr, "Failed to allocate memory for new counternode.\n");
        return NULL;
    }
    node->key = key;
    node->count = 1;  // Initial count is set to 1
    node->next = NULL;
    return node;
}

