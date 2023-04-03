/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructors.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 17:46:33 by nali              #+#    #+#             */
/*   Updated: 2023/04/03 00:00:34 by nali             ###   ########.fr       */
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
        /*Default constructor*/
        NAMESPACE::stack<int> stck1;
        for (int i = 0; i < 10; i++)
            stck1.push(i);
        /*copy constructor*/
        NAMESPACE::stack<int> stck2(stck1);
        /*copy assignment operator*/
        NAMESPACE::stack<int> stck3 = stck1;

        std::cout <<"Contents of stck1\n";
        print_stack(stck1);
        std::cout <<"Contents of stck2\n";
        print_stack(stck2);
        std::cout <<"Contents of stck3\n";
        print_stack(stck3);
    }

    {
        NAMESPACE::stack<std::string> stck1;
        stck1.push( "aaaa" );
        stck1.push( "bbbb" );
        stck1.push( "cccc" );
        stck1.push( "dddd" );

        /*copy constructor*/
        NAMESPACE::stack<std::string> stck2(stck1);
        /*copy assignment operator*/
        NAMESPACE::stack<std::string> stck3 = stck1;

        std::cout <<"Contents of stck1\n";
        print_stack(stck1);
        std::cout <<"Contents of stck2\n";
        print_stack(stck2);
        std::cout <<"Contents of stck3\n";
        print_stack(stck3);
    
    }
    std::cout <<std::endl;
    gettimeofday(&exec, NULL);
	double end = 1.0e6 * exec.tv_sec + exec.tv_usec;
	std::cout << std::fixed << std::setprecision(3) << (end - start) / 1000 << " ms" << std::endl;
	return 0;
}