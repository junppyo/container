#ifndef BSTITERATOR_HPP
#define BSTITERATOR_HPP

#include "Iterator.hpp"
#include "utility.hpp"
#include "utils.hpp"
#include "BSTree.hpp"

namespace ft
{
    template <class T, class Compare>
    struct BSTNode;
    // template <class T, class Compare>
    template <class T, class node_type>
    class BSTIterator : ft::iterator<ft::bidirectional_iterator_tag, T>
    {
        public:
        	typedef T value_type;
            typedef node_type* Node;
            typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::reference           reference;
            typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::pointer             pointer;
            typedef typename ft::iterator<ft::bidirectional_iterator_tag, node_type>::difference_type     difference_type;
            typedef typename ft::iterator<ft::bidirectional_iterator_tag, node_type>::iterator_category   iterator_category;
            Node _node;
            template <class, class, class, class>
            friend class map;
            template <class, class>
            friend class BSTIterator;
            // Compare _comp;
        private:
            Node min(Node node) {
                if (node == u_nullptr)
                    return u_nullptr;
                if (node->left != u_nullptr)
                    return min(node->left);
                return node;
            }
            Node max(Node node) {
                if (node == u_nullptr)
                    return u_nullptr;
                if (node->right != u_nullptr)
                    return max(node->right);
                return node;
            }
            Node previous(Node node) {
                if (node->left != u_nullptr)
                    return max(node->left);
                Node current = node;
                while (current->parent != u_nullptr && current->parent->left == current) {
                    current = current->parent;
                }
                return current->parent;
            }
            Node next(Node node) {
                if (node->right != u_nullptr)
                    return min(node->right);
                Node current = node;
                while (current->parent != u_nullptr && current->parent->right == current) {
                    current = current->parent;
                }
                return current->parent;
            }

        public:
            operator BSTIterator<const T, node_type>() const { return _node; }
            BSTIterator() : _node() {};
            BSTIterator(node_type* node) : _node(node) {};
            BSTIterator(const BSTIterator& other) : _node(other._node) {};
            virtual ~BSTIterator() {};
            BSTIterator& operator=(const BSTIterator& other) {
                if (this == &other)
                    return *this;
                _node = other._node;
                return *this;
            };
            template <class U> bool operator==(const BSTIterator<U, node_type>& other) { return (other._node == this->_node); };
            template <class U> bool operator!=(const BSTIterator<U, node_type>& other) { return (other._node != this->_node); };
            bool operator!=(const BSTIterator& other) { return (other._node != this->_node); };
            bool operator!=(T* other) { return (other != _node); };
            reference operator*() const { return this->_node->value; };
            pointer operator->() const { return &(_node->value); };
            BSTIterator& operator++() { _node = next(_node); return *this; };
            BSTIterator operator++(int) { BSTIterator tmp = *this; _node = next(_node); return tmp; };
            BSTIterator& operator--() { _node = previous(_node); return *this; };
            BSTIterator operator--(int) { BSTIterator tmp = *this; _node = previous(_node); return tmp; };
            Node base() { return _node; };
            reference operator[](difference_type _n) const { return *(*this + _n); };
    };
}

#endif