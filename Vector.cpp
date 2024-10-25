#include "Vector.h"
#include <stdexcept> //xử lí ngoại lệ

template <typename T>
size_t vector<T>::size() const
{
    return size_;
}

template <typename T>
size_t vector<T>::capacity() const
{
    return capacity_;
}

template <typename T>
bool vector<T>::empty() const
{
    return size_ == 0;
}

template <typename T>
void vector<T>::push_back(const T &value)
{
    if (size_ == capacity_)
    {
        size_t newCapacity = (capacity_ == 0 ? 1 : capacity_ * 2);
        T *newData = new T[newCapacity];

        for (size_t i = 0; i < size_; ++i)
        {
            newData[i] = data[i];
        }

        delete[] data;
        data = newData;
        capacity_ = newCapacity;
    }
    data[size_++] = value;
}

template <typename T>
void vector<T>::pop_back()
{
    if (size_ > 0)
    {
        --size_;
    }
}

template <typename T>
T &vector<T>::operator[](size_t index)
{
    return data[index];
}

template <typename T>
const T &vector<T>::operator[](size_t index) const
{
    return data[index];
}

template <typename T>
const T &vector<T>::get(size_t index) const
{
    if (index >= size_)
    {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

template <typename T>
void vector<T>::set(size_t index, const T &value)
{
    if (index >= size_)
    {
        throw std::out_of_range("Index out of range");
    }
    data[index] = value;
}

template <typename T>
void vector<T>::clear()
{
    size_ = 0;
}