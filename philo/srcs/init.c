/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 12:04:40 by simarcha          #+#    #+#             */
/*   Updated: 2024/09/18 16:06:59 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_philo	*init_philo_struct(char **argv, t_big *watch)//to free once used
{
	int				philo_nb;
	t_philo			*philo;
	struct timeval	start;
	int				i;

	
	philo_nb = ft_atoi(argv[1]);
	philo = malloc(sizeof(t_philo) * philo_nb);
	if (!philo)
		return (write(2, "Error malloc", 13), NULL);
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
		philo[i].time_last_meal = start;
		philo[i].eating_times = 0;
		philo[i].watcher = watch;
//		printf("i = %i\n", i);
//		philo[i].dead_flag = dead_flag;
//		printf("philo[i].dead_flag memory address = %p\n", (void *)philo[i].dead_flag);
//		printf("philo[i].dead_flag value = %li\n", *philo[i].dead_flag);
	}
	return (philo);
}

pthread_mutex_t	*init_forks(t_philo *philo)//to free once used
{
	pthread_mutex_t	*forks;
	int				i;

	forks = malloc(sizeof(pthread_mutex_t) * philo->nb_philo);
	if (!forks)
		return (write(2, "Error malloc\n", 13), NULL);
	i = -1;
	while (++i < philo->nb_philo)
	{
		pthread_mutex_init(&forks[i], NULL);
		philo[i].left_fork = &forks[i];
		philo[i].right_fork = &forks[(i + 1) % philo->nb_philo];
	}
	return (forks);
}

//une fois que tu initialises le mutex, il faut que tu le mettes dans ta 
//structure philo comme ca tu definies le mutex correspondant a la fourchette
//droite et gauche pour chaque philo
//it takes more ms to create an array of threads with malloc
int	init_threads(t_philo *philo)
{
	int			i;
	pthread_t	*thread;

	i = -1;
	thread = malloc(sizeof(pthread_t) * philo->nb_philo);
	if (!thread)
		return (write(2, "Error malloc\n", 13), -1);
	pthread_mutex_init(&philo->print_mutex, NULL);
	pthread_mutex_init(&philo->watcher->dead_mutex, NULL);
	while (++i < philo->nb_philo)
	{
		if (pthread_create(&thread[i], NULL, &philo_routine, &philo[i]) == -1)
			return (-1);
	}
	i = -1;
	while (++i < philo->nb_philo)
	{
		if (pthread_join(thread[i], NULL) == -1)
			return (-1);
	}
	free(thread);
	return (0);
}

/*This function was to check if all philo were well configured
void	print_philo(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo->nb_philo)
	{
		printf("thread_id = %li\n", philo[i].thread_id);
		printf("philo_nb = %li\n", philo[i].nb_philo);
		printf("time_to_die = %li\n", philo[i].time_to_die);
		printf("time_to_eat = %li\n", philo[i].time_to_eat);
		printf("time_to_sleep = %li\n", philo[i].time_to_sleep);
		printf("nb_must_eat = %li\n", philo[i].nb_must_eat);
		printf("start_living = %li\n", timestamp_in_ms(philo[i].start_living));
		printf("______________________\n");
	}
}*/