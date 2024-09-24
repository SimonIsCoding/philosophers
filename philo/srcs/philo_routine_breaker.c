/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine_breaker.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 16:20:32 by simarcha          #+#    #+#             */
/*   Updated: 2024/09/24 14:35:40 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	checking_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->watcher->dead_mutex);
	if (philo->watcher->dead_flag == 1)
	{
		pthread_mutex_unlock(&philo->watcher->dead_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->watcher->dead_mutex);
	return (0);
}

//If one philo is dead, we return 1 to break the philo_routine function
//If every philo has eaten the good amount of time, we go out of the routine
//If one philo is about to die, we change the value of our flag and we go out
//of the routine function
//Otherwise, everthing is good and we return 0, meaning that we continue
//the philo_routine
int	break_conditions(t_philo *philo)
{
	if (checking_death(philo) == 1)
		return (1);
	if (philo->nb_must_eat != -1 && philo->eating_times >= philo->nb_must_eat)
		return (1);
	if (timestamp_in_ms(philo->time_last_meal) >= philo->time_to_die)
	{
		pthread_mutex_lock(&philo->watcher->dead_mutex);
		philo->watcher->dead_flag = 1L;
		pthread_mutex_unlock(&philo->watcher->dead_mutex);
		pthread_mutex_lock(&philo->print_mutex);
		write_dead_msg(philo);
		pthread_mutex_unlock(&philo->print_mutex);
		return (1);
	}
	return (0);
}
