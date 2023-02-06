/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 16:44:10 by nali              #+#    #+#             */
/*   Updated: 2023/02/06 10:13:16 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "../includes/containers.hpp"
#include "../includes/normal_iterator.hpp"
#include "../includes/reverse_iterator.hpp"
#include "../includes/type_traits.hpp"
#include "../includes/compare_utils.hpp"
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
            typedef ft::normal_iterator <T>              iterator;
            typedef ft::normal_iterator <const T>       const_iterator;
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
		
            explicit vector (const allocator_type &alloc = allocator_type())
            :_start(NULL),_finish(NULL),_capacity(NULL),_alloc(alloc)
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
            
            /*range constructor*/ //refer comment #1
            template <class InputIterator>  
            vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
            typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL)
            {
                size_type d = 0;
                InputIterator tmp = first;
                while ( tmp != last)
                {
                    tmp++;
                    d++;
                }
                this->_alloc = alloc;
                this->_start = this->_alloc.allocate(d);
                this->_capacity = this->_start + d;
                this->_finish = this->_start;
                for (size_type i = 0; i < d; i++)
                {
                    this->_alloc.construct(this->_finish, *first);
                    first++;
                    this->_finish++;
                }  
            } 
            
            /* copy constructor */
            vector (const vector& x):_start(NULL),_finish(NULL),_capacity(NULL),_alloc(x._alloc)
            {   *this = x; }//calls copy assignment
            
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
                for (size_type i = 0; i < s; i++)
                {
                    this->_alloc.construct(this->_finish, *(x._start + i));
                    this->_finish++;
                }
                return(*this);
            }
            /*member functions*/

            template <class InputIterator>  
            void assign (InputIterator first, InputIterator last,
            typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL)
            {
                size_type d = 0;
                InputIterator tmp = first;
                while ( tmp != last)
                {
                    tmp++;
                    d++;
                }
                if (d > capacity())
                    reserve(d);
                clear();
                // if (first > last)
                //     throw std::length_error("cannot create ft::vector larger than max_size()");
                while(first != last)
                {
                    _alloc.construct(_finish, *first);
                    first++;
                    _finish++;
                }
            }

            void assign (size_type n, const value_type& val)
            {
                if (n > capacity())
                {
                     _alloc.deallocate(_start, capacity());
                    _start = _alloc.allocate(n);
                    _capacity = _start + n;
                    _finish = _start;
                     while (n--)
                    {
                        _alloc.construct(_finish, val);
                        _finish++;
                    }
                }
                else
                {
                    clear();
                    while (n--)
                    {
                        _alloc.construct(_finish, val);
                        _finish++;
                    }
                }
            }

            allocator_type get_allocator() const
            {
                return _alloc;
            }
            
            /*Element Access*/
            reference at (size_type n)
            {
                if ( n >= size())
                    throw(std::out_of_range("Index out of range"));
                return *(this->_start + n);
            }
            
            const_reference at (size_type n) const
            {
                if ( n >= size())
                    throw(std::out_of_range("Index out of range"));
                return *(this->_start + n);
            }

            reference operator[](size_type n)
            {   return *(this->_start + n);}

            const_reference operator[] (size_type n) const
            {   return *(this->_start + n);}

            reference front() 
            {   return *this->begin();}

		    const_reference front() const 
            {   return *this->begin();}

		    reference back() 
            {   return *(this->end() - 1);}

		    const_reference back() const 
            {   return *(this->end() - 1);}
            
            /*Iterators*/
            iterator begin()
            {   return iterator(this->_start);}
            
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

            /*Capacity*/
            bool empty() const 
            { return begin() == end(); }

            size_type size() const //  number of actual objects held in the vector
            {   return (this->_finish - this->_start);}

            size_type max_size() const //maximum potential size the container can reach
            { 
                return _alloc.max_size();
            }

            void reserve (size_type n)
            {
                if (n > max_size())
                    throw std::length_error("reserve length error");
                else if(n > capacity())
                {
                    pointer tmp_start = _start;
                    // pointer tmp_finish = _finish;
                    size_t tmp_size = size();
                    size_t tmp_cap = capacity();
                    
                    _start = _alloc.allocate(n);
                    _capacity = _start + n;
                    _finish = _start;
                    for (size_type i = 0; i < tmp_size; i++, _finish++)
                        _alloc.construct(_finish, *(tmp_start + i));
                    _alloc.deallocate(tmp_start, tmp_cap);
                } 
            }

            size_type   capacity() const
            { return size_type(this->_capacity - this->_start); }

            /* Modifiers */
            
            void clear()
            {   
                size_type n = this->size();
                if (n == 0)
                    return;
				for (size_t i = 0; _start + i != _finish ; i++)
					_alloc.destroy(_start + i);
                _finish = _start;
            }

            iterator insert (iterator position, const value_type& val)
            {
   
                return(this->insert(position, 1, val));
            }

            iterator insert (iterator position, size_type n, const value_type& val)
            {   
                size_type d = position - this->begin();
                if (d >= 0)
                {
                    if(!_capacity)
                        reserve(1);
                    else if (size() + n > capacity())
                        reserve(std::max(capacity() * 2, size() + n));
                    size_type l = size();
                    while(l - d) //shift values only if insert is not at the end
                    {
                        _alloc.construct(_start + l + n - 1 , *(_start + l - 1));
                        l--;
                    }
                    for(size_t i = 0; i < n; i++)
                        _alloc.construct(_start + d + i, val);
                    _finish = _finish + n;
                }
                return (position);
            }
    	
            template <class InputIterator>    
            iterator insert (iterator position, InputIterator first, InputIterator last, 
            typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL)
            {
                size_type d = position - this->begin();
                size_type n = 0;
                InputIterator tmp = first;
                while ( tmp != last)
                {
                    tmp++;
                    n++;
                }
                if (d >= 0)
                {
                    if(!_capacity)
                        reserve(n);
                    else if (size() + n > capacity())
                        reserve(std::max(capacity() * 2, size() + n));
                    size_type l = size();
                    while(l - d)
                    {
                        _alloc.construct(_start + l + n - 1 , *(_start + l - 1));
                        l--;
                    }
                    for(size_t i = 0; i < n; i++)
                    {
                        _alloc.construct(_start + d + i, *first);
                        first++;
                    }
                    _finish = _finish + n;
                }
                return (position);

            }

            iterator erase (iterator position)
            {
                size_type d = position - this->begin();
                size_type l = size();
                while(d < l)
                {
                    _alloc.construct(_start + d, *(_start + d + 1));
                    d++;
                }
                _alloc.destroy(_finish);
                _finish--;
                return (position);
            }

        
            iterator erase (iterator first, iterator last)
            {
                size_type offset, d;
                offset  =  first - begin(); //dist of first from start of the array
                d = last - first;   // how many elemenst are to be erased
                size_type l = size();
                for(size_t i = 0; i < l - d - offset; i++)
                    _alloc.construct(_start + offset + i , *(_start + offset + d + i));
                for (size_type j = l - d; j < l; j++) 
				    _alloc.destroy(_start + j);
			    _finish -= d ;
                return first;
            }

            void	push_back( const T& value)
            {
				if (size() == capacity()) 
                {
					if (!(size()))
						reserve(1);
					else
						reserve(capacity() * 2);
				}
				_alloc.construct(_finish, value);
				_finish++;
			}

            void pop_back(void) 
            {
				this->_alloc.destroy(_finish - 1);
				this->_finish--;
			}

            void resize (size_type n, value_type val = value_type())
            {
                if (n > max_size()) 
				    throw std::length_error("ft::vector::resize");
			    if (n < size()) 
                {
					while (n < size()) 
                    {
						this->_finish--;
						this->_alloc.destroy(_finish);
					}
				}
                else
                {
                    if (this->capacity() < n)
						reserve(n);
					while (this->size() != n) 
                    {
						this->_alloc.construct(_finish, val);
						this->_finish++;
                    }

                }
			
            }

            void swap (vector& x)
            {
				allocator_type	tmp_alloc = x._alloc;
				pointer			tmp_start = x._start;
				pointer			tmp_finish = x._finish;
				pointer			tmp_capacity = x._capacity;

				x._alloc = this->_alloc;
				x._start = this->_start;
				x._finish = this->_finish;
				x._capacity = this->_capacity;
				this->_alloc = tmp_alloc;
				this->_start = tmp_start;
				this->_finish = tmp_finish;
				this->_capacity = tmp_capacity;
			}
    };
    /* relational operators */
    template <class T, class Alloc>  
    bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        if(lhs.size() != rhs.size())
            return (false);
        return(ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
    }

    template <class T, class Alloc>  
    bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        return !(lhs == rhs);
    }

    template <class T, class Alloc>  
    bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
    }

    template <class T, class Alloc>  
    bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        return !(lhs > rhs);
    }

    template <class T, class Alloc>  
    bool operator> (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        return (rhs < lhs);
    }

    template <class T, class Alloc>  
    bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        return !(lhs < rhs);
    }
    
    template <class T, class Alloc>
	void swap (vector<T,Alloc>& lhs, vector<T,Alloc>& rhs) {
		lhs.swap(rhs);
	}
}

#endif

/*  Allocators are objects responsible for encapsulating memory management.
    std::allocator is used when you want to separate allocation and do
    construction in two steps. It is also used when separate destruction
    and deallocation is done in two steps.
    https://www.geeksforgeeks.org/how-to-implement-our-own-vector-class-in-c/*/

/*  building vector container
    https://richardhnguyen.com/articles/rebuild-cpp-vector-p1
    https://www.youtube.com/watch?v=ryRf4Jh_YC0 */

 /* vector iterators
    https://www.youtube.com/watch?v=F9eDv-YIOQ0*/

 /* comment #1
    SOmetimes while calling fill contsructor for int values, the system will call the 
    range constructor. So we have to include a  trait check to verify that arguments 
    of range constructor are iterators over T elements
    https://stackoverflow.com/questions/45847787/how-to-differentiate-fill-constructor-and-range-constructor-in-c11
 
    Better explanation (also explains SFINAE and enable_if)
    https://eli.thegreenplace.net/2014/sfinae-and-enable_if/

    https://learn.microsoft.com/en-us/cpp/standard-library/enable-if-class?view=msvc-170
 
 */