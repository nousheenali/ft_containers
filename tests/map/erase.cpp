/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   erase.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 19:41:37 by nali              #+#    #+#             */
/*   Updated: 2023/04/04 12:32:44 by nali             ###   ########.fr       */
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
        //clear()
        NAMESPACE::map<char,int> mp;
        for (int i = 0; i < 5; i++)
            mp.insert (NAMESPACE::pair<char,int>('a' + i, (i + 1) * 100) );
        std::cout << "Map contents are:" <<std::endl;
        print_map(mp);

        std::cout << "Map contents after clearing" <<std::endl;
        mp.clear();
        print_map(mp);
    }
    {
        //erase()
        NAMESPACE::map<char,int> mp;
        NAMESPACE::map<char,int>::iterator it, ite;
        
        for (int i = 0; i < 6; i++)
            mp.insert (NAMESPACE::pair<char,int>('a' + i, (i + 1) * 100) );
        std::cout << "Map contents are:" <<std::endl;
        print_map(mp);

        std::cout << "Erase element 'b' using iterator" <<std::endl;
        it=mp.find('b');
        mp.erase (it); 
        print_map(mp);

        std::cout << "Erase element 'd' using key value" <<std::endl;
        mp.erase ('d'); 
        print_map(mp);

        std::cout << "Erase elements using range of iterators" <<std::endl;
        it = mp.begin(), ite = mp.end();
        mp.erase (it, ite); 
        print_map(mp);
    }
    
    std::cout <<std::endl;
    gettimeofday(&exec, NULL);
	double end = 1.0e6 * exec.tv_sec + exec.tv_usec;
	std::cout << std::fixed << std::setprecision(3) << (end - start) / 1000 << " ms" << std::endl;
	return 0;
}