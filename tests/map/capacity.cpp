/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   capacity.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 19:41:37 by nali              #+#    #+#             */
/*   Updated: 2023/04/04 10:06:53 by nali             ###   ########.fr       */
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
        //empty
        NAMESPACE::map<char,int> map1;
        std::cout<< "map1 empty?: " << map1.empty() << std::endl;
        std::cout<< "\nInserting values into map1......." << std::endl;
        for (int i = 0; i <5 ; i++)
            map1['a' + i] = (i + 1) * 100;
        std::cout<< "\nmap1 empty?: " << map1.empty() << std::endl;
            
        //size
        std::cout << "\nmap size  is " << map1.size() << '\n';

        //maxsize
        std::cout << "\nmap max size is " << map1.max_size() << '\n';
        
        std::cout<< "\ncontents: " << std::endl;
        while (!map1.empty())
        {
            std::cout << "key: "  << map1.begin()->first << " - value: " << map1.begin()->second << '\n';
            map1.erase(map1.begin());
        }   
        std::cout<< "\n------------------------\n";
    }
    
    std::cout <<std::endl;
    gettimeofday(&exec, NULL);
	double end = 1.0e6 * exec.tv_sec + exec.tv_usec;
	std::cout << std::fixed << std::setprecision(3) << (end - start) / 1000 << " ms" << std::endl;
	return 0;
}