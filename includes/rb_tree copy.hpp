/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 10:35:00 by nali              #+#    #+#             */
/*   Updated: 2023/03/01 10:30:08 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RB_TREE_HPP
#define RB_TREE_HPP

#include "tree_node.hpp"
#include "rb_tree_iterator.hpp"
#include "reverse_iterator.hpp"
#include  <stddef.h>

namespace ft
{
    // T here is a pair<const key_type, mapped_type> from map
    template<typename T, typename Compare, typename Alloc>
    /* template <typename T, class Compare = std::less<T>, class Allocator = std::allocator<T> >*/
    class Rb_tree
    {       
        typedef typename Alloc::template rebind<Rb_tree_node<T> >::other Node_allocator; // refer comment #1
        
        public:
            typedef T                       value_type;
            typedef Compare                 value_compare;
            typedef value_type*             pointer;
            typedef const value_type*       const_pointer;
            typedef value_type&             reference;
            typedef const value_type&       const_reference;
            typedef Rb_tree_node<T>*        Node_ptr; //Link_type
            typedef const Rb_tree_node<T>*  Const_Node_ptr; //const_Link_type
            typedef size_t                  size_type;
            typedef ptrdiff_t               difference_type;
            typedef Alloc                   allocator_type;

            typedef Rb_tree_iterator<value_type>       iterator;
            typedef Rb_tree_const_iterator<value_type> const_iterator;

            // typedef ft::reverse_iterator<iterator>       reverse_iterator;
            // typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
        

         private:
            Node_ptr                        _root;
            Node_ptr                        _TNULL; //leaf node or NULL node
            Node_ptr                        _node;
            size_type                       _node_count; //node count of the tree
            Compare                         _comp;
            Node_allocator                  _node_alloc;
            allocator_type                  _alloc;
            
        private:
            void initialize()
            {
                this->_node->color= red;
                this->_node->parent = 0;
                this->_node->left = nullptr;
                this->_node->right = nullptr;
            }
        protected:
            Node_ptr get_node()
            {   return Node_allocator::allocate(1); }
        
            void put_node(Node_ptr p)
            {   Node_allocator::deallocate(p, 1); }

            Node_ptr create_node(const value_type& x)
            {
                Node_ptr tmp = get_node();
                _alloc.construct(tmp->value, x);
                initialize();
                return tmp;
            }
            
            void destroy_node(Node_ptr p)
            {
                _alloc.destroy(&(p->value));
                put_node(p);
            }
            
            Node_ptr clone_node(Const_Node_ptr x)
            {
                Node_ptr tmp = create_node(x->value);
                tmp->color = x->color;
                tmp->left = 0;
                tmp->right = 0;
                return tmp;
            }

            Node_ptr& root()
            {   return this->_root; }

            Const_Node_ptr root() const
            {   return this->_root; }

            Node_ptr& leftmost()
            { return this->_root->left; }

            Const_Node_ptr leftmost() const
            { return this->_root->left; }

            Node_ptr& rightmost()
            { return this->_root->right; }

            Const_Node_ptr rightmost() const
            { return this->_root->right;  }

            // Node_ptr begin()
            // {  return static_cast<Node_ptr>(this->_root->parent); }

            // Const_Node_ptr begin() const
            // {  return static_cast<Const_Node_ptr>(this->_node->parent); }

            // Const_Node_ptr end()
            // { return static_cast<Node_ptr>(&this->_root); }

            // Const_Node_ptr end() const
            // { return static_cast<Const_Node_ptr>(&this->_root); }

            iterator begin()
            {  return leftmost(); }

            const_iterator begin() const
            {  return leftmost(); }

            iterator end()
            { return this->root; }

            const_iterator end() const
            { return this->root; }


            static const_reference S_value(Const_Node_ptr x)
            { return x->value; }

            static Node_ptr& S_left(Node_ptr x)
            { return (Node_ptr&)(x->left); }

            static Const_Node_ptr S_left(Const_Node_ptr x)
            { return (Const_Node_ptr&)(x->left); }

            static Node_ptr& S_right(Node_ptr x)
            { return (Node_ptr&)(x->right); }

            static Const_Node_ptr S_right(Const_Node_ptr x)
            { return (Const_Node_ptr&)(x->right); }

            // static const_reference S_value(Const_Node_ptr x)
            // { return static_cast<Const_Node_ptr>(x)->value; }

            static Node_ptr minimum(Node_ptr x)
            { return minimum(x); }

            static Const_Node_ptr minimum(Const_Node_ptr x)
            { return minimum(x); }

            static Node_ptr maximum(Node_ptr x)
            { return maximum(x); }

            static Const_Node_ptr maximum(Const_Node_ptr x)
            { return maximum(x); }
            

            // Node_ptr sibling()
            // {
            //     if (node == node->parent->left) //if the current node is left node of parent
            //         return (node->parent->right);
            //     else
            //         return (node->parent.left);
            // }
            
        public:
            // allocation/deallocation
            Rb_tree() { }

            explicit Rb_tree(const value_compare& comp, const allocator_type& a)
            : _node_count(0), _comp(comp), _alloc(a),_root()
            {
                initialize(); //
            }
            
            Rb_tree( Rb_tree const &x ) :_comp(x._comp), _alloc(x._alloc)                                
            {   
                if (x.root() != 0)
                {
                    this->root() = this->copy(x.begin(), x.end());
                    this->node_count = x.node_count;
                }
            }

            Rb_tree& operator = ( const Rb_tree &x )
            {
                if ( this != &x )
                {
                    this->erase(this->begin());
                    if (x.root() != 0)
                    {
                        this->root() = this->copy(x.begin(), x.end());
                        this->node_count = x.node_count;
                    }
                }
                return *this;
            };

            // ~Rb_tree( void )                                                             
            // {       this->erase(this->begin()); };

            pair<iterator,bool> insert_unique(const value_type& v)
            {
                Node_ptr n = create_node(v);
                Node_ptr y = nullptr;
                Node_ptr x = root();
                bool comp = true;
                while (x != 0) 
                {
                    y = x;
                    if (n->value < x->value)
                        x = x->left;
                    else
                        x = x->right;
                }
                n->parent == y;
                if y == nullptr
                    root = n;
                
                
                iterator __j = iterator(__y);   
                if (__comp)
                    if (__j == begin())     
                    return pair<iterator,bool>(_M_insert(__x, __y, __v), true);
                    else
                    --__j;
                if (_M_key_compare(_S_key(__j._M_node), _KeyOfValue()(__v)))
                    return pair<iterator,bool>(_M_insert(__x, __y, __v), true);
                return pair<iterator,bool>(__j, false);
            }

            // iterator insert(const value_type& v)
            // {
            //     Node_ptr n = create_node(v);
            //     Node_ptr x = this->root();
            //     Node_ptr y = nullptr;
            //     if (x == NULL)
                
            //     while( x != NULL )
            //     {
            //         n.val < x.val
            //     }

            //     // if (_y == _M_header || __x != 0 || 
            //     //     _M_key_compare(_KeyOfValue()(__v), _S_key(__y))) {
            //     //     __z = _M_create_node(__v);
            //     //     _S_left(__y) = __z;               // also makes _M_leftmost() = __z 
            //     //                                     //    when __y == _M_header
            //     //     if (__y == _M_header) {
            //     //     _M_root() = __z;
            //     //     _M_rightmost() = __z;
            //     //     }
            //     //     else if (__y == _M_leftmost())
            //     //     _M_leftmost() = __z;   // maintain _M_leftmost() pointing to min node
            //     // }
            //     // else {
            //         z = create_node(v);
            //         S_right(_y) = z;
            //         if (__y == _M_rightmost())
            //         _M_rightmost() = __z;  // maintain _M_rightmost() pointing to max node
            //     }
            //     _S_parent(__z) = __y;
            //     _S_left(__z) = 0;
            //     _S_right(__z) = 0;
            //     _Rb_tree_rebalance(__z, _M_header->_M_parent);
            //     ++_M_node_count;
            //     return iterator(__z);
            // }
            
            // void erase(iterator pos)
            // {
            //     if (node_count != 0) 
            //     {
            //         _M_erase(_M_root());
            //         root() = 0;
            //         // _M_leftmost() = _M_header;
            //         // _M_rightmost() = _M_header;
            //         node_count = 0;
            //     }
                
            // }

            


            /* Accessors */



            // Link_type begin()
            // { return static_cast<Link_type>(this->node->parent); }

            // Const_Link_type begin() const
            // {
            //     return static_cast<Const_Link_type>(this->node->parent);
            // }

            // Link_type end()
            // { return static_cast<Link_type>(&this->node); }

            // Const_Link_type end() const
            // { return static_cast<Const_Link_type>(&this->node); }

            // static const_reference value(Const_Link_type x)
            // { return x->value; }

            // static const Key& key(Const_Link_type x)
            // { return _KeyOfValue()(_S_value(__x)); }

            // static Link_type
            // _S_left(Node_ptr __x)
            // { return static_cast<Link_type>(__x->left); }

            // static Const_Link_type
            // _S_left(Const_Node_ptr __x)
            // { return static_cast<Const_Link_type>(__x->left); }

            // static Link_type
            // _S_right(Node_ptr __x)
            // { return static_cast<Link_type>(__x->right); }

            // static Const_Link_type
            // _S_right(Const_Node_ptr __x)
            // { return static_cast<Const_Link_type>(__x->right); }

            // static const_reference
            // _S_value(Const_Node_ptr __x)
            // { return static_cast<Const_Link_type>(__x)->_M_value_field; }

            // static const _Key&
            // _S_key(Const_Node_ptr __x)
            // { return _KeyOfValue()(_S_value(__x)); }

            // static Node_ptr minimum(Node_ptr x)
            // { return x->minimum(x->right); }

            // static Const_Node_ptr minimum(Const_Node_ptr x)
            // { return x->minimum(x->right); }

            // static Node_ptr maximum(Node_ptr x)
            // { return x->maximum(x->left); }

            // static Const_Node_ptr maximum(Const_Node_ptr x)
            // { return x->maximum(x->left); }
    };
}

#endif

/*  
    Comment #1
    https://stackoverflow.com/questions/14148756/what-does-template-rebind-do

    The Alloc template is used to obtain objects of some type. The container may 
    have an internal need to allocate objects of a different type. 
    For example, 
    when you have a std::map<T, A>, the allocator A is meant to allocate objects of type T 
    but the std::map<T, A> actually needs to allocate objects of some node type. 
    Calling the node type _Ty, the std::map<T, A> needs to get hold of an allocator 
    for _Ty objects which is using the allocation mechanism provided by A. So we use rebind:
    
    typename _A::template rebind<_Ty>::other

    why separate implementation class in stl_tree.h
    https://stackoverflow.com/questions/24092264/gcc-stl-tree-h-red-black-tree-source-code-for-stdset




*/