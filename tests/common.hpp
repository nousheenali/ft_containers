/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 23:38:06 by nali              #+#    #+#             */
/*   Updated: 2023/04/02 23:45:22 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_HPP
#define COMMON_HPP

template<typename T>
void print_vector(T &vec)
{
    std::cout << "size: " << vec.size() << std::endl;
	std::cout << "Elements:" << std::endl;
	for (size_t i = 0; i < vec.size(); i++) 
        std::cout << "vector[" << i << "] = " << vec[i] << std::endl;
    std::cout << "---------------------------------------\n";
}

template<typename T>
void print_stack(T &stck)
{
    std::cout << "size: " << stck.size() << std::endl;
	std::cout << "Elements:" << std::endl;
	while (stck.size() != 0) 
    {
		std::cout << "- " << stck.top() << std::endl;
		stck.pop();
	}
    std::cout << "---------------------------------------\n";
}

#endif