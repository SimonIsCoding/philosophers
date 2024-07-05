/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 12:09:47 by simarcha          #+#    #+#             */
/*   Updated: 2024/07/05 14:34:06 by simarcha         ###   ########.fr       */
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
	long 			sec;
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

void	philo_taking_fork(t_philo *philo)
{
	int	total_fork = philo->nb_philo;

	philo->left_fork = 1;
	printf("%li %i has taken a fork\n", timestamp_in_ms(philo->start_living), philo->thread_id);
	total_fork--;
	philo->right_fork = 1;
	printf("%li %i has taken a fork\n", timestamp_in_ms(philo->start_living), philo->thread_id);
	total_fork--;
	if (total_fork < 0)
		printf("total_fork = %i\n", total_fork);
	return ;
}

void	philo_start_eating(t_philo *philo)
{
	//if (philo->thread_id == 1 && philo->left_fork == 1 && philo->right_fork == 1)
	//	printf("%li %i is eating\n", timestamp_in_ms(philo->start_living), philo->thread_id);

}

void	*philo_routine(void *arg)
{
	static int		i = 1;
	t_philo			*philo;
	pthread_mutex_t	mutex;

	pthread_mutex_init(&mutex, NULL);
	philo = (t_philo *)arg;
	if (i % 2 == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
		philo_taking_fork(philo);
		philo_start_eating(philo);
		pthread_mutex_unlock(&mutex);
	}
	i++;
	pthread_mutex_destroy(&mutex);
	return (NULL);
}

int	init_threads(t_philo *philo)
{
	int			i;
	pthread_t	thread[philo->nb_philo];

	i = 0;
	while (i < philo->nb_philo)
	{
		philo->thread_id = i;
		printf("philo->thread_id = %i\n", philo->thread_id);
		if (pthread_create(&thread[i], NULL, &philo_routine, philo) == -1)
		{
			return (-1);
		}
		i++;
	}
	printf("this is a test\n");
	i = 0;
	while (i < philo->nb_philo)
	{
		if (pthread_join(thread[i], NULL) == -1)
			return (-1);
		i++;
	}
	return (0);
}

int	start_philosophing(t_philo *philo)
{
	if (philo->nb_philo == 1)
		return (dying_state_for_one_philo(philo), 0);
	if (philo->nb_philo % 2 == 0)
	{
		printf("threads\n");
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
