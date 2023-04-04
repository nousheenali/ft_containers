/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element_access.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 19:41:37 by nali              #+#    #+#             */
/*   Updated: 2023/04/04 00:27:13 by nali             ###   ########.fr       */
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
        NAMESPACE::map<std::string,int> map1;
        map1.insert(NAMESPACE::make_pair("alpha", 0));
        map1.insert(NAMESPACE::make_pair("beta", 0));
        map1.insert(NAMESPACE::make_pair("gamma", 0));
        print_map(map1);
        
        //at
        map1.at("alpha") = 10;
        map1.at("beta") = 20;
        map1.at("gamma") = 30;
        print_map(map1);

        //operator[]
        map1["alpha"]= 50;
        map1["beta"]= 100;
        map1["gamma"]=map1["beta"];
        print_map(map1);  
    }
    
    std::cout <<std::endl;
    gettimeofday(&exec, NULL);
	double end = 1.0e6 * exec.tv_sec + exec.tv_usec;
	std::cout << std::fixed << std::setprecision(3) << (end - start) / 1000 << " ms" << std::endl;
	return 0;
}