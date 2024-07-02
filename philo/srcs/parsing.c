/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 17:10:53 by simarcha          #+#    #+#             */
/*   Updated: 2024/07/02 17:12:34 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_number_range(char *str_user, char *positive_lim,
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

int	check_error(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		if (check_number_range(argv[i], "2147483647", "-2147483648") == 0)
		{
			write(2, "You have to input integers only\n", 33);
			printf("argv[%i] is not in the integer range\n", i);
			return (1);
		}
		while (argv[i][j])
		{
			if (ft_isdigit(argv[i][j]) == 0)
			{
				if (j != 0 && argv[i][j] != '+' && argv[i][j] != '-')
					return (printf("argv[%i] ill written\n", i), 1);
			}
			j++;
		}
		i++;
	}
	return (0);
}