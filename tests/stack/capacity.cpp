/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   capacity.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 11:36:07 by nali              #+#    #+#             */
/*   Updated: 2023/04/02 14:54:29 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/containers.hpp"

int main(void)
{
    timeval exec_time;
	gettimeofday(&exec_time, NULL);
	double start = 1.0e6 * exec_time.tv_sec + exec_time.tv_usec;
    
    // std::cout << "My variable is: " << VAR << std::endl;
    NAMESPACE::stack<int> stck;
    std::cout << "Stack empty?: "<< stck.empty()<<std::endl;
    std::cout << "Pushing a values 3, 11 , 12 to stack..."<<std::endl;
    stck.push(3);
    stck.push(11);
    stck.push(12);
    std::cout << "Stack empty?: "<< stck.empty()<<std::endl;
    std::cout << "Top value of stack: "<< stck.top()<<std::endl;
    stck.pop();
    std::cout << "Top value of stack: "<< stck.top()<<std::endl;
    std::cout << "Stack empty?: "<< stck.empty()<<std::endl;
    
    gettimeofday(&exec_time, NULL);
	double end = 1.0e6 * exec_time.tv_sec + exec_time.tv_usec;
	std::cout << std::fixed << std::setprecision(3) << (end - start) / 1000 << " ms" << std::endl;
	return 0;
}