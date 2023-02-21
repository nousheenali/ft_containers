/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 10:35:00 by nali              #+#    #+#             */
/*   Updated: 2023/02/21 13:24:43 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RB_TREE_HPP
#define RB_TREE_HPP

namespace ft
{
    enum Rb_tree_color { _S_red = false, _S_black = true };
        
   struct Rb_tree_node_base
   {
        typedef Rb_tree_node_base*          Base_ptr;
        typedef const Rb_tree_node_base*    Const_Base_ptr;

        Rb_tree_color  M_color;
        Base_ptr       M_parent;
        Base_ptr       M_left;
        Base_ptr       M_right;

        static Base_ptr S_minimum(Base_ptr x)
        {
            while (x->M_left != 0) 
                x = x->M_left;
            return x;
        }

        static Const_Base_ptr S_minimum(Const_Base_ptr x)
        {
            while (x->M_left != 0) 
                x = x->M_left;
            return x;
        }

        static Base_ptr S_maximum(Base_ptr x)
        {
            while (x->M_right != 0) 
                x = x->M_right;
            return x;
        }

        static Const_Base_ptr _S_maximum(Const_Base_ptr x)
        {
            while (x->M_right != 0) 
                x = x->M_right;
              return x;
        }
    };

    template<typename Val>
    struct Rb_tree_node : public Rb_tree_node_base
    {
        typedef Rb_tree_node<Val>* Link_type;
        Val M_value_field;
 
    };

    template<typename T>
    struct Rb_tree_iterator
    {
        typedef T  value_type;
        typedef T& reference;
        typedef T* pointer;
        
        typedef bidirectional_iterator_tag  iterator_category;
        typedef ptrdiff_t                   difference_type;
        typedef Rb_tree_iterator<T>         Self;
        typedef Rb_tree_node_base::Base_ptr Base_ptr;
        typedef Rb_tree_node<T>*           Link_type;

//         Rb_tree_iterator(): M_node() { }
//   172 
//   173       explicit
//   174       _Rb_tree_iterator(_Link_type __x)
//   175       : _M_node(__x) { }
//   176 
//   177       reference
//   178       operator*() const
//   179       { return static_cast<_Link_type>(_M_node)->_M_value_field; }
//   180 
//   181       pointer
//   182       operator->() const
//   183       { return std::__addressof(static_cast<_Link_type>
//   184                 (_M_node)->_M_value_field); }
//   185 
//   186       _Self&
//   187       operator++()
//   188       {
//   189     _M_node = _Rb_tree_increment(_M_node);
//   190     return *this;
//   191       }
//   192 
//   193       _Self
//   194       operator++(int)
//   195       {
//   196     _Self __tmp = *this;
//   197     _M_node = _Rb_tree_increment(_M_node);
//   198     return __tmp;
//   199       }
//   200 
//   201       _Self&
//   202       operator--()
//   203       {
//   204     _M_node = _Rb_tree_decrement(_M_node);
//   205     return *this;
//   206       }
//   207 
//   208       _Self
//   209       operator--(int)
//   210       {
//   211     _Self __tmp = *this;
//   212     _M_node = _Rb_tree_decrement(_M_node);
//   213     return __tmp;
//   214       }
//   215 
//   216       bool
//   217       operator==(const _Self& __x) const
//   218       { return _M_node == __x._M_node; }
//   219 
//   220       bool
//   221       operator!=(const _Self& __x) const
//   222       { return _M_node != __x._M_node; }
//   223 
//   224       _Base_ptr _M_node;
    };


    
    template<typename Key, typename Val, typename Compare, typename Alloc>
    class Rb_tree
    {
            typedef typename Alloc::template rebind<_Rb_tree_node<_Val> >::other Node_allocator;
        
        protected:
            typedef Rb_tree_node_base*       Base_ptr;
            typedef const Rb_tree_node_base* Const_Base_ptr;

        public:
            typedef Key                     key_type;
            typedef Val                     value_type;
            typedef value_type*             pointer;
            typedef const value_type*       const_pointer;
            typedef value_type&             reference;
            typedef const value_type&       const_reference;
            typedef Rb_tree_node<Val>*      Link_type;
            typedef Rb_tree_node<Val>*      Const_Link_type;
            typedef size_t                  size_type;
            typedef ptrdiff_t               difference_type;
            typedef Alloc                  allocator_type;
    }
}

#endif