/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 19:41:37 by nali              #+#    #+#             */
/*   Updated: 2023/04/06 13:20:08 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/containers.hpp"
#include "../common.hpp"

int main(void)
{
    timeval exec;
	gettimeofday(&exec, NULL);
	double start = 1.0e6 * exec.tv_sec + exec.tv_usec;
    
    {
        NAMESPACE::map<char,int> mp1,mp2;
        mp1['x']=100;
        mp1['y']=200;

        mp2['a']=11;
        mp2['b']=22;
        mp2['c']=33;
        
        NAMESPACE::map<char,int>::iterator it1 = mp1.begin(), it2 =mp2.begin();

        std::cout << "Contents of map1:\n";
        print_map(mp1);
        std::cout << "Contents of map2:\n";
        print_map(mp2);
        
        mp1.swap(mp2);

        std::cout << "After swapping.....\n";
        std::cout << "Contents of map1:\n";
        print_map(mp1);
        std::cout << "Contents of map2:\n";
        print_map(mp2);

        std::cout << "Checking Iterator validity:" << std::endl;
        std::cout << (it1 == mp2.begin()) << std::endl;
        std::cout << (it2 == mp1.begin()) << std::endl;
        
    }
    
    std::cout <<std::endl;
    gettimeofday(&exec, NULL);
	double end = 1.0e6 * exec.tv_sec + exec.tv_usec;
	std::cout << std::fixed << std::setprecision(3) << (end - start) / 1000 << " ms" << std::endl;
	return 0;
}