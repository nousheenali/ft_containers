/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 17:59:19 by nali              #+#    #+#             */
/*   Updated: 2023/01/23 15:09:52 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/containers.hpp"
#include <vector>

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

/* stack test*/
// int main(void)
// {
//     std::stack<int> s;
//     std::vector<int> v;
//     ft::stack<int> stck;
//     stck.push(3);
//     stck.push(11);
//     stck.push(12);
//     s.push(3);
//     s.push(11);
//     s.push(12);
//     printf("%lu\n", stck.size());
//     ft::stack<int> stck2(stck);
//     std::stack<int> s2(s);
//     ft::stack<int> stck3 = stck;
//     std::stack<int> s3 = s;
//     printf("%d\n", stck3<stck2);
//     printf("%d\n", s3<s2);
// }


/*vector test*/
int main(void)
{
    std::vector<int> vec_s1;
    ft::vector<int> vec_f1;

    std::vector<int>::iterator it1;
    ft::vector<int>::iterator it2;
    
    std::vector<int> vec_s2(5, 10);
    ft::vector<int> vec_f2(5, 10);

    it2 = vec_f2.begin();
    while(it2 != vec_f2.end())
    {}
        std::cout << vec_s2[i]<< ' ';
    }

    std::vector<int> vec_s3(vec_s2);
    ft::vector<int> vec_f3(vec_f2);

    


    

}

