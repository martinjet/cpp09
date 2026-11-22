# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmarek <mmarek@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/25 12:31:44 by mmarek            #+#    #+#              #
#    Updated: 2025/09/12 11:09:42 by mmarek           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = PmergeMe

CXX = c++
CFLAGS = -Wall -Werror -Wextra -std=c++98 -Iinc

SRCS = 		main.cpp \
			src/PmergeMe.cpp \
			src/Count.cpp \
			src/test_function.cpp \
			src/helper.cpp

OBJECTS = $(SRCS:.cpp=.o)

%.o: %.cpp
	$(CXX) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CXX) $(CFLAGS) -o $(NAME) $(OBJECTS)

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean re