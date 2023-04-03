/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element_access.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 17:46:33 by nali              #+#    #+#             */
/*   Updated: 2023/04/03 10:43:54 by nali             ###   ########.fr       */
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
            //at
            NAMESPACE::vector<int> vec (6);   // 6 zero-initialized ints
            for (size_t i = 0; i < vec.size(); i++)
                vec.at(i) = rand() % 10;
            
            std::cout << "vec contains:\n";
            print_vector(vec);
        }
        {
            //operator[]
            NAMESPACE::vector<int> vec (10);   // 10 zero-initialized elements
            NAMESPACE::vector<int>::size_type sz = vec.size();
            
            for (size_t i = 0; i < sz; i++) 
                vec[i] = i;
            std::cout << "vec contains:\n";
            print_vector(vec);

            // reverse vector using operator[]:
            for (size_t i=0; i<sz/2; i++)
            {
                int temp;
                temp = vec[sz-1-i];
                vec[sz-1-i] = vec[i];
                vec[i] = temp;
            }

            std::cout << "\nvec after reversing contains:\n";
            print_vector(vec);
        }
        {
            //back and front
            NAMESPACE::vector<int> vec; 
            std::cout << "pushing values 12, 78, 16, 22 into the vector\n";
            vec.push_back(12);
            vec.push_back(78);
            vec.push_back(16);
            vec.push_back(55);
            vec.push_back(22);

            std::cout << "front value in vec " << vec.front() << '\n';
            std::cout << "back value in vec " << vec.back() << '\n';
        }
    }

   
    std::cout <<std::endl;
    gettimeofday(&exec, NULL);
	double end = 1.0e6 * exec.tv_sec + exec.tv_usec;
	std::cout << std::fixed << std::setprecision(3) << (end - start) / 1000 << " ms" << std::endl;
	return 0;
}