/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarek <mmarek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 13:15:57 by mmarek            #+#    #+#             */
/*   Updated: 2025/10/29 12:10:10 by mmarek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include "helper.hpp"
#include "Count.hpp"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <iostream>
#include <limits>

/**
 * @brief Default constructor for PmergeMe class
 */
PmergeMe::PmergeMe() {}

/**
 * @brief Destructor for PmergeMe class
 */
PmergeMe::~PmergeMe() {}

/**
 * @brief Copy constructor for PmergeMe class
 */
PmergeMe::PmergeMe(const PmergeMe& other) : vec(other.vec), deq(other.deq), jacobNumber(other.jacobNumber), countCompare(other.countCompare) {}

/**
 * @brief Assignment operator for PmergeMe class
 */
PmergeMe& PmergeMe::operator=(const PmergeMe &other) {

    if (this != &other) {
        vec = other.vec;
        deq = other.deq;
        jacobNumber = other.jacobNumber;
        countCompare = other.countCompare;
    }
    return *this;
}

/**
 * @brief Constructor for testing permutations
 */
PmergeMe::PmergeMe(int argc, std::vector<int> vec) {

    for (int i = 0; i < argc; ++i) {

        this->vec.push_back(vec[i]);
    }
    jacobNumber = generateJacob(vec.size());
    Count::setCountZero();
}

/**
 * @brief Constructor that parses and validate command line arguments
 */
PmergeMe::PmergeMe(int argc, char** argv) {

    for (int i = 1; i < argc; ++i) {

        char *end;

        long value = std::strtol(argv[i], &end, 10);
        if (argv[i][0] == '\0' || *end != '\0')
        {
            std::cerr << "Not correct number: " << argv[i] << std::endl;
            throw ErrorInput();
        }

        if (value < 0) {
            std::cerr << "Negative number found: " << argv[i] << std::endl;
            throw ErrorInput();
        }

        if (value > std::numeric_limits<int>::max()) {
            std::cerr << "Out of int range: " << argv[i] << std::endl;
            throw ErrorInput();
        }

        vec.push_back(static_cast<int>(value));
        deq.push_back(static_cast<int>(value));
    }
    jacobNumber = generateJacob(vec.size());
    Count::setCountZero();
}

/**
 * @brief Sorts the vector using Ford-Johnson merge-insertion algorithm
 *
 * Initiates the sorting process by converting the vector into a matrix where
 * each element occupies its own row.
 *
 * @return std::vector<int> The sorted vector (first row of resulting matrix)
 */
std::vector<int> PmergeMe::sortVector() {

    Count::Compare::count = 0;
    if (vec.size() < 2) {
        countCompare = 0;
        return vec;
    }
	const int col = 1;
	std::vector<std::vector<int> > matrix;
    for (size_t i = 0; i < vec.size(); i += col) {
        std::vector<int> row;
        for (size_t j = 0; j < col && (i + j) < vec.size(); ++j) {
            row.push_back(vec[i + j]);
        }
        matrix.push_back(row);
    }
	std::vector<int> residue;
    vec = recursiveSort(matrix, residue)[0];
    countCompare = Count::getCount();
    return vec;
}

/**
 * @brief Sorts the deque using Ford-Johnson merge-insertion algorithm
 */
std::deque<int> PmergeMe::sortDeque() {

    Count::Compare::count = 0;
    if (deq.size() < 2) {
        countCompare = 0;
        return deq;
    }
    const int col = 1;
    std::deque<std::deque<int> > matrix;
    for (size_t i = 0; i < deq.size(); i += col) {
        std::deque<int> row;
        for (size_t j = 0; j < col && (i + j) < deq.size(); ++j) {
            row.push_back(deq[i + j]);
        }
        matrix.push_back(row);
    }
	std::deque<int> residue;
    deq = recursiveSort(matrix, residue)[0];
    countCompare = Count::getCount();
    return deq;
}

/**
 * @brief Calculates the next insertion index using Jacobsthal sequence
 *
 * @param b Current base index for Jacobsthal sequence
 * @param indexJ Reference to current position in Jacobsthal array
 * @return size_t Next optimal insertion index
 */
size_t PmergeMe::getIndex(size_t b, size_t &indexJ) {

    //size_t Jacobsthal[] = {1, 3, 5, 11, 21, 43, 85, 171, 341, 683, 1365, 2731, 5461, 10923, 21845, 43691, 87381, 174763, 349525, 699051, 1398101, 2796203, 5592405, 11184811, 22369621, 44739243, 89478485, 178956971, 357913941, 715827883, 1431655765};

    if (indexJ > 0 && (b - 1) > jacobNumber[indexJ - 1])
        return (b - 1);

    indexJ++;
    return jacobNumber[indexJ];
}

// **************************** VECTOR IMPLEMENTATION ****************************

/**
 * @brief Recursive core of Ford-Johnson merge-insertion sort algorithm
 *
 * @return std::vector<std::vector<int> > Matrix with single sorted row
 */
std::vector<std::vector<int> > PmergeMe::recursiveSort(std::vector<std::vector<int> > &input, std::vector<int> &residue) {

    size_t size = input[0].size() * 2;

    compareAndSwap(input);

	// Store odd remaining row in residue
	if (input.size() % 2 != 0) {
		residue.insert(residue.begin(), input.back().begin(), input.back().end());
	}

    std::vector<std::vector<int> > matrix;

    // Merge rows: 1+2, 3+4, etc.
    // Process pairs of rows (step by 2)
    for (size_t i = 0; i + 1 < input.size(); i += 2) {

        std::vector<int> mergedRow = input[i];
        mergedRow.insert(mergedRow.end(), input[i + 1].begin(), input[i + 1].end());
        matrix.push_back(mergedRow);
    }

    // Continue recursion until only one row remains
	if (matrix.size() > 1) {

        matrix = recursiveSort(matrix, residue);
	}

    // Add residue elements if current level is appropriate
    if ((matrix[0].size()) / 2 < size) {
		matrix[0].insert(matrix[0].end(), residue.begin(), residue.end());
	}

	std::vector<int> mainChain;
	std::vector<int> pend;
	std::vector<int> res;

    // Separate into main chain, pending elements, and residue
    initMainChain(matrix, mainChain, pend, res, size);

    // Insert pending elements optimally using Jacobsthal sequence
    matrix[0] = pendToMainChain(mainChain, pend, size);
	matrix[0].insert(matrix[0].end(), res.begin(), res.end());

	return matrix;
}

/**
 * @brief Inserts elements from the pending chain into the sorted main chain
 *
 * @return std::vector<int> Complete sorted sequence after all insertions
 */
std::vector<int> PmergeMe::pendToMainChain(std::vector<int> mainChain, std::vector<int> pend, int size) {

    // Initialize positions of a elements (a1, a2, a3, a4, ...)
    // Create array with positions of elements a1, a2, a3, ...
    std::vector<size_t> aPosition;
    size_t j = 0;
    for (size_t i = size/2; i <= mainChain.size(); i += size/2) {
        aPosition.push_back(static_cast<int>(i));
        j++;
    }

    // Insert b1, which shifts positions of all a elements
    for (size_t i = 0; i < aPosition.size(); ++i) {
        aPosition[i] += size/2;
    }

     size_t indexJ = 0;    // Initialize Jacobsthal index
     size_t b = 1;         // Initialize b counter

	for (size_t i = (size/2)-1; i < pend.size(); i += (size/2)) {

        // Get next b using Jacobsthal sequence: b=1 (already inserted), then b=3, b=2, b=11, etc.
        b = getIndex(b, indexJ);

        // Calculate index for current b element
        // First is b2 since b1 is already placed
        size_t bPosition = ((b - 1) * (size/2)) - 1;

        // Check if index is within bounds
        if (bPosition >= (pend.size())) {
            // If out of bounds, find a valid b to insert
            while (bPosition >= (pend.size())) {
                b--;
                bPosition = ((b - 1) * (size/2)) - 1;
            }
        }

        // Determine search range for binary search
        size_t endSearch;
        if (b < (aPosition.size()))
            endSearch = aPosition[b] - size/2 - 1;
        else
            endSearch = mainChain.size();

        // Create search space for binary search
        std::vector<int> indexMainChain;
		for (size_t i = size / 2 - 1; i < endSearch; i += (size / 2)) {
			indexMainChain.push_back(mainChain[i]);
		}

        // Perform binary search to find insertion position
        std::vector<int>::iterator it = std::lower_bound(indexMainChain.begin(), indexMainChain.end(), pend[bPosition], Count::Compare());

		// Calculate safe insertion position
		size_t insertPosition = (it - indexMainChain.begin() + 1) * (size / 2) - 1;

        // Update positions of a elements that come after insertion point
        for (size_t i = 0; i < aPosition.size(); ++i) {
            if (aPosition[i] > (insertPosition))
                aPosition[i] += size/2;
        }

		// Insert the element(s) at calculated position
        mainChain.insert(mainChain.begin() + insertPosition - ((size/2) - 1), pend.begin() + bPosition - ((size/2) - 1), pend.begin() + (size/2) + bPosition - ((size/2) - 1));
    }

    return mainChain;
}

// **************************** DEQUE IMPLEMENTATION ****************************

/**
 * @brief Deque Recursive core of Ford-Johnson merge-insertion sort algorithm
 *
 * @return std::deque<std::deque<int> > Matrix with single sorted row
 */
std::deque<std::deque<int> > PmergeMe::recursiveSort(std::deque<std::deque<int> > &input, std::deque<int> &residue) {

	size_t size = input[0].size() * 2;

    compareAndSwap(input);

	if (input.size() % 2 != 0) {
		residue.insert(residue.begin(), input.back().begin(), input.back().end());
	}

    std::deque<std::deque<int> > matrix;

    for (size_t i = 0; i + 1 < input.size(); i += 2) {

        std::deque<int> mergedRow = input[i];
        mergedRow.insert(mergedRow.end(), input[i + 1].begin(), input[i + 1].end());
        matrix.push_back(mergedRow);
    }

	if (matrix.size() > 1) {

        matrix = recursiveSort(matrix, residue);
	}

	if ((matrix[0].size()) / 2 < size) {

		matrix[0].insert(matrix[0].end(), residue.begin(), residue.end());
	}

	std::deque<int> mainChain;
	std::deque<int> pend;
	std::deque<int> res;

    initMainChain(matrix, mainChain, pend, res, size);

    matrix[0] = pendToMainChain(mainChain, pend, size);
	matrix[0].insert(matrix[0].end(), res.begin(), res.end());

	return matrix;
}

/**
 * @brief Inserts elements from the pending chain into the sorted main chain
 *
 * @return std::deque<int> Complete sorted sequence after all insertions
 */
std::deque<int> PmergeMe::pendToMainChain(std::deque<int> mainChain, std::deque<int> pend, int size) {

    std::deque<size_t> aPosition;
    size_t j = 0;
    for (size_t i = size/2; i <= mainChain.size(); i += size/2) {
        aPosition.push_back(static_cast<int>(i));
        j++;
    }

    for (size_t i = 0; i < aPosition.size(); ++i) {
        aPosition[i] += size/2;
    }

    size_t indexJ = 0;
    size_t b = 1;

	for (size_t i = (size/2)-1; i < pend.size(); i += (size/2)) {

        b = getIndex(b, indexJ);

        size_t bPosition = ((b - 1) * (size/2)) - 1;

        if (bPosition >= (pend.size())) {
            while (bPosition >= (pend.size())) {
                b--;
                bPosition = ((b - 1) * (size/2)) - 1;
            }
        }

        size_t endSearch;
        if (b < size_t(aPosition.size()))
            endSearch = aPosition[b] - size/2 - 1;
        else
            endSearch = mainChain.size();

        std::deque<int> indexMainChain;
		for (size_t i = size / 2 - 1; i < endSearch; i += (size / 2)) {
			indexMainChain.push_back(mainChain[i]);
		}

        std::deque<int>::iterator it = std::lower_bound(indexMainChain.begin(), indexMainChain.end(), pend[bPosition], Count::Compare());

		size_t insertPosition = (it - indexMainChain.begin() + 1) * (size / 2) - 1;

        for (size_t i = 0; i < aPosition.size(); ++i) {
            if (aPosition[i] > (insertPosition))
                aPosition[i] += size/2;
        }

        size_t startInsert = 0;
        if (insertPosition >= static_cast<size_t>((size/2)-1))
            startInsert = insertPosition - ((size/2)-1);

        size_t startPend = 0;
        if (bPosition >= static_cast<size_t>((size/2)-1))
            startPend = bPosition - ((size/2)-1);

        size_t endPend = std::min(pend.size(), startPend + size/2);

        mainChain.insert(
            mainChain.begin() + startInsert,
            pend.begin() + startPend,
            pend.begin() + endPend
        );
    }

    return mainChain;

}

// **************************** GETTER METHODS ****************************

/**
 * @brief Gets the number of comparisons performed during sorting
 */
int PmergeMe::getCount() {

    return countCompare;
}

/**
 * @brief Returns vector
 */
std::vector<int> PmergeMe::getVector() {

    return vec;
}

/**
 * @brief Returns deque
 *
 */
std::deque<int> PmergeMe::getDeque() {

    return deq;
}

/**
 * @brief Gets the size of the data containers
 */
int PmergeMe::getSize() const {

    if (!vec.empty())
        return static_cast<int>(vec.size());

    return static_cast<int>(deq.size());
}

/**
 * @brief Error message for input validation exceptions
 */
const char* PmergeMe::ErrorInput::what() const throw() {

    return "Error";
}