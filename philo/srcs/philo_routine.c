/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:58:52 by simarcha          #+#    #+#             */
/*   Updated: 2024/09/18 16:20:53 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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

	if (checking_death(philo) == 1)
		return ;
	pick_correct_fork(philo);
	pthread_mutex_lock(&philo->print_mutex);
	printf("\033[1;38;5;196m%li %li has taken a fork\033[0m\n",
		timestamp_in_ms(philo->start_living), philo->thread_id);
	printf("\033[1;38;5;196m%li %li has taken a fork\033[0m\n",
		timestamp_in_ms(philo->start_living), philo->thread_id);
	printf("\033[1;38;5;93m%li %li is eating\033[0m\n",
		timestamp_in_ms(philo->start_living), philo->thread_id);
	gettimeofday(&reset, NULL);
	philo->time_last_meal = reset;
	precise_usleep(philo->time_to_eat * 1000);
	philo->eating_times++;
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(&philo->print_mutex);
}

static void	philo_sleep(t_philo *philo)
{
	if (checking_death(philo) == 1)
		return ;
	pthread_mutex_lock(&philo->print_mutex);
	printf("\033[1;38;5;46m%li %li is sleeping\033[0m\n",
		timestamp_in_ms(philo->start_living), philo->thread_id);
	precise_usleep(philo->time_to_sleep * 1000);
	pthread_mutex_unlock(&philo->print_mutex);
}

static void	think(t_philo *philo)
{
	if (checking_death(philo) == 1)
		return ;
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

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (checking_death(philo) == 0)
	{
		eat(philo);
		if (break_conditions(philo) == 1)
			break ;
		philo_sleep(philo);
		if (break_conditions(philo) == 1)
			break ;
		think(philo);
	}
	return (NULL);
}
