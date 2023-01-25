/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 16:44:10 by nali              #+#    #+#             */
/*   Updated: 2023/01/25 16:45:26 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "../includes/containers.hpp"
#include "../includes/random_access_iterator.hpp"
#include "../includes/reverse_iterator.hpp"
#include <memory> //to access allocator

namespace ft
{
    template < class T, class Alloc = std::allocator<T> >
    class vector
    {    
        public:
            typedef T                                           value_type;
            typedef Alloc                                       allocator_type;
            typedef size_t					                    size_type;
            typedef ptrdiff_t			                        difference_type;
            typedef typename allocator_type::pointer            pointer;
            typedef typename allocator_type::const_pointer	    const_pointer;
            typedef typename allocator_type::reference	        reference;
            typedef typename allocator_type::const_reference	const_reference;
            typedef ft::random_access_iterator <T>              iterator;
            typedef ft::random_access_iterator <const T>        const_iterator;
            typedef ft::reverse_iterator<const_iterator>	    const_reverse_iterator;
            typedef ft::reverse_iterator<iterator>		        reverse_iterator;
        
        private:
            T*                  _start;    // Point to the first element
            T*                  _finish;   // Point to one-past the last element
            T*                  _capacity;  // Point to the end of the internal array(max elements it can hold)
            allocator_type     _alloc;
        
        public:
            /*constructors*/
            /*default constructor*/
            explicit vector (const allocator_type& alloc = allocator_type())
            :_alloc(alloc),_start(NULL),_finish(NULL),_capacity(NULL)
            {}	
            
            /*fill constructor*/
            explicit vector (size_type n, const value_type& val = value_type(),const allocator_type& alloc = allocator_type())
            :_alloc(alloc) 
            {
                _start = _alloc.allocate(n);
                _capacity = _start + n;
                _finish = _start;
                while(n--)
                {
                    this->_alloc.construct(_finish, val);
                    this->_finish++;
                }  
            }	
            
            /*range constructor*/
            template <class InputIterator>         
            vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type())
            {
                size_type i = 0;
                difference_type d = last - first;
                this->_alloc = alloc;
                this->_start = this->_alloc(d);
                this->_capacity = this->_start + d;
                this->_finish = this->_start;
                while(i < d)
                {
                    this->_alloc.construct(this->_finish, *(first + i));
                    i++;
                    this->_finish++;
                }  
            } 
            
            /* copy constructor */
            vector (const vector& x):_alloc(alloc),_start(NULL),_finish(NULL),_capacity(NULL)
            {
                *this = x; //calls copy assignment
            }
            
            /*destructor*/
            ~vector()
            {
                this->clear();
				_alloc.deallocate(this->_start, this->capacity());
            }
            /*copy assignment*/
            vector& operator= (const vector& x)
            {
                if (!this->empty())
				{   this->~vector();}
                size_type c = x.capacity();
                size_type s = x.size();
                this->_start = this->_alloc.allocate(c);
                this->_capacity = this->_start + c;
                this->_finish = this->_start;
                for (int i = 0; i < s; i++)
                {
                    this->_alloc.construct(this->_finish, *(x._start + i));
                    this->_finish++;
                }
                return(*this);
            }
            /*member functions*/

            template <class InputIterator>  
            void assign (InputIterator first, InputIterator last)
            {}

            void assign (size_type n, const value_type& val)
            {
                if (n > capacity())
                {
                    
                }
                    vector tmp(n, val, this->_alloc)
                else if (n > size())
                
                else
            }
            
            void assign(size_type __n, const value_type& __val)
            { _M_fill_assign(__n, __val); }
            
            iterator begin()
            {   return (this->_start);}
            
            const_iterator begin() const
            {   return const_iterator(this->_start);}
            
            iterator end()
            {   return (this->_finish);}
            
            const_iterator end() const
            {   return const_iterator(this->_finish); }
            
            reverse_iterator rbegin()
            {   return reverse_iterator(end());}
            
            const_reverse_iterator rbegin() const
            {   return const_reverse_iterator(end());}

            reverse_iterator rend() 
            {   return reverse_iterator(begin()); }

            const_reverse_iterator rend() const
            {   return const_reverse_iterator(begin()); }

            size_type size() const //  number of actual objects held in the vector
            {   return (this->_finish - this->_start);}

            size_type max_size() const //maximum potential size the container can reach
            {   return _alloc.max_size();}
            
            void resize (size_type n, value_type val = value_type())
            {
                if (n > size())
                {
                    if (n == 0)
                        return;
                    if (capacity() - size() >= n)
                }
                else if (n < size())
            }

            size_type   capacity() const
            { return size_type(this->_capacity - this->_start); }

            bool empty() const 
            { return begin() == end(); }

            void reserve (size_type n)
            {
                if (n > max_size())
                    throw std::length_error("reserve length error");
                else if(n > capacity())
                {
                    size_t i = 0;
                    pointer tmp_start = _start;
                    pointer tmp_finish = _finish;
                    size_t tmp_size = size();
                    size_t tmp_cap = capacity();
                    
                    _start = _alloc.allocate(n);
                    _capacity = start + n;
                    _finish = _start;
                    while(i < tmp_size)
                    {
                        _alloc.construct(_finish, *(tmp_start + i));
                        _finish++;
                        i++;
                    }
                    _alloc.deallocate(tmp_start, tmp_cap);
                } 
            }
            void clear()
            {
                size_type n = this->size();
				for (size_t i = 0; i < n ; i++)
					_alloc.destroy(_start + i);
                this->_finish = this->start;
            }
                 
    };
    // /* relational operators */
    // template <class T, class Alloc>  
    // bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    // {
    //     if(lhs.size() != rhs.size())
    //         return (false);
    //     return();
    // }
    // template <class T, class Alloc>  
    // bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    // {
        
    // }
// (3)	
// template <class T, class Alloc>  bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
// (4)	
// template <class T, class Alloc>  bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
// (5)	
// template <class T, class Alloc>  bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
// (6)	
// template <class T, class Alloc>  bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
}

#endif

/*Allocators are objects responsible for encapsulating memory management.
 std::allocator is used when you want to separate allocation and do
  construction in two steps. It is also used when separate destruction
   and deallocation is done in two steps.
https://www.geeksforgeeks.org/how-to-implement-our-own-vector-class-in-c/*/

/* building vector container
 https://richardhnguyen.com/articles/rebuild-cpp-vector-p1
 https://www.youtube.com/watch?v=ryRf4Jh_YC0 */

 /* vector iterators
 https://www.youtube.com/watch?v=F9eDv-YIOQ0*/