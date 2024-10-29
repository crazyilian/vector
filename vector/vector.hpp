#pragma once

#include <compare>
#include <cstddef>
#include <cstdlib>
#include <initializer_list>
#include <algorithm>

template<typename T>
class Vector {
public:
    using value_type = T;
    using size_type = size_t;
    using difference_type = ptrdiff_t;

    class iterator {
    public:
        using value_type = Vector::value_type;

        value_type *pointer;

        explicit iterator(value_type *pointer);
        iterator();

        value_type &operator*() const;
        value_type *operator->() const;

        iterator &operator=(iterator other);

        iterator &operator++();
        iterator operator++(int);
        iterator &operator--();
        iterator operator--(int);

        iterator operator+(difference_type shift) const;
        iterator operator-(difference_type shift) const;
        difference_type operator-(iterator other) const;
        iterator &operator+=(difference_type shift);
        iterator &operator-=(difference_type shift);

        bool operator==(const iterator &) const;
        std::strong_ordering operator<=>(const iterator &other) const;
    };

    class reverse_iterator {
    public:
        using value_type = Vector::value_type;

        value_type *pointer;

        explicit reverse_iterator(value_type *pointer);
        reverse_iterator();

        value_type &operator*() const;
        value_type *operator->() const;

        reverse_iterator &operator=(reverse_iterator other);

        reverse_iterator &operator++();
        reverse_iterator operator++(int);
        reverse_iterator &operator--();
        reverse_iterator operator--(int);

        reverse_iterator operator+(difference_type shift) const;
        reverse_iterator operator-(difference_type shift) const;
        difference_type operator-(reverse_iterator other) const;
        reverse_iterator &operator+=(difference_type shift);
        reverse_iterator &operator-=(difference_type shift);

        bool operator==(const reverse_iterator &) const;
        std::strong_ordering operator<=>(const reverse_iterator &other) const;
    };

    Vector();
    explicit Vector(size_type size);
    Vector(std::initializer_list<value_type> list);
    Vector(const Vector &other);
    Vector &operator=(const Vector &other);
    ~Vector();

    size_type size() const;
    size_type capacity() const;
    bool empty() const;

    const value_type *data() const;

    const value_type &operator[](size_type position) const;
    value_type &operator[](size_type position);

    bool operator==(const Vector &other) const;
    bool operator<(const Vector &other) const;
    std::strong_ordering operator<=>(const Vector &other) const;

    void reserve(size_type new_capacity);
    void clear();
    void assign(size_type new_size, const value_type &new_elements);
    void resize(size_type new_size);
    void shrink_to_fit();

    void push_back(const value_type &new_element);
    void insert(iterator pos, const value_type &new_element);
    void pop_back();
    void erase(iterator pos);

    void swap(Vector &other) noexcept;

    iterator begin() const;
    iterator end() const;
    reverse_iterator rbegin() const;
    reverse_iterator rend() const;

private:
    iterator begin_;
    size_type size_;
    size_type capacity_;
};


// Vector<T>::iterator

template<typename T>
Vector<T>::iterator::iterator() : pointer(nullptr) {
}

template<typename T>
Vector<T>::iterator::iterator(T *pointer) : pointer(pointer) {
}

template<typename T>
typename Vector<T>::value_type &Vector<T>::iterator::operator*() const {
    return *pointer;
}

template<typename T>
typename Vector<T>::value_type *Vector<T>::iterator::operator->() const {
    return pointer;
}

template<typename T>
typename Vector<T>::iterator &Vector<T>::iterator::operator=(iterator other) {
    pointer = other.pointer;
    return *this;
}

template<typename T>
typename Vector<T>::iterator &Vector<T>::iterator::operator++() {
    ++pointer;
    return *this;
}

template<typename T>
typename Vector<T>::iterator Vector<T>::iterator::operator++(int) {
    iterator iterator_copy = *this;
    ++pointer;
    return iterator_copy;
}

template<typename T>
typename Vector<T>::iterator &Vector<T>::iterator::operator--() {
    --pointer;
    return *this;
}

template<typename T>
typename Vector<T>::iterator Vector<T>::iterator::operator--(int) {
    iterator iterator_copy = *this;
    --pointer;
    return iterator_copy;
}

template<typename T>
typename Vector<T>::iterator Vector<T>::iterator::operator+(difference_type shift) const {
    return Vector::iterator(pointer + shift);
}

template<typename T>
typename Vector<T>::iterator Vector<T>::iterator::operator-(difference_type shift) const {
    return Vector::iterator(pointer - shift);
}

template<typename T>
typename Vector<T>::difference_type Vector<T>::iterator::operator-(iterator other) const {
    return pointer - other.pointer;
}

template<typename T>
typename Vector<T>::iterator &Vector<T>::iterator::operator+=(difference_type shift) {
    pointer += shift;
    return *this;
}

template<typename T>
typename Vector<T>::iterator &Vector<T>::iterator::operator-=(difference_type shift) {
    pointer -= shift;
    return *this;
}

template<typename T>
bool Vector<T>::iterator::operator==(const iterator &other) const {
    return pointer == other.pointer;
}

template<typename T>
std::strong_ordering Vector<T>::iterator::operator<=>(const iterator &other) const {
    return pointer <=> other.pointer;
}


// Vector<T>::reverse_iterator

template<typename T>
Vector<T>::reverse_iterator::reverse_iterator() : pointer(nullptr) {
}

template<typename T>
Vector<T>::reverse_iterator::reverse_iterator(T *pointer) : pointer(pointer) {
}

template<typename T>
typename Vector<T>::value_type &Vector<T>::reverse_iterator::operator*() const {
    return *pointer;
}

template<typename T>
typename Vector<T>::value_type *Vector<T>::reverse_iterator::operator->() const {
    return pointer;
}

template<typename T>
typename Vector<T>::reverse_iterator &Vector<T>::reverse_iterator::operator=(reverse_iterator other) {
    pointer = other.pointer;
    return *this;
}

template<typename T>
typename Vector<T>::reverse_iterator &Vector<T>::reverse_iterator::operator++() {
    --pointer;
    return *this;
}

template<typename T>
typename Vector<T>::reverse_iterator Vector<T>::reverse_iterator::operator++(int) {
    reverse_iterator iterator_copy = *this;
    --pointer;
    return iterator_copy;
}

template<typename T>
typename Vector<T>::reverse_iterator &Vector<T>::reverse_iterator::operator--() {
    ++pointer;
    return *this;
}

template<typename T>
typename Vector<T>::reverse_iterator Vector<T>::reverse_iterator::operator--(int) {
    reverse_iterator iterator_copy = *this;
    ++pointer;
    return iterator_copy;
}

template<typename T>
typename Vector<T>::reverse_iterator Vector<T>::reverse_iterator::operator+(difference_type shift) const {
    return Vector::reverse_iterator(pointer - shift);
}

template<typename T>
typename Vector<T>::reverse_iterator Vector<T>::reverse_iterator::operator-(difference_type shift) const {
    return Vector::reverse_iterator(pointer + shift);
}

template<typename T>
typename Vector<T>::difference_type Vector<T>::reverse_iterator::operator-(reverse_iterator other) const {
    return other.pointer - pointer;
}

template<typename T>
typename Vector<T>::reverse_iterator &Vector<T>::reverse_iterator::operator+=(difference_type shift) {
    pointer -= shift;
    return *this;
}

template<typename T>
typename Vector<T>::reverse_iterator &Vector<T>::reverse_iterator::operator-=(difference_type shift) {
    pointer += shift;
    return *this;
}

template<typename T>
bool Vector<T>::reverse_iterator::operator==(const reverse_iterator &other) const {
    return pointer == other.pointer;
}

template<typename T>
std::strong_ordering Vector<T>::reverse_iterator::operator<=>(const reverse_iterator &other) const {
    return other.pointer <=> pointer;
}


// Vector<T>

template<typename T>
Vector<T>::Vector() : begin_(nullptr), size_(0), capacity_(0) {
}

template<typename T>
Vector<T>::Vector(const size_type size) : begin_(nullptr), size_(0), capacity_(0) {
    reserve(size);
    size_ = size;
    std::fill(begin(), end(), value_type());
}

template<typename T>
Vector<T>::Vector(std::initializer_list<T> list) : begin_(nullptr), size_(0), capacity_(0) {
    reserve(list.size());
    size_ = list.size();
    std::copy(list.begin(), list.end(), begin());
}

template<typename T>
Vector<T>::Vector(const Vector &other) : begin_(nullptr), size_(0), capacity_(0) {
    *this = other;
}

template<typename T>
Vector<T> &Vector<T>::operator=(const Vector &other) {
    if (this == &other) {
        return *this;
    }
    reserve(other.size_);
    size_ = other.size_;
    std::copy(other.begin(), other.end(), begin());
    return *this;
}

template<typename T>
Vector<T>::~Vector() {
    free(begin_.pointer);
}

template<typename T>
typename Vector<T>::size_type Vector<T>::size() const {
    return size_;
}

template<typename T>
typename Vector<T>::size_type Vector<T>::capacity() const {
    return capacity_;
}

template<typename T>
bool Vector<T>::empty() const {
    return size_ == 0;
}


template<typename T>
const typename Vector<T>::value_type *Vector<T>::data() const {
    return begin().pointer;
}

template<typename T>
const typename Vector<T>::value_type &Vector<T>::operator[](size_type position) const {
    return begin().pointer[position];
}

template<typename T>
typename Vector<T>::value_type &Vector<T>::operator[](size_type position) {
    return begin().pointer[position];
}

template<typename T>
bool Vector<T>::operator==(const Vector &other) const {
    return std::equal(begin().pointer, end().pointer, other.begin().pointer, other.end().pointer);
}

template<typename T>
bool Vector<T>::operator<(const Vector &other) const {
    return std::lexicographical_compare(begin().pointer, end().pointer, other.begin().pointer, other.end().pointer);
}

template<typename T>
std::strong_ordering Vector<T>::operator<=>(const Vector &other) const {
    return *this == other
               ? std::strong_ordering::equal
               : *this < other
                     ? std::strong_ordering::less
                     : std::strong_ordering::greater;
}

template<typename T>
void Vector<T>::reserve(const size_type new_capacity) {
    if (capacity_ >= new_capacity) {
        return;
    }
    auto ptr = static_cast<value_type *>(reallocarray(begin().pointer, new_capacity, sizeof(value_type)));
    capacity_ = new_capacity;
    begin_ = iterator(ptr);
}

template<typename T>
void Vector<T>::clear() {
    size_ = 0;
}

template<typename T>
void Vector<T>::assign(size_type new_size, const value_type &new_elements) {
    if (new_size <= size_) {
        size_ = new_size;
        return;
    }
    if (new_size > capacity_) {
        reserve(std::max(capacity_ * 2, new_size));
    }
    std::fill(begin() + size_, begin() + new_size, new_elements);
    size_ = new_size;
}

template<typename T>
void Vector<T>::resize(const size_type new_size) {
    assign(new_size, value_type());
}

template<typename T>
void Vector<T>::shrink_to_fit() {
    if (size_ == capacity_) {
        return;
    }
    auto ptr = static_cast<value_type *>(reallocarray(begin().pointer, size_, sizeof(value_type)));
    capacity_ = size_;
    begin_ = iterator(ptr);
}

template<typename T>
void Vector<T>::push_back(const T &new_element) {
    if (size_ == capacity_) {
        reserve(capacity_ == 0 ? 1 : capacity_ * 2);
    }
    (*this)[size_++] = new_element;
}

template<typename T>
void Vector<T>::insert(const iterator pos, const T &new_element) {
    size_t ind = pos - begin();
    if (size_ == capacity_) {
        reserve(capacity_ == 0 ? 1 : capacity_ * 2);
    }
    ++size_;
    std::copy_backward(begin() + ind, end() - 1, end());
    (*this)[ind] = new_element;
}

template<typename T>
void Vector<T>::pop_back() {
    --size_;
}

template<typename T>
void Vector<T>::erase(const iterator pos) {
    std::copy(pos + 1, end(), pos);
    --size_;
}

template<typename T>
void Vector<T>::swap(Vector &other) noexcept {
    std::swap(begin_, other.begin_);
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
}

template<typename T>
typename Vector<T>::iterator Vector<T>::begin() const {
    return begin_;
}

template<typename T>
typename Vector<T>::iterator Vector<T>::end() const {
    return begin() + size_;
}

template<typename T>
typename Vector<T>::reverse_iterator Vector<T>::rbegin() const {
    return rend() - size_;
}

template<typename T>
typename Vector<T>::reverse_iterator Vector<T>::rend() const {
    return reverse_iterator(begin_.pointer) + 1;
}
