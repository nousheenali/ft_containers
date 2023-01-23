/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 16:44:10 by nali              #+#    #+#             */
/*   Updated: 2023/01/23 15:21:53 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory> //to access allocator

namespace ft
{
    template < class T, class Alloc = std::allocator<T> >
    class vector
    {    
        public:
            typedef T                           value_type;
            typedef Alloc                       allocator_type;
            typedef size_t					    size_type;
            typedef ptrdiff_t			        difference_type;
            typedef typename allocator_type::reference	        reference;
            typedef typename allocator_type::const_reference	const_reference;
            typedef typename allocator_type::pointer            pointer;
            typedef typename allocator_type::const_pointer	    const_pointer;
            typedef std::random_access_iterator_tag             iterator;
            // typedef std::reverse_iterator<iterator>		    reverse_iterator;
            // typedef std::reverse_iterator<const_iterator>	const_reverse_iterator;
            // typedef std::reverse_iterator<iterator>		    reverse_iterator;
        
        private:
            T*                  _start;    // Point to the first element
            T*                  _end;   // Point to one-past the last element
            T*                  _capacity;  // Point to the end of the internal array(max elements it can hold)
            allocator_type     _alloc;
        
        public:
            /*constructors*/
            /*default constructor*/
            explicit vector (const allocator_type& alloc = allocator_type()):_alloc(alloc),_start(NULL),_end(NULL),_capacity(NULL)
            {}	
            /*fill constructor*/
            explicit vector (size_type n, const value_type& val = value_type(),const allocator_type& alloc = allocator_type()):_alloc(alloc) 
            {
                int i = 0;
                _start = _alloc.allocate(n);
                _capacity = _start + n;
                _end = _start;
                while(i < n)
                {
                    this->_alloc.construct(_end, val);
                    i++;
                    _end++;
                }  
            }	
            // /*range constructor*/
            // template <class InputIterator>         
            // vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type())
            // {
                
            // } 
            /* copy constructor */
            vector (const vector& x):_alloc(x._alloc)
            {
                int i = 0;
                this->_start = this->_alloc.allocate(x._capacity - x._start);
                this->_capacity = this->_start + (x._capacity - x._start);
                this->_end = this->_start;
                while(i < (x._capacity - x._start))
                {
                    this->_alloc.construct(this->_end, *(x._start + i));
                    i++;
                    this->_end++;
                } 
            }
            /*destructor*/
            ~vector(){}
            /*copy assignment*/
            vector& operator= (const vector& x)
            {
                int i = 0;
                this->_start = this->_alloc.allocate(x._capacity - x._start);
                this->_capacity = this->_start + (x._capacity - x._start);
                this->_end = this->_start;
                while(i < (x._capacity - x._start))
                {
                    this->_alloc.construct(this->_end, *(x._start + i));
                    i++;
                    this->_end++;
                } 
                return(*this);
            }
            /*member functions*/
            iterator begin()
            {
                return (this->_start);
            }
            iterator end()
            {
                return (this->_end);
            }
            size_type size() const
            {
                return (this->_end - this->_start);
            }
                 
    };
    /* relational operators */
    template <class T, class Alloc>  
    bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        if(lhs.size() != rhs.size())
            return (false);
        {
            
        }
        
    }
    template <class T, class Alloc>  
    bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        
    }
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