# CS50 Spring 2021 - Counters Module

## Description
The Counters module provides a collection of counters, each uniquely identified by an integer key. It resembles a set where each key can occur only once, but rather than storing (key, item) pairs, it tracks a counter for each key. The module starts empty, and counters are incremented with `counters_add`. The current value of any counter can be retrieved using its key.

## Usage
The counters module, defined in `counters.h` and implemented in associated source files, supports several operations for managing counters:

- `counters_t* counters_new(void);` - Creates a new, empty counter set.
- `int counters_add(counters_t* ctrs, const int key);` - Increments the counter for the given key and returns the new value.
- `int counters_get(counters_t* ctrs, const int key);` - Retrieves the current value of the counter for the specified key.
- `bool counters_set(counters_t* ctrs, const int key, const int count);` - Sets the counter for the specified key to a specified value.
- `void counters_print(counters_t* ctrs, FILE* fp);` - Prints all counters in the counter set to the provided file.
- `void counters_iterate(counters_t* ctrs, void* arg, void (*itemfunc)(void* arg, const int key, const int count));` - Iterates over all counters, applying a function to each.
- `void counters_delete(counters_t* ctrs);` - Deletes the entire counter set, freeing all associated memory.

## Implementation
Counters are managed internally as a hash table to efficiently handle operations based on key values. This allows for quick additions, updates, and retrievals by key:

- **Addition**: If the key does not exist, a new counter is created and initialized to 1. If it does exist, the counter is incremented.
- **Retrieval**: Returns the current value of the counter associated with the key, or 0 if the key does not exist.
- **Setting**: If the key exists, its counter is updated; if it doesn't, a new counter is initialized with the specified value.
- **Printing**: Outputs a comma-separated list of key=counter pairs.
- **Iteration**: The user-provided function is applied to each counter.
- **Deletion**: All memory allocated for the counters is freed.

## Assumptions
- All keys are non-negative integers.
- Pointers to `counters_t` structures are valid.
- Functions ignore NULL pointers and negative keys as errors.

## Files
- `Makefile` - Compilation procedures
- `counters.h` - Interface definition
- Source files (`*.c`) containing the implementation
- Test files for unit testing

## Compilation
Compile the module with the following command:
```bash
make counters.o

