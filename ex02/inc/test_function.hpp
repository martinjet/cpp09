/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_function.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarek <mmarek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 15:46:49 by mmarek            #+#    #+#             */
/*   Updated: 2025/09/11 13:44:58 by mmarek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_FUNCTION_HPP
#define TEST_FUNCTION_HPP

#include "PmergeMe.hpp"

#include <vector>

std::vector<std::vector<int> > generateAllPermutations(int n);

char** generateTestOne ();
char** generateTestTwo ();
char** generateTestThree ();
char** generateTestFour ();

void checkTime (PmergeMe &merge);
void sortCheck (PmergeMe &merge, char** argv);
int maxCompare(int numbers);

void runTest(char** testArray);

#endif
