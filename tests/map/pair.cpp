/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 19:41:37 by nali              #+#    #+#             */
/*   Updated: 2023/04/06 13:11:31 by nali             ###   ########.fr       */
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
        NAMESPACE::map<std::string,int> mp;
        std::cout << "Demostrates mak_pair and insertion into map\n";
        mp.insert (NAMESPACE::make_pair<std::string,int>("aa", 100) );
        mp.insert (NAMESPACE::make_pair<std::string,int>("bb", 200) );
        mp.insert (NAMESPACE::make_pair<std::string,int>("cc", 300) );
        print_map(mp);
       
        std::cout << "Demostrates duplicate key is not inserted into Map But duplicate value is.\n";
        mp.insert (NAMESPACE::make_pair<std::string,int>("aa", 400) );
        mp.insert (NAMESPACE::make_pair<std::string,int>("dd", 100) );
        print_map(mp);
    }
    
    std::cout <<std::endl;
    gettimeofday(&exec, NULL);
	double end = 1.0e6 * exec.tv_sec + exec.tv_usec;
	std::cout << std::fixed << std::setprecision(3) << (end - start) / 1000 << " ms" << std::endl;
	return 0;
}