#ifndef BSTREE_HPP
#define BSTREE_HPP

#include <iostream>
#include "utils.hpp"
#include "BSTIterator.hpp"

namespace ft
{
    template <class T, class Compare = ft::less<T> >
    struct BSTNode {
        public:
            typedef T       value_type;
            value_type      value;
            BSTNode*        parent;
            BSTNode*        left;
            BSTNode*        right;
            Compare _comp;
            BSTNode(const T &val = T()) : value(val), parent(u_nullptr), left(u_nullptr), right(u_nullptr), _comp(Compare()) {};
            BSTNode(const BSTNode& other) : value(other.value), parent(other.parent), left(other.left), right(other.right), _comp(Compare()) {};
            virtual ~BSTNode() {};
            BSTNode* operator=(const BSTNode& other) {
                if (this == &other)
                    return this;
                value = other.value;
                parent = other.parent;
                left = other.left;
                right = other.right;
                return this;
            };
            operator BSTNode<T>() const { return value; }
            bool operator==(const BSTNode& other) { return (value == other.value); };
            bool operator!=(const BSTNode& other) const { return (value != other.value); };
            template <class U>
            bool operator==(const BSTNode<U>& other) { return (value == other.value); };
            template <class U>
            bool operator!=(const BSTNode<U>& other) { return (value != other.value); };
            bool operator<(const BSTNode& other) { return ( _comp(value, other.value) );};
            bool operator>(const BSTNode& other) { return (other.value < value); };
            bool operator>=(const BSTNode& other) { return !(value < other.value); };
            bool operator<=(const BSTNode& other) { return !(other.value < value); };
    };
    template <class T, class U>
    bool operator==(const BSTNode<T>& lhs, const BSTNode<U>& rhs) { return (lhs.value == rhs.value); }
    template <class T, class U>
    bool operator!=(const BSTNode<T>* lhs, const BSTNode<U>* rhs) { return (lhs->value != rhs->value); }

    template <class T, class Compare = ft::less<T>, class Node = ft::BSTNode<T, Compare>, class alloc = std::allocator<T> >
    class BST {
        public:
            typedef T                                       value_type;
            typedef Node                                    node_type;
            typedef Node const                              const_node_type;
            typedef Node*                                   node_pointer;
            typedef Node&                                   node_reference;
            typedef typename alloc::template rebind<node_type>::other node_alloc;
            typedef ft::BSTIterator<T, node_type>          iterator;
            typedef ft::BSTIterator<T, node_type>     const_iterator;
            typedef size_t                                  size_type;

            node_pointer   _root;
            node_alloc  _node_alloc;
            size_type __size;
            node_pointer last_node;
            Compare _comp;
        protected:
            size_type getHeight(node_pointer node) {
                if (node == NULL || node == last_node) return 0;
                node_pointer tmp = node;
                size_type lheight = 0;
                size_type rheight = 0;
                while (tmp != u_nullptr && tmp != last_node) {
                    lheight++;
                    if (tmp->left != u_nullptr)
                        tmp = tmp->left;
                    else if (tmp->right != u_nullptr)
                        tmp = tmp->right;
                    else
                        break;
                }
                tmp = node;
                while (tmp != u_nullptr && tmp != last_node) {
                    rheight++;
                    if (tmp->left != u_nullptr)
                        tmp = tmp->left;
                    else if (tmp->right != u_nullptr)
                        tmp = tmp->right;
                    else
                        break;
                }
                return lheight > rheight ? lheight + 1 : rheight + 1;
            }
            int getBalance(node_pointer node) {
                return getHeight(node->left) - getHeight(node->right);
            }
            node_pointer turnLL(node_pointer node) {
                node_pointer x =  node;
                node_pointer y = x->left;
                node_pointer z = 0;

                if (y != 0) {
                    z = y->right;
                    y->parent = x->parent;
                    y->right = x;
                }
                if (x != 0) {
                    x->parent = y;
                    x->left = z;
                }
                if (z != 0)
                    z->parent = x;
                return y;
            }

            node_pointer turnRR(node_pointer node) {
                node_pointer x = node;
                node_pointer y = x->right;
                node_pointer z = 0;

                if (y != 0) {
                    z = y->left;
                    y->parent = x->parent;
                    y->left = x;
                }
                if (x != 0) {
                    x->right = z;
                    x->parent = y;
                }
                if (z != 0)
                    z->parent = x;
                return y;   
            }

            node_pointer turnLR(node_pointer node) {
                node_pointer x = node;
                node_pointer y = x->left;
                y = turnRR(y);
                x = turnLL(x);
                return x;
            }

            node_pointer turnRL(node_pointer node) {
                node_pointer x = node;
                node_pointer y = node->right;
                y = turnLL(y);
                x = turnRR(x);
                return x;
            }

            void rebalance() {
                if (_root == u_nullptr)
                    return ;
                int balance = getBalance(_root);
                if (balance >= 2) {
                    balance = getBalance(_root->left);
                    if (balance >= 1) 
                        _root = turnLL(_root);
                    else
                        _root = turnLR(_root);
                }
                else if (balance <= -2) {
                    balance = getBalance(_root->right);
                    if (balance <= -1)
                        _root = turnRR(_root);
                    else
                        _root = turnRL(_root);
                }
            }

            node_pointer insert_node(node_pointer node, T data) {
                int cnt = 0;
                node_pointer ret = _node_alloc.allocate(1);
                _node_alloc.construct(ret, Node(data));
                if (_root == u_nullptr) {
                    ret->right = last_node;
                    _root = ret;
                    last_node->parent = ret;
                    return ret;
                }
                while (node != u_nullptr && node != last_node) {
                    if (_comp(data.first, node->value.first)) {
                        cnt++;
                        if (node->left == u_nullptr) {
                            node->left = ret;
                            ret->parent = node;
                            return ret;
                        }
                        node = node->left;
                    }
                    else if (_comp(node->value.first, data.first)) {
                        if (node->right == u_nullptr || node->right == last_node) {
                            if (node->right == last_node) {
                                ret->right = last_node;
                                last_node->parent = ret;
                            }
                            node->right = ret;
                            ret->parent = node;
                            return ret;
                        }
                        node = node->right;
                    }
                    else
                        break;
                }
                return _root;
            };
            void print_node(node_pointer node) {
                if (node == u_nullptr || node == last_node)
                    return ;
                for (iterator it = getmin(); it != last_node; it++)
                    std::cout << "key: " << it->first << " value: " << it->second << std::endl;
            }

            ft::pair<node_pointer, bool> search_node(node_pointer node, value_type data) const {
                if (node == u_nullptr)
                    return ft::make_pair(u_nullptr, false);
                while (node->value.first != data.first) {
                    if (_comp(data.first, node->value.first)) {
                        if (node->left != u_nullptr)
                            node = node->left;
                        else
                            return ft::make_pair(node, false);
                    }
                    else if (_comp(node->value.first, data.first)) {
                        if (node->right != u_nullptr && node->right != last_node)
                            node = node->right;
                        else
                            return ft::make_pair(node, false);
                    }
                }
                return ft::make_pair(node, true);
            }
            bool delete_node(node_pointer node) {
                if (node == u_nullptr || node == last_node)
                    return false;
                node_pointer parent = node->parent;
                if (node->left == u_nullptr && node->right == u_nullptr) {
                    if (parent && parent->left == node)
                        parent->left = u_nullptr;
                    else if (parent && parent->right == node)
                        parent->right = u_nullptr;
                    _node_alloc.destroy(node);
                    _node_alloc.deallocate(node, 1);
                }
                else if (node->left && node->right) {
                    node_pointer tmp = previous(node);
                    node->value = tmp->value;
                    if (tmp->left != u_nullptr) {
                        if (tmp->parent->left == tmp) 
                            tmp->parent->left = tmp->left;
                        else
                            tmp->parent->right = tmp->left;
                        tmp->left->parent = tmp->parent;
                    }
                    else {
                        if (tmp->parent->left == tmp)
                            tmp->parent->left = u_nullptr;
                        else
                            tmp->parent->right = u_nullptr;
                    }
                    _node_alloc.destroy(tmp);
                    _node_alloc.deallocate(tmp, 1);
                }
                else if (node->left) {
                    node->left->parent = parent;
                    if (parent && parent->left == node)
                        parent->left = node->left;
                    else if (parent && parent->right == node)
                        parent->right = node->left;
                    if (node == _root)
                        _root = node->left;
                    _node_alloc.destroy(node);
                    _node_alloc.deallocate(node, 1);
                }
                else if (node->right) {
                    node->right->parent = parent;
                    if (parent && parent->left == node)
                        parent->left = node->right;
                    else if (parent && parent->right == node)
                        parent->right = node->right;
                    if (node == _root)
                        _root = node->right;
                    _node_alloc.destroy(node);
                    _node_alloc.deallocate(node, 1);
                }
                if (__size == 0)
                    _root = u_nullptr;
                return true;
            }
            void delete_all(node_pointer node) {
                if (node == u_nullptr || node == last_node)
                    return ;
                if (node->left != u_nullptr) {
                    delete_all(node->left);
                }
                if (node->right != u_nullptr || node == last_node) {
                    delete_all(node->right);
                }
                delete_node(node);
            }
            bool remove_node(node_pointer node, value_type data) {
                ft::pair<node_pointer, bool> ret = search_node(node, data);
                if (ret.second == true)
                    return delete_node(ret.first);
                return false;
            }
            node_pointer min(node_pointer node) const {
                if (node == u_nullptr || node == last_node)
                    return u_nullptr;
                else if (node->left == u_nullptr)
                    return node;
                else
                    return min(node->left);
                return node;
            }
            node_pointer max(node_pointer node) const {
                if (node == u_nullptr || node == last_node)
                    return u_nullptr;
                else if (node->right == nullptr)
                    return node;
                else
                    return max(node->right);
                return node;
            }
            node_pointer previous(node_pointer node) {
                if (node->left != u_nullptr)
                    return max(node->left);
                node_pointer current = node;
                while (current->parent != u_nullptr && current->parent->left == current) {
                    current = current->parent;
                }
                return current->parent;
            }
            node_pointer next(node_pointer node) {
                if (node->right != u_nullptr && node->right != last_node)
                    return min(node->right);
                Node current = node;
                while (current->parent != u_nullptr && current->parent->right == current) {
                    current = current->parent;
                }
                return current->parent;
            }
            void insert_all(node_pointer node) {
                node_pointer tmp = node->_root;
                insert(tmp->value);
                if (tmp->left != u_nullptr)
                    insert_all(tmp->left);
                if (tmp->right != u_nullptr && tmp->right != last_node)
                    insert_all(tmp->right);
                // while (tmp != max(node->_root)) {
                //     insert(tmp->value);
                //     tmp++;
                // }
            }
        public:
            BST(const node_alloc& init = node_alloc()) : _root(u_nullptr), _node_alloc(init), __size(0), _comp(Compare()) { last_node = _node_alloc.allocate(1); _node_alloc.construct(last_node, Node(0)); };
            BST(node_pointer node) : _root(u_nullptr), _node_alloc(node_alloc()), __size(0), _comp(Compare()) { last_node = _node_alloc.allocate(1); _node_alloc.construct(last_node, Node(0)); insert(node->value); };
            BST(node_reference other) : _root(u_nullptr), _node_alloc(node_alloc()), last_node(other.last_node), __size(0), _comp(other._comp) {
                insert_all(other._root);
            };
            ~BST() { delete_all(_root); _node_alloc.destroy(last_node); _node_alloc.deallocate(last_node, 1); };
            node_reference operator=(node_reference other) {
                delete_all(_root);
                insert_all(other._root);
            }
            size_type max_size() const { return (_node_alloc.max_size()); };
            ft::pair<iterator, bool> insert(const T& data) {
                ft::pair<node_pointer, bool> ret = search_node(_root, data);
                if (ret.second == true)
                    return ft::make_pair(iterator(ret.first), false);
                ret = insert_node(ret.first, data);
                rebalance();
                __size++;
                return ft::make_pair(iterator(ret.first), true);
            };
            void print() { print_node(_root);};
            bool remove(value_type data) { 
                bool ret = remove_node(_root, data);
                if (ret)
                    __size--;
                if (__size == 0)
                    _root = u_nullptr;
                return ret; 
            };
            node_pointer search(value_type data) const { 
                ft::pair<node_pointer, bool> ret = search_node(_root, data);
                if (ret.second == false)
                    return u_nullptr;
                else
                    return ret.first;
            }
            node_pointer getmin() const { return min(_root); };
            node_pointer getmax() const { return max(_root); };
            node_pointer getlast() const { return last_node; };
            void swap(BST& other) {
                if (this == &other)
                    return ;
                node_pointer tmp_root = _root;
                node_pointer tmp_last = last_node;
                size_t tmp_size = __size;
                _root = other._root;
                last_node = other.last_node;
                __size = other.__size;
                other._root = tmp_root;
                other.last_node = tmp_last;
                other.__size = tmp_size;     
            }
            void clear() { delete_all(_root); };
            void print_tree(node_pointer node) {
                if (node == u_nullptr)
                    return ;
                std::cout << "key: " << node->value.first << " value: " << node->value.second << std::endl;
                if (node->left != u_nullptr) {
                    std::cout << "left key: " << node->left->value.first << " value: " << node->left->value.second << std::endl;
                } 
                if (node->right != u_nullptr) {
                    std::cout << "right key: " << node->right->value.first << " value: " << node->right->value.second << std::endl;
                }
                std::cout << "\n";
                if (node->left != u_nullptr)
                    print_tree(node->left);
                if (node->right != u_nullptr)
                    print_tree(node->right);
            }
    };
}
#endif