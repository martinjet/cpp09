/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarek <mmarek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:31:26 by mmarek            #+#    #+#             */
/*   Updated: 2025/09/17 11:00:39 by mmarek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "helper.hpp"

#include <vector>

std::vector<size_t> generateJacob(size_t sizeVector) {

    size_t limitGenerator = 100;
    std::vector<size_t> jacob;

    jacob.push_back(0);
    jacob.push_back(1);

    for (size_t i = 2 ; i < limitGenerator; ++i) {

        size_t newJ = jacob[i-1] + 2 * jacob[i - 2];
        jacob.push_back(newJ);
        if (newJ > sizeVector)
            break;
    }
    jacob.erase(jacob.begin());
    jacob.erase(jacob.begin());

    return jacob;
}
