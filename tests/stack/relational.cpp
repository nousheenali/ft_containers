/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   relational.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 20:10:38 by nali              #+#    #+#             */
/*   Updated: 2023/04/02 20:18:28 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/containers.hpp"

int main(void)
{
    timeval exec;
	gettimeofday(&exec, NULL);
	double start = 1.0e6 * exec.tv_sec + exec.tv_usec;
    
    {
        /*Default constructor*/
        NAMESPACE::stack<int> stck1;
        for (int i = 0; i < 10; i++)
            stck1.push(i);
        std::cout <<"stck2 created from stck1 through copy constructor\n";
        NAMESPACE::stack<int> stck2(stck1);
        std::cout <<"stck3 created from stck1 through copy assignment\n";
        NAMESPACE::stack<int> stck3 = stck1;

        std::cout <<"stck1 == stck2 : " << (stck1 == stck2) <<std::endl;
        stck1.pop();
        std::cout <<"Check after popping an element of stck1\n";
        std::cout <<"stck1 == stck2 : " << (stck1 == stck2) <<std::endl;
        std::cout <<"stck1 != stck2 : " << (stck1 != stck2) <<std::endl;
        
        
    }

    std::cout <<std::endl;
    gettimeofday(&exec, NULL);
	double end = 1.0e6 * exec.tv_sec + exec.tv_usec;
	std::cout << std::fixed << std::setprecision(3) << (end - start) / 1000 << " ms" << std::endl;
	return 0;
}