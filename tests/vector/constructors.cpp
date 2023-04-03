/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructors.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 17:46:33 by nali              #+#    #+#             */
/*   Updated: 2023/04/02 23:43:31 by nali             ###   ########.fr       */
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
            NAMESPACE::vector<int> vec1;
            std::cout << "Default empty constructor\n";
            print_vector(vec1);
       
            NAMESPACE::vector<int> vec2(5, 13);
            std::cout << "vec2 created using fill constructor\n";
            print_vector(vec2);
        }

        {
            NAMESPACE::vector<int> vec1(7);
            NAMESPACE::vector<int>::iterator it = vec1.begin(), ite = vec1.end();
            for (int i = 0; it != ite; ++it,++i)
                *it = rand()%10;
            std::cout << "elements in vec1\n";
            print_vector(vec1);

            NAMESPACE::vector<int> vec2(vec1);
            std::cout << "vec2 created using copy constructor\n";
            print_vector(vec2);
            
            std::cout << "vec3 created using range constructor\n";
            NAMESPACE::vector<int> vec3(++(++vec1.begin()), (--vec1.end())); 
            print_vector(vec3);
        }

        {
            NAMESPACE::vector<std::string> vec1(5);
            vec1[0] ="hello";
            vec1[1] ="there";
            vec1[2] ="how";
            vec1[3] ="are";
            vec1[4] ="you?";
            std::cout << "elements in vec1\n";
            print_vector(vec1);

            NAMESPACE::vector<std::string> vec2(vec1);
            std::cout << "vec2 created using copy constructor\n";
            print_vector(vec2);
            
            std::cout << "vec3 created using range constructor\n";
            NAMESPACE::vector<std::string> vec3(++(++vec1.begin()), (vec1.end())); 
            print_vector(vec3);

            std::cout << "vec4 created using copy assignment\n";
            NAMESPACE::vector<std::string> vec4 = vec3; 
            print_vector(vec4);
        }
    }

   
    std::cout <<std::endl;
    gettimeofday(&exec, NULL);
	double end = 1.0e6 * exec.tv_sec + exec.tv_usec;
	std::cout << std::fixed << std::setprecision(3) << (end - start) / 1000 << " ms" << std::endl;
	return 0;
}