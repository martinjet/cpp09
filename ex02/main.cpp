/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarek <mmarek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 13:15:38 by mmarek            #+#    #+#             */
/*   Updated: 2025/10/27 13:15:44 by mmarek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include "test_function.hpp"
#include "Count.hpp"

#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>

static void printUsage() {

    std::cerr << "Usage:\n"
              << "  ./PmergeMe <positive integers...>   sort and time vector vs deque\n"
              << "  ./PmergeMe check <integers...>      sort and verify result + comparison count\n"
              << "  ./PmergeMe test <1-4>               run a built-in test set\n"
              << "  ./PmergeMe permut <2-8>             average comparisons over all permutations"
              << std::endl;
}

static double elapsedMicroseconds(clock_t start, clock_t end) {

    return static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000000;
}

static int runPermutations(const char *arg) {

    char *end;
    long value = std::strtol(arg, &end, 10);

    if (*arg == '\0' || *end != '\0' || value < 2 || value > 8) {
        std::cerr << "Error: permutation size must be a number from 2 to 8" << std::endl;
        return 1;
    }

    std::vector<std::vector<int> > allPermutation = generateAllPermutations(value);
    long fordJohnson = 0;
    long classic = 0;

    for (size_t i = 0; i < allPermutation.size(); ++i) {
        PmergeMe sorter(allPermutation[i].size(), allPermutation[i]);
        sorter.sortVector();
        fordJohnson += Count::getCount();
    }

    for (size_t i = 0; i < allPermutation.size(); ++i) {
        Count::setCountZero();
        std::sort(allPermutation[i].begin(), allPermutation[i].end(), Count::Compare());
        classic += Count::getCount();
    }

    double total = static_cast<double>(allPermutation.size());
    std::cout << "Permutations of " << value << " elements: " << allPermutation.size() << std::endl;
    std::cout << "Average comparisons, Ford-Johnson : " << fordJohnson / total << std::endl;
    std::cout << "Average comparisons, std::sort    : " << classic / total << std::endl;
    std::cout << "Worst case allowed by Ford-Johnson: " << maxCompare(value) << std::endl;
    return 0;
}

static int runTestSet(const std::string &arg) {

    if (arg == "1")
        runTest(generateTestOne());
    else if (arg == "2")
        runTest(generateTestTwo());
    else if (arg == "3")
        runTest(generateTestThree());
    else if (arg == "4")
        runTest(generateTestFour());
    else {
        std::cerr << "Error: test set must be 1, 2, 3 or 4" << std::endl;
        return 1;
    }
    return 0;
}

int main(int argc, char** argv) {

    if (argc < 2) {
        printUsage();
        return 1;
    }

    std::string mode = argv[1];

    try {

        if (mode == "test" || mode == "permut") {
            if (argc != 3) {
                printUsage();
                return 1;
            }
            return mode == "test" ? runTestSet(argv[2]) : runPermutations(argv[2]);
        }

        if (mode == "check") {
            if (argc < 3) {
                printUsage();
                return 1;
            }
            // Skip the "check" keyword: argv[1] becomes the program name slot.
            PmergeMe sorter(argc - 1, argv + 1);
            checkTime(sorter);
            sortCheck(sorter, argv + 1);
            return 0;
        }

        // Default mode: output format required by the subject.
        PmergeMe sorter(argc, argv);

        std::cout << "Before:";
        printPreview(sorter.getVector(), 20);

        clock_t start = clock();
        sorter.sortVector();
        double vectorTime = elapsedMicroseconds(start, clock());

        start = clock();
        sorter.sortDeque();
        double dequeTime = elapsedMicroseconds(start, clock());

        std::cout << "After:";
        printPreview(sorter.getVector(), 20);
        std::cout << "Time to process a range of " << sorter.getSize()
                  << " elements with std::vector : " << vectorTime << " us" << std::endl;
        std::cout << "Time to process a range of " << sorter.getSize()
                  << " elements with std::deque  : " << dequeTime << " us" << std::endl;

    } catch (std::exception &e) {

        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
