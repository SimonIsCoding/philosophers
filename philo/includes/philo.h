/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 11:59:17 by simarcha          #+#    #+#             */
/*   Updated: 2024/07/02 19:22:15 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

//# define ERROR_MSG	"./philo number_of_philosophers time_to_die time_to_eat
//time_to_sleep [number_of_times_each_philosopher_must_eat]"
//# define INT_MIN	-2147483648
//# define INT_MAX	2147483647
# define MALLOC_ERROR	3

typedef struct philo
{
	int	nb_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
}				t_philo;

//utils_functions.c
int		ft_isdigit(int c);
int		ft_strcmp(const char *s1, const char *s2);
size_t	ft_strlen(const char *s);
int		ft_atoi(const char *str);

//parsing.c
int		check_number_range(char *str_user, char *positive_lim,
						char *negative_lim);
int		check_error(char **argv);

#endif