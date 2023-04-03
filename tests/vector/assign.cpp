/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 17:46:33 by nali              #+#    #+#             */
/*   Updated: 2023/04/02 23:41:57 by nali             ###   ########.fr       */
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
        vec1.assign(7, 100);
        std::cout << "vec1 created using assign fill version\n";
        print_vector(vec1);

        NAMESPACE::vector<int> vec2(7);
        NAMESPACE::vector<int>::iterator it = vec2.begin(), ite = vec2.end();
        for (int i = 0; it != ite; ++it,++i)
            *it = rand()%10;
        std::cout << "contents of vec2\n";
        print_vector(vec2);
       
        it = vec2.begin(), ite = vec2.end();
        NAMESPACE::vector<int> vec3;
        std::cout << "vec3 created using assign range version\n";
        vec3.assign(++it, --ite);
        print_vector(vec3);

        vec2.assign(4,200);
        std::cout << "vec2 re-assigned using assign fill version\n";
        print_vector(vec2);
    }

    std::cout <<std::endl;
    gettimeofday(&exec, NULL);
	double end = 1.0e6 * exec.tv_sec + exec.tv_usec;
	std::cout << std::fixed << std::setprecision(3) << (end - start) / 1000 << " ms" << std::endl;
	return 0;
}