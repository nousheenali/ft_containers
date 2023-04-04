/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 23:38:06 by nali              #+#    #+#             */
/*   Updated: 2023/04/03 20:21:40 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_HPP
#define COMMON_HPP

#include <iomanip> //for setprecision

template<typename T>
void print_stack(T &stck)
{
    std::cout << "size: " << stck.size() << std::endl;
	std::cout << "Stack Elements:" << std::endl;
	while (stck.size() != 0) 
    {
		std::cout << "- " << stck.top() << std::endl;
		stck.pop();
	}
    std::cout << "---------------------------------------\n";
}

template<typename T>
void print_vector(T &vec)
{
    std::cout << "size: " << vec.size() << std::endl;
	std::cout << "Vector Elements:" << std::endl;
	for (size_t i = 0; i < vec.size(); i++) 
        std::cout << "vector[" << i << "] = " << vec[i] << std::endl;
    std::cout << "---------------------------------------\n";
}

template <typename T>
void	print_map(T const &mp)
{
	std::cout << "size: " << mp.size() << std::endl;
	typename T::const_iterator it = mp.begin(), ite = mp.end();
	std::cout << std::endl << "Map Elements:" << std::endl;
	for (; it != ite; ++it)
		std::cout << "key: " << it->first << " - value: " << it->second << std::endl;
	std::cout << "---------------------------------------\n\n";
}
#endif