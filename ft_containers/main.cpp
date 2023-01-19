/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 17:59:19 by nali              #+#    #+#             */
/*   Updated: 2023/01/18 15:07:50 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/containers.hpp"

int main(void)
{
    std::string choice;
    std::cout << "Please enter your choice: ";
    std::cin >> choice;
    if (choice == "STACK")
    {
        std::cout << BLUE << "TESTING FEATURES OF STACK\t" << END;
        begin_stack_test();
    }
    return (0);
}
