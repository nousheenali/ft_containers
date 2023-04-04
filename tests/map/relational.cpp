/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   relational.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 19:41:37 by nali              #+#    #+#             */
/*   Updated: 2023/04/04 13:10:47 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/containers.hpp"
#include "../common.hpp"

template <class T>
void	ft_compare(const T &lhs, const T &rhs)
{
    std::cout << "Contents of map1\n";
    print_map(lhs);
    std::cout << "Contents of map2\n";
    print_map(rhs);
    if (lhs==rhs) std::cout << "map1 and map2 are equal\n";
    if (lhs!=rhs) std::cout << "map1 and map2 are not equal\n";
    if (lhs< rhs) std::cout << "map1 is less than map2\n";
    if (lhs> rhs) std::cout << "map1 is greater than map2\n";
    if (lhs<=rhs) std::cout << "map1 is less than or equal to map2\n";
    if (lhs>=rhs) std::cout << "map1 is greater than or equal to map2\n";

    std::cout << "\n---------------------------------------\n";
}

int main(void)
{
    timeval exec;
	gettimeofday(&exec, NULL);
	double start = 1.0e6 * exec.tv_sec + exec.tv_usec;
    
    {
        NAMESPACE::map<char,int> mp1;
        for (int i = 0; i < 5; i++)
            mp1.insert (NAMESPACE::pair<char,int>('a' + i, (i + 1) * 100) );
            
        NAMESPACE::map<char,int> mp2(mp1);
        ft_compare(mp1, mp2);

        std::cout << "After dropping element 'c' from map1........\n";
        std::cout << "---------------------------------------\n";
        mp1.erase('c');
        ft_compare(mp1, mp2);
        
        
    }
    
    std::cout <<std::endl;
    gettimeofday(&exec, NULL);
	double end = 1.0e6 * exec.tv_sec + exec.tv_usec;
	std::cout << std::fixed << std::setprecision(3) << (end - start) / 1000 << " ms" << std::endl;
	return 0;
}