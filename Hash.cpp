#include <iostream>
#include <functional>

class HashTable {
private:
    // Doubly Linked List Node
    struct Node {
        int key;
        int value;
        Node* prev;
        Node* next;
        
        Node(int k, int v) : key(k), value(v), prev(nullptr), next(nullptr) {}
    };

    // C-style array of Node pointers
    Node** table;
    int capacity;
    int size;

    // Function pointer for hash function
    std::function<unsigned int(int)> hashFunc;

    // Default hash function using multiplication and division method
    unsigned int defaultHashFunction(int key) {
        // Multiplication method with a known constant
        unsigned int hashValue = key * 2654435761;  // Golden ratio constant
        // Division method using capacity
        return hashValue % capacity;
    }

    void resize(int newCapacity) {
        // Store old table
        Node** oldTable = table;
        int oldCapacity = capacity;

        // Create new table
        capacity = newCapacity;
        table = new Node*[capacity]();
        size = 0;

        // Re-hash all existing elements
        for (int i = 0; i < oldCapacity; i++) {
            Node* current = oldTable[i];
            while (current) {
                insert(current->key, current->value);
                Node* toDelete = current;
                current = current->next;
                delete toDelete;
            }
        }

        // Free old table
        delete[] oldTable;
    }

public:
    // Constructor with optional custom hash function
    HashTable(int initialCapacity = 16, 
              std::function<unsigned int(int)> customHashFunc = nullptr) 
        : capacity(initialCapacity), size(0) {
        // Use custom hash function if provided, else use default
        hashFunc = customHashFunc ? customHashFunc : 
            std::bind(&HashTable::defaultHashFunction, this, std::placeholders::_1);
        
        // Allocate C-style array
        table = new Node*[capacity]();
    }

    // Destructor to free memory
    ~HashTable() {
        for (int i = 0; i < capacity; i++) {
            Node* current = table[i];
            while (current) {
                Node* toDelete = current;
                current = current->next;
                delete toDelete;
            }
        }
        delete[] table;
    }

    void insert(int key, int value) {
        // Grow if nearly full (75% full)
        if (size * 4 >= capacity * 3) {
            resize(capacity * 2);
        }

        // Calculate hash index
        unsigned int index = hashFunc(key);

        // Create new node
        Node* newNode = new Node(key, value);

        // Chaining for collision resolution
        if (!table[index]) {
            table[index] = newNode;
        } else {
            // Insert at the beginning of the list
            newNode->next = table[index];
            table[index]->prev = newNode;
            table[index] = newNode;
        }

        size++;
    }

    int get(int key) {
        unsigned int index = hashFunc(key);
        Node* current = table[index];

        // Search through the chain
        while (current) {
            if (current->key == key) {
                return current->value;
            }
            current = current->next;
        }

        // Key not found
        throw std::runtime_error("Key not found");
    }

    void remove(int key) {
        unsigned int index = hashFunc(key);
        Node* current = table[index];

        // Search and remove
        while (current) {
            if (current->key == key) {
                // Unlink the node
                if (current->prev) {
                    current->prev->next = current->next;
                } else {
                    table[index] = current->next;
                }

                if (current->next) {
                    current->next->prev = current->prev;
                }

                delete current;
                size--;

                // Shrink if less than 25% full
                if (size > 0 && size * 4 <= capacity && capacity > 16) {
                    resize(capacity / 2);
                }
                return;
            }
            current = current->next;
        }

        throw std::runtime_error("Key not found");
    }

    int getSize() const { return size; }
    int getCapacity() const { return capacity; }
};

int main() {
    HashTable ht;

    // Insert integer key-value pairs
    ht.insert(5, 50);
    ht.insert(15, 150);
    ht.insert(25, 250);

    // Print size
    std::cout << "Size of hash table: " << ht.getSize() << std::endl;

    // Get and print a value
    std::cout << "Value for key 15: " << ht.get(15) << std::endl;

    // Remove a key
    ht.remove(15);

    // Print new size
    std::cout << "Size after removal: " << ht.getSize() << std::endl;

    return 0;
}
