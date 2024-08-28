/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 17:10:53 by simarcha          #+#    #+#             */
/*   Updated: 2024/08/26 15:48:51 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	display_error_message(void)
{
	write(2, "Arguments ill written.\n", 24);
	write(2, "Try to follow this example:\n", 29);
	write(2, ERROR_MSG, 116);
	write(2, "with: 1 ≤ number_of_philosophers ≤ 200\n", 44);
	write(2, "and : time_to_die ≥ 60\n", 26);
	write(2, "and : time_to_eat ≥ 60\n", 26);
	write(2, "and : time_to_sleep ≥ 60\n", 28);
	write(2, "and : number_of_times_each_philosopher_must_eat ≥ 0\n", 55);
	return ;
}

//This functions is use to know if the number input is in the integer range
//If not, we send an error message
static int	check_number_range(char *str_user, char *positive_lim,
						char *negative_lim)
{
	int	len_user;

	len_user = ft_strlen(str_user);
	if (len_user > 12)
		return (0);
	else if (len_user == 12 || len_user == 11)
	{
		if (str_user[0] == '-')
		{
			if (ft_strcmp(str_user, negative_lim) > 0)
				return (0);
		}
		else if (str_user[0] == '+')
		{
			if (ft_strcmp(&str_user[1], positive_lim) > 0)
				return (0);
		}
		else
		{
			if (ft_strcmp(str_user, positive_lim) > 0)
				return (0);
		}
	}
	return (1);
}

//This functions checks if the number is well written as a digit
//It can start with '+' or '-' at the beginning
//But the input should be positive
//If the number is negative, we will send a message to tell the user to write
//a positive number.
static int	check_digit(char **argv, int i)
{
	int	j;

	j = 0;
	while (argv[i][j])
	{
		if (ft_isdigit(argv[i][j]) == 0)
		{
			if (!(j == 0 && (argv[i][j] == '+' || argv[i][j] == '-')))
				return (printf("argv[%i] ill written\n", i), 1);
		}
		j++;
	}
	return (0);
}

//This function is the last check.
//Some number can be well written but they should be in the certain range
//Like written in the display_message function.
static int	is_number_not_good(char *argv, int i)
{
	int	check_nb;

	check_nb = ft_atoi(argv);
	if (check_nb <= 0 && i != 5)
	{
		if (i >= 2 && i <= 4)
			printf("argv[%i] should be higher than 60ms\n", i);
		else
			printf("argv[1] has to be strictly positive but lower than 200\n");
		return (1);
	}
	else if (i == 5 && check_nb < 0)
		return (printf("argv[5] has to be positive or null\n"), 1);
	if (i == 1 && check_nb > 200)
	{
		write(2, "Too many philosophers\n", 23);
		write(2, "The argv[1] should be lower than 200\n", 38);
		return (1);
	}
	else if ((i >= 2 && i <= 4) && check_nb < 60)
		return (printf("argv[%i] should be higher than 60ms\n", i), 1);
	return (0);
}

//This function is the parsing function
//If this function returns 0, it means that all the inputs are well written
//Then there is no error
int	check_error(int argc, char **argv)
{
	int	i;

	if (argc != 5 && argc != 6)
		return (display_error_message(), 1);
	i = 1;
	while (argv[i])
	{
		if (check_number_range(argv[i], "2147483647", "-2147483648") == 0)
		{
			write(2, "You have to input integers only\n", 33);
			printf("argv[%i] is not in the integer range\n", i);
			return (1);
		}
		if (check_digit(argv, i) == 1)
			return (1);
		if (is_number_not_good(argv[i], i) == 1)
			return (1);
		i++;
	}
	return (0);
}
