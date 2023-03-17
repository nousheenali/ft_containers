/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 15:43:53 by nali              #+#    #+#             */
/*   Updated: 2023/02/28 15:07:52 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RB_TREE_ITERATOR_HPP
#define RB_TREE_ITERATOR_HPP

#include "tree_node.hpp"
#include "iterators.hpp"

namespace ft
{
    template<typename T>
    struct Rb_tree_iterator
    {
        typedef T  value_type;
        typedef T& reference;
        typedef T* pointer;
        
        typedef ft::bidirectional_iterator_tag  iterator_category;
        typedef std::ptrdiff_t                       difference_type;
        
        typedef Rb_tree_iterator<T>                 Self;
        typedef typename Rb_tree_node<T>::node_ptr  base_ptr;
        typedef Rb_tree_node<T>*                    Link_type;

        base_ptr node;

        Rb_tree_iterator(): node(){ }
        
        explicit Rb_tree_iterator(Link_type x):node(x) { }

        reference operator*() const
        { return node->_value;}
   
        pointer operator->() const
        { return &(node->_value); }

        base_ptr    Rb_tree_increment(base_ptr node)
        {
            //Take a step down to the right, Then run down to the left as far as possible
            if (node->_right->_type != 0) 
            {
                base_ptr y = node->_right;
                while (y->_left->_type != 0)
                    y = y->_left;
                node = y;
            }
            else //move up the tree until we have moved over a left child link
            {
                base_ptr y = node->_parent;
                while (y != 0 && node == y->_right) 
                {
                    node = y;
                    y = y->_parent;
                }
                if (node->_right != y)
                    node = y;
            }
            return node;
        }

        base_ptr Rb_tree_decrement(base_ptr node)
        {
            // if (node->_color == red && node->_parent->_parent == node)
            //     node = node->_right;
            //Take a step down to the left, Then run down to the right as far as possible
            // if (node == 0)
            // {
            //     std::cout <<"tring\n";
            //     // node = 
                
            //     // // error! ++ requested for an empty tree
            //     // if (nodePtr == nullptr)
            //     //     throw UnderflowException { };
                
            //     // // move to the smallest value in the tree,
            //     // // which is the first node inorder
            //     // while (nodePtr->left != nullptr) 
            //     //     nodePtr = nodePtr->left;
            // }
            // else
            {
                if (node->_left->_type != 0) 
                {
                    base_ptr y = node->_left;
                    while (y->_right->_type != 0)
                        y = y->_right;
                    node = y;
                }
                else //move up the tree until we have moved over a right child link
                {
                    std::cout <<"tring 2\n";
                    base_ptr y = node->_parent;
                    while (y!= 0 && node == y->_left) 
                    {
                        node = y;
                        y = y->_parent;
                    }
                    node = y;
                }
            }
            return node;
        }

        Self& operator++()
        {
            node = Rb_tree_increment(node);
            return *this;
        }
        
        Self operator++(int)
        {
            Self tmp = *this;
            node = Rb_tree_increment(node);
            return tmp;
        }

        Self& operator--()
        {
            node = Rb_tree_decrement(node);
            return *this;
        }
        
        Self operator--(int)
        {
            Self tmp = *this;
            node = Rb_tree_decrement(node);
            return tmp;
        }

        base_ptr	base() const 
        {   return (this->node);}
    
        // bool operator==(const Self& x) const
        // { return node == x.node; }
    
        // bool operator!=(const Self& x) const
        // { return node != x.node; }
      
    };
    template<typename Val>
    inline bool operator==(const Rb_tree_iterator<Val>& x,const Rb_tree_iterator<Val>& y)
    { return x.node == y.node; }

    template<typename Val>
    inline bool operator!=(const Rb_tree_iterator<Val>& x, const Rb_tree_iterator<Val>& y)
    { return x.node != y.node; }

    

    template<typename T>
    struct Rb_tree_const_iterator
    {
        typedef T  value_type;
        typedef const T& reference;
        typedef const T* pointer;

        typedef Rb_tree_iterator<T> iterator;
        
        typedef std::bidirectional_iterator_tag             iterator_category;
        typedef std::ptrdiff_t                                   difference_type;
        typedef Rb_tree_const_iterator<T>                   Self;            
        typedef typename  Rb_tree_node<T>::const_node_ptr   base_ptr;
        typedef Rb_tree_node<T>*                            Link_type;

        base_ptr node;
  
        Rb_tree_const_iterator(): node(){ }
            
        explicit Rb_tree_const_iterator(const Rb_tree_node<T>* x): node(x){ }
 
        Rb_tree_const_iterator(const  Rb_tree_const_iterator& it) : node(it.node){}

        Rb_tree_const_iterator(const iterator& it): node(it.node){ }

        reference operator*() const
        { return node->_value; }

        pointer operator->() const
        { return &(node)->_value; }

        base_ptr    Rb_tree_increment(base_ptr node)
        {
            //Take a step down to the right, Then run down to the left as far as possible
            if (node->_right->_type != 0) 
            {
                base_ptr y = node->_right;
                while (y->_left->_type != 0)
                    y = y->_left;
                node = y;
            }
            else //move up the tree until we have moved over a left child link
            {
                base_ptr y = node->_parent;
                while (y!= 0 && node == y->_right)   //if current node is right node move to parent                  
                {
                    node = y;
                    y = y->_parent;
                }
                if (node->_right != y)  
                {                      
                    node = y;
                }
            }
            return node;
        }

        base_ptr Rb_tree_decrement(base_ptr node)
        {
            std::cout << "hi---\n";
            // if (node->_color == red && node->_parent->_parent == node)
            //     node = node->_right;
            //Take a step down to the left, Then run down to the right as far as possible
            if (node->_left->_type != 0) 
            {
                base_ptr y = node->_left;
                while (y->_right->_type != 0)
                    y = y->_right;
                node = y;
            }
            else //move up the tree until we have moved over a right child link
            {
                base_ptr y = node->_parent;
                while (y!= 0 && node == y->_left) 
                {
                    node = y;
                    y = y->_parent;
                }
                node = y;
            }
            return node;
        }

        Self& operator++()
        {
            node = Rb_tree_increment(node);
            return *this;
        }

        Self operator++(int)
        {
            Self tmp = *this;
            node = Rb_tree_increment(node);
            return tmp;
        }
        
        Self& operator--()
        {
            node = Rb_tree_decrement(node);
            return *this;
        }
            
        Self operator--(int)
        {
            Self tmp = *this;
            node = Rb_tree_decrement(node);
            return tmp;
        }

        bool operator==(const Self& x) const
        { return this->node == x.node; }

        bool operator!=(const Self& x) const
        { return this->node != x.node; }

        base_ptr	base() const 
        {   return (this->node);}

};

template<typename Val>
inline bool operator==(const Rb_tree_iterator<Val>& x,const Rb_tree_const_iterator<Val>& y)
{ return x.node == y.node; }

template<typename Val>
inline bool operator!=(const Rb_tree_iterator<Val>& x, const Rb_tree_const_iterator<Val>& y)
{ return x.node != y.node; }


// template<typename Const_node_ptr, typename Value>
// inline bool operator==(const const_tree_iterator<Const_node_ptr,Value>& rhs,
// 				const const_tree_iterator<Const_node_ptr,Value>& lhs) {
// 		return (rhs.base() == lhs.base());
// 	}

// 	template<typename Const_node_ptr, typename Value>
// 	inline bool operator!=(const const_tree_iterator<Const_node_ptr,Value>& rhs,
// 				const const_tree_iterator<Const_node_ptr,Value>& lhs) {
// 		return (rhs.base() != lhs.base());
// 	}


// 	template<typename Const_node_ptr, typename Node_ptr, typename Value>
// 	inline bool operator==(const const_tree_iterator<Const_node_ptr,Value>& rhs,
// 				const tree_iterator<Node_ptr,Value>& lhs) {
// 		return (rhs.base() == lhs.base());
// 	}

// 	template<typename Const_node_ptr, typename Node_ptr, typename Value>
// 	inline bool operator!=(const const_tree_iterator<Const_node_ptr,Value>& rhs,
// 				const tree_iterator<Node_ptr,Value>& lhs) {
// 		return (rhs.base() != lhs.base());
// 	}

// 	template<typename Const_node_ptr, typename Node_ptr, typename Value>
// 	inline bool operator==(const tree_iterator<Node_ptr,Value>& rhs,
// 				const const_tree_iterator<Const_node_ptr,Value>& lhs) {
// 		return (rhs.base() == lhs.base());
// 	}

// 	template<typename Const_node_ptr, typename Node_ptr, typename Value>
// 	inline bool operator!=(const tree_iterator<Node_ptr,Value>& rhs,
// 				const const_tree_iterator<Const_node_ptr,Value>& lhs) {
// 		return (rhs.base() != lhs.base());
// 	}


}

#endif

/*
    References

    Code reference
    http://ld2014.scusa.lsu.edu/STL_doc/stl_tree.h

    Iterating through a tree
    https://www.cs.odu.edu/~zeil/cs361/latest/Public/treetraversal/index.html
    
    operator++
        If the current node has a non-null right child,
            - Take a step down to the right
            - Then run down to the left as far as possible

            If the current node has a null right child,
            - move up the tree until we have moved over a left child link
    
*/