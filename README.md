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

// Insert key-value pairs
ht.insert(5, 50);
ht.insert(15, 150);
ht.insert(25, 250);

// Retrieve a value
int value = ht.get(15);  // Returns 150

// Remove a key
ht.remove(15);
```
