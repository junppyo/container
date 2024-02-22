#ifndef RANDOMACCESSITERATOR_HPP
#define RANDOMACCESSITERATOR_HPP

#include "Iterator.hpp"

namespace ft
{
    template <class T>
    class RandomAccessIterator : public ft::iterator<ft::random_access_iterator_tag, T>
    {
        public:
            typedef typename ft::iterator<ft::random_access_iterator_tag, T>::value_type          value_type;
            typedef typename ft::iterator<ft::random_access_iterator_tag, T>::difference_type     difference_type;
            typedef typename ft::iterator<ft::random_access_iterator_tag, T>::pointer             pointer;
            typedef typename ft::iterator<ft::random_access_iterator_tag, T>::reference           reference;
            typedef typename ft::iterator<ft::random_access_iterator_tag, T>::iterator_category   iterator_category;
        protected:
            pointer ptr;
        public:
            RandomAccessIterator(pointer ptr = nullptr) : ptr(ptr) {};
            RandomAccessIterator(const RandomAccessIterator& other) : ptr(other.ptr) { };
            const pointer& base() const { return ptr; }
            operator RandomAccessIterator< const T >() const { return this->ptr; }
            RandomAccessIterator& operator++() { ++ptr; return *this; };
            RandomAccessIterator operator++(int) { RandomAccessIterator tmp = *(this); ++(*this); return tmp; };
            RandomAccessIterator& operator--() { --ptr; return *this; };
            RandomAccessIterator operator--(int) { RandomAccessIterator tmp = *(this); --(*this); return tmp; };
            reference operator*() const { return *ptr; };
            pointer operator->() { return &(operator*()); };
            RandomAccessIterator& operator=(const RandomAccessIterator& other) { this->ptr = other.ptr; return *this; };
            bool operator==(RandomAccessIterator<T>& other) { return (this->ptr == other.ptr); };
            bool operator==(const RandomAccessIterator<T>& other) const { return (this->ptr == other.ptr); };
            bool operator!=(RandomAccessIterator<T>& other) { return (this->ptr != other.ptr); };
            bool operator!=(const RandomAccessIterator<T>& other) const { return (this->ptr != other.ptr); };
            reference operator[](difference_type n) const { return ptr[n]; };
            RandomAccessIterator& operator+=(difference_type n) { 
                ptr += n;
                return *this;
            };
            RandomAccessIterator& operator-=(difference_type n) { 
                ptr -= n;
                return *this;
            };
            RandomAccessIterator operator+(difference_type n) const {
                return RandomAccessIterator(this->ptr + n);
            };
            RandomAccessIterator operator-(difference_type n) const {
                return RandomAccessIterator(this->ptr - n);
            };
    };

    template <class T1, class T2>
    bool operator==(const RandomAccessIterator<T1>& lhs, const RandomAccessIterator<T2>& rhs)
    {
        return (lhs.base() == rhs.base());
    }
    template <class T1, class T2>
    bool operator!=(const RandomAccessIterator<T1>& lhs, const RandomAccessIterator<T2>& rhs)
    {
        return (lhs.base() != rhs.base());
    }
    template <class T1, class T2>
    bool operator<(const RandomAccessIterator<T1>& lhs, const RandomAccessIterator<T2>& rhs)
    {
        return (lhs.base() < rhs.base());
    }
    template <class T1, class T2>
    bool operator>(const RandomAccessIterator<T1>& lhs, const RandomAccessIterator<T2>& rhs)
    {
        return (lhs.base() > rhs.base());
    }
    template <class T1, class T2>
    bool operator<=(const RandomAccessIterator<T1>& lhs, const RandomAccessIterator<T2>& rhs)
    {
        return (lhs.base() <= rhs.base());
    }
    template <class T1, class T2>
    bool operator>=(const RandomAccessIterator<T1>& lhs, const RandomAccessIterator<T2>& rhs)
    {
        return (lhs.base() >= rhs.base());
    }
    template <class T1, class T2>
    typename RandomAccessIterator<T1>::difference_type operator-(const RandomAccessIterator<T2>& lhs, const RandomAccessIterator<T1>& rhs) {
        return lhs.base() - rhs.base();
    }
    template <class T1, class T2>
    typename RandomAccessIterator<T1>::difference_type operator+(const RandomAccessIterator<T2>& lhs, const RandomAccessIterator<T1>& rhs) {
        return lhs.base() + rhs.base();
    }
    template <class Iterator>
    RandomAccessIterator<Iterator> operator+(typename RandomAccessIterator<Iterator>::difference_type n, const RandomAccessIterator<Iterator>& iter)
    {
        return iter + n;
    }
    
    template <class Iterator>
    RandomAccessIterator<Iterator> operator-(typename RandomAccessIterator<Iterator>::difference_type n, const RandomAccessIterator<Iterator>& iter) 
    {
        return iter - n;
    }

}

#endif