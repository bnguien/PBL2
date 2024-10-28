#include "Vector.h"

template <typename T>
vector<T>::vector() : data_(nullptr), size_(0), capacity_(0) {}

template <typename T>
vector<T>::vector(size_t n) : size_(n), capacity_(n) {
    data_ = new T[capacity_];
    for (size_t i = 0; i < size_; ++i) {
        data_[i] = T();
    }
}

template <typename T>
vector<T>::vector(size_t n, const T& value) : size_(n), capacity_(n) {
    data_ = new T[capacity_];
    std::fill(data_, data_ + size_, value);
}

template <typename T>
vector<T>::vector(std::initializer_list<T> list)
    : size_(list.size()), capacity_(list.size()) {
    data_ = new T[capacity_];
    std::copy(list.begin(), list.end(), data_);
}

template <typename T>
vector<T>::vector(const vector<T>& other)
    : size_(other.size_), capacity_(other.capacity_) {
    data_ = new T[capacity_];
    std::copy(other.data_, other.data_ + size_, data_);
}

template <typename T>
vector<T>::vector(vector<T>&& other) noexcept
    : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
    other.data_ = nullptr;
    other.size_ = other.capacity_ = 0;
}

template <typename T>
vector<T>::~vector() {
    delete[] data_;
}

// Assignment operators
template <typename T>
vector<T>& vector<T>::operator=(const vector<T>& other) {
    if (this != &other) {
        delete[] data_;
        size_ = other.size_;
        capacity_ = other.capacity_;
        data_ = new T[capacity_];
        std::copy(other.data_, other.data_ + size_, data_);
    }
    return *this;
}

template <typename T>
vector<T>& vector<T>::operator=(vector<T>&& other) noexcept {
    if (this != &other) {
        delete[] data_;
        data_ = other.data_;
        size_ = other.size_;
        capacity_ = other.capacity_;
        other.data_ = nullptr;
        other.size_ = other.capacity_ = 0;
    }
    return *this;
}

template <typename T>
vector<T>& vector<T>::operator=(std::initializer_list<T> list) {
    delete[] data_;
    size_ = list.size();
    capacity_ = size_;
    data_ = new T[capacity_];
    std::copy(list.begin(), list.end(), data_);
    return *this;
}

template <typename T>
T& vector<T>::at(size_t pos) {
    if (pos >= size_) {
        throw std::out_of_range("Index out of range");
    }
    return data_[pos];
}

template <typename T>
size_t vector<T>::size() const noexcept {
    return size_;
}

template <typename T>
size_t vector<T>::capacity() const noexcept {
    return capacity_;
}

template <typename T>
bool vector<T>::empty() const noexcept {
    return size_ == 0;
}

template <typename T>
void vector<T>::clear() noexcept {
    size_ = 0;
}

template <typename T>
T* vector<T>::begin() noexcept {
    return data_;
}

template <typename T>
const T* vector<T>::begin() const noexcept {
    return data_;
}

template <typename T>
T* vector<T>::end() noexcept {
    return data_ + size_;
}

template <typename T>
const T* vector<T>::end() const noexcept {
    return data_ + size_;
}

template <typename T>
void vector<T>::realloc(size_t newCapacity) {
    T* newData = new T[newCapacity];
    size_t copySize = std::min(size_, newCapacity);
    
    for (size_t i = 0; i < copySize; ++i) {
        newData[i] = std::move(data_[i]);
    }
    
    delete[] data_;
    data_ = newData;
    capacity_ = newCapacity;
}

template <typename T>
void vector<T>::push_back(const T& value) {
    if (size_ >= capacity_) {
        size_t newCapacity = (capacity_ == 0) ? 1 : capacity_ * 2;
        realloc(newCapacity);
    }
    data_[size_++] = value;
}

template <typename T>
void vector<T>::push_back(T&& value) {
    if (size_ >= capacity_) {
        size_t newCapacity = (capacity_ == 0) ? 1 : capacity_ * 2;
        realloc(newCapacity);
    }
    data_[size_++] = std::move(value);
}

template <typename T>
void vector<T>::pop_back() {
    if (size_ > 0) {
        --size_;
    }
}

template <typename T>
T& vector<T>::operator[](size_t pos) {
    return data_[pos];
}

template <typename T>
const T& vector<T>::operator[](size_t pos) const {
    return data_[pos];
}

template <typename T>
T& vector<T>::get(size_t index) {
    if (index >= size_) {
        throw std::out_of_range("Index out of range");
    }
    return data_[index];
}

template <typename T>
const T& vector<T>::get(size_t index) const {
    if (index >= size_) {
        throw std::out_of_range("Index out of range");
    }
    return data_[index];
}

template <typename T>
T& vector<T>::front() {
    return data_[0];
}

template <typename T>
const T& vector<T>::front() const {
    return data_[0];
}

template <typename T>
T& vector<T>::back() {
    return data_[size_ - 1];
}

template <typename T>
const T& vector<T>::back() const {
    return data_[size_ - 1];
}

template <typename T>
void vector<T>::reserve(size_t new_cap) {
    if (new_cap > capacity_) {
        realloc(new_cap);
    }
}

template <typename T>
void vector<T>::shrink_to_fit() {
    if (size_ < capacity_) {
        realloc(size_);
    }
}

template <typename T>
void vector<T>::resize(size_t count) {
    resize(count, T());
}

template <typename T>
void vector<T>::resize(size_t count, const T& value) {
    if (count > capacity_) {
        reserve(count);
    }
    if (count > size_) {
        std::fill(data_ + size_, data_ + count, value);
    }
    size_ = count;
}

template <typename T>
void vector<T>::print() const {
    for (size_t i = 0; i < size_; ++i) {
        std::cout << data_[i] << " ";
    }
    std::cout << std::endl;
}
