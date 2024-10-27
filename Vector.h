#ifndef VECTOR_H
#define VECTOR_H

#include "Function.h"

using namespace std;

template <typename T>
class vector
{
private:
    T *data;
    size_t size_;
    size_t capacity_;

public:
    vector();
    vector(const T *array, size_t n);
    vector(size_t n, const T &value = T());
    vector(initializer_list<T> list);
    ~vector();

    size_t size() const;
    size_t capacity() const;
    bool empty() const;
    void push_back(const T &value);
    void pop_back();
    T &get(size_t index);
    const T &get(size_t index) const;
    void set(size_t index, const T &value);
    void clear();

    T &operator[](size_t index);
    const T &operator[](size_t index) const;

    T *begin() const;
    T *end() const;
};

#endif
