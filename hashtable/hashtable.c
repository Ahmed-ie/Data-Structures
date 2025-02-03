/* hashtable.c - CS50 'hashtable' module
 *
 * see hashtable.h for more information.
 *
 * David Kotz, April 2016, 2017, 2019, 2021
 * Ahmed Elmi, April 2024
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"
#include "../set/set.h"
#include "hash.h"

/**************** Local types ****************/
typedef struct hashtable {
    set_t **table; // Array of pointers to sets
    int num_slots; // Number of slots in the hashtable
} hashtable_t;

/**************** Local functions prototypes ****************/
// None needed

/**************** hashtable_new() ****************/
hashtable_t *hashtable_new(const int num_slots) {
    hashtable_t *ht = malloc(sizeof(hashtable_t));
    if (ht == NULL) {
        return NULL; // Memory allocation failed
    }

    ht->num_slots = num_slots;
    ht->table = malloc(num_slots * sizeof(set_t *));
    if (ht->table == NULL) {
        free(ht); // Clean up and return NULL
        return NULL;
    }

    // Initialize each slot in the hashtable with a new set
    for (int i = 0; i < num_slots; i++) {
        ht->table[i] = set_new();
        if (ht->table[i] == NULL) {
            // Clean up and return NULL
            for (int j = 0; j < i; j++) {
                set_delete(ht->table[j], NULL); // Don't need itemdelete function for now
            }
            free(ht->table);
            free(ht);
            return NULL;
        }
    }

    return ht;
}

/**************** hashtable_insert() ****************/
bool hashtable_insert(hashtable_t *ht, const char *key, void *item) {
    if (ht == NULL || key == NULL) {
        return false;
    }

    // Calculate the hash value for the key
    unsigned long hash = hash_jenkins(key, ht->num_slots);

    // Insert the key-item pair into the corresponding set
    return set_insert(ht->table[hash], key, item);
}

/**************** hashtable_find() ****************/
void *hashtable_find(hashtable_t *ht, const char *key) {
    if (ht == NULL || key == NULL) {
        return NULL;
    }

    // Calculate the hash value for the key
    unsigned long hash = hash_jenkins(key, ht->num_slots);

    // Find the item in the corresponding set
    return set_find(ht->table[hash], key);
}

/**************** hashtable_print() ****************/
void hashtable_print(hashtable_t *ht, FILE *fp, void (*itemprint)(FILE *fp, const char *key, void *item)) {
    if (fp == NULL || ht == NULL) {
        fprintf(fp, "(null)\n");
        return;
    }

    fprintf(fp, "{");
    for (int i = 0; i < ht->num_slots; i++) {
        set_print(ht->table[i], fp, itemprint);
    }
    fprintf(fp, "}\n");
}

/**************** hashtable_iterate() ****************/
void hashtable_iterate(hashtable_t *ht, void *arg, void (*itemfunc)(void *arg, const char *key, void *item)) {
    if (ht != NULL && itemfunc != NULL) {
        for (int i = 0; i < ht->num_slots; i++) {
            set_iterate(ht->table[i], arg, itemfunc);
        }
    }
}

/**************** hashtable_delete() ****************/
void hashtable_delete(hashtable_t *ht, void (*itemdelete)(void *item)) {
    if (ht != NULL) {
        for (int i = 0; i < ht->num_slots; i++) {
            set_delete(ht->table[i], itemdelete);
        }
        free(ht->table);
        free(ht);
    }
}

