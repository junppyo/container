#ifndef MAP_HPP
#define MAP_HPP

#include <iostream>

#include <exception>
#include <functional>
#include <memory>
#include "BSTree.hpp"
#include <time.h>

namespace ft
{
    template<class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<ft::pair<Key, T> > >
    class map
    {
        public:
            typedef Key                                                         key_type;
            typedef T                                                           mapped_type;
            typedef ft::pair<key_type, mapped_type>                             value_type;
            typedef std::size_t                                                 size_type;
            typedef Compare                                                     key_compare;
            typedef Allocator                                                   allocator_type;
            typedef ft::BSTNode<value_type, key_compare>                                     node_type;
            typedef node_type*                                                  node_ptr;
            typedef typename allocator_type::reference                          reference;
            typedef typename allocator_type::const_reference                    const_reference;
            typedef typename allocator_type::pointer                            pointer;
            typedef typename allocator_type::const_pointer                      const_pointer;
            typedef typename ft::BSTIterator<value_type, node_type>                          iterator;
            typedef typename ft::BSTIterator<const value_type, node_type>              const_iterator;
            typedef typename ft::reverse_iterator<iterator>                     reverse_iterator;
            typedef typename ft::reverse_iterator<const_iterator>               const_reverse_iterator;
            typedef typename ft::iterator_traits<iterator>::difference_type     difference_type;

            class value_compare : std::binary_function<value_type, value_type, bool> {
                friend class map<key_type, mapped_type, key_compare, Allocator>;
                private:
                    typedef bool                    result_type;
                    typedef value_type              first_argument_type;
                    typedef value_type              second_argument_type;
                protected:
                    Compare                 comp;
                    value_compare(Compare c) : comp(c) {};
                public:
                    bool operator()(const first_argument_type& lhs, const second_argument_type& rhs) const { return comp(lhs.first, rhs.first); };

					static value_compare constructObject(Compare c)
					{
						return value_compare(c);
					}
            };
        private:
            allocator_type                      _alloc;
            key_compare                         _comp;
            ft::BST<value_type, Compare>        _bst;
        protected:
            void copy(node_ptr other, node_ptr last) {
                insert(other->value);
                if (other->left != u_nullptr)
                    copy(other->left, last);
                if (other->right != u_nullptr && other->right != last)
                    copy(other->right, last);
            }

        public:
            map() : _alloc(allocator_type()), _comp(key_compare()) {};
            explicit map(const key_compare& comp, const allocator_type& alloc = allocator_type()) : _alloc(alloc), _comp(comp) { };
            template<class InputIt>
            map(InputIt first, InputIt last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type(), typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = 0) : _alloc(alloc), _comp(comp), _bst() {
                insert(first, last);
            };
            map(const map& other) : _alloc(other.get_allocator()), _comp(other._comp) {
                copy(other._bst._root, other._bst.last_node);
                 }; 
            ~map() { };
            map& operator=(const map& other) {
                if (this == &other)
                    return *this;
                clear();
                copy(other._bst._root, other._bst.last_node);
                return *this;
            };
            allocator_type get_allocator() const { return _alloc; };
            mapped_type& at(const Key& key) { 
                iterator tmp = find(key);
                if (tmp == end())
                    throw std::out_of_range("ft::map");
                return (*tmp).second;
            }
            const mapped_type& at(const Key& key) const { 
                iterator tmp = find(key);
                if (tmp == end())
                    throw std::out_of_range("ft::map");
                return (*tmp).second;
            }
            mapped_type& operator[](const Key& key) {
                iterator tmp = find(key);
                if (tmp == end())
                    insert(ft::make_pair(key, mapped_type()));
                tmp = find(key);
                return ((*tmp).second);
            }
            iterator begin() { if (empty()) return end(); return iterator(_bst.getmin()); };
            const_iterator begin() const { if (empty()) return end(); return const_iterator(_bst.getmin()); };
            iterator end() { return iterator(_bst.getlast()); };
            const_iterator end() const { return const_iterator(_bst.getlast()); };
            reverse_iterator rbegin() { return reverse_iterator(_bst.getlast()); };
            const_reverse_iterator rbegin() const { return const_reverse_iterator(_bst.getlast()); };
            reverse_iterator rend() { if (empty()) return reverse_iterator(end()); return reverse_iterator(_bst.getmin()); };
            const_reverse_iterator rend() const { if (empty()) return const_reverse_iterator(end()); return const_reverse_iterator(_bst.getmin()); };
            bool empty() const { return (_bst.__size == 0); };
            size_type size() const { return _bst.__size; };
            size_type max_size() const { return _alloc.max_size(); };
            void clear() { 
                erase(begin(), end());
            };
            ft::pair<iterator, bool> insert(const value_type& value) {
                return _bst.insert(value);
            }
            void print() { _bst.print(); };
            iterator insert(iterator pos, const_reference value) {
                (void)pos;
                return iterator(insert(value).first);
            };
            template <class InputIt>
            void insert(InputIt first, InputIt last, typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = 0) {
                while (first != last) {
                    insert(*(first++));
                }
            };
            void erase(iterator pos) {
                _bst.remove(pos.base()->value); 
            };
            bool erase(iterator start, iterator last) {
                bool ret = false;
                while (start != last) {
                    ret = ret | _bst.remove(start.base()->value);
                    start++;
                }
                return ret;
            };
            size_type erase (const key_type& key) { return _bst.remove(ft::make_pair(key, mapped_type())); };
            void swap(map& other) {
                _bst.swap(other._bst);
            };
            iterator find(const key_type& key) {
                if (_bst.search(ft::make_pair(key, mapped_type())) == u_nullptr)
                    return end();
                return iterator(_bst.search(ft::make_pair(key, mapped_type())));
            };
            const_iterator find(const key_type& key) const {
                if (_bst.search(ft::make_pair(key, mapped_type())) == u_nullptr)
                    return end();
                return const_iterator(_bst.search(ft::make_pair(key, mapped_type())));
            };
            size_type count(const key_type& key) const {
                if (find(key) == end())
                    return 0;
                return 1;
            };
            iterator lower_bound(const key_type& key) {
                iterator it = begin();
                bool is_break = false;
                for (;it != end(); it++) {
                    if (it->first >= key)
                    {
                        is_break = true;
                        break;
                    }
                }
                if (is_break)
                    return it;
                else
                    return end();
            };
            const_iterator lower_bound(const key_type& key) const {
                const_iterator it = begin();
                bool is_break = false;
                for (;it != end(); it++) {
                    if (it->first >= key)
                    {
                        is_break = true;
                        break;
                    }
                }
                if (is_break)
                    return it;
                else
                    return end();
            };

            iterator upper_bound(const key_type& key) {
                iterator it = begin();
                for (;it != end(); it++) {
                    if (it->first > key)
                        break;
                }
                return it;
            };
            const_iterator upper_bound(const key_type& key) const {
                const_iterator it = begin();
                for (;it != end(); it++) {
                    if (it->first > key)
                        break;
                }
                return it;
            };

            ft::pair<iterator, iterator> equal_range(const key_type& key) {
                return ft::make_pair<iterator, iterator>(lower_bound(key), upper_bound(key));
            };
            ft::pair<const_iterator, const_iterator> equal_range(const key_type& key) const {
                return ft::make_pair<const_iterator, const_iterator>(lower_bound(key), upper_bound(key));
            };
            key_compare key_comp() const { return key_compare(); };
            value_compare value_comp() const { return value_compare(key_compare()); };
    };
    template< class Key, class T, class Compare, class Alloc >
    bool operator==(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ) {
        if (lhs.size() != rhs.size())
            return false;
        return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
    }
    template< class Key, class T, class Compare, class Alloc >
    bool operator!=(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ) {
        return !(lhs == rhs);
    }
    template< class Key, class T, class Compare, class Alloc >
    bool operator<(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ) {
        return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }
    template< class Key, class T, class Compare, class Alloc >
    bool operator<=(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ) {
        return !(rhs < lhs);
    }
    template< class Key, class T, class Compare, class Alloc >
    bool operator>(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ) {
        return (rhs < lhs);
    }
    template< class Key, class T, class Compare, class Alloc >
    bool operator>=(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ) {
        return !(lhs < rhs);
    }
}

#endif