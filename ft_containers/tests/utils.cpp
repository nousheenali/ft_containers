/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 14:30:14 by nali              #+#    #+#             */
/*   Updated: 2023/01/18 15:06:25 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/containers.hpp"

int ft_compare_files(std::string file1, std::string file2)
{
    char c1, c2;
    std::fstream f1, f2;

    f1.open(file1,std::ios::in);
    f2.open(file2,std::ios::in);
    while(1)
    {
        c1=f1.get();
        c2=f2.get();
        if(c1!=c2){
            return (1);
        }
        if((c1==EOF)||(c2==EOF))
            break;
    }
    f1.close();
    f2.close();
    return (0);
}