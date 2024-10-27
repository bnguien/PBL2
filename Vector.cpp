#include "Vector.h"

template <typename T>
vector<T>::vector() : data(nullptr), size_(0), capacity_(0) {}

template <typename T>
vector<T>::vector(const T* array, size_t n) : size_(n), capacity_(n) {
    data = new T[capacity_];
    std::copy(array, array + n, data);
}

template <typename T>
vector<T>::vector(size_t n, const T& value) : size_(n), capacity_(n) {
    data = new T[capacity_];
    std::fill(data, data + size_, value);
}

template <typename T>
vector<T>::vector(std::initializer_list<T> list) : size_(0), capacity_(list.size()) {
    data = new T[capacity_];
    for (const auto& item : list) {
        push_back(item);
    }
}

template <typename T>
vector<T>::~vector() {
    delete[] data;
}

template <typename T>
size_t vector<T>::size() const {
    return size_;
}

template <typename T>
size_t vector<T>::capacity() const {
    return capacity_;
}

template <typename T>
bool vector<T>::empty() const {
    return size_ == 0;
}

template <typename T>
void vector<T>::push_back(const T& value) {
    if (size_ == capacity_) {
        resize(capacity_ == 0 ? 1 : capacity_ * 2);
    }
    data[size_++] = value;
}

template <typename T>
void vector<T>::pop_back() {
    if (size_ > 0) {
        --size_;
    }
}

template <typename T>
T& vector<T>::operator[](size_t index) {
    if (index >= size_) {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

template <typename T>
const T& vector<T>::operator[](size_t index) const {
    if (index >= size_) {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

template <typename T>
T* vector<T>::begin() {
    return data;
}

template <typename T>
T* vector<T>::end() {
    return data + size_;
}

template <typename T>
const T* vector<T>::begin() const {
    return data;
}

template <typename T>
const T* vector<T>::end() const {
    return data + size_;
}

template <typename T>
void vector<T>::clear() {
    size_ = 0;
}

template <typename T>
void vector<T>::resize(size_t newCapacity) {
    T* newData = new T[newCapacity];
    std::copy(data, data + size_, newData);
    delete[] data;
    data = newData;
    capacity_ = newCapacity;
}
template <typename T>
T& vector<T>::get(size_t index) {
    if (index >= size_) {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

template <typename T>
const T& vector<T>::get(size_t index) const {
    if (index >= size_) {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}