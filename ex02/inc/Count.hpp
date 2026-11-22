/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Count.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarek <mmarek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 16:17:14 by mmarek            #+#    #+#             */
/*   Updated: 2025/09/12 11:22:45 by mmarek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COUNT_HPP
#define COUNT_HPP

class Count {

public:

    Count();

    ~Count();

    Count(const Count& other);

    Count &operator=(const Count& other); 

    struct Compare {
        static int count;

        Compare() {}
        ~Compare() {}
        Compare(const Compare& other);
        Compare& operator=(const Compare& other);
        bool operator()(int a, int b);
    };

    static int getCount();

    static void setCountZero();
};

#endif