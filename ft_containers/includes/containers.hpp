/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   containers.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 09:02:05 by nali              #+#    #+#             */
/*   Updated: 2023/01/18 15:07:43 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTAINERS_HPP
#define CONTAINERS_HPP

#include <stdio.h>
#include <iostream>
#include <stack>
#include <fstream>
#include "../container_files/stack.hpp"
#include "stack_test.hpp"

#define GREEN "\033[1;32m"
#define RED "\031[1;32m"
#define BLUE "\033[1;34m"
#define END "\033[0m"


void begin_stack_test(void);
int ft_compare_files(std::string f1, std::string f2);

#endif
