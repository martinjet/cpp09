/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarek <mmarek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 13:16:19 by mmarek            #+#    #+#             */
/*   Updated: 2025/08/26 13:16:49 by mmarek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
#define RPN_HPP

#include <stack>
#include <string>

class RPN {

public:
    RPN();
    RPN(const RPN& other);
    RPN& operator=(const RPN& other);
    ~RPN();

    double calculate(const std::string& input);

    class ErrorInput : public std::exception {
        private:
            const char* what() const throw();
    };

    class ErrorDivideByZero : public std::exception {
        private:
            const char* what() const throw();
    };

    class ErrorNumberInput : public std::exception {
        private:
            const char* what() const throw();
    };

private:
    std::stack<double> st;
};

#endif