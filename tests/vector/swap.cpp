/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 12:40:43 by nali              #+#    #+#             */
/*   Updated: 2023/04/06 23:11:34 by nali             ###   ########.fr       */
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
        NAMESPACE::vector<int> vec1(3,100);   // three ints with a value of 100
        NAMESPACE::vector<int> vec2(5,200);   // five ints with a value of 200
        NAMESPACE::vector<int>::iterator it1 = vec1.begin(), it2 = vec2.begin();
        
        std::cout<< "Elements in vec1\n";
        print_vector(vec1);
        std::cout<< "Elements in vec2\n";
        print_vector(vec2);
        
        vec1.swap(vec2);

        std::cout<< "Elements in vec1\n";
        print_vector(vec1);
        std::cout<< "Elements in vec2\n";
        print_vector(vec2);

        std::cout << "Checking Iterator validity:" << std::endl;
        std::cout << (it1 == vec2.begin()) << std::endl;
        std::cout << (it2 == vec1.begin()) << std::endl;

    }
    
    std::cout <<std::endl;
    gettimeofday(&exec, NULL);
	double end = 1.0e6 * exec.tv_sec + exec.tv_usec;
	std::cout << std::fixed << std::setprecision(3) << (end - start) / 1000 << " ms" << std::endl;
	return 0;
}