/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterators_invalidation.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 17:46:33 by nali              #+#    #+#             */
/*   Updated: 2023/04/06 23:43:25 by nali             ###   ########.fr       */
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
        std::cout << "Begin iterator invalidation due to resize\n";
        NAMESPACE::vector<int> vec(1,2);
        NAMESPACE::vector<int>::iterator it, it2;
        
        it= vec.begin();
        vec.resize(10);
        it2= vec.begin();
        if (it == it2)
            std::cout << "Iterators equal\n";
        else
            std::cout << "Iterators not equal\n";
    } 
    {
        std::cout << "\nEnd iterator invalidation due to pop_back\n";
        NAMESPACE::vector<int> vec(4,2);
        NAMESPACE::vector<int>::iterator ite, ite2;
        
        ite = vec.end();
        vec.pop_back();
        ite2= vec.end();
        if (ite == ite2)
            std::cout << "Iterators equal\n";
        else
            std::cout << "Iterators not equal\n";
  
    } 
    {
        std::cout << "\nIterator invalidation due to = operator\n";
        NAMESPACE::vector<int> vec(4,2);
        NAMESPACE::vector<int>::iterator it, it2;
        
        it = vec.begin();
        NAMESPACE::vector<int> vec2 = vec;
        it2 = vec2.begin();
        if (it == it2)
            std::cout << "Iterators equal\n";
        else
            std::cout << "Iterators not equal\n";
  
    } 
    std::cout <<std::endl;
    gettimeofday(&exec, NULL);
	double end = 1.0e6 * exec.tv_sec + exec.tv_usec;
	std::cout << std::fixed << std::setprecision(3) << (end - start) / 1000 << " ms" << std::endl;
	return 0;
}