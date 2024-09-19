/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine_breaker.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 16:20:32 by simarcha          #+#    #+#             */
/*   Updated: 2024/09/19 20:19:55 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	checking_death(t_philo *philo)
{
	printf("philo->thread_id = %li\n", philo->thread_id);
	printf("philo->watcher->dead_flag = %p\n", &philo->watcher->dead_flag);
	pthread_mutex_lock(&philo->watcher->dead_mutex);
	if (philo->watcher->dead_flag == 1)
	{
		pthread_mutex_unlock(&philo->watcher->dead_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->watcher->dead_mutex);
	return (0);
}

int	break_conditions(t_philo *philo)
{
	if (checking_death(philo) == 1)
		return (1);
	if (philo->nb_must_eat != -1 && philo->eating_times > philo->nb_must_eat)
		return (1);
	if (timestamp_in_ms(philo->time_last_meal) >= philo->time_to_die)
	{
		pthread_mutex_lock(&philo->watcher->dead_mutex);
		philo->watcher->dead_flag = 1L;
		pthread_mutex_unlock(&philo->watcher->dead_mutex);
		pthread_mutex_lock(&philo->print_mutex);
		printf("\033[1;38;5;214m%li %li is dead\033[0m\n",
			timestamp_in_ms(philo->start_living), philo->thread_id);
		pthread_mutex_unlock(&philo->print_mutex);
		return (1);
	}
	return (0);
}
