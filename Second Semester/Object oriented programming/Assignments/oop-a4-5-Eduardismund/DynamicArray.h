#pragma once

//This template class represents a dynamic array that can hold elements of any type (TypeOfElement)
template <typename TypeOfElement> class DynamicVector{
private:
        TypeOfElement* elements;
        int size{};
        int capacity{};
        void resize(int newCapacity);
public:
    explicit DynamicVector(int capacity=10);
    DynamicVector(const DynamicVector& other);
    DynamicVector& operator=(const DynamicVector& other);
    ~DynamicVector();
    //Functions

    void addElement(const TypeOfElement& newElement);
    void addElementAtPosition(const TypeOfElement& newElement, int position);
    void removeElement1(const TypeOfElement& element);
    void removeElementFromPosition(int position);
    TypeOfElement* findElement(const TypeOfElement& element);

    //Operators
    TypeOfElement& operator[](int position);
    const TypeOfElement& operator[](int position) const;
    void setElement(int position, const TypeOfElement& newElement);

    //Getters
    int getSize() const;
    int getCapacity() const;

};

//The constructor initializes a DynamicVector object with a specified initial capacity. If no capacity is provided, it defaults to 10.
template<typename TypeOfElement> DynamicVector<TypeOfElement>::DynamicVector(int capacity): size{0}, capacity{capacity}
{
    this->elements = new TypeOfElement[capacity];
}

//It performs a deep copy of the elements from the source object to the newly created object.
template<typename TypeOfElement> DynamicVector<TypeOfElement>::DynamicVector(const DynamicVector& other) {
    this->size = other.size;
    this->capacity = other.capacity;
    this->elements = new TypeOfElement[this->capacity];
    for(int i = 0; i< this->size; i++)
        this->elements[i] = other.elements[i];
}

// The assignment operator overloads the assignment (=) operator for DynamicVector objects.
template<typename TypeOfElement> DynamicVector<TypeOfElement> &DynamicVector<TypeOfElement>::operator=(const
        DynamicVector& other){
    if (this != &other) {
        this->size = other.size;
        this->capacity = other.capacity;
        delete[] this->elements;
        this->elements = new TypeOfElement[this->capacity];
        for (int i = 0; i < this->size; i++)
            this->elements[i] = other.elements[i];
    }
    return *this;
}

//The destructor deallocates the dynamically allocated memory used by the DynamicVector object
template<typename TypeOfElement> DynamicVector<TypeOfElement>::~DynamicVector() {
    delete[] this->elements;
}

// Adds a new element to the end of the array. If the array is full, it resizes the array to accommodate more elements.
template<typename TypeOfElement>
void DynamicVector<TypeOfElement>::addElement(const TypeOfElement &newElement) {
    if(this->size == this->capacity)
        this->resize(this->capacity*2);
    this->elements[this->size++] = newElement;
}

//resize
template<typename TypeOfElement>
void DynamicVector<TypeOfElement>::resize(int newCapacity) {
    auto* newCopy = new TypeOfElement[newCapacity];
    for(int i = 0; i<this->size; i++)
        newCopy[i] = this->elements[i];
    delete[] this->elements;
    this->capacity = newCapacity;
    this->elements = newCopy;
}

//Removes the first occurrence of a specified element from the array
template<typename TypeOfElement>
void DynamicVector<TypeOfElement>::removeElement1(const TypeOfElement &element) {
    int position=0;
    for(int i = 0; i < this->size; i++)
        if(this->elements[i] == element)
            position = i;
    this->removeElementFromPosition(position);
}

//Removes the element at a specified position from the array.
template<typename TypeOfElement>
void DynamicVector<TypeOfElement>::removeElementFromPosition(int position) {
    for(int i = position; i< this->size-1; i++)
        this->elements[i] = this->elements[i+1];
    this->size--;
    if(this->size == this->capacity/4)
        this->resize(this->capacity/2);
}

//Searches for the first occurrence of a specified element in the array and returns a pointer to it.
template<typename TypeOfElement>
TypeOfElement *DynamicVector<TypeOfElement>::findElement(const TypeOfElement &element) {
    for(int i = 0; i<this->size; i++)
        if(this->elements[i] == element)
            return &this->elements[i];
    return nullptr;
}

//Adds a new element at a specified position in the array.
template<typename TypeOfElement>
void DynamicVector<TypeOfElement>::addElementAtPosition(const TypeOfElement &newElement, int position) {
    if(this->size == this->capacity)
        this->resize(this->capacity*2);
    for(int i = this->size; i>position;i--)
        this->elements[i] = this->elements[i-1];
    this->elements[position] = newElement;
    this->size++;
}

//get capacity
template<typename TypeOfElement>
int DynamicVector<TypeOfElement>::getCapacity() const {
    return this->capacity;
}

//get size
template<typename TypeOfElement>
int DynamicVector<TypeOfElement>::getSize() const {
    return this->size;
}

//Overloads the subscript operator ([]) to provide array-like access to elements of the DynamicVector.
template<typename TypeOfElement>
TypeOfElement &DynamicVector<TypeOfElement>::operator[](int position) {
    return this->elements[position];
}

//Overloads the subscript operator ([]) to provide array-like access to const elements of the DynamicVector.
template<typename TypeOfElement>
const TypeOfElement &DynamicVector<TypeOfElement>::operator[](int position) const {
    return this->elements[position];
}

//set element
template<typename TypeOfElement>
void DynamicVector<TypeOfElement>::setElement(int position, const TypeOfElement &newElement) {
    this->elements[position] = newElement;
}
