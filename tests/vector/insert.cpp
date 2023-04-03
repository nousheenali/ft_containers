/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 12:40:43 by nali              #+#    #+#             */
/*   Updated: 2023/04/03 12:58:45 by nali             ###   ########.fr       */
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
	    NAMESPACE::vector<int> vec(5, 20);
        NAMESPACE::vector<int> vec2(3, 10);
        NAMESPACE::vector<int> vec3(4, 5);
        NAMESPACE::vector<int>::iterator it, ite, it2;
        
        std::cout<< "Contents of vec\n";
        print_vector(vec);
        it = vec.begin();
        std::cout<< "Inserting an element 25 at position 3\n";
	    vec.insert(++(++it), 25);
        print_vector(vec);

        std::cout<< "Inserting 5 elements of value 10 at position 3\n";
        it = vec.begin();
	    vec.insert(++it, 5, 10);
        print_vector(vec);

        it = vec3.begin();
        ite = vec3.end();
        it2 = vec2.begin();
        std::cout<< "Elements in vec2\n";
        print_vector(vec2);
        std::cout<< "Elements in vec3\n";
        print_vector(vec3);
        
        vec2.insert(++it2, it, ite);
        std::cout<< "Elements in vec2 after insertion of vec3 into vec2 \n";
        print_vector(vec2);
    }

    std::cout <<std::endl;
    gettimeofday(&exec, NULL);
	double end = 1.0e6 * exec.tv_sec + exec.tv_usec;
	std::cout << std::fixed << std::setprecision(3) << (end - start) / 1000 << " ms" << std::endl;
	return 0;
}