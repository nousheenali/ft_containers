/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   erase.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 12:40:43 by nali              #+#    #+#             */
/*   Updated: 2023/04/03 14:57:31 by nali             ###   ########.fr       */
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
        //clear
	    NAMESPACE::vector<int> vec(5, 20);
        
        std::cout<< "Elements in vec\n";
        print_vector(vec);
        
        std::cout<< "Elements in vec after clearing\n";
        vec.clear();
        print_vector(vec);
    }
    
    {
        //erase
        NAMESPACE::vector<int> vec(10);   // 6 zero-initialized ints
        for (size_t i = 0; i < vec.size(); i++)
            vec.at(i) = (i + 1) * 2;
            
        std::cout<< "Elements in vec\n";
        print_vector(vec);

        NAMESPACE::vector<int>::iterator it  = vec.begin();
        std::cout<< "Erase element at position 2 in vec\n";
        vec.erase(++(++it));
        print_vector(vec);
        
        NAMESPACE::vector<int>::iterator ite  = vec.end();
        it  = vec.begin();
        std::cout<< "Erase few elements in vec\n";
        vec.erase(++(++it), --(--ite));
        print_vector(vec);

        std::cout<< "Erase all elements in vec\n";
        it  = vec.begin(); ite  = vec.end();
        vec.erase(it, ite);
        print_vector(vec);
 
    }

    std::cout <<std::endl;
    gettimeofday(&exec, NULL);
	double end = 1.0e6 * exec.tv_sec + exec.tv_usec;
	std::cout << std::fixed << std::setprecision(3) << (end - start) / 1000 << " ms" << std::endl;
	return 0;
}