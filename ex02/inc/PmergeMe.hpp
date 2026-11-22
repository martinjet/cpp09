/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarek <mmarek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 13:16:03 by mmarek            #+#    #+#             */
/*   Updated: 2025/09/12 11:21:15 by mmarek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include "helper.hpp"
#include "Count.hpp"
#include <vector>
#include <deque>
#include <string>

class Count;

/**
 * @class PmergeMe
 * @brief A class that demonstrates sorting and comparison counting
 *        using both std::vector and std::deque.
 *
 * The class stores two containers (vector and deque)
 *
 */
class PmergeMe {
private:

    PmergeMe();

    std::vector<int> vec;
    std::deque<int> deq;
    std::vector<size_t> jacobNumber;
    int countCompare;

    std::vector<std::vector<int> > recursiveSort(std::vector<std::vector<int> > &input, std::vector<int> &residue);
    std::deque<std::deque<int> > recursiveSort(std::deque<std::deque<int> > &input, std::deque<int> &residue);

    std::vector<int> pendToMainChain(std::vector<int> mainChain, std::vector<int> pend, int size);
    std::deque<int> pendToMainChain(std::deque<int> mainChain, std::deque<int> pend, int size);

    size_t getIndex(size_t b, size_t &indexJ);

public:

    PmergeMe(const PmergeMe& other);
    PmergeMe& operator=(const PmergeMe& other);
    ~PmergeMe();

    PmergeMe(int argc, char** argv);
    PmergeMe(int argc, std::vector<int> vec);

    //getters
    std::vector<int> getVector();
    std::deque<int> getDeque();
    int getSize() const;
    int getCount();

    //sort
    std::vector<int> sortVector();
    std::deque<int> sortDeque();

    class ErrorInput : public std::exception {
        private:
            const char* what() const throw();
    };

/**
 * @brief It compares the rows of a matrix by the last number,
 *        and swaps them if necessary so that the smaller one is on top.
 *        It compares rows 1 and 2, 3 and 4 ...
 */
template <typename Container>
void compareAndSwap(Container &input) {

    for (size_t i = 0; i + 1 < input.size(); i += 2) {

        typename Count::Compare cmp;
        if (!cmp(input[i].back(), input[i + 1].back())) {
            std::swap(input[i], input[i + 1]);
        }
    }
}

/**
 * @brief init MainChain as b1 a1 a2 a3 ..., init pend b2, b3 ... and res
 */

template <typename MatrixContainer, typename Container>
void initMainChain(MatrixContainer &matrix, Container &mainChain, Container &pend, Container &res, int size) {

    for (int i = 0; i < size; ++i)
		mainChain.push_back(matrix[0][i]);

	bool doV1 = false;

    for (size_t i = size; i < matrix[0].size(); i += (size / 2)) {
        size_t end = i + size / 2;
        if (end > matrix[0].size()) {
			res.insert(res.end(), matrix[0].begin() + i, matrix[0].end());
			break;
		}
        if (doV1)
            mainChain.insert(mainChain.end(), matrix[0].begin() + i, matrix[0].begin() + end);
        else
            pend.insert(pend.end(), matrix[0].begin() + i, matrix[0].begin() + end);
        doV1 = !doV1;
    }
}

};

#endif