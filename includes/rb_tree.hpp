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
#include "type_traits.hpp"
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
            typedef std::ptrdiff_t 			difference_type;
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
            Node_type                       _end_node; //past-the-end element, is struct not a pointer
            size_type                       _node_count; //node count of the tree
            Compare                         _comp;
            Node_allocator                  _node_alloc;
            allocator_type                  _alloc;
            
        private:
            void initialize(Node_ptr n)
            {
                n->_type = 0;
                n->_color= red;
                n->_parent = &_end_node;
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
                    if (k == _root) 
                        break;
		        }
		        _root->_color = black;
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
                if (x->_parent == 0) 
                    this->_root = y;
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
                if (x->_parent == 0) 
                    this->_root = y;
                else if (x == x->_parent->_right) 
                    x->_parent->_right = y;
                else
                    x->_parent->_left = y;

                y->_right = x;
                x->_parent = y;
            }

            void swap_color(Node_ptr x)
            {
                if (x->_color == red)
                    x->_color = black;
                else
                    x->_color = red;
            }

            void rebalance_delete(Node_ptr x) 
            {
                Node_ptr s; //sibling
                while (x != _root && x->_color == black) 
                {
                    if (x == x->_parent->_left) 
                    {
                        s = x->_parent->_right; 
                        if (s->_color == red) // case 3.1
                        {
                            swap_color(s);
                            swap_color(x->_parent);
                            leftRotate(x->_parent);
                            s = x->_parent->_right; //new sibling
                        }
                        if(s->_color == black)
                        {
                            if (s->_left->_color == black && s->_right->_color == black) // case 3.2
                            {
                                s->_color = red;
                                x = x->_parent;
                            } 
                            else 
                            {
                                if (s->_right->_color == black) // case 3.3
                                {
                                    s->_left->_color = black;
                                    s->_color = red;
                                    rightRotate(s);
                                    s = x->_parent->_right;
                                } 
                                // case 3.4
                                // s->_color = x->_parent->_color;
                                x->_parent->_color = black;
                                s->_right->_color = black;
                                leftRotate(x->_parent);
                                x = _root;
                            }
                        }
                    } 
                    else 
                    {
                        s = x->_parent->_left;
                        if (s->_color == red) // case 3.1
                        {
                            swap_color(s);
                            swap_color(x->_parent);
                            rightRotate(x->_parent);
                            s = x->_parent->_left;
                        }
                        if (s->_color == black)
                        {
                            if (s->_right->_color == black && s->_right->_color == black) // case 3.2
                            {
                                s->_color = red;
                                x = x->_parent;
                            } 
                            else 
                            {
                                if (s->_left->_color == black)  // case 3.3
                                {
                                    s->_right->_color = black;
                                    s->_color = red;
                                    leftRotate(s);
                                    s = x->_parent->_left;
                                } 
                                // case 3.4
                                // s->_color = x->_parent->_color;
                                x->_parent->_color = black;
                                s->_left->_color = black;
                                rightRotate(x->_parent);
                                x = _root;
                            }
                        }
                    } 
                }
                x->_color = black;
	        }

         
            // this function replaces u node with v node by changing all links
            // that point to u to point to v
            void replace_node(Node_ptr u, Node_ptr v)
            {
                if (u->_parent == 0) 
                    this->_root = v;
                else if (u == u->_parent->_left)
                    u->_parent->_left = v;
                else
                    u->_parent->_right = v;
                v->_parent = u->_parent;
            }

            void delete_helper(Node_ptr node, key_type key) //Refer comment #3
            {
                Node_ptr z = this->end();
                Node_ptr x, y;
                while (node != end()) //find position of key
                {
                    if (S_key(node) == key)
                        z = node;
                    if (S_key(node) < key) 
                        node = node->_right;
                    else
                        node = node->_left;
                }
                if (z == end()) //key not found
                    return;
                y = z;
		        int y_original_color = y->_color;
                //check if both child nodes or one of the child nodes is null. If yes, 
                // replace the node to be deleted with the child node and delete the node.
                if (z->_left == end()) 
                {
                    x = z->_right;
                    replace_node(z, z->_right);
                }
                else if (z->_right == end()) 
                {
                    x = z->_left;
                    replace_node(z, z->_left);
                } 
                else //if both childs are not null
                {
                    y = z->minimum(z->_right); //inorder successor
                    y_original_color = y->_color;
                    x = y->_right;
                    // if (y->_parent == z)
                    //     x->_parent = y;
                    // else 
                    if (y->_parent != z)
                    {
                        replace_node(y, y->_right); //moving y->_right to position of y
                        y->_right = z->_right; //moving y to position of z
                        y->_right->_parent = y;
                    }
                    replace_node(z, y);
                    y->_left = z->_left;
                    y->_left->_parent = y;
                    y->_color = z->_color;
                }
                destroy_node(z);
                if (y_original_color == black)
                    rebalance_delete(x);
	        }

            Node_ptr copy(Node_ptr x, Node_ptr p)
            {
                // structural copy.  x and p must be non-null.
                // std::cout <<"hello "<< (int)S_key(x)<<std::endl;
                Node_ptr top = clone_node(x);
                top->_parent = p;
                try
                {
                    if (S_key(x->_right))
                        top->_right = copy(x->_right, top);
                    p = top;
                    x = x->_left;
                    while (S_key(x))
                    {
                        Node_ptr y = clone_node(x);
                        p->_left = y;
                        y->_parent = p;
                        if (S_key(x->_right))
                            y->_right = copy(x->_right, y);
                        p = y;
                        x = x->_left;
                    }
                }
                catch(const std::exception& e)
                {
                    this->erase(top); 
                }
                return top;
            }

            // Node_ptr	end_node() 
            // {  return (&this->_end_node);}

			// Const_Node_ptr	end_node() const 
            // {  return (const_cast<const_node_ptr>(&this->_end_node));}
        public:
        
            Node_ptr Rb_tree_decrement(Node_ptr node)
            {
                if (node == 0)
                {
                    node = rightmost();
                    // node = 
                    
                    // // error! ++ requested for an empty tree
                    // if (nodePtr == nullptr)
                    //     throw UnderflowException { };
                    
                    // // move to the smallest value in the tree,
                    // // which is the first node inorder
                    // while (nodePtr->left != nullptr) 
                    //     nodePtr = nodePtr->left;
                }
                else
                {
                    if (node->_left->_type != 0) 
                    {
                        Node_ptr y = node->_left;
                        while (y->_right->_type != 0)
                            y = y->_right;
                        node = y;
                    }
                    else //move up the tree until we have moved over a right child link
                    {
                        // std::cout <<"tring 2\n";
                        Node_ptr y = node->_parent;
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

        public:
            Node_ptr get_node() //allocates
            {   return _node_alloc.allocate(1); }
        
            void put_node(Node_ptr p) //deallocates
            {   _node_alloc.deallocate(p, 1); }

            Node_ptr create_node(const value_type& x)
            {
                Node_ptr tmp = get_node();
                //instead of node_alloc we have alloc coz we want to just assign the pair 
                // value not the entire node structure which contains other values also
                _alloc.construct(&tmp->_value, x); 
                initialize(tmp);
                tmp->_type = 1; //changing type from leaf node to regular node
                _node_count++;
                return tmp;
            }
            
            void destroy_node(Node_ptr p)
            {
                _alloc.destroy(&p->_value);
                put_node(p);
                _node_count--;
            }
            
            Node_ptr clone_node(Const_Node_ptr x)
            {
                Node_ptr tmp = create_node(x->_value);
                tmp->_color = x->_color;
                tmp->_left = &_end_node;
                tmp->_right = &_end_node;
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
            { return static_cast<Const_Node_ptr>(&this->_end_node); }


            iterator _begin() 
            {   
                if (_root == end()) // if empty
                    return (_end());
                Node_ptr i = _root;
                while (i->_left != end()) 
                    i = i->_left;
                return iterator(i); 
            }

            const_iterator _begin() const 
            {
               if (_root == end()) //if empty
                    return (_end());
                Node_ptr i = _root;
                while (i->_left != end()) 
                    i = i->_left;
                return const_iterator(i);
            }

            iterator _end()
            { 
               return iterator(this->_end_node._parent);
            } 

            const_iterator _end() const
            {
                return const_iterator(this->_end_node._parent);
            }

    //         // iterator end()
    //         // { return iterator(this->_end_node); }

    //         // const_iterator end() const
    //         // { return const_iterator(this->_end_node); }

    //         // reverse_iterator rbegin() 
    //         // { return reverse_iterator(end()); }

    //         // const_reverse_iterator rbegin() const 
    //         // { return const_reverse_iterator(end()); }

    //         // reverse_iterator rend() 
    //         // { return reverse_iterator(begin()); }

    //         // const_reverse_iterator rend() const 
    //         // { return const_reverse_iterator(begin()); }

            bool empty() const 
            { return _node_count == 0; }

            size_type size() const 
            { return _node_count; }

            size_type max_size() const 
            { return _node_alloc.max_size(); }

            static const Key& S_key(Const_Node_ptr x)
            { return KeyOfValue()(x->_value); }

            Node_ptr rightmost() const 
            { 
                Node_ptr i = _root;
                while (i->_right != end()) 
                    i = i->_right;
                return (i);
            }

            // Node_ptr minimum(Node_ptr x)
            // {
            //     while (x->_left != &_end_node) 
            //         x = x->_left;
            //     return x;
            // }

            // Node_ptr maximum(Node_ptr x)
            // {
            //     while (x->_right != &_end_node) 
            //         x = x->_right;
            //     return x;
            // }
            
        public:
            // allocation/deallocation
            Rb_tree() { }

            explicit Rb_tree(const Compare& comp, const allocator_type& a)
            : _root(),_node_count(0), _comp(comp), _alloc(a)
            {
                // creates an end node struct
                _end_node._color= black;
                _end_node._type = 0; //specifying type as leaf node
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

            Rb_tree& operator=(const Rb_tree &x)
            {
                if(this != &x)
                {
                    clear(); // Replacement allocator cannot free existing storage, we need to erase nodes first.
                    this->_node_count = 0;
                    this->_comp = x._comp;
                    if (x.root() == 0) 
                    {
                        root() = 0;
                        _root->_left = &_end_node;
                        _root->_right = &_end_node;
                    }
                    else
                    {
                        root() = copy(x._root, end());
                        this->_root->_parent = x._root->_parent;
                        _node_count = x._node_count;
                    }
                }
                return *this;
            }


            ~Rb_tree( void )                                                             
            {       this->erase(begin()); };

            Node_allocator& get_Node_allocator()
            { return this->_node_alloc; }

            const Node_allocator& get_Node_allocator() const
            { return this->_node_alloc; }

            allocator_type get_allocator() const
            { return allocator_type(get_Node_allocator()); }

            ft::pair<iterator, bool> insert_unique(const value_type & v) //refer comment #2
            {
                Node_ptr n = create_node(v);
                Node_ptr y = 0;
                Node_ptr x = this->_root;
                bool flag = true; //indicates if insert was a success
                while (x != end()) //at the end of this loop y will be the parent of new node
                {
                    y = x;
                    if(S_key(n) <  S_key(x))
                        x = x->_left;
                    else
                        x = x->_right;
                }
                iterator i(n);
                n->_parent = y;
                //inserting the node
                if (y == 0)
                    _root = n;
                else if (S_key(n) < S_key(y))
                    y->_left = n;
                else if (S_key(n) > S_key(y))
                    y->_right = n;
                else //case of duplicate key
                {
                    flag = false;
                    destroy_node(n);
                    return (ft::make_pair(i, flag));
                }
                if (n->_parent == 0) // if n is root node make it black
                {
                    n->_color = black;
                    return(ft::make_pair(i, flag));
                }
                if (n->_parent->_parent == 0) //if granparent is nul i.e., parent is root do nothing
                    return(ft::make_pair(i, flag));
                // rebalance the tree
                rebalance_insert(n);
                return (ft::make_pair(i, flag));
            }

            template<typename InputIterator>
			void	insert_range_unique(InputIterator first, InputIterator last,
            typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL)
            {
				while (first != last) 
                {
					this->insert_unique(*first);
					++first;
				}
			}

            template<typename InputIterator>
	        void insert(InputIterator first, InputIterator last)
	        {
                while (first != last) 
                {
					this->insert_unique(*first);
					++first;
				}
            }

            void erase(const_iterator position)
            {
                if (position != end())
                {
                    Node_ptr y = (Node_ptr)position.base();
				    this->delete_helper(this->root(), y->_value.first);
                    destroy_node(y);
                }
            }

            void erase(const_iterator first, const_iterator last)
            {
                iterator tmp;
                while (first != last) 
                {   
                    tmp = first;
					this->erase(*tmp);
					++first;
				}
            }

            //deletes a key value pair with key value x
            size_type erase(const key_type& x)
            {
                delete_helper(this->root(), x);
                return (_node_count);
            }

            //erases the entire tree
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
                this->erase(begin());
                this->reset();
            }

            void reset()
            {
                this->_node_count = 0;
                this->_root = &(_end_node);
            }

            iterator find(const key_type& k)
            {
                iterator j = lower_bound(k);
                return (j);
            }

            const_iterator find(const key_type& k) const
            {
                const_iterator j = lower_bound(k);
                return (j);
            }

            size_type count(const key_type& k) const
            {  return (this->find(k) == this->end() ? 0 : 1);}

            /* Returns an iterator pointing to the first element in the container
             whose key is not considered to go before k (i.e., either it is equivalent or goes after).*/
            iterator lower_bound(const key_type& k)
            { 
                Node_ptr x = root();
                iterator y = _end();
                while(x->_type!= 0)
                {
                    if (!this->_comp(S_key(x), k)) //if k < x
                    {
                        y= iterator(x);
                        x = x->_left;
                    }
                    else
                        x = x->_right;
                }
                return iterator(y);
            }


            const_iterator lower_bound(const key_type& k) const
            { 
                Const_Node_ptr x = root();
                const_iterator y = _end();
                while(x->_type!= 0)
                {
                    if (!this->_comp(S_key(x), k))
                    {
                        y= const_iterator(x);
                        x = x->_left;
                    }
                    else
                        x = x->_right;
                }
                return const_iterator(y); 
            }

            iterator upper_bound(const key_type& k)
            { 
                Node_ptr x = root();
                iterator y = _end();
                while(x->_type!= 0)
                {
                    if (this->_comp(k, S_key(x)))
                    {
                        y= iterator(x);
                        x = x->_left;
                    }
                    else
                        x = x->_right;
                }
                return iterator(y);
            }

            const_iterator upper_bound(const key_type& k) const
            { 
                Const_Node_ptr x = root();
                const_iterator y = _end();
                while(x->_type!= 0)
                {
                    if (this->_comp(k, S_key(x)))
                    {
                        y= const_iterator(x);
                        x = x->_left;
                    }
                    else
                        x = x->_right;
                }
                return const_iterator(y); 
            }

            // void swap(Rb_tree& t)
            // {
            //     std::swap(this.root(),t.root());
            //     // std::swap(_M_leftmost(),__t._M_leftmost());
            //     // std::swap(_M_rightmost(),__t._M_rightmost());
            //     root()->_parent = end();
            //     t.root()->_parent = t.end();
            //     std::swap(this->_node_count, t._node_count);                    // No need to swap header's color as it does not change.
            //     std::swap(this->_comp, t._comp);
            //     std::__alloc_on_swap(this->get_Node_allocator(), t.get_Node_allocator());
            // }

            Compare key_comp() const
            { return _comp; }

            /*Returns the bounds of a range that includes all the elements in the container which 
            have a key equivalent to k. Because the elements in a map container have unique keys, 
            the range returned will contain a single element at most.
            If no matches are found, the range returned has a length of zero, with both iterators 
            pointing to the first element that has a key considered to go after k*/
            ft::pair<iterator, iterator> equal_range(const key_type& k)
            {
               return pair<iterator, iterator>(lower_bound(k), upper_bound(k));
            }

            ft::pair<const_iterator,const_iterator> equal_range(const key_type& k) const 
            {
                return pair<const_iterator,const_iterator>(lower_bound(k), upper_bound(k));
			}



    

    // ft::pair<iterator, iterator> equal_range(const key_type& k)
    //         {
                
    //             Node_ptr x = root();
    //             Node_ptr y = end();
    //             while (x->_type != 0)
    //             {
    //                 if (this->_comp(S_key(x), k))
    //                     x = x->_right;
    //                 else if (this->_comp(k, S_key(x)))
    //                 {
    //                     y = x;
    //                     x = x->_left;
    //                 }
    //                 else
    //                 {
    //                     // Node_ptr xu(x);
    //                     // Node_ptr yu(y);
    //                     // y = x, x = x->_left;
    //                     // xu = xu->_right;
    //                     return ft::make_pair(lower_bound(k),upper_bound(k));
    //                 }
    //             }
    //             // return ft::make_pair(iterator(y),iterator(y));
    //         }

            
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

/*  Comment #3
    reference videos:
        bst deletion: https://www.youtube.com/watch?v=cySVml6e_Fc
        redbalck tree deletion: https://www.youtube.com/watch?v=w5cvkTXY0vQ&t=2422s
*/