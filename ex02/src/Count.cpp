/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Count.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarek <mmarek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 16:17:16 by mmarek            #+#    #+#             */
/*   Updated: 2025/09/12 11:22:30 by mmarek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Count.hpp"
#include "PmergeMe.hpp"

int Count::Compare::count = 0;

Count::Count() {}

Count::~Count() {}

Count::Count(const Count& other) { 

    (void) other;
}

Count &Count::operator=(const Count& other) {

    if (this != &other) {
    }
    return *this;
}

Count::Compare::Compare(const Count::Compare& other) { 

    (void)other;
 }

Count::Compare& Count::Compare::operator=(const Count::Compare& other) {

    (void)other;
    return *this;
}

bool Count::Compare::operator()(int a, int b) {
    ++count;
    return a < b;
}

int Count::getCount() {

    return Compare::count;
}

void Count::setCountZero() {

   Compare::count = 0;
}