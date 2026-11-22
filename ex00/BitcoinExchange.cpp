/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarek <mmarek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 13:16:32 by mmarek            #+#    #+#             */
/*   Updated: 2025/09/17 10:55:26 by mmarek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <cstdlib>
#include <cctype>

BitcoinExchange::BitcoinExchange() {}
BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) : database(other.database) {}
BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other) {

    if (this != &other)
        database = other.database;
    return *this;
}
BitcoinExchange::~BitcoinExchange() {}

bool BitcoinExchange::loadDatabase(const std::string& filename) {

    int row = 2;
    std::map<int, std::string> dataMapErr;

    std::ifstream file(filename.c_str());
    if (!file.is_open()) {

        std::cerr << "Error: could not open database file." << std::endl;
        return false;
    }

    std::string line;
    std::getline(file, line);

    if (trimString(line) != "date,exchange_rate") {

        file.clear();
        file.seekg(0, std::ios::beg);
        row = 1;
    }

    while (std::getline(file, line)) {

        if (line.empty())
            continue;

        line = trimString(line);

        std::size_t delimiterPos = line.find(',');

        std::string date = line.substr(0, delimiterPos);
        std::string valueStr = line.substr(delimiterPos + 1);

        if (isValidDate(date) && !valueStr.empty()) {

            char* endptr;
            double value = std::strtod(valueStr.c_str(), &endptr);
            if (*endptr == '\0') {

                if (database.find(date) != database.end()) {

                    dataMapErr[row] = "Duplicate found";
                }
                database[date] = value;
            } else {

                dataMapErr[row] = line;
            }
        } else {

            dataMapErr[row] = line;
        }
        row++;
    }

    if (!dataMapErr.empty()) {

        std::cerr << "Warning: invalid rows in database:" << std::endl;

        for (std::map<int, std::string>::iterator it = dataMapErr.begin(); it != dataMapErr.end(); ++it)
            std::cerr << "  row " << it->first << ": " << it->second << std::endl;
    }

    return true;
}

bool BitcoinExchange::isValidDate(std::string& date) {

    if (!isValidDateFormat(date))
        return false;

    int year = atoi(date.substr(0, 4).c_str());
    int month = atoi(date.substr(5, 2).c_str());
    int day = atoi(date.substr(8, 2).c_str());

    if (month < 1 || month > 12)
        return false;

    bool leap = (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
    int daysInMonth[] = { 31, leap ? 29 : 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    if (day >= 1 && day <= daysInMonth[month - 1])
        return true;

    return false;
}

bool BitcoinExchange::isValidDateFormat(std::string& date) {

    if (date.size() != 10 || date[4] != '-' || date[7] != '-')
        return false;

    for (size_t i = 0; i < date.size(); ++i) {
        if (i == 4 || i == 7)
            continue;
        if (!std::isdigit(date[i]))
            return false;
    }

    return true;
}

double BitcoinExchange::isValidValue(std::string valueStr, const std::string &line) {

    if (valueStr.empty()) {

        std::cerr << "Error: bad input => " << line << std::endl;
        return -1;
    };

    char* endptr;
    double value = std::strtod(valueStr.c_str(), &endptr);
    if (*endptr != '\0') {

        std::cerr << "Error: bad input => " << line << std::endl;
        return -1;
    }

    if (value < 0.0) {

        std::cerr << "Error: not a positive number." << std::endl;
        return -1;
    }

    if (value > 1000.0) {

        std::cerr << "Error: too large a number." << std::endl;
        return -1;
    }

    return value;
}

double BitcoinExchange::getPriceForDate(std::string& date) {

    std::map<std::string, double>::const_iterator it = database.lower_bound(date);

    if (it == database.end() || it->first != date) {
        if (it != database.begin())
            --it;
        else
            return -1;
    }

    return it->second;
}

std::string BitcoinExchange::trimString(std::string &line) {

    std::string result;
    for (std::size_t i = 0; i < line.length(); ++i) {
        if (!std::isspace(static_cast<unsigned char>(line[i]))) {
            result += line[i];
        }
    }

    return result;
}

void BitcoinExchange::processInput(const std::string& filename) {

    std::ifstream file(filename.c_str());
    if (!file.is_open()) {

        std::cerr << "Error: could not open file." << std::endl;
        return ;
    }

    std::string line;
    std::getline(file, line);

    if (trimString(line) != "date|value") {

        file.clear();
        file.seekg(0, std::ios::beg);
    }

    while (std::getline(file, line)) {

        if (line.empty())
             continue;

        std::string original = line;
        line = trimString(line);

        std::size_t delimiterPos = line.find('|');
        if (delimiterPos == std::string::npos) {

            std::cerr << "Error: bad input => " << original << std::endl;
            continue ;
        }

        std::string date = line.substr(0, delimiterPos);
        std::string valueStr = line.substr(delimiterPos + 1);

        double value = isValidValue(valueStr, original);
        if (value < 0)
            continue ;

        if (date.empty()) {

            std::cerr << "Error: bad input => " << original << std::endl;
            continue ;
        };

        if (!isValidDate(date))  {

            std::cerr << "Error: bad input => " << original << std::endl;
            continue ;
        };

        double price = getPriceForDate(date);

        if (price < 0) {

            std::cerr << "Error: no exchange rate on or before " << date << std::endl;
            continue ;
        };

        std::cout << date << " => " << value << " = " << value * price << std::endl;
    }
}

void BitcoinExchange::printDatabase() {

     for (std::map<std::string, double>::iterator it = database.begin(); it != database.end(); ++it) {
         std::cout << std::fixed << std::setprecision(2);
         std::cout << it->first << " => " << it->second << std::endl;
     }
}