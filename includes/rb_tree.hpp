/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 10:35:00 by nali              #+#    #+#             */
/*   Updated: 2023/03/01 10:55:19 by nali             ###   ########.fr       */
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
    template<typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc >
    class Rb_tree
    {       
        typedef typename Alloc::template rebind<Rb_tree_node<Val> >::other Node_allocator; // refer comment #1
        
        public:
            typedef Key                     key_type;
            typedef Val                     value_type; //this is the pair
            typedef value_type* 			pointer;
            typedef const value_type* 		const_pointer;
            typedef value_type& 			reference;
            typedef const value_type& 		const_reference;
            typedef size_t 				    size_type;
            typedef ptrdiff_t 			    difference_type;
            typedef Alloc 				    allocator_type;

        protected:
            typedef Rb_tree_node<Val>*        Node_ptr; //Link_type
            typedef const Rb_tree_node<Val>*  Const_Node_ptr; //const_Link_type
            typedef Rb_tree_node<Val>         Node_type;
            typedef const Rb_tree_node<Val>   Const_Node_type;
            // typedef Compare                 value_compare;
        
        public:
            typedef Rb_tree_iterator<value_type>       iterator;
            typedef Rb_tree_const_iterator<value_type> const_iterator;

            typedef ft::reverse_iterator<iterator>       reverse_iterator;
            typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
        
         private:
            Node_ptr                        _root;
            // Node_ptr                        _end_node; //past-the-end element
            Node_type                       _end_node; //past-the-end element, is struct not a pointer
            // Node_ptr                        _node;
            size_type                       _node_count; //node count of the tree
            Compare                         _comp;
            Node_allocator                  _node_alloc;
            allocator_type                  _alloc;
            
        private:
            void initialize(Node_ptr n)
            {
                n->_color= red;
                n->_parent = 0;
                n->_left = &_end_node;
                n->_right = &_end_node;
            }


            void rebalance_insert(Node_ptr k)
            {
		        Node_ptr uncle;

		        while (k->_parent->_color == red) 
                {
                    if (k->_parent == k->_parent->_parent->_right) 
                    {
                        uncle  = k->_parent->_parent->_left;
                        if (uncle->_color == red) 
                        {
					        // case 3.1
					        uncle->_color = black;
                            k->_parent->_color = black;
					        k->_parent->_parent->_color = red;
					        k = k->_parent->_parent;
				        } 
                        else 
                        {
                            if (k == k->_parent->_left) 
                            {
                                // case 3.2.2
                                k = k->_parent;
                                rightRotate(k); //rotate at the parent
					        }
                            // case 3.2.1
                            k->_parent->_color = black;
                            k->_parent->_parent->_color = red;
                            leftRotate(k->_parent->_parent);
				        }
			        } 
                    else 
                    {
                        uncle = k->_parent->_parent->_right; 

                        if (uncle->_color == red) 
                        {
                            // mirror case 3.1
                            uncle->_color = black;
                            k->_parent->_color = black;
                            k->_parent->_parent->_color = red;
                            k = k->_parent->_parent;	
                        } 
                        else 
                        {
                            if (k == k->_parent->_right) 
                            {
                                // mirror case 3.2.2
                                k = k->_parent;
                                leftRotate(k);
                            }
                            // mirror case 3.2.1
                            k->_parent->_color = black;
                            k->_parent->_parent->_color = red;
                            rightRotate(k->_parent->_parent);
                        }
			        }
                    if (k == root) 
                        break;
		        }
		        root->_color = black;
	        }
            // https://algorithmtutor.com/Data-Structures/Tree/Red-Black-Trees/
            // refer fig 3
            void leftRotate(Node_ptr x) 
            {
                Node_ptr y = x->_right;
                x->_right = y->_left;
                if (y->_left != end()) 
                    y->_left->_parent = x;

                y->_parent = x->_parent;
                if (x->_parent == nullptr) 
                    this->root = y;
                else if (x == x->_parent->_left) 
                    x->_parent->_left = y;
                else
                    x->_parent->_right = y;

                y->_left = x;
                x->_parent = y;
            }

            // refer fig 4
            void rightRotate(Node_ptr x) 
            {
                Node_ptr y = x->_left;
                x->_left = y->_right;
                if (y->_right != end())
                    y->_right->_parent = x;

                y->_parent = x->_parent;
                if (x->_parent == nullptr) 
                    this->root = y;
                else if (x == x->_parent->_right) 
                    x->_parent->_right = y;
                else
                    x->_parent->_left = y;

                y->_right = x;
                x->_parent = y;
            }


        protected:
            Node_ptr get_node() //allocates
            {   return _node_alloc.allocate(1); }
        
            void put_node(Node_ptr p) //deallocates
            {   _node_alloc.deallocate(p, 1); }

            Node_ptr create_node(const value_type& x)
            {
                Node_ptr tmp = get_node();
                _node_alloc.construct(tmp, x);
                initialize(tmp);
                _node_count++;
                return tmp;
            }
            
            void destroy_node(Node_ptr p)
            {
                _node_alloc.destroy(&(p->_value));
                put_node(p);
                _node_count--;
            }
            
            Node_ptr clone_node(Const_Node_ptr x)
            {
                Node_ptr tmp = create_node(x->_value);
                tmp->_color = x->_color;
                tmp->_left = 0;
                tmp->_right = 0;
                return tmp;
            }

            Node_ptr& root()
            {   return this->_root; }

            Const_Node_ptr root() const
            {   return this->_root; }

            Node_ptr begin()
            { return static_cast<Node_ptr>(this->_end_node._parent); }

            Const_Node_ptr begin() const
            {
                return static_cast<Const_Node_ptr>(this->_end_node._parent);
            }

            Node_ptr end()
            { return (&this->_end_node); }

            Const_Node_ptr end() const
            { return (&this->_end_node); }


            // Node_ptr& leftmost()
            // { 
            //     Node_ptr n = root();
            //     return (n->minimum());
            // }

            // Const_Node_ptr leftmost() const
            // { 
            //     Node_ptr n = root();
            //     return (n->minimum());
            // }

            // Node_ptr& rightmost()
            // { 
            //     Node_ptr n = root();
            //     return (n->maximum());
            // }

            // Const_Node_ptr rightmost() const
            // { 
            //     Node_ptr n = root();
            //     return (n->maximum());
            // }

            // iterator begin()
            // {  return iterator(leftmost()); }

            // const_iterator begin() const
            // {  return const_iterator(leftmost()); }

            // iterator end()
            // { return iterator(this->_end_node); }

            // const_iterator end() const
            // { return const_iterator(this->_end_node); }

            // reverse_iterator rbegin() 
            // { return reverse_iterator(end()); }

            // const_reverse_iterator rbegin() const 
            // { return const_reverse_iterator(end()); }

            // reverse_iterator rend() 
            // { return reverse_iterator(begin()); }

            // const_reverse_iterator rend() const 
            // { return const_reverse_iterator(begin()); }

            bool empty() const 
            { return _node_count == 0; }

            size_type size() const 
            { return _node_count; }

            size_type max_size() const 
            { return _node_alloc.max_size(); }

            static const Key& S_key(Node_ptr x)
            { return KeyOfValue()(x->_value); }
            
        public:
            // allocation/deallocation
            Rb_tree() { }

            explicit Rb_tree(const Compare& comp, const allocator_type& a)
            : _root(),_node_count(0), _comp(comp), _alloc(a)
            {
                // creates an end node struct
                _end_node._color= black;
                _end_node._parent = 0;
                _end_node._left = &_end_node;
                _end_node._right = &_end_node;
                _root = &(_end_node);

            }
            
            Rb_tree( Rb_tree const &x ) :_comp(x._comp), _alloc(x._alloc)                                
            {   
                _root = x._root;
                _node_count = x._node_count;
                _end_node = x._end_node;
            }

            // Rb_tree& operator = ( const Rb_tree &x )
            // {
            //     clear(); // Replacement allocator cannot free existing storage, we need to erase nodes first.
            //     this->_comp = x._comp;
            //     if (x.root() != 0)
	        //         root() = copy(x, __roan);

            //     return *this;
            // };

            ~Rb_tree( void )                                                             
            {       this->erase(this->_root); };

            void erase(Node_ptr x)
            {
                // Erase without rebalancing.
                while (x != 0)
                {
                    erase(x->_right);
                    Node_ptr y = x->_left;
	                destroy_node(x);
	                x = y;
                }
            }

            void clear()
            {
                this->erase(this->_root);
                this->reset();
            }

            void reset()
            {
                this._root = this->_end_node;
                this->_node_count = 0;
                this->_root = &(_end_node);
            }


            Node_allocator& get_Node_allocator()
            { return this->_node_alloc; }

            const Node_allocator& get_Node_allocator() const
            { return this->_node_alloc; }

            allocator_type get_allocator() const
            { return allocator_type(get_Node_allocator()); }

            pair<iterator, bool> insert_unique(const value_type & v) //refer comment #2
            {
                Node_ptr n = create_node(v);
                Node_ptr y = nullptr;
                Node_ptr x = begin();
                bool flag = true; //indicates if insert was a success
                while (x != 0) //at the end of this loop y will be the parent of new node
                {
                    y = x;
                    if(S_key(n) <  S_key(x))
                        x = x->_left;
                    else
                        x = x->_right;
                }
                iterator i = n;
                n->_parent == y;
                //inserting the node
                if (y == nullptr)
                    _root = n;
                else if (S_key(n) < S_key(y))
                    y->_left = n; 
                else if (S_key(n) > S_key(y))
                    y->_right = n;
                else //case of duplicate key
                {
                    flag = false;
                    destroy_node(n);
                    return(i, flag);
                }
                if (n->_parent == nullptr) // if n is parent node make it black
                {
                    n->_color = black;
                    return(i, flag);
                }
                if (n->_parent->_parent == nullptr) //if granparent is nul i.e., parent is root do nothing
			        return(i, flag);
                // rebalance the tree
                rebalance_insert(n);
                return(i, flag);
            }

            template<typename InputIterator>
			void	insert_range_unique(InputIterator first, InputIterator last,
            typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL)
            {
				while (first != last) 
                {
					this->insert(*first);
					++first;
				}
			}



            // void insert(const value_type& v) //refer comment #2
            // {
            //     Node_ptr n = create_node(v);
            //     Node_ptr y = nullptr;
            //     Node_ptr x = root();
            //     //at the end of this loop y will be the parent of new node
            //     while (x != 0) 
            //     {
            //         y = x;
            //         if (n->_value < x->_value)
            //             x = x->_left;
            //         else
            //             x = x->_right;
            //     }
            //     n->_parent == y;
            //     //inserting the node
            //     if (y == nullptr)
            //         _root = n;
            //     else if (n->_value < y->_value)
            //         y->_left = n;
            //     else
            //         y->_right = n;
            //     // if n is parent node make it black
            //     if (n->_parent == nullptr) 
            //     {
            //         n->_color = black;
            //         return;
		    //     }
            //     //if granparent is nul i.e., parent is root do nothing
            //     if (n->_parent->_parent == nullptr) 
			//         return;
            //     // rebalance the tree
            //     rebalance_insert(n);
            // }

            template<typename InputIterator>
	        void insert(InputIterator first, InputIterator last)
	        {
                while (first != last) 
                {
					this->insert(*first);
					++first;
				}
            }

            // iterator find(const key_type& __k);

            // const_iterator
            // find(const key_type& __k) const;

            // size_type
            // count(const key_type& __k) const;

            // iterator lower_bound(const key_type& k)
            // { 
            //     Node_ptr x = begin();
            //     Node_ptr y = end();
            //     while(x != 0)

            
            // }

            // const_iterator
            // lower_bound(const key_type& __k) const
            // { return _M_lower_bound(_M_begin(), _M_end(), __k); }

            // iterator
            // upper_bound(const key_type& __k)
            // { return _M_upper_bound(_M_begin(), _M_end(), __k); }

            // const_iterator
            // upper_bound(const key_type& __k) const
            // { return _M_upper_bound(_M_begin(), _M_end(), __k); }

            // pair<iterator, iterator>
            // equal_range(const key_type& __k);

            // pair<const_iterator, const_iterator>
            // equal_range(const key_type& __k) const;

            
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

/*  Comment #1
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

/*  Comment #2
    reference : https://algorithmtutor.com/Data-Structures/Tree/Red-Black-Trees/

*/