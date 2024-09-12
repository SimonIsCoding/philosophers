# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/01 15:18:01 by simarcha          #+#    #+#              #
#    Updated: 2024/09/12 13:22:05 by simarcha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#SETUP
NAME				= philo
CC					= cc
CFLAGS				= -Wall -Wextra -Werror -fsanitize=thread
RM					= rm -rf

#INC Files - All the includes/header files that I used for this project
INC_DIR				= ./includes/
INC_FILES			= philo.h
INC					= $(addprefix $(INC_DIR), $(INC_FILES))

#SRCS Files - All files that I need for this project
SRCS_DIR			= ./srcs/
SRCS_FILES			= main.c \
					utils_functions.c \
					parsing.c \
					custom_usleep.c \
					init.c \
					philo_routine.c
SRCS				= $(addprefix $(SRCS_DIR), $(SRCS_FILES))

#OBJ Files - All .c files transformed in .o files
OBJ_DIR				= obj/
OBJ					= $(patsubst $(SRCS_DIR)%.c, $(OBJ_DIR)%.o, $(SRCS))

#RULES AND COMMANDS - All the rules that we need to create this project
all:				$(NAME)

$(OBJ_DIR):
					mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o:		$(SRCS_DIR)%.c Makefile $(INC) | $(OBJ_DIR)
					$(CC) $(CFLAGS) -c $< -o $@

$(NAME):			Makefile $(INC) $(OBJ)
					$(CC) $(CFLAGS) $(OBJ) -o $@

clean:
					$(RM) $(OBJ_DIR)

fclean: 			clean
					$(RM) $(NAME)

re:					fclean all