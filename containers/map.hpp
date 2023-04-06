/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 10:21:29 by nali              #+#    #+#             */
/*   Updated: 2023/04/06 12:15:22 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
#define MAP_HPP

#include "../includes/pair.hpp"
#include "../includes/rb_tree.hpp"
#include "../includes/compare_utils.hpp"
#include "../includes/type_traits.hpp"

namespace ft
{
    /*  Map stores elements that are key value pairs.
        No 2 elements have the same key values
        key - key type
        T - value type
        Compare - Keys are sorted by using the comparison function Compare. by default it is std::less
        Search, removal, and insertion operations have logarithmic complexity.
        ALlocator - Allocator type, defaults to allocator<pair<const _Key, _Tp>.*/
    template <class Key, class T, class Compare = ft::less<Key>,
          class Allocator = std::allocator<ft::pair<const Key, T> > >
    class map
    {
        public:
            // types:
            typedef Key                                         key_type;
            typedef T                                           mapped_type;
            typedef ft::pair<const key_type, mapped_type>       value_type;
            typedef Compare                                     key_compare;
            typedef Allocator                                   allocator_type;

        private:
            typedef ft::Rb_tree<key_type, value_type, ft::Select1st<value_type>, key_compare, allocator_type> rep_type;
            rep_type tree;
            
        public:
            typedef typename allocator_type::size_type          size_type;
            typedef typename allocator_type::difference_type    difference_type;
            typedef typename allocator_type::reference          reference;
            typedef typename allocator_type::const_reference    const_reference;
            typedef typename allocator_type::pointer            pointer;
            typedef typename allocator_type::const_pointer      const_pointer;

            typedef typename rep_type::iterator                 iterator;
            typedef typename rep_type::const_iterator           const_iterator;
            typedef typename rep_type::reverse_iterator         reverse_iterator;
            typedef typename rep_type::const_reverse_iterator   const_reverse_iterator;




            /* -- Member Class -- */
            /*  value_compare reference https://cplusplus.com/reference/map/map/value_comp/*/
            /*  - Compares objects of type std::map::value_type (key-value pairs) 
                  by comparing of the first components of the pairs.
                - A C++ functor (function object) is a class or struct object that can be called like a function.
                  It overloads the function-call operator () and allows us to use an object like a function.
                - value_compare has no public constructor, therefore no objects can be directly created from 
                  this nested class outside map members.
            */
            class value_compare: public ft::binary_function<value_type, value_type, bool>
            {
                friend class map<Key, T, Compare, Allocator>;
                protected:
                    key_compare comp;
                    value_compare(key_compare c):comp(c) //constructor
                    {}

                public:
                    bool operator() (const value_type& x, const value_type& y) const
                    {
                        return comp(x.first, y.first);
                    }
            };
        
            
            /* -- Constructors and Destructor -- */
            // construct/copy/destroy:
            // default constructors
            explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
            : tree(comp,alloc){ }
            
            template <class InputIterator>
            map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type(), 
			typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL) 
            : tree(comp, alloc)
            {
                tree.insert(first, last);
            }

            map(const map& m):tree(m.tree){}

            ~map(){}

            /* -- Member Functions -- */
            map& operator=(const map& m) 
            {
                if (this != &m)
                    this->tree = m.tree;
                return (*this);
		    }

            allocator_type get_allocator() const 
            { return allocator_type(tree.get_allocator()); }

            /* -- Element Access -- */
            mapped_type& at(const key_type& k)
            {
                iterator i = lower_bound(k);
                if (i == end())
                    std::out_of_range("out of range");
                return (*i).second;
            }

            const mapped_type& at(const key_type& k) const
            {
                const_iterator i = lower_bound(k);
                if (i == end())
                    std::out_of_range("out of range");
                return (*i).second;
            }
            
            /*returns mapped value to key k. If key not present, this function inserts a new element
             with that key and returns reference to its mappedvale*/
            mapped_type& operator[](const key_type& k)
            {
                iterator i = (insert(ft::make_pair(k,mapped_type())).first);
                return (*i).second;
            }

            /* -- Iterators -- */
            iterator begin() 
            { return tree._begin(); }

            const_iterator begin() const 
            { return tree._begin(); }

            iterator end() 
            { return tree._end(); }

            const_iterator end() const 
            { return tree._end(); }

            reverse_iterator rbegin() 
            { return tree.rbegin(); }
            
            const_reverse_iterator rbegin() const 
            { return tree.rbegin(); }

            reverse_iterator rend() 
            { return tree.rend(); }

            const_reverse_iterator rend() const 
            { return tree.rend(); }

            /* -- Capacity -- */
            bool empty() const 
            { return tree.empty(); }

            /** Returns the size of the %map.  */
            size_type size() const 
            { return tree.size(); }

            /** Returns the maximum size of the %map.  */
            size_type max_size() const 
            { return tree.max_size(); }


            /* -- Modifiers -- */

            void clear()
            { tree.clear();}
            
            /*  This function attempts to insert a (key, value) pair into the map.
                A pair is only inserted if its first element (the key) is not already 
                present in the map. Insertion requires logarithmic time.

                val - Pair to be inserted 
                Return -  A pair, of which the first element is an iterator that 
                points to the possibly inserted pair, and the second is a bool 
                that is true if the pair was actually inserted.*/
            pair<iterator,bool> insert(const value_type& val)
            { return tree.insert_unique(val); }


            /*  Attempts to insert a std::pair into the %map.

                position - An iterator that serves as a hint as to where the pair should be inserted.
                val  - Pair to be inserted 
                Return - An iterator that points to the element with key of
                @a __x (may or may not be the %pair passed in).

                *  This function is not concerned about whether the insertion
                *  took place, and thus does not return a boolean like the
                *  single-argument insert() does.  Note that the first
                *  parameter is only a hint and can potentially improve the
                *  performance of the insertion process.  A bad hint would
                *  cause no gains in efficiency.*/
    
            iterator insert (iterator position, const value_type& val)
            { 
                (void)position;
				return(this->insert(val).first);
            }
	
            /*inserts a range of elements.*/
            template <class InputIterator>  
            void insert (InputIterator first, InputIterator last)
            {   tree.insert_range_unique(first, last);}
   
            void erase(iterator position)
            { tree.erase(position);}

            size_type erase (const key_type& k)
            { 
                size_t size_before = this->size();
                size_t size_after = tree.erase(k);
                return (size_before - size_after);
            }

            void erase (iterator first, iterator last)
            { 
                tree.erase(first, last);
            }

            /*Exchanges the content of the container by the content of x, which is another 
            map of the same type. Sizes may differ.*/
            void swap (map& x)
            { 
                tree.swap(x.tree);
            }

            /* -- Lookup -- */
            size_type count (const key_type& k) const
            { return tree.count(k); }
            
            iterator find(const key_type& x)
            { return tree.find(x); }

            const_iterator find(const key_type& x) const
            { return tree.find(x); }

            iterator lower_bound(const key_type& x)
            { return tree.lower_bound(x);}

            const_iterator lower_bound (const key_type& x) const
            { return tree.lower_bound(x); }

            iterator upper_bound (const key_type& k)
            { return tree.upper_bound(k);}
            
            const_iterator upper_bound (const key_type& k) const
            { return tree.upper_bound(k); }

            pair<const_iterator,const_iterator> equal_range (const key_type& k) const
            { return tree.equal_range(k);}
            
            pair<iterator,iterator> equal_range (const key_type& k)
            { return tree.equal_range(k); }
            
            /* -- Observers -- */
            key_compare key_comp() const
            { return tree.key_comp(); }

            /* Returns a value comparison object, built from the key comparison
            object out of which the %map was constructed.*/
            value_compare value_comp() const
            { return value_compare(tree.key_comp()); }
            
    };

    /* Non-Member Functions*/
    template <class Key, class T, class Compare, class Alloc>  
    bool operator== ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs)
    {  return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());}

    template <class Key, class T, class Compare, class Alloc>  
    bool operator!= ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
    { return !(lhs == rhs); }
    
    template <class Key, class T, class Compare, class Alloc>  
    bool operator<  ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
    { return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()); }
    
    template <class Key, class T, class Compare, class Alloc>  
    bool operator<= ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
    { return !(rhs < lhs); }
    
    template <class Key, class T, class Compare, class Alloc>  
    bool operator>  ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
    { return rhs < lhs; }
    
    template <class Key, class T, class Compare, class Alloc>  
    bool operator>= ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
    { return !(lhs < rhs); }  

    template <typename Key, typename T, typename Compare, typename Alloc>
	void  swap(ft::map<Key, T, Compare, Alloc>& lhs, ft::map<Key, T, Compare, Alloc>& rhs) 
    { lhs.swap(rhs); }      
}
#endif