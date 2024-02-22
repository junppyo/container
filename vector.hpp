#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <memory>
#include <algorithm>
#include <cstddef>
#include "utils.hpp"
#include "RandomAccessIterator.hpp"
#include <exception>

#include <iostream>

namespace ft
{
	template < class T, class Allocator = std::allocator<T> >
	class vector
	{
		public:
			typedef T                                           				value_type;
			typedef T const                                     				const_value_type;
			typedef Allocator                                   				allocator_type;
			typedef typename allocator_type::size_type							size_type;
			typedef typename allocator_type::reference       					reference;
			typedef typename allocator_type::const_reference   					const_reference;
			typedef typename allocator_type::pointer        		    		pointer;
			typedef typename allocator_type::const_pointer   					const_pointer;
			typedef typename ft::RandomAccessIterator<value_type>   			iterator;
			typedef typename ft::RandomAccessIterator<const_value_type> 		const_iterator;
			typedef typename ft::reverse_iterator<iterator>						reverse_iterator;
			typedef typename ft::reverse_iterator<const_iterator>				const_reverse_iterator;
			typedef typename ft::iterator_traits<iterator>::difference_type		difference_type;

		private:
			void vdeallocate()
			{
				if (this->__begin_ != u_nullptr)
				{
					clear();
					__alloc.deallocate(__begin_, capacity());
					__begin_ = __end_ = __cap = u_nullptr;
				}
			};
			allocator_type& alloc() { return __alloc; };
			const allocator_type& alloc() const { return __alloc; };
			pointer cap() { return __cap; };
			
			allocator_type __alloc;
			pointer __begin_;
			pointer __end_;
			pointer __cap;
		public:
			size_type capacity() const { return __cap - __begin_; };

			explicit vector(const allocator_type alloc = allocator_type())
				 : __alloc(alloc),
				   __begin_(u_nullptr),
				   __end_(u_nullptr),
				   __cap(u_nullptr)
					 {};
			explicit vector(size_type count, const value_type& value = value_type(),
							const allocator_type& alloc = allocator_type())
				: __alloc(alloc) {
					this->__begin_ = this->__alloc.allocate(count);
					this->__end_ = this->__begin_;
					this->__cap = this->__begin_ + count;
					while (count--) this->__alloc.construct(__end_++, value);
				};

			template <class InputIterator>
			vector(InputIterator first, InputIterator last,
				   const allocator_type& alloc = allocator_type(),
				   typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = ft::u_nullptr)
				   : __alloc(alloc)
				    {
						size_type n = difference(first, last);
						__begin_ = __alloc.allocate(n);
						__end_ = __begin_;
						__cap = __begin_ + n;
						while (n--) __alloc.construct(__end_++, *(first++));
				   };

			vector(const vector& v) : __alloc(v.alloc()){
				size_type n = v.size();
				this->__begin_ = this->__alloc.allocate(n);
				this->__cap = this->__begin_ + n;
				this->__end_ = this->__begin_;
				pointer other = v.__begin_;
				while (n--) this->__alloc.construct(this->__end_++, *other++);
			};

			~vector() { vdeallocate(); };
			vector& operator=( const vector& other ) {
				if (this != &other)
				{
					// clear();
					// std::cout << "copy" << std::endl;
					// insert(__begin_, other.begin(), other.end());
					vdeallocate();
					__alloc = other.alloc();
					__begin_ = __alloc.allocate(other.capacity());
					__cap = __begin_ + other.capacity();
					__end_ = __begin_;
					iterator begin = iterator(other.__begin_);
					for (;begin != other.end();begin++) push_back(*begin);
				}
				return *this;
			};

			void clear() {
				while (__begin_ != __end_)
					__alloc.destroy(--__end_);
			};

			void assign( size_type count, const value_type& value ) {
				if (capacity() >= count) {
					clear();
					while (count--) __alloc.construct(__end_++, value);
				}
				else {
					vdeallocate();
					__begin_ = __alloc.allocate(count);
					__end_ = __begin_;
					__cap = __begin_ + count;
					while (count--) *(__end_++) = value;
				}
			};

			template< class InputIt >
			void assign( InputIt first, InputIt last,
			typename enable_if<!is_integral<InputIt>::value>::type* = u_nullptr) {
				size_type n = difference(first, last);
				if (n > capacity())
				{
					vdeallocate();
					__begin_ = __alloc.allocate(n);
					__end_ = __begin_;
					__cap = __begin_ + n;
				}
				else
					clear();
				while (n--) __alloc.construct(__end_++, *first++);	
			};
			
			allocator_type get_allocator() const { return allocator_type(this->alloc()); };
			reference at( size_type pos ) {
				if (pos >= size()) throw std::out_of_range("ft::vector");
				return this->__begin_[pos];
			};
			const_reference at( size_type pos ) const {
				if (pos >= size()) throw std::out_of_range("ft::vector");
				return this->__begin_[pos];
			};
			reference operator[]( size_type pos ) { return this->__begin_[pos];	};
			const_reference operator[]( size_type pos ) const { return this->__begin_[pos]; };
			reference front() { return this->__begin_[0]; };
			const_reference front() const { return this->__begin_[0]; };
			reference back() { return this->__begin_[size() - 1]; };
			const_reference back() const { return this->__begin_[size() - 1]; };
			value_type* data() { return ((value_type)this->__begin_); };
			const value_type* data() const { return ((value_type)this->__begin_); };
			iterator begin() { return this->__begin_; };
			const_iterator begin() const { return iterator(this->__begin_); };
			iterator end() { return __end_; };
			const_iterator end() const { return this->__end_; };
			reverse_iterator rbegin() { return reverse_iterator(this->__end_); };
			const_reverse_iterator rbegin() const { return this->__end_; };
			reverse_iterator rend() { return reverse_iterator(this->__begin_); };
			const_reverse_iterator rend() const { return this->__begin_; };
			bool empty() const { return (size() == 0);};
			size_type size() const { return (__end_ - __begin_); };
			size_type max_size() const { return __alloc.max_size(); };
			void reserve(size_type n) {
				if (n > max_size())
					throw std::length_error("ft::vector");
				if (n <= capacity())
					return;
				pointer tmp_begin = __begin_;
				pointer tmp_end = __end_;
				size_type tmp_cap = capacity();
				__begin_ = __alloc.allocate(n);
				__end_ = __begin_;
				__cap = __begin_ + n;
				for (pointer tmp = tmp_begin ; tmp != tmp_end; tmp++)
					__alloc.construct(__end_++, *tmp);
				for (;tmp_end != tmp_begin;)
					__alloc.destroy(--tmp_end);
				__alloc.deallocate(tmp_begin, tmp_cap);
			};
			iterator insert( const_iterator pos, const T& value ) {
				size_type at = &(*pos) - __begin_;
				insert(pos, 1, value);
				return __begin_ + at;
			};
			void insert( const_iterator pos, size_type count, const T& value ) {
				size_type n = &(*pos) - __begin_;
				 if (size() + count <= capacity()) {
					 for (size_type i = 0; i < size() - n; i++) {
						 __alloc.construct(__end_ + count - i, *(__end_ - i));
						 __alloc.destroy(__end_ - i);
					 }
					 for (size_type i = 0; i < n; i++)
					 {
						 __alloc.construct(__begin_ + n + i, value);
					 }
				 }
				 else {
					 pointer tmp_begin = __alloc.allocate(count + size());
					 pointer tmp_end = tmp_begin;
					 size_type tmp_cap = count + size();
					 for (size_type i = 0; i < n; i++)
					 {
						 __alloc.construct(tmp_end++, *(__begin_ + i));
					 }
					 for (size_type i = 0; i < count; i++)
					 {
						 __alloc.construct(tmp_end++, value);
					 }
					 for (size_type i = 0 ; i < size() - n; i++)
					 {
						 __alloc.construct(tmp_end++, *(__begin_ + n + i));
					 }
					vdeallocate();
					__begin_ = tmp_begin;
					__end_ = tmp_end;
					__cap = __begin_ + tmp_cap;
				 }
			};
			template< class InputIt >
			void insert( iterator pos, InputIt first, InputIt last,
							 typename enable_if<!is_integral<InputIt>::value>::type* = u_nullptr ) {
				size_type count = difference(first, last);
				size_type at = &(*pos) - __begin_;
				if (size() + count <= capacity())
				{
					for (size_type i = 0; i < size() - at; ++i) {
						__alloc.construct(__end_ + count - i, *(__end_ - i));
						__alloc.destroy(__end_ - i);
					}
					for (size_type i = 0; i < count; ++i)
					{
						__alloc.construct(__begin_ + at + i, *(first++));
					}
					__end_ += count;
				}
				else {
					vector<T> tmp;
					for (iterator it = begin(); it != pos; it++)
						tmp.push_back(*it);
					for (;first != last; first++)
						tmp.push_back(*first);
					for (iterator it = pos; it != end(); it++)
						tmp.push_back(*it);
					vdeallocate();
					*this = tmp;
				}
			};
			iterator erase( iterator pos ) {
				size_type at = &(*pos) - __begin_;
				
				for (;pos != end() - 1; pos++)
				{
					__alloc.destroy(&(*pos));
					__alloc.construct(&(*pos), *(pos + 1));
				}
				--__end_;
				return __begin_ + at;
			};
			iterator erase( iterator first, iterator last ) {
				size_type at = &(*first) - __begin_;
				size_type count = last - first;
				for (size_type i = 0 ; i < count; i++)
					__alloc.destroy(&(*(first + i)));
				for (size_type i = 0 ; i < size() - at; ++i) {
					__alloc.construct(__begin_ + at + i, *(__begin_ + at + i + count));
					__alloc.destroy(__begin_ + at + i + count);
				}
				__end_ -= count;
				return __begin_ + at;
			};
			void push_back( const T& value ) {
				if (__end_ == __cap)
				{
					size_type n;
					if (capacity() == 0)
						n = 1;
					else
						n = capacity() * 2;
					reserve(n);
				}
				__alloc.construct(__end_++, value);
			};
			void pop_back() {
				if (__begin_ == __end_)
					return ;
				erase(__end_ - 1);
			}
			void resize( size_type count, T value = T() ) {
				if (count > max_size())
					throw std::length_error("ft::vector");
				if (count == size())
					return ;
				else if (count < size())
				{
					size_t tmp = size();
					while (tmp -- > count)
						__alloc.destroy(--__end_);
					return ;
				}
				this->insert(__end_, count - size(), value);
			}
			void swap( vector& other ) {
				if (this == &other)
					return;
				pointer tmp_begin = other.__begin_;
				pointer tmp_end = other.__end_;
				pointer tmp_cap = other.__cap;
				other.__begin_ = __begin_;
				other.__end_ = __end_;
				other.__cap = __cap;
				__begin_ = tmp_begin;
				__end_ = tmp_end;
				__cap = tmp_cap;
			}


	};
	template< class T, class Alloc >
	bool operator==( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs ) {
		if (lhs.size() != rhs.size())
			return false;
		for (size_t i = 0 ; i < lhs.size(); i++) {
			if (*(lhs.begin() + i) != *(rhs.begin() + i))
				return false;
		}
		return true;
	}
	template< class T, class Alloc >
	bool operator!=( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs ) {
		return !(lhs == rhs);
	}
	template< class T, class Alloc >
	bool operator<( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs ) {
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template< class T, class Alloc >
	bool operator<=( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs ) {
		if (lhs == rhs)
			return true;
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}
	template< class T, class Alloc >
	bool operator>( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs ) {
		return ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end());
	}
	template< class T, class Alloc >
	bool operator>=( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs ) {
		if (lhs == rhs)
			return true;
		return ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end());
	}
}
#endif