# CS50 Spring 2021 - Set Module

## Description
A set maintains an unordered collection of unique (key, item) pairs. It starts empty and grows as new pairs are inserted. Each key in a set can only occur once, making each item uniquely retrievable by its key. Unlike a bag, a set allows for item retrieval using keys but does not support removing or updating pairs once added.

## Usage
The set module, defined in `set.h` and implemented in `set.c`, manages (key, item) pairs with the following functions:

- `set_t* set_new(void);`
- `bool set_insert(set_t* set, const char* key, void* item);`
- `void* set_find(set_t* set, const char* key);`
- `void set_print(set_t* set, FILE* fp, void (*itemprint)(FILE* fp, const char* key, void* item));`
- `void set_iterate(set_t* set, void* arg, void (*itemfunc)(void* arg, const char* key, void* item));`
- `void set_delete(set_t* set, void (*itemdelete)(void* item));`

## Implementation
The set is implemented using a hash table to ensure efficient key-based retrieval:

- **Insertion**: A new (key, item) pair is hashed to determine the appropriate bucket and added if the key is not already present.
- **Retrieval**: To find an item, the key is hashed to locate the bucket, then the bucket is searched for the key.
- **Printing**: Iterates over the hash table, using the `itemprint` function to print each pair.
- **Iteration**: Applies a user-specified function to each item in the set.
- **Deletion**: Frees all memory associated with the set, optionally using a user-provided `itemdelete` function for each item.

## Assumptions
- Keys are strings; NULL keys or items are not permitted and prevent insertion.
- Memory management for items is the caller's responsibility beyond storing pointers.

## Files
- `Makefile` - compilation procedure
- `set.h` - the interface
- `set.c` - the implementation
- `settest.c` - unit test driver
- `test.keys` - test data
- `testing.out` - result of `make test &> testing.out`

## Compilation
Compile with the command:
```bash
make set.o

