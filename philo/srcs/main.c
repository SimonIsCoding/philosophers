/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 12:09:47 by simarcha          #+#    #+#             */
/*   Updated: 2024/09/15 19:18:12 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// try to execute this example: ./philo 2 500 200 200
// The result should be:
/*
0 1 has taken a fork
0 1 has taken a fork
0 1 is eating
200 1 is sleeping
200 2 has taken a fork
200 2 has taken a fork
200 2 is eating
400 1 is thinking
400 2 is sleeping
400 1 has taken a fork
400 1 has taken a fork
400 1 is eating
600 1 is sleeping
600 2 is thinking
600 2 has taken a fork
600 2 has taken a fork
600 2 is eating
800 1 is thinking
800 2 is sleeping
800 1 has taken a fork
800 1 has taken a fork
800 1 is eating
1000 2 is thinking
1000 2 has taken a fork
1000 2 has taken a fork
1000 2 is eating
1000 1 is sleeping
1200 1 is thinking
1200 2 is sleeping
1200 1 has taken a fork
1200 1 has taken a fork
1200 1 is eating
...
*/

static int	start_philosophing(t_philo *philo)
{
	if (philo->nb_philo == 1)
	{
		pthread_mutex_lock(&philo->print_mutex);
		precise_usleep(philo->time_to_die * 1000);
		printf("\033[1;38;5;214m%li %li is dead\033[0m\n",
			timestamp_in_ms(philo->start_living), philo->thread_id);
		pthread_mutex_unlock(&philo->print_mutex);
		return (0);
	}
	if (init_threads(philo) == -1)
		return (-1);
	return (0);
}

static int	destroy_forks(t_philo *philo, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < philo->nb_philo)
	{
		if (pthread_mutex_destroy(&forks[i]) != 0)
			return (-1);
//		pthread_mutex_destroy(&philo[i].dead_flag_mutex);
		i++;
	}
	if (pthread_mutex_destroy(&philo->print_mutex) != 0)
		return (-1);
	if (pthread_mutex_destroy(philo->dead_flag_mutex) != 0)
		return (-1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo			*philo;
	pthread_mutex_t	*forks;
	long			dead_flag;

	dead_flag = 0;
	if (check_error(argc, argv) == 1)
		return (1);
	philo = init_philo_struct(argv, &dead_flag);//to free once used
	forks = init_forks(philo);//to free once used
	if (!philo || !forks)
		return (2);
	start_philosophing(philo);//=>init_threads
	destroy_forks(philo, forks);
	free(philo);
	free(forks);
	return (0);
}

	// printf("before starting philosophing\n");
	// printf("before destroying the forks\n");
	// printf("after destroying the forks\n");
	// 	return (3);
		// return (4);

