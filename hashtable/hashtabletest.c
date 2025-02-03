/* CS50
 * Ahmed Elmi
 * Usage: hashtest to test the functionality 
 * Date Updated: April 20, 2024
 */

#include <stdio.h>
#include <stdlib.h>
#include "hashtable.h"

// Function declarations for specific hashtable operations
static void nameprint(FILE* fp, const char* key, void* item);
static void namedelete(void* item);
static void itemfunc(void* arg, const char* key, void* item);

int main() {
    // Step 1: Initialize the hashtable with a specified capacity
    hashtable_t* class_records = hashtable_new(10);

    // Memory allocation for student grades
    int* grade_of_alice = malloc(sizeof(int));
    int* grade_of_bob = malloc(sizeof(int));
    int* grade_of_clara = malloc(sizeof(int));
 
    // Assign grades to students
    *grade_of_alice = 88;
    *grade_of_bob = 92;
    *grade_of_clara = 85;
 
    // Define student names as keys
    const char* alice_key = "Alice";
    const char* bob_key = "Bob";
    const char* clara_key = "Clara";
 
    // Variable to count the number of student records
    int records_count = 0;
 
    // Check the creation of the hashtable
    if (class_records == NULL) {
        fprintf(stderr, "Error: Unable to initialize the hashtable.\n");
        return 1;
    } else {
        printf("Hashtable successfully initialized.\n");
    }
 
    // Step 3: Insert student records into the hashtable
    hashtable_insert(class_records, alice_key, grade_of_alice);
    hashtable_insert(class_records, bob_key, grade_of_bob);
    hashtable_insert(class_records, clara_key, grade_of_clara);
 
    printf("Displaying Hashtable Content:\n");
    hashtable_print(class_records, stdout, nameprint);
 
    // Step 5: Count the number of records in the hashtable
    hashtable_iterate(class_records, &records_count, itemfunc);
    printf("Validation Complete: Total records are %d (expected 3).\n", records_count);
 
    // Step 7: Clean up all records and free memory
    hashtable_delete(class_records, namedelete);
}
 
// Print each student's record in a readable format
static void nameprint(FILE* fp, const char* key, void* item) {
    int* grade = item;
    if (grade == NULL) {
        fprintf(fp, "(none)");
    } else {
        fprintf(fp, "Record: %s has a grade of %d;", key, *grade);
    }
}
// Free the memory allocated to a student's grade
static void namedelete(void* item) {
    free(item);
}

// Increment a count for each record found
static void itemfunc(void* arg, const char* key, void* item) {
    int* count = arg;
    if (count != NULL && item != NULL && key != NULL)
        (*count)++;
}

