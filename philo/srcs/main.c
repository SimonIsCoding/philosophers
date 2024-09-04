/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 12:09:47 by simarcha          #+#    #+#             */
/*   Updated: 2024/09/04 18:00:30 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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

/*void	philo_sleeping(t_philo *philo)
{
	printf("%li %i is sleeping\n", timestamp_in_ms(philo->start_living), philo->thread_id);
	precise_usleep(philo->time_to_sleep * 1000);
}*/

/*void	philo_taking_fork(t_philo *philo)
{
	int			total_fork;

	total_fork = philo->nb_philo;
	pthread_mutex_lock(&philo->left_fork);
	pthread_mutex_lock(&philo->right_fork);
	printf("%li %i has taken a fork\n", timestamp_in_ms(philo->start_living), philo->thread_id);
	printf("%li %i has taken a fork\n", timestamp_in_ms(philo->start_living), philo->thread_id);
	printf("%li %i is eating\n", timestamp_in_ms(philo->start_living), philo->thread_id);
	precise_usleep(philo->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->left_fork);
	pthread_mutex_unlock(&philo->right_fork);
	return ;
}*/

void	*philo_routine(void *arg)
{
	t_philo			*philo;

	philo = (t_philo *)arg;

	while (1)
	{
		printf("philo->thread_id = %i\n", philo->thread_id);// probleme
		pthread_mutex_lock(philo->print_mutex);
		printf("%li philo %i has taken a fork\n", timestamp_in_ms(philo->start_living), philo->thread_id);
		pthread_mutex_unlock(philo->print_mutex);
		break ;
	}
	return (NULL);
}

int	init_threads(t_philo *philo)
{
	int			i;
	pthread_t	thread[philo->nb_philo];

	i = 0;
	printf("init_threads\n");
	while (i < philo->nb_philo)
	{
		philo->thread_id = i;
		printf("init_threads 2\n");
		if (pthread_create(&thread[i], NULL, &philo_routine, &philo) == -1)
			return (-1);
		i++;
	}
	printf("init_threads 3\n");
	i = 0;
	while (i < philo->nb_philo)
	{
		if (pthread_join(thread[i], NULL) == -1)
			return (-1);
		i++;
	}
	printf("init_threads 4\n");
	return (0);
}

t_philo	*init_philo_struct(char **argv)//to free once used
{
	int				philo_nb;
	t_philo			*philo;
	struct timeval	start;
	int				i;

	philo_nb = ft_atoi(argv[1]);
	philo = malloc(sizeof(t_philo) * philo_nb);
	if (!philo)
		return (write(2, "Error malloc - main.c l.184\n", 29), NULL);
	i = -1;
	while (++i < philo_nb)
	{
		philo[i].thread_id = i + 1;
		philo[i].nb_philo = philo_nb;
		philo[i].time_to_die = ft_atoi(argv[2]);
		philo[i].time_to_eat = ft_atoi(argv[3]);
		philo[i].time_to_sleep = ft_atoi(argv[4]);
		if (argv[5])
			philo[i].nb_must_eat = ft_atoi(argv[5]);
		else
			philo[i].nb_must_eat = -1;
		gettimeofday(&start, NULL);
		philo[i].start_living = start;
	}
	return (philo);
}

void	print_philo(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo->nb_philo)
	{
		printf("______________________\n");
		printf("thread_id = %i\n", philo[i].thread_id);
		printf("philo_nb = %i\n", philo[i].nb_philo);
		printf("time_to_die = %i\n", philo[i].time_to_die);
		printf("time_to_eat = %i\n", philo[i].time_to_eat);
		printf("time_to_sleep = %i\n", philo[i].time_to_sleep);
		printf("nb_must_eat = %i\n", philo[i].nb_must_eat);
		printf("start_living = %li\n", timestamp_in_ms(philo[i].start_living));
	}
}

pthread_mutex_t	*init_forks(t_philo *philo)
{
	pthread_mutex_t	*forks;
	int				i;

//	pthread_mutex_init(philo->print_mutex, NULL);
	i = -1;
	forks = malloc(sizeof(pthread_mutex_t) * philo->nb_philo);
	if (!forks)
		return (NULL);
	while (++i < philo->nb_philo)
		pthread_mutex_init(&forks[i], NULL);
	return (forks);
}

int	start_philosophing(t_philo *philo)
{
	if (philo->nb_philo == 1)
		return (dying_state_for_one_philo(philo), 0);
	if (init_threads(philo) == -1)
		return (-1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo			*philo;
	pthread_mutex_t	*forks;

	if (check_error(argc, argv) == 1)
		return (1);
	philo = init_philo_struct(argv);//to free once used
	printf("1\n");
	print_philo(philo);
	printf("2\n");
	forks = init_forks(philo);//to free once used
	printf("3\n");
	start_philosophing(philo);//=>init_threads
	printf("4\n");
	free(philo);
	free(forks);
	return (0);
}
