/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:58:52 by simarcha          #+#    #+#             */
/*   Updated: 2024/09/20 14:20:34 by simarcha         ###   ########.fr       */
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
	print(philo, FORK);
	print(philo, FORK);
	print(philo, EAT);
	gettimeofday(&reset, NULL);
	philo->time_last_meal = reset;
	precise_usleep(philo->time_to_eat * 1000);
	philo->eating_times++;
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

static void	philo_sleep(t_philo *philo)
{
	if (checking_death(philo) == 1)
		return ;
	print(philo, SLEEP);
	precise_usleep(philo->time_to_sleep * 1000);
}

static void	think(t_philo *philo)
{
	if (checking_death(philo) == 1)
		return ;
	if (philo->nb_philo % 2 == 0 && philo->time_to_eat > philo->time_to_sleep)
	{
		print(philo, THINK);
		precise_usleep((philo->time_to_eat - philo->time_to_sleep) * 1000);
	}
	if (philo->nb_philo % 2 == 1)
	{
		print(philo, THINK);
		precise_usleep((philo->time_to_eat * 2 - philo->time_to_sleep) * 1000);
	}
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (break_conditions(philo) == 0)
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
