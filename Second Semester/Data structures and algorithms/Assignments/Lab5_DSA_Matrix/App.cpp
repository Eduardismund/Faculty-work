#include <iostream>
#include <stdexcept>

using namespace std;

class Vector {
    int* elems;
    int size;
    int capacity; // Add capacity to track allocated size

public:
    Vector() : size(0), capacity(10), elems(new int[capacity]) {}

    // Copy constructor
    Vector(const Vector& other) : size(other.size), capacity(other.capacity), elems(new int[other.capacity]) {
        for (int i = 0; i < size; ++i) {
            elems[i] = other.elems[i];
        }
    }

    // Assignment operator
    Vector& operator=(const Vector& other) {
        if (this != &other) {
            // Deallocate current memory
            delete[] elems;

            // Copy size and capacity
            size = other.size;
            capacity = other.capacity;

            // Allocate new memory and copy elements
            elems = new int[capacity];
            for (int i = 0; i < size; ++i) {
                elems[i] = other.elems[i];
            }
        }
        return *this;
    }

    void add(int elem) {
        // Check if resizing is necessary
        if (size >= capacity) {
            int* new_elems = new int[capacity * 2]; // Double the capacity
            for (int i = 0; i < size; ++i) {
                new_elems[i] = elems[i];
            }
            delete[] elems;
            elems = new_elems;
            capacity *= 2;
        }
        elems[size++] = elem;
    }

    int& operator[](int pos) {
        if (pos < 0 || pos >= size)
            throw std::runtime_error("Index out of bounds.");
        return elems[pos];
    }

    ~Vector() {
        delete[] elems;
    }
};

int main() {
    Vector v1;
    v1.add(0);
    v1.add(1);

    Vector v2 = v1;

    try {
        v1[0] = 2;
        cout << v1[0] << " " << v1[1] << " ";
        cout << v2[0] << " " << v2[1] << " ";
    } catch (std::runtime_error& e) {
        cout << e.what();
        return 1; // Return a non-zero code upon exception
    }

    return 0;
}
