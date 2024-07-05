/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 12:09:47 by simarcha          #+#    #+#             */
/*   Updated: 2024/07/05 12:16:58 by simarcha         ###   ########.fr       */
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
/*	
	struct timeval	end;

	printf("start.tv_usec = %li\n", start.tv_usec);
	precise_usleep(2 * 1000000);
	gettimeofday(&end, NULL);
	printf("end.tv_usec = %li\n", end.tv_usec);*/
	return (philo);
}

//philo->start_living = start;
//print_philo_parameter(philo);
void	*philo_routine(void *arg)
{
	arg = NULL;
	printf("hola from the thread nb 1\n");
	return (NULL);
}

int	init_threads(t_philo *philo)
{
	int			i;
	pthread_t	thread[philo->nb_philo];

	i = 0;
	while (i < philo->nb_philo)
	{
		if (pthread_create(&thread[i], NULL, &philo_routine, NULL) == -1)
			return (-1);
		i++;
	}
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
		dying_state_for_one_philo(philo);
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

long	timestamp_in_ms(struct timeval start)
{
	struct timeval	end;
	long int		sec;
	long int		usec;
	long int		elapsed_time_in_ms;
//	long int		elapsed_time_in_us;
//	long int		elapsed_time_in_sec;

	gettimeofday(&end, NULL);
	sec = end.tv_sec - start.tv_sec;
	usec = end.tv_usec - start.tv_usec;
//	elapsed_time_in_us = (sec * 1000000L) + (usec);
	elapsed_time_in_ms = (sec * 1000L) + (usec / 1000L);
//	elapsed_time_in_sec = (sec) + (usec / 1000000L);
	return (elapsed_time_in_ms);
}

int	main(int argc, char **argv)
{
	t_philo	*philo;

	if (check_error(argc, argv) == 1)
		return (1);
	philo = init_philo_struct(argv);
	start_philosophing(philo);
	//precise_usleep(1 * 1000000);
	free(philo);
	return (0);
}
