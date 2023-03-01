/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_node.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 17:24:00 by nali              #+#    #+#             */
/*   Updated: 2023/02/24 09:17:51 by nali             ###   ########.fr       */
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
        typedef const Rb_tree_node<Val>*    Const_node_ptr;

        Val             value;
        Rb_tree_color   color;
        node_ptr        parent;
        node_ptr        left;
        node_ptr        right;

        static node_ptr minimum(node_ptr x)
        {
            while (x->left != 0) 
                x = x->left;
            return x;
        }

        static Const_node_ptr minimum(Const_node_ptr x)
        {
            while (x->left != 0) 
                x = x->left;
            return x;
        }

        static node_ptr maximum(node_ptr x)
        {
            while (x->right != 0) 
                x = x->right;
            return x;
        }

        static Const_node_ptr maximum(Const_node_ptr x)
        {
            while (x->right != 0) 
                x = x->right;
              return x;
        }
    };

    // template<typename Val>
    // struct Rb_tree_node : public Rb_tree_node_base
    // {
    //     typedef Rb_tree_node<Val>* Link_type;
    //     Val M_value_field;
 
    // };

    
}
#endif

/*
    stl_tree.h
    https://gcc.gnu.org/onlinedocs/gcc-4.8.2/libstdc++/api/a01568_source.html
*/