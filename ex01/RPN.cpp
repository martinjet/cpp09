/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarek <mmarek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 13:16:13 by mmarek            #+#    #+#             */
/*   Updated: 2025/09/17 11:00:39 by mmarek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <iostream>
#include <sstream>
#include <cctype>

RPN::RPN() {}
RPN::~RPN() {}

RPN::RPN(const RPN& other) : st(other.st) {}

RPN& RPN::operator=(const RPN& other)
{
    if (this != &other)
    {
        this->st = other.st;
    }
    return *this;
}

double RPN::calculate(const std::string &input) {

    std::istringstream tokens(input);
    std::string token;

    // Every token must be a single digit (0-9) or one operator.
    // Splitting on whitespace (instead of stripping it) makes "11 +"
    // an error rather than silently reading it as "1 1 +".
    while (tokens >> token) {

        if (token.size() != 1)
            throw ErrorInput();

        char c = token[0];

        if (std::isdigit(static_cast<unsigned char>(c))) {

            st.push(static_cast<double>(c - '0'));
        }
        else if (c == '+' || c == '-' || c == '/' || c == '*') {

            if (st.size() < 2)
                throw ErrorNumberInput();

            double right = st.top(); st.pop();
            double left = st.top(); st.pop();
            double tmp = 0;

            if (c == '+')
                tmp = left + right;
            else if (c == '-')
                tmp = left - right;
            else if (c == '*')
                tmp = left * right;
            else {
                if (right == 0)
                    throw ErrorDivideByZero();
                tmp = left / right;
            }
            st.push(tmp);
        }
        else {

            throw ErrorInput();
        }
    }

    if (st.size() != 1)
        throw ErrorNumberInput();

    return st.top();
}

const char* RPN::ErrorNumberInput::what() const throw() {

    return "Error: not enough operands or too many numbers";
}

const char* RPN::ErrorDivideByZero::what() const throw() {

    return "Error: division by zero";
}

const char* RPN::ErrorInput::what() const throw() {

    return "Error";
}