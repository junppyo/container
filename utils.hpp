#ifndef UTILS_HPP
#define UTILS_HPP
#include "Iterator.hpp"
namespace ft
{
    template <bool, typename T = void>
    struct enable_if {};

    template <typename T>
    struct enable_if<true, T> {
        typedef T type;
    };

    struct true_type {
        static const bool value = true;
        typedef bool value_type;
        typedef true_type type;
    };
    struct false_type {
        static const bool value = false ;
        typedef bool value_type;
        typedef true_type type;
    };

    template <class T>
    struct is_integral : public false_type {};
    template < >
    struct is_integral<bool> : public true_type {};
    template < >
    struct is_integral<char> : public true_type {};
    template < >
    struct is_integral<char16_t> : public true_type {};
    template < >
    struct is_integral<char32_t> : public true_type {};
    template < >
    struct is_integral<wchar_t> : public true_type {};
    template < >
    struct is_integral<signed char> : public true_type {};
    template < >
    struct is_integral<short int> : public true_type {};
    template < >
    struct is_integral<int> : public true_type {};
    template < >
    struct is_integral<long int> : public true_type {};
    template < >
    struct is_integral<long long int> : public true_type {};
    template < >
    struct is_integral<unsigned char> : public true_type {};
    template < >
    struct is_integral<unsigned short int> : public true_type {};
    template < >
    struct is_integral<unsigned int> : public true_type {};
    template < >
    struct is_integral<unsigned long int> : public true_type {};
    template < >
    struct is_integral<unsigned long long int> : public true_type {};

    struct nullptr_t {
        private:
        void operator&() const;

        public:
        template < class T >
        inline operator T*() const {
            return 0;
        }

        template < class C, class T >
        inline operator T C::*() const {
            return 0;
        }
    };
    static nullptr_t u_nullptr = {};

    template <class InputIterator>
    typename iterator_traits< InputIterator >::difference_type difference(InputIterator first, InputIterator last) {
        typedef typename ft::iterator_traits< InputIterator >::difference_type size_type;
        size_type n = 0;
        for (;first != last; ++first)
            ++n;
        return n;
    }

    template<class Arg1, class Arg2, class Result>
    struct binary_function {
        typedef Arg1        frist_argument_type;
        typedef Arg2        second_argument_type;
        typedef Result      result_type;
    };

    template <class T>
    struct less : binary_function<T, T, bool> {
        bool operator() (const T& lhs, const T& rhs) const { return lhs < rhs; };
    };
    template<class InputIt1, class InputIt2>
    bool lexicographical_compare(InputIt1 first1, InputIt1 last1,
                                InputIt2 first2, InputIt2 last2)
    {
        for (; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2)
        {
            if (*first1 < *first2)
                return true;
            if (*first2 < *first1)
                return false;
        }
    
        return (first1 == last1) && (first2 != last2);
    }

    template <class InputIt1, class InputIt2>
    bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2)
    {
        while (first1 != last1)
        {
            if (*first1 != *first2)
                return false;
            ++first1; ++first2;
        }
        return true;
    }
}

#endif