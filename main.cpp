/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 17:59:19 by nali              #+#    #+#             */
/*   Updated: 2023/01/20 11:48:16 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/containers.hpp"

// int main(void)
// {
//     std::string choice;
//     std::cout << "Please enter your choice: ";
//     std::cin >> choice;
//     if (choice == "STACK")
//     {
//         std::cout << BLUE << "TESTING FEATURES OF STACK\n" << END;
//         begin_stack_test();
//     }
//     return (0);
// }

int main(void)
{
    std::stack<int> s;
    ft::Stack<int> stck;
    stck.push(3);
    stck.push(11);
    stck.push(12);
    s.push(3);
    s.push(11);
    s.push(12);
    printf("%lu\n", stck.size());

    ft::Stack<int> stck2(stck);
    std::stack<int> s2(s);
    
    ft::Stack<int> stck3 = stck;
    std::stack<int> s3 = s;
    
    
    printf("%d\n", stck3<stck2);
    printf("%d\n", s3<s2);
   

}
