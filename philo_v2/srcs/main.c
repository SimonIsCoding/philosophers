/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 16:44:46 by simarcha          #+#    #+#             */
/*   Updated: 2024/09/02 14:47:49 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

//je veux creer une fonction qui m'imprimes quel philo a pris un fourchette
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
	printf("philo_thread_id = %i\n", philo->thread_id);
	printf("nb_philo = %i\n", philo->nb_philo);
	printf("time_to_die = %i\n", philo->time_to_die);
	printf("time_to_eat = %i\n", philo->time_to_eat);
	printf("time_to_sleep = %i\n", philo->time_to_sleep);
	printf("nb_must_eat = %i\n", philo->nb_must_eat);
	printf("start = %li\n", timestamp_in_ms(philo->start));
	printf("philo_has_eaten = %i\n", philo->has_eaten);
	printf("_________________\n");
}

/*void	init_philo_struct(t_philo *philo, int i, char **argv)
{
	struct timeval	start;

	philo->thread_id = i + 1;//verifie que le i est bien correct
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
//	return (philo);
}*/

void	very_first_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->right_fork);
	pthread_mutex_lock(philo->print_mutex);
	printf("%li philo %i has taken a fork\n", timestamp_in_ms(philo->start), philo->thread_id);
	pthread_mutex_unlock(philo->print_mutex);
	pthread_mutex_lock(&philo->left_fork);
	pthread_mutex_lock(philo->print_mutex);
	printf("%li philo %i has taken a fork\n", timestamp_in_ms(philo->start), philo->thread_id);
	printf("%li philo %i is eating\n", timestamp_in_ms(philo->start), philo->thread_id);
	precise_usleep(philo->time_to_eat * 1000);
	pthread_mutex_unlock(philo->print_mutex);
	pthread_mutex_lock(philo->print_mutex);
	printf("%li philo %i is sleeping\n", timestamp_in_ms(philo->start), philo->thread_id);
	pthread_mutex_unlock(philo->print_mutex);
	pthread_mutex_unlock(&philo->right_fork);
	pthread_mutex_unlock(&philo->left_fork);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	int		eating_times;

	philo = (t_philo *)arg;
	very_first_meal(philo);
	eating_times = 0;
	while (philo->nb_must_eat == -1 || (eating_times <= philo->nb_must_eat * philo->nb_philo))
	{
		if (eating_times == 0 && philo->thread_id == 1)
		{
		//	continue ;
			//on veut sauter le premier philo qui doit manger car il a deja mange
		}
/*		pthread_mutex_lock(&philo->right_fork);
		pthread_mutex_lock(philo->print_mutex);
		printf("%li philo %i has taken a fork\n", timestamp_in_ms(philo->start), philo->thread_id);
		pthread_mutex_unlock(philo->print_mutex);
		pthread_mutex_lock(&philo->left_fork);
		pthread_mutex_lock(philo->print_mutex);
		printf("%li philo %i has taken a fork\n", timestamp_in_ms(philo->start), philo->thread_id);
		printf("%li philo %i is eating\n", timestamp_in_ms(philo->start), philo->thread_id);
		precise_usleep(philo->time_to_eat * 1000);
		pthread_mutex_unlock(philo->print_mutex);
		philo->has_eaten += 1;
		pthread_mutex_lock(philo->print_mutex);
		printf("%li philo %i is sleeping\n", timestamp_in_ms(philo->start), philo->thread_id);
		pthread_mutex_unlock(philo->print_mutex);
		pthread_mutex_lock(philo->print_mutex);
		printf("%li philo %i is thinking\n", timestamp_in_ms(philo->start), philo->thread_id % philo->nb_philo);
		pthread_mutex_unlock(philo->print_mutex);
		pthread_mutex_unlock(&philo->right_fork);
		pthread_mutex_unlock(&philo->left_fork);
		eating_times++;*/
		
	}
	if (pthread_mutex_lock(&philo->right_fork) == 0)
	{
		
	}
	return (NULL);
}

void	init_threads(t_philo *philo, pthread_mutex_t *forks)
{
	pthread_t		thread[philo->nb_philo];
	int	i;

	i = 0;
	//printf("nb_philo = %i\n", philo->nb_philo);
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
	struct timeval	start;
	int				nb_philo;
	pthread_mutex_t	print_mutex;

	nb_philo = ft_atoi(argv[1]);
	i = -1;
	pthread_mutex_init(&print_mutex, NULL);
	while (++i < nb_philo)
		pthread_mutex_init(&forks[i], NULL);
	//mets a jour le i
	i = -1;
	while (++i < nb_philo)
	{
		philo[i].thread_id = i + 1;//verifie que le i est bien correct
		philo[i].nb_philo = ft_atoi(argv[1]);
		philo[i].time_to_die = ft_atoi(argv[2]);
		philo[i].time_to_eat = ft_atoi(argv[3]);
		philo[i].time_to_sleep = ft_atoi(argv[4]);
		if (argv[5])
			philo[i].nb_must_eat = ft_atoi(argv[5]);
		else
			philo[i].nb_must_eat = -1;
		gettimeofday(&start, NULL);
		philo[i].start = start;
		philo[i].has_eaten = 0;
		philo[i].print_mutex = &print_mutex;
	//	init_philo_struct(&philo[i], i, argv);
		print_philo_struct(&philo[i]);
	}
	init_threads(philo, forks);
	i = -1;
	while (++i < nb_philo)
		pthread_mutex_destroy(&forks[i]);
	pthread_mutex_destroy(&print_mutex);
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