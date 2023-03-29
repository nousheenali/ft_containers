/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_node.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 17:24:00 by nali              #+#    #+#             */
/*   Updated: 2023/03/26 23:00:41 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_NODE_HPP
#define TREE_NODE_HPP

namespace ft
{
     enum Rb_tree_color { red = false, black = true };
        
    template<typename Val>
    struct Rb_tree_node
    {
        typedef Rb_tree_node<Val>*          node_ptr;
        typedef const Rb_tree_node<Val>*    const_node_ptr;

        Val             _value;
        bool            _end_element; //true(1) - end node, false(0)-other nodes
        Rb_tree_color   _color;
        node_ptr        _parent;
        node_ptr        _left;
        node_ptr        _right;

        Rb_tree_node():_value(),_color(black),_parent(), _left(), _right(){}

        Rb_tree_node(const Rb_tree_node& x) 
        : _value(x._value), _color(x._color), _parent(x._parent), _left(x._left), _right(x._right){}
        
        Rb_tree_node& operator=(const Rb_tree_node& x) 
        {
			if (this != &x) 
            {
				this->_value = x._value;
				this->_color = x._color;
				this->_parent = x._parent;
				this->_left = x._left;
				this->_right = x._right;
			}
			return (*this);
		}
        
        ~Rb_tree_node(){}

        static node_ptr minimum(node_ptr x)
        {
            while (x->_left->_end_element != true) 
                x = x->_left;
            return x;
        }

        static const_node_ptr minimum(const_node_ptr x)
        {
            while (x->_left->_end_element != true) 
                x = x->_left;
            return x;
        }

        static node_ptr maximum(node_ptr x)
        {
            while (x->_right->_end_element != true) 
                x = x->_right;
            return x;
        }

        static const_node_ptr maximum(const_node_ptr x)
        {
            while (x->_right->_end_element != true) 
                x = x->_right;
              return x;
        }
        
        Val* valptr()
        { return &(_value); }

        const Val* valptr() const
        { return &(_value); }

    };

    template<typename Key_compare>
    struct Rb_tree_key_compare
    {
      Key_compare		_key_compare;

      Rb_tree_key_compare(): _key_compare()
      { }

      Rb_tree_key_compare(const Key_compare& comp)
      : _key_compare(comp)
      { }

    };
}
#endif

/*
    stl_tree.h
    https://gcc.gnu.org/onlinedocs/gcc-4.8.2/libstdc++/api/a01568_source.html
*/