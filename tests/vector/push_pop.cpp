/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_pop.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 12:40:43 by nali              #+#    #+#             */
/*   Updated: 2023/04/03 15:15:31 by nali             ###   ########.fr       */
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
        NAMESPACE::vector<int> vec;
        std::cout << "Pushing values 100, 200 and 300 into vec\n";
        vec.push_back (100);
        vec.push_back (200);
        vec.push_back (300);

        std::cout << "Elements in vec\n";
        print_vector(vec);
        
        std::cout << "Pop elements of vec and print\n";
        while (!vec.empty())
        {
            std::cout << "- " << vec.back() << std::endl;
            vec.pop_back();
        }
        std::cout << "----------------------------------\n";

        std::cout << "Elements in vec\n";
        print_vector(vec);
    }
    
    std::cout <<std::endl;
    gettimeofday(&exec, NULL);
	double end = 1.0e6 * exec.tv_sec + exec.tv_usec;
	std::cout << std::fixed << std::setprecision(3) << (end - start) / 1000 << " ms" << std::endl;
	return 0;
}