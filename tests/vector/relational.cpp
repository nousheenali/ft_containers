/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   relational.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 12:40:43 by nali              #+#    #+#             */
/*   Updated: 2023/04/04 13:14:52 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/containers.hpp"
#include "../common.hpp"

template <class T>
void	ft_compare(const T &lhs, const T &rhs)
{
    std::cout << "Contents of vec1\n";
    print_vector(lhs);
    std::cout << "Contents of vec2\n";
    print_vector(rhs);
    if (lhs==rhs) std::cout << "vec1 and vec2 are equal\n";
    if (lhs!=rhs) std::cout << "vec1 and vec2 are not equal\n";
    if (lhs< rhs) std::cout << "vec1 is less than vec2\n";
    if (lhs> rhs) std::cout << "vec1 is greater than vec2\n";
    if (lhs<=rhs) std::cout << "vec1 is less than or equal to vec2\n";
    if (lhs>=rhs) std::cout << "vec1 is greater than or equal to vec2\n";

    std::cout << "---------------------------------------\n";
}

int main(void)
{
    timeval exec;
	gettimeofday(&exec, NULL);
	double start = 1.0e6 * exec.tv_sec + exec.tv_usec;
    
    {
        NAMESPACE::vector<int> vec1(3,100);   // three ints with a value of 100
        NAMESPACE::vector<int> vec2(vec1); 
        
        ft_compare(vec1, vec2);
        std::cout << "After dropping last element from vec1........\n";
        std::cout << "---------------------------------------\n";
        vec1.pop_back();
        ft_compare(vec1, vec2);
    }
    
    std::cout <<std::endl;
    gettimeofday(&exec, NULL);
	double end = 1.0e6 * exec.tv_sec + exec.tv_usec;
	std::cout << std::fixed << std::setprecision(3) << (end - start) / 1000 << " ms" << std::endl;
	return 0;
}