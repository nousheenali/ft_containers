/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructors.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 19:41:37 by nali              #+#    #+#             */
/*   Updated: 2023/04/04 00:14:32 by nali             ###   ########.fr       */
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
        /*Default constructor*/
        
        NAMESPACE::map<char, int > map1;
        map1['a']=10;
        map1['b']=30;
        map1['c']=50;
        map1['d']=70;
        std::cout << "Map1\n";
        print_map(map1);

        std::cout << "Map2 - using Range constructor\n";
        NAMESPACE::map<char,int> map2 (map1.begin(),map1.end());
        print_map(map2);
        
        std::cout << "Map3 - using Copy Constructor\n";
        NAMESPACE::map<char,int> map3 (map2);
        print_map(map3);
        
        std::cout << "Map4 - using Copy assignment operator\n";
        NAMESPACE::map<char,int> map4; 
        map4 = map3;
        print_map(map4);              
    }
    {
        //map of maps
        NAMESPACE::map<std::string, NAMESPACE::map<int, int> > outer_map;
        NAMESPACE::map<int, int> inner_map[3];

        int k = 1;
        for ( int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++,k++)
                inner_map[i].insert(NAMESPACE::make_pair<int,int>(k, k * 100));

        outer_map.insert(NAMESPACE::make_pair("aaa", inner_map[0]));
        outer_map.insert(NAMESPACE::make_pair("bbb", inner_map[1]));
        outer_map.insert(NAMESPACE::make_pair("ccc", inner_map[2]));

        std::cout << "Map of Maps\n";
        NAMESPACE::map<std::string, NAMESPACE::map<int, int> >::iterator it = outer_map.begin(), ite = outer_map.end();
        for (; it != ite; ++it)
        {
            std::cout << "Key = " << it->first << std::endl;
            for (NAMESPACE::map<int, int>::iterator in = it->second.begin(); in != it->second.end(); in++) 
                std::cout << "Value->first = " << in->first << "  |  Value->second = " << in->second <<std::endl;
        }
    }
    
    std::cout <<std::endl;
    gettimeofday(&exec, NULL);
	double end = 1.0e6 * exec.tv_sec + exec.tv_usec;
	std::cout << std::fixed << std::setprecision(3) << (end - start) / 1000 << " ms" << std::endl;
	return 0;
}