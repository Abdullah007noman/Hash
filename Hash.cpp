#include <iostream>
#include <functional>
#include <stdexcept>

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

    void print() {
        std::cout << "Hash Table Contents:" << std::endl;
        for (int i = 0; i < capacity; i++) {
            Node* current = table[i];
            if (current) {
                std::cout << "Bucket " << i << ": ";
                while (current) {
                    std::cout << "(" << current->key << ":" << current->value << ") ";
                    current = current->next;
                }
                std::cout << std::endl;
            }
        }
    }

    int getSize() const { return size; }
    int getCapacity() const { return capacity; }
};

int main() {
    // Create hash table
    HashTable ht;

    // Large set of numbers to demonstrate functionality
    int keys[] = {5, 15, 25, 35, 45, 55, 65, 75, 85, 95, 
                  105, 115, 125, 135, 145, 155, 165, 175, 185, 195};
    int values[] = {50, 150, 250, 350, 450, 550, 650, 750, 850, 950,
                    1050, 1150, 1250, 1350, 1450, 1550, 1650, 1750, 1850, 1950};

    // Insert multiple elements
    std::cout << "Inserting elements:" << std::endl;
    for (int i = 0; i < 20; i++) {
        ht.insert(keys[i], values[i]);
        std::cout << "Inserted (" << keys[i] << ":" << values[i] << ")" << std::endl;
    }

    // Print initial size
    std::cout << "\nSize of hash table: " << ht.getSize() << std::endl;

    // Print the entire hash table
    ht.print();

    // Retrieve and print a specific value
    std::cout << "\nValue for key 15: " << ht.get(15) << std::endl;

    // Remove some keys
    std::cout << "\nRemoving keys 15 and 95:" << std::endl;
    ht.remove(15);
    ht.remove(95);

    // Print new size
    std::cout << "Size after removal: " << ht.getSize() << std::endl;

    // Print updated hash table
    ht.print();

    return 0;
}
