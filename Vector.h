#ifndef VECTOR_H
#define VECTOR_H
#include <iostream>
using namespace std;

template <typename T>
class vector
{
private:
    T *data;
    size_t size_;
    size_t capacity_;

public:
    vector() : data(nullptr), size_(0), capacity_(1) {
        data = new T[capacity_];
    }

    vector(const T *array, size_t n) : size_(0), capacity_(n) {
        data = new T[capacity_];
        for (size_t i = 0; i < n; ++i) {
            push_back(array[i]);
        }
    }

    vector(size_t n, const T& value = T()) : size_(n), capacity_(n) {
        data = new T[capacity_];
        for (size_t i = 0; i < n; ++i) {
            data[i] = value;
        }
    }
    vector(initializer_list<T> list) : size_(0), capacity_(list.size()) {
        data = new T[capacity_];
        for (const auto &item : list) {
            push_back(item);
        }
    }
    ~vector();

    size_t size() const;
    size_t capacity() const;
    bool empty() const;
    void push_back(const T &value);
    void pop_back();
    const T &get(size_t index) const;
    void set(size_t index, const T &value);
    void clear();
    T &operator[](size_t index);
    const T *begin() const
    {
        return data;
    }

    const T *end() const
    {
        return data + size_;
    }
    const T &operator[](size_t index) const;
};
#endif