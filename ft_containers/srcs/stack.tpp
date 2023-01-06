/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.tpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 08:16:41 by nali              #+#    #+#             */
/*   Updated: 2023/01/06 09:58:35 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.hpp"

namespace ft
{
    template<typename T, typename Container>
    bool Stack<T, Container>::empty() const
    {
        return (this->c.empty());
    }

    template<typename T, typename Container>
    void Stack<T, Container>::pop()
    {
        return (this->c.pop_back());
    }

    template<typename T, typename Container>
    void Stack<T, Container>::push(const T& x)
    {
        this->c.push_back(x);
    }

    template<typename T, typename Container>
    T& Stack<T, Container>::top()
    {
        return (this->c.back());
    }
}