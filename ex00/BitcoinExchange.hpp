/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarek <mmarek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 13:16:38 by mmarek            #+#    #+#             */
/*   Updated: 2025/09/17 10:59:41 by mmarek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_H
#define BITCOINEXCHANGE_H

#include <map>
#include <string>
#include <iomanip>

class BitcoinExchange {

public:
    BitcoinExchange();
    BitcoinExchange(const BitcoinExchange& other);
    BitcoinExchange& operator=(const BitcoinExchange& other);
    ~BitcoinExchange();

    bool loadDatabase(const std::string& filename);
    void processInput(const std::string& filename);

    void printDatabase();

private:

    std::map<std::string, double> database;

    bool isValidDate(std::string& date);
    bool isValidDateFormat(std::string& date);
    double isValidValue(std::string valueStr, const std::string &line);      //rename getValue or convert ...
    double getPriceForDate(std::string& date);
    std::string trimString(std::string &line);
};


#endif