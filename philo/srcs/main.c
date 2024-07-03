/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 12:09:47 by simarcha          #+#    #+#             */
/*   Updated: 2024/07/03 19:15:12 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// on a besoin de convertir chaque argument en entier
// pour le premier entier, ce sera notre nombre de threads

int	philosophing(char **argv)
{
	t_philo	*data;

	data = malloc(sizeof(t_philo) * 1 /*data->nb_philo*/);
	if (!data)
		return (write(2, "Malloc Error\n", 14), MALLOC_ERROR);
	data->nb_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	return (0);
}

int	main(int argc, char **argv)
{
	if (check_error(argc, argv) == 1)
		return (1);
	philosophing(argv);
	return (0);
}
/*
int	rate_time(void)
{
	int				requested_sleep_time;
	int				actual_time;
	struct timeval	start;
	struct timeval	end;

	requested_sleep_time = 2 * 1000000;
	printf("requested_sleep_time = 2 seconds = 2 000 000 microseconds\n");
	gettimeofday(&start, NULL);
	usleep(requested_sleep_time);
	gettimeofday(&end, NULL);
	actual_time = (end.tv_sec - start.tv_sec) * 10000000 + (end.tv_usec - start.tv_usec);
	printf("actual_time slept = %d\n", actual_time);
	return (0);
}

int main(void)
{
	rate_time();
	return (0);
}*/