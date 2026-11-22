/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarek <mmarek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 19:26:14 by mmarek            #+#    #+#             */
/*   Updated: 2025/09/11 15:47:15 by mmarek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HELPER_HPP
# define HELPER_HPP

#include <iostream>
#include <vector>

std::vector<size_t> generateJacob(size_t sizeVecotr);

template <typename Container>
void printMatrix(const Container &matrix) {

    for (size_t r = 0; r < matrix.size(); ++r) {
        for (size_t c = 0; c < matrix[r].size(); ++c) {
            std::cout << matrix[r][c] << " ";
        }
        std::cout << std::endl;
    }
}

template <typename Container>
void printVector(const Container &con) {

    for (long unsigned int i = 0; i < con.size(); ++i)
        std::cout << " " << con[i];
    std::cout << std::endl;
}

// Prints at most `limit` elements, then " [...]" for long sequences.
template <typename Container>
void printPreview(const Container &con, size_t limit) {

    for (size_t i = 0; i < con.size() && i < limit; ++i)
        std::cout << " " << con[i];
    if (con.size() > limit)
        std::cout << " [...]";
    std::cout << std::endl;
}

#endif