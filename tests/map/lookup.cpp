/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lookup.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 19:41:37 by nali              #+#    #+#             */
/*   Updated: 2023/04/04 12:02:01 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/containers.hpp"
#include "../common.hpp"

template <typename T, typename T1>
void ft_count(T &mp, T1 key)
{
    if (mp.count(key) == 0)
        std::cout << "The element '" << key <<"' not present in map\n";
    else
        std::cout << "The element '" << key <<"' present in map\n";
}

template <typename T, typename T1>
void ft_find(T &mp, T1 key)
{
    typename T::iterator it;
    it = mp.find(key);
    if (it != mp.end())
        std::cout << "The element '" << key <<"' present in map\n";
    else
        std::cout << "The element '" << key <<"' not present in map\n";
}

template <typename T, typename T1>
void	ft_bound(T &mp, T1 key)
{
	NAMESPACE::pair<typename T::iterator ,typename T::iterator > ret;
    ret = mp.equal_range(key);

    std::cout << "The bounds for the element '" << key << "' are:\n"; 
    if(ret.first == mp.end() && ret.second == mp.end())
        std::cout << "The element '" << key <<"' not present in map\n";
    else
    {   
        if(ret.first != mp.end()){
        std::cout << "lower bound points to: ";
        std::cout << "key: " << ret.first->first << " - value : " << ret.first->second << '\n';}
        if(ret.second != mp.end()){
        std::cout << "upper bound points to: ";
        std::cout << "key: " << ret.second->first << " - value : " << ret.second->second << '\n';}
    }
    std::cout << std::endl;
}

int main(void)
{
    timeval exec;
	gettimeofday(&exec, NULL);
	double start = 1.0e6 * exec.tv_sec + exec.tv_usec;
    
    {
        //empty
        NAMESPACE::map<char,int> map1;
        for (int i = 0; i <5 ; i++)
            map1['a' + i] = (i + 1) * 100;
        print_map(map1);

        std::cout << "Using map.count()\n";
        ft_count(map1, 'a');
        ft_count(map1, 'f');

        std::cout << "\nUsing map.find()\n";
        ft_count(map1, 'b');
        ft_count(map1, 'g');


        std::cout << "\nUsing map.equal_range()\n";
        ft_bound(map1, 'c');
        ft_bound(map1, 'e');
        ft_bound(map1, 'h');        
    }
    
    std::cout <<std::endl;
    gettimeofday(&exec, NULL);
	double end = 1.0e6 * exec.tv_sec + exec.tv_usec;
	std::cout << std::fixed << std::setprecision(3) << (end - start) / 1000 << " ms" << std::endl;
	return 0;
}