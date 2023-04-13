/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 16:44:10 by nali              #+#    #+#             */
/*   Updated: 2023/04/13 14:34:09 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "../includes/normal_iterator.hpp"
#include "../includes/reverse_iterator.hpp"
#include "../includes/type_traits.hpp"
#include "../includes/compare_utils.hpp"
#include "../includes/iterator_validity.hpp"
#include <memory> //to access allocator
#include <stddef.h>

namespace ft
{
    template <class T, class Alloc = std::allocator<T> >
    class vector
    {    
        public:
            /* -- Member Types -- */
            typedef T                                           value_type;
            typedef Alloc                                       allocator_type;
            typedef size_t					                    size_type;
            typedef ptrdiff_t			                        difference_type;
            typedef typename allocator_type::pointer            pointer;
            typedef typename allocator_type::const_pointer	    const_pointer;
            typedef typename allocator_type::reference	        reference;
            typedef typename allocator_type::const_reference	const_reference;
            typedef ft::normal_iterator <T>                     iterator;
            typedef ft::normal_iterator <const T>               const_iterator;
            typedef ft::reverse_iterator<iterator>		        reverse_iterator;
            typedef ft::reverse_iterator<const_iterator>	    const_reverse_iterator;
        
        private:
            T*                  _start;     // Point to the first element
            T*                  _finish;    // Point to one-past the last element
            T*                  _capacity;  // Point to the end of the internal array(max elements it can hold)
            allocator_type      _alloc;
        
        public:
            /* -- Constructors -- */
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
            //enable_if - a compile-time switch for templates
            template <class InputIterator>  
            vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
            typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL)
            {
                ft::check_range(first, last);
                size_type d = 0;
                InputIterator tmp = first;
                while (tmp != last)
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
				    this->~vector();
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

            /* -- Member Functions -- */
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
            
            /* -- Element Access -- */
            
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
            
            /* -- Iterators -- */
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

            /* -- Capacity -- */
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
					throw std::length_error("exceeds maximum supported size");
                if (n > capacity())
                {
                    allocator_type	tmp_alloc;
                    pointer 		tmp_start 	= tmp_alloc.allocate(n);
                    size_type		tmp_size	= size();
                
                    for (size_type i = 0; i < tmp_size; i++)
                        tmp_alloc.construct(tmp_start + i, *(_start + i));
                    this->~vector();
                    
                    _start	  = tmp_start;
                    _alloc	  = tmp_alloc;
                    _finish	  = _start + tmp_size;
                    _capacity = _start + n;
                }
            }

            size_type   capacity() const
            { return size_type(this->_capacity - this->_start); }

            /* -- Modifiers -- */
            
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
                insert(position, 1, val);
                return position;
            }

            void insert (iterator position, size_type n, const value_type& val)
            {   
                // difference_type d	= position - this->begin();
                if ( n <= 0)
                    return;
                size_type d = position - this->begin();


                if (size() + n >= capacity())
                    this->reserve(ft::max(capacity() * 2, size() + n));
                size_type l = size();
                while(l - d) //shift values only if insert is not at the end
                {
                    _alloc.construct(_start + l + n - 1 , *(_start + l - 1));
                    _alloc.destroy(_start + l - 1);
                    l--;
                }
                for(size_t i = 0; i < n; i++)
                    _alloc.construct(_start + d + i, val);
                _finish = _finish + n;
            }

            template <class InputIterator>    
            void insert (iterator position, InputIterator first, InputIterator last, 
            typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL)
            {
                size_type d = position - this->begin();
                size_type n = 0;
                InputIterator tmp = first;
                size_type l = size();
                while ( tmp != last)
                {
                    tmp++;
                    n++;
                }
                if (l + n >= capacity())
                    this->reserve(ft::max(capacity() * 2, l + n));
                while(l - d)
                {
                    _alloc.construct(_start + l + n - 1 , *(_start + l - 1));
                    _alloc.destroy(_start + l - 1);
                    l--;
                }
                for(size_t i = 0; i < n; i++)
                {
                    _alloc.construct(_start + d + i, *first);
                    first++;
                }
                _finish = _finish + n;
            }

            iterator erase (iterator position)
            {
                for (iterator i = position; i != this->end() - 1; i++)
				    *i = *(i + 1);
                size_t l = size();
			    _alloc.destroy(_start + l - 1);
			    _finish--;
			    return position;
            }

        
            iterator erase (iterator first, iterator last)
            {
                if (first == last)
                    return first;
                size_type offset, d;
                offset  =  first - begin(); //dist of first from start of the array
                d = last - first;   // how many elemenst are to be erased
                size_type l = size();
                if (l - d - offset > 0)
                {
                    for(size_t i = 0; i < l - d - offset; i++)
                        *(_start + offset + i) = *(_start + offset + d + i);
                }
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
						reserve(ft::max(capacity() * 2, n));
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
    
    /* -- Relational Operators -- */
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
    (refer under the heading "Uses of enable_if")

    https://learn.microsoft.com/en-us/cpp/standard-library/enable-if-class?view=msvc-170

    In C++, substitution failure of template parameters isn't an error in itself—this is
     referred to as SFINAE (substitution failure isn't an error). Typically, enable_if 
     is used to remove candidates from overload resolution—that is, it culls the overload
     set—so that one definition can be rejected in favor of another. 
    
    For example: when a fill constructor is called ft::vector<int> vec(7,20)
    this creates a vector with 7 elements having value 20. 
    Since we have a fill constructor and range constructor defined in our 
    vector class and  both constructors take two arguments. The second 
    one has the catch-all property of templates.  So when the above statement 
    is executed it tends to call the range constructor instead of fill constructor. 
    so we have to use enable_if condition for range constructor in which case it is 
    executed only if the arguments are not integral vals.
 
 */