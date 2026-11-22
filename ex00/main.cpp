/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarek <mmarek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 13:16:45 by mmarek            #+#    #+#             */
/*   Updated: 2025/09/17 10:59:17 by mmarek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <iomanip> 
#include "BitcoinExchange.hpp"

int main(int argc, char** argv) {

    if (argc != 2) {

        std::cerr << "Error: could not open file." << std::endl;
        return 1;
    }

    BitcoinExchange btc;

    if (!btc.loadDatabase("./data.csv")) {

        std::cerr << "Error: could not load database." << std::endl;
        return 1;
    }

    btc.processInput(argv[1]);

    return 0;
}