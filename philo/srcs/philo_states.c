/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_states.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 12:31:22 by simarcha          #+#    #+#             */
/*   Updated: 2024/07/04 18:03:25 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/*void	print_mutexed(t_philo *philo)
{
	pthread_mutex_lock(philo->mutex);
	
	pthread_mutex_unlock(philo->mutex);
}*/

void	dying_state_for_one_philo(t_philo *philo)
{
	struct timeval	stop;

	precise_usleep(philo->time_to_die * 1000);
	gettimeofday(&stop, NULL);
	printf("stop.tv_usec = %li\n", stop.tv_usec);
	printf("philo->start_living.tv_usec = %li\n", philo->start_living.tv_usec);
	printf("la difference des deux = %li\n", philo->start_living.tv_usec);
	philo->timestamp_in_ms = (stop.tv_usec - philo->start_living.tv_usec);
	printf("%li 1 died\n", philo->timestamp_in_ms);
	//philo->timestamp_in_ms = ;
	//printf("philo->timestamp_in_ms = %i\n", philo->timestamp_in_ms);
	return ;
}

/*
void	eating_state(t_philo *philo)
{
	
}

void	thinking_state(t_philo *philo)
{
	
}

void	sleeping_state(t_philo *philo)
{
	
}

void	dying_state(t_philo *philo)
{

}*/