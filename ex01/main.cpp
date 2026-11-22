/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarek <mmarek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 13:16:26 by mmarek            #+#    #+#             */
/*   Updated: 2025/09/17 11:00:39 by mmarek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <iostream>

int main(int argc, char** argv)
{

    if (argc < 2)
    {
        std::cerr << "Error: Wrong input, insert input as ./RPN \"9 8 + 2 *\" or ./RPN 9 8 + 2 '*'" << std::endl;
        return 1;
    }

    std::string inputString;

    for (int i = 1; i < argc; ++i) {

        if (i > 1)
            inputString += " ";
        inputString += argv[i];
    }

    RPN rpn;

    try
    {
        double result = rpn.calculate(inputString);
        std::cout << result << std::endl;
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
