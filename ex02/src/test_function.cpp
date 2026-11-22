/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_function.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarek <mmarek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 15:46:00 by mmarek            #+#    #+#             */
/*   Updated: 2025/09/11 13:45:08 by mmarek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "test_function.hpp"
#include "Count.hpp"

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>

std::vector<std::vector<int> > generateAllPermutations(int n) {
	std::vector<std::vector<int> > results;
	std::vector<int> base;

	for (int i = 1; i <= n; ++i) {
		base.push_back(i);
	}

	do {
		results.push_back(base);
	} while (std::next_permutation(base.begin(), base.end()));

	return results;
}

// Sorts one of the built-in test sets and verifies the result.
void runTest(char** testArray) {

    int size = 0;

    for (int i = 1; testArray[i] != NULL; ++i) {
        std::cout << testArray[i] << " ";
        ++size;
    }
    std::cout << std::endl;
    std::cout << "Size is : " << size << std::endl;

    PmergeMe sorter_one(size + 1, testArray);

    checkTime(sorter_one);

    std::cout << "FJ Sorted vector:";
    printVector(sorter_one.getVector());
    std::cout << "FJ Sorted deque:";
    printVector(sorter_one.getDeque());

    sortCheck(sorter_one, testArray);
}

void sortCheck (PmergeMe &merge, char** argv) {


    std::vector<int> origData;

    for (int i = 1; argv[i] != NULL; ++i) {

        long value = std::strtol(argv[i], NULL, 10);
        origData.push_back(static_cast<int>(value));
    }

    std::cout << std::endl;
    std::cout << "Original data:";
    printPreview(origData, 20);

	Count::setCountZero();

    std::sort(origData.begin(), origData.end(), Count::Compare());

    std::cout << "Sorted with std::sort:";
    printPreview(origData, 20);
    std::cout << std::endl;
	std::cout << "Count of compare using std::sort : " << Count::Compare::count << std::endl;
    std::cout << "Real Ford Johnson Count of compare :" << merge.getCount() << std::endl;
    std::cout << "Number of data :" << merge.getSize() << std::endl;
    std::cout << "Max. theoretical FJ compare :" << maxCompare(merge.getSize()) << std::endl;
	bool isTest = (origData == merge.getVector()) && (merge.getCount() <= maxCompare(merge.getSize()));

    if (isTest)
        std::cout << "\033[32m" << " --- OK --- " << "\033[0m" << std::endl;
    else
        std::cout << "\033[31m" << " !!! WRONG !!! " << "\033[0m" << std::endl;
}

void checkTime(PmergeMe &merge) {

    clock_t startVec = clock();
    merge.sortVector();
    clock_t endVec = clock();

    // clock() returns processor ticks; CLOCKS_PER_SEC converts them to seconds.
    std::cout << "Time to process a range of " << merge.getSize()
              << " elements with std::vector<int> : "
              << static_cast<double>(endVec - startVec) / CLOCKS_PER_SEC * 1000000
              << " us" << std::endl;


    startVec = clock();
    merge.sortDeque();
    endVec = clock();

    std::cout << "Time to process a range of " << merge.getSize()
              << " elements with std::deque<int> : "
              << static_cast<double>(endVec - startVec) / CLOCKS_PER_SEC * 1000000
              << " us" << std::endl;
}

int maxCompare(int numbers) {

    int sum = 0;
    for (int k = 1; k <= numbers; ++k) {
        double value = (3.0 / 4.0) * k;
        sum += static_cast<int>(ceil(log2(value)));
    }
    return sum;
}

char** generateTestThree () {

    static char* argv[] = { (char*)".pmergeme", (char*)"11", (char*)"17", (char*)"4", (char*)"20", (char*)"15", NULL };

    return argv;
}

char** generateTestTwo () {

    static char* argv[] = { (char*)"./pmergeme", (char*)"11", (char*)"17", (char*)"1", NULL };

    return argv;
}

char** generateTestOne () {

    static char* argv[] = {
        (char*)"./pmergeme",
        (char*)"2",
        (char*)"8",
        (char*)"3",
        (char*)"6",
        (char*)"7",
        (char*)"5",
        (char*)"0",
        (char*)"4",
        (char*)"9",
        (char*)"1",
        NULL
    };

    return argv;
}

char** generateTestFour () {

    static char* argv[] = {
        (char*)"./pmergeme",
        (char*)"11",
        (char*)"2",
        (char*)"17",
        (char*)"0",
        (char*)"16",
        (char*)"8",
        (char*)"6",
        (char*)"15",
        (char*)"10",
        (char*)"3",
        (char*)"21",
        (char*)"1",
        (char*)"18",
        (char*)"9",
        (char*)"14",
        (char*)"19",
        (char*)"12",
        (char*)"5",
        (char*)"4",
        (char*)"20",
        (char*)"13",
        (char*)"7",
        NULL
    };

    return argv;
}