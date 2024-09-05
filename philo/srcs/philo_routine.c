/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:58:52 by simarcha          #+#    #+#             */
/*   Updated: 2024/09/05 19:40:43 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	break_conditions(t_philo *philo, int eating_times)
{
	if (philo->nb_must_eat != -1 && eating_times >= philo->nb_must_eat)
		return (1);
	else if (timestamp_in_ms(philo->time_last_meal) >= philo->time_to_die)
	{
		pthread_mutex_lock(&philo->print_mutex);
		printf("%li %i is dead\n", timestamp_in_ms(philo->start_living), philo->thread_id);
		pthread_mutex_unlock(&philo->print_mutex);
		return (1);
	}
	return (0);
}

void *philo_routine(void *arg)
{
	t_philo			*philo;
	int				eating_times;
	struct timeval	reset;

	eating_times = 0;
	philo = (t_philo *)arg;
	while (1)
	{
		//usleep(510 * 1000);
		if (break_conditions(philo, eating_times) == 1)
			break ;
		pthread_mutex_lock(&philo->print_mutex);
		pthread_mutex_lock(&philo->left_fork);
		pthread_mutex_lock(&philo->right_fork);
		printf("%li %i has taken a fork\n", timestamp_in_ms(philo->start_living), philo->thread_id);
		printf("%li %i has taken a fork\n", timestamp_in_ms(philo->start_living), philo->thread_id);
		printf("%li %i is eating\n", timestamp_in_ms(philo->start_living), philo->thread_id);
		pthread_mutex_unlock(&philo->print_mutex);
		precise_usleep(philo->time_to_eat * 1000);
		gettimeofday(&reset, NULL);
		philo->time_last_meal = reset;
		pthread_mutex_lock(&philo->print_mutex);
		printf("%li %i is sleeping\n", timestamp_in_ms(philo->start_living), philo->thread_id);
		pthread_mutex_unlock(&philo->left_fork);
		pthread_mutex_unlock(&philo->right_fork);
		pthread_mutex_unlock(&philo->print_mutex);
		precise_usleep(philo->time_to_sleep * 1000);
		eating_times++;
	}
	return (NULL);
}