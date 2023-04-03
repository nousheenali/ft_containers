/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   capacity.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 17:46:33 by nali              #+#    #+#             */
/*   Updated: 2023/04/03 12:40:30 by nali             ###   ########.fr       */
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
        NAMESPACE::vector<int> vec1;
        std::cout<< "vec1 empty?: " << vec1.empty() << std::endl;
        std::cout<< "Inserting value into vec1." << std::endl;
        vec1.push_back(42);
        std::cout<< "vec1 empty?: " << vec1.empty() << std::endl;
        std::cout<< "\n------------------------\n";
    }
    {
        NAMESPACE::vector<int> vec;

        // set some content in the vector:
        for (int i=0; i<100; i++) 
            vec.push_back(i);

        std::cout << "size: " <<vec.size() << "\n";
        std::cout << "capacity: " << vec.capacity() << "\n";
        std::cout << "max_size: " << vec.max_size() << "\n";
        std::cout<< "\n------------------------\n";
    }
    {
        std::cout<< "creating a vec with size 4 and values 20\n";
	    NAMESPACE::vector<int> vec(4, 20);
        print_vector(vec);
    
        std::cout<< "resizing vec to size 6\n";
	    vec.resize(6, 42);
        print_vector(vec);

        std::cout<< "resizing vec to size 3\n";
        vec.resize(3);
        print_vector(vec);

        std::cout<< "reserving a capacity of 5\n";
        vec.reserve(5);
        std::cout << "capacity: " << vec.capacity() << "\n";
        
        std::cout<< "reserving a capacity of 10\n";
        vec.reserve(10);
        std::cout << "capacity: " << vec.capacity() << "\n";
    }

    std::cout <<std::endl;
    gettimeofday(&exec, NULL);
	double end = 1.0e6 * exec.tv_sec + exec.tv_usec;
	std::cout << std::fixed << std::setprecision(3) << (end - start) / 1000 << " ms" << std::endl;
	return 0;
}