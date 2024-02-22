#ifndef UTILITY_HPP
#define UTILITY_HPP

namespace ft
{
    template <class T1, class T2>
    struct pair {
        public:
            typedef T1      first_type;
            typedef T2      second_type;
            first_type      first;
            second_type     second;
            pair(const T1& x = T1(), const T2& y = T2()) : first(x), second(y) { };
            template<class U1, class U2>
            pair(const pair<U1, U2>& p) : first(p.first), second(p.second) { };
            pair& operator=(const pair& other) { 
                if (this == &other)
                    return *this;
                this->first = other.first;
                this->second = other.second;
                return *this;
            };
    };

    template <class T1, class T2>
    ft::pair<T1, T2> make_pair(T1 t, T2 u) { return ft::pair<T1, T2>(t, u); }
    template <class T1, class T2>
    bool operator==(const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs) { return lhs.first == rhs.first && lhs.second == rhs.second; }
    template <class T1, class T2>
    bool operator!=(const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs) { return !(lhs == rhs); }
    template <class T1, class T2>
    bool operator<(const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs) {
        return lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second);
    }
    template <class T1, class T2>
    bool operator<=(const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs) {
        return !(rhs < lhs);
        if (lhs == rhs)
            return true;
        return lhs < rhs;
    }
    template <class T1, class T2>
    bool operator>(const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs) { 
        return (rhs < lhs);
    }
    template <class T1, class T2>
    bool operator>=(const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs) {
        return !(lhs < rhs);
    }
}

#endif