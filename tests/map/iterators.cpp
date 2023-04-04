/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterators.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 19:41:37 by nali              #+#    #+#             */
/*   Updated: 2023/04/04 09:53:22 by nali             ###   ########.fr       */
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
        NAMESPACE::map<char,int> map1;
        for (int i = 0; i <5 ; i++)
            map1['a' + i] = (i + 1) * 100;
        

        std::cout << "Printing contents of Map1 using iterators\n";
        NAMESPACE::map<char,int>::iterator it = map1.begin(), ite = map1.end();
        for (; it != ite; ++it)
            std::cout << "key: " << it->first << " - value: " << it->second << std::endl;

        std::cout << "---------------------------------------\n\n";

        it = map1.begin();
        std::cout << "Map2 constructed using Range of iterators\n";
        NAMESPACE::map<char,int> map2 (++it, --ite);
        print_map(map2);

        
        std::cout << "Printing contents of Map1 in reverse using reverse iterators\n";
         NAMESPACE::map<char,int>::reverse_iterator rit = map1.rbegin();
        for (; rit != map1.rend(); ++rit)
            std::cout << "key: " << rit->first << " - value: " << rit->second << std::endl;
 
    }
    
    std::cout <<std::endl;
    gettimeofday(&exec, NULL);
	double end = 1.0e6 * exec.tv_sec + exec.tv_usec;
	std::cout << std::fixed << std::setprecision(3) << (end - start) / 1000 << " ms" << std::endl;
	return 0;
}