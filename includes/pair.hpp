/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 10:53:53 by nali              #+#    #+#             */
/*   Updated: 2023/02/28 14:48:39 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PAIR_HPP
#define PAIR_HPP

/*  Pair is used to combine together two values that may be of different data types. 
    Pair provides a way to store two heterogeneous objects as a single unit. */
namespace ft
{
    template<class T1, class T2> 
    struct pair
    {
        typedef T1 first_type;    ///< The type of the `first` member
        typedef T2 second_type;   ///< The type of the `second` member

        T1 first;                 ///< The first member
        T2 second;  

        pair(): first(), second() { } //default const
        
        pair( const T1& x, const T2& y ): first(x), second(y) { } //value init

        template< class U1, class U2 >
        pair( const pair<U1, U2>& p ): first(p.first), second(p.second) { } //copy const

        pair& operator=( const pair& other )
        {
            first = other.first;
            second = other.second;
            return *this;
        }
    };
    template <class T1, class T2>  
    bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
    { return lhs.first == rhs.first && lhs.second == rhs.second; }

    template <class T1, class T2>  
    bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
    { return !(lhs == rhs); }

    // compares the first elements and only if they are equivalent, compares the second elements.
    template <class T1, class T2>  
    bool operator<  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
    { return lhs.first<rhs.first || (!(rhs.first<lhs.first) && lhs.second<rhs.second); }

    template <class T1, class T2>  
    bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
    { return !(rhs < lhs);}
    
    template <class T1, class T2>  
    bool operator>  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
    { return (rhs < lhs);}

    template <class T1, class T2>  
    bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
    { return !(lhs < rhs);}

    template <class T1, class T2>  
    pair<T1,T2> make_pair (T1 x, T2 y)
    {
        return ( pair<T1,T2>(x,y) );
    }

    template<typename Arg1, typename Arg2, typename Result>
	struct binary_function {
		typedef Arg1	frist_argument_type;
		typedef Arg2	second_argument_type;
		typedef Result	result_type;
	};
	
	template<typename T>
	struct less: binary_function<T,T,bool> {
		bool operator()(const T& x, const T& y) const {
			return (x < y);
		}
	};
}
#endif