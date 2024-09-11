/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:58:52 by simarcha          #+#    #+#             */
/*   Updated: 2024/09/11 13:00:20 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	break_conditions(t_philo *philo)
{
	if (philo->nb_must_eat != -1 && philo->eating_times >= philo->nb_must_eat)
		return (1);
	else if (timestamp_in_ms(philo->time_last_meal) >= philo->time_to_die)
	{
		pthread_mutex_lock(&philo->print_mutex);
		printf("\033[1;38;5;214m%li %li is dead ⚰️\033[0m\n",
			timestamp_in_ms(philo->start_living), philo->thread_id);
		pthread_mutex_unlock(&philo->print_mutex);
		return (1);
	}
	return (0);
}

void	eat(t_philo *philo)
{
	struct timeval	reset;

//	printf("thread_id = %li\n", philo->thread_id);
//	printf("---------------we are in eat function--------------------\n");
//	print_philo(philo);
//	fflush(stdout);
	pthread_mutex_lock(&philo->print_mutex);
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(philo->right_fork);
	printf("\033[1;38;5;196m%li %li has taken 1° fork 🍴\033[0m\n",
		timestamp_in_ms(philo->start_living), philo->thread_id);
	printf("\033[1;38;5;196m%li %li has taken 2° fork 🍴\033[0m\n",
		timestamp_in_ms(philo->start_living), philo->thread_id);
	printf("\033[1;38;5;93m%li %li is eating 🍝\033[0m\n",
		timestamp_in_ms(philo->start_living), philo->thread_id);
	precise_usleep(philo->time_to_eat * 1000);
	gettimeofday(&reset, NULL);
	philo->time_last_meal = reset;
	philo->eating_times++;
	//sleep(2);
	//printf("reached l.44 - philo_routine.c\n");
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(&philo->print_mutex);
}

void	philo_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->print_mutex);
	printf("\033[1;38;5;46m%li %li is sleeping 😴\033[0m\n", timestamp_in_ms(philo->start_living), philo->thread_id);
	precise_usleep(philo->time_to_sleep * 1000);
	pthread_mutex_unlock(&philo->print_mutex);
}

void	think(t_philo *philo)
{
	pthread_mutex_lock(&philo->print_mutex);
	if ((philo->thread_id + 1) % philo->nb_philo != 0)
		//printf("%li %li is thinking\n", timestamp_in_ms(philo->start_living), ((philo->thread_id + 1) % philo->nb_philo));
	printf("\033[1;38;5;21m%li %li is thinking 💭\033[0m\n", timestamp_in_ms(philo->start_living), philo->thread_id);
	pthread_mutex_unlock(&philo->print_mutex);
}

void *philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while(1)
	{
		// if (philo->thread_id % 2 == 0)
		// {
		// 	usleep(1);
		// 	sleep(5);
		// }
		//usleep(510 * 1000);
		if (break_conditions(philo) == 1)
			break ;
//		printf("reached l.78 - philo_routine.c\n");
		eat(philo);
//		printf("reached l.79 - philo_routine.c\n");
		philo_sleep(philo);
		think(philo);
	}
	return (NULL);
}