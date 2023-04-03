/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterators.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 17:46:33 by nali              #+#    #+#             */
/*   Updated: 2023/04/03 11:17:25 by nali             ###   ########.fr       */
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
        {
            //begin and end
            NAMESPACE::vector<int> vec(5);
            for (size_t i = 0; i < vec.size(); i++)
                vec.at(i) = i;
            
            NAMESPACE::vector<int>::iterator it = vec.begin(), ite = vec.end();
            std::cout << "vec contains:\n";
            for ( ; it != ite; ++it)
                std::cout << ' ' << *it;
            std::cout << "\n-------------------------\n";
       
            
            NAMESPACE::vector<int> vec2(vec);
            std::cout << "vec2 contains:\n";
            print_vector(vec2);
            
            NAMESPACE::vector<int>::iterator it2 = vec2.begin();
            vec2.insert(++(++it2), 3, 10);
            std::cout << "vec2 after insertion at position 2 contains:\n";
            print_vector(vec2);
        }
        {
            //reverse iterators rend() rbegin()
            NAMESPACE::vector<int> vec3(5);  // 5 default-constructed ints
            NAMESPACE::vector<int>::reverse_iterator rit = vec3.rbegin();
            for (int i = 0; rit != vec3.rend(); ++rit)
                *rit = ++i;
            std::cout << "vec3 after insertion using reverse iterator:\n";
            print_vector(vec3);
        }
        
    }
    std::cout <<std::endl;
    gettimeofday(&exec, NULL);
	double end = 1.0e6 * exec.tv_sec + exec.tv_usec;
	std::cout << std::fixed << std::setprecision(3) << (end - start) / 1000 << " ms" << std::endl;
	return 0;
}