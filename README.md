# Custom Integer Hash Table in C++
This is a custom hash table implementation in C++ that provides a flexible, dynamically resizing data structure for storing integer key-value pairs. The implementation follows specific design constraints and demonstrates advanced data structure techniques.
## Features
  * Integer-only key-value storage
  * Dynamic resizing (growth and shrinkage)
  * Collision resolution using chaining
  * Custom hash function support
  * Implemented using C-style arrays
  * Doubly linked list for collision handling

## Key Characteristics
# Hash Function
   * Uses multiplication and division method
   * Supports custom hash function injection
   * Provides a default hash function using the golden ratio constant

# Resizing Mechanism

* Grows when table is 75% full (doubles capacity)
* Shrinks when table is 25% full (halves capacity)
* Minimum capacity is 16
* Rehashes all elements during resize operation
# Collision Resolution
  * Implements chaining using a custom doubly linked list
  * New elements added at the beginning of the collision chain

## Usage Example
```
// Create a hash table
HashTable ht;

 // Large set of numbers to demonstrate functionality
    int keys[] = {5, 15, 25, 35, 45, 55, 65, 75, 85, 95, 
                  105, 115, 125, 135, 145, 155, 165, 175, 185, 195};
    int values[] = {50, 150, 250, 350, 450, 550, 650, 750, 850, 950,
                    1050, 1150, 1250, 1350, 1450, 1550, 1650, 1750, 1850, 1950};


// Retrieve and print a specific value
    std::cout << "\nValue for key 15: " << ht.get(15) << std::endl;

 // Remove some keys
    std::cout << "\nRemoving keys 15 and 95:" << std::endl;
    ht.remove(15);
    ht.remove(95);
```

# Key Methods

* ```insert(int key, int value)```: Add a new key-value pair
* ```get(int key)```: Retrieve value for a given key
* ```remove(int key)```: Remove a key-value pair
* ```print()```: Display all elements in the hash table
* ```getSize()```: Get number of elements
* ```getCapacity()```: Get current table capacity
# Performance Characteristics

Average time complexity:

* Insertion: O(1)
* Retrieval: O(1)
* Deletion: O(1)


Worst-case time complexity (heavy collisions): O(n)

# Requirements

  * C++ Compiler supporting C++11 or later
  * Standard C++ Library

# Compilation
Compile with a C++11 or later compatible compiler:
```
g++ -std=c++11 hash_table.cpp -o hash_table
```
# Limitations

* Supports only integer keys and values
* Uses manual memory management
* Not thread-safe
