/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:58:52 by simarcha          #+#    #+#             */
/*   Updated: 2024/09/13 16:48:05 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	break_conditions(t_philo *philo)
{
	if (philo->nb_must_eat != -1 && philo->eating_times >= philo->nb_must_eat)
		return (1);
	if (timestamp_in_ms(philo->time_last_meal) >= philo->time_to_die)
	{
		pthread_mutex_lock(&philo->print_mutex);
		printf("\033[1;38;5;214m%li %li is dead\033[0m\n",
			timestamp_in_ms(philo->start_living), philo->thread_id);
		pthread_mutex_unlock(&philo->print_mutex);
		pthread_mutex_lock(&philo->monitor->mutex);
		*(philo->monitor->dead_flag) = 1;
		pthread_mutex_unlock(&philo->monitor->mutex);
		return (1);
	}
	return (0);
}

static void	pick_correct_fork(t_philo *philo)
{
	if (philo->left_fork < philo->right_fork)
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(philo->left_fork);
	}
}

static void	eat(t_philo *philo)
{
	struct timeval	reset;

	pick_correct_fork(philo);
	pthread_mutex_lock(&philo->print_mutex);
	printf("\033[1;38;5;196m%li %li has taken a fork\033[0m\n",
		timestamp_in_ms(philo->start_living), philo->thread_id);
	printf("\033[1;38;5;196m%li %li has taken a fork\033[0m\n",
		timestamp_in_ms(philo->start_living), philo->thread_id);
	printf("\033[1;38;5;93m%li %li is eating\033[0m\n",
		timestamp_in_ms(philo->start_living), philo->thread_id);
	precise_usleep(philo->time_to_eat * 1000);
	gettimeofday(&reset, NULL);
	philo->time_last_meal = reset;
	philo->eating_times++;
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(&philo->print_mutex);
}

static void	philo_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->print_mutex);
	printf("\033[1;38;5;46m%li %li is sleeping\033[0m\n",
		timestamp_in_ms(philo->start_living), philo->thread_id);
	precise_usleep(philo->time_to_sleep * 1000);
	pthread_mutex_unlock(&philo->print_mutex);
}

static void	think(t_philo *philo)
{
	if (philo->nb_philo % 2 == 0 && philo->time_to_eat > philo->time_to_sleep)
	{
		pthread_mutex_lock(&philo->print_mutex);
		printf("\033[1;38;5;21m%li %li is thinking\033[0m\n",
			timestamp_in_ms(philo->start_living), philo->thread_id);
		precise_usleep((philo->time_to_eat - philo->time_to_sleep) * 1000);
		pthread_mutex_unlock(&philo->print_mutex);
	}
	if (philo->nb_philo % 2 == 1)
	{
		pthread_mutex_lock(&philo->print_mutex);
		printf("\033[1;38;5;21m%li %li is thinking\033[0m\n",
			timestamp_in_ms(philo->start_living), philo->thread_id);
		precise_usleep((philo->time_to_eat * 2 - philo->time_to_sleep) * 1000);
		pthread_mutex_unlock(&philo->print_mutex);
	}
}

void *philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while(1)
	{
		if (break_conditions(philo) == 1)
			break ;
		eat(philo);
		philo_sleep(philo);
		think(philo);
	}
	return (NULL);
}

void	*observer_routine(void *arg)
{
	t_monitor	*monitor;

	monitor = (t_monitor *)arg;
	while (1)
	{
		if (*(monitor->dead_flag) == 1)
			break ;
	}
	return (NULL);
}
