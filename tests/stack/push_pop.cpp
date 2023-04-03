/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_pop.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 17:46:33 by nali              #+#    #+#             */
/*   Updated: 2023/04/03 00:00:40 by nali             ###   ########.fr       */
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
        std::cout <<"Inputting values 1 to 9 into stack" <<std::endl;
        NAMESPACE::stack<int> stck1;
        for (int i = 0; i < 10; i++)
            stck1.push(i);

        std::cout <<"Top value in the stack: " << stck1.top() <<std::endl;
        
        stck1.pop();

        std::cout <<"Top value in the stack after a pop: " << stck1.top() <<std::endl;
    }
    std::cout <<"\n--------------------------------------\n";
    {
        std::cout <<"Inputting stringsinto stack" <<std::endl;
        NAMESPACE::stack<std::string> stck1;
        stck1.push("abcd");
        stck1.push("efgh");
        stck1.push("ijkl");
        stck1.push("mnop");

        std::cout <<"Top value in the stack: " << stck1.top() <<std::endl;
        
        stck1.pop();

        std::cout <<"Top value in the stack after a pop: " << stck1.top() <<std::endl;
    }
    std::cout <<std::endl;
    gettimeofday(&exec, NULL);
	double end = 1.0e6 * exec.tv_sec + exec.tv_usec;
	std::cout << std::fixed << std::setprecision(3) << (end - start) / 1000 << " ms" << std::endl;
	return 0;
}