#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <iostream>
#include <cstddef>

namespace ft
{
    struct input_iterator_tag { };
    struct output_iterator_tag { };
    struct forward_iterator_tag : public input_iterator_tag { };
    struct bidirectional_iterator_tag : public forward_iterator_tag { };
    struct random_access_iterator_tag : public bidirectional_iterator_tag { };

    template <class Category, class T, class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T&>
    struct iterator {
        typedef T         value_type;
        typedef Distance  difference_type;
        typedef Pointer   pointer;
        typedef Reference reference;
        typedef Category  iterator_category;
    };

    template <class Iterator>
    struct iterator_traits {
        typedef typename Iterator::iterator_category    iterator_category;
        typedef typename Iterator::value_type           value_type;
        typedef typename Iterator::pointer              pointer;
        typedef typename Iterator::reference            reference;
        typedef typename Iterator::difference_type      difference_type;
    };

    template <class T>
    struct iterator_traits<T*> {
        typedef ptrdiff_t                   difference_type;
        typedef T                           value_type;
        typedef T*                          pointer;
        typedef T&                          reference;
        typedef random_access_iterator_tag  iterator_category;
    };
    
    template <class T>
    struct iterator_traits<const T*> {
        typedef ptrdiff_t                   difference_type;
        typedef T                           value_type;
        typedef const T*                    pointer;
        typedef const T&                    reference;
        typedef random_access_iterator_tag  iterator_category;
    };

    template <class Iterator>
    class reverse_iterator
    {
        public:
            typedef Iterator                                                iterator_type;
            typedef typename iterator_traits<Iterator>::iterator_category   iterator_category;
            typedef typename iterator_traits<Iterator>::value_type          value_type;
            typedef typename iterator_traits<Iterator>::difference_type     difference_type;
            typedef typename iterator_traits<Iterator>::reference           reference;
            typedef typename iterator_traits<Iterator>::pointer             pointer;

        protected:
            iterator_type current;
        public:
            reverse_iterator() : current() { };
            explicit reverse_iterator(iterator_type __x) : current(__x) { };

            template <class T>
            reverse_iterator(const reverse_iterator<T>& diffT) : current(diffT.base()) { };
            template <class T>
            reverse_iterator &operator=(const reverse_iterator<T>& diffT) {
                if (reinterpret_cast<const void *>(this) == reinterpret_cast<const void *>(&diffT))
                    return *this;
                this->current = diffT.base();
                return *this;
            }

            virtual ~reverse_iterator() {};
            iterator_type base() const { return current; };
            operator reverse_iterator< const Iterator >() const { return this->current; }

            reference operator*() const { Iterator tmp = current; return *--tmp; };
            pointer operator->() const { return &(operator*()); };
            reverse_iterator& operator++() { --current; return *this; };
            reverse_iterator operator++(int) { reverse_iterator tmp(*this); --current; return tmp; };
            reverse_iterator& operator--() { ++current; return *this; };
            reverse_iterator operator--(int) { reverse_iterator tmp(*this); ++current; return tmp; };
            reverse_iterator operator+(difference_type _n) const { return reverse_iterator(current - _n); };
            reverse_iterator& operator+=(difference_type _n) { current -= _n; return *this; };
            reverse_iterator operator-(difference_type _n) const { return reverse_iterator(current + _n); };
            reverse_iterator& operator-=(difference_type _n) { current += _n; return *this; };
            reference operator[](difference_type _n) const { return *(*this + _n); };
    };

    template <class T1, class T2>
    bool operator==(const reverse_iterator<T1>& _x, const reverse_iterator<T2>& _y)
    {
        return _x.base() == _y.base();
    };
    template <class T1, class T2>
    bool operator<(const reverse_iterator<T1>& _x, const reverse_iterator<T2>& _y)
    {
        return _x.base() > _y.base();
    };
    template <class T1, class T2>
    bool operator!=(const reverse_iterator<T1>& _x, const reverse_iterator<T2>& _y)
    {
        return _x.base() != _y.base();
    };
    template <class T1, class T2>
    bool operator>(const reverse_iterator<T1>& _x, const reverse_iterator<T2>& _y)
    {
        return _x.base() < _y.base();
    };
    template <class T1, class T2>
    bool operator>=(const reverse_iterator<T1>& _x, const reverse_iterator<T2>& _y)
    {
        return _x.base() <= _y.base();
    };
    template <class T1, class T2>
    bool operator<=(const reverse_iterator<T1>& _x, const reverse_iterator<T2>& _y)
    {
        return _x.base() >= _y.base();
    };
    template <class T1, class T2>
    typename reverse_iterator<T1>::difference_type operator-(const reverse_iterator<T1>& _x, const reverse_iterator<T2>& _y)
    {
        return _y.base() - _x.base();
    };
    template <class T>
    reverse_iterator<T> operator+(typename reverse_iterator<T>::difference_type _n, const reverse_iterator<T>& _x)
    {
        return _x + _n;
    };
    template <class T>
    reverse_iterator<T> operator-(typename reverse_iterator<T>::difference_type _n, const reverse_iterator<T>& _x)
    {
        return _x - _n;
    };
}
#endif