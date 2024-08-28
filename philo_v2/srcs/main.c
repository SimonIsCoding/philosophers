/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 16:44:46 by simarcha          #+#    #+#             */
/*   Updated: 2024/08/28 21:50:22 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

//je veux creer une fonction qui m'imprimes quel philo a ris un fourchette
//avant je devrais mettre le temps qui s'est ecoule avant cette action

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

void	print_philo_struct(t_philo *philo)
{
	printf("nb_philo = %i\n", philo->nb_philo);
	printf("time_to_die = %i\n", philo->time_to_die);
	printf("time_to_eat = %i\n", philo->time_to_eat);
	printf("time_to_sleep = %i\n", philo->time_to_sleep);
	printf("nb_must_eat = %i\n", philo->nb_must_eat);
	printf("start = %li\n", timestamp_in_ms(philo->start));
}

t_philo	*init_philo_struct(t_philo *philo, int i, char **argv)
{
	struct timeval	start;

	philo->thread_id = i + 1;
	philo->nb_philo = ft_atoi(argv[1]);
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		philo->nb_must_eat = ft_atoi(argv[5]);
	else
		philo->nb_must_eat = -1;
	gettimeofday(&start, NULL);
	philo->start = start;
//	print_philo_struct(philo);
	return (philo);
}

//	while (philo->nb_must_eat >= 0 && i < philo->eat)
void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	
	pthread_mutex_lock(&philo->left_fork);
	printf("philo 1 has taken a fork\n");
	pthread_mutex_unlock(&philo->left_fork);

//	printf("we are in routine\n");
//	sleep(3);
//	printf("end routine\n");
	return (NULL);
}

void	init_threads(t_philo *philo, pthread_mutex_t *forks/*, char **argv*/)
{
	pthread_t		thread[philo->nb_philo];
	int	i;

	i = 0;
	while (i < philo->nb_philo)
	{
		philo->left_fork = forks[i];
		philo->right_fork = forks[(i + 1) % philo->nb_philo];
		pthread_create(&thread[i], NULL, &routine, &philo[i]);
		i++;
	}
	i = 0;
	while (i < philo->nb_philo)
	{
		pthread_join(thread[i], NULL);
		i++;
	}
}

int	main(int argc, char **argv)
{
	pthread_mutex_t	forks[ft_atoi(argv[1])];
	t_philo			philo[ft_atoi(argv[1])];
	int				i;
	
	i = -1;
	while (++i < philo->nb_philo)
		pthread_mutex_init(&forks[i], NULL);
	init_philo_struct(&philo[i], i, argv);
	print_philo_struct(&philo[i]);
	init_threads(philo, forks);//, argv);
	i = -1;
	while (++i < philo->nb_philo)
		pthread_mutex_destroy(&forks[i]);
	argc = 0;
	return (0);
}

//Objectif:
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
400 2 is sleeping
400 1 is thinking
400 1 has taken a fork
400 1 has taken a fork
400 1 is eating
600 1 is sleeping
600 2 is thinking
600 2 has taken a fork
600 2 has taken a fork
600 2 is eating
800 2 is sleeping
800 1 is thinking
800 1 has taken a fork
800 1 has taken a fork
800 1 is eating
1000 1 is sleeping
1000 2 is thinking
...
*/