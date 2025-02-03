# CS50 Spring 2021 - Hashtable Module

## Description
The Hashtable module is an efficient implementation of a set of (key, item) pairs. It allows for quick retrieval, addition, and management of items using keys. A hashtable is ideal for situations where quick lookup of data is essential, making it far more efficient for large collections compared to a simple list or unsorted array.

## Usage
The hashtable module, defined in `hashtable.h` and implemented in related source files, provides an API for managing a hashtable including the following functions:

- `hashtable_t* hashtable_new(const int num_slots);` - Create a new, empty hashtable specifying the number of slots.
- `bool hashtable_insert(hashtable_t* ht, const char* key, void* item);` - Insert an item with a unique key into the hashtable.
- `void* hashtable_find(hashtable_t* ht, const char* key);` - Retrieve the item associated with a specific key.
- `void hashtable_print(hashtable_t* ht, FILE* fp, void (*itemprint)(FILE* fp, const char* key, void* item));` - Print the contents of the hashtable.
- `void hashtable_iterate(hashtable_t* ht, void* arg, void (*itemfunc)(void* arg, const char* key, void* item));` - Apply a function to each item in the hashtable.
- `void hashtable_delete(hashtable_t* ht, void (*itemdelete)(void* item));` - Delete the hashtable and free all associated memory.

## Implementation
Internally, the hashtable uses an array of linked lists (or slots) to store (key, item) pairs. Each key is hashed to determine which slot its corresponding item should be stored in. This allows for average-case constant time complexity (O(1)) for adding, finding, and removing items, under typical conditions.

- **Insertion**: If the key does not exist, the item is added to the corresponding slot. If the key already exists, the insertion fails.
- **Lookup**: The item associated with a given key can be quickly retrieved by hashing the key to find the correct slot.
- **Printing**: Outputs the contents of each slot, including the keys and items, if a print function is provided.
- **Iteration**: Iterates over all items in an undefined order, applying a user-specified function to each item.
- **Deletion**: Frees all memory associated with the hashtable, including the memory for keys and items, if a delete function is provided.

## Assumptions
- The number of slots in the hashtable must be greater than zero.
- Keys are strings, and item pointers are to generic void types, allowing for diverse data storage.

## Files
- `Makefile` - For compiling the module and tests.
- `hashtable.h` - The interface for the hashtable module.
- Source files (`*.c`) - Implementation of the hashtable functions.
- Test files - Various tests to ensure functionality and robustness.

## Compilation
Compile the module using the following command:
```bash
make hashtable.o

