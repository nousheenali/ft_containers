/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 10:35:00 by nali              #+#    #+#             */
/*   Updated: 2023/03/29 23:13:08 by nali             ###   ########.fr       */
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
            Node_ptr                        _end_node; //past-the-end element, is struct not a pointer
            size_type                       _node_count; //node count of the tree
            Compare                         _comp;
            Node_allocator                  _node_alloc;
            allocator_type                  _alloc;
            
        private:
            void initialize(Node_ptr n)
            {
                n->_end_element = false;
                n->_color= red;
                n->_parent = _end_node;
                n->_left = _end_node;
                n->_right = _end_node;
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
					        k = k->_parent->_parent; // to repeat 
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
                if (x->_parent == end()) 
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
                if (x->_parent == end()) 
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
                                // x->_parent->_color = black;
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
                                s->_color = x->_parent->_color;
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
                                // x->_parent->_color = black;
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
                                s->_color = x->_parent->_color;
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

            Node_ptr find_position(Node_ptr node, key_type key)
            {
                while (node != end()) //find position of key
                {
                    if (S_key(node) == key)
                    {
                        return (node);
                    }
                    else if (_comp(S_key(node),key)) //node < key
                        node = node->_right;
                    else
                        node = node->_left;
                }
                return (end());
            }
            
            // this function replaces u node with v node by changing all links
            // that point to u to point to v
            void replace_node(Node_ptr u, Node_ptr v)
            {
                if (u->_parent == end()) 
                    this->_root = v;
                else if (u == u->_parent->_left)
                    u->_parent->_left = v;
                else
                    u->_parent->_right = v;
                v->_parent = u->_parent;
            }

            void delete_helper(Node_ptr node, key_type key) //Refer comment #3
            {
                Node_ptr x, y;
                Node_ptr z = find_position(node, key);
                if (z == end()) //key not found
                    return ;  
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
                    if (y->_parent == z)
                        x->_parent = y;
                    else //y->_parent != z
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
                // std::cout <<S_key(x)<<std::endl;
                Node_ptr top = clone_node(x);
                top->_parent = p;
                try
                {
                    if (x->_right->_end_element != true)
                        top->_right = copy(x->_right, top);
                    p = top;
                    x = x->_left;
                    while (x->_end_element != true)
                    {
                        Node_ptr y = clone_node(x);
                        p->_left = y;
                        y->_parent = p;
                        if (x->_right->_end_element != true)
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

            Node_ptr find_parent_node(Node_ptr x, Node_ptr n, bool *flag)
            {
                Node_ptr y = end();
                //at the end of this loop y will be the parent of new node
                while (x != end()) 
                {
                    y = x;
                    if(_comp(S_key(n), S_key(x)))
                        x = x->_left;
                    else if(_comp(S_key(x), S_key(n)))
                        x = x->_right;
                    else //if duplicate key
                    {
                        *flag = false;
                        destroy_node(n);
                        return (x);
                    }
                }
                return (y);
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
                return tmp;
            }

            Node_ptr& root()
            {   return this->_root; }

            Const_Node_ptr root() const
            {   return this->_root; }

            Node_ptr begin()
            { 
                if (_root == end()) // if empty
                    return (end());
                return(_end_node->_right);
                // Node_ptr i = _root;
                // while (i->_left->_end_element != true) // can use condition (i->_left != end()), but creates problem after swap
                //     i = i->_left;
                // return (i);
            }

            Const_Node_ptr begin() const
            {
                if (_root == end()) // if empty
                    return (end());
                return(_end_node->_right);
                // Const_Node_ptr i = _root;
                // while (i->_left->_end_element != true)  // can use condition (i->_left != end()), but creates problem after swap
                //     i = i->_left;
                // return (i);
            }

            Node_ptr end()
            { return (this->_end_node); }

            Const_Node_ptr end() const
            { return (this->_end_node); }

            iterator _begin() 
            { return iterator(begin()); }

            const_iterator _begin() const 
            { return const_iterator(begin());}

            iterator _end()
            { return iterator(end());} 

            const_iterator _end() const
            { return const_iterator(end());}

            reverse_iterator rbegin() 
            { return reverse_iterator(_end()); }

            const_reverse_iterator rbegin() const 
            { return const_reverse_iterator(_end()); }

            reverse_iterator rend() 
            { return reverse_iterator(_begin()); }

            const_reverse_iterator rend() const 
            { return const_reverse_iterator(_begin()); }

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
                if (i != end())
                {
                    while (i->_right->_end_element != true) 
                        i = i->_right;
                }
                return (i);
            }

            Node_ptr lefttmost() const 
            { 
                Node_ptr i = _root;
                while (i->_left->_end_element != true) 
                    i = i->_left;
                return (i);
            }
            
        public:
            // allocation/deallocation

            explicit Rb_tree(const Compare& comp, const allocator_type& a)
            : _root(),_node_count(0), _comp(comp), _alloc(a)
            {
                _end_node = get_node();
                initialize(_end_node);
                _end_node->_color= black;
                _end_node->_end_element = true; //specifying type as leaf node
                _root = _end_node;
            }
            
            Rb_tree( Rb_tree const &x ) :_comp(x._comp), _alloc(x._alloc)                                
            {   
                _end_node = get_node();
                initialize(_end_node);
                _end_node->_color = black;
                _end_node->_end_element = true; //specifying type as leaf node
                _root = _end_node;
                if (x.size() != 0) 
                {
                    this->root() = copy(x._root, end());
                    _node_count = x._node_count;
                    _end_node->_left = rightmost();
                    _end_node->_right = lefttmost();
                }
            }

            Rb_tree& operator=(const Rb_tree &x)
            {
                if(this != &x)
                {
                    clear(); // Replacement allocator cannot free existing storage, we need to erase nodes first.
                    this->_comp = x._comp;
                    this->_alloc = x._alloc;
                    if (x.size() != 0) 
                    {
                        // this->insert(x.begin(), x.end());
                        this->root() = copy(x._root, end());
                        _node_count = x._node_count;
                        _end_node->_left = rightmost();
                        _end_node->_right = lefttmost();
                    }
                }
                return *this;
            }


            ~Rb_tree( void )                                                             
            {  
                clear();
                put_node(_end_node);
            };

            Node_allocator& get_Node_allocator()
            { return this->_node_alloc; }

            const Node_allocator& get_Node_allocator() const
            { return this->_node_alloc; }

            allocator_type get_allocator() const
            { return allocator_type(get_Node_allocator()); }

            ft::pair<iterator, bool> insert_unique(const value_type & v) //refer comment #2
            {
                Node_ptr n = create_node(v);
                Node_ptr x = this->_root;
                bool flag = true; //indicates if insert was a success
                Node_ptr y = find_parent_node(x, n, &flag);
                if (!flag)
                    return (ft::make_pair(iterator(y), flag));
                iterator i(n);
                n->_parent = y;
                //inserting the node
                if (y == end())
                    _root = n;
                else if (_comp(S_key(n),S_key(y)))
                    y->_left = n;
                else 
                    y->_right = n;
                if (n->_parent == end()) // if n is root node make it black
                {
                    n->_color = black;
                    _end_node->_left = rightmost();
                    _end_node->_right = lefttmost();
                    return(ft::make_pair(i, flag));
                }
                if (n->_parent->_parent == end()) //if granparent is nul i.e., parent is root do nothing
                {
                    _end_node->_left = rightmost();
                    _end_node->_right = lefttmost();
                    return(ft::make_pair(i, flag));
                }
                rebalance_insert(n);  // rebalance the tree
                _end_node->_left = rightmost();
                _end_node->_right = lefttmost();
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
                if (position != _end())
                {
                    Node_ptr y = (Node_ptr)position.base();
				    this->delete_helper(this->root(), y->_value.first);
                    _end_node->_left = rightmost();
                    _end_node->_right = lefttmost();
                }
            }

            void erase(const_iterator first, const_iterator last)
            {
                const_iterator tmp;
                while (first != last) 
                {   
                    tmp = first;
					++first;
					this->erase(tmp);
				}
            }

            //deletes a key value pair with key value x
            size_type erase(const key_type& x)
            {
                delete_helper(this->root(), x);
                _end_node->_left = rightmost();
                _end_node->_right = lefttmost();
                return (_node_count);
            }

            //erases the entire tree
            void erase(Node_ptr x)
            {
                // Erase without rebalancing.
                while (x->_end_element != true) // can use condition (x != end()), buts after swap creates problem
                {
                    erase(x->_right);
                    Node_ptr y = x->_left;
	                destroy_node(x);
	                x = y;
                }
                // _end_node->_left = _end_node;
                // _end_node->_right = _end_node;
            }

            void clear()
            {
                if (!this->empty())
                    this->erase(root());
                this->reset();
            }

            void reset()
            {
                this->_node_count = 0;
                this->_root = _end_node;
                _end_node->_left = _end_node;
                _end_node->_right = _end_node;
            }

            iterator find(const key_type& k)
            {
                Node_ptr n = root();
                while(n != end())
                {
                    if (this->_comp(k, S_key(n)))
                        n = n->_left;
                    else if (this->_comp(S_key(n), k))
                        n = n->_right;
                    else
                        return (iterator(n));
                }
                return (this->_end());
            }

            const_iterator find(const key_type& k) const
            {
                Const_Node_ptr n = root();
                while(n != end())
                {
                    if (this->_comp(k, S_key(n)))
                        n = n->_left;
                    else if (this->_comp(S_key(n), k))
                        n = n->_right;
                    else
                        return (const_iterator(n));
                }
                return (this->_end());
            }

            size_type count(const key_type& k) const
            {  return (this->find(k) == this->_end() ? 0 : 1);}

            /* Returns an iterator pointing to the first element in the container
             whose key is not considered to go before k (i.e., either it is equivalent or goes after).*/
            iterator lower_bound(const key_type& k)
            { 
                Node_ptr x = root();
                iterator y = _end();
                while(x->_end_element!= true)
                {
                    if (!this->_comp(S_key(x), k)) //if k < x
                    {
                        y = iterator(x);
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
                while(x->_end_element != true)
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
                while(x->_end_element != true)
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
                while(x->_end_element!= true)
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

            template <class T> 
            void _swap ( T& a, T& b )
            {
                T c(a); a=b; b=c;
            }
            
            void swap(Rb_tree& t)
            {
                if (this != &t)
                {
                    this->_swap(this->_root, t._root);
                    this->_swap(_end_node, t._end_node);
                    this->_swap(_node_count, t._node_count);
                    this->_swap(_comp, t._comp);
                    this->_swap(_alloc, t._alloc);
                    // this->_swap(this->_end_node->_left, t._end_node->_left);
                    
                    // this->_root->_parent = _end_node;
                    // this->_end_node->_left = this->rightmost();
                    // this->_end_node->_right = lefttmost();
                    // t._root->_parent = &t._end_node;
                    // t._end_node->_left = t.rightmost();
                    // t._end_node->_right = t.lefttmost();
                }
                // Node_ptr tmp_root = this->_root;
                // Node_ptr tmp_rightmost = this->rightmost();
                // size_type tmp_node_count = this->_node_count;
                // Compare tmp_comp = this->_comp;
                // allocator_type tmp_alloc = this->_alloc;

                // this->_root = t._root;
                // _end_node->_left = t.rightmost();
                // this->_node_count = t._node_count;
                // this->_comp = t._comp;
                // this->_alloc = t._alloc;
            
                // t._root = tmp_root;
                // t._end_node->_left = tmp_rightmost;
                // t._node_count = tmp_node_count;
                // t._comp = tmp_comp;
                // t._alloc = tmp_alloc;
                
                

                // t._end_node->_left = t.rightmost();
                // this->_end_node->_left = this->rightmost();

            }

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