/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 12:09:47 by simarcha          #+#    #+#             */
/*   Updated: 2024/07/09 17:15:29 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	print_philo_parameter(t_philo *philo)
{
	printf("philo->nb_philo = %i\n", philo->nb_philo);
	printf("philo->time_to_die = %i\n", philo->time_to_die);
	printf("philo->time_to_eat = %i\n", philo->time_to_eat);
	printf("philo->time_to_sleep = %i\n", philo->time_to_sleep);
	printf("philo->nb_must_eat = %i\n", philo->nb_must_eat);
//	printf("philo->start_living = %i\n", (int)philo->start_living);
}

long	timestamp_in_ms(struct timeval start)
{
	struct timeval	end;
	long			sec;
	long			usec;
	long			elapsed_time_in_ms;

	gettimeofday(&end, NULL);
	sec = end.tv_sec - start.tv_sec;
	usec = end.tv_usec - start.tv_usec;
	elapsed_time_in_ms = (sec * 1000L) + (usec / 1000L);
	return (elapsed_time_in_ms);
}

t_philo	*init_philo_struct(char **argv)
{
	int				philo_nb;
	t_philo			*philo;
	struct timeval	start;

	philo_nb = ft_atoi(argv[1]);
	philo = malloc(sizeof(t_philo) * philo_nb);
	if (!philo)
		return (write(2, "Malloc Error\n", 14), NULL);
	philo->nb_philo = philo_nb;
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		philo->nb_must_eat = ft_atoi(argv[5]);
	else
		philo->nb_must_eat = -1;
	gettimeofday(&start, NULL);
	philo->start_living = start;
	return (philo);
}

//try to execute this example: ./philo 2 500 200 200
//The result should be:
/*
0 1 has taken a fork
0 1 has taken a fork
0 1 is eating
200 1 is sleeping
200 2 has taken a fork
200 2 has taken a fork
200 2 is eating
400 1 is thinking
400 1 has taken a fork
400 1 has taken a fork
400 1 is eating
400 2 is sleeping
*/

void	 philo_taking_fork(t_philo *philo)
{
	int			total_fork;
	static int	counter = 0;

	total_fork = philo->nb_philo;
	pthread_mutex_lock(&philo->left_fork);
	printf("%li %i has taken a fork\n", timestamp_in_ms(philo->start_living), philo->thread_id);
	counter++;
	total_fork--;
	pthread_mutex_unlock(&philo->left_fork);
	if (counter % 2 == 0)
		printf("%li %i is eating\n", timestamp_in_ms(philo->start_living), philo->thread_id);
	return ;
}

void	philo_sleeping(t_philo *philo)
{
	printf("%li %i is sleeping\n", timestamp_in_ms(philo->start_living), philo->thread_id);
}

void	*philo_routine(void *arg)
{
	static int		i = 1;
	t_philo			*philo;

	philo = (t_philo *)arg;
	if (philo->thread_id % 2 == 1)
	{
		philo_taking_fork(philo);
		precise_usleep(philo->time_to_eat);
		philo_sleeping(philo);
	}
	else
	{
		
	}
	i++;
	return (NULL);
}

int	init_threads(t_philo *philo)
{
	static int	i = 0;
	pthread_t	thread[philo->nb_philo];

	pthread_mutex_init(&philo->left_fork, NULL);
	while (i < philo->nb_philo)
	{
		printf("philo->thread_id = %i\n", philo->thread_id);
		philo->thread_id = i;
		if (pthread_create(&thread[i], NULL, &philo_routine, philo) == -1)
			return (-1);
		i++;
	}
	static int j = 0;
	while (j < philo->nb_philo)
	{
		if (pthread_join(thread[j], NULL) == -1)
			return (-1);
		j++;
	}
	pthread_mutex_destroy(&philo->left_fork);
	return (0);
}

int	start_philosophing(t_philo *philo)
{
	if (philo->nb_philo == 1)
		return (dying_state_for_one_philo(philo), 0);
	if (philo->nb_philo % 2 == 0)
	{
		if (init_threads(philo) == -1)
			return (-1);
	}
	else
	{
		
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo	*philo;

	if (check_error(argc, argv) == 1)
		return (1);
	philo = init_philo_struct(argv);
	start_philosophing(philo);
	free(philo);
	return (0);
}
