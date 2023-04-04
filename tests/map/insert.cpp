/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 19:41:37 by nali              #+#    #+#             */
/*   Updated: 2023/04/04 12:22:15 by nali             ###   ########.fr       */
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
        NAMESPACE::map<char,int> mp;
        NAMESPACE::map<char,int>::iterator it;

        std::cout << "Single insert of map\n";  
        for (int i = 0; i < 5; i++)
            mp.insert (NAMESPACE::pair<char,int>('a' + i, (i + 1) * 100) );
        print_map(mp);

        it = mp.begin();
        std::cout << "Position insert of map\n";  
        mp.insert (it, NAMESPACE::pair<char,int>('z', 600) );
        print_map(mp);

        std::cout << "Range Insert of map\n"; 
        NAMESPACE::map<char,int> mp2;
        mp2.insert(mp.begin(),mp.find('d'));
        print_map(mp2);
        
    }
    
    std::cout <<std::endl;
    gettimeofday(&exec, NULL);
	double end = 1.0e6 * exec.tv_sec + exec.tv_usec;
	std::cout << std::fixed << std::setprecision(3) << (end - start) / 1000 << " ms" << std::endl;
	return 0;
}