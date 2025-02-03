/* 
 * set.c - CS50 'set' module
 *
 * see set.h for more information.
 *
 * Ahmed Elmi, April 2024
 * Usage: Set.c refer to set.h for more information
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "set.h"

/**************** file-local global variables ****************/
/* none */

/**************** local types ****************/
typedef struct setnode {
    char* key;
    void* item;
    struct setnode* next;
} setnode_t;

/**************** global types ****************/
typedef struct set {
    setnode_t* head;
} set_t;

/**************** local functions ****************/
static setnode_t* setnode_new(const char* key, void* item);
static char* duplicate_string(const char* str);

/**************** set_new() ****************/
/* see set.h for description */
set_t* set_new(void) {
    set_t* set = malloc(sizeof(set_t));
    if (set == NULL) {
        return NULL;
    }
    set->head = NULL;
    return set;
}

/**************** set_insert() ****************/
/* see set.h for description */
bool set_insert(set_t* set, const char* key, void* item) {
    if (set == NULL || key == NULL || item == NULL) {
        return false;
    }

    // Check for existing key and find the last node
    setnode_t* last_node = NULL;
    for (setnode_t* node = set->head; node != NULL; node = node->next) {
        if (strcmp(node->key, key) == 0) {
            return false; // Key already exists
        }
        last_node = node; // Keep track of the last node
    }

    // Create a new node
    setnode_t* newnode = setnode_new(key, item);
    if (newnode == NULL) {
        return false;
    }

    // Append new node to the end if not empty, otherwise set as head
    if (last_node == NULL) {
        set->head = newnode; // Set is empty, new node becomes head
    } else {
        last_node->next = newnode; // Append to the end
    }
    return true;
}

/**************** set_find() ****************/
/* see set.h for description */
void* set_find(set_t* set, const char* key) {
    if (set == NULL || key == NULL) {
        return NULL;
    }
    for (setnode_t* node = set->head; node != NULL; node = node->next) {
        if (strcmp(node->key, key) == 0) {
            return node->item;
        }
    }
    return NULL;
}

void set_print(set_t* set, FILE* fp, void (*itemprint)(FILE* fp, const char* key, void* item)) {
    if (fp == NULL) {
        return; // No file to write to
    }
    if (itemprint == NULL) {
        fputs("{}\n", fp);
        return; // No function to print items
    }
    if (set == NULL || set->head == NULL) {
        fputs("(null)\n", fp); // Print (null) for an empty or null set
        return;
    }

    fputs("{", fp);
    for (setnode_t* node = set->head; node != NULL; node = node->next) {
        itemprint(fp, node->key, node->item);
        if (node->next != NULL) {
            fputs(", ", fp); // Correctly place a comma before the next item
        }
    }
    fputs("}\n", fp);
}
/**************** set_delete() ****************/
/* see set.h for description */

void set_delete(set_t* set, void (*itemdelete)(void* item)) {
    if (set != NULL) {
        setnode_t* node = set->head;
        while (node != NULL) {
            setnode_t* next = node->next;
            if (itemdelete != NULL) {
                itemdelete(node->item);
            }
            free(node->key);
            free(node);
            node = next;
        }
        free(set);
    }
}

/**************** set_iterate() ****************/
/* see set.h for description */
void set_iterate(set_t* set, void* arg, void (*itemfunc)(void* arg, const char* key, void* item)) {
    if (set == NULL || itemfunc == NULL) {
        return;
    }
    for (setnode_t* node = set->head; node != NULL; node = node->next) {
        itemfunc(arg, node->key, node->item);
    }
}

/**************** setnode_new() ****************/
/* locally used to create a new set node */
static setnode_t* setnode_new(const char* key, void* item) {
    setnode_t* node = malloc(sizeof(setnode_t));
    if (node == NULL) {
        return NULL;
    }
    node->key = duplicate_string(key);
    if (node->key == NULL) {
        free(node);
        return NULL;
    }
    node->item = item;
    node->next = NULL;
    return node;
}

/**************** duplicate_string() ****************/
/* locally used to safely duplicate strings */
static char* duplicate_string(const char* str) {
    char* new_str = malloc(strlen(str) + 1);
    if (new_str == NULL) {
        return NULL;
    }
    strcpy(new_str, str);
    return new_str;
}

